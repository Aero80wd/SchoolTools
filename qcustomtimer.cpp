#include "qcustomtimer.h"

//静态线程成员指针初始化
QThread* QCustomTimer::m_pTimerThread = NULL;

QCustomTimer::QCustomTimer(QObject *parent) :
    QObject(parent)
{
    if ( m_pTimerThread == NULL )
    {
        //此判断分支依赖于Qt将静态成员指针变量初始化为NULL，不是好的做法
        //但如果工程中存在其他全局变量并且有了依赖关系，那么应该也就只能这样了
        //保证QCustomTimer类不要跟其他全局变量产生依赖关系，可以在类外初始化，这样更好
        m_pTimerThread = new QThread;
    }

    m_pTimer = new QTimer(0);
    m_pTimer->setSingleShot( true );//单次触发

    m_pTimerThread->start();

    m_pTimer->moveToThread( m_pTimerThread );//更改定时器运行的线程

    connect( m_pTimer, SIGNAL(timeout()), this, SLOT(onTimer()) , Qt::DirectConnection );//定时器事件触发槽

    connect( this, SIGNAL(startSignal(int)), m_pTimer, SLOT(start( int ) ), Qt::BlockingQueuedConnection );//连接定时器启动槽函数，不可用“直连”

    connect( this, SIGNAL(stopSignal()), m_pTimer, SLOT(stop()), Qt::BlockingQueuedConnection );//连接定时器关闭槽函数，不可用“直连”

    connect( this, SIGNAL( deletelater() ), m_pTimer, SLOT(deleteLater()) );//删除位于线程中的定时器对象，插入一个延时删除的事件
}

QCustomTimer::~QCustomTimer()
{
    StopTimer();
    DeleteLater();
}

void QCustomTimer::onTimer()
{
    emit TimeOut();//发射定时器触发信号
}

void QCustomTimer::StartTimer(int nMsc)
{
    emit startSignal(nMsc) ;//向子线程内的定时器发送开启定时器信号
}

void QCustomTimer::StopTimer()
{
    emit stopSignal();//向子线程内的定时器发送停止定时器信号
}

void QCustomTimer::DeleteLater()
{
    emit deletelater();//向子线程的事件循环插入一个延期删除事件
}
