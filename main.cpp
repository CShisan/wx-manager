#include "wxmanager.h"

#include <QApplication>
#include <QSettings>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    WxManager w;
    w.show();
    return a.exec();
}
