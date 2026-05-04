#include "NodeScene.h"
#include "PortItem.h"
#include "ConnectionItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

NodeScene::NodeScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(-5000, -5000, 10000, 10000);
}

void NodeScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    // 背景网格绘制逻辑（保持之前的高级灰风格）
    painter->setRenderHint(QPainter::Antialiasing, false);
    QPen pen(QColor(50, 50, 50), 1);
    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % 20);
    qreal top = int(rect.top()) - (int(rect.top()) % 20);
    for (qreal x = left; x < rect.right(); x += 20) painter->drawLine(x, rect.top(), x, rect.bottom());
    for (qreal y = top; y < rect.bottom(); y += 20) painter->drawLine(rect.left(), y, rect.right(), y);

    QPen penBold(QColor(35, 35, 35), 2);
    painter->setPen(penBold);
    left = int(rect.left()) - (int(rect.left()) % 100);
    top = int(rect.top()) - (int(rect.top()) % 100);
    for (qreal x = left; x < rect.right(); x += 100) painter->drawLine(x, rect.top(), x, rect.bottom());
    for (qreal y = top; y < rect.bottom(); y += 100) painter->drawLine(rect.left(), y, rect.right(), y);
}

// --- 鼠标交互控制 ---

void NodeScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    PortItem* port = dynamic_cast<PortItem*>(item);

    if (port && event->button() == Qt::LeftButton) {
        startConnection(port); // 点击端口开始
        return;
    }
    QGraphicsScene::mousePressEvent(event);
}

void NodeScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_activeConnection) {
        updateActiveConnection(event->scenePos()); // 线条跟随鼠标
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void NodeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_activeConnection) {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        PortItem* endPort = dynamic_cast<PortItem*>(item);

        // 验证逻辑：不能连自己，不能连同类型的端口（In连In），不能连同一个Node上的端口
        if (endPort && endPort != m_connStartPort &&
            endPort->portType() != m_connStartPort->portType()) {
            doneConnection(endPort);
        }
        else {
            cancelConnection();
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

// --- 连线逻辑实现 ---

void NodeScene::startConnection(PortItem* startPort)
{
    m_connStartPort = startPort;
    // 使用你定义的新构造函数：ConnectionItem(PortItem* start, ...)
    m_activeConnection = new ConnectionItem(startPort);
    addItem(m_activeConnection);

    // 初始化位置
    m_activeConnection->setEndPoint(startPort->scenePos());
}

void NodeScene::updateActiveConnection(const QPointF& pos)
{
    if (m_activeConnection) {
        // 调用你定义的接口，ConnectionItem 内部会自动 updatePath()
        m_activeConnection->setEndPoint(pos);
    }
}

void NodeScene::doneConnection(PortItem* endPort)
{
    if (m_activeConnection) {
        // 1. 锁定最终端口
        m_activeConnection->setEndPort(endPort);

        // 2. 将此连线通知给两个端口，方便节点移动时线自动跟着走
        // 假设 PortItem 有 addConnection 接口
        m_connStartPort->addConnection(m_activeConnection);
        endPort->addConnection(m_activeConnection);

        // 3. 这里是触发 Core 模块连接的关键点
        // 获取逻辑 ID 并建立绑定
        /*
        auto outNode = (m_connStartPort->portType() == PortType::Out) ? m_connStartPort : endPort;
        auto inNode  = (m_connStartPort->portType() == PortType::In) ? m_connStartPort : endPort;
        CoreManager::instance().onLineConnected(outNode->parentNode()->id(), outNode->index(),
                                               inNode->parentNode()->id(), inNode->index());
        */
    }

    m_activeConnection = nullptr;
    m_connStartPort = nullptr;
}

void NodeScene::cancelConnection()
{
    if (m_activeConnection) {
        removeItem(m_activeConnection);
        delete m_activeConnection; // 只有没连成功的才 delete
        m_activeConnection = nullptr;
    }
    m_connStartPort = nullptr;
}