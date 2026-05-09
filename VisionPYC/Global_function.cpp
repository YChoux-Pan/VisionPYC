#include "Global_function.h"
#include <windows.h>


// 同时获取 Mat 和 QImage 的高效函数
bool loadAndPrepareImage(const QString& filePath, cv::Mat& outMat, QImage& outImage) {
	// 1. 使用 QFile 读取，彻底规避中文路径问题
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "无法打开文件:" << filePath;
		return false;
	}
	QByteArray data = file.readAll();
	file.close();

	// 2. OpenCV 内存解码
	// 将 QByteArray 转为 std::vector 给 OpenCV 使用
	std::vector<uchar> buffer(data.begin(), data.end());
	outMat = cv::imdecode(buffer, cv::IMREAD_COLOR); // 解码为 BGR 格式

	if (outMat.empty()) {
		qDebug() << "图片解码失败";
		return false;
	}

	// 3. 将 Mat 转换为 QImage 用于显示
	// 注意：OpenCV 是 BGR，Qt 默认是 RGB，需要转换通道
	cv::Mat rgbMat;
	cv::cvtColor(outMat, rgbMat, cv::COLOR_BGR2RGB);

	// 使用 .copy() 确保 QImage 拥有独立内存，防止后续 Mat 处理影响显示
	outImage = QImage(rgbMat.data, rgbMat.cols, rgbMat.rows,
		static_cast<int>(rgbMat.step),
		QImage::Format_RGB888).copy();

	return true;
}
