#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class NodeView : public QGraphicsView {
	Q_OBJECT
public:
	using QGraphicsView::QGraphicsView; // 使用基类构造函数

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dropEvent(QDropEvent* event) override;
};