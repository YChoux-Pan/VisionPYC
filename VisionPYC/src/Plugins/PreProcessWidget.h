#pragma once

#include <QWidget>
#include "ui_PreProcessWidget.h"

class PreProcessWidget : public QWidget
{
	Q_OBJECT

public:
	PreProcessWidget(QWidget *parent = nullptr);
	~PreProcessWidget();

private:
	Ui::PreProcessWidgetClass ui;
};

