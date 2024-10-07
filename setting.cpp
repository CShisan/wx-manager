#include "setting.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QIntValidator>

QSettings* Setting::settings = new QSettings("setting.ini", QSettings::IniFormat);
Setting* Setting::dialog = nullptr;

Setting* Setting::instance(QWidget *parent) {
    if (dialog) {
        dialog->initData();
    } else {
        dialog = new Setting(parent);
    }
    return dialog;
}

Setting::Setting(QWidget *parent) : QDialog(parent) {
    this->initData();

    // 创建表单布局
    QFormLayout *formLayout = new QFormLayout(this);

    // 启动数量
    QLineEdit *mopenNum = new QLineEdit(this);
    mopenNum->setText(QString::number(this->mopenNum));
    mopenNum->setValidator(new QIntValidator(1, 9, this));
    QObject::connect(mopenNum, &QLineEdit::textChanged, this, [this](const QString &text) {
        this->mopenNum = text.toInt();
    });
    formLayout->addRow("启动数量：", mopenNum);


    QDialogButtonBox *btnGroup = new QDialogButtonBox(this);
    btnGroup->addButton("保存", QDialogButtonBox::ButtonRole::AcceptRole);
    btnGroup->addButton("取消", QDialogButtonBox::ButtonRole::RejectRole);
    QObject::connect(btnGroup, &QDialogButtonBox::accepted, this, [this]() {
        this->write("mopenNum", this->mopenNum);
        this->accept();
    });
    QObject::connect(btnGroup, &QDialogButtonBox::rejected, this, [this]() {
        this->initData();
        this->reject();
    });
    formLayout->addRow(btnGroup);

    this->setLayout(formLayout);
    this->setWindowTitle("应用配置");
    qDebug() << "应用配置";
}

void Setting::initData() {
    this->mopenNum = this->read("mopenNum", 2);
}

template<typename T>
void Setting::write(QString property, T value) {
    Setting::settings->setValue(property, value);
}

template<typename T>
T Setting::read(QString property, T defaultVal) {
    return Setting::settings->value(property, defaultVal).template value<T>();
}


