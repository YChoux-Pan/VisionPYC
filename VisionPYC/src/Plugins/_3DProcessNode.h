
#pragma once
#include "BaseAlgorithmNode.h"

// 3D 检测类算子：高度检测 / 平面度检测
// 通过注册宏 REGISTER_NODE 以多个 typeKey 注册同一实现
class _3DProcessNode : public BaseAlgorithmNode {
public:
	explicit _3DProcessNode(QString subType = QString());

	QString typeKey() const override { return m_subType; }
	QString displayName() const override { return m_subType; }
	QString category() const override { return "3D检测"; }

	QVector<FlowPort> inputPorts() const override;
	QVector<FlowPort> outputPorts() const override;

	bool process() override;
	QWidget* createConfigWidget() override;
	QJsonObject saveParams() const override;
	void loadParams(const QJsonObject&) override;

private:
	QString m_subType;
	QWidget* m_cachedWidget = nullptr;
};
