#include "OperatorButton.h"
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

// 手动代码创建时使用
OperatorButton::OperatorButton(const QString& displayName, const QString& internalName, QWidget* parent)
	: QPushButton(displayName, parent), m_internalName(internalName)
{
	this->setFixedHeight(60);
	this->setProperty("opType", internalName);
	this->setStyleSheet(
		"QPushButton {"
		"   color: white;"                // 字体颜色
		"   background-color: #3c3c3c;"   // 深灰色背景
		"   border-radius: 5px;"          // 圆角
		"   border: 1px solid #555555;"   // 边框
		"}"
		"QPushButton:hover {"             // 鼠标悬停时的效果
		"   background-color: #505050;"   // 变亮一点
		"   color: #00ff00;"              // 悬停时文字变绿（可选）
		"}"
	);
}

// Qt Designer 提升时使用
OperatorButton::OperatorButton(QWidget* parent)
	: QPushButton(parent)
{
	this->setFixedHeight(60);
	this->setStyleSheet(
		"QPushButton {"
		"   color: white;"                // 字体颜色
		"   background-color: #3c3c3c;"   // 深灰色背景
		"   border-radius: 5px;"          // 圆角
		"   border: 1px solid #555555;"   // 边框
		"}"
		"QPushButton:hover {"             // 鼠标悬停时的效果
		"   background-color: #505050;"   // 变亮一点
		"   color: #00ff00;"              // 悬停时文字变绿（可选）
		"}"
	);
}

void OperatorButton::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) m_startPos = event->pos();
	QPushButton::mousePressEvent(event);
}

void OperatorButton::mouseMoveEvent(QMouseEvent* event) {
	if (!(event->buttons() & Qt::LeftButton)) return;
	if ((event->pos() - m_startPos).manhattanLength() < QApplication::startDragDistance()) return;

	QDrag* drag = new QDrag(this);
	QMimeData* mimeData = new QMimeData;

	// 如果 m_internalName 为空（忘记设置），则降级使用按钮显示的 text
	QString finalName = m_internalName.isEmpty() ? this->text() : m_internalName;

	mimeData->setText(finalName);
	drag->setMimeData(mimeData);
	drag->exec(Qt::CopyAction);
}