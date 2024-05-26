#ifndef ANISHOW_LABEL_H
#define ANISHOW_LABEL_H
#include<QLabel>
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>
#include<QRect>
#include<QPoint>
#endif // ANISHOW_LABEL_H
class AnimationLabel: public QWidget{
    Q_OBJECT
public:
    explicit AnimationLabel(QWidget *parent = nullptr);
    ~AnimationLabel();
    void Anishow();
    void AniHide();
    virtual void resizeEvent(QResizeEvent *event) override;
    QPropertyAnimation* ani_pos;
    QPropertyAnimation* ani_opty;
};
