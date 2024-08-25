//
// Created by JH182 on 2024/8/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DayTimerWidget.h" resolved

#include "daytimerwidget.h"
#include "ui_DayTimerWidget.h"


DayTimerWidget::DayTimerWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::DayTimerWidget) {
    ui->setupUi(this);
    readTimeJson();
    setWindowFlags(Qt::WindowType::FramelessWindowHint | Qt::WindowType::Tool | Qt::WindowType::WindowStaysOnBottomHint);
    setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground);
    timer_timer = new QTimer();
    timer_timer->setInterval(1);
    connect(timer_timer,&QTimer::timeout,this,&DayTimerWidget::reload_timer);
    timer_timer->start();
    ui->label_2->setText("距离"+TimeJson["label_tag"].toString());

}

DayTimerWidget::~DayTimerWidget() {
    delete ui;
}

void DayTimerWidget::reload_timer() {
    TimeJson["english_end"] = TimeJson["english_end"].toString().toUpper();
    TimeJson["english"] = TimeJson["english"].toString().toUpper();
    QDateTime CurrentTime = QDateTime::currentDateTime();
    QDateTime EndTime = QDateTime::fromString(TimeJson["end_time"].toString(),"yyyy-MM-dd hh:mm:ss");
    qint64 msecs = CurrentTime.msecsTo(EndTime);
    // 计算天、小时、分钟、秒和毫秒
    int days = msecs / (24 * 60 * 60 * 1000);
    msecs %= (24 * 60 * 60 * 1000);
    int hours = msecs / (60 * 60 * 1000);
    msecs %= (60 * 60 * 1000);
    int minutes = msecs / (60 * 1000);
    msecs %= (60 * 1000);
    int seconds = msecs / 1000;
    int milliseconds = msecs % 1000;
    QString dw;
    QString dw_e;
    int retime;
    resize(114514,height());
    if (!days < 1){
        dw = "天";
        dw_e = "Days";
        ui->label_7->setText(QString(":%1:%2:%3.%4").arg(hours).arg(minutes).arg(seconds).arg(milliseconds));
        retime = days;
    }else if(!hours <= 0){
        dw = "时";
        dw_e = "Hours";
        ui->label_7->setText(QString(":%1:%2.%3").arg(minutes).arg(seconds).arg(milliseconds));
        retime = hours;
    }else if(!minutes <= 0){
        dw = "分";
        dw_e = "Minutes";
        ui->label_7->setText(QString(":%1.%2").arg(seconds).arg(milliseconds));
        retime = minutes;
    }else if(!seconds <= 0){
        dw = "秒";
        dw_e = "Seconds";
        ui->label_7->setText(QString(".%2").arg(milliseconds));
        retime = seconds;
    }else if(!milliseconds <= 0){
        dw = "毫秒";
        dw_e = "Milliseconds";
        ui->label_7->setText("");
        retime = milliseconds;
    }else{
        ui->label_3->setText("");
        ui->label_5->setText("");
        ui->label_4->setText("一天不剩");
        ui->label_7->setText("");
        ui->label_6->setText(TimeJson["english_end"].toString());
        ui->label_4->setGeometry(QRect(280, 70, 200 * 4, 111));
        QFont font = QFont();
        font.setFamily("字魂59号-创粗黑");
        font.setPointSize(47);
        ui->label_4->setFont(font);
        ui->label_5->setGeometry(QRect(270 + 50 * 0, 90, 211, 111));
        return;
    }
    if (retime != abs(retime)){
        ui->label_3->setText("");
        ui->label_5->setText("");
        ui->label_4->setText("一天不剩");
        ui->label_7->setText("");
        ui->label_6->setText(TimeJson["english_end"].toString().replace("$","DAY"));
        ui->label_4->setGeometry(QRect(170, 100, 200 * 4, 111));
        QFont font = QFont();
        font.setFamily("字魂59号-创粗黑");
        font.setPointSize(54);
        ui->label_4->setFont(font);
        ui->label_5->setGeometry(QRect(270 + 50 * 0, 90, 211, 111));
        return;
    }

    ui->label_7->setGeometry(QRect(380 + (50 * QString::number(retime).length()), 100, 411, 21));
    dw_e = dw_e.toUpper();
    ui->label_5->setText(dw);
    ui->label_4->setGeometry(QRect(290, 70, 100 * QString::number(retime).length(), 111));
    ui->label_5->setGeometry(QRect(300+80 * QString::number(retime).length(), 120, 211, 61));
    ui->label_4->setNum(retime);
    ui->label_6->setText(TimeJson["english"].toString().replace("()", QString::number(retime)).replace("$",dw_e));
}
void DayTimerWidget::readTimeJson() {
    QFile file(QDir::currentPath() + "/config.json");
    file.open(QIODevice::ReadWrite | QIODevice::Text);

    QTextStream stream(&file);
    QString file_str = stream.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument jsondoc = QJsonDocument::fromJson(file_str.toUtf8(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError && !jsondoc.isNull()) {
        showLog("Config.json is Error!",LogStatus::ERR);
    }
    TimeJson = jsondoc.object();

}