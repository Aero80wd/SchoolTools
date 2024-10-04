#include "../headers/tableeditwidget.h"
#include "ui_tableeditwidget.h"

TableEditWidget::TableEditWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TableEditWidget)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(5);
    connect(ui->radioButton,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->radioButton_2,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->radioButton_3,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->radioButton_4,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->radioButton_5,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->save_syncset,&QPushButton::clicked,this,&TableEditWidget::saveSyncSettings);
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{
        ui->tabWidget->removeTab(5);
    });
    connect(ui->label,&ClickLabel::clicked,this,[=]{
        if (clickcnt >=10){
            clickcnt=0;
            ui->tabWidget->insertTab(5,ui->tab_3,QString(tr("彩蛋设置")));
        }else{
            clickcnt++;
        }

    });
    readTableJson();
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=]{
        QDesktopServices::openUrl(QUrl("https://github.com/Aero80wd/SchoolTools"));
    });
    connect(ui->save_text_config,&QPushButton::clicked,this,&TableEditWidget::on_timerInfo_changed);
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
    readPluginList();
    ui->pluginInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->pluginList->installEventFilter(this);
    ui->pluginList->setAcceptDrops(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->installEventFilter(this);
    ui->label_4->setText("Version " + APP_VERSION);

}

TableEditWidget::~TableEditWidget()
{

    delete ui;
}
bool TableEditWidget::timesort(QJsonObject &obj1, QJsonObject &obj2){
    QTime time1 = QTime::fromString(obj1.value("start").toString());
    QTime time2 = QTime::fromString(obj2.value("start").toString());
    return time1 < time2;
}
void TableEditWidget::showEvent(QShowEvent* event){

    toggleded();
}
void TableEditWidget::closeEvent(QCloseEvent *event){
    QApplication::setQuitOnLastWindowClosed( true );
    emit refechTable_signal();
    this->hide();
    event->ignore();
}
void TableEditWidget::saveSyncSettings() {
    ui->sync_log->clear();
    ui->sync_log->setReadOnly(true);
    QNetworkAccessManager *netManager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://%1:%2/create_class?class_name=%3").arg(ui->sync_server->text()).arg(ui->sync_port->value()).arg(ui->sync_class->text())));
    QNetworkReply *reply;
    reply = netManager->get(request);
    ui->sync_log->insertPlainText("请求服务器中，目标" + QString("http://%1:%2/create_class?class_name=%3").arg(ui->sync_server->text()).arg(ui->sync_port->value()).arg(ui->sync_class->text()) + "\n");
    connect(reply,&QNetworkReply::finished,this,[=]{
        if (reply->error()){
            showLog("请求发生错误！请求终止！",LogStatus::ERR);
            ui->sync_log->insertPlainText("请求失败！状态码："+QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()) + "\n");
            ui->sync_log->insertPlainText("错误信息：" + reply->errorString() + "\n");
            ui->sync_log->insertPlainText(QString("服务器不可用！请重新配置！") + "\n");
        }else{
            showLog(("请求完成！状态码："+QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt())).toStdString().c_str(),LogStatus::INFO);
            ui->sync_log->insertPlainText("请求完成！状态码："+QString::number(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()) + "\n");
            QJsonObject obj = QJsonDocument::fromJson(reply->readAll()).object();
            if (obj["code"].toInt() == 0)
            {
                ui->sync_log->insertPlainText("班级状态：创建成功！\n");
            }else
            {
                ui->sync_log->insertPlainText("班级状态：已创建！\n");
            }

            ui->sync_log->insertPlainText(QString("服务器可用！已保存配置！重启生效！") + "\n");
            config["sync_open"] = ui->syncopen->isChecked();
            config["sync_server"] = ui->sync_server->text();
            config["sync_server_port"] = ui->sync_port->value();
            config["class_name"] = ui->sync_class->text();
            QMessageBox::information(this,tr("提示"),tr("重启生效"));
        }

    });
    QFile config_file(QDir::currentPath() + "/config.json");
    config_file.open(QFile::WriteOnly);
    QJsonDocument temp_doc;
    temp_doc.setObject(config);
    config_file.write(temp_doc.toJson(QJsonDocument::Indented));
    config_file.close();

}
void TableEditWidget::setConfig(QJsonObject obj){
    config=obj;
    ui->checkBox_2->setChecked(config.value("zuan_status").toBool());
    ui->checkBox->setChecked(config.value("muyu_status").toBool());
    ui->chkHide->setChecked(config.value("toolbox_status").toBool());
    ui->timer_hide->setChecked(config.value("disable_timer").toBool());
    ui->timer_time->setDateTime(QDateTime::fromString(config["end_time"].toString(),"yyyy-MM-dd hh:mm:ss"));
    ui->edit_name->setText(config["label_tag"].toString());
    ui->edit_name_eng->setText(config["english_tag"].toString());
    ui->syncopen->setChecked(config.value("sync_open").toBool());
    ui->sync_server->setText(config["sync_server"].toString());
    ui->sync_port->setValue(config["sync_server_port"].toInt());
    ui->sync_class->setText(config["class_name"].toString());
}
void TableEditWidget::on_timerInfo_changed(){
    config["end_time"] = ui->timer_time->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    config["label_tag"] = ui->edit_name->text();
    config["english"] = QString("There are () $\nleft until %1").arg(ui->edit_name_eng->text());
    config["english_end"] = QString("There is not a $\nleft until %1").arg(ui->edit_name_eng->text());
    config["english_tag"] = ui->edit_name_eng->text();
    config["disable_timer"] = ui->timer_hide->isChecked();
    QFile config_file(QDir::currentPath() + "/config.json");
    config_file.open(QFile::WriteOnly);
    QJsonDocument temp_doc;
    temp_doc.setObject(config);
    config_file.write(temp_doc.toJson(QJsonDocument::Indented));
    config_file.close();
    QMessageBox::information(this,tr("提示"),tr("重启生效"));
}

void TableEditWidget::readTableJson(){
    QFile file(QDir::currentPath() + "/tables.json");
    file.open(QIODevice::ReadWrite | QIODevice::Text);


    QTextStream stream(&file);
    QString file_str = stream.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument jsondoc = QJsonDocument::fromJson(file_str.toUtf8(),&jsonError);
    if (jsonError.error != QJsonParseError::NoError && !jsondoc.isNull()) {
        showLog("table.json is Error!",LogStatus::ERR);
        return;
    }
    timeTable = jsondoc.object();


}
void TableEditWidget::readPluginList(){
    QDir plugin_dir(QDir::currentPath() + "/plugins");
    if (!plugin_dir.exists()){
        plugin_dir.mkdir(QDir::currentPath() + "/plugins");
        return;
    }
    QFileInfoList fileList = plugin_dir.entryInfoList();
    ui->pluginList->clear();
    for (auto x : fileList){
        QString JsonPath = x.filePath() + "/pluginConfig.json";
        if (x.filePath()[x.filePath().size() -1] == '.'){
            continue;
        }
        QFile file(x.filePath() + "/pluginConfig.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString value = file.readAll();
        file.close();
        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
        QJsonObject PluginObject = document.object();
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(PluginObject["name"].toString());
        item->setData(Qt::UserRole,x.filePath() + "/pluginConfig.json");
        item->setData(Qt::UserRole+1,x.filePath());
        ui->pluginList->addItem(item);


    }
}
void TableEditWidget::refechTableWidget(QJsonArray today_table){

    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "课程" << "上课时间" << "下课时间" << "课间时间");
    ui->tableWidget->setRowCount(today_table.count());
    for (int x = 0; x<today_table.count();x++){
        QJsonObject value_object = today_table.at(x).toObject();
        QString name = value_object.value("name").toString();
        QString start_time = value_object.value("start").toString();
        QString end_time = value_object.value("end").toString();
        int split_time = value_object.value("split").toInt();
        ui->tableWidget->setItem(x,0,new QTableWidgetItem(name));
        ui->tableWidget->setItem(x,1,new QTableWidgetItem(start_time));
        ui->tableWidget->setItem(x,2,new QTableWidgetItem(end_time));
        ui->tableWidget->setItem(x,3,new QTableWidgetItem(QString::number(split_time)));
    }
}
void TableEditWidget::toggleded(){
    if (ui->radioButton->isChecked()){
        refechTableWidget(timeTable.value("Mon").toArray());
    }else
    if (ui->radioButton_2->isChecked()){
        refechTableWidget(timeTable.value("Tue").toArray());
    }else
    if (ui->radioButton_3->isChecked()){
        refechTableWidget(timeTable.value("Wed").toArray());
    }else
    if (ui->radioButton_4->isChecked()){
        refechTableWidget(timeTable.value("Thu").toArray());
    }else
    if (ui->radioButton_5->isChecked()){
        refechTableWidget(timeTable.value("Fri").toArray());
    }
}
void TableEditWidget::addItem(QString key){
    QJsonObject insert_json;
    insert_json.insert("name",ui->lineEdit->text());
    insert_json.insert("start",ui->timeEdit->text());
    insert_json.insert("end",ui->timeEdit_2->text());
    insert_json.insert("split",ui->spinBox->value());
    QJsonArray editarray = timeTable[key].toArray();
    editarray.append(insert_json);
    // for (int x = 0;x<editarray.count()-1;x++){
    //     for (int y = x+1;y<editarray.count();y++){
    //         if (QTime::fromString(editarray[y].toObject().value("start").toString()) < QTime::fromString(editarray[x].toObject().value("start").toString())){
    //             min_index = y;
    //         }
    //     }
    //     QJsonObject max_Object = editarray[x].toObject();
    //     editarray[x] = editarray[min_index];
    //     editarray[min_index] = max_Object;
    // }

    for (int i = 0; i < editarray.count() - 1; i++) {	// 操作i至len-1个数据（剩下最后一个不需要操作）
        int index = i;	// 赋初值给索引
        for (int j = i + 1; j < editarray.count(); j++) {	// 比较剩余未排序的数据
            if (getTodayTime(editarray[j].toObject().value("start").toString()) < getTodayTime(editarray[index].toObject().value("start").toString())) {	// 当剩余的数据有比索引对应的数小时，更新索引
                index = j;
            }
        }
        // 当索引不等于初值时
        if (index != i) {
            // 交换数据
            QJsonObject temp = editarray[index].toObject();
            editarray[index] = editarray[i];
            editarray[i] = temp;
        }
    }
    timeTable[key] = editarray;
    QFile config_file(QDir::currentPath() + "/tables.json");
    config_file.open(QFile::WriteOnly);
    QJsonDocument temp_doc;
    temp_doc.setObject(timeTable);
    config_file.write(temp_doc.toJson(QJsonDocument::Indented));
    config_file.close();
    toggleded();

}



bool TableEditWidget::eventFilter(QObject *watched,QEvent*event)
{
    if (event->type() == QEvent::Resize)
    {
        ui->tabWidget->setStyleSheet(QString("QTabBar::tab{background:#ffffff;width:%1;border-radius:3px;border:1px solid #1191d3;padding:5px;}QTabBar::tab:hover{background:rgb(217, 217, 217);}QTabBar::tab:selected{color:#ffffff;background:#1191d3;}QTabWidget::tab-bar{alignment:center;}").arg(ui->tabWidget->width()/5*0.9)); //1
        QCoreApplication::processEvents(QEventLoop::AllEvents,1145141919810);
        return true;
    }
    if (event->type() == QEvent::Drop){
        showLog("PluginFile is Drop",LogStatus::INFO);
        ui->status_bar->setText("");
        QDropEvent *drop_event = (QDropEvent*) event;
        const QMimeData *mimeData = drop_event->mimeData();

        if(!mimeData->hasUrls())
        {
            return true;
        }

        QList<QUrl> urlList = mimeData->urls();
        for (int x = 0;x<urlList.length();x++){
            QString fileName = urlList.at(x).toLocalFile();
            if(fileName.isEmpty())
            {
                return true;
            }

            if (fileName.split(".").last() == "zip"){
                QZipReader reader(fileName);
                reader.extractAll(QDir::currentPath() + "/plugins");
                QFile file(QDir::currentPath() + "/plugins");
                file.open(QIODevice::WriteOnly);
                file.write(reader.fileData(QDir::currentPath() + "/plugins/" + QTime::currentTime().toString()));
                file.close();
                reader.close();
                readPluginList();
                QMessageBox::information(this,tr("提示"),tr("插件安装完成！"));
                emit refechToolBar_signal();
            }else if (fileName.split(".").last() == "lnk"){
                QFileInfo info(fileName);
                if (info.exists() && info.isSymLink()){
                    QJsonObject pluginObj;
                    pluginObj["name"] = info.baseName();
                    pluginObj["type"] = "link";
                    pluginObj["linkPath"] = fileName;
                    pluginObj["pluginVersion"] = "0.0";
                    pluginObj["pluginAuthor"] = "";
                    pluginObj["pluginIntroduce"] = info.baseName();
                    pluginObj["icon"] = "icon.png";
                    QDir pluginDir(QDir::currentPath() + "/plugins/" + info.baseName());
                    pluginDir.mkdir(QDir::currentPath() + "/plugins/" + info.baseName());
                    QFile file(QDir::currentPath() + "/plugins/" + info.baseName() + "/pluginConfig.json");
                    file.open(QIODevice::ReadWrite);
                    QJsonDocument pluginDoc;
                    pluginDoc.setObject(pluginObj);
                    file.write(pluginDoc.toJson());
                    file.close();
                    QFileInfo fileinfo(info.symLinkTarget());
                    QFileIconProvider fileicon;
                    QIcon icon=fileicon.icon(fileinfo);
                    QPixmap pixmap = icon.pixmap(256,256);
                    pixmap.save(QDir::currentPath() + "/plugins/" + info.baseName() + "/icon.png");
                    readPluginList();
                    emit refechToolBar_signal();

                }
            }else{
                QMessageBox::critical(this,tr("错误"),tr("此文件不是插件或快捷方式！"));
                return true;
            }
        }
        QMessageBox::information(this,tr("提示"),tr("图标添加完成！"));
        return true;

    }
    if (event->type() == QEvent::DragEnter) {
        QDragEnterEvent *drag_event = (QDragEnterEvent *) event;
        if (drag_event->mimeData()->hasUrls()) {
            QList<QUrl> urlList = drag_event->mimeData()->urls();
            bool isPlugin = false;
            for (int x = 0; x < urlList.length(); x++) {
                QString fileName = urlList.at(x).toLocalFile();
                if (fileName.split(".").last() == "zip" or fileName.split(".").last() == "lnk") {
                    isPlugin = true;
                } else {
                    isPlugin = false;
                    break;
                }

            }
            if (isPlugin) {
                ui->status_bar->setText("拖放以添加至工具栏");
                drag_event->acceptProposedAction();
            } else {
                ui->status_bar->setText("此文件不是插件或快捷方式！");
                drag_event->ignore();
            }
            return true;
        }
    }
    return QWidget::eventFilter(watched,event);
}
void TableEditWidget::on_pushButton_clicked()
{
    if (ui->radioButton->isChecked()){
        addItem("Mon");
    }else
    if (ui->radioButton_2->isChecked()){
        addItem("Tue");
    }else
    if (ui->radioButton_3->isChecked()){
        addItem("Wed");
    }else
    if (ui->radioButton_4->isChecked()){
        addItem("Thu");
    }else
    if (ui->radioButton_5->isChecked()){
        addItem("Fri");
    }
}


void TableEditWidget::on_tableWidget_itemChanged(QTableWidgetItem *item)
{

}



void TableEditWidget::on_checkBox_2_clicked(bool checked)
{
    config["zuan_status"] = checked;
    QFile config_file(QDir::currentPath() + "/config.json");
    config_file.open(QFile::WriteOnly);
    QJsonDocument temp_doc;
    temp_doc.setObject(config);
    config_file.write(temp_doc.toJson(QJsonDocument::Indented));
    config_file.close();
    QMessageBox::information(this,tr("提示"),tr("重启生效"));

}


void TableEditWidget::on_checkBox_clicked(bool checked)
{
    config["muyu_status"] = checked;
    QFile config_file(QDir::currentPath() + "/config.json");
    config_file.open(QFile::WriteOnly);
    QJsonDocument temp_doc;
    temp_doc.setObject(config);
    config_file.write(temp_doc.toJson(QJsonDocument::Indented));
    config_file.close();
    QMessageBox::information(this,tr("提示"),tr("重启生效"));
}


void TableEditWidget::on_chkHide_clicked(bool checked)
{
    config["toolbox_status"] = checked;
    QFile config_file(QDir::currentPath() + "/config.json");
    config_file.open(QFile::WriteOnly);
    QJsonDocument temp_doc;
    temp_doc.setObject(config);
    config_file.write(temp_doc.toJson(QJsonDocument::Indented));
    config_file.close();
    QMessageBox::information(this,tr("提示"),tr("重启生效"));
}





void TableEditWidget::on_pluginList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    showLog("Reading Plugin List",LogStatus::INFO);
    if (current == nullptr){
        return;
    }
    QString config_path = current->data(Qt::UserRole).toString();
    QFile file(config_path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
    QJsonObject PluginObject = document.object();
    ui->pluginInfo->clearContents();
    ui->pluginInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pluginInfo->setRowCount(4);
    ui->pluginInfo->setItem(0,0,new QTableWidgetItem("名称"));
    ui->pluginInfo->setItem(0,1,new QTableWidgetItem(PluginObject["name"].toString()));
    ui->pluginInfo->setItem(1,0,new QTableWidgetItem("版本"));
    ui->pluginInfo->setItem(1,1,new QTableWidgetItem(PluginObject["pluginVersion"].toString()));
    ui->pluginInfo->setItem(2,0,new QTableWidgetItem("作者"));
    ui->pluginInfo->setItem(2,1,new QTableWidgetItem(PluginObject["pluginAuthor"].toString()));
    ui->pluginInfo->setItem(3,0,new QTableWidgetItem("简介"));
    ui->pluginInfo->setItem(3,1,new QTableWidgetItem(PluginObject["pluginIntroduce"].toString()));

}


void TableEditWidget::on_pluginList_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox MyBox(QMessageBox::Warning,"警告","将会删除此插件，是否继续？",QMessageBox::Yes | QMessageBox::No,this);
    int clickedBut = MyBox.exec();
    if (clickedBut == QMessageBox::Yes){
        QDir dir(item->data(Qt::UserRole+1).toString());
        dir.removeRecursively();

        readPluginList();
        QMessageBox::information(this,"提示","删除完成");
        emit refechToolBar_signal();
    }


}

