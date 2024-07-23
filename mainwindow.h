#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QMouseEvent>
#include<QDialog>
#include<QGraphicsDropShadowEffect>
#include<QPropertyAnimation>
#include<QInputDialog>
#include<QList>
#include<QListWidgetItem>
#include<QCheckBox>
#include<QRandomGenerator>
#include<QTimer>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include<QFileInfo>
#include<QDir>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QNetworkAccessManager>
#include<QNetworkProxy>
#include<QTranslator>
namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showEvent(QShowEvent *event) override;
    void readTodos();
    QStringList yilist;
    QStringList jilist;
    QJsonArray todos;
    QJsonObject Config;
    QNetworkAccessManager *smsManager;
    QNetworkRequest *Request;
    void newTodo(QString name,bool n=false);
    QNetworkReply* initReply;
private slots:
    void on_butAdd_clicked();
    void getYunShi();
    void on_btnhk_clicked();

signals:
    void hk(QString day);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
