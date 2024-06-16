/**
 * \file report.h
 * \brief Header file for the ReportMeasurements class.
 *
 * This file defines the ReportMeasurements class, which provides functionality
 * for generating and managing reports of measurements.
 *
 * \author Constantin
 * \date Insert date
 */

#ifndef REPORT_H
#define REPORT_H

// Qt headers for various UI components and utilities
#include <QDialog>      // Modal or modeless dialog window
#include <QCheckBox>    // Checkbox UI element
#include <QLineEdit>    // Single-line text input widget
#include <QString>      // Qt's string class with Unicode support
#include <QTimer>       // Timer for delayed or periodic execution
#include <vector>       // Standard C++ vector container

// Project-specific definitions and constants
#include "definitions.h"


namespace Ui
{
class report;
}

/**
 * \brief The ReportMeasurements class provides a dialog for reporting measurements.
 *
 * This class allows users to generate and print a report based on selected checkboxes
 * and serial numbers. It supports PDF generation and provides signals upon completion.
 */
class ReportMeasurements : public QDialog
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a ReportMeasurements dialog.
     * \param parent The parent widget.
     * \param vectorCheckNumber Vector of QCheckBox pointers for measurement selection.
     * \param vectorSerialNumber Vector of QLineEdit pointers for serial numbers.
     * \param resultAllTests Array of QStrings containing test results.
     */
    explicit ReportMeasurements(QWidget *parent,
                                const std::vector<QCheckBox *> &vectorCheckNumber,
                                const std::vector<QLineEdit *> &vectorSerialNumber,
                                const QString resultAllTests[MAX_ARRAY_SIZE]);

    /**
     * \brief Destroys the ReportMeasurements dialog.
     */
    ~ReportMeasurements();

    /**
     * \brief Translates the UI elements to the selected language.
     */
    void Translate();

    /**
     * \brief Static method to start a thread for PDF generation.
     * \param report The report to generate in PDF format.
     */
    static void printPdfThread(QString report);

signals:
    /**
     * \brief Signal emitted when PDF generation is completed.
     */
    void pdfGenerationCompleted();

private slots:
    /**
     * \brief Slot invoked when the Print button is clicked.
     */
    void onPrintClicked();

    /**
     * \brief Slot invoked when the Close button is clicked.
     */
    void onCloseClicked();

    /**
     * \brief Slot to enable the "Generare BV" button.
     */
    void enableGenerareBvButton();

private:
    Ui::report *ui; ///< User interface object.
    std::vector<QCheckBox *> vectorCheckNumberCopy; ///< Copy of vectorCheckNumber.
    std::vector<QLineEdit *> vectorSerialNumberCopy; ///< Copy of vectorSerialNumber.
    QString resultAllTestsCopy[MAX_ARRAY_SIZE]; ///< Copy of resultAllTests.
    QTimer *QTimerGenerareBv; ///< Timer object for enabling "Generare BV" button.
    QWidget *parentWidget; ///< Parent widget (avoid renaming for now to maintain consistency).
};

#endif // REPORT_H
