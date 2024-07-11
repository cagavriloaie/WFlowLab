/**
 * \file interface.cpp
 * \brief Implementation file for Interface dialog functionality.
 *
 * This file contains the implementation of the Interface class, which provides
 * functionality for configuring and interacting with a user interface dialog.
 *
 * \author Constantin
 * \date Insert date
 */

#include <mutex>                    // Include for std::mutex
#include <unistd.h>                 // POSIX API for various functionalities

#include <QMessageBox>              // Qt class for displaying message boxes
#include <QSettings>                // Qt class for persistent application settings
#include <QStringList>              // Qt class for manipulating string lists
#include <QtSerialBus/QModbusClient>        // Qt class for Modbus client functionality
#include <QtSerialBus/QModbusRtuSerialServer> // Qt class for Modbus RTU serial server
#include <QtSerialPort/QSerialPort> // Qt class for serial port communication

#include "interface.h"              // Include header for Interface dialog
#include "mainwindow.h"             // Include header for MainWindow
#include "ui_interface.h"           // Generated UI header file for Interface dialog
#include "ui_mainwindow.h"          // Generated UI header file for MainWindow

namespace
{
    MainWindow *mainwindow;
    unsigned positionTable = 0;
}  // namespace

std::mutex modbusLock;

/**
 * \file interface.cpp
 * \brief Implementation of the Interface class.
 */

#include "interface.h"

/**
 * \brief Constructs the Interface dialog.
 *
 * This constructor initializes the user interface, sets up signal-slot connections,
 * validators for line edits, style sheets for various widgets, and translates text
 * for internationalization.
 *
 * \param parent The parent widget, usually a MainWindow.
 */
Interface::Interface(QWidget *parent) : QDialog(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);  // Setup the user interface defined in Ui::Interface
    mainwindow = dynamic_cast<MainWindow *>(parent);  // Cast parent to MainWindow*

    ports = QSerialPortInfo::availablePorts();

    connect(ui->cbSelectSerial_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onSelectSerialChanged);
    connect(ui->cbBaudRate_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onBaudRateChanged);
    connect(ui->cbSelectDataBits_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onSelectDataBitsChanged);
    connect(ui->cbSelectParity_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onSelectParityChanged);
    connect(ui->cbSelectStopBits_1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onSelectStopBitsChanged);

    connect(ui->cbSelectSerial_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onSelectSerialChanged);
    connect(ui->cbBaudRate_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onBaudRateChanged);
    connect(ui->cbSelectDataBits_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onSelectDataBitsChanged);
    connect(ui->cbSelectParity_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onSelectParityChanged);
    connect(ui->cbSelectStopBits_2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Interface::onSelectStopBitsChanged);

    // Connect signals to slots
    connect(ui->pbClose, &QPushButton::clicked, this, &Interface::onCloseClicked);
    connect(ui->pbSaveConfiguration, &QPushButton::clicked, this, &Interface::onSaveConfigurationClicked);
    connect(ui->pbTestConnection, &QPushButton::clicked, this, &Interface::onTestConfigurationClicked);
    connect(ui->pbRefreshSerialPort, &QPushButton::clicked, this, &Interface::onRefreshSerialPortClicked);

    ui->cbSelectSerial_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->cbSelectSerial_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mainwindow->modbusDevice_1 =  new QModbusRtuSerialClient(this);
    mainwindow->modbusDevice_2 =  new QModbusRtuSerialClient(this);

    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("RS_485_422");

    // Set UI components to the saved settings
    ui->cbSelectSerial_1->setCurrentIndex(settings.value("selectedSerial_1", 0).toInt());
    ui->cbBaudRate_1->setCurrentIndex(settings.value("baudRate_1", 7).toInt());
    ui->cbSelectDataBits_1->setCurrentIndex(settings.value("dataBits_1", 1).toInt());
    ui->cbSelectParity_1->setCurrentIndex(settings.value("parity_1", 2).toInt());
    ui->cbSelectStopBits_1->setCurrentIndex(settings.value("stopBits_1", 1).toInt());
    ui->leTimeout_1->setText(settings.value("timeout_1", 1000).toString());
    ui->cbNumberRetries_1->setCurrentIndex(settings.value("retriesNumber_1", 0).toInt());

    ui->cbSelectSerial_2->setCurrentIndex(settings.value("selectedSerial_2", 0).toInt());
    ui->cbBaudRate_2->setCurrentIndex(settings.value("baudRate_2", 7).toInt());
    ui->cbSelectDataBits_2->setCurrentIndex(settings.value("dataBits_2", 1).toInt());
    ui->cbSelectParity_2->setCurrentIndex(settings.value("parity_2", 2).toInt());
    ui->cbSelectStopBits_2->setCurrentIndex(settings.value("stopBits_2", 1).toInt());
    ui->leTimeout_2->setText(settings.value("timeout_2", 1000).toString());
    ui->cbNumberRetries_2->setCurrentIndex(settings.value("retriesNumber_2", 0).toInt());

    settings.endGroup();
    settings.sync();

    Translate();
}

/**
 * \brief Destructor for the Interface class.
 *
 * This destructor deallocates resources associated with the Interface object.
 * It specifically deletes the user interface object (ui), which manages the
 * graphical components of the interface.
 */
Interface::~Interface()
{
    delete ui; // Deletes the user interface object
}


/**
 * \brief Translates the UI text to the current language.
 *
 * This function sets the translated text for various widgets in the UI
 * based on the current language settings.
 */
void Interface::Translate()
{
    // Set translated text for various widgets in the UI
    ui->groupBox_1->setTitle(tr("RS-485/422 Serial Interface MODBUS"));
    ui->lbSelectSerial_1->setText(tr("Serial Port:"));
    ui->lbBaudRate_1->setText(tr("Baud Rate:"));
    ui->lbDataBits_1->setText(tr("Data Bits:"));
    ui->lbSelectParity_1->setText(tr("Parity:"));
    ui->lbSelectStopBits_1->setText(tr("Stop Bits:"));
    ui->lbTimeout_1->setText(tr("Timeout [ms]:"));
    ui->lbNumberOfRetries_1->setText(tr("Number of Retries:"));

    ui->groupBox_2->setTitle(tr("RS-485/422 Serial Interface MODBUS"));
    ui->lbSelectSerial_2->setText(tr("Serial Port:"));
    ui->lbBaudRate_2->setText(tr("Baud Rate:"));
    ui->lbDataBits_2->setText(tr("Data Bits:"));
    ui->lbSelectParity_2->setText(tr("Parity:"));
    ui->lbSelectStopBits_2->setText(tr("Stop Bits:"));
    ui->lbTimeout_2->setText(tr("Timeout [ms]:"));
    ui->lbNumberOfRetries_2->setText(tr("Number of Retries:"));

    ui->pbClose->setText(tr("Close"));
    ui->pbSaveConfiguration->setText(tr("Save Configuration"));
    ui->pbTestConnection->setText(tr("Test Connection"));
    ui->pbRefreshSerialPort->setText(tr("Refresh Ports"));
}

/**
 * \brief Slot to handle the Close button click event.
 *
 * This function hides the current interface window when the Close button is clicked.
 */
void Interface::onCloseClicked()
{
    // Hide the current interface window
    this->hide();
}

/**
 * \brief Slot to handle Modbus read request completion.
 *
 * This function is called when a Modbus read request is completed.
 * It updates the LED state based on the result of the read request.
 */
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

/**
 * \brief Checks the Modbus address.
 *
 * This function checks if a given Modbus address is valid by sending a read request
 * to the Modbus device. It uses a lock to ensure thread safety and updates the LED state.
 *
 * \param address The Modbus address to check.
 * \return true if the request was successfully sent, false otherwise.
 */
bool Interface::checkModbusAddress(qint16 address)
{
    std::lock_guard<std::mutex> lock(modbusLock);
    usleep(50000);
    QModbusRtuSerialClient *portModbus =
        static_cast<QModbusRtuSerialClient *>
        (mainwindow->modbusDevice_1);
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

/**
 * \brief Slot function to handle the Test Configuration button click event.
 *
 * This function tests the Modbus connection by setting the Modbus device parameters
 * and attempting to connect. It updates the UI elements and displays the result
 * of the connection attempt.
 */
void Interface::onTestConfigurationClicked()
{
    // Check if either modbusDevice_1 or modbusDevice_2 is not set
    if (!mainwindow->modbusDevice_1 || !mainwindow->modbusDevice_2)
    {
        return; // Exit if either device is not set
    }

    DisconnectSerialPort(); // Disconnect any existing serial port connections

    // Get references to modbusDevice_1 and modbusDevice_2
    QModbusClient *&portModbus_1 = mainwindow->modbusDevice_1;
    QModbusClient *&portModbus_2 = mainwindow->modbusDevice_2;

    // Disable the "Test Connection" button while configuring
    ui->pbTestConnection->setDisabled(true);

    // Set flags for selected serial ports in the main window
    mainwindow->selectedInfo.serialPort_1 = true;
    mainwindow->selectedInfo.serialPort_2 = true;

    // Enable interface radio button and disable manual radio button
    mainwindow->ui->rbInterface->setDisabled(false);
    mainwindow->ui->rbManual->setDisabled(true);

    // Create new instances of QModbusRtuSerialClient for modbusDevice_1 and modbusDevice_2
    portModbus_1 = new QModbusRtuSerialClient(this);
    portModbus_2 = new QModbusRtuSerialClient(this);

    // Configure serial port parameters for modbusDevice_1
    QString serialName_1 = "COM" + entries.at(ui->cbSelectSerial_1->currentIndex());
    portModbus_1->setConnectionParameter(QModbusDevice::SerialPortNameParameter, serialName_1);

    // Set baud rate for modbusDevice_1 based on user selection
    switch (ui->cbBaudRate_1->currentIndex())
    {
    case 0:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud1200);
        break;
    case 1:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud2400);
        break;
    case 2:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud4800);
        break;
    case 3:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    case 4:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
        break;
    case 5:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud38400);
        break;
    case 6:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
        break;
    case 7:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
        break;
    default:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    }

    // Set data bits for modbusDevice_1 based on user selection
    switch (ui->cbSelectDataBits_1->currentIndex())
    {
    case 0:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data5);
        break;
    case 1:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data6);
        break;
    case 2:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data7);
        break;
    case 3:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    default:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    }

    // Set parity for modbusDevice_1 based on user selection
    switch (ui->cbSelectParity_1->currentIndex())
    {
    case 0:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    case 1:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
        break;
    case 2:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::OddParity);
        break;
    case 3:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::SpaceParity);
        break;
    case 4:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::MarkParity);
        break;
    default:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    }

    // Set stop bits for modbusDevice_1 based on user selection
    switch (ui->cbSelectStopBits_1->currentIndex())
    {
    case 0:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    case 1:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneAndHalfStop);
        break;
    case 2:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::TwoStop);
        break;
    default:
        portModbus_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    }

    // Set timeout for modbusDevice_1 based on user input
    int timeout_1 = ui->leTimeout_1->text().toInt();
    portModbus_1->setTimeout(timeout_1);

    // Set number of retries for modbusDevice_1 based on user selection
    int retries_1 = ui->cbNumberRetries_1->currentIndex();
    portModbus_1->setNumberOfRetries(retries_1);

    // Configure serial port parameters for modbusDevice_2
    QString serialName_2 = "COM" + entries.at(ui->cbSelectSerial_2->currentIndex());
    portModbus_2->setConnectionParameter(QModbusDevice::SerialPortNameParameter, serialName_2);

    // Set baud rate for modbusDevice_2 based on user selection
    switch (ui->cbBaudRate_2->currentIndex())
    {
    case 0:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud1200);
        break;
    case 1:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud2400);
        break;
    case 2:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud4800);
        break;
    case 3:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    case 4:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
        break;
    case 5:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud38400);
        break;
    case 6:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
        break;
    case 7:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
        break;
    default:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    }

    // Set data bits for modbusDevice_2 based on user selection
    switch (ui->cbSelectDataBits_2->currentIndex())
    {
    case 0:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data5);
        break;
    case 1:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data6);
        break;
    case 2:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data7);
        break;
    case 3:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    default:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    }

    // Set parity for modbusDevice_2 based on user selection
    switch (ui->cbSelectParity_2->currentIndex())
    {
    case 0:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    case 1:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
        break;
    case 2:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::OddParity);
        break;
    case 3:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::SpaceParity);
        break;
    case 4:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::MarkParity);
        break;
    default:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    }

    // Set stop bits for modbusDevice_2 based on user selection
    switch (ui->cbSelectStopBits_2->currentIndex())
    {
    case 0:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    case 1:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneAndHalfStop);
        break;
    case 2:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::TwoStop);
        break;
    default:
        portModbus_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    }

    // Set timeout for modbusDevice_2 based on user input
    int timeout_2 = ui->leTimeout_2->text().toInt();
    portModbus_2->setTimeout(timeout_2);

    // Set number of retries for modbusDevice_2 based on user selection
    int retries_2 = ui->cbNumberRetries_2->currentIndex();
    portModbus_2->setNumberOfRetries(retries_2);

    // Re-enable the "Test Connection" button after configuration
    ui->pbTestConnection->setEnabled(true);

    // Attempt to open modbusDevice_1 with configured parameters
    if (!portModbus_1->connectDevice())
    {
        qDebug() << "Failed to open modbusDevice_1:";
        qDebug() << portModbus_1->errorString();
    }
    else
    {
        qDebug() << "modbusDevice_1 opened successfully!";
    }

    // Attempt to open modbusDevice_1 with configured parameters
    if (!portModbus_2->connectDevice())
    {
        qDebug() << "Failed to open modbusDevice_2:";
        qDebug() << portModbus_2->errorString();
    }
    else
    {
        qDebug() << "modbusDevice_2 opened successfully!";
    }
}


/**
 * \brief Slot function to handle the Refresh Serial Port button click event.
 *
 * This function refreshes the list of available serial ports, updates the entries in the serial port combo box,
 * and disconnects the current serial port if connected. It also disables the Refresh button to prevent multiple clicks.
 */
void Interface::onRefreshSerialPortClicked()
{

    // Disable the "Refresh Ports" button to prevent multiple clicks
    ui->pbRefreshSerialPort->setDisabled(true);

    // Clear the entries container
    entries.clear();

    ports = QSerialPortInfo::availablePorts();

    ui->cbSelectSerial_1->clear();
    ui->cbSelectSerial_2->clear();

    foreach (const QSerialPortInfo &port, ports) {

        QString serialPort = port.portName() + " - " + port.description();

        ui->cbSelectSerial_1->addItem(serialPort);
    }

    // Disconnect from the current serial port
    DisconnectSerialPort();

    // Re-enable the "Refresh Ports" button
    ui->pbRefreshSerialPort->setDisabled(false);
}

/**
 * \brief Slot function to handle the Save Configuration button click event.
 *
 * This function saves the current configuration settings of the Interface dialog to the Windows registry.
 * It disables the Save button while saving to prevent multiple triggers and re-enables it after saving.
 */
void Interface::onSaveConfigurationClicked()
{
    // Disable the Save Configuration button to prevent multiple triggers
    ui->pbSaveConfiguration->setDisabled(true);

    // Initialize QSettings to save settings in the Windows registry
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("RS_485_422");

    // Save the current configuration settings to the registry
    settings.setValue("selectedSerial_1", ui->cbSelectSerial_1->currentIndex());
    settings.setValue("baudRate_1", ui->cbBaudRate_1->currentIndex());
    settings.setValue("dataBits_1", ui->cbSelectDataBits_1->currentIndex());
    settings.setValue("parity_1", ui->cbSelectParity_1->currentIndex());
    settings.setValue("stopBits_1", ui->cbSelectStopBits_1->currentIndex());
    settings.setValue("timeout_1", ui->leTimeout_1->text().toInt());
    settings.setValue("retriesNumber_1", ui->cbNumberRetries_1->currentIndex());

    settings.setValue("selectedSerial_2", ui->cbSelectSerial_2->currentIndex());
    settings.setValue("baudRate_2", ui->cbBaudRate_2->currentIndex());
    settings.setValue("dataBits_2", ui->cbSelectDataBits_2->currentIndex());
    settings.setValue("parity_2", ui->cbSelectParity_2->currentIndex());
    settings.setValue("stopBits_2", ui->cbSelectStopBits_2->currentIndex());
    settings.setValue("timeout_2", ui->leTimeout_2->text().toInt());
    settings.setValue("retriesNumber_2", ui->cbNumberRetries_2->currentIndex());

    settings.endGroup();
    settings.sync();

    // Re-enable the Save Configuration button
    ui->pbSaveConfiguration->setDisabled(false);
}

/**
 * \brief Handles the event when the Interface dialog is shown.
 *
 * This function is called when the Interface dialog is shown. It populates various UI components
 * with initial values such as baud rates, data bits, parity, stop bits, and other configuration settings.
 * It also retrieves and sets serial port information from the main window, and loads settings from the registry.
 *
 * \param event Pointer to the QShowEvent.
 */
void Interface::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    // Populate baud rate options
    QStringList baudRates{
          "1200",    "2400",    "4800",
          "9600",   "19200",   "38400",
         "57600"
    };

    ui->cbBaudRate_1->addItems(baudRates);
    ui->cbBaudRate_2->addItems(baudRates);

    // Populate data bits options
    QStringList dataBits{"5", "6", "7", "8"};
    ui->cbSelectDataBits_1->addItems(dataBits);
    ui->cbSelectDataBits_2->addItems(dataBits);

    // Populate parity options
    QStringList parity{"None", "Even", "Odd", "Space", "Mark"};
    ui->cbSelectParity_1->addItems(parity);
    ui->cbSelectParity_2->addItems(parity);

    // Populate stop bits options
    QStringList stopBits{"1", "2"};
    ui->cbSelectStopBits_1->addItems(stopBits);
    ui->cbSelectStopBits_2->addItems(stopBits);

    // Populate number of retries options
    QStringList retriesNumber{"1", "2", "3", "4", "5"};
    ui->cbNumberRetries_1->addItems(retriesNumber);
    ui->cbNumberRetries_2->addItems(retriesNumber);

    ui->pbRefreshSerialPort->setDisabled(true);

    // Clear the entries container
    entries.clear();

    ports = QSerialPortInfo::availablePorts();

    ui->cbSelectSerial_1->clear();
    ui->cbSelectSerial_2->clear();

    foreach (const QSerialPortInfo &port, ports) {

        QString serialPort = port.portName() + " - " + port.description();

        ui->cbSelectSerial_1->addItem(serialPort);
        ui->cbSelectSerial_2->addItem(serialPort);
    }

    // Disconnect from the current serial port
    DisconnectSerialPort();

    // Re-enable the "Refresh Ports" button
    ui->pbRefreshSerialPort->setDisabled(false);

    if (!ui->cbSelectSerial_1->count() || !ui->cbSelectSerial_2->count())
    {
        // Handle case where no serial ports are available (optional)
    }

    // Load settings from the registry
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("RS_485_422");

    // Set UI components to the saved settings
    ui->cbSelectSerial_1->setCurrentIndex(settings.value("selectedSerial_1", 0).toInt());
    ui->cbBaudRate_1->setCurrentIndex(settings.value("baudRate_1", 3).toInt());
    ui->cbSelectDataBits_1->setCurrentIndex(settings.value("dataBits_1", 3).toInt());
    ui->cbSelectParity_1->setCurrentIndex(settings.value("parity_1", 1).toInt());
    ui->cbSelectStopBits_1->setCurrentIndex(settings.value("stopBits_1", 0).toInt());
    ui->leTimeout_1->setText(settings.value("timeout_1", 1000).toString());
    ui->cbNumberRetries_1->setCurrentIndex(settings.value("retriesNumber_1", 4).toInt());

    ui->cbSelectSerial_2->setCurrentIndex(settings.value("selectedSerial_2", 1).toInt());
    ui->cbBaudRate_2->setCurrentIndex(settings.value("baudRate_2", 3).toInt());
    ui->cbSelectDataBits_2->setCurrentIndex(settings.value("dataBits_2", 3).toInt());
    ui->cbSelectParity_2->setCurrentIndex(settings.value("parity_2", 1).toInt());
    ui->cbSelectStopBits_2->setCurrentIndex(settings.value("stopBits_2", 0).toInt());
    ui->leTimeout_2->setText(settings.value("timeout_2", 1000).toString());
    ui->cbNumberRetries_2->setCurrentIndex(settings.value("retriesNumber_2", 4).toInt());

    settings.endGroup();
    settings.sync();

    // Set focus to the serial port selection combo box
    ui->cbSelectSerial_1->setFocus();
}


/**
 * \brief Disconnects the serial port.
 *
 * This function handles the disconnection process, ensuring that the serial port is properly closed.
 * It updates the UI to reflect the disconnection state and turns off the LED indicator for the serial connection.
 * Additionally, it deletes the ModbusClient object and sets the pointer to null.
 */
void Interface::DisconnectSerialPort()
{
    // Update UI to indicate that the interface is not connected to the RS485 network
    mainwindow->ui->lbConnected->setText(
        tr("Not connections to RS 485/422 networks"));

    // Turn off the LED indicator for the serial connection
    mainwindow->ui->SerialLedIndicator->setState(false);

    // Get a reference to the first Modbus Client pointer from the main window
    QModbusClient *&portModbus_1 = mainwindow->modbusDevice_1;

    // Check if the ModbusClient pointer is not null
    if (portModbus_1)
    {
        // Delete the ModbusClient object and set the pointer to null
        delete portModbus_1;
        portModbus_1 = nullptr;
    }

    // Get a reference to the second Modbus Client pointer from the main window
    QModbusClient *&portModbus_2 = mainwindow->modbusDevice_2;

    // Check if the ModbusClient pointer is not null
    if (portModbus_2)
    {
        // Delete the ModbusClient object and set the pointer to null
        delete portModbus_2;
        portModbus_2 = nullptr;
    }

    // Update the flag indicating whether there are Modbus ports openend
    isOpenModbusPort = false;
}

void Interface::onSelectSerialChanged()
{
    DisconnectSerialPort();
}

/**
 * \brief Slot called when the baud rate selection is changed.
 * Disconnects the serial port to apply the new baud rate setting.
 */
void Interface::onBaudRateChanged()
{
    DisconnectSerialPort();
}

/**
 * \brief Slot called when the data bits selection is changed.
 * Disconnects the serial port to apply the new data bits setting.
 */
void Interface::onSelectDataBitsChanged()
{
    DisconnectSerialPort();
}

/**
 * \brief Slot called when the parity selection is changed.
 * Disconnects the serial port to apply the new parity setting.
 */
void Interface::onSelectParityChanged()
{
    DisconnectSerialPort();
}

/**
 * \brief Slot called when the stop bits selection is changed.
 * Disconnects the serial port to apply the new stop bits setting.
 */
void Interface::onSelectStopBitsChanged()
{
    DisconnectSerialPort();
}
