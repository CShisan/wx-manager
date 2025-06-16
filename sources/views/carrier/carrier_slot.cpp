#include "carrier_slot.h"
#include <QVBoxLayout>

CarrierSlot::CarrierSlot(QString uuid, HWND hwnd, QWidget *parent) : QWidget{parent}, uuid(uuid), hwnd(hwnd) {
    GetWindowRect(hwnd, &rect);
    this->winStyle = GetWindowLong(hwnd, GWL_STYLE);
    this->winExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

    this->window = QWindow::fromWinId((WId) hwnd);
    this->blocker = new EventBlocker;
    this->window->installEventFilter(this->blocker);
    this->widget = QWidget::createWindowContainer(this->window, this);
    this->widget->winId(); // 调用winId方法使得wechat变成native窗口,否则会以wxp为父节点而不是slot

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
}

void CarrierSlot::hideSlot() {
    this->setVisible(false);
}

void CarrierSlot::clear() {
    this->layout()->removeWidget(this->widget);
    this->widget->setParent(nullptr);
    this->window->setParent(nullptr);

    // SetParent(this->hwnd, GetDesktopWindow());
    SetWindowLongPtr(this->hwnd, GWL_STYLE, this->winStyle);
    SetWindowLongPtr(this->hwnd, GWL_EXSTYLE, this->winExStyle);
    SetWindowPos(
        hwnd, nullptr, rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_NOREDRAW
    );
    // ShowWindow(hwnd, SW_HIDE);
}
