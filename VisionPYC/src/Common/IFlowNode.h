#ifndef IFLOWNODE_H
#define IFLOWNODE_H

#include <QString>
#include <QVector>
#include <memory>
#include "INodeData.h"

class IFlowNode {
public:
	virtual ~IFlowNode() {}

	// --- 基础信息 ---
	virtual QString category() const = 0;  // 返回分类：如 "图像处理"
	virtual QString modelName() const = 0; // 返回模型名称：如 "边缘检测"

	// --- 核心执行逻辑 ---
	// process 是算法执行的主体
	virtual void process() = 0;

	// --- 输入输出管理 ---
	// 设置输入数据（由上一个节点通过连线传来）
	virtual void setInputData(int portIndex, std::shared_ptr<INodeData> data) = 0;

	// 获取输出数据（供下一个节点使用）
	virtual std::shared_ptr<INodeData> getOutputData(int portIndex) = 0;

	// --- 状态查询 ---
	bool isSuccess() const { return m_lastResult; }
	long long elapsedMS() const { return m_runTime; }

protected:
	bool m_lastResult = false; // 上一次运行是否 OK
	long long m_runTime = 0;   // 运行耗时
};

#endif // IFLOWNODE_H