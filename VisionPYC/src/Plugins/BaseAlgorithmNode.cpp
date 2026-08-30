#include "BaseAlgorithmNode.h"

BaseAlgorithmNode::BaseAlgorithmNode()
{
	m_lastResult = false;
	m_runTime = 0;
}

BaseAlgorithmNode::~BaseAlgorithmNode() = default;

void BaseAlgorithmNode::setInput(int portIndex, std::shared_ptr<INodeData> data)
{
	m_inputs[portIndex] = std::move(data);
}

std::shared_ptr<INodeData> BaseAlgorithmNode::getOutput(int portIndex)
{
	auto it = m_outputs.find(portIndex);
	return (it != m_outputs.end()) ? it->second : nullptr;
}

QWidget* BaseAlgorithmNode::createConfigWidget()
{
	QWidget* defaultWidget = new QWidget();
	defaultWidget->setMinimumSize(300, 200);
	return defaultWidget;
}
