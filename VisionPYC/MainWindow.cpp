#include "MainWindow.h"
#include "CoreManager.h"
#include <QPushButton>

#include "BaseAlgorithmNode.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::MainWindowClass)
{
	ui->setupUi(this); // 这行代码执行后，ui->graphicsView 已经是 NodeView 实例了

	ui->workFlowTreeWidget->setHeaderLabels({ "执行步骤", "状态/耗时" });
	// 图像检测类
	ui->nodeSelectorWidget->addOperator("图像检测", "预处理模块", "图像预处理");
	ui->nodeSelectorWidget->addOperator("图像检测", "区域提取", "ROI设置");

	// --- 2. 注册3D检测大类 ---
	ui->nodeSelectorWidget->addOperator("3D检测", "高度测量", "高度检测");
	ui->nodeSelectorWidget->addOperator("3D检测", "拟合平面", "平面度检测");

	// 4. 连接运行信号
	//connect(ui->btnRun, &QPushButton::clicked, this, &MainWindow::onRunClicked);

	//connect(ui->btnRun, &QPushButton::clicked, this, &MainWindow::onRunClicked);
}

MainWindow::~MainWindow()
{}

void MainWindow::onRunClicked() {
	// 调用 Core 模块执行逻辑
	int count = ui->workFlowTreeWidget->topLevelItemCount();
	if (count == 0) return;

	std::shared_ptr<INodeData> currentData = nullptr;

	for (int i = 0; i < count; ++i) {
		QTreeWidgetItem* item = ui->workFlowTreeWidget->topLevelItem(i);

		// 从 Item 中提取绑定的算子对象指针
		BaseAlgorithmNode* node = static_cast<BaseAlgorithmNode*>(
			item->data(0, Qt::UserRole).value<void*>()
			);

		if (node) {
			// 设置状态为“运行中”
			item->setText(1, "Running...");
			item->setForeground(1, Qt::yellow);

			// 自动传递数据（前一个的输出给后一个的输入）
			if (currentData) node->setInputData(0, currentData);

			node->process();

			if (node->lastResult()) {
				currentData = node->getOutputData(0);
				item->setText(1, QString("OK (%1ms)").arg(node->runTime()));
				item->setForeground(1, Qt::green);
			}
			else {
				item->setText(1, "Failed");
				item->setForeground(1, Qt::red);
				break; // 报错则停止流程
			}
		}
	}
}
