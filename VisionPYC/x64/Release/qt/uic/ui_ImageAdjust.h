/********************************************************************************
** Form generated from reading UI file 'ImageAdjust.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEADJUST_H
#define UI_IMAGEADJUST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageAdjust
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *ColorToGray;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QWidget *ImageMirror;

    void setupUi(QWidget *ImageAdjust)
    {
        if (ImageAdjust->objectName().isEmpty())
            ImageAdjust->setObjectName("ImageAdjust");
        ImageAdjust->resize(299, 327);
        verticalLayout = new QVBoxLayout(ImageAdjust);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(ImageAdjust);
        stackedWidget->setObjectName("stackedWidget");
        ColorToGray = new QWidget();
        ColorToGray->setObjectName("ColorToGray");
        gridLayout = new QGridLayout(ColorToGray);
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(ColorToGray);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(ColorToGray);
        comboBox_2->setObjectName("comboBox_2");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy1);
        comboBox_2->setMinimumSize(QSize(30, 30));
        comboBox_2->setStyleSheet(QString::fromUtf8("\n"
"QComboBox::down-arrow {\n"
"    /* 1. \345\274\225\345\205\245\344\275\240\347\232\204 SVG \350\265\204\346\272\220\350\267\257\345\276\204\357\274\210\350\257\267\346\233\277\346\215\242\344\270\272\344\275\240\351\241\271\347\233\256\344\270\255\347\234\237\345\256\236\347\232\204 qrc \350\265\204\346\272\220\350\267\257\345\276\204\357\274\211 */\n"
"    qproperty-icon:url(:/icon/icon/arrow-down-s-fill.svg);\n"
"    \n"
"    /* 2. \347\262\276\345\207\206\346\216\247\345\210\266 SVG \345\234\250\350\276\223\345\205\245\346\241\206\345\217\263\344\276\247\346\230\276\347\244\272\347\232\204\345\244\247\345\260\217 */\n"
"    width: 14px;                        /* \360\237\221\210 \351\231\220\345\210\266 SVG \347\232\204\347\211\251\347\220\206\346\230\276\347\244\272\345\256\275\345\272\246 */\n"
"    height: 14px;                       /* \360\237\221\210 \351\231\220\345\210\266 SVG \347\232\204\347\211\251\347\220\206\346\230\276\347\244\272\351\253\230\345\272\246 */\n"
"}"));

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 1);

        label = new QLabel(ColorToGray);
        label->setObjectName("label");
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(30, 0));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(ColorToGray);
        comboBox->setObjectName("comboBox");
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(30, 30));
        comboBox->setStyleSheet(QString::fromUtf8("\n"
"QComboBox::down-arrow {\n"
"    /* 1. \345\274\225\345\205\245\344\275\240\347\232\204 SVG \350\265\204\346\272\220\350\267\257\345\276\204\357\274\210\350\257\267\346\233\277\346\215\242\344\270\272\344\275\240\351\241\271\347\233\256\344\270\255\347\234\237\345\256\236\347\232\204 qrc \350\265\204\346\272\220\350\267\257\345\276\204\357\274\211 */\n"
"    qproperty-icon:url(:/icon/icon/arrow-down-s-fill.svg);\n"
"    \n"
"    /* 2. \347\262\276\345\207\206\346\216\247\345\210\266 SVG \345\234\250\350\276\223\345\205\245\346\241\206\345\217\263\344\276\247\346\230\276\347\244\272\347\232\204\345\244\247\345\260\217 */\n"
"    width: 14px;                        /* \360\237\221\210 \351\231\220\345\210\266 SVG \347\232\204\347\211\251\347\220\206\346\230\276\347\244\272\345\256\275\345\272\246 */\n"
"    height: 14px;                       /* \360\237\221\210 \351\231\220\345\210\266 SVG \347\232\204\347\211\251\347\220\206\346\230\276\347\244\272\351\253\230\345\272\246 */\n"
"}"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 234, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 2);

        gridLayout->setColumnStretch(0, 3);
        gridLayout->setColumnStretch(1, 7);
        stackedWidget->addWidget(ColorToGray);
        ImageMirror = new QWidget();
        ImageMirror->setObjectName("ImageMirror");
        stackedWidget->addWidget(ImageMirror);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(ImageAdjust);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ImageAdjust);
    } // setupUi

    void retranslateUi(QWidget *ImageAdjust)
    {
        ImageAdjust->setWindowTitle(QCoreApplication::translate("ImageAdjust", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("ImageAdjust", "\350\275\254\345\214\226\347\261\273\345\236\213:", nullptr));
        label->setText(QCoreApplication::translate("ImageAdjust", "\350\275\254\345\214\226\347\261\273\345\236\213:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageAdjust: public Ui_ImageAdjust {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEADJUST_H
