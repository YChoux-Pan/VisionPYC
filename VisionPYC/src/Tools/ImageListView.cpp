#include "ImageListView.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFileInfo>
#include <QHeaderView>
#include <QCheckBox>
#include <algorithm>




// --- Delegate 实现 ---
void ImageListDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	QStyleOptionViewItem opt = option;
	this->initStyleOption(&opt, index);

	painter->save();

	// 背景处理
	if (option.state & QStyle::State_Selected) {
		painter->fillRect(option.rect, QColor("#2d5a3a"));
	}
	else if (option.state & QStyle::State_MouseOver) {
		painter->fillRect(option.rect, QColor("#2a2a2a"));
	}

	// 第一列：CheckBox
	if (index.column() == 0) {
		bool checked = index.data(Qt::CheckStateRole).toInt() == Qt::Checked;
		int side = 16;
		QRect box(option.rect.center().x() - side / 2, option.rect.center().y() - side / 2, side, side);
		painter->setPen(QPen(checked ? QColor("#00CC66") : Qt::gray, 1));
		painter->drawRect(box);
		if (checked) painter->fillRect(box.adjusted(3, 3, -3, -3), QColor("#00CC66"));
	}
	// 第二列：索引（居中）
	else if (index.column() == 1) {
		painter->setPen(QColor("#888888"));
		painter->drawText(option.rect, Qt::AlignCenter, index.data(Qt::DisplayRole).toString());
	}
	// 第三列：名称（左对齐）
	else if (index.column() == 2) {
		painter->setPen(QColor("#cccccc"));
		painter->drawText(option.rect.adjusted(10, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, index.data(Qt::DisplayRole).toString());
	}

	painter->restore();
}

//bool ImageListDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) {
//	if (event->type() == QEvent::MouseButtonPress) {
//		QMouseEvent* me = static_cast<QMouseEvent*>(event);
//		int unit = option.rect.width() / 8;
//		if (me->pos().x() < option.rect.x() + unit) {
//			bool checked = index.data(Qt::CheckStateRole).toInt() == Qt::Checked;
//			model->setData(index, checked ? Qt::Unchecked : Qt::Checked, Qt::CheckStateRole);
//			return true;
//		}
//
//		
//
//		// 2. 无论点击哪里，或者你只想在点击非 Checkbox 区域时返回索引
//		// 我们通过 option.widget 找回父级 ListView 并发射信号
//		auto* listView = qobject_cast<ImageListView*>(const_cast<QWidget*>(option.widget));
//		if (listView) {
//			emit listView->itemClickedWithIndex(index.row());
//		}
//	}
//	return QStyledItemDelegate::editorEvent(event, model, option, index);
//}

QSize ImageListDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
	// 获取完整路径文本

	// 根据文字长度计算宽度，确保滚动条逻辑正常

	

	QString path = index.data(Qt::DisplayRole).toString();

	// 计算文本宽度 (使用当前字体的度量信息)
	int textWidth = option.fontMetrics.horizontalAdvance(path);

	// 根据 1:1:6 比例，如果文本占 6 份，总宽度应该是 (textWidth / 6) * 8
	// 我们再加一些额外的缓冲空间 (如 40px)
	//int totalWidth = (textWidth * 8 / 6) + 40;
	int totalWidth = qMax(option.rect.width(), (textWidth * 8 / 6) + 60);
	// 返回一个足够大的宽度，只有当这个宽度 > ListView 实际宽度时，水平滚动条才会出现
	return QSize(totalWidth, 32);
	
	
	
}

// --- ListView 实现 ---
ImageListView::ImageListView(QWidget* parent) : QTreeView(parent) {
	m_model = new QStandardItemModel(this);
	m_model->setColumnCount(3);
	m_model->setHeaderData(0, Qt::Horizontal, "");
	m_model->setHeaderData(1, Qt::Horizontal, "索引");
	m_model->setHeaderData(2, Qt::Horizontal, "名称");

	this->setModel(m_model);
	this->setItemDelegate(new ImageListDelegate(this));

	// 使用自定义表头
	ImageHeader* myHeader = new ImageHeader(Qt::Horizontal, this);
	this->setHeader(myHeader);

	// 配置表头尺寸
	this->header()->setSectionResizeMode(0, QHeaderView::Fixed);
	this->header()->resizeSection(0, 40);
	this->header()->setSectionResizeMode(1, QHeaderView::Fixed);
	this->header()->resizeSection(1, 60);
	this->header()->setSectionResizeMode(2, QHeaderView::Stretch);

	// --- 关键优化点：选择模式 ---
	// 如果你想通过鼠标拖拽或 Ctrl 选中多行高亮，使用 ExtendedSelection
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);

	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setMouseTracking(true);
	this->setIndentation(0);
	this->setRootIsDecorated(false);
	this->header()->setSectionsClickable(true);
	// 连接表头点击信号
	connect(this->header(), &QHeaderView::sectionClicked, this, &ImageListView::onHeaderClicked);

	// 点击行发射信号 (这里修正为只在点击内容时触发)
	connect(this, &QTreeView::clicked, [this](const QModelIndex& index) {
		// 如果点击的是第一列内容区，切换该行的勾选状态
		if (index.column() == 0) {
			bool isChecked = m_model->data(index, Qt::CheckStateRole).toInt() == Qt::Checked;
			m_model->setData(index, isChecked ? Qt::Unchecked : Qt::Checked, Qt::CheckStateRole);
		}
		emit itemClickedWithIndex(index.row());
		});
}

void ImageListView::sortItems(SortType type, bool ascending)
{
	if (m_currentFullPaths.isEmpty()) return;

	std::sort(m_currentFullPaths.begin(), m_currentFullPaths.end(), [type, ascending](const QString& a, const QString& b) {
		bool result = false;
		if (type == ByName) {
			// 按文件名排序（不区分大小写）
			result = QString::compare(QFileInfo(a).fileName(), QFileInfo(b).fileName(), Qt::CaseInsensitive) < 0;
		}
		else if (type == ByTime) {
			// 按最后修改时间排序
			result = QFileInfo(a).lastModified() < QFileInfo(b).lastModified();
		}

		return ascending ? result : !result;
		});

	// 排序完成后重新刷入模型
	refreshModel();
}

void ImageListView::setImageList(const QStringList& filePaths) {
	
	m_currentFullPaths = filePaths; // 备份路径用于后续排序
	refreshModel();
	
}

QVector<bool> ImageListView::getCheckedStatus() const {
	QVector<bool> results;
	for (int i = 0; i < m_model->rowCount(); ++i) {
		results.append(m_model->index(i, 0).data(Qt::CheckStateRole).toInt() == Qt::Checked);
	}
	return results;
}
void ImageListView::moveRowUp()
{
	QModelIndex currentIndex = this->currentIndex();
	int row = currentIndex.row();

	// 如果没有选中，或者是第一行，则无法上移
	if (!currentIndex.isValid() || row <= 0) return;

	// 1. 获取要移动的行数据（这里有3列）
	QList<QStandardItem*> rowItems = m_model->takeRow(row);

	// 2. 插入到上一行
	m_model->insertRow(row - 1, rowItems);

	// 3. 重新设置选中状态，让高亮跟着行走
	QModelIndex newIndex = m_model->index(row - 1, 0);
	this->setCurrentIndex(newIndex);

	// 4. 重要：更新所有行的“索引”列（第二列）数字
	updateIndexColumn();
}
void ImageListView::moveRowDown()
{
	QModelIndex currentIndex = this->currentIndex();
	int row = currentIndex.row();

	// 如果没有选中，或者是最后一行，则无法下移
	if (!currentIndex.isValid() || row >= m_model->rowCount() - 1) return;

	// 1. 获取当前行数据
	QList<QStandardItem*> rowItems = m_model->takeRow(row);

	// 2. 插入到下一行
	m_model->insertRow(row + 1, rowItems);

	// 3. 重新设置选中
	QModelIndex newIndex = m_model->index(row + 1, 0);
	this->setCurrentIndex(newIndex);

	// 4. 更新索引数字
	updateIndexColumn();
}
void ImageListView::updateIndexColumn()
{
	for (int i = 0; i < m_model->rowCount(); ++i) {
		m_model->setData(m_model->index(i, 1), QString::number(i + 1));
	}
}
void ImageListView::refreshModel()
{
	m_model->removeRows(0, m_model->rowCount());
	for (int i = 0; i < m_currentFullPaths.size(); ++i) {
		QList<QStandardItem*> rowItems;

		QStandardItem* checkItem = new QStandardItem();
		checkItem->setCheckable(true);
		checkItem->setCheckState(Qt::Unchecked);

		QStandardItem* indexItem = new QStandardItem(QString::number(i + 1));

		QString fileName = QFileInfo(m_currentFullPaths[i]).fileName();
		QStandardItem* nameItem = new QStandardItem(fileName);
		nameItem->setData(m_currentFullPaths[i], Qt::UserRole);

		rowItems << checkItem << indexItem << nameItem;
		m_model->appendRow(rowItems);
	}
}
void ImageListView::onHeaderClicked(int logicalIndex)
{
	if (logicalIndex == 0) {
		m_allChecked = !m_allChecked;

		// 同步自定义表头的变量，用于重绘
		ImageHeader* h = qobject_cast<ImageHeader*>(this->header());
		if (h) h->allChecked = m_allChecked;

		// 批量更新数据
		for (int i = 0; i < m_model->rowCount(); ++i) {
			m_model->setData(m_model->index(i, 0), m_allChecked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
		}

		// 强制刷新表头绘制
		this->header()->viewport()->update();
	}
}

void ImageHeader::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
{
	{
		painter->save();
		// 绘制统一的深色背景
		painter->fillRect(rect, QColor("#252526"));
		painter->setPen(QColor("#3a3a3a"));
		painter->drawRect(rect); // 边框

		if (logicalIndex == 0) {
			// 绘制列头的 Checkbox 样式，与 Delegate 保持一致
			int side = 16;
			QRect box(rect.center().x() - side / 2, rect.center().y() - side / 2, side, side);
			painter->setPen(QPen(allChecked ? QColor("#00CC66") : Qt::gray, 1));
			painter->drawRect(box);
			if (allChecked) painter->fillRect(box.adjusted(3, 3, -3, -3), QColor("#00CC66"));
		}
		else {
			// 绘制文字
			painter->setPen(QColor("#888888"));
			QString text = model()->headerData(logicalIndex, Qt::Horizontal).toString();
			painter->drawText(rect, Qt::AlignCenter, text);
		}
		painter->restore();
	}
}
