#include "property.h"
#include <QMetaEnum>
#include <QMetaObject>

Property::Property(QObject *parent): QObject{parent} {
    this->settings = new QSettings("setting.ini", QSettings::IniFormat);
    this->groupName = "Property";
    this->namesMap.insert(Names::MOPEN_NUM, "mopen_num");
}

Property* Property::that = nullptr;
Property* Property::instance() {
    if (that == nullptr) {
        that = new Property();
    }
    return that;
}
