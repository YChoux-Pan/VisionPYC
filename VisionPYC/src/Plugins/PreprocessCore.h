#pragma once

#include <QJsonObject>
#include <QString>
#include <opencv2/opencv.hpp>

// 图像预处理参数模型（节点侧持久化，与 UI 解耦）
struct PreprocessParams {
	QString command = "灰度处理";  // 算子名（与菜单显示名一致）

	// 灰度处理
	int grayMode = 0;              // 0: BGR→GRAY  1: 保留三通道(GRAY→BGR)
	// 图像镜像
	int flipCode = 1;              // 0: 垂直翻转  1: 水平翻转  -1: 双向
	// 图像旋转
	int rotateCode = 0;            // 0: 顺时针90  1: 180  2: 逆时针90
	// 修改尺寸
	double scale = 1.0;            // 缩放比例
	int width = 0;                 // 指定宽（>0 生效）
	int height = 0;                // 指定高（>0 生效）
	// 滤波
	int kernelSize = 3;            // 核尺寸 3/5/7
	double sigma = 1.0;            // 高斯滤波 σ
	// 形态学
	int morphKernel = 3;           // 形态学核尺寸
	int morphIterations = 1;       // 迭代次数
	// 增强
	double alpha = 1.2;            // 对比度系数
	double beta = 0.0;             // 亮度增量
	// 二值化
	int threshold = 128;           // 阈值
	int maxVal = 255;              // 最大值
	int binaryType = 0;            // 0: THRESH_BINARY  1: THRESH_BINARY_INV
	int adaptiveKernel = 11;       // 自适应二值化核
	int adaptiveOffset = 5;        // 自适应二值化常量
};

// 参数序列化 / 反序列化
QJsonObject preprocessParamsToJson(const PreprocessParams& p);
PreprocessParams preprocessParamsFromJson(const QJsonObject& obj);

// 预处理算法核心：根据 p.command 执行对应 OpenCV 算子
// 返回 true 表示成功，结果写入 dst
bool applyPreprocess(const cv::Mat& src, const PreprocessParams& p, cv::Mat& dst);
