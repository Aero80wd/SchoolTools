/********************************************************************************
** Form generated from reading UI file 'maintablewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINTABLEWIDGET_H
#define UI_MAINTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "clicklabel.h"
#include "rolling_label.h"

QT_BEGIN_NAMESPACE

class Ui_MainTableWidget
{
public:
    QPushButton *label_2;
    QPushButton *label;
    RollingLabel *pushButton_2;
    QLabel *pushButton;
    QLabel *table_show;
    QLabel *table_show_2;
    RollingLabel *pushButton_3;
    QPushButton *muyu;
    ClickLabel *down_button;
    QLabel *label_3;

    void setupUi(QWidget *MainTableWidget)
    {
        if (MainTableWidget->objectName().isEmpty())
            MainTableWidget->setObjectName("MainTableWidget");
        MainTableWidget->resize(781, 70);
        label_2 = new QPushButton(MainTableWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(17, 14, 25, 25));
        label_2->setStyleSheet(QString::fromUtf8("border-image:url(\":/res/a.png\");"));
        label = new QPushButton(MainTableWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(684, 15, 25, 25));
        label->setStyleSheet(QString::fromUtf8("border-image:url(\":/res/speak.png\");"));
        pushButton_2 = new RollingLabel(MainTableWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(679, 10, 35, 35));
        QFont font;
        font.setPointSize(14);
        pushButton_2->setFont(font);
        pushButton_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,0.5);\n"
"border-radius:17px;\n"
"color:#1191d3;"));
        pushButton_2->setAlignment(Qt::AlignCenter);
        pushButton = new QLabel(MainTableWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(560, 10, 111, 35));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,0.5);\n"
"border-radius:17px;\n"
"color:#caa257;"));
        pushButton->setAlignment(Qt::AlignCenter);
        table_show = new QLabel(MainTableWidget);
        table_show->setObjectName("table_show");
        table_show->setGeometry(QRect(52, 10, 501, 35));
        table_show->setFont(font);
        table_show->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,0.5);border-radius:17px;color:#caa257;"));
        table_show->setAlignment(Qt::AlignCenter);
        table_show_2 = new QLabel(MainTableWidget);
        table_show_2->setObjectName("table_show_2");
        table_show_2->setGeometry(QRect(12, 10, 35, 35));
        table_show_2->setFont(font);
        table_show_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,0.5);\n"
"border-radius:17px;\n"
"color:#caa257;"));
        pushButton_3 = new RollingLabel(MainTableWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(720, 10, 35, 35));
        pushButton_3->setFont(font);
        pushButton_3->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,0.5);\n"
"border-radius:17px;\n"
"color:#1191d3;"));
        pushButton_3->setAlignment(Qt::AlignCenter);
        muyu = new QPushButton(MainTableWidget);
        muyu->setObjectName("muyu");
        muyu->setGeometry(QRect(728, 18, 19, 19));
        muyu->setStyleSheet(QString::fromUtf8("border-image:url(\":/res/muyu.png\");"));
        down_button = new ClickLabel(MainTableWidget);
        down_button->setObjectName("down_button");
        down_button->setGeometry(QRect(293, 52, 191, 7));
        down_button->setStyleSheet(QString::fromUtf8("background:white;\n"
"border-radius: 5px;\n"
""));
        label_3 = new QLabel(MainTableWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(750, 10, 40, 12));
        label_3->setStyleSheet(QString::fromUtf8("color:rgba(0,0,0,0)"));
        pushButton_2->raise();
        label->raise();
        pushButton->raise();
        table_show->raise();
        table_show_2->raise();
        label_2->raise();
        pushButton_3->raise();
        muyu->raise();
        down_button->raise();
        label_3->raise();

        retranslateUi(MainTableWidget);

        QMetaObject::connectSlotsByName(MainTableWidget);
    } // setupUi

    void retranslateUi(QWidget *MainTableWidget)
    {
        MainTableWidget->setWindowTitle(QCoreApplication::translate("MainTableWidget", "MainTableWidget", nullptr));
        label_2->setText(QString());
        label->setText(QString());
        pushButton_2->setText(QString());
        pushButton->setText(QString());
        table_show->setText(QString());
        table_show_2->setText(QString());
        pushButton_3->setText(QString());
        muyu->setText(QString());
        down_button->setText(QString());
        label_3->setText(QCoreApplication::translate("MainTableWidget", "\345\212\237\345\276\267+1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainTableWidget: public Ui_MainTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINTABLEWIDGET_H
