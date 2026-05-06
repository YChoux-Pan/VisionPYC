#include "ImageFilterNode.h"
// 包含所有具体的小模块 UI
#include "PreProcessWidget.h"
#include "RoiWidget.h"
#include "CameraInputWidget.h"
ImageFilterNode::ImageFilterNode(QString subType)
	: BaseAlgorithmNode(), m_subType(subType) {
}

QWidget* ImageFilterNode::getConfigWidget() {
	// 如果已经创建过，直接返回（保留用户调节好的参数）
	if (m_cachedWidget) return m_cachedWidget;

	// 根据身份进行中转，返回独立的小模块控件
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

void ImageFilterNode::process() {
	// 算法中转逻辑
	if (!m_cachedWidget) return;

	if (m_subType == "图像预处理") {
		auto* w = qobject_cast<PreProcessWidget*>(m_cachedWidget);
		if (w) {
			//int blurValue = w->getBlurValue(); // 从具体小模块拿到参数
			//qDebug() << "Executing Image PreProcess with Blur:" << blurValue;
			// 执行 OpenCV 逻辑...
		}
	}
	else if (m_subType == "ROI设置") {
		auto* w = qobject_cast<RoiWidget*>(m_cachedWidget);
		if (w) {
			//QRect roi = w->getRoiRect(); // 从 ROI 界面拿到矩形
			//qDebug() << "Setting ROI:" << roi;
		}
	}
	else if (m_subType == "ROI设置") {
		auto* w = qobject_cast<CameraInputWidget*>(m_cachedWidget);
		if (w) {
			//QRect roi = w->getRoiRect(); // 从 ROI 界面拿到矩形
			//qDebug() << "Setting ROI:" << roi;
		}
	}

	m_lastResult = true;
}