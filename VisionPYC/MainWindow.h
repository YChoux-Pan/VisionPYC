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
	Ui::MainWindowClass *ui;

private slots:
	void onRunClicked();


};

