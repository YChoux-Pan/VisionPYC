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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraInputWidgetClass
{
public:
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *widget_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *CameraInputWidgetClass)
    {
        if (CameraInputWidgetClass->objectName().isEmpty())
            CameraInputWidgetClass->setObjectName("CameraInputWidgetClass");
        CameraInputWidgetClass->resize(1465, 750);
        horizontalLayout_3 = new QHBoxLayout(CameraInputWidgetClass);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, -1);
        widget = new QWidget(CameraInputWidgetClass);
        widget->setObjectName("widget");
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMaximumSize(QSize(280, 16777215));
        tabWidget->setSizeIncrement(QSize(280, 0));
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        radioButton = new QRadioButton(widget_2);
        radioButton->setObjectName("radioButton");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy);
        radioButton->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(widget_2);
        radioButton_2->setObjectName("radioButton_2");
        sizePolicy.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy);
        radioButton_2->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(widget_2);
        radioButton_3->setObjectName("radioButton_3");
        sizePolicy.setHeightForWidth(radioButton_3->sizePolicy().hasHeightForWidth());
        radioButton_3->setSizePolicy(sizePolicy);
        radioButton_3->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(radioButton_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addWidget(widget_2);

        stackedWidget = new QStackedWidget(tab);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(widget_3, 0, 1, 1, 1);

        frame = new QFrame(widget);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(16777215, 60));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(9);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(760, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(frame);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(100, 20));
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMaximumSize(QSize(100, 20));
        label_2->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(120, 0));
        pushButton->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(120, 0));
        pushButton_2->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(120, 0));
        pushButton_3->setMaximumSize(QSize(120, 40));
        pushButton_3->setSizeIncrement(QSize(120, 40));

        horizontalLayout_2->addWidget(pushButton_3);


        gridLayout->addWidget(frame, 1, 0, 1, 2);


        horizontalLayout_3->addWidget(widget);


        retranslateUi(CameraInputWidgetClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CameraInputWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *CameraInputWidgetClass)
    {
        CameraInputWidgetClass->setWindowTitle(QCoreApplication::translate("CameraInputWidgetClass", "CameraInputWidget", nullptr));
        radioButton->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\214\207\345\256\232\345\233\276\345\203\217", nullptr));
        radioButton_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\226\207\344\273\266\347\233\256\345\275\225", nullptr));
        radioButton_3->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\233\270\346\234\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("CameraInputWidgetClass", "\345\237\272\346\234\254\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("CameraInputWidgetClass", "\345\233\276\345\203\217\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("CameraInputWidgetClass", "\345\205\266\344\273\226\345\217\202\346\225\260", nullptr));
        label->setText(QCoreApplication::translate("CameraInputWidgetClass", "\350\200\227\346\227\266:%d", nullptr));
        label_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\212\266\346\200\201\357\274\232\346\234\252\347\237\245", nullptr));
        pushButton->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\211\247\350\241\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\241\256\345\256\232", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CameraInputWidgetClass", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraInputWidgetClass: public Ui_CameraInputWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAINPUTWIDGET_H
