#include "wxmanager.h"
#include "ui_wxmanager.h"
#include "global.h"

WxManager::WxManager(QWidget *parent) : QMainWindow(parent), ui(new Ui::WxManager) {
    ui->setupUi(this);
}

WxManager::~WxManager() {
    delete ui;
}

void WxManager::moveEvent(QMoveEvent *event) {
    // 主要是为了解决微信存在透明层问题(窗口移动时透明层会留在原地)
    emit allMoveEvent();
    event->accept();
}

void WxManager::closeEvent(QCloseEvent *event) {
    Global::clearCtns();
    event->accept();
}

void WxManager::showEvent(QShowEvent *event) {
    // 暗黑模式
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(60, 60, 60));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Highlight, QColor(0, 120, 215));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    // this->setPalette(darkPalette);

    ui->navmain->add();
    event->accept();
}
