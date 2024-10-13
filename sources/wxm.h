#ifndef WXM_H
#define WXM_H

#include <QMainWindow>
#include <sources/carrier/carrier.h>
#include <sources/nav/nav.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Wxm;
}
QT_END_NAMESPACE

class Wxm : public QMainWindow
{
    Q_OBJECT

public:
    Wxm(QWidget *parent = nullptr);
    ~Wxm();

protected:
    void moveEvent(QMoveEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Wxm *ui;
    Nav *nav;
    Carrier *carrier;

    void initCenter();
};
#endif // WXM_H
