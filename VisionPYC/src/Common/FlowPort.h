#pragma once

#include <QString>
#include "GlobalDef.h"

// 端口方向
enum class PortDirection {
	In,   // 输入端口
	Out   // 输出端口
};

// 端口描述：定义算子的输入/输出接口，驱动数据流自动串联
struct FlowPort {
	QString name;            // 端口名称，如 "输入图像"
	DataType type;           // 数据类型，如 DataType::Image
	PortDirection direction; // 方向
};
