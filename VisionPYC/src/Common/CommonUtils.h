#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QPointF>
#include <cmath>

class CommonUtils {
public:
	// 计算贝塞尔曲线所需的两点间距离
	static float getDistance(const QPointF& p1, const QPointF& p2) {
		return std::sqrt(std::pow(p1.x() - p2.x(), 2) + std::pow(p1.y() - p2.y(), 2));
	}

	// 生成唯一 ID (UUID)，用于标识每个节点实例
	static QString generateUUID();
};

#endif // COMMONUTILS_H