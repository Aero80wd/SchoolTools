#ifndef TABLEEDITWIDGET_H
#define TABLEEDITWIDGET_H
#include<QAbstractItemView>
#include <QWidget>
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QDir>
#include<QCloseEvent>
#include<QTableWidgetItem>
#include<QtGlobal>
#include<QMessageBox>
#include<QTranslator>
#include <qdesktopservices.h>
#include<QListWidgetItem>
//拖拽事件
#include <QDragEnterEvent>
//放下事件
#include <QDropEvent>
#include<QMimeData>
#include <private/qzipwriter_p.h>
#include <private/qzipreader_p.h>
#include<QFileIconProvider>
#include<QTimer>
#include"windows.h"
#include"AppLog.h"
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include<QInputDialog>
#include<QCryptographicHash>
#include "NetworkRequests.h"
#include "AppendixTableManager.h"

namespace Ui {
class TableEditWidget;
}

class TableEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableEditWidget(QWidget *parent = nullptr);
    void showEvent(QShowEvent *event) override;
    void readTableJson();
    void refechTableWidget(QJsonArray today_table);
    QJsonObject config;
    QString APP_VERSION = "5.4";
    void setConfig(QJsonObject obj);
    QJsonObject timeTable;
    void closeEvent(QCloseEvent *event) override;
    void addItem(QString key);
    void readPluginList();
    static bool timesort(QJsonObject &obj1,QJsonObject &obj2);
    QTime getTodayTime(QString str){
        QString timeString = str;
        QStringList timeList = timeString.split(":");
        int hour = timeList[0].toInt();
        int minute = timeList[1].toInt();
        return QTime(hour, minute);
    }
    ~TableEditWidget();
    bool eventFilter(QObject *watched,QEvent* e) override;
    bool isDeleteing = false;
    int clickcnt = 0;
public slots:
    void toggleded();
    void saveSyncSettings();
private slots:
    void on_pushButton_clicked();
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

    void on_chkHide_clicked(bool checked);

    void searchWeatherLocaltions();
    void saveWeatherLocaltions();

    void on_pluginList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pluginList_itemDoubleClicked(QListWidgetItem *item);

    void on_show_AppendixTableManager();
    void on_timerInfo_changed();
    void on_editAppendixTable(QString table_name);
signals:
    void refechTable_signal();
    void refechToolBar_signal();
private:
    bool isEditAppendixTable = false;
    QString currentEditAppendixTableName;
    Ui::TableEditWidget *ui;
    NetworkRequests weather_search_req;
};

#endif // TABLEEDITWIDGET_H
