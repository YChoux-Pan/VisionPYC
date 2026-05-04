#include "NodeSelectorWidget.h"
#include "CollapsibleCategory.h"
#include "OperatorButton.h"

NodeSelectorWidget::NodeSelectorWidget(QWidget* parent) : QWidget(parent) {
	QVBoxLayout* rootLayout = new QVBoxLayout(this);
	rootLayout->setContentsMargins(0, 0, 0, 0);

	QScrollArea* scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setStyleSheet("background-color: #1e1e1e;");

	QWidget* container = new QWidget();
	m_mainLayout = new QVBoxLayout(container);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);
	m_mainLayout->setSpacing(1);
	m_mainLayout->addStretch(); // 底部弹簧

	scrollArea->setWidget(container);
	rootLayout->addWidget(scrollArea);
}

void NodeSelectorWidget::addOperator(const QString& categoryName, const QString& displayName, const QString& internalName) {
	if (m_categoryMap.find(categoryName) == m_categoryMap.end()) {
		CollapsibleCategory* newCat = new CollapsibleCategory(categoryName, this);
		// 在弹簧之前插入
		m_mainLayout->insertWidget(m_mainLayout->count() - 1, newCat);
		m_categoryMap[categoryName] = newCat;
	}

	OperatorButton* btn = new OperatorButton(displayName, internalName);
	m_categoryMap[categoryName]->addWidget(btn);
}

void NodeSelectorWidget::addCategoryWidget(const QString& categoryName, QWidget* customWidget) {
	if (m_categoryMap.find(categoryName) == m_categoryMap.end()) {
		CollapsibleCategory* newCat = new CollapsibleCategory(categoryName, this);
		m_mainLayout->insertWidget(m_mainLayout->count() - 1, newCat);
		m_categoryMap[categoryName] = newCat;
	}
	m_categoryMap[categoryName]->addWidget(customWidget);
}