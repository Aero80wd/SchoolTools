#include "maintablewidget.h"
#include "toolbox.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
bool ToolBoxisOpen(){
    QFile file(QDir::currentPath() + "/config.json");
    file.open(QIODevice::ReadWrite | QIODevice::Text);

    QTextStream stream(&file);
    QString file_str = stream.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument jsondoc = QJsonDocument::fromJson(file_str.toUtf8(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError && !jsondoc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
        qDebug("OPne");
        return true;
    }
    QJsonObject Config = jsondoc.object();
    if (Config.contains("toolbox_status")){
        qDebug("Colse");
        return !Config["toolbox_status"].toBool();
    }
    qDebug("OPne");
    return true;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("校园悬浮窗");
    QApplication::setQuitOnLastWindowClosed(false);

    MainTableWidget w;
    w.show();
    QScreen *scr = a.primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    w.move((scr_w - w.width()) / 2*1.1, (scr_h - w.height()) / 9999999999999999999);
    ToolBox tb;
    tb.move((scr_w - tb.width()) * 0.9975, (scr_h - tb.height()) / 2*0.9);
    if (ToolBoxisOpen()){
        tb.show();
    }

    return a.exec();
}
