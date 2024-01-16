/*
 *  Author: Constantin
 *  File:    mainwindow.h
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
    SelectedInfo():
        density_20{0},
        entriesNumber{0},
        nominalDiameter{0},
        nominalFlow{0},
        maximumFlow{0},
        trasitionFlow{0},
        minimumFlow{0},
        nominalError{0},
        maximumError{0},
        ambientTemperature{},
        athmosphericPressure{},
        relativeAirHumidity{},
        rbGravimetric_new{true},
        rbVolumetric{false},
        rbManual{true},
        rbInterface{false},
        rbTerminal{false},
        serialPort{false},
        selectedLanguage{ROMANIAN},
        modbusDevice{nullptr}
    {
    };

    float density_20;
    std::string pathResults;

    size_t entriesNumber;
    std::string certificate;

    std::string nameWaterMeter;
    unsigned nominalDiameter;
    double nominalFlow;
    double maximumFlow;
    double trasitionFlow;
    double minimumFlow;
    double nominalError;
    double maximumError;

    std::string ambientTemperature;
    std::string athmosphericPressure;
    std::string relativeAirHumidity;
    
    bool rbGravimetric_new;
    bool rbVolumetric;

    bool rbManual;
    bool rbInterface;
    bool rbTerminal;

    bool serialPort;
    SELECTED_LANGUAGE selectedLanguage;

    QModbusClient *modbusDevice;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SelectedInfo selectedInfo;

    Ui::MainWindow *ui {nullptr};
    TableBoard *inputData{nullptr};
    License *licenseDialog{nullptr};
    HelpAbout *helpAbout;
    Interface *interfaceDialog{nullptr};
    QActionGroup *alignmentGroup;
    LedIndicator *LED;

    void Translate();
    void setLabelValue(QLabel* label, double value, int precision);
    void updateSelectedInfo();
    void SelectMeterComboBox();
    void ReadConfiguration();
    void CenterToScreen(QWidget *widget);

    unsigned MAX_NR_WATER_METERS {20};
    unsigned NUMBER_ENTRIES_METER_FLOW_DB {0};
    std::map<std::string, std::string> optionsConfiguration;

    typedef const wchar_t *(*EnumerateSerialPorts)();
    EnumerateSerialPorts serialPorts{nullptr};

  protected:
    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            // Check if the event occurred on this window
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (rect().contains(mouseEvent->pos()))
            {
                activateWindow();
            }
        }
        return QMainWindow::eventFilter(obj, event);
    }

  private slots:
    void onMeterTypeChanged(int index);
    void onNumberOfWaterMetersChanged(int index);
    void onNewSessionClicked();
    void onExitApplication();
    void onRbGavritmetricClicked();
    void onRbVolumeClicked();
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
    void closeEvent(QCloseEvent *event) override;

  signals:
    void numberOfWaterMetersChangedSignal();
    void meterTypeChangedSignal();
    void measurementTypeChangedSignal();

};
#endif // MAINWINDOW_H
