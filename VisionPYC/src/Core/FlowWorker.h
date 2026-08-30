#pragma once

#include <QObject>
#include <QVector>
#include <memory>

class FlowEngine;
class INodeData;

// 工作线程执行器：在独立 QThread 中按线性顺序执行整个流程。
// 通过信号将节点运行状态回传给 GUI 线程。
class FlowWorker : public QObject {
	Q_OBJECT
public:
	explicit FlowWorker(FlowEngine* engine, QObject* parent = nullptr);

public slots:
	// 阻塞式执行整个流程（在 worker 线程中调用），结果通过信号反馈
	void runFlow();

signals:
	void nodeStarted(const QString& id, int index);
	void nodeFinished(const QString& id, int index, bool ok, qint64 ms);
	void flowFinished(bool ok);

private:
	FlowEngine* m_engine;
};
