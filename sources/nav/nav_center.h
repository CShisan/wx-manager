#ifndef NAV_CENTER_H
#define NAV_CENTER_H

#include "nav_tag.h"

#include <QListWidget>
#include <QMap>

namespace Ui {
    class NavCenter;
}

class NavCenter : public QListWidget {
    Q_OBJECT

public:
    explicit NavCenter(QWidget *parent = nullptr);
    ~NavCenter();

public slots:
    void slot_add_tag();
    void slot_del_tag();

private:
    Ui::NavCenter *ui;

    void resetTagText();

signals:
    void signal_switch_tag(NavTag*);
    void signal_del_tag(NavTag*);
};

#endif // NAV_CENTER_H
