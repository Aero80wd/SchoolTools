#include "twtodowidget.h"
#include "ui_twtodowidget.h"

TWTodoWidget::TWTodoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TWTodoWidget)
{
    ui->setupUi(this);
    readTodos();
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

TWTodoWidget::~TWTodoWidget()
{
    delete ui;
}

void TWTodoWidget::newTodo(QString name,bool n){
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
        QListWidgetItem *item = ui->listWidget->currentItem();
        QWidget *widget = ui->listWidget->itemWidget(item);
        QLabel* curLabel = textLabel;
        QCheckBox* box = okbox;
        box->setDisabled(true);

        QJsonArray temparray;

        for (auto x:todos){

            if (x == textLabel->text()){
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
void TWTodoWidget::readTodos(){
    showLog("Reading Todos",LogStatus::INFO);
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
void TWTodoWidget::on_butAdd_clicked()
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

