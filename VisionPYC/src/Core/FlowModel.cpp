#include "FlowModel.h"
#include "NodeRegistry.h"
#include "IFlowNode.h"
#include <QJsonArray>
#include <QUuid>
#include <map>
#include <utility>

FlowModel::FlowModel(QObject* parent)
	: QObject(parent)
{
}

QString FlowModel::addNode(const QString& typeKey)
{
	QString id;
	int index = -1;
	{
		QMutexLocker locker(&mutex);
		auto impl = NodeRegistry::create(typeKey);
		if (!impl) return {};

		auto item = std::make_unique<FlowNodeItem>();
		item->id = QUuid::createUuid().toString(QUuid::WithoutBraces);
		item->typeKey = typeKey;
		item->impl = std::move(impl);

		index = static_cast<int>(m_nodes.size());
		m_nodes.push_back(std::move(item));
		id = m_nodes.back()->id;
	}
	emit nodeAdded(id, index);
	return id;
}

bool FlowModel::removeNode(const QString& id)
{
	int index = -1;
	{
		QMutexLocker locker(&mutex);
		for (size_t i = 0; i < m_nodes.size(); ++i) {
			if (m_nodes[i]->id == id) {
				index = static_cast<int>(i);
				m_nodes.erase(m_nodes.begin() + static_cast<std::ptrdiff_t>(i));
				break;
			}
		}
	}
	if (index >= 0) {
		emit nodeRemoved(id, index);
		return true;
	}
	return false;
}

bool FlowModel::moveNode(const QString& id, int newIndex)
{
	int from = -1;
	{
		QMutexLocker locker(&mutex);
		for (size_t i = 0; i < m_nodes.size(); ++i) {
			if (m_nodes[i]->id == id) {
				from = static_cast<int>(i);
				break;
			}
		}
		if (from < 0) return false;
		if (newIndex < 0) newIndex = 0;
		if (newIndex >= static_cast<int>(m_nodes.size()))
			newIndex = static_cast<int>(m_nodes.size()) - 1;
		if (from == newIndex) return true;

		auto item = std::move(m_nodes[static_cast<size_t>(from)]);
		m_nodes.erase(m_nodes.begin() + from);
		m_nodes.insert(m_nodes.begin() + newIndex, std::move(item));
	}
	emit nodeMoved(id, from, newIndex);
	return true;
}

bool FlowModel::syncOrder(const QVector<QString>& orderedIds)
{
	QMutexLocker locker(&mutex);
	if (orderedIds.size() != static_cast<int>(m_nodes.size())) return false;

	// 用 ID 建索引，按传入顺序重排
	std::map<QString, std::unique_ptr<FlowNodeItem>> byId;
	for (auto& it : m_nodes)
		byId[it->id] = std::move(it);

	std::vector<std::unique_ptr<FlowNodeItem>> reordered;
	for (const QString& id : orderedIds) {
		auto it = byId.find(id);
		if (it == byId.end()) return false;   // ID 集合不一致，放弃
		reordered.push_back(std::move(it->second));
	}
	m_nodes = std::move(reordered);
	return true;
}

void FlowModel::clear()
{
	{
		QMutexLocker locker(&mutex);
		m_nodes.clear();
	}
	emit modelCleared();
}

int FlowModel::nodeCount() const
{
	QMutexLocker locker(&mutex);
	return static_cast<int>(m_nodes.size());
}

QString FlowModel::nodeIdAt(int index) const
{
	QMutexLocker locker(&mutex);
	if (index < 0 || index >= static_cast<int>(m_nodes.size())) return {};
	return m_nodes[static_cast<size_t>(index)]->id;
}

QString FlowModel::typeKeyAt(int index) const
{
	QMutexLocker locker(&mutex);
	if (index < 0 || index >= static_cast<int>(m_nodes.size())) return {};
	return m_nodes[static_cast<size_t>(index)]->typeKey;
}

IFlowNode* FlowModel::node(const QString& id) const
{
	QMutexLocker locker(&mutex);
	for (auto& it : m_nodes) {
		if (it->id == id) return it->impl.get();
	}
	return nullptr;
}

QJsonObject FlowModel::serialize() const
{
	QMutexLocker locker(&mutex);
	QJsonArray arr;
	for (auto& it : m_nodes) {
		QJsonObject obj;
		obj[QStringLiteral("id")] = it->id;
		obj[QStringLiteral("typeKey")] = it->typeKey;
		obj[QStringLiteral("enabled")] = it->enabled;
		obj[QStringLiteral("params")] = it->impl->saveParams();
		arr.append(obj);
	}
	QJsonObject root;
	root[QStringLiteral("nodes")] = arr;
	return root;
}

bool FlowModel::deserialize(const QJsonObject& json)
{
	const QJsonArray arr = json.value(QStringLiteral("nodes")).toArray();
	std::vector<std::unique_ptr<FlowNodeItem>> nodes;
	for (const auto& val : arr) {
		const QJsonObject obj = val.toObject();
		const QString typeKey = obj.value(QStringLiteral("typeKey")).toString();
		auto impl = NodeRegistry::create(typeKey);
		if (!impl) continue;   // 未知算子类型，跳过

		auto item = std::make_unique<FlowNodeItem>();
		item->id = obj.value(QStringLiteral("id")).toString(
			QUuid::createUuid().toString(QUuid::WithoutBraces));
		item->typeKey = typeKey;
		item->enabled = obj.value(QStringLiteral("enabled")).toBool(true);
		impl->loadParams(obj.value(QStringLiteral("params")).toObject());
		item->impl = std::move(impl);
		nodes.push_back(std::move(item));
	}

	{
		QMutexLocker locker(&mutex);
		m_nodes = std::move(nodes);
	}
	emit modelCleared();
	return true;
}

// ===== unlocked 辅助（FlowWorker 使用，调用方持锁） =====
int FlowModel::nodeCountUnlocked() const
{
	return static_cast<int>(m_nodes.size());
}

QString FlowModel::nodeIdAtUnlocked(int index) const
{
	if (index < 0 || index >= static_cast<int>(m_nodes.size())) return {};
	return m_nodes[static_cast<size_t>(index)]->id;
}

FlowNodeItem* FlowModel::itemUnlocked(const QString& id) const
{
	for (auto& it : m_nodes) {
		if (it->id == id) return it.get();
	}
	return nullptr;
}
