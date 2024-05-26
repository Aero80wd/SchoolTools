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

#include <QCloseEvent>
#include "tableeditwidget.h"
#include "yiyandialog.h"
#include "animationlabelup.h"
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
    void pss(QString text);
    void pst(QString text);
    void tss(QString text);
    void tst(QString text);
};
class MainTableWidget : public QWidget
{
    Q_OBJECT

public:
    MainTableWidget(QWidget *parent = nullptr);
    ~MainTableWidget();
    void readTimeTable();
    void readConfig();
    void initTodayTable();
    void swithToYiYan();
    void refechYiYan();
    void configZuanyan();
    void refechZuanyan();
    void initSysTrayIcon();
    void createActions();
    void createMenu();
    void setStyleSheetFromFile(QWidget* widget,QString file);
    TableEditWidget EditWindow;
    QMenu *tray_menu;
    QAction *m_showedit;
    QAction *m_gongde;
    QAction *m_exitApp;
    QSystemTrayIcon *m_sysTrayIcon; //系统托盘
    bool ZuanYanisOpen = false;
    QSqlDatabase db;
    refechTableThread rtt;
    QString getToken();
    QPropertyAnimation *muyuding;
    QPropertyAnimation *hideani;
    QJsonObject Config;
    bool ishide = false;
    int flag = 0;
public slots:
    void setTable_SLOT(QString str);
    void refechTable_slot();
    void do_repaint();
    // void do_pss();
    // void do_pst();
    // void do_tss();
    // void do_tst();

private slots:
    void on_label_clicked();
    void on_showMainAction();
    void on_exitAppAction();
    void on_label_2_clicked();

    void on_muyu_clicked();

private:
    Ui::MainTableWidget *ui;
};


#endif // MAINTABLEWIDGET_H
