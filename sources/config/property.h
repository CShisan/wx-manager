#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>
#include <QSettings>
#include <QMap>

class Property : public QObject {
    Q_OBJECT

public:
    enum Names {
        MOPEN_NUM
    };
    QMap<Names, QString> namesMap;
    template<typename T>
    void write(Names property, T value) {
        QString propertyName = Property::namesMap.value(property, "");
        Property::settings->beginGroup(Property::groupName);
        Property::settings->setValue(propertyName, value);
        Property::settings->endGroup();
    }
    template<typename T>
    T read(Names property, T defaultVal) {
        QString propertyName = Property::namesMap.value(property, "");
        Property::settings->beginGroup(Property::groupName);
        T value = Property::settings->value(propertyName, defaultVal).template value<T>();
        Property::settings->endGroup();
        return value;
    }

    static Property* instance();

private:
    explicit Property(QObject *parent = nullptr);

    static Property *that;
    QSettings* settings;
    QString groupName;

};

#endif // PROPERTY_H
