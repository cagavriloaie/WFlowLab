/**
 * \class ReportMeasurements
 * \brief Handles generation and display of measurement reports.
 *
 * This class manages report creation, formatting, and interaction with the user interface.
 * It includes functionalities for generating HTML reports, displaying them in dialogs,
 * and exporting to PDF.
 *
 * \note Assumes the presence of specific UI elements and connections defined in the associated .ui file.
 */

#include "Report.h"  // Header for report functionality

#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QMessageBox>
#include <QPrinter>
#include <QSettings>
#include <QTextDocument>
#include <QThread>
#include <QTimer>

#include <algorithm>  // Standard C++ algorithms
#include <iomanip>    // I/O manipulators
#include <sstream>    // String stream operations

#include "Logger.h"            // Logging system
#include "MainWindow.h"        // Your application's main window
#include "MainWindowInstance.h"  // Thread-safe singleton for MainWindow access
#include "PdfGeneratorWorker.h"  // Thread-safe PDF generation worker
#include "ui_MainWindow.h"     // UI definition for main window
#include "ui_Report.h"         // UI definition for report dialog

// NOTE: printPdfThread() function removed - PDF generation now handled by PdfGeneratorWorker with QThread

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
    static const std::string units[] = {
        "",       ///< 0
        "un",     ///< 1
        "doua",   ///< 2
        "trei",   ///< 3
        "patru",  ///< 4
        "cinci",  ///< 5
        "sase",   ///< 6
        "sapte",  ///< 7
        "opt",    ///< 8
        "noua"    ///< 9
    };
    static const std::string teens[] = {
        "",               ///< 0
        "unsprezece",     ///< 11
        "doisprezece",    ///< 12
        "treisprezece",   ///< 13
        "paisprezece",    ///< 14
        "cincisprezece",  ///< 15
        "saisprezece",    ///< 16
        "saptesprezece",  ///< 17
        "optisprezece",   ///< 18
        "nouasprezece"    ///< 19
    };
    static const std::string tens[] = {
        "",           ///< 0
        "",           ///< 1
        "douazeci",   ///< 20
        "treizeci",   ///< 30
        "patruzeci",  ///< 40
        "cincizeci",  ///< 50
        "saizeci",    ///< 60
        "saptezeci",  ///< 70
        "optzeci",    ///< 80
        "nouazeci"    ///< 90
    };

    std::string result;

    // Handle the zero case
    if (num == 0) {
        return (addSuffix) ? "zero" : "";
    }

    // Handle negative values
    if (num < 0) {
        result += "minus ";
        num = -num;  // Make num positive for further processing
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
 * Example:
 * \code
 * ReportMeasurements report;
 * report.Translate();
 * \endcode
 */
void ReportMeasurements::translate() {
    // Retranslate UI elements from .ui file (tooltips, etc.)
    ui->retranslateUi(this);

    this->setWindowTitle(tr("WStreamLab - Informatii buletin de verificare metrologica"));
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

    // Re-translate ComboBox items (do not add new items - they exist from constructor)
    ui->cbValabilitate->setItemText(0, tr("0 ani"));
    ui->cbValabilitate->setItemText(1, tr("6 luni"));
    ui->cbValabilitate->setItemText(2, tr("1 an"));
    ui->cbValabilitate->setItemText(3, tr("2 ani"));
    ui->cbValabilitate->setItemText(4, tr("3 ani"));
    ui->cbValabilitate->setItemText(5, tr("4 ani"));
    ui->cbValabilitate->setItemText(6, tr("5 ani"));
    ui->cbValabilitate->setItemText(7, tr("6 ani"));
    ui->cbValabilitate->setItemText(8, tr("7 ani"));
    ui->cbValabilitate->setItemText(9, tr("8 ani"));
    ui->cbValabilitate->setItemText(10, tr("9 ani"));
    ui->cbValabilitate->setItemText(11, tr("10 ani"));

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
ReportMeasurements::ReportMeasurements(QWidget* parent, const std::vector<QCheckBox*>& vectorCheckNumber,
                                       const std::vector<QLineEdit*>& vectorSerialNumber,
                                       const QString resultAllTests[20])
    : QDialog(parent), ui(new Ui::report), vectorCheckNumberCopy(vectorCheckNumber),
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
    setWindowTitle(tr("WStreamLab - Informatii buletin de verificare metrologica"));

    // Set labels and options for the UI elements
    ui->grBoxBuletin->setTitle(tr("Date de verificare metrologica"));
    ui->lbAutorizatiaNumarul->setText(tr("Autorizatia numarul:"));
    ui->lbNumarInregistrare->setText(tr("Numar de inregistrare:"));
    ui->lbBeneficiar->setText(tr("Beneficiar:"));
    ui->lbCodulDinLt->setText(tr("Cod din LT:"));
    ui->lbNormativ->setText(tr("Normativ:"));
    ui->lbValabilitate->setText(tr("Valabilitate:"));
    ui->lbCost->setText(tr("Cost:"));
    ui->lbVerificatorMetrolog->setText(tr("Verificator metrolog:"));
    ui->lbLoculEfectuariiVerificarii->setText(tr("Locul efectuarii verificarii metrologice:"));

    // Populate validity ComboBox (items added only once in constructor)
    ui->cbValabilitate->addItem(tr("0 ani"));
    ui->cbValabilitate->addItem(tr("6 luni"));
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
    QSettings settings(REGISTRY_PATH, QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");

    ui->leAutorizatiaNumarul->setText(settings.value("authorizationNumber", "1050/2024").toString());
    ui->leNumarInregistrare->setText(settings.value("registrationNumber", 1).toString());
    ui->leBeneficiar->setText(settings.value("beneficiary", "Termo Util").toString());
    ui->leCoduldinLt->setText(settings.value("ltCode", "1.06.28.1.1").toString());
    ui->leNormativ->setText(settings.value("standard", "NML").toString());
    // ComboBox index: 0="6 luni", 1="1 an", 2="2 ani", ..., 6="6 ani", 7="7 ani", ..., 10="10 ani"
    // Previous default was index 6 (7 ani), now index 7 for same value
    ui->cbValabilitate->setCurrentIndex(settings.value("validityYears", 7).toInt());
    ui->leCost->setText(settings.value("cost", 100).toString());
    ui->leVerificatorMetrolog->setText(settings.value("metrologistName", "Adrian Pintilie").toString());
    ui->leLoculEfectuariiVerificarii->setText(
        settings.value("verificationLocation", "Str. Morilor nr 8, Pascani").toString());

    settings.endGroup();
    settings.sync();

    // Set initial focus to the first input field in the tab order
    ui->leAutorizatiaNumarul->setFocus();

    // Connect signals and slots
    connect(ui->pbInchide, &QPushButton::clicked, this, &ReportMeasurements::onCloseClicked);
    connect(ui->pbGenerareBV, &QPushButton::clicked, this, &ReportMeasurements::onPrintClicked);
    connect(QTimerGenerareBv, &QTimer::timeout, this, &ReportMeasurements::enableGenerareBvButton);
}

/**
 * \brief Destructor for the ReportMeasurements class.
 *
 * Releases allocated UI resources.
 */
ReportMeasurements::~ReportMeasurements() {
    delete ui;
}





/**
 * \brief Slot invoked when the "Generate BV" button is clicked.
 *
 * Collects data from line edits, validates input, and generates a verification report in PDF format.
 * Displays error message if any required field is empty.
 */
void ReportMeasurements::onPrintClicked() {
    // Collect line edits in a vector
    std::vector<QLineEdit*> lineEdits = {ui->leAutorizatiaNumarul,
                                          ui->leNumarInregistrare,
                                          ui->leBeneficiar,
                                          ui->leCoduldinLt,
                                          ui->leNormativ,
                                          ui->leCost,
                                          ui->leVerificatorMetrolog,
                                          ui->leLoculEfectuariiVerificarii};

    // Check whether any required field is empty
    bool anyFieldEmpty = std::any_of(lineEdits.begin(), lineEdits.end(),
                                     [](const QLineEdit* lineEdit) { return lineEdit->text().isEmpty(); });

    if (anyFieldEmpty) {
        QMessageBox messageBoxWindowsTitle;
        messageBoxWindowsTitle.setWindowTitle(tr("Metrological Verification Report"));
        messageBoxWindowsTitle.setText(tr("Some required fields are not filled in."));
        messageBoxWindowsTitle.setStandardButtons(QMessageBox::Ok);
        messageBoxWindowsTitle.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint |
                                              Qt::WindowCloseButtonHint);
        if (messageBoxWindowsTitle.exec() == QMessageBox::Ok) {
            messageBoxWindowsTitle.close();
        }
        return;
    }

    // Get MainWindow instance thread-safely
    MainWindow* pMainWindow = MainWindowInstance::getInstance();
    if (!pMainWindow) {
        qCritical() << "ReportMeasurements::onPrintClicked:" << tr("MainWindow instance is null!");
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

    QString ltCode = ui->leCoduldinLt->text();
    QString nmlNtmNorms = ui->leNormativ->text();
    QString checkValability = ui->cbValabilitate->currentText();
    QString costRon = ui->leCost->text();
    QString companyLaboratory = QString::fromStdString(pMainWindow->optionsConfiguration["company"]);
    QString autorizationNumarul = ui->leAutorizatiaNumarul->text();
    QString certiticateLaboratory = QString::fromStdString(pMainWindow->optionsConfiguration["certificate"]);
    QString detinator = ui->leBeneficiar->text();
    QString meterType = pMainWindow->ui->cbWaterMeterType->currentText();

    std::stringstream htmlTable;

    // Begin constructing the HTML content
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
              << "      table-layout: fixed;\n"  // Ensures equal width allocation
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
              << "      width: 30%;\n"  // More balanced size for description column
              << "    }\n"
              << "    th:nth-child(5), td:nth-child(5) {\n"
              << "      width: 35%;\n"  // Increased width for column 5
              << "      word-break: break-word;\n"
              << "    }\n"
              << "    table.header-table {\n"
              << "      border-collapse: collapse;\n"
              << "      width: 100%;\n"
              << "      font-size: 11px;\n"
              << "      table-layout: fixed;\n"
              << "    }\n"
              << "    table.header-table td {\n"
              << "      border: 1px solid #000000;\n"  // Full black frame around every header cell
              << "      padding: 6px;\n"
              << "      text-align: center;\n"
              << "      vertical-align: middle;\n"
              << "    }\n"
              << "  </style>\n"
              << "</head>\n"
              << "<body>\n"
              << "  <table class=\"header-table\" width=\"100%\" border=\"1\" cellspacing=\"0\" cellpadding=\"6\" "
                 "style=\"border-collapse: collapse; border: 1px solid #000000; table-layout: fixed; font-size: "
                 "11px;\">\n"
              << "    <tr>\n"
              << "      <td rowspan=\"2\" width=\"25%\" style=\"border: 1px solid #000000; padding: 6px; text-align: "
                 "left; vertical-align: middle;\"><strong>"
              << companyLaboratory.toHtmlEscaped().toStdString()
              << "</strong><br><strong>LABORATOR DE</strong><br><strong>METROLOGIE</strong></td>\n"
              << "      <td width=\"50%\" style=\"border: 1px solid #000000; padding: 6px; text-align: center; "
                 "vertical-align: middle;\"><strong>PROCEDURA GENERALA</strong></td>\n"
              << "      <td rowspan=\"2\" width=\"25%\" style=\"border: 1px solid #000000; padding: 6px; text-align: "
                 "center; vertical-align: middle;\"><strong>Cod: PGLM-10</strong></td>\n"
              << "    </tr>\n"
              << "    <tr>\n"
              << "      <td width=\"50%\" style=\"border: 1px solid #000000; padding: 6px; text-align: center; "
                 "vertical-align: middle;\"><strong>RAPORTAREA REZULTATELOR</strong></td>\n"
              << "    </tr>\n"
              << "  </table>\n"
              << "  <p style=\"font-size: 12px; line-height: 0.6;\">Anexa nr.5 - Model - Buletin de verificare metrologica cod F-02-PML 3-01"
              << "  <br>\n"
              << "  <p style=\"font-size: 10px; line-height: 0.6;\">Laboratorul de metrologie al "
              << companyLaboratory.toStdString() << "</p>\n"
              << "  <p style=\"font-size: 10px; line-height: 0.6;\">Autorizatia nr. "
              << autorizationNumarul.toStdString() << "</p>\n"
              << "  <br>\n"
              << "  <center>\n"
              << "    <p style=\"font-size: 13px; line-height: 0.6;\">Buletin de verificare metrologica</p>\n"
              << "    <p style=\"font-size: 10px; line-height: 0.6;\">nr. "
              << ui->leNumarInregistrare->text().toStdString()
              << " data emiterii: " << std::put_time(localTime, "%d-%m-%Y")
              << " ora: " << std::put_time(localTime, "%H:%M") << "<br>\n"
              << "  </center>\n"
              << "  <p style=\"font-size: 10px; text-align:left;\">Mijloacele de masurare apartinand "
              << detinator.toStdString()
              << ", prezentate la verificare metrologica, au obtinut urmatoarele rezultate:</p>\n"


              << "<center>\n"
              << "  <table class=\"first\">\n"
              << "    <thead>\n"
              << "      <tr>\n"
              << "        <th>Nr. <br>buc.</th>\n"
              << "        <th>Mijloc de masurare-denumire, <br>tip, producator, caracteristici, <br>seria/an de "
                 "fabricatie</th>\n"
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

        // A rejected meter gets no period of validity, whatever the dialog has selected
        QString entryValability = (resultEntry == "RESPINS") ? tr("0 ani") : checkValability;

        htmlTable << "      <tr style=\"height: 20px;\">\n"
                  << "        <td class=\"reduced-height\">1</td>\n"
                  << "        <td class=\"reduced-height\">" << meterType.toStdString() << "<br>"
                  << vectorSerialNumberCopy[row]->text().toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << ltCode.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << nmlNtmNorms.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << certiticateLaboratory.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << resultEntry.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << entryValability.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << costRon.toStdString() << "</td>\n"
                  << "      </tr>\n";
    }

    std::ostringstream streamObjCost;
    streamObjCost << std::fixed << std::setprecision(2);
    streamObjCost << costRon.toDouble() * entriesTableUsed;
    std::string totalCost = streamObjCost.str();

    std::ostringstream streamObjTVA;
    streamObjTVA << std::fixed << std::setprecision(2);
    streamObjTVA << costRon.toDouble() * entriesTableUsed * TVA;
    std::string totalTVA = streamObjTVA.str();

    std::ostringstream streamObjCostTVA;
    streamObjCostTVA << std::fixed << std::setprecision(2);
    streamObjCostTVA << costRon.toDouble() * entriesTableUsed * (1 + TVA);
    std::string totalCostTVA = streamObjCostTVA.str();
    // Generate 3 table rows: Total, TVA and grand total, with the verification location in a
    // single cell on the left spanning all 3 rows
    for (size_t row = 0; row < 3; ++row)
    {
        htmlTable << "     <tr style=\"height: 20px;\">\n";

        if (row == 0) {
            htmlTable << "        <td colspan=\"6\" rowspan=\"3\" style=\"border: 1px solid #dddddd; "
                         "text-align:left; vertical-align:top;\">Locul efectuarii verificarii metrologice: "
                      << ui->leLoculEfectuariiVerificarii->text().toStdString() << "<br><br>"
                      << "Data si ora finalizarii masurarilor "
                         "metrologic:____________________________________________________</td>\n";
        }

        switch (row) {
        case 0:
            htmlTable << "        <td style=\"border: 1px solid #dddddd;\">Total</td>\n"
                      << "        <td style=\"border: 1px solid #dddddd;\">" << totalCost << "</td>\n";
            break;

        case 1:
            htmlTable << "        <td style=\"border: 1px solid #dddddd;\"><strong>TVA</strong></td>\n"
                      << "        <td style=\"border: 1px solid #dddddd;\">" << totalTVA << "</td>\n";
            break;

        case 2:
            htmlTable << "        <td style=\"border: 1px solid #dddddd;\"><strong>Total general</strong></td>\n"
                      << "        <td style=\"border: 1px solid #dddddd;\">" << totalCostTVA << "</td>\n";
            break;
        }

        htmlTable << "        </tr>\n";
    }

    htmlTable
        << "  </table><br>\n"
        << "<table width=\"100%\" style=\"text-align: left;\">\n"
        << "    <tbody>\n"
        << "        <tr>\n"
        << "                <td style=\"width: 40%; text-align: left;\"><u>Verificator metrolog </u></td>\n"
        << "                <td style=\"width: 60%; text-align: left;\">Prezentul document a fost predat "
           "beneficiarului</td>\n"
        << "        </tr>\n"
        << "        <tr>\n"
        << "              <td style=\"width: 40%; text-align: left;\">"
        << ui->leVerificatorMetrolog->text().toStdString() << "</td>\n"
        << "              <td style=\"width: 60%; text-align: "
           "left;\">Nume,&nbsp;prenume,&nbsp;B.I.&nbsp;/&nbsp;C.I.,&nbsp;nr.&nbsp;imputernicire "
           "_____________________________</td>\n"
        << "        </tr>\n"
        << "        <tr>\n"
        << "              <td style=\"width: 40%; text-align: left;\">Semnatura_____________________________</td>\n"
        << "              <td style=\"width: 60%; text-align: "
           "left;\">___________________________________________________________________________</td>\n"
        << "        </tr>\n"
        << "        <tr>\n"
        << "              <td style=\"width: 40%; text-align: "
           "left;\">Indicativul&nbsp;marcii_______________________</td>\n"
        << "              <td style=\"width: 60%; text-align: "
           "left;\">Data,ora&nbsp;__________________________________Semnatura____________________</td>\n"
        << "        </tr>\n"
        << "    </tbody>\n"
        << "</table>\n"
        << "<div class=\"text-container\" style=\"text-align: left;\">"
        << "<p style=\"font-size: 7px; line-height: 0.6;\">"
        << "1) Prezentul buletin nu se refera la caracterisitici sau functii pentru care normativele nu contin cerinte "
           "metrologice sau tehnice.<br>"
           "2) In cazul mijloacelor de masurare pentru care, conform reglementarilor in vigoare, este prevazuta "
           "aprobarea de model se completeaza si numarul AM<br>"
           "sau AM CEE. In cazul evaluarii conformitatii, se completeaza numarul documentului care aproba tipul.<br>"
           "3) Daca rezultatul este \"RESPINS\" se precizeaza succint cauzele respingerii, daca s-a efectuat si "
           "calibrarea, se mentioneaza numarul<br>certificatului de "
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

    // Validate path before use - critical security check (pMainWindow already declared earlier)
    QString pathResults = QString::fromStdString(pMainWindow->selectedInfo.pathResults);
    QString validatedPath = MainWindow::validateAndSanitizePath(pathResults, true);

    if (validatedPath.isEmpty()) {
        qCritical() << "ReportMeasurements::onPrintClicked:" << tr("Invalid or unsafe path:") << pathResults;
        Logger::error(LogCategory::UserAction,
                      tr("BV Report failed - invalid path: %1").arg(pathResults));
        return;
    }

    // Create worker and thread for PDF generation
    QString htmlReport = QString::fromStdString(htmlTable.str());
    QThread* pdfThread = new QThread();
    PdfGeneratorWorker* worker = new PdfGeneratorWorker();
    worker->moveToThread(pdfThread);

    // Connect signals and slots
    connect(pdfThread, &QThread::started, worker, [worker, htmlReport, validatedPath]() {
        worker->generatePdf(htmlReport, validatedPath, "BV_");
    });
    connect(worker, &PdfGeneratorWorker::finished, pdfThread, &QThread::quit);
    connect(worker, &PdfGeneratorWorker::finished, worker, &PdfGeneratorWorker::deleteLater);
    connect(pdfThread, &QThread::finished, pdfThread, &QThread::deleteLater);

    // Start the thread
    pdfThread->start();

    QSettings settings(REGISTRY_PATH, QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");

    settings.setValue("authorizationNumber", ui->leAutorizatiaNumarul->text());
    int numarInregistrare = ui->leNumarInregistrare->text().toInt();
    numarInregistrare++;
    ui->leNumarInregistrare->setText(QString::number(numarInregistrare));
    settings.setValue("registrationNumber", numarInregistrare);
    settings.setValue("beneficiary", ui->leBeneficiar->text());
    settings.setValue("ltCode", ui->leCoduldinLt->text());
    settings.setValue("standard", ui->leNormativ->text());
    settings.setValue("validityYears", ui->cbValabilitate->currentIndex());
    settings.setValue("cost", ui->leCost->text());
    settings.setValue("metrologistName", ui->leVerificatorMetrolog->text());
    settings.setValue("verificationLocation", ui->leLoculEfectuariiVerificarii->text());

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
