#include "nav_tag.h"
#include "ui_nav_tag.h"
#include <QUuid>

NavTag::NavTag(QListWidgetItem * item, QWidget * parent)
: QFrame(parent)
, ui(new Ui::NavTag)
, item(item)
, uuid(QUuid::createUuid().toString()) {
    ui->setupUi(this);
    ui->close->setStyleSheet(
      "QPushButton { background-color: none; border: none; }"
      "QPushButton:hover { "
      "   background-color: none; "
      "   border: none; "
      "   color: rgb(100, 100, 100); "
      "}"
    );
    this->setStyleSheet("NavTag { border: 1px solid #171717; border-radius: 5px; }");

    // 绑定"删除"按钮触发事件
    QObject::connect(ui->close, & QPushButton::clicked, this, [this]() {
        emit this->signal_del_tag(this);
    });
}

NavTag::~NavTag() {
    delete ui;
}

QListWidgetItem * NavTag::getItem() {
    return this->item;
}

QString NavTag::getUuid() {
    return this->uuid;
}

void NavTag::setText(QString text) {
    ui->text->setText(text);
}
