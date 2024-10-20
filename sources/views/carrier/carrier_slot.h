#ifndef CARRIER_SLOT_H
#define CARRIER_SLOT_H

#include "qt_windows.h"

#include <QWidget>
#include <QWindow>

class CarrierSlot : public QWidget {
    Q_OBJECT
public:
    explicit CarrierSlot(QString uuid, HWND hwnd, QWidget *parent = nullptr);

    QString getUuid();
    QWidget* getWidget();
    void showSlot();
    void hideSlot();
    void clear();

private:
    QString uuid;
    HWND hwnd;
    QWindow *window;
    QWidget *widget;

    RECT rect;
    LONG winStyle;
    LONG winExStyle;

signals:
};

#endif // CARRIER_SLOT_H
