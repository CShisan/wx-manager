#include "settings.h"
#include "ui_settings.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QIntValidator>

Settings::Settings(QWidget *parent) : QDialog(parent) , ui(new Ui::Settings) {
    this->properties = Property::instance();
    ui->setupUi(this);
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

    // 决策按钮
    QDialogButtonBox *decisionBox = new QDialogButtonBox(this);
    decisionBox->addButton("保存", QDialogButtonBox::ButtonRole::AcceptRole);
    decisionBox->addButton("取消", QDialogButtonBox::ButtonRole::RejectRole);
    QObject::connect(decisionBox, &QDialogButtonBox::accepted, this, [this]() {
        this->properties->write(Property::Names::MOPEN_NUM, this->mopenNum);
        this->accept();
    });
    QObject::connect(decisionBox, &QDialogButtonBox::rejected, this, [this]() {
        this->initData();
        this->reject();
    });
    formLayout->addRow(decisionBox);

    this->setLayout(formLayout);
    this->setWindowTitle("应用配置");
    this->adjustSize();
    qDebug() << "应用配置";
}

Settings::~Settings() {
    delete ui;
}

void Settings::initData() {
    this->mopenNum = this->properties->read(Property::Names::MOPEN_NUM, 2);
}
