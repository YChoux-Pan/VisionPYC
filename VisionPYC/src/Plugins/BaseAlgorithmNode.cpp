#include "BaseAlgorithmNode.h"

BaseAlgorithmNode::BaseAlgorithmNode()
{
	m_lastResult = false;
	m_runTime = 0;
}

// 默认返回一个空白 Widget，子类应重写它
QWidget* BaseAlgorithmNode::getConfigWidget()
{
	QWidget* defaultWidget = new QWidget();
	defaultWidget->setMinimumSize(300, 200);
	// 可以在这里加一个默认的 label 提示：该节点无配置项
	return defaultWidget;
}

void BaseAlgorithmNode::setInputData(int portIndex, std::shared_ptr<INodeData> data)
{
	// 将上游节点传来的数据存入缓存
	m_inputs[portIndex] = data;
}

std::shared_ptr<INodeData> BaseAlgorithmNode::getOutputData(int portIndex)
{
	// 供下游节点或 Core 模块提取结果
	if (m_outputs.count(portIndex)) {
		return m_outputs[portIndex];
	}
	return nullptr;
}