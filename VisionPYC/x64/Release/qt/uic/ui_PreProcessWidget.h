/********************************************************************************
** Form generated from reading UI file 'PreProcessWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREPROCESSWIDGET_H
#define UI_PREPROCESSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <imagelistview.h>
#include <imageviewwidget.h>

QT_BEGIN_NAMESPACE

class Ui_PreProcessWidgetClass
{
public:
    QVBoxLayout *verticalLayout_8;
    QWidget *widget;
    QVBoxLayout *verticalLayout_7;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTextEdit *textEdit;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_4;
    QFormLayout *formLayout;
    QLabel *label_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QTextEdit *textEdit_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *m_toolbtn_add;
    QToolButton *m_toolbtn_delate;
    QToolButton *m_toolbtn_up;
    QToolButton *m_toolbtn_down;
    QCheckBox *checkBox;
    ImageListView *listView;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_9;
    QWidget *m_wid_setting;
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

    void setupUi(QWidget *PreProcessWidgetClass)
    {
        if (PreProcessWidgetClass->objectName().isEmpty())
            PreProcessWidgetClass->setObjectName("PreProcessWidgetClass");
        PreProcessWidgetClass->resize(1465, 750);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreProcessWidgetClass->sizePolicy().hasHeightForWidth());
        PreProcessWidgetClass->setSizePolicy(sizePolicy);
        verticalLayout_8 = new QVBoxLayout(PreProcessWidgetClass);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(PreProcessWidgetClass);
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
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(280, 0));
        tabWidget->setMaximumSize(QSize(280, 16777215));
        tabWidget->setSizeIncrement(QSize(280, 0));
        tab = new QWidget();
        tab->setObjectName("tab");
        sizePolicy.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(widget_2);
        groupBox->setObjectName("groupBox");
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(16777215, 80));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(10, 10, 0, 0);
        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName("frame_2");
        frame_2->setMaximumSize(QSize(16777215, 30));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_2);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        textEdit = new QTextEdit(frame_2);
        textEdit->setObjectName("textEdit");

        horizontalLayout->addWidget(textEdit);

        toolButton = new QToolButton(frame_2);
        toolButton->setObjectName("toolButton");
        sizePolicy.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy);
        toolButton->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/link.svg)"));

        horizontalLayout->addWidget(toolButton);

        toolButton_2 = new QToolButton(frame_2);
        toolButton_2->setObjectName("toolButton_2");
        sizePolicy.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy);
        toolButton_2->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/close-line.svg)"));

        horizontalLayout->addWidget(toolButton_2);


        verticalLayout_3->addWidget(frame_2);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget_2);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(10, 0, 0, 0);
        widget_4 = new QWidget(groupBox_2);
        widget_4->setObjectName("widget_4");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy2);
        formLayout = new QFormLayout(widget_4);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName("formLayout");
        label_3 = new QLabel(widget_4);
        label_3->setObjectName("label_3");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        radioButton = new QRadioButton(widget_4);
        radioButton->setObjectName("radioButton");

        formLayout->setWidget(0, QFormLayout::FieldRole, radioButton);

        radioButton_2 = new QRadioButton(widget_4);
        radioButton_2->setObjectName("radioButton_2");

        formLayout->setWidget(1, QFormLayout::FieldRole, radioButton_2);


        verticalLayout_4->addWidget(widget_4);

        frame_3 = new QFrame(groupBox_2);
        frame_3->setObjectName("frame_3");
        frame_3->setMaximumSize(QSize(16777215, 30));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(frame_3);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        textEdit_2 = new QTextEdit(frame_3);
        textEdit_2->setObjectName("textEdit_2");

        horizontalLayout_3->addWidget(textEdit_2);

        toolButton_3 = new QToolButton(frame_3);
        toolButton_3->setObjectName("toolButton_3");
        sizePolicy.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy);
        toolButton_3->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/link.svg)"));

        horizontalLayout_3->addWidget(toolButton_3);

        toolButton_4 = new QToolButton(frame_3);
        toolButton_4->setObjectName("toolButton_4");
        sizePolicy.setHeightForWidth(toolButton_4->sizePolicy().hasHeightForWidth());
        toolButton_4->setSizePolicy(sizePolicy);
        toolButton_4->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/close-line.svg)"));

        horizontalLayout_3->addWidget(toolButton_4);


        verticalLayout_4->addWidget(frame_3);

        verticalSpacer = new QSpacerItem(20, 533, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        verticalLayout_2->addWidget(groupBox_2);


        verticalLayout->addWidget(widget_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        sizePolicy.setHeightForWidth(tab_2->sizePolicy().hasHeightForWidth());
        tab_2->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_5 = new QWidget(tab_2);
        widget_5->setObjectName("widget_5");
        verticalLayout_6 = new QVBoxLayout(widget_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        frame_4 = new QFrame(widget_5);
        frame_4->setObjectName("frame_4");
        frame_4->setMinimumSize(QSize(0, 50));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_4);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        m_toolbtn_add = new QToolButton(frame_4);
        m_toolbtn_add->setObjectName("m_toolbtn_add");
        m_toolbtn_add->setMinimumSize(QSize(40, 40));
        m_toolbtn_add->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/add-large-fill.svg);\n"
"icon-color: white;"));

        horizontalLayout_4->addWidget(m_toolbtn_add);

        m_toolbtn_delate = new QToolButton(frame_4);
        m_toolbtn_delate->setObjectName("m_toolbtn_delate");
        m_toolbtn_delate->setMinimumSize(QSize(40, 40));
        m_toolbtn_delate->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/subtract-line.svg)"));

        horizontalLayout_4->addWidget(m_toolbtn_delate);

        m_toolbtn_up = new QToolButton(frame_4);
        m_toolbtn_up->setObjectName("m_toolbtn_up");
        m_toolbtn_up->setMinimumSize(QSize(40, 40));
        m_toolbtn_up->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/arrow-up-long-line.svg)"));

        horizontalLayout_4->addWidget(m_toolbtn_up);

        m_toolbtn_down = new QToolButton(frame_4);
        m_toolbtn_down->setObjectName("m_toolbtn_down");
        m_toolbtn_down->setMinimumSize(QSize(40, 40));
        m_toolbtn_down->setStyleSheet(QString::fromUtf8("qproperty-icon:url(:/icon/icon/arrow-down-long-line.svg)"));

        horizontalLayout_4->addWidget(m_toolbtn_down);

        checkBox = new QCheckBox(frame_4);
        checkBox->setObjectName("checkBox");

        horizontalLayout_4->addWidget(checkBox);


        verticalLayout_6->addWidget(frame_4);

        listView = new ImageListView(widget_5);
        listView->setObjectName("listView");

        verticalLayout_6->addWidget(listView);

        groupBox_3 = new QGroupBox(widget_5);
        groupBox_3->setObjectName("groupBox_3");
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout_9 = new QVBoxLayout(groupBox_3);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 10, 0, 0);
        m_wid_setting = new QWidget(groupBox_3);
        m_wid_setting->setObjectName("m_wid_setting");

        verticalLayout_9->addWidget(m_wid_setting);


        verticalLayout_6->addWidget(groupBox_3);

        verticalLayout_6->setStretch(0, 1);
        verticalLayout_6->setStretch(1, 6);
        verticalLayout_6->setStretch(2, 6);

        verticalLayout_5->addWidget(widget_5);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        sizePolicy.setHeightForWidth(tab_3->sizePolicy().hasHeightForWidth());
        tab_3->setSizePolicy(sizePolicy);
        tabWidget->addTab(tab_3, QString());
        splitter->addWidget(tabWidget);
        widget_3 = new ImageViewWidget(splitter);
        widget_3->setObjectName("widget_3");
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(3);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy3);
        splitter->addWidget(widget_3);

        verticalLayout_7->addWidget(splitter);

        frame = new QFrame(widget);
        frame->setObjectName("frame");
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 60));
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
        sizePolicy.setHeightForWidth(m_label_timer->sizePolicy().hasHeightForWidth());
        m_label_timer->setSizePolicy(sizePolicy);
        m_label_timer->setMaximumSize(QSize(100, 20));
        m_label_timer->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(m_label_timer);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(100, 20));
        label_2->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        m_btn_fun = new QPushButton(frame);
        m_btn_fun->setObjectName("m_btn_fun");
        sizePolicy.setHeightForWidth(m_btn_fun->sizePolicy().hasHeightForWidth());
        m_btn_fun->setSizePolicy(sizePolicy);
        m_btn_fun->setMinimumSize(QSize(120, 40));
        m_btn_fun->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(m_btn_fun);

        m_btn_OK = new QPushButton(frame);
        m_btn_OK->setObjectName("m_btn_OK");
        sizePolicy.setHeightForWidth(m_btn_OK->sizePolicy().hasHeightForWidth());
        m_btn_OK->setSizePolicy(sizePolicy);
        m_btn_OK->setMinimumSize(QSize(120, 0));
        m_btn_OK->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(m_btn_OK);

        m_btn_chanel = new QPushButton(frame);
        m_btn_chanel->setObjectName("m_btn_chanel");
        sizePolicy.setHeightForWidth(m_btn_chanel->sizePolicy().hasHeightForWidth());
        m_btn_chanel->setSizePolicy(sizePolicy);
        m_btn_chanel->setMinimumSize(QSize(120, 0));
        m_btn_chanel->setMaximumSize(QSize(120, 40));
        m_btn_chanel->setSizeIncrement(QSize(120, 40));

        horizontalLayout_2->addWidget(m_btn_chanel);


        verticalLayout_7->addWidget(frame);


        verticalLayout_8->addWidget(widget);


        retranslateUi(PreProcessWidgetClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PreProcessWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *PreProcessWidgetClass)
    {
        PreProcessWidgetClass->setWindowTitle(QCoreApplication::translate("PreProcessWidgetClass", "PreProcessWidget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PreProcessWidgetClass", "\345\233\276\345\203\217\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("PreProcessWidgetClass", "\350\276\223\345\205\245\345\233\276\345\203\217     ", nullptr));
        toolButton->setText(QString());
        toolButton_2->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("PreProcessWidgetClass", "ROI\344\277\241\346\201\257", nullptr));
        label_3->setText(QCoreApplication::translate("PreProcessWidgetClass", "\344\275\234\347\224\250\350\214\203\345\233\264  ", nullptr));
        radioButton->setText(QCoreApplication::translate("PreProcessWidgetClass", "\345\205\250\345\233\276", nullptr));
        radioButton_2->setText(QCoreApplication::translate("PreProcessWidgetClass", "ROI\351\223\276\346\216\245", nullptr));
        label_4->setText(QCoreApplication::translate("PreProcessWidgetClass", "ROI           ", nullptr));
        toolButton_3->setText(QString());
        toolButton_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PreProcessWidgetClass", "\345\237\272\346\234\254\350\256\276\347\275\256", nullptr));
        m_toolbtn_add->setText(QString());
        m_toolbtn_delate->setText(QString());
        m_toolbtn_up->setText(QString());
        m_toolbtn_down->setText(QString());
        checkBox->setText(QCoreApplication::translate("PreProcessWidgetClass", "\345\256\236\346\227\266\345\210\267\346\226\260", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("PreProcessWidgetClass", "\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PreProcessWidgetClass", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("PreProcessWidgetClass", "\351\253\230\347\272\247\345\217\202\346\225\260", nullptr));
        m_label_timer->setText(QCoreApplication::translate("PreProcessWidgetClass", "\350\200\227\346\227\266: 0.00 ms", nullptr));
        label_2->setText(QCoreApplication::translate("PreProcessWidgetClass", "\347\212\266\346\200\201\357\274\232\346\234\252\347\237\245", nullptr));
        m_btn_fun->setText(QCoreApplication::translate("PreProcessWidgetClass", "\346\211\247\350\241\214", nullptr));
        m_btn_OK->setText(QCoreApplication::translate("PreProcessWidgetClass", "\347\241\256\345\256\232", nullptr));
        m_btn_chanel->setText(QCoreApplication::translate("PreProcessWidgetClass", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PreProcessWidgetClass: public Ui_PreProcessWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREPROCESSWIDGET_H
