#ifndef SERIAL_H
#define SERIAL_H

#include <QDialog>

namespace Ui {
class Serial;
}

class Serial : public QDialog {
    Q_OBJECT

public:
    explicit Serial ( QWidget *parent = nullptr );
    ~Serial();
    void Translate (  );

private:
    Ui::Serial *ui;

private slots:
    void onCloseClicked();
};

#endif // SERIAL_H
