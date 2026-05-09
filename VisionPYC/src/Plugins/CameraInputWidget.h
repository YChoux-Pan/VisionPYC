#pragma once

#include <QWidget>
#include "ui_CameraInputWidget.h"
#include "Global.h"

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

	QString m_FilePath;//执行路径
	QString m_FileProject;//文件夹路径
	QStringList fileList;//文件路径容器
	QImage m_QImg;
	cv::Mat m_CImg;
	bool m_fun = false;//是否开启循环
	double m_timer = 0.0f;
	
private slots:

	void on_btnSelectFile_clicked();  //指定文件路径
	void on_btnSelsctProject_clicked();//指定文件夹路径
	void on_m_btn_fun_clicked(); //执行

	void on_listView_clicked(int row);//列表点击信号

	void on_m_btn_OK_clicked();
};

