#pragma once

#include <QWidget>
#include "ui_CameraInputWidget.h"

class CameraInputWidget : public QWidget
{
	Q_OBJECT

public:
	CameraInputWidget(QWidget *parent = nullptr);
	~CameraInputWidget();

	void InitWidget();//界面初始化
	void applyCustomStyles();//qss初始化
private:
	Ui::CameraInputWidgetClass *ui;
};

