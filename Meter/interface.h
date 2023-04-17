#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDialog>
#include <Qstring>
#include <QVector>
#include <QtSerialPort/QSerialPort>
#include <QtSerialBus/QModbusRtuSerialServer>

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

  private:
    Ui::Interface *ui;
    QVector<QString> entries;
    bool isOpenPort {false};
    void DisconnectSerialPort();

  private slots:

    void onCloseClicked();
    void onSaveClicked();
    void onRefreshClicked();

    void showEvent(QShowEvent *event);

    void onSelectSerialChanged();
    void onBaudRateChanged();
    void onSelectDataBitsnChanged();
    void onSelectParityChanged();
    void onSelectStopBitsChanged();
};

#endif // INTERFACE_H
