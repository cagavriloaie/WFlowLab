/*
 *  Author: Constantin
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QApplication>
#include <QtSerialBus/QModbusRtuSerialClient>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTranslator>
#include "tableBoard.h"
#include "license.h"
#include "helpabout.h"
#include "interface.h"
#include "ledindicator.h"

enum SELECTED_LANGUAGE
{
    ROMANIAN,
    ENGLISH,
    DEFAULT = ENGLISH
};

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

struct SelectedInfo
{

    float density_20{0};
    std::string pathResults{""};

    size_t entriesNumber {0};
    std::string certificate;

    std::string nameWaterMeter;
    unsigned nominalDiameter {0};
    double nominalFlow;
    double maximumFlow {0};
    double trasitionFlow {0};
    double minimumFlow {0};
    double nominalError {0};
    double maximumError {0};

    double ambientTemperature {0};
    double relativeAirHumidity {0};
    double athmosphericPressure {0};

    bool rbVolumetric{true};
    bool rbGravitmetric{false};

    bool rbManual {true};
    bool rbInterface {false};
    bool rbTerminal {false};

    bool serialPort {false};
    SELECTED_LANGUAGE selectedLanguage{ROMANIAN};

  //  QSerialPort *serialPortSelected{nullptr};
    QModbusClient *modbusDevice{nullptr};

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SelectedInfo selectedInfo;

    Ui::MainWindow *ui {nullptr};
    Dialog *inputData{nullptr};
    License *licenseDialog{nullptr};
    HelpAbout *helpAbout;
    Interface *interfaceDialog{nullptr};
    QActionGroup *alignmentGroup;
    LedIndicator *LED;

    void Translate();
    void SelectMeterComboBox();
    void ReadConfiguration();

    unsigned MAX_NR_WATER_METERS {20};
    unsigned NUMBER_ENTRIES_METER_FLOW_DB {0};
    std::map<std::string, std::string> optionsConfiguration;

    typedef const wchar_t *(*EnumerateSerialPorts)();
    EnumerateSerialPorts serialPorts{nullptr};

  private slots:
    void onMeterTypeChanged(int index);

    void onNumberOfWaterMetersChanged(int index);
    void onNewSessionClicked();
    void onExitApplication();

    void onRbVolumeClicked();
    void onRbGavritmetricClicked();

    void onRbManualClicked();
    void onRbInterfaceClicked();

    void onAmbientTemperatureTextChanged();
    void onRelativeAirHumidityTextChanged();
    void onAthmosphericPressureTextChanged();

    void onSetRomanian();
    void onSetEnglish();
    void onGeneralDescription();
    void onShowLicense();
    void onWaterDensityPage();
    void onHelpAbout();
    void onPortSettings();

    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

  signals:
    void numberOfWaterMetersChangedSignal();
    void meterTypeChangedSignal();
    void measurementTypeChangedSignal();

};
#endif // MAINWINDOW_H
