#include "interface.h"
#include "ui_interface.h"
#include "mainwindow.h"
#include <QStringList>
#include <QMessageBox>
#include <QSettings>
#include "ui_mainwindow.h"

namespace
{
MainWindow *mainwindow;
}

Interface::Interface ( QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::Interface )
    {
    ui->setupUi ( this );

    mainwindow = dynamic_cast<MainWindow *> ( parent );

    connect ( this, SIGNAL ( showEvent ), this, SLOT ( showEvent ) );
    connect ( ui->pbClose, &QPushButton::clicked, this, &Interface::onCloseClicked );
    connect ( ui->pbConnect, &QPushButton::clicked, this, &Interface::onSaveClicked );
    connect ( ui->pbRefresh, &QPushButton::clicked, this, &Interface::onRefreshClicked );

    connect ( ui->cbSelectSerial, &QComboBox::currentIndexChanged, this, &Interface::onSelectSerialChanged );
    connect ( ui->cbBaudRate, &QComboBox::currentIndexChanged, this, &Interface::onBaudRateChanged );
    connect ( ui->cbSelectDataBits, &QComboBox::currentIndexChanged, this, &Interface::onSelectDataBitsnChanged );
    connect ( ui->cbSelectParity, &QComboBox::currentIndexChanged, this, &Interface::onSelectParityChanged );
    connect ( ui->cbSelectStopBits, &QComboBox::currentIndexChanged, this, &Interface::onSelectStopBitsChanged );

    ui->leSmallScale->setValidator ( new QIntValidator ( 0, 255, this ) );
    ui->leLargeScale->setValidator ( new QIntValidator ( 0, 100, this ) );
    ui->leTemperature->setValidator ( new QIntValidator ( 0, 100, this ) );
    ui->leWaterMeters_1_10->setValidator ( new QIntValidator ( 0, 100, this ) );
    ui->leWaterMeters_11_20->setValidator ( new QIntValidator ( 0, 100, this ) );

    ui->cbSelectSerial->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbBaudRate->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbSelectDataBits->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbSelectParity->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbSelectStopBits->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );

    ui->checkLargeScale->setStyleSheet ( "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->checkSmallScale->setStyleSheet ( "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->checkTemperature->setStyleSheet ( "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->checkWaterMeters_1_10->setStyleSheet ( "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->checkWaterMeters_11_20->setStyleSheet ( "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );

    Translate();
    }

Interface::~Interface()
    {
    delete ui;
    }

void Interface::Translate()
    {
    ui->groupBox->setTitle ( tr ( "RS485" ) );
    ui->lbSelectSerial->setText ( tr ( "Serial port" ) );
    ui->lbBaudRate->setText ( tr ( "Baud Rate" ) );
    ui->lbDataBits->setText ( tr ( "Data Bits" ) );
    ui->lbSelectParity->setText ( tr ( "Parity" ) );
    ui->lbSelectStopBits->setText ( tr ( "Stop Bits" ) );
    ui->pbClose->setText ( tr ( "Close" ) );
    ui->pbConnect->setText ( tr ( "Connect" ) );
    ui->pbRefresh->setText ( tr ( "Refresh Serial Ports" ) );

    ui->checkLargeScale->setText ( tr ( "Large Scale" ) );
    ui->checkSmallScale->setText ( tr ( "Small Scale:" ) );
    ui->checkTemperature->setText ( tr ( "Temperature:" ) );
    ui->checkWaterMeters_1_10->setText ( tr ( "Water Meters [1..10]:" ) );
    ui->checkWaterMeters_11_20->setText ( tr ( "Water Meters [11..20]:" ) );
    ui->groupBox_2->setTitle ( tr ( "Device Addresses" ) );
    }

void Interface::onCloseClicked()
    {
    this->hide();
    }

void Interface::onSaveClicked()
    {
    QSerialPort *&port = mainwindow->selectedInfo.serialPortSelected;

    if ( isOpenPort )
        {
        DisconnectSerialPort();
        return;
        }

    mainwindow->selectedInfo.serialPort = true;

    ( ( Ui_MainWindow * ) mainwindow->ui )->rbInterface->setDisabled ( false );

    QString serialName = "COM" + entries.at ( ui->cbSelectSerial->currentIndex() );
    port = new QSerialPort ( serialName );

    switch ( ui->cbBaudRate->currentIndex() )
        {
        case 0:
            port->setBaudRate ( QSerialPort::Baud1200 );
            break;

        case 1:
            port->setBaudRate ( QSerialPort::Baud2400 );
            break;

        case 2:
            port->setBaudRate ( QSerialPort::Baud4800 );
            break;

        case 3:
            port->setBaudRate ( QSerialPort::Baud9600 );
            break;

        case 4:
            port->setBaudRate ( QSerialPort::Baud19200 );
            break;

        case 5:
            port->setBaudRate ( QSerialPort::Baud38400 );
            break;

        case 6:
            port->setBaudRate ( QSerialPort::Baud57600 );
            break;

        case 7:
            port->setBaudRate ( QSerialPort::Baud115200 );
            break;

        default:
            port->setBaudRate ( QSerialPort::Baud1200 );
            break;
        }

    switch ( ui->cbSelectDataBits->currentIndex() )
        {
        case 0:
            port->setDataBits ( QSerialPort::Data5 );
            break;

        case 1:
            port->setDataBits ( QSerialPort::Data6 );
            break;

        case 2:
            port->setDataBits ( QSerialPort::Data7 );
            break;

        case 3:
            port->setDataBits ( QSerialPort::Data8 );
            break;

        default:
            port->setDataBits ( QSerialPort::Data8 );
            break;
        }

    switch ( ui->cbSelectParity->currentIndex() )
        {
        case 0:
            port->setParity ( QSerialPort::NoParity );
            break;

        case 1:
            port->setParity ( QSerialPort::EvenParity );
            break;

        case 2:
            port->setParity ( QSerialPort::OddParity );
            break;

        case 3:
            port->setParity ( QSerialPort::SpaceParity );
            break;

        case 4:
            port->setParity ( QSerialPort::MarkParity );
            break;

        default:
            port->setParity ( QSerialPort::NoParity );
            break;
        }

    switch ( ui->cbSelectParity->currentIndex() )
        {
        case 0:
            port->setStopBits ( QSerialPort::OneStop );
            break;

        case 1:
            port->setStopBits ( QSerialPort::OneAndHalfStop );
            break;

        case 2:
            port->setStopBits ( QSerialPort::TwoStop );
            break;

        default:
            port->setStopBits ( QSerialPort::OneStop );
            break;
        }

    port->setFlowControl ( QSerialPort::NoFlowControl );



    if ( !isOpenPort )
        {
        port->close();
        }

    isOpenPort = port->open ( QIODevice::ReadWrite );

    if ( isOpenPort )
        {
        QMessageBox messageSerialInterface;
        messageSerialInterface.setWindowTitle ( tr ( "Serial Interface Settings" ) );
        QString message ( "Serial interface %1 - (B:%2  D:%3  P:%4  S:%5) is available." );
        message = message
                  .arg ( ui->cbSelectSerial->currentText() )
                  .arg ( ui->cbBaudRate->currentText() )
                  .arg ( ui->cbSelectDataBits->currentText() )
                  .arg ( ui->cbSelectParity->currentText() )
                  .arg ( ui->cbSelectStopBits->currentText() );
        messageSerialInterface.setText ( message );
        messageSerialInterface.setStandardButtons ( QMessageBox::Ok );
        messageSerialInterface.setWindowFlags ( Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

        if ( messageSerialInterface.exec() == QMessageBox::Ok )
            {
            messageSerialInterface.close();
            }

        mainwindow->ui->SerialLedIndicator->setState ( true );
        QString messageMain ( "%1 (B:%2  D:%3  P:%4  S:%5)" );
        messageMain = messageMain
                      .arg ( ui->cbSelectSerial->currentText() )
                      .arg ( ui->cbBaudRate->currentText() )
                      .arg ( ui->cbSelectDataBits->currentText() )
                      .arg ( ui->cbSelectParity->currentText() )
                      .arg ( ui->cbSelectStopBits->currentText() );
        mainwindow->ui->lbConnected->setText ( messageMain );
        ui->pbConnect->setText ( tr ( "Disconnect" ) );
        }
    else
        {
        QMessageBox messageSerialInterface;
        messageSerialInterface.setWindowTitle ( tr ( "Serial Interface Settings" ) );
        QString message ( "Serial interface %1 is not available." );
        message = message.arg ( ui->cbSelectSerial->currentText() );
        messageSerialInterface.setText ( message );
        messageSerialInterface.setStandardButtons ( QMessageBox::Ok );
        messageSerialInterface.setWindowFlags ( Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

        if ( messageSerialInterface.exec() == QMessageBox::Ok )
            {
            messageSerialInterface.close();
            }

        mainwindow->ui->SerialLedIndicator->setState ( false );
        }

    QSettings settings ( "HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat );
    settings.beginGroup ( "RS485" );

    settings.setValue ( "baudRate", ui->cbBaudRate->currentIndex() );
    settings.setValue ( "dataBits", ui->cbSelectDataBits->currentIndex() );
    settings.setValue ( "parity", ui->cbSelectParity->currentIndex() );
    settings.setValue ( "stopBits", ui->cbSelectStopBits->currentIndex() );
    settings.setValue ( "selectedSerial", ui->cbSelectSerial->currentIndex() );

    settings.setValue ( "smallScale", ui->checkSmallScale->isChecked() );
    settings.setValue ( "largeScale", ui->checkLargeScale->isChecked() );
    settings.setValue ( "temperature", ui->checkTemperature->isChecked() );
    settings.setValue ( "waterMeters1_10", ui->checkWaterMeters_1_10->isChecked() );
    settings.setValue ( "waterMeters11_20", ui->checkWaterMeters_11_20->isChecked() );

    settings.setValue ( "smallScaleValue", ui->leSmallScale->text().toInt() );
    settings.setValue ( "largeScaleValue", ui->leLargeScale->text().toInt() );
    settings.setValue ( "temperatureValue", ui->leTemperature->text().toInt() );
    settings.setValue ( "waterMeters1_10Value", ui->leWaterMeters_1_10->text().toInt() );
    settings.setValue ( "waterMeters11_20Value", ui->leWaterMeters_11_20->text().toInt() );

    settings.endGroup();
    settings.sync();
    }

void Interface::onRefreshClicked()
    {
    entries.clear();
    wchar_t *ports = ( wchar_t * ) mainwindow->serialPorts();
    wchar_t *pwc;
    pwc = std::wcstok ( ports, L"|" );
    int even{0};
    QString portEntry;

    ui->cbSelectSerial->clear();

    while ( pwc != NULL )
        {
        even = ( even + 1 ) % 2;

        if ( even )
            {
            portEntry = QString::fromWCharArray ( pwc );
            entries.push_back ( portEntry );
            }
        else
            {
            portEntry += "  " + QString::fromWCharArray ( pwc );
            ui->cbSelectSerial->addItem ( portEntry );
            portEntry.clear();
            }

        wprintf ( L"%ls\n", pwc );
        pwc = wcstok ( NULL, L"|" );
        }
    }

void Interface::showEvent ( QShowEvent *event )
    {
    QWidget::showEvent ( event );

    QStringList baudRates
        {
        "1200",  "2400", "4800",  "9600",
        "19200", "38400", "57600", "115200"
        };
    ui->cbBaudRate->addItems ( baudRates );

    QStringList dataBits
        {
        "5",
        "6",
        "7",
        "8"
        };
    ui->cbSelectDataBits->addItems ( dataBits );

    QStringList parity
        {
        "None",
        "Even",
        "Odd",
        "Space",
        "Mark"
        };
    ui->cbSelectParity->addItems ( parity );

    QStringList stopBits
        {
        "1",
        "2"
        };
    ui->cbSelectStopBits->addItems ( stopBits );

    entries.clear();
    wchar_t *ports = ( wchar_t * ) mainwindow->serialPorts();
    wchar_t *pwc;
    pwc = std::wcstok ( ports, L"|" );
    int even{0};
    QString portEntry;

    while ( pwc != NULL )
        {
        even = ( even + 1 ) % 2;

        if ( even )
            {
            portEntry = QString::fromWCharArray ( pwc );
            entries.push_back ( portEntry );
            }
        else
            {
            portEntry += "  " + QString::fromWCharArray ( pwc );
            ui->cbSelectSerial->addItem ( portEntry );
            portEntry.clear();
            }

        wprintf ( L"%ls\n", pwc );
        pwc = wcstok ( NULL, L"|" );
        }

    if ( !ui->cbSelectSerial->count() )
        {

        }

    QSettings settings ( "HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat );
    settings.beginGroup ( "RS485" );
    ui->cbBaudRate->setCurrentIndex ( settings.value ( "baudRate", 7 ).toInt() );
    ui->cbSelectDataBits->setCurrentIndex ( settings.value ( "dataBits", 1 ).toInt() );
    ui->cbSelectParity->setCurrentIndex ( settings.value ( "parity", 2 ).toInt() );
    ui->cbSelectStopBits->setCurrentIndex ( settings.value ( "stopBits", 1 ).toInt() );
    ui->cbSelectSerial->setCurrentIndex ( settings.value ( "selectedSerial", 0 ).toInt() );

    ui->checkSmallScale->setChecked ( settings.value ( "smallScale", 1 ).toInt() );
    ui->checkLargeScale->setChecked ( settings.value ( "largeScale", 1 ).toInt() );
    ui->checkTemperature->setChecked ( settings.value ( "temperatureScale", 1 ).toInt() );
    ui->checkWaterMeters_1_10->setChecked ( settings.value ( "checkWaterMeters_1_10", 1 ).toInt() );
    ui->checkWaterMeters_11_20->setChecked ( settings.value ( "checkWaterMeters_11_20", 1 ).toInt() );

    ui->leSmallScale->setText ( settings.value ( "smallScaleValue", 100 ).toString() );
    ui->leLargeScale->setText ( settings.value ( "largeScaleValue", 101 ).toString() );
    ui->leTemperature->setText ( settings.value ( "temperatureScaleValue", 102 ).toString() );
    ui->leWaterMeters_1_10->setText ( settings.value ( "checkWaterMeters_1_10", 103 ).toString() );
    ui->leWaterMeters_11_20->setText ( settings.value ( "checkWaterMeters_11_20", 104 ).toString() );

    settings.endGroup();
    settings.sync();

    ui->cbSelectSerial->setFocus();
    }

void Interface::DisconnectSerialPort()
    {
    mainwindow->ui->lbConnected->setText ( tr ( "Not connected to RS485 network" ) );
    mainwindow->ui->SerialLedIndicator->setState ( false );
    QSerialPort *&port = mainwindow->selectedInfo.serialPortSelected;

    if ( port )
        {
        delete port;
        port = nullptr;
        }

    isOpenPort = false;
    ui->pbConnect->setText ( tr ( "Connect" ) );
    }

void Interface::onSelectSerialChanged()
    {
    DisconnectSerialPort();
    }

void Interface::onBaudRateChanged()
    {
    DisconnectSerialPort();
    }

void Interface::onSelectDataBitsnChanged()
    {
    DisconnectSerialPort();
    }

void Interface::onSelectParityChanged()
    {
    DisconnectSerialPort();
    }

void Interface::onSelectStopBitsChanged()
    {
    DisconnectSerialPort();
    }

