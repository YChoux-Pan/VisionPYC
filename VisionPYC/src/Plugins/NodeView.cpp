#include "NodeView.h"
#include "NodeFactory.h"
#include "NodeScene.h"
#include "BaseAlgorithmNode.h"
#include "CoreManager.h"

void NodeView::dragEnterEvent(QDragEnterEvent* event) {
	if (event->mimeData()->hasText()) {
		event->acceptProposedAction();
	}
}

void NodeView::dragMoveEvent(QDragMoveEvent* event) {
	event->acceptProposedAction();
}

void NodeView::dropEvent(QDropEvent* event) {
	// 1. 获取拖拽的算子名称
	QString typeName = event->mimeData()->text();

	// 2. 使用插件工厂创建节点对象 (Plugins 模块)
	BaseAlgorithmNode* newNode = NodeFactory::createNode(typeName);

	if (newNode) {
		// 3. 将节点添加到场景中 (GUI 模块)
		this->scene()->addItem(newNode);

		// --- 修正位置获取代码 ---
		// Qt 6 推荐做法：使用 position() 获取 QPointF
		QPointF dropPos = event->position();

		// 将视图坐标转换为场景坐标
		QPointF scenePos = mapToScene(dropPos.toPoint());
		newNode->setPos(scenePos);

		// 4. 通知逻辑层注册该节点 (Core 模块)
		CoreManager::instance().onNodeAdded(
			std::shared_ptr<IFlowNode>(newNode, [](IFlowNode*) {}),
			newNode->id()
		);

		event->acceptProposedAction();
	}
}