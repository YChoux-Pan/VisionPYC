#pragma once

#include <QWidget>
#include "ui_Height3DWidget.h"

class Height3DWidget : public QWidget
{
	Q_OBJECT

public:
	Height3DWidget(QWidget *parent = nullptr);
	~Height3DWidget();

private:
	Ui::Height3DWidgetClass ui;
};

