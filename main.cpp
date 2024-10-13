#include "sources/wxm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Wxm w;
    w.show();
    return a.exec();
}
