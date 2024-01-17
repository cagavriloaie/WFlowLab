/*
 *  Author: Constantin
 *  File:   report.h
 */

#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QString>
#include <QTimer>
#include <vector>

#include "definitions.h"

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
                                const QString resultAllTests[MAX_ARRAY_SIZE]);
    ~ReportMeasurements();

    void Translate();
    static void printPdfThread(QString report);

signals:
    void pdfGenerationCompleted();

private slots:
    void onPrintClicked();
    void onCloseClicked();
    void enableGenerareBvButton();

private:
    Ui::report *ui;
    std::vector<QCheckBox *> vectorCheckNumberCopy;
    std::vector<QLineEdit *> vectorSerialNumberCopy;
    QString resultAllTestsCopy[MAX_ARRAY_SIZE];
    QTimer *QTimerGenerareBv;
    QWidget *parentWidget; // Rename to avoid conflict with member variable name
};

#endif // REPORT_H
