#include "CollapsibleCategory.h"

CollapsibleCategory::CollapsibleCategory(const QString& title, QWidget* parent)
	: QWidget(parent), m_pureTitle(title)
{
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);

	m_headerButton = new QPushButton("▶ " + title, this);
	m_headerButton->setFixedHeight(32);
	m_headerButton->setStyleSheet(
		"QPushButton { background-color: #2d2d2d; color: #bbb; border: 1px solid #222; text-align: left; padding-left: 5px; font-weight: bold; }"
		"QPushButton:hover { background-color: #383838; color: white; }"
	);

	m_contentArea = new QWidget(this);
	m_contentLayout = new QVBoxLayout(m_contentArea);
	m_contentLayout->setContentsMargins(10, 5, 5, 5);
	m_contentLayout->setSpacing(4);

	m_contentArea->setVisible(false); // 初始隐藏

	mainLayout->addWidget(m_headerButton);
	mainLayout->addWidget(m_contentArea);

	connect(m_headerButton, &QPushButton::clicked, this, &CollapsibleCategory::onHeaderClicked);
}

void CollapsibleCategory::addWidget(QWidget* widget) {
	m_contentLayout->addWidget(widget);
}

void CollapsibleCategory::onHeaderClicked() {
	m_isExpanded = !m_isExpanded;
	m_contentArea->setVisible(m_isExpanded);
	m_headerButton->setText((m_isExpanded ? "▼ " : "▶ ") + m_pureTitle);
}