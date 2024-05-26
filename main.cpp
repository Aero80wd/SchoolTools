#include "maintablewidget.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("课程表");
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TodayCurriculum_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainTableWidget w;


    // w.setEditWindow(&EditWindow);
    w.show();
    QScreen *scr = a.primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    w.move((scr_w - w.width()) / 2*1.1, (scr_h - w.height()) / 300);

    return a.exec();
}
