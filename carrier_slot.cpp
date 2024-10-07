#include "carrier_slot.h"
#include "global.h"

CarrierSlot::CarrierSlot(int index, QWidget* parent, HWND hwnd) : QWidget{parent} {
    Global::containerMap.insert(index, this);
    this->index = index;
    this->hwnd = hwnd;
    this->setObjectName("carrierSlot" + QString::number(index));
}

int CarrierSlot::getIndex() {
    return this->index;
}

void CarrierSlot::setHwnd(HWND hwnd) {
    this->hwnd = hwnd;
}

HWND CarrierSlot::getHwnd() {
    return this->hwnd;
}

bool CarrierSlot::inited() {
    return this->hwnd != nullptr && IsWindow(this->hwnd);
}

void CarrierSlot::refresh() {
    if (this->inited()) {
        bool visibled = this->isVisible();
        this->setVisible(false);
        this->setVisible(visibled);
    }
}
