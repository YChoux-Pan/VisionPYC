#ifndef IMAGELISTVIEW_H
#define IMAGELISTVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QHeaderView>
#include <QPainter>
// 委派类放在头文件内部或作为私有类
class ImageListDelegate : public QStyledItemDelegate {
public:
	using QStyledItemDelegate::QStyledItemDelegate;
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	//bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
// --- 1. 自定义表头，用于绘制 Checkbox 和统一背景 ---
class ImageHeader : public QHeaderView {
	Q_OBJECT
public:
	ImageHeader(Qt::Orientation orientation, QWidget* parent = nullptr)
		: QHeaderView(orientation, parent) {
	}

	bool allChecked = false;

protected:
	void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override;
};
class ImageListView : public QTreeView {
	Q_OBJECT
public:
	explicit ImageListView(QWidget* parent = nullptr);
	// 排序类型枚举
	enum SortType {
		ByName,
		ByTime
	};

	// 新增排序接口
	void sortItems(SortType type, bool ascending = true);
	// 外部调用：传入路径列表
	void setImageList(const QStringList& filePaths);

	// 外部调用：获取哪些行被选中了
	QVector<bool> getCheckedStatus() const;

	void moveRowUp();
	void moveRowDown();

private slots:
	void onHeaderClicked(int logicalIndex);
	
private:
	QStandardItemModel* m_model;
	bool m_allChecked = false; // 记录全选状态
	void updateIndexColumn();
	QStringList m_currentFullPaths;
	void refreshModel();
signals:
	// 定义信号：当任何地方被点击时触发，或者仅当 Checkbox 以外的区域被点击时触发
	void itemClickedWithIndex(int row);

};

#endif