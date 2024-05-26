#include "anishow_label.h"
AnimationLabel::AnimationLabel(QWidget *parent):QWidget(parent){
    // QGraphicsOpacityEffect *label_opty = new QGraphicsOpacityEffect(this);
    // label_opty->setOpacity(1);
    // this->setGraphicsEffect(label_opty);
    // ani_pos = new QPropertyAnimation(this,"pos");
    // ani_pos->setDuration(500);
    // ani_pos->setStartValue(QPoint(this->pos().x() + 100,this->pos().y()));
    // ani_pos->setEndValue(QPoint(this->pos().x(),this->pos().y()));
    // qDebug() << this->pos();
    // ani_pos->setEasingCurve(QEasingCurve::InOutQuad);
    // ani_opty = new QPropertyAnimation(this,"opacity");
    // ani_opty->setDuration(500);
    // ani_opty->setStartValue(0);
    // ani_opty->setEndValue(1);
}
AnimationLabel::~AnimationLabel()
{

}
void AnimationLabel::resizeEvent(QResizeEvent *event){
    QGraphicsOpacityEffect *label_opty = new QGraphicsOpacityEffect(this);
    label_opty->setOpacity(1);
    this->setGraphicsEffect(label_opty);
    ani_pos = new QPropertyAnimation(this,"pos");
    ani_pos->setDuration(500);
    ani_pos->setStartValue(QPoint(this->pos().x() + 200,this->pos().y()));
    ani_pos->setEndValue(QPoint(this->pos().x(),this->pos().y()));
    qDebug() << this->pos();
    ani_pos->setEasingCurve(QEasingCurve::InOutSine);
    ani_opty = new QPropertyAnimation(label_opty,"opacity",this);
    ani_opty->setDuration(500);
    ani_opty->setStartValue(0);
    ani_opty->setEndValue(1);
}
void AnimationLabel::Anishow(){
    this->show();
    ani_pos->setDirection(QAbstractAnimation::Forward);
    ani_opty->setDirection(QAbstractAnimation::Forward);
    //动画同时开始
    ani_pos->start();
    ani_opty->start();

}
void AnimationLabel::AniHide(){
    this->show();
    ani_pos->setDirection(QAbstractAnimation::Backward);
    ani_opty->setDirection(QAbstractAnimation::Backward);
    //动画同时开始
    ani_pos->start();
    ani_opty->start();
}

