/*
 *  Author: Constantin
 *  File:   mainwindow.cpp
 */

// C++ Standard Library headers
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>

// Qt headers
#include <QDesktopServices>
#include <QDir>
#include <QLibrary>
#include <QLineEdit>
#include <QMessageBox>
#include <QSettings>
#include <QValidator>

// Windows-specific headers
#include <windows.h>

// Custom headers
#include "definitions.h"
#include "water-density.h"
#include "flow-meter-type.h"
#include "mainwindow.h"
#include "md5.h"
#include "ui_mainwindow.h"

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

void MainWindow::SetDefaultConfiguration() {
    optionsConfiguration.clear();
    optionsConfiguration["company"] = "NONE";
    optionsConfiguration["archive"] = "C:/Stand/Fise";
    optionsConfiguration["maximum"] = "2";
    optionsConfiguration["certificate"] = "NONE";
    optionsConfiguration["density_20"] = "998.2009";
    optionsConfiguration["control"] = "00000000000000000000000000000000";
}

/*
 *  readConfiguration()
 *  The file is checked for MD5 "company" field
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

    SetDefaultConfiguration();

    inConfigurationFile.close();

    return;
}

struct RS485SettingInfo {
    const char* key;
    const QVariant defaultValue;
};

void MainWindow::setLabelValue(QLabel* label, double value, int precision)
{
    std::ostringstream streamObj;
    streamObj << std::fixed << std::setprecision(precision) << value;
    label->setText(streamObj.str().c_str());
    streamObj.str("");
}

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

void MainWindow::Translate()
{
    this->setWindowTitle(tr("WStreamLab - Dashboard"));
    ui->menu_File->setTitle(tr("File"));
    ui->menu_Language->setTitle(tr("Language"));
    ui->menu_Help->setTitle(tr("Help"));
    ui->action_StartSession->setText(tr("Start Session"));
    ui->action_ExitApp->setText(tr("Exit"));
    ui->action_English->setText(tr("English"));
    ui->action_Romana->setText(tr("Română"));
    ui->action_General_Description->setText(tr("General Description"));
    ui->action_WaterDensity->setText(tr("Water Density"));
    ui->action_License->setText(tr("License"));
    ui->action_About->setText(tr("About"));
    ui->lbWaterMeterType->setText(tr("Water meter type:"));
    ui->lbNumberOfWaterMeters->setText(tr("Number of water meters:"));
    ui->lbTemperature->setText(tr("Temperature:"));
    ui->lbPressure->setText(tr("Athmosferic pressure:"));
    ui->lbHumidity->setText(tr("Relative air humidity:"));
    ui->lbTab5->setText(tr("[mbar]"));
    ui->lbTab3->setText(tr("\302\260C"));
    ui->lbTab4->setText(tr("[%]"));
    ui->gbMeasurementMethod->setTitle(tr("Measurement method"));
    ui->rbVolumetric->setText(tr("Volumetric"));
    ui->rbGravimetric->setText(tr("Gravimetric"));
    ui->gbReadMethod->setTitle(tr("Read method"));
    ui->rbManual->setText(tr("Manual"));
    ui->rbInterface->setText(tr("Interface"));
    ui->gbWaterMeterFeatures->setTitle(tr("Water meter features"));
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
    ui->pbNewSession->setText(tr("&New Session"));
    ui->pbExitApplication->setText(tr("&Exit"));
}

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
    }
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

    CenterToScreen(this);
    ui->SerialLedIndicator->setState(false);
    ui->lbConnected->setText(
        tr("RS485 protocol MODBUS ITF off."));
    ui->lbConnected->setStyleSheet(
        "QLabel{font-family: \"Segoe UI\"; font-size: 12pt}");

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

    settings.endGroup();

    // RS485
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

    for (const RS485SettingInfo& setting : rs485Settings) {
        if (!settings.childKeys().contains(setting.key, Qt::CaseInsensitive)) {
            settings.setValue(setting.key, setting.defaultValue);
        }
    }

    settings.endGroup();
    settings.sync();

    inputData = new TableBoard(this);
    connect(this, SIGNAL(meterTypeChangedSignal()), inputData,
            SLOT(onTypeMeterChanged()));
    connect(this, SIGNAL(numberOfWaterMetersChangedSignal()), inputData,
            SLOT(onNumberOfWaterMetersChanged()));
    connect(this, SIGNAL(measurementTypeChangedSignal()), inputData,
            SLOT(onMeasurementTypeChanged()));

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMeterTypeChanged(int index)
{
    Q_UNUSED(index);
    SelectMeterComboBox();
    emit meterTypeChangedSignal();
}

void MainWindow::onNumberOfWaterMetersChanged(int index)
{
    Q_UNUSED(index);
    selectedInfo.entriesNumber =
        ui->cbNumberOfWaterMeters->currentText().toInt();
    emit numberOfWaterMetersChangedSignal();
}

void MainWindow::onNewSessionClicked()
{
    if (!this->inputData)
    {
        inputData = new TableBoard(this);
        connect(this, SIGNAL(meterTypeChangedSignal()), inputData,
                SLOT(onTypeMeterChanged()));
        connect(this, SIGNAL(numberOfWaterMetersChangedSignal()), inputData,
                SLOT(onNumberOfWaterMetersChanged()));
        connect(this, SIGNAL(measurementTypeChangedSignal()), inputData,
                SLOT(onMeasurementTypeChanged()));
    }

    updateSelectedInfo();

    // Set the fixed size of the window
    int fixedWidth = MAIN_WINDOW_WIDTH;   // Set your fixed width
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

void MainWindow::onExitApplication()
{
    if (inputData)
    {
        // delete inputData;
        inputData = nullptr;
    }
    this->close();
}

void MainWindow::onRbGavritmetricClicked()
{
    selectedInfo.rbVolumetric = ui->rbVolumetric->isChecked();
    selectedInfo.rbGravimetric_new = ui->rbGravimetric->isChecked();
    emit measurementTypeChangedSignal();
}

void MainWindow::onRbVolumeClicked()
{
    selectedInfo.rbVolumetric = ui->rbVolumetric->isChecked();
    selectedInfo.rbGravimetric_new = ui->rbGravimetric->isChecked();
    emit measurementTypeChangedSignal();
}

void MainWindow::onRbManualClicked()
{
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbInterface = ui->rbInterface->isChecked();
}

void MainWindow::onRbInterfaceClicked() {}

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

void MainWindow::onGeneralDescription()
{
    if (ROMANIAN == selectedInfo.selectedLanguage)
    {
        QString fileName = MANUAL_RO;
        QString appDirPath = QCoreApplication::applicationDirPath();
        QString filePath = QDir(appDirPath).filePath(fileName);

        if (QFile::exists(filePath)) {
            QUrl fileUrl = QUrl::fromLocalFile(filePath);
            QDesktopServices::openUrl(fileUrl);
        }
    }

    return;
}

#include <QFile>
#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <fstream>
#include <iomanip>
#include <sstream>

void MainWindow::onWaterDensityPage() {
    QString htmlFilePath = QDir::temp().filePath("water_density.html");

    std::ofstream densityHtmlFile(htmlFilePath.toStdString());
    if (!densityHtmlFile.is_open()) {
        // Handle error opening file
        return;
    }

    std::stringstream output;

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

    output << R"(
                    <pre><span class="white">&nbsp;&nbsp;&nbsp;T [°C]</span>&nbsp;&nbsp;<span class="yellow">ρ[kg/mc]</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="blue">K</span></pre>
                    <hr />
    )";

    for (int i = 0; i <= 1000; ++i) {
        double temperature = 0.1 * i;
        double density = quadraticInterpolationTemperature(temperature, 998.2009);
        double coefficient = quadraticInterpolationVolumeCorrection(temperature);

        output << "<pre><span class=\"black\">" << std::fixed << std::setprecision(1)
               << "&nbsp;&nbsp;&nbsp;&nbsp;" << temperature << "</span>&nbsp;&nbsp;&nbsp;&nbsp;<span class=\"green\">"
               << std::setprecision(4) << density << "</span>&nbsp;&nbsp;&nbsp;<span class=\"blue\">"
               << std::setprecision(5) <<  coefficient << "</span></pre>";

        if ((i + 1) % 10 == 0) {
            output << "<hr />\n";
        }
    }

    output << R"(
                </h2>
                </div>
            </body>
        </html>
    )";

    densityHtmlFile << output.str() << std::endl;

    QDesktopServices::openUrl(QUrl::fromLocalFile(htmlFilePath));

    QFile::remove(htmlFilePath);
}



void MainWindow::onShowLicense()
{
    licenseDialog->show();
}

void MainWindow::onHelpAbout()
{
    helpAbout->show();
}

void MainWindow::onPortSettings()
{
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbInterface = ui->rbInterface->isChecked();
    const wchar_t *serial = serialPorts();
    if (!std::wcslen(serial))
    {
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
        ui->rbManual->setChecked(true);
    }
    else
    {
        interfaceDialog->show();
    }
}

void MainWindow::onSetRomanian()
{
    QString qmPath = qApp->applicationDirPath() + "/translations";
    QString translationFile = "meter_ro_RO.qm";

    // Remove existing translator
    if (appTranslator)
    {
        qApp->removeTranslator(appTranslator);
        delete appTranslator;
        appTranslator = nullptr;
    }

    // Create and install new translator
    appTranslator = new QTranslator(nullptr);
    if (appTranslator->load(qmPath + "/" + translationFile))
    {
        qApp->installTranslator(appTranslator);

        // Translate UI elements in various components
        Translate();
        if (inputData) inputData->Translate();
        if (licenseDialog) licenseDialog->Translate();
        if (helpAbout) helpAbout->Translate();
        if (interfaceDialog) interfaceDialog->Translate();

        // Set the selected language
        selectedInfo.selectedLanguage =  ROMANIAN;
    }
    else
    {
        delete appTranslator;
        appTranslator = nullptr;
    }
}

void MainWindow::onSetEnglish()
{
    QString qmPath = qApp->applicationDirPath() + "/translations";
    QString translationFile = "meter_en_EN.qm";

    // Remove existing translator
    if (appTranslator)
    {
        qApp->removeTranslator(appTranslator);
        delete appTranslator;
        appTranslator = nullptr;
    }

    // Create and install new translator
    appTranslator = new QTranslator(nullptr);
    if (appTranslator->load(qmPath + "/" + translationFile))
    {
        qApp->installTranslator(appTranslator);

        // Translate UI elements in various components
        Translate();
        if (inputData) inputData->Translate();
        if (licenseDialog) licenseDialog->Translate();
        if (helpAbout) helpAbout->Translate();
        if (interfaceDialog) interfaceDialog->Translate();

        // Set the selected language
        selectedInfo.selectedLanguage =  ENGLISH;
    }
    else
    {
        delete appTranslator;
        appTranslator = nullptr;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    activateWindow();
    QMainWindow::mousePressEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (inputData)
    {
        delete inputData;
        inputData = nullptr;
    }
    event->accept();
}

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
