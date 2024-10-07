#include "carrier.h"
#include <QWindow>
#include <QVBoxLayout>

Carrier::Carrier(QWidget *parent) : QFrame{parent} {
    qDebug() << "容器初始化";
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setObjectName("carrierLayout");
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);


}

void Carrier::addSlot(int index, QPushButton *button) {
    CarrierSlot *slot = new CarrierSlot(index, this);
    QHBoxLayout* layout = new QHBoxLayout(slot);
    layout->setObjectName("carrierSlotLayout" + QString::number(index));
    layout->setContentsMargins(0, 0, 0, 0);
    slot->setLayout(layout);
    this->layout()->addWidget(slot);
    this->switchSlot(slot);

    // 容器选择按钮 绑定 对应插槽
    QObject::connect(button, &QPushButton::clicked, this, [this, slot](){
        this->switchSlot(slot);
    });
}

void Carrier::switchSlot(CarrierSlot *slot) {
    Global::curSlotIndex = slot->getIndex();
    QList<CarrierSlot *> children = this->findChildren<CarrierSlot *>();
    for (CarrierSlot *child : children) {
        child->setVisible(false);
        if (child->objectName() == slot->objectName()) {
            child->setVisible(true);
        }
    }
}

void Carrier::embed(CarrierSlot *slot) {
    if (slot == nullptr || !slot->inited()) {
        qDebug() << "插槽未初始化";
        return;
    }
    qDebug() << "WeChat嵌入插槽";
    HWND target = slot->getHwnd();
    QWindow *externalWindow = QWindow::fromWinId((WId) target);
    QWidget *wechat = QWidget::createWindowContainer(externalWindow, (QWidget*)slot);

    // 防止子窗口超出父窗口显示
    wechat->setParent(slot);
    slot->setParent(this);
    slot->layout()->addWidget(wechat);
}

void Carrier::allMoveEvent() {
    QList<CarrierSlot*> slotList = Global::containerMap.values();
    for (CarrierSlot* slot : slotList) {
        slot->refresh();
    }
}
