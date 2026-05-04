#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#include <QColor>
#include <QString>

// 端口类型：输入或输出
enum class PortType {
	In,
	Out
};

// 数据类型定义：决定了哪些线可以连接
enum class DataType {
	None,
	Image,    // 图像数据
	Int,      // 整数（如计数结果）
	Double,   // 浮点数（如测量坐标）
	String,   // 字符串（如OCR识别结果）
	Boolean   // 布尔值（如OK/NG判断）
};

namespace Style {
	// 节点基础属性
	const float NodeWidth = 160.0f;
	const float NodeTitleHeight = 35.0f;
	const float NodeRadius = 8.0f;

	// 端口属性
	const float PortRadius = 6.0f;
	const float PortOffset = 10.0f; // 端口距离边界的偏移

	// 颜色配置
	const QColor NodeBackgroundColor(45, 45, 45, 230);
	const QColor NodeSelectedBorderColor(255, 165, 0); // 选中时橙色边框
	const QColor ConnectionColor(180, 180, 180);
	const QColor TextColor(220, 220, 220);
}

#endif // GLOBALDEF_H

