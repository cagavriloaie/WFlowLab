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

QModbusClient *modbusDevice_1; /**< Pointer to the first Modbus client device. */
QModbusClient *modbusDevice_2; /**< Pointer to the second Modbus client device. */


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

    std::unique_ptr<QIntValidator> timeoutValidator(new QIntValidator(0, 1000, this));
    ui->leTimeout_1->setValidator(timeoutValidator.get());
    ui->leTimeout_2->setValidator(timeoutValidator.get());

    serialPorts = QSerialPortInfo::availablePorts();

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
    connect(ui->pbConnect, &QPushButton::clicked, this, &Interface::onConnectClicked);
    connect(ui->pbTestConnection, &QPushButton::clicked, this, &Interface::onTestConfigurationClicked);
    connect(ui->pbRefreshSerialPort, &QPushButton::clicked, this, &Interface::onRefreshSerialPortClicked);

    ui->cbSelectSerial_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->cbSelectSerial_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    modbusDevice_1 =  new QModbusRtuSerialClient(this);
    modbusDevice_2 =  new QModbusRtuSerialClient(this);

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


    nodesModbusCom1.emplace_back(1);
    nodesModbusCom2.emplace_back(1);

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
    // Set translated text for GroupBox 1
    ui->groupBox_1->setTitle(tr("RS-485/422 Serial Interface MODBUS"));
    ui->lbSelectSerial_1->setText(tr("Serial Port:"));
    ui->lbBaudRate_1->setText(tr("Baud Rate:"));
    ui->lbDataBits_1->setText(tr("Data Bits:"));
    ui->lbSelectParity_1->setText(tr("Parity:"));
    ui->lbSelectStopBits_1->setText(tr("Stop Bits:"));
    ui->lbTimeout_1->setText(tr("Timeout [ms]:"));
    ui->lbNumberOfRetries_1->setText(tr("Number of Retries:"));

    // Set translated text for GroupBox 2
    ui->groupBox_2->setTitle(tr("RS-485/422 Serial Interface MODBUS"));
    ui->lbSelectSerial_2->setText(tr("Serial Port:"));
    ui->lbBaudRate_2->setText(tr("Baud Rate:"));
    ui->lbDataBits_2->setText(tr("Data Bits:"));
    ui->lbSelectParity_2->setText(tr("Parity:"));
    ui->lbSelectStopBits_2->setText(tr("Stop Bits:"));
    ui->lbTimeout_2->setText(tr("Timeout [ms]:"));
    ui->lbNumberOfRetries_2->setText(tr("Number of Retries:"));

    // Set translated text for buttons
    ui->pbClose->setText(tr("Close"));
    ui->pbSaveConfiguration->setText(tr("Save Configuration"));
    ui->pbTestConnection->setText(tr("Test Connection"));
    ui->pbRefreshSerialPort->setText(tr("Refresh Ports"));
    ui->pbConnect->setText(tr("Connect ports"));
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
    //ledStateTable[positionTable]->setState(false);

    // Check if the cast was successful
    if (!reply)
    {
        return; // If the cast fails, exit the function
    }

    // Check if there was no error in the Modbus reply
    if (reply->error() == QModbusDevice::NoError)
    {
        // If there is no error, set the state of the LED to true
        //ledStateTable[positionTable]->setState(true);
    }

    // Increment the positionTable
    ++positionTable;

    // Schedule the reply object for deletion
    reply->deleteLater();
}

/**
 * \brief Checks the Modbus address by sending a read request.
 *
 * This function checks if a given Modbus address is valid by sending a read request
 * to the Modbus device. It uses a mutex lock to ensure thread safety and updates the LED state.
 *
 * \param address The Modbus address to check.
 * \return true if the request was successfully sent and accepted, false otherwise.
 */
// Declaration of extern variable
extern const std::vector<qint16> nodesModbusCom1;

/**
 * \brief Checks the Modbus addresses by sending read requests for all nodes in the vector.
 *
 * This function checks if the given Modbus addresses are valid by sending read requests
 * to the Modbus device for each address in the vector. It uses a mutex lock to ensure
 * thread safety and updates the LED state.
 *
 * \return true if all requests were successfully sent and accepted, false otherwise.
 */
bool Interface::checkModbusAddresses()
{
    std::lock_guard<std::mutex> lock(modbusLock); // Lock to ensure thread safety

    usleep(50000); // Delay before sending requests (50 ms)

    // Ensure modbusDevice_1 is properly initialized
    if (!modbusDevice_1)
    {
        qWarning() << "Modbus device 1 is not initialized.";
        return false;
    }

    // Ensure modbusDevice_2 is properly initialized
    if (!modbusDevice_2)
    {
        qWarning() << "Modbus device 2 is not initialized.";
        return false;
    }

    QModbusRtuSerialClient *portModbus_1 = qobject_cast<QModbusRtuSerialClient *>(modbusDevice_1);
    if (!portModbus_1)
    {
        qWarning() << "Failed to cast modbusDevice_1 to QModbusRtuSerialClient.";
        return false;
    }

    QModbusRtuSerialClient *portModbus_2 = qobject_cast<QModbusRtuSerialClient *>(modbusDevice_2);
    if (!portModbus_2)
    {
        qWarning() << "Failed to cast modbusDevice_2 to QModbusRtuSerialClient.";
        return false;
    }

    bool allRequestsSent = true;

    // Process each address in the nodesModbusCom1 vector
    for (const qint16 &address : nodesModbusCom1)
    {
        // Send a read request to the Modbus device 1
        QModbusReply *reply_1 = portModbus_1->sendReadRequest(QModbusDataUnit(QModbusDataUnit::InputRegisters, 1, 2), address);
        if (!reply_1)
        {
            qWarning() << "Failed to send Modbus read request for address (Device 1):" << address;
            allRequestsSent = false;
            continue;
        }

        if (!reply_1->isFinished())
        {
            // Connect finished signal to handle the reply
            connect(reply_1, &QModbusReply::finished, this, &Interface::onReadModbusReady);
        }
        else
        {
            // Handle immediately finished reply (broadcast replies)
            delete reply_1;
        }
    }

    // Process each address in the nodesModbusCom2 vector
    for (const qint16 &address : nodesModbusCom2)
    {
        // Send a read request to the Modbus device 2
        QModbusReply *reply_2 = portModbus_2->sendReadRequest(QModbusDataUnit(QModbusDataUnit::InputRegisters, 1, 2), address);
        if (!reply_2)
        {
            qWarning() << "Failed to send Modbus read request for address (Device 2):" << address;
            allRequestsSent = false;
            continue;
        }

        if (!reply_2->isFinished())
        {
            // Connect finished signal to handle the reply
            connect(reply_2, &QModbusReply::finished, this, &Interface::onReadModbusReady);
        }
        else
        {
            // Handle immediately finished reply (broadcast replies)
            delete reply_2;
        }
    }

    return allRequestsSent; // Successfully sent all requests
}

/**
 * \brief Slot function to handle the Test Configuration button click event.
 *
 * This function tests the Modbus connection by setting the Modbus device parameters
 * and attempting to connect. It updates the UI elements and displays the result
 * of the connection attempt.
 */
void Interface::onConnectClicked()
{
    // Disconnect any existing serial port connections
    DisconnectSerialPort();

    if (!modbusDevice_1) {
        modbusDevice_1 =  new QModbusRtuSerialClient(this);
    }

    if (!modbusDevice_2) {
        modbusDevice_2 =  new QModbusRtuSerialClient(this);
    }

    // Check if either modbusDevice_1 or modbusDevice_2 is not set
    if (!modbusDevice_1 || !modbusDevice_2)
    {
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
    }

    // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
    ui->pbTestConnection->setDisabled(true);
    ui->pbRefreshSerialPort->setDisabled(true);

    // Ensure serialPorts is properly initialized
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();

    // Get the selected index from the combo box
    int selectedIndex_1 = ui->cbSelectSerial_1->currentIndex();

    // Check if the index is valid
    if (selectedIndex_1 >= 0 && selectedIndex_1 < serialPorts.size()) {
        // Get the selected serial port information
        QSerialPortInfo serialPortInfo_1 = serialPorts.at(selectedIndex_1);
        QString serialName_1 = serialPortInfo_1.portName();

        // Ensure modbusDevice_1 is initialized
        if (modbusDevice_1 != nullptr) {
            // Set the connection parameter for modbusDevice_1
            modbusDevice_1->setConnectionParameter(QModbusDevice::SerialPortNameParameter, serialName_1);
        } else {
            // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
            ui->pbTestConnection->setDisabled(false);
            ui->pbRefreshSerialPort->setDisabled(false);

            DisconnectSerialPort(); // Disconnect any existing serial port connections
        }
    } else {
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
    }

    // Set baud rate for modbusDevice_1 based on user selection
    switch (ui->cbBaudRate_1->currentIndex())
    {
    case 0:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud1200);
        break;
    case 1:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud2400);
        break;
    case 2:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud4800);
        break;
    case 3:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    case 4:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
        break;
    case 5:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud38400);
        break;
    case 6:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
        break;
    case 7:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
        break;
    default:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    }

    // Set data bits for modbusDevice_1 based on user selection
    switch (ui->cbSelectDataBits_1->currentIndex())
    {
    case 0:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data5);
        break;
    case 1:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data6);
        break;
    case 2:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data7);
        break;
    case 3:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    default:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    }

    // Set parity for modbusDevice_1 based on user selection
    switch (ui->cbSelectParity_1->currentIndex())
    {
    case 0:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    case 1:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
        break;
    case 2:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::OddParity);
        break;
    case 3:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::SpaceParity);
        break;
    case 4:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::MarkParity);
        break;
    default:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    }

    // Set stop bits for modbusDevice_1 based on user selection
    switch (ui->cbSelectStopBits_1->currentIndex())
    {
    case 0:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    case 1:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneAndHalfStop);
        break;
    case 2:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::TwoStop);
        break;
    default:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    }

    bool ok_1;
    int timeout_1 = ui->leTimeout_1->text().toInt(&ok_1);
    if (ok_1 && timeout_1 > 0 && timeout_1 <= 1000) {
        modbusDevice_1->setTimeout(timeout_1);
    } else {
        QMessageBox::warning(this, "Invalid Timeout", "Timeout 1 is more than 1000 ms.");
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
        return;
    }

    // Set number of retries for modbusDevice_1 based on user selection
    int retries_1 = ui->cbNumberRetries_1->currentIndex();
    modbusDevice_1->setNumberOfRetries(retries_1);


    // Configure serial port parameters for modbusDevice_2
    int selectedIndex_2 = ui->cbSelectSerial_2->currentIndex();
    if (selectedIndex_2 >= 0 && selectedIndex_2 < serialPorts.size()) {
        QSerialPortInfo serialPortInfo_2 = serialPorts.at(selectedIndex_2);
        QString serialName_2 = serialPortInfo_2.portName();

        if (modbusDevice_2 != nullptr) {
            modbusDevice_2->setConnectionParameter(QModbusDevice::SerialPortNameParameter, serialName_2);
        } else {
            // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
            ui->pbTestConnection->setDisabled(false);
            ui->pbRefreshSerialPort->setDisabled(false);

            DisconnectSerialPort(); // Disconnect any existing serial port connections
        }
    } else {
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
    }
    // Set baud rate for modbusDevice_2 based on user selection
    switch (ui->cbBaudRate_2->currentIndex())
    {
    case 0:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud1200);
        break;
    case 1:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud2400);
        break;
    case 2:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud4800);
        break;
    case 3:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    case 4:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
        break;
    case 5:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud38400);
        break;
    case 6:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
        break;
    case 7:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
        break;
    default:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    }

    // Set data bits for modbusDevice_2 based on user selection
    switch (ui->cbSelectDataBits_2->currentIndex())
    {
    case 0:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data5);
        break;
    case 1:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data6);
        break;
    case 2:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data7);
        break;
    case 3:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    default:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    }

    // Set parity for modbusDevice_2 based on user selection
    switch (ui->cbSelectParity_2->currentIndex())
    {
    case 0:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    case 1:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
        break;
    case 2:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::OddParity);
        break;
    case 3:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::SpaceParity);
        break;
    case 4:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::MarkParity);
        break;
    default:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    }

    // Set stop bits for modbusDevice_2 based on user selection
    switch (ui->cbSelectStopBits_2->currentIndex())
    {
    case 0:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    case 1:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneAndHalfStop);
        break;
    case 2:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::TwoStop);
        break;
    default:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    }

    // Set timeout for modbusDevice_2 based on user input
    bool ok_2;
    int timeout_2 = ui->leTimeout_2->text().toInt(&ok_2);
    if (ok_2 && timeout_2 > 0 && timeout_2 <= 1000) {
        modbusDevice_2->setTimeout(timeout_2);
    } else {
        QMessageBox::warning(this, "Invalid Timeout", "Timeout 2 is more than 1000 ms.");
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
        return;
    }

    // Set number of retries for modbusDevice_2 based on user selection
    int retries_2 = ui->cbNumberRetries_2->currentIndex();
    modbusDevice_2->setNumberOfRetries(retries_2);

    // Attempt to open modbusDevice_1 with configured parameters
    bool modbusDevice_1_opened = modbusDevice_1->connectDevice();
    if (!modbusDevice_1_opened)
    {
        qDebug() << "Failed to open modbusDevice_1:";
        qDebug() << modbusDevice_1->errorString();
    }
    else
    {
        qDebug() << "modbusDevice_1 opened successfully!";
    }

    // Attempt to open modbusDevice_1 with configured parameters
    bool modbusDevice_2_opened = modbusDevice_2->connectDevice();
    if (!modbusDevice_2_opened)
    {
        qDebug() << "Failed to open modbusDevice_2:";
        qDebug() << modbusDevice_2->errorString();
    }
    else
    {
        qDebug() << "modbusDevice_2 opened successfully!";
    }

    // Create a message box to display the connection status
    QString statusMessage;

    QSerialPortInfo serialPortInfo_1 = serialPorts.at(selectedIndex_1);
    QString serialName_1 = serialPortInfo_1.portName();

    QSerialPortInfo serialPortInfo_2 = serialPorts.at(selectedIndex_2);
    QString serialName_2 = serialPortInfo_2.portName();

    statusMessage += QString("Modbus Device %1 connection status: %2\n").arg(serialName_1).arg(modbusDevice_1_opened ? "Success" : "Failure");
    statusMessage += QString("Modbus Device %1 connection status: %2").arg(serialName_2).arg(modbusDevice_2_opened ? "Success" : "Failure");

    QMessageBox::information(this, "MODBUS Connection Status", statusMessage);

    // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
    ui->pbTestConnection->setDisabled(false);
    ui->pbRefreshSerialPort->setDisabled(false);

    checkModbusAddresses();

    if (mainwindow) {
        if(modbusDevice_1_opened && modbusDevice_1_opened) {
            mainwindow->statusBarMessage = " > MODBUS Interface Mode Operation / Connected";
        }
        else
        {
            mainwindow->statusBarMessage = " > MODBUS Interface Mode Operation / Not Connected";
        }
        mainwindow->setStatusBarMessage(mainwindow->statusBarMessage);
    }
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
    // Disconnect any existing serial port connections
    DisconnectSerialPort();

    if (!modbusDevice_1) {
        modbusDevice_1 =  new QModbusRtuSerialClient(this);
    }

    if (!modbusDevice_2) {
        modbusDevice_2 =  new QModbusRtuSerialClient(this);
    }

    // Check if either modbusDevice_1 or modbusDevice_2 is not set
    if (!modbusDevice_1 || !modbusDevice_2)
    {
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
    }

    // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
    ui->pbTestConnection->setDisabled(true);
    ui->pbRefreshSerialPort->setDisabled(true);

    // Ensure serialPorts is properly initialized
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();

    // Get the selected index from the combo box
    int selectedIndex_1 = ui->cbSelectSerial_1->currentIndex();

    // Check if the index is valid
    if (selectedIndex_1 >= 0 && selectedIndex_1 < serialPorts.size()) {
        // Get the selected serial port information
        QSerialPortInfo serialPortInfo_1 = serialPorts.at(selectedIndex_1);
        QString serialName_1 = serialPortInfo_1.portName();

        // Ensure modbusDevice_1 is initialized
        if (modbusDevice_1 != nullptr) {
            // Set the connection parameter for modbusDevice_1
            modbusDevice_1->setConnectionParameter(QModbusDevice::SerialPortNameParameter, serialName_1);
        } else {
            // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
            ui->pbTestConnection->setDisabled(false);
            ui->pbRefreshSerialPort->setDisabled(false);

            DisconnectSerialPort(); // Disconnect any existing serial port connections
        }
    } else {
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
    }

    // Set baud rate for modbusDevice_1 based on user selection
    switch (ui->cbBaudRate_1->currentIndex())
    {
    case 0:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud1200);
        break;
    case 1:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud2400);
        break;
    case 2:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud4800);
        break;
    case 3:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    case 4:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
        break;
    case 5:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud38400);
        break;
    case 6:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
        break;
    case 7:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
        break;
    default:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    }

    // Set data bits for modbusDevice_1 based on user selection
    switch (ui->cbSelectDataBits_1->currentIndex())
    {
    case 0:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data5);
        break;
    case 1:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data6);
        break;
    case 2:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data7);
        break;
    case 3:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    default:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    }

    // Set parity for modbusDevice_1 based on user selection
    switch (ui->cbSelectParity_1->currentIndex())
    {
    case 0:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    case 1:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
        break;
    case 2:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::OddParity);
        break;
    case 3:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::SpaceParity);
        break;
    case 4:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::MarkParity);
        break;
    default:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    }

    // Set stop bits for modbusDevice_1 based on user selection
    switch (ui->cbSelectStopBits_1->currentIndex())
    {
    case 0:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    case 1:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneAndHalfStop);
        break;
    case 2:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::TwoStop);
        break;
    default:
        modbusDevice_1->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    }

    bool ok_1;
    int timeout_1 = ui->leTimeout_1->text().toInt(&ok_1);
    if (ok_1 && timeout_1 > 0 && timeout_1 <= 1000) {
        modbusDevice_1->setTimeout(timeout_1);
    } else {
        QMessageBox::warning(this, "Invalid Timeout", "Timeout 1 is more than 1000 ms.");
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
        return;
    }

    // Set number of retries for modbusDevice_1 based on user selection
    int retries_1 = ui->cbNumberRetries_1->currentIndex();
    modbusDevice_1->setNumberOfRetries(retries_1);


    // Configure serial port parameters for modbusDevice_2
    int selectedIndex_2 = ui->cbSelectSerial_2->currentIndex();
    if (selectedIndex_2 >= 0 && selectedIndex_2 < serialPorts.size()) {
        QSerialPortInfo serialPortInfo_2 = serialPorts.at(selectedIndex_2);
        QString serialName_2 = serialPortInfo_2.portName();

        if (modbusDevice_2 != nullptr) {
            modbusDevice_2->setConnectionParameter(QModbusDevice::SerialPortNameParameter, serialName_2);
        } else {
            // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
            ui->pbTestConnection->setDisabled(false);
            ui->pbRefreshSerialPort->setDisabled(false);

            DisconnectSerialPort(); // Disconnect any existing serial port connections
        }
    } else {
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
    }
    // Set baud rate for modbusDevice_2 based on user selection
    switch (ui->cbBaudRate_2->currentIndex())
    {
    case 0:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud1200);
        break;
    case 1:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud2400);
        break;
    case 2:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud4800);
        break;
    case 3:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    case 4:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
        break;
    case 5:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud38400);
        break;
    case 6:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud57600);
        break;
    case 7:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud115200);
        break;
    default:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
        break;
    }

    // Set data bits for modbusDevice_2 based on user selection
    switch (ui->cbSelectDataBits_2->currentIndex())
    {
    case 0:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data5);
        break;
    case 1:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data6);
        break;
    case 2:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data7);
        break;
    case 3:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    default:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
        break;
    }

    // Set parity for modbusDevice_2 based on user selection
    switch (ui->cbSelectParity_2->currentIndex())
    {
    case 0:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    case 1:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
        break;
    case 2:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::OddParity);
        break;
    case 3:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::SpaceParity);
        break;
    case 4:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::MarkParity);
        break;
    default:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
        break;
    }

    // Set stop bits for modbusDevice_2 based on user selection
    switch (ui->cbSelectStopBits_2->currentIndex())
    {
    case 0:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    case 1:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneAndHalfStop);
        break;
    case 2:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::TwoStop);
        break;
    default:
        modbusDevice_2->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
        break;
    }

    // Set timeout for modbusDevice_2 based on user input
    bool ok_2;
    int timeout_2 = ui->leTimeout_2->text().toInt(&ok_2);
    if (ok_2 && timeout_2 > 0 && timeout_2 <= 1000) {
        modbusDevice_2->setTimeout(timeout_2);
    } else {
        QMessageBox::warning(this, "Invalid Timeout", "Timeout 2 is more than 1000 ms.");
        // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
        ui->pbTestConnection->setDisabled(false);
        ui->pbRefreshSerialPort->setDisabled(false);

        DisconnectSerialPort(); // Disconnect any existing serial port connections
        return;
    }

    // Set number of retries for modbusDevice_2 based on user selection
    int retries_2 = ui->cbNumberRetries_2->currentIndex();
    modbusDevice_2->setNumberOfRetries(retries_2);

    // Attempt to open modbusDevice_1 with configured parameters
    bool modbusDevice_1_opened = modbusDevice_1->connectDevice();
    if (!modbusDevice_1_opened)
    {
        qDebug() << "Failed to open modbusDevice_1:";
        qDebug() << modbusDevice_1->errorString();
    }
    else
    {
        qDebug() << "modbusDevice_1 opened successfully!";
    }

    // Attempt to open modbusDevice_1 with configured parameters
    bool modbusDevice_2_opened = modbusDevice_2->connectDevice();
    if (!modbusDevice_2_opened)
    {
        qDebug() << "Failed to open modbusDevice_2:";
        qDebug() << modbusDevice_2->errorString();
    }
    else
    {
        qDebug() << "modbusDevice_2 opened successfully!";
    }

    // Create a message box to display the connection status
    QString statusMessage;

    QSerialPortInfo serialPortInfo_1 = serialPorts.at(selectedIndex_1);
    QString serialName_1 = serialPortInfo_1.portName();

    QSerialPortInfo serialPortInfo_2 = serialPorts.at(selectedIndex_2);
    QString serialName_2 = serialPortInfo_2.portName();

    statusMessage += QString("Modbus Device %1 connection status: %2\n").arg(serialName_1).arg(modbusDevice_1_opened ? "Success" : "Failure");
    statusMessage += QString("Modbus Device %1 connection status: %2").arg(serialName_2).arg(modbusDevice_2_opened ? "Success" : "Failure");

    QMessageBox::information(this, "MODBUS Connection Status", statusMessage);

    // Disable the "Test Connection" and "Refresh Serial Ports" buttons while configuring
    ui->pbTestConnection->setDisabled(false);
    ui->pbRefreshSerialPort->setDisabled(false);

    checkModbusAddresses();

    DisconnectSerialPort(); // Disconnect any existing serial port connections
}

/**
 * \brief Slot function to handle the Refresh Serial Port button click event.
 *
 * This function refreshes the list of available serial serialPorts, updates the entries in the serial port combo box,
 * and disconnects the current serial port if connected. It also disables the Refresh button to prevent multiple clicks.
 */
void Interface::onRefreshSerialPortClicked()
{
    ui->pbConnect->setEnabled(false);
    ui->pbRefreshSerialPort->setEnabled(true);
    ui->pbSaveConfiguration->setEnabled(false);
    ui->pbClose->setEnabled(true);
    ui->pbTestConnection->setEnabled(true);

    // Disable the "Refresh Ports" button to prevent multiple clicks
    ui->pbRefreshSerialPort->setEnabled(false);

    // Disable the "Test Connection" button to prevent multiple clicks
    ui->pbTestConnection->setEnabled(false);

    // Get the currently available serial ports
    serialPorts = QSerialPortInfo::availablePorts();

    // Clear the items in both combo boxes
    ui->cbSelectSerial_1->clear();
    ui->cbSelectSerial_2->clear();

    // Populate the combo boxes with available serial ports
    for (const QSerialPortInfo &port : serialPorts) {
        QString serialPort = port.portName() + " - " + port.description();
        ui->cbSelectSerial_1->addItem(serialPort);
        ui->cbSelectSerial_2->addItem(serialPort); // Assuming both combo boxes should have the same list
    }

    // Disconnect from any existing serial port connections
    DisconnectSerialPort();

    // Re-enable the "Refresh Ports" button
    ui->pbRefreshSerialPort->setEnabled(true);

    // Enable the "Test Connection" button
    ui->pbTestConnection->setEnabled(true);

    // Check if there are fewer than 2 serial ports
    if (serialPorts.size() < 2) {
        ui->pbConnect->setEnabled(false);
        ui->pbRefreshSerialPort->setEnabled(true);
        ui->pbSaveConfiguration->setEnabled(false);
        ui->pbClose->setEnabled(true);
        ui->pbTestConnection->setEnabled(false);
        QMessageBox::critical(this, tr("Error"), tr("At least two MODBUS interfaces are required."));
    }
    else {
        QMessageBox::information(this, tr("Serial Ports Updated"), tr("MODBUS serial ports DB have been updated."));
    }
}

/**
 * \brief Slot function to handle the Save Configuration button click event.
 *
 * This function saves the current configuration settings of the Interface dialog to the Windows registry.
 * It disables the Save button while saving to prevent multiple triggers and re-enables it after saving.
 */
void Interface::onSaveConfigurationClicked()
{
    // Check if selections are different
    if (ui->cbSelectSerial_1->currentIndex() != ui->cbSelectSerial_2->currentIndex())
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

        // Show message box to confirm configuration saved
        QMessageBox::information(this, "Configuration Saved", "Current MODBUS configuration is saved.");
    }
    else
    {
        // If selections are the same, show a warning message
        QMessageBox::warning(this, "Configuration Not Saved", "Serial port selections must be different to save configuration.");
    }
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

    ui->pbConnect->setEnabled(true);
    ui->pbRefreshSerialPort->setEnabled(true);
    ui->pbSaveConfiguration->setEnabled(true);
    ui->pbClose->setEnabled(true);
    ui->pbTestConnection->setEnabled(true);

    // Populate baud rate options
    QStringList baudRates{"1200", "2400", "4800", "9600", "19200", "38400", "57600"};
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

    // Disable the "Refresh Ports" button initially to prevent multiple clicks
    ui->pbRefreshSerialPort->setEnabled(false);

    // Clear and populate serial port selection combo boxes
    ui->cbSelectSerial_1->clear();
    ui->cbSelectSerial_2->clear();

    // Disconnect from the current serial port if any
    DisconnectSerialPort();

    // Re-enable the "Refresh Ports" button after populating serial ports
    ui->pbRefreshSerialPort->setEnabled(true);

    // Load settings from the registry
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("RS_485_422");

    // Set UI components to the saved settings for port 1
    ui->cbSelectSerial_1->setCurrentIndex(settings.value("selectedSerial_1", 0).toInt());
    ui->cbBaudRate_1->setCurrentIndex(settings.value("baudRate_1", 3).toInt());
    ui->cbSelectDataBits_1->setCurrentIndex(settings.value("dataBits_1", 3).toInt());
    ui->cbSelectParity_1->setCurrentIndex(settings.value("parity_1", 1).toInt());
    ui->cbSelectStopBits_1->setCurrentIndex(settings.value("stopBits_1", 0).toInt());
    ui->leTimeout_1->setText(settings.value("timeout_1", 1000).toString());
    ui->cbNumberRetries_1->setCurrentIndex(settings.value("retriesNumber_1", 4).toInt());

    // Set UI components to the saved settings for port 2
    ui->cbSelectSerial_2->setCurrentIndex(settings.value("selectedSerial_2", 1).toInt());
    ui->cbBaudRate_2->setCurrentIndex(settings.value("baudRate_2", 3).toInt());
    ui->cbSelectDataBits_2->setCurrentIndex(settings.value("dataBits_2", 3).toInt());
    ui->cbSelectParity_2->setCurrentIndex(settings.value("parity_2", 1).toInt());
    ui->cbSelectStopBits_2->setCurrentIndex(settings.value("stopBits_2", 0).toInt());
    ui->leTimeout_2->setText(settings.value("timeout_2", 1000).toString());
    ui->cbNumberRetries_2->setCurrentIndex(settings.value("retriesNumber_2", 4).toInt());

    settings.endGroup();
    settings.sync();

    // Set focus to the serial port selection combo box for port 1
    ui->cbSelectSerial_1->setFocus();

    serialPorts = QSerialPortInfo::availablePorts();

    // Check if there are fewer than 2 serial ports
    if (serialPorts.size() < 2) {
        ui->pbConnect->setEnabled(false);
        ui->pbRefreshSerialPort->setEnabled(true);
        ui->pbSaveConfiguration->setEnabled(false);
        ui->pbClose->setEnabled(true);
        ui->pbTestConnection->setEnabled(false);
        QMessageBox::critical(this, tr("Error"), tr("At least two MODBUS interfaces are required."));
    } else {
        foreach (const QSerialPortInfo &port, serialPorts) {
            QString serialPort = port.portName() + " - " + port.description();
            ui->cbSelectSerial_1->addItem(serialPort);
            ui->cbSelectSerial_2->addItem(serialPort);
        }
    }
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
    // Check if the ModbusClient pointers are valid before deleting them
    if (modbusDevice_1) {
        delete modbusDevice_1;
        modbusDevice_1 = nullptr;
    }

    if (modbusDevice_2) {
        delete modbusDevice_2;
        modbusDevice_2 = nullptr;
    }

    // Update UI indicators if mainwindow is valid
    if (mainwindow) {
        // Update connected status label
        mainwindow->ui->lbConnected->setText(tr("Not connected to RS 485/422 networks"));

        // Turn off the LED indicator for serial connection
        //mainwindow->ui->SerialLedIndicator->setState(false);
    }

    // Update flag indicating Modbus ports are not open
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
