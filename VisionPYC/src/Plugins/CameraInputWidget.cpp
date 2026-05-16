#include "CameraInputWidget.h"
#include <QFile>
#include <QFileDialog>
#include <QToolButton>
#include "Global_function.h"
CameraInputWidget::CameraInputWidget(QWidget *parent)
	: QWidget(parent),ui(new Ui::CameraInputWidgetClass)
{
	ui->setupUi(this);

	//applyCustomStyles();

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
			ui->stackedWidget_2->setCurrentWidget(ui->page_5);
		}
		});

	connect(ui->m_rad_5, &QRadioButton::toggled, this, [=](bool checked) {
		if (checked) {
			ui->stackedWidget_2->setCurrentWidget(ui->page_4);
		}
		});

	connect(ui->checkBox, &QCheckBox::toggled, this, [=](bool checked)
		{
			if (checked)
			{
				m_fun = checked;
			}
		});

	connect(ui->toolButton, &QToolButton::clicked, this, &CameraInputWidget::on_btnSelectFile_clicked);
	connect(ui->toolButton_4, &QToolButton::clicked, this, &CameraInputWidget::on_btnSelsctProject_clicked);
	connect(ui->listView, &ImageListView::itemClickedWithIndex, this, &CameraInputWidget::on_listView_clicked);

	connect(ui->m_btn_up, &QToolButton::clicked, this, [=]() {
		ui->listView->moveRowUp(); // 调用提升类的方法
		});

	connect(ui->m_btn_down, &QToolButton::clicked, this, [=]() {
		ui->listView->moveRowDown();
		});

	// 按照名称升序排序
	connect(ui->m_btn_name, &QToolButton::clicked, this, [=]() {
		ui->listView->sortItems(ImageListView::ByName, true);
		});

	// 按照修改时间降序排序（最新的在上面）
	connect(ui->m_btn_timer, &QToolButton::clicked, this, [=]() {
		ui->listView->sortItems(ImageListView::ByTime, false);
		});

	/*connect(ui->m_btn_OK, &QPushButton::clicked, this, &QWidget::close);*/
	connect(ui->m_btn_chanel, &QPushButton::clicked, this, &QWidget::close);


	//初始化默认点击控件

	ui->m_rad_1->setChecked(true);
	ui->m_rad_4->setChecked(true);

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
		":/lineEdit.qss",
		":/plainTextEdit.qss"
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

void CameraInputWidget::on_btnSelsctProject_clicked()
{
	m_FileProject = QFileDialog::getExistingDirectory(
		this,
		tr("选择图片文件夹"),
		QString::fromStdString(g_pathfile),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
	);

	if (m_FileProject.isEmpty()) {
		return; // 用户取消了选择
	}

	// 2. 判断用户是否选择了文件（如果点击取消，filePath 为空）
	if (!m_FileProject.isEmpty()) {
		// 3. 将路径显示在 Edit 控件中
		ui->lineEdit->setText(m_FileProject);
		
	}

	QStringList filters;
	filters << "*.jpg" << "*.png" << "*.ply" << "*.tiff" << "*.tif" << "*.bmp" << "*.jpeg";
	QDir directory(m_FileProject);
	fileList = directory.entryList(filters, QDir::Files | QDir::NoDotAndDotDot);

	ui->listView->setImageList(fileList);

	QVector<bool>status = ui->listView->getCheckedStatus();


}

void CameraInputWidget::on_m_btn_fun_clicked()
{
	//读取图片
	int64 start = cv::getTickCount();
	if (m_fun)
	{
		//后续再进行填充
		//主要是点击了后，流程能够输出下一组数据
	}


	if (m_QImg.isNull())  
	{
		qDebug() << "m_QImg 图像为空";
		//图像为空
		return;
	}
	ui->widget_3->setImage(m_QImg);
	int64 end = cv::getTickCount();
	m_timer = (end - start) * 1000 / cv::getTickFrequency();
	QString m_STimers = QString(tr("耗时: %1 ms")).arg(m_timer, 0, 'f', 2);
	
	ui->m_label_timer->setText(m_STimers);
}

void CameraInputWidget::on_listView_clicked(int row)
{
	if (fileList[row].isEmpty())
	{
		//文件获取失败
		qDebug() << "文件获取失败";
		return;
	}
	QString path = m_FileProject +"/" + fileList[row];
	loadAndPrepareImage(path, m_CImg, m_QImg);
	ui->widget_3->setImage(m_QImg);
}

void CameraInputWidget::on_m_btn_OK_clicked()
{
	//需要传参是内容以及保存的内容
	this->close();
}

void CameraInputWidget::on_btnSelectFile_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(
		this,
		tr("选择文件"),
		QString::fromStdString(g_pathfile),
		tr("所有文件 (*.*);;文本文件 (*.txt);;图片文件 (*.png *.jpg)")
	);

	
	
	// 2. 判断用户是否选择了文件（如果点击取消，filePath 为空）
	if (!filePath.isEmpty()) {
		// 3. 将路径显示在 Edit 控件中
		ui->label_7->setText(filePath);
		loadAndPrepareImage(m_FilePath, m_CImg, m_QImg);
		m_FilePath = filePath;
	}

}
