#include "MainWindow.h"
#include "FlowEngine.h"
#include "NodeRegistry.h"
#include "IFlowNode.h"
#include "NodeData.h"
#include "Global.h"
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

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

	// 4. 节点执行完成后，把输出图像显示到右侧大界面
	connect(&FlowEngine::instance(), &FlowEngine::nodeFinished, this,
		[this](const QString& id, int, bool ok, qint64) {
			if (ok) displayNodeResult(id);
		});

	// 5. 流程清空/加载后重建流程树
	connect(&FlowEngine::instance(), &FlowEngine::modelCleared, this,
		[this] { rebuildFlowTree(); });

	// 6. 文件菜单：新建 / 打开 / 保存流程
	QMenu* fileMenu = ui->menu;
	QAction* actNew = fileMenu->addAction("新建流程");
	QAction* actOpen = fileMenu->addAction("打开流程...");
	QAction* actSave = fileMenu->addAction("保存流程...");
	fileMenu->addSeparator();
	QAction* actExit = fileMenu->addAction("退出");

	connect(actNew, &QAction::triggered, this, [this] {
		FlowEngine::instance().clear();
		ui->imageViewWidget->clearImage();
	});
	connect(actOpen, &QAction::triggered, this, &MainWindow::loadFlowFromFile);
	connect(actSave, &QAction::triggered, this, &MainWindow::saveFlowToFile);
	connect(actExit, &QAction::triggered, this, &QWidget::close);
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

void MainWindow::rebuildFlowTree()
{
	auto& engine = FlowEngine::instance();
	ui->workFlowTreeWidget->clear();
	for (int i = 0; i < engine.nodeCount(); ++i) {
		const QString id = engine.nodeIdAt(i);
		auto* node = engine.node(id);
		auto* item = new QTreeWidgetItem();
		item->setText(0, node ? node->displayName() : engine.typeKeyAt(i));
		item->setText(1, "等待运行...");
		item->setData(0, Qt::UserRole, id);
		ui->workFlowTreeWidget->addTopLevelItem(item);
	}
}

void MainWindow::saveFlowToFile()
{
	const QString path = QFileDialog::getSaveFileName(this, "保存流程",
		QString::fromStdString(g_pathexe), "流程文件 (*.vpjson)");
	if (path.isEmpty()) return;

	QFile file(path);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this, "保存失败", "无法写入文件：" + path);
		return;
	}
	file.write(QJsonDocument(FlowEngine::instance().serializeFlow()).toJson(QJsonDocument::Indented));
	file.close();
	statusBar()->showMessage("流程已保存：" + path, 3000);
}

void MainWindow::loadFlowFromFile()
{
	const QString path = QFileDialog::getOpenFileName(this, "打开流程",
		QString::fromStdString(g_pathexe), "流程文件 (*.vpjson);;所有文件 (*.*)");
	if (path.isEmpty()) return;

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, "打开失败", "无法读取文件：" + path);
		return;
	}
	QJsonParseError err;
	const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
	file.close();
	if (err.error != QJsonParseError::NoError || !doc.isObject()) {
		QMessageBox::warning(this, "打开失败", "流程文件格式错误：" + err.errorString());
		return;
	}
	if (!FlowEngine::instance().loadFlow(doc.object())) {
		QMessageBox::warning(this, "打开失败", "流程加载失败（可能包含未知算子）。");
		return;
	}
	rebuildFlowTree();
	statusBar()->showMessage("流程已加载：" + path, 3000);
}

void MainWindow::displayNodeResult(const QString& id)
{
	auto* node = FlowEngine::instance().node(id);
	if (!node) return;

	auto out = node->getOutput(0);
	auto img = std::dynamic_pointer_cast<ImageData>(out);
	if (img && !img->image.empty()) {
		ui->imageViewWidget->updatedisplayMat(img->image);
	}
}

