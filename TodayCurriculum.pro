QT       += core gui network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
VERSION = 2.0
QMAKE_TARGET_PRODUCT = 课程表
QMAKE_TARGET_COMPANY = Aero8m
QMAKE_TARGET_DESCRIPTION = 课程表
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animationlabelup.cpp \
    anishow_label.cpp \
    clicklabel.cpp \
    main.cpp \
    maintablewidget.cpp \
    qcustomtimer.cpp \
    rolling_label.cpp \
    tableeditwidget.cpp \
    tablewidget_updown.cpp \
    yiyandialog.cpp

HEADERS += \
    API.h \
    animationlabelup.h \
    anishow_label.h \
    clicklabel.h \
    maintablewidget.h \
    qcustomtimer.h \
    rolling_label.h \
    tableeditwidget.h \
    tablewidget_updown.h \
    yiyandialog.h

FORMS += \
    maintablewidget.ui \
    tableeditwidget.ui \
    yiyandialog.ui

TRANSLATIONS += \
    TodayCurriculum_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
RC_ICONS = icon.ico
