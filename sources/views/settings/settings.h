#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "sources/config/property.h"

namespace Ui {
    class Settings;
}

class Settings : public QDialog {
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
    Property *properties;
    int mopenNum;

    void initData();
};

#endif // SETTINGS_H
