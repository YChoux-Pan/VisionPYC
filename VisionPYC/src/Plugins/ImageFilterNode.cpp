#include "ImageFilterNode.h"
#include "NodeData.h"
#include "NodeRegistry.h"
#include "PreProcessWidget.h"
#include "RoiWidget.h"
#include "CameraInputWidget.h"
#include <QMutexLocker>

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
		auto* w = new PreProcessWidget();
		w->setNode(this);   // 关联节点，预览时读取输入图像
		m_cachedWidget = w;
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
		const cv::Mat img = w->currentImage();
		auto out = std::make_shared<ImageData>();
		out->image = img;
		m_outputs[0] = std::move(out);
		setPreviewInput(img);
		setPreviewOutput(img);
		m_lastResult = true;
		return true;
	}

	// --- 图像预处理：执行真正的 OpenCV 算法 ---
	if (m_subType == "图像预处理") {
		auto src = m_inputs[0];
		if (!src || src->type() != DataType::Image) {
			m_lastResult = false;
			return false;   // 缺少上游图像数据
		}
		auto imgData = std::dynamic_pointer_cast<ImageData>(src);
		if (!imgData || imgData->image.empty()) {
			m_lastResult = false;
			return false;
		}

		cv::Mat dst;
		// 线程安全获取参数快照（GUI 线程可能正在调整参数）
		const PreprocessParams params = paramsSnapshot();
		if (!applyPreprocess(imgData->image, params, dst)) {
			m_lastResult = false;
			return false;
		}

		auto out = std::make_shared<ImageData>();
		out->image = dst;
		m_outputs[0] = std::move(out);
		setPreviewInput(imgData->image);
		setPreviewOutput(dst);
		m_lastResult = true;
		return true;
	}

	// --- ROI设置：透传输入图像（具体算法后续填充）---
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
	obj["preprocess"] = preprocessParamsToJson(m_preParams);
	return obj;
}

void ImageFilterNode::loadParams(const QJsonObject& obj)
{
	if (obj.contains("subType"))
		m_subType = obj["subType"].toString();
	if (obj.contains("preprocess"))
		m_preParams = preprocessParamsFromJson(obj["preprocess"].toObject());
}

// --- 预处理参数线程安全访问 ---
PreprocessParams ImageFilterNode::paramsSnapshot() const
{
	QMutexLocker locker(&m_paramMutex);
	return m_preParams;
}

void ImageFilterNode::setParams(const PreprocessParams& p)
{
	QMutexLocker locker(&m_paramMutex);
	m_preParams = p;
}

// --- 预览图像缓存（线程安全）---
cv::Mat ImageFilterNode::previewInput() const
{
	QMutexLocker locker(&m_imgMutex);
	return m_lastInput.clone();
}

cv::Mat ImageFilterNode::previewOutput() const
{
	QMutexLocker locker(&m_imgMutex);
	return m_lastOutput.clone();
}

void ImageFilterNode::setPreviewInput(const cv::Mat& img)
{
	QMutexLocker locker(&m_imgMutex);
	m_lastInput = img.clone();
}

void ImageFilterNode::setPreviewOutput(const cv::Mat& img)
{
	QMutexLocker locker(&m_imgMutex);
	m_lastOutput = img.clone();
}

// 一个实现类注册多个算子类型（自动出现在左侧算子库）
REGISTER_NODE(ImageFilterNode, "图像预处理", "图像检测", "图像预处理")
REGISTER_NODE(ImageFilterNode, "ROI设置", "图像检测", "ROI设置")
REGISTER_NODE(ImageFilterNode, "采集图像", "图像检测", "采集图像")
