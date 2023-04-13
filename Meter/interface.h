#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDialog>

namespace Ui
{
class Interface;
}

class Interface : public QDialog
    {
        Q_OBJECT

    public:
        explicit Interface ( QWidget *parent = nullptr );
        ~Interface();
        void Translate (  );

    private:
        Ui::Interface *ui;

    private slots:

        void onCloseClicked();
        void onSaveClicked();
        void onRefreshClicked();

        void showEvent ( QShowEvent *event );

        void onSelectSerialChanged();
        void onBaudRateChanged();
        void onSelectDataBitsnChanged();
        void onSelectParityChanged();
        void onSelectStopBitsChanged();
    };

#endif // INTERFACE_H
