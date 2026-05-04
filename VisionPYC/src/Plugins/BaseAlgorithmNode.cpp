#include "BaseAlgorithmNode.h"
#include "PortItem.h"

BaseAlgorithmNode::BaseAlgorithmNode(QString title)
	: NodeItem(title)
{
	// 初始化时，确保 m_lastResult 为 false
	m_lastResult = false;
	m_runTime = 0;

	setFlags(QGraphicsItem::ItemIsMovable |
		QGraphicsItem::ItemIsSelectable |
		QGraphicsItem::ItemSendsGeometryChanges); // 发送位置改变信号（用于更新连线）

	// 建议开启，以便接收 hoverEnterEvent 等
	setAcceptHoverEvents(true);

}

void BaseAlgorithmNode::syncPortsToCore()
{
	// 1. 清空旧的逻辑缓存（可选，视重置逻辑而定）
	m_inputs.clear();
	m_outputs.clear();

	// 2. 遍历 GUI 层已有的所有端口
	// NodeItem 维护了 QList<PortItem*> m_ports
	for (PortItem* port : this->ports())
	{
		int index = 0;
		if (port->portType() == PortType::In)
		{
			// 找到当前输入端口的索引（例如第几个输入口）
			// 这里可以根据端口在 m_ports 中的顺序或自定义属性来确定
			// 简单处理：按添加顺序自动编号
			index = m_inputs.size();
			m_inputs[index] = nullptr; // 初始化为空指针，等待 Core 填充数据
		}
		else
		{
			index = m_outputs.size();
			m_outputs[index] = nullptr; // 初始化为空指针，等待 process() 产生结果
		}
	}
}

// 顺便补充 IFlowNode 要求的接口实现，方便子类直接使用
void BaseAlgorithmNode::setInputData(int portIndex, std::shared_ptr<INodeData> data)
{
	// Core 模块在执行前，会调用此函数将数据注入插件
	m_inputs[portIndex] = data;
}

std::shared_ptr<INodeData> BaseAlgorithmNode::getOutputData(int portIndex)
{
	// 执行完 process() 后，Core 模块或下一个节点会通过此函数拿走数据
	if (m_outputs.count(portIndex)) {
		return m_outputs[portIndex];
	}
	return nullptr;
}

void BaseAlgorithmNode::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mousePressEvent(event);
}
