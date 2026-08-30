#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include "Global.h"
#include "FlowEngine.h"
#include "NodeRegistry.h"
#include "IFlowNode.h"
#include "NodeData.h"
#include <QEventLoop>
#include <QTimer>
#include <QElapsedTimer>
#include <QJsonArray>
#include <map>

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <QAbstractNativeEventFilter>
#include <QWindow>
// 定义全局系统样式过滤器
class SystemStyleFilter : public QObject {
public:
	bool eventFilter(QObject* obj, QEvent* event) override {
		// 监听窗口显示事件
		if (event->type() == QEvent::Show) {
			QWidget* widget = qobject_cast<QWidget*>(obj);

			// 确保是顶级窗口（如 MainWindow 或 Dialog），排除普通子控件
			if (widget && widget->isWindow()) {
				HWND hwnd = (HWND)widget->winId();
				if (hwnd) {
					// 定义你的墨绿色
					COLORREF moLvColor = RGB(0, 77, 64);
					COLORREF frameColor = RGB(13, 92, 83);

					// 1. 设置边框颜色为墨绿 (DWMWA_BORDER_COLOR = 34)
					DwmSetWindowAttribute(hwnd, 34, &frameColor, sizeof(frameColor));

					// 2. 设置标题栏（顶部状态栏区域）颜色为墨绿 (DWMWA_CAPTION_COLOR = 35)
					// 这会让整个窗口顶部由原来的黑色/白色变为墨绿色
					DwmSetWindowAttribute(hwnd, 35, &moLvColor, sizeof(moLvColor));

					// 3. 设置标题文字颜色 (DWMWA_TEXT_COLOR = 36)
					// 既然背景是墨绿，文字建议设为白色，清晰度更高
					COLORREF textColor = RGB(255, 255, 255);
					DwmSetWindowAttribute(hwnd, 36, &textColor, sizeof(textColor));

					// 4. 保持强制直角 (DWMWA_WINDOW_CORNER_PREFERENCE = 33)
					int cornerPreference = 1;
					DwmSetWindowAttribute(hwnd, 33, &cornerPreference, sizeof(cornerPreference));
				}
			}
		}
		return QObject::eventFilter(obj, event);
	}
};

void loadStyleSheet(const QString& path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly))
    {
        //读取QSS
        QString styleSheet = QLatin1String(file.readAll());
        //应用到程序
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
}

// ==================== 核心引擎自检（--selftest 参数触发） ====================
// 测试节点：无输入，输出一张 16x16 图像
class TestSourceNode : public IFlowNode {
public:
	QString typeKey() const override { return "_TestSource"; }
	QString displayName() const override { return "_TestSource"; }
	QString category() const override { return "_Test"; }
	QVector<FlowPort> inputPorts() const override { return {}; }
	QVector<FlowPort> outputPorts() const override {
		return { { "图像", DataType::Image, PortDirection::Out } };
	}
	bool process() override {
		auto out = std::make_shared<ImageData>();
		out->image = cv::Mat(16, 16, CV_8UC3, cv::Scalar(120, 60, 0));
		m_outputs[0] = std::move(out);
		m_lastResult = true;
		return true;
	}
	void setInput(int, std::shared_ptr<INodeData>) override {}
	std::shared_ptr<INodeData> getOutput(int portIndex) override {
		auto it = m_outputs.find(portIndex);
		return (it != m_outputs.end()) ? it->second : nullptr;
	}
private:
	std::map<int, std::shared_ptr<INodeData>> m_outputs;
};

// 测试节点：接收图像并校验尺寸（验证数据流是否真正串联）
class TestSinkNode : public IFlowNode {
public:
	QString typeKey() const override { return "_TestSink"; }
	QString displayName() const override { return "_TestSink"; }
	QString category() const override { return "_Test"; }
	QVector<FlowPort> inputPorts() const override {
		return { { "图像", DataType::Image, PortDirection::In } };
	}
	QVector<FlowPort> outputPorts() const override { return {}; }
	bool process() override {
		auto src = std::dynamic_pointer_cast<ImageData>(m_inputs[0]);
		m_lastResult = (src && !src->image.empty() && src->image.cols == 16);
		return m_lastResult;
	}
	void setInput(int portIndex, std::shared_ptr<INodeData> data) override {
		m_inputs[portIndex] = std::move(data);
	}
	std::shared_ptr<INodeData> getOutput(int) override { return nullptr; }
private:
	std::map<int, std::shared_ptr<INodeData>> m_inputs;
};

static int runSelfTest()
{
	int failures = 0;
	auto check = [&failures](bool ok, const QString& msg) {
		if (ok) qInfo().noquote() << "[ OK ]" << msg;
		else { qWarning().noquote() << "[FAIL]" << msg; ++failures; }
	};

	// 1. 算子注册表
	const auto metas = NodeRegistry::all();
	check(metas.size() == 5, QString("注册算子数量 = %1（期望 5）").arg(metas.size()));
	for (const auto& m : metas) {
		check(NodeRegistry::create(m.typeKey) != nullptr, "可实例化: " + m.displayName);
	}

	// 2. 注册测试节点
	NodeRegistry::registerNode({ "_TestSource", "_Test", "_TestSource",
		[](const QString&) { return std::make_unique<TestSourceNode>(); } });
	NodeRegistry::registerNode({ "_TestSink", "_Test", "_TestSink",
		[](const QString&) { return std::make_unique<TestSinkNode>(); } });

	auto& engine = FlowEngine::instance();

	// 3. 节点增删改查
	QString srcId = engine.addNode("_TestSource");
	QString sinkId = engine.addNode("_TestSink");
	check(!srcId.isEmpty() && !sinkId.isEmpty(), "addNode 创建两个测试节点");
	check(engine.nodeCount() == 2, QString("节点数量 = %1").arg(engine.nodeCount()));
	check(engine.addNode("_NotExist").isEmpty(), "非法 typeKey 返回空 ID");
	check(engine.removeNode(srcId), "removeNode 删除源节点");
	check(engine.nodeCount() == 1, "删除后节点数量 = 1");

	// 4. 数据流执行：源 -> 汇（核心验证）
	engine.clear();
	srcId = engine.addNode("_TestSource");
	sinkId = engine.addNode("_TestSink");
	check(engine.nodeCount() == 2, "源->汇 节点数量 = 2");

	bool flowOk = false;
	bool gotNodeFinish = false;
	QObject::connect(&engine, &FlowEngine::flowFinished, &engine,
		[&](bool ok) { flowOk = ok; });
	QObject::connect(&engine, &FlowEngine::nodeFinished, &engine,
		[&](const QString&, int, bool ok, qint64) { gotNodeFinish = gotNodeFinish || ok; });

	engine.runAsync();
	QEventLoop loop;
	QObject::connect(&engine, &FlowEngine::flowFinished, &loop, &QEventLoop::quit);
	QTimer::singleShot(5000, &loop, &QEventLoop::quit);
	loop.exec();
	check(flowOk, "源->汇 数据流执行成功");
	check(gotNodeFinish, "收到 nodeFinished 状态信号");

	// 5. 失败路径：采集图像节点（未配置界面）执行失败 -> 流程停止
	engine.clear();
	const QString camId = engine.addNode("采集图像");
	check(!camId.isEmpty(), "添加真实算子: 采集图像");
	bool flowOk2 = true;
	QObject::connect(&engine, &FlowEngine::flowFinished, &engine,
		[&](bool ok) { flowOk2 = ok; });
	engine.runAsync();
	QEventLoop loop2;
	QObject::connect(&engine, &FlowEngine::flowFinished, &loop2, &QEventLoop::quit);
	QTimer::singleShot(5000, &loop2, &QEventLoop::quit);
	loop2.exec();
	check(!flowOk2, "未配置图像时流程正确失败");

	// 6. 序列化 / 反序列化
	engine.clear();
	engine.addNode("图像预处理");
	engine.addNode("高度检测");
	const QJsonObject json = engine.serializeFlow();
	check(json.contains("nodes") && json["nodes"].toArray().size() == 2, "序列化节点数 = 2");
	engine.clear();
	check(engine.nodeCount() == 0, "clear 后节点数 = 0");
	check(engine.loadFlow(json) && engine.nodeCount() == 2, "反序列化恢复节点数 = 2");

	// 7. 异步执行期间拒绝编辑
	bool runningSeen = false;
	QObject::connect(&engine, &FlowEngine::runningChanged, &engine,
		[&](bool r) { runningSeen = runningSeen || r; });
	engine.clear();
	engine.addNode("图像预处理");
	engine.runAsync();
	QEventLoop loop3;
	QObject::connect(&engine, &FlowEngine::flowFinished, &loop3, &QEventLoop::quit);
	QTimer::singleShot(5000, &loop3, &QEventLoop::quit);
	loop3.exec();
	check(runningSeen, "执行期间 runningChanged 信号正确发射");

	engine.clear();
	qInfo().noquote() << QString("=========== 自检完成：失败 %1 项 ===========").arg(failures);
	return failures;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	// 自检模式：验证核心引擎逻辑（注册表/数据流/异步执行/序列化）
	if (QCoreApplication::arguments().contains(QStringLiteral("--selftest"))) {
		const int failures = runSelfTest();
		return (failures == 0) ? 0 : 1;
	}

	// 安装全局过滤器
	SystemStyleFilter filter;
	app.installEventFilter(&filter);

    MainWindow window;

    //获取全局路径
    QString exePath = QCoreApplication::applicationDirPath();
    g_pathexe = exePath.toUtf8().toStdString();

	//加载文字字体
	QString fullStyle;
	// 将所有样式文件路径放在一个列表里

	//需要按照界面控件的最低层到最外层进行qss加载，否则颜色会被覆盖
	//必须要首先加载widget整体背景
	QStringList qssFiles = {
		":/widget.qss",
		":/tabBar.qss",
		":/groupBox.qss",
		":/radiobutton.qss",
		":/pushbutton.qss",
		":/lineEdit.qss",
		":/plainTextEdit.qss",
		":/toolbutton.qss"
	};


	for (const QString& path : qssFiles) {
		QFile file(path);
		if (file.open(QFile::ReadOnly)) {
			fullStyle.append(file.readAll());
			file.close();
		}
		else {
			qDebug() << "Failed to load QSS file:" << path;
		}
	}

	if (!fullStyle.isEmpty()) {
		app.setStyleSheet(fullStyle);
	}


    window.showMaximized();
    window.show();
    return app.exec();
}
