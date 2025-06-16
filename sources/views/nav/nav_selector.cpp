#include "nav_selector.h"
#include "ui_nav_selector.h"

#include <QIcon>
#include <QMessageBox>

NavSelector::NavSelector(QWidget *parent) : QLabel(parent) , ui(new Ui::NavSelector) {
    ui->setupUi(this);
}

NavSelector::~NavSelector() {
    delete ui;
}


void NavSelector::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Mouse Pressed";
        // 开始拖动操作，显示准星
        setCursor(Qt::CrossCursor);
    }
}

void NavSelector::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Mouse Released";
        // 停止拖动操作，恢复正常鼠标样式
        setCursor(Qt::ArrowCursor);

        // 获取目标窗口句柄
        QPointF globalPos = event->globalPosition();
        QPoint point = globalPos.toPoint();
        HWND target = WindowFromPoint(POINT{point.x(), point.y()});
        if (!target || !isWechatWindow(target)) {
            qDebug() << "未找到微信窗口";
            QMessageBox message(
                QMessageBox::NoIcon, "警告", "未找到微信窗口",
                QMessageBox::StandardButton::NoButton, this->parentWidget()
            );
            message.setWindowIcon(QIcon(QPixmap(":/icons/bubbles.svg")));
            message.addButton("确认", QMessageBox::AcceptRole);
            message.exec();
            return;
        }

        emit this->signal_selected(target);
        qDebug() << "Target Window Found";
    }
}

bool NavSelector::isWechatWindow(HWND hwnd) {
    if (IsWindow(hwnd)) {
        const int classNameSize = 256;
        TCHAR classNameArray[classNameSize];
        if (GetWindowText(hwnd, classNameArray, classNameSize) > 0) {
            QString title = QString::fromWCharArray(classNameArray);
            return title.compare("微信") == 0;
        }
    }
    return false;
}
