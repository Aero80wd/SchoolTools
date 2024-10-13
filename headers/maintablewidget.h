#ifndef MAINTABLEWIDGET_H
#define MAINTABLEWIDGET_H
#include <QScreen>
#include <QWidget>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonValue>
#include<QJsonParseError>
#include<QMessageBox>
#include <QTimer>
#include<QThread>
#include<QPropertyAnimation>
#include<QEasingCurve>
#include<QAbstractAnimation>
#include<QRect>
#include<QAbstractAnimation>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include<QHBoxLayout>
#include <QCloseEvent>
#include "tableeditwidget.h"
#include "yiyandialog.h"
#include "animationlabelup.h"
#include "getstartwidget.h"
#include "mainwindow.h"
#include "twtodowidget.h"
#include"NetworkRequests.h"
#include <windows.h>
#include<QTranslator>
#include"AppLog.h"
#include<dwmapi.h>
QT_BEGIN_NAMESPACE

namespace Ui {
class MainTableWidget;

}
QT_END_NAMESPACE
class refechTableThread:public QThread{
    Q_OBJECT
public:
    QDateTime getTodayTime(QString str);

    void run();
signals:
    void setTable(QString str);
    void repaint();
    void tst(QString text);
    void showStatusMessage(QString str);
    void changeStackedIndex(int idx);
    void addClass(QString text);
    void setClassStyleSheet(int idx,QString styleSheet);
    void toDone();
};
class MainTableWidget : public QWidget
{
    Q_OBJECT

public:
    bool TodoisOpen=false;
    MainTableWidget(QWidget *parent = nullptr);
    ~MainTableWidget();
    void readTimeTable();
    void readConfig();
    void initTodayTable();
    void swithToYiYan();
    void setWidgetBlur(QWidget* widget);
    void createActions();
    void createMenu();
    void setStyleSheetFromFile(QWidget* widget,QString file);
    TableEditWidget *EditWindow;
    QMenu *tray_menu;
    QAction *m_showedit;
    QAction *m_gongde;
    QAction *m_exitApp;
    QAction *m_hidewindow;
    QSystemTrayIcon *m_sysTrayIcon; //系统托盘
    bool ZuanYanisOpen = false;
    bool TodoisOpeninBack = false;
    QSqlDatabase db;
    refechTableThread* rtt;
    QString getToken();
    QPropertyAnimation* status_msg_animation;
    QAction* m_showmain;
    QJsonObject Config;
    bool ishide = false;
    int flag = 0;
    NetworkRequests req;

public slots:
    void refechTable_slot();
    void do_repaint();
    void startMainWindow();
    void startGetStart();
    void on_showConfig_modal();
    void hk_slot(QString day);
    void showStatus(QString str);
    // void do_pss();
    // void do_pst();
    // void do_tss();
    // void do_tst();

private slots:
    void on_label_clicked();
    void on_showMainAction();
    void on_exitAppAction();
private:
    Ui::MainTableWidget *ui;
    void initSysTrayIcon();
    void initSignal();
    void initUi();
    QHBoxLayout* class_show_widget_layout;
};


#endif // MAINTABLEWIDGET_H
