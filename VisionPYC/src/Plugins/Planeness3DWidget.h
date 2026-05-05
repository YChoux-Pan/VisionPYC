#pragma once

#include <QWidget>
#include "ui_Planeness3DWidget.h"

class Planeness3DWidget : public QWidget
{
	Q_OBJECT

public:
	Planeness3DWidget(QWidget *parent = nullptr);
	~Planeness3DWidget();

private:
	Ui::Planeness3DWidgetClass ui;
};

