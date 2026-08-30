#pragma once
#include "BaseAlgorithmNode.h"

// 图像检测类算子：图像预处理 / ROI设置 / 采集图像
// 通过注册宏 REGISTER_NODE 以多个 typeKey 注册同一实现
class ImageFilterNode : public BaseAlgorithmNode {
public:
	explicit ImageFilterNode(QString subType = QString());

	QString typeKey() const override { return m_subType; }
	QString displayName() const override { return m_subType; }
	QString category() const override { return "图像检测"; }

	QVector<FlowPort> inputPorts() const override;
	QVector<FlowPort> outputPorts() const override;

	bool process() override;
	QWidget* createConfigWidget() override;
	QJsonObject saveParams() const override;
	void loadParams(const QJsonObject&) override;

private:
	QString m_subType;               // 具体小模块身份（typeKey）
	QWidget* m_cachedWidget = nullptr; // 缓存已创建的配置界面，避免重复创建
};
