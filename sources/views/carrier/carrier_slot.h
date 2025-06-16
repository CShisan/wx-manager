#ifndef CARRIER_SLOT_H
#define CARRIER_SLOT_H

#include "qt_windows.h"
#include <QWidget>
#include <QWindow>

class EventBlocker : public QObject {
protected:
    bool resize = false;
    bool eventFilter(QObject *obj, QEvent *event) override {
        qDebug() << event->type();
        if (event->type() == QEvent::Resize) {
            if (resize) {
                QWidget *widget = qobject_cast<QWidget*>(obj);
                if (widget) {
                    qDebug() << widget->size();
                    qDebug() << "==============";
                    QWidget *parent = widget->parentWidget();
                    qDebug() << parent->size();
                    qDebug() << widget->size();
                    qDebug() << "==============";
                    widget->setFixedSize(parent->size());
                    qDebug() << parent->size();
                    qDebug() << widget->size();
                    qDebug() << "==============";
                    qDebug() << "拦截事件";
                    return true;
                }
            } else {
                resize = true;
            }
        }
        return QObject::eventFilter(obj, event);
    }
};

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
    EventBlocker *blocker;

    RECT rect;
    LONG winStyle;
    LONG winExStyle;
signals:
};

#endif // CARRIER_SLOT_H
