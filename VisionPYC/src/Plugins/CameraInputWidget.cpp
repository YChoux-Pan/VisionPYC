#include "CameraInputWidget.h"
#include <QFile>
CameraInputWidget::CameraInputWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QFile file(":/style.qss");
	if (file.open(QFile::ReadOnly)) {
		this->setStyleSheet(file.readAll());
	}


}

CameraInputWidget::~CameraInputWidget()
{}

