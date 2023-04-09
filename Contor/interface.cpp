#include "interface.h"
#include "ui_interface.h"
#include "mainwindow.h"
#include <QStringList>
#include <QMessageBox>
#include <QSettings>
#include "ui_mainwindow.h"

namespace {
MainWindow *mainwindow;
}

Interface::Interface ( QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::Interface ) {
    ui->setupUi ( this );

    mainwindow = dynamic_cast<MainWindow *> ( parent );

    connect ( this, SIGNAL ( showEvent ), this, SLOT ( showEvent ) );
    connect ( ui->pbClose, &QPushButton::clicked, this, &Interface::onCloseClicked );
    connect ( ui->pbSave, &QPushButton::clicked, this, &Interface::onSaveClicked );

    connect ( ui->cbSelectSerial, &QComboBox::currentIndexChanged, this, &Interface::onSelectSerialChanged );
    connect ( ui->cbBaudRate, &QComboBox::currentIndexChanged, this, &Interface::onBaudRateChanged );
    connect ( ui->cbSelectDataBits, &QComboBox::currentIndexChanged, this, &Interface::onSelectDataBitsnChanged );
    connect ( ui->cbSelectParity, &QComboBox::currentIndexChanged, this, &Interface::onSelectParityChanged );
    connect ( ui->cbSelectStopBits, &QComboBox::currentIndexChanged, this, &Interface::onSelectStopBitsChanged );

    ui->cbSelectSerial->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbBaudRate->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbSelectDataBits->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbSelectParity->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbSelectStopBits->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
}

Interface::~Interface() {
    delete ui;
}

void Interface::Translate() {

}

void Interface::onCloseClicked() {
    this->hide();
}

void Interface::onSaveClicked() {
    mainwindow->selectedInfo.serialPort = true;
    ( ( Ui_MainWindow * ) mainwindow->ui )->rbInterface->setDisabled ( false );
    ui->pbSave->setDisabled ( true );


    QSettings settings ( "HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat );
    settings.beginGroup ( "RS485" );
    settings.setValue ( "baudRate", ui->cbBaudRate->currentIndex() );
    settings.setValue ( "dataBits", ui->cbSelectDataBits->currentIndex() );
    settings.setValue ( "parity", ui->cbSelectParity->currentIndex() );
    settings.setValue ( "stopBits", ui->cbSelectStopBits->currentIndex() );
    settings.setValue ( "selectedSerial", ui->cbSelectSerial->currentIndex() );
    settings.endGroup();
    settings.sync();
}

void Interface::showEvent ( QShowEvent *event ) {
    QWidget::showEvent ( event );

    QStringList baudRates {
        "300", "600", "1200", "1800", "2400",
        "4800", "7200", "9600", "14400", "19200",
        "28800", "38400", "57600", "76800", "115200",
        "230400"};
    ui->cbBaudRate->addItems ( baudRates );

    QStringList dataBits {
        "5",
        "6",
        "7",
        "8"
    };
    ui->cbSelectDataBits->addItems ( dataBits );

    QStringList parity {
        "None",
        "Odd",
        "Even"
    };
    ui->cbSelectParity->addItems ( parity );

    QStringList stopBits {
        "1",
        "2"
    };
    ui->cbSelectStopBits->addItems ( stopBits );

    wchar_t *ports = ( wchar_t * ) mainwindow->serialPorts();
    wchar_t *pwc;
    pwc = std::wcstok ( ports, L"|" );
    int even{0};
    QString portEntry;

    while ( pwc != NULL ) {
        even = ( even + 1 ) % 2;

        if ( even ) {
            portEntry = QString::fromWCharArray ( pwc );
        } else {
            portEntry += "  " + QString::fromWCharArray ( pwc );
            ui->cbSelectSerial->addItem ( portEntry );
            portEntry.clear();
        }

        wprintf ( L"%ls\n", pwc );
        pwc = wcstok ( NULL, L"|" );
    }

    if ( !ui->cbSelectSerial->count() ) {
        ui->pbSave->setDisabled ( true );
    }

    QSettings settings ( "HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat );
    settings.beginGroup ( "RS485" );
    ui->cbBaudRate->setCurrentIndex ( settings.value ( "baudRate", 7 ).toInt() );
    ui->cbSelectDataBits->setCurrentIndex ( settings.value ( "dataBits", 1 ).toInt() );
    ui->cbSelectParity->setCurrentIndex ( settings.value ( "parity", 2 ).toInt() );
    ui->cbSelectStopBits->setCurrentIndex ( settings.value ( "stopBits", 1 ).toInt() );
    ui->cbSelectSerial->setCurrentIndex ( settings.value ( "selectedSerial", 0 ).toInt() );
    settings.endGroup();
    settings.sync();

    ui->cbSelectSerial->setFocus();
}

void Interface::onSelectSerialChanged() {
    ui->pbSave->setDisabled ( false );
}

void Interface::onBaudRateChanged() {
    ui->pbSave->setDisabled ( false );
}

void Interface::onSelectDataBitsnChanged() {
    ui->pbSave->setDisabled ( false );
}

void Interface::onSelectParityChanged() {
    ui->pbSave->setDisabled ( false );
}

void Interface::onSelectStopBitsChanged() {
    ui->pbSave->setDisabled ( false );
}
