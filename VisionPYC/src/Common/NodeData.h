#pragma once

#include <opencv2/opencv.hpp>
#include "INodeData.h"

// 图像数据：节点间传递的 cv::Mat
class ImageData : public INodeData {
public:
	DataType type() const override { return DataType::Image; }
	QString typeName() const override { return QStringLiteral("cv::Mat"); }
	QVariant value() const override { return {}; }   // Mat 不适合进 QVariant

	cv::Mat image;   // 实际图像数据
};

// 标量数据：承载 Int / Double / String / Boolean 类型
class ScalarData : public INodeData {
public:
	ScalarData() = default;
	explicit ScalarData(DataType t, QVariant v) : m_type(t), m_value(std::move(v)) {}

	DataType type() const override { return m_type; }
	QVariant value() const override { return m_value; }
	QString typeName() const override {
		switch (m_type) {
		case DataType::Int:     return QStringLiteral("Int");
		case DataType::Double:  return QStringLiteral("Double");
		case DataType::String:  return QStringLiteral("String");
		case DataType::Boolean: return QStringLiteral("Boolean");
		default:                return QStringLiteral("Scalar");
		}
	}

private:
	DataType m_type = DataType::None;
	QVariant m_value;
};
