/**
 * \file mainwindow.cpp
 * \brief Implementation file for the MainWindow class.
 *
 * This file contains the implementations of member functions and slots
 * for the MainWindow class. It handles the main window of the application,
 * including initialization, event handling, and slot implementations.
 *
 * \author Constantin
 * \date Insert date
 */

// C++ Standard Library headers
#include <filesystem>   ///< Provides facilities to manipulate and query file systems and their components.
#include <fstream>      ///< Input/output stream class to operate on files.
#include <iomanip>      ///< Manipulators for formatting output.
#include <map>          ///< Associative containers that store elements in a mapped fashion.
#include <sstream>      ///< Implements input/output operations on memory-based streams.

// Qt headers
#include <QDesktopServices> ///< Access to the desktop services such as opening a URL.
#include <QDir>             ///< Provides access to directory structures and their contents.
#include <QLibrary>         ///< Platform-independent library loading and function resolution.
#include <QLineEdit>        ///< Single-line text editor widget with input validation and styling.
#include <QMessageBox>      ///< Modal dialog for informing the user or for asking the user a question and receiving an answer.
#include <QSettings>        ///< Persistent platform-independent application settings.
#include <QValidator>       ///< Base class for all validators that can be easily attached to input widgets.

// Windows-specific headers
#include <windows.h>    ///< Main Windows SDK header providing core Windows APIs.

// Custom headers
#include "definitions.h"    ///< Custom application-specific definitions.
#include "waterdensity.h"   ///< Header for water density calculations.
#include "flow-meter-type.h"///< Header defining flow meter types.
#include "mainwindow.h"     ///< Header for the main application window.
#include "md5.h"            ///< Header for MD5 hashing functionality.
#include "ui_mainwindow.h"  ///< User interface header generated from Qt Designer.

#include <QFile>        ///< Provides functions to read from and write to files.
#include <QDir>         ///< Provides access to directory structures and their contents.
#include <QUrl>         ///< Represents a URL.
#include <QDesktopServices> ///< Access to the desktop services such as opening a URL.
#include <fstream>      ///< Input/output stream class to operate on files.
#include <iomanip>      ///< Manipulators for formatting output.
#include <sstream>      ///< Implements input/output operations on memory-based streams.

extern QTranslator *appTranslator;
MainWindow *pMainWindow;

std::wstring ExePath()
{
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(
                                      L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

/**
 * \brief Sets default configuration values for optionsConfiguration.
 *
 * This function clears the optionsConfiguration map and initializes default
 * values for various configuration keys:
 * - "company": Default value is "NONE".
 * - "archive": Default path is "C:/Stand/Fise".
 * - "maximum": Default value is "2".
 * - "certificate": Default value is "NONE".
 * - "density_20": Default value is "998.2009".
 * - "control": Default value is "00000000000000000000000000000000".
 */
void MainWindow::SetDefaultConfiguration()
{
    optionsConfiguration.clear();
    optionsConfiguration["company"] = "NONE";
    optionsConfiguration["archive"] = "C:/Stand/Fise";
    optionsConfiguration["maximum"] = "2";
    optionsConfiguration["certificate"] = "NONE";
    optionsConfiguration["density_20"] = "998.2009";
    optionsConfiguration["control"] = "00000000000000000000000000000000";
}

/**
 * \brief Reads and parses configuration settings from a file.
 *
 * This function reads the configuration file specified by 'watermeters.conf'
 * located in the application's directory. It parses key-value pairs separated
 * by '=' and terminates each entry with '>'. It then validates the MD5 checksum
 * formed by concatenating 'company' and 'maximum' fields against a stored control
 * checksum ('control'). If validation succeeds, default configuration values
 * are updated.
 *
 * If the configuration file cannot be opened or if validation fails, default
 * configuration values are set using SetDefaultConfiguration().
 *  e.g.
 *      company=Compania de Apa Braila>
 *      archive=C:/Stand/Fise>
 *      maximum=20>
 *      certificate=CE 06.02-355/15>
 *      density_20=998>
 *      control=f1807e24ccba79a76baa08194b7fa9bf>
 *
 *      company + density_20 => MD5
 */
void MainWindow::ReadConfiguration()
{
    std::wstring pathToConfig = ExePath() + L"\\watermeters.conf";
    std::ifstream
        inConfigurationFile(pathToConfig.c_str());
    if (inConfigurationFile.is_open())
    {
        std::string key;
        while (std::getline(inConfigurationFile, key, '='))
        {
            std::string value;
            if (std::getline(inConfigurationFile, value, '>'))
            {
                optionsConfiguration[key] = value;
                std::getline(inConfigurationFile, value);
            }
        }

        if(
            optionsConfiguration.find("company") != optionsConfiguration.end() &&
            optionsConfiguration.find("control") != optionsConfiguration.end() &&
            optionsConfiguration.find("maximum") != optionsConfiguration.end()
            )
        {
            std::string md5Read;
            std::string md5Calculate;
            md5Read = optionsConfiguration["control"];
            std::string wordControl = optionsConfiguration["company"] +
                                      optionsConfiguration["maximum"];
            md5Calculate = md5(wordControl);

            if (md5Read == md5Calculate)
            {
                // Update options only if the key does not exist
                optionsConfiguration.insert({"density_20", "998.2009"});
                optionsConfiguration.insert({"archive", "C:/Stand/Fise"});
                optionsConfiguration.insert({"certificate", "NONE"});

                // Close the file stream before returning
                inConfigurationFile.close();
                return;
            }
        }
    }

    // If file cannot be opened or validation fails, set default configuration
    SetDefaultConfiguration();

    inConfigurationFile.close(); // Close the file stream
    return;
}

/**
 * \brief Structure to hold information about RS485 settings.
 *
 * This struct defines a key-value pair where:
 * - `key` is a pointer to a constant character array representing the setting's identifier.
 * - `defaultValue` is a QVariant storing the default value associated with the setting.
 */
struct RS485SettingInfo {
    const char* key;         ///< Pointer to a constant character array representing the setting's identifier.
    const QVariant defaultValue;   ///< QVariant storing the default value associated with the setting.
};

/**
 * \brief Sets the text of a QLabel to display a double value with specified precision.
 *
 * This function converts a double value to a string with fixed precision and sets
 * the text of the specified QLabel to display this string.
 *
 * \param label The QLabel widget whose text will be set.
 * \param value The double value to be displayed.
 * \param precision The number of decimal places to display.
 */
void MainWindow::setLabelValue(QLabel* label, double value, int precision)
{
    std::ostringstream streamObj;  // Create a string stream object
    streamObj << std::fixed << std::setprecision(precision) << value;  // Format the double value with fixed precision
    label->setText(streamObj.str().c_str());  // Set the text of the label to the formatted value
    streamObj.str("");  // Clear the string stream for future use
}

/**
 * \brief Updates the selectedInfo structure with current configuration and UI data.
 *
 * This function updates the selectedInfo structure with the following information:
 * - Parameters from optionsConfiguration: density_20, archive path, certificate, and number of water meters.
 * - Lab conditions from settings: ambient temperature, relative air humidity, and atmospheric pressure.
 * - Selected water meter information from UI: name, nominal diameter, nominal flow, maximum flow,
 *   transition flow, minimum flow, nominal error, and maximum error.
 */
void MainWindow::updateSelectedInfo()
{
    // Update selectedInfo with parameters from optionsConfiguration
    selectedInfo.density_20 = std::stof(optionsConfiguration["density_20"]);
    selectedInfo.pathResults = optionsConfiguration["archive"];
    selectedInfo.certificate = optionsConfiguration["certificate"];
    selectedInfo.entriesNumber = ui->cbNumberOfWaterMeters->currentText().toInt();

    // Read lab conditions from settings
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);

    // LabConditions
    settings.beginGroup("LabConditions");

    // Read and set ambient temperature
    std::string temperature;
    if (settings.childKeys().contains("labTemperature")) {
        temperature = settings.value("labTemperature").toString().toStdString();
    } else {
        temperature = "18";  // Default value if not found
    }

    // Read and set relative air humidity
    std::string humidity;
    if (settings.childKeys().contains("labHumidity")) {
        humidity = settings.value("labHumidity").toString().toStdString();
    } else {
        humidity = "51";  // Default value if not found
    }

    // Read and set atmospheric pressure
    std::string pressure;
    if (settings.childKeys().contains("labPressure")) {
        pressure = settings.value("labPressure").toString().toStdString();
    } else {
        pressure = "1026";  // Default value if not found
    }

    settings.endGroup();

    // Update selectedInfo with lab conditions
    selectedInfo.ambientTemperature = temperature;
    selectedInfo.athmosphericPressure = pressure;
    selectedInfo.relativeAirHumidity = humidity;

    // Get selected water meter index from UI
    int selectedWaterMeter = ui->cbWaterMeterType->currentIndex();

    // Retrieve meter flow information from MeterFlowDB
    const auto& meterFlowInfo = MeterFlowDB[selectedWaterMeter];

    // Update selectedInfo with meter flow information
    selectedInfo.nameWaterMeter = meterFlowInfo.nameWaterMeter;
    selectedInfo.nominalDiameter = meterFlowInfo.nominalDiameter;
    selectedInfo.nominalFlow = meterFlowInfo.nominalFlow;
    selectedInfo.maximumFlow = meterFlowInfo.maximumFlow;
    selectedInfo.trasitionFlow = meterFlowInfo.trasitionFlow;
    selectedInfo.minimumFlow = meterFlowInfo.minimumFlow;
    selectedInfo.nominalError = meterFlowInfo.nominalError;
    selectedInfo.maximumError = meterFlowInfo.maximumError;
}

/**
 * \brief Updates selectedInfo based on the currently selected water meter,
 *        creates necessary directories, and updates UI labels.
 *
 * This function performs the following tasks:
 * 1. Calls updateSelectedInfo() to update selectedInfo with current configuration and UI data.
 * 2. Creates directories for results and input data using selectedInfo.pathResults.
 * 3. Updates various QLabel widgets in the UI with values from selectedInfo.
 */
void MainWindow::SelectMeterComboBox()
{
    // Update selectedInfo with information based on the selected water meter
    updateSelectedInfo();

    // Create directories for results and input data
    std::filesystem::create_directories(selectedInfo.pathResults);
    std::filesystem::create_directories(selectedInfo.pathResults + "/inputData");

    // Update labels in the UI with selectedInfo values
    setLabelValue(ui->lbNominalDiameterCurrent, selectedInfo.nominalDiameter, 0);
    setLabelValue(ui->lbMaximumFlowCurrent, selectedInfo.maximumFlow, 2);
    setLabelValue(ui->lbNominalFlowCurrent, selectedInfo.nominalFlow, 2);
    setLabelValue(ui->lbTransitionFlowCurrent, selectedInfo.trasitionFlow, 2);
    setLabelValue(ui->lbMinimumFlowCurrent, selectedInfo.minimumFlow, 2);
    setLabelValue(ui->lbMaximumErrorCurrent, selectedInfo.maximumError, 1);
    setLabelValue(ui->lbNominalErrorCurrent, selectedInfo.nominalError, 1);
}

/**
 * \brief Translates all UI elements to the current language.
 *
 * This function translates all visible UI elements to the current language.
 * It sets the window title, menu titles, action texts, labels, group box titles,
 * radio button texts, and push button texts.
 */
void MainWindow::Translate()
{
    // Translate window title
    this->setWindowTitle(tr("WStreamLab - Dashboard"));

    // Translate menu titles
    ui->menu_File->setTitle(tr("File"));
    ui->menu_Language->setTitle(tr("Language"));
    ui->menu_Help->setTitle(tr("Help"));

    // Translate action texts
    ui->action_StartSession->setText(tr("Start Session"));
    ui->action_ExitApp->setText(tr("Exit"));
    ui->action_English->setText(tr("English"));
    ui->action_Romana->setText(tr("Română"));
    ui->action_General_Description->setText(tr("General Description"));
    ui->action_WaterDensity->setText(tr("Water Density"));
    ui->action_License->setText(tr("License"));
    ui->action_About->setText(tr("About"));

    // Translate labels
    ui->lbWaterMeterType->setText(tr("Water meter type:"));
    ui->lbNumberOfWaterMeters->setText(tr("Number of water meters:"));
    ui->lbTemperature->setText(tr("Temperature:"));
    ui->lbPressure->setText(tr("Athmosferic pressure:"));
    ui->lbHumidity->setText(tr("Relative air humidity:"));
    ui->lbTab5->setText(tr("[mbar]"));
    ui->lbTab3->setText(tr("\302\260C")); // Degrees Celsius symbol
    ui->lbTab4->setText(tr("[%]"));

    // Translate group box titles
    ui->gbMeasurementMethod->setTitle(tr("Measurement method"));
    ui->gbReadMethod->setTitle(tr("Read method"));
    ui->gbWaterMeterFeatures->setTitle(tr("Water meter features"));

    // Translate radio button texts
    ui->rbVolumetric->setText(tr("Volumetric"));
    ui->rbGravimetric->setText(tr("Gravimetric"));
    ui->rbManual->setText(tr("Manual"));
    ui->rbInterface->setText(tr("Interface"));

    // Translate labels in Water Meter Features group
    ui->lbNominalDiameter->setText(tr("Nominal diameter:"));
    ui->lbMaximumFlow->setText(tr("Maximum flow:"));
    ui->lbNominalFlow->setText(tr("Nominal flow:"));
    ui->lbTransitionFlow->setText(tr("Transition flow:"));
    ui->lbMinimumFlow->setText(tr("Minimum flow:"));
    ui->lbMaximumError->setText(tr("Maximum error:"));
    ui->lbNominalError->setText(tr("Nominal error:"));
    ui->lbNominalDiameterUnit->setText(tr("[mm]"));
    ui->lbMaximumFlowUnit->setText(tr("[l/h]"));
    ui->lbNominalFlowUnit->setText(tr("[l/h]"));
    ui->lbTransitionFlowUnit->setText(tr("[l/h]"));
    ui->lbMinimumFlowUnit->setText(tr("[l/h]"));
    ui->lbMaximumErrorUnit->setText(tr("[%]"));
    ui->lbNominalErrorUnit->setText(tr("[%]"));

    // Translate push button texts
    ui->pbNewSession->setText(tr("&New Session"));
    ui->pbExitApplication->setText(tr("&Exit"));
}

/**
 * \brief Constructor for MainWindow class.
 *
 * Initializes the main window of the application, sets up UI elements,
 * loads necessary libraries, handles settings and configurations,
 * connects signals and slots, and initializes dialogs.
 *
 * \param parent The parent widget.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      inputData(nullptr)
{
    ui->setupUi(this);
    pMainWindow = this;
    bool serialDll{false};
    try
    {
        if (QLibrary::isLibrary("SerialPorts.dll"))
        {
            QLibrary library("SerialPorts.dll");
            library.load();
            if (library.isLoaded())
            {
                serialPorts =
                    (EnumerateSerialPorts)library.resolve("enumerateSerialPorts");
                serialDll = true;
            }
        }
    }
    catch (...)
    {
        // Handle any exceptions (not specified in detail)
    }

    // Display warning and close application if SerialPorts.dll is not available
    if (!serialDll)
    {
        QMessageBox warningMessage;
        QApplication::beep();
        warningMessage.addButton(QMessageBox::Ok);
        warningMessage.setWindowTitle(QObject::tr("Warning"));
        warningMessage.setText(
            QObject::tr("Serial interfaces is not available."));
        warningMessage.setInformativeText(
            QObject::tr("The application cannot use serial driver because the "
                        "dll package is not available."));
        warningMessage.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                      Qt::WindowTitleHint |
                                      Qt::WindowCloseButtonHint);
        warningMessage.exec();
        this->close();
    }

    // Center the main window on the screen
    CenterToScreen(this);

    // Initialize UI elements and styles
    ui->SerialLedIndicator->setState(false);
    ui->lbConnected->setText(
        tr("RS485 protocol MODBUS ITF off."));
    ui->lbConnected->setStyleSheet(
        "QLabel{font-family: \"Segoe UI\"; font-size: 12pt}");

    // Read settings from registry
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab",
                       QSettings::NativeFormat);

    // LabConditions
    settings.beginGroup("LabConditions");

    if (settings.childKeys().contains("labTemperature")) {
        ui->leTemperature->setText(settings.value("labTemperature").toString());
    } else {
        ui->leTemperature->setText("18");
    }

    if (settings.childKeys().contains("labHumidity")) {
        ui->leHumidity->setText(settings.value("labHumidity").toString());
    } else {
        ui->leHumidity->setText("51");
    }

    if (settings.childKeys().contains("labPressure")) {
        ui->lePressure->setText(settings.value("labPressure").toString());
    } else {
        ui->lePressure->setText("1026");
    }

    // Initialize RS485 settings if not already set
    settings.endGroup();
    settings.beginGroup("RS485");

    const RS485SettingInfo rs485Settings[] =
        {
         {"selectedSerial", 0},
         {"baudRate", 7},
         {"dataBits", 3},
         {"parity", 2},
         {"stopBits", 0},
         {"timeout", 1000},
         {"retriesNumber", 0},
         {"smallScale", 1},
         {"largeScale", 1},
         {"temperature", 1},
         {"emFlowMeter1", 1},
         {"emFlowMeter2", 1},
         {"emFlowMeter3", 1},
         {"waterMeters1_5", 1},
         {"waterMeters6_10", 1},
         {"waterMeters11_15", 1},
         {"waterMeters16_20", 1},
         {"smallScaleValue", 100},
         {"largeScaleValue", 101},
         {"temperatureValue", 102},
         {"emFlowMeter1Value", 103},
         {"emFlowMeter2Value", 104},
         {"emFlowMeter3Value", 105},
         {"waterMeters1_5Value", 103},
         {"waterMeters6_10Value", 104},
         {"waterMeters10_15Value", 103},
         {"waterMeters16_20Value", 104},
         };

    // Ensure all RS485 settings exist in registry
    for (const RS485SettingInfo& setting : rs485Settings) {
        if (!settings.childKeys().contains(setting.key, Qt::CaseInsensitive)) {
            settings.setValue(setting.key, setting.defaultValue);
        }
    }

    settings.endGroup();
    settings.sync();

    // Initialize TableBoard and connect signals to slots
    inputData = new TableBoard(this);
    connect(this, SIGNAL(meterTypeChangedSignal()), inputData,
            SLOT(onTypeMeterChanged()));
    connect(this, SIGNAL(numberOfWaterMetersChangedSignal()), inputData,
            SLOT(onNumberOfWaterMetersChanged()));
    connect(this, SIGNAL(measurementTypeChangedSignal()), inputData,
            SLOT(onMeasurementTypeChanged()));

    // Disable interface radio button (future feature)
    ui->rbInterface->setDisabled(true);

    licenseDialog = new License(this);
    licenseDialog->setModal(true);
    CenterToScreen(licenseDialog);

    helpAbout = new HelpAbout(this);
    helpAbout->setModal(true);
    CenterToScreen(helpAbout);

    interfaceDialog = new Interface(this);
    licenseDialog->setModal(true);
    CenterToScreen(licenseDialog);

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(ui->action_English);
    alignmentGroup->addAction(ui->action_Romana);
    ui->action_English->setCheckable(true);
    ui->action_Romana->setCheckable(true);
    ui->action_Romana->setChecked(true);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint |
                   Qt::Dialog | Qt::WindowTitleHint);
    Translate();
    ReadConfiguration();
    std::string filename = CSV_FLOW_METER_TYPES;
    std::vector < MeterFlowType > meterFlowTypesVector =
        readFlowMeterTypesCSV(filename);

    NUMBER_ENTRIES_METER_FLOW_DB = meterFlowTypesVector.size();

    // Copy elements from meterFlowTypesVector to MeterFlowDB
    for (size_t iter = 0; iter < meterFlowTypesVector.size(); ++iter)
    {
        MeterFlowDB[iter] = meterFlowTypesVector.at(iter);
    }

    // Populate cbNumberOfWaterMeters with numbers from 1 to MAX_NR_WATER_METERS
    for (unsigned iter = 1; iter <= MAX_NR_WATER_METERS; ++iter)
    {
        std::string value = std::to_string(iter);
        ui->cbNumberOfWaterMeters->addItem(value.c_str());
    }

    // Populate cbWaterMeterType with names from MeterFlowDB
    for (unsigned iter = 0; iter < NUMBER_ENTRIES_METER_FLOW_DB; ++iter)
    {
        std::string nameWaterMeter = MeterFlowDB[iter].nameWaterMeter;
        ui->cbWaterMeterType->addItem(nameWaterMeter.c_str());
    }

    // Connect QComboBox signals to custom slots
    connect(ui->cbNumberOfWaterMeters, &QComboBox::currentIndexChanged, this, &MainWindow::onNumberOfWaterMetersChanged);
    connect(ui->cbWaterMeterType, &QComboBox::currentIndexChanged, this, &MainWindow::onMeterTypeChanged);

    // Connect QRadioButton signals to custom slots
    connect(ui->rbVolumetric, &QRadioButton::clicked, this, &MainWindow::onRbVolumeClicked);
    connect(ui->rbGravimetric, &QRadioButton::clicked, this, &MainWindow::onRbGavritmetricClicked);
    connect(ui->rbManual, &QRadioButton::clicked, this, &MainWindow::onRbManualClicked);
    connect(ui->rbInterface, &QRadioButton::clicked, this, &MainWindow::onRbInterfaceClicked);

    // Connect QLineEdit signals to custom slots
    connect(ui->leTemperature, &QLineEdit::textChanged, this, &MainWindow::onAmbientTemperatureTextChanged);
    connect(ui->lePressure, &QLineEdit::textChanged, this, &MainWindow::onAthmosphericPressureTextChanged);
    connect(ui->leHumidity, &QLineEdit::textChanged, this, &MainWindow::onRelativeAirHumidityTextChanged);

    // Connect QPushButton signals to custom slots
    connect(ui->pbNewSession, &QPushButton::clicked, this, &MainWindow::onNewSessionClicked);
    connect(ui->pbExitApplication, &QPushButton::clicked, this, &MainWindow::onExitApplication);

    // Connect QAction signals to custom slots
    connect(ui->action_License, SIGNAL(triggered()), this, SLOT(onShowLicense()));
    connect(ui->action_ExitApp, SIGNAL(triggered()), this, SLOT(onExitApplication()));
    connect(ui->action_StartSession, SIGNAL(triggered()), this, SLOT(onNewSessionClicked()));
    connect(ui->action_WaterDensity, SIGNAL(triggered()), this, SLOT(onWaterDensityPage()));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(onHelpAbout()));
    connect(ui->action_General_Description, SIGNAL(triggered()), this, SLOT(onGeneralDescription()));

    // Added for future improvements
    ui->action_General_Description->setVisible(false);

    // Connect QAction signals for language and serial port configuration
    connect(ui->action_Romana, SIGNAL(triggered()), this, SLOT(onSetRomanian()));
    connect(ui->action_English, SIGNAL(triggered()), this, SLOT(onSetEnglish()));
    connect(ui->action_Configure_Serial_Port, SIGNAL(triggered()), this, SLOT(onPortSettings()));
/*
    QDoubleValidator *validatorTemperature = new QDoubleValidator(0.0,
            100.0, 5, ui->leTemperature);
    ui->leTemperature->setValidator(validatorTemperature);

    QDoubleValidator *validatorHumidity = new QDoubleValidator(0.0, 100.0,
            5, ui->leHumidity);
    ui->leHumidity->setValidator(validatorHumidity);

    QDoubleValidator *validatorPressure = new QDoubleValidator(500.0,
            1500.0, 5, ui->lePressure);
    ui->lePressure->setValidator(validatorPressure);
*/
    if (optionsConfiguration.find("maximum") !=
            optionsConfiguration.end())
    {
        size_t index = std::stoi(optionsConfiguration["maximum"]);
        ui->cbNumberOfWaterMeters->setCurrentIndex(index - 1);
    }
    else
    {
        ui->cbNumberOfWaterMeters->setCurrentIndex(0);
    }
    ui->rbGravimetric->setChecked(true);
    ui->rbManual->setChecked(true);

    ui->cbWaterMeterType->setStyleSheet("QComboBox { background: rgb(240, 255, 240); color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0); }");
    ui->cbNumberOfWaterMeters->setStyleSheet("QComboBox { background: rgb(240, 255, 240); color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0); }");

    ui->leTemperature->setStyleSheet("QLineEdit { background: rgb(240, 255, 240); selection-background-color: rgb(0, 0, 0); }");
    ui->leHumidity->setStyleSheet("QLineEdit { background: rgb(240, 255, 240); color: rgb(0, 0, 0); }");
    ui->lePressure->setStyleSheet("QLineEdit { background: rgb(240, 255, 240); color: rgb(0, 0, 0); }");

    SelectMeterComboBox();
    // 485 Indicator State
    ui->SerialLedIndicator->hide();
    ui->lbConnected->hide();
    installEventFilter(this);
}

/**
 * \brief Destructor for MainWindow class.
 *
 * Cleans up resources associated with the MainWindow.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * \brief Slot invoked when the meter type is changed.
 *
 * \param index The index of the selected meter type (unused).
 *
 * This function selects the meter combo box and emits the meterTypeChangedSignal.
 */
void MainWindow::onMeterTypeChanged(int index)
{
    Q_UNUSED(index);
    SelectMeterComboBox();
    emit meterTypeChangedSignal();
}

/**
 * \brief Slot invoked when the number of water meters is changed.
 *
 * \param index The index of the selected number of water meters (unused).
 *
 * This function updates the selectedInfo.entriesNumber based on the current
 * text in cbNumberOfWaterMeters and emits the numberOfWaterMetersChangedSignal.
 */
void MainWindow::onNumberOfWaterMetersChanged(int index)
{
    Q_UNUSED(index);
    selectedInfo.entriesNumber = ui->cbNumberOfWaterMeters->currentText().toInt();
    emit numberOfWaterMetersChangedSignal();
}

/**
 * \brief Slot invoked when the "New Session" button is clicked.
 *
 * If `inputData` is not already initialized, it creates a new TableBoard instance,
 * connects signals to slots in `inputData`, and updates selected information.
 * Then it sets the fixed size, calculates the center position on the primary screen,
 * and displays the window.
 */
void MainWindow::onNewSessionClicked()
{
    if (!this->inputData)
    {
        // Create new TableBoard instance if not already initialized
        inputData = new TableBoard(this);

        // Connect signals to slots in inputData
        connect(this, SIGNAL(meterTypeChangedSignal()), inputData,
                SLOT(onTypeMeterChanged()));
        connect(this, SIGNAL(numberOfWaterMetersChangedSignal()), inputData,
                SLOT(onNumberOfWaterMetersChanged()));
        connect(this, SIGNAL(measurementTypeChangedSignal()), inputData,
                SLOT(onMeasurementTypeChanged()));
    }

    // Update selected information (assuming this function exists in your class)
    updateSelectedInfo();

    // Set the fixed size of the window
    int fixedWidth = MAIN_WINDOW_WIDTH;    // Set your fixed width
    int fixedHeight = MAIN_WINDOW_HEIGHT;  // Set your fixed height
    this->inputData->setFixedSize(fixedWidth, fixedHeight);

    // Calculate the center position using the primary screen
    QScreen *primaryScreen = QApplication::primaryScreen();
    QRect availableGeometry = primaryScreen->availableGeometry();
    int x = (availableGeometry.width() - fixedWidth) / 2;
    int y = (availableGeometry.height() - fixedHeight) / 2;

    // Set the position and display properties for the window
    this->inputData->move(x, y);         // Set the window position
    this->inputData->setModal(false);    // Set the window to non-modal
    this->inputData->show();             // Display the window
}

/**
 * \brief Slot invoked when the application exit action is triggered.
 *
 * If `inputData` is initialized, it sets it to nullptr (without deleting to avoid
 * double deletion if already deleted elsewhere). Then, it closes the main window.
 */
void MainWindow::onExitApplication()
{
    if (inputData)
    {
        // Assuming you do not want to delete inputData to avoid double deletion.
        inputData = nullptr;
    }
    this->close();
}

/**
 * \brief Slot invoked when the "Gravimetric" radio button is clicked.
 *
 * Updates the selectedInfo structure with the states of the "Volumetric" and "Gravimetric"
 * radio buttons. Then, emits the measurementTypeChangedSignal to notify listeners.
 */
void MainWindow::onRbGavritmetricClicked()
{
    selectedInfo.rbVolumetric = ui->rbVolumetric->isChecked();
    selectedInfo.rbGravimetric_new = ui->rbGravimetric->isChecked();
    emit measurementTypeChangedSignal();
}

/**
 * \brief Slot invoked when the "Volumetric" radio button is clicked.
 *
 * Updates the selectedInfo structure with the states of the "Volumetric" and "Gravimetric"
 * radio buttons. Then, emits the measurementTypeChangedSignal to notify listeners.
 */
void MainWindow::onRbVolumeClicked()
{
    selectedInfo.rbVolumetric = ui->rbVolumetric->isChecked();
    selectedInfo.rbGravimetric_new = ui->rbGravimetric->isChecked();
    emit measurementTypeChangedSignal();
}

/**
 * \brief Slot invoked when the "Manual" radio button is clicked.
 *
 * Updates the selected information structure (`selectedInfo`) based on the
 * state of the "Manual" and "Interface" radio buttons.
 *
 * \note This function assumes `selectedInfo` is a member variable representing
 *       selected options or settings.
 */
void MainWindow::onRbManualClicked()
{
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbInterface = ui->rbInterface->isChecked();
}

/**
 * \brief Slot invoked when the "Interface" radio button is clicked.
 *
 * Currently does nothing and serves as a placeholder for future functionality
 * related to the "Interface" radio button.
 */
void MainWindow::onRbInterfaceClicked()
{
    // Placeholder function
    // This slot is intended for future use related to the "Interface" radio button.
}

/**
 * \brief Slot invoked when the text in the ambient temperature QLineEdit (`ui->leTemperature`) changes.
 *
 * Retrieves the updated ambient temperature, atmospheric pressure, and relative air humidity
 * from their respective QLineEdit fields (`ui->leTemperature`, `ui->lePressure`, `ui->leHumidity`).
 * Updates `selectedInfo` with the new values and saves them to application settings.
 *
 * \note This function assumes the use of `selectedInfo` to store the retrieved values.
 */
void MainWindow::onAmbientTemperatureTextChanged()
{
    // Retrieve and update ambient temperature
    QString temperatureText = ui->leTemperature->text();
    selectedInfo.ambientTemperature = temperatureText.toStdString();

    // Retrieve and update atmospheric pressure
    QString pressureText = ui->lePressure->text();
    selectedInfo.athmosphericPressure = pressureText.toStdString();

    // Retrieve and update relative air humidity
    QString humidityText = ui->leHumidity->text();
    selectedInfo.relativeAirHumidity = humidityText.toStdString();

    // Update settings with the new values
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("LabConditions");
    settings.setValue("labTemperature", temperatureText);
    settings.setValue("labPressure", pressureText);
    settings.setValue("labHumidity", humidityText);
    settings.endGroup();
    settings.sync();
}

/**
 * \brief Slot invoked when the relative air humidity text field changes.
 *
 * Retrieves the text from the relative air humidity QLineEdit and updates
 * selectedInfo.relativeAirHumidity with its string representation.
 * Similarly, retrieves text from temperature and pressure QLineEdit fields
 * and updates selectedInfo.ambientTemperature and selectedInfo.athmosphericPressure
 * respectively. Updates settings with the new values.
 */
void MainWindow::onRelativeAirHumidityTextChanged()
{
    // Retrieve and update ambient temperature
    QString temperatureText = ui->leTemperature->text();
    selectedInfo.ambientTemperature = temperatureText.toStdString();

    // Retrieve and update atmospheric pressure
    QString pressureText = ui->lePressure->text();
    selectedInfo.athmosphericPressure = pressureText.toStdString();

    // Retrieve and update relative air humidity
    QString humidityText = ui->leHumidity->text();
    selectedInfo.relativeAirHumidity = humidityText.toStdString();

    // Update settings with the new values
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("LabConditions");
    settings.setValue("labTemperature", temperatureText);
    settings.setValue("labPressure", pressureText);
    settings.setValue("labHumidity", humidityText);
    settings.endGroup();
    settings.sync();
}

/**
 * \brief Slot invoked when the atmospheric pressure text field changes.
 *
 * Retrieves the text from the atmospheric pressure QLineEdit and updates
 * selectedInfo.athmosphericPressure with its string representation.
 * Similarly, retrieves text from temperature and relative air humidity
 * QLineEdit fields and updates selectedInfo.ambientTemperature and
 * selectedInfo.relativeAirHumidity respectively. Updates settings with
 * the new values.
 */
void MainWindow::onAthmosphericPressureTextChanged()
{
    // Retrieve and update ambient temperature
    QString temperatureText = ui->leTemperature->text();
    selectedInfo.ambientTemperature = temperatureText.toStdString();

    // Retrieve and update atmospheric pressure
    QString pressureText = ui->lePressure->text();
    selectedInfo.athmosphericPressure = pressureText.toStdString();

    // Retrieve and update relative air humidity
    QString humidityText = ui->leHumidity->text();
    selectedInfo.relativeAirHumidity = humidityText.toStdString();

    // Update settings with the new values
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("LabConditions");
    settings.setValue("labTemperature", temperatureText);
    settings.setValue("labPressure", pressureText);
    settings.setValue("labHumidity", humidityText);
    settings.endGroup();
    settings.sync();
}

/**
 * \brief Opens the general description manual based on the selected language.
 *
 * If the selected language is Romanian (ROMANIAN == selectedInfo.selectedLanguage),
 * attempts to open the manual file (MANUAL_RO) located in the application's directory.
 * If the file exists, it opens it using QDesktopServices::openUrl().
 *
 * This function has no effect if the selected language is not Romanian or if the manual
 * file does not exist.
 */
void MainWindow::onGeneralDescription()
{
    if (ROMANIAN == selectedInfo.selectedLanguage)
    {
        QString fileName = MANUAL_RO;   // Filename of the Romanian manual
        QString appDirPath = QCoreApplication::applicationDirPath();   // Get application directory path
        QString filePath = QDir(appDirPath).filePath(fileName);   // Construct full file path

        // Check if the file exists
        if (QFile::exists(filePath)) {
            QUrl fileUrl = QUrl::fromLocalFile(filePath);   // Create a URL from local file path
            QDesktopServices::openUrl(fileUrl);   // Open the file URL using default application
        }
    }

    return;
}

/**
 * \brief Opens a temporary HTML file displaying water density vs temperature data.
 *
 * Generates an HTML table showing water density (ρ) in kg/m³ and volume correction factor (K)
 * for temperatures from 0 to 100°C with a step of 0.1°C. The table is based on quadratic interpolation
 * functions and adjusts content based on the selected language (Romanian or English).
 *
 * After generating the HTML file, it opens it using the default web browser and removes the temporary file afterwards.
 */
void MainWindow::onWaterDensityPage()
{
    // Create a temporary HTML file path
    QString htmlFilePath = QDir::temp().filePath("water_density.html");

    // Open the HTML file for writing
    std::ofstream densityHtmlFile(htmlFilePath.toStdString());
    if (!densityHtmlFile.is_open()) {
        // Handle error opening file
        return;
    }

    std::stringstream output;

    // HTML header and style
    output << R"(
        <!DOCTYPE html>
        <html>
            <head>
                <title>Water Density vs Temperature</title>
                <style>
                    body {
                        -webkit-user-select: none;  /* Chrome all / Safari all */
                        -moz-user-select: none;     /* Firefox all */
                        -ms-user-select: none;      /* IE 10+ */
                        user-select: none;          /* Likely future */
                    }
                    .black { color: black; }
                    .green { color: green; }
                    .blue { color: blue; }
                    h2 { font-size: 15px; } /* Adjust font size for the first lines */
                    pre { font-size: 20px; } /* Adjust font size for the columns */
                </style>
            </head>
            <body>
                <div>
                    <pre><h2 style="color:DodgerBlue;">)";

    // Language-specific description
    if (ROMANIAN == selectedInfo.selectedLanguage) {
        output << "Tabelul de mai jos reprezinta densitatea apei in kg/mc "
                  "si factorul de corectie volum functie de temperatura intre 0 si 100°C</br>"
                  "cu un pas de 0.1°C la presiune normala (1013.25 kPa). Aceste valori "
                  "sunt generate plecand de la datele existente in aplicatie.</pre></br>";
    } else {
        output << "The table below shows the density of water in kg/mc and "
                  "volume correction factor for different temperatures between 0 and 100°C with</br>"
                  "the step of 0.1°C under normal pressure (1013.25 kPa). "
                  "These values ​​are generated starting from the existing database in the application.</pre></br>";
    }

    // Table header
    output << R"(
        <pre><span class="black">&nbsp;&nbsp;&nbsp;T [°C]</span>&nbsp;&nbsp;<span class="green">ρ[kg/m³]</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="blue">K</span></pre>
        <hr />
     )";

    // Generate table rows with temperature, density, and coefficient values
    for (int i = 0; i <= 1000; ++i) {
        double temperature = 0.1 * i;
        double density = quadraticInterpolationTemperature(temperature, 998.2009);
        double coefficient = quadraticInterpolationVolumeCorrection(temperature);

        // Append row to HTML output
        output << "<pre><span class=\"black\">" << std::fixed << std::setprecision(1)
               << "&nbsp;&nbsp;&nbsp;&nbsp;" << temperature << "</span>&nbsp;&nbsp;&nbsp;&nbsp;<span class=\"green\">"
               << std::setprecision(4) << density << "</span>&nbsp;&nbsp;&nbsp;<span class=\"blue\">"
               << std::setprecision(5) <<  coefficient << "</span></pre>";

        // Insert horizontal rule every 10 rows for readability
        if ((i + 1) % 10 == 0) {
            output << "<hr />\n";
        }
    }

    // Close HTML body and document
    output << R"(
                </h2>
                </div>
            </body>
        </html>
    )";

    // Write HTML content to file and close it
    densityHtmlFile << output.str() << std::endl;
    densityHtmlFile.close();

    // Open the generated HTML file in the default web browser
    QDesktopServices::openUrl(QUrl::fromLocalFile(htmlFilePath));

    // Remove the temporary HTML file
    QFile::remove(htmlFilePath);
}

/**
 * \brief Shows the license dialog.
 *
 * Displays the license dialog when called.
 */
void MainWindow::onShowLicense()
{
    licenseDialog->show();
}

/**
 * \brief Shows the help/about dialog.
 *
 * Displays the help/about dialog when called.
 */
void MainWindow::onHelpAbout()
{
    helpAbout->show();
}

/**
 * \brief Opens port settings or shows a warning if no serial interfaces are detected.
 *
 * Checks if serial ports are available. If no serial interfaces are detected,
 * it shows a warning message and defaults the manual radio button. Otherwise,
 * it shows the interface dialog for port settings.
 */
void MainWindow::onPortSettings()
{
    // Update selectedInfo based on UI state
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbInterface = ui->rbInterface->isChecked();

    // Check for available serial ports
    const wchar_t *serial = serialPorts();
    if (!std::wcslen(serial))
    {
        // Show warning message if no serial interfaces are found
        QMessageBox warningMessage;
        QApplication::beep();
        warningMessage.addButton(QMessageBox::Ok);
        warningMessage.setWindowTitle(QObject::tr("Warning"));
        warningMessage.setText(QObject::tr("Serial interfaces."));
        warningMessage.setInformativeText(
            QObject::tr("The application did not detect any serial interface "
                        "on this computer."));
        warningMessage.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                      Qt::WindowTitleHint |
                                      Qt::WindowCloseButtonHint);
        warningMessage.exec();

        // Set manual radio button as default
        ui->rbManual->setChecked(true);
    }
    else
    {
        // Show the interface dialog for port settings
        interfaceDialog->show();
    }
}

/**
 * \brief Sets the application language to Romanian.
 *
 * Loads and installs the Romanian translation file ("meter_ro_RO.qm").
 * Translates UI elements in various components and updates the selected language.
 */
void MainWindow::onSetRomanian()
{
    QString qmPath = qApp->applicationDirPath() + "/translations";
    QString translationFile = "meter_ro_RO.qm";

    // Remove existing translator if it exists
    if (appTranslator)
    {
        qApp->removeTranslator(appTranslator);
        delete appTranslator;
        appTranslator = nullptr;
    }

    // Create new translator and load the Romanian translation file
    appTranslator = new QTranslator(nullptr);
    if (appTranslator->load(qmPath + "/" + translationFile))
    {
        // Install the translator to the application
        qApp->installTranslator(appTranslator);

        // Translate UI elements in various components
        Translate(); // Assuming Translate() function handles translation in MainWindow
        if (inputData) inputData->Translate(); // Translate UI in inputData if available
        if (licenseDialog) licenseDialog->Translate(); // Translate UI in licenseDialog if available
        if (helpAbout) helpAbout->Translate(); // Translate UI in helpAbout if available
        if (interfaceDialog) interfaceDialog->Translate(); // Translate UI in interfaceDialog if available

        // Set the selected language to Romanian
        selectedInfo.selectedLanguage = ROMANIAN;
    }
    else
    {
        // Clean up translator if loading fails
        delete appTranslator;
        appTranslator = nullptr;
    }
}

/**
 * \brief Sets the application language to English.
 *
 * Loads and installs the English translation file ("meter_en_EN.qm").
 * Translates UI elements in various components and updates the selected language.
 */
void MainWindow::onSetEnglish()
{
    QString qmPath = qApp->applicationDirPath() + "/translations";
    QString translationFile = "meter_en_EN.qm";

    // Remove existing translator if it exists
    if (appTranslator)
    {
        qApp->removeTranslator(appTranslator);
        delete appTranslator;
        appTranslator = nullptr;
    }

    // Create new translator and load the English translation file
    appTranslator = new QTranslator(nullptr);
    if (appTranslator->load(qmPath + "/" + translationFile))
    {
        // Install the translator to the application
        qApp->installTranslator(appTranslator);

        // Translate UI elements in various components
        Translate(); // Assuming Translate() function handles translation in MainWindow
        if (inputData) inputData->Translate(); // Translate UI in inputData if available
        if (licenseDialog) licenseDialog->Translate(); // Translate UI in licenseDialog if available
        if (helpAbout) helpAbout->Translate(); // Translate UI in helpAbout if available
        if (interfaceDialog) interfaceDialog->Translate(); // Translate UI in interfaceDialog if available

        // Set the selected language to English
        selectedInfo.selectedLanguage = ENGLISH;
    }
    else
    {
        // Clean up translator if loading fails
        delete appTranslator;
        appTranslator = nullptr;
    }
}

/**
 * \brief Handles the mouse press event.
 *
 * Activates the main window when a mouse press event occurs.
 *
 * \param event The mouse event object.
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    activateWindow();
    QMainWindow::mousePressEvent(event);
}

/**
 * \brief Handles the close event of the main window.
 *
 * Deletes the `inputData` object if it exists and accepts the close event.
 *
 * \param event The close event object.
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (inputData)
    {
        delete inputData;
        inputData = nullptr;
    }
    event->accept();
}

/**
 * \brief Centers a widget to the screen.
 *
 * Moves the given widget to the center of the primary screen.
 *
 * \param widget The widget to be centered.
 */
void MainWindow::CenterToScreen(QWidget *widget)
{
    if (!widget)
        return;

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int widgetWidth = widget->width();
    int widgetHeight = widget->height();

    int xPosition = screenGeometry.center().x() - widgetWidth / 2;
    int yPosition = screenGeometry.center().y() - widgetHeight / 2;

    widget->move(xPosition, yPosition);
}
