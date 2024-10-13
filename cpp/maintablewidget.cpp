#include "../headers/maintablewidget.h"
#include "ui_maintablewidget.h"

#include "../headers/API.h"

MainTableWidget::MainTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainTableWidget)
{
    ui->setupUi(this);
    EditWindow = new TableEditWidget();
    readConfig();
    readTimeTable();

    EditWindow->setConfig(Config);

    initUi();
    rtt = new refechTableThread();

    initSignal();

    rtt->start();
    initSysTrayIcon();
    QTranslator translator;
    QLocale::Language lab = QLocale::system().language();
    if(QLocale::Chinese == lab)
    {
        translator.load(":/lang/lang_cn.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }else if(QLocale::English== lab){
        translator.load(":/language/lang_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }

}

MainTableWidget::~MainTableWidget()
{
    delete ui;
}
void MainTableWidget::showStatus(QString str)
{
    showLog("ShowStatused!",INFO);
    ui->label_3->setText(str);
    status_msg_animation->setDirection(QAbstractAnimation::Forward);
    status_msg_animation->start();
    QTimer::singleShot(5000,this,[&]()
    {
        status_msg_animation->setDirection(QAbstractAnimation::Backward);
        status_msg_animation->start();
    });
}
enum AccentStateForMainTableWidget {
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,
    ACCENT_INVALID_STATE = 5
};

struct AccentPolicyForMainTableWidget {
    AccentStateForMainTableWidget AccentState;
    int AccentFlags;
    int GradientColor;
    int AnimationId;
};
struct WindowCompositionAttributeDataForMainTableWidget {
    int Attribute;
    PVOID Data;
    ULONG DataSize;
};
typedef BOOL(WINAPI*pSetWindowCompositionAttributeForMainTableWidget)(HWND, WindowCompositionAttributeDataForMainTableWidget*);
pSetWindowCompositionAttributeForMainTableWidget SetWindowCompositionAttributeForMainTableWidget = nullptr;
void MainTableWidget::setWidgetBlur(QWidget* widget){
    if (!SetWindowCompositionAttributeForMainTableWidget) {
        HMODULE hModule = LoadLibrary(TEXT("user32.dll"));
        if (hModule) {
            SetWindowCompositionAttributeForMainTableWidget =
                (pSetWindowCompositionAttributeForMainTableWidget)GetProcAddress(hModule, "SetWindowCompositionAttribute");
        }
    }
    HWND hWnd = HWND(widget->winId());
    AccentPolicyForMainTableWidget policy = { ACCENT_ENABLE_ACRYLICBLURBEHIND, 0, int(0x66FFFFFF), 0 };
    WindowCompositionAttributeDataForMainTableWidget data = { 19, &policy, sizeof(AccentPolicyForMainTableWidget) };
    SetWindowCompositionAttributeForMainTableWidget(hWnd, &data);
}
void MainTableWidget::initUi(){
    setWindowFlags(Qt::WindowType::FramelessWindowHint | Qt::WindowType::Tool | Qt::WindowType::WindowStaysOnTopHint);
    setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground);
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(Qt::black);
    shadow->setBlurRadius(10);
    setWidgetBlur(this);
    status_msg_animation = new QPropertyAnimation(ui->status_show,"pos");
    status_msg_animation->setDuration(500);
    status_msg_animation->setEasingCurve(QEasingCurve::InOutSine);
    status_msg_animation->setStartValue(QPoint(0,-49));
    status_msg_animation->setEndValue(QPoint(0,0));
    class_show_widget_layout = new QHBoxLayout();
    class_show_widget_layout->setContentsMargins(0,0,0,0);
    class_show_widget_layout->setSpacing(0);
    ui->class_show_widget->setLayout(class_show_widget_layout);
//    setWidgetBlur(ui->table_show_2);
//    setWidgetBlur(ui->table_show_3);
//    setWidgetBlur(ui->pushButton_2);
//    setWidgetBlur(ui->pushButton_3);
//    setWidgetBlur(ui->pushButton_4);
//    setWidgetBlur(ui->pushButton_5);


}
void MainTableWidget::initSignal(){

    connect(EditWindow,SIGNAL(refechTable_signal()),this,SLOT(refechTable_slot()));
    connect(rtt,&refechTableThread::repaint,this,&MainTableWidget::do_repaint,Qt::QueuedConnection);
    connect(rtt,&refechTableThread::tst,ui->class_time,&QLabel::setText,Qt::QueuedConnection);
    connect(rtt,&refechTableThread::showStatusMessage,this,&MainTableWidget::showStatus,Qt::QueuedConnection);
    connect(rtt,&refechTableThread::changeStackedIndex,this,[=](int idx)
    {
        ui->stackedWidget->setCurrentIndex(idx);
    },Qt::QueuedConnection);
    connect(rtt,&refechTableThread::addClass,this,[=](QString text)
    {
        QLabel *class_label = new QLabel(ui->class_show_widget);
        class_show_widget_layout->addWidget(class_label);
        class_label->setText(text);
        class_label->setFixedSize(49,49);
        QFont font("Microsoft YaHei UI",16);
        class_label->setFont(font);
        class_label->setAlignment(Qt::AlignCenter);

    },Qt::QueuedConnection);
    connect(rtt,&refechTableThread::setClassStyleSheet,this,[=](int idx,QString styleSheet)
    {
        QList<QLabel*> class_list = ui->class_show_widget->findChildren<QLabel*>();
        class_list[idx]->setStyleSheet(styleSheet);
    },Qt::QueuedConnection);
    connect(rtt,&refechTableThread::toDone,this,[=]
    {
        resize(531,height());
        ui->stackedWidget->resize(531,height());
        ui->status_show->resize(531,height());
        QScreen *scr = qApp->primaryScreen();
        int scr_w = scr->size().width();
        int scr_h = scr->size().height();
        move((scr_w - width()) / 2, (scr_h - height()) / 9999999999999999999);

    },Qt::QueuedConnection);
}
void MainTableWidget::readTimeTable(){
    QFileInfo fi(TABLE_JSON);
    if (!fi.isFile()){
        QFile file(TABLE_JSON);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QJsonObject tempjson;
        QJsonArray nulljsonarray;
        tempjson.insert("Fri",nulljsonarray);
        tempjson.insert("Thu",nulljsonarray);
        tempjson.insert("Wed",nulljsonarray);
        tempjson.insert("Tue",nulljsonarray);
        tempjson.insert("Mon",nulljsonarray);
        QJsonDocument tempdoc;
        tempdoc.setObject(tempjson);
        file.close();
        QFile file_2(TABLE_JSON);
        file_2.open(QIODevice::ReadWrite | QIODevice::Text);
        file_2.write(tempdoc.toJson());
        file_2.close();
        QMessageBox::information(this,tr("提示"),tr("您未创建课程文件，系统已帮您创建，请手动编辑。"));
    }else{
        QFile file(TABLE_JSON);
        file.open(QIODevice::ReadWrite | QIODevice::Text);


        QTextStream stream(&file);
        QString file_str = stream.readAll();
        file.close();
        QJsonParseError jsonError;
        QJsonDocument jsondoc = QJsonDocument::fromJson(file_str.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError && !jsondoc.isNull()) {
            showLog("Config.json is Error!",LogStatus::ERR);
            return;
        }
        time_table = jsondoc.object();
        initTodayTable();

    }
}
void MainTableWidget::readConfig(){
    QFileInfo fi(CONFIG_JSON);
    if (!fi.isFile()){
        QFile file(CONFIG_JSON);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        QJsonObject config_json;
        config_json.insert("end_time","2000-01-01 00:00:00");
        config_json.insert("english","There are () $\nleft until install");
        config_json.insert("english_end","There is not a $\nleft until install");
        config_json.insert("english_tag","install");
        config_json.insert("label_tag","安装完成");
        QJsonDocument write_doc;
        write_doc.setObject(config_json);
        file.write(write_doc.toJson());
        file.close();
        startGetStart();
    }else{
        QFile file(CONFIG_JSON);
        file.open(QIODevice::ReadWrite | QIODevice::Text);

        QTextStream stream(&file);
        QString file_str = stream.readAll();
        file.close();
        QJsonParseError jsonError;
        QJsonDocument jsondoc = QJsonDocument::fromJson(file_str.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError && !jsondoc.isNull()) {
            showLog("Config.json is Error!",LogStatus::ERR);
            return;
        }
        Config = jsondoc.object();
    }
}
void MainTableWidget::initTodayTable(){
    QDateTime current_date_time = QDateTime::currentDateTime();
    today_table = time_table.value(current_date_time.toString("ddd")).toArray();
    resize(154+20+today_table.count()*49,height());
    ui->stackedWidget->resize(154+20+today_table.count()*49,height());
    ui->status_show->resize(154+20+today_table.count()*49,height());
}
void MainTableWidget::do_repaint(){
    return;
}
void refechTableThread::run(){
    QString display_string = "";
    QString showstr;
    QJsonObject temp;
    bool shangkelema = false;
    QDateTime current_date_time = QDateTime::currentDateTime();
    if (today_table.count() <= 0)
    {
        emit changeStackedIndex(0);
    }
    for (int i=0;i<today_table.count();i++)
    {
        emit addClass(QString(today_table[i].toObject()["name"].toString().at(0)));
    }
    emit changeStackedIndex(1);
    for(int x = 0;x < today_table.count();){
        QDateTime current_date_time = QDateTime::currentDateTime();
        QDateTime class_start_time = getTodayTime(today_table[x].toObject().value("start").toString());

        QDateTime class_end_time = getTodayTime(today_table[x].toObject().value("end").toString());


        // qDebug() << getTodayTime(today_table[x-1].toObject().value("end").toString()).secsTo(getTodayTime(today_table[x].toObject().value("start").toString()));

        if (current_date_time.secsTo(class_start_time) <= 0 and current_date_time.secsTo(class_end_time) <= 0){
            shangkelema = true;
            emit setClassStyleSheet(x,"");
            if (x+1 != today_table.count())
            {
                emit setClassStyleSheet(x+1,"border-width: 0px 0px 4px 0px; border-color:#1191d3; border-style: solid;");
            }

            emit showStatusMessage("下课时间到");
            x++;
            continue;
        }else if(current_date_time.secsTo(class_start_time) <= 0 and current_date_time.secsTo(class_start_time) <= 0){

            int diff_time = current_date_time.secsTo(class_end_time);
            if (!shangkelema)
            {
                if (x>0)
                {
                    emit setClassStyleSheet(x-1,"");
                }
                emit setClassStyleSheet(x,"border-width: 0px 0px 4px 0px; border-color:#1191d3; border-style: solid;");
                emit showStatusMessage("上课时间到");
                shangkelema = true;
            }
            int  hour = diff_time / 3600;
            diff_time = diff_time % 3600;
            int min = diff_time / 60;
            int sec = diff_time % 60;
            display_string = QString("%1:%2:%3").arg(hour, 2, 10, QLatin1Char('0')).arg(min, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'));
            emit tst(display_string);
            Sleep(1000);
        }else if(getTodayTime(today_table[x-1].toObject().value("end").toString()).secsTo(getTodayTime(today_table[x].toObject().value("start").toString())) <= today_table[x-1].toObject().value("split").toInt() * 60 and
                   x != 0){

            QDateTime current_date_time = QDateTime::currentDateTime();
            int diff_time = current_date_time.secsTo(getTodayTime(today_table[x].toObject().value("start").toString()));
            if (shangkelema)
            {
                if (x>0)
                {
                    emit setClassStyleSheet(x-1,"");
                }
                emit setClassStyleSheet(x,"border-width: 0px 0px 4px 0px; border-color:rgb(0,226,142); border-style: solid;");
                shangkelema = false;
            }
            int  hour = diff_time / 3600;
            diff_time = diff_time % 3600;
            int min = diff_time / 60;
            int sec = diff_time % 60;
            display_string = QString("%1:%2:%3").arg(hour, 2, 10, QLatin1Char('0')).arg(min, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'));
            emit tst(display_string);
            Sleep(1000);
        }else{

            x++;
            continue;
        }
    }
    emit changeStackedIndex(0);
    emit toDone();
}
QDateTime refechTableThread::getTodayTime(QString str){
    QString timeString = str;
    QStringList timeList = timeString.split(":");
    int hour = timeList[0].toInt();
    int minute = timeList[1].toInt();

    QDateTime dateTime;
    dateTime.setDate(QDate::currentDate());
    dateTime.setTime(QTime(hour, minute));
    return dateTime;
}

void MainTableWidget::swithToYiYan(){
    yiyanDialog *yiyan = new yiyanDialog(this);
    yiyan->setConfig(Config);
    yiyan->setZuanYanOpen(ZuanYanisOpen);
    QScreen *scr = qApp->primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    yiyan->move((scr_w - yiyan->width()) / 2, (scr_h - yiyan->height()) / 3);
    yiyan->setModal(false);
    yiyan->show();
}




QString MainTableWidget::getToken(){
    QNetworkAccessManager *smsManager = new QNetworkAccessManager(this);
    QString url = "https://v2.jinrishici.com/token";
    QNetworkRequest *Request = new QNetworkRequest(QUrl(url));
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(smsManager , SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply* initReply = smsManager ->get(*Request );
    eventLoop.exec();       //block until finish
    responseData = initReply->readAll();

    //解析json
    QString imageData;//接收到服务器的base64数据是string类型
    QString txt;
    QJsonParseError json_error;
    QJsonDocument doucment = QJsonDocument::fromJson(responseData, &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (doucment.isObject()) {
            const QJsonObject obj = doucment.object();
            return obj.value("data").toString();
        }
    }
}
void MainTableWidget::on_label_clicked()
{
    swithToYiYan();
}
void MainTableWidget::hk_slot(QString day){
    rtt->quit();
    today_table = time_table.value(day).toArray();
    QScreen *scr = qApp->primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    move((scr_w - width()) / 2, (scr_h - height()) / 9999999999999999999);
    for (QWidget*widget : ui->class_show_widget->findChildren<QWidget*>())
    {
        delete widget;
    }
    rtt->start();
}



void MainTableWidget::initSysTrayIcon()
{


    //新建QSystemTrayIcon对象
    m_sysTrayIcon = new QSystemTrayIcon(this);

    //设置托盘图标
    QIcon icon = QIcon(":/res/icon.png");    //资源文件添加的图标
    m_sysTrayIcon->setIcon(icon);

    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    m_sysTrayIcon->setToolTip(tr("校园悬浮窗"));

    // //给QSystemTrayIcon添加槽函数
    // connect(m_sysTrayIcon, &QSystemTrayIcon::activated,
    //         [=](QSystemTrayIcon::ActivationReason reason)
    //         {
    //             switch(reason)
    //             {
    //             case QSystemTrayIcon::Trigger:
    //                 //单击托盘图标
    //                 m_sysTrayIcon->showMessage(QObject::trUtf8("Message Title"),
    //                                            QObject::trUtf8("欢迎使用此程序"),
    //                                            QSystemTrayIcon::Information,
    //                                            1000);
    //                 break;
    //             case QSystemTrayIcon::DoubleClick:
    //                 //双击托盘图标
    //                 //双击后显示主程序窗口
    //                 this->show();
    //                 break;
    //             default:
    //                 break;
    //             }
    //         });

    //建立托盘操作的菜单
    createActions();
    createMenu();


    //在系统托盘显示此对象
    m_sysTrayIcon->show();
}
void MainTableWidget::createActions(){
    m_showedit = new QAction(tr("设置"),this);
    connect(m_showedit,SIGNAL(triggered()),this,SLOT(on_showMainAction()));
    m_showmain = new QAction(tr("打开主界面"),this);
    connect(m_showmain,&QAction::triggered,this,&MainTableWidget::startMainWindow);
    m_exitApp = new QAction(tr("退出"),this);
    connect(m_exitApp,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));
    if (Config["muyu_status"].toBool()){
        m_gongde = new QAction(tr("功德：") + QString::number(Config.value("gd").toInteger()),this);
    }/*else{
        m_gongde = new QAction("φ(*￣0￣)",this);
    }*/

}
void MainTableWidget::startMainWindow(){
    MainWindow *mainwin = new MainWindow(this);
    connect(mainwin,&MainWindow::hk,this,&MainTableWidget::hk_slot);
    QScreen *scr = qApp->primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    mainwin->move((scr_w - mainwin->width()) / 2, (scr_h - mainwin->height()) / 3);
    mainwin->setModal(false);
    mainwin->show();
}
void MainTableWidget::startGetStart(){
    GetStartWidget *getstart = new GetStartWidget(this);
    connect(getstart,&GetStartWidget::toSettings,this,&MainTableWidget::on_showConfig_modal);

    QScreen *scr = qApp->primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    getstart->move((scr_w - getstart->width()) / 2, (scr_h - getstart->height()) / 3);
    getstart->setModal(false);
    getstart->show();
    while (getstart->isVisible()){
        QCoreApplication::processEvents(QEventLoop::AllEvents,1145141919810);
    }
}
void MainTableWidget::createMenu(){

    tray_menu = new QMenu(this);
    setStyleSheetFromFile(tray_menu,":/res/menu.qss");
    tray_menu->addAction(m_showedit);
    tray_menu->addAction(m_showmain);
    if (Config["muyu_status"].toBool()){
        tray_menu->addAction(m_gongde);
    }
    tray_menu->addSeparator();
    tray_menu->addAction(m_exitApp);
    m_sysTrayIcon->setContextMenu(tray_menu);
}
void MainTableWidget::on_showMainAction(){

    EditWindow->show();
}
void MainTableWidget::on_showConfig_modal(){
    EditWindow->show();
    while (EditWindow->isVisible()){
        QCoreApplication::processEvents(QEventLoop::AllEvents,1145141919810);
    }
}
void MainTableWidget::on_exitAppAction(){
    qApp->exit();
}
void MainTableWidget::refechTable_slot(){
    rtt->quit();
    readTimeTable();

    QScreen *scr = qApp->primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    move((scr_w - width()) / 2, (scr_h - height()) / 9999999999999999999);
    for (QWidget*widget : ui->class_show_widget->findChildren<QWidget*>())
    {
        delete widget;
    }
    rtt->start();
    m_sysTrayIcon->showMessage(tr("提示"),tr("配置已成功应用！"),QSystemTrayIcon::MessageIcon::Information,500);

}


void MainTableWidget::setStyleSheetFromFile(QWidget* widget,QString file){
    QFile styleFile(file);
    if(styleFile.open(QIODevice::ReadOnly))
    {
        showLog("StyleSheet is Loaded",LogStatus::INFO);
        QString setStyleSheet(styleFile.readAll());
        widget->setStyleSheet(setStyleSheet);
        styleFile.close();
    }
    else
    {
        showLog("StyleSheet is Load failed",LogStatus::ERR);
    }
}