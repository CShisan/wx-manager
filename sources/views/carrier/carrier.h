#ifndef CARRIER_H
#define CARRIER_H

#include "qt_windows.h"
#include "carrier_slot.h"

#include <QFrame>
#include <QMap>

namespace Ui {
    class Carrier;
}

class Carrier : public QFrame {
    Q_OBJECT

public:
    explicit Carrier(QWidget *parent = nullptr);
    ~Carrier();

    void refresh();

private:
    Ui::Carrier *ui;
    QMap<QString, CarrierSlot*> slotMap;

public slots:
    void slot_embed_cslot(QString uuid, HWND hwnd);
    void slot_switch_cslot(QString uuid);
    void slot_clear_cslot(QString uuid = nullptr);
};
#endif // CARRIER_H
