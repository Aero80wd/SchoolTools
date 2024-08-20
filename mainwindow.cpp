#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
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
    readTodos();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::getYunShi(){
    QByteArray responseData;
    responseData = initReply->readAll();
    //解析json
    QString imageData;//接收到服务器的base64数据是string类型
    QString txt;
    QJsonParseError json_error;
    QJsonDocument doucment = QJsonDocument::fromJson(responseData, &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (doucment.isObject()) {
            const QJsonObject obj = doucment.object();
            if (obj.contains("yilist")) {
                for (auto x : obj.value("yilist").toArray()){
                    yilist << x.toString();
                }
            }
            if (obj.contains("jilist")) {
                for (auto x : obj.value("jilist").toArray()){
                    jilist << x.toString();
                }
            }
            initReply->deleteLater();
        }
    }
    if (yilist.empty() or jilist.empty()){
        return;
    }
    QString s1 = "宜\n";
    s1 = s1+yilist[QDate::currentDate().day()%yilist.size()]+"\n";
    s1 = s1+yilist[QDate::currentDate().day()%yilist.size()+1];
    QString s2 = "忌\n";
    s2 = s2+jilist[QDate::currentDate().day()%jilist.size()]+"\n";
    s2 = s2+jilist[QDate::currentDate().day()%jilist.size()+1];
    ui->jilabel->setText(s2);
    ui->yilabel->setText(s1);
    ui->label_4->setText("中平");
}
void MainWindow::showEvent(QShowEvent* event){
    smsManager = new QNetworkAccessManager(this);
    smsManager->setProxy(QNetworkProxy::NoProxy);
    QString url = "http://aero80wd.github.io/apis/school/list.json";
    Request = new QNetworkRequest(QUrl(url));
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    connect(smsManager , &QNetworkAccessManager::finished, this,&MainWindow::getYunShi);
    initReply = smsManager ->get(*Request);
}

void MainWindow::on_butAdd_clicked()
{
    QInputDialog dialog{this, Qt::WindowCloseButtonHint};
    dialog.setWindowTitle(tr("新建待办"));
    dialog.setInputMode(QInputDialog::InputMode::TextInput);
    dialog.setTextEchoMode(QLineEdit::Normal);
    dialog.setLabelText(tr("请输入待办内容"));
    dialog.setOkButtonText(QObject::tr("确定"));
    dialog.setCancelButtonText(QObject::tr("取消"));
    dialog.setFixedSize(350,250);
    dialog.setTextValue("");
    // 设置了 QPushButtuon 的三态， QLineEdit 的样式， QLable 和 整体的背景色
    QString style = "QPushButton{background:#1191d3; color:rgb(255,255,255); border-radius:3px; min-height:30px; min-width:60px; font:13px \"Microsoft YaHei\";}"
                    "QPushButton:hover{background:#1191d0;}"
                    "QPushButton:pressed{background:rgb(32,75,148);}"
                    "QLineEdit{border:2px solid rgb(229,230,231);background:#ffffff;padding:4px;padding-left:10px;border-radius:3px;color:rgb(105,105,105);font:13px \"Microsoft YaHei\";}"
                    "QLineEdit:focus{border:2px solid #1191d3;}"
                    "QLineEdit:disabled{background-color:rgb(238,238,238);}"
                    "QLabel{color:rgb(85,85,85); background:#ffffff;font:12px \"Microsoft YaHei\"; font-weight:bold;}"
                    "QInputDialog{background-color:rgb(255,255,255); }";
    dialog.setStyleSheet(style);
    dialog.exec();
    if (!dialog.textValue().isEmpty()){
        newTodo(dialog.textValue(),true);
    }


}
void MainWindow::newTodo(QString name,bool n){
    QString todoText = name;
    QWidget* itemWidget = new QWidget;
    QHBoxLayout* hlayout = new QHBoxLayout;
    QCheckBox* okbox = new QCheckBox(itemWidget);
    todos.append(todoText);
    if (n){
        Config["todos"] = todos;
        QFile config_file(QDir::currentPath() + "/config.json");
        config_file.open(QFile::WriteOnly);
        QJsonDocument temp_doc;
        temp_doc.setObject(Config);
        config_file.write(temp_doc.toJson(QJsonDocument::Indented));
        config_file.close();
    }
    QLabel* textLabel = new QLabel(itemWidget);
    textLabel->setObjectName("textLabel");
    textLabel->setText(todoText);
    textLabel->setStyleSheet("color:#000000;");
    hlayout->addWidget(okbox);
    hlayout->addWidget(textLabel);
    hlayout->setStretch(0,1);
    hlayout->setStretch(1,100);
    itemWidget->setLayout(hlayout);
    connect(okbox,&QCheckBox::clicked,this,[=]{
        qDebug("Clicked");
        QListWidgetItem *item = ui->listWidget->currentItem();
        QWidget *widget = ui->listWidget->itemWidget(item);
        QLabel* curLabel = textLabel;
        QCheckBox* box = okbox;
        box->setDisabled(true);

        QJsonArray temparray;
        for (auto x:todos){

            if (x == textLabel->text()){
                qDebug("Continue");
                continue;
            }
            temparray.append(x);
        }
        curLabel->setText(QString("<s>%1</s>").arg(curLabel->text()));
        todos = temparray;

        Config["todos"] = temparray;
        QFile config_file(QDir::currentPath() + "/config.json");
        config_file.open(QFile::WriteOnly);
        QJsonDocument temp_doc;
        temp_doc.setObject(Config);
        config_file.write(temp_doc.toJson(QJsonDocument::Indented));
        config_file.close();

    });
    QListWidgetItem* item = new QListWidgetItem;

    ui->listWidget->addItem(item);

    ui->listWidget->setItemWidget(item,itemWidget);
    itemWidget->adjustSize();
    item->setSizeHint(itemWidget->size());
}
void MainWindow::readTodos(){
    QFileInfo fi(QDir::currentPath() + "/config.json");
    if (!fi.isFile()){
        QFile file(QDir::currentPath() + "/config.json");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.close();
    }else{
        QFile file(QDir::currentPath() + "/config.json");
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
        todos = jsondoc.object()["todos"].toArray();
        Config = jsondoc.object();
        ui->listWidget->clear();
        for (auto x : todos){
            newTodo(x.toString());
        }
    }
}

void MainWindow::on_btnhk_clicked()
{
    QStringList items;
    items << "星期一" << "星期二" << "星期三" << "星期四" << "星期五";
    QMap<QString,QString> en_cnday;
    en_cnday["星期一"] = "Mon";
    en_cnday["星期二"] = "Tue";
    en_cnday["星期三"] = "Wed";
    en_cnday["星期四"] = "Thu";
    en_cnday["星期五"] = "Fri";
    QString day = QInputDialog::getItem(this,"换课","选择使用的星期",items);
    emit hk(en_cnday[day]);
}

