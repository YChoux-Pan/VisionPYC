#include "NodeDataModel.h"

NodeDataModel::NodeDataModel(std::shared_ptr<IFlowNode> plugin)
	: m_plugin(plugin)
{
	// 生成全局唯一标识符，用于逻辑与 GUI 的映射
	m_id = QUuid::createUuid();
}

void NodeDataModel::setInputBinding(int myPortIndex, QUuid sourceNodeId, int sourcePortIndex)
{
	if (sourceNodeId.isNull()) {
		// 如果传入空 ID，视为断开连接
		m_inputBindings.erase(myPortIndex);
	}
	else {
		// 建立连接：记录数据来源
		m_inputBindings[myPortIndex] = std::make_pair(sourceNodeId, sourcePortIndex);
	}
}

void NodeDataModel::setOutputCache(int portIndex, std::shared_ptr<INodeData> data)
{
	// 每一个节点运行 process() 后，应该通过此方法更新缓存
	m_outputCache[portIndex] = data;
}

std::shared_ptr<INodeData> NodeDataModel::getOutputCache(int portIndex)
{
	auto it = m_outputCache.find(portIndex);
	if (it != m_outputCache.end()) {
		return it->second;
	}
	// 如果没有缓存（比如节点未运行或运行失败），返回空指针
	return nullptr;
}