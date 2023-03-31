/*
 *  Author: Constantin
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <QScrollArea>
#include <QDesktopServices>
#include <QDir>
#include <QValidator>

#include <sstream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <sstream>

#include "flow-meter-type.h"
#include "md5.h"
#include "air-density.h"

extern QTranslator *appTranslator;

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
void MainWindow::ReadConfiguration() {

    std::ifstream inConfigurationFile ( "watermeters.conf" );

    std::string md5Read;
    std::string md5Calculate;
    bool license{ false };

    if ( inConfigurationFile.is_open() ) {

        std::string line;
        std::string key;

        while ( std::getline ( inConfigurationFile, key, '=' ) ) {
            std::string value;

            if ( std::getline ( inConfigurationFile, value, '>' ) ) {
                optionsConfiguration[key] = value;
                std::getline ( inConfigurationFile, value );
            }
        }

        if ( optionsConfiguration.find ( "control" ) != optionsConfiguration.end() &&
                optionsConfiguration.find ( "company" ) != optionsConfiguration.end() &&
                optionsConfiguration.find ( "density_20" ) != optionsConfiguration.end() ) {

            md5Read = optionsConfiguration["control"];
            std::string wordControl = optionsConfiguration["company"] + optionsConfiguration["density_20"];
            md5Calculate = md5 ( wordControl );

            if ( md5Read == md5Calculate ) {
                return;
            }
        }
    }

    optionsConfiguration.clear();

    optionsConfiguration["company"] = "NONE";
    optionsConfiguration["archive"] = "C:/watermeters/reports";
    optionsConfiguration["maximum"] = "5";
    optionsConfiguration["certificate"] = "NONE";
    optionsConfiguration["density_20"] = "998.2009";
    optionsConfiguration["control"] = "00000000000000000000000000000000";
    return;
}

void MainWindow::SelectMeterComboBox() {

    selectedInfo.density_20 = std::stof ( optionsConfiguration["density_20"] );
    selectedInfo.pathResults = optionsConfiguration["archive"];
    selectedInfo.certificate =  optionsConfiguration["certificate"];

    selectedInfo.entriesNumber = ui->cbNumberOfWaterMeters->currentText().toInt();

    selectedInfo.ambientTemperature = ui->leTemperature->text().toInt();
    selectedInfo.athmosphericPressure = ui->lePressure->text().toInt();
    selectedInfo.relativeAirHumidity = ui->leHumidity->text().toInt();

    int selectedWaterMeter = ui->cbWaterMeterType->currentIndex();

    selectedInfo.nameWaterMeter = MeterFlowDB[selectedWaterMeter].nameWaterMeter;
    selectedInfo.nominalDiameter = MeterFlowDB[selectedWaterMeter].nominalDiameter;
    selectedInfo.nominalFlow = MeterFlowDB[selectedWaterMeter].nominalFlow;
    selectedInfo.maximumFlow = MeterFlowDB[selectedWaterMeter].maximumFlow;
    selectedInfo.trasitionFlow = MeterFlowDB[selectedWaterMeter].trasitionFlow;
    selectedInfo.minimumFlow = MeterFlowDB[selectedWaterMeter].minimumFlow;
    selectedInfo.nominalError = MeterFlowDB[selectedWaterMeter].nominalError;
    selectedInfo.maximumError = MeterFlowDB[selectedWaterMeter].maximumError;

    selectedInfo.rbGravitmetric = ui->rbGravitmetric->isChecked();
    selectedInfo.rbVolumetric = ui->rbVolumetric->isChecked();
    selectedInfo.rbInterface = ui->rbInterface->isChecked();
    selectedInfo.rbManual = ui->rbManual->isChecked();

    std::filesystem::create_directories ( selectedInfo.pathResults );
    std::filesystem::create_directories ( selectedInfo.pathResults + "/inputData" );

    std::ostringstream streamObj;

    streamObj << std::fixed << std::setprecision ( 0 ) << selectedInfo.nominalDiameter;
    ui->lbNominalDiameterCurrent->setText ( streamObj.str().c_str() );
    streamObj.str ( "" );

    streamObj << std::fixed << std::setprecision ( 2 ) << selectedInfo.maximumFlow;
    ui->lbMaximumFlowCurrent->setText ( streamObj.str().c_str() );
    streamObj.str ( "" );

    streamObj << std::fixed << std::setprecision ( 2 ) << selectedInfo.nominalFlow;
    ui->lbNominalFlowCurrent->setText ( streamObj.str().c_str() );
    streamObj.str ( "" );

    streamObj << std::fixed << std::setprecision ( 2 ) << selectedInfo.trasitionFlow;
    ui->lbTransitionFlowCurrent->setText ( streamObj.str().c_str() );
    streamObj.str ( "" );

    streamObj << std::fixed << std::setprecision ( 2 ) << selectedInfo.minimumFlow;
    ui->lbMinimumFlowCurrent->setText ( streamObj.str().c_str() );
    streamObj.str ( "" );

    streamObj << std::fixed << std::setprecision ( 1 ) << selectedInfo.maximumError;
    ui->lbMaximumErrorCurrent->setText ( streamObj.str().c_str() );
    streamObj.str ( "" );

    streamObj << std::fixed << std::setprecision ( 1 ) << selectedInfo.nominalError;
    ui->lbNominalErrorCurrent->setText ( streamObj.str().c_str() );
    streamObj.str ( "" );
}

void MainWindow::Translate() {

    this->setWindowTitle ( tr ( "WFlowLab - Dashboard" ) );

    ui->menu_File->setTitle ( tr ( "File" ) );
    ui->menu_Language->setTitle ( tr ( "Language" ) );
    ui->menu_Help->setTitle ( tr ( "Help" ) );

    ui->action_StartSession->setText ( tr ( "Start Session" ) );
    ui->action_ExitApp->setText ( tr ( "Exit" ) );
    ui->action_English->setText ( tr ( "English" ) );
    ui->action_Romana->setText ( tr ( "Română" ) );
    ui->action_General_Description->setText ( tr ( "General Description" ) );
    ui->action_WaterDensity->setText ( tr ( "Water Density" ) );
    ui->action_License->setText ( tr ( "License" ) );
    ui->action_About->setText ( tr ( "About" ) );

    ui->lbWaterMeterType->setText ( tr ( "Water meter type:" ) );
    ui->lbNumberOfWaterMeters->setText ( tr ( "Number of water meters:" ) );
    ui->lbTemperature->setText ( tr ( "Temperature" ) );
    ui->lbPressure->setText ( tr ( "Athmosferic pressure:" ) );
    ui->lbHumidity->setText ( tr ( "Relative air humidity:" ) );
    ui->lbTab5->setText ( tr ( "[mbar]" ) );
    ui->lbTab3->setText ( tr ( "\302\260C" ) );
    ui->lbTab4->setText ( tr ( "[%]" ) );

    ui->gbMeasurementMethod->setTitle ( tr ( "Measurement method" ) );
    ui->rbVolumetric->setText ( tr ( "Volumetric" ) );
    ui->rbGravitmetric->setText ( tr ( "Gravimetric" ) );

    ui->gbReadMethod->setTitle ( tr ( "Read method" ) );
    ui->rbManual->setText ( tr ( "Manual" ) );
    ui->rbInterface->setText ( tr ( "Interface" ) );

    ui->gbWaterMeterFeatures->setTitle ( tr ( "Water meter features" ) );
    ui->lbNominalDiameter->setText ( tr ( "Nominal diameter:" ) );
    ui->lbMaximumFlow->setText ( tr ( "Maximum flow:" ) );
    ui->lbNominalFlow->setText ( tr ( "Nominal flow:" ) );
    ui->lbTransitionFlow->setText ( tr ( "Transition flow:" ) );
    ui->lbMinimumFlow->setText ( tr ( "Minimum flow:" ) );
    ui->lbMaximumError->setText ( tr ( "Maximum error:" ) );
    ui->lbNominalError->setText ( tr ( "Nominal error:" ) );

    ui->lbNominalDiameterUnit->setText ( tr ( "[mm]" ) );
    ui->lbMaximumFlowUnit->setText ( tr ( "[l/h]" ) );
    ui->lbNominalFlowUnit->setText ( tr ( "[l/h]" ) );
    ui->lbTransitionFlowUnit->setText ( tr ( "[l/h]" ) );
    ui->lbMinimumFlowUnit->setText ( tr ( "[l/h]" ) );
    ui->lbMaximumErrorUnit->setText ( tr ( "[%]" ) );
    ui->lbNominalErrorUnit->setText ( tr ( "[%]" ) );

    ui->pbNewSession->setText ( tr ( "New Session" ) );
    ui->pbExit->setText ( tr ( "Exit" ) );
}

MainWindow::MainWindow ( QWidget *parent )
    : QMainWindow ( parent )
    , ui ( new Ui::MainWindow ) {

    ui->setupUi ( this );
    inputData = new Dialog ( this );
    licenseDialog = new License ( this );
    helpAbout = new HelpAbout ( this );

    alignmentGroup = new QActionGroup ( this );
    alignmentGroup->addAction ( ui->action_English );
    alignmentGroup->addAction ( ui->action_Romana );
    ui->action_English->setCheckable ( true );
    ui->action_Romana->setCheckable ( true );
    ui->action_Romana->setChecked ( true );

    setWindowFlags ( Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint | Qt::Dialog | Qt::WindowTitleHint );
    Translate();

    ReadConfiguration();
    //setWindowIcon(QIcon(":/images/Elegantthemes-Beautiful-Flat-Water.64.png"));

    unsigned MAX_NR_WATER_METERS = std::stoi ( optionsConfiguration["maximum"] );
    unsigned NUMBER_ENTRIES_METER_FLOW_DB = sizeof ( MeterFlowDB ) / sizeof ( MeterFlowType );

    for ( int iter = 1; iter <=  MAX_NR_WATER_METERS; ++iter ) {
        std::string value = std::to_string ( iter );
        ui->cbNumberOfWaterMeters->addItem ( value.c_str() );
    }

    for ( int iter = 0; iter < NUMBER_ENTRIES_METER_FLOW_DB; ++iter ) {
        std::string nameWaterMeter = MeterFlowDB[iter].nameWaterMeter;
        ui->cbWaterMeterType->addItem ( nameWaterMeter.c_str() );
    }

    connect ( ui->cbNumberOfWaterMeters, &QComboBox::currentIndexChanged, this, &MainWindow::onNumberOfWaterMetersChanged );
    connect ( ui->cbWaterMeterType, &QComboBox::currentIndexChanged, this, &MainWindow::onMeterTypeChanged );

    connect ( ui->rbVolumetric, &QRadioButton::clicked, this, &MainWindow::onRbVolumeClicked );
    connect ( ui->rbGravitmetric, &QRadioButton::clicked, this, &MainWindow::onRbGavritmetricClicked );

    connect ( ui->rbManual, &QRadioButton::clicked, this, &MainWindow::onRbManualClicked );
    connect ( ui->rbInterface, &QRadioButton::clicked, this, &MainWindow::onRbGavritmetricClicked );

    connect ( ui->leTemperature, &QLineEdit::textChanged, this, &MainWindow::onAmbientTemperatureTextChanged );
    connect ( ui->leHumidity, &QLineEdit::textChanged, this, &MainWindow::onRelativeAirHumidityTextChanged );
    connect ( ui->lePressure, &QLineEdit::textChanged, this, &MainWindow::onAthmosphericPressureTextChanged );

    connect ( ui->pbNewSession, &QPushButton::clicked, this, &MainWindow::onNewSessionClicked );
    connect ( ui->pbExit, &QPushButton::clicked, this, &MainWindow::onExitApplication );

    connect ( this, SIGNAL ( meterTypeChangedSignal() ), inputData, SLOT ( onTypeMeterChanged() ) );
    connect ( this, SIGNAL ( numberOfWaterMetersChangedSignal() ), inputData, SLOT ( onNumberOfWaterMetersChanged() ) );
    connect ( this, SIGNAL ( measurementTypeChangedSignal() ), inputData, SLOT ( onMeasurementTypeChanged() ) );

    connect ( ui->action_License, SIGNAL ( triggered() ), this, SLOT ( onShowLicense() ) );
    connect ( ui->action_ExitApp, SIGNAL ( triggered() ), this,  SLOT ( onExitApplication() ) );
    connect ( ui->action_StartSession, SIGNAL ( triggered() ), this,  SLOT ( onNewSessionClicked() ) );
    connect ( ui->action_WaterDensity, SIGNAL ( triggered() ), this,  SLOT ( onWaterDensityPage() ) );
    connect ( ui->action_About, SIGNAL ( triggered() ), this, SLOT ( onHelpAbout() ) );
    connect ( ui->action_General_Description, SIGNAL ( triggered() ), this, SLOT ( onGeneralDescription() ) );
    connect ( ui->action_Romana, SIGNAL ( triggered() ), this, SLOT ( onSetRomanian() ) );
    connect ( ui->action_English, SIGNAL ( triggered() ), this, SLOT ( onSetEnglish() ) );

    QValidator *validatorNaturalNumber = new QIntValidator ( 0, 999999999, this );
    ui->leHumidity->setValidator ( validatorNaturalNumber );
    ui->leTemperature->setValidator ( validatorNaturalNumber );
    ui->leHumidity->setValidator ( validatorNaturalNumber );

    if ( optionsConfiguration.find ( "maximum" ) != optionsConfiguration.end() ) {
        size_t index = std::stoi ( optionsConfiguration["maximum"] );
        ui->cbNumberOfWaterMeters->setCurrentIndex ( index - 1 );
    } else {
        ui->cbNumberOfWaterMeters->setCurrentIndex ( 0 );
    }

    ui->rbGravitmetric->setChecked ( true );
    ui->rbManual->setChecked ( true );
    ui->leTemperature->setText ( "18" );
    ui->leHumidity->setText ( "51" );
    ui->lePressure->setText ( "1026" );

    ui->cbWaterMeterType->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->cbNumberOfWaterMeters->setStyleSheet ( "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); selection-background-color: rgb(240, 255, 240); selection-color: rgb(0, 0, 0);}" );
    ui->leTemperature->setStyleSheet ( "QLineEdit { background: rgb(240, 255, 240); selection-background-color: rgb(0, 0, 0); }" );
    ui->leHumidity->setStyleSheet ( "QLineEdit { background: rgb(240, 255, 240); color: rgb(0, 0, 0); }" );
    ui->lePressure->setStyleSheet ( "QLineEdit { background: rgb(240, 255, 240); color: rgb(0, 0, 0); }" );

    SelectMeterComboBox();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onMeterTypeChanged ( int index ) {
    SelectMeterComboBox();
    emit meterTypeChangedSignal();
}

void MainWindow::onNumberOfWaterMetersChanged ( int index ) {
    selectedInfo.entriesNumber = ui->cbNumberOfWaterMeters->currentText().toInt();
    emit numberOfWaterMetersChangedSignal();
}

void MainWindow::onNewSessionClicked() {
    this->inputData->setModal ( false );
    this->inputData->show();
    this->inputData->showMaximized();
}

void MainWindow::onExitApplication() {
    this->close();
}

void MainWindow::onRbVolumeClicked() {
    selectedInfo.rbVolumetric = ui->rbVolumetric->isChecked();
    selectedInfo.rbGravitmetric = ui->rbGravitmetric->isChecked();
    emit measurementTypeChangedSignal();
}

void MainWindow::onRbGavritmetricClicked() {
    selectedInfo.rbVolumetric = ui->rbVolumetric->isChecked();
    selectedInfo.rbGravitmetric = ui->rbGravitmetric->isChecked();
    emit measurementTypeChangedSignal();
}

void MainWindow::onRbManualClicked() {
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbGravitmetric = ui->rbInterface->isChecked();
}

void MainWindow::onRbInterfaceClicked() {
    selectedInfo.rbManual = ui->rbManual->isChecked();
    selectedInfo.rbGravitmetric = ui->rbInterface->isChecked();
}

void MainWindow::onAmbientTemperatureTextChanged() {
    selectedInfo.ambientTemperature = ui->leTemperature->text().toInt();
}

void MainWindow::onRelativeAirHumidityTextChanged() {
    selectedInfo.athmosphericPressure = ui->lePressure->text().toInt();
}

void MainWindow::onAthmosphericPressureTextChanged() {
    selectedInfo.relativeAirHumidity = ui->leHumidity->text().toInt();
}

void MainWindow::onGeneralDescription() {
    QString htmlFile = QDir::temp().path() + QString ( "/5igsg2ly2v.html" );
    std::ofstream generalDescriptionHtmlFile ( htmlFile.toStdString() );
    std::stringstream output;

    if ( ENGLISH == selectedInfo.selectedLanguage ) {
        output <<
               "<!DOCTYPE html>"
               "<html>"
               "   <head>"
               "      <title>WStreamLab 1.0 Windows OS</title>"
               "   </head>"
               "   <body  oncopy=\"return false\" onpaste=\"return false\" oncut=\"return false\">"
               "   <div onmousedown=\"return false\" onselectstart=\"return false\">"
               "   <h2 style=\"font-family:Courier; font-size: 20px; color:Black;\"> [ WWStreamLab 1.0 Windows OS ]</h2>"
               "   <h3 style=\"font-family:Courier; color:Blue; font-size: 18px; background-color:powderblue;\">"
               "   The WStreamLab application is designed to be used in conjunction with a water meter testing bench.</br></br>"
               "   The water meter testing bench is the necessary measure instrument for the test and repair of water meter in metrological service, water meter manufacture, water supply company and other industrial establishments.</br></br>"
               "   As each client has different and specific needs, we design and construct test benches to fit your needs, based on our largely proven experience throughout the years.</br></br>"
               "   A Water Meter Test Bench is equipment that can be built from a simple and completely manually operated machine, to the highest levels of high-tech, designed with automatic controls, and software and hardware support.</br></br>"
               "   Each project is discussed with the client and tailor-made to fit both the technical needs and budget constraints.</br></br>"
               "   The Test Bench can be in the following sort and diameters (water meters range) DN15 - DN40, DN15 - DN50, DN50 - DN200.</br></br>"
               "   Measurement method from the point of  counted volume are as follows:</br></br>"
               "   - Reference flow meter (comparative method);</br></br>"
               "   - Weighing scales (gravimetric method);</br></br>"
               "   In the latter option, we utilize high precision and performance digital scales and  include comparative method.</br></br>"
               "   The both methods are used electromagnetic flow meters of high precision.</br>"
               "   </body>"
               "</html>";
    } else {
        output <<
               "<!DOCTYPE html>"
               "<html>"
               "   <head>"
               "      <title>WStreamLab 1.0 Windows OS</title>"
               "   </head>"
               "   <body  oncopy=\"return false\" onpaste=\"return false\" oncut=\"return false\">"
               "   <div onmousedown=\"return false\" onselectstart=\"return false\">"
               "   <h2 style=\"font-family:Courier; font-size: 20px; color:Black;\"> [ WWStreamLab 1.0 Windows OS ]</h2>"
               "   <h3 style=\"font-family:Courier; color:Blue; font-size: 18px; background-color:powderblue;\">"
               "   Aplicația WStreamLab este concepută pentru a fi utilizată împreună cu un ștand de testare a contoarelor de apă.</br></br>"
               "   Ștandul de testare a contoarelor de apă este instrumentul de măsură necesar pentru testarea și repararea contoarelor de apă în cadrul serviciilor de metrologie, al fabricării contoarelor de apă, al companiilor de alimentare cu apă și al altor unități industriale.</br></br>"
               "   Deoarece fiecare client are nevoi diferite și specifice, proiectăm și construim ștanduri de testare care să se potrivească nevoilor dumneavoastră, pe baza experienței noastre dovedite în mare măsură de-a lungul anilor.</br></br>"
               "   Un ștand de testare a contoarelor de apă este un echipament care poate fi construit de la o instalatie simplă și complet manuală, până la cele mai înalte niveluri de înaltă tehnologie, proiectat cu comenzi automate și cu suport software și hardware.</br></br>"
               "   Fiecare proiect este discutat cu clientul și este personalizat pentru a se potrivi atât nevoilor tehnice, cât și constrângerilor bugetare.</br></br>"
               "   Ștandul de testare poate fi în următoarele categorii și diametre (gama de apometre) DN15 - DN40, DN15 - DN50, DN50 - DN200.</br></br>"
               "   Metodele de măsurare din punct de vedere al volumului masurat sunt următoarele:</br></br>"
               "   - debitmetru de referință (metodă comparativă);</br></br>"
               "   - cântar pentru determinare masa (metoda gravimetrică);</br></br>"
               "   În a doua opțiune, utilizăm cântare digitale de înaltă precizie și performanță și includem metoda comparativă.</br></br>"
               "   La ambele metode se folosesc debitmetre electromagnetice de mare precizie.</br></br>"
               "   </body></br></br>"
               "</html>"
               "</br></br>";
    }

    generalDescriptionHtmlFile << output.str() << std::endl;

    QDesktopServices::openUrl ( QUrl::fromUserInput ( htmlFile ) );
}

void MainWindow::onWaterDensityPage() {
    QString htmlFile = QDir::temp().path() + QString ( "/5igsg2ly2t.html" );
    std::ofstream densityHtmlFile ( htmlFile.toStdString() );
    std::stringstream output;

    if ( ROMANIAN == selectedInfo.selectedLanguage ) {
        output <<
               "<!DOCTYPE html>"
               "<html>"
               "   <head>"
               "      <title>Densitate apa in functie de temperatura</title>"
               "   </head>"
               "   <body  oncopy=\"return false\" onpaste=\"return false\" oncut=\"return false\">"
               "     <div onmousedown=\"return false\" onselectstart=\"return false\">";
        output << "     <pre><h2  style=\"color:DodgerBlue\">";
        output << "Tabelul de mai jos reprezinta densitatea apei in kg/m² in functie de temperatura intre 0 si 100°C</br>"
               "cu pas de 0.1°C la presiune normala (1013.25 kPa). Aceste valori sunt generate prin interpolare</br>"
               "plecand de la datele existente in apliactie.</pre></br></br>";
        output << "     <pre>   T [°C]  ρ[kg/m²]</pre><hr />";
    } else {
        output <<
               "<!DOCTYPE html>"
               "<html>"
               "   <head>"
               "      <title>Water density by temperature</title>"
               "   </head>"
               "   <body  oncopy=\"return false\" onpaste=\"return false\" oncut=\"return false\">"
               "     <div onmousedown=\"return false\" onselectstart=\"return false\">";
        output << "     <pre><h2  style=\"color:DodgerBlue\">";
        output << "The table below shows the density of water in kg/m² for different temperatures between 0 and 100°C</br>"
               "with the step of 0.1°C under normal pressure (1013.25 kPa). These values ​​are generated by interpolation</br>"
               "starting from the existing database in the application.</pre></br></br>";
        output << "     <pre>   T [°C]  ρ[kg/m²]</pre><hr />";
    }

    for ( int i = 0; i <= 1000; ++i ) {

        double temperature = 0.1 * i;
        double density = quadraticInterpolationTemperature ( temperature, 998.2009 );
        output << "     <pre>   " << std::fixed << std::setprecision ( 1 ) << temperature
               << "     " << std::setprecision ( 4 ) << density << "</pre>";

        if ( ( i + 1 ) % 10 == 0 ) {
            output << "<hr />\n";
        }
    }

    output << "     </h2>"
           "     </div>"
           "   </body>"
           "</html>";

    densityHtmlFile << output.str() << std::endl;

    QDesktopServices::openUrl ( QUrl::fromUserInput ( htmlFile ) );
    QFile ( htmlFile ).remove();
}

void MainWindow::onHelpAbout() {
    helpAbout->setModal ( true );
    helpAbout->show();
}

void MainWindow::onSetRomanian() {

    QString qmPath = qApp->applicationDirPath() + "/translations";

    if ( appTranslator ) {
        qApp->removeTranslator ( appTranslator );
    }

    appTranslator = new QTranslator ( nullptr );

    if ( appTranslator->load ( qmPath + "/romanian.qm" ) ) {
        qApp->installTranslator ( appTranslator );
        Translate();
        inputData->Translate();
        licenseDialog->Translate();
        helpAbout->Translate();
    }

    selectedInfo.selectedLanguage = ROMANIAN;
}

void MainWindow::onSetEnglish() {
    QString qmPath = qApp->applicationDirPath() + "/translations";

    if ( appTranslator ) {
        qApp->removeTranslator ( appTranslator );
    }

    appTranslator = new QTranslator ( nullptr );

    if ( appTranslator->load ( qmPath + "/english.qm" ) ) {
        qApp->installTranslator ( appTranslator );
        Translate();
        inputData->Translate();
        licenseDialog->Translate();
        helpAbout->Translate();
    }

    selectedInfo.selectedLanguage = ENGLISH;
}

void MainWindow::mousePressEvent ( QMouseEvent *event ) {
    this->raise();
}

void MainWindow::onShowLicense() {
    helpAbout->setModal ( true );
    licenseDialog->show();
}
