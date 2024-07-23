#include "maintablewidget.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("校园悬浮窗");

    MainTableWidget w;
    w.show();
    QScreen *scr = a.primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    w.move((scr_w - w.width()) / 2*1.1, (scr_h - w.height()) / 9999999999999999999);

    return a.exec();
}
