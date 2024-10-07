#ifndef CARRIER_H
#define CARRIER_H

#include "global.h"
#include "carrier_slot.h"
#include <QFrame>
#include <QPushButton>

class Carrier : public QFrame {
    Q_OBJECT
public:
    explicit Carrier(QWidget *parent = nullptr);

protected:
    void switchSlot(CarrierSlot *slot);

public slots:
    void addSlot(int index, QPushButton *button);
    void embed(CarrierSlot *container);
    void allMoveEvent();
};

#endif // CARRIER_H
