/********************************************************************************
** Form generated from reading UI file 'yiyandialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YIYANDIALOG_H
#define UI_YIYANDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clicklabel.h"
#include "rolling_label.h"

QT_BEGIN_NAMESPACE

class Ui_yiyanDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    ClickLabel *label;
    ClickLabel *label_5;
    ClickLabel *label_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    RollingLabel *label_3;
    RollingLabel *label_4;
    QLabel *show_tags;

    void setupUi(QDialog *yiyanDialog)
    {
        if (yiyanDialog->objectName().isEmpty())
            yiyanDialog->setObjectName("yiyanDialog");
        yiyanDialog->resize(619, 176);
        verticalLayout = new QVBoxLayout(yiyanDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, -1);
        widget = new QWidget(yiyanDialog);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background:#1191d3;"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new ClickLabel(widget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:#ffffff"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        label_5 = new ClickLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("ClickLabel{\n"
"image:url(\":/res/refech.png\");\n"
"}\n"
"ClickLabel:hover{\n"
"background:rgb(255, 58, 58);\n"
"}"));

        horizontalLayout->addWidget(label_5);

        label_2 = new ClickLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("ClickLabel{\n"
"image:url(\":/res/cha.png\");\n"
"}\n"
"ClickLabel:hover{\n"
"background:rgb(255, 58, 58);\n"
"}"));

        horizontalLayout->addWidget(label_2);

        horizontalLayout->setStretch(0, 30);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 2);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);

        frame = new QFrame(yiyanDialog);
        frame->setObjectName("frame");
        frame->setStyleSheet(QString::fromUtf8("background:#ffffff;"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new RollingLabel(frame);
        label_3->setObjectName("label_3");
        QFont font1;
        font1.setPointSize(18);
        label_3->setFont(font1);

        verticalLayout_3->addWidget(label_3);

        label_4 = new RollingLabel(frame);
        label_4->setObjectName("label_4");
        QFont font2;
        font2.setPointSize(14);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_3->addWidget(label_4);

        show_tags = new QLabel(frame);
        show_tags->setObjectName("show_tags");
        show_tags->setFont(font);

        verticalLayout_3->addWidget(show_tags);

        verticalLayout_3->setStretch(0, 3);
        verticalLayout_3->setStretch(1, 1);

        verticalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_2->setStretch(0, 1);

        verticalLayout->addWidget(frame);

        verticalLayout->setStretch(0, 1600);
        verticalLayout->setStretch(1, 7000);

        retranslateUi(yiyanDialog);

        QMetaObject::connectSlotsByName(yiyanDialog);
    } // setupUi

    void retranslateUi(QDialog *yiyanDialog)
    {
        yiyanDialog->setWindowTitle(QCoreApplication::translate("yiyanDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("yiyanDialog", "\344\270\200\350\250\200", nullptr));
        label_5->setText(QString());
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("yiyanDialog", "\345\212\240\350\275\275\344\270\255......", nullptr));
        label_4->setText(QCoreApplication::translate("yiyanDialog", "\345\212\240\350\275\275\344\270\255......", nullptr));
        show_tags->setText(QCoreApplication::translate("yiyanDialog", "Tags:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class yiyanDialog: public Ui_yiyanDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YIYANDIALOG_H
