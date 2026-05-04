#ifndef INODEDATA_H
#define INODEDATA_H

#include <QVariant>
#include "GlobalDef.h"

// 节点间传输的数据包装器
class INodeData {
public:
	virtual ~INodeData() {}

	// 获取当前数据的类型
	virtual DataType type() const = 0;

	// 将数据转换为 QVariant 以便通用处理
	virtual QVariant value() const = 0;

	// 获取类型名称（用于 UI 显示，如 "cv::Mat"）
	virtual QString typeName() const = 0;
};

#endif // INODEDATA_H