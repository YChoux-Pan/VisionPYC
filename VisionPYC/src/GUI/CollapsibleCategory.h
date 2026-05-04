#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class CollapsibleCategory : public QWidget {
	Q_OBJECT
public:
	explicit CollapsibleCategory(const QString& title, QWidget* parent = nullptr);
	void addWidget(QWidget* widget);

private slots:
	void onHeaderClicked();

private:
	QPushButton* m_headerButton;
	QWidget* m_contentArea;
	QVBoxLayout* m_contentLayout;
	bool m_isExpanded = false;
	QString m_pureTitle;
};