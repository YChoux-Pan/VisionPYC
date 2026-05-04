#include "CoreManager.h"
#include "NodeDataModel.h"

// 单例模式实现
CoreManager& CoreManager::instance() {
	static CoreManager inst;
	return inst;
}

void CoreManager::onNodeAdded(std::shared_ptr<IFlowNode> plugin, QUuid id) {
	// 1. 将插件包装成逻辑模型
	auto newNode = std::make_shared<NodeDataModel>(plugin);

	// 2. 这里有个关键细节：我们需要同步 GUI 传来的 ID
	// 假设 NodeDataModel 有一个 setId 方法，或者在构造时传入
	// 确保 Core 层的 ID 和 GUI 层的 NodeItem ID 完全一致

	// 3. 加入逻辑图管理
	m_graph.addNode(newNode);
}

void CoreManager::onLineConnected(QUuid outNode, int outPort, QUuid inNode, int inPort) {
	// 当用户在界面上拉好一条线时，通知逻辑层建立连接
	// outNode: 起始节点（输出端）
	// inNode:  目标节点（输入端）
	m_graph.connectNodes(outNode, outPort, inNode, inPort);
}

void CoreManager::runOnce() {
	// 执行一键运行逻辑
	// 1. 可以先进行前置检查（比如是否有孤立的必需节点）

	// 2. 调用执行引擎
	m_executor.execute(m_graph);

	// 3. 运行完成后，可以通过信号或回调通知 GUI 更新结果显示
}