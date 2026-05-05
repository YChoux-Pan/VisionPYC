#pragma once

#include <QWidget>
#include "ui_RoiWidget.h"

class RoiWidget : public QWidget
{
	Q_OBJECT

public:
	RoiWidget(QWidget *parent = nullptr);
	~RoiWidget();

private:
	Ui::RoiWidgetClass ui;
};

