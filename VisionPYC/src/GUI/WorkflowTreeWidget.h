#pragma once

#include <QTreeWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QDragEnterEvent>
#include <QDropEvent>

// 流程编排树：只持有节点 ID，不直接持有算法指针。
// 节点创建 / 删除 / 排序全部委托 FlowEngine 完成。
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
	void keyPressEvent(QKeyEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	// 绘制右侧流程指示线
	void drawFlowLinks(QPainter* painter);
	// 查找持有指定节点 ID 的树项
	QTreeWidgetItem* findItem(const QString& id) const;
	// 更新指定节点的状态列显示
	void updateItemState(const QString& id, const QString& text, const QColor& color);
	// 内部拖拽排序完成后，将 UI 顺序同步给 FlowEngine
	void syncOrderToEngine();
	// 弹出节点参数配置窗口（双击 / 右键菜单共用）
	void showConfigDialog(const QString& id);
};
