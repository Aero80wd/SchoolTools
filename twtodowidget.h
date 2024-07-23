#ifndef TWTODOWIDGET_H
#define TWTODOWIDGET_H

#include <QWidget>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QCheckBox>
#include<QFile>
#include<QDir>
#include<QInputDialog>
#include<QTranslator>
namespace Ui {
class TWTodoWidget;
}

class TWTodoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TWTodoWidget(QWidget *parent = nullptr);
    ~TWTodoWidget();
    QJsonArray todos;
    void readTodos();
    void newTodo(QString name,bool n=false);
    QJsonObject Config;
private slots:
    void on_butAdd_clicked();

private:
    Ui::TWTodoWidget *ui;
};

#endif // TWTODOWIDGET_H
