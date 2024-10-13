#include "../headers/getstartwidget.h"
#include "ui_getstartwidget.h"

GetStartWidget::GetStartWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GetStartWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->label_2,&ClickLabel::clicked,this,&GetStartWidget::close);
    ani_opty = new QPropertyAnimation(this,"windowOpacity");
    ani_opty->setDuration(500);
    ani_opty->setStartValue(0);
    ani_opty->setEndValue(1);
    initSignal();
    setWidgetBlur(this);
    this->installEventFilter(this);
    ui->widget_2->installEventFilter(this);
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
enum AccentState {
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,
    ACCENT_INVALID_STATE = 5
};

struct AccentPolicy {
    AccentState AccentState;
    int AccentFlags;
    int GradientColor;
    int AnimationId;
};
struct WindowCompositionAttributeData {
    int Attribute;
    PVOID Data;
    ULONG DataSize;
};
typedef BOOL(WINAPI*pSetWindowCompositionAttribute)(HWND, WindowCompositionAttributeData*);
pSetWindowCompositionAttribute SetWCA = nullptr;
void GetStartWidget::setWidgetBlur(QWidget* widget){
    if (!SetWCA) {
        HMODULE hModule = LoadLibrary(TEXT("user32.dll"));
        if (hModule) {
            SetWCA =
                (pSetWindowCompositionAttribute)GetProcAddress(hModule, "SetWindowCompositionAttribute");
        }
    }
    HWND hWnd = HWND(widget->winId());
    int gradientColor = DWORD(0x50F2F2F2);
    AccentPolicy policy = { ACCENT_ENABLE_ACRYLICBLURBEHIND, 0, gradientColor, 0 };
    WindowCompositionAttributeData data = { 19, &policy, sizeof(AccentPolicy) };
    SetWCA(hWnd, &data);
}
void GetStartWidget::initSignal(){
    connect(ui->continue_1,&QPushButton::clicked,this,[=]{
        ui->stackedWidget->setCurrentIndex(0);
        });
    connect(ui->continue_2,&QPushButton::clicked,this,[=]{
        ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->but_ok,&QPushButton::clicked,this,[=]{
        close();
    });
    connect(ui->config_tt,&QPushButton::clicked,this,[=]{
        hide();
        emit toSettings();
        show();
        ui->stackedWidget->setCurrentIndex(1);
    });
}
bool GetStartWidget::eventFilter(QObject* watched,QEvent* event){
    if (event->type() == QEvent::MouseButtonPress and watched == ui->widget){
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        if (mouse_event->buttons() == Qt::LeftButton){
            startPos = mouse_event->pos();
            tracking = true;
            // move(mouse_event->this->pos()()-QPoint(this->width()/2,0));
            return true;
        }
    }
    if (event->type() == QEvent::MouseMove){
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        back_show->setStartValue(pos() - QPoint(0,100));
        back_show->setEndValue(pos());

        back_show->setEasingCurve(QEasingCurve::InOutSine);
        back_show->setDuration(500);
        endPos = mouse_event->pos() - startPos;
        move(pos() + endPos - QPoint(width()/2,0));
        return true;

    }
    if (event->type() == QEvent::MouseButtonRelease){
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        if (mouse_event->buttons() == Qt::LeftButton){
            tracking = false;
        }

    }
    if (event->type() == QEvent::Show){
        if (!showed){
            back_show = new QPropertyAnimation(this,"pos");

            back_show->setStartValue(pos() - QPoint(0,100));
            back_show->setEndValue(pos());

            back_show->setEasingCurve(QEasingCurve::InOutSine);
            back_show->setDuration(500);
            back_show->setDirection(QAbstractAnimation::Forward);
            ani_opty->setDirection(QAbstractAnimation::Forward);
            ani_opty->start();
            back_show->start();
            showed = true;
        }


        return true;
    }

    return QDialog::eventFilter(watched,event);
}
void GetStartWidget::close(){
    back_show->setDirection(QAbstractAnimation::Backward);
    connect(back_show,&QPropertyAnimation::finished,this,[=]{
        QDialog::close();
    });
    ani_opty->setDirection(QAbstractAnimation::Backward);
    ani_opty->start();
    back_show->start();
}
GetStartWidget::~GetStartWidget()
{
    delete ui;
}


