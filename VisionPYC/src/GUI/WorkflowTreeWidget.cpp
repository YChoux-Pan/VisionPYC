#include "WorkflowTreeWidget.h"
#include "NodeFactory.h"
#include "BaseAlgorithmNode.h"
#include "CoreManager.h"
#include <QHeaderView>
#include <QMimeData>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QMimeData>

WorkflowTreeWidget::WorkflowTreeWidget(QWidget* parent) : QTreeWidget(parent) {
	// 1. 基础列配置
	setColumnCount(2);
	setHeaderLabels({ "流程步骤", "逻辑绑定" });

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
}

void WorkflowTreeWidget::dragEnterEvent(QDragEnterEvent* event) {
	// 只接受带有文本（internalName）的数据
	if (event->mimeData()->hasText()) {
		event->acceptProposedAction();
	}
}

void WorkflowTreeWidget::dragMoveEvent(QDragMoveEvent* event) {
	event->acceptProposedAction();
}

void WorkflowTreeWidget::dropEvent(QDropEvent* event) {
	// 情况 A：数据来自外部（算子库拖入）
	if (event->source() != this) {
		// 1. 获取拖拽的算子名称 (对应 OperatorButton 设置的 internalName)
		QString typeName = event->mimeData()->text();

		// 2. 使用插件工厂创建算法实例 (Plugins 模块)
		BaseAlgorithmNode* newNode = NodeFactory::createNode(typeName);

		if (newNode) {
			// 3. 创建树节点并显示 (GUI 模块)
			QTreeWidgetItem* item = new QTreeWidgetItem();
			item->setText(0, newNode->modelName()); // 第一列：算子名称
			item->setText(1, "等待运行...");          // 第二列：状态描述

			// 关键：将算法实例指针绑定到 Item 中，方便双击和运行逻辑调用
			// 注意：QVariant 不直接支持原始指针，我们转为 void* 存储
			item->setData(0, Qt::UserRole, QVariant::fromValue((void*)newNode));

			// 4. 确定插入位置：是插入到某个节点后面，还是追加到末尾
			QTreeWidgetItem* targetItem = itemAt(event->position().toPoint());
			if (targetItem) {
				int index = indexOfTopLevelItem(targetItem);
				insertTopLevelItem(index, item);
			}
			else {
				addTopLevelItem(item);
			}

			// 5. 通知逻辑层注册该节点 (Core 模块)
			// 注意：这里需要确保你的 CoreManager 能够处理线性顺序
			QString newId = QUuid::createUuid().toString(); // 先生成字符串 ID

			CoreManager::instance().onNodeAdded(
				std::shared_ptr<IFlowNode>(newNode, [](IFlowNode*) {}),
				newId
			);

			// 记得把这个 ID 也存在 QTreeWidgetItem 里，方便以后查找
			item->setData(0, Qt::UserRole + 1, newId);

			event->acceptProposedAction();
		}
	}
	// B. 处理内部排序（长按拖动换位）
	else {
		// 调用基类 QTreeWidget 的原生处理逻辑完成换位
		QTreeWidget::dropEvent(event);

		// 【建议】换位结束后，调用一个同步函数刷新 CoreManager 里的执行顺序
		// syncOrderToCore(); 
	}
}

void WorkflowTreeWidget::mouseDoubleClickEvent(QMouseEvent* event) {
	QTreeWidgetItem* item = itemAt(event->pos());
	if (!item) return;

	// 提取出对应的算法节点指针
	BaseAlgorithmNode* node = static_cast<BaseAlgorithmNode*>(item->data(0, Qt::UserRole).value<void*>());
	if (node) {
		// 创建居中弹窗配置界面
		QWidget* clientUI = node->getConfigWidget();
		if (!clientUI) return;

		// 2. 设置窗口属性：使其成为一个独立的窗口，且拥有最小化、最大化和关闭按钮
		// Qt::Window: 声明这是一个独立窗口
		// Qt::WindowMinMaxButtonsHint: 显示放大缩小按钮
		// Qt::WindowCloseButtonHint: 显示关闭按钮
		clientUI->setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

		// 3. 设置窗口标题（会显示在标题栏）
		clientUI->setWindowTitle("参数配置 - " + item->text(0));

		// 4. 设置初始大小（你可以根据需要动态设置）
		// 如果想让它有最小尺寸限制：
		clientUI->setMinimumSize(200, 100);
		clientUI->resize(900, 600); // 初始默认大小

		// 5. 居中显示（可选）
		// 如果不设置，它通常会出现在屏幕左上角或上次关闭的位置
		clientUI->show();
		clientUI->activateWindow(); // 确保窗口提到最前方并获得焦点
	}
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