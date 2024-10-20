#ifndef NAV_SELECTOR_H
#define NAV_SELECTOR_H

#include "qt_windows.h"

#include <QLabel>
#include <QMouseEvent>

namespace Ui {
    class NavSelector;
}

class NavSelector : public QLabel {
    Q_OBJECT

public:
    explicit NavSelector(QWidget *parent = nullptr);
    ~NavSelector();

protected:
    bool isWechatWindow(HWND hwnd);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::NavSelector *ui;

signals:
    void signal_selected(HWND hwnd);
};

#endif // NAV_SELECTOR_H
