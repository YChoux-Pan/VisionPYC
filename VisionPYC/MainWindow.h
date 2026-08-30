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
	// 根据 FlowEngine 当前节点重建右侧流程树
	void rebuildFlowTree();
	// 保存 / 加载流程到 JSON 文件
	void saveFlowToFile();
	void loadFlowFromFile();
	// 把节点输出图像显示到右侧大界面
	void displayNodeResult(const QString& id);

	Ui::MainWindowClass *ui;
};


