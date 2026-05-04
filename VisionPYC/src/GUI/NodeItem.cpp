#include "NodeItem.h"
#include "PortItem.h"
#include "ConnectionItem.h"
#include <QPainter>
#include <QLinearGradient>

NodeItem::NodeItem(QString title, QGraphicsItem* parent)
	: QGraphicsPathItem(parent), m_title(title)
{
	m_id = QUuid::createUuid();

	// 默认初始大小
	m_rect = QRectF(0, 0, Style::NodeWidth, 100); // 高度会根据端口数量动态调整

	// 设置标志位：可移动、可选择、发送几何改变通知
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges);

	setZValue(1); // 确保节点在连线之上
}

NodeItem::~NodeItem() {
	// 析构时，由于端口是子 Item，Qt 会自动删除它们
}

PortItem* NodeItem::addPort(QString name, PortType type) {
	PortItem* port = new PortItem(type, name, this);
	m_ports.append(port);
	updatePortsLayout(); // 每加一个端口，重新排版
	return port;
}

void NodeItem::updatePortsLayout() {
	int inCount = 0;
	int outCount = 0;
	float spacing = 25.0f; // 端口间距

	for (auto port : m_ports) {
		if (port->portType() == PortType::In) {
			// 输入端口排在左侧
			port->setPos(0, Style::NodeTitleHeight + (inCount + 1) * spacing);
			inCount++;
		}
		else {
			// 输出端口排在右侧
			port->setPos(m_rect.width(), Style::NodeTitleHeight + (outCount + 1) * spacing);
			outCount++;
		}
	}

	// 根据端口数量动态调整节点高度
	float newHeight = Style::NodeTitleHeight + (qMax(inCount, outCount) + 1) * spacing + 10;
	m_rect.setHeight(newHeight);
	prepareGeometryChange(); // 通知场景大小改变
}

QRectF NodeItem::boundingRect() const {
	// 包含描边宽度
	return m_rect.adjusted(-2, -2, 2, 2);
}

void NodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
	Q_UNUSED(option);
	painter->setRenderHint(QPainter::Antialiasing);

	// 1. 绘制背景（渐变效果更显高级）
	QLinearGradient grad(m_rect.topLeft(), m_rect.bottomLeft());
	grad.setColorAt(0, QColor(60, 60, 60));
	grad.setColorAt(1, QColor(40, 40, 40));

	painter->setPen(QPen(QColor(20, 20, 20), 1));
	painter->setBrush(grad);
	painter->drawRoundedRect(m_rect, Style::NodeRadius, Style::NodeRadius);

	// 2. 绘制标题栏背景
	QRectF titleRect(0, 0, m_rect.width(), Style::NodeTitleHeight);
	QPainterPath titlePath;

	// 技巧：移动到左下角，顺时针画线
	titlePath.moveTo(0, titleRect.height()); // 左下角
	titlePath.lineTo(0, Style::NodeRadius);  // 向上画到圆角开始处

	// 画左上角圆角 (矩形区域, 起始角度, 跨越角度)
	// 角度以 3 点钟方向为 0 度，逆时针为正。180 度是左侧，90 度是正上方
	titlePath.arcTo(0, 0, Style::NodeRadius * 2, Style::NodeRadius * 2, 180, -90);

	// 画右上角圆角
	titlePath.arcTo(titleRect.width() - Style::NodeRadius * 2, 0,
		Style::NodeRadius * 2, Style::NodeRadius * 2, 90, -90);

	titlePath.lineTo(titleRect.width(), titleRect.height()); // 右下角
	titlePath.closeSubpath(); // 闭合路径（自动连回左下角）

	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(30, 30, 30));
	painter->drawPath(titlePath);

	// 3. 绘制标题文字
	painter->setPen(Qt::white);
	QFont font = painter->font();
	font.setBold(true);
	painter->setFont(font);
	painter->drawText(titleRect.adjusted(10, 0, 0, 0), Qt::AlignVCenter, m_title);

	// 4. 选中状态高亮边框
	if (isSelected()) {
		painter->setPen(QPen(Style::NodeSelectedBorderColor, 2));
		painter->setBrush(Qt::NoBrush);
		painter->drawRoundedRect(m_rect, Style::NodeRadius, Style::NodeRadius);
	}
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant& value) {
	if (change == ItemPositionHasChanged) {
		// 【核心逻辑】节点移动时，找到所有连接在端口上的线，通知它们重新计算路径
		for (auto port : m_ports) {
			port->updateConnections();
		}
	}
	return QGraphicsPathItem::itemChange(change, value);
}