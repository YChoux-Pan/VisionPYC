#pragma once
#include <QGraphicsEllipseItem>
#include <QList>
#include "GlobalDef.h"

class NodeItem;
class ConnectionItem;

class PortItem : public QGraphicsEllipseItem {
public:
	PortItem(PortType type, QString name, NodeItem* parent);

	PortType portType() const { return m_type; }
	NodeItem* parentNode() const { return m_parentNode; }
	QString portName() const { return m_name; }

	// --- 连接管理 ---
	// 注册连线：当连线成功时，由 NodeScene 调用
	void addConnection(ConnectionItem* connection);
	// 移除连线：当连线被删除时调用
	void removeConnection(ConnectionItem* connection);
	// 通知所有相连的线更新位置
	void updateConnections();

	// 获取连接点的场景坐标（圆心位置）
	QPointF scenePos() const;

private:
	PortType m_type;
	NodeItem* m_parentNode;
	QString m_name;

	// 存储所有连接到此端口的线
	QList<ConnectionItem*> m_connections;

	// 样式参数
	const qreal m_radius = 5.0;

protected:
	// 鼠标悬停效果，增强交互感
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

	// 绘制端口名称等
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};