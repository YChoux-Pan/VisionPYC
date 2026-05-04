#pragma once

#include <QWidget>
#include "ui_TESTWidget.h"

class TESTWidget : public QWidget
{
	Q_OBJECT

public:
	TESTWidget(QWidget *parent = nullptr);
	~TESTWidget();

private:
	Ui::TESTWidgetClass ui;
};

