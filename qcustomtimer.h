#ifndef QCUSTOMTIMER_H
#define QCUSTOMTIMER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include<QNetworkAccessManager>
#include<QNetworkReply>

class QCustomTimer : public QObject
{
    Q_OBJECT
public:
    explicit QCustomTimer(QObject *parent = 0);
    ~QCustomTimer();

private:
    static QThread     *m_pTimerThread; //定时器依赖线程
    QTimer             *m_pTimer;       //定时器对象

signals:
    void startSignal( int nMsc );//开启定时器信号
    void stopSignal();           //停止定时器信号
    void TimeOut();              //定时器触发，外部需连接此信号
    void deletelater();          //延时删除定时器信号
public slots:
    void onTimer();              //对象内部定时触发槽函数，向外部发射定时器触发信号
public:
    void StartTimer( int nMsc ); //开启定时器
    void StopTimer();            //关闭定时器
    void DeleteLater();          //延时删除定时器对象

};

#endif // QCUSTOMTIMER_H
