#include "ImageFilterNode.h"
#include <QDebug>
#include <QElapsedTimer>

ImageFilterNode::ImageFilterNode() : BaseAlgorithmNode("高斯滤波") {
	addPort("Input", PortType::In);
	addPort("Output", PortType::Out);
	syncPortsToCore(); // 确保逻辑层的 map 被初始化
}

void ImageFilterNode::process() {
	QElapsedTimer timer;
	timer.start();

	// 1. 获取输入数据
	auto input = m_inputs[0];
	if (!input || input->type() != DataType::Image) {
		m_lastResult = false;
		return;
	}

	// 2. 执行真正的算法逻辑 (这里以伪代码示意，你可以接入 OpenCV)
	qDebug() << "Executing Gaussian Blur on data...";
	// cv::Mat src = input->toMat();
	// cv::GaussianBlur(src, dst, ...);

	// 3. 将结果封装成 INodeData 存入输出
	// m_outputs[0] = std::make_shared<ImageData>(dst);

	m_lastResult = true;
	m_runTime = timer.elapsed();
}