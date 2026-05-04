#include "TESTWidget.h"

TESTWidget::TESTWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.pushButton->setInternalName("GaussianBlurNode");
	ui.pushButton->setText("高斯滤波"); // 也可以顺便设置显示名称
}

TESTWidget::~TESTWidget()
{}

