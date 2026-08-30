#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "WorkflowTreeWidget.h"
#include "NodeSelectorWidget.h" // 算子库

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
	// 从算子注册表自动填充左侧算子库
	void initOperators();

	Ui::MainWindowClass *ui;
};


