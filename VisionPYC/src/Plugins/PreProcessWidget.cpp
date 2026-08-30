#include "PreProcessWidget.h"
#include "ImageFilterNode.h"
#include "PreprocessCore.h"
#include <QMenu>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QDebug>

PreProcessWidget::PreProcessWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	InitDlg();
}

PreProcessWidget::~PreProcessWidget()
{
	clearSettingArea();
}

void PreProcessWidget::setNode(ImageFilterNode* node)
{
	m_node = node;
	// 若节点已有配置，同步到界面
	if (m_node) syncParamsFromNodeToUI();
}

QString PreProcessWidget::commandName(SubCommand cmd)
{
	switch (cmd) {
	case SubCommand::ColorToGray:      return "灰度处理";
	case SubCommand::ImageMirror:      return "图像镜像";
	case SubCommand::ImageRotate:      return "图像旋转";
	case SubCommand::DepthToColor:     return "深度转彩色";
	case SubCommand::ModifySize:       return "修改尺寸";
	case SubCommand::MeanFilter:       return "均值滤波";
	case SubCommand::MedianFilter:     return "中值滤波";
	case SubCommand::GaussianFilter:   return "高斯滤波";
	case SubCommand::Expand:           return "灰度膨胀";
	case SubCommand::Erosion:          return "灰度腐蚀";
	case SubCommand::Opening:          return "灰度开运算";
	case SubCommand::Closed:           return "灰度闭运算";
	case SubCommand::Sharpen:          return "锐化";
	case SubCommand::Contrast:         return "对比度";
	case SubCommand::Luminance:        return "亮度调节";
	case SubCommand::Inverse:          return "反色";
	case SubCommand::EdgeEnhancement:  return "边缘增强";
	case SubCommand::BinaryNormal:     return "二值化";
	case SubCommand::MeanBinary:       return "均值二值化";
	case SubCommand::ColorBinary:      return "彩色二值化";
	default:                           return "灰度处理";
	}
}

void PreProcessWidget::InitDlg()
{
	ui.listView->updateHeader(1, "类型");
	ui.listView->updateHeader(2, "参数");

	this->setStyleSheet("QMenu { background-color: #333333; color: white; }");

	m_mainMenu = new QMenu(this);
	auto registerAction = [this](QAction* action, MainCategory cat, SubCommand sub) {
		MenuCommandData cmdData{ cat, sub };
		action->setData(QVariant::fromValue(cmdData));
		connect(action, &QAction::triggered, this, &PreProcessWidget::onMenuActionTriggered);
	};

	// 1. 图像调整
	QMenu* menuImageAdjust = new QMenu("图像调整", this);
	registerAction(menuImageAdjust->addAction("灰度处理"), MainCategory::ImageAdjust, SubCommand::ColorToGray);
	registerAction(menuImageAdjust->addAction("图像镜像"), MainCategory::ImageAdjust, SubCommand::ImageMirror);
	registerAction(menuImageAdjust->addAction("图像旋转"), MainCategory::ImageAdjust, SubCommand::ImageRotate);
	registerAction(menuImageAdjust->addAction("深度转彩色"), MainCategory::ImageAdjust, SubCommand::DepthToColor);
	registerAction(menuImageAdjust->addAction("修改尺寸"), MainCategory::ImageAdjust, SubCommand::ModifySize);
	m_mainMenu->addMenu(menuImageAdjust);

	// 2. 滤波
	QMenu* menuFilter = new QMenu("滤波", this);
	registerAction(menuFilter->addAction("均值滤波"), MainCategory::Filter, SubCommand::MeanFilter);
	registerAction(menuFilter->addAction("中值滤波"), MainCategory::Filter, SubCommand::MedianFilter);
	registerAction(menuFilter->addAction("高斯滤波"), MainCategory::Filter, SubCommand::GaussianFilter);
	m_mainMenu->addMenu(menuFilter);

	// 3. 形态学运算
	QMenu* menuMorphology = new QMenu("形态学运算", this);
	registerAction(menuMorphology->addAction("灰度膨胀"), MainCategory::Morphology, SubCommand::Expand);
	registerAction(menuMorphology->addAction("灰度腐蚀"), MainCategory::Morphology, SubCommand::Erosion);
	registerAction(menuMorphology->addAction("灰度开运算"), MainCategory::Morphology, SubCommand::Opening);
	registerAction(menuMorphology->addAction("灰度闭运算"), MainCategory::Morphology, SubCommand::Closed);
	m_mainMenu->addMenu(menuMorphology);

	// 4. 图像增强
	QMenu* menuEnhance = new QMenu("图像增强", this);
	registerAction(menuEnhance->addAction("锐化"), MainCategory::Enhance, SubCommand::Sharpen);
	registerAction(menuEnhance->addAction("对比度"), MainCategory::Enhance, SubCommand::Contrast);
	registerAction(menuEnhance->addAction("亮度调节"), MainCategory::Enhance, SubCommand::Luminance);
	registerAction(menuEnhance->addAction("反色"), MainCategory::Enhance, SubCommand::Inverse);
	registerAction(menuEnhance->addAction("边缘增强"), MainCategory::Enhance, SubCommand::EdgeEnhancement);
	m_mainMenu->addMenu(menuEnhance);

	// 5. 二值化
	QMenu* menubinary = new QMenu("二值化", this);
	registerAction(menubinary->addAction("二值化"), MainCategory::Binary, SubCommand::BinaryNormal);
	registerAction(menubinary->addAction("均值二值化"), MainCategory::Binary, SubCommand::MeanBinary);
	registerAction(menubinary->addAction("彩色二值化"), MainCategory::Binary, SubCommand::ColorBinary);
	m_mainMenu->addMenu(menubinary);

	connect(ui.m_toolbtn_add, &QToolButton::clicked, this, &PreProcessWidget::onToolButtonClicked);
	connect(ui.m_btn_fun, &QPushButton::clicked, this, &PreProcessWidget::on_m_btn_fun_clicked);
	connect(ui.m_btn_OK, &QPushButton::clicked, this, &PreProcessWidget::on_m_btn_OK_clicked);
	connect(ui.m_btn_chanel, &QPushButton::clicked, this, &PreProcessWidget::on_m_btn_chanel_clicked);

	// 默认选中灰度处理
	MenuCommandData def{ MainCategory::ImageAdjust, SubCommand::ColorToGray };
	updateOperation(def);
}

void PreProcessWidget::clearSettingArea()
{
	m_cmbGrayMode = nullptr;
	m_cmbFlip = nullptr;
	m_cmbRotate = nullptr;
	m_spinScale = nullptr;
	m_spinWidth = nullptr;
	m_spinHeight = nullptr;
	m_cmbKernel = nullptr;
	m_spinSigma = nullptr;
	m_cmbMorphKernel = nullptr;
	m_spinIterations = nullptr;
	m_sliderAlpha = nullptr;
	m_labelAlpha = nullptr;
	m_sliderBeta = nullptr;
	m_labelBeta = nullptr;
	m_sliderThreshold = nullptr;
	m_labelThreshold = nullptr;
	m_cmbBinaryType = nullptr;
	m_spinAdaptKernel = nullptr;
	m_spinAdaptOffset = nullptr;

	if (m_currentSettingWidget) {
		delete m_currentSettingWidget;
		m_currentSettingWidget = nullptr;
	}
}

void PreProcessWidget::updateOperation(MenuCommandData data)
{
	m_currentCommand = data;

	// 切换算子前，先把当前界面参数保存到节点
	if (m_node) applyCurrentParamsToNode();

	clearSettingArea();

	if (ui.m_wid_setting->layout()) {
		delete ui.m_wid_setting->layout();
	}

	QVBoxLayout* pVLayout = new QVBoxLayout(ui.m_wid_setting);
	pVLayout->setContentsMargins(0, 0, 0, 0);
	pVLayout->setSpacing(0);

	m_currentSettingWidget = buildParamPanel(commandName(data.subCmd), data);
	if (m_currentSettingWidget)
		pVLayout->addWidget(m_currentSettingWidget);

	// 节点参数 -> 界面
	if (m_node) syncParamsFromNodeToUI();
}
// 根据算子动态生成参数面板
QWidget* PreProcessWidget::buildParamPanel(const QString& cmd, MenuCommandData data)
{
	Q_UNUSED(data);
	auto* panel = new QWidget(this);
	auto* form = new QFormLayout(panel);
	form->setContentsMargins(8, 8, 8, 8);
	form->setSpacing(6);

	if (cmd == "灰度处理") {
		m_cmbGrayMode = new QComboBox(panel);
		m_cmbGrayMode->addItems({ "灰度（单通道）", "保留三通道" });
		form->addRow("转换模式:", m_cmbGrayMode);
	}
	else if (cmd == "图像镜像") {
		m_cmbFlip = new QComboBox(panel);
		m_cmbFlip->addItems({ "水平翻转", "垂直翻转", "双向翻转" });
		form->addRow("翻转方向:", m_cmbFlip);
	}
	else if (cmd == "图像旋转") {
		m_cmbRotate = new QComboBox(panel);
		m_cmbRotate->addItems({ "顺时针 90°", "180°", "逆时针 90°" });
		form->addRow("旋转角度:", m_cmbRotate);
	}
	else if (cmd == "深度转彩色") {
		auto* lbl = new QLabel("使用 JET 彩色映射增强深度信息", panel);
		lbl->setWordWrap(true);
		form->addRow(lbl);
	}
	else if (cmd == "修改尺寸") {
		m_spinScale = new QDoubleSpinBox(panel);
		m_spinScale->setRange(0.05, 10.0);
		m_spinScale->setSingleStep(0.05);
		m_spinScale->setValue(1.0);
		m_spinScale->setDecimals(2);
		form->addRow("缩放比例:", m_spinScale);

		m_spinWidth = new QSpinBox(panel);
		m_spinWidth->setRange(0, 100000);
		m_spinWidth->setValue(0);
		form->addRow("宽度(0=按比例):", m_spinWidth);

		m_spinHeight = new QSpinBox(panel);
		m_spinHeight->setRange(0, 100000);
		m_spinHeight->setValue(0);
		form->addRow("高度(0=按比例):", m_spinHeight);
	}
	else if (cmd == "均值滤波" || cmd == "中值滤波" || cmd == "高斯滤波") {
		m_cmbKernel = new QComboBox(panel);
		m_cmbKernel->addItems({ "3×3", "5×5", "7×7" });
		m_cmbKernel->setCurrentIndex(0);
		form->addRow("核尺寸:", m_cmbKernel);

		if (cmd == "高斯滤波") {
			m_spinSigma = new QDoubleSpinBox(panel);
			m_spinSigma->setRange(0.1, 10.0);
			m_spinSigma->setSingleStep(0.1);
			m_spinSigma->setValue(1.0);
			form->addRow("σ:", m_spinSigma);
		}
	}
	else if (cmd == "灰度膨胀" || cmd == "灰度腐蚀" || cmd == "灰度开运算" || cmd == "灰度闭运算") {
		m_cmbMorphKernel = new QComboBox(panel);
		m_cmbMorphKernel->addItems({ "3×3", "5×5", "7×7" });
		m_cmbMorphKernel->setCurrentIndex(0);
		form->addRow("核尺寸:", m_cmbMorphKernel);

		m_spinIterations = new QSpinBox(panel);
		m_spinIterations->setRange(1, 10);
		m_spinIterations->setValue(1);
		form->addRow("迭代次数:", m_spinIterations);
	}
	else if (cmd == "锐化" || cmd == "反色") {
		auto* lbl = new QLabel("使用默认参数执行", panel);
		form->addRow(lbl);
	}
	else if (cmd == "对比度") {
		m_sliderAlpha = new QSlider(Qt::Horizontal, panel);
		m_sliderAlpha->setRange(0, 300);
		m_sliderAlpha->setValue(120);
		m_sliderAlpha->setTickPosition(QSlider::TicksBelow);
		form->addRow("对比度(×):", m_sliderAlpha);
		m_labelAlpha = new QLabel("1.20", panel);
		form->addRow("数值:", m_labelAlpha);

		m_sliderBeta = new QSlider(Qt::Horizontal, panel);
		m_sliderBeta->setRange(-100, 100);
		m_sliderBeta->setValue(0);
		m_sliderBeta->setTickPosition(QSlider::TicksBelow);
		form->addRow("亮度:", m_sliderBeta);
		m_labelBeta = new QLabel("0", panel);
		form->addRow("数值:", m_labelBeta);

		connect(m_sliderAlpha, &QSlider::valueChanged, this, [this](int v) {
			if (m_labelAlpha) m_labelAlpha->setText(QString::number(v / 100.0, 'f', 2));
		});
		connect(m_sliderBeta, &QSlider::valueChanged, this, [this](int v) {
			if (m_labelBeta) m_labelBeta->setText(QString::number(v));
		});
	}
	else if (cmd == "亮度调节") {
		m_sliderBeta = new QSlider(Qt::Horizontal, panel);
		m_sliderBeta->setRange(-100, 100);
		m_sliderBeta->setValue(0);
		m_sliderBeta->setTickPosition(QSlider::TicksBelow);
		form->addRow("亮度增量:", m_sliderBeta);
		m_labelBeta = new QLabel("0", panel);
		form->addRow("数值:", m_labelBeta);

		connect(m_sliderBeta, &QSlider::valueChanged, this, [this](int v) {
			if (m_labelBeta) m_labelBeta->setText(QString::number(v));
		});
	}
	else if (cmd == "边缘增强") {
		m_cmbKernel = new QComboBox(panel);
		m_cmbKernel->addItems({ "3×3", "5×5" });
		m_cmbKernel->setCurrentIndex(0);
		form->addRow("Laplacian 核:", m_cmbKernel);
	}
	else if (cmd == "二值化" || cmd == "彩色二值化") {
		m_sliderThreshold = new QSlider(Qt::Horizontal, panel);
		m_sliderThreshold->setRange(0, 255);
		m_sliderThreshold->setValue(128);
		m_sliderThreshold->setTickPosition(QSlider::TicksBelow);
		form->addRow("阈值:", m_sliderThreshold);
		m_labelThreshold = new QLabel("128", panel);
		form->addRow("数值:", m_labelThreshold);

		m_cmbBinaryType = new QComboBox(panel);
		m_cmbBinaryType->addItems({ "THRESH_BINARY", "THRESH_BINARY_INV" });
		form->addRow("类型:", m_cmbBinaryType);

		connect(m_sliderThreshold, &QSlider::valueChanged, this, [this](int v) {
			if (m_labelThreshold) m_labelThreshold->setText(QString::number(v));
		});
	}
	else if (cmd == "均值二值化") {
		m_spinAdaptKernel = new QSpinBox(panel);
		m_spinAdaptKernel->setRange(3, 99);
		m_spinAdaptKernel->setSingleStep(2);
		m_spinAdaptKernel->setValue(11);
		form->addRow("核尺寸(奇数):", m_spinAdaptKernel);

		m_spinAdaptOffset = new QSpinBox(panel);
		m_spinAdaptOffset->setRange(0, 50);
		m_spinAdaptOffset->setValue(5);
		form->addRow("常量C:", m_spinAdaptOffset);
	}

	form->addItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
	return panel;
}

// 界面控件值 -> 节点参数模型
void PreProcessWidget::applyCurrentParamsToNode()
{
	if (!m_node) return;

	PreprocessParams p = m_node->paramsSnapshot();
	p.command = commandName(m_currentCommand.subCmd);

	if (m_cmbGrayMode)      p.grayMode = m_cmbGrayMode->currentIndex();
	if (m_cmbFlip)          p.flipCode = (m_cmbFlip->currentIndex() == 0) ? 1 : (m_cmbFlip->currentIndex() == 1) ? 0 : -1;
	if (m_cmbRotate)        p.rotateCode = m_cmbRotate->currentIndex();
	if (m_spinScale)        p.scale = m_spinScale->value();
	if (m_spinWidth)        p.width = m_spinWidth->value();
	if (m_spinHeight)       p.height = m_spinHeight->value();
	if (m_cmbKernel)        p.kernelSize = (m_cmbKernel->currentIndex() + 1) * 2 + 1;
	if (m_spinSigma)        p.sigma = m_spinSigma->value();
	if (m_cmbMorphKernel)   p.morphKernel = (m_cmbMorphKernel->currentIndex() + 1) * 2 + 1;
	if (m_spinIterations)   p.morphIterations = m_spinIterations->value();
	if (m_sliderAlpha)      p.alpha = m_sliderAlpha->value() / 100.0;
	if (m_sliderBeta)       p.beta = m_sliderBeta->value();
	if (m_sliderThreshold)  p.threshold = m_sliderThreshold->value();
	if (m_cmbBinaryType)    p.binaryType = m_cmbBinaryType->currentIndex();
	if (m_spinAdaptKernel)  p.adaptiveKernel = m_spinAdaptKernel->value();
	if (m_spinAdaptOffset)  p.adaptiveOffset = m_spinAdaptOffset->value();

	m_node->setParams(p);
}

// 节点参数模型 -> 界面控件
void PreProcessWidget::syncParamsFromNodeToUI()
{
	if (!m_node) return;
	m_paramSyncing = true;

	const PreprocessParams p = m_node->paramsSnapshot();
	if (m_cmbGrayMode)     m_cmbGrayMode->setCurrentIndex(qBound(0, p.grayMode, 1));
	if (m_cmbFlip) {
		const int idx = (p.flipCode == -1) ? 2 : (p.flipCode == 0) ? 1 : 0;
		m_cmbFlip->setCurrentIndex(idx);
	}
	if (m_cmbRotate)       m_cmbRotate->setCurrentIndex(qBound(0, p.rotateCode, 2));
	if (m_spinScale)       m_spinScale->setValue(p.scale);
	if (m_spinWidth)       m_spinWidth->setValue(p.width);
	if (m_spinHeight)      m_spinHeight->setValue(p.height);
	if (m_cmbKernel)       m_cmbKernel->setCurrentIndex(qBound(0, (p.kernelSize - 1) / 2 - 1, m_cmbKernel->count() - 1));
	if (m_spinSigma)       m_spinSigma->setValue(p.sigma);
	if (m_cmbMorphKernel)  m_cmbMorphKernel->setCurrentIndex(qBound(0, (p.morphKernel - 1) / 2 - 1, m_cmbMorphKernel->count() - 1));
	if (m_spinIterations)  m_spinIterations->setValue(p.morphIterations);
	if (m_sliderAlpha)     m_sliderAlpha->setValue(qBound(0, static_cast<int>(p.alpha * 100), 300));
	if (m_sliderBeta)      m_sliderBeta->setValue(qBound(-100, static_cast<int>(p.beta), 100));
	if (m_sliderThreshold) m_sliderThreshold->setValue(qBound(0, p.threshold, 255));
	if (m_cmbBinaryType)   m_cmbBinaryType->setCurrentIndex(qBound(0, p.binaryType, 1));
	if (m_spinAdaptKernel) m_spinAdaptKernel->setValue(qBound(3, p.adaptiveKernel | 1, 99));
	if (m_spinAdaptOffset) m_spinAdaptOffset->setValue(p.adaptiveOffset);

	m_paramSyncing = false;
}

void PreProcessWidget::onToolButtonClicked()
{
	if (!m_mainMenu) return;
	QPoint showPos = ui.m_toolbtn_add->mapToGlobal(QPoint(ui.m_toolbtn_add->width(), ui.m_toolbtn_add->height()));
	m_mainMenu->exec(showPos);
}

void PreProcessWidget::onMenuActionTriggered()
{
	QAction* clickedAction = qobject_cast<QAction*>(sender());
	if (!clickedAction) return;

	QVariant varData = clickedAction->data();
	if (!varData.canConvert<MenuCommandData>()) return;
	updateOperation(varData.value<MenuCommandData>());
}

// 执行：用当前参数处理输入图像并显示在右侧
void PreProcessWidget::on_m_btn_fun_clicked()
{
	if (!m_node) {
		QMessageBox::warning(this, "提示", "节点未关联，无法预览。请先运行一次流程。");
		return;
	}
	// 1. 先把界面参数保存到节点
	applyCurrentParamsToNode();

	// 2. 获取输入图像（流程运行时的输入缓存）
	const cv::Mat input = m_node->previewInput();
	if (input.empty()) {
		QMessageBox::warning(this, "提示", "暂无输入图像。\n请先在流程中运行一次（采集图像 → 本节点），或点击主窗口【开始流程】。");
		return;
	}

	// 3. 执行算法
	const PreprocessParams params = m_node->paramsSnapshot();
	cv::Mat dst;
	QElapsedTimer timer;
	timer.start();
	if (!applyPreprocess(input, params, dst)) {
		QMessageBox::warning(this, "提示", "算法执行失败。");
		return;
	}
	const double ms = timer.elapsed();

	// 4. 显示结果到右侧图像区
	ui.widget_3->updatedisplayMat(dst);

	// 5. 刷新状态
	ui.m_label_timer->setText(QString("执行成功：%1，耗时 %2 ms").arg(params.command).arg(ms, 0, 'f', 1));
}

// 确定：保存配置并关闭
void PreProcessWidget::on_m_btn_OK_clicked()
{
	applyCurrentParamsToNode();
	close();
}

// 取消
void PreProcessWidget::on_m_btn_chanel_clicked()
{
	close();
}

