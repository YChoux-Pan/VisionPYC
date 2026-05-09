#ifndef AUTOWRAPLABEL_H
#define AUTOWRAPLABEL_H

#include <QLabel>

class AutoWrapLabel : public QLabel
{
	Q_OBJECT
public:
	explicit AutoWrapLabel(QWidget* parent = nullptr);

protected:
	// 如果你希望在启用状态下也有焦点边框效果，需要让 Label 接受焦点
	// 但通常 Label 只做展示，这里我们保持它的简洁性
};

#endif // AUTOWRAPLABEL_H