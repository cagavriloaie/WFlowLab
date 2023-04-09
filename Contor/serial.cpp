#include "serial.h"
#include "ui_serial.h"

Serial::Serial ( QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::Dialog ) {
    ui->setupUi ( this );
}

void Serial::Translate() {
}

void Serial::onCloseClicked() {
}

Serial::~Serial() {
    delete ui;
}
