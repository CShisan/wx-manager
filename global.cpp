#include "global.h"

Global::Global() {
    containerMap.insert(0, nullptr);
}

QMap<int, CarrierSlot*> Global::containerMap;
int Global::maxSlotIndex = 0;
int Global::curSlotIndex = 0;


void Global::clearCtns() {
    HWND desktop = GetDesktopWindow();
    for (CarrierSlot *slot : Global::containerMap.values()) {
        if (slot->inited()) {
            HWND target = slot->getHwnd();
            SetParent(target, desktop);
            ShowWindow(target, SW_HIDE);
            qDebug() << "容器" << slot->getIndex() << "清理完成";
        }

    }
}

CarrierSlot* Global::curSlot() {
    return Global::containerMap.value(Global::curSlotIndex);
}
