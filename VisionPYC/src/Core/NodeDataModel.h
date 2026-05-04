#pragma once
#include <QUuid>
#include <map>
#include <memory>
#include "IFlowNode.h"

class NodeDataModel {
public:
	NodeDataModel(std::shared_ptr<IFlowNode> plugin);

	// 基础属性
	QUuid id() const { return m_id; }
	std::shared_ptr<IFlowNode> plugin() { return m_plugin; }

	// --- 连接管理 ---
	// 设置输入绑定：将本节点的 myPortIndex 端口连接到 sourceNodeId 的 sourcePortIndex 端口
	void setInputBinding(int myPortIndex, QUuid sourceNodeId, int sourcePortIndex);

	// 【新增接口】获取所有输入绑定关系，供 FlowGraph 进行拓扑排序
	std::map<int, std::pair<QUuid, int>> getInputBindings() const { return m_inputBindings; }

	// --- 数据缓存管理 ---
	// 存储计算结果的缓存（由 Executor 运行后填充）
	void setOutputCache(int portIndex, std::shared_ptr<INodeData> data);

	// 获取结果缓存（供下游节点读取）
	std::shared_ptr<INodeData> getOutputCache(int portIndex);

private:
	QUuid m_id;                               // 每个节点在逻辑层唯一的ID
	std::shared_ptr<IFlowNode> m_plugin;      // 实际的算法对象（插件实例）

	// 数据结构说明：
	// key: 当前节点的输入端口索引
	// value: <来源节点的ID, 来源节点的输出端口索引>
	std::map<int, std::pair<QUuid, int>> m_inputBindings;

	// 数据结构说明：
	// key: 当前节点的输出端口索引
	// value: 具体的计算结果数据包
	std::map<int, std::shared_ptr<INodeData>> m_outputCache;
};