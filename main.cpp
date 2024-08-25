#include "maintablewidget.h"
#include "toolbox.h"
#include"daytimerwidget.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include<QDir>
#include<QDateTime>
#include<QProcess>
#include"AppLog.h"
bool ToolBoxisOpen(){
    QFile file(QDir::currentPath() + "/config.json");
    file.open(QIODevice::ReadWrite | QIODevice::Text);

    QTextStream stream(&file);
    QString file_str = stream.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument jsondoc = QJsonDocument::fromJson(file_str.toUtf8(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError && !jsondoc.isNull()) {
        showLog("Config.json is Error!",LogStatus::ERR);
        return true;
    }
    QJsonObject Config = jsondoc.object();
    if (Config.contains("toolbox_status")){
        showLog("ToolBox is Not Show",LogStatus::INFO);
        return !Config["toolbox_status"].toBool();
    }
    showLog("ToolBox is Show",LogStatus::INFO);
    return true;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationDisplayName("校园悬浮窗");
    QApplication::setQuitOnLastWindowClosed(false);
    showLog("MainWindow is Show",LogStatus::INFO);
    MainTableWidget *w = new MainTableWidget();
    w->show();

    QScreen *scr = a.primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    w->move((scr_w - w->width()) / 2*1.1, (scr_h - w->height()) / 9999999999999999999);
    ToolBox *tb = new ToolBox();
    tb->move((scr_w - tb->width()) * 0.9975, (scr_h - tb->height()) / 2*0.9);
    if (ToolBoxisOpen()){
        tb->show();
    }
    DayTimerWidget *dtw = new DayTimerWidget();
    dtw->move((scr_w - dtw->width())*1.55,(scr_h - dtw->height()) * 0.95);
    dtw->show();
    QObject::connect(w->EditWindow,&TableEditWidget::refechToolBar_signal,tb,&ToolBox::LoadPlugins);
    return a.exec();
}
