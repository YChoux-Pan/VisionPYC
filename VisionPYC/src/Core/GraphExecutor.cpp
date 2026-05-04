#include "GraphExecutor.h"
#include "FlowGraph.h"
#include "NodeDataModel.h"
#include <QElapsedTimer>
#include <QDebug>

void GraphExecutor::execute(FlowGraph& graph) {
	qDebug() << "--- Starting Graph Execution ---";

	// 1. 获取拓扑排序后的执行序列 (确保先执行相机，再执行算法)
	std::vector<QUuid> executionOrder = graph.getExecutionOrder();

	if (executionOrder.empty()) {
		qDebug() << "Warning: Execution order is empty. No nodes to run or circular dependency detected.";
		return;
	}

	// 2. 依次执行节点
	for (const QUuid& nodeId : executionOrder) {
		auto nodeModel = graph.findNode(nodeId);
		if (!nodeModel || !nodeModel->plugin()) continue;

		// A. 数据搬运：把连线对端的输出数据抓过来
		prepareInputs(graph, nodeId);

		// B. 计时并执行
		QElapsedTimer timer;
		timer.start();

		try {
			qDebug() << "Executing Node:" << nodeModel->plugin()->modelName();

			// 调用 Plugins 模块实现的具体算法
			nodeModel->plugin()->process();

			// C. 运行结束后，将插件内部产生的输出数据同步到逻辑层的缓存中
			// 假设每个插件可能有多个输出端口
			for (int i = 0; i < 5; ++i) { // 5可以替换为动态的端口数量
				auto outData = nodeModel->plugin()->getOutputData(i);
				if (outData) {
					nodeModel->setOutputCache(i, outData);
				}
			}

			qDebug() << "Node" << nodeModel->plugin()->modelName() << "finished in" << timer.elapsed() << "ms";
		}
		catch (const std::exception& e) {
			qDebug() << "Critical Error executing node" << nodeId << ":" << e.what();
		}
	}

	qDebug() << "--- Execution Finished ---";
}

void GraphExecutor::prepareInputs(FlowGraph& graph, QUuid nodeId) {
	auto targetNode = graph.findNode(nodeId);
	if (!targetNode) return;

	// 获取该节点所有的输入绑定关系
	// 结构：map<本节点输入端口索引, pair<源节点ID, 源节点输出端口索引>>
	auto bindings = targetNode->getInputBindings();

	for (auto const& [myPort, sourceInfo] : bindings) {
		QUuid sourceId = sourceInfo.first;
		int sourcePort = sourceInfo.second;

		// 找到源节点（上游节点）
		auto sourceNode = graph.findNode(sourceId);
		if (sourceNode) {
			// 从源节点的【结果缓存】中取出数据
			auto data = sourceNode->getOutputCache(sourcePort);

			// 喂给当前节点的插件
			targetNode->plugin()->setInputData(myPort, data);
		}
	}
}