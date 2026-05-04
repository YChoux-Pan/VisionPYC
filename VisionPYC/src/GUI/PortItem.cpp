#include "PortItem.h"
#include "NodeItem.h"
#include "ConnectionItem.h"
#include <QBrush>
#include <QPen>
#include <QPainter>

PortItem::PortItem(PortType type, QString name, NodeItem* parent)
	: QGraphicsEllipseItem(parent), m_type(type), m_name(name), m_parentNode(parent)
{
	// 设置圆形形状 (以圆心为原点)
	setRect(-m_radius, -m_radius, m_radius * 2, m_radius * 2);

	// 初始样式
	setBrush(QColor(150, 150, 150));
	setPen(QPen(Qt::black, 1));

	// 开启悬停事件响应
	setAcceptHoverEvents(true);
}

QPointF PortItem::scenePos() const {
	// 将端口自身的中心点(0,0)转换为场景全局坐标
	return mapToScene(0, 0);
}

void PortItem::addConnection(ConnectionItem* connection) {
	if (connection && !m_connections.contains(connection)) {
		m_connections.append(connection);
	}
}

void PortItem::removeConnection(ConnectionItem* connection) {
	m_connections.removeAll(connection);
}

void PortItem::updateConnections() {
	// 遍历所有关联的线，要求它们重新计算贝塞尔曲线
	for (auto conn : m_connections) {
		conn->updatePath();
	}
}

void PortItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
	// 悬停时变色，暗示用户这里可以点击连线
	setBrush(QColor(0, 255, 0));
	update();
	QGraphicsEllipseItem::hoverEnterEvent(event);
}

void PortItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
	setBrush(QColor(150, 150, 150));
	update();
	QGraphicsEllipseItem::hoverLeaveEvent(event);
}

void PortItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	// 先画圆点
	QGraphicsEllipseItem::paint(painter, option, widget);

	// 在圆点旁边画出端口名称（UI 细节）
	painter->setPen(Qt::white);
	QFont font = painter->font();
	font.setPointSize(8);
	painter->setFont(font);

	if (m_type == PortType::In) {
		// 输入端口文字在右边
		painter->drawText(m_radius + 5, m_radius, m_name);
	}
	else {
		// 输出端口文字在左边（右对齐逻辑需计算宽度，这里简化处理）
		painter->drawText(-m_radius - 50, m_radius, m_name);
	}
}