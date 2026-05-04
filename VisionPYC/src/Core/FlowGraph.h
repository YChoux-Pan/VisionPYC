#pragma once
#include <vector>
#include "NodeDataModel.h"

class FlowGraph {
public:
	// 添加/删除节点
	void addNode(std::shared_ptr<NodeDataModel> node);
	void removeNode(QUuid id);

	// 建立逻辑连接
	void connectNodes(QUuid fromNode, int fromPort, QUuid toNode, int toPort);
	void disconnectNodes(QUuid toNode, int toPort);

	// 获取拓扑排序后的执行顺序
	// 确保“采集节点”永远在“处理节点”之前运行
	std::vector<QUuid> getExecutionOrder();

	// 根据ID查找节点
	std::shared_ptr<NodeDataModel> findNode(QUuid id);

private:
	std::vector<std::shared_ptr<NodeDataModel>> m_nodes;
};