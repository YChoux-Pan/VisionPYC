#pragma once
#include "FlowGraph.h"
#include "GraphExecutor.h"

class CoreManager {
public:
	static CoreManager& instance();

	// 给 GUI 调用的接口
	void onNodeAdded(std::shared_ptr<IFlowNode> plugin, QUuid id);
	void onLineConnected(QUuid outNode, int outPort, QUuid inNode, int inPort);

	// 一键运行所有逻辑
	void runOnce();

private:
	FlowGraph m_graph;
	GraphExecutor m_executor;
};