#include "CameraInputWidget.h"
#include <QFile>
CameraInputWidget::CameraInputWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QString fullStyle;

	// 加载第一个样式文件
	QFile file1(":/style.qss");
	if (file1.open(QFile::ReadOnly)) {
		fullStyle.append(file1.readAll());
		file1.close();
	}

	// 加载第二个样式文件
	QFile file2(":/radiobutton.qss");
	if (file2.open(QFile::ReadOnly)) {
		fullStyle.append(file2.readAll());
		file2.close();
	}

	// 统一应用
	if (!fullStyle.isEmpty()) {
		this->setStyleSheet(fullStyle);
	}


}

CameraInputWidget::~CameraInputWidget()
{}

