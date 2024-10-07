#ifndef GLOBAL_H
#define GLOBAL_H

#include <Windows.h>
#include <QMap>
#include "carrier_slot.h"
#include <QDebug>

class Global
{
public:
    Global();
    static QMap<int, CarrierSlot*> containerMap;
    static int maxSlotIndex;
    static int curSlotIndex;
    static void clearCtns();
    static CarrierSlot* curSlot();
};


#endif // GLOBAL_H
