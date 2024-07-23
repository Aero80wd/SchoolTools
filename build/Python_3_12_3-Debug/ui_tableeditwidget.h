/********************************************************************************
** Form generated from reading UI file 'tableeditwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEEDITWIDGET_H
#define UI_TABLEEDITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clicklabel.h"

QT_BEGIN_NAMESPACE

class Ui_TableEditWidget
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QTimeEdit *timeEdit;
    QTimeEdit *timeEdit_2;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    ClickLabel *label;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox;
    QLabel *label_9;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_2;

    void setupUi(QWidget *TableEditWidget)
    {
        if (TableEditWidget->objectName().isEmpty())
            TableEditWidget->setObjectName("TableEditWidget");
        TableEditWidget->resize(698, 437);
        gridLayout = new QGridLayout(TableEditWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(TableEditWidget);
        widget_2->setObjectName("widget_2");
        widget_2->setStyleSheet(QString::fromUtf8("background:#1191d3;"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color:#ffffff;\n"
""));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_2);

        horizontalLayout_3->setStretch(0, 20);

        gridLayout->addWidget(widget_2, 0, 0, 1, 1);

        tabWidget = new QTabWidget(TableEditWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab{\n"
"background:#ffffff;\n"
"width:200%;\n"
"border-radius:3px;\n"
"border:1px solid #1191d3;\n"
"\n"
"padding:5px;\n"
"}\n"
"QTabBar::tab:hover{\n"
"background:rgb(217, 217, 217);\n"
"}\n"
"QTabBar::tab:selected{\n"
"color:#ffffff;\n"
"background:#1191d3;\n"
"}\n"
"QTabWidget::tab-bar{\n"
"alignment:center;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout_4 = new QHBoxLayout(tab);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(tab);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(25, 10, 25, 25);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"\n"
"border-bottom: 1px solid #1191d3;; /* \350\276\271\346\241\206\345\256\275\345\272\246\344\270\2721px\357\274\214\351\242\234\350\211\262\344\270\272#A0A0A0 */\n"
"	border-radius: 3px; /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"	padding-left: 5px; /* \346\226\207\346\234\254\350\267\235\347\246\273\345\267\246\350\276\271\347\225\214\346\234\2115px */\n"
"	background-color: #FAFAFA; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	color: #000000; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"	selection-background-color: #1191d3; /* \351\200\211\344\270\255\346\226\207\346\234\254\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	selection-color: #F2F2F2; /* \351\200\211\344\270\255\346\226\207\346\234\254\347\232\204\351\242\234\350\211\262 */\n"
"	font-family: \"Microsoft YaHei\"; /* \346\226\207\346\234\254\345\255\227\344\275\223\346\227\217 */\n"
"	font-size: 10pt; /* \346\226\207\346\234\254\345\255\227\344\275\223\345\244\247\345"
                        "\260\217 */\n"
"}\n"
"QLineEdit:hover,QLineEdit:editble{\n"
"border-bottom: 1px solid rgb(255, 58, 58);\n"
"}"));
        lineEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(lineEdit);

        timeEdit = new QTimeEdit(widget);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setStyleSheet(QString::fromUtf8("QDateTimeEdit{\n"
"\n"
"border-bottom: 1px solid #1191d3;; /* \350\276\271\346\241\206\345\256\275\345\272\246\344\270\2721px\357\274\214\351\242\234\350\211\262\344\270\272#A0A0A0 */\n"
"	border-radius: 3px; /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"	padding-left: 5px; /* \346\226\207\346\234\254\350\267\235\347\246\273\345\267\246\350\276\271\347\225\214\346\234\2115px */\n"
"	background-color: #FAFAFA; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	color: #000000; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"	selection-background-color: #1191d3; /* \351\200\211\344\270\255\346\226\207\346\234\254\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	selection-color: #F2F2F2; /* \351\200\211\344\270\255\346\226\207\346\234\254\347\232\204\351\242\234\350\211\262 */\n"
"	font-family: \"Microsoft YaHei\"; /* \346\226\207\346\234\254\345\255\227\344\275\223\346\227\217 */\n"
"	font-size: 10pt; /* \346\226\207\346\234\254\345\255\227\344\275\223\345\244\247"
                        "\345\260\217 */\n"
"}\n"
"QDateTimeEdit:hover{\n"
"border-bottom: 1px solid rgb(255, 58, 58);\n"
"}\n"
"QDateTimeEdit::down-button{\n"
"width:7px;\n"
"background:#F0F0F0;\n"
"border-image: url(\":/res/down.png\");\n"
"}\n"
"QDateTimeEdit::up-button{\n"
"width:7px;\n"
"background:#F0F0F0;\n"
"border-image: url(\":/res/up.png\");\n"
"}\n"
"QDateTimeEdit::down-button:hover{\n"
"background:#1191d3;\n"
"}\n"
"QDateTimeEdit::up-button:hover{\n"
"background:#1191d3;\n"
"}"));

        horizontalLayout->addWidget(timeEdit);

        timeEdit_2 = new QTimeEdit(widget);
        timeEdit_2->setObjectName("timeEdit_2");
        timeEdit_2->setStyleSheet(QString::fromUtf8("QDateTimeEdit{\n"
"\n"
"border-bottom: 1px solid #1191d3;; /* \350\276\271\346\241\206\345\256\275\345\272\246\344\270\2721px\357\274\214\351\242\234\350\211\262\344\270\272#A0A0A0 */\n"
"	border-radius: 3px; /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"	padding-left: 5px; /* \346\226\207\346\234\254\350\267\235\347\246\273\345\267\246\350\276\271\347\225\214\346\234\2115px */\n"
"	background-color: #FAFAFA; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	color: #000000; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"	selection-background-color: #1191d3; /* \351\200\211\344\270\255\346\226\207\346\234\254\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	selection-color: #F2F2F2; /* \351\200\211\344\270\255\346\226\207\346\234\254\347\232\204\351\242\234\350\211\262 */\n"
"	font-family: \"Microsoft YaHei\"; /* \346\226\207\346\234\254\345\255\227\344\275\223\346\227\217 */\n"
"	font-size: 10pt; /* \346\226\207\346\234\254\345\255\227\344\275\223\345\244\247"
                        "\345\260\217 */\n"
"}\n"
"QDateTimeEdit:hover{\n"
"border-bottom: 1px solid rgb(255, 58, 58);\n"
"}\n"
"QDateTimeEdit::down-button{\n"
"width:7px;\n"
"background:#F0F0F0;\n"
"border-image: url(\":/res/down.png\");\n"
"}\n"
"QDateTimeEdit::up-button{\n"
"width:7px;\n"
"background:#F0F0F0;\n"
"border-image: url(\":/res/up.png\");\n"
"}\n"
"QDateTimeEdit::down-button:hover{\n"
"background:#1191d3;\n"
"}\n"
"QDateTimeEdit::up-button:hover{\n"
"background:#1191d3;\n"
"}"));

        horizontalLayout->addWidget(timeEdit_2);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName("spinBox");
        spinBox->setStyleSheet(QString::fromUtf8("QSpinBox{\n"
"\n"
"border-bottom: 1px solid #1191d3;; /* \350\276\271\346\241\206\345\256\275\345\272\246\344\270\2721px\357\274\214\351\242\234\350\211\262\344\270\272#A0A0A0 */\n"
"	border-radius: 3px; /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"	padding-left: 5px; /* \346\226\207\346\234\254\350\267\235\347\246\273\345\267\246\350\276\271\347\225\214\346\234\2115px */\n"
"	background-color: #FAFAFA; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	color: #000000; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"	selection-background-color: #1191d3; /* \351\200\211\344\270\255\346\226\207\346\234\254\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	selection-color: #F2F2F2; /* \351\200\211\344\270\255\346\226\207\346\234\254\347\232\204\351\242\234\350\211\262 */\n"
"	font-family: \"Microsoft YaHei\"; /* \346\226\207\346\234\254\345\255\227\344\275\223\346\227\217 */\n"
"	font-size: 10pt; /* \346\226\207\346\234\254\345\255\227\344\275\223\345\244\247\345"
                        "\260\217 */\n"
"}\n"
"QSpinBox:hover{\n"
"border-bottom: 1px solid rgb(255, 58, 58);\n"
"}\n"
"QSpinBox::down-button{\n"
"width:7px;\n"
"background:#F0F0F0;\n"
"border-image: url(\":/res/down.png\");\n"
"}\n"
"QSpinBox::up-button{\n"
"width:7px;\n"
"background:#F0F0F0;\n"
"border-image: url(\":/res/up.png\");\n"
"}\n"
"QSpinBox::down-button:hover{\n"
"background:#1191d3;\n"
"}\n"
"QSpinBox::up-button:hover{\n"
"background:#1191d3;\n"
"}"));

        horizontalLayout->addWidget(spinBox);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"\n"
"border-bottom: 1px solid #1191d3;; /* \350\276\271\346\241\206\345\256\275\345\272\246\344\270\2721px\357\274\214\351\242\234\350\211\262\344\270\272#A0A0A0 */\n"
"	border-radius: 3px; /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"	\n"
"	background-color: #FAFAFA; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	color: #000000; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"	padding:3px;\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"border-bottom: 1px solid rgb(255, 58, 58);\n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(4, 2);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        radioButton = new QRadioButton(widget);
        radioButton->setObjectName("radioButton");
        radioButton->setStyleSheet(QString::fromUtf8("QRadioButton::indicator{\n"
"	width:15px;\n"
"	height:15px;\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked:hover{\n"
"	border-image:url(\":/radiobutton/radiobutton/hover.png\");\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"	border-image:url(\":/radiobutton/radiobutton/checked.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked{\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}"));
        radioButton->setChecked(true);

        horizontalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setStyleSheet(QString::fromUtf8("QRadioButton::indicator{\n"
"	width:15px;\n"
"	height:15px;\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked:hover{\n"
"	border-image:url(\":/radiobutton/radiobutton/hover.png\");\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"	border-image:url(\":/radiobutton/radiobutton/checked.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked{\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}"));

        horizontalLayout_2->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(widget);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setStyleSheet(QString::fromUtf8("QRadioButton::indicator{\n"
"	width:15px;\n"
"	height:15px;\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked:hover{\n"
"	border-image:url(\":/radiobutton/radiobutton/hover.png\");\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"	border-image:url(\":/radiobutton/radiobutton/checked.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked{\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}"));

        horizontalLayout_2->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(widget);
        radioButton_4->setObjectName("radioButton_4");
        radioButton_4->setStyleSheet(QString::fromUtf8("QRadioButton::indicator{\n"
"	width:15px;\n"
"	height:15px;\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked:hover{\n"
"	border-image:url(\":/radiobutton/radiobutton/hover.png\");\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"	border-image:url(\":/radiobutton/radiobutton/checked.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked{\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}"));

        horizontalLayout_2->addWidget(radioButton_4);

        radioButton_5 = new QRadioButton(widget);
        radioButton_5->setObjectName("radioButton_5");
        radioButton_5->setStyleSheet(QString::fromUtf8("QRadioButton::indicator{\n"
"	width:15px;\n"
"	height:15px;\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked:hover{\n"
"	border-image:url(\":/radiobutton/radiobutton/hover.png\");\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"	border-image:url(\":/radiobutton/radiobutton/checked.png\");\n"
"}\n"
"QRadioButton::indicator:unchecked{\n"
"	border-image:url(\":/radiobutton/radiobutton/stable.png\");\n"
"}"));

        horizontalLayout_2->addWidget(radioButton_5);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(widget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem7);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget{\n"
"background:#ffffff;\n"
"border-radius:10px;\n"
"}\n"
"QTableWidget::item{\n"
"border:none;\n"
"border-radius:3px;\n"
"}\n"
"QTableWidget::item:selected{\n"
"background:#1191d3;\n"
"}\n"
"QTableWidget::item:hover{\n"
"color:#000000;\n"
"background:rgb(217, 217, 217);\n"
"}\n"
"QHeaderView::section{\n"
"border:1px solid white;\n"
"border-radius:3px;\n"
"text-align:center;\n"
"background:#1191d3;\n"
"padding:3px;\n"
"color:#ffffff;\n"
"}\n"
"QScrollBar::handle:vertical{\n"
"background:#1191d3;\n"
"\n"
"}"));

        verticalLayout->addWidget(tableWidget);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 5);
        verticalLayout->setStretch(2, 45);

        horizontalLayout_4->addWidget(widget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new ClickLabel(tab_2);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("image:url(\":/res/a.png\")"));

        horizontalLayout_5->addWidget(label);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(tab_2);
        label_3->setObjectName("label_3");
        QFont font1;
        font1.setPointSize(28);
        label_3->setFont(font1);

        verticalLayout_3->addWidget(label_3);

        label_4 = new QLabel(tab_2);
        label_4->setObjectName("label_4");
        QFont font2;
        font2.setPointSize(18);
        label_4->setFont(font2);

        verticalLayout_3->addWidget(label_4);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        verticalLayout_3->addWidget(label_5);

        verticalLayout_3->setStretch(0, 3);
        verticalLayout_3->setStretch(1, 3);
        verticalLayout_3->setStretch(2, 3);

        horizontalLayout_5->addLayout(verticalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName("label_6");
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayout_2->setStretch(1, 10);
        verticalLayout_2->setStretch(3, 11);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        horizontalLayout_6 = new QHBoxLayout(tab_3);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        checkBox_2 = new QCheckBox(tab_3);
        checkBox_2->setObjectName("checkBox_2");
        QFont font3;
        font3.setPointSize(11);
        checkBox_2->setFont(font3);
        checkBox_2->setStyleSheet(QString::fromUtf8("QCheckBox{\n"
"border:none;\n"
"}\n"
"\n"
"QCheckBox::indicator{/*\351\200\211\346\213\251\346\241\206\345\260\272\345\257\270*/\n"
"    border: 0px solid #b1b1b1;\n"
"	width: 50px;\n"
"	height: 50px;\n"
"}\n"
"QCheckBox::indicator:unchecked{\n"
"image:url(\":/res/checkbutton/unchecked.png\");\n"
"}\n"
"QCheckBox::indicator:checked{\n"
"image:url(\":/res/checkbutton/checked.png\");\n"
"}\n"
"QCheckBox:hover{\n"
"color:#1191d3;\n"
"}"));

        horizontalLayout_7->addWidget(checkBox_2);

        checkBox = new QCheckBox(tab_3);
        checkBox->setObjectName("checkBox");
        checkBox->setFont(font3);
        checkBox->setStyleSheet(QString::fromUtf8("QCheckBox{\n"
"border:none;\n"
"}\n"
"\n"
"QCheckBox::indicator{/*\351\200\211\346\213\251\346\241\206\345\260\272\345\257\270*/\n"
"    border: 0px solid #b1b1b1;\n"
"	width: 50px;\n"
"	height: 50px;\n"
"}\n"
"QCheckBox::indicator:unchecked{\n"
"image:url(\":/res/checkbutton/unchecked.png\");\n"
"}\n"
"QCheckBox::indicator:checked{\n"
"image:url(\":/res/checkbutton/checked.png\");\n"
"}\n"
"QCheckBox:hover{\n"
"color:#1191d3;\n"
"}"));

        horizontalLayout_7->addWidget(checkBox);


        verticalLayout_4->addLayout(horizontalLayout_7);

        label_9 = new QLabel(tab_3);
        label_9->setObjectName("label_9");
        label_9->setFont(font);

        verticalLayout_4->addWidget(label_9);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        pushButton_2 = new QPushButton(tab_3);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"\n"
"border-bottom: 1px solid #1191d3;; /* \350\276\271\346\241\206\345\256\275\345\272\246\344\270\2721px\357\274\214\351\242\234\350\211\262\344\270\272#A0A0A0 */\n"
"	border-radius: 3px; /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"	\n"
"	background-color: #FAFAFA; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	color: #000000; /* \346\226\207\346\234\254\351\242\234\350\211\262 */\n"
"	padding:3px;\n"
"\n"
"}\n"
"QPushButton:hover{\n"
"border-bottom: 1px solid rgb(255, 58, 58);\n"
"}\n"
""));

        horizontalLayout_9->addWidget(pushButton_2);

        horizontalLayout_9->setStretch(0, 1);

        verticalLayout_4->addLayout(horizontalLayout_9);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 2);
        verticalLayout_4->setStretch(2, 5);
        verticalLayout_4->setStretch(3, 1);

        horizontalLayout_6->addLayout(verticalLayout_4);

        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 20);

        retranslateUi(TableEditWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TableEditWidget);
    } // setupUi

    void retranslateUi(QWidget *TableEditWidget)
    {
        TableEditWidget->setWindowTitle(QCoreApplication::translate("TableEditWidget", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("TableEditWidget", "\350\256\276\347\275\256", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("TableEditWidget", "\350\276\223\345\205\245\345\220\215\347\247\260", nullptr));
#if QT_CONFIG(tooltip)
        timeEdit->setToolTip(QCoreApplication::translate("TableEditWidget", "\350\276\223\345\205\245\344\270\212\350\257\276\346\227\266\351\227\264", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        timeEdit_2->setToolTip(QCoreApplication::translate("TableEditWidget", "\350\276\223\345\205\245\344\270\213\350\257\276\346\227\266\351\227\264", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinBox->setToolTip(QCoreApplication::translate("TableEditWidget", "\350\276\223\345\205\245\347\246\273\344\270\212\350\257\276\347\232\204\350\257\276\351\227\264\346\227\266\351\227\264", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton->setText(QCoreApplication::translate("TableEditWidget", "\346\267\273\345\212\240", nullptr));
        radioButton->setText(QCoreApplication::translate("TableEditWidget", "\345\221\250\344\270\200", nullptr));
        radioButton_2->setText(QCoreApplication::translate("TableEditWidget", "\345\221\250\344\272\214", nullptr));
        radioButton_3->setText(QCoreApplication::translate("TableEditWidget", "\345\221\250\344\270\211", nullptr));
        radioButton_4->setText(QCoreApplication::translate("TableEditWidget", "\345\221\250\345\233\233", nullptr));
        radioButton_5->setText(QCoreApplication::translate("TableEditWidget", "\345\221\250\344\272\224", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TableEditWidget", "\350\257\276\347\250\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TableEditWidget", "\344\270\212\350\257\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TableEditWidget", "\344\270\213\350\257\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TableEditWidget", "\350\257\276\351\227\264\346\227\266\351\227\264", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TableEditWidget", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("TableEditWidget", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("TableEditWidget", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("TableEditWidget", "1", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("TableEditWidget", "\350\257\276\347\250\213\350\241\250\350\256\276\347\275\256", nullptr));
        label->setText(QString());
        label_3->setText(QCoreApplication::translate("TableEditWidget", "\350\257\276\347\250\213\350\241\250", nullptr));
        label_4->setText(QCoreApplication::translate("TableEditWidget", "\347\211\210\346\234\2542.0", nullptr));
        label_5->setText(QCoreApplication::translate("TableEditWidget", "Powered By Aero8m", nullptr));
        label_6->setText(QCoreApplication::translate("TableEditWidget", "\345\237\272\344\272\216Qt 6.2.4 \347\274\226\345\206\231", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("TableEditWidget", "\345\205\263\344\272\216", nullptr));
        checkBox_2->setText(QCoreApplication::translate("TableEditWidget", "\346\211\223\345\274\200\345\217\243\345\220\220\350\212\254\350\212\263", nullptr));
        checkBox->setText(QCoreApplication::translate("TableEditWidget", "\346\211\223\345\274\200\346\234\250\351\261\274", nullptr));
        label_9->setText(QCoreApplication::translate("TableEditWidget", "\344\277\256\346\224\271\350\256\276\347\275\256\345\220\216\350\257\267\351\207\215\345\220\257\347\250\213\345\272\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TableEditWidget", "\345\205\263\351\227\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("TableEditWidget", "\345\275\251\350\233\213\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TableEditWidget: public Ui_TableEditWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEEDITWIDGET_H
