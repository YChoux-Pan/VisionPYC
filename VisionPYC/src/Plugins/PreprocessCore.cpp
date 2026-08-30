#include "PreprocessCore.h"
#include <QVariant>

static void toGray(const cv::Mat& src, cv::Mat& gray)
{
	if (src.channels() == 3)
		cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	else if (src.channels() == 4)
		cv::cvtColor(src, gray, cv::COLOR_BGRA2GRAY);
	else
		gray = src.clone();
}

QJsonObject preprocessParamsToJson(const PreprocessParams& p)
{
	QJsonObject obj;
	obj["command"] = p.command;
	obj["grayMode"] = p.grayMode;
	obj["flipCode"] = p.flipCode;
	obj["rotateCode"] = p.rotateCode;
	obj["scale"] = p.scale;
	obj["width"] = p.width;
	obj["height"] = p.height;
	obj["kernelSize"] = p.kernelSize;
	obj["sigma"] = p.sigma;
	obj["morphKernel"] = p.morphKernel;
	obj["morphIterations"] = p.morphIterations;
	obj["alpha"] = p.alpha;
	obj["beta"] = p.beta;
	obj["threshold"] = p.threshold;
	obj["maxVal"] = p.maxVal;
	obj["binaryType"] = p.binaryType;
	obj["adaptiveKernel"] = p.adaptiveKernel;
	obj["adaptiveOffset"] = p.adaptiveOffset;
	return obj;
}

PreprocessParams preprocessParamsFromJson(const QJsonObject& obj)
{
	PreprocessParams p;
	p.command = obj.value("command").toString(p.command);
	p.grayMode = obj.value("grayMode").toInt(p.grayMode);
	p.flipCode = obj.value("flipCode").toInt(p.flipCode);
	p.rotateCode = obj.value("rotateCode").toInt(p.rotateCode);
	p.scale = obj.value("scale").toDouble(p.scale);
	p.width = obj.value("width").toInt(p.width);
	p.height = obj.value("height").toInt(p.height);
	p.kernelSize = obj.value("kernelSize").toInt(p.kernelSize);
	p.sigma = obj.value("sigma").toDouble(p.sigma);
	p.morphKernel = obj.value("morphKernel").toInt(p.morphKernel);
	p.morphIterations = obj.value("morphIterations").toInt(p.morphIterations);
	p.alpha = obj.value("alpha").toDouble(p.alpha);
	p.beta = obj.value("beta").toDouble(p.beta);
	p.threshold = obj.value("threshold").toInt(p.threshold);
	p.maxVal = obj.value("maxVal").toInt(p.maxVal);
	p.binaryType = obj.value("binaryType").toInt(p.binaryType);
	p.adaptiveKernel = obj.value("adaptiveKernel").toInt(p.adaptiveKernel);
	p.adaptiveOffset = obj.value("adaptiveOffset").toInt(p.adaptiveOffset);
	return p;
}

bool applyPreprocess(const cv::Mat& src, const PreprocessParams& p, cv::Mat& dst)
{
	if (src.empty()) return false;

	const QString cmd = p.command;

	if (cmd == "灰度处理") {
		if (p.grayMode == 0) {
			toGray(src, dst);
		}
		else {
			cv::Mat gray;
			toGray(src, gray);
			cv::cvtColor(gray, dst, cv::COLOR_GRAY2BGR);
		}
	}
	else if (cmd == "图像镜像") {
		cv::flip(src, dst, p.flipCode);
	}
	else if (cmd == "图像旋转") {
		const int code = ((p.rotateCode % 3) + 3) % 3;
		if (code == 0)      cv::rotate(src, dst, cv::ROTATE_90_CLOCKWISE);
		else if (code == 1) cv::rotate(src, dst, cv::ROTATE_180);
		else                cv::rotate(src, dst, cv::ROTATE_90_COUNTERCLOCKWISE);
	}
	else if (cmd == "深度转彩色") {
		cv::Mat gray;
		toGray(src, gray);
		cv::Mat normalized;
		cv::normalize(gray, normalized, 0, 255, cv::NORM_MINMAX, CV_8U);
		cv::applyColorMap(normalized, dst, cv::COLORMAP_JET);
	}
	else if (cmd == "修改尺寸") {
		cv::Size sz;
		if (p.width > 0 && p.height > 0) {
			sz = cv::Size(p.width, p.height);
		}
		else {
			sz = cv::Size(
				std::max(1, static_cast<int>(std::lround(src.cols * p.scale))),
				std::max(1, static_cast<int>(std::lround(src.rows * p.scale))));
		}
		cv::resize(src, dst, sz, 0, 0, cv::INTER_LINEAR);
	}
	else if (cmd == "均值滤波") {
		const int k = std::max(1, p.kernelSize | 1);
		cv::blur(src, dst, cv::Size(k, k));
	}
	else if (cmd == "中值滤波") {
		const int k = std::max(1, p.kernelSize | 1);
		cv::medianBlur(src, dst, k);
	}
	else if (cmd == "高斯滤波") {
		const int k = std::max(1, p.kernelSize | 1);
		cv::GaussianBlur(src, dst, cv::Size(k, k), p.sigma);
	}
	else if (cmd == "灰度膨胀" || cmd == "灰度腐蚀" ||
		cmd == "灰度开运算" || cmd == "灰度闭运算") {
		const int k = std::max(1, p.morphKernel | 1);
		const cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(k, k));
		const int iters = std::max(1, p.morphIterations);
		if (cmd == "灰度膨胀")      cv::dilate(src, dst, kernel, cv::Point(-1, -1), iters);
		else if (cmd == "灰度腐蚀") cv::erode(src, dst, kernel, cv::Point(-1, -1), iters);
		else if (cmd == "灰度开运算") cv::morphologyEx(src, dst, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), iters);
		else                        cv::morphologyEx(src, dst, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), iters);
	}
	else if (cmd == "锐化") {
		cv::Mat blurred;
		cv::GaussianBlur(src, blurred, cv::Size(0, 0), 3);
		cv::addWeighted(src, 1.8, blurred, -0.8, 0, dst);
	}
	else if (cmd == "对比度") {
		src.convertTo(dst, -1, p.alpha, p.beta);
	}
	else if (cmd == "亮度调节") {
		src.convertTo(dst, -1, 1.0, p.beta);
	}
	else if (cmd == "反色") {
		if (src.channels() == 1) {
			cv::bitwise_not(src, dst);
		}
		else {
			cv::Mat gray;
			toGray(src, gray);
			cv::bitwise_not(gray, dst);
		}
	}
	else if (cmd == "边缘增强") {
		cv::Mat gray;
		toGray(src, gray);
		cv::Mat edges;
		const int k = std::max(1, p.kernelSize | 1);
		cv::Laplacian(gray, edges, CV_8U, k);
		cv::addWeighted(gray, 1.0, edges, 1.0, 0, dst);
	}
	else if (cmd == "二值化") {
		cv::Mat gray;
		toGray(src, gray);
		const int type = (p.binaryType == 0) ? cv::THRESH_BINARY : cv::THRESH_BINARY_INV;
		cv::threshold(gray, dst, p.threshold, p.maxVal, type);
	}
	else if (cmd == "均值二值化") {
		cv::Mat gray;
		toGray(src, gray);
		const int k = std::max(3, p.adaptiveKernel | 1);
		cv::adaptiveThreshold(gray, dst, 255,
			cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, k, p.adaptiveOffset);
	}
	else if (cmd == "彩色二值化") {
		cv::Mat gray;
		toGray(src, gray);
		cv::threshold(gray, dst, p.threshold, p.maxVal, cv::THRESH_BINARY);
	}
	else {
		// 未知算子：透传
		dst = src.clone();
	}
	return !dst.empty();
}
