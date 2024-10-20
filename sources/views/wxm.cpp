#include "wxm.h"
#include "ui_wxm.h"
#include "settings/settings.h"
#include "sources/config/property.h"
#include "sources/common/utils/wechat.h"
#include <QHBoxLayout>

Wxm::Wxm(QWidget *parent) : QMainWindow(parent), ui(new Ui::Wxm) {
    ui->setupUi(this);
    this->initMenus();
    this->initCenter();
}

Wxm::~Wxm() {
    delete ui;
    delete nav;
    delete carrier;
}

void Wxm::initMenus() {
    QAction *start = new QAction(QIcon(QPixmap(":/icons/start.svg")), "启动", ui->operate);
    QObject::connect(start, &QAction::triggered, this, []() {
        Property *properies = Property::instance();
        Wechat::start(properies->read(Property::Names::MOPEN_NUM, 2));
    });

    QAction *settings = new QAction(QIcon(QPixmap(":/icons/setting.svg")), "应用配置", ui->operate);
    QObject::connect(settings, &QAction::triggered, this, [this]() {
        Settings *dialog = new Settings(this);
        dialog->exec();
    });

    ui->operate->addActions({ start, settings });

    ui->about->addAction(QIcon(QPixmap(":/icons/write.svg")), "by cshisan");
    ui->about->addAction(QIcon(QPixmap(":/icons/version.svg")), "v1.0.0");
}

void Wxm::initCenter() {
    this->nav = new Nav(ui->center);
    this->carrier = new Carrier(ui->center);
    QHBoxLayout *layout = new QHBoxLayout(ui->center);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(nav);
    layout->addWidget(this->carrier);
    ui->center->setLayout(layout);

    QObject::connect(this->nav, &Nav::signal_embed_cslot, this->carrier, &Carrier::slot_embed_cslot);
    QObject::connect(this->nav, &Nav::signal_switch_cslot, this->carrier, &Carrier::slot_switch_cslot);
    QObject::connect(this->nav, &Nav::signal_clear_cslot, this->carrier, &Carrier::slot_clear_cslot);
}

void Wxm::moveEvent(QMoveEvent *event) {
    // 主要是为了解决微信存在透明层问题(窗口移动时透明层会留在原地)
    this->carrier->refresh();
    event->accept();
}

void Wxm::closeEvent(QCloseEvent *event) {
    emit this->nav->signal_clear_cslot();
    event->accept();
}
