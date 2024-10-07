#include "navmain.h"
#include "global.h"
#include "carrier_slot.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>

NavMain::NavMain(QWidget *parent) : QListWidget{parent} {
}

void NavMain::add() {
    int index = ++Global::maxSlotIndex;

    QWidget* widget = new QWidget(this);
    QString btnText = "容器" + QString::number(index);
    QPushButton *button = new QPushButton(btnText, widget);

    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);

    QListWidgetItem *item = new QListWidgetItem(this);
    item->setSizeHint(widget->sizeHint());
    this->setItemWidget(item, widget);

    emit notifyAddSlot(index, button);
}
