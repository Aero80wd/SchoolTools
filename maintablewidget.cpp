#include "maintablewidget.h"
#include "ui_maintablewidget.h"

#include "API.h"

MainTableWidget::MainTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainTableWidget)
{
    ui->setupUi(this);
    qDebug() << TABLE_JSON;
    readConfig();
    readTimeTable();

    EditWindow.setConfig(Config);
    if (!Config.value("muyu_status").toBool()){
        ui->muyu->hide();
        ui->pushButton_3->hide();
    }
    qDebug() << time_table;

    initUi();

    rtt = new refechTableThread();
    connect(rtt,&refechTableThread::repaint,this,&MainTableWidget::do_repaint,Qt::QueuedConnection);
    connect(rtt,&refechTableThread::pss,ui->pushButton,&QLabel::setStyleSheet,Qt::QueuedConnection);
    connect(rtt,&refechTableThread::pst,ui->pushButton,&QLabel::setText,Qt::QueuedConnection);
    connect(rtt,&refechTableThread::tss,ui->table_show,&QLabel::setStyleSheet,Qt::QueuedConnection);
    connect(rtt,&refechTableThread::tst,ui->table_show,&QLabel::setText,Qt::QueuedConnection);
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
void MainTableWidget::setWidgetBlur(QWidget* widget){
    QGraphicsBlurEffect* blur = new QGraphicsBlurEffect(widget);
    blur->setBlurRadius(3);
    widget->setGraphicsEffect(blur);


}
void MainTableWidget::initUi(){
    setWindowFlags(Qt::WindowType::FramelessWindowHint | Qt::WindowType::Tool | Qt::WindowType::WindowStaysOnTopHint);
    setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground);
    muyuding = new QPropertyAnimation(ui->muyu, "geometry");
    muyuding->setStartValue(QRect(ui->muyu->pos().x(),ui->muyu->pos().y(),ui->muyu->width(),ui->muyu->height()));
    muyuding->setEndValue(QRect(770,18,21,21));
    muyuding->setDuration(100);
    muyuding->setEasingCurve(QEasingCurve::InOutQuad);
    hideani = new QPropertyAnimation(this, "pos");
    QScreen *scr = qApp->primaryScreen();
    int scr_w = scr->size().width();
    int scr_h = scr->size().height();
    QPoint globalpos = QPoint((scr_w - width()) / 2*1.1, (scr_h - height()) / 9999999999999999999);
    hideani->setStartValue(globalpos);
    hideani->setEndValue(QPoint(globalpos.x(),globalpos.y()-this->height()+(this->height()*0.9)));
    hideani->setDuration(500);
    hideani->setEasingCurve(QEasingCurve::InOutQuad);

    connect(muyuding,&QPropertyAnimation::finished,this,[=]{
        ui->muyu->setGeometry(QRect(770,18,19,19));
    });


    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(Qt::black);
    shadow->setBlurRadius(10);

    ui->down_button->setGraphicsEffect(shadow);
    ui->down_button->setParent(this);
    ui->down_button->hide();

    setWidgetBlur(ui->table_show_2);
    setWidgetBlur(ui->table_show_3);
    setWidgetBlur(ui->pushButton_2);
    setWidgetBlur(ui->pushButton_3);
    setWidgetBlur(ui->pushButton_4);

    todomovea = new QPropertyAnimation(ui->pushButton_5,"geometry");
    todomovea->setStartValue(QRect(ui->pushButton_5->pos().x(),ui->pushButton_5->pos().y(),ui->pushButton_5->width(),ui->pushButton_5->height()));
    todomovea->setEndValue(QRect(130,70,531,361));
    todomovea->setDuration(500);
    todomovea->setEasingCurve(QEasingCurve::InOutQuad);

    todomoveb = new QPropertyAnimation(ui->todo,"pos");
    todomoveb->setStartValue(ui->todo->pos());
    todomoveb->setEndValue(QPoint(140,80));
    todomoveb->setDuration(500);
    todomoveb->setEasingCurve(QEasingCurve::InOutQuad);

    muyumovea = new QPropertyAnimation(ui->pushButton_3,"pos");
    muyumovea->setStartValue(ui->pushButton_3->pos());
    muyumovea->setEndValue(QPoint(722,10));
    muyumovea->setDuration(300);
    muyumovea->setEasingCurve(QEasingCurve::InOutQuad);

    muyumoveb = new QPropertyAnimation(ui->muyu,"pos");
    muyumoveb->setStartValue(ui->muyu->pos());
    muyumoveb->setEndValue(QPoint(730,18));
    muyumoveb->setDuration(300);
    muyumoveb->setEasingCurve(QEasingCurve::InOutQuad);
}
void MainTableWidget::initSignal(){

    connect(&EditWindow,SIGNAL(refechTable_signal()),this,SLOT(refechTable_slot()));
    connect(ui->down_button,&ClickLabel::clicked,this,&MainTableWidget::on_label_2_clicked);
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
            qDebug() << "Json格式错误！" << jsonError.error;
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
            qDebug() << "Json格式错误！" << jsonError.error;
            return;
        }
        Config = jsondoc.object();
        if (Config.contains("zuan_status")){
            if (Config.value("zuan_status").toBool()){
                ZuanYanisOpen = true;
                configZuanyan();
            }
        }
    }
}
void MainTableWidget::initTodayTable(){
    QDateTime current_date_time = QDateTime::currentDateTime();
    today_table = time_table.value(current_date_time.toString("ddd")).toArray();

}
void MainTableWidget::do_repaint(){
    return;
}
void refechTableThread::run(){
    QString display_string = "";
    QString showstr;
    QJsonObject temp;
    QDateTime current_date_time = QDateTime::currentDateTime();
    for(int x = 0;x < today_table.count();){
        QDateTime current_date_time = QDateTime::currentDateTime();
        QDateTime class_start_time = getTodayTime(today_table[x].toObject().value("start").toString());

        QDateTime class_end_time = getTodayTime(today_table[x].toObject().value("end").toString());


        // qDebug() << getTodayTime(today_table[x-1].toObject().value("end").toString()).secsTo(getTodayTime(today_table[x].toObject().value("start").toString()));

        if (current_date_time.secsTo(class_start_time) <= 0 and current_date_time.secsTo(class_end_time) <= 0){
            x++;
            continue;
        }else if(current_date_time.secsTo(class_start_time) <= 0 and current_date_time.secsTo(class_start_time) <= 0){

            int diff_time = current_date_time.secsTo(class_end_time);
            int  hour = diff_time / 3600;
            diff_time = diff_time % 3600;
            int min = diff_time / 60;
            int sec = diff_time % 60;
            display_string = QString("%1:%2:%3").arg(hour, 2, 10, QLatin1Char('0')).arg(min, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'));
            emit pss("color:#caa257;");
            emit pst(display_string);
            showstr = tr("  当前课程：") + today_table[x].toObject().value("name").toString() + tr("  下节课程：") + today_table[x+1].toObject().value("name").toString();
            emit tst(showstr);
            Sleep(1000);
        }else if(getTodayTime(today_table[x-1].toObject().value("end").toString()).secsTo(getTodayTime(today_table[x].toObject().value("start").toString())) <= today_table[x-1].toObject().value("split").toInt() * 60 and
                   x != 0){
            QDateTime current_date_time = QDateTime::currentDateTime();
            int diff_time = current_date_time.secsTo(getTodayTime(today_table[x].toObject().value("start").toString()));
            int  hour = diff_time / 3600;
            diff_time = diff_time % 3600;
            int min = diff_time / 60;
            int sec = diff_time % 60;
            display_string = QString("%1:%2:%3").arg(hour, 2, 10, QLatin1Char('0')).arg(min, 2, 10, QLatin1Char('0')).arg(sec, 2, 10, QLatin1Char('0'));
            emit pss("color:rgb(0,240,0);");
            emit pst(display_string);
            showstr = tr("  上节课程：") + today_table[x-1].toObject().value("name").toString() + tr("  下节课程：") + today_table[x].toObject().value("name").toString();
            emit tst(showstr);
            Sleep(1000);
        }else{
            x++;
            continue;
        }
    }
    emit pss("color:#caa257;");
    emit pst("--:--:--");
    emit tst(tr("今日的课程已上完"));
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
void MainTableWidget::setTable_SLOT(QString str){
    ui->label->setText(str);
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



void MainTableWidget::refechYiYan(){
    if (ZuanYanisOpen){
        refechZuanyan();
    }
    else{
        QNetworkAccessManager *smsManager = new QNetworkAccessManager(this);
        QString url = "https://v2.jinrishici.com/sentence";
        QNetworkRequest *Request = new QNetworkRequest(QUrl(url));
        if (!Config.contains("yiyan_token")){
            Config.insert("yiyan_token",getToken());
            QFile config_file(CONFIG_JSON);
            config_file.open(QFile::WriteOnly);
            QJsonDocument temp_doc;
            temp_doc.setObject(Config);
            config_file.write(temp_doc.toJson(QJsonDocument::Indented));
            config_file.close();
        }
        Request->setRawHeader("X-User-Token",Config.value("yiyan_token").toString().toUtf8());
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
                qDebug() << obj;
                if (obj.contains("data")) {
                    QJsonObject object_data = obj.value("data").toObject();
                    ui->pushButton_2->setText(object_data.value("content").toString());
                }
            }
        }}
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
            qDebug() << obj;
            return obj.value("data").toString();
        }
    }
}
void MainTableWidget::on_label_clicked()
{
    swithToYiYan();
}
void MainTableWidget::hk_slot(QString day){
    qDebug() << "SLOT" << day << time_table.value(day).toArray() << time_table << TABLE_JSON;
    rtt->quit();
    today_table = time_table.value(day).toArray();
    rtt->start();
}

void MainTableWidget::on_label_2_clicked()
{
    if (!ishide){
        hideani->setDirection(QAbstractAnimation::Forward);
        ishide = true;
        ui->down_button->show();
    }else{
        hideani->setDirection(QAbstractAnimation::Backward);
        ishide=false;
        ui->down_button->hide();
        if (TodoisOpeninBack){
            qDebug("aaa");
            TWTodoWidget* todo = new TWTodoWidget();
            QHBoxLayout *layout = new QHBoxLayout();
            layout->addWidget(todo);
            todo->setParent(ui->pushButton_5);
            ui->pushButton_5->setLayout(layout);
            todomovea->setDirection(QAbstractAnimation::Forward);
            todomoveb->setDirection(QAbstractAnimation::Forward);
            muyumovea->setDirection(QAbstractAnimation::Forward);
            muyumoveb->setDirection(QAbstractAnimation::Forward);
            todomovea->start();
            todomoveb->start();
            muyumovea->start();
            muyumoveb->start();
            connect(muyumoveb,&QAbstractAnimation::finished,this,[=]{
                muyuding = new QPropertyAnimation(ui->muyu, "geometry");
                muyuding->setStartValue(QRect(ui->muyu->pos().x(),ui->muyu->pos().y(),ui->muyu->width(),ui->muyu->height()));
                muyuding->setEndValue(QRect(730,18,21,21));
                muyuding->setDuration(100);
                muyuding->setEasingCurve(QEasingCurve::InOutQuad);
                connect(muyuding,&QPropertyAnimation::finished,this,[=]{
                    ui->muyu->setGeometry(QRect(730,18,19,19));
                });
            });
            TodoisOpen = true;
            TodoisOpeninBack = false;
            hideani->start();
            return;
        }
    }
    if(TodoisOpen){
        on_todo_clicked();
        TodoisOpeninBack = true;
    }
    hideani->start();

}

void MainTableWidget::configZuanyan(){
    if (ZUAN_DB_QDOBJECT.exists()){
        QFile file(ZUAN_DB);
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug()<<"打开待下载文件失败！";
        }
        int timeout = 1000 * 60;

        QNetworkAccessManager networkManager;
        QNetworkRequest request;
        request.setUrl(QUrl("https://aero80wd.github.io/zuan.db"));
        QNetworkReply *reply = networkManager.get(request);

        QTimer timer;
        QEventLoop eventLoop;
        connect(reply, &QNetworkReply::downloadProgress, [=, &file, &timer](qint64 bytesReceived,qint64 bytesTotal){
            qDebug()<<"当前下载的文件大小："<<bytesReceived<<"   总文件大小："<<bytesTotal;
            if (timer.isActive())
                timer.start(timeout);
            file.write(reply->readAll());
        });
        connect(reply, &QNetworkReply::finished, &timer, &QTimer::stop);
        connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);

        connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
        timer.start(timeout);

        eventLoop.exec();//QEventLoop::ExcludeUserInputEvents


        if (reply->error() != QNetworkReply::NoError)
        {
            qDebug()<<"请求失败！失败原因："<<reply->error();
            file.close();
            delete reply;
        }
        if(timer.isActive())
        {
            qDebug()<<"请求超时！";
            timer.stop();
            file.close();
            delete reply;
        }
        qDebug()<<"下载3D文件成功！";
        file.close();
        delete reply;

    }

}
void MainTableWidget::refechZuanyan(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(ZUAN_DB);
    if (db.open())
    {
        qDebug() << "Database opened successfully！";
    }
    else
    {
        qDebug() << "无法打开数据库：" << db.lastError().text();
    }
    QString query_string = "SELECT * FROM `main` ORDER BY RANDOM() limit 1";
    QSqlQuery query;
    query.prepare(query_string);
    query.exec();
    QString zuan_text;
    while (query.next()){
        zuan_text = query.value("text").toString();
    }
    ui->pushButton_2->setText(zuan_text);
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
    m_showedit = new QAction(tr("编辑课程表"),this);
    connect(m_showedit,SIGNAL(triggered()),this,SLOT(on_showMainAction()));
    m_showmain = new QAction(tr("打开主界面"),this);
    connect(m_showmain,&QAction::triggered,this,&MainTableWidget::startMainWindow);
    m_exitApp = new QAction(tr("退出"),this);
    connect(m_exitApp,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));
    qDebug()<<Config;
    if (Config["muyu_status"].toBool()){
        m_gongde = new QAction(tr("功德：") + QString::number(Config.value("gd").toInteger()),this);
    }else{
        m_gongde = new QAction("φ(*￣0￣)",this);
    }

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
    ;;;;;;;;;;;;;;
    ;;;
    ;;;
    ;;;;;;;;;;;;;;
               ;;;
               ;;;
    ;;;;;;;;;;;;;;
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
    tray_menu->addAction(m_gongde);
    tray_menu->addSeparator();
    tray_menu->addAction(m_exitApp);
    m_sysTrayIcon->setContextMenu(tray_menu);
}
void MainTableWidget::on_showMainAction(){
    EditWindow.show();
}
void MainTableWidget::on_showConfig_modal(){
    EditWindow.show();
    while (EditWindow.isVisible()){
        QCoreApplication::processEvents(QEventLoop::AllEvents,1145141919810);
    }
}
void MainTableWidget::on_exitAppAction(){
    qApp->exit();
}
void MainTableWidget::refechTable_slot(){
    rtt->quit();
    readTimeTable();
    rtt->start();
    m_sysTrayIcon->showMessage(tr("提示"),tr("配置已成功应用！"),QSystemTrayIcon::MessageIcon::Information,500);

}

void MainTableWidget::on_muyu_clicked()
{
    muyuding->start();
    AnimationLabelUp* gpp = new AnimationLabelUp(this);
    gpp->setText("功德+1");
    gpp->setStyleSheet("color:#ffffff");
    gpp->move(ui->muyu->pos().x()+10,ui->muyu->pos().y()-30);
    gpp->AniHide();
    if (!Config.contains("gd")){
        Config["gd"] = 0;
    }else{
        Config["gd"] = Config.value("gd").toInteger() + 1;
    }
    QFile config_file(CONFIG_JSON);
    config_file.open(QFile::WriteOnly);
    QJsonDocument temp_doc;
    temp_doc.setObject(Config);
    config_file.write(temp_doc.toJson(QJsonDocument::Indented));
    config_file.close();
    qDebug() << Config;
    if (Config["muyu_status"].toBool()){
        m_gongde = new QAction(tr("功德：") + QString::number(Config.value("gd").toInteger()),this);
        tray_menu->deleteLater();
        createMenu();
    }
}
void MainTableWidget::setStyleSheetFromFile(QWidget* widget,QString file){
    QFile styleFile(file);
    if(styleFile.open(QIODevice::ReadOnly))
    {
        qDebug("open success");
        QString setStyleSheet(styleFile.readAll());
        widget->setStyleSheet(setStyleSheet);
        styleFile.close();
    }
    else
    {
        qDebug("Open failed");
    }
}

void MainTableWidget::on_todo_clicked()
{
    if (!TodoisOpen){
        TWTodoWidget* todo = new TWTodoWidget();
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(todo);
        todo->setParent(ui->pushButton_5);
        ui->pushButton_5->setLayout(layout);
        todomovea->setDirection(QAbstractAnimation::Forward);
        todomoveb->setDirection(QAbstractAnimation::Forward);
        muyumovea->setDirection(QAbstractAnimation::Forward);
        muyumoveb->setDirection(QAbstractAnimation::Forward);
        todomovea->start();
        todomoveb->start();
        muyumovea->start();
        muyumoveb->start();
        connect(muyumoveb,&QAbstractAnimation::finished,this,[=]{
            muyuding = new QPropertyAnimation(ui->muyu, "geometry");
            muyuding->setStartValue(QRect(ui->muyu->pos().x(),ui->muyu->pos().y(),ui->muyu->width(),ui->muyu->height()));
            muyuding->setEndValue(QRect(730,18,21,21));
            muyuding->setDuration(100);
            muyuding->setEasingCurve(QEasingCurve::InOutQuad);
            connect(muyuding,&QPropertyAnimation::finished,this,[=]{
                ui->muyu->setGeometry(QRect(730,18,19,19));
            });
        });

        TodoisOpen=true;
    }else{
        todomovea->setDirection(QAbstractAnimation::Backward);
        todomoveb->setDirection(QAbstractAnimation::Backward);
        muyumovea->setDirection(QAbstractAnimation::Backward);
        muyumoveb->setDirection(QAbstractAnimation::Backward);
        todomovea->start();
        todomoveb->start();
        muyumovea->start();
        muyumoveb->start();
        connect(muyumoveb,&QAbstractAnimation::finished,this,[=]{
            muyuding = new QPropertyAnimation(ui->muyu, "geometry");
            muyuding->setStartValue(QRect(ui->muyu->pos().x(),ui->muyu->pos().y(),ui->muyu->width(),ui->muyu->height()));
            muyuding->setEndValue(QRect(770,18,21,21));
            muyuding->setDuration(100);
            muyuding->setEasingCurve(QEasingCurve::InOutQuad);
            connect(muyuding,&QPropertyAnimation::finished,this,[=]{
                ui->muyu->setGeometry(QRect(770,18,19,19));
            });
        });
        TodoisOpen=false;
    }
}

