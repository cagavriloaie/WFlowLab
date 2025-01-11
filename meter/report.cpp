/**
 * \file report.cpp
 * \brief Implementation file for the ReportMeasurements class.
 *
 * This file contains the implementation of methods for the ReportMeasurements class,
 * which is responsible for generating and handling reports related to measurements.
 *
 * \author Constantin
 * \date Insert creation date
 */

#include <algorithm> // Standard C++ algorithms
#include <chrono>    // C++11 time utilities
#include <ctime>     // C time utilities
#include <iomanip>   // I/O manipulators
#include <iostream>  // Standard I/O streams
#include <mutex>     // C++11 mutual exclusion primitives
#include <sstream>   // String stream operations
#include <string>    // String utilities
#include <thread>    // C++11 thread support

#include <QCheckBox>        // Qt checkbox widget
#include <QCoreApplication> // Qt core application handling
#include <QDateTime>        // Qt date and time handling
#include <QDesktopServices> // Qt desktop services
#include <QDialog>          // Qt dialog window
#include <QDoubleValidator> // Qt validator for double values
#include <QFileDialog>      // Qt file dialog
#include <QKeyEvent>        // Qt key event handling
#include <QLabel>           // Qt label widget
#include <QLineEdit>        // Qt line edit widget
#include <QMainWindow>      // Qt main window
#include <QMessageBox>      // Qt message box for alerts
#include <QPageSize>        // Qt page size
#include <QPainter>         // Qt painter for drawing
#include <QPrintDialog>     // Qt print dialog
#include <QPrinter>         // Qt printer support
#include <QSettings>        // Qt application settings
#include <QString>          // Qt string class
#include <QTimer>           // Qt timer for periodic events
#include <QValidator>       // Qt validator base class

#include "mainwindow.h"    // Your application's main window
#include "report.h"        // Header for report functionality
#include "ui_mainwindow.h" // UI definition for main window
#include "ui_report.h"     // UI definition for report dialog

/**
 * \extern MainWindow *pMainWindow
 * \brief Pointer to the main window instance.
 *
 * This global variable holds a pointer to the main window instance,
 * allowing access to its properties and methods from various parts of the application.
 */
extern MainWindow* pMainWindow;

/**
 * \extern std::mutex printReportPdfThreadMutex
 * \brief Mutex for thread-safe PDF printing.
 *
 * This global mutex ensures thread safety when printing PDF documents from multiple threads.
 * It protects critical sections where file paths are manipulated and directories are created.
 */
std::mutex printReportPdfThreadMutex;

/**
 * \brief Generates a PDF document from HTML content and opens it using the default PDF viewer.
 *
 * This function generates a PDF document from the provided HTML report content. It ensures
 * thread safety when accessing shared resources using a mutex. After generating the PDF,
 * it checks for errors and opens the generated PDF file using the default PDF viewer.
 *
 * \param report The HTML content to be printed into the PDF.
 */
void ReportMeasurements::printPdfThread(QString report) {
    // Generate a unique timestamp for the file name
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

    // Construct the file name using QDir
    QString fileName = QString::fromStdString(pMainWindow->selectedInfo.pathResults) +
                       QDir::separator() + QString("BV_") + timestamp + ".pdf";

    {
        // Lock the mutex to ensure exclusive access to the shared resource
        std::lock_guard<std::mutex> lock(printReportPdfThreadMutex);

        // Check if the directory exists, and create it if not
        QDir resultDir(QString::fromStdString(pMainWindow->selectedInfo.pathResults));
        resultDir.mkpath(".");
    }

    // Initialize the printer
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setFullPage(true);
    qreal margin = 5.0;
    printer.setPageMargins(QMarginsF(margin, margin, margin, margin), QPageLayout::Millimeter);

    // Initialize QTextDocument with the provided HTML report
    QTextDocument outputReport;
    outputReport.setHtml(report);
    outputReport.setDocumentMargin(0);

    // Check if the PDF generation is successful
    if (outputReport.isEmpty() || !printer.isValid()) {
        qDebug() << "Error: Empty document or invalid printer, PDF not generated.";
        return;
    }

    // Print the document to the PDF file
    outputReport.print(&printer);

    // Check if the file was created successfully and is non-empty
    QFile outputFile(fileName);
    if (!outputFile.exists() || outputFile.size() == 0) {
        qDebug() << "Error: Failed to generate a non-empty PDF file.";
        return;
    }

    // Convert the file path to a URL and open it in the default PDF viewer
    QString fileUrl = QUrl::fromLocalFile(fileName).toString();
    QDesktopServices::openUrl(QUrl(fileUrl));
}

/**
 * \brief Converts an integer number into its Romanian words representation.
 *
 * This function converts a given integer number into its equivalent words in Romanian.
 * It handles numbers from -999,999 to 999,999.
 *
 * \param num The integer number to convert.
 * \param addSuffix Flag indicating whether to add suffixes like "mii", "milion", etc.
 *                  Default is false.
 * \return A string containing the Romanian words representation of the number.
 */
std::string convertNumberToWords(int num, bool addSuffix = false) {
    static const std::string units[] =
        {
            "",      ///< 0
            "un",    ///< 1
            "doua",  ///< 2
            "trei",  ///< 3
            "patru", ///< 4
            "cinci", ///< 5
            "sase",  ///< 6
            "sapte", ///< 7
            "opt",   ///< 8
            "noua"   ///< 9
        };
    static const std::string teens[] =
        {
            "",              ///< 0
            "unsprezece",    ///< 11
            "doisprezece",   ///< 12
            "treisprezece",  ///< 13
            "paisprezece",   ///< 14
            "cincisprezece", ///< 15
            "saisprezece",   ///< 16
            "saptesprezece", ///< 17
            "optisprezece",  ///< 18
            "nouasprezece"   ///< 19
        };
    static const std::string tens[] =
        {
            "",          ///< 0
            "",          ///< 1
            "douazeci",  ///< 20
            "treizeci",  ///< 30
            "patruzeci", ///< 40
            "cincizeci", ///< 50
            "saizeci",   ///< 60
            "saptezeci", ///< 70
            "optzeci",   ///< 80
            "nouazeci"   ///< 90
        };

    std::string result;

    // Handle zero case
    if (num == 0) {
        return (addSuffix) ? "zero" : "";
    }

    // Handle negative numbers
    if (num < 0) {
        result += "minus ";
        num = -num; // Make num positive for further processing
    }

    // Handle millions part
    if (num >= 1000000) {
        result += convertNumberToWords(num / 1000000, true);
        result += (num / 1000000 == 1) ? " milion " : " milioane ";
        num %= 1000000;
    }

    // Handle thousands part
    if (num >= 1000) {
        if (num >= 2000) {
            result += convertNumberToWords(num / 1000, true);
        } else {
            result += "o mie ";
        }
        num %= 1000;
    }

    // Handle hundreds part
    if (num >= 100) {
        if (num >= 200) {
            result += " " + convertNumberToWords(num / 100, true) + " sute ";
        } else {
            result += "o suta ";
        }
        num %= 100;
    }

    // Handle teens (11-19)
    if (num >= 11 && num <= 19) {
        result += teens[num - 11] + " ";
    }
    // Handle tens (20, 30, ..., 90)
    else if (num >= 20 || num == 10) {
        result += tens[num / 10] + " ";
        num %= 10;
    }

    // Handle units (1-9)
    if (num >= 1 && num <= 9) {
        result += units[num];
    }

    return result;
}

/**
 * \brief Translates UI elements and sets localized text for the ReportMeasurements dialog.
 *
 * This function translates various UI elements and sets localized text using the
 * current application's translation system. It is typically called during initialization
 * or when the language/locale is changed to ensure the UI reflects the selected language.
 *
 * Translated elements include window title, group box title, labels, combo box items,
 * and push button texts.
 *
 * Example usage:
 * \code
 * ReportMeasurements report;
 * report.Translate();
 * \endcode
 */
void ReportMeasurements::Translate() {
    this->setWindowTitle(tr("WFlowLab - Informatii buletin verificare metrologica"));
    ui->grBoxBuletin->setTitle(tr("Date verificare metrologica"));
    ui->lbAutorizatiaNumarul->setText(tr("Autorizatia numarul:"));
    ui->lbNumarInregistrare->setText(tr("Numar de inregistrare: "));
    ui->lbBeneficiar->setText(tr("Beneficiar: "));
    ui->lbCodulDinLt->setText(tr("Codul din LT: "));
    ui->lbNormativ->setText(tr("Normativ: "));
    ui->lbValabilitate->setText(tr("Valabilitate: "));
    ui->lbCost->setText(tr("Cost: "));
    ui->lbVerificatorMetrolog->setText(tr("Verificator metrolog: "));
    ui->lbLoculEfectuariiVerificarii->setText(tr("Locul efectuarii verificarii:"));
    ui->cbValabilitate->addItem(tr("6 luni"));
    ui->cbValabilitate->addItem(tr("1 an"));
    ui->cbValabilitate->addItem(tr("2 ani"));
    ui->cbValabilitate->addItem(tr("3"));
    ui->cbValabilitate->addItem(tr("5 ani"));
    ui->pbGenerareBV->setText(tr("&Generare BV"));
    ui->pbInchide->setText(tr("&Inchide"));
}

/**
 * \brief Constructor for the ReportMeasurements class.
 *
 * Initializes the ReportMeasurements dialog with the provided parent widget,
 * sets up the user interface, copies arrays, and initializes timer and connections.
 *
 * \param parent Parent widget to which this dialog belongs.
 * \param vectorCheckNumber Vector of QCheckBox pointers used for storing check numbers.
 * \param vectorSerialNumber Vector of QLineEdit pointers used for storing serial numbers.
 * \param resultAllTests Array of QString containing results of all tests.
 */
ReportMeasurements::ReportMeasurements(QWidget*                       parent,
                                       const std::vector<QCheckBox*>& vectorCheckNumber,
                                       const std::vector<QLineEdit*>& vectorSerialNumber,
                                       const QString                  resultAllTests[20])
    : QDialog(parent),
      ui(new Ui::report),
      vectorCheckNumberCopy(vectorCheckNumber),
      vectorSerialNumberCopy(vectorSerialNumber) {
    // Set up the UI
    ui->setupUi(this);

    // Set window flags
    setWindowFlags(Qt::Window);

    // Initialize QTimer for generating BV
    QTimerGenerareBv = new QTimer(this);

    // Copy resultsAllTests array
    for (size_t iter = 0; iter < MAX_ARRAY_SIZE; ++iter) {
        resultAllTestsCopy[iter] = resultAllTests[iter];
    }

    // Set window title
    setWindowTitle(tr("WFlowLab - Informatii buletin de verificare metrologica"));

    // Set labels and options for the UI elements
    ui->grBoxBuletin->setTitle(tr("Date verificare metrologica"));
    ui->lbAutorizatiaNumarul->setText(tr("Autorizatia numarul:"));
    ui->lbNumarInregistrare->setText(tr("Numar de inregistrare:"));
    ui->lbBeneficiar->setText(tr("Beneficiar:"));
    ui->lbCodulDinLt->setText(tr("Codul din LT:"));
    ui->lbNormativ->setText(tr("Normativ:"));
    ui->lbValabilitate->setText(tr("Valabilitate:"));
    ui->lbCost->setText(tr("Cost:"));
    ui->lbVerificatorMetrolog->setText(tr("Verificator metrolog:"));
    ui->lbLoculEfectuariiVerificarii->setText(tr("Locul efectuarii verificarii:"));
    ui->cbValabilitate->addItem(tr("1 an"));
    ui->cbValabilitate->addItem(tr("2 ani"));
    ui->cbValabilitate->addItem(tr("3 ani"));
    ui->cbValabilitate->addItem(tr("4 ani"));
    ui->cbValabilitate->addItem(tr("5 ani"));
    ui->cbValabilitate->addItem(tr("6 ani"));
    ui->cbValabilitate->addItem(tr("7 ani"));
    ui->cbValabilitate->addItem(tr("8 ani"));
    ui->cbValabilitate->addItem(tr("9 ani"));
    ui->cbValabilitate->addItem(tr("10 ani"));
    ui->pbGenerareBV->setText(tr("&Generare BV"));
    ui->pbInchide->setText(tr("&Inchide"));

    // Set up validators
    QDoubleValidator* validatorDoubleNumber = new QDoubleValidator(this);
    ui->leCost->setValidator(validatorDoubleNumber);

    // Load settings from QSettings
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");

    ui->leAutorizatiaNumarul->setText(settings.value("autorizatiaNumarul", "1050/2024").toString());
    ui->leNumarInregistrare->setText(settings.value("numarInregistrare", 1).toString());
    ui->leBeneficiar->setText(settings.value("beneficiar", "Termo Util").toString());
    ui->leCoduldinLt->setText(settings.value("codulDinLt", "1.06.28.1.1").toString());
    ui->leNormativ->setText(settings.value("normativ", "NML").toString());
    ui->cbValabilitate->setCurrentIndex(settings.value("valabilitate", 6).toInt());
    ui->leCost->setText(settings.value("cost", 100).toString());
    ui->leVerificatorMetrolog->setText(settings.value("verificatorMetrolog", "Adrian Pintilie").toString());
    ui->leLoculEfectuariiVerificarii->setText(settings.value("loculEfectuariiVerificarii", "Str. Morilor nr 8, Pascani").toString());

    settings.endGroup();
    settings.sync();
    ui->lbNumarInregistrare->setFocus();

    // Connect signals and slots
    connect(ui->pbInchide, &QPushButton::clicked, this, &ReportMeasurements::onCloseClicked);
    connect(ui->pbGenerareBV, &QPushButton::clicked, this, &ReportMeasurements::onPrintClicked);
    connect(QTimerGenerareBv, &QTimer::timeout, this, &ReportMeasurements::enableGenerareBvButton);
}

/**
 * \brief Destructor for the ReportMeasurements class.
 *
 * Cleans up the user interface (ui) resources.
 */
ReportMeasurements::~ReportMeasurements() {
    delete ui;
}

/**
 * \brief Slot triggered when the "Generate BV" button is clicked.
 *
 * Collects data from line edits, validates input, and generates a verification report in PDF format.
 * Displays error message if any required field is empty.
 */
void ReportMeasurements::onPrintClicked() {
    // Collect line edits in a vector
    std::vector<QLineEdit*> lineEdits = {
        ui->leAutorizatiaNumarul,
        ui->leNumarInregistrare,
        ui->leBeneficiar,
        ui->leCoduldinLt,
        ui->leNormativ,
        ui->leCost,
        ui->leVerificatorMetrolog,
        ui->leLoculEfectuariiVerificarii};

    // Check if any field is empty
    bool anyFieldEmpty = std::any_of(lineEdits.begin(), lineEdits.end(), [](const QLineEdit* lineEdit) {
        return lineEdit->text().isEmpty();
    });

    if (anyFieldEmpty) {
        QMessageBox messageBoxWindowsTitle;
        messageBoxWindowsTitle.setWindowTitle(tr("Verification report"));
        messageBoxWindowsTitle.setText(tr("There are unfilled fields!"));
        messageBoxWindowsTitle.setStandardButtons(QMessageBox::Ok);
        messageBoxWindowsTitle.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        if (messageBoxWindowsTitle.exec() == QMessageBox::Ok) {
            messageBoxWindowsTitle.close();
        }
        return;
    }

    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t to a tm structure
    std::tm* localTime = std::localtime(&currentTime);

    // Other variables
    size_t entriesTable = pMainWindow->selectedInfo.entriesNumber;

    QString ltCode                = ui->leCoduldinLt->text();
    QString nmlNtmNorms           = ui->leNormativ->text();
    QString checkValability       = ui->cbValabilitate->currentText();
    QString costRon               = ui->leCost->text();
    QString companyLaboratory     = QString::fromStdString(pMainWindow->optionsConfiguration["company"]);
    QString autorizationNumarul   = ui->leAutorizatiaNumarul->text();
    QString certiticateLaboratory = QString::fromStdString(pMainWindow->optionsConfiguration["certificate"]);
    QString detinator             = ui->leBeneficiar->text();
    QString meterType             = pMainWindow->ui->cbWaterMeterType->currentText();

    std::stringstream htmlTable;

    // Start building the HTML string
    htmlTable << "<html>\n"
              << "<head>\n"
              << "  <title>Buletin de verificare metrologica</title>\n"
              << "  <meta charset=\"UTF-8\">\n"
              << "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
              << "  <style>\n"
              << "    p { font-size: 18px; }\n"
              << "    table.first {\n"
              << "      border-collapse: collapse;\n"
              << "      width: 100%;\n"
              << "      font-size: 8px;\n"
              << "      table-layout: fixed;\n" // Ensures equal width allocation
              << "    }\n"
              << "    th, td {\n"
              << "      border: 1px solid #dddddd;\n"
              << "      text-align: center;\n"
              << "      padding: 4px;\n"
              << "      margin: 0;\n"
              << "      word-wrap: break-word;\n"
              << "    }\n"
              << "    th {\n"
              << "      background-color: #f2f2f2;\n"
              << "    }\n"
              << "    tbody {\n"
              << "      background-color: #f0f0f0;\n"
              << "    }\n"
              << "    th.smaller-column {\n"
              << "      width: 50px;\n"
              << "    }\n"
              << "    th:nth-child(2), td:nth-child(2) {\n"
              << "      width: 30%;\n" // More balanced size for description column
              << "    }\n"
              << "    th:nth-child(5), td:nth-child(5) {\n"
              << "      width: 35%;\n" // Increased width for column 5
              << "      word-break: break-word;\n"
              << "    }\n"
              << "  </style>\n"
              << "</head>\n"
              << "<body>\n"
              << "  <p style=\"font-size: 10px; line-height: 0.6;\">Laboratorul de metrologie al " << companyLaboratory.toStdString() << "</p>\n"
              << "  <p style=\"font-size: 10px; line-height: 0.6;\">Autorizatia nr. " << autorizationNumarul.toStdString() << "</p>\n"
              << "  <center>\n"
              << "    <p style=\"font-size: 13px; line-height: 0.6;\">Buletin de verificare metrologica</p>\n"
              << "    <p style=\"font-size: 13px; line-height: 0.6;\">nr. " << ui->leNumarInregistrare->text().toStdString() << " data emiterii: "
              << std::put_time(localTime, "%d-%m-%Y") << " ora: " << std::put_time(localTime, "%H:%M") << "<br>\n"
              << "  </center>\n"
              << "  <p style=\"font-size: 10px; text-align:left;\">Mijloacele de masurare apartinand "
              << detinator.toStdString() << ", prezentate la verificare metrologica, au obtinut urmatoarele rezultate:</p>\n"
              << "<center>\n"
              << "  <table class=\"first\">\n"
              << "    <thead>\n"
              << "      <tr>\n"
              << "        <th>Nr. <br>buc.</th>\n"
              << "        <th>Mijloc de masurare-denumire, <br>tip, producator, caracteristici, <br>seria/an de fabricatie</th>\n"
              << "        <th>Codul din LT</th>\n"
              << "        <th>Normativ<br>(NML, NTM etc)</th>\n"
              << "        <th>Etaloane utilizate,<br>denumire, serie, nr. CE</th>\n"
              << "        <th>Rezultatul<br>verificarii</th>\n"
              << "        <th>Valabilitatea<br>verificarii</th>\n"
              << "        <th>Cost</th>\n"
              << "      </tr>\n"
              << "    </thead>\n"
              << "    <tbody>\n";

    size_t entriesTableUsed{0};

    for (size_t row = 0; row < entriesTable; ++row) {
        if (!vectorCheckNumberCopy[row]->checkState()) {
            continue;
        }

        ++entriesTableUsed;
        QString resultEntry = resultAllTestsCopy[row];

        htmlTable << "      <tr style=\"height: 20px;\">\n"
                  << "        <td class=\"reduced-height\">1</td>\n"
                  << "        <td class=\"reduced-height\">" << meterType.toStdString() << "<br>"
                  << vectorSerialNumberCopy[row]->text().toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << ltCode.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << nmlNtmNorms.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << certiticateLaboratory.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << resultEntry.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << checkValability.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << costRon.toStdString() << "</td>\n"
                  << "      </tr>\n";
    }

    std::ostringstream streamObjCost;
    streamObjCost << std::fixed << std::setprecision(2);
    streamObjCost << costRon.toDouble() * entriesTableUsed;
    std::string totalCost = streamObjCost.str();

    std::ostringstream streamObjTVA;
    streamObjTVA << std::fixed << std::setprecision(2);
    streamObjTVA << costRon.toDouble() * entriesTableUsed * 0.19;
    std::string totalTVA = streamObjTVA.str();

    std::ostringstream streamObjCostTVA;
    streamObjCostTVA << std::fixed << std::setprecision(2);
    streamObjCostTVA << costRon.toDouble() * entriesTableUsed * 1.19;
    std::string totalCostTVA = streamObjCostTVA.str();

    for (size_t row = 0; row < 1; ++row) // Assuming you want to iterate only once based on the provided loop condition
    {
        htmlTable << "     <tr style=\"height: 20px;\">\n";

        switch (row) {
        case 0:
            htmlTable << "        <td style=\"no-border\" colspan=6 style=\"text-align:left;\">Locul efectuarii verificarii metrologice: " << ui->leLoculEfectuariiVerificarii->text().toStdString() << "<br><br>"
                      << "Data si ora finalizarii masurarilor:____________________________________________________</td>\n"
                      << "        <td>Total</td>\n"
                      << "        <td>" << totalCost << "</td>\n";
            break;

        case 1:
            htmlTable << "        <td style=\"no-border\" colspan=6 class=\"left\">Costul total al verificarii metrologice fara TVA este " << totalCost << " lei.</td>\n"
                      << "        <td><strong>TVA</strong></td>\n"
                      << "        <td>" << totalTVA << "</td>\n";
            break;

        case 2:
            htmlTable << "        <td style=\"no-border\" colspan=6></td>\n"
                      << "        <td><strong>Total general</strong></td>\n"
                      << "        <td>" << totalCostTVA << "</td>\n";
            break;
        }

        htmlTable << "        </tr>\n";
    }

    htmlTable << "  </table><br>\n"
              << "<table width=\"100%\" style=\"text-align: left;\">\n"
              << "    <tbody>\n"
              << "        <tr>\n"
              << "                <td style=\"width: 40%; text-align: left;\"><u>Verificator metrolog </u></td>\n"
              << "                <td style=\"width: 60%; text-align: left;\">Prezentul document a fost predat beneficiarului</td>\n"
              << "        </tr>\n"
              << "        <tr>\n"
              << "              <td style=\"width: 40%; text-align: left;\">" << ui->leVerificatorMetrolog->text().toStdString() << "</td>\n"
              << "              <td style=\"width: 60%; text-align: left;\">Nume,&nbsp;prenume,&nbsp;B.I.&nbsp;/&nbsp;C.I.,&nbsp;nr.&nbsp;imputernicire _____________________________</td>\n"
              << "        </tr>\n"
              << "        <tr>\n"
              << "              <td style=\"width: 40%; text-align: left;\">Semnatura_____________________________</td>\n"
              << "              <td style=\"width: 60%; text-align: left;\">___________________________________________________________________________</td>\n"
              << "        </tr>\n"
              << "        <tr>\n"
              << "              <td style=\"width: 40%; text-align: left;\">Indicativul&nbsp;marcii_______________________</td>\n"
              << "              <td style=\"width: 60%; text-align: left;\">Data,ora&nbsp;__________________________________Semnatura____________________</td>\n"
              << "        </tr>\n"
              << "    </tbody>\n"
              << "</table>\n"
              << "<div class=\"text-container\" style=\"text-align: left;\">"
              << "<p style=\"font-size: 7px; line-height: 0.6;\">" << "1) Prezentul buletin nu se refera la caractersitici sau functii pentru care normativele nu contin cerinte metrologice sau tehnice.<br>"
                                                                      "2) In cazul mijloacelor de masurare pentru care, conform reglementarilor in vigoare, este prevazuta aprobarea de model se completeazasi numarul AM<br>"
                                                                      "sau AM CEE. In cazul evaluarii conformitatii, se completeaza numarul documentului care aproba tipul.<br>"
                                                                      "3) Daca rezultatul este \"RESPINS\" se precizeaza succint cauzele respingerii, daca s-a efectuat si calibrarea, se mentioneaza numarul<br>certificatului de "
                                                                      "calibrare<br><br>"
                                                                      "F-02-PML 3-01</p>";

    htmlTable << "</body>\n"
              << "</html>\n";

    ///////////////////////
    //    std::string fileNameHtlm = "generated_html_file.html";
    //    std::ofstream outputFile(fileNameHtlm);
    //    outputFile << htmlTable.str();
    //    outputFile.close();
    ///////////////////////

    QTimerGenerareBv->start(2000);
    ui->pbGenerareBV->setEnabled(false);
    std::thread pdfThread(printPdfThread, QString::fromStdString(htmlTable.str()));
    pdfThread.detach();

    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");

    settings.setValue("autorizatiaNumarul", ui->leAutorizatiaNumarul->text());
    int numarInregistrare =  ui->leNumarInregistrare->text().toInt();
    numarInregistrare++;
    ui->leNumarInregistrare->setText(QString::number(numarInregistrare));
    settings.setValue("numarInregistrare", numarInregistrare);
    settings.setValue("beneficiar", ui->leBeneficiar->text());
    settings.setValue("codulDinLt", ui->leCoduldinLt->text());
    settings.setValue("normativ", ui->leNormativ->text());
    settings.setValue("valabilitate", ui->cbValabilitate->currentIndex());
    settings.setValue("cost", ui->leCost->text());
    settings.setValue("verificatorMetrolog", ui->leVerificatorMetrolog->text());
    settings.setValue("loculEfectuariiVerificarii", ui->leLoculEfectuariiVerificarii->text());

    settings.endGroup();
    settings.sync();
}

/**
 * \brief Slot triggered when the "Close" button is clicked.
 *
 * Hides the dialog window.
 */
void ReportMeasurements::onCloseClicked() {
    this->hide();
}

/**
 * \brief Slot triggered when the timer for "Generate BV" button is stopped.
 *
 * Stops the timer and re-enables the "Generate BV" button.
 */
void ReportMeasurements::enableGenerareBvButton() {
    // Stop the timer
    QTimerGenerareBv->stop();

    // Re-enable the button
    ui->pbGenerareBV->setEnabled(true);
}
