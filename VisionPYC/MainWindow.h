#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "NodeScene.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
	Ui::MainWindowClass *ui;
    NodeScene* m_scene;  // 逻辑容器
private slots:
	void onRunClicked();


};

