/**
 * \file mainwindow.h
 * \brief Header file for the MainWindow class.
 *
 * This file defines the MainWindow class, which represents the main window
 * of the application.
 *
 * \author Constantin
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QActionGroup>                       // Qt class for grouping actions together.
#include <QApplication>                       // Qt class for managing the application's control flow.
#include <QMainWindow>                        // Qt class for main application window.
#include <QSerialPort>                        // Qt class for accessing serial port hardware.
#include <QSerialPortInfo>                    // Qt class for retrieving information about available serial ports.
#include <QTranslator>                        // Qt class for providing translations in the application.
#include <QtSerialBus/QModbusRtuSerialClient> // Qt class for Modbus RTU serial client communication.
#include "helpabout.h"                        // Custom header for HelpAbout class.
#include "interface.h"                        // Custom header for Interface class.
#include "license.h"                          // Custom header for License class.
#include "tableBoard.h"                       // Custom header for TableBoard class.

enum SELECTED_LANGUAGE {
    ROMANIAN,
    ENGLISH,
    DEFAULT = ENGLISH
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * \brief The SelectedInfo struct holds selected information related to a device or configuration.
 *
 * This struct encapsulates various parameters and flags that represent selected settings
 * and state for a device or application configuration.
 */
struct SelectedInfo {
    /**
     * \brief Default constructor initializes all members to default values.
     */
    SelectedInfo()
        : density_20{0.0f},          /**< Density at 20 degrees Celsius. */
          entriesNumber{0},          /**< Number of entries. */
          nominalDiameter{0},        /**< Nominal diameter of the device. */
          nominalFlow{0.0f},         /**< Nominal flow rate. */
          maximumFlow{0.0f},         /**< Maximum flow rate. */
          transitionFlow{0.0f},      /**< Transition flow rate. */
          minimumFlow{0.0f},         /**< Minimum flow rate. */
          nominalError{0.0f},        /**< Nominal error. */
          maximumError{0.0f},        /**< Maximum error. */
          ambientTemperature{0},     /**< Ambient temperature. */
          athmosphericPressure{0},   /**< Atmospheric pressure. */
          relativeAirHumidity{0},    /**< Relative air humidity. */
          rbGravimetric_new{true},   /**< Gravimetric measurement flag. */
          rbVolumetric{false},       /**< Volumetric measurement flag. */
          rbManual{true},            /**< Manual operation mode flag. */
          rbInterface{false},        /**< Interface operation mode flag. */
          rbTerminal{false},         /**< Terminal operation mode flag. */
          serialPort_1{false},       /**< Serial port usage flag. */
          serialPort_2{false},       /**< Serial port usage flag. */
          selectedLanguage{ROMANIAN} /**< Selected language enumeration. */
    {
    }

    float       density_20;  /**< Density at 20 degrees Celsius. */
    std::string pathResults; /**< Path for storing results. */

    size_t      entriesNumber; /**< Number of entries. */
    std::string certificate;   /**< Certificate information. */

    std::string nameWaterMeter;  /**< Name of the water meter. */
    unsigned    nominalDiameter; /**< Nominal diameter of the device. */
    double      nominalFlow;     /**< Nominal flow rate. */
    double      maximumFlow;     /**< Maximum flow rate. */
    double      transitionFlow;  /**< Transition flow rate. */
    double      minimumFlow;     /**< Minimum flow rate. */
    double      nominalError;    /**< Nominal error. */
    double      maximumError;    /**< Maximum error. */

    std::string ambientTemperature;   /**< Ambient temperature. */
    std::string athmosphericPressure; /**< Atmospheric pressure. */
    std::string relativeAirHumidity;  /**< Relative air humidity. */

    bool rbGravimetric_new; /**< Gravimetric measurement flag. */
    bool rbVolumetric;      /**< Volumetric measurement flag. */

    bool rbManual;    /**< Manual operation mode flag. */
    bool rbInterface; /**< Interface operation mode flag. */
    bool rbTerminal;  /**< Terminal operation mode flag. */

    bool              serialPort_1;     /**< Serial port usage flag. */
    bool              serialPort_2;     /**< Serial port usage flag. */
    SELECTED_LANGUAGE selectedLanguage; /**< Selected language enumeration. */
};

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    /**
     * \brief Constructs a MainWindow object.
     * \param parent The parent widget (default: nullptr).
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /**
     * \brief Destroys the MainWindow object.
     */
    ~MainWindow();

    SelectedInfo                       selectedInfo;                    /**< Holds selected information related to the application. */
    Ui::MainWindow*                    ui{nullptr};                     /**< Pointer to the UI components of the main window. */
    TableBoard*                        inputData{nullptr};              /**< Pointer to the input data board. */
    License*                           licenseDialog{nullptr};          /**< Pointer to the license dialog. */
    HelpAbout*                         helpAbout{nullptr};              /**< Pointer to the help/about dialog. */
    Interface*                         interfaceDialog{nullptr};        /**< Pointer to the interface dialog. */
    QActionGroup*                      alignmentGroup{nullptr};         /**< Action group for alignment settings. */
    QStatusBar*                        statusBar{nullptr};              /**< The status bar widget for displaying messages. */
    unsigned                           MAX_NR_WATER_METERS{20};         /**< Maximum number of water meters supported. */
    unsigned                           NUMBER_ENTRIES_METER_FLOW_DB{0}; /**< Number of entries in meter flow database. */
    std::map<std::string, std::string> optionsConfiguration;            /**< Map for storing configuration options. */
    QList<QSerialPortInfo>             ports;
    QString                            statusBarMessage;

    typedef const wchar_t* (*EnumerateSerialPorts)(); /**< Function pointer type for serial port enumeration. */
    EnumerateSerialPorts serialPorts{nullptr};        /**< Pointer to the function for serial port enumeration. */

    /**
     * \brief Translates the UI components to the selected language.
     */
    void Translate();

    /**
     * \brief Sets the value of a QLabel with specified precision.
     * \param label Pointer to the QLabel widget.
     * \param value Value to set on the label.
     * \param precision Number of decimal places for the value.
     */
    void setLabelValue(QLabel* label, double value, int precision);

    /**
     * \brief Updates the selected information based on user inputs.
     */
    void updateSelectedInfo();

    /**
     * \brief Initializes the ComboBox for selecting meter types.
     */
    void SelectMeterComboBox();

    /**
     * \brief Reads the application configuration from settings.
     */
    void ReadConfiguration();

    /**
     * \brief Sets the default configuration settings.
     */
    void SetDefaultConfiguration();

    /**
     * \brief Centers a given widget to the screen.
     * \param widget Pointer to the widget to center.
     */
    void CenterToScreen(QWidget* widget);

    /**
     * \brief Sets the message in the status bar.
     *
     * \param message The message to set in the status bar.
     */
    void setStatusBarMessage(const QString message);

  protected:
    /**
     * \brief Handles mouse press events on the main window.
     * \param event The mouse event.
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * \brief Filters events for the main window.
     * \param obj The object that received the event.
     * \param event The event that occurred.
     * \return True if the event was handled, otherwise false.
     */
    bool eventFilter(QObject* obj, QEvent* event) override {
        if (event->type() == QEvent::MouseButtonPress) {
            // Check if the event occurred on this window
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (rect().contains(mouseEvent->pos())) {
                activateWindow();
            }
        }
        return QMainWindow::eventFilter(obj, event);
    }

  private slots:
    /**
     * \brief Slot function called when the meter type is changed.
     * \param index The new index of the meter type.
     */
    void onMeterTypeChanged(int index);

    /**
     * \brief Slot function called when the number of water meters is changed.
     * \param index The new index of the number of water meters.
     */
    void onNumberOfWaterMetersChanged(int index);

    /**
     * \brief Slot function called when a new session is started.
     */
    void onNewSessionClicked();

    /**
     * \brief Slot function called when the application is exited.
     */
    void onExitApplication();

    /**
     * \brief Slot function called when the gravimetric measurement mode is selected.
     */
    void onRbGravimetricClicked();

    /**
     * \brief Slot function called when the volumetric measurement mode is selected.
     */
    void onRbVolumeClicked();

    /**
     * \brief Slot function called when the manual operation mode is selected.
     */
    void onRbManualClicked();

    /**
     * \brief Slot function called when the interface operation mode is selected.
     */
    void onRbInterfaceClicked();

    /**
     * \brief Slot function called when the ambient temperature text is changed.
     */
    void onAmbientTemperatureTextChanged();

    /**
     * \brief Slot function called when the relative air humidity text is changed.
     */
    void onRelativeAirHumidityTextChanged();

    /**
     * \brief Slot function called when the atmospheric pressure text is changed.
     */
    void onAtmosphericPressureTextChanged();

    /**
     * \brief Slot function called when the Romanian language is selected.
     */
    void onSetRomanian();

    /**
     * \brief Slot function called when the English language is selected.
     */
    void onSetEnglish();

    /**
     * \brief Slot function called when the general description action is triggered.
     */
    void onGeneralDescription();

    /**
     * \brief Slot function called when the license dialog is requested to be shown.
     */
    void onShowLicense();

    /**
     * \brief Slot function called when the water density page action is triggered.
     */
    void onWaterDensityPage();

    /**
     * \brief Slot function called when the help/about dialog is requested to be shown.
     */
    void onHelpAbout();

    /**
     * \brief Slot function called when the port settings action is triggered.
     */
    void onPortSettings();

    /**
     * \brief Handles close events for the main window.
     * \param event The close event.
     */
    void closeEvent(QCloseEvent* event) override;

  signals:
    /**
     * \brief Signal emitted when the number of water meters is changed.
     */
    void numberOfWaterMetersChangedSignal();

    /**
     * \brief Signal emitted when the meter type is changed.
     */
    void meterTypeChangedSignal();

    /**
     * \brief Signal emitted when the measurement type is changed.
     */
    void measurementTypeChangedSignal();
};
#endif // MAINWINDOW_H
