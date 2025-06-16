#include "nav_center.h"
#include "ui_nav_center.h"

NavCenter::NavCenter(QWidget * parent) : QListWidget(parent), ui(new Ui::NavCenter) {
    ui->setupUi(this);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setStyleSheet(
      "QListWidget { background: transparent; }"
      "QListWidget::Item { margin: 3px; }"
      "QListWidget::Item:hover{ background: grey; }"
      "QListWidget::Item:selected{ background: grey; }"
      "QListWidget::Item:selected:!active{ background: grey; }"
    );


    // 标签被选择时发送"切换标签"信号
    QObject::connect(this, & NavCenter::currentItemChanged, this, [this](QListWidgetItem * current) {
        // 删除标签时也会触发
        if (current != nullptr) {
            NavTag * tag = static_cast<NavTag*>(this->itemWidget(current));
            emit this->signal_switch_tag(static_cast<NavTag*>(tag));
        }
    });
}

NavCenter::~NavCenter() {
    delete ui;
}

/**
 * 添加标签
 *
 * @brief NavCenter::slot_add_tag
 */
void NavCenter::slot_add_tag() {
    QListWidgetItem * item = new QListWidgetItem();
    NavTag * tag = new NavTag(item, this);
    tag->setText("容器" + QString::number(this->count() + 1));
    // 绑定"删除"按钮触发事件
    QObject::connect(tag, & NavTag::signal_del_tag, this, [this](NavTag * tag) {
        emit this->signal_del_tag(tag);
        this->removeItemWidget(tag->getItem());
        delete tag->getItem();

        // 重新设置tag文本
        this->resetTagText();
    });


    QSize size(tag->sizeHint().width(), tag->sizeHint().height() + 6);
    item->setSizeHint(size);
    this->addItem(item);
    this->setItemWidget(item, tag);
    this->setCurrentItem(item);
}

void NavCenter::slot_del_tag() {
    QListWidgetItem * current = this->currentItem();
    if (current != nullptr) {
        NavTag * tag = static_cast<NavTag*>(this->itemWidget(current));
        emit tag->signal_del_tag(tag);
    }
}

void NavCenter::resetTagText() {
    for (int i = 0; i < this->count(); ++i) {
        QListWidgetItem * item = this->item(i);
        NavTag * tag = static_cast<NavTag*>(this->itemWidget(item));
        tag->setText("容器" + QString::number(i + 1));
    }
}


