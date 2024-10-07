#ifndef SELECTOR_H
#define SELECTOR_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <Windows.h>
#include "carrier_slot.h"

class Selector : public QLabel {
    Q_OBJECT

public:
    explicit Selector(QWidget *parent = nullptr);

protected:
    bool isWechatWindow(HWND hwnd);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    // void paintEvent(QPaintEvent *event) override;

signals:
    void selected(CarrierSlot *container);

};

#endif // SELECTOR_H
