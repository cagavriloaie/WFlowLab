#ifndef LICENCE_H
#define LICENCE_H

#include <QDialog>

namespace Ui
{
class Licence;
}

class License : public QDialog
    {
        Q_OBJECT

    public:
        explicit License ( QWidget *parent = nullptr );
        ~License();
        void Translate();

        Ui::Licence *ui;

    private slots:
        void showEvent ( QShowEvent *event );
        void onCloseClicked();
    };

#endif // LICENCE_H
