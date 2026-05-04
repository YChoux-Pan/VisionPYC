#pragma once
#include <QGraphicsPathItem>
#include <QPen>

class PortItem;

class ConnectionItem : public QGraphicsPathItem {
public:
	ConnectionItem(PortItem* start, QGraphicsItem* parent = nullptr);

	// 设置/更新终点端口
	void setEndPort(PortItem* end);

	// 如果还没连上端口，可以设置一个临时的终点坐标（随鼠标移动）
	void setEndPoint(const QPointF& point);

	// 核心绘制逻辑
	void updatePath();

	// 获取起始/结束端口，用于逻辑层判断
	PortItem* startPort() const { return m_startPort; }
	PortItem* endPort() const { return m_endPort; }

private:
	PortItem* m_startPort = nullptr;
	PortItem* m_endPort = nullptr;
	QPointF m_endPos; // 临时终点坐标
};