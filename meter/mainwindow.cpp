/**
 * \file mainwindow.cpp
 * \brief Implementation file for the MainWindow class.
 *
 * This file contains the implementations of member functions and slots
 * for the MainWindow class. It handles the main window of the application,
 * including initialization, event handling, and slot implementations.
 * md5 generator: https://www.md5hashgenerator.com/
 *
 * \author Constantin
 * \date Insert date
 */

// C++ Standard Library headers
#include <algorithm>
#include <filesystem>  ///< Provides facilities to manipulate and query file systems and their components.
#include <fstream>     ///< Input/output stream class to operate on files.
#include <iomanip>     ///< Manipulators for formatting output.
#include <map>         ///< Associative containers that store elements in a mapped fashion.
#include <sstream>     ///< Implements input/output operations on memory-based streams.

// Qt headers
#include <QDesktopServices>  ///< Access to the desktop services such as opening a URL.
#include <QDir>              ///< Provides access to directory structures and their contents.
#include <QKeyEvent>         ///< Provides key event handling.
#include <QLibrary>          ///< Platform-independent library loading and function resolution.
#include <QLineEdit>         ///< Single-line text editor widget with input validation and styling.
#include <QList>
#include <QMap>              ///< Associative container that provides a dictionary-like interface.
#include <QMessageBox>  ///< Modal dialog for informing the user or for asking the user a question and receiving an answer.
#include <QPushButton>  ///< Provides push button widget.
#include <QSettings>    ///< Persistent platform-independent application settings.
#include <QStatusBar>
#include <QTimer>      ///< Provides timers for single-shot and repeating actions.
#include <QValidator>  ///< Base class for all validators that can be easily attached to input widgets.

// Windows-specific headers
#include <windows.h>  ///< Main Windows SDK header providing core Windows APIs.

// Custom headers
#include "definitions.h"      ///< Custom application-specific definitions.
#include "flow-meter-type.h"  ///< Header defining flow meter types.
#include "mainwindow.h"       ///< Header for the main application window.
#include "md5.h"              ///< Header for MD5 hashing functionality.
#include "ui_mainwindow.h"    ///< User interface header generated from Qt Designer.
#include "waterdensity.h"     ///< Header for water density calculations.

// Additional Qt headers (unique includes only)
#include <QFile>                ///< Provides functions to read from and write to files.
#include <QUrl>                 ///< Represents a URL.
#include <QRegularExpression>   ///< Provides regular expression pattern matching.
#include <QTextStream>          ///< Provides a convenient interface for reading and writing text.
#include <QStringConverter>     ///< Provides encoding and decoding of text.

extern QTranslator* appTranslator;
MainWindow* pMainWindow;

std::wstring ExePath() {
    TCHAR buffer[MAX_PATH] = {0};
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

/**
 * \brief Sets default configuration values for optionsConfiguration.
 *
 * This function clears the optionsConfiguration map and initializes default
 * values for various configuration keys:
 * - "company": Default value is "Elcost Company".
 * - "archive": Default path is "C:/Stand/Fise".
 * - "volume_correction": Default value is "CLASSIC_VOLUME_CORRECTION".
 * - "certificate": Default value is "CE 06.02-2025/15".
 * - "density_20": Default value is "998.2009".
 * - "control": Default value is "004b3d5b6f320ab986035bf8252ea845".
 */
void MainWindow::SetDefaultConfiguration() {
    optionsConfiguration.clear();
    optionsConfiguration["company"] = "Elcost Company";
    optionsConfiguration["archive"] = "C:/Stand/Fise";
    optionsConfiguration["volume_correction"] = "CLASSIC_VOLUME_CORRECTION";
    optionsConfiguration["certificate"] = "CE 06.02-2025/15";
    optionsConfiguration["density_20"] = "998.2009";
    optionsConfiguration["control"] = "004b3d5b6f320ab986035bf8252ea845";
}

/**
 * \brief Reads and parses configuration settings from a file.
 *
 * This function reads the configuration file specified by 'watermeters.conf'
 * located in the application's directory. It parses key-value pairs separated
 * by '=' and terminated by the '>' character.
 *
 * After loading the configuration, it validates the MD5 checksum formed by
 * concatenating the values of the following fields:
 *
 *     company + volume_correction => MD5
 *
 * The resulting string is hashed using MD5 and compared against the stored
 * checksum value under the 'control' key.
 *
 * If the configuration file cannot be opened, required keys are missing,
 * or the MD5 validation fails, default configuration values are applied using
 * SetDefaultConfiguration().
 *
 * Example configuration file format:
 *
 *     company=Compania de Apa Braila>
 *     archive=C:/Stand/Fise>
 *     volume_correction=CLASSIC_VOLUME_CORRECTION>
 *     certificate=CE 06.02-355/15>
 *     density_20=998.2009>
 *     control=f1807e24ccba79a76baa08194b7fa9bf>
 */
void MainWindow::ReadConfiguration() {
    std::wstring pathToConfig = ExePath() + L"\\watermeters.conf";
    std::ifstream inConfigurationFile(pathToConfig.c_str());

    // If the configuration file cannot be opened, fall back to defaults
    if (!inConfigurationFile.is_open()) {
        SetDefaultConfiguration();

        QString msg = QString("The configuration file could not be opened. "
                              "Default settings will be used.");
        QMessageBox box(QMessageBox::Critical, "Warning", msg, QMessageBox::Ok, nullptr);
        return;
    }

    // Parse configuration lines of the form: key=value>
    std::string line;
    while (std::getline(inConfigurationFile, line)) {
        auto posEq = line.find('=');
        auto posGt = line.find('>');

        // Ignore malformed lines
        if (posEq == std::string::npos || posGt == std::string::npos || posGt <= posEq)
            continue;

        std::string key = line.substr(0, posEq);
        std::string value = line.substr(posEq + 1, posGt - posEq - 1);

        if (!key.empty())
            optionsConfiguration[key] = value;
    }

    // Validate presence of all mandatory configuration keys
    if (optionsConfiguration.find("company") == optionsConfiguration.end() ||
        optionsConfiguration.find("archive") == optionsConfiguration.end() ||
        optionsConfiguration.find("volume_correction") == optionsConfiguration.end() ||
        optionsConfiguration.find("certificate") == optionsConfiguration.end() ||
        optionsConfiguration.find("density_20") == optionsConfiguration.end() ||
        optionsConfiguration.find("control") == optionsConfiguration.end()) {
        SetDefaultConfiguration();
        QString msg = QString("The configuration file does not contain all "
                              "mandatory entries. Default settings will be used.");
        QMessageBox box(QMessageBox::Critical, "Warning", msg, QMessageBox::Ok, nullptr);
        return;
    }

    // Validate configuration integrity using MD5 checksum
    std::string md5Read = optionsConfiguration["control"];
    std::string wordControl = optionsConfiguration["company"] + optionsConfiguration["volume_correction"];
    std::string md5Calculate = md5(wordControl);

    if (md5Read != md5Calculate) {
        SetDefaultConfiguration();
        QString msg = QString("The configuration file failed the MD5 integrity check. "
                              "Default settings will be used.");
        QMessageBox box(QMessageBox::Critical, "Warning", msg, QMessageBox::Ok, nullptr);
        return;
    }

    std::string volumeCorrectionType = optionsConfiguration["volume_correction"];

    if (volumeCorrectionType != "CLASSIC_VOLUME_CORRECTION" && volumeCorrectionType != "INM_VOLUME_CORRECTION" &&
        volumeCorrectionType != "ELCOST_VOLUME_CORRECTION") {
        QString msg = QString("Unknown volume correction type: %1\n\nAllowed values are:\n%2\n%3\n%4")
                          .arg(QString::fromStdString(volumeCorrectionType))
                          .arg("  CLASSIC_VOLUME_CORRECTION")
                          .arg("  INM_VOLUME_CORRECTION")
                          .arg("  ELCOST_VOLUME_CORRECTION");

        QMessageBox box(QMessageBox::Critical, "Error", msg, QMessageBox::Ok, nullptr);
        return;
    }

    // Configuration is valid; keep loaded values
}

/**
 * \brief Structure to hold information about RS 485/422 settings.
 *
 * This struct defines a key-value pair where:
 * - `key` is a pointer to a constant character array representing the setting's identifier.
 * - `defaultValue` is a QVariant storing the default value associated with the setting.
 */
struct serialSettingInfo {
    const char* key;              ///< Pointer to a constant character array representing the setting's identifier.
    const QVariant defaultValue;  ///< QVariant storing the default value associated with the setting.
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
void MainWindow::setLabelValue(QLabel* label, double value, int precision) {
    QString text = QString::number(value, 'f', precision);  // Format the double value with fixed precision
    label->setText(text);                                   // Set the text of the label to the formatted value
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
void MainWindow::updateSelectedInfo() {
    // Update selectedInfo with parameters from optionsConfiguration
    try {
        selectedInfo.density_20 = std::stof(optionsConfiguration["density_20"]);
    } catch (const std::exception& e) {
        // Set default or show error
        selectedInfo.density_20 = 998.2009;
        qWarning() << "Invalid density_20 value:" << e.what();
    }
    selectedInfo.pathResults = optionsConfiguration["archive"];
    selectedInfo.certificate = optionsConfiguration["certificate"];
    // The new version has just the option 20 for entries number
    selectedInfo.entriesNumber = ui->cbNumberOfWaterMeters->currentText().toInt();
    // selectedInfo.entriesNumber = MAX_NUMBER_FLOW_METERS;

    // Read lab conditions from application settings
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.beginGroup("LabConditions");

    // Read and set ambient temperature
    selectedInfo.ambientTemperature = settings.value("labTemperature", "18").toString().toStdString();

    // Read and set relative air humidity
    selectedInfo.relativeAirHumidity = settings.value("labHumidity", "51").toString().toStdString();

    // Read and set atmospheric pressure
    selectedInfo.atmosphericPressure = settings.value("labPressure", "1026").toString().toStdString();

    settings.endGroup();
    settings.sync();

    // Get selected water meter index from UI
    int selectedWaterMeter = ui->cbWaterMeterType->currentIndex();
    if (selectedWaterMeter < 0 || static_cast<size_t>(selectedWaterMeter) >= NUMBER_ENTRIES_METER_FLOW_DB) {
        qWarning() << "Invalid water meter index:" << selectedWaterMeter;
        return;
    }

    // Retrieve meter flow information from MeterFlowDB
    const auto& meterFlowInfo = MeterFlowDB[selectedWaterMeter];

    // Update selectedInfo with meter flow information
    selectedInfo.nameWaterMeter = meterFlowInfo.nameWaterMeter;
    selectedInfo.nominalDiameter = meterFlowInfo.nominalDiameter;
    selectedInfo.nominalFlow = meterFlowInfo.nominalFlow;
    selectedInfo.maximumFlow = meterFlowInfo.maximumFlow;
    selectedInfo.transitionFlow = meterFlowInfo.transitionFlow;
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
void MainWindow::SelectMeterComboBox() {
    // Update selectedInfo with information based on the selected water meter
    updateSelectedInfo();

    // Create directories for results and input data
    try {
        std::filesystem::create_directories(selectedInfo.pathResults);
        std::filesystem::create_directories(selectedInfo.pathResults + "/inputData");
    } catch (const std::filesystem::filesystem_error& e) {
        QMessageBox::warning(this, tr("Directory Error"),
                             tr("Failed to create directory: %1").arg(QString::fromStdString(e.what())));
    }

    // Update labels in the UI with selectedInfo values
    setLabelValue(ui->lbNominalDiameterCurrent, selectedInfo.nominalDiameter, 0);
    setLabelValue(ui->lbMaximumFlowCurrent, selectedInfo.maximumFlow, 2);
    setLabelValue(ui->lbNominalFlowCurrent, selectedInfo.nominalFlow, 2);
    setLabelValue(ui->lbTransitionFlowCurrent, selectedInfo.transitionFlow, 2);  // Corrected typo
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
void MainWindow::Translate() {
    // Retranslate UI elements from .ui file (tooltips, etc.)
    ui->retranslateUi(this);

    // Translate window title
    this->setWindowTitle(tr("WStreamLab - Dashboard"));

    // Translate menu titles
    ui->menu_File->setTitle(tr("File"));
    ui->menu_Language->setTitle(tr("Language"));
    ui->menu_Help->setTitle(tr("Help"));

    // Translate actions
    ui->action_StartSession->setText(tr("Start Session"));
    ui->action_ExitApp->setText(tr("Exit"));
    ui->action_English->setText(tr("English"));
    ui->action_Romana->setText(tr("Română"));
    ui->action_General_Description->setText(tr("General Description"));
    ui->action_Verification_Method->setText(tr("Verification Method"));
    ui->action_WaterDensity->setText(tr("Water Density"));
    ui->action_License->setText(tr("License"));
    ui->action_About->setText(tr("About"));

    // Translate labels
    ui->lbWaterMeterType->setText(tr("Type of water meter:"));
    ui->lbNumberOfWaterMeters->setText(tr("Number of water meters:"));
    ui->lbTemperature->setText(tr("Temperature:"));
    ui->lbPressure->setText(tr("Atmospheric pressure:"));
    ui->lbHumidity->setText(tr("Relative air humidity:"));
    ui->lbTab5->setText(tr("[mbar]"));
    ui->lbTab3->setText(tr("°C"));  // Degrees Celsius symbol
    ui->lbTab4->setText(tr("[%]"));

    // Translate group box titles
    ui->gbInputData->setTitle(tr("Configuration"));
    ui->gbMeasurementMethod->setTitle(tr("Measurement method"));
    ui->gbReadMethod->setTitle(tr("Read method"));
    ui->gbWaterMeterFeatures->setTitle(tr("Water meter features"));

    // Translate radio buttons
    ui->rbVolumetric->setText(tr("Volumetric"));
    ui->rbGravimetric->setText(tr("Gravimetric"));
    ui->rbManual->setText(tr("Manual Mode Operation"));
    ui->rbInterface->setText(tr("Interface MODBUS operation"));

    // Translate labels in Water Meter Features group
    ui->lbNominalDiameter->setText(tr("Nominal diameter:"));
    ui->lbMaximumFlow->setText(tr("Maximum flow:"));
    ui->lbNominalFlow->setText(tr("Nominal flow:"));
    ui->lbTransitionFlow->setText(tr("Transition flow:"));
    ui->lbMinimumFlow->setText(tr("Minimum flow:"));
    ui->lbMaximumError->setText(tr("Maximum error:"));
    ui->lbNominalError->setText(tr("Nominal error:"));
    ui->lbNominalDiameterUnit->setText(tr("[mm]"));
    ui->lbMaximumFlowUnit->setText(tr("[L/h]"));
    ui->lbNominalFlowUnit->setText(tr("[L/h]"));
    ui->lbTransitionFlowUnit->setText(tr("[L/h]"));
    ui->lbMinimumFlowUnit->setText(tr("[L/h]"));
    ui->lbMaximumErrorUnit->setText(tr("[%]"));
    ui->lbNominalErrorUnit->setText(tr("[%]"));

    // Translate push buttons
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
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), inputData(nullptr), licenseDialog(new License(this)),
      helpAbout(new HelpAbout(this)), interfaceDialog(new Interface(this)), alignmentGroup(new QActionGroup(this)) {
    ui->setupUi(this);

#ifdef BUILD_WITHOUT_RS_485_422_MODBUS
    // Remove menuInterface from the menu bar
    ui->menubar->removeAction(ui->menuInterface->menuAction());
    ui->rbInterface->setEnabled(false);
#endif

    // Remove maximize button from window and make non-resizable
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint |
                   Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setFixedSize(580, 620);

    // Initialize status bar explicitly with permanent label
    statusBar()->setSizeGripEnabled(false);
    statusBar()->setVisible(true);

    // Create a permanent label in the status bar
    statusBarLabel = new QLabel(this);
    statusBarLabel->setStyleSheet("QLabel { padding-left: 5px; }");
    statusBar()->addPermanentWidget(statusBarLabel, 1);  // Stretch factor 1

    // Set Romanian as default language at startup
    onSetRomanian();

    // Read configuration settings
    ReadConfiguration();

    // Set main window pointer and apply style sheet
    pMainWindow = this;
    pMainWindow->setStyleSheet(styleSheet());

    // Center the main window on the screen
    CenterToScreen(this);

    // Initialize UI elements
    ui->lbConnected->setText(tr("RS485/RS422 protocol MODBUS ITF off."));

    // Read settings from registry
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);

    // LabConditions
    settings.beginGroup("LabConditions");

    // Set temperature with default value "18"
    ui->leTemperature->setText(settings.value("labTemperature", "18").toString());

    // Set humidity with default value "51"
    ui->leHumidity->setText(settings.value("labHumidity", "51").toString());

    // Set pressure with default value "1026"
    ui->lePressure->setText(settings.value("labPressure", "1026").toString());

    settings.endGroup();
    settings.sync();

    // Initialize TableBoard and connect signals to slots
    inputData = new TableBoard(this);
    inputData->setModal(false);

    // Disable interface radio button (future feature)
    // ui->rbManual->setEnabled(true);
    // ui->rbInterface->setEnabled(true);

    licenseDialog->setModal(true);
    CenterToScreen(licenseDialog);

    helpAbout->setModal(true);
    CenterToScreen(helpAbout);

    alignmentGroup->addAction(ui->action_English);
    alignmentGroup->addAction(ui->action_Romana);
    ui->action_English->setCheckable(true);
    ui->action_Romana->setCheckable(true);
    ui->action_Romana->setChecked(true);

    std::string filename = CSV_FLOW_METER_TYPES;
    std::vector<MeterFlowType> meterFlowTypesVector = readFlowMeterTypesCSV(filename);

    // Clear existing items if any
    ui->cbNumberOfWaterMeters->clear();

    // Populate cbNumberOfWaterMeters with numbers from 1 to MAX_NR_WATER_METERS
    for (unsigned int i = 1; i <= MAX_NUMBER_FLOW_METERS; ++i) {
        ui->cbNumberOfWaterMeters->addItem(QString::number(i));
    }

    NUMBER_ENTRIES_METER_FLOW_DB = meterFlowTypesVector.size();

    // Copy elements from meterFlowTypesVector to MeterFlowDB
    for (size_t iter = 0; iter < NUMBER_ENTRIES_METER_FLOW_DB; ++iter) {
        MeterFlowDB[iter] = meterFlowTypesVector.at(iter);
    }

    // Populate cbWaterMeterType with names from MeterFlowDB
    ui->cbWaterMeterType->clear();  // Clear existing items if any
    for (size_t iter = 0; iter < NUMBER_ENTRIES_METER_FLOW_DB; ++iter) {
        ui->cbWaterMeterType->addItem(QString::fromStdString(MeterFlowDB[iter].nameWaterMeter));
    }

    // Connect QComboBox signals to custom slots
    connect(ui->cbNumberOfWaterMeters, &QComboBox::currentIndexChanged, this,
            &MainWindow::onNumberOfWaterMetersChanged);
    connect(ui->cbWaterMeterType, &QComboBox::currentIndexChanged, this, &MainWindow::onMeterTypeChanged);

    // Connect QRadioButton signals to custom slots
    connect(ui->rbVolumetric, &QRadioButton::clicked, this, &MainWindow::onRbVolumeClicked);
    connect(ui->rbGravimetric, &QRadioButton::clicked, this, &MainWindow::onRbGravimetricClicked);
    connect(ui->rbManual, &QRadioButton::clicked, this, &MainWindow::onRbManualClicked);
    connect(ui->rbInterface, &QRadioButton::clicked, this, &MainWindow::onRbInterfaceClicked);

    // Connect QLineEdit signals to custom slots
    connect(ui->leTemperature, &QLineEdit::textChanged, this, &MainWindow::onAmbientTemperatureTextChanged);
    connect(ui->lePressure, &QLineEdit::textChanged, this, &MainWindow::onAtmosphericPressureTextChanged);
    connect(ui->leHumidity, &QLineEdit::textChanged, this, &MainWindow::onRelativeAirHumidityTextChanged);

    // Connect QPushButton signals to custom slots
    connect(ui->pbNewSession, &QPushButton::clicked, this, &MainWindow::onNewSessionClicked);
    connect(ui->pbExitApplication, &QPushButton::clicked, this, &MainWindow::onExitApplication);

    // Connect QAction signals to custom slots
    connect(ui->action_License, &QAction::triggered, this, &MainWindow::onShowLicense);
    connect(ui->action_ExitApp, &QAction::triggered, this, &MainWindow::onExitApplication);
    connect(ui->action_StartSession, &QAction::triggered, this, &MainWindow::onNewSessionClicked);
    connect(ui->action_WaterDensity, &QAction::triggered, this, &MainWindow::onWaterDensityPage);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::onHelpAbout);
    connect(ui->action_General_Description, &QAction::triggered, this, &MainWindow::onGeneralDescription);
    connect(ui->action_Verification_Method, &QAction::triggered, this, &MainWindow::onVerificationMethod);

    // Connect QAction signals for language and serial port configuration
    connect(ui->action_Romana, &QAction::triggered, this, &MainWindow::onSetRomanian);
    connect(ui->action_English, &QAction::triggered, this, &MainWindow::onSetEnglish);
    connect(ui->action_Configure_Serial_Port, &QAction::triggered, this, &MainWindow::onPortSettings);

    // Connect signals to slots in another object (inputData) - Modern Qt5+ syntax
    connect(this, &MainWindow::meterTypeChangedSignal, inputData, &TableBoard::onTypeMeterChanged);
    connect(this, &MainWindow::numberOfWaterMetersChangedSignal, inputData, &TableBoard::onNumberOfWaterMetersChanged);
    connect(this, &MainWindow::measurementTypeChangedSignal, inputData, &TableBoard::onMeasurementTypeChanged);

    // Added for future improvements
    ui->action_General_Description->setVisible(false);

    ui->rbGravimetric->setChecked(true);
    ui->rbManual->setChecked(true);

    SelectMeterComboBox();

    ui->lbConnected->hide();
    installEventFilter(this);

    settings.beginGroup("BenchConfiguration");

    int numberWaterMeters = 20;
    if (settings.contains("numberWaterMeters")) {
        numberWaterMeters = settings.value("numberWaterMeters").toInt();
    }
    numberWaterMeters = std::clamp(numberWaterMeters, 0, static_cast<int>(MAX_NUMBER_FLOW_METERS - 1));

    int waterMeterType = 0;
    if (settings.contains("typeWaterMeters")) {
        waterMeterType = settings.value("typeWaterMeters").toInt();
    }
    waterMeterType = std::clamp(waterMeterType, 0, static_cast<int>(meterFlowTypesDefault.size() - 1));

    settings.endGroup();
    ui->cbNumberOfWaterMeters->setCurrentIndex(numberWaterMeters);
    ui->cbWaterMeterType->setCurrentIndex(waterMeterType);

    // Set initial focus to the first input widget in the tab order
    ui->cbNumberOfWaterMeters->setFocus();

    // Set status bar message after UI is fully initialized using QTimer
    QTimer::singleShot(100, this, [this]() {
        statusBarMessage = tr("Mod de operare stand: manual");
        setStatusBarMessage(statusBarMessage);
    });
}

/**
 * \brief Destructor for MainWindow class.
 *
 * Cleans up resources associated with the MainWindow.
 */
MainWindow::~MainWindow() {

    // Retrieve and update ambient temperature
    selectedInfo.ambientTemperature = ui->leTemperature->text().toStdString();

    // Retrieve and update atmospheric pressure
    selectedInfo.atmosphericPressure = ui->lePressure->text().toStdString();

    // Retrieve and update relative air humidity
    selectedInfo.relativeAirHumidity = ui->leHumidity->text().toStdString();

    // Update settings with the new values
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);

    settings.beginGroup("LabConditions");
    settings.setValue("labTemperature", ui->leTemperature->text());
    settings.setValue("labPressure", ui->lePressure->text());
    settings.setValue("labHumidity", ui->leHumidity->text());
    settings.endGroup();

    // Update BenchConfiguration settings
    settings.beginGroup("BenchConfiguration");
    settings.setValue("numberWaterMeters", ui->cbNumberOfWaterMeters->currentIndex());
    settings.setValue("typeWaterMeters", ui->cbWaterMeterType->currentIndex());
    settings.endGroup();

    settings.sync();

    // Clean up UI resources
    delete ui;
}

/**
 * \brief Slot invoked when the meter type is changed.
 *
 * \param index The index of the selected meter type (unused).
 *
 * This function selects the meter combo box and emits the meterTypeChangedSignal.
 */
void MainWindow::onMeterTypeChanged(int index) {
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
void MainWindow::onNumberOfWaterMetersChanged(int index) {
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
void MainWindow::onNewSessionClicked() {
    if (!this->inputData) {
        // Create new TableBoard instance if not already initialized
        if (!inputData) {
            inputData = new TableBoard(this);
        } else {
            inputData->raise();
            inputData->activateWindow();
        }

        // Connect signals to slots in inputData - Modern Qt5+ syntax
        connect(this, &MainWindow::meterTypeChangedSignal, inputData, &TableBoard::onTypeMeterChanged);
        connect(this, &MainWindow::numberOfWaterMetersChangedSignal, inputData,
                &TableBoard::onNumberOfWaterMetersChanged);
        connect(this, &MainWindow::measurementTypeChangedSignal, inputData, &TableBoard::onMeasurementTypeChanged);
    }

    // Update selected information (assuming this function exists in your class)
    updateSelectedInfo();

    // Set the fixed size of the window
    int fixedWidth = MAIN_WINDOW_WIDTH;    // Set your fixed width
    int fixedHeight = MAIN_WINDOW_HEIGHT;  // Set your fixed height
    this->inputData->setFixedSize(fixedWidth, fixedHeight);

    // Calculate the center position using the primary screen
    QScreen* primaryScreen = QApplication::primaryScreen();
    QRect availableGeometry = primaryScreen->availableGeometry();
    int x = (availableGeometry.width() - fixedWidth) / 2;
    int y = (availableGeometry.height() - fixedHeight) / 2;

    // Set the position and display properties for the window
    inputData->move(x, y);       // Set the window position
    inputData->setModal(false);  // Set the window to non-modal
    inputData->show();           // Display the window
    inputData->raise();
    inputData->activateWindow();
}

/**
 * \brief Slot invoked when the application exit action is triggered.
 *
 * If `inputData` is initialized, it sets it to nullptr (without deleting to avoid
 * double deletion if already deleted elsewhere). Then, it closes the main window.
 */
void MainWindow::onExitApplication() {
    if (inputData) {
        inputData->close();
        delete inputData;
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
void MainWindow::onRbGravimetricClicked() {
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
void MainWindow::onRbVolumeClicked() {
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
void MainWindow::onRbManualClicked() {
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbInterface = ui->rbInterface->isChecked();
    statusBarMessage = tr("Mod de operare stand: manual");
    setStatusBarMessage(statusBarMessage);
}

/**
 * \brief Slot invoked when the "Interface" radio button is clicked.
 *
 * Currently does nothing and serves as a placeholder for future functionality
 * related to the "Interface" radio button.
 */
void MainWindow::onRbInterfaceClicked() {
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbInterface = ui->rbInterface->isChecked();
    statusBarMessage = tr("Mod de operare stand: interface");
    setStatusBarMessage(statusBarMessage);
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
void MainWindow::onAmbientTemperatureTextChanged() {
    // Retrieve and update ambient temperature
    QString temperatureText = ui->leTemperature->text();
    selectedInfo.ambientTemperature = temperatureText.toStdString();

    // Retrieve and update atmospheric pressure
    QString pressureText = ui->lePressure->text();
    selectedInfo.atmosphericPressure = pressureText.toStdString();

    // Retrieve and update relative air humidity
    QString humidityText = ui->leHumidity->text();
    selectedInfo.relativeAirHumidity = humidityText.toStdString();

    // Update settings with the new values
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
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
 * and updates selectedInfo.ambientTemperature and selectedInfo.atmosphericPressure
 * respectively. Updates settings with the new values.
 */
void MainWindow::onRelativeAirHumidityTextChanged() {
    // Retrieve and update ambient temperature
    QString temperatureText = ui->leTemperature->text();
    selectedInfo.ambientTemperature = temperatureText.toStdString();

    // Retrieve and update atmospheric pressure
    QString pressureText = ui->lePressure->text();
    selectedInfo.atmosphericPressure = pressureText.toStdString();

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
 * selectedInfo.atmosphericPressure with its string representation.
 * Similarly, retrieves text from temperature and relative air humidity
 * QLineEdit fields and updates selectedInfo.ambientTemperature and
 * selectedInfo.relativeAirHumidity respectively. Updates settings with
 * the new values.
 */
void MainWindow::onAtmosphericPressureTextChanged() {
    // Retrieve and update ambient temperature
    QString temperatureText = ui->leTemperature->text();
    selectedInfo.ambientTemperature = temperatureText.toStdString();

    // Retrieve and update atmospheric pressure
    QString pressureText = ui->lePressure->text();
    selectedInfo.atmosphericPressure = pressureText.toStdString();

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
void MainWindow::onGeneralDescription() {
    if (ROMANIAN == selectedInfo.selectedLanguage) {
        QString fileName = MANUAL_RO;                                 // Filename of the Romanian manual
        QString appDirPath = QCoreApplication::applicationDirPath();  // Get application directory path
        QString filePath = QDir(appDirPath).filePath(fileName);       // Construct full file path

        // Check if the file exists
        if (QFile::exists(filePath)) {
            QUrl fileUrl = QUrl::fromLocalFile(filePath);  // Create a URL from local file path
            QDesktopServices::openUrl(fileUrl);            // Open the file URL using default application
        }
    }

    return;
}

/**
 * \brief Opens the verification method documentation.
 *
 * Displays the verification method documentation in HTML format when called.
 * Reads the appropriate markdown file based on selected language and converts it to HTML for display.
 */
void MainWindow::onVerificationMethod() {
    // Select file based on language
    QString fileName;
    if (ROMANIAN == selectedInfo.selectedLanguage) {
        fileName = "PROCES_CALCUL_VERIFICARE_CONTOARE.md";
    } else {
        fileName = "VERIFICATION_METHOD_PROCESS.md";
    }

    QString appDirPath = QCoreApplication::applicationDirPath();
    QString filePath = QDir(appDirPath).filePath(fileName);

    // Check if the markdown file exists
    if (!QFile::exists(filePath)) {
        QMessageBox::warning(this,
            tr("Fișier lipsă"),
            tr("Fișierul cu documentația metodei de verificare nu a fost găsit:\n%1").arg(filePath));
        return;
    }

    // Read the markdown file
    QFile mdFile(filePath);
    if (!mdFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this,
            tr("Eroare citire"),
            tr("Nu s-a putut deschide fișierul pentru citire."));
        return;
    }

    QTextStream in(&mdFile);
    in.setEncoding(QStringConverter::Utf8);
    QString markdownContent = in.readAll();
    mdFile.close();

    // Create temporary HTML file path
    QString tempHtmlFilePath = QDir::temp().filePath("verification_method.html");

    // Open HTML file for writing
    std::ofstream htmlFile(tempHtmlFilePath.toStdString());
    if (!htmlFile.is_open())
        return;

    std::stringstream output;

    // === HTML Header and CSS ===
    output << R"(
<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Metoda de Verificare - Contoare de Apă</title>
    <style>
        body {
            margin: 40px;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 1200px;
            margin-left: auto;
            margin-right: auto;
            background-color: #f9f9f9;
        }

        h1 {
            font-size: 32px;
            color: #1a5490;
            border-bottom: 3px solid #1a5490;
            padding-bottom: 10px;
            margin-top: 30px;
        }

        h2 {
            font-size: 26px;
            color: #2874a6;
            margin-top: 30px;
            margin-bottom: 15px;
            border-left: 5px solid #2874a6;
            padding-left: 15px;
        }

        h3 {
            font-size: 20px;
            color: #34495e;
            margin-top: 20px;
            margin-bottom: 10px;
        }

        p {
            font-size: 16px;
            margin-bottom: 15px;
            text-align: justify;
        }

        ul, ol {
            margin-bottom: 15px;
            padding-left: 30px;
        }

        li {
            margin-bottom: 8px;
            font-size: 16px;
        }

        code {
            background-color: #f4f4f4;
            padding: 2px 6px;
            border-radius: 3px;
            font-family: 'Consolas', 'Monaco', monospace;
            font-size: 14px;
            color: #c7254e;
        }

        pre {
            background-color: #f8f8f8;
            border: 1px solid #ddd;
            border-radius: 5px;
            padding: 15px;
            overflow-x: auto;
            font-family: 'Consolas', 'Monaco', 'Courier New', monospace;
            font-size: 13px;
            line-height: 1.2;
            margin-bottom: 20px;
            white-space: pre;
            color: #2c3e50;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 20px;
            background-color: white;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }

        th, td {
            padding: 12px;
            text-align: left;
            border: 1px solid #ddd;
        }

        th {
            background-color: #2874a6;
            color: white;
            font-weight: bold;
        }

        tr:nth-child(even) {
            background-color: #f9f9f9;
        }

        tr:hover {
            background-color: #f0f8ff;
        }

        .formula {
            background-color: #e8f4f8;
            padding: 10px 15px;
            border-left: 4px solid #2874a6;
            margin: 15px 0;
            font-family: 'Consolas', 'Monaco', monospace;
            font-size: 15px;
        }

        blockquote {
            border-left: 4px solid #95a5a6;
            padding-left: 15px;
            margin-left: 0;
            color: #555;
            font-style: italic;
        }

        hr {
            border: none;
            border-top: 2px solid #ddd;
            margin: 30px 0;
        }

        strong {
            color: #2c3e50;
            font-weight: 600;
        }
    </style>
</head>
<body>
)";

    // Convert markdown to HTML - line by line processing
    QStringList lines = markdownContent.split('\n');
    QString processedHtml;
    bool inList = false;
    bool inOrderedList = false;
    bool inTable = false;
    bool inCodeBlock = false;
    QString codeBlockContent;

    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines[i];

        // Check for code block markers
        if (line.trimmed() == "```" || line.trimmed().startsWith("```")) {
            if (!inCodeBlock) {
                // Starting a code block
                inCodeBlock = true;
                codeBlockContent.clear();
                continue;
            } else {
                // Ending a code block
                inCodeBlock = false;
                processedHtml += "<pre>" + codeBlockContent + "</pre>\n";
                codeBlockContent.clear();
                continue;
            }
        }

        // If inside code block, collect content
        if (inCodeBlock) {
            codeBlockContent += line + "\n";
            continue;
        }

        // Escape HTML special characters for regular content
        line.replace("&", "&amp;");
        line.replace("<", "&lt;");
        line.replace(">", "&gt;");

        // Convert inline code (` ... `)
        QRegularExpression inlineCodeRegex("`([^`]+)`");
        line.replace(inlineCodeRegex, "<code>\\1</code>");

        // Convert headers
        if (line.startsWith("# ")) {
            line = "<h1>" + line.mid(2) + "</h1>";
        } else if (line.startsWith("## ")) {
            line = "<h2>" + line.mid(3) + "</h2>";
        } else if (line.startsWith("### ")) {
            line = "<h3>" + line.mid(4) + "</h3>";
        } else if (line.startsWith("#### ")) {
            line = "<h4>" + line.mid(5) + "</h4>";
        }

        // Convert bold (**text**)
        line.replace(QRegularExpression("\\*\\*([^*]+)\\*\\*"), "<strong>\\1</strong>");

        // Convert italic (*text*)
        line.replace(QRegularExpression("\\*([^*]+)\\*"), "<em>\\1</em>");

        // Convert horizontal rules
        if (line.trimmed() == "---" || line.trimmed().startsWith("---")) {
            line = "<hr>";
        }

        // Handle tables
        if (line.trimmed().startsWith("|")) {
            if (!inTable) {
                processedHtml += "<table>\n";
                inTable = true;
            }

            // Split by |
            QStringList cells = line.split('|', Qt::SkipEmptyParts);

            // Check if it's a header separator line
            if (i + 1 < lines.size() && lines[i + 1].contains("---")) {
                processedHtml += "<thead><tr>";
                for (const QString& cell : cells) {
                    processedHtml += "<th>" + cell.trimmed() + "</th>";
                }
                processedHtml += "</tr></thead>\n<tbody>\n";
                ++i; // Skip separator line
                continue;
            }

            // Regular table row
            if (!lines[i].contains("---")) {
                processedHtml += "<tr>";
                for (const QString& cell : cells) {
                    processedHtml += "<td>" + cell.trimmed() + "</td>";
                }
                processedHtml += "</tr>\n";
            }
        } else {
            if (inTable) {
                processedHtml += "</tbody></table>\n";
                inTable = false;
            }

            // Handle unordered lists
            if (line.trimmed().startsWith("- ") || line.trimmed().startsWith("* ")) {
                if (!inList) {
                    processedHtml += "<ul>\n";
                    inList = true;
                }
                QString listItem = line.trimmed().mid(2); // Remove "- " or "* "
                processedHtml += "<li>" + listItem + "</li>\n";
            } else if (QRegularExpression("^\\d+\\.\\s").match(line.trimmed()).hasMatch()) {
                // Handle ordered lists
                if (!inOrderedList) {
                    processedHtml += "<ol>\n";
                    inOrderedList = true;
                }
                QString listItem = line.trimmed();
                listItem = listItem.mid(listItem.indexOf('.') + 1).trimmed();
                processedHtml += "<li>" + listItem + "</li>\n";
            } else {
                // Close lists if needed
                if (inList) {
                    processedHtml += "</ul>\n";
                    inList = false;
                }
                if (inOrderedList) {
                    processedHtml += "</ol>\n";
                    inOrderedList = false;
                }

                // Add paragraph for non-empty lines (but not for special tags)
                if (!line.trimmed().isEmpty() &&
                    !line.contains("<h1>") && !line.contains("<h2>") &&
                    !line.contains("<h3>") && !line.contains("<h4>") &&
                    !line.contains("<pre>") && !line.contains("<hr>")) {
                    processedHtml += "<p>" + line + "</p>\n";
                } else {
                    processedHtml += line + "\n";
                }
            }
        }
    }

    // Close any remaining open lists or tables
    if (inList) processedHtml += "</ul>\n";
    if (inOrderedList) processedHtml += "</ol>\n";
    if (inTable) processedHtml += "</tbody></table>\n";

    output << processedHtml.toStdString();

    // === Close HTML ===
    output << R"(
</body>
</html>
)";

    // Write the content to the file and close it
    htmlFile << output.str();
    htmlFile.close();

    // Open the file in the browser
    QDesktopServices::openUrl(QUrl::fromLocalFile(tempHtmlFilePath));
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
void MainWindow::onWaterDensityPage() {
    // Create temporary HTML file path
    QString tempHtmlFilePath = QDir::temp().filePath("water_density.html");

    // Open HTML file for writing
    std::ofstream densityHtmlFile(tempHtmlFilePath.toStdString());
    if (!densityHtmlFile.is_open())
        return;

    std::stringstream output;

    // === HTML Header and CSS ===
    output << R"(
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Water Density vs Temperature</title>
        <style>
            body {
                margin: 20px;
                font-family: Arial, sans-serif;
                -webkit-user-select: none;
                -moz-user-select: none;
                -ms-user-select: none;
                user-select: none;
            }

            h2 {
                font-size: 24px;
                color: DodgerBlue;
                font-weight: normal;
                margin-bottom: 10px;
            }

            p {
                font-size: 18px;
                color: #333;
                margin-bottom: 20px;
                line-height: 1.5;
            }

            table {
                width: 100%;
                border-collapse: collapse;
                font-family: Consolas, monospace;
                font-size: 16px;
            }

            th, td {
                padding: 8px 16px;
                text-align: right;
                border-bottom: 1px solid #ddd;
            }

            th {
                background-color: #f0f8ff;
                color: DodgerBlue;
            }

            tr:hover {
                background-color: #f9f9f9;
            }
        </style>
    </head>
    <body>
    )";

    // === Introductory text depending on language ===
    if (ROMANIAN == selectedInfo.selectedLanguage) {
        output << "<h2>Densitatea și Corecția Volumului Apei</h2>";
        output << "<p>Tabelul de mai jos afișează densitatea apei în kg/m³ și "
                  "factorul de corecție a volumului în funcție de temperatură între 0 și 100°C, "
                  "cu un pas de 0,1°C la presiune normală (1013,25 kPa). Valorile sunt generate pe baza datelor din "
                  "aplicație.</p>";
    } else {
        output << "<h2>Density and Volume Correction of Water</h2>";
        output
            << "<p>The table below shows the density of water in kg/m³ and the volume correction factor "
               "as a function of temperature from 0 to 100°C, with a 0.1°C step under normal pressure (1013.25 kPa). "
               "These values are generated based on the application data.</p>";
    }

    // === Tabel HTML ===
    output << R"(
    <table>
        <thead>
            <tr>
                <th>&nbsp;&nbsp;&nbsp;T [°C]</th>
                <th>ρ [kg/m³]</th>
                <th>K&nbsp;&nbsp;&nbsp;</th>
                <th></th>
            </tr>
        </thead>
        <tbody>
    )";

    // === Generate table rows ===
    // double rho_real20 = std::stof(optionsConfiguration["density_20"]);
    for (int i = 0; i <= 1000; ++i) {
        double temperature = 0.1 * i;
        double density = get_ro(temperature);
        double correction = get_K(temperature);

        output << "<tr>"
               << "<td>" << std::fixed << std::setprecision(1) << temperature << "</td>"
               << "<td>" << std::fixed << std::setprecision(4) << density << "</td>"
               << "<td>" << std::fixed << std::setprecision(5) << correction << "</td>"
               << "</tr>\n";
    }

    // === Final HTML ===
    output << R"(
        </tbody>
    </table>
    </body>
    </html>
    )";

    // Write the content to the file and close it
    densityHtmlFile << output.str();
    densityHtmlFile.close();

    // Open the file in the browser
    QDesktopServices::openUrl(QUrl::fromLocalFile(tempHtmlFilePath));

    // Delete the temporary file after opening
    // QFile::remove(tempHtmlFilePath);
}

/**
 * \brief Shows the license dialog.
 *
 * Displays the license dialog when called.
 */
void MainWindow::onShowLicense() {
    licenseDialog->show();
}

/**
 * \brief Shows the help/about dialog.
 *
 * Displays the help/about dialog when called.
 */
void MainWindow::onHelpAbout() {
    helpAbout->show();
}

/**
 * \brief Opens port settings or shows a warning if no serial interfaces are detected.
 *
 * Checks if serial ports are available. If no serial interfaces are detected,
 * it shows a warning message and defaults the manual radio button. Otherwise,
 * it shows the interface dialog for port settings.
 */
void MainWindow::onPortSettings() {
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbInterface = ui->rbInterface->isChecked();

    /*
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
    */
    interfaceDialog->show();
}

/**
 * \brief Sets the application language to Romanian.
 *
 * Loads and installs the Romanian translation file ("meter_ro_RO.qm").
 * Translates UI elements in various components and updates the selected language.
 */
void MainWindow::onSetRomanian() {
    // Remove existing translator if it exists
    if (appTranslator) {
        qApp->removeTranslator(appTranslator);
        delete appTranslator;
        appTranslator = nullptr;
    }

    // Create new translator and try loading from embedded resources first
    appTranslator = new QTranslator(qApp);  // Use qApp as parent for automatic cleanup
    bool loaded = appTranslator->load(":/translations/meter_ro_RO.qm");

    // Fallback to external file if embedded resource not found
    if (!loaded) {
        QString qmPath = qApp->applicationDirPath() + "/translations";
        loaded = appTranslator->load(qmPath + "/meter_ro_RO.qm");
    }

    if (loaded) {
        // Install the translator to the application
        qApp->installTranslator(appTranslator);

        // Translate UI elements in various components
        Translate();  // Assuming Translate() function handles translation in MainWindow
        if (inputData)
            inputData->Translate();  // Translate UI in inputData if available
        if (licenseDialog)
            licenseDialog->Translate();  // Translate UI in licenseDialog if available
        if (helpAbout)
            helpAbout->Translate();  // Translate UI in helpAbout if available
        if (interfaceDialog)
            interfaceDialog->Translate();  // Translate UI in interfaceDialog if available

        // Set the selected language to Romanian
        selectedInfo.selectedLanguage = ROMANIAN;
    } else {
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
void MainWindow::onSetEnglish() {
    // Remove existing translator if it exists
    if (appTranslator) {
        qApp->removeTranslator(appTranslator);
        delete appTranslator;
        appTranslator = nullptr;
    }

    // Create new translator and try loading from embedded resources first
    appTranslator = new QTranslator(qApp);  // Use qApp as parent for automatic cleanup
    bool loaded = appTranslator->load(":/translations/meter_en_EN.qm");

    // Fallback to external file if embedded resource not found
    if (!loaded) {
        QString qmPath = qApp->applicationDirPath() + "/translations";
        loaded = appTranslator->load(qmPath + "/meter_en_EN.qm");
    }

    if (loaded) {
        // Install the translator to the application
        qApp->installTranslator(appTranslator);

        // Translate UI elements in various components
        Translate();  // Assuming Translate() function handles translation in MainWindow
        if (inputData)
            inputData->Translate();  // Translate UI in inputData if available
        if (licenseDialog)
            licenseDialog->Translate();  // Translate UI in licenseDialog if available
        if (helpAbout)
            helpAbout->Translate();  // Translate UI in helpAbout if available
        if (interfaceDialog)
            interfaceDialog->Translate();  // Translate UI in interfaceDialog if available

        // Set the selected language to English
        selectedInfo.selectedLanguage = ENGLISH;
    } else {
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
void MainWindow::mousePressEvent(QMouseEvent* event) {
    activateWindow();
    QMainWindow::mousePressEvent(event);
}

/**
 * \brief Handles key press events for the main window.
 *
 * When Enter or Return key is pressed and a button has focus, trigger the button click.
 *
 * \param event The key event object.
 */
void MainWindow::keyPressEvent(QKeyEvent* event) {
    // Check if Enter or Return key was pressed
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // Get the currently focused widget
        QWidget* focusedWidget = QApplication::focusWidget();

        // Check if the focused widget is a QPushButton
        QPushButton* button = qobject_cast<QPushButton*>(focusedWidget);
        if (button) {
            // Trigger the button click
            button->click();
            event->accept();
            return;
        }
    }

    // Call base class implementation for other keys
    QMainWindow::keyPressEvent(event);
}

/**
 * \brief Handles the close event of the main window.
 *
 * Deletes the `inputData` object if it exists and accepts the close event.
 *
 * \param event The close event object.
 */
void MainWindow::closeEvent(QCloseEvent* event) {
    if (inputData) {
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
void MainWindow::CenterToScreen(QWidget* widget) {
    if (!widget)
        return;

    // Get the geometry of the primary screen
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // Get the dimensions of the widget
    int widgetWidth = widget->width();
    int widgetHeight = widget->height();

    // Calculate the center position for the widget
    int xPosition = screenGeometry.center().x() - widgetWidth / 2;
    int yPosition = screenGeometry.center().y() - widgetHeight / 2;

    // Move the widget to the calculated position
    widget->move(xPosition, yPosition);
}

/**
 * \brief Sets the message in the status bar.
 *
 * \param message The message to set in the status bar.
 */
void MainWindow::setStatusBarMessage(const QString message) {
    // Update the permanent label in the status bar
    if (statusBarLabel) {
        statusBarLabel->setText(message);
    }
}
