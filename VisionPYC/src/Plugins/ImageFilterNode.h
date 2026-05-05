#pragma once
#include "BaseAlgorithmNode.h"

class ImageFilterNode : public BaseAlgorithmNode {
public:
	// 构造时传入小模块的名称 (例如 "GaussianBlur" 或 "Threshold")
	explicit ImageFilterNode(QString subType);

	QString category() const override { return "图像处理"; }
	QString modelName() const override { return m_subType; }

	// 核心中转：运行算法
	void process() override;

	// 核心中转：获取对应的 UI 控件
	QWidget* getConfigWidget() override;

private:
	QString m_subType;        // 记录具体的小模块身份
	QWidget* m_cachedWidget = nullptr; // 缓存已经创建的 UI，避免重复创建
};