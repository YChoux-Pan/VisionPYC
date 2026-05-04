#pragma once

#include <QGraphicsScene>
#include <QUuid>

class NodeItem;
class PortItem;
class ConnectionItem;

class NodeScene : public QGraphicsScene {
	Q_OBJECT
public:
	explicit NodeScene(QObject* parent = nullptr);

	// 连线生命周期管理
	void startConnection(PortItem* startPort);
	void updateActiveConnection(const QPointF& pos);
	void doneConnection(PortItem* endPort);
	void cancelConnection();

protected:
	// 背景绘制
	void drawBackground(QPainter* painter, const QRectF& rect) override;

	// 交互事件处理
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
	ConnectionItem* m_activeConnection = nullptr; // 当前正在拉的线
	PortItem* m_connStartPort = nullptr;          // 起点端口
};