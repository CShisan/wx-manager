#include "nav.h"
#include "ui_nav.h"
#include <QHBoxLayout>
#include <QPushButton>

Nav::Nav(QWidget *parent) : QFrame(parent) , ui(new Ui::Nav) {
    ui->setupUi(this);
    initHeader();
    initCenter();

    // 绑定"添加"按钮触发"添加标签"事件
    QObject::connect(
        this->header->q_ui()->add_btn, &QPushButton::clicked,
        this->center, &NavCenter::slot_add_tag
    );
    // 绑定"删除"按钮触发"删除标签"事件
    QObject::connect(
        this->header->q_ui()->del_btn, &QPushButton::clicked,
        this->center, &NavCenter::slot_del_tag
    );
    // 绑定"选择器"触发"嵌入"信号
    QObject::connect(
        this->header->q_selector(), &NavSelector::signal_selected,
        this, [this](HWND hwnd) {
            QListWidgetItem *current = this->center->currentItem();
            if (current != nullptr) {
                NavTag *tag = static_cast<NavTag*>(this->center->itemWidget(current));
                emit this->signal_embed_cslot(tag->getUuid(), hwnd);
            }
        }
    );
    // 绑定"标签"点击触发切换"载体"信号
    QObject::connect(this->center, &NavCenter::signal_switch_tag, this, [this](NavTag* tag){
        emit this->signal_switch_cslot(tag->getUuid());
    });
    // 绑定"标签"点击触发切换"载体"信号
    QObject::connect(this->center, &NavCenter::signal_del_tag, this, [this](NavTag* tag){
        emit this->signal_clear_cslot(tag->getUuid());
    });
}

Nav::~Nav() {
    delete ui;
    delete header;
    delete center;
}

void Nav::resizeEvent(QResizeEvent *event)  {
    center->resize(event->size());
    event->accept();
}

void Nav::initHeader() {
    this->header = new NavHeader(ui->header);
    this->init(ui->header, this->header);
}

void Nav::initCenter() {
    this->center = new NavCenter(ui->center);
    this->init(ui->center, this->center);
}

void Nav::init(QWidget* parent, QWidget* child) {
    child->setStyle(parent->style());
    child->setSizePolicy(parent->sizePolicy());
    child->setGeometry(
        parent->geometry().x(),
        parent->geometry().y(),
        parent->geometry().width(),
        parent->geometry().height()
    );
    QHBoxLayout layout(parent);
    layout.setContentsMargins(0, 0, 0, 0);
    layout.addWidget(child);
    parent->setLayout(&layout);
}
