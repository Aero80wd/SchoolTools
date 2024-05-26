#ifndef TABLEWIDGET_UPDOWN_H
#define TABLEWIDGET_UPDOWN_H

#include <QWidget>
#include <QTableWidget>
#include <QDropEvent>
#include <QDebug>
class tablewidget_updown : public QTableWidget
{
    Q_OBJECT
public:
    explicit tablewidget_updown(QWidget *parent = nullptr);
protected:
    void dropEvent(QDropEvent *event);
};

#endif // TABLEWIDGET_UPDOWN_H
