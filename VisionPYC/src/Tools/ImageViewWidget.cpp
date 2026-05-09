#include "ImageViewWidget.h"
#include <QPainter>
#include <QWheelEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>
#include <QFile>
#include <QImageReader>
#include <algorithm>
#include <qmenu.h>
#include <cmath>
#include <QPainterPath>

#define M_PI 3.14159265358979323846

ImageViewWidget::ImageViewWidget(QWidget* parent)
	: QWidget(parent)
{
	setAcceptDrops(true);
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
	setMinimumSize(200, 200);
	setStyleSheet("background-color:white;");

	// 初始化测量工具位置（默认在中心）
	m_arrowStart = QPointF(100, 100);
	m_arrowEnd = QPointF(200, 100);


	
}

// ===================== 图像加载 =====================
bool ImageViewWidget::loadImage(const QString& filePath)
{
	if (!QFile::exists(filePath)) {
		qWarning() << "文件不存在:" << filePath;
		return false;
	}
	cv::Mat mat = cv::imread(filePath.toStdString(), cv::IMREAD_UNCHANGED);
	if (mat.empty()) {
		qWarning() << "无法加载图像(OpenCV):" << filePath;
		return false;
	}
	m_cvImage = mat.clone();
	imageLoadCV(m_cvImage);
	QImage img;
	if (mat.type() == CV_8UC1) {
		img = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8).copy();
	}
	else if (mat.type() == CV_8UC3) {
		cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
		img = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).copy();
	}
	else if (mat.type() == CV_8UC4) {
		img = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32).copy();
	}
	else if (mat.type() == CV_16UC1) {

		// 1. 获取真实深度范围
		double minV = 0.0, maxV = 0.0;
		cv::minMaxLoc(mat, &minV, &maxV);

		if (maxV <= minV) {
			// 避免除零，同时保证图像可见
			maxV = minV + 1.0;
		}

		// 2. 归一化到 8bit 进行显示
		cv::Mat mat8;
		mat.convertTo(mat8, CV_8U, 255.0 / maxV);
		img = QImage(mat8.data, mat8.cols, mat8.rows, mat8.step, QImage::Format_Grayscale8).copy();


	}
	else {
		qWarning() << "不支持的图像格式:" << mat.type();
		return false;
	}

	setImage(img);
	qDebug() << "图像加载成功:" << filePath
		<< ", 分辨率:" << img.width() << "x" << img.height();

	return true;
}

// ===================== 设置图像 =====================
void ImageViewWidget::setImage(const QImage& image)
{
	m_image = image;
	m_offset = QPointF(0, 0);
	m_scaleFactor = 1.0;

	// 初始化测量工具位置到图像中心
	if (!image.isNull()) {
		m_arrowStart = QPointF(image.width() * 0.3, image.height() * 0.5);
		m_arrowEnd = QPointF(image.width() * 0.7, image.height() * 0.5);
	}

	fitToWidget();  // 自适应显示
	updateScaledImage(true);
	update();
}

void ImageViewWidget::updatedisplayMat(const cv::Mat& mat)
{
	displayMat(1, mat);

}

void ImageViewWidget::displayMat(int mode, const cv::Mat& mat)
{
	cv::Mat src;

	if (mode == 0)
	{
		if (m_cvImage.empty()) {
			qWarning() << "内部图像为空，无法显示。";
			return;
		}
		src = m_cvImage;
	}
	else if (mode == 1)
	{
		if (mat.empty()) {
			qWarning() << "输入图像为空，无法显示。";
			return;
		}
		src = mat;
	}
	else {
		qWarning() << "未知显示模式";
		return;
	}

	// ---------- Mat → QImage 转换 ----------
	QImage img;
	cv::Mat converted;

	switch (src.type())
	{
	case CV_8UC1:
		img = QImage(src.data, src.cols, src.rows, src.step, QImage::Format_Grayscale8).copy();
		break;
	case CV_8UC3:
		cv::cvtColor(src, converted, cv::COLOR_BGR2RGB);
		img = QImage(converted.data, converted.cols, converted.rows, converted.step, QImage::Format_RGB888).copy();
		break;
	case CV_8UC4:
		img = QImage(src.data, src.cols, src.rows, src.step, QImage::Format_ARGB32).copy();
		break;
	default:
		qWarning() << "不支持的图像类型:" << src.type();
		return;
	}
	m_image = img.copy();
	// ---------- 更新显示 ----------
	fitToWidget();
	update();

	/*qDebug() << "displayMat() -> 模式:" << (mode == 0 ? "内部" : "外部")
		<< ", 尺寸:" << img.width() << "x" << img.height();*/
}

void ImageViewWidget::GrayscalePatternImage(int minVal, int maxVal)
{
	cv::Mat m_src;
	m_src = m_cvImage.clone();
	cv::Mat thresholded;
	if (m_src.empty())
	{
		qDebug() << "图像为空";
		return;
	}

	switch (m_GrayscalePattern)
	{
	case ImageViewWidget::HIST_BINARY:
	{
		if (m_src.channels() == 1) {
			cv::threshold(m_src, thresholded, minVal, maxVal, cv::THRESH_BINARY);
		}
		else {
			cv::Mat gray;
			cv::cvtColor(m_src, gray, cv::COLOR_BGR2GRAY);
			cv::threshold(gray, thresholded, minVal, maxVal, cv::THRESH_BINARY);
		}
		displayMat(1, thresholded);
	}
	break;
	case ImageViewWidget::HIST_MINMAX:
	{
		if (m_src.channels() == 1) {
			cv::normalize(m_src, thresholded, minVal, maxVal, cv::NORM_MINMAX);
		}
		else {
			cv::Mat gray;
			cv::cvtColor(m_src, gray, cv::COLOR_BGR2GRAY);
			cv::normalize(gray, thresholded, minVal, maxVal, cv::NORM_MINMAX);

		}
		displayMat(1, thresholded);
	}
	break;
	default:
		break;
	}
}

// ===================== 新增一维测量接口实现 =====================
void ImageViewWidget::setOneDMeasureParams(int rectWidth, double lineSpacing,
	int pixelThreshold, int lineDirection)
{
	m_rectWidth = std::max(1, rectWidth);
	m_lineSpacing = std::max(0.1, lineSpacing);

	m_pixelThreshold = pixelThreshold;
	m_lineDirection = (lineDirection == 0 || lineDirection == 1) ? lineDirection : 0;

	if (!m_cvImage.empty() && m_cvImage.channels() == 1) {
		updateMeasurePoints();
	}

	update();
}

void ImageViewWidget::clearMeasureResults()
{
	m_measurePoints.clear();
	update();
}

void ImageViewWidget::updateMeasurePoints()
{
	if (m_cvImage.empty() || m_cvImage.channels() != 1) {
		qWarning() << "图像为空或不是单通道图像，无法进行测量";
		return;
	}

	m_measurePoints.clear();

	// 计算箭头方向向量
	QPointF arrowVec = m_arrowEnd - m_arrowStart;
	double arrowLength = std::sqrt(arrowVec.x() * arrowVec.x() + arrowVec.y() * arrowVec.y());
	if (arrowLength < 1e-6) return;

	// 归一化方向向量
	QPointF dirVec = arrowVec / arrowLength;

	// 垂直方向向量（用于矩形宽度方向）
	QPointF perpVec(-dirVec.y(), dirVec.x());

	// 计算测量线的起点和方向
	QPointF measureStart = m_arrowStart;
	QPointF measureDir = dirVec;
	if (m_lineDirection == 1) {
		measureStart = m_arrowEnd;
		measureDir = -dirVec;
	}

	// 计算等距线的数量
	int numLines = static_cast<int>(arrowLength / m_lineSpacing);
	if (numLines <= 0) numLines = 1;

	for (int i = 0; i <= numLines; ++i) {
		double t = i * m_lineSpacing;
		if (t > arrowLength) break;

		// 计算等距线中心点
		QPointF lineCenter = measureStart + measureDir * t;

		// 计算等距线端点
		QPointF lineStart = lineCenter - perpVec * (m_rectWidth / 2.0);
		QPointF lineEnd = lineCenter + perpVec * (m_rectWidth / 2.0);

		// 在图像上采样点
		std::vector<QPoint> samplePoints;
		double lineLength = std::sqrt(std::pow(lineEnd.x() - lineStart.x(), 2) +
			std::pow(lineEnd.y() - lineStart.y(), 2));
		int numSamples = static_cast<int>(lineLength);
		if (numSamples < 2) numSamples = 2;

		for (int j = 0; j < numSamples; ++j) {
			double u = static_cast<double>(j) / (numSamples - 1);
			QPointF samplePoint = lineStart + (lineEnd - lineStart) * u;
			samplePoints.push_back(QPoint(static_cast<int>(samplePoint.x()),
				static_cast<int>(samplePoint.y())));
		}

		// 检测边缘点
		MeasurePoint measurePoint;
		measurePoint.valid = false;

		for (size_t j = 1; j < samplePoints.size(); ++j) {
			const QPoint& prev = samplePoints[j - 1];
			const QPoint& curr = samplePoints[j];

			// 检查坐标是否在图像范围内
			if (prev.x() < 0 || prev.x() >= m_cvImage.cols || prev.y() < 0 || prev.y() >= m_cvImage.rows ||
				curr.x() < 0 || curr.x() >= m_cvImage.cols || curr.y() < 0 || curr.y() >= m_cvImage.rows) {
				continue;
			}

			// 计算像素差值
			int prevValue = static_cast<int>(m_cvImage.at<uchar>(prev.y(), prev.x()));
			int currValue = static_cast<int>(m_cvImage.at<uchar>(curr.y(), curr.x()));
			int diff = std::abs(currValue - prevValue);

			if (diff >= m_pixelThreshold) {
				measurePoint.position = QPointF(curr.x(), curr.y());
				measurePoint.valid = true;
				break; // 找到第一个满足条件的点
			}
		}

		m_measurePoints.push_back(measurePoint);
	}

	emit measurePointsUpdated(m_measurePoints);
}

void ImageViewWidget::updateMeasureRect()
{
	// 矩形会根据箭头位置自动更新，这里主要是为了触发重绘
	update();
}

// ===================== 坐标转换 =====================
QPointF ImageViewWidget::imageToWidget(const QPointF& imagePoint) const
{
	if (m_image.isNull()) return imagePoint;

	QPointF widgetPoint = imagePoint * m_scaleFactor + m_offset;
	return widgetPoint;
}

QPointF ImageViewWidget::widgetToImage(const QPointF& widgetPoint) const
{
	if (m_image.isNull() || m_scaleFactor == 0) return widgetPoint;

	QPointF imagePoint = (widgetPoint - m_offset) / m_scaleFactor;
	return imagePoint;
}

// ===================== 交互检测 =====================
bool ImageViewWidget::isPointOnArrowHead(const QPointF& widgetPoint) const
{
	QPointF arrowHead = imageToWidget(m_arrowEnd);
	double distance = std::sqrt(std::pow(widgetPoint.x() - arrowHead.x(), 2) +
		std::pow(widgetPoint.y() - arrowHead.y(), 2));
	return distance < 8.0; // 8像素的点击范围
}

bool ImageViewWidget::isPointOnArrowTail(const QPointF& widgetPoint) const
{
	QPointF arrowTail = imageToWidget(m_arrowStart);
	double distance = std::sqrt(std::pow(widgetPoint.x() - arrowTail.x(), 2) +
		std::pow(widgetPoint.y() - arrowTail.y(), 2));
	return distance < 8.0; // 8像素的点击范围
}

bool ImageViewWidget::isPointOnRectEdge(const QPointF& widgetPoint) const
{
	// 计算箭头方向向量
	QPointF arrowVec = m_arrowEnd - m_arrowStart;
	double arrowLength = std::sqrt(arrowVec.x() * arrowVec.x() + arrowVec.y() * arrowVec.y());
	if (arrowLength < 1e-6) return false;

	// 归一化方向向量
	QPointF dirVec = arrowVec / arrowLength;
	QPointF perpVec(-dirVec.y(), dirVec.x());

	// 计算矩形四个角点（图像坐标）
	QPointF rectTopStart = m_arrowStart - perpVec * (m_rectWidth / 2.0);
	QPointF rectTopEnd = m_arrowEnd - perpVec * (m_rectWidth / 2.0);
	QPointF rectBottomStart = m_arrowStart + perpVec * (m_rectWidth / 2.0);
	QPointF rectBottomEnd = m_arrowEnd + perpVec * (m_rectWidth / 2.0);

	// 转换到控件坐标
	QPointF widgetRectTopStart = imageToWidget(rectTopStart);
	QPointF widgetRectTopEnd = imageToWidget(rectTopEnd);
	QPointF widgetRectBottomStart = imageToWidget(rectBottomStart);
	QPointF widgetRectBottomEnd = imageToWidget(rectBottomEnd);

	// 计算矩形边缘中点
	QPointF widgetRectTopCenter = (widgetRectTopStart + widgetRectTopEnd) / 2.0;
	QPointF widgetRectBottomCenter = (widgetRectBottomStart + widgetRectBottomEnd) / 2.0;

	// 检查是否靠近上下边缘中点
	double distanceToTop = std::sqrt(std::pow(widgetPoint.x() - widgetRectTopCenter.x(), 2) +
		std::pow(widgetPoint.y() - widgetRectTopCenter.y(), 2));
	double distanceToBottom = std::sqrt(std::pow(widgetPoint.x() - widgetRectBottomCenter.x(), 2) +
		std::pow(widgetPoint.y() - widgetRectBottomCenter.y(), 2));

	return distanceToTop < 8.0 || distanceToBottom < 8.0;
}

bool ImageViewWidget::isPointOnRectCenter(const QPointF& widgetPoint) const
{
	// 计算箭头方向向量
	QPointF arrowVec = m_arrowEnd - m_arrowStart;
	double arrowLength = std::sqrt(arrowVec.x() * arrowVec.x() + arrowVec.y() * arrowVec.y());
	if (arrowLength < 1e-6) return false;

	// 归一化方向向量
	QPointF dirVec = arrowVec / arrowLength;
	QPointF perpVec(-dirVec.y(), dirVec.x());

	// 计算矩形中心点（图像坐标）
	QPointF rectCenter = (m_arrowStart + m_arrowEnd) / 2.0;

	// 转换到控件坐标
	QPointF widgetRectCenter = imageToWidget(rectCenter);

	// 检查是否靠近矩形中心
	double distance = std::sqrt(std::pow(widgetPoint.x() - widgetRectCenter.x(), 2) +
		std::pow(widgetPoint.y() - widgetRectCenter.y(), 2));

	return distance < 10.0; // 10像素的点击范围
}

// ===================== 绘制 =====================
void ImageViewWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	// 1. 手动绘制棋盘格背景
	static QPixmap cache;
	if (cache.isNull()) {
		cache = QPixmap(32, 32);
		QPainter p(&cache);
		p.fillRect(0, 0, 16, 16, QColor("#252525"));
		p.fillRect(16, 16, 16, 16, QColor("#252525"));
		p.fillRect(16, 0, 16, 16, QColor("#303030"));
		p.fillRect(0, 16, 16, 16, QColor("#303030"));
	}
	painter.drawTiledPixmap(rect(), cache);






	if (!m_scaledPixmap.isNull()) {
		painter.drawPixmap(m_offset, m_scaledPixmap); // ✅ 使用偏移绘制
	}

	// 绘制测量工具
	if (m_measureToolEnabled) {
		drawMeasureTool(painter);
	}

	// 绘制矩形工具
	if (m_rectangleToolEnabled) {
		drawRectangleTool(painter);
	}

	// 绘制圆弧测量工具
	if (m_arcMeasureToolEnabled) {
		drawArcMeasureTool(painter);
	}
}

void ImageViewWidget::drawMeasureTool(QPainter& painter)
{
	if (m_image.isNull()) return;

	// 保存 painter 状态
	painter.save();

	// 设置抗锯齿
	painter.setRenderHint(QPainter::Antialiasing);

	// 计算箭头方向向量
	QPointF arrowVec = m_arrowEnd - m_arrowStart;
	double arrowLength = std::sqrt(arrowVec.x() * arrowVec.x() + arrowVec.y() * arrowVec.y());
	if (arrowLength < 1e-6) {
		painter.restore();
		return;
	}

	// 归一化方向向量
	QPointF dirVec = arrowVec / arrowLength;
	QPointF perpVec(-dirVec.y(), dirVec.x());

	// 计算矩形四个角点
	QPointF rectTopStart = m_arrowStart - perpVec * (m_rectWidth / 2.0);
	QPointF rectTopEnd = m_arrowEnd - perpVec * (m_rectWidth / 2.0);
	QPointF rectBottomStart = m_arrowStart + perpVec * (m_rectWidth / 2.0);
	QPointF rectBottomEnd = m_arrowEnd + perpVec * (m_rectWidth / 2.0);

	// 转换到控件坐标
	QPointF widgetArrowStart = imageToWidget(m_arrowStart);
	QPointF widgetArrowEnd = imageToWidget(m_arrowEnd);
	QPointF widgetRectTopStart = imageToWidget(rectTopStart);
	QPointF widgetRectTopEnd = imageToWidget(rectTopEnd);
	QPointF widgetRectBottomStart = imageToWidget(rectBottomStart);
	QPointF widgetRectBottomEnd = imageToWidget(rectBottomEnd);

	// 绘制矩形
	painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
	painter.drawLine(widgetRectTopStart, widgetRectTopEnd);
	painter.drawLine(widgetRectBottomStart, widgetRectBottomEnd);
	painter.drawLine(widgetRectTopStart, widgetRectBottomStart);
	painter.drawLine(widgetRectTopEnd, widgetRectBottomEnd);

	// 绘制等距线
	painter.setPen(QPen(Qt::green, 1, Qt::SolidLine));
	QPointF measureStart = m_arrowStart;
	QPointF measureDir = dirVec;
	if (m_lineDirection == 1) {
		measureStart = m_arrowEnd;
		measureDir = -dirVec;
	}

	int numLines = static_cast<int>(arrowLength / m_lineSpacing);
	for (int i = 0; i <= numLines; ++i) {
		double t = i * m_lineSpacing;
		if (t > arrowLength) break;

		QPointF lineCenter = measureStart + measureDir * t;
		QPointF lineStart = lineCenter - perpVec * (m_rectWidth / 2.0);
		QPointF lineEnd = lineCenter + perpVec * (m_rectWidth / 2.0);

		QPointF widgetLineStart = imageToWidget(lineStart);
		QPointF widgetLineEnd = imageToWidget(lineEnd);

		// 绘制等距线方向指示（小箭头）
		QPointF lineDir = (lineEnd - lineStart) / std::sqrt(std::pow(lineEnd.x() - lineStart.x(), 2) +
			std::pow(lineEnd.y() - lineStart.y(), 2));
		QPointF arrowTip = lineStart + lineDir * 10.0; // 10像素长的箭头

		QPointF widgetArrowTip = imageToWidget(arrowTip);

		painter.drawLine(widgetLineStart, widgetLineEnd);

		// 绘制小箭头
		QPointF arrowPerp(-lineDir.y(), lineDir.x());
		QPointF arrowLeft = arrowTip - lineDir * 5.0 + arrowPerp * 3.0;
		QPointF arrowRight = arrowTip - lineDir * 5.0 - arrowPerp * 3.0;

		QPointF widgetArrowLeft = imageToWidget(arrowLeft);
		QPointF widgetArrowRight = imageToWidget(arrowRight);

		painter.drawLine(widgetArrowTip, widgetArrowLeft);
		painter.drawLine(widgetArrowTip, widgetArrowRight);
	}

	// 绘制主箭头
	painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
	painter.drawLine(widgetArrowStart, widgetArrowEnd);

	// 绘制箭头头部
	QPointF arrowHeadLeft = m_arrowEnd - dirVec * 10.0 + perpVec * 5.0;
	QPointF arrowHeadRight = m_arrowEnd - dirVec * 10.0 - perpVec * 5.0;

	QPointF widgetArrowHeadLeft = imageToWidget(arrowHeadLeft);
	QPointF widgetArrowHeadRight = imageToWidget(arrowHeadRight);

	painter.drawLine(widgetArrowEnd, widgetArrowHeadLeft);
	painter.drawLine(widgetArrowEnd, widgetArrowHeadRight);

	// 绘制控制点（箭头首尾和矩形边缘中点）
	painter.setBrush(QBrush(Qt::yellow));
	painter.setPen(QPen(Qt::black, 1));

	// 箭头起点
	painter.drawEllipse(widgetArrowStart, 4, 4);
	// 箭头终点
	painter.drawEllipse(widgetArrowEnd, 4, 4);
	// 矩形边缘中点
	QPointF widgetRectTopCenter = (widgetRectTopStart + widgetRectTopEnd) / 2.0;
	QPointF widgetRectBottomCenter = (widgetRectBottomStart + widgetRectBottomEnd) / 2.0;
	painter.drawEllipse(widgetRectTopCenter, 4, 4);
	painter.drawEllipse(widgetRectBottomCenter, 4, 4);

	// 绘制矩形中心点
	QPointF widgetRectCenter = imageToWidget((m_arrowStart + m_arrowEnd) / 2.0);
	painter.setBrush(QBrush(Qt::cyan));
	painter.drawEllipse(widgetRectCenter, 6, 6);

	// 绘制测量点
	painter.setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
	for (const auto& point : m_measurePoints) {
		if (point.valid) {
			QPointF widgetPoint = imageToWidget(point.position);
			// 绘制十字线（倾斜45°）
			painter.drawLine(widgetPoint - QPointF(5, 5), widgetPoint + QPointF(5, 5));
			painter.drawLine(widgetPoint - QPointF(5, -5), widgetPoint + QPointF(5, -5));
		}
	}

	painter.restore();
}

// ===================== 新增矩形框绘制实现 =====================
int ImageViewWidget::addRectangle(int recendID, const QPointF& center, double width, double height, double angle)
{
	RectangleTool rect;
	rect.center = center;
	rect.width = std::max(10.0, width);
	rect.height = std::max(10.0, height);
	rect.angle = angle;

	rect.id = recendID;

	m_rectangles.push_back(rect);
	update();

	return rect.id;
}

void ImageViewWidget::removeRectangle(int id)
{
	auto it = std::remove_if(m_rectangles.begin(), m_rectangles.end(),
		[id](const RectangleTool& rect) { return rect.id == id; });
	m_rectangles.erase(it, m_rectangles.end());
	update();
}

void ImageViewWidget::clearRectangles()
{
	m_rectangles.clear();
	update();
}
cv::Mat ImageViewWidget::cropImageByRectangle(int id)
{
	if (m_cvImage.empty()) return cv::Mat();

	// 查找对应矩形
	auto it = std::find_if(m_rectangles.begin(), m_rectangles.end(),
		[id](const RectangleTool& rect) { return rect.id == id; });

	if (it == m_rectangles.end()) {
		qWarning() << "未找到ID为" << id << "的矩形框";
		return cv::Mat();
	}

	const RectangleTool& rect = *it;

	try {
		// ---- 1. 构造旋转矩形 ----
		cv::Point2f center(rect.center.x(), rect.center.y());
		cv::Size2f size(rect.width, rect.height);

		// OpenCV RotatedRect 的角度为度数，且逆时针为正
		float angle_deg = static_cast<float>(rect.angle * 180.0 / CV_PI);
		cv::RotatedRect rotatedRect(center, size, angle_deg);

		// ---- 2. 获取旋转矩形 4 个顶点 ----
		cv::Point2f pts[4];
		rotatedRect.points(pts);

		cv::Point2f srcPts[4] =
		{
			pts[1],
			pts[2],
			pts[3],
			pts[0]
		};
		// ---- 3. 准备变换后的目标矩形（角度归 0） ----
		cv::Point2f dstPts[4] = {
			cv::Point2f(0, 0),									//右上
			cv::Point2f(size.width - 1, 0),						//左上
			cv::Point2f(size.width - 1, size.height - 1),		//左下
			cv::Point2f(0, size.height - 1)						//右下
		};

		// ---- 4. 计算透视/仿射变换矩阵 ----
		cv::Mat M = cv::getPerspectiveTransform(srcPts, dstPts);

		// ---- 6. 逆向映射裁剪出旋转后的正向矩形 ----
		cv::Mat cropped;
		cv::warpPerspective(
			m_cvImage, cropped, M,
			cv::Size((int)size.width, (int)size.height),
			cv::INTER_LINEAR, cv::BORDER_REPLICATE
		);

		return cropped;
	}
	catch (const cv::Exception& e) {
		qWarning() << "OpenCV异常 - 裁剪图像时发生错误:" << e.what();
	}
	catch (const std::exception& e) {
		qWarning() << "标准异常 - 裁剪图像时发生错误:" << e.what();
	}
	catch (...) {
		qWarning() << "未知异常 - 裁剪图像时发生错误";
	}

	return cv::Mat();
}


void ImageViewWidget::drawRectangleTool(QPainter& painter)
{
	if (m_image.isNull()) return;

	painter.save();
	painter.setRenderHint(QPainter::Antialiasing, true);

	for (size_t i = 0; i < m_rectangles.size(); ++i)
	{
		const RectangleTool& rect = m_rectangles[i];

		// === 坐标变换 ===
		QPointF widgetCenter = imageToWidget(rect.center);
		double scaledWidth = rect.width * m_scaleFactor;
		double scaledHeight = rect.height * m_scaleFactor;

		painter.save();
		painter.translate(widgetCenter);
		painter.rotate(rect.angle * 180 / M_PI);

		// === 绘制主矩形 ===
		QRectF rectRect(-scaledWidth / 2, -scaledHeight / 2, scaledWidth, scaledHeight);
		painter.setPen(QPen(rect.isSelected ? QColor(255, 80, 80) : QColor(0, 120, 255), 2));
		painter.setBrush(QBrush(QColor(0, 0, 255, 25))); // 半透明内部
		painter.drawRect(rectRect);

		// === 绘制贴边 L 形角帽（向内） ===
		auto drawCornerMarker = [&](const QPointF& corner, bool isRight, bool isBottom)
			{
				double len = std::max(8.0, std::min(scaledWidth, scaledHeight) * 0.08); // 角帽长度
				double thick = 3.0; // 角帽厚度（视觉权重）

				double sx = isRight ? -1.0 : 1.0;  // 朝内方向
				double sy = isBottom ? -1.0 : 1.0;

				// 从矩形顶点往内偏移绘制
				QPointF base = corner;

				QPainterPath path;
				path.moveTo(base);
				path.lineTo(base + QPointF(sx * len, 0));
				path.lineTo(base + QPointF(sx * len, sy * thick));
				path.lineTo(base + QPointF(0, sy * thick));
				path.closeSubpath();

				QPainterPath path2;
				path2.moveTo(base);
				path2.lineTo(base + QPointF(0, sy * len));
				path2.lineTo(base + QPointF(sx * thick, sy * len));
				path2.lineTo(base + QPointF(sx * thick, 0));
				path2.closeSubpath();

				painter.save();
				painter.setPen(Qt::NoPen);
				painter.setBrush(QColor(60, 190, 255, 220)); // 柔和蓝青色
				painter.drawPath(path);
				painter.drawPath(path2);
				painter.restore();
			};

		// 四个角帽：贴在矩形内侧
		double offset = 3.0;
		drawCornerMarker(QPointF(scaledWidth / 2 + offset, scaledHeight / 2 + offset), true, true);    // 右下
		drawCornerMarker(QPointF(-scaledWidth / 2 - offset, scaledHeight / 2 + offset), false, true);  // 左下
		drawCornerMarker(QPointF(scaledWidth / 2 + offset, -scaledHeight / 2 - offset), true, false);  // 右上
		drawCornerMarker(QPointF(-scaledWidth / 2 - offset, -scaledHeight / 2 - offset), false, false);// 左上

		// === 绘制中心点（十字形） ===
		painter.save();
		QPen crossPen(QColor(230, 240, 255), 1.5);
		painter.setPen(crossPen);
		double crossLen = 8.0;
		painter.drawLine(QPointF(-crossLen, 0), QPointF(crossLen, 0));
		painter.drawLine(QPointF(0, -crossLen), QPointF(0, crossLen));
		painter.restore();

		// === 绘制旋转控制点 ===
		QPointF rotateHandle(scaledWidth / 4, 0);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(0, 255, 180, 230)); // 青绿色圆点
		painter.drawEllipse(rotateHandle, 5, 5);
		painter.setPen(QPen(QColor(0, 255, 180, 180), 1.5));
		painter.drawLine(QPointF(0, 0), rotateHandle);

		painter.restore();

		// === 绘制矩形 ID 标签 ===
		painter.setPen(QColor(240, 240, 240));
		painter.drawText(widgetCenter + QPointF(10, -10), QString::number(rect.id));
	}

	painter.restore();
}

bool ImageViewWidget::isPointOnRectangleCenter(const QPointF& widgetPoint, int rectIndex) const
{
	if (rectIndex < 0 || rectIndex >= static_cast<int>(m_rectangles.size())) return false;

	const RectangleTool& rect = m_rectangles[rectIndex];
	QPointF widgetCenter = imageToWidget(rect.center);

	// 检测阈值根据缩放因子调整,最小10像素,最大18像素
	double detectionRadius = std::max(10.0, std::min(18.0, 10.0 / m_scaleFactor));

	double distance = std::sqrt(std::pow(widgetPoint.x() - widgetCenter.x(), 2) +
		std::pow(widgetPoint.y() - widgetCenter.y(), 2));
	return distance < detectionRadius;
}

int ImageViewWidget::isPointOnRectangleCorner(const QPointF& widgetPoint, int rectIndex) const
{
	if (rectIndex < 0 || rectIndex >= static_cast<int>(m_rectangles.size())) return -1;

	const RectangleTool& rect = m_rectangles[rectIndex];
	QPointF widgetCenter = imageToWidget(rect.center);

	// 计算四个顶点在控件坐标系中的位置
	double cosAngle = std::cos(rect.angle);
	double sinAngle = std::sin(rect.angle);

	QPointF corners[4];
	corners[0] = QPointF(rect.width / 2, rect.height / 2);   // 右下
	corners[1] = QPointF(-rect.width / 2, rect.height / 2);  // 左下
	corners[2] = QPointF(rect.width / 2, -rect.height / 2);  // 右上
	corners[3] = QPointF(-rect.width / 2, -rect.height / 2); // 左上

	// 旋转并转换到控件坐标
	for (int i = 0; i < 4; ++i) {
		double x = corners[i].x() * cosAngle - corners[i].y() * sinAngle;
		double y = corners[i].x() * sinAngle + corners[i].y() * cosAngle;
		corners[i] = widgetCenter + QPointF(x * m_scaleFactor, y * m_scaleFactor);
	}

	// 检测阈值根据缩放因子调整,最小12像素,最大20像素
	double detectionRadius = std::max(12.0, std::min(20.0, 12.0 / m_scaleFactor));

	// 检查是否靠近任一顶点,返回最近的顶点索引
	int closestCorner = -1;
	double minDistance = detectionRadius;
	for (int i = 0; i < 4; ++i) {
		double distance = std::sqrt(std::pow(widgetPoint.x() - corners[i].x(), 2) +
			std::pow(widgetPoint.y() - corners[i].y(), 2));
		if (distance < minDistance) {
			minDistance = distance;
			closestCorner = i;
		}
	}

	return closestCorner;
}

bool ImageViewWidget::isPointOnRectangleRotateHandle(const QPointF& widgetPoint, int rectIndex) const
{
	if (rectIndex < 0 || rectIndex >= static_cast<int>(m_rectangles.size())) return false;

	const RectangleTool& rect = m_rectangles[rectIndex];

	// 计算旋转控制点的图像坐标
	double cosAngle = std::cos(rect.angle);
	double sinAngle = std::sin(rect.angle);
	QPointF rotateHandleImage = rect.center + QPointF(rect.width / 4 * cosAngle, rect.width / 4 * sinAngle);

	QPointF widgetRotateHandle = imageToWidget(rotateHandleImage);

	// 检测阈值根据缩放因子调整,最小10像素,最大18像素
	double detectionRadius = std::max(10.0, std::min(18.0, 10.0 / m_scaleFactor));

	double distance = std::sqrt(std::pow(widgetPoint.x() - widgetRotateHandle.x(), 2) +
		std::pow(widgetPoint.y() - widgetRotateHandle.y(), 2));
	return distance < detectionRadius;
}

void ImageViewWidget::updateRectangle(int index)
{
	if (index < 0 || index >= static_cast<int>(m_rectangles.size())) return;

	RectangleTool& rect = m_rectangles[index];
	emit rectangleUpdated(rect.id, rect.center, rect.width, rect.height, rect.angle);
	update();
}

// ===================== 新增圆弧测量实现 =====================
int ImageViewWidget::addArcMeasure(const QPointF& center, double radius,
	double startAngle, double endAngle, double thickness)
{
	ArcMeasureTool arc;

	// 如果center为空或未指定，使用图像中心
	if (center.isNull() || (center.x() == 0 && center.y() == 0)) {
		if (!m_image.isNull()) {
			arc.center = QPointF(m_image.width() / 2.0, m_image.height() / 2.0);
		}
		else {
			arc.center = QPointF(100, 100); // 默认值
		}
	}
	else {
		arc.center = center;
	}

	arc.radius = std::max(10.0, radius);

	// 如果角度未指定，使用默认值：起点0度（右侧），终点-3π/2（上方），逆时针
	if (startAngle == 0 && endAngle == -M_PI * 1.5) {
		arc.startAngle = 0;           // 起点在右侧 (X+R, Y)
		arc.endAngle = -M_PI * 1.5;   // 终点在上方 (X, Y-R)，逆时针方向
	}
	else {
		arc.startAngle = startAngle;
		arc.endAngle = endAngle;
	}

	arc.thickness = std::max(5.0, thickness);
	arc.id = m_arcMeasures.empty() ? 1 : (m_arcMeasures.back().id + 1);

	m_arcMeasures.push_back(arc);

	// 添加对应的参数
	ArcMeasureParams params;
	params.direction = 1; // 默认从外到内
	m_arcMeasureParams.push_back(params);

	update();

	return arc.id;
}

void ImageViewWidget::setArcMeasureParams(int id, double angleSpacing, int pixelThreshold, int direction)
{
	for (size_t i = 0; i < m_arcMeasures.size(); ++i) {
		if (m_arcMeasures[i].id == id) {
			m_arcMeasureParams[i].angleSpacing = std::max(0.01, angleSpacing);
			m_arcMeasureParams[i].pixelThreshold = pixelThreshold;
			m_arcMeasureParams[i].direction = (direction == 0 || direction == 1) ? direction : 1;

			if (!m_cvImage.empty() && m_cvImage.channels() == 1) {
				updateArcMeasurePoints(static_cast<int>(i));
			}
			break;
		}
	}
	update();
}

std::vector<std::pair<float, float>> ImageViewWidget::getArcMeasurePoints(int id) const
{
	std::vector<std::pair<float, float>> result;
	for (size_t i = 0; i < m_arcMeasures.size(); ++i) {
		if (m_arcMeasures[i].id == id) {
			const auto& points = m_arcMeasureParams[i].points;
			for (const auto& point : points) {
				if (point.valid) {
					result.push_back(std::make_pair(
						static_cast<float>(point.position.x()),
						static_cast<float>(point.position.y())
					));
				}
			}
			break;
		}
	}
	return result;
}

void ImageViewWidget::setArcMeasurePointsVisible(int id, bool show)
{
	for (size_t i = 0; i < m_arcMeasures.size(); ++i) {
		if (m_arcMeasures[i].id == id) {
			m_arcMeasureParams[i].showPoints = show;
			update();
			break;
		}
	}
}

void ImageViewWidget::removeArcMeasure(int id)
{
	for (size_t i = 0; i < m_arcMeasures.size(); ++i) {
		if (m_arcMeasures[i].id == id) {
			m_arcMeasures.erase(m_arcMeasures.begin() + i);
			m_arcMeasureParams.erase(m_arcMeasureParams.begin() + i);
			break;
		}
	}
	update();
}

void ImageViewWidget::clearArcMeasures()
{
	m_arcMeasures.clear();
	m_arcMeasureParams.clear();
	update();
}

void ImageViewWidget::drawArcMeasureTool(QPainter& painter)
{
	if (m_image.isNull()) return;

	painter.save();
	painter.setRenderHint(QPainter::Antialiasing);

	for (size_t i = 0; i < m_arcMeasures.size(); ++i) {
		const ArcMeasureTool& arc = m_arcMeasures[i];
		const ArcMeasureParams& params = m_arcMeasureParams[i];

		QPointF widgetCenter = imageToWidget(arc.center);

		// 计算内外圆半径（内圆半径R-d/2，外圆半径R+d/2）
		double innerRadius = arc.radius - arc.thickness / 2.0;
		double outerRadius = arc.radius + arc.thickness / 2.0;

		// 确保内圆半径大于0
		if (innerRadius < 1.0) innerRadius = 1.0;

		// 计算圆弧的控件坐标半径
		double widgetInnerRadius = innerRadius * m_scaleFactor;
		double widgetOuterRadius = outerRadius * m_scaleFactor;
		double widgetRadius = arc.radius * m_scaleFactor;

		// 计算有效圆弧的角度范围（逆时针从startAngle到endAngle）
		double angleRange = arc.endAngle - arc.startAngle;
		// 如果endAngle < startAngle，说明跨越了0度线
		if (angleRange < 0) {
			angleRange += 2 * M_PI;
		}

		// 绘制圆弧区域
		QRectF outerRect(widgetCenter.x() - widgetOuterRadius,
			widgetCenter.y() - widgetOuterRadius,
			widgetOuterRadius * 2,
			widgetOuterRadius * 2);
		QRectF innerRect(widgetCenter.x() - widgetInnerRadius,
			widgetCenter.y() - widgetInnerRadius,
			widgetInnerRadius * 2,
			widgetInnerRadius * 2);

		painter.setPen(QPen(arc.isSelected ? Qt::red : Qt::blue, 2));
		painter.setBrush(Qt::NoBrush);

		// 绘制有效圆弧（内圆和外圆）
		// Qt的drawArc使用1/16度为单位，0度在右侧，逆时针为正
		int startAngle16 = static_cast<int>(arc.startAngle * 180 / M_PI * 16);
		int spanAngle16 = static_cast<int>(angleRange * 180 / M_PI * 16);

		painter.drawArc(outerRect, startAngle16, spanAngle16);
		painter.drawArc(innerRect, startAngle16, spanAngle16);

		// 绘制辅助线（在半径R的圆弧上）
		painter.setPen(QPen(Qt::cyan, 1, Qt::DashLine));
		QRectF guideRect(widgetCenter.x() - widgetRadius,
			widgetCenter.y() - widgetRadius,
			widgetRadius * 2,
			widgetRadius * 2);
		/*int startAngle16 = static_cast<int>(arc.startAngle * 180 / M_PI * 16);
		int spanAngle16 = static_cast<int>(angleRange * 180 / M_PI * 16);*/
		painter.drawArc(guideRect, startAngle16, spanAngle16);

		// 绘制连接线（起始和结束位置的径向线）
		double cosStart = std::cos(arc.startAngle);
		double sinStart = std::sin(arc.startAngle);
		double cosEnd = std::cos(arc.endAngle);
		double sinEnd = std::sin(arc.endAngle);

		// 起始点和末尾点在辅助线上（半径R的圆弧上）
		QPointF guideStart = widgetCenter + QPointF(arc.radius * cosStart * m_scaleFactor,
			arc.radius * -sinStart * m_scaleFactor);
		QPointF guideEnd = widgetCenter + QPointF(arc.radius * cosEnd * m_scaleFactor,
			arc.radius * -sinEnd * m_scaleFactor);

		QPointF outerStart = widgetCenter + QPointF(outerRadius * cosStart * m_scaleFactor,
			outerRadius * -sinStart * m_scaleFactor);
		QPointF innerStart = widgetCenter + QPointF(innerRadius * cosStart * m_scaleFactor,
			innerRadius * -sinStart * m_scaleFactor);
		QPointF outerEnd = widgetCenter + QPointF(outerRadius * cosEnd * m_scaleFactor,
			outerRadius * -sinEnd * m_scaleFactor);
		QPointF innerEnd = widgetCenter + QPointF(innerRadius * cosEnd * m_scaleFactor,
			innerRadius * -sinEnd * m_scaleFactor);

		// 绘制从辅助线到内外圆的连接线
		painter.setPen(QPen(arc.isSelected ? Qt::red : Qt::blue, 2));
		painter.drawLine(guideStart, outerStart);
		painter.drawLine(guideStart, innerStart);
		painter.drawLine(guideEnd, outerEnd);
		painter.drawLine(guideEnd, innerEnd);

		// 绘制末端三角箭头（不填充）
		painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
		painter.setBrush(Qt::NoBrush);

		// 计算箭头方向（沿圆弧切线方向，逆时针）
		QPointF endTangent(-sinEnd, cosEnd); // 逆时针方向的切线
		QPointF arrowSize = endTangent * 10.0 * m_scaleFactor;

		// 三角箭头的三个顶点
		QPointF arrowTip = outerEnd;
		QPointF arrowLeft = outerEnd - arrowSize + QPointF(-cosEnd * 6 * m_scaleFactor, sinEnd * 6 * m_scaleFactor);
		QPointF arrowRight = outerEnd - arrowSize - QPointF(-cosEnd * 6 * m_scaleFactor, sinEnd * 6 * m_scaleFactor);

		QPolygonF arrow;
		arrow << arrowTip << arrowLeft << arrowRight;
		painter.drawPolyline(arrow); // 不填充，只绘制轮廓

		// 绘制测量线（只在有效圆弧范围内）
		painter.setPen(QPen(Qt::green, 1, Qt::SolidLine));

		// 计算有效区域：从startAngle到endAngle的逆时针圆弧
		// 如果endAngle < startAngle，说明跨越了0度线，需要特殊处理
		double effectiveStartAngle = arc.startAngle;
		double effectiveEndAngle = arc.endAngle;

		// 确保有效区域是逆时针方向
		if (effectiveEndAngle < effectiveStartAngle) {
			effectiveEndAngle += 2 * M_PI;
		}

		int numLines = static_cast<int>(angleRange / params.angleSpacing);
		for (int j = 0; j <= numLines; ++j) {
			// 计算当前角度（从startAngle开始，按angleSpacing递增）
			double angle = arc.startAngle + j * params.angleSpacing;

			// 规范化角度到[-π, π]
			double normalizedAngle = normalizeAngle(angle);

			// 检查是否在有效圆弧范围内（逆时针从startAngle到endAngle）
			bool inRange = false;
			if (arc.endAngle >= arc.startAngle) {
				// 正常情况：endAngle >= startAngle
				// 有效区域是 [startAngle, endAngle]
				inRange = (normalizedAngle >= arc.startAngle && normalizedAngle <= arc.endAngle);
			}
			else {
				// 跨越0度线：endAngle < startAngle
				// 有效区域是逆时针从startAngle到endAngle
				// 即 [startAngle, π] 或 [-π, endAngle]
				inRange = (normalizedAngle >= arc.startAngle || normalizedAngle <= arc.endAngle);
			}

			if (!inRange && j > 0) break; // 超出范围，停止绘制

			// 使用规范化后的角度进行计算
			double cosAngle = std::cos(normalizedAngle);
			double sinAngle = std::sin(normalizedAngle);

			QPointF lineStart = widgetCenter + QPointF(innerRadius * cosAngle * m_scaleFactor,
				innerRadius * -sinAngle * m_scaleFactor);
			QPointF lineEnd = widgetCenter + QPointF(outerRadius * cosAngle * m_scaleFactor,
				outerRadius * -sinAngle * m_scaleFactor);

			painter.drawLine(lineStart, lineEnd);

			// 绘制测量线方向指示
			if (params.direction == 0) {
				// 从内到外
				QPointF dir = (lineEnd - lineStart);
				double len = std::sqrt(dir.x() * dir.x() + dir.y() * dir.y());
				if (len > 0) {
					dir = dir / len;
					QPointF arrowTip = lineStart + dir * 15.0;
					QPointF arrowLeft = arrowTip - dir * 5.0 + QPointF(-dir.y(), dir.x()) * 3.0;
					QPointF arrowRight = arrowTip - dir * 5.0 - QPointF(-dir.y(), dir.x()) * 3.0;

					painter.drawLine(arrowTip, arrowLeft);
					painter.drawLine(arrowTip, arrowRight);
				}
			}
			else {
				// 从外到内
				QPointF dir = (lineStart - lineEnd);
				double len = std::sqrt(dir.x() * dir.x() + dir.y() * dir.y());
				if (len > 0) {
					dir = dir / len;
					QPointF arrowTip = lineEnd + dir * 15.0;
					QPointF arrowLeft = arrowTip - dir * 5.0 + QPointF(-dir.y(), dir.x()) * 3.0;
					QPointF arrowRight = arrowTip - dir * 5.0 - QPointF(-dir.y(), dir.x()) * 3.0;

					painter.drawLine(arrowTip, arrowLeft);
					painter.drawLine(arrowTip, arrowRight);
				}
			}
		}

		// 绘制控制点
		// 中心点
		painter.setBrush(QBrush(Qt::yellow));
		painter.setPen(QPen(Qt::black, 1));
		painter.drawEllipse(widgetCenter, 6, 6);

		// 起始和结束角度控制点（在辅助线上，半径R的圆弧上）
		painter.setBrush(QBrush(Qt::green));
		painter.drawEllipse(guideStart, 5, 5);
		painter.drawEllipse(guideEnd, 5, 5);

		// 绘制测量点（如果显示开关打开）
		if (params.showPoints) {
			painter.setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
			for (const auto& point : params.points) {
				if (point.valid) {
					QPointF widgetPoint = imageToWidget(point.position);
					// 绘制十字线
					painter.drawLine(widgetPoint - QPointF(5, 0), widgetPoint + QPointF(5, 0));
					painter.drawLine(widgetPoint - QPointF(0, 5), widgetPoint + QPointF(0, 5));
				}
			}
		}

		// 绘制ID标签
		painter.setPen(QPen(Qt::black, 1));
		painter.drawText(widgetCenter + QPointF(10, -10), QString::number(arc.id));
	}

	painter.restore();
}

void ImageViewWidget::updateArcMeasurePoints(int arcIndex)
{
	if (m_cvImage.empty() || m_cvImage.channels() != 1 ||
		arcIndex < 0 || arcIndex >= static_cast<int>(m_arcMeasures.size())) {
		return;
	}

	const ArcMeasureTool& arc = m_arcMeasures[arcIndex];
	ArcMeasureParams& params = m_arcMeasureParams[arcIndex];

	params.points.clear();

	// 计算内外圆半径（内圆半径R-d/2，外圆半径R+d/2）
	double innerRadius = arc.radius - arc.thickness / 2.0;
	double outerRadius = arc.radius + arc.thickness / 2.0;

	if (innerRadius < 1.0) innerRadius = 1.0;

	// 计算有效圆弧的角度范围
	double angleRange = arc.endAngle - arc.startAngle;
	if (angleRange < 0) angleRange += 2 * M_PI;

	// 计算采样角度数量
	int numAngles = static_cast<int>(angleRange / params.angleSpacing);
	if (numAngles <= 0) numAngles = 1;

	// 计算有效区域的角度范围（逆时针从startAngle到endAngle）
	double effectiveStartAngle = arc.startAngle;
	double effectiveEndAngle = arc.endAngle;

	// 如果endAngle < startAngle，说明跨越了0度线，需要调整
	if (effectiveEndAngle < effectiveStartAngle) {
		effectiveEndAngle += 2 * M_PI;
	}

	for (int i = 0; i <= numAngles; ++i) {
		// 计算当前角度（从startAngle开始，按angleSpacing递增）
		double angle = arc.startAngle + i * params.angleSpacing;

		// 规范化角度到[-π, π]
		double normalizedAngle = normalizeAngle(angle);

		// 检查是否在有效圆弧范围内（逆时针从startAngle到endAngle）
		bool inRange = false;

		if (arc.endAngle >= arc.startAngle) {
			// 正常情况：endAngle >= startAngle
			// 有效区域是 [startAngle, endAngle]
			inRange = (normalizedAngle >= arc.startAngle && normalizedAngle <= arc.endAngle);
		}
		else {
			// 跨越0度线：endAngle < startAngle
			// 有效区域是逆时针从startAngle到endAngle
			// 即 [startAngle, π] 或 [-π, endAngle]
			inRange = (normalizedAngle >= arc.startAngle || normalizedAngle <= arc.endAngle);
		}

		// 如果不在有效范围内，停止检测
		if (!inRange) {
			break;
		}

		// 使用规范化后的角度进行计算
		double cosAngle = std::cos(normalizedAngle);
		double sinAngle = std::sin(normalizedAngle);

		// 计算采样线的起点和终点（在内外圆之间）
		// direction=0: 从内到外, direction=1: 从外到内（默认）
		QPointF lineStart, lineEnd;
		if (params.direction == 0) {
			// 从内到外（注意：图像坐标系y向下，需使用 -sinAngle 保持与角度定义一致）
			lineStart = arc.center + QPointF(innerRadius * cosAngle, innerRadius * -sinAngle);
			lineEnd = arc.center + QPointF(outerRadius * cosAngle, outerRadius * -sinAngle);
		}
		else {
			// 从外到内（默认）
			lineStart = arc.center + QPointF(outerRadius * cosAngle, outerRadius * -sinAngle);
			lineEnd = arc.center + QPointF(innerRadius * cosAngle, innerRadius * -sinAngle);
		}

		// 在径向线上采样点
		std::vector<QPoint> samplePoints;
		double lineLength = std::sqrt(std::pow(lineEnd.x() - lineStart.x(), 2) +
			std::pow(lineEnd.y() - lineStart.y(), 2));
		int numSamples = static_cast<int>(lineLength);
		if (numSamples < 2) numSamples = 2;

		for (int j = 0; j < numSamples; ++j) {
			double u = static_cast<double>(j) / (numSamples - 1);
			QPointF samplePoint = lineStart + (lineEnd - lineStart) * u;
			samplePoints.push_back(QPoint(static_cast<int>(samplePoint.x()),
				static_cast<int>(samplePoint.y())));
		}

		// 检测边缘点：取第一个大于阈值变化最小值的点
		ArcMeasurePoint measurePoint;
		measurePoint.angle = normalizedAngle; // 使用规范化后的角度
		measurePoint.valid = false;

		for (size_t j = 1; j < samplePoints.size(); ++j) {
			const QPoint& prev = samplePoints[j - 1];
			const QPoint& curr = samplePoints[j];

			// 检查坐标是否在图像范围内
			if (prev.x() < 0 || prev.x() >= m_cvImage.cols || prev.y() < 0 || prev.y() >= m_cvImage.rows ||
				curr.x() < 0 || curr.x() >= m_cvImage.cols || curr.y() < 0 || curr.y() >= m_cvImage.rows) {
				continue;
			}

			// 计算像素差值（阈值变化）
			int prevValue = static_cast<int>(m_cvImage.at<uchar>(prev.y(), prev.x()));
			int currValue = static_cast<int>(m_cvImage.at<uchar>(curr.y(), curr.x()));
			int diff = std::abs(currValue - prevValue);

			// 取第一个大于阈值变化最小值的点
			if (diff >= params.pixelThreshold) {
				measurePoint.position = QPointF(curr.x(), curr.y());
				measurePoint.valid = true;
				break; // 找到第一个满足条件的点
			}
		}

		params.points.push_back(measurePoint);
	}

	emit arcMeasureUpdated(arc.id, arc.center, arc.radius, arc.startAngle, arc.endAngle, arc.thickness);
}

bool ImageViewWidget::isPointOnArcCenter(const QPointF& widgetPoint, int arcIndex) const
{
	if (arcIndex < 0 || arcIndex >= static_cast<int>(m_arcMeasures.size())) return false;

	const ArcMeasureTool& arc = m_arcMeasures[arcIndex];
	QPointF widgetCenter = imageToWidget(arc.center);

	double detectionRadius = std::max(8.0, std::min(15.0, 8.0 / m_scaleFactor));
	double distance = std::sqrt(std::pow(widgetPoint.x() - widgetCenter.x(), 2) +
		std::pow(widgetPoint.y() - widgetCenter.y(), 2));
	return distance < detectionRadius;
}

bool ImageViewWidget::isPointOnArcRadius(const QPointF& widgetPoint, int arcIndex) const
{
	if (arcIndex < 0 || arcIndex >= static_cast<int>(m_arcMeasures.size())) return false;

	const ArcMeasureTool& arc = m_arcMeasures[arcIndex];
	QPointF imagePoint = widgetToImage(widgetPoint);
	QPointF widgetCenter = imageToWidget(arc.center);

	// 计算点到圆心的距离
	QPointF delta = imagePoint - arc.center;
	double distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());

	// 计算角度
	double angle = std::atan2(-delta.y(), delta.x()); // Qt坐标系，y轴向下

	// 检查是否在有效圆弧范围内（不包括起始和终点）
	double angleRange = arc.endAngle - arc.startAngle;
	if (angleRange < 0) angleRange += 2 * M_PI;

	bool inAngleRange = false;
	if (arc.endAngle >= arc.startAngle) {
		inAngleRange = (angle > arc.startAngle && angle < arc.endAngle);
	}
	else {
		// 跨越0度线
		inAngleRange = (angle > arc.startAngle || angle < arc.endAngle);
	}

	if (!inAngleRange) return false;

	// 检查距离是否接近半径（允许一定误差）
	double detectionRadius = std::max(8.0, std::min(15.0, 8.0 / m_scaleFactor));
	double distanceDiff = std::abs(distance - arc.radius);

	return distanceDiff * m_scaleFactor < detectionRadius;
}

bool ImageViewWidget::isPointOnArcStartHandle(const QPointF& widgetPoint, int arcIndex) const
{
	if (arcIndex < 0 || arcIndex >= static_cast<int>(m_arcMeasures.size())) return false;

	const ArcMeasureTool& arc = m_arcMeasures[arcIndex];
	QPointF imagePoint = widgetToImage(widgetPoint);
	QPointF widgetCenter = imageToWidget(arc.center);

	// 计算点到圆心的距离和角度
	QPointF delta = imagePoint - arc.center;
	double distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());
	double angle = std::atan2(-delta.y(), delta.x());

	// 检查距离是否接近半径R（辅助线位置）
	double detectionRadius = std::max(8.0, std::min(15.0, 8.0 / m_scaleFactor));
	double distanceDiff = std::abs(distance - arc.radius);

	if (distanceDiff * m_scaleFactor > detectionRadius) return false;

	// 检查角度是否接近起始角度
	double angleDiff = std::abs(angle - arc.startAngle);
	if (angleDiff > M_PI) angleDiff = 2 * M_PI - angleDiff;

	// 允许一定角度误差（约5度）
	return angleDiff < (5.0 * M_PI / 180.0);
}

bool ImageViewWidget::isPointOnArcEndHandle(const QPointF& widgetPoint, int arcIndex) const
{
	if (arcIndex < 0 || arcIndex >= static_cast<int>(m_arcMeasures.size())) return false;

	const ArcMeasureTool& arc = m_arcMeasures[arcIndex];
	QPointF imagePoint = widgetToImage(widgetPoint);
	QPointF widgetCenter = imageToWidget(arc.center);

	// 计算点到圆心的距离和角度
	QPointF delta = imagePoint - arc.center;
	double distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());
	double angle = std::atan2(-delta.y(), delta.x());

	// 检查距离是否接近半径R（辅助线位置）
	double detectionRadius = std::max(8.0, std::min(15.0, 8.0 / m_scaleFactor));
	double distanceDiff = std::abs(distance - arc.radius);

	if (distanceDiff * m_scaleFactor > detectionRadius) return false;

	// 检查角度是否接近结束角度
	double angleDiff = std::abs(angle - arc.endAngle);
	if (angleDiff > M_PI) angleDiff = 2 * M_PI - angleDiff;

	// 允许一定角度误差（约5度）
	return angleDiff < (5.0 * M_PI / 180.0);
}

bool ImageViewWidget::isPointOnArcThicknessHandle(const QPointF& widgetPoint, int arcIndex, bool& isInner) const
{
	if (arcIndex < 0 || arcIndex >= static_cast<int>(m_arcMeasures.size())) return false;

	const ArcMeasureTool& arc = m_arcMeasures[arcIndex];
	QPointF imagePoint = widgetToImage(widgetPoint);
	QPointF widgetCenter = imageToWidget(arc.center);

	// 计算点到圆心的距离和角度
	QPointF delta = imagePoint - arc.center;
	double distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());
	double angle = std::atan2(-delta.y(), delta.x());

	// 计算内外圆半径
	double innerRadius = arc.radius - arc.thickness / 2.0;
	double outerRadius = arc.radius + arc.thickness / 2.0;

	// 检查是否在有效圆弧范围内
	double angleRange = arc.endAngle - arc.startAngle;
	if (angleRange < 0) angleRange += 2 * M_PI;

	bool inAngleRange = false;
	if (arc.endAngle >= arc.startAngle) {
		inAngleRange = (angle >= arc.startAngle && angle <= arc.endAngle);
	}
	else {
		inAngleRange = (angle >= arc.startAngle || angle <= arc.endAngle);
	}

	if (!inAngleRange) return false;

	// 检查距离是否接近内圆或外圆弧线
	double detectionRadius = std::max(8.0, std::min(15.0, 8.0 / m_scaleFactor));
	double innerDiff = std::abs(distance - innerRadius);
	double outerDiff = std::abs(distance - outerRadius);

	if (innerDiff * m_scaleFactor < detectionRadius) {
		isInner = true;
		return true;
	}
	else if (outerDiff * m_scaleFactor < detectionRadius) {
		isInner = false;
		return true;
	}

	return false;
}

void ImageViewWidget::updateArcMeasure(int index)
{
	if (index < 0 || index >= static_cast<int>(m_arcMeasures.size())) return;

	ArcMeasureTool& arc = m_arcMeasures[index];
	emit arcMeasureUpdated(arc.id, arc.center, arc.radius, arc.startAngle, arc.endAngle, arc.thickness);

	if (!m_cvImage.empty() && m_cvImage.channels() == 1) {
		updateArcMeasurePoints(index);
	}

	update();
}

double ImageViewWidget::normalizeAngle(double angle) const
{
	// 规范化角度到[-π, π]范围
	while (angle > M_PI) angle -= 2 * M_PI;
	while (angle < -M_PI) angle += 2 * M_PI;
	return angle;
}

// ===================== 缩放 =====================
void ImageViewWidget::wheelEvent(QWheelEvent* event)
{
	if (m_image.isNull()) return;

	const double factor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
	const double oldScale = m_scaleFactor;
	m_scaleFactor = std::clamp(m_scaleFactor * factor, 0.05, 50.0);

	// 保持鼠标位置为缩放中心
	QPointF mousePos = event->position();
	QPointF imgPos = (mousePos - m_offset) / oldScale;
	QPointF newOffset = mousePos - imgPos * m_scaleFactor;
	m_offset = newOffset;

	updateScaledImage(true);  // ✅ 保留偏移
	update();
}

// ===================== 平移 =====================
void ImageViewWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		QPointF widgetPos = event->position();

		// 检查圆弧测量工具交互（按优先级顺序检查）
		if (m_arcMeasureToolEnabled && !m_image.isNull()) {
			for (size_t i = 0; i < m_arcMeasures.size(); ++i) {
				// 优先检查旋转控制点（起始和结束）
				// 如果起始点和终点重合，检查鼠标更接近哪个点
				bool onStart = isPointOnArcStartHandle(widgetPos, static_cast<int>(i));
				bool onEnd = isPointOnArcEndHandle(widgetPos, static_cast<int>(i));

				if (onStart || onEnd) {
					// 如果两个点都检测到（重合情况），根据鼠标位置确定优先级
					if (onStart && onEnd) {
						// 重合情况：检查鼠标更接近哪个点（拖动时选中的点有优先级）
						const ArcMeasureTool& arc = m_arcMeasures[i];
						QPointF imagePoint = widgetToImage(widgetPos);
						QPointF delta = imagePoint - arc.center;
						double angle = std::atan2(-delta.y(), delta.x());

						double startDist = std::abs(angle - arc.startAngle);
						if (startDist > M_PI) startDist = 2 * M_PI - startDist;
						double endDist = std::abs(angle - arc.endAngle);
						if (endDist > M_PI) endDist = 2 * M_PI - endDist;

						// 选择距离更近的点
						if (startDist <= endDist) {
							m_arcDragState = DraggingArcStart;
							m_isDraggingStartPoint = true;
						}
						else {
							m_arcDragState = DraggingArcEnd;
							m_isDraggingStartPoint = false;
						}
					}
					else if (onStart) {
						m_arcDragState = DraggingArcStart;
						m_isDraggingStartPoint = true;
					}
					else {
						m_arcDragState = DraggingArcEnd;
						m_isDraggingStartPoint = false;
					}

					m_selectedArcIndex = static_cast<int>(i);
					m_selectedThicknessIsInner = false;
					m_lastMousePos = event->pos();
					setCursor(Qt::SizeAllCursor);
					return;
				}
				// 检查厚度控制点（内圆或外圆弧线）
				else if (isPointOnArcThicknessHandle(widgetPos, static_cast<int>(i), m_selectedThicknessIsInner)) {
					m_arcDragState = DraggingArcThickness;
					m_selectedArcIndex = static_cast<int>(i);
					m_lastMousePos = event->pos();
					setCursor(Qt::SizeHorCursor);
					return;
				}
				// 检查有效圆弧（用于拖动半径）
				else if (isPointOnArcRadius(widgetPos, static_cast<int>(i))) {
					m_arcDragState = DraggingArcRadius;
					m_selectedArcIndex = static_cast<int>(i);
					m_selectedThicknessIsInner = false;
					m_lastMousePos = event->pos();
					setCursor(Qt::SizeHorCursor);
					return;
				}
				// 最后检查中心
				else if (isPointOnArcCenter(widgetPos, static_cast<int>(i))) {
					m_arcDragState = DraggingArcCenter;
					m_selectedArcIndex = static_cast<int>(i);
					m_selectedThicknessIsInner = false;
					m_lastMousePos = event->pos();
					setCursor(Qt::SizeAllCursor);
					return;
				}
			}
		}

		// 检查矩形工具交互(按优先级顺序检查:旋转控制点 > 顶点 > 中心)
		if (m_rectangleToolEnabled && !m_image.isNull()) {
			for (size_t i = 0; i < m_rectangles.size(); ++i) {
				// 优先检查旋转控制点
				if (isPointOnRectangleRotateHandle(widgetPos, static_cast<int>(i))) {
					m_rectDragState = DraggingRectRotate;
					m_selectedRectIndex = static_cast<int>(i);
					m_selectedCorner = -1;
					m_lastMousePos = event->pos();
					setCursor(Qt::SizeAllCursor);
					return;
				}
				// 然后检查顶点
				int cornerIndex = isPointOnRectangleCorner(widgetPos, static_cast<int>(i));
				if (cornerIndex >= 0) {
					m_rectDragState = DraggingRectCorner;
					m_selectedRectIndex = static_cast<int>(i);
					m_selectedCorner = cornerIndex;
					m_lastMousePos = event->pos();
					setCursor(Qt::SizeFDiagCursor);
					return;
				}
				// 最后检查中心
				if (isPointOnRectangleCenter(widgetPos, static_cast<int>(i))) {
					m_rectDragState = DraggingRectCenter;
					m_selectedRectIndex = static_cast<int>(i);
					m_selectedCorner = -1;
					m_lastMousePos = event->pos();
					setCursor(Qt::SizeAllCursor);
					return;
				}
			}
		}

		// 检查直线测量工具交互
		if (m_measureToolEnabled && !m_image.isNull()) {
			if (isPointOnArrowHead(widgetPos)) {
				m_dragState = DraggingArrowHead;
				m_lastMousePos = event->pos();
				setCursor(Qt::ClosedHandCursor);
				return;
			}
			else if (isPointOnArrowTail(widgetPos)) {
				m_dragState = DraggingArrowTail;
				m_lastMousePos = event->pos();
				setCursor(Qt::ClosedHandCursor);
				return;
			}
			else if (isPointOnRectEdge(widgetPos)) {
				m_dragState = DraggingRectEdge;
				m_lastMousePos = event->pos();
				setCursor(Qt::SizeVerCursor);
				return;
			}
			else if (isPointOnRectCenter(widgetPos)) {
				m_dragState = DraggingWholeMeasure;
				m_lastMousePos = event->pos();
				setCursor(Qt::SizeAllCursor);
				return;
			}
		}

		// 默认的图像拖动行为(只有在没有选中任何矩形控制点时才触发)
		if (!m_scaledPixmap.isNull() && m_rectDragState == RectNoDrag) {
			m_dragging = true;
			m_lastMousePos = event->pos();
			setCursor(Qt::ClosedHandCursor);
		}
	}
}

void ImageViewWidget::mouseMoveEvent(QMouseEvent* event)
{
	QPointF widgetPos = event->position();

	// 如果不在拖动状态,检查鼠标是否在控制点上并更新光标
	// 优先检查圆弧测量工具控制点
	if (m_arcMeasureToolEnabled && !m_image.isNull() && m_arcDragState == ArcNoDrag && !m_dragging) {
		bool foundControlPoint = false;
		for (size_t i = 0; i < m_arcMeasures.size(); ++i) {
			bool dummyInner = false;
			if (isPointOnArcStartHandle(widgetPos, static_cast<int>(i)) ||
				isPointOnArcEndHandle(widgetPos, static_cast<int>(i))) {
				setCursor(Qt::SizeAllCursor);
				foundControlPoint = true;
				break;
			}
			else if (isPointOnArcThicknessHandle(widgetPos, static_cast<int>(i), dummyInner)) {
				setCursor(Qt::SizeHorCursor);
				foundControlPoint = true;
				break;
			}
			else if (isPointOnArcRadius(widgetPos, static_cast<int>(i))) {
				setCursor(Qt::SizeHorCursor);
				foundControlPoint = true;
				break;
			}
			else if (isPointOnArcCenter(widgetPos, static_cast<int>(i))) {
				setCursor(Qt::SizeAllCursor);
				foundControlPoint = true;
				break;
			}
		}
		if (foundControlPoint) {
			return;
		}
	}

	// 然后检查矩形工具控制点,避免触发图像拖动
	if (m_rectangleToolEnabled && !m_image.isNull() && m_rectDragState == RectNoDrag && !m_dragging) {
		bool foundControlPoint = false;
		for (size_t i = 0; i < m_rectangles.size(); ++i) {
			// 优先检查旋转控制点
			if (isPointOnRectangleRotateHandle(widgetPos, static_cast<int>(i))) {
				setCursor(Qt::SizeAllCursor);
				foundControlPoint = true;
				break;
			}
			// 检查顶点
			if (isPointOnRectangleCorner(widgetPos, static_cast<int>(i)) >= 0) {
				setCursor(Qt::SizeFDiagCursor);
				foundControlPoint = true;
				break;
			}
			// 检查中心
			if (isPointOnRectangleCenter(widgetPos, static_cast<int>(i))) {
				setCursor(Qt::SizeAllCursor);
				foundControlPoint = true;
				break;
			}
		}
		if (foundControlPoint) {
			// 如果找到控制点,确保不会触发图像拖动
			return;
		}
	}

	if (m_dragging && !m_scaledPixmap.isNull()) {
		QPoint delta = event->pos() - m_lastMousePos;
		m_offset += delta;
		m_lastMousePos = event->pos();
		update();
	}
	else if (m_dragState != NoDrag && m_measureToolEnabled) {
		QPointF currentWidgetPos = event->position();
		QPointF currentImagePos = widgetToImage(currentWidgetPos);
		QPointF lastImagePos = widgetToImage(m_lastMousePos);

		switch (m_dragState) {
		case DraggingArrowHead:
			m_arrowEnd = currentImagePos;
			break;
		case DraggingArrowTail:
			m_arrowStart = currentImagePos;
			break;
		case DraggingRectEdge: {
			// 计算矩形宽度变化
			QPointF arrowVec = m_arrowEnd - m_arrowStart;
			double arrowLength = std::sqrt(arrowVec.x() * arrowVec.x() + arrowVec.y() * arrowVec.y());
			if (arrowLength > 1e-6) {
				QPointF dirVec = arrowVec / arrowLength;
				QPointF perpVec(-dirVec.y(), dirVec.x());

				// 计算鼠标移动在垂直方向的分量
				QPointF deltaImage = currentImagePos - lastImagePos;
				double deltaWidth = deltaImage.x() * perpVec.x() + deltaImage.y() * perpVec.y();

				// 更新矩形宽度（允许负值，负值表示方向翻转）
				int newRectWidth = static_cast<int>(m_rectWidth + deltaWidth * 2);

				// 检查是否翻转方向
				if (newRectWidth * m_rectWidth < 0) { // 符号变化表示翻转
					m_lineDirection = 1 - m_lineDirection; // 翻转方向
				}

				m_rectWidth = newRectWidth;

				// 确保最小宽度为1（绝对值）
				if (std::abs(m_rectWidth) < 1) {
					m_rectWidth = (m_rectWidth >= 0) ? 1 : -1;
				}
			}
			break;
		}
		case DraggingWholeMeasure: {
			// 整体移动测量模块
			QPointF deltaImage = currentImagePos - lastImagePos;
			m_arrowStart += deltaImage;
			m_arrowEnd += deltaImage;
			break;
		}
		default:
			break;
		}

		m_lastMousePos = event->pos();

		// 更新测量点
		if (!m_cvImage.empty() && m_cvImage.channels() == 1) {
			updateMeasurePoints();
		}

		update();
	}
	else if (m_rectDragState != RectNoDrag && m_rectangleToolEnabled) {
		QPointF currentWidgetPos = event->position();
		QPointF currentImagePos = widgetToImage(currentWidgetPos);
		QPointF lastImagePos = widgetToImage(m_lastMousePos);

		if (m_selectedRectIndex >= 0 && m_selectedRectIndex < static_cast<int>(m_rectangles.size())) {
			RectangleTool& rect = m_rectangles[m_selectedRectIndex];

			switch (m_rectDragState) {
			case DraggingRectCenter: {
				// 移动矩形中心
				QPointF deltaImage = currentImagePos - lastImagePos;
				rect.center += deltaImage;
				break;
			}
			case DraggingRectCorner: {
				if (m_selectedCorner >= 0 && m_selectedCorner < 4) {
					// 当前矩形的旋转角
					double cosAngle = std::cos(rect.angle);
					double sinAngle = std::sin(rect.angle);

					// 获取矩形四个顶点（图像/world 坐标）
					std::array<QPointF, 4> corners;
					double hw = rect.width / 2.0;
					double hh = rect.height / 2.0;
					// world = center + (lx*cos - ly*sin, lx*sin + ly*cos)
					corners[0] = rect.center + QPointF(hw * cosAngle - hh * sinAngle, hw * sinAngle + hh * cosAngle); // 右下
					corners[1] = rect.center + QPointF(-hw * cosAngle - hh * sinAngle, -hw * sinAngle + hh * cosAngle); // 左下
					corners[2] = rect.center + QPointF(hw * cosAngle + hh * sinAngle, hw * sinAngle - hh * cosAngle); // 右上
					corners[3] = rect.center + QPointF(-hw * cosAngle + hh * sinAngle, -hw * sinAngle - hh * cosAngle); // 左上

					// 当前拖动的顶点（数组内元素）
					QPointF draggedCorner = currentImagePos; // 使用鼠标位置作为新的拖动顶点

					// 正确的对角点索引（0<->3, 1<->2）
					int oppositeIndex = m_selectedCorner ^ 3; // 修复：使用异或 3
					QPointF fixedCorner = corners[oppositeIndex]; // 对角点保持不动

					// 新的中心为对角线中点
					QPointF newCenter = (draggedCorner + fixedCorner) * 0.5;

					// 在矩形局部坐标系（即旋转回去）计算对角向量的局部分量
					QPointF localVec = draggedCorner - fixedCorner;
					double localX = localVec.x() * cosAngle + localVec.y() * sinAngle;  // 投影到局部 X 轴
					double localY = -localVec.x() * sinAngle + localVec.y() * cosAngle; // 投影到局部 Y 轴

					// 由对角点差得到的是完整宽高（等于 2*half）
					double newWidth = std::abs(localX);
					double newHeight = std::abs(localY);

					// 最小尺寸保护
					const double MIN_SIZE = 10.0;
					rect.center = newCenter;
					rect.width = std::max(MIN_SIZE, newWidth);
					rect.height = std::max(MIN_SIZE, newHeight);
				}
				break;
			}
			case DraggingRectRotate: {
				// 旋转矩形
				QPointF delta = currentImagePos - rect.center;
				double newAngle = std::atan2(delta.y(), delta.x());
				rect.angle = newAngle;
				break;
			}
			default:
				break;
			}

			updateRectangle(m_selectedRectIndex);
		}

		m_lastMousePos = event->pos();
	}
	else if (m_arcDragState != ArcNoDrag && m_arcMeasureToolEnabled) {
		QPointF currentWidgetPos = event->position();
		QPointF currentImagePos = widgetToImage(currentWidgetPos);

		if (m_selectedArcIndex >= 0 && m_selectedArcIndex < static_cast<int>(m_arcMeasures.size())) {
			ArcMeasureTool& arc = m_arcMeasures[m_selectedArcIndex];
			ArcMeasureParams& params = m_arcMeasureParams[m_selectedArcIndex];

			switch (m_arcDragState) {
			case DraggingArcCenter: {
				// 移动圆弧中心（移动整个工具）
				QPointF lastImagePos = widgetToImage(m_lastMousePos);
				QPointF deltaImage = currentImagePos - lastImagePos;
				arc.center += deltaImage;
				break;
			}
			case DraggingArcRadius: {
				// 拖动有效圆弧改变半径（除了起始和终点）
				QPointF delta = currentImagePos - arc.center;
				double newRadius = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());
				arc.radius = std::max(10.0, newRadius);
				break;
			}
			case DraggingArcStart: {
				// 拖动起始位置改变起始角度，起始点在辅助线上（半径R）
				QPointF delta = currentImagePos - arc.center;
				double distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());

				// 将点投影到辅助线上（半径R的圆弧）
				if (distance > 0.1) {
					QPointF projectedPoint = arc.center + (delta / distance) * arc.radius;
					QPointF newDelta = projectedPoint - arc.center;
					double newAngle = std::atan2(-newDelta.y(), newDelta.x());
					newAngle = normalizeAngle(newAngle);

					// 计算从旧起始点到新起始点的角度差（逆时针方向）
					double oldStartAngle = arc.startAngle;
					double angleDiff = newAngle - oldStartAngle;
					if (angleDiff < 0) angleDiff += 2 * M_PI;

					// 检查是否与终点重合
					double startToEnd = arc.endAngle - oldStartAngle;
					if (startToEnd < 0) startToEnd += 2 * M_PI;

					// 检查新起始点与终点的关系
					double newToEnd = newAngle - arc.endAngle;
					if (newToEnd < 0) newToEnd += 2 * M_PI;

					// 检查是否超过终点（顺时针方向）
					double endToNew = arc.endAngle - newAngle;
					if (endToNew < 0) endToNew += 2 * M_PI;

					// 如果起始点与终点重合（在逆时针方向上），终点一起移动
					if (newToEnd < 0.1) {
						// 起始点与终点重合，终点跟随
						arc.startAngle = newAngle;
						arc.endAngle = newAngle;
					}
					else if (endToNew < 0.1) {
						// 起始点超过终点（顺时针方向），终点停留，但起始点可以继续移动
						arc.startAngle = newAngle;
					}
					else {
						// 正常情况，起始点移动
						arc.startAngle = newAngle;
					}
				}
				break;
			}
			case DraggingArcEnd: {
				// 拖动末端位置改变结束角度，终点在辅助线上（半径R）
				// 起始点固定状态
				QPointF delta = currentImagePos - arc.center;
				double distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());

				// 将点投影到辅助线上（半径R的圆弧）
				if (distance > 0.1) {
					QPointF projectedPoint = arc.center + (delta / distance) * arc.radius;
					QPointF newDelta = projectedPoint - arc.center;
					double newAngle = std::atan2(-newDelta.y(), newDelta.x());
					newAngle = normalizeAngle(newAngle);

					// 计算从起始点到新终点的角度差（逆时针方向）
					double startToNew = newAngle - arc.startAngle;
					if (startToNew < 0) startToNew += 2 * M_PI;

					// 计算从起始点到旧终点的角度差（逆时针方向）
					double startToOldEnd = arc.endAngle - arc.startAngle;
					if (startToOldEnd < 0) startToOldEnd += 2 * M_PI;

					// 检查逆时针一圈是否与起始点重合
					if (startToNew >= 2 * M_PI - 0.1) {
						// 逆时针一圈恰好与起始点重合，只能顺时针运动
						// 检查是否顺时针与起始点重合
						double clockwiseDiff = arc.startAngle - newAngle;
						if (clockwiseDiff < 0) clockwiseDiff += 2 * M_PI;

						if (clockwiseDiff < 0.1) {
							// 顺时针与起始点重合，不能超过起始点，只能逆时针拖动
							// 保持终点在起始点附近（逆时针方向）
							arc.endAngle = normalizeAngle(arc.startAngle + 0.1);
						}
						else {
							// 顺时针方向，可以移动
							arc.endAngle = newAngle;
						}
					}
					else {
						// 正常逆时针方向移动
						arc.endAngle = newAngle;
					}
				}
				break;
			}
			case DraggingArcThickness: {
				// 拖动厚度控制点改变厚度
				QPointF delta = currentImagePos - arc.center;
				double distance = std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());

				if (m_selectedThicknessIsInner) {
					// 拖动内圆弧线
					double newThickness = (arc.radius - distance) * 2.0;

					// 如果超过R，自动翻转检测方向
					if (distance > arc.radius) {
						// 翻转：内圆变成外圆
						arc.thickness = (distance - arc.radius) * 2.0;
						params.direction = 1 - params.direction; // 翻转检测方向
						m_selectedThicknessIsInner = false; // 现在变成外圆了
					}
					else {
						arc.thickness = std::max(5.0, newThickness);
					}
				}
				else {
					// 拖动外圆弧线
					double newThickness = (distance - arc.radius) * 2.0;

					// 如果小于R，自动翻转检测方向
					if (distance < arc.radius) {
						// 翻转：外圆变成内圆
						arc.thickness = (arc.radius - distance) * 2.0;
						params.direction = 1 - params.direction; // 翻转检测方向
						m_selectedThicknessIsInner = true; // 现在变成内圆了
					}
					else {
						arc.thickness = std::max(5.0, newThickness);
					}
				}
				break;
			}
			default:
				break;
			}

			updateArcMeasure(m_selectedArcIndex);
		}

		m_lastMousePos = event->pos();
	}
}

void ImageViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		if (m_dragState != NoDrag) {
			m_dragState = NoDrag;
			setCursor(Qt::ArrowCursor);
		}
		else if (m_rectDragState != RectNoDrag) {
			m_rectDragState = RectNoDrag;
			m_selectedRectIndex = -1;
			m_selectedCorner = -1;
			setCursor(Qt::ArrowCursor);
		}
		else if (m_arcDragState != ArcNoDrag) {
			m_arcDragState = ArcNoDrag;
			m_selectedArcIndex = -1;
			m_selectedThicknessIsInner = false;
			m_isDraggingStartPoint = false;
			setCursor(Qt::ArrowCursor);
		}
		else {
			m_dragging = false;
			setCursor(Qt::ArrowCursor);
		}
	}
}

// ===================== 自适应缩放 =====================
void ImageViewWidget::fitToWidget()
{
	if (m_image.isNull()) return;

	QSizeF imgSize = m_image.size();
	QSizeF widgetSize = size();

	if (widgetSize.width() <= 0 || widgetSize.height() <= 0)
		return;

	double scaleX = widgetSize.width() / imgSize.width();
	double scaleY = widgetSize.height() / imgSize.height();
	m_scaleFactor = std::min(scaleX, scaleY);

	updateScaledImage(false);
	update();
}

// ===================== 更新缩放图像 =====================
void ImageViewWidget::updateScaledImage(bool keepOffset)
{
	if (m_image.isNull()) return;

	QSizeF imgSize = m_image.size();
	QSizeF scaledSize = imgSize * m_scaleFactor;
	QSize scaledInt = scaledSize.toSize();

	m_scaledPixmap = QPixmap::fromImage(m_image).scaled(
		scaledInt,
		Qt::KeepAspectRatio,
		Qt::SmoothTransformation
	);

	if (!keepOffset)
	{
		// 居中偏移
		const double xOffset = (width() - scaledInt.width()) / 2.0;
		const double yOffset = (height() - scaledInt.height()) / 2.0;
		m_offset = QPointF(xOffset, yOffset);
	}
}

void ImageViewWidget::fitImageToWidget()
{
	if (m_image.isNull())
		return;

	fitToWidget();        // 自动计算 scale
	updateScaledImage(true);  // ✅ 刷新 Pixmap
	update();             // ✅ 重绘

}

void ImageViewWidget::showOriginalImage()
{
	if (m_image.isNull())
		return;

	m_scaleFactor = 1.0;
	fitToWidget();
	updateScaledImage(true);  // ✅ 生成新 Pixmap 并更新偏移
	update();
}

void ImageViewWidget::clearImage()
{
	m_image = QImage();
	m_scaledPixmap = QPixmap();
	update();
}

void ImageViewWidget::InputImg(int mode, cv::Mat& Img)
{
	displayMat(mode, Img);
}

// ========== 拖拽加载 ==========
void ImageViewWidget::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
}

void ImageViewWidget::dropEvent(QDropEvent* event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty()) return;

	QString filePath = urls.first().toLocalFile();
	if (!filePath.isEmpty()) {
		loadImage(filePath);
	}
}
// ===================== 新增菜单选项 =====================
void ImageViewWidget::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu menu(this);
	QAction* resetAction = menu.addAction(tr("重置自适应显示"));
	QAction* originalAction = menu.addAction(tr("显示原始图像"));
	QAction* clearAction = menu.addAction(tr("清除图像"));

	// 新增测量工具菜单项
	QAction* measureAction = menu.addAction(
		m_measureToolEnabled ? tr("禁用测量工具") : tr("启用测量工具"));
	QAction* clearMeasureAction = menu.addAction(tr("清除测量结果"));

	// 新增矩形工具菜单项
	QAction* rectangleAction = menu.addAction(
		m_rectangleToolEnabled ? tr("禁用矩形工具") : tr("启用矩形工具"));
	QAction* addRectangleAction = menu.addAction(tr("添加矩形框"));
	QAction* clearRectanglesAction = menu.addAction(tr("清除所有矩形框"));

	// 新增圆弧测量菜单项
	QAction* arcMeasureAction = menu.addAction(
		m_arcMeasureToolEnabled ? tr("禁用圆弧测量") : tr("启用圆弧测量"));
	QAction* addArcMeasureAction = menu.addAction(tr("添加圆弧测量"));
	QAction* clearArcMeasuresAction = menu.addAction(tr("清除所有圆弧测量"));

	QAction* selectedAction = menu.exec(event->globalPos());
	if (!selectedAction)
		return;

	if (selectedAction == resetAction)
	{
		fitImageToWidget(); // 调整到控件大小
	}
	else if (selectedAction == originalAction)
	{
		showOriginalImage(); // 显示原始大小图像
	}
	else if (selectedAction == clearAction)
	{
		clearImage(); // 清除图像
	}
	else if (selectedAction == measureAction)
	{
		enableMeasureTool(!m_measureToolEnabled); // 切换测量工具状态
	}
	else if (selectedAction == clearMeasureAction)
	{
		clearMeasureResults(); // 清除测量结果
	}
	else if (selectedAction == rectangleAction)
	{
		enableRectangleTool(!m_rectangleToolEnabled); // 切换矩形工具状态
	}
	else if (selectedAction == addRectangleAction)
	{
		// 在图像中心添加默认矩形
		if (!m_image.isNull()) {
			addRectangle(m_rectangles.empty() ? 1 : (m_rectangles.back().id + 1), QPointF(m_image.width() / 2.0, m_image.height() / 2.0), 100, 80);
		}
	}
	else if (selectedAction == clearRectanglesAction)
	{
		clearRectangles(); // 清除所有矩形框
	}
	else if (selectedAction == arcMeasureAction)
	{
		enableArcMeasureTool(!m_arcMeasureToolEnabled); // 切换圆弧测量状态
	}
	else if (selectedAction == addArcMeasureAction)
	{
		// 在图像中心添加默认圆弧测量
		if (!m_image.isNull()) {
			addArcMeasure(QPointF(m_image.width() / 2.0, m_image.height() / 2.0), 80);
		}
	}
	else if (selectedAction == clearArcMeasuresAction)
	{
		clearArcMeasures(); // 清除所有圆弧测量
	}
}

// ===================== 窗口大小变化 =====================
void ImageViewWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
	if (m_image.isNull()) return;

	// 仅在首次加载或首次显示时自动居中
	//if (m_scaledPixmap.isNull())
		fitToWidget();
}