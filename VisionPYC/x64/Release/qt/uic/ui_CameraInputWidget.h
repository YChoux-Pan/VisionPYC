/********************************************************************************
** Form generated from reading UI file 'CameraInputWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAINPUTWIDGET_H
#define UI_CAMERAINPUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <autowraplabel.h>
#include <imagelistview.h>
#include <imageviewwidget.h>

QT_BEGIN_NAMESPACE

class Ui_CameraInputWidgetClass
{
public:
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_7;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *m_rad_1;
    QRadioButton *m_rad_2;
    QRadioButton *m_rad_3;
    QStackedWidget *stackedWidget;
    QWidget *m_page_1;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_9;
    QRadioButton *m_rad_4;
    QRadioButton *m_rad_5;
    QStackedWidget *stackedWidget_2;
    QWidget *page_5;
    QHBoxLayout *horizontalLayout_4;
    AutoWrapLabel *label_7;
    QToolButton *toolButton;
    QWidget *page_4;
    QHBoxLayout *horizontalLayout_5;
    AutoWrapLabel *label_8;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QSpacerItem *verticalSpacer_2;
    QWidget *m_page_2;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox;
    QLineEdit *lineEdit;
    QToolButton *toolButton_4;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_7;
    QToolButton *m_btn_up;
    QToolButton *m_btn_down;
    QCheckBox *checkBox_2;
    QToolButton *m_btn_timer;
    QToolButton *m_btn_name;
    QSpacerItem *horizontalSpacer_2;
    ImageListView *listView;
    QWidget *m_page_3;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QWidget *tab_2;
    QWidget *tab_3;
    ImageViewWidget *widget_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *m_label_timer;
    QLabel *label_2;
    QPushButton *m_btn_fun;
    QPushButton *m_btn_OK;
    QPushButton *m_btn_chanel;

    void setupUi(QWidget *CameraInputWidgetClass)
    {
        if (CameraInputWidgetClass->objectName().isEmpty())
            CameraInputWidgetClass->setObjectName("CameraInputWidgetClass");
        CameraInputWidgetClass->resize(1465, 750);
        horizontalLayout_3 = new QHBoxLayout(CameraInputWidgetClass);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(CameraInputWidgetClass);
        widget->setObjectName("widget");
        verticalLayout_7 = new QVBoxLayout(widget);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(widget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(5);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(280, 0));
        tabWidget->setMaximumSize(QSize(280, 16777215));
        tabWidget->setSizeIncrement(QSize(280, 0));
        tab = new QWidget();
        tab->setObjectName("tab");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        m_rad_1 = new QRadioButton(widget_2);
        m_rad_1->setObjectName("m_rad_1");
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(m_rad_1->sizePolicy().hasHeightForWidth());
        m_rad_1->setSizePolicy(sizePolicy3);
        m_rad_1->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_rad_1);

        m_rad_2 = new QRadioButton(widget_2);
        m_rad_2->setObjectName("m_rad_2");
        sizePolicy3.setHeightForWidth(m_rad_2->sizePolicy().hasHeightForWidth());
        m_rad_2->setSizePolicy(sizePolicy3);
        m_rad_2->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_rad_2);

        m_rad_3 = new QRadioButton(widget_2);
        m_rad_3->setObjectName("m_rad_3");
        sizePolicy3.setHeightForWidth(m_rad_3->sizePolicy().hasHeightForWidth());
        m_rad_3->setSizePolicy(sizePolicy3);
        m_rad_3->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_rad_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addWidget(widget_2);

        stackedWidget = new QStackedWidget(tab);
        stackedWidget->setObjectName("stackedWidget");
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        m_page_1 = new QWidget();
        m_page_1->setObjectName("m_page_1");
        sizePolicy2.setHeightForWidth(m_page_1->sizePolicy().hasHeightForWidth());
        m_page_1->setSizePolicy(sizePolicy2);
        verticalLayout_5 = new QVBoxLayout(m_page_1);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(m_page_1);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(groupBox_4);
        widget_4->setObjectName("widget_4");
        verticalLayout_6 = new QVBoxLayout(widget_4);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        widget_7 = new QWidget(widget_4);
        widget_7->setObjectName("widget_7");
        horizontalLayout_9 = new QHBoxLayout(widget_7);
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(16, -1, -1, 0);
        m_rad_4 = new QRadioButton(widget_7);
        m_rad_4->setObjectName("m_rad_4");

        horizontalLayout_9->addWidget(m_rad_4);

        m_rad_5 = new QRadioButton(widget_7);
        m_rad_5->setObjectName("m_rad_5");

        horizontalLayout_9->addWidget(m_rad_5);


        verticalLayout_6->addWidget(widget_7);

        stackedWidget_2 = new QStackedWidget(widget_4);
        stackedWidget_2->setObjectName("stackedWidget_2");
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(stackedWidget_2->sizePolicy().hasHeightForWidth());
        stackedWidget_2->setSizePolicy(sizePolicy4);
        stackedWidget_2->setMinimumSize(QSize(0, 55));
        stackedWidget_2->setMaximumSize(QSize(16777215, 40));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        horizontalLayout_4 = new QHBoxLayout(page_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        label_7 = new AutoWrapLabel(page_5);
        label_7->setObjectName("label_7");
        label_7->setMinimumSize(QSize(0, 35));
        label_7->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(label_7);

        toolButton = new QToolButton(page_5);
        toolButton->setObjectName("toolButton");
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy5);
        toolButton->setMinimumSize(QSize(30, 0));
        toolButton->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/search-line.svg)"));

        horizontalLayout_4->addWidget(toolButton);

        stackedWidget_2->addWidget(page_5);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        horizontalLayout_5 = new QHBoxLayout(page_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        label_8 = new AutoWrapLabel(page_4);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(label_8);

        toolButton_2 = new QToolButton(page_4);
        toolButton_2->setObjectName("toolButton_2");
        sizePolicy5.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy5);
        toolButton_2->setMinimumSize(QSize(30, 0));
        toolButton_2->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/attachment-2.svg)"));

        horizontalLayout_5->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(page_4);
        toolButton_3->setObjectName("toolButton_3");
        sizePolicy5.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy5);
        toolButton_3->setMinimumSize(QSize(30, 0));
        toolButton_3->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/close-large-fill.svg)"));

        horizontalLayout_5->addWidget(toolButton_3);

        stackedWidget_2->addWidget(page_4);

        verticalLayout_6->addWidget(stackedWidget_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);


        verticalLayout_2->addWidget(widget_4);


        verticalLayout_5->addWidget(groupBox_4);

        stackedWidget->addWidget(m_page_1);
        m_page_2 = new QWidget();
        m_page_2->setObjectName("m_page_2");
        sizePolicy2.setHeightForWidth(m_page_2->sizePolicy().hasHeightForWidth());
        m_page_2->setSizePolicy(sizePolicy2);
        horizontalLayout_8 = new QHBoxLayout(m_page_2);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        groupBox_3 = new QGroupBox(m_page_2);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_5 = new QWidget(groupBox_3);
        widget_5->setObjectName("widget_5");
        widget_5->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_6 = new QHBoxLayout(widget_5);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        checkBox = new QCheckBox(widget_5);
        checkBox->setObjectName("checkBox");

        horizontalLayout_6->addWidget(checkBox);

        lineEdit = new QLineEdit(widget_5);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_6->addWidget(lineEdit);

        toolButton_4 = new QToolButton(widget_5);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/attachment-2.svg)"));

        horizontalLayout_6->addWidget(toolButton_4);


        verticalLayout_3->addWidget(widget_5);

        widget_6 = new QWidget(groupBox_3);
        widget_6->setObjectName("widget_6");
        widget_6->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_7 = new QHBoxLayout(widget_6);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(6, -1, -1, -1);
        m_btn_up = new QToolButton(widget_6);
        m_btn_up->setObjectName("m_btn_up");
        m_btn_up->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/arrow-up-long-line.svg)"));

        horizontalLayout_7->addWidget(m_btn_up);

        m_btn_down = new QToolButton(widget_6);
        m_btn_down->setObjectName("m_btn_down");
        m_btn_down->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/arrow-down-long-line.svg)"));

        horizontalLayout_7->addWidget(m_btn_down);

        checkBox_2 = new QCheckBox(widget_6);
        checkBox_2->setObjectName("checkBox_2");
        sizePolicy1.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
        checkBox_2->setSizePolicy(sizePolicy1);
        checkBox_2->setMinimumSize(QSize(60, 0));

        horizontalLayout_7->addWidget(checkBox_2);

        m_btn_timer = new QToolButton(widget_6);
        m_btn_timer->setObjectName("m_btn_timer");
        m_btn_timer->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/history-fill.svg)"));

        horizontalLayout_7->addWidget(m_btn_timer);

        m_btn_name = new QToolButton(widget_6);
        m_btn_name->setObjectName("m_btn_name");
        m_btn_name->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/filter-2-fill.svg)"));

        horizontalLayout_7->addWidget(m_btn_name);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(widget_6);

        listView = new ImageListView(groupBox_3);
        listView->setObjectName("listView");

        verticalLayout_3->addWidget(listView);


        horizontalLayout_8->addWidget(groupBox_3);

        stackedWidget->addWidget(m_page_2);
        m_page_3 = new QWidget();
        m_page_3->setObjectName("m_page_3");
        sizePolicy2.setHeightForWidth(m_page_3->sizePolicy().hasHeightForWidth());
        m_page_3->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(m_page_3);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(m_page_3);
        groupBox->setObjectName("groupBox");

        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(m_page_3);
        groupBox_2->setObjectName("groupBox_2");

        verticalLayout_4->addWidget(groupBox_2);

        stackedWidget->addWidget(m_page_3);

        verticalLayout->addWidget(stackedWidget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        sizePolicy1.setHeightForWidth(tab_2->sizePolicy().hasHeightForWidth());
        tab_2->setSizePolicy(sizePolicy1);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        sizePolicy1.setHeightForWidth(tab_3->sizePolicy().hasHeightForWidth());
        tab_3->setSizePolicy(sizePolicy1);
        tabWidget->addTab(tab_3, QString());
        splitter->addWidget(tabWidget);
        widget_3 = new ImageViewWidget(splitter);
        widget_3->setObjectName("widget_3");
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(3);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy6);
        splitter->addWidget(widget_3);

        verticalLayout_7->addWidget(splitter);

        frame = new QFrame(widget);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(16777215, 60));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 40, 0);
        horizontalSpacer = new QSpacerItem(760, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_label_timer = new QLabel(frame);
        m_label_timer->setObjectName("m_label_timer");
        sizePolicy1.setHeightForWidth(m_label_timer->sizePolicy().hasHeightForWidth());
        m_label_timer->setSizePolicy(sizePolicy1);
        m_label_timer->setMaximumSize(QSize(100, 20));
        m_label_timer->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_label_timer);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMaximumSize(QSize(100, 20));
        label_2->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        m_btn_fun = new QPushButton(frame);
        m_btn_fun->setObjectName("m_btn_fun");
        sizePolicy1.setHeightForWidth(m_btn_fun->sizePolicy().hasHeightForWidth());
        m_btn_fun->setSizePolicy(sizePolicy1);
        m_btn_fun->setMinimumSize(QSize(120, 0));
        m_btn_fun->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(m_btn_fun);

        m_btn_OK = new QPushButton(frame);
        m_btn_OK->setObjectName("m_btn_OK");
        sizePolicy1.setHeightForWidth(m_btn_OK->sizePolicy().hasHeightForWidth());
        m_btn_OK->setSizePolicy(sizePolicy1);
        m_btn_OK->setMinimumSize(QSize(120, 0));
        m_btn_OK->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(m_btn_OK);

        m_btn_chanel = new QPushButton(frame);
        m_btn_chanel->setObjectName("m_btn_chanel");
        sizePolicy1.setHeightForWidth(m_btn_chanel->sizePolicy().hasHeightForWidth());
        m_btn_chanel->setSizePolicy(sizePolicy1);
        m_btn_chanel->setMinimumSize(QSize(120, 0));
        m_btn_chanel->setMaximumSize(QSize(120, 40));
        m_btn_chanel->setSizeIncrement(QSize(120, 40));

        horizontalLayout_2->addWidget(m_btn_chanel);


        verticalLayout_7->addWidget(frame);


        horizontalLayout_3->addWidget(widget);


        retranslateUi(CameraInputWidgetClass);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(1);
        stackedWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CameraInputWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *CameraInputWidgetClass)
    {
        CameraInputWidgetClass->setWindowTitle(QCoreApplication::translate("CameraInputWidgetClass", "CameraInputWidget", nullptr));
        m_rad_1->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\214\207\345\256\232\345\233\276\345\203\217", nullptr));
        m_rad_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\226\207\344\273\266\347\233\256\345\275\225", nullptr));
        m_rad_3->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\233\270\346\234\272", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("CameraInputWidgetClass", "\346\214\207\345\256\232\345\233\276\345\203\217", nullptr));
        m_rad_4->setText(QCoreApplication::translate("CameraInputWidgetClass", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        m_rad_5->setText(QCoreApplication::translate("CameraInputWidgetClass", "\351\223\276\346\216\245\350\267\257\345\276\204", nullptr));
        label_7->setText(QString());
        toolButton->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        label_8->setText(QString());
        toolButton_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CameraInputWidgetClass", "\346\226\207\344\273\266\347\233\256\345\275\225", nullptr));
        checkBox->setText(QCoreApplication::translate("CameraInputWidgetClass", "\345\276\252\347\216\257", nullptr));
        toolButton_4->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        m_btn_up->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        m_btn_down->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        checkBox_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\350\207\252\345\212\250\345\210\207\346\215\242", nullptr));
        m_btn_timer->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        m_btn_name->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CameraInputWidgetClass", "\347\233\270\346\234\272\346\250\241\345\274\217", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CameraInputWidgetClass", "\345\205\211\346\272\220\351\200\232\350\256\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("CameraInputWidgetClass", "\345\237\272\346\234\254\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("CameraInputWidgetClass", "\345\233\276\345\203\217\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("CameraInputWidgetClass", "\345\205\266\344\273\226\345\217\202\346\225\260", nullptr));
        m_label_timer->setText(QCoreApplication::translate("CameraInputWidgetClass", "\350\200\227\346\227\266: 0.00 ms", nullptr));
        label_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\212\266\346\200\201\357\274\232\346\234\252\347\237\245", nullptr));
        m_btn_fun->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\211\247\350\241\214", nullptr));
        m_btn_OK->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\241\256\345\256\232", nullptr));
        m_btn_chanel->setText(QCoreApplication::translate("CameraInputWidgetClass", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraInputWidgetClass: public Ui_CameraInputWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAINPUTWIDGET_H
