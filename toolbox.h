#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QtTest/QTest>
#include<QKeyEvent>
#include <windows.h>
#include<QCoreApplication>
#include<QDir>
#include<QLibrary>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonParseError>
#include<QtWebEngineWidgets>
#include"clicklabel.h"


namespace Ui {
class ToolBox;
}

class ToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBox(QWidget *parent = nullptr);
    ~ToolBox();
    void LoadPlugins();
    void setWidgetBlur(QWidget* widget);

private:
    Ui::ToolBox *ui;
};

#endif // TOOLBOX_H
