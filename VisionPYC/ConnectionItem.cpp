#include "ConnectionItem.h"
#include "PortItem.h"
#include "GlobalDef.h"
#include <QPainterPath>
#include <QPainter>

ConnectionItem::ConnectionItem(PortItem* start, QGraphicsItem* parent)
	: QGraphicsPathItem(parent), m_startPort(start)
{
	// 设置线条样式
	QPen pen(Style::ConnectionColor, 3); // 使用 Common 定义的颜色
	pen.setCapStyle(Qt::RoundCap);
	setPen(pen);

	// 确保线条在节点下方
	setZValue(-1);

	updatePath();
}

void ConnectionItem::setEndPort(PortItem* end) {
	m_endPort = end;
	updatePath();
}

void ConnectionItem::setEndPoint(const QPointF& point) {
	m_endPos = point;
	updatePath();
}

void ConnectionItem::updatePath() {
	if (!m_startPort) return;

	// 1. 获取起点坐标（场景坐标）
	QPointF startPos = m_startPort->scenePos();

	// 2. 获取终点坐标
	// 如果已经连上了端口，取端口位置；否则取鼠标移动的临时位置
	QPointF endPos = m_endPort ? m_endPort->scenePos() : m_endPos;

	// 3. 计算贝塞尔曲线
	QPainterPath path;
	path.moveTo(startPos);

	// 计算控制点逻辑：
	// 让曲线在水平方向上有一定的延伸感，延伸长度取两点间距离的一半，但要有最小值约束
	qreal dx = endPos.x() - startPos.x();
	qreal dy = endPos.y() - startPos.y();

	// 这里的 0.5 是平滑度系数，可以根据视觉需求调整
	qreal ctrlX = qAbs(dx) * 0.5;
	if (ctrlX < 50) ctrlX = 50; // 保证即使垂直排列也有弧度

	// 控制点 1：从起点水平向右（或向左，取决于端口类型）
	QPointF ctrl1 = startPos + QPointF(ctrlX, 0);
	// 控制点 2：从终点水平向左
	QPointF ctrl2 = endPos - QPointF(ctrlX, 0);

	// 绘制三次贝塞尔曲线
	path.cubicTo(ctrl1, ctrl2, endPos);

	setPath(path);
}