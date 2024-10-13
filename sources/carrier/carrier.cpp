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
    QWindow *externalWindow = QWindow::fromWinId((WId) hwnd);
    QWidget *wechat = QFrame::createWindowContainer(externalWindow, this);
    this->layout()->addWidget(wechat);
    this->slotMap.insert(uuid, new CarrierSlot(uuid, hwnd, wechat, externalWindow));
    this->slot_switch_cslot(uuid);
}

void Carrier::slot_switch_cslot(QString uuid) {
    for (auto &slot : this->slotMap) {
        slot->widget->setVisible(false);
    }
    CarrierSlot *slot = this->slotMap.value(uuid);
    if (slot != nullptr) {
        slot->widget->setVisible(true);
    }
}

void Carrier::slot_clear_cslot(QString uuid) {
    this->slotMap.removeIf([uuid](const QMap<QString, CarrierSlot*>::iterator it) {
        // 空指针代表清除全部,否则清除对应控件
        if (uuid == nullptr || uuid == it.value()->uuid) {
            it.value()->window->setParent(nullptr);
            it.value()->window->hide();
            it.value()->widget = nullptr;
            return true;
        }
        return false;
    });
}

void Carrier::refresh() {
    for (auto &slot : this->slotMap) {
        bool visibled = slot->widget->isVisible();
        slot->widget->setVisible(false);
        if (visibled) {
            slot->widget->setVisible(true);
        }
    }
}

CarrierSlot::CarrierSlot(QString uuid, HWND hwnd, QWidget *widget, QWindow *window)
    : uuid(uuid)
    , hwnd(hwnd)
    , widget(widget)
    , window(window)
{

}
