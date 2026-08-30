#pragma once

#include <QWidget>
#include <QMutex>
#include <opencv2/opencv.hpp>
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

	// --- 算法侧访问接口（供流程引擎在 worker 线程调用，线程安全）---
	bool hasImage() const { QMutexLocker l(&m_imgMutex); return !m_CImg.empty(); }
	cv::Mat currentImage() const { QMutexLocker l(&m_imgMutex); return m_CImg.clone(); }

private:
	Ui::CameraInputWidgetClass *ui;

	QString m_FilePath;//执行路径
	QString m_FileProject;//文件夹路径
	QStringList fileList;//文件路径容器
	QImage m_QImg;
	cv::Mat m_CImg;
	mutable QMutex m_imgMutex;   // 保护 m_CImg（GUI 写 / worker 读）
	bool m_fun = false;//是否开启循环
	double m_timer = 0.0f;
	
private slots:

	void on_btnSelectFile_clicked();  //指定文件路径
	void on_btnSelsctProject_clicked();//指定文件夹路径
	void on_m_btn_fun_clicked(); //执行

	void on_listView_clicked(int row);//列表点击信号

	void on_m_btn_OK_clicked();
};

