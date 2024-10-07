#ifndef CARRIER_SLOT_H
#define CARRIER_SLOT_H

#include <windows.h>
#include <functional>
#include <QWidget>
#include <QMouseEvent>

class CarrierSlot : public QWidget {
    Q_OBJECT
public:
    CarrierSlot(int index, QWidget* parent, HWND hwnd = nullptr);
    int getIndex();
    HWND getHwnd();
    void setHwnd(HWND hwnd);
    bool inited();
    void refresh();

private:
    int index;
    HWND hwnd;
    bool visabled;
};

#endif // CARRIER_SLOT_H
