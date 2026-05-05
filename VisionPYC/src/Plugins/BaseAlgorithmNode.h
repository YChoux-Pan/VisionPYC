#pragma once

#include "IFlowNode.h"
#include <QString>
#include <memory>
#include <map>
#include <QWidget>

// 插件基类：现在它只负责 逻辑算法 + 参数界面
class BaseAlgorithmNode : public IFlowNode {
public:
	BaseAlgorithmNode();
	virtual ~BaseAlgorithmNode() = default;

	// --- 身份标识 ---
	virtual QString category() const { return "Default"; }
	virtual QString modelName() const = 0; // 由子类（如 GaussianBlurNode）实现

	// --- UI 接口 ---
	// 双击列表项时，WorkflowTreeWidget 会调用此函数弹出界面
	// 子类应重写此函数，返回一个包含具体参数（Slider, ComboBox等）的 Widget
	virtual QWidget* getConfigWidget();

	// --- 核心算法接口 (继承自 IFlowNode) ---
	// 流程引擎在运行时会调用这些接口
	void setInputData(int portIndex, std::shared_ptr<INodeData> data) override;
	std::shared_ptr<INodeData> getOutputData(int portIndex) override;
	virtual void process() override = 0; // 具体算法逻辑由子类实现

	// 状态获取
	bool lastResult() const { return m_lastResult; }
	qint64 runTime() const { return m_runTime; }

protected:
	// 数据缓存
	std::map<int, std::shared_ptr<INodeData>> m_inputs;
	std::map<int, std::shared_ptr<INodeData>> m_outputs;

	bool m_lastResult;  // 上一次运行是否成功
	qint64 m_runTime;   // 运行耗时(ms)
};