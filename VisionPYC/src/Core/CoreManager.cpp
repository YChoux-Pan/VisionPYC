#include "CoreManager.h"
#include <QDebug>

CoreManager& CoreManager::instance() {
	static CoreManager inst;
	return inst;
}

void CoreManager::onNodeAdded(std::shared_ptr<IFlowNode> plugin, const QString& id) {
	if (!plugin) return;

	// 1. 注册节点到管理器
	m_nodes[id] = plugin;

	// 2. 默认加入到执行序列末尾
	m_executionOrder.push_back(id);

	qDebug() << "Core: Node added with ID:" << id << " Model:" << plugin->modelName();
}

void CoreManager::updateWorkflowOrder(const QList<QString>& idOrder) {
	// 当 WorkflowTreeWidget 发生拖拽排序后，调用此函数同步逻辑顺序
	m_executionOrder.clear();
	for (const QString& id : idOrder) {
		if (m_nodes.count(id)) {
			m_executionOrder.push_back(id);
		}
	}
}

void CoreManager::runOnce() {
	//qDebug() << "Core: Starting workflow execution...";

	std::shared_ptr<INodeData> lastResult = nullptr;

	// 按照记录的顺序线性执行
	for (const QString& id : m_executionOrder) {
		auto node = m_nodes[id];
		if (!node) continue;

		// 1. 自动传递数据：将上一个算子的输出作为当前算子的输入
		if (lastResult) {
			node->setInputData(0, lastResult);
		}

		// 2. 执行计算
		node->process();

		// 3. 检查并获取结果
		// 假设 IFlowNode 有获取运行状态的接口
		lastResult = node->getOutputData(0);

		qDebug() << "Core: Executed" << node->modelName() << " ID:" << id;
	}
}