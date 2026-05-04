#pragma once
#include <QPushButton>

class OperatorButton : public QPushButton {
	Q_OBJECT
public:
	// 保留之前的全参数构造函数（手动代码调用）
	explicit OperatorButton(const QString& displayName, const QString& internalName, QWidget* parent = nullptr);

	// 新增：兼容 Qt Designer 提升的构造函数
	// 提升机制通常只传递一个 QWidget* parent
	explicit OperatorButton(QWidget* parent = nullptr);

	// 提供一个设置内部名称的方法，方便在 TESTWidget 中手动指定
	void setInternalName(const QString& name) { m_internalName = name; }

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	QPoint m_startPos;
	QString m_internalName;
};