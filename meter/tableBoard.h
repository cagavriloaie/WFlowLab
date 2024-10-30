/**
 * \file tableBoard.h
 * \brief Header file for the TableBoard class.
 *
 * This file defines the TableBoard class, which represents a dialog
 * for managing and validating input data related to a table board.
 *
 * \author Constantin
 * \date Insert date
 */

#ifndef TABLEBOARD_H
#define TABLEBOARD_H

// Qt headers for various UI components and utilities
#include <QCheckBox> // Checkbox UI element
#include <QDialog>   // Modal or modeless dialog window
#include <QKeyEvent> // Keyboard event handling
#include <QLabel>    // Text or image display widget
#include <QLineEdit> // Single-line text input widget
#include <QTimer>    // Timer for delayed or periodic execution

// Standard C++ header for string stream operations
#include <sstream>

// Project-specific header for report generation
#include "report.h"

namespace Ui {
class TableBoard;
}

/**
 * \brief Converts a numeric value to a string with a specified precision.
 *
 * \tparam T Type of the numeric value (e.g., float, double, int).
 * \param a_value The numeric value to convert to a string.
 * \param n Precision (number of digits after the decimal point).
 * \return std::string The string representation of the numeric value with specified precision.
 */
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6) {
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

/**
 * \brief Dialog window for managing and displaying water meter test data in a table format.
 *
 * This class extends QDialog and provides functionality for input validation,
 * populating the table with data, and managing PDF report generation.
 */
class TableBoard : public QDialog {
    Q_OBJECT

  public:
    /**
     * \brief Constructs a TableBoard dialog.
     *
     * \param _parent Pointer to the parent widget (default: nullptr).
     */
    explicit TableBoard(QWidget* _parent = nullptr);

    /**
     * \brief Destroys the TableBoard dialog.
     */
    ~TableBoard();

    /**
     * \brief Validates input data in the table.
     *
     * Invoked to ensure input data in the table cells meets specified criteria.
     */
    void ValidatorInput();

    /**
     * \brief Populates the table with initial data.
     *
     * Initializes and fills the table with default or stored data.
     */
    void PopulateTable();

    /**
     * \brief Initiates a PDF generation process in a separate thread.
     *
     * \param report Path or identifier of the report to generate.
     */
    static void printPdfThread(QString report);

    /**
     * \brief Translates the UI components to the current language.
     *
     * Adjusts all visible UI elements to display text in the chosen language.
     */
    void Translate();

  private:
    QWidget*        parent; ///< Pointer to the parent widget.
    Ui::TableBoard* ui;     ///< User interface object for the TableBoard dialog.

    // Member variables grouped by functionality
    size_t              entries{0};                        ///< Number of entries in the table.
    ReportMeasurements* reportMeasurementsDialog{nullptr}; ///< Pointer to the report measurements dialog.
    std::string         nameWaterMeter;                    ///< Name of the water meter being tested.
    double              minimumFlowMain{0};                ///< Minimum flow rate.
    double              transitoriuFlowMain{0};            ///< Transitory flow rate.
    double              nominalFlowMain{0};                ///< Nominal flow rate.
    double              nominalError{0};                   ///< Nominal error.
    double              maximumError{0};                   ///< Maximum error.

    // Vectors for managing table widgets
    std::vector<QLabel*>    vectorNumber;           ///< Vector of labels for row numbers.
    std::vector<QCheckBox*> vectorCheckNumber;      ///< Vector of checkboxes for row selection.
    std::vector<QLineEdit*> vectorSerialNumber;     ///< Vector of line edits for serial numbers.
    std::vector<QLineEdit*> vectorFirstIndexStart;  ///< Vector of line edits for first index start values.
    std::vector<QLineEdit*> vectorFirstIndexStop;   ///< Vector of line edits for first index stop values.
    std::vector<QLineEdit*> vectorFirstError;       ///< Vector of line edits for first index error values.
    std::vector<QLineEdit*> vectorSecondIndexStart; ///< Vector of line edits for second index start values.
    std::vector<QLineEdit*> vectorSecondIndexStop;  ///< Vector of line edits for second index stop values.
    std::vector<QLineEdit*> vectorSecondError;      ///< Vector of line edits for second index error values.
    std::vector<QLineEdit*> vectorThirdIndexStart;  ///< Vector of line edits for third index start values.
    std::vector<QLineEdit*> vectorThirdIndexStop;   ///< Vector of line edits for third index stop values.
    std::vector<QLineEdit*> vectorThirdError;       ///< Vector of line edits for third index error values.

    static QString report;           ///< Static variable for storing report information.
    QTimer*        QTimerGenerareFM; ///< Timer object for generating FM.

    /**
     * \brief Event filter for intercepting events targeted at this object.
     *
     * \param obj Pointer to the QObject sending the event.
     * \param event Pointer to the QEvent being sent.
     * \return bool True if the event was handled; otherwise false.
     */
    bool eventFilter(QObject*, QEvent*);

  private slots:
    /**
     * \brief Slot called when the type of water meter is changed.
     */
    void onTypeMeterChanged();

    /**
     * \brief Slot called when the number of water meters is changed.
     */
    void onNumberOfWaterMetersChanged();

    /**
     * \brief Slot called when the measurement type is changed.
     */
    void onMeasurementTypeChanged();

    /**
     * \brief Slot called when the select all checkbox state changes.
     */
    void onSelectAllChanged();

    /**
     * \brief Slot called when a checkbox is clicked.
     *
     * \param status Current state of the checkbox (checked or unchecked).
     */
    void onCbClicked(bool status);

    /**
     * \brief Slot called when the calculate button is clicked.
     */
    void onCalculateClicked();

    /**
     * \brief Slot called when the clean button is clicked.
     */
    void onCleanClicked();

    /**
     * \brief Slot called when the close button is clicked.
     */
    void onCloseClicked();

    /**
     * \brief Slot called when the save current input data button is clicked.
     */
    void onSaveCurrentInputDataClicked();

    /**
     * \brief Slot called when the open input data button is clicked.
     */
    void onOpenInputDataClicked();

    /**
     * \brief Slot called when the print PDF document button is clicked.
     */
    void onPrintPdfDocClicked();

    /**
     * \brief Event handler for when the widget gains focus.
     *
     * \param event Pointer to the QFocusEvent being received.
     */
    void focusInEvent(QFocusEvent* event);

    /**
     * \brief Event handler for when the widget loses focus.
     *
     * \param event Pointer to the QFocusEvent being received.
     */
    void focusOutEvent(QFocusEvent* event);

    /**
     * \brief Copies text between widgets based on specified regex patterns.
     *
     * \param startRegex Regular expression pattern for identifying start widget.
     * \param stopRegex Regular expression pattern for identifying stop widget.
     */
    void copyTextBetweenWidgets(const QString& startRegex, const QString& stopRegex);

    /**
     * \brief Slot called when the copy button between first and second fields is clicked.
     */
    void onCopy12Clicked();

    /**
     * \brief Slot called when the copy button between second and third fields is clicked.
     */
    void onCopy23Clicked();

    /**
     * \brief Slot called when the report button is clicked.
     */
    void onReportClicked();

    /**
     * \brief Enables the Generare FM button after a specified interval.
     */
    void enableGenerareFmButton();

  protected:
    /**
     * \brief Event handler for when the dialog is shown.
     *
     * \param event Pointer to the QShowEvent being received.
     */
    void showEvent(QShowEvent* event);
};

#endif // TABLEBOARD_H
