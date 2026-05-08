#include "CameraInputWidget.h"
#include <QFile>
CameraInputWidget::CameraInputWidget(QWidget *parent)
	: QWidget(parent),ui(new Ui::CameraInputWidgetClass)
{
	ui->setupUi(this);

	applyCustomStyles();

	InitWidget();
	


}

CameraInputWidget::~CameraInputWidget()
{
	delete ui;
}

void CameraInputWidget::InitWidget(void)
{
	connect(ui->m_rad_1, &QRadioButton::toggled, this, [=](bool checked) {
		if (checked) {
			ui->stackedWidget->setCurrentWidget(ui->m_page_1);
		}
		});

	connect(ui->m_rad_2, &QRadioButton::toggled, this, [=](bool checked) {
		if (checked) {
			ui->stackedWidget->setCurrentWidget(ui->m_page_2);
		}
		});

	connect(ui->m_rad_3, &QRadioButton::toggled, this, [=](bool checked) {
		if (checked) {
			ui->stackedWidget->setCurrentWidget(ui->m_page_3);
		}
		});

	connect(ui->m_rad_4, &QRadioButton::toggled, this, [=](bool checked) {
		if (checked) {
			ui->stackedWidget_2->setCurrentWidget(ui->page_4);
		}
		});

	connect(ui->m_rad_5, &QRadioButton::toggled, this, [=](bool checked) {
		if (checked) {
			ui->stackedWidget_2->setCurrentWidget(ui->page_5);
		}
		});



}

void CameraInputWidget::applyCustomStyles()
{
	QString fullStyle;
	// 将所有样式文件路径放在一个列表里

	//需要按照界面控件的最低层到最外层进行qss加载，否则颜色会被覆盖
	//必须要首先加载widget整体背景
	QStringList qssFiles = {
		":/widget.qss",
		":/tabBar.qss",
		":/groupBox.qss",
		":/radiobutton.qss",
		":/pushbutton.qss",
		":/lineEdit.qss"
	};
	

	for (const QString& path : qssFiles) {
		QFile file(path);
		if (file.open(QFile::ReadOnly)) {
			fullStyle.append(file.readAll());
			file.close();
		}
		else {
			qDebug() << "Failed to load QSS file:" << path;
		}
	}

	if (!fullStyle.isEmpty()) {
		this->setStyleSheet(fullStyle);
	}


}

