#include "WorkflowTreeWidget.h"
#include "FlowEngine.h"
#include "IFlowNode.h"
#include <QHeaderView>
#include <QMimeData>
#include <QMenu>
#include <QDebug>

WorkflowTreeWidget::WorkflowTreeWidget(QWidget* parent) : QTreeWidget(parent) {
	// 1. 基础列配置
	setColumnCount(2);
	setHeaderLabels({ "流程步骤", "状态/耗时" });

	// 2. 开启拖放功能 (针对 Qt 6 优化的组合设置)
	setDragEnabled(true);                // 允许拖出
	setAcceptDrops(true);                // 允许拖入
	setDragDropMode(QAbstractItemView::InternalMove); // 设为内部移动模式，支持长按排序
	setDefaultDropAction(Qt::MoveAction);
	showDropIndicator();                 // 显示放置指示线
	setDropIndicatorShown(true);

	// 3. UI 布局与样式
	setIndentation(25);                  // 层级缩进
	setAnimated(true);                   // 开启展开折叠动画
	header()->setSectionResizeMode(0, QHeaderView::Stretch);
	header()->setSectionResizeMode(1, QHeaderView::Fixed);
	setColumnWidth(1, 120);              // 固定第二列宽度，预留绘制箭头的空间

	setStyleSheet(
		"QTreeWidget { background-color: #2b2b2b; color: #e0e0e0; border: none; font-size: 13px; outline: none; }"
		"QTreeWidget::item { height: 45px; border-bottom: 1px solid #3a3a3a; }"
		"QTreeWidget::item:selected { background-color: #3d3d3d; border-left: 3px solid #00ff00; color: white; }"
	);

	// 4. 与流程引擎联动：状态刷新 / 运行期间禁用编辑
	connect(&FlowEngine::instance(), &FlowEngine::nodeStarted, this,
		[this](const QString& id, int) {
			updateItemState(id, "运行中...", Qt::yellow);
		});
	connect(&FlowEngine::instance(), &FlowEngine::nodeFinished, this,
		[this](const QString& id, int, bool ok, qint64 ms) {
			updateItemState(id,
				ok ? QString("OK (%1 ms)").arg(ms) : QString("失败"),
				ok ? QColor(0, 200, 0) : QColor(255, 90, 90));
		});
	connect(&FlowEngine::instance(), &FlowEngine::runningChanged, this,
		[this](bool running) {
			setEnabled(!running);   // 运行中锁定流程树，防止编辑造成数据竞争
		});
}

void WorkflowTreeWidget::dragEnterEvent(QDragEnterEvent* event) {
	// 只接受带有文本（typeKey）的数据
	if (event->mimeData()->hasText()) {
		event->acceptProposedAction();
	}
}

void WorkflowTreeWidget::dragMoveEvent(QDragMoveEvent* event) {
	event->acceptProposedAction();
}

void WorkflowTreeWidget::dropEvent(QDropEvent* event) {
	// 情况 A：数据来自算子库（外部拖入）
	if (event->source() != this) {
		const QString typeKey = event->mimeData()->text();

		// 1. 委托流程引擎创建节点实例
		const QString id = FlowEngine::instance().addNode(typeKey);
		if (id.isEmpty()) {
			event->ignore();
			return;
		}

		// 2. 创建树节点（仅保存节点 ID）
		auto* node = FlowEngine::instance().node(id);
		auto* item = new QTreeWidgetItem();
		item->setText(0, node ? node->displayName() : typeKey);
		item->setText(1, "等待运行...");
		item->setData(0, Qt::UserRole, id);

		// 3. 确定插入位置：是插入到某个节点后面，还是追加到末尾
		QTreeWidgetItem* targetItem = itemAt(event->position().toPoint());
		if (targetItem) {
			const int index = indexOfTopLevelItem(targetItem);
			insertTopLevelItem(index, item);
			// 引擎中节点默认追加到末尾，若插入中间需同步移动
			FlowEngine::instance().moveNode(id, index);
		}
		else {
			addTopLevelItem(item);
		}
		event->acceptProposedAction();
	}
	// 情况 B：内部排序（长按拖动换位）
	else {
		QTreeWidget::dropEvent(event);
		syncOrderToEngine();   // 拖拽结束后将 UI 顺序同步给引擎
	}
}

void WorkflowTreeWidget::mouseDoubleClickEvent(QMouseEvent* event) {
	QTreeWidgetItem* item = itemAt(event->pos());
	if (!item) return;

	const QString id = item->data(0, Qt::UserRole).toString();
	if (!id.isEmpty()) showConfigDialog(id);
}

void WorkflowTreeWidget::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Delete) {
		auto* item = currentItem();
		if (item) {
			const QString id = item->data(0, Qt::UserRole).toString();
			if (FlowEngine::instance().removeNode(id))
				delete item;
		}
		return;
	}
	QTreeWidget::keyPressEvent(event);
}

void WorkflowTreeWidget::contextMenuEvent(QContextMenuEvent* event) {
	QTreeWidgetItem* item = itemAt(event->pos());
	if (!item) return;
	const QString id = item->data(0, Qt::UserRole).toString();
	if (id.isEmpty()) return;

	QMenu menu(this);
	QAction* actConfig = menu.addAction("参数配置...");
	QAction* actUp = menu.addAction("上移");
	QAction* actDown = menu.addAction("下移");
	menu.addSeparator();
	QAction* actDelete = menu.addAction("删除节点");

	QAction* chosen = menu.exec(event->globalPos());
	if (!chosen) return;

	if (chosen == actConfig) {
		showConfigDialog(id);
	}
	else if (chosen == actUp) {
		const int idx = indexOfTopLevelItem(item);
		if (idx > 0 && FlowEngine::instance().moveNode(id, idx - 1)) {
			QTreeWidgetItem* taken = takeTopLevelItem(idx);
			insertTopLevelItem(idx - 1, taken);
			setCurrentItem(taken);
		}
	}
	else if (chosen == actDown) {
		const int idx = indexOfTopLevelItem(item);
		if (idx < topLevelItemCount() - 1 && FlowEngine::instance().moveNode(id, idx + 1)) {
			QTreeWidgetItem* taken = takeTopLevelItem(idx);
			insertTopLevelItem(idx + 1, taken);
			setCurrentItem(taken);
		}
	}
	else if (chosen == actDelete) {
		if (FlowEngine::instance().removeNode(id))
			delete item;
	}
}

void WorkflowTreeWidget::showConfigDialog(const QString& id) {
	auto* node = FlowEngine::instance().node(id);
	if (!node) return;

	QWidget* clientUI = node->createConfigWidget();
	if (!clientUI) return;

	// 防止重复弹出同一个节点的配置窗口
	if (clientUI->isVisible()) {
		clientUI->activateWindow();
		return;
	}

	clientUI->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
	clientUI->setWindowTitle("参数配置 - " + node->displayName());
	clientUI->setMinimumSize(200, 100);
	clientUI->resize(900, 600);
	clientUI->show();
	clientUI->activateWindow();
}

void WorkflowTreeWidget::paintEvent(QPaintEvent* event) {
	// 必须先调用基类绘制列表项，否则界面为空白
	QTreeWidget::paintEvent(event);

	QPainter painter(viewport());
	painter.setRenderHint(QPainter::Antialiasing);
	drawFlowLinks(&painter);
}

void WorkflowTreeWidget::drawFlowLinks(QPainter* painter) {
	int count = topLevelItemCount();
	if (count < 2) return; // 只有一个节点不需要画线

	// 设置流程指示线的颜色（半透明绿）
	QPen pen(QColor(0, 255, 0, 150), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	painter->setPen(pen);

	// 计算 X 轴参考位置（右侧 10% 处）
	int lineX = width() - 40;

	for (int i = 0; i < count - 1; ++i) {
		QTreeWidgetItem* curr = topLevelItem(i);
		QTreeWidgetItem* next = topLevelItem(i + 1);

		// 获取 Item 在视图中的实时坐标矩形
		QRect r1 = visualItemRect(curr);
		QRect r2 = visualItemRect(next);

		if (r1.isNull() || r2.isNull()) continue;

		int yStart = r1.center().y();
		int yEnd = r2.center().y();

		// 1. 绘制垂直连接线
		painter->drawLine(lineX, yStart, lineX, yEnd);

		// 2. 绘制指示箭头（yEnd 处）
		painter->drawLine(lineX, yEnd, lineX - 6, yEnd - 8);
		painter->drawLine(lineX, yEnd, lineX + 6, yEnd - 8);
	}
}

QTreeWidgetItem* WorkflowTreeWidget::findItem(const QString& id) const {
	for (int i = 0; i < topLevelItemCount(); ++i) {
		auto* it = topLevelItem(i);
		if (it->data(0, Qt::UserRole).toString() == id)
			return it;
	}
	return nullptr;
}

void WorkflowTreeWidget::updateItemState(const QString& id, const QString& text, const QColor& color) {
	auto* it = findItem(id);
	if (!it) return;
	it->setText(1, text);
	it->setForeground(1, color);
}

void WorkflowTreeWidget::syncOrderToEngine() {
	QVector<QString> ids;
	for (int i = 0; i < topLevelItemCount(); ++i) {
		ids << topLevelItem(i)->data(0, Qt::UserRole).toString();
	}
	FlowEngine::instance().syncOrder(ids);
}
