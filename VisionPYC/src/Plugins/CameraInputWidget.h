#pragma once

#include <QWidget>
#include "ui_CameraInputWidget.h"

class CameraInputWidget : public QWidget
{
	Q_OBJECT

public:
	CameraInputWidget(QWidget *parent = nullptr);
	~CameraInputWidget();

private:
	Ui::CameraInputWidgetClass ui;
};

