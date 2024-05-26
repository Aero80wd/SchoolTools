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
    void setConfig(QJsonObject obj);
    QJsonObject timeTable;
    void closeEvent(QCloseEvent *event) override;
    void addItem(QString key);
    static bool timesort(QJsonObject &obj1,QJsonObject &obj2);
    QTime getTodayTime(QString str){
        QString timeString = str;
        QStringList timeList = timeString.split(":");
        int hour = timeList[0].toInt();
        int minute = timeList[1].toInt();
        return QTime(hour, minute);
    }
    ~TableEditWidget();
public slots:
    void toggleded();

private slots:
    void on_pushButton_clicked();
    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

signals:
    void refechTable_signal();
private:
    Ui::TableEditWidget *ui;
};

#endif // TABLEEDITWIDGET_H
