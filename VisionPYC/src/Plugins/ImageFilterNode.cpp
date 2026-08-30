#include "ImageFilterNode.h"
#include "NodeData.h"
#include "NodeRegistry.h"
#include "PreProcessWidget.h"
#include "RoiWidget.h"
#include "CameraInputWidget.h"

ImageFilterNode::ImageFilterNode(QString subType)
	: BaseAlgorithmNode(), m_subType(std::move(subType))
{
}

QVector<FlowPort> ImageFilterNode::inputPorts() const
{
	// "采集图像"是数据源，无输入端口；其余算子接收图像输入
	if (m_subType == "采集图像") return {};
	return { { "输入图像", DataType::Image, PortDirection::In } };
}

QVector<FlowPort> ImageFilterNode::outputPorts() const
{
	return { { "输出图像", DataType::Image, PortDirection::Out } };
}

QWidget* ImageFilterNode::createConfigWidget()
{
	// 缓存界面，保留用户调节好的参数
	if (m_cachedWidget) return m_cachedWidget;

	if (m_subType == "图像预处理") {
		m_cachedWidget = new PreProcessWidget();
	}
	else if (m_subType == "ROI设置") {
		m_cachedWidget = new RoiWidget();
	}
	else if (m_subType == "采集图像") {
		m_cachedWidget = new CameraInputWidget();
	}
	return m_cachedWidget;
}

bool ImageFilterNode::process()
{
	// --- 采集图像：输出相机/文件当前选中的图像 ---
	if (m_subType == "采集图像") {
		auto* w = qobject_cast<CameraInputWidget*>(m_cachedWidget);
		if (!w || !w->hasImage()) {
			m_lastResult = false;
			return false;   // 未选择图像，流程停止
		}
		auto out = std::make_shared<ImageData>();
		out->image = w->currentImage();
		m_outputs[0] = std::move(out);
		m_lastResult = true;
		return true;
	}

	// --- 图像预处理 / ROI设置：透传输入图像（具体算法后续填充）---
	auto src = m_inputs[0];
	if (!src || src->type() != DataType::Image) {
		m_lastResult = false;
		return false;   // 缺少上游图像数据
	}
	m_outputs[0] = src;
	m_lastResult = true;
	return true;
}

QJsonObject ImageFilterNode::saveParams() const
{
	QJsonObject obj;
	obj["subType"] = m_subType;
	return obj;
}

void ImageFilterNode::loadParams(const QJsonObject& obj)
{
	if (obj.contains("subType"))
		m_subType = obj["subType"].toString();
}

// 一个实现类注册多个算子类型（自动出现在左侧算子库）
REGISTER_NODE(ImageFilterNode, "图像预处理", "图像检测", "图像预处理")
REGISTER_NODE(ImageFilterNode, "ROI设置", "图像检测", "ROI设置")
REGISTER_NODE(ImageFilterNode, "采集图像", "图像检测", "采集图像")
