#include "wxmmenubar.h"
#include "setting.h"
#include "wechat.h"


CustomQMenu::CustomQMenu(const QString &title, QWidget *parent) : QMenu(title, parent) {

}

void CustomQMenu::contextMenuEvent(QContextMenuEvent *event) {
    qDebug() << event;
}


WxmMenuBar::WxmMenuBar(QWidget *parent) : QMenuBar(parent) {
    QMenu *operate = new QMenu("操作", this);
    QAction *start = new QAction(QIcon(QPixmap(":/icons/start.svg")), "启动程序", operate);
    QObject::connect(start, &QAction::triggered, this, []() {
        Wechat::start(Setting::read("mopenNum", 2));
    });
    QAction *settings = new QAction(QIcon(QPixmap(":/icons/setting.svg")), "应用配置", operate);
    QObject::connect(settings, &QAction::triggered, this, [parent]() {
        Setting::instance(parent)->exec();
    });
    operate->addActions({start, settings});
    this->addMenu(operate);


    // 隐藏图标
    QMenu *about = new QMenu("关于", this);
    about->addAction(QIcon(QPixmap(":/icons/write.svg")), "作者  cshisan");
    about->addAction(QIcon(QPixmap(":/icons/version.svg")), "版本  v1.0.0");
    this->addMenu(about);
}

