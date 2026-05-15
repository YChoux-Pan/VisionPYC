/********************************************************************************
** Form generated from reading UI file 'TemplateWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATEWIDGET_H
#define UI_TEMPLATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
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

    void setupUi(QWidget *PreProcessWidgetClass)
    {
        if (PreProcessWidgetClass->objectName().isEmpty())
            PreProcessWidgetClass->setObjectName("PreProcessWidgetClass");
        PreProcessWidgetClass->resize(1509, 831);
        verticalLayout_8 = new QVBoxLayout(PreProcessWidgetClass);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName("verticalLayout_8");
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
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(3);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy2);
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


        verticalLayout_8->addWidget(widget);


        retranslateUi(PreProcessWidgetClass);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(PreProcessWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *PreProcessWidgetClass)
    {
        PreProcessWidgetClass->setWindowTitle(QCoreApplication::translate("PreProcessWidgetClass", "PreProcessWidget", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PreProcessWidgetClass", "\345\237\272\346\234\254\350\256\276\347\275\256", nullptr));
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

#endif // UI_TEMPLATEWIDGET_H
