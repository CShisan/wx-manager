#include "selector.h"
#include "global.h"
#include <windows.h>
#include <QMessageBox>
#include <QIcon>

Selector::Selector(QWidget *parent) : QLabel{parent} {
}

void Selector::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Mouse Pressed";
        // 开始拖动操作，显示准星
        setCursor(Qt::CrossCursor);
    }
}

void Selector::mouseReleaseEvent(QMouseEvent *event) {
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

        CarrierSlot* current =  Global::curSlot();
        if (current != nullptr) {
            current->setHwnd(target);
            emit selected(current);
        }
        // 把目标窗口嵌入到容器窗口中
        qDebug() << "Target Window Found";
    }
}

bool Selector::isWechatWindow(HWND hwnd) {
    if (IsWindow(hwnd)) {
        const int classNameSize = 256;
        TCHAR classNameArray[classNameSize];
        if (GetClassName(hwnd, classNameArray, classNameSize) > 0) {
            QString className = QString::fromWCharArray(classNameArray);
            return className.contains("wechat", Qt::CaseInsensitive);
        }
    }
    return false;
}
