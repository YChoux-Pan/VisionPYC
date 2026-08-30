#include "_3DProcessNode.h"

#include "NodeData.h"
#include "NodeRegistry.h"
#include "Height3DWidget.h"
#include "Planeness3DWidget.h"

_3DProcessNode::_3DProcessNode(QString subType)
	: BaseAlgorithmNode(), m_subType(std::move(subType))
{
}

QVector<FlowPort> _3DProcessNode::inputPorts() const
{
	return { { "输入图像", DataType::Image, PortDirection::In } };
}

QVector<FlowPort> _3DProcessNode::outputPorts() const
{
	return { { "输出图像", DataType::Image, PortDirection::Out } };
}

QWidget* _3DProcessNode::createConfigWidget()
{
	if (m_cachedWidget) return m_cachedWidget;

	if (m_subType == "高度检测") {
		m_cachedWidget = new Height3DWidget();
	}
	else if (m_subType == "平面度检测") {
		m_cachedWidget = new Planeness3DWidget();
	}
	return m_cachedWidget;
}

bool _3DProcessNode::process()
{
	// 透传输入图像（3D 具体算法后续填充）
	auto src = m_inputs[0];
	if (!src || src->type() != DataType::Image) {
		m_lastResult = false;
		return false;   // 缺少上游图像数据
	}
	m_outputs[0] = src;
	m_lastResult = true;
	return true;
}

QJsonObject _3DProcessNode::saveParams() const
{
	QJsonObject obj;
	obj["subType"] = m_subType;
	return obj;
}

void _3DProcessNode::loadParams(const QJsonObject& obj)
{
	if (obj.contains("subType"))
		m_subType = obj["subType"].toString();
}

// 一个实现类注册多个算子类型（自动出现在左侧算子库）
REGISTER_NODE(_3DProcessNode, "高度检测", "3D检测", "高度检测")
REGISTER_NODE(_3DProcessNode, "平面度检测", "3D检测", "平面度检测")
