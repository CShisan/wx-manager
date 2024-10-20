#include "carrier.h"
#include "ui_carrier.h"

#include <QVBoxLayout>
#include <QWindow>

Carrier::Carrier(QWidget *parent): QFrame(parent), ui(new Ui::Carrier) {
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setObjectName("carrierLayout");
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

Carrier::~Carrier() {
    delete ui;
}

void Carrier::slot_embed_cslot(QString uuid, HWND hwnd) {
    if (this->slotMap.value(uuid, nullptr) != nullptr) {
        return;
    }
    CarrierSlot *slot = new CarrierSlot(uuid, hwnd, this);
    this->layout()->addWidget(slot);
    this->slotMap.insert(uuid, slot);
    this->slot_switch_cslot(uuid);
}

void Carrier::slot_switch_cslot(QString uuid) {
    for (auto &slot : this->slotMap) {
        slot->hideSlot();
        this->layout()->removeWidget(slot);
    }
    CarrierSlot *slot = this->slotMap.value(uuid, nullptr);
    if (slot != nullptr) {
        slot->showSlot();
        this->layout()->addWidget(slot);
    }
}

void Carrier::slot_clear_cslot(QString uuid) {
    this->slotMap.removeIf([this, uuid](const QMap<QString, CarrierSlot*>::iterator it) {
        // 空指针代表清除全部,否则清除对应控件
        if (uuid == nullptr || uuid == it.value()->getUuid()) {
            it.value()->clear();
            this->layout()->removeWidget(it.value());
            return true;
        }
        return false;
    });
}

void Carrier::refresh() {
    this->setVisible(false);
    this->setVisible(true);
}
