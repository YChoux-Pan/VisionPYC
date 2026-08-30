#pragma once

#include <QObject>
#include <QThread>
#include <QJsonObject>
#include <QVector>
#include <atomic>

#include "FlowModel.h"
#include "FlowWorker.h"

// 流程引擎：线性流程的唯一入口（单例）。
// 职责：
//   1. 节点模型管理（增删改查 / 排序 / 持久化）
//   2. 异步执行调度（QThread + 工作队列）
// GUI 层只与本类交互，不直接持有算法指针。
class FlowEngine : public QObject {
	Q_OBJECT
public:
	static FlowEngine& instance();

	// --- 模型操作（GUI 线程调用；运行中自动拒绝）---
	QString addNode(const QString& typeKey);
	bool removeNode(const QString& id);
	bool moveNode(const QString& id, int newIndex);
	bool syncOrder(const QVector<QString>& orderedIds);
	void clear();

	// --- 查询 ---
	int nodeCount() const;
	QString nodeIdAt(int index) const;
	QString typeKeyAt(int index) const;
	IFlowNode* node(const QString& id) const;

	// --- 执行控制 ---
	void runAsync();          // 异步执行（推荐，不阻塞 UI）
	void stop();              // 请求停止（下一个节点执行前生效）
	bool isRunning() const { return m_running.load(); }

	// --- 持久化 ---
	QJsonObject serializeFlow() const;
	bool loadFlow(const QJsonObject& json);

	// --- 供 FlowWorker 使用 ---
	FlowModel* model() const { return m_model; }
	bool isStopRequested() const { return m_stopRequested.load(); }

signals:
	// 模型变更
	void nodeAdded(const QString& id, int index);
	void nodeRemoved(const QString& id, int index);
	void nodeMoved(const QString& id, int from, int to);
	void modelCleared();
	// 执行状态
	void nodeStarted(const QString& id, int index);
	void nodeFinished(const QString& id, int index, bool ok, qint64 ms);
	void flowFinished(bool ok);
	void runningChanged(bool running);

private:
	FlowEngine();
	~FlowEngine() override;
	FlowEngine(const FlowEngine&) = delete;
	FlowEngine& operator=(const FlowEngine&) = delete;

	void onWorkerFinished(bool ok);

	FlowModel* m_model;
	FlowWorker* m_worker;
	QThread m_thread;
	std::atomic<bool> m_running{ false };
	std::atomic<bool> m_stopRequested{ false };
};
