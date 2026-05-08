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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraInputWidgetClass
{
public:
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
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
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QRadioButton *m_rad_4;
    QStackedWidget *stackedWidget_2;
    QWidget *page_5;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QToolButton *toolButton;
    QWidget *page_4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEdit_2;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QRadioButton *m_rad_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *m_page_2;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox;
    QLineEdit *lineEdit_3;
    QToolButton *toolButton_4;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QLabel *label_4;
    QCheckBox *checkBox_2;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QListView *listView;
    QWidget *m_page_3;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QWidget *tab_2;
    QWidget *tab_3;

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
        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);

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
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(100, 20));
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(100, 20));
        label_2->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(120, 0));
        pushButton->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(120, 0));
        pushButton_2->setMaximumSize(QSize(120, 40));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName("pushButton_3");
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(120, 0));
        pushButton_3->setMaximumSize(QSize(120, 40));
        pushButton_3->setSizeIncrement(QSize(120, 40));

        horizontalLayout_2->addWidget(pushButton_3);


        gridLayout->addWidget(frame, 1, 0, 1, 2);

        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMaximumSize(QSize(280, 16777215));
        tabWidget->setSizeIncrement(QSize(280, 0));
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        m_rad_1 = new QRadioButton(widget_2);
        m_rad_1->setObjectName("m_rad_1");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_rad_1->sizePolicy().hasHeightForWidth());
        m_rad_1->setSizePolicy(sizePolicy1);
        m_rad_1->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_rad_1);

        m_rad_2 = new QRadioButton(widget_2);
        m_rad_2->setObjectName("m_rad_2");
        sizePolicy1.setHeightForWidth(m_rad_2->sizePolicy().hasHeightForWidth());
        m_rad_2->setSizePolicy(sizePolicy1);
        m_rad_2->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_rad_2);

        m_rad_3 = new QRadioButton(widget_2);
        m_rad_3->setObjectName("m_rad_3");
        sizePolicy1.setHeightForWidth(m_rad_3->sizePolicy().hasHeightForWidth());
        m_rad_3->setSizePolicy(sizePolicy1);
        m_rad_3->setMinimumSize(QSize(80, 0));

        horizontalLayout->addWidget(m_rad_3);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addWidget(widget_2);

        stackedWidget = new QStackedWidget(tab);
        stackedWidget->setObjectName("stackedWidget");
        m_page_1 = new QWidget();
        m_page_1->setObjectName("m_page_1");
        verticalLayout_5 = new QVBoxLayout(m_page_1);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        groupBox_4 = new QGroupBox(m_page_1);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget_4 = new QWidget(groupBox_4);
        widget_4->setObjectName("widget_4");
        gridLayout_2 = new QGridLayout(widget_4);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);

        m_rad_4 = new QRadioButton(widget_4);
        m_rad_4->setObjectName("m_rad_4");

        gridLayout_2->addWidget(m_rad_4, 1, 0, 1, 1);

        stackedWidget_2 = new QStackedWidget(widget_4);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setMaximumSize(QSize(16777215, 40));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        horizontalLayout_4 = new QHBoxLayout(page_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        lineEdit = new QLineEdit(page_5);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_4->addWidget(lineEdit);

        toolButton = new QToolButton(page_5);
        toolButton->setObjectName("toolButton");

        horizontalLayout_4->addWidget(toolButton);

        stackedWidget_2->addWidget(page_5);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        horizontalLayout_5 = new QHBoxLayout(page_4);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        lineEdit_2 = new QLineEdit(page_4);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout_5->addWidget(lineEdit_2);

        toolButton_2 = new QToolButton(page_4);
        toolButton_2->setObjectName("toolButton_2");

        horizontalLayout_5->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(page_4);
        toolButton_3->setObjectName("toolButton_3");

        horizontalLayout_5->addWidget(toolButton_3);

        stackedWidget_2->addWidget(page_4);

        gridLayout_2->addWidget(stackedWidget_2, 2, 0, 1, 2);

        m_rad_5 = new QRadioButton(widget_4);
        m_rad_5->setObjectName("m_rad_5");

        gridLayout_2->addWidget(m_rad_5, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 0, 1, 1);


        verticalLayout_2->addWidget(widget_4);


        verticalLayout_5->addWidget(groupBox_4);

        stackedWidget->addWidget(m_page_1);
        m_page_2 = new QWidget();
        m_page_2->setObjectName("m_page_2");
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

        lineEdit_3 = new QLineEdit(widget_5);
        lineEdit_3->setObjectName("lineEdit_3");

        horizontalLayout_6->addWidget(lineEdit_3);

        toolButton_4 = new QToolButton(widget_5);
        toolButton_4->setObjectName("toolButton_4");

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
        label_3 = new QLabel(widget_6);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(25, 0));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_3);

        label_4 = new QLabel(widget_6);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(25, 0));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_4);

        checkBox_2 = new QCheckBox(widget_6);
        checkBox_2->setObjectName("checkBox_2");
        sizePolicy.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
        checkBox_2->setSizePolicy(sizePolicy);
        checkBox_2->setMinimumSize(QSize(60, 0));

        horizontalLayout_7->addWidget(checkBox_2);

        label_5 = new QLabel(widget_6);
        label_5->setObjectName("label_5");
        label_5->setMinimumSize(QSize(25, 0));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_5);

        label_6 = new QLabel(widget_6);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(25, 0));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(widget_6);

        listView = new QListView(groupBox_3);
        listView->setObjectName("listView");

        verticalLayout_3->addWidget(listView);


        horizontalLayout_8->addWidget(groupBox_3);

        stackedWidget->addWidget(m_page_2);
        m_page_3 = new QWidget();
        m_page_3->setObjectName("m_page_3");
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
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(widget);


        retranslateUi(CameraInputWidgetClass);

        tabWidget->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(1);
        stackedWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CameraInputWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *CameraInputWidgetClass)
    {
        CameraInputWidgetClass->setWindowTitle(QCoreApplication::translate("CameraInputWidgetClass", "CameraInputWidget", nullptr));
        label->setText(QCoreApplication::translate("CameraInputWidgetClass", "\350\200\227\346\227\266:%d", nullptr));
        label_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\212\266\346\200\201\357\274\232\346\234\252\347\237\245", nullptr));
        pushButton->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\211\247\350\241\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\241\256\345\256\232", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CameraInputWidgetClass", "\345\217\226\346\266\210", nullptr));
        m_rad_1->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\214\207\345\256\232\345\233\276\345\203\217", nullptr));
        m_rad_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\226\207\344\273\266\347\233\256\345\275\225", nullptr));
        m_rad_3->setText(QCoreApplication::translate("CameraInputWidgetClass", "\347\233\270\346\234\272", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("CameraInputWidgetClass", "\346\214\207\345\256\232\345\233\276\345\203\217", nullptr));
        m_rad_4->setText(QCoreApplication::translate("CameraInputWidgetClass", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        toolButton->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        toolButton_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        m_rad_5->setText(QCoreApplication::translate("CameraInputWidgetClass", "\351\223\276\346\216\245\350\267\257\345\276\204", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CameraInputWidgetClass", "\346\226\207\344\273\266\347\233\256\345\275\225", nullptr));
        checkBox->setText(QCoreApplication::translate("CameraInputWidgetClass", "\345\276\252\347\216\257", nullptr));
        toolButton_4->setText(QCoreApplication::translate("CameraInputWidgetClass", "...", nullptr));
        label_3->setText(QCoreApplication::translate("CameraInputWidgetClass", "\344\270\212", nullptr));
        label_4->setText(QCoreApplication::translate("CameraInputWidgetClass", "\344\270\213", nullptr));
        checkBox_2->setText(QCoreApplication::translate("CameraInputWidgetClass", "\350\207\252\345\212\250\345\210\207\346\215\242", nullptr));
        label_5->setText(QCoreApplication::translate("CameraInputWidgetClass", "\346\227\266\351\227\264", nullptr));
        label_6->setText(QCoreApplication::translate("CameraInputWidgetClass", "A-Z", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CameraInputWidgetClass", "\347\233\270\346\234\272\346\250\241\345\274\217", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CameraInputWidgetClass", "\345\205\211\346\272\220\351\200\232\350\256\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("CameraInputWidgetClass", "\345\237\272\346\234\254\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("CameraInputWidgetClass", "\345\233\276\345\203\217\345\217\202\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("CameraInputWidgetClass", "\345\205\266\344\273\226\345\217\202\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraInputWidgetClass: public Ui_CameraInputWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAINPUTWIDGET_H
