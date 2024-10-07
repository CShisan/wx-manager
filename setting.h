#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QSettings>

class Setting : public QDialog {
public:
    static Setting* instance(QWidget *parent);
    template<typename T>
    static void write(QString property, T value);
    template<typename T>
    static T read(QString property, T defaultVal);

private:
    explicit Setting(QWidget *parent = nullptr);
    static QSettings* settings;
    static Setting* dialog;
    void initData();
    int mopenNum;
};

#endif // SETTING_H
