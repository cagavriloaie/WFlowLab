/**
 * \file tableBoard.cpp
 * \brief Implementation file for the TableBoard class.
 *
 * This file contains the implementation of methods for the TableBoard class,
 * which is responsible for managing and displaying tabular data related to water meters.
 *
 * \author Constantin
 * \date Insert creation date
 */

// Standard C++ headers
#include <algorithm> // Standard C++ algorithms
#include <fstream>   // File stream operations
#include <iomanip>   // I/O manipulators
#include <iostream>  // Standard I/O streams
#include <mutex>     // C++11 mutual exclusion primitives
#include <sstream>   // String stream operations
#include <thread>    // C++11 thread support

// Qt headers
#include <QApplication>
#include <QDesktopServices> // Qt desktop services
#include <QDoubleValidator> // Qt validator for double values
#include <QFileDialog>      // Qt file dialog
#include <QMainWindow>      // Qt main window
#include <QMainWindow>
#include <QMessageBox>             // Qt message box for alerts
#include <QPainter>                // Qt painter for drawing
#include <QPrinter>                // Qt printer support
#include <QString>                 // Qt string class
#include <QTimer>                  // Qt timer for periodic events
#include <QValidator>              // Qt validator base class
#include <QtPrintSupport/QPrinter> // Qt printer support
#include <Windows.h>

// Project-specific headers
#include "definitions.h"   // Project-specific constants and definitions
#include "mainwindow.h"    // Your application's main window
#include "tableBoard.h"    // Header for table board functionality
#include "ui_mainwindow.h" // UI definition for main window
#include "ui_tableBoard.h" // UI definition for table board
#include "waterdensity.h"  // Header for water density calculations

extern MainWindow* pMainWindow;

namespace {
MainWindow* mainwindow = nullptr;
;
} // namespace

QString TableBoard::report;

std::mutex printTablePdfThreadMutex;

/**
 * \brief Generates a PDF document from the provided HTML report and saves it.
 *
 * This function generates a PDF document using QTextDocument and QPrinter,
 * based on the provided HTML report. The generated PDF is saved to a file
 * with a timestamped filename in a specified directory.
 *
 * \param report The HTML report content to be converted to PDF.
 */
void TableBoard::printPdfThread(QString report) {
    // Generate a unique timestamp for the file name
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

    // Construct the file name using QDir
    QString fileName = QString::fromStdString(mainwindow->selectedInfo.pathResults) +
                       QDir::separator() + QString("FM_") + timestamp + ".pdf";

    // Lock the mutex to ensure exclusive access to the shared resource
    std::lock_guard<std::mutex> lock(printTablePdfThreadMutex);

    // Check if the directory exists, and create it if not
    QDir resultDir(QString::fromStdString(mainwindow->selectedInfo.pathResults));

    if (!resultDir.exists() && !resultDir.mkpath(".")) {
        qDebug() << "Error: Failed to create result directory, PDF not generated.";
        return;
    }

    // Initialize the printer
    QPrinter printer(QPrinter::PrinterResolution);

    // Set the output format to PDF
    printer.setOutputFormat(QPrinter::PdfFormat);

    // Set the output file name
    printer.setOutputFileName(fileName);

    // Optionally set a custom or default page size
    QPageSize pageSize = QPageSize(QPageSize::A4); // Customize as needed
    printer.setPageSize(pageSize);

    // Set margins dynamically
    qreal leftMargin   = 1.0;
    qreal topMargin    = 1.0;
    qreal rightMargin  = 1.0;
    qreal bottomMargin = 1.0;
    printer.setPageMargins(QMarginsF(leftMargin, topMargin, rightMargin, bottomMargin));

    // Set color mode based on document needs
    printer.setColorMode(QPrinter::ColorMode::Color);

    printer.setResolution(300); // Higher resolution for better quality

    // Optional: Handle printer errors
    if (!printer.isValid()) {
        qWarning() << "Printer setup failed.";
    }

    // Initialize QTextDocument with the provided HTML report
    QTextDocument outputReport;
    outputReport.setHtml(report);

    // Check if the PDF generation is successful
    if (outputReport.isEmpty() || !printer.isValid()) {
        qDebug() << "Error: Empty document or invalid printer, PDF not generated.";
        return;
    }

    // Print the document to the PDF file
    outputReport.print(&printer);

    // Convert the file path to a URL and open it in the default PDF viewer
    QString fileUrl = QUrl::fromLocalFile(fileName).toString();

    QDesktopServices::openUrl(QUrl(fileUrl));
}

/**
 * \brief Saves current input data to a text file with a timestamped filename.
 *
 * This function saves various input data, including selectedInfo data,
 * vector data, and UI data, to a text file. The file is saved in a specified
 * directory with a filename containing a timestamp.
 */
void TableBoard::onSaveCurrentInputDataClicked() {
    size_t    entriesNumber = mainwindow->selectedInfo.entriesNumber;
    QDateTime now           = QDateTime::currentDateTime();
    QString   fileName      = QString(mainwindow->selectedInfo.pathResults.c_str()) +
                       "/inputData/" + QString("WStreamLab_") +
                       now.toString(QLatin1String("dd-MM-yyyy_hh_mm_ss")) + ".in";

    std::ofstream outputDataFile(fileName.toStdString());
    if (!outputDataFile.is_open()) {
        qDebug() << "Error: Unable to open the file for writing.";
        return;
    }

    outputDataFile << mainwindow->selectedInfo.entriesNumber << "\n";
    outputDataFile << mainwindow->selectedInfo.nameWaterMeter << "\n";

    outputDataFile << mainwindow->selectedInfo.ambientTemperature << "\n";
    outputDataFile << mainwindow->selectedInfo.athmosphericPressure << "\n";
    outputDataFile << mainwindow->selectedInfo.relativeAirHumidity << "\n";

    outputDataFile << mainwindow->selectedInfo.rbVolumetric << "\n";
    outputDataFile << mainwindow->selectedInfo.rbGravimetric_new << "\n";
    outputDataFile << mainwindow->selectedInfo.rbManual << "\n";
    outputDataFile << mainwindow->selectedInfo.rbInterface << "\n";
    outputDataFile << mainwindow->selectedInfo.rbTerminal << "\n";
    for (size_t iter = 0; iter < entriesNumber; ++iter) {
        outputDataFile << vectorSerialNumber[iter]->text().toStdString() << "\n";
        outputDataFile << vectorFirstIndexStart[iter]->text().toStdString() << "\n";
        outputDataFile << vectorFirstIndexStop[iter]->text().toStdString() << "\n";
        outputDataFile << vectorSecondIndexStart[iter]->text().toStdString() << "\n";
        outputDataFile << vectorSecondIndexStop[iter]->text().toStdString() << "\n";
        outputDataFile << vectorThirdIndexStart[iter]->text().toStdString() << "\n";
        outputDataFile << vectorThirdIndexStop[iter]->text().toStdString() << "\n";
    }
    outputDataFile << ui->leFlowRateMinumum->text().toStdString() << "\n";
    outputDataFile << ui->leMass1->text().toStdString() << "\n";
    outputDataFile << ui->leTemperature1->text().toStdString() << "\n";
    outputDataFile << ui->leVolume1->text().toStdString() << "\n";

    outputDataFile << ui->leFlowRateTransitoriu->text().toStdString() << "\n";
    outputDataFile << ui->leMass2->text().toStdString() << "\n";
    outputDataFile << ui->leTemperature2->text().toStdString() << "\n";
    outputDataFile << ui->leVolume2->text().toStdString() << "\n";

    outputDataFile << ui->leFlowRateNominal->text().toStdString() << "\n";
    outputDataFile << ui->leMass3->text().toStdString() << "\n";
    outputDataFile << ui->leTemperature3->text().toStdString() << "\n";
    outputDataFile << ui->leVolume3->text().toStdString() << "\n";

    // Display a message box
    QMessageBox messageBoxSaveInputFile;
    messageBoxSaveInputFile.setWindowTitle(tr("Save input data"));
    messageBoxSaveInputFile.setText("The file " + fileName + " was created!");
    messageBoxSaveInputFile.setStandardButtons(QMessageBox::Ok);

    // Get the HWND (Windows handle) of the main window
    HWND hwnd = reinterpret_cast<HWND>(winId());

    // Remove the WS_MAXIMIZEBOX style from the window
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    SetWindowLong(hwnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX);

    // Create a QTimer
    QTimer* timer = new QTimer(&messageBoxSaveInputFile);
    timer->setSingleShot(true); // Make the timer a single-shot timer
    timer->setInterval(3000);   // Set the interval to 3000 milliseconds (5 seconds)

    // Connect the timeout signal to close the message box
    QObject::connect(timer, &QTimer::timeout, &messageBoxSaveInputFile, &QMessageBox::accept);

    // Start the timer
    timer->start();

    // Show the message box
    messageBoxSaveInputFile.exec();
}

/**
 * \brief Opens a dialog to select and load input data from a text file.
 *
 * This function displays a file dialog allowing the user to select an input
 * data file. It reads the selected file and populates various UI elements
 * and internal data structures with the loaded data.
 */
void TableBoard::onOpenInputDataClicked() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Input Data"),
        QString(mainwindow->selectedInfo.pathResults.c_str()) + "/inputData/",
        tr("Input data (*.in);;All file (*.*)"));

    std::ifstream inputDataFile(fileName.toStdString());
    Translate();

    size_t      entriesNumber;
    std::string nameSelectedWaterMeter;

    std::string ambientTemperature;
    std::string athmosphericPressure;
    std::string relativeAirHumidity;

    bool        rbVolumetric;
    bool        rbGravitmetric;
    bool        rbManual;
    bool        rbInterface;
    bool        rbTerminal;
    std::string tmpInput;

    inputDataFile >> entriesNumber;
    std::getline(inputDataFile, tmpInput);
    std::getline(inputDataFile, nameSelectedWaterMeter);
    inputDataFile >> ambientTemperature;
    inputDataFile >> athmosphericPressure;
    inputDataFile >> relativeAirHumidity;
    inputDataFile >> rbVolumetric;
    inputDataFile >> rbGravitmetric;
    inputDataFile >> rbManual;
    inputDataFile >> rbInterface;
    inputDataFile >> rbTerminal;

    int index = mainwindow->ui->cbNumberOfWaterMeters->findText(std::to_string(entriesNumber).c_str());
    if (index != -1) {
        mainwindow->ui->cbNumberOfWaterMeters->setCurrentIndex(index);
    }

    index = mainwindow->ui->cbWaterMeterType->findText(nameSelectedWaterMeter.c_str());
    if (index != -1) {
        mainwindow->ui->cbWaterMeterType->setCurrentIndex(index);
    }

    QString qAmbientTemperature   = ambientTemperature.c_str();
    QString qAthmosphericPressure = athmosphericPressure.c_str();
    QString qRelativeAirHumidity  = relativeAirHumidity.c_str();

    mainwindow->ui->leTemperature->setText(qAmbientTemperature);
    mainwindow->ui->lePressure->setText(qAthmosphericPressure);
    mainwindow->ui->leHumidity->setText(qRelativeAirHumidity);

    if (rbVolumetric) {
        mainwindow->ui->rbVolumetric->setChecked(true);
        mainwindow->selectedInfo.rbVolumetric = true;
        mainwindow->ui->rbGravimetric->setChecked(false);
        mainwindow->selectedInfo.rbGravimetric_new = false;
    }

    if (rbGravitmetric) {
        mainwindow->ui->rbGravimetric->setChecked(true);
        mainwindow->selectedInfo.rbGravimetric_new = true;
        mainwindow->ui->rbVolumetric->setChecked(false);
        mainwindow->selectedInfo.rbVolumetric = false;
    }

    if (rbManual) {
        mainwindow->ui->rbManual->setChecked(true);
    }

    if (rbInterface) {
        mainwindow->ui->rbInterface->setChecked(true);
    }

    std::getline(inputDataFile, tmpInput);

    for (size_t iter = 0; iter < entries; ++iter) {
        std::getline(inputDataFile, tmpInput);
        vectorSerialNumber[iter]->setText(tmpInput.c_str());
        std::getline(inputDataFile, tmpInput);
        vectorFirstIndexStart[iter]->setText(tmpInput.c_str());
        std::getline(inputDataFile, tmpInput);
        vectorFirstIndexStop[iter]->setText(tmpInput.c_str());
        std::getline(inputDataFile, tmpInput);
        vectorSecondIndexStart[iter]->setText(tmpInput.c_str());
        std::getline(inputDataFile, tmpInput);
        vectorSecondIndexStop[iter]->setText(tmpInput.c_str());
        std::getline(inputDataFile, tmpInput);
        vectorThirdIndexStart[iter]->setText(tmpInput.c_str());
        std::getline(inputDataFile, tmpInput);
        vectorThirdIndexStop[iter]->setText(tmpInput.c_str());
    }

    std::getline(inputDataFile, tmpInput);
    ui->leFlowRateMinumum->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leMass1->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leTemperature1->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leVolume1->setText(tmpInput.c_str());

    std::getline(inputDataFile, tmpInput);
    ui->leFlowRateTransitoriu->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leMass2->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leTemperature2->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leVolume2->setText(tmpInput.c_str());

    std::getline(inputDataFile, tmpInput);
    ui->leFlowRateNominal->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leMass3->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leTemperature3->setText(tmpInput.c_str());
    std::getline(inputDataFile, tmpInput);
    ui->leVolume3->setText(tmpInput.c_str());

    onMeasurementTypeChanged();
}

/**
 * \brief Converts a double number to a string with 4 decimal precision.
 *
 * This function converts a given double number into a string representation
 * with exactly 4 decimal places.
 *
 * \param number The double number to convert.
 * \return A string representation of the number with 4 decimal precision.
 */
std::string precision_4(double number) {
    int integer_part = static_cast<int>(number);                          ///< Integer part of the number.
    int decimal_part = static_cast<int>((number - integer_part) * 10000); ///< Decimal part of the number.

    if (decimal_part >= 10) {
        return std::to_string(integer_part) + "." + std::to_string(decimal_part); ///< Return the formatted string.
    } else {
        return std::to_string(integer_part) + ".0" + std::to_string(decimal_part); ///< Return the formatted string with leading zero.
    }
}

/**
 * \brief Performs exclusive OR (XOR) operation between two boolean values.
 *
 * This function computes the result of the XOR operation between two boolean values.
 * XOR returns true if one and only one of the boolean operands is true; otherwise, it returns false.
 *
 * \param a First boolean operand.
 * \param b Second boolean operand.
 * \return The result of the XOR operation between @p a and @p b.
 */
bool XOR(bool a, bool b) {
    return a != b; ///< Return true if @p a and @p b are different; otherwise, false.
}

/**
 * \brief Sets up validators, event filters, read-only states, and check states for UI elements.
 *
 * This method initializes validators for numeric inputs, installs event filters for certain UI elements,
 * sets read-only states for error fields, and sets check states for checkboxes.
 *
 * It also sets specific styles and properties for certain QLineEdit elements related to flow rates,
 * masses, and temperatures.
 *
 * \note This function assumes the existence of specific UI elements (e.g., ui->lbN1, ui->cbSet1, ui->leSN1).
 */
void TableBoard::ValidatorInput() {
    QLabel* pNumber[] = {ui->lbN1, ui->lbN2, ui->lbN3, ui->lbN4, ui->lbN5,
                         ui->lbN6, ui->lbN7, ui->lbN8, ui->lbN9, ui->lbN10,
                         ui->lbN11, ui->lbN12, ui->lbN13, ui->lbN14, ui->lbN15,
                         ui->lbN16, ui->lbN17, ui->lbN18, ui->lbN19, ui->lbN20};
    vectorNumber.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorNumber.push_back(pNumber[iter]);
    }
    QCheckBox* pCheckNumber[] =
        {
            ui->cbSet1,
            ui->cbSet2,
            ui->cbSet3,
            ui->cbSet4,
            ui->cbSet5,
            ui->cbSet6,
            ui->cbSet7,
            ui->cbSet8,
            ui->cbSet9,
            ui->cbSet10,
            ui->cbSet11,
            ui->cbSet12,
            ui->cbSet13,
            ui->cbSet14,
            ui->cbSet15,
            ui->cbSet16,
            ui->cbSet17,
            ui->cbSet18,
            ui->cbSet19,
            ui->cbSet20,
        };
    vectorCheckNumber.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorCheckNumber.push_back(pCheckNumber[iter]);
        pCheckNumber[iter]->installEventFilter(this);
    }
    QLineEdit* pSerialNumber[] =
        {
            ui->leSN1, ui->leSN2, ui->leSN3, ui->leSN4, ui->leSN5,
            ui->leSN6, ui->leSN7, ui->leSN8, ui->leSN9, ui->leSN10,
            ui->leSN11, ui->leSN12, ui->leSN13, ui->leSN14, ui->leSN15,
            ui->leSN16, ui->leSN17, ui->leSN18, ui->leSN19, ui->leSN20};
    vectorSerialNumber.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorSerialNumber.push_back(pSerialNumber[iter]);
        pSerialNumber[iter]->installEventFilter(this);
    }
    QLineEdit* pFirstIndexStart[] =
        {
            ui->leStart1_1, ui->leStart1_2, ui->leStart1_3, ui->leStart1_4,
            ui->leStart1_5, ui->leStart1_6, ui->leStart1_7, ui->leStart1_8,
            ui->leStart1_9, ui->leStart1_10, ui->leStart1_11, ui->leStart1_12,
            ui->leStart1_13, ui->leStart1_14, ui->leStart1_15, ui->leStart1_16,
            ui->leStart1_17, ui->leStart1_18, ui->leStart1_19, ui->leStart1_20};
    vectorFirstIndexStart.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorFirstIndexStart.push_back(pFirstIndexStart[iter]);
        pFirstIndexStart[iter]->installEventFilter(this);
    }
    QLineEdit* pFirstIndexStop[] =
        {
            ui->leStop1_1, ui->leStop1_2, ui->leStop1_3, ui->leStop1_4,
            ui->leStop1_5, ui->leStop1_6, ui->leStop1_7, ui->leStop1_8,
            ui->leStop1_9, ui->leStop1_10, ui->leStop1_11, ui->leStop1_12,
            ui->leStop1_13, ui->leStop1_14, ui->leStop1_15, ui->leStop1_16,
            ui->leStop1_17, ui->leStop1_18, ui->leStop1_19, ui->leStop1_20};
    vectorFirstIndexStop.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorFirstIndexStop.push_back(pFirstIndexStop[iter]);
        pFirstIndexStop[iter]->installEventFilter(this);
    }
    QLineEdit* pFirstError[] =
        {
            ui->leError1_1, ui->leError1_2, ui->leError1_3, ui->leError1_4,
            ui->leError1_5, ui->leError1_6, ui->leError1_7, ui->leError1_8,
            ui->leError1_9, ui->leError1_10, ui->leError1_11, ui->leError1_12,
            ui->leError1_13, ui->leError1_14, ui->leError1_15, ui->leError1_16,
            ui->leError1_17, ui->leError1_18, ui->leError1_19, ui->leError1_20};
    vectorFirstError.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorFirstError.push_back(pFirstError[iter]);
    }
    QLineEdit* pSecondIndexStart[] =
        {
            ui->leStart2_1, ui->leStart2_2, ui->leStart2_3, ui->leStart2_4,
            ui->leStart2_5, ui->leStart2_6, ui->leStart2_7, ui->leStart2_8,
            ui->leStart2_9, ui->leStart2_10, ui->leStart2_11, ui->leStart2_12,
            ui->leStart2_13, ui->leStart2_14, ui->leStart2_15, ui->leStart2_16,
            ui->leStart2_17, ui->leStart2_18, ui->leStart2_19, ui->leStart2_20};
    vectorSecondIndexStart.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorSecondIndexStart.push_back(pSecondIndexStart[iter]);
        pSecondIndexStart[iter]->installEventFilter(this);
    }
    QLineEdit* pSecondIndexStop[] =
        {
            ui->leStop2_1, ui->leStop2_2, ui->leStop2_3, ui->leStop2_4,
            ui->leStop2_5, ui->leStop2_6, ui->leStop2_7, ui->leStop2_8,
            ui->leStop2_9, ui->leStop2_10, ui->leStop2_11, ui->leStop2_12,
            ui->leStop2_13, ui->leStop2_14, ui->leStop2_15, ui->leStop2_16,
            ui->leStop2_17, ui->leStop2_18, ui->leStop2_19, ui->leStop2_20};
    vectorSecondIndexStop.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorSecondIndexStop.push_back(pSecondIndexStop[iter]);
        pSecondIndexStop[iter]->installEventFilter(this);
    }
    QLineEdit* pSecondError[] =
        {
            ui->leError2_1, ui->leError2_2, ui->leError2_3, ui->leError2_4,
            ui->leError2_5, ui->leError2_6, ui->leError2_7, ui->leError2_8,
            ui->leError2_9, ui->leError2_10, ui->leError2_11, ui->leError2_12,
            ui->leError2_13, ui->leError2_14, ui->leError2_15, ui->leError2_16,
            ui->leError2_17, ui->leError2_18, ui->leError2_19, ui->leError2_20};
    vectorSecondError.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorSecondError.push_back(pSecondError[iter]);
    }
    QLineEdit* pThirdIndexStart[] =
        {
            ui->leStart3_1, ui->leStart3_2, ui->leStart3_3, ui->leStart3_4,
            ui->leStart3_5, ui->leStart3_6, ui->leStart3_7, ui->leStart3_8,
            ui->leStart3_9, ui->leStart3_10, ui->leStart3_11, ui->leStart3_12,
            ui->leStart3_13, ui->leStart3_14, ui->leStart3_15, ui->leStart3_16,
            ui->leStart3_17, ui->leStart3_18, ui->leStart3_19, ui->leStart3_20};
    vectorThirdIndexStart.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorThirdIndexStart.push_back(pThirdIndexStart[iter]);
        pThirdIndexStart[iter]->installEventFilter(this);
    }
    QLineEdit* pThirdIndexStop[] =
        {
            ui->leStop3_1, ui->leStop3_2, ui->leStop3_3, ui->leStop3_4,
            ui->leStop3_5, ui->leStop3_6, ui->leStop3_7, ui->leStop3_8,
            ui->leStop3_9, ui->leStop3_10, ui->leStop3_11, ui->leStop3_12,
            ui->leStop3_13, ui->leStop3_14, ui->leStop3_15, ui->leStop3_16,
            ui->leStop3_17, ui->leStop3_18, ui->leStop3_19, ui->leStop3_20};
    vectorThirdIndexStop.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorThirdIndexStop.push_back(pThirdIndexStop[iter]);
        pThirdIndexStop[iter]->installEventFilter(this);
    }
    QLineEdit* pThirdError[] =
        {
            ui->leError3_1, ui->leError3_2, ui->leError3_3, ui->leError3_4,
            ui->leError3_5, ui->leError3_6, ui->leError3_7, ui->leError3_8,
            ui->leError3_9, ui->leError3_10, ui->leError3_11, ui->leError3_12,
            ui->leError3_13, ui->leError3_14, ui->leError3_15, ui->leError3_16,
            ui->leError3_17, ui->leError3_18, ui->leError3_19, ui->leError3_20};
    vectorThirdError.clear();
    for (size_t iter = 0; iter < MAX_ENTRIES; ++iter) {
        vectorThirdError.push_back(pThirdError[iter]);
    }
    ui->cbSet->installEventFilter(this);
    ui->pbCalculate->installEventFilter(this);
    ui->pbClean->installEventFilter(this);
    ui->pbClose->installEventFilter(this);
    ui->pbOpen->installEventFilter(this);
    ui->pbPrint->installEventFilter(this);
    ui->pbSaveResults->installEventFilter(this);
    ui->leVolume1->installEventFilter(this);
    ui->leVolume2->installEventFilter(this);
    ui->leVolume3->installEventFilter(this);
    ui->leMass1->installEventFilter(this);
    ui->leMass2->installEventFilter(this);
    ui->leMass3->installEventFilter(this);
    ui->leTemperature1->installEventFilter(this);
    ui->leTemperature2->installEventFilter(this);
    ui->leTemperature3->installEventFilter(this);
    QRegularExpression rx("\\b[A-Z0-9.-]*",
                          QRegularExpression::CaseInsensitiveOption);
    auto               validatorAlphanumeric = new QRegularExpressionValidator(rx,
                                                                               this);
    QDoubleValidator*  validatorDoubleNumber = new QDoubleValidator(this);
    // set natural numbers as input for SN input line
    for (auto iter = begin(vectorSerialNumber);
         iter != end(vectorSerialNumber);
         ++iter) {
        (*iter)->setValidator(validatorAlphanumeric);
    }
    // set natural numbers as input for minimal flow input line
    for (auto iter = begin(vectorFirstIndexStart);
         iter != end(vectorFirstIndexStart); ++iter) {
        (*iter)->setValidator(validatorDoubleNumber);
    }
    for (auto iter = begin(vectorFirstIndexStop);
         iter != end(vectorFirstIndexStop); ++iter) {
        (*iter)->setValidator(validatorDoubleNumber);
    }
    ui->leFlowRateMinumum->setValidator(validatorDoubleNumber);
    ui->leMass1->setValidator(validatorDoubleNumber);
    ui->leTemperature1->setValidator(validatorDoubleNumber);
    // set natural numbers as input for transient flow input line
    for (auto iter = begin(vectorSecondIndexStart);
         iter != end(vectorSecondIndexStart); ++iter) {
        (*iter)->setValidator(validatorDoubleNumber);
    }
    for (auto iter = begin(vectorSecondIndexStop);
         iter != end(vectorSecondIndexStop); ++iter) {
        (*iter)->setValidator(validatorDoubleNumber);
    }
    ui->leFlowRateTransitoriu->setValidator(validatorDoubleNumber);
    ui->leMass2->setValidator(validatorDoubleNumber);
    ui->leTemperature2->setValidator(validatorDoubleNumber);
    // set natural numbers as input for nominal flow input line
    for (auto iter = begin(vectorThirdIndexStart);
         iter != end(vectorThirdIndexStart); ++iter) {
        (*iter)->setValidator(validatorDoubleNumber);
    }
    for (auto iter = begin(vectorThirdIndexStop);
         iter != end(vectorThirdIndexStop); ++iter) {
        (*iter)->setValidator(validatorDoubleNumber);
    }
    ui->leFlowRateNominal->setValidator(validatorDoubleNumber);
    ui->leMass3->setValidator(validatorDoubleNumber);
    ui->leTemperature3->setValidator(validatorDoubleNumber);
    for (auto iter = begin(vectorFirstError);
         iter != end(vectorFirstError);
         ++iter) {
        (*iter)->setReadOnly(true);
    }
    for (auto iter = begin(vectorSecondError);
         iter != end(vectorSecondError);
         ++iter) {
        (*iter)->setReadOnly(true);
    }
    for (auto iter = begin(vectorThirdError);
         iter != end(vectorThirdError);
         ++iter) {
        (*iter)->setReadOnly(true);
    }
    ui->leMass1->show();
    ui->leMass2->show();
    ui->leMass2->show();
    ui->lbTemperature1->show();
    ui->lbTemperature2->show();
    ui->lbTemperature3->show();
    ui->leVolume1->setReadOnly(true);
    ui->leVolume2->setReadOnly(true);
    ui->leVolume3->setReadOnly(true);

    QPalette paletteDiactivatedLineEdit;
    paletteDiactivatedLineEdit.setColor(QPalette::Base,
                                        QColor(220, 235, 220, 255));
/*    if (mainwindow->selectedInfo.rbGravimetric_new == true) {
        ui->leVolume1->setStyleSheet(
            "QLineEdit {background-color: rgb(235, 235, 235)}");
        ui->leVolume2->setStyleSheet(
            "QLineEdit {background-color: rgb(235, 235, 235)}");
        ui->leVolume3->setStyleSheet(
            "QLineEdit {background-color: rgb(235, 235, 235)}");
    }*/

    for (auto iter = begin(vectorCheckNumber);
         iter != end(vectorCheckNumber);
         ++iter) {
        (*iter)->setCheckState(Qt::Checked);
    }
    ui->cbSet->setCheckState(Qt::Checked);
}

/**
 * \brief Translates and updates UI elements with localized texts.
 *
 * This function updates various UI elements such as window title, labels, buttons,
 * and dynamic text with their translated versions. It ensures the user interface
 * reflects the current language settings.
 */
void TableBoard::Translate() {
    nameWaterMeter = mainwindow->selectedInfo.nameWaterMeter;
    this->setWindowTitle(tr("WStreamLab - Input Table") + " [ " +
                         QString::fromUtf8(nameWaterMeter.c_str()) + " ]");
    ui->lbN1->setText("01");
    ui->lbN2->setText("02");
    ui->lbN3->setText("03");
    ui->lbN4->setText("04");
    ui->lbN5->setText("05");
    ui->lbN6->setText("06");
    ui->lbN7->setText("07");
    ui->lbN8->setText("08");
    ui->lbN9->setText("09");
    ui->lbN10->setText("10");
    ui->lbN11->setText("11");
    ui->lbN12->setText("12");
    ui->lbN13->setText("13");
    ui->lbN14->setText("14");
    ui->lbN15->setText("15");
    ui->lbN16->setText("16");
    ui->lbN17->setText("17");
    ui->lbN18->setText("18");
    ui->lbN19->setText("19");
    ui->lbN20->setText("20");
    ui->lbIndex1->setText(tr("Index"));
    ui->lbStart1->setText(tr("Start index"));
    ui->lbStop1->setText(tr("Stop index"));
    ui->lbError1->setText(tr("Err. Qmin"));
    ui->lbIndex2->setText(tr("Index"));
    ui->lbStart2->setText(tr("Start index"));
    ui->lbStop2->setText(tr("Stop index"));
    ui->lbError2->setText(tr("Err. Qt"));
    ui->lbIndex3->setText(tr("Index"));
    ui->lbStart3->setText(tr("Start index"));
    ui->lbStop3->setText(tr("Stop index"));
    ui->lbError3->setText(tr("Err. Qn"));
    ui->lbFlowRateMin->setText(tr("Flow rate [L/h]"));
    ui->lbMass1->setText(tr("Mass [kg]"));
    ui->lbTemperature1->setText(tr("Temperature [\302\260C]"));
    ui->lbVolume1->setText(tr("Volume [L]"));
    ui->lbFlowRateTransition->setText(tr("Flow rate [L/h]"));
    ui->lbMass2->setText(tr("Mass [kg]"));
    ui->lbTemperature2->setText(tr("Temperature [\302\260C]"));
    ui->lbVolume2->setText(tr("Volume [L]"));
    ui->lbFlowRateNominal->setText(tr("Flow rate [L/h]"));
    ui->lbMass3->setText(tr("Mass [kg]", nullptr));
    ui->lbTemperature3->setText(tr("Temperature [\302\260C]"));
    ui->lbVolume3->setText(tr("Volume [L]", nullptr));
    ui->lbSN->setText("Seria (Tip)");
    // Buttons
    ui->pbCalculate->setText(tr("&Data evaluate"));
    ui->pbPrint->setText(tr("&Print PDF"));
    ui->pbReport->setText(tr("Report PDF"));
    ui->pbOpen->setText(tr("&Open"));
    ui->pbSaveResults->setText(tr("&Save"));
    ui->pbClose->setText(tr("&Close"));
    ui->pbClean->setText(tr("Clean &Input"));
    ui->pbCalculate->setContentsMargins(100, 0, 100, 0);
    ui->pbPrint->setContentsMargins(10, 0, 10, 0);
    ui->pbOpen->setContentsMargins(10, 0, 10, 0);
    ui->pbSaveResults->setContentsMargins(10, 0, 10, 0);
    ui->pbClose->setContentsMargins(10, 0, 10, 0);
    ui->pbClean->setContentsMargins(10, 0, 10, 0);
    ui->lbIndex1->setText(
        QString("Index [L] -  Qmin: %1 L/h  Eroare: %2%")
            .arg(QString::number(minimumFlowMain),
                 QString::number(maximumError)));
    ui->lbIndex2->setText(
        QString("Index [L] -  Qt:  %1 L/h  Eroare: %2%")
            .arg(QString::number(transitoriuFlowMain),
                 QString::number(nominalError)));
    ui->lbIndex3->setText(
        QString("Index [L] -  Qn: %1 L/h  Eroare: %2%")
            .arg(QString::number(nominalFlowMain),
                 QString::number(nominalError)));
    if (reportMeasurementsDialog != nullptr) {
        reportMeasurementsDialog->Translate();
    }
}

/**
 * \brief Constructor for TableBoard class.
 *
 * Initializes the TableBoard dialog with the given parent widget, sets up UI,
 * connects signals to slots, and configures window flags.
 *
 * \param _parent Pointer to the parent widget.
 */
TableBoard::TableBoard(QWidget* _parent)
    : QDialog(_parent),
      parent(_parent),
      ui(new Ui::TableBoard) {
    // Ensure the dialog is non-modal
    setModal(false);

    // Setup the user interface
    ui->setupUi(this);

    // Create a timer for generating FM (Flow Meter?) values
    QTimerGenerareFM = new QTimer(this);

    // Attempt to cast the parent widget to MainWindow
    mainwindow = dynamic_cast<MainWindow*>(parent);

    // Translate UI elements to the current language
    Translate();

    // Validate input fields if needed
    ValidatorInput();

    // Connect signals to slots
    connect(ui->pbCalculate, SIGNAL(clicked()), this, SLOT(onCalculateClicked()));
    connect(ui->pbClean, SIGNAL(clicked()), this, SLOT(onCleanClicked()));
    connect(ui->pbClose, SIGNAL(clicked()), this, SLOT(onCloseClicked()));
    connect(ui->pbSaveResults, SIGNAL(clicked()), this, SLOT(onSaveCurrentInputDataClicked()));
    connect(ui->pbOpen, SIGNAL(clicked()), this, SLOT(onOpenInputDataClicked()));
    connect(ui->pbPrint, SIGNAL(clicked()), this, SLOT(onPrintPdfDocClicked()));
    connect(ui->pbReport, SIGNAL(clicked()), this, SLOT(onReportClicked()));
    connect(ui->cbSet, SIGNAL(stateChanged(int)), this, SLOT(onSelectAllChanged()));

    connect(ui->pbCopy12, SIGNAL(clicked()), this, SLOT(onCopy12Clicked()));
    connect(ui->pbCopy23, SIGNAL(clicked()), this, SLOT(onCopy23Clicked()));

    // Connect vectorCheckNumber signals to onCbClicked slot using dynamic_cast
    for (unsigned iter = 0; iter < MAX_ENTRIES; ++iter) {
        connect(vectorCheckNumber[iter], SIGNAL(clicked(bool)), this, SLOT(onCbClicked(bool)));
    }

    // Connect timer timeout signal to slot for enabling a button
    connect(QTimerGenerareFM, &QTimer::timeout, this, &TableBoard::enableGenerareFmButton);

    // Configure window flags for the dialog
    Qt::WindowFlags flags = Qt::Dialog | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint;
    setWindowFlags(flags);
}

/**
 * \brief Destructor for TableBoard class.
 *
 * Cleans up resources used by the TableBoard dialog.
 * Deletes the UI instance and resets input data in the MainWindow if applicable.
 */
TableBoard::~TableBoard() {
    // Attempt to cast parent widget to MainWindow
    MainWindow* mainWindow = dynamic_cast<MainWindow*>(this->parent);

    // If cast successful and mainWindow is not nullptr
    if (mainWindow) {
        // Reset inputData pointer in MainWindow
        mainWindow->inputData = nullptr;
    }

    // Delete the user interface instance
    delete ui;
}

/**
 * \brief Slot invoked when the "Clean Input" button is clicked.
 *
 * Clears all input fields and widgets on the dialog.
 * This includes serial number, index start/stop, and error fields for each entry,
 * as well as temperature, mass, and volume fields.
 */
void TableBoard::onCleanClicked() {
    // Clear serial number, index start/stop, and error fields for each entry
    for (unsigned iter = 0; iter < entries; ++iter) {
        vectorSerialNumber[iter]->clear();     ///< Clear serial number input field for entry iter.
        vectorFirstIndexStart[iter]->clear();  ///< Clear first index start input field for entry iter.
        vectorFirstIndexStop[iter]->clear();   ///< Clear first index stop input field for entry iter.
        vectorFirstError[iter]->clear();       ///< Clear first error input field for entry iter.
        vectorSecondIndexStart[iter]->clear(); ///< Clear second index start input field for entry iter.
        vectorSecondIndexStop[iter]->clear();  ///< Clear second index stop input field for entry iter.
        vectorSecondError[iter]->clear();      ///< Clear second error input field for entry iter.
        vectorThirdIndexStart[iter]->clear();  ///< Clear third index start input field for entry iter.
        vectorThirdIndexStop[iter]->clear();   ///< Clear third index stop input field for entry iter.
        vectorThirdError[iter]->clear();       ///< Clear third error input field for entry iter.
    }

    // Clear temperature, mass, and volume input fields
    ui->leFlowRateMinumum->clear(); ///< Clear temperature input field for entry 1.
    ui->leFlowRateNominal->clear(); ///< Clear temperature input field for entry 2.
    ui->leFlowRateTransitoriu->clear(); ///< Clear temperature input field for entry 3.
    ui->leTemperature1->clear(); ///< Clear temperature input field for entry 1.
    ui->leTemperature2->clear(); ///< Clear temperature input field for entry 2.
    ui->leTemperature3->clear(); ///< Clear temperature input field for entry 3.
    ui->leMass1->clear();        ///< Clear mass input field for entry 1.
    ui->leMass2->clear();        ///< Clear mass input field for entry 2.
    ui->leMass3->clear();        ///< Clear mass input field for entry 3.
    ui->leVolume1->clear();      ///< Clear volume input field for entry 1.
    ui->leVolume2->clear();      ///< Clear volume input field for entry 2.
    ui->leVolume3->clear();      ///< Clear volume input field for entry 3.
}

QString resultAllTests[20];

/**
 * \brief Slot triggered when the "Calculate" button is clicked.
 *
 * This function handles the click event of the "Calculate" button. It performs
 * calculations based on user input and updates the UI with results.
 *
 * Detailed steps:
 * - Clears previous error highlighting.
 * - Calculates results for all input rows.
 * - Updates UI with calculated results and highlights errors.
 * - Stores detailed results in the `resultAllTests` array.
 *
 * \note Assumes the UI elements (`vectorSerialNumber`, `vectorFirstIndexStart`, etc.)
 *       are properly initialized and connected.
 */
void TableBoard::onCalculateClicked() {
    QPalette paletteOddRowErr;
    paletteOddRowErr.setColor(QPalette::Base, QColor(220, 235, 220, 255));
    QPalette paletteEvenRowErr;
    paletteEvenRowErr.setColor(QPalette::Base, QColor(235, 235, 235,
                                                      255));
    QPalette paletteNormal;
    paletteNormal.setColor(QPalette::Base, QColor(250, 250, 250, 255));
    QPalette paletteErr;
    paletteErr.setColor(QPalette::Base, QColor(245, 220, 220, 255));

    for (size_t iter = 0; iter < 20; ++iter)
        resultAllTests[iter] = "RESPINS";

    bool result{true};

    for (unsigned iter = 0; iter < entries; ++iter) {
        vectorFirstError[iter]->setText("");
        vectorSecondError[iter]->setText("");
        vectorThirdError[iter]->setText("");
    }

    if (mainwindow->selectedInfo.rbGravimetric_new == true) {
        bool   result_t1{true}, result_t2{true}, result_t3{true};
        bool   result_m1{true}, result_m2{true}, result_m3{true};
        double tmp{0};
        double temperatureFirst{0};
        double temperatureSecond{0};
        double temperatureThird{0};
        bool   bConvert(false);
        // Temperature for minimal flow
        tmp = ui->leTemperature1->text().toDouble(&bConvert);
        ui->leTemperature1->setPalette(paletteNormal);
        if (bConvert) {
            temperatureFirst = tmp;
            if (temperatureFirst < 0 || temperatureFirst > 100) {
                ui->leTemperature1->setPalette(paletteErr);
                result_t1 = false;
            }
        } else {
            ui->leTemperature1->setPalette(paletteErr);
            temperatureFirst = 20;
            result_t1        = false;
            result           = false;
        }
        // Temperature for transitoriu flow
        tmp = ui->leTemperature2->text().toDouble(&bConvert);
        ui->leTemperature2->setPalette(paletteNormal);
        if (bConvert) {
            temperatureSecond = tmp;
            if (temperatureSecond < 0 || temperatureSecond > 100) {
                ui->leTemperature2->setPalette(paletteErr);
                result_t2 = false;
            }
        } else {
            ui->leTemperature2->setPalette(paletteErr);
            temperatureSecond = 20;
            result_t2         = false;
            result            = false;
        }
        // Temperature for nominal flow
        tmp = ui->leTemperature3->text().toDouble(&bConvert);
        ui->leTemperature3->setPalette(paletteNormal);
        if (bConvert) {
            temperatureThird = tmp;
            if (temperatureThird < 0 || temperatureThird > 100) {
                ui->leTemperature3->setPalette(paletteErr);
                result_t3 = false;
            }
        } else {
            ui->leTemperature3->setPalette(paletteErr);
            temperatureThird = 20;
            result_t3        = false;
            result           = false;
        }
        double massFirst{0};
        double massSecond{0};
        double massThird{0};
        // Mass for minimal flow
        tmp = ui->leMass1->text().toDouble(&bConvert);
        ui->leMass1->setPalette(paletteNormal);
        if (bConvert) {
            massFirst = tmp;
            if (massFirst < 0) {
                ui->leMass1->setPalette(paletteErr);
                massFirst = 100;
                result_m1 = false;
            }
        } else {
            ui->leMass1->setPalette(paletteErr);
            massFirst = 100;
            result_m1 = false;
            result    = false;
        }
        // Mass for transitoriu flow
        tmp = ui->leMass2->text().toDouble(&bConvert);
        ui->leMass2->setPalette(paletteNormal);
        if (bConvert) {
            massSecond = tmp;
            if (massSecond < 0) {
                ui->leMass2->setPalette(paletteErr);
                massSecond = 100;
                result_m2  = false;
            }
        } else {
            ui->leMass2->setPalette(paletteErr);
            massSecond = 100;
            result_m2  = false;
            result     = false;
        }
        // Mass for nominal flow
        tmp = ui->leMass3->text().toDouble(&bConvert);
        ui->leMass3->setPalette(paletteNormal);
        if (bConvert) {
            massThird = tmp;
            if (massThird < 0) {
                ui->leMass3->setPalette(paletteErr);
                massThird = 100;
                result_m3 = false;
            }
        } else {
            ui->leMass3->setPalette(paletteErr);
            massThird = 100;
            result_m3 = false;
            result    = false;
        }
        /*
        double densityFirst{0};
        double densitySecond{0};
        double densityThird{0};
        double correction = mainwindow->selectedInfo.density_20;

        densityFirst =
            getWaterDensityQuadratic(temperatureFirst, correction);
        densitySecond =
            getWaterDensityQuadratic(temperatureSecond, correction);
        densityThird =
            getWaterDensityQuadratic(temperatureThird, correction);
*/
        double volumeCorrectionFirst{0};
        double volumeCorrectionSecond{0};
        double volumeCorrectionThird{0};

        volumeCorrectionFirst =
            quadraticInterpolationVolumeCorrection(temperatureFirst);
        volumeCorrectionSecond =
            quadraticInterpolationVolumeCorrection(temperatureSecond);
        volumeCorrectionThird =
            quadraticInterpolationVolumeCorrection(temperatureThird);
/*
        double VolumeFirst  = volumeCorrectionFirst * 1000 * massFirst / densityFirst;
        double VolumeSecond = volumeCorrectionSecond * 1000 * massSecond / densitySecond;
        double VolumeThird  = volumeCorrectionThird * 1000 * massThird / densityThird;
*/

        double VolumeFirst  = volumeCorrectionFirst * massFirst;
        double VolumeSecond = volumeCorrectionSecond * massSecond;
        double VolumeThird  = volumeCorrectionThird * massThird;

        std::ostringstream streamObj;

        if (VolumeFirst > 0 && result_t1 && result_m1) {
            streamObj.str("");
            streamObj << std::fixed << std::setprecision(4) << VolumeFirst;
            ui->leVolume1->setText(streamObj.str().c_str());
        } else {
        }

        if (VolumeSecond > 0 && result_t2 && result_m2) {
            streamObj.str("");
            streamObj << std::fixed << std::setprecision(4) << VolumeSecond;
            ui->leVolume2->setText(streamObj.str().c_str());
        } else {
        }

        if (VolumeThird > 0 && result_t3 && result_m3) {
            streamObj.str("");
            streamObj << std::fixed << std::setprecision(4) << VolumeThird;
            ui->leVolume3->setText(streamObj.str().c_str());
        } else {
        }
        /// Q minim
        if (VolumeFirst > 0 && result_t1 && result_m1)
            for (unsigned iter = 0; iter < entries; ++iter) {
                resultAllTests[iter] = "ADMIS";

                if (vectorCheckNumber[iter]->isChecked()) {
                    double start{0};
                    bool   bStart{false};
                    double stop{0};
                    bool   bStop{false};
                    tmp = vectorFirstIndexStart[iter]->text().toDouble(&bConvert);
                    if (bConvert) {
                        bStart = true;
                        start  = tmp;
                    } else {
                        start                = 0;
                        result               = false;
                        resultAllTests[iter] = "RESPINS";
                    }

                    tmp = vectorFirstIndexStop[iter]->text().toDouble(&bConvert);
                    if (bConvert) {
                        bStop = true;
                        stop  = tmp;
                    } else {
                        stop                 = 0;
                        result               = false;
                        resultAllTests[iter] = "RESPINS";
                    }

                    if (bStart && bStop && (start >= 0) && (stop >= 0) &&
                        (stop >= start)) {
                        double error =
                            (stop - start - VolumeFirst) / VolumeFirst * 100;
                        streamObj.str("");
                        streamObj << std::fixed << std::setprecision(2) << error;
                        if (vectorCheckNumber[iter]->isChecked()) {
                            vectorFirstError[iter]->setText(streamObj.str().c_str());
                            if (abs(error) > maximumError) {
                                vectorFirstError[iter]->setStyleSheet(
                                    "QLineEdit { color: red }");
                                resultAllTests[iter] = "RESPINS";
                            } else {
                                vectorFirstError[iter]->setStyleSheet(
                                    "QLineEdit { color: black }");
                            }
                        } else {
                            vectorFirstError[iter]->setText("");
                        }
                        if (iter % 4 == 0 || iter % 4 == 1) {
                            vectorFirstError[iter]->setPalette(paletteOddRowErr);
                        } else {
                            vectorFirstError[iter]->setPalette(paletteEvenRowErr);
                        }
                    }
                }
            }
        /// Q transitor
        if (VolumeSecond > 0 && result_t2 && result_m2)
            for (unsigned iter = 0; iter < entries; ++iter) {
                if (vectorCheckNumber[iter]->isChecked()) {
                    double start{0};
                    bool   bStart{false};
                    double stop{0};
                    bool   bStop{false};
                    tmp = vectorSecondIndexStart[iter]->text().toDouble(&bConvert);
                    if (bConvert) {
                        bStart = true;
                        start  = tmp;
                    } else {
                        start                = 0;
                        result               = false;
                        resultAllTests[iter] = "RESPINS";
                    }
                    tmp = vectorSecondIndexStop[iter]->text().toDouble(&bConvert);
                    if (bConvert) {
                        bStop = true;
                        stop  = tmp;
                    } else {
                        stop                 = 0;
                        result               = false;
                        resultAllTests[iter] = "RESPINS";
                    }

                    if (bStart && bStop && (start >= 0) && (stop >= 0) &&
                        (stop >= start)) {
                        double error =
                            (stop - start - VolumeSecond) / VolumeSecond * 100;
                        streamObj.str("");
                        streamObj << std::fixed << std::setprecision(2) << error;
                        if (vectorCheckNumber[iter]->isChecked()) {
                            vectorSecondError[iter]->setText(streamObj.str().c_str());
                            if (abs(error) > nominalError) {
                                vectorSecondError[iter]->setStyleSheet(
                                    "QLineEdit { color: red }");
                                resultAllTests[iter] = "RESPINS";
                            } else {
                                vectorSecondError[iter]->setStyleSheet(
                                    "QLineEdit { color: black }");
                            }
                        } else {
                            vectorSecondError[iter]->setText("");
                        }
                        if (iter % 4 == 0 || iter % 4 == 1) {
                            vectorSecondError[iter]->setPalette(paletteOddRowErr);
                        } else {
                            vectorSecondError[iter]->setPalette(paletteEvenRowErr);
                        }
                    }
                }
            }
        /// Q nominal
        if (VolumeThird > 0 && result_t3 && result_m3)
            for (unsigned iter = 0; iter < entries; ++iter) {
                if (vectorCheckNumber[iter]->isChecked()) {
                    double start{0};
                    bool   bStart{false};
                    double stop{0};
                    bool   bStop{false};

                    tmp = vectorThirdIndexStart[iter]->text().toDouble(&bConvert);
                    if (bConvert) {
                        bStart = true;
                        start  = tmp;
                    } else {
                        start                = 0;
                        result               = false;
                        resultAllTests[iter] = "RESPINS";
                    }

                    tmp = vectorThirdIndexStop[iter]->text().toDouble(&bConvert);
                    if (bConvert) {
                        bStop = true;
                        stop  = tmp;
                    } else {
                        stop                 = 0;
                        result               = false;
                        resultAllTests[iter] = "RESPINS";
                    }

                    if (bStart && bStop && (start >= 0) && (stop >= 0) &&
                        (stop >= start)) {
                        double error =
                            (stop - start - VolumeThird) / VolumeThird * 100;
                        streamObj.str("");
                        streamObj << std::fixed << std::setprecision(2) << error;
                        if (vectorCheckNumber[iter]->isChecked()) {
                            vectorThirdError[iter]->setText(streamObj.str().c_str());
                            if (abs(error) > nominalError) {
                                vectorThirdError[iter]->setStyleSheet(
                                    "QLineEdit { color: red }");
                                resultAllTests[iter] = "RESPINS";
                            } else {
                                vectorThirdError[iter]->setStyleSheet(
                                    "QLineEdit { color: black }");
                            }
                        } else {
                            vectorFirstError[iter]->setText("");
                        }
                        if (iter % 4 == 0 || iter % 4 == 1) {
                            vectorThirdError[iter]->setPalette(paletteOddRowErr);
                        } else {
                            vectorThirdError[iter]->setPalette(paletteEvenRowErr);
                        }
                    }
                }
            }
        result = result_t1 && result_m1 && result_t2 && result_m2 &&
                 result_t3 && result_m3 && result;
    } else {
        double tmp{0};
        double volumeFirst{0};
        double volumeSecond{0};
        double volumeThird{0};
        bool   bConvert(false);

        // Volume for minimal flow
        tmp = ui->leVolume1->text().toDouble(&bConvert);
        if (bConvert) {
            volumeFirst = tmp;
            if (volumeFirst < 0) {
                ui->leVolume1->setPalette(paletteErr);
                volumeFirst = 100;
            }
        } else {
            ui->leVolume1->setPalette(paletteErr);
            volumeFirst = 100;
            result      = false;
        }

        // Volume for transitoriu flow
        tmp = ui->leVolume2->text().toDouble(&bConvert);
        if (bConvert) {
            volumeSecond = tmp;
            if (volumeSecond < 0) {
                ui->leVolume2->setPalette(paletteErr);
                volumeSecond = 100;
            }
        } else {
            ui->leVolume2->setPalette(paletteErr);
            volumeSecond = 100;
            result       = false;
        }

        // Volume for nominal flow
        tmp = ui->leVolume3->text().toDouble(&bConvert);
        if (bConvert) {
            volumeThird = tmp;
            if (volumeThird < 0) {
                ui->leVolume3->setPalette(paletteErr);
                volumeThird = 100;
            }
        } else {
            ui->leVolume3->setPalette(paletteErr);
            volumeThird = 100;
            result      = false;
        }
        std::ostringstream streamObj;
        /// Q minim
        for (unsigned iter = 0; iter < entries; ++iter) {
            resultAllTests[iter] = "ADMIS";

            if (vectorCheckNumber[iter]->isChecked()) {
                double start{0};
                bool   bStart{false};
                double stop{0};
                bool   bStop{false};

                tmp = vectorFirstIndexStart[iter]->text().toDouble(&bConvert);
                if (bConvert) {
                    bStart = true;
                    start  = tmp;
                } else {
                    start                = 0;
                    result               = false;
                    resultAllTests[iter] = "RESPINS";
                }
                tmp = vectorFirstIndexStop[iter]->text().toDouble(&bConvert);
                if (bConvert) {
                    bStop = true;
                    stop  = tmp;
                } else {
                    stop                 = 0;
                    result               = false;
                    resultAllTests[iter] = "RESPINS";
                }
                if (bStart && bStop && (start >= 0) && (stop >= 0) &&
                    (stop >= start)) {
                    double error = (stop - start - volumeFirst) / volumeFirst * 100;
                    streamObj.str("");
                    streamObj << std::fixed << std::setprecision(2) << error;
                    vectorFirstError[iter]->setText(streamObj.str().c_str());
                    if (abs(error) > maximumError) {
                        vectorFirstError[iter]->setStyleSheet(
                            "QLineEdit { color: red }");
                        result               = false;
                        resultAllTests[iter] = "RESPINS";
                    } else {
                        vectorFirstError[iter]->setStyleSheet(
                            "QLineEdit { color: black }");
                    }
                    if (iter % 4 == 0 || iter % 4 == 1) {
                        vectorFirstError[iter]->setPalette(paletteOddRowErr);
                    } else {
                        vectorFirstError[iter]->setPalette(paletteEvenRowErr);
                    }
                }
            }
        }
        /// Q transition
        for (unsigned iter = 0; iter < entries; ++iter) {
            if (vectorCheckNumber[iter]->isChecked()) {
                double start{0};
                bool   bStart{false};
                double stop{0};
                bool   bStop{false};
                tmp = vectorSecondIndexStart[iter]->text().toDouble(&bConvert);
                if (bConvert) {
                    bStart = true;
                    start  = tmp;
                } else {
                    start                = 0;
                    result               = false;
                    resultAllTests[iter] = "RESPINS";
                }

                tmp = vectorSecondIndexStop[iter]->text().toDouble(&bConvert);
                if (bConvert) {
                    bStop = true;
                    stop  = tmp;
                } else {
                    stop                 = 0;
                    result               = false;
                    resultAllTests[iter] = "RESPINS";
                }

                if (bStart && bStop && (start >= 0) && (stop >= 0) &&
                    (stop >= start)) {
                    double error =
                        (stop - start - volumeSecond) / volumeSecond * 100;
                    streamObj.str("");
                    streamObj << std::fixed << std::setprecision(2) << error;
                    vectorSecondError[iter]->setText(streamObj.str().c_str());
                    if (abs(error) > maximumError) {
                        vectorSecondError[iter]->setStyleSheet(
                            "QLineEdit { color: red }");
                        resultAllTests[iter] = "RESPINS";
                    } else {
                        vectorSecondError[iter]->setStyleSheet(
                            "QLineEdit { color: black }");
                    }
                    if (iter % 4 == 0 || iter % 4 == 1) {
                        vectorSecondError[iter]->setPalette(paletteOddRowErr);
                    } else {
                        vectorSecondError[iter]->setPalette(paletteEvenRowErr);
                    }
                }
            }
        }
        /// Q nominal
        for (unsigned iter = 0; iter < entries; ++iter) {
            if (vectorCheckNumber[iter]->isChecked()) {
                double start{0};
                bool   bStart{false};
                double stop{0};
                bool   bStop{false};
                tmp = vectorThirdIndexStart[iter]->text().toDouble(&bConvert);
                if (bConvert) {
                    bStart = true;
                    start  = tmp;
                } else {
                    start                = 0;
                    result               = false;
                    resultAllTests[iter] = "RESPINS";
                }

                tmp = vectorThirdIndexStop[iter]->text().toDouble(&bConvert);
                if (bConvert) {
                    bStop = true;
                    stop  = tmp;
                } else {
                    stop                 = 0;
                    result               = false;
                    resultAllTests[iter] = "RESPINS";
                }

                if (bStart && bStop && (start >= 0) && (stop >= 0) &&
                    (stop >= start)) {
                    double error = (stop - start - volumeThird) / volumeThird * 100;
                    streamObj.str("");
                    streamObj << std::fixed << std::setprecision(2) << error;
                    vectorThirdError[iter]->setText(streamObj.str().c_str());
                    if (abs(error) > maximumError) {
                        vectorThirdError[iter]->setStyleSheet(
                            "QLineEdit { color: red }");
                        resultAllTests[iter] = "RESPINS";
                    } else {
                        vectorThirdError[iter]->setStyleSheet(
                            "QLineEdit { color: black }");
                    }

                    if (iter % 4 == 0 || iter % 4 == 1) {
                        vectorThirdError[iter]->setPalette(paletteOddRowErr);
                    } else {
                        vectorThirdError[iter]->setPalette(paletteEvenRowErr);
                    }
                }
            }
        }
    }
    if (!result) {
        QMessageBox messageInputData;
        messageInputData.setWindowTitle(
            tr("Collected data from flow meters."));
        messageInputData.setText(
            tr("Some user input data are not available or are outside the "
               "normal rage!"));
        messageInputData.setStandardButtons(QMessageBox::Ok);
        messageInputData.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                        Qt::WindowTitleHint |
                                        Qt::WindowCloseButtonHint);
        if (messageInputData.exec() == QMessageBox::Ok) {
            messageInputData.close();
        }
    }
}

/**
 * \brief Slot triggered when the "Close" button is clicked.
 *
 * This function hides the current dialog window.
 */
void TableBoard::onCloseClicked() {
    this->hide();
}

/**
 * \brief Slot triggered when the type of water meter is changed.
 *
 * This function repopulates the table based on the new type of water meter selected.
 * It updates the UI with relevant data for the new meter type.
 */
void TableBoard::onTypeMeterChanged() {
    PopulateTable();
}

/**
 * \brief Slot triggered when the number of water meters is changed.
 *
 * This function repopulates the table based on the new number of water meters selected.
 * It updates the UI with relevant data for the new number of meters.
 */
void TableBoard::onNumberOfWaterMetersChanged() {
    PopulateTable();
}

/**
 * \brief Slot triggered when a checkbox in the vectorCheckNumber is clicked.
 *
 * This function handles the enabling or disabling of related input fields
 * based on the state of the checkbox.
 *
 * \param checked Indicates whether the checkbox is checked (true) or unchecked (false).
 */
void TableBoard::onCbClicked(bool checked) {
    QObject*   obj      = sender();                      // Get the object that triggered the signal
    QCheckBox* checkBox = dynamic_cast<QCheckBox*>(obj); // Attempt to cast to QCheckBox

    // Find the checkbox in the vectorCheckNumber
    auto iter = std::find(vectorCheckNumber.begin(), vectorCheckNumber.end(), checkBox);
    if (iter != vectorCheckNumber.end()) {
        // Calculate the index of the checkbox in the vector
        auto index = std::distance(vectorCheckNumber.begin(), iter);

        // Enable or disable related input fields based on the checkbox state
        vectorSerialNumber[index]->setDisabled(!checked);
        vectorFirstIndexStart[index]->setDisabled(!checked);
        vectorFirstIndexStop[index]->setDisabled(!checked);
        vectorSecondIndexStart[index]->setDisabled(!checked);
        vectorSecondIndexStop[index]->setDisabled(!checked);
        vectorThirdIndexStart[index]->setDisabled(!checked);
        vectorThirdIndexStop[index]->setDisabled(!checked);
    }
}

/**
 * \brief Slot triggered when the state of the "Select All" checkbox (ui->cbSet) changes.
 *
 * This function sets the check state of all checkboxes in vectorCheckNumber to match
 * the check state of ui->cbSet.
 */
void TableBoard::onSelectAllChanged() {
    Qt::CheckState checkState = ui->cbSet->checkState();

    // Set the check state of all checkboxes in vectorCheckNumber
    for (auto* checkbox : vectorCheckNumber) {
        checkbox->setCheckState(checkState);
    }
}

/**
 * \brief Custom event filter to handle key events for the dialog.
 *
 * This function filters key press events, specifically handling Enter (Return) key presses
 * to focus on the next child widget.
 *
 * \param target The object that receives the event.
 * \param event The event that occurred.
 * \return true if the event was handled, otherwise false.
 */
bool TableBoard::eventFilter(QObject* target, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // Handle Enter (Return) key press
        if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
            focusNextChild(); // Focus on the next child widget
            return true;      // Event handled
        }
    }

    // Call base event filter for other event types
    return QDialog::eventFilter(target, event);
}

/**
 * \brief Slot triggered when the measurement type changes.
 *
 * This function adjusts the visibility, read-only status, and background color
 * of widgets based on whether the measurement type is gravimetric or not.
 *
 * \note Assumes the presence of specific UI elements: ui->leMass1, ui->leMass2, ui->leMass3,
 *       ui->lbMass1, ui->lbMass2, ui->lbMass3, ui->leTemperature1, ui->leTemperature2, ui->leTemperature3,
 *       ui->lbTemperature1, ui->lbTemperature2, ui->lbTemperature3, ui->leVolume1, ui->leVolume2, ui->leVolume3.
 */
void TableBoard::onMeasurementTypeChanged() {
    const bool isGravimetric = mainwindow->selectedInfo.rbGravimetric_new;

    // Lambda function to set background color and read-only status for QLineEdit
    auto setBackgroundAndReadOnly = [](QLineEdit* lineEdit, bool isReadOnly) {
        lineEdit->setReadOnly(isReadOnly);
        lineEdit->setStyleSheet(isReadOnly ? "QLineEdit {background-color: rgb(220, 235, 220)}" : "QLineEdit {background-color: rgb(235, 235, 235)}");
    };

    // Lambda function to set visibility of QWidget
    auto setElementVisibility = [](QWidget* widget, bool isVisible) {
        widget->setVisible(isVisible);
    };

    // Show or hide elements based on measurement type
    setElementVisibility(ui->lbMass1, isGravimetric);
    setElementVisibility(ui->lbMass2, isGravimetric);
    setElementVisibility(ui->lbMass3, isGravimetric);
    setElementVisibility(ui->leMass1, isGravimetric);
    setElementVisibility(ui->leMass2, isGravimetric);
    setElementVisibility(ui->leMass3, isGravimetric);

    setElementVisibility(ui->lbTemperature1, isGravimetric);
    setElementVisibility(ui->lbTemperature2, isGravimetric);
    setElementVisibility(ui->lbTemperature3, isGravimetric);
    setElementVisibility(ui->leTemperature1, isGravimetric);
    setElementVisibility(ui->leTemperature2, isGravimetric);
    setElementVisibility(ui->leTemperature3, isGravimetric);

    // Set read-only status and background color for volume line edits
    setBackgroundAndReadOnly(ui->leVolume1, isGravimetric);
    setBackgroundAndReadOnly(ui->leVolume2, isGravimetric);
    setBackgroundAndReadOnly(ui->leVolume3, isGravimetric);
}

/**
 * \brief Slot triggered when the user clicks the Print PDF button.
 *
 * This function initiates the calculation process and then sets the result
 * for all tests to "RESPINS" for each entry.
 *
 * \note This function assumes the presence of the following:
 *       - resultAllTests[] array with a size of at least mainwindow->selectedInfo.entriesNumber
 *       - onCalculateClicked() function to perform calculations before setting results
 */
void TableBoard::onPrintPdfDocClicked() {
    onCalculateClicked();
    size_t count{0};
    for (size_t iter = 0; iter != mainwindow->selectedInfo.entriesNumber;
         ++iter) {
        resultAllTests[iter] = "RESPINS";
    }
    QString companyName =
        mainwindow->optionsConfiguration["company"].c_str();
    QDateTime date          = QDateTime::currentDateTime();
    QString   formattedTime = date.toString(" dd.MM.yyyy / hh:mm:ss");
    if (mainwindow->selectedInfo.selectedLanguage == ROMANIAN) {
        formattedTime = QString("Data / Ora:") + formattedTime;
    } else {
        formattedTime = QString("Date / Time:") + formattedTime;
    }
    std::string ambientTemperature =
        mainwindow->selectedInfo.ambientTemperature;
    std::string athmosphericPressure =
        mainwindow->selectedInfo.athmosphericPressure;
    std::string humidity = mainwindow->selectedInfo.relativeAirHumidity;

    std::string temperatureMinimum   = ui->leTemperature1->text().toStdString();
    std::string temperatureTransitor = ui->leTemperature2->text().toStdString();
    std::string temperatureNominal   = ui->leTemperature3->text().toStdString();

    std::string standardVolumeMinimum   = ui->leVolume1->text().toStdString();
    std::string standardVolumeTransitor = ui->leVolume2->text().toStdString();
    std::string standardVolumeNominal   = ui->leVolume3->text().toStdString();

    std::string standardMassMinimum   = ui->leMass1->text().toStdString();
    std::string standardMassTransitor = ui->leMass2->text().toStdString();
    std::string standardMassNominal   = ui->leMass3->text().toStdString();

    QString certificate = mainwindow->selectedInfo.certificate.c_str();
    QString nameSelectedWaterMeter =
        mainwindow->selectedInfo.nameWaterMeter.c_str();
    unsigned nominalDiameter = mainwindow->selectedInfo.nominalDiameter;
    QString  methodMeasurement{"Volumetric"};
    if (mainwindow->selectedInfo.rbGravimetric_new == true) {
        methodMeasurement = "Gravitmetric";
    }
    double  minimumFlow   = mainwindow->selectedInfo.minimumFlow;
    double  trasitionFlow = mainwindow->selectedInfo.transitionFlow;
    double  nominalFlow   = mainwindow->selectedInfo.nominalFlow;
    double  maximumFlow   = mainwindow->selectedInfo.maximumFlow;
    QString minimumFlowString =
        to_string_with_precision(minimumFlow, 0).c_str();
    QString transitionFlowString =
        to_string_with_precision(trasitionFlow, 0).c_str();
    QString nominalFlowString =
        to_string_with_precision(nominalFlow, 0).c_str();
    QString maximumFlowString =
        to_string_with_precision(maximumFlow, 0).c_str();
    auto size = minimumFlowString.size();
    for (auto iter = 1; iter < 10 - size; iter++) {
        minimumFlowString = QString("&nbsp;") + minimumFlowString;
    }
    size = transitionFlowString.size();
    for (auto iter = 1; iter < 10 - size; iter++) {
        transitionFlowString = QString("&nbsp;") + transitionFlowString;
    }
    size = nominalFlowString.size();
    for (auto iter = 1; iter < 10 - size; iter++) {
        nominalFlowString = QString("&nbsp;") + nominalFlowString;
    }
    size = maximumFlowString.size();
    for (auto iter = 1; iter < 10 - size; iter++) {
        maximumFlowString = QString("&nbsp;") + maximumFlowString;
    }
    double nominalWaterMeterError = mainwindow->selectedInfo.nominalError;
    double maximumWaterMeterError = mainwindow->selectedInfo.maximumError;
    if (mainwindow->selectedInfo.selectedLanguage == ROMANIAN) {
        size_t totalEntries{0};
        report =
            QString("<!DOCTYPE html>\n") +
            "<html>\n" +
            "<head>\n" +
            "   <style>\n" +
            "       table {\n" +
            "           width: 100%;\n" +
            "           border-spacing: 0;" + // Ensures no space between cells
            "       }\n" +
            "       th, td {\n" +
            "           border: 1px solid black;\n" +
            "           width: 100%;\n" +
            "           font-family: Courier New;\n" +
            "           font-size: 10px;\n" + // Corrected font-size
            "           font-weight: 700;\n" +
            "           table-layout: fixed;\n" +
            "       }\n" +
            "       th {\n" +
            "           word-wrap: break-word;\n" +
            "       }\n" +
            "   </style>\n" +
            "</head>\n" +
            "<body>\n" +
            "</body>\n" +
            "</html>\n" +

            "<body style=\"font-family:'Courier New'\" \"font-weight: 700\" "
            "style=\"font-size: 4\" style=\"text-align: left\" >" +
            "<h4>" + companyName + "<br>" +
            ">>>> Instalatie de verificare debitmetre si contoare de apa >>>></h4>" +
            "<h4 style=\"text-align: center\"><u>Fisa de masuratori</u></h4>" +
            "<h4>" + formattedTime + "<br>" +
            "Numar certificat:&nbsp;" +
            certificate + "&nbsp;<br>" + "Temperatura:&nbsp;" +
            to_string_with_precision(ambientTemperature, 1).c_str() +
            "&nbsp;[°C]<br>" + "Presiune atmosferica:&nbsp;" +
            to_string_with_precision(athmosphericPressure, 1).c_str() +
            "&nbsp;[mbar]<br>" + "Umiditate:&nbsp;" +
            to_string_with_precision(humidity, 1).c_str() +
            "&nbsp;[%]<br><br>" + "Tip contor apa:&nbsp;" + nameSelectedWaterMeter +
            "<br>" + "Medoda de verificare:&nbsp;" + methodMeasurement +
            "<br>" + "Diametru nominal:&nbsp;" +
            to_string_with_precision(nominalDiameter, 2).c_str() +

            "<br>"

            "<style>"
            "     th, td {"
            "          text-align: center;"
            "      }"
            "</style>";

        if ("Gravitmetric" == methodMeasurement) {
            report +=
                "<table style=\"border-collapse: collapse;\">"
                "   <tr>"
                "       <th></th>"
                "       <th>Volum etalon<br>&nbsp;&nbsp;[L]</th>"
                "       <th>&nbsp;Masa<br>&nbsp;[kg]</th>"
                "       <th>Temperatura<br>&nbsp;[°C]</th>"
                "       <th>Debit<br>&nbsp;&nbsp;[L/h]</th>"
                "   </tr>"
                "   <tr>"
                "       <td>&nbsp;Qmin&nbsp;</td>"
                "       <td>" +
                standardVolumeMinimum + "</td>"
                                        "       <td>" +
                standardMassMinimum + "</td>"
                                      "       <td>" +
                temperatureMinimum + "</td>"
                                     "       <td>" +
                minimumFlowString.toStdString() + "</td>"
                                                  "   </tr>"
                                                  "   <tr>"
                                                  "       <td>&nbsp;Qt&nbsp;</td>"
                                                  "       <td>" +
                standardVolumeTransitor + "</td>"
                                          "       <td>" +
                standardMassTransitor + "</td>"
                                        "       <td>" +
                temperatureTransitor.c_str() + "</td>"
                                               "       <td>" +
                transitionFlowString.toStdString() + "</td>"
                                                     "   </tr>"
                                                     "   <tr>"
                                                     "       <td>&nbsp;Qn&nbsp;</td>"
                                                     "       <td>" +
                standardVolumeNominal + "</td>"
                                        "       <td>" +
                standardMassNominal + "</td>"
                                      "       <td>" +
                temperatureNominal.c_str() + "</td>"
                                             "       <td>" +
                nominalFlowString.toStdString() + "</td>"
                                                  "   </tr>"
                                                  "</table>"
                                                  "<br>";
        } else {
            report +=
                "<table style=\"border-collapse: collapse;\">"
                "   <tr>"
                "       <th></th>"
                "       <th>Volum etalon<br>&nbsp;&nbsp;[L]</th>"
                "       <th>Debit<br>&nbsp;&nbsp;[L/h]</th>"
                "   </tr>"
                "   <tr>"
                "       <td>&nbsp;Qmin&nbsp;</td>"
                "       <td>" +
                standardVolumeMinimum + "</td>"
                                        "       <td>" +
                minimumFlowString.toStdString() + "</td>"
                                                  "   </tr>"
                                                  "   <tr>"
                                                  "       <td>&nbsp;Qt&nbsp;</td>"
                                                  "       <td>" +
                standardVolumeTransitor + "</td>"
                                          "       <td>" +
                transitionFlowString.toStdString() + "</td>"
                                                     "   </tr>"
                                                     "   <tr>"
                                                     "       <td>&nbsp;Qn&nbsp;</td>"
                                                     "       <td>" +
                standardVolumeNominal + "</td>"
                                        "       <td>" +
                nominalFlowString.toStdString() + "</td>"
                                                  "   </tr>"
                                                  "</table>"
                                                  "<br>";
        }

        report +=
            QString("<table style=\"border: 1px solid black; border-collapse: collapse; border-spacing: 0; width: 100%;\">") +
            "\n    <caption>Rezultate test:</caption>" +
            "\n    <thead>" +
            "\n        <tr>" +
            "\n            <th style=\"border: 1px solid black;\" width=\"15%\">Serie (Tip)</th>"
            "\n            <th style=\"border: 1px solid black;\" width=\"9%\">&nbsp;Debit&nbsp;&nbsp;[L/h]</th>"
            "\n            <th style=\"border: 1px solid black;\" width=\"14%\">Index start [L]</th>"
            "\n            <th style=\"border: 1px solid black;\" width=\"14%\">Index stop&nbsp;[L]</th>"
            "\n            <th style=\"border: 1px solid black;\" width=\"14%\">Volum contor [L]</th>"
            "\n            <th style=\"border: 1px solid black;\" width=\"14%\">Volum etalon [L]</th>"
            "\n            <th style=\"border: 1px solid black;\" width=\"9%\">Eroare [%]</th>"
            "\n            <th style=\"border: 1px solid black;\" width=\"15%\">Rezultate</th>"
            "\n        </tr>" +
            "\n    </thead>" +
            "\n    <tbody>";

        unsigned iter{0};
        size_t   entriesTable = mainwindow->selectedInfo.entriesNumber;
        for (; iter < 10 && iter < entriesTable; ++iter) {
            if (!vectorCheckNumber[iter]->checkState()) {
                continue;
            }
            QString SN         = vectorSerialNumber[iter]->text();
            QString startFirst = vectorFirstIndexStart[iter]->text() + "&nbsp;";
            QString stopFirst  = vectorFirstIndexStop[iter]->text() + "&nbsp;";
            QString registerVolumeDoubleFirst =
                QString::number((vectorFirstIndexStop[iter]->text().toDouble() -
                                 vectorFirstIndexStart[iter]->text().toDouble()));
            QString errorFirst = vectorFirstError[iter]->text() + "&nbsp;";
            QString realVolumeFirst =
                QString(precision_4(ui->leVolume1->text().toDouble()).c_str()) +
                "&nbsp;";
            if (vectorFirstIndexStart[iter]->text() == "" || vectorFirstIndexStop[iter]->text() == "") {
                registerVolumeDoubleFirst = "";
            }
            QString startSecond = vectorSecondIndexStart[iter]->text() + "&nbsp;";
            QString stopSecond  = vectorSecondIndexStop[iter]->text() + "&nbsp;";
            QString registerVolumeDoubleSecond =
                QString::number((vectorSecondIndexStop[iter]->text().toDouble() -
                                 vectorSecondIndexStart[iter]->text().toDouble()));
            QString errorSecond = vectorSecondError[iter]->text() + "&nbsp;";
            QString realVolumeSecond =
                QString(precision_4(ui->leVolume2->text().toDouble()).c_str()) +
                "&nbsp;";
            if (vectorSecondIndexStart[iter]->text() == "" || vectorSecondIndexStop[iter]->text() == "") {
                registerVolumeDoubleSecond = "";
            }
            QString startThird = vectorThirdIndexStart[iter]->text() + "&nbsp;";
            QString stopThird  = vectorThirdIndexStop[iter]->text() + "&nbsp;";
            QString registerVolumeDoubleThird =
                QString::number((vectorThirdIndexStop[iter]->text().toDouble() -
                                 vectorThirdIndexStart[iter]->text().toDouble()));
            QString errorThird = vectorThirdError[iter]->text() + "&nbsp;";
            QString realVolumeThird =
                QString(precision_4(ui->leVolume3->text().toDouble()).c_str()) +
                "&nbsp;";
            if (vectorThirdIndexStart[iter]->text() == "" || vectorThirdIndexStop[iter]->text() == "") {
                registerVolumeDoubleThird = "";
            }
            if (XOR(startFirst.isEmpty(), stopFirst.isEmpty()) ||
                XOR(startSecond.isEmpty(), stopSecond.isEmpty()) ||
                XOR(startThird.isEmpty(), stopThird.isEmpty()) ||
                SN.isEmpty()) {
                continue;
            }
            ++totalEntries;
            QString resultTests{"ADMIS"};
            try {
                bool bFirst =
                    std::abs(std::stod(errorFirst.toStdString().c_str())) <=
                    maximumWaterMeterError;
                bool bSecond =
                    std::abs(std::stod(errorSecond.toStdString().c_str())) <=
                    nominalWaterMeterError;
                bool bThird =
                    std::abs(std::stod(errorThird.toStdString().c_str())) <=
                    nominalWaterMeterError;
                resultTests =
                    (bFirst && bSecond && bThird ? "ADMIS" : "RESPINS");
            } catch (...) {
                resultTests = "RESPINS";
            }
            resultAllTests[count++] = resultTests;
            double minimumFlowRate  = ui->leFlowRateMinumum->text().toDouble();
            double trasitionFlowRate =
                ui->leFlowRateTransitoriu->text().toDouble();
            double nominalFlowRate = ui->leFlowRateNominal->text().toDouble();
            report +=
                QString("    <tr>") +
                "        <th style=\"text-align: left; border: 1px solid black;\" rowspan=\"3\"><br>&nbsp;" + SN + "</th>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 2px;\">" + QString::number(minimumFlowRate) + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startFirst + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopFirst + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleFirst + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeFirst + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorFirst + "</td>" +
                "        <th style=\"text-align: center; border: 1px solid black;\" rowspan=\"3\">" + resultTests + "</th>" +
                "    </tr>" +
                "    <tr>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(trasitionFlowRate) + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startSecond + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopSecond + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleSecond + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeSecond + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorSecond + "</td>" +
                "    </tr>" +
                "    <tr>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(nominalFlowRate) + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startThird + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopThird + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleThird + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeThird + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorThird + "</td>" +
                "    </tr>";
        };
        report += QString("</tbody>") + "</table>";

        /////// Page two
        bool header{true};
        if (iter < entriesTable) {
            for (unsigned iterEntry = 10; iterEntry < entriesTable; ++iterEntry) {
                if (totalEntries == 10 && header) {
                    report += "<br><br><br><br><br><br><br><br><br><br>";
                    report +=
                        QString("<table style=\"border: 1px solid black; border-collapse: collapse; border-spacing: 0; width: 100%;\">") +
                        "\n    <caption>Rezultate test:</caption>" +
                        "\n    <thead>" +
                        "\n        <tr>" +
                        "\n            <th style=\"border: 1px solid black;\" width=\"15%\">Serie (Tip)</th>"
                        "\n            <th style=\"border: 1px solid black;\" width=\"9%\">&nbsp;Debit&nbsp;&nbsp;[L/h]</th>"
                        "\n            <th style=\"border: 1px solid black;\" width=\"14%\">Index start [L]</th>"
                        "\n            <th style=\"border: 1px solid black;\" width=\"14%\">Index stop&nbsp;[L]</th>"
                        "\n            <th style=\"border: 1px solid black;\" width=\"14%\">Volum contor [L]</th>"
                        "\n            <th style=\"border: 1px solid black;\" width=\"14%\">Volum etalon [L]</th>"
                        "\n            <th style=\"border: 1px solid black;\" width=\"9%\">Eroare [%]</th>"
                        "\n            <th style=\"border: 1px solid black;\" width=\"15%\">Rezultate</th>"
                        "\n        </tr>" +
                        "\n    </thead>" +
                        "\n    <tbody>";
                    header = false;
                }
                if (!vectorCheckNumber[iterEntry]->checkState()) {
                    continue;
                }
                QString SN         = vectorSerialNumber[iterEntry]->text();
                QString startFirst = vectorFirstIndexStart[iterEntry]->text() + "&nbsp;";
                QString stopFirst  = vectorFirstIndexStop[iterEntry]->text() + "&nbsp;";
                QString registerVolumeDoubleFirst =
                    QString::number((vectorFirstIndexStop[iterEntry]->text().toDouble() -
                                     vectorFirstIndexStart[iterEntry]->text().toDouble()));
                QString errorFirst = vectorFirstError[iterEntry]->text() + "&nbsp;";
                QString realVolumeFirst =
                    QString(precision_4(ui->leVolume1->text().toDouble()).c_str()) +
                    "&nbsp;";
                if (vectorFirstIndexStart[iterEntry]->text() == "" || vectorFirstIndexStop[iterEntry]->text() == "") {
                    registerVolumeDoubleFirst = "";
                }
                QString startSecond = vectorSecondIndexStart[iterEntry]->text() + "&nbsp;";
                QString stopSecond  = vectorSecondIndexStop[iterEntry]->text() + "&nbsp;";
                QString registerVolumeDoubleSecond =
                    QString::number((vectorSecondIndexStop[iterEntry]->text().toDouble() -
                                     vectorSecondIndexStart[iterEntry]->text().toDouble()));
                QString errorSecond = vectorSecondError[iterEntry]->text() + "&nbsp;";
                QString realVolumeSecond =
                    QString(precision_4(ui->leVolume2->text().toDouble()).c_str()) +
                    "&nbsp;";
                if (vectorSecondIndexStart[iterEntry]->text() == "" || vectorSecondIndexStop[iterEntry]->text() == "") {
                    registerVolumeDoubleSecond = "";
                }
                QString startThird = vectorThirdIndexStart[iterEntry]->text() + "&nbsp;";
                QString stopThird  = vectorThirdIndexStop[iterEntry]->text() + "&nbsp;";
                QString registerVolumeDoubleThird =
                    QString::number((vectorThirdIndexStop[iterEntry]->text().toDouble() -
                                     vectorThirdIndexStart[iterEntry]->text().toDouble()));
                QString errorThird = vectorThirdError[iterEntry]->text() + "&nbsp;";
                QString realVolumeThird =
                    QString(precision_4(ui->leVolume3->text().toDouble()).c_str()) +
                    "&nbsp;";
                if (vectorThirdIndexStart[iterEntry]->text() == "" || vectorThirdIndexStop[iterEntry]->text() == "") {
                    registerVolumeDoubleThird = "";
                }
                if (XOR(startFirst.isEmpty(), stopFirst.isEmpty()) ||
                    XOR(startSecond.isEmpty(), stopSecond.isEmpty()) ||
                    XOR(startThird.isEmpty(), stopThird.isEmpty()) ||
                    SN.isEmpty()) {
                    continue;
                }
                ++totalEntries;
                QString resultTests{"ADMIS"};
                try {
                    bool bFirst =
                        std::abs(std::stod(errorFirst.toStdString().c_str())) <
                        maximumWaterMeterError;
                    bool bSecond =
                        std::abs(std::stod(errorSecond.toStdString().c_str())) <
                        nominalWaterMeterError;
                    bool bThird =
                        std::abs(std::stod(errorThird.toStdString().c_str())) <
                        nominalWaterMeterError;
                    resultTests =
                        (bFirst && bSecond && bThird ? "ADMIS" : "RESPINS");
                } catch (...) {
                    resultTests = "RESPINS";
                }
                resultAllTests[count++] = resultTests;
                double minimumFlowRate  = ui->leFlowRateMinumum->text().toDouble();
                double trasitionFlowRate =
                    ui->leFlowRateTransitoriu->text().toDouble();
                double nominalFlowRate = ui->leFlowRateNominal->text().toDouble();
                report +=
                    QString("    <tr>") +
                    "        <th style=\"text-align: left; border: 1px solid black;\" rowspan=\"3\"><br>&nbsp;" + SN + "</th>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 2px;\">" + QString::number(minimumFlowRate) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startFirst + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopFirst + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleFirst + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeFirst + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorFirst + "</td>" +
                    "        <th style=\"text-align: center; border: 1px solid black;\" rowspan=\"3\">" + resultTests + "</th>" +
                    "    </tr>" +
                    "    <tr>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(trasitionFlowRate) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startSecond + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopSecond + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleSecond + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeSecond + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorSecond + "</td>" +
                    "    </tr>" +
                    "    <tr>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(nominalFlowRate) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startThird + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopThird + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleThird + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeThird + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorThird + "</td>" +
                    "    </tr>";
            };
            report += QString("</tbody>") + "</table>";
        }
        ////////////////
        report += QString("<br><pre><h3>") +
                  "  Verificator metrolog                   Responsabil tehnic<br><br>" +
                  "  Nume ________________________          Nume ________________________<br>" +
                  "<br>" +
                  "  Semnatura ___________________          Semnatura ___________________<br>" +
                  "</h3></pre>";

        ui->pbPrint->setEnabled(false);
        QTimerGenerareFM->start(2000);

        std::thread pdfThread(printPdfThread, report);
        pdfThread.detach();
    }

    // English translation
    else {
        size_t totalEntries{0};
        report = QString("<!DOCTYPE html>\n") +
                 report =
                     QString("<!DOCTYPE html>\n") +
                     "<html>\n" +
                     "<head>\n" +
                     "   <style>\n" +
                     "       table {\n" +
                     "           width: 100%;\n" +
                     "           border-spacing: 0;" + // Ensures no space between cells
                     "       }\n" +
                     "       th, td {\n" +
                     "           border: 1px solid black;\n" +
                     "           width: 100%;\n" +
                     "           font-family: Courier New;\n" +
                     "           font-size: 9px;\n" + // Corrected font-size
                     "           font-weight: 700;\n" +
                     "           table-layout: fixed;\n" +
                     "       }\n" +
                     "       th {\n" +
                     "           word-wrap: break-word;\n" +
                     "       }\n" +
                     "   </style>\n" +
                     "</head>\n" +
                     "<body>\n" +
                     "</body>\n" +
                     "</html>\n" +

                     "<body style=\"font-family:'Courier New'\" \"font-weight: 700\" "
                     "style=\"font-size: 5\" style=\"text-align: left\" >" +
                     "<h4>" + companyName + "</h4>\n" +
                     "<h4 class=\"header\">Water meters test bench</h4>\n" +
                     "<h4 class=\"header\"><u>Measurement sheet</u></h4><br>\n" +
                     "<h4>" + formattedTime + "<br>\n" +
                     "Certificate number:&nbsp;" +
                     certificate + "&nbsp;<br>" + "Temperature:&nbsp;" +
                     to_string_with_precision(ambientTemperature, 2).c_str() +
                     "&nbsp;[°C]<br>" + "Atmospheric pressure:&nbsp;" +
                     to_string_with_precision(athmosphericPressure, 2).c_str() +
                     "&nbsp;[mbar]<br>" + "Humidity:&nbsp;" +
                     to_string_with_precision(humidity, 2).c_str() +
                     "&nbsp;[%]<br><br>" + "Water meter type:&nbsp;" +
                     nameSelectedWaterMeter + "<br>" + "Used measurement method:&nbsp;" +
                     methodMeasurement + "<br>" + "Nominal diameter:&nbsp;" +
                     to_string_with_precision(nominalDiameter, 2).c_str() +
                     "</body>\n" +
                     "</html>\n";

        if ("Gravitmetric" == methodMeasurement) {
            report +=
                "<table style=\"border-collapse: collapse;\">"
                "   <tr>"
                "       <th></th>"
                "       <th>Standard Volume<br>&nbsp;&nbsp;[L]</th>"
                "       <th>&nbsp;Mass<br>&nbsp;[kg]</th>"
                "       <th>Temperature<br>&nbsp;[°C]</th>"
                "       <th>Flow Rate<br>&nbsp;&nbsp;[L/h]</th>"
                "   </tr>"
                "   <tr>"
                "       <td>&nbsp;Qmin&nbsp;</td>"
                "       <td>" +
                standardVolumeMinimum + "</td>"
                                        "       <td>" +
                standardMassMinimum + "</td>"
                                      "       <td>" +
                temperatureMinimum + "</td>"
                                     "       <td>" +
                minimumFlowString.toStdString() + "</td>"
                                                  "   </tr>"
                                                  "   <tr>"
                                                  "       <td>&nbsp;Qt&nbsp;</td>"
                                                  "       <td>" +
                standardVolumeTransitor + "</td>"
                                          "       <td>" +
                standardMassTransitor + "</td>"
                                        "       <td>" +
                temperatureTransitor.c_str() + "</td>"
                                               "       <td>" +
                transitionFlowString.toStdString() + "</td>"
                                                     "   </tr>"
                                                     "   <tr>"
                                                     "       <td>&nbsp;Qn&nbsp;</td>"
                                                     "       <td>" +
                standardVolumeNominal + "</td>"
                                        "       <td>" +
                standardMassNominal + "</td>"
                                      "       <td>" +
                temperatureNominal.c_str() + "</td>"
                                             "       <td>" +
                nominalFlowString.toStdString() + "</td>"
                                                  "   </tr>"
                                                  "</table>"
                                                  "<br>";
        } else {
            report +=
                "<table style=\"border-collapse: collapse;\">"
                "   <tr>"
                "       <th></th>"
                "       <th>Standard Volume<br>&nbsp;&nbsp;[L]</th>"
                "       <th>Flow Rate<br>&nbsp;&nbsp;[L/h]</th>"
                "   </tr>"
                "   <tr>"
                "       <td>&nbsp;Qmin&nbsp;</td>"
                "       <td>" +
                standardVolumeMinimum + "</td>"
                                        "       <td>" +
                minimumFlowString.toStdString() + "</td>"
                                                  "   </tr>"
                                                  "   <tr>"
                                                  "       <td>&nbsp;Qt&nbsp;</td>"
                                                  "       <td>" +
                standardVolumeTransitor + "</td>"
                                          "       <td>" +
                transitionFlowString.toStdString() + "</td>"
                                                     "   </tr>"
                                                     "   <tr>"
                                                     "       <td>&nbsp;Qn&nbsp;</td>"
                                                     "       <td>" +
                standardVolumeNominal + "</td>"
                                        "       <td>" +
                nominalFlowString.toStdString() + "</td>"
                                                  "   </tr>"
                                                  "</table>"
                                                  "<br>";
        }

        report +=
            QString("<table style=\"border: 1px solid black; border-collapse: collapse; border-spacing: 0; width: 100%;\">\n") +
            "    <caption>Test Results:</caption>\n" +
            "    <thead>\n" +
            "        <tr>\n" +
            "            <th style=\"border: 1px solid black;\" width=\"15%\">Series (Type)</th>\n" +
            "            <th style=\"border: 1px solid black;\" width=\"9%\">&nbsp;Flow&nbsp;&nbsp;[L/h]</th>\n" +
            "            <th style=\"border: 1px solid black;\" width=\"14%\">Start Index [L]</th>\n" +
            "            <th style=\"border: 1px solid black;\" width=\"14%\">Stop Index [L]</th>\n" +
            "            <th style=\"border: 1px solid black;\" width=\"14%\">Meter Volume [L]</th>\n" +
            "            <th style=\"border: 1px solid black;\" width=\"14%\">Reference Volume [L]</th>\n" +
            "            <th style=\"border: 1px solid black;\" width=\"9%\">Error [%]</th>\n" +
            "            <th style=\"border: 1px solid black;\" width=\"15%\">Results</th>\n" +
            "        </tr>\n" +
            "    </thead>\n" +
            "    <tbody>";
        unsigned iter{0};
        size_t   entriesTable = mainwindow->selectedInfo.entriesNumber;
        for (; iter < 10 && iter < entriesTable; ++iter) {
            if (!vectorCheckNumber[iter]->checkState()) {
                continue;
            }
            QString SN         = vectorSerialNumber[iter]->text();
            QString startFirst = vectorFirstIndexStart[iter]->text() + "&nbsp;";
            QString stopFirst  = vectorFirstIndexStop[iter]->text() + "&nbsp;";
            QString registerVolumeDoubleFirst =
                QString::number((vectorFirstIndexStop[iter]->text().toDouble() -
                                 vectorFirstIndexStart[iter]->text().toDouble()));
            QString errorFirst = vectorFirstError[iter]->text() + "&nbsp;";
            QString realVolumeFirst =
                QString(precision_4(ui->leVolume1->text().toDouble()).c_str()) +
                "&nbsp;";
            if (vectorFirstIndexStart[iter]->text() == "" || vectorFirstIndexStop[iter]->text() == "") {
                registerVolumeDoubleFirst = "";
            }
            QString startSecond = vectorSecondIndexStart[iter]->text() + "&nbsp;";
            QString stopSecond  = vectorSecondIndexStop[iter]->text() + "&nbsp;";
            QString registerVolumeDoubleSecond =
                QString::number((vectorSecondIndexStop[iter]->text().toDouble() -
                                 vectorSecondIndexStart[iter]->text().toDouble()));
            QString errorSecond = vectorSecondError[iter]->text() + "&nbsp;";
            QString realVolumeSecond =
                QString(precision_4(ui->leVolume2->text().toDouble()).c_str()) +
                "&nbsp;";
            if (vectorSecondIndexStart[iter]->text() == "" || vectorSecondIndexStop[iter]->text() == "") {
                registerVolumeDoubleSecond = "";
            }
            QString startThird = vectorThirdIndexStart[iter]->text() + "&nbsp;";
            QString stopThird  = vectorThirdIndexStop[iter]->text() + "&nbsp;";
            QString registerVolumeDoubleThird =
                QString::number((vectorThirdIndexStop[iter]->text().toDouble() -
                                 vectorThirdIndexStart[iter]->text().toDouble()));
            QString errorThird = vectorThirdError[iter]->text() + "&nbsp;";
            QString realVolumeThird =
                QString(precision_4(ui->leVolume3->text().toDouble()).c_str()) +
                "&nbsp;";
            if (vectorThirdIndexStart[iter]->text() == "" || vectorThirdIndexStop[iter]->text() == "") {
                registerVolumeDoubleThird = "";
            }
            if (XOR(startFirst.isEmpty(), stopFirst.isEmpty()) ||
                XOR(startSecond.isEmpty(), stopSecond.isEmpty()) ||
                XOR(startThird.isEmpty(), stopThird.isEmpty()) ||
                SN.isEmpty()) {
                continue;
            }
            ++totalEntries;
            QString resultTests{"PASSED"};
            try {
                bool bFirst =
                    std::abs(std::stod(errorFirst.toStdString().c_str())) <
                    maximumWaterMeterError;
                bool bSecond =
                    std::abs(std::stod(errorFirst.toStdString().c_str())) <
                    nominalWaterMeterError;
                bool bThird =
                    std::abs(std::stod(errorFirst.toStdString().c_str())) <
                    nominalWaterMeterError;
                resultTests =
                    (bFirst && bSecond && bThird ? "PASSED" : "FAILED");
            } catch (...) {
                resultTests = "FAILED";
            }
            resultAllTests[count++] = resultTests;
            double minimumFlowRate  = ui->leFlowRateMinumum->text().toDouble();
            double trasitionFlowRate =
                ui->leFlowRateTransitoriu->text().toDouble();
            double nominalFlowRate = ui->leFlowRateNominal->text().toDouble();
            report +=
                QString("    <tr>") +
                "        <th style=\"text-align: left; border: 1px solid black;\" rowspan=\"3\"><br>&nbsp;" + SN + "</th>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(minimumFlowRate) + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startFirst + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopFirst + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleFirst + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeFirst + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorFirst + "</td>" +
                "        <th style=\"text-align: center; border: 1px solid black;\" rowspan=\"3\">" + resultTests + "</th>" +
                "    </tr>" +
                "    <tr>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(trasitionFlowRate) + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startSecond + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopSecond + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleSecond + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeSecond + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorSecond + "</td>" +
                "    </tr>" +
                "    <tr>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(nominalFlowRate) + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startThird + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopThird + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + registerVolumeDoubleThird + "&nbsp;</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeThird + "</td>" +
                "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorThird + "</td>" +
                "    </tr>";
        };
        report += QString("</tbody>") + "</table>";
        // Part two
        if (iter < entriesTable) {
            bool header{true};
            for (unsigned iter = 10; iter < entriesTable; ++iter) {
                if (totalEntries == 10 && header) {
                    report += "<br><br><br><br><br><br><br><br><br><br>";
                    report +=
                        QString("<table style=\"border: 1px solid black; border-collapse: collapse; border-spacing: 0; width: 100%;\">\n") +
                        "    <caption>Test Results:</caption>\n" +
                        "    <thead>\n" +
                        "        <tr>\n" +
                        "            <th style=\"border: 1px solid black;\" width=\"15%\">Series (Type)</th>\n" +
                        "            <th style=\"border: 1px solid black;\" width=\"9%\">&nbsp;Flow&nbsp;&nbsp;[L/h]</th>\n" +
                        "            <th style=\"border: 1px solid black;\" width=\"14%\">Start Index [L]</th>\n" +
                        "            <th style=\"border: 1px solid black;\" width=\"14%\">Stop Index [L]</th>\n" +
                        "            <th style=\"border: 1px solid black;\" width=\"14%\">Meter Volume [L]</th>\n" +
                        "            <th style=\"border: 1px solid black;\" width=\"14%\">Reference Volume [L]</th>\n" +
                        "            <th style=\"border: 1px solid black;\" width=\"9%\">Error [%]</th>\n" +
                        "            <th style=\"border: 1px solid black;\" width=\"15%\">Results</th>\n" +
                        "        </tr>\n" +
                        "    </thead>\n" +
                        "    <tbody>";
                    header = false;
                }
                if (!vectorCheckNumber[iter]->checkState()) {
                    continue;
                }
                QString SN         = vectorSerialNumber[iter]->text();
                QString startFirst = vectorFirstIndexStart[iter]->text() +
                                     "&nbsp;";
                QString stopFirst = vectorFirstIndexStop[iter]->text() +
                                    "&nbsp;";
                double registerVolumeDoubleFirst =
                    (vectorFirstIndexStop[iter]->text().toDouble() -
                     vectorFirstIndexStart[iter]->text().toDouble());
                QString errorFirst = vectorFirstError[iter]->text() +
                                     "&nbsp;";
                QString realVolumeFirst =
                    QString(precision_4(ui->leVolume1->text().toDouble()).c_str()) +
                    "&nbsp;";
                QString startSecond = vectorSecondIndexStart[iter]->text() +
                                      "&nbsp;";
                QString stopSecond = vectorSecondIndexStop[iter]->text() +
                                     "&nbsp;";
                double registerVolumeDoubleSecond =
                    (vectorSecondIndexStop[iter]->text().toDouble() -
                     vectorSecondIndexStart[iter]->text().toDouble());
                QString errorSecond = vectorSecondError[iter]->text() +
                                      "&nbsp;";
                QString realVolumeSecond =
                    QString(precision_4(ui->leVolume2->text().toDouble()).c_str()) +
                    "&nbsp;";
                ;
                QString startThird = vectorThirdIndexStart[iter]->text() +
                                     "&nbsp;";
                QString stopThird = vectorThirdIndexStop[iter]->text() +
                                    "&nbsp;";
                double registerVolumeDoubleThird =
                    (vectorThirdIndexStop[iter]->text().toDouble() -
                     vectorThirdIndexStart[iter]->text().toDouble());
                QString errorThird = vectorThirdError[iter]->text() +
                                     "&nbsp;";
                QString realVolumeThird =
                    QString(precision_4(ui->leVolume3->text().toDouble()).c_str()) +
                    "&nbsp;";
                if (XOR(startFirst.isEmpty(), stopFirst.isEmpty()) ||
                    XOR(startSecond.isEmpty(), stopSecond.isEmpty()) ||
                    XOR(startThird.isEmpty(), stopThird.isEmpty()) ||
                    SN.isEmpty()) {
                    continue;
                }
                ++totalEntries;
                QString resultTests{"PASSED"};
                try {
                    bool bFirst =
                        std::abs(std::stod(errorFirst.toStdString().c_str())) <
                        maximumWaterMeterError;
                    bool bSecond =
                        std::abs(std::stod(errorFirst.toStdString().c_str())) <
                        nominalWaterMeterError;
                    bool bThird =
                        std::abs(std::stod(errorFirst.toStdString().c_str())) <
                        nominalWaterMeterError;
                    resultTests =
                        (bFirst && bSecond && bThird ? "PASSED" : "FAILED");
                } catch (...) {
                    resultTests = "FAILED";
                }
                resultAllTests[count++] = resultTests;
                double minimumFlowRate  = ui->leFlowRateMinumum->text().toDouble();
                double trasitionFlowRate =
                    ui->leFlowRateTransitoriu->text().toDouble();
                double nominalFlowRate = ui->leFlowRateNominal->text().toDouble();
                report +=
                    QString("    <tr>") +
                    "        <th style=\"text-align: left; border: 1px solid black;\" rowspan=\"3\"><br>&nbsp;" + SN + "</th>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(minimumFlowRate) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startFirst + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopFirst + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(registerVolumeDoubleFirst) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeFirst + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorFirst + "</td>" +
                    "        <th style=\"text-align: center; border: 1px solid black;\" rowspan=\"3\">" + resultTests + "</th>" +
                    "    </tr>" +
                    "    <tr>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(trasitionFlowRate) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startSecond + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopSecond + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(registerVolumeDoubleSecond) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeSecond + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorSecond + "</td>" +
                    "    </tr>" +
                    "    <tr>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(nominalFlowRate) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + startThird + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + stopThird + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + QString::number(registerVolumeDoubleThird) + "&nbsp;</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + realVolumeThird + "</td>" +
                    "        <td style=\"text-align: right; border: 1px solid black; padding-right: 5px;\">" + errorThird + "</td>" +
                    "    </tr>";
            };
            report += QString("</tbody>") + "</table>";
        }
        report += QString("<br><pre><h3>") +
                  "  Metrological Verifier                   Technical Responsible<br><br>" +
                  "  Name ________________________           Name _______________________<br>" +
                  "<br>" +
                  "  Signature ___________________           Signature __________________<br>" +
                  "</h3></pre>";

        ui->pbPrint->setEnabled(false);
        QTimerGenerareFM->start(2000);

        std::thread pdfThread(printPdfThread, report);
        pdfThread.detach();
    }
}

/**
 * \brief Overridden function called when the dialog is shown.
 *
 * This function is automatically called when the dialog is shown. It ensures
 * that the table is populated with data when the dialog is displayed.
 *
 * \param event A QShowEvent object.
 */
void TableBoard::showEvent(QShowEvent* event) {
    Q_UNUSED(event);

    // Populate the table with data when the dialog is shown
    PopulateTable();
}

/**
 * \brief Populates the table with data based on selected information from the main window.
 *
 * This function updates the UI elements in the dialog to reflect the selected water meter
 * information from the main window. It adjusts visibility, sets palettes for rows, and updates
 * text fields with relevant data.
 *
 * It also initializes and sets palettes for alternating row colors to improve readability.
 *
 * This function assumes that the necessary data (entries, nameWaterMeter, minimumFlowMain,
 * transitoriuFlowMain, nominalFlowMain, nominalError, maximumError) have already been set
 * in the main window (mainwindow->selectedInfo).
 */
void TableBoard::PopulateTable() {
    Translate(); // Update UI with translated strings if necessary

    // Retrieve data from main window
    entries             = mainwindow->selectedInfo.entriesNumber;
    nameWaterMeter      = mainwindow->selectedInfo.nameWaterMeter;
    minimumFlowMain     = mainwindow->selectedInfo.minimumFlow;
    transitoriuFlowMain = mainwindow->selectedInfo.transitionFlow; // Typo corrected to transitoriuFlowMain
    nominalFlowMain     = mainwindow->selectedInfo.nominalFlow;
    nominalError        = mainwindow->selectedInfo.nominalError;
    maximumError        = mainwindow->selectedInfo.maximumError;

    // Define palettes for row colors
    QPalette paletteOddRow, paletteEvenRow, paletteOddRowErr, paletteEvenRowErr;

    // Lambda function to initialize palette with given RGB values
    auto initializePalette = [](QPalette& palette, int r, int g, int b, int a = 255) {
        palette.setColor(QPalette::Base, QColor(r, g, b, a));
    };

    // Initialize palettes for odd and even rows with their respective colors
    initializePalette(paletteOddRow, 240, 255, 240);
    initializePalette(paletteEvenRow, 255, 255, 255);
    initializePalette(paletteOddRowErr, 220, 235, 220);
    initializePalette(paletteEvenRowErr, 235, 235, 235);

    // Iterate through the vectors to show/hide and set properties based on number of entries
    for (unsigned iter = 0; iter < MAX_ENTRIES; ++iter) {
        if (iter < entries) {
            // Show widgets for valid entries
            vectorNumber[iter]->show();
            vectorCheckNumber[iter]->show();
            vectorCheckNumber[iter]->setCheckState(Qt::Checked);
            vectorSerialNumber[iter]->show();
            vectorFirstIndexStart[iter]->show();
            vectorFirstIndexStop[iter]->show();
            vectorFirstError[iter]->show();
            vectorSecondIndexStart[iter]->show();
            vectorSecondIndexStop[iter]->show();
            vectorSecondError[iter]->show();
            vectorThirdIndexStart[iter]->show();
            vectorThirdIndexStop[iter]->show();
            vectorThirdError[iter]->show();

            // Determine row palette based on even or odd row index
            auto rowPalette    = (iter % 4 == 0 || iter % 4 == 1) ? paletteOddRow : paletteEvenRow;
            auto rowErrPalette = (iter % 4 == 0 || iter % 4 == 1) ? paletteOddRowErr : paletteEvenRowErr;

            // Apply palettes to widgets for this row
            vectorNumber[iter]->setPalette(rowPalette);
            vectorCheckNumber[iter]->setPalette(rowPalette);
            vectorSerialNumber[iter]->setPalette(rowPalette);
            vectorFirstIndexStart[iter]->setPalette(rowPalette);
            vectorFirstIndexStop[iter]->setPalette(rowPalette);
            vectorFirstError[iter]->setPalette(rowErrPalette);
            vectorSecondIndexStart[iter]->setPalette(rowPalette);
            vectorSecondIndexStop[iter]->setPalette(rowPalette);
            vectorSecondError[iter]->setPalette(rowErrPalette);
            vectorThirdIndexStart[iter]->setPalette(rowPalette);
            vectorThirdIndexStop[iter]->setPalette(rowPalette);
            vectorThirdError[iter]->setPalette(rowErrPalette);
        } else {
            // Hide widgets for entries that exceed the current number of entries
            vectorNumber[iter]->hide();
            vectorCheckNumber[iter]->hide();
            vectorCheckNumber[iter]->setCheckState(Qt::Unchecked);
            vectorSerialNumber[iter]->hide();
            vectorFirstIndexStart[iter]->hide();
            vectorFirstIndexStop[iter]->hide();
            vectorFirstError[iter]->hide();
            vectorSecondIndexStart[iter]->hide();
            vectorSecondIndexStop[iter]->hide();
            vectorSecondError[iter]->hide();
            vectorThirdIndexStart[iter]->hide();
            vectorThirdIndexStop[iter]->hide();
            vectorThirdError[iter]->hide();
        }
    }

    // Update labels with measurement indices and errors
    ui->lbIndex1->setText(QString(tr("Index [L] -  Qmin: %1  [L/h]  Eroare: %2 %")).arg(QString::number(minimumFlowMain), QString::number(maximumError)));
    ui->lbIndex2->setText(QString(tr("Index [L] -  Qt:  %1  [L/h]  Eroare: %2 %")).arg(QString::number(transitoriuFlowMain), QString::number(nominalError)));
    ui->lbIndex3->setText(QString(tr("Index [L] -  Qn: %1  [L/h]  Eroare: %2 %")).arg(QString::number(nominalFlowMain), QString::number(nominalError)));

    // Update line edits with flow rate values
    ui->leFlowRateMinumum->setText(QString::number(minimumFlowMain));
    ui->leFlowRateTransitoriu->setText(QString::number(transitoriuFlowMain));
    ui->leFlowRateNominal->setText(QString::number(nominalFlowMain));
}

/**
 * \brief Custom logic executed when the dialog gains focus.
 *
 * This function overrides the default behavior when the dialog gains focus.
 * It currently performs no additional actions beyond the base class implementation.
 *
 * \param event The focus event.
 */
void TableBoard::focusInEvent(QFocusEvent* event) {
    // Your custom logic when the dialog gains focus
    QDialog::focusInEvent(event);
}

/**
 * \brief Custom logic executed when the dialog loses focus.
 *
 * This function overrides the default behavior when the dialog loses focus.
 * It currently performs no additional actions beyond the base class implementation.
 *
 * \param event The focus event.
 */
void TableBoard::focusOutEvent(QFocusEvent* event) {
    // Your custom logic when the dialog loses focus
    QDialog::focusOutEvent(event);
}

/**
 * \brief Copies text between widgets based on specified regex patterns.
 *
 * This function finds QLineEdit widgets matching the start and stop regex patterns
 * among the children of this dialog. It copies text from start widgets to
 * corresponding stop widgets up to the minimum of their sizes.
 *
 * \param startRegex Regular expression pattern to match start widgets.
 * \param stopRegex Regular expression pattern to match stop widgets.
 */
void TableBoard::copyTextBetweenWidgets(const QString& startRegex, const QString& stopRegex) {
    QList<QLineEdit*> startWidgets = findChildren<QLineEdit*>(QRegularExpression(startRegex));
    QList<QLineEdit*> stopWidgets  = findChildren<QLineEdit*>(QRegularExpression(stopRegex));

    for (int i = 0; i < qMin(startWidgets.size(), stopWidgets.size()); ++i) {
        startWidgets[i]->setText(stopWidgets[i]->text());
    }
}

/**
 * \brief Slot triggered when the "Copy 1-2" button is clicked.
 *
 * This function copies text from widgets matching the start and stop patterns
 * for groups 2 to 1.
 */
void TableBoard::onCopy12Clicked() {
    copyTextBetweenWidgets("leStart2_\\d+", "leStop1_\\d+");
    ui->leStop2_1->setFocus();
}

/**
 * \brief Slot triggered when the "Copy 2-3" button is clicked.
 *
 * This function copies text from widgets matching the start and stop patterns
 * for groups 3 to 2.
 */
void TableBoard::onCopy23Clicked() {
    copyTextBetweenWidgets("leStart3_\\d+", "leStop2_\\d+");
    ui->leStop3_1->setFocus();
}

/**
 * \brief Slot triggered when the "Report PDF" button is clicked.
 *
 * This function first calculates data (if necessary) and then shows the report measurements dialog.
 * If the dialog does not exist, it creates a new instance of ReportMeasurements.
 */
void TableBoard::onReportClicked() {
    onCalculateClicked();

    if (reportMeasurementsDialog) {
        delete reportMeasurementsDialog;
        reportMeasurementsDialog = nullptr;
    }

    if (!reportMeasurementsDialog) {
        reportMeasurementsDialog = new ReportMeasurements(this, vectorCheckNumber, vectorSerialNumber, resultAllTests);
    }

    if (reportMeasurementsDialog) {
        reportMeasurementsDialog->show();
    }
}

/**
 * \brief Slot triggered to enable the "Print PDF" button.
 *
 * This function stops the QTimerGenerareFM timer and enables the "Print PDF" button.
 */
void TableBoard::enableGenerareFmButton() {
    // Stop the timer
    QTimerGenerareFM->stop();

    // Re-enable the button
    ui->pbPrint->setEnabled(true);
}
