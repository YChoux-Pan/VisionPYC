/********************************************************************************
** Form generated from reading UI file 'CameraInpputWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAINPPUTWIDGET_H
#define UI_CAMERAINPPUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraInpputWidgetClass
{
public:

    void setupUi(QWidget *CameraInpputWidgetClass)
    {
        if (CameraInpputWidgetClass->objectName().isEmpty())
            CameraInpputWidgetClass->setObjectName("CameraInpputWidgetClass");
        CameraInpputWidgetClass->resize(600, 400);

        retranslateUi(CameraInpputWidgetClass);

        QMetaObject::connectSlotsByName(CameraInpputWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *CameraInpputWidgetClass)
    {
        CameraInpputWidgetClass->setWindowTitle(QCoreApplication::translate("CameraInpputWidgetClass", "CameraInpputWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraInpputWidgetClass: public Ui_CameraInpputWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAINPPUTWIDGET_H
