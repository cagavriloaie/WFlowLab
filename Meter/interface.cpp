/*
 *  Author: Constantin
 *  File:   interface.cpp
 */

#include <mutex>
#include <thread>
#include <unistd.h>

#include <QMessageBox>
#include <QSettings>
#include <QStringList>
#include <QtSerialBus/QModbusClient>
#include <QtSerialBus/QModbusRtuSerialServer>
#include <QtSerialPort/QSerialPort>

#include "interface.h"
#include "mainwindow.h"
#include "ui_interface.h"
#include "ui_mainwindow.h"

namespace
{
    MainWindow *mainwindow;
    unsigned positionTable = 0;
}  // namespace

std::mutex modbusLock;

Interface::Interface(QWidget *parent) : QDialog(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    mainwindow = dynamic_cast<MainWindow *>(parent);
    connect(ui->pbClose, &QPushButton::clicked, this,
            &Interface::onCloseClicked);
    connect(ui->pbSaveConfiguration, &QPushButton::clicked, this,
            &Interface::onSaveConfigurationClicked);
    connect(ui->pbTestConnection, &QPushButton::clicked, this,
            &Interface::onTestConfigurationClicked);
    connect(ui->pbRefreshSerialPort, &QPushButton::clicked, this,
            &Interface::onRefreshSerialPortClicked);
    connect(ui->cbSelectSerial, &QComboBox::currentIndexChanged, this,
            &Interface::onSelectSerialChanged);
    connect(ui->cbBaudRate, &QComboBox::currentIndexChanged, this,
            &Interface::onBaudRateChanged);
    connect(ui->cbSelectDataBits, &QComboBox::currentIndexChanged, this,
            &Interface::onSelectDataBitsnChanged);
    connect(ui->cbSelectParity, &QComboBox::currentIndexChanged, this,
            &Interface::onSelectParityChanged);
    connect(ui->cbSelectStopBits, &QComboBox::currentIndexChanged, this,
            &Interface::onSelectStopBitsChanged);
    ui->leSmallScale->setValidator(new QIntValidator(0, 255, this));
    ui->leLargeScale->setValidator(new QIntValidator(0, 100, this));
    ui->leTemperature->setValidator(new QIntValidator(0, 100, this));
    ui->leWaterMeters_1_5->setValidator(new QIntValidator(0, 100, this));
    ui->leWaterMeters_6_10->setValidator(new QIntValidator(0, 100, this));
    ui->leWaterMeters_11_15->setValidator(new QIntValidator(0, 100,
                                          this));
    ui->leWaterMeters_16_20->setValidator(new QIntValidator(0, 100,
                                          this));
    ui->cbSelectSerial->setStyleSheet(
        "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->cbBaudRate->setStyleSheet(
        "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->cbSelectDataBits->setStyleSheet(
        "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->cbSelectParity->setStyleSheet(
        "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->cbSelectStopBits->setStyleSheet(
        "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->cbNumberRetries->setStyleSheet(
        "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkLargeScale->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkSmallScale->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkTemperature->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkWaterMeters_1_5->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkWaterMeters_6_10->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkWaterMeters_11_15->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkWaterMeters_16_20->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkWaterMeter1->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkWaterMeter2->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->checkWaterMeter3->setStyleSheet(
        "QCheckButton { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ledStateTable[0] = ui->ledSmallScaleState;
    ledStateTable[1] = ui->ledLargeScaleState;
    ledStateTable[2] = ui->ledTemperatureState;
    ledStateTable[3] = ui->ledWaterMeter1State;
    ledStateTable[4] = ui->ledWaterMeter2State;
    ledStateTable[5] = ui->ledWaterMeter3State;
    ledStateTable[6] = ui->ledWaterMeters_1_5State;
    ledStateTable[7] = ui->ledWaterMeters_6_10State;
    ledStateTable[8] = ui->ledWaterMeters_11_15Status;
    ledStateTable[9] = ui->ledWaterMeters_16_20State;
    Translate();
}

Interface::~Interface()
{
    delete ui;
}

void Interface::Translate()
{
    // Set translated text for various widgets in the UI
    ui->groupBox->setTitle(tr("RS485 MODBUS"));
    ui->lbSelectSerial->setText(tr("Serial Port:"));
    ui->lbBaudRate->setText(tr("Baud Rate:"));
    ui->lbDataBits->setText(tr("Data Bits:"));
    ui->lbSelectParity->setText(tr("Parity:"));
    ui->lbSelectStopBits->setText(tr("Stop Bits:"));
    ui->lbTimeout->setText("Timeout [ms]:");
    ui->lbNumberOfRetries->setText("Numar reincercari:"); // "Retry Count:" in English
    ui->checkLargeScale->setText(tr("Large Scale"));
    ui->checkSmallScale->setText(tr("Small Scale"));
    ui->checkTemperature->setText(tr("Temperature"));
    ui->checkWaterMeters_1_5->setText(tr("Water Meters [1..5]"));
    ui->checkWaterMeters_6_10->setText(tr("Water Meters [6..10]"));
    ui->checkWaterMeters_11_15->setText(tr("Water Meters [11..15]"));
    ui->checkWaterMeters_16_20->setText(tr("Water Meters [16..20]"));
    ui->checkWaterMeter1->setText(tr("EM Flow Meter 1"));
    ui->checkWaterMeter2->setText(tr("EM Flow Meter 2"));
    ui->checkWaterMeter3->setText(tr("EM Flow Meter 3"));
    ui->groupBox_2->setTitle(tr("Device Addresses"));
    ui->pbClose->setText(tr("Close"));
    ui->pbSaveConfiguration->setText(tr("Save Configuration"));
    ui->pbTestConnection->setText(tr("Test Connection"));
    ui->pbRefreshSerialPort->setText(tr("Refresh Ports"));
}

void Interface::onCloseClicked()
{
    this->hide();
}

void Interface::onReadModbusReady()
{
    // Attempt to cast the sender() to a QModbusReply
    auto reply = qobject_cast<QModbusReply *>(sender());
    // Set the state of the LED to false (assuming ledStateTable is a vector of LEDState objects)
    ledStateTable[positionTable]->setState(false);
    // Check if the cast was successful
    if (!reply)
    {
        return; // If the cast fails, exit the function
    }
    // Check if there was no error in the Modbus reply
    if (reply->error() == QModbusDevice::NoError)
    {
        // If there is no error, set the state of the LED to true
        ledStateTable[positionTable]->setState(true);
    }
    // Increment the positionTable
    ++positionTable;
    // Schedule the reply object for deletion
    reply->deleteLater();
}


bool Interface::checkModbusAddress(qint16 address)
{
    std::lock_guard<std::mutex> lock(modbusLock);
    usleep(50000);
    QModbusRtuSerialClient *portModbus =
        static_cast<QModbusRtuSerialClient *>
        (mainwindow->selectedInfo.modbusDevice);
    ledStateTable[positionTable]->setState(false);
    if (QModbusReply *reply = portModbus->sendReadRequest(
                                  QModbusDataUnit(QModbusDataUnit::InputRegisters, 1, 2), address))
    {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, this,
                    &Interface::onReadModbusReady);
        }
        else
        {
            delete reply;  // Broadcast replies return immediately
        }
    }
    else
    {
        return false;
    }
    return true;
}

void Interface::onTestConfigurationClicked()
{
    if (!mainwindow->selectedInfo.modbusDevice)
    {
        return;
    }
    DisconnectSerialPort();
    for (auto iter = 0; iter < 10; ++iter)
    {
        ledStateTable[iter]->setState(false);
    }
    QModbusClient *&portModbus = mainwindow->selectedInfo.modbusDevice;
    ui->pbTestConnection->setDisabled(true);
    mainwindow->selectedInfo.serialPort = true;
    mainwindow->ui->rbInterface->setDisabled(false);
    portModbus = new QModbusRtuSerialClient(this);
    QString serialName = "COM" + entries.at(
                             ui->cbSelectSerial->currentIndex());
    portModbus->setConnectionParameter(
        QModbusDevice::SerialPortNameParameter,
        serialName);
    switch (ui->cbBaudRate->currentIndex())
    {
        case 0:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud1200);
            break;
        case 1:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud2400);
            break;
        case 2:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud4800);
            break;
        case 3:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
            break;
        case 4:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
            break;
        case 5:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud38400);
            break;
        case 6:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
            break;
        case 7:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter,
                QSerialPort::Baud115200);
            break;
        default:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
            break;
    }
    switch (ui->cbSelectDataBits->currentIndex())
    {
        case 0:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialDataBitsParameter, QSerialPort::Data5);
            break;
        case 1:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialDataBitsParameter, QSerialPort::Data6);
            break;
        case 2:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialDataBitsParameter, QSerialPort::Data7);
            break;
        case 3:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
            break;
        default:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
            break;
    }
    switch (ui->cbSelectParity->currentIndex())
    {
        case 0:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
            break;
        case 1:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
            break;
        case 2:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialParityParameter, QSerialPort::OddParity);
            break;
        case 3:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialParityParameter, QSerialPort::SpaceParity);
            break;
        case 4:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialParityParameter, QSerialPort::MarkParity);
            break;
        default:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
            break;
    }
    switch (ui->cbSelectParity->currentIndex())
    {
        case 0:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
            break;
        case 1:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialStopBitsParameter,
                QSerialPort::OneAndHalfStop);
            break;
        case 2:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialStopBitsParameter, QSerialPort::TwoStop);
            break;
        default:
            portModbus->setConnectionParameter(
                QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
            break;
    }
    int timeout = ui->leTimeout->text().toInt();
    portModbus->setTimeout(timeout);
    int retries = ui->cbNumberRetries->currentIndex();
    portModbus->setNumberOfRetries(retries);
    if (!isOpenModbusPort)
    {
        portModbus->disconnectDevice();
    }
    isOpenModbusPort = portModbus->connectDevice();
    if (isOpenModbusPort)
    {
        QMessageBox messageSerialInterface;
        messageSerialInterface.setWindowTitle(
            tr("Serial RTU MODBUS Interface Settings"));
        QString message(
            "Serial  RTU MODBUS interface %1 - (B:%2  D:%3  P:%4  S:%5) is "
            "available.");
        message = message.arg(ui->cbSelectSerial->currentText(),
                              ui->cbBaudRate->currentText(),
                              ui->cbSelectDataBits->currentText(),
                              ui->cbSelectParity->currentText(),
                              ui->cbSelectStopBits->currentText());
        messageSerialInterface.setText(message);
        messageSerialInterface.setStandardButtons(QMessageBox::Ok);
        messageSerialInterface.setWindowFlags(
            Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint |
            Qt::WindowCloseButtonHint);
        if (messageSerialInterface.exec() == QMessageBox::Ok)
        {
            messageSerialInterface.close();
        }
        positionTable = 0;
        checkModbusAddress(ui->leSmallScale->text().toUShort());
        checkModbusAddress(ui->leLargeScale->text().toUShort());
        checkModbusAddress(ui->leTemperature->text().toUShort());
        checkModbusAddress(ui->leWaterMeter1->text().toUShort());
        checkModbusAddress(ui->leWaterMeter2->text().toUShort());
        checkModbusAddress(ui->leWaterMeter3->text().toUShort());
        checkModbusAddress(ui->leWaterMeters_1_5->text().toUShort());
        checkModbusAddress(ui->leWaterMeters_6_10->text().toUShort());
        checkModbusAddress(ui->leWaterMeters_11_15->text().toUShort());
        checkModbusAddress(ui->leWaterMeters_16_20->text().toUShort());
    }
    else
    {
        QMessageBox messageSerialInterface;
        messageSerialInterface.setWindowTitle(
            tr("Serial Interface Settings"));
        QString message("Serial interface %1 is not available.");
        message = message.arg(ui->cbSelectSerial->currentText());
        messageSerialInterface.setText(message);
        messageSerialInterface.setStandardButtons(QMessageBox::Ok);
        messageSerialInterface.setWindowFlags(
            Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint |
            Qt::WindowCloseButtonHint);
        if (messageSerialInterface.exec() == QMessageBox::Ok)
        {
            messageSerialInterface.close();
        }
        mainwindow->ui->SerialLedIndicator->setState(false);
    }
    ui->pbTestConnection->setDisabled(false);
}

void Interface::onRefreshSerialPortClicked()
{
    // Disable the "Refresh Ports" button to prevent multiple clicks
    ui->pbRefreshSerialPort->setDisabled(true);
    // Clear the entries container
    entries.clear();
    // Get the list of serial ports from the main window
    const wchar_t *ports = mainwindow->serialPorts();
    wchar_t *pwc;
    pwc = std::wcstok(const_cast<wchar_t *>(ports), L"|");
    // Variables for processing serial port entries
    int even{0};
    QString portEntry;
    // Clear the items in the serial port combo box
    ui->cbSelectSerial->clear();
    // Process each serial port entry
    while (pwc != NULL)
    {
        even = (even + 1) % 2;
        if (even)
        {
            // Odd index, add to entries container
            portEntry = QString::fromWCharArray(pwc);
            entries.push_back(portEntry);
        }
        else
        {
            // Even index, combine with the previous entry and add to the combo box
            portEntry += "  " + QString::fromWCharArray(pwc);
            ui->cbSelectSerial->addItem(portEntry);
            portEntry.clear();
        }
        // Print the serial port entry (for debugging)
        wprintf(L"%ls\n", pwc);
        // Get the next serial port entry
        pwc = wcstok(NULL, L"|");
    }
    // Disconnect from the current serial port (assuming there is a function named DisconnectSerialPort)
    DisconnectSerialPort();
    // Re-enable the "Refresh Ports" button
    ui->pbRefreshSerialPort->setDisabled(false);
}

void Interface::onSaveConfigurationClicked()
{
    ui->pbSaveConfiguration->setDisabled(true);
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab",
                       QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("RS485");
    settings.setValue("selectedSerial",
                      ui->cbSelectSerial->currentIndex());
    settings.setValue("baudRate", ui->cbBaudRate->currentIndex());
    settings.setValue("dataBits", ui->cbSelectDataBits->currentIndex());
    settings.setValue("parity", ui->cbSelectParity->currentIndex());
    settings.setValue("stopBits", ui->cbSelectStopBits->currentIndex());
    settings.setValue("timeout", ui->leTimeout->text().toInt());
    settings.setValue("retriesNumber",
                      ui->cbNumberRetries->currentIndex());
    settings.setValue("smallScale", ui->checkSmallScale->isChecked());
    settings.setValue("largeScale", ui->checkLargeScale->isChecked());
    settings.setValue("temperature", ui->checkTemperature->isChecked());
    settings.setValue("waterMeters1_5",
                      ui->checkWaterMeters_1_5->isChecked());
    settings.setValue("waterMeters6_10",
                      ui->checkWaterMeters_6_10->isChecked());
    settings.setValue("waterMeters11_15",
                      ui->checkWaterMeters_11_15->isChecked());
    settings.setValue("waterMeters16_20",
                      ui->checkWaterMeters_16_20->isChecked());
    settings.setValue("waterMeter1", ui->checkWaterMeter1->isChecked());
    settings.setValue("waterMeter2", ui->checkWaterMeter2->isChecked());
    settings.setValue("waterMeter3", ui->checkWaterMeter3->isChecked());
    settings.setValue("smallScaleValue",
                      ui->leSmallScale->text().toInt());
    settings.setValue("largeScaleValue",
                      ui->leLargeScale->text().toInt());
    settings.setValue("temperatureValue",
                      ui->leTemperature->text().toInt());
    settings.setValue("waterMeters1_5Value",
                      ui->leWaterMeters_1_5->text().toInt());
    settings.setValue("waterMeters6_10Value",
                      ui->leWaterMeters_6_10->text().toInt());
    settings.setValue("waterMeters11_15Value",
                      ui->leWaterMeters_11_15->text().toInt());
    settings.setValue("waterMeters16_20Value",
                      ui->leWaterMeters_16_20->text().toInt());
    settings.setValue("waterMeter1Value",
                      ui->leWaterMeter1->text().toInt());
    settings.setValue("waterMeter2Value",
                      ui->leWaterMeter2->text().toInt());
    settings.setValue("waterMeter3Value",
                      ui->leWaterMeter3->text().toInt());
    settings.endGroup();
    settings.sync();
    ui->pbSaveConfiguration->setDisabled(false);
}

void Interface::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    QStringList baudRates{"1200",  "2400",  "4800",  "9600",
                          "19200", "38400", "57600", "115200"};
    ui->cbBaudRate->addItems(baudRates);
    QStringList dataBits{"5", "6", "7", "8"};
    ui->cbSelectDataBits->addItems(dataBits);
    QStringList parity{"None", "Even", "Odd", "Space", "Mark"};
    ui->cbSelectParity->addItems(parity);
    QStringList stopBits{"1", "2"};
    ui->cbSelectStopBits->addItems(stopBits);
    QStringList retriesNumber{"1", "2", "3", "4", "5"};
    ui->cbNumberRetries->addItems(retriesNumber);
    entries.clear();
    const wchar_t *ports = mainwindow->serialPorts();
    wchar_t *pwc;
    pwc = std::wcstok(const_cast<wchar_t *>(ports), L"|");
    int even{0};
    QString portEntry;
    while (pwc != NULL)
    {
        even = (even + 1) % 2;
        if (even)
        {
            portEntry = QString::fromWCharArray(pwc);
            entries.push_back(portEntry);
        }
        else
        {
            portEntry += "  " + QString::fromWCharArray(pwc);
            ui->cbSelectSerial->addItem(portEntry);
            portEntry.clear();
        }
        wprintf(L"%ls\n", pwc);
        pwc = wcstok(NULL, L"|");
    }
    if (!ui->cbSelectSerial->count())
    {
    }
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab",
                       QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("RS485");
    ui->cbSelectSerial->setCurrentIndex(
        settings.value("selectedSerial", 0).toInt());
    ui->cbBaudRate->setCurrentIndex(settings.value("baudRate",
                                    7).toInt());
    ui->cbSelectDataBits->setCurrentIndex(
        settings.value("dataBits", 1).toInt());
    ui->cbSelectParity->setCurrentIndex(settings.value("parity",
                                        2).toInt());
    ui->cbSelectStopBits->setCurrentIndex(
        settings.value("stopBits", 1).toInt());
    ui->leTimeout->setText((settings.value("timeout", 1000).toString()));
    ui->cbNumberRetries->setCurrentIndex(
        settings.value("retriesNumber", 0).toInt());
    ui->checkSmallScale->setChecked(settings.value("smallScale",
                                    1).toBool());
    ui->checkLargeScale->setChecked(settings.value("largeScale",
                                    1).toBool());
    ui->checkTemperature->setChecked(settings.value("temperature",
                                     1).toBool());
    ui->checkWaterMeters_1_5->setChecked(
        settings.value("waterMeters1_5", 1).toBool());
    ui->checkWaterMeters_6_10->setChecked(
        settings.value("waterMeters6_10", 1).toBool());
    ui->checkWaterMeters_11_15->setChecked(
        settings.value("waterMeters11_15", 1).toBool());
    ui->checkWaterMeters_16_20->setChecked(
        settings.value("waterMeters16_20", 1).toBool());
    ui->checkWaterMeter1->setChecked(settings.value("waterMeter1",
                                     1).toBool());
    ui->checkWaterMeter2->setChecked(settings.value("waterMeter2",
                                     1).toBool());
    ui->checkWaterMeter3->setChecked(settings.value("waterMeter3",
                                     1).toBool());
    ui->leSmallScale->setText(
        settings.value("smallScaleValue", 100).toString());
    ui->leLargeScale->setText(
        settings.value("largeScaleValue", 101).toString());
    ui->leTemperature->setText(
        settings.value("temperatureScaleValue", 102).toString());
    ui->leWaterMeters_1_5->setText(
        settings.value("waterMeters1_5Value", 103).toString());
    ui->leWaterMeters_6_10->setText(
        settings.value("waterMeters6_10Value", 104).toString());
    ui->leWaterMeters_11_15->setText(
        settings.value("waterMeters11_15Value", 103).toString());
    ui->leWaterMeters_16_20->setText(
        settings.value("waterMeters16_20Value", 104).toString());
    ui->leWaterMeter1->setText(
        settings.value("waterMeter1Value", 105).toString());
    ui->leWaterMeter2->setText(
        settings.value("waterMeter2Value", 106).toString());
    ui->leWaterMeter3->setText(
        settings.value("waterMeter3Value", 107).toString());
    settings.endGroup();
    settings.sync();
    ui->cbSelectSerial->setFocus();
}

void Interface::DisconnectSerialPort()
{
    // Update UI to indicate that the interface is not connected to the RS485 network
    mainwindow->ui->lbConnected->setText(
        tr("Not connected to RS485 network"));
    // Turn off the LED indicator for the serial connection
    mainwindow->ui->SerialLedIndicator->setState(false);
    // Get a reference to the ModbusClient pointer from the main window
    QModbusClient *&portModbus = mainwindow->selectedInfo.modbusDevice;
    // Check if the ModbusClient pointer is not null
    if (portModbus)
    {
        // Delete the ModbusClient object and set the pointer to null
        delete portModbus;
        portModbus = nullptr;
    }
    // Update the flag indicating whether the Modbus port is open
    isOpenModbusPort = false;
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
