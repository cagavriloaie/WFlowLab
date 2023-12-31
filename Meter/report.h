/*
 *  Author: Constantin
 *  File:   report.h
 */

#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <vector>
#include <QCheckBox>
#include <QLineEdit>

namespace Ui
{
    class report;
}

class ReportMeasurements : public QDialog
{
    Q_OBJECT

  public:
    explicit ReportMeasurements(QWidget *parent,
                                const std::vector<QCheckBox *> &vectorCheckNumber,
                                const std::vector<QLineEdit *> &vectorSerialNumber,
                                const QString resultAllTests[20]);
    ~ReportMeasurements();

    void Translate();

  private slots:
    void onPrintClicked();
    void onCloseClicked();

  private:
    Ui::report *ui;
    std::vector<QCheckBox *> vectorCheckNumberCopy;
    std::vector<QLineEdit *> vectorSerialNumberCopy;
    QString resultAllTestsCopy[20];
    QWidget *parentWidget; // Rename to avoid conflict with member variable name
};

#endif // REPORT_H
