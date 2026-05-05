#pragma once

#include <QTreeWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>

class WorkflowTreeWidget : public QTreeWidget {
	Q_OBJECT
public:
	explicit WorkflowTreeWidget(QWidget* parent = nullptr);

protected:
	// 拖放事件处理
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dropEvent(QDropEvent* event) override;

	// 交互与绘图
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	// 绘制右侧流程指示线
	void drawFlowLinks(QPainter* painter);
};