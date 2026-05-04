#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <map>

class CollapsibleCategory;

class NodeSelectorWidget : public QWidget {
	Q_OBJECT
public:
	explicit NodeSelectorWidget(QWidget* parent = nullptr);

	// 核心函数：向分类中添加自定义定义的算子
	void addOperator(const QString& categoryName, const QString& displayName, const QString& internalName);

	// 支持直接添加一个复杂的 Widget 子类作为分类内容
	void addCategoryWidget(const QString& categoryName, QWidget* customWidget);

private:
	QVBoxLayout* m_mainLayout;
	std::map<QString, CollapsibleCategory*> m_categoryMap;
};