#include "tableeditwidget.h"
#include "ui_tableeditwidget.h"

TableEditWidget::TableEditWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TableEditWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("课程表设置");
    this->setWindowIcon(QIcon(":/res/a.png"));
    ui->tabWidget->removeTab(2);
    connect(ui->radioButton,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->radioButton_2,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->radioButton_3,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->radioButton_4,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->radioButton_5,SIGNAL(toggled(bool)),this,SLOT(toggleded()));
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{
        ui->tabWidget->removeTab(2);
    });
    connect(ui->label,&ClickLabel::DoubleClicked,this,[=]{
        ui->tabWidget->insertTab(2,ui->tab_3,QString("彩蛋设置"));
    });
    readTableJson();

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
void TableEditWidget::setConfig(QJsonObject obj){
    config=obj;
    ui->checkBox_2->setChecked(config.value("zuan_status").toBool());
    ui->checkBox->setChecked(config.value("muyu_status").toBool());
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
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }
    timeTable = jsondoc.object();


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
    qDebug() << "switch";
    if (ui->radioButton->isChecked()){
        qDebug() << timeTable.value("Mon").toArray();
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
    }else{
        qDebug() << "no";
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
    qDebug() << "sorted:" << editarray;
    timeTable[key] = editarray;
    QFile config_file(QDir::currentPath() + "/tables.json");
    config_file.open(QFile::WriteOnly);
    QJsonDocument temp_doc;
    temp_doc.setObject(timeTable);
    config_file.write(temp_doc.toJson(QJsonDocument::Indented));
    config_file.close();
    toggleded();

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
    }else{
        qDebug() << "no";
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
    QMessageBox::information(this,"提示","重启生效");

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
    QMessageBox::information(this,"提示","重启生效");
}

