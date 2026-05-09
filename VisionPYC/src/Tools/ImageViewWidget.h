#pragma once

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QPointF>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <opencv2/opencv.hpp>
#include <vector>

class ImageViewWidget : public QWidget
{
	Q_OBJECT
public:

	enum GrayscalePattern {
		HIST_BINARY,            // 阈值输出
		HIST_MINMAX                // 归一化输出
	};

	GrayscalePattern m_GrayscalePattern = HIST_BINARY;//输出图像模式
	explicit ImageViewWidget(QWidget* parent = nullptr);

	bool loadImage(const QString& filePath);  // 打开图像（不支持中文路径）
	void setImage(const QImage& image);       // 设置图像（外部传入）
	void updatedisplayMat(const cv::Mat& mat); //图像显示接口

	const QImage& image() const { return m_image; } // 获取当前图像
	// 外部访问接口
	cv::Mat getCurrentImage() const { return m_cvImage.clone(); }
	bool hasImage() const { return !m_cvImage.empty(); }

	void displayMat(int mode, const cv::Mat& mat);//外部直接访问 0访问原始图像并显示 1外部临时图像显示

	void GrayscalePatternImage(int minVal, int maxVal);//阈值分割 && 归一化增强对比度

	void setGrayscalePattern(GrayscalePattern Pat) { m_GrayscalePattern = Pat; }; //设置图像显示模式

	// ===================== 新增一维测量接口 =====================
	struct MeasurePoint {
		QPointF position;
		bool valid;
	};

	// 
	/**
	 * @brief                    设置一维测量参数
	 * @param rectWidth            设置测量高度
	 * @param lineSpacing        设置测量间距
	 * @param pixelThreshold    变化梯度阈值
	 * @param lineDirection        测量方向
	 */
	void setOneDMeasureParams(int rectWidth, double lineSpacing,
		int pixelThreshold = 20, int lineDirection = 0);

	// 获取捕捉到的点
	std::vector<MeasurePoint> getMeasurePoints() const { return m_measurePoints; }

	// 清除测量结果
	void clearMeasureResults();

	// 启用/禁用测量工具
	void enableMeasureTool(bool enable) { m_measureToolEnabled = enable; update(); }

	// ===================== 新增矩形框绘制接口 =====================
	struct RectangleTool {
		QPointF center;              // 矩形中心
		double width = 100;          // 矩形宽度
		double height = 80;          // 矩形高度
		double angle = 0;            // 旋转角度（弧度）
		bool isSelected = false;     // 是否被选中
		int id = 0;                  // 矩形ID
	};

	/**
	 * @brief                    添加矩形框
	 * @param center            矩形中心位置
	 * @param width            矩形宽度
	 * @param height            矩形高度
	 * @param angle            旋转角度（弧度）
	 * @return int             矩形ID
	 */
	int addRectangle(int recendID, const QPointF& center, double width, double height, double angle = 0);

	/**
	 * @brief                    移除矩形框
	 * @param id                矩形ID
	 */
	void removeRectangle(int id);

	/**
	 * @brief                    清除所有矩形框
	 */
	void clearRectangles();

	/**
	 * @brief                    设置矩形框剪切模式
	 * @param cropInside        true:剪切矩形内部, false:剪切矩形外部
	 */
	void setRectangleCropMode(bool cropInside) { m_rectangleCropInside = cropInside; }

	/**
	 * @brief                    根据矩形框剪切图像
	 * @param id                矩形ID
	 * @return cv::Mat         剪切后的图像
	 */
	cv::Mat cropImageByRectangle(int id);

	// 启用/禁用矩形工具
	void enableRectangleTool(bool enable) { m_rectangleToolEnabled = enable; update(); }

	// ===================== 新增圆弧测量接口 =====================
	struct ArcMeasureTool {
		QPointF center;              // 圆弧中心
		double radius = 100;         // 圆弧半径
		double startAngle = 0;       // 起始角度（弧度，0度在右侧，逆时针为正）
		double endAngle = -M_PI * 1.5; // 结束角度（弧度），默认3/4圆（逆时针）
		double thickness = 30;       // 圆弧厚度
		bool isSelected = false;     // 是否被选中
		int id = 0;                  // 圆弧ID
	};

	struct ArcMeasurePoint {
		QPointF position;            // 点的位置（图像坐标）
		double angle;                // 点的角度位置（弧度）
		bool valid;                  // 是否有效
	};

	/**
	 * @brief                    添加圆弧测量工具
	 * @param center            圆弧中心
	 * @param radius            圆弧半径
	 * @param startAngle        起始角度（弧度）
	 * @param endAngle          结束角度（弧度）
	 * @param thickness         圆弧厚度
	 * @return int             圆弧ID
	 */
	int addArcMeasure(const QPointF& center = QPointF(), double radius = 100,
		double startAngle = 0, double endAngle = -M_PI * 1.5,
		double thickness = 30);

	/**
	 * @brief                    设置圆弧测量参数
	 * @param id                圆弧ID
	 * @param angleSpacing      角度间距（弧度）
	 * @param pixelThreshold    像素变化阈值
	 * @param direction         测量方向 (0: 从内到外, 1: 从外到内，默认1)
	 */
	void setArcMeasureParams(int id, double angleSpacing, int pixelThreshold = 20, int direction = 1);

	/**
	 * @brief                    获取圆弧测量点（float类型输出）
	 * @param id                圆弧ID
	 * @return std::vector<std::pair<float, float>> 测量点集合(x, y)
	 */
	std::vector<std::pair<float, float>> getArcMeasurePoints(int id) const;

	/**
	 * @brief                    设置测量点显示开关
	 * @param id                圆弧ID
	 * @param show              true显示，false隐藏
	 */
	void setArcMeasurePointsVisible(int id, bool show);

	/**
	 * @brief                    移除圆弧测量工具
	 * @param id                圆弧ID
	 */
	void removeArcMeasure(int id);

	/**
	 * @brief                    清除所有圆弧测量工具
	 */
	void clearArcMeasures();

	// 启用/禁用圆弧测量工具
	void enableArcMeasureTool(bool enable) { m_arcMeasureToolEnabled = enable; update(); }

protected:
	// Qt事件重载
	void paintEvent(QPaintEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;//拖拽加载
	void dropEvent(QDropEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event);

private:
	void fitToWidget();       // 自适应控件大小
	void updateScaledImage(bool keepOffset); // 更新缩放后图像
	void fitImageToWidget();  // 重置图像显示
	void showOriginalImage(); //显示原始图像
	void clearImage();        //清空图像

	// ===================== 新增一维测量私有方法 =====================
	void drawMeasureTool(QPainter& painter);  // 绘制测量工具
	void updateMeasurePoints();               // 更新测量点
	QPointF imageToWidget(const QPointF& imagePoint) const; // 图像坐标转控件坐标
	QPointF widgetToImage(const QPointF& widgetPoint) const; // 控件坐标转图像坐标
	bool isPointOnArrowHead(const QPointF& widgetPoint) const; // 判断是否在箭头头部
	bool isPointOnArrowTail(const QPointF& widgetPoint) const; // 判断是否在箭头尾部
	bool isPointOnRectEdge(const QPointF& widgetPoint) const; // 判断是否在矩形边缘
	bool isPointOnRectCenter(const QPointF& widgetPoint) const; // 判断是否在矩形中心区域
	void updateMeasureRect(); // 更新测量矩形

	// ===================== 新增矩形框绘制私有方法 =====================
	void drawRectangleTool(QPainter& painter); // 绘制矩形工具
	bool isPointOnRectangleCenter(const QPointF& widgetPoint, int rectIndex) const; // 判断是否在矩形中心
	int isPointOnRectangleCorner(const QPointF& widgetPoint, int rectIndex) const; // 判断是否在矩形顶点,返回顶点索引(-1表示不在顶点上)
	bool isPointOnRectangleRotateHandle(const QPointF& widgetPoint, int rectIndex) const; // 判断是否在旋转控制点
	void updateRectangle(int index);           // 更新矩形

	// ===================== 新增圆弧测量私有方法 =====================
	void drawArcMeasureTool(QPainter& painter); // 绘制圆弧测量工具
	void updateArcMeasurePoints(int arcIndex);  // 更新圆弧测量点
	bool isPointOnArcCenter(const QPointF& widgetPoint, int arcIndex) const;     // 判断是否在圆弧中心
	bool isPointOnArcRadius(const QPointF& widgetPoint, int arcIndex) const;     // 判断是否在有效圆弧上（用于拖动半径）
	bool isPointOnArcStartHandle(const QPointF& widgetPoint, int arcIndex) const; // 判断是否在起始角度控制点
	bool isPointOnArcEndHandle(const QPointF& widgetPoint, int arcIndex) const;   // 判断是否在结束角度控制点
	bool isPointOnArcThicknessHandle(const QPointF& widgetPoint, int arcIndex, bool& isInner) const; // 判断是否在厚度控制点（内圆或外圆弧线）
	void updateArcMeasure(int index);          // 更新圆弧测量
	double normalizeAngle(double angle) const; // 规范化角度到[-π, π]范围

private:
	QImage m_image;           // 当前显示图像
	cv::Mat m_cvImage;        // 原始OpenCV图像
	QPixmap m_scaledPixmap;   // 当前缩放后的pixmap

	double m_scaleFactor = 1.0;   // 缩放比例
	QPoint m_lastMousePos;      // 鼠标拖动记录
	QPointF m_offset;             // 平移偏移量
	bool m_dragging = false;      // 是否正在拖动

	// ===================== 新增一维测量私有成员 =====================
	bool m_measureToolEnabled = false;        // 测量工具是否启用
	QPointF m_arrowStart;                     // 箭头起点（图像坐标）
	QPointF m_arrowEnd;                       // 箭头终点（图像坐标）
	int m_rectWidth = 50;                     // 矩形宽度
	double m_lineSpacing = 10.0;              // 等距线间距
	bool m_enableCapture = true;             // 是否启用捕捉
	int m_pixelThreshold = 30;                // 像素变化阈值
	int m_lineDirection = 0;                  // 等距线方向 (0: 从左到右, 1: 从右到左)

	// 交互状态
	enum DragState {
		NoDrag,
		DraggingArrowHead,
		DraggingArrowTail,
		DraggingRectEdge,
		DraggingWholeMeasure  // 拖动整个测量模块
	};
	DragState m_dragState = NoDrag;

	std::vector<MeasurePoint> m_measurePoints; // 测量点结果

	// ===================== 新增矩形框绘制私有成员 =====================
	bool m_rectangleToolEnabled = false;      // 矩形工具是否启用
	std::vector<RectangleTool> m_rectangles;  // 矩形框集合
	bool m_rectangleCropInside = true;        // 矩形剪切模式：true=内部，false=外部

	// 矩形交互状态
	enum RectangleDragState {
		RectNoDrag,
		DraggingRectCenter,      // 拖动矩形中心
		DraggingRectCorner,      // 拖动矩形顶点(同时调整长宽)
		DraggingRectRotate       // 拖动旋转控制点
	};
	RectangleDragState m_rectDragState = RectNoDrag;
	int m_selectedRectIndex = -1;             // 当前选中的矩形索引
	int m_selectedCorner = -1;                // 当前选中的顶点索引(0-3)

	// ===================== 新增圆弧测量私有成员 =====================
	bool m_arcMeasureToolEnabled = false;     // 圆弧测量工具是否启用
	std::vector<ArcMeasureTool> m_arcMeasures; // 圆弧测量工具集合

	// 圆弧测量参数
	struct ArcMeasureParams {
		double angleSpacing = M_PI / 18;      // 角度间距（10度）
		int pixelThreshold = 20;              // 像素变化阈值
		int direction = 1;                    // 测量方向 (0: 从内到外, 1: 从外到内，默认从外到内)
		std::vector<ArcMeasurePoint> points;  // 测量点结果
		bool showPoints = true;               // 是否显示测量点
	};
	std::vector<ArcMeasureParams> m_arcMeasureParams; // 圆弧测量参数集合

	// 圆弧交互状态
	enum ArcDragState {
		ArcNoDrag,
		DraggingArcCenter,        // 拖动圆弧中心
		DraggingArcRadius,        // 拖动圆弧半径(在有效圆弧上拖动)
		DraggingArcStart,         // 拖动起始角度
		DraggingArcEnd,           // 拖动结束角度
		DraggingArcThickness      // 拖动圆弧厚度（在内圆或外圆弧线上拖动）
	};
	ArcDragState m_arcDragState = ArcNoDrag;
	int m_selectedArcIndex = -1;              // 当前选中的圆弧索引
	bool m_selectedThicknessIsInner = false;  // 选中的厚度控制点是内圆还是外圆
	bool m_isDraggingStartPoint = false;      // 记录拖动的是起始点还是终点（用于重合时的优先级）

private slots:
	void InputImg(int mode, cv::Mat& Img);//信号槽接口输入图像

signals:
	void imageLoaded(const QImage& image); // 图像加载信号
	void imageLoadCV(const cv::Mat& Image);// 传出opencv原始图像
	void measurePointsUpdated(const std::vector<MeasurePoint>& points); // 测量点更新信号
	void rectangleUpdated(int id, const QPointF& center, double width, double height, double angle); // 矩形更新信号
	void arcMeasureUpdated(int id, const QPointF& center, double radius, double startAngle, double endAngle, double thickness); // 圆弧测量更新信号
};