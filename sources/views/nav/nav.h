#ifndef NAV_H
#define NAV_H

#include "nav_center.h"
#include "nav_header.h"
#include "ui_nav_center.h"
#include "ui_nav_header.h"

#include <QFrame>

namespace Ui {
    class Nav;
}

class Nav : public QFrame {
    Q_OBJECT

public:
    explicit Nav(QWidget *parent = nullptr);
    ~Nav();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::Nav *ui;
    NavHeader *header;
    NavCenter *center;

    void init(QWidget* parent, QWidget* child);
    void initHeader();
    void initCenter();

signals:
    void signal_embed_cslot(QString, HWND);
    void signal_switch_cslot(QString);
    void signal_clear_cslot(QString uuid = nullptr);
};

#endif // NAV_H
