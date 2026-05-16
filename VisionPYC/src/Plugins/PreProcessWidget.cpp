#include "PreProcessWidget.h"
#include <QMenu>
PreProcessWidget::PreProcessWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	

	InitDlg();
}

PreProcessWidget::~PreProcessWidget()
{
	clearSettingArea();
}

void PreProcessWidget::InitDlg()
{
	ui.listView->updateHeader(1,"类型");
	ui.listView->updateHeader(2,"参数");

	//注册信号
	
	//当前窗口生态样式设置
	this->setStyleSheet("QMenu { background-color: #333333; color: white; }");
	//算子管理
	m_mainMenu = new QMenu(this);	
	// 辅助 Lambda 函数：用来快速设置 Action 的自定义数据并连接槽函数
	auto registerAction = [this](QAction* action, MainCategory cat, SubCommand sub) {
		MenuCommandData cmdData{ cat, sub };
		// 将结构体打包进 QVariant 存入 QAction
		action->setData(QVariant::fromValue(cmdData));
		// 统一连接到同一个槽函数
		connect(action, &QAction::triggered, this, &PreProcessWidget::onMenuActionTriggered);
		};

	// =========================================================================
	// 1. 图像调整
	// =========================================================================
	QMenu* menuImageAdjust = new QMenu("图像调整", this);
	registerAction(menuImageAdjust->addAction("灰度处理"), MainCategory::ImageAdjust, SubCommand::ColorToGray);
	registerAction(menuImageAdjust->addAction("图像镜像"), MainCategory::ImageAdjust, SubCommand::ImageMirror);
	registerAction(menuImageAdjust->addAction("图像旋转"), MainCategory::ImageAdjust, SubCommand::ImageRotate);
	registerAction(menuImageAdjust->addAction("深度转彩色"), MainCategory::ImageAdjust, SubCommand::DepthToColor);
	registerAction(menuImageAdjust->addAction("修改尺寸"), MainCategory::ImageAdjust, SubCommand::ModifySize);
	m_mainMenu->addMenu(menuImageAdjust);

	// =========================================================================
	// 2. 滤波
	// =========================================================================
	QMenu* menuFilter = new QMenu("滤波", this);
	registerAction(menuFilter->addAction("均值滤波"), MainCategory::Filter, SubCommand::MeanFilter);
	registerAction(menuFilter->addAction("中值滤波"), MainCategory::Filter, SubCommand::MedianFilter);
	registerAction(menuFilter->addAction("高斯滤波"), MainCategory::Filter, SubCommand::GaussianFilter);
	m_mainMenu->addMenu(menuFilter);

	// =========================================================================
	// 3. 形态学运算
	// =========================================================================
	QMenu* menuMorphology = new QMenu("形态学运算", this);
	registerAction(menuMorphology->addAction("灰度膨胀"), MainCategory::Morphology, SubCommand::Expand);
	registerAction(menuMorphology->addAction("灰度腐蚀"), MainCategory::Morphology, SubCommand::Erosion);
	registerAction(menuMorphology->addAction("灰度开运算"), MainCategory::Morphology, SubCommand::Opening);
	registerAction(menuMorphology->addAction("灰度闭运算"), MainCategory::Morphology, SubCommand::Closed);
	m_mainMenu->addMenu(menuMorphology);

	// =========================================================================
	// 4. 图像增强
	// =========================================================================
	QMenu* menuEnhance = new QMenu("图像增强", this);
	registerAction(menuEnhance->addAction("锐化"), MainCategory::Enhance, SubCommand::Sharpen);
	registerAction(menuEnhance->addAction("对比度"), MainCategory::Enhance, SubCommand::Contrast);
	registerAction(menuEnhance->addAction("亮度调节"), MainCategory::Enhance, SubCommand::Luminance);
	registerAction(menuEnhance->addAction("反色"), MainCategory::Enhance, SubCommand::Inverse);
	registerAction(menuEnhance->addAction("边缘增强"), MainCategory::Enhance, SubCommand::EdgeEnhancement);
	m_mainMenu->addMenu(menuEnhance);

	// =========================================================================
	// 5. 二值化
	// =========================================================================
	QMenu* menubinary = new QMenu("二值化", this);
	registerAction(menubinary->addAction("二值化"), MainCategory::Binary, SubCommand::BinaryNormal);
	registerAction(menubinary->addAction("均值二值化"), MainCategory::Binary, SubCommand::MeanBinary);
	registerAction(menubinary->addAction("彩色二值化"), MainCategory::Binary, SubCommand::ColorBinary);
	m_mainMenu->addMenu(menubinary);


	
	// 增加算子信号槽
	connect(ui.m_toolbtn_add, &QToolButton::clicked, this, &PreProcessWidget::onToolButtonClicked);

	

}

void PreProcessWidget::clearSettingArea()
{
	if (m_currentSettingWidget) {
		delete m_currentSettingWidget;
		m_currentSettingWidget = nullptr;
	}

	if (m_uiAdjust) { delete m_uiAdjust;     m_uiAdjust = nullptr; }

	//if (m_uiFilter) { delete m_uiFilter;     m_uiFilter = nullptr; }
	//if (m_uiMorphology) { delete m_uiMorphology; m_uiMorphology = nullptr; }
}

void PreProcessWidget::updateOperation(MenuCommandData m_Data)
{	
	clearSettingArea();

	if (ui.m_wid_setting->layout()) {
		delete ui.m_wid_setting->layout();
	}

	m_currentSettingWidget = new QWidget(this);
	
	switch (m_Data.subCmd)
	{		
	case SubCommand::ColorToGray:
		m_uiAdjust = new Ui::ImageAdjust;
		m_uiAdjust->setupUi(m_currentSettingWidget);
		//ui.m_wid_setting = m_currentSettingWidget;
		break;
	}


	QVBoxLayout* pVLayout = new QVBoxLayout(ui.m_wid_setting);

	// 消除布局的内边距（Margins），让你的小 UI 能够 100% 完美铺满整个右侧区域，不留白边
	pVLayout->setContentsMargins(0, 0, 0, 0);
	pVLayout->setSpacing(0); // 控件间的间距设为 0

	// 将你的小 UI 容器塞入布局
	pVLayout->addWidget(m_currentSettingWidget);

}

void PreProcessWidget::onToolButtonClicked()
{
	if (!m_mainMenu) return;

	// 2. 计算按钮右下角在屏幕上的绝对坐标
	// QPoint(ui->toolButton->width(), ui->toolButton->height()) 代表按钮的右下角顶点
	QPoint showPos = ui.m_toolbtn_add->mapToGlobal(QPoint(ui.m_toolbtn_add->width(), ui.m_toolbtn_add->height()));

	// 3. 在该坐标弹出菜单
	// 推荐使用 exec()，它是阻塞/模态形式的，用户点击菜单外任意地方会自动消失，非常符合标准菜单行为
	m_mainMenu->exec(showPos);
}

void PreProcessWidget::onMenuActionTriggered()
{
	QAction* clickedAction = qobject_cast<QAction*>(sender());
	if (!clickedAction) return;

	// 提取保存在 Action 中的结构体数据
	QVariant varData = clickedAction->data();
	if (!varData.canConvert<MenuCommandData>()) return;

	MenuCommandData cmdData = varData.value<MenuCommandData>();
	if (!varData.canConvert<MenuCommandData>()) {
		// 如果断点依然进不去，你可以在这里打个断点，看看程序是不是死在这一步了！
		return;
	}
	updateOperation(cmdData);
}


void PreProcessWidget::on_m_btn_fun_clicked()
{
	



}

