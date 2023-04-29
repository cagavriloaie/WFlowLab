#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDialog>
#include <Qstring>
#include <QVector>
#include <QtSerialPort/QSerialPort>
#include <QtSerialBus/QModbusRtuSerialServer>
#include "ledindicator.h"

namespace Ui
{
    class Interface;
}

class Interface : public QDialog
{
    Q_OBJECT

  public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();
    void Translate();

    bool checkModbusAddress(qint16 address);
  private:
    Ui::Interface *ui;
    QVector<QString> entries;
    bool isOpenModbusPort {false};
    void DisconnectSerialPort();
    LedIndicator *ledStateTable[10];

  private slots:

    void onCloseClicked();
    void onTestConfigurationClicked();
    void onSaveConfigurationClicked();
    void onRefreshSerialPortClicked();

    void showEvent(QShowEvent *event);

    void onSelectSerialChanged();
    void onBaudRateChanged();
    void onSelectDataBitsnChanged();
    void onSelectParityChanged();
    void onSelectStopBitsChanged();

    void onReadModbusReady();
};

#endif // INTERFACE_H
