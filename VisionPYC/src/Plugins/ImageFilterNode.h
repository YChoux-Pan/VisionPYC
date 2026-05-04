#pragma once
#include "BaseAlgorithmNode.h"

class ImageFilterNode : public BaseAlgorithmNode {
public:
	ImageFilterNode();

	// 实现 Common 定义的接口
	QString category() const override { return "图像处理"; }
	QString modelName() const override { return "GaussianBlur"; }

	// 实现核心算法
	void process() override;

private:
	// 可以在这里添加具体的算法参数，如内核大小
	int m_kernelSize = 5;
};