/*
 *  Author: Constantin
 *  File:   tableBoard.h
 */

#ifndef TABLEBOARD_H
#define TABLEBOARD_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QKeyEvent>
#include <sstream>
#include "report.h"

namespace Ui
{
    class TableBoard;
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

class TableBoard : public QDialog
{
    Q_OBJECT

public:
    explicit TableBoard(QWidget *_parent = nullptr);
    ~TableBoard();

    void ValidatorInput();
    void PopulateTable();
    static void printPdfThread(QString report);
    void Translate();

private:
    QWidget *parent;
    Ui::TableBoard *ui;

    // Member variables grouped by functionality
    size_t entries {0};
    ReportMeasurements *reportMeasurementsDialog {nullptr};
    std::string nameWaterMeter;
    double minimumFlowMain {0};
    double transitoriuFlowMain {0};
    double nominalFlowMain {0};
    double nominalError {0};
    double maximumError {0};

    std::vector<QLabel *> vectorNumber;
    std::vector<QCheckBox *> vectorCheckNumber;
    std::vector<QLineEdit *> vectorSerialNumber;
    std::vector<QLineEdit *> vectorFirstIndexStart;
    std::vector<QLineEdit *> vectorFirstIndexStop;
    std::vector<QLineEdit *> vectorFirstError;
    std::vector<QLineEdit *> vectorSecondIndexStart;
    std::vector<QLineEdit *> vectorSecondIndexStop;
    std::vector<QLineEdit *> vectorSecondError;
    std::vector<QLineEdit *> vectorThirdIndexStart;
    std::vector<QLineEdit *> vectorThirdIndexStop;
    std::vector<QLineEdit *> vectorThirdError;

    static QString report;

    bool eventFilter(QObject *, QEvent *);

private slots:
    void onTypeMeterChanged();
    void onNumberOfWaterMetersChanged();
    void onMeasurementTypeChanged();
    void onSelectAllChanged();
    void onCbClicked(bool status);
    void onCalculateClicked();
    void onCleanClicked();
    void onCloseClicked();
    void onSaveCurrentInputDataClicked();
    void onOpenInputDataClicked();
    void onPrintPdfDocClicked();
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void copyTextBetweenWidgets(const QString& startRegex, const QString& stopRegex);
    void onCopy12Clicked();
    void onCopy23Clicked_new();
    void onReportClicked();

protected:
    void showEvent(QShowEvent *event);
};

#endif // TABLEBOARD_H
