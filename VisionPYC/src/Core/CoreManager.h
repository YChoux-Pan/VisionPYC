#pragma once
#include <memory>
#include <vector>
#include <QString>
#include <QUuid>
#include "IFlowNode.h"

// 线性架构下，我们可以简化逻辑，不再需要复杂的 FlowGraph
// 如果你仍想保留 FlowGraph 结构，建议将其内部改为有序容器
class CoreManager {
public:
	static CoreManager& instance();

	// 更新接口：统一使用 QString 作为 ID 标识，避免 QUuid 类型转换报错
	void onNodeAdded(std::shared_ptr<IFlowNode> plugin, const QString& id);

	// 线性模式下，移除旧的连线接口，改为更新节点顺序
	void updateWorkflowOrder(const QList<QString>& idOrder);

	// 运行逻辑：按照当前列表顺序依次执行
	void runOnce();

private:
	CoreManager() = default;

	// 存储 节点ID -> 节点对象 的映射
	std::map<QString, std::shared_ptr<IFlowNode>> m_nodes;

	// 存储当前的执行顺序
	std::vector<QString> m_executionOrder;
};