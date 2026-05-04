#pragma once
#include <vector>
#include <QUuid>
#include <memory>

class FlowGraph; // 前向声明

class GraphExecutor {
public:
    GraphExecutor() = default;

    /**
     * @brief 执行整个流程图
     * @param graph 传入当前的逻辑图结构
     */
    void execute(FlowGraph& graph);

private:
    /**
     * @brief 为特定节点准备输入数据
     * 从前驱节点的输出缓存中抓取数据并填入当前节点
     */
    void prepareInputs(FlowGraph& graph, QUuid nodeId);
};