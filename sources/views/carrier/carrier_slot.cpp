#include "carrier_slot.h"
#include <QVBoxLayout>

CarrierSlot::CarrierSlot(QString uuid, HWND hwnd, QWidget *parent) : QWidget{parent}, uuid(uuid), hwnd(hwnd) {
    GetWindowRect(hwnd, &rect);
    SetParent(hwnd, (HWND) this->winId());
    this->winStyle = GetWindowLong(hwnd, GWL_STYLE);
    this->winExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

    this->window = QWindow::fromWinId((WId) hwnd);
    this->widget = QWidget::createWindowContainer(this->window, this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setObjectName("CarrierSlotLayout" + uuid);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(this->widget);
    this->setLayout(layout);
}

QString CarrierSlot::getUuid() {
    return this->uuid;
}

QWidget *CarrierSlot::getWidget() {
    return this->widget;
}

void CarrierSlot::showSlot() {
    this->setVisible(true);
    this->widget->setVisible(true);
    this->window->setVisible(true);
}

void CarrierSlot::hideSlot() {
    this->setVisible(false);
    this->widget->setVisible(false);
    this->window->setVisible(false);
}

void CarrierSlot::clear() {
    this->layout()->removeWidget(this->widget);
    this->widget->setParent(nullptr);
    this->window->setParent(nullptr);

    SetParent(this->hwnd, GetDesktopWindow());
    SetWindowLongPtr(this->hwnd, GWL_STYLE, this->winStyle);
    SetWindowLongPtr(this->hwnd, GWL_EXSTYLE, this->winExStyle);
    SetWindowPos(
        hwnd, nullptr, rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_NOREDRAW | SWP_HIDEWINDOW
    );
    ShowWindow(hwnd, SW_HIDE);
}
