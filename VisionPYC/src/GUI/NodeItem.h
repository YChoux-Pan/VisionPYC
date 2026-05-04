#pragma once

#include <QGraphicsPathItem>
#include <QList>
#include <QUuid>
#include "GlobalDef.h"

class PortItem;
class ConnectionItem;

class NodeItem : public QGraphicsPathItem {
public:
	NodeItem(QString title, QGraphicsItem* parent = nullptr);
	~NodeItem();

	// 基础属性
	QUuid id() const { return m_id; }
	QRectF rect() const { return m_rect; }

	// 端口管理
	PortItem* addPort(QString name, PortType type);
	QList<PortItem*> ports() const { return m_ports; }

	// 绘图与事件
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	QRectF boundingRect() const override;

protected:
	// 核心交互：监听位置改变以更新连线
	QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
	void updatePortsLayout(); // 自动排列端口位置

	QUuid m_id;
	QString m_title;
	QRectF m_rect;
	QList<PortItem*> m_ports;
};