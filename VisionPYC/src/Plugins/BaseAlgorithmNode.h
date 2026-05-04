#pragma once
#include "NodeItem.h"
#include "IFlowNode.h"

// 插件基类：双重继承，既是界面方块，又是逻辑节点
class BaseAlgorithmNode : public NodeItem, public IFlowNode {
public:
	BaseAlgorithmNode(QString title);

	// 默认实现接口中的一些通用功能
	virtual QString category() const override { return "Default"; }

	// 兼容 GUI 层的连线更新逻辑
	// 当 UI 上添加了 Port 后，逻辑层也需要知道输入输出的数量
	void syncPortsToCore();

	// 在 BaseAlgorithmNode.h 中确保实现了这几个函数
	void setInputData(int portIndex, std::shared_ptr<INodeData> data) override;
	std::shared_ptr<INodeData> getOutputData(int portIndex) override;

	
protected:
	// 存储每个端口的数据缓存
	std::map<int, std::shared_ptr<INodeData>> m_inputs;
	std::map<int, std::shared_ptr<INodeData>> m_outputs;

	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

	
};