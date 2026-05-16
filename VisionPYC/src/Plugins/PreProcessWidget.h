#pragma once

#include <QWidget>
#include "ui_PreProcessWidget.h"
#include "ui_ImageAdjust.h"

enum class MainCategory {
	ImageAdjust,   // 图像调整
	Filter,        // 滤波
	Morphology,    // 形态学运算
	Enhance,       // 图像增强
	Binary         // 二值化
};

// 定义二级子项目枚举（将所有子功能放在一起，或者按分类区分均可）
enum class SubCommand {
	// 图像调整类
	ColorToGray, ImageMirror, ImageRotate, DepthToColor, ModifySize,
	// 滤波类
	MeanFilter, MedianFilter, GaussianFilter,
	// 形态学类
	Expand, Erosion, Opening, Closed,
	// 图像增强类
	Sharpen, Contrast, Luminance, Inverse, EdgeEnhancement,
	// 二值化类
	BinaryNormal, MeanBinary, ColorBinary
};

// 核心管理结构体
struct MenuCommandData {
	MainCategory mainCat; // 一级目录标示
	SubCommand subCmd;    // 二级具体指令标示
};

//注册结构体到元对象
Q_DECLARE_METATYPE(MenuCommandData)

class PreProcessWidget : public QWidget
{
	Q_OBJECT

public:
	PreProcessWidget(QWidget *parent = nullptr);
	~PreProcessWidget();


	

	void InitDlg();//初始化
	void clearSettingArea();//界面清理
private:
	Ui::PreProcessWidgetClass ui;
	//算子参数ui
	QWidget* m_currentSettingWidget = NULL;
	Ui::ImageAdjust* m_uiAdjust = nullptr;

	//算子菜单栏
	QMenu* m_mainMenu = NULL;


	void updateOperation(MenuCommandData m_Data);//运算核心
private slots:
	// 4. 统一的公共槽函数
	void onMenuActionTriggered();
	void onToolButtonClicked();

	void on_m_btn_fun_clicked();//执行


};

//// 关键步骤：为了让自定义结构体能塞进 QAction 的 QVariant 中，需要向 Qt 注册该类型
//Q_DECLARE_METATYPE(PreProcessWidget::MenuCommandData)

