#ifndef NAV_HEADER_H
#define NAV_HEADER_H

#include <QFrame>
#include "nav_selector.h"
#include "qt_windows.h"

namespace Ui {
    class NavHeader;
}

class NavHeader : public QFrame {
    Q_OBJECT
    Q_PROPERTY(NavSelector *q_selector READ q_selector CONSTANT)

public:
    explicit NavHeader(QWidget *parent = nullptr);
    ~NavHeader();

    Ui::NavHeader* q_ui() const { return this->ui; }
    NavSelector* q_selector() const { return this->selector; }

signals:
    void signal_selected(HWND hwnd);

private:
    Ui::NavHeader *ui;
    NavSelector *selector;

    void initSelector();
};

#endif // NAV_HEADER_H
