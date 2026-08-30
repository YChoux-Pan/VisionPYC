#pragma once

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QLabel>
#include <opencv2/opencv.hpp>
#include "ui_PreProcessWidget.h"

class ImageFilterNode;

enum class MainCategory {
	ImageAdjust,   // 图像调整
	Filter,        // 滤波
	Morphology,    // 形态学运算
	Enhance,       // 图像增强
	Binary         // 二值化
};

// 二级子项目枚举
enum class SubCommand {
	ColorToGray, ImageMirror, ImageRotate, DepthToColor, ModifySize,
	MeanFilter, MedianFilter, GaussianFilter,
	Expand, Erosion, Opening, Closed,
	Sharpen, Contrast, Luminance, Inverse, EdgeEnhancement,
	BinaryNormal, MeanBinary, ColorBinary
};

struct MenuCommandData {
	MainCategory mainCat;
	SubCommand subCmd;
};
Q_DECLARE_METATYPE(MenuCommandData)

// 图像预处理配置界面：
//   - 左侧选择算子 + 动态参数面板
//   - 右侧 ImageViewWidget 预览执行结果
//   - "执行"：用当前参数处理输入图像并显示
//   - "确定"：保存参数到节点并关闭
class PreProcessWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PreProcessWidget(QWidget* parent = nullptr);
	~PreProcessWidget();

	void InitDlg();
	void setNode(ImageFilterNode* node);   // 关联所属节点（不拥有）

private:
	void clearSettingArea();
	void updateOperation(MenuCommandData data);
	// 生成当前算子的参数面板（动态控件）
	QWidget* buildParamPanel(const QString& cmd, MenuCommandData data);
	// 界面控件值 -> 节点参数模型
	void applyCurrentParamsToNode();
	// 节点参数模型 -> 界面控件
	void syncParamsFromNodeToUI();

	Ui::PreProcessWidgetClass ui;
	QWidget* m_currentSettingWidget = nullptr;
	QMenu* m_mainMenu = nullptr;
	ImageFilterNode* m_node = nullptr;
	MenuCommandData m_currentCommand;
	bool m_paramSyncing = false;   // 防止同步时信号触发回写

	// 参数控件引用（应用/读取时使用）
	QComboBox* m_cmbGrayMode = nullptr;
	QComboBox* m_cmbFlip = nullptr;
	QComboBox* m_cmbRotate = nullptr;
	QDoubleSpinBox* m_spinScale = nullptr;
	QSpinBox* m_spinWidth = nullptr;
	QSpinBox* m_spinHeight = nullptr;
	QComboBox* m_cmbKernel = nullptr;
	QDoubleSpinBox* m_spinSigma = nullptr;
	QComboBox* m_cmbMorphKernel = nullptr;
	QSpinBox* m_spinIterations = nullptr;
	QSlider* m_sliderAlpha = nullptr;
	QLabel* m_labelAlpha = nullptr;
	QSlider* m_sliderBeta = nullptr;
	QLabel* m_labelBeta = nullptr;
	QSlider* m_sliderThreshold = nullptr;
	QLabel* m_labelThreshold = nullptr;
	QComboBox* m_cmbBinaryType = nullptr;
	QSpinBox* m_spinAdaptKernel = nullptr;
	QSpinBox* m_spinAdaptOffset = nullptr;

	// 将算子枚举转显示名
	static QString commandName(SubCommand cmd);

private slots:
	void onMenuActionTriggered();
	void onToolButtonClicked();
	void on_m_btn_fun_clicked();      // 执行
	void on_m_btn_OK_clicked();       // 确定（保存配置并关闭）
	void on_m_btn_chanel_clicked();   // 取消
};
