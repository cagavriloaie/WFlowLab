/**
 * \file interface.h
 * \brief Header file for the Interface class.
 *
 * This file defines the Interface class, which represents a dialog
 * for configuring and managing interface settings.
 *
 * \author Constantin
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDir>        // Qt class for handling directories and their contents.
#include <QMessageBox> // Qt class for displaying modal dialog boxes with messages.
#include <QSerialPortInfo>
#include <vector> // Standard C++ container class for dynamic arrays.

namespace Ui {
class Interface;
}

/**
 * \class Interface
 * \brief The Interface class represents a dialog window for configuring and managing settings.
 *
 * This class extends QDialog and provides functionalities for interacting with various
 * widgets such as buttons, combo boxes, and LEDs. It manages serial port connections,
 * Modbus configurations, and UI translations.
 */
class Interface : public QDialog {
    Q_OBJECT

  public:
    /**
     * \brief Constructs the Interface dialog.
     * \param parent The parent widget (optional).
     */
    explicit Interface(QWidget* parent = nullptr);

    /**
     * \brief Destroys the Interface dialog.
     */
    ~Interface();

    /**
     * \brief Translates UI elements to the current language.
     *
     * This function translates all UI elements to the current language
     * using the current locale settings.
     */
    void Translate();

    /**
     * \brief Checks if the Modbus address is valid.
     * \param address The Modbus address to check.
     * \return true if the address is valid, false otherwise.
     */
    bool checkModbusAddresses();

  private:
    Ui::Interface*      ui;                      /**< The user interface object. */
    QVector<QString>    entries;                 /**< A vector of strings for storing entries. */
    bool                isOpenModbusPort{false}; /**< Flag indicating if the Modbus port is open. */
    std::vector<qint16> nodesModbusCom1;
    std::vector<qint16> nodesModbusCom2;

    /**
     * \brief Disconnects from the serial port.
     *
     * This function disconnects from the current serial port,
     * closing the connection and releasing associated resources.
     */
    void DisconnectSerialPort();

    QList<QSerialPortInfo> serialPorts;

  private slots:
    /**
     * \brief Slot function called when the Close button is clicked.
     */
    void onCloseClicked();

    /**
     * \brief Slot function called when the Test Configuration button is clicked.
     */
    void onConnectClicked();

    /**
     * \brief Slot function called when the Test Configuration button is clicked.
     */
    void onTestConfigurationClicked();

    /**
     * \brief Slot function called when the Save Configuration button is clicked.
     */
    void onSaveConfigurationClicked();

    /**
     * \brief Slot function called when the Refresh Serial Port button is clicked.
     */
    void onRefreshSerialPortClicked();

    /**
     * \brief Slot function called when the selected serial port changes.
     */
    void onSelectSerialChanged();

    /**
     * \brief Slot function called when the selected baud rate changes.
     */
    void onBaudRateChanged();

    /**
     * \brief Slot function called when the selected data bits configuration changes.
     */
    void onSelectDataBitsChanged();

    /**
     * \brief Slot function called when the selected parity configuration changes.
     */
    void onSelectParityChanged();

    /**
     * \brief Slot function called when the selected stop bits configuration changes.
     */
    void onSelectStopBitsChanged();

    /**
     * \brief Slot function called when Modbus data is ready to be read.
     */
    void onReadModbusReady();

    /**
     * \brief Overridden function called when the dialog is shown.
     * \param event The show event.
     */
    void showEvent(QShowEvent* event) override;
};
#endif // INTERFACE_H
