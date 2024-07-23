QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animationlabelup.cpp \
    anishow_label.cpp \
    clicklabel.cpp \
    getstartwidget.cpp \
    main.cpp \
    maintablewidget.cpp \
    mainwindow.cpp \
    qcustomtimer.cpp \
    rolling_label.cpp \
    tableeditwidget.cpp \
    tablewidget_updown.cpp \
    twtodowidget.cpp \
    yiyandialog.cpp


HEADERS += animationlabelup.h \
    anishow_label.h \
    clicklabel.h \
    getstartwidget.h \
    maintablewidget.h \
    mainwindow.h \
    qcustomtimer.h \
    rolling_label.h \
    tableeditwidget.h \
    tablewidget_updown.h \
    twtodowidget.h \
    yiyandialog.h

FORMS +=getstartwidget.ui \
    maintablewidget.ui \
    mainwindow.ui \
    tableeditwidget.ui \
    twtodowidget.ui \
    yiyandialog.ui
TRANSLATIONS += lang/lang_cn.ts \
                lang/lang_en.ts
RC_ICONS = icon.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
