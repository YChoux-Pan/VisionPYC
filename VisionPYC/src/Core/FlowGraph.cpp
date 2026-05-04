#include "FlowGraph.h"
#include <queue>
#include <map>
#include <set>
#include <QDebug>

void FlowGraph::addNode(std::shared_ptr<NodeDataModel> node) {
	if (node) {
		m_nodes.push_back(node);
	}
}

void FlowGraph::removeNode(QUuid id) {
	// 使用 std::remove_if 移除指定 ID 的节点
	m_nodes.erase(std::remove_if(m_nodes.begin(), m_nodes.end(),
		[&id](const std::shared_ptr<NodeDataModel>& node) {
			return node->id() == id;
		}), m_nodes.end());
}

void FlowGraph::connectNodes(QUuid fromNode, int fromPort, QUuid toNode, int toPort) {
	auto target = findNode(toNode);
	if (target) {
		// 在逻辑模型中记录：我的 toPort 端口数据来自 fromNode 的 fromPort 端口
		target->setInputBinding(toPort, fromNode, fromPort);
	}
}

void FlowGraph::disconnectNodes(QUuid toNode, int toPort) {
	auto target = findNode(toNode);
	if (target) {
		// 传入一个空的 UUID 来解除绑定
		target->setInputBinding(toPort, QUuid(), -1);
	}
}

std::shared_ptr<NodeDataModel> FlowGraph::findNode(QUuid id) {
	for (auto& node : m_nodes) {
		if (node->id() == id) return node;
	}
	return nullptr;
}

std::vector<QUuid> FlowGraph::getExecutionOrder() {
	std::vector<QUuid> sortedOrder;

	// 1. 建立邻接表和入度表
	// inDegree: 节点ID -> 入度数量
	// adjacencyList: 源节点ID -> [目标节点ID列表]
	std::map<QUuid, int> inDegree;
	std::map<QUuid, std::vector<QUuid>> adjacencyList;

	// 初始化所有节点的入度为 0
	for (const auto& node : m_nodes) {
		inDegree[node->id()] = 0;
	}

	// 遍历所有节点，根据它们的 InputBindings 构建图
	for (const auto& node : m_nodes) {
		auto bindings = node->getInputBindings(); // 假设 NodeDataModel 提供了此接口
		for (auto const& [port, sourceInfo] : bindings) {
			QUuid sourceId = sourceInfo.first;
			if (!sourceId.isNull()) {
				// 逻辑关系：sourceId -> node->id()
				adjacencyList[sourceId].push_back(node->id());
				inDegree[node->id()]++;
			}
		}
	}

	// 2. 将所有入度为 0 的节点放入队列（起点节点）
	std::queue<QUuid> queue;
	for (auto const& [id, degree] : inDegree) {
		if (degree == 0) {
			queue.push(id);
		}
	}

	// 3. 开始拓扑排序 (Kahn算法)
	while (!queue.empty()) {
		QUuid u = queue.front();
		queue.pop();
		sortedOrder.push_back(u);

		// 遍历所有由 u 指向的节点 v
		if (adjacencyList.count(u)) {
			for (const QUuid& v : adjacencyList[u]) {
				inDegree[v]--;
				if (inDegree[v] == 0) {
					queue.push(v);
				}
			}
		}
	}

	// 4. 循环检测
	if (sortedOrder.size() != m_nodes.size()) {
		qDebug() << "Error: Circular dependency detected in the graph!";
		// 如果有环，通常返回一个空列表或抛出异常，防止引擎死循环
		return std::vector<QUuid>();
	}

	return sortedOrder;
}