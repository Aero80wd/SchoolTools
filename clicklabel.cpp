#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget* &) {

}
void ClickLabel::mouseClickEvent(QMouseEvent* e){
    qDebug("signal clicked()");
    setWindowFlags(Qt::Widget);
    emit clicked();
}
void ClickLabel::mouseDoubleClickEvent(QMouseEvent* e){
    qDebug("signal DoubleClicked()");
    setWindowFlags(Qt::Widget);
    emit DoubleClicked();
}
bool ClickLabel::event(QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
        if(mouseEvent->button() == Qt::LeftButton)
        {
            emit clicked();
            return true;
        }
    }
    if (e->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
        if(mouseEvent->button() == Qt::LeftButton)
        {
            emit DoubleClicked();
            return true;
        }
    }
    return QLabel::event(e);
}
