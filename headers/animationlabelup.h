#ifndef ANIMATIONLABELUP_H
#define ANIMATIONLABELUP_H

#include <QWidget>
#include<QLabel>
#include<QResizeEvent>
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>
class AnimationLabelUp: public QLabel{
    Q_OBJECT
public:
    AnimationLabelUp(QWidget *parent = nullptr);
    ~AnimationLabelUp();
    void Anishow();
    void AniHide();
    int time = 700;
    void setTime(int secs){
        time = secs;
    }
    virtual void resizeEvent(QResizeEvent *event) override;
    QPropertyAnimation* ani_pos;
    QPropertyAnimation* ani_opty;
};


#endif // ANIMATIONLABELUP_H
