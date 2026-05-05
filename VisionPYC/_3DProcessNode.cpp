#include "_3DProcessNode.h"

#include "Height3DWidget.h" // 高度检测UI
#include "Planeness3DWidget.h"   // 平面拟合UI
#include <QDebug>
#include <QElapsedTimer>

_3DProcessNode::_3DProcessNode(QString subType)
	: BaseAlgorithmNode(), m_subType(subType) {
}

QWidget* _3DProcessNode::getConfigWidget() {
	if (m_cachedWidget) return m_cachedWidget;

	if (m_subType == "高度检测") {
		m_cachedWidget = new Height3DWidget();
	}
	else if (m_subType == "平面度检测") {
		m_cachedWidget = new Planeness3DWidget();
	}

	return m_cachedWidget;
}

void _3DProcessNode::process() {
	QElapsedTimer timer;
	timer.start();

	if (!m_cachedWidget) {
		m_lastResult = false;
		return;
	}

	if (m_subType == "高度检测") {
		auto* w = qobject_cast<Height3DWidget*>(m_cachedWidget);
		
	}
	else if (m_subType == "平面度检测")
	{
		auto* w = qobject_cast<Planeness3DWidget*>(m_cachedWidget);
	}

	m_lastResult = true;
	m_runTime = timer.elapsed();
}