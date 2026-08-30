#pragma once
#include "BaseAlgorithmNode.h"
#include "PreprocessCore.h"
#include <QMutex>

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

	// --- 预处理参数（供配置界面读写，GUI 线程）---
	PreprocessParams& preParams() { return m_preParams; }
	// 线程安全快照（供 worker 线程 process 读取）
	PreprocessParams paramsSnapshot() const;
	void setParams(const PreprocessParams& p);

	// --- 图像缓存（供配置界面预览，线程安全）---
	cv::Mat previewInput() const;    // 上次流程运行时的输入图像
	cv::Mat previewOutput() const;   // 上次流程运行时的输出图像
	void setPreviewInput(const cv::Mat& img);
	void setPreviewOutput(const cv::Mat& img);

private:
	QString m_subType;                 // 具体小模块身份（typeKey）
	QWidget* m_cachedWidget = nullptr; // 缓存已创建的配置界面
	PreprocessParams m_preParams;      // 预处理参数模型

	mutable QMutex m_imgMutex;         // 保护预览图像缓存
	mutable QMutex m_paramMutex;       // 保护预处理参数（GUI 写 / worker 读）
	cv::Mat m_lastInput;
	cv::Mat m_lastOutput;
};

