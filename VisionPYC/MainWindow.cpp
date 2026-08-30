#include "MainWindow.h"
#include "FlowEngine.h"
#include "NodeRegistry.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindowClass)
{
	ui->setupUi(this); // 这行代码执行后，ui->graphicsView 已经是 NodeView 实例了

	// 1. 从注册表自动填充左侧算子库（新增算子无需再改此处）
	initOperators();

	// 2. 运行按钮 -> 异步执行整个流程
	connect(ui->m_btn_Open, &QPushButton::clicked, this, [] {
		FlowEngine::instance().runAsync();
	});

	// 3. 运行期间禁用运行按钮
	connect(&FlowEngine::instance(), &FlowEngine::runningChanged, this,
		[this](bool running) {
			ui->m_btn_Open->setEnabled(!running);
		});
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initOperators()
{
	for (const auto& meta : NodeRegistry::all()) {
		ui->nodeSelectorWidget->addOperator(meta.category, meta.displayName, meta.typeKey);
	}
}

