#include "MainWindow.h"
#include "CoreManager.h"
#include <QPushButton>
#include <TESTWidget.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindowClass)
{
	ui->setupUi(this); // 这行代码执行后，ui->graphicsView 已经是 NodeView 实例了

	// 1. 初始化场景
	m_scene = new NodeScene(this);

	// 2. 将场景绑定到提升后的 View 中
	ui->graphicsView->setScene(m_scene);

	// 3. 填充算子库数据 (也可以在 NodeSelectorWidget 内部实现)
	ui->nodeSelectorWidget->addOperator("图像滤波", "高斯模糊", "GaussianBlur");
	ui->nodeSelectorWidget->addOperator("图像滤波", "均值滤波", "GaussianBlur");
	TESTWidget* m_TESTWidget = new TESTWidget();
	ui->nodeSelectorWidget->addCategoryWidget("测试1", m_TESTWidget);

	// 4. 连接运行信号
	//connect(ui->btnRun, &QPushButton::clicked, this, &MainWindow::onRunClicked);
}

MainWindow::~MainWindow()
{}

void MainWindow::onRunClicked() {
	// 调用 Core 模块执行逻辑
	CoreManager::instance().runOnce();
}
