#pragma once

#include "IFlowNode.h"
#include <QString>
#include <QWidget>
#include <map>
#include <memory>

// 插件基类：负责 算法逻辑 + 参数界面 的统一管理。
// 子类只需实现 typeKey/displayName/category、端口描述、process()、createConfigWidget()。
class BaseAlgorithmNode : public IFlowNode {
public:
	BaseAlgorithmNode();
	~BaseAlgorithmNode() override;

	// 默认无端口，子类按需重写
	QVector<FlowPort> inputPorts() const override { return {}; }
	QVector<FlowPort> outputPorts() const override { return {}; }

	// 数据访问（端口索引缓存）
	void setInput(int portIndex, std::shared_ptr<INodeData> data) override;
	std::shared_ptr<INodeData> getOutput(int portIndex) override;

	// 默认返回空白配置页，子类重写
	QWidget* createConfigWidget() override;

	// 状态获取
	bool lastResult() const { return m_lastResult; }
	qint64 runTime() const { return m_runTime; }

protected:
	// 输入 / 输出数据缓存（key: 端口索引）
	std::map<int, std::shared_ptr<INodeData>> m_inputs;
	std::map<int, std::shared_ptr<INodeData>> m_outputs;
};
