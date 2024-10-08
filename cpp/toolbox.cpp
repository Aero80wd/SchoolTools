#include "../headers/toolbox.h"
#include "ui_toolbox.h"
ToolBox::ToolBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowType::FramelessWindowHint | Qt::WindowType::Tool | Qt::WindowType::WindowStaysOnBottomHint);
    setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground);
    LoadPlugins();
    setWidgetBlur(this);
    this->setAcceptDrops(true);
    this->installEventFilter(this);

}

ToolBox::~ToolBox()
{
    delete ui;
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
typedef BOOL(WINAPI*pSetWindowCompositionAttribute114)(HWND, WindowCompositionAttributeData*);
pSetWindowCompositionAttribute114 SetWindowCompositionAttribute114 = nullptr;

COLORREF GetWindowsThemeColor()
{
    DWORD crColorization;
    BOOL fOpaqueBlend;
    COLORREF theme_color{};
    HRESULT result = DwmGetColorizationColor(&crColorization, &fOpaqueBlend);
    if (result == S_OK)
    {
        BYTE r, g, b;
        r = int((crColorization >> 16) * 1.06) % 256;
        g = int((crColorization >> 8) * 1.06) % 256;
        b = int(crColorization * 1.06) % 256;
        theme_color = RGB(r, g, b);
    }
    return theme_color;
}
void ToolBox::setWidgetBlur(QWidget* widget){
    if (!SetWindowCompositionAttribute114) {
        HMODULE hModule = LoadLibrary(TEXT("user32.dll"));
        if (hModule) {
            SetWindowCompositionAttribute114 =
                (pSetWindowCompositionAttribute114)GetProcAddress(hModule, "SetWindowCompositionAttribute");
        }
    }
    HWND hWnd = HWND(widget->winId());
    int gradientColor = DWORD(GetWindowsThemeColor());
    AccentPolicy policy = { ACCENT_ENABLE_ACRYLICBLURBEHIND , 0, gradientColor, 0 };
    WindowCompositionAttributeData data = { 19, &policy, sizeof(AccentPolicy) };
    SetWindowCompositionAttribute114(hWnd, &data);
}

void ToolBox::LoadPlugins(){
    for (auto x:findChildren<ClickLabel*>()){
        delete x;
    }
    QDir plugin_dir(QDir::currentPath() + "/plugins");
    if (!plugin_dir.exists()){
        plugin_dir.mkdir(QDir::currentPath() + "/plugins");
        return;
    }
    QFileInfoList fileList = plugin_dir.entryInfoList();
    for (auto x : fileList){
        QString JsonPath = x.filePath() + "/pluginConfig.json";
        if (x.filePath()[x.filePath().size() -1] == '.'){
            continue;
        }
        QFile file(x.filePath() + "/pluginConfig.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString value = file.readAll();
        file.close();

        QJsonParseError parseJsonErr;
        QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
        QJsonObject PluginObject = document.object();
        ClickLabel *PluginBut = new ClickLabel(this);
        ui->verticalLayout->addWidget(PluginBut);

        PluginBut->setMinimumSize(QSize(50,50));
        PluginBut->setAniOpen(true);
        PluginBut->setCursor(Qt::PointingHandCursor);
        adjustSize();

        PluginBut->setStyleSheet(QString("image: url(\"%1\");").arg(x.filePath() + "/" + PluginObject["icon"].toString()));
        if (PluginObject["type"].toString() == "win32"){

            connect(PluginBut,&ClickLabel::clicked,this,[=]{
                ShellExecute(NULL,L"open",QString("%1/%2").arg(x.filePath()).arg(PluginObject["execPath"].toString()).toStdWString().c_str(),NULL,NULL,SW_SHOW);
            });
        }
        if (PluginObject["type"].toString() == "url"){

            connect(PluginBut,&ClickLabel::clicked,this,[=]{
                QWebEngineView *web_window = new QWebEngineView();
                web_window->setWindowTitle(PluginObject["name"].toString());
                web_window->setUrl(QUrl(PluginObject["url"].toString()));
                web_window->page()->profile()->setHttpUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36 Edg/127.0.0.0");
                web_window->show();
            });
        }
        if (PluginObject["type"].toString() == "html"){

            connect(PluginBut,&ClickLabel::clicked,this,[=]{
                QWebEngineView *web_window = new QWebEngineView();
                web_window->setWindowTitle(PluginObject["name"].toString());
                web_window->setUrl(QUrl(x.filePath() + "/" + PluginObject["index"].toString()));
                web_window->page()->profile()->setHttpUserAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/127.0.0.0 Safari/537.36 Edg/127.0.0.0");
                web_window->show();
            });
        }
        if (PluginObject["type"].toString() == "link"){

            connect(PluginBut,&ClickLabel::clicked,this,[=]{
                QFileInfo info(PluginObject["linkPath"].toString());
                if (info.exists() && info.isSymLink()){
                    ShellExecute(NULL,L"open",info.symLinkTarget().toStdWString().c_str(),NULL,NULL,SW_SHOW);
                }
            });
        }

    }
}
