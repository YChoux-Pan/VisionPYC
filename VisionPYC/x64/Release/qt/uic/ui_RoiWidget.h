/********************************************************************************
** Form generated from reading UI file 'RoiWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROIWIDGET_H
#define UI_ROIWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoiWidgetClass
{
public:

    void setupUi(QWidget *RoiWidgetClass)
    {
        if (RoiWidgetClass->objectName().isEmpty())
            RoiWidgetClass->setObjectName("RoiWidgetClass");
        RoiWidgetClass->resize(600, 400);

        retranslateUi(RoiWidgetClass);

        QMetaObject::connectSlotsByName(RoiWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *RoiWidgetClass)
    {
        RoiWidgetClass->setWindowTitle(QCoreApplication::translate("RoiWidgetClass", "RoiWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoiWidgetClass: public Ui_RoiWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROIWIDGET_H
