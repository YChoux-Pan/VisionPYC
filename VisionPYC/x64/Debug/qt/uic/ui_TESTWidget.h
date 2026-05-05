/********************************************************************************
** Form generated from reading UI file 'TESTWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWIDGET_H
#define UI_TESTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include <operatorbutton.h>

QT_BEGIN_NAMESPACE

class Ui_TESTWidgetClass
{
public:
    QGridLayout *gridLayout;
    OperatorButton *pushButton;
    OperatorButton *pushButton_2;

    void setupUi(QWidget *TESTWidgetClass)
    {
        if (TESTWidgetClass->objectName().isEmpty())
            TESTWidgetClass->setObjectName("TESTWidgetClass");
        TESTWidgetClass->resize(600, 400);
        gridLayout = new QGridLayout(TESTWidgetClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        pushButton = new OperatorButton(TESTWidgetClass);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new OperatorButton(TESTWidgetClass);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);


        retranslateUi(TESTWidgetClass);

        QMetaObject::connectSlotsByName(TESTWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *TESTWidgetClass)
    {
        TESTWidgetClass->setWindowTitle(QCoreApplication::translate("TESTWidgetClass", "TESTWidget", nullptr));
        pushButton->setText(QCoreApplication::translate("TESTWidgetClass", "\346\265\213\350\257\2251", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TESTWidgetClass", "\346\265\213\350\257\2252", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TESTWidgetClass: public Ui_TESTWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWIDGET_H
