#include "FlowEngine.h"
#include "IFlowNode.h"
#include <QMetaObject>
#include <QDebug>

FlowEngine& FlowEngine::instance()
{
	static FlowEngine inst;
	return inst;
}

FlowEngine::FlowEngine()
	: QObject(nullptr)
{
	m_model = new FlowModel(this);

	// 工作线程 + 工作队列：worker 移入子线程，通过队列连接调度
	m_worker = new FlowWorker(this, nullptr);
	m_worker->moveToThread(&m_thread);

	// 模型信号转发（GUI 线程内）
	connect(m_model, &FlowModel::nodeAdded, this, &FlowEngine::nodeAdded);
	connect(m_model, &FlowModel::nodeRemoved, this, &FlowEngine::nodeRemoved);
	connect(m_model, &FlowModel::nodeMoved, this, &FlowEngine::nodeMoved);
	connect(m_model, &FlowModel::modelCleared, this, &FlowEngine::modelCleared);

	// worker 信号回传 GUI 线程（queued connection 自动跨线程）
	connect(m_worker, &FlowWorker::flowFinished, this, &FlowEngine::onWorkerFinished,
		Qt::QueuedConnection);
	connect(m_worker, &FlowWorker::nodeStarted, this, &FlowEngine::nodeStarted,
		Qt::QueuedConnection);
	connect(m_worker, &FlowWorker::nodeFinished, this, &FlowEngine::nodeFinished,
		Qt::QueuedConnection);

	// 线程结束自动回收 worker
	connect(&m_thread, &QThread::finished, m_worker, &QObject::deleteLater);

	m_thread.start();
}

FlowEngine::~FlowEngine()
{
	m_stopRequested.store(true);
	if (m_thread.isRunning()) {
		m_thread.quit();
		if (!m_thread.wait(5000))
			qWarning() << "FlowEngine: 工作线程未能在 5 秒内停止";
	}
}

// --- 模型操作 ---
QString FlowEngine::addNode(const QString& typeKey)
{
	if (m_running.load()) return {};
	return m_model->addNode(typeKey);
}

bool FlowEngine::removeNode(const QString& id)
{
	if (m_running.load()) return false;
	return m_model->removeNode(id);
}

bool FlowEngine::moveNode(const QString& id, int newIndex)
{
	if (m_running.load()) return false;
	return m_model->moveNode(id, newIndex);
}

bool FlowEngine::syncOrder(const QVector<QString>& orderedIds)
{
	if (m_running.load()) return false;
	return m_model->syncOrder(orderedIds);
}

void FlowEngine::clear()
{
	if (m_running.load()) return;
	m_model->clear();
}

int FlowEngine::nodeCount() const
{
	return m_model->nodeCount();
}

QString FlowEngine::nodeIdAt(int index) const
{
	return m_model->nodeIdAt(index);
}

QString FlowEngine::typeKeyAt(int index) const
{
	return m_model->typeKeyAt(index);
}

IFlowNode* FlowEngine::node(const QString& id) const
{
	return m_model->node(id);
}

// --- 执行控制 ---
void FlowEngine::runAsync()
{
	bool expected = false;
	if (!m_running.compare_exchange_strong(expected, true))
		return;   // 已有流程在运行

	m_stopRequested.store(false);
	emit runningChanged(true);
	// 将执行任务投递到工作线程队列
	QMetaObject::invokeMethod(m_worker, "runFlow", Qt::QueuedConnection);
}

void FlowEngine::stop()
{
	m_stopRequested.store(true);
}

void FlowEngine::onWorkerFinished(bool ok)
{
	m_running.store(false);
	emit runningChanged(false);
	emit flowFinished(ok);
}

// --- 持久化 ---
QJsonObject FlowEngine::serializeFlow() const
{
	return m_model->serialize();
}

bool FlowEngine::loadFlow(const QJsonObject& json)
{
	if (m_running.load()) return false;
	return m_model->deserialize(json);
}
