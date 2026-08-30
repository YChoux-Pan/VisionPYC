#ifndef IFLOWNODE_H
#define IFLOWNODE_H

#include <QJsonObject>
#include <QString>
#include <QVector>
#include <memory>
#include "INodeData.h"
#include "FlowPort.h"

class QWidget;

// 节点抽象接口：所有算法算子都必须实现此接口
class IFlowNode {
public:
	virtual ~IFlowNode() = default;

	// --- 身份标识 ---
	virtual QString typeKey() const = 0;      // 类型键（注册表 / 序列化用）
	virtual QString displayName() const = 0;  // 显示名称
	virtual QString category() const = 0;     // 分类，如 "图像处理"

	// --- 端口描述：驱动数据流自动串联 ---
	virtual QVector<FlowPort> inputPorts() const = 0;
	virtual QVector<FlowPort> outputPorts() const = 0;

	// --- 参数持久化（流程保存 / 加载）---
	virtual QJsonObject saveParams() const { return {}; }
	virtual void loadParams(const QJsonObject&) {}

	// --- 核心执行逻辑 ---
	// 返回 true 表示成功；失败时流程停止
	virtual bool process() = 0;

	// --- 数据访问 ---
	// 设置输入数据（由执行器按端口映射自动填充）
	virtual void setInput(int portIndex, std::shared_ptr<INodeData> data) = 0;
	// 获取输出数据（供下游节点使用）
	virtual std::shared_ptr<INodeData> getOutput(int portIndex) = 0;

	// --- 参数配置界面 ---
	virtual QWidget* createConfigWidget() { return nullptr; }

	// --- 状态查询 ---
	bool isSuccess() const { return m_lastResult; }
	qint64 elapsedMS() const { return m_runTime; }
	// 执行器统一写入耗时
	void setRunTime(qint64 ms) { m_runTime = ms; }

protected:
	bool m_lastResult = false; // 上一次运行是否成功
	qint64 m_runTime = 0;      // 运行耗时(ms)
};

#endif // IFLOWNODE_H