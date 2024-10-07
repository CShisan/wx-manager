#ifndef NAVLISTVIEW_H
#define NAVLISTVIEW_H

#include <QListWidget>
#include <QPushButton>

class NavMain : public QListWidget
{
    Q_OBJECT
public:
    explicit NavMain(QWidget *parent = nullptr);

signals:
    void notifyAddSlot(int index, QPushButton *button);

public slots:
    void add();
};

#endif // NAVLISTVIEW_H
