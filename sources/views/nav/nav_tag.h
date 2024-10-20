#ifndef NAV_TAG_H
#define NAV_TAG_H

#include <QFrame>
#include <QListWidgetItem>

namespace Ui {
    class NavTag;
}

class NavTag : public QFrame {
    Q_OBJECT

public:
    explicit NavTag(QListWidgetItem* item, QWidget *parent = nullptr);
    ~NavTag();

    QListWidgetItem* getItem();
    QString getUuid();
    void setText(QString text);

signals:
    void signal_del_tag(NavTag*);

private:
    Ui::NavTag *ui;
    QListWidgetItem* item;
    QString uuid;
};

#endif // NAV_TAG_H
