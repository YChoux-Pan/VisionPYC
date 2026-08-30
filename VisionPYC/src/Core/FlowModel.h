#pragma once

#include <QMutex>
#include <QObject>
#include <QJsonObject>
#include <QVector>
#include <memory>
#include <vector>
#include <QString>

class IFlowNode;

// 线性流程中的一个节点实例
class FlowNodeItem {
public:
	QString id;                          // 实例ID（UUID 字符串）
	QString typeKey;                     // 算子类型键
	std::unique_ptr<IFlowNode> impl;     // 算法实例（唯一所有者）
	bool enabled = true;
};

// 线性流程模型：负责节点增删改查、排序、序列化。
// 线程安全：数据操作在内部 QMutex 保护下进行；信号在锁外发射。
class FlowModel : public QObject {
	Q_OBJECT
public:
	explicit FlowModel(QObject* parent = nullptr);

	// --- 节点操作（GUI 线程）---
	QString addNode(const QString& typeKey);   // 追加到末尾，返回实例ID（空=失败）
	bool removeNode(const QString& id);
	bool moveNode(const QString& id, int newIndex);
	bool syncOrder(const QVector<QString>& orderedIds);  // 按 UI 拖拽结果整体重排
	void clear();

	// --- 查询 ---
	int nodeCount() const;
	QString nodeIdAt(int index) const;
	QString typeKeyAt(int index) const;
	// 不转移所有权；调用方需保证运行期间不删除该节点
	IFlowNode* node(const QString& id) const;

	// --- 序列化 / 反序列化 ---
	QJsonObject serialize() const;
	bool deserialize(const QJsonObject& json);

	// ===== 以下供 FlowWorker 执行器使用，调用方必须持有 mutex 锁 =====
	mutable QMutex mutex;
	int nodeCountUnlocked() const;
	QString nodeIdAtUnlocked(int index) const;
	FlowNodeItem* itemUnlocked(const QString& id) const;

signals:
	void nodeAdded(const QString& id, int index);
	void nodeRemoved(const QString& id, int index);
	void nodeMoved(const QString& id, int from, int to);
	void modelCleared();

private:
	std::vector<std::unique_ptr<FlowNodeItem>> m_nodes;
};
