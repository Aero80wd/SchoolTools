#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include<QMouseEvent>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    ClickLabel(QWidget* &);
    virtual void mouseClickEvent(QMouseEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);
    virtual bool event(QEvent *e);

signals:
    void clicked();
    void DoubleClicked();
};

#endif // CLICKLABEL_H
