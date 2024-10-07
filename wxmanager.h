#ifndef WXMANAGER_H
#define WXMANAGER_H


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class WxManager;
}
QT_END_NAMESPACE

class WxManager : public QMainWindow {
    Q_OBJECT

public:
    WxManager(QWidget *parent = nullptr);
    ~WxManager();

protected:
    void moveEvent(QMoveEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    Ui::WxManager *ui;

signals:
    void allMoveEvent();
};
#endif // WXMANAGER_H
