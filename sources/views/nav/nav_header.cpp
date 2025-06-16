#include "nav_header.h"
#include "ui_nav_header.h"

NavHeader::NavHeader(QWidget * parent) : QFrame(parent), ui(new Ui::NavHeader) {
    ui->setupUi(this);
    this->initSelector();

    // this->setStyleSheet("QFrame { border-bottom: 2px solid grey; }");
    this->setStyleSheet("NavHeader { background: transparent; border-bottom: 1px solid #171717; }");
}

NavHeader::~NavHeader() {
    delete ui;
}

void NavHeader::initSelector() {
    this->selector = new NavSelector(ui->selector);
    selector->setStyle(ui->selector->style());
    selector->setSizePolicy(ui->selector->sizePolicy());
    selector->setGeometry(
      ui->selector->geometry().x(),
      ui->selector->geometry().y(),
      ui->selector->geometry().width(),
      ui->selector->geometry().height()
    );
    QHBoxLayout layout(ui->selector);
    layout.setContentsMargins(0, 0, 0, 0);
    layout.addWidget(selector);
    ui->selector->setLayout( & layout);
}
