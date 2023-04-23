#ifndef LICENSE_H
#define LICENSE_H

#include <QDialog>

namespace Ui
{
    class Licence;
}

class License : public QDialog
{
    Q_OBJECT

  public:
    explicit License(QWidget *parent = nullptr);
    ~License();
    void Translate();

    Ui::Licence *ui;

  private slots:
    void showEvent(QShowEvent *event);
    void onCloseClicked();
};

#endif // LICENSE_H
