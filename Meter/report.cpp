/*
 *  Author: Constantin
 *  File:   report.cpp
 */

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include <QCheckBox>
#include <QCoreApplication>
#include <QDateTime>
#include <QDialog>
#include <QDesktopServices>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QPageSize>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QValidator>
#include <QtDebug>

#include "mainwindow.h"
#include "report.h"
#include "ui_mainwindow.h"
#include "ui_report.h"

extern MainWindow *pw;


std::string convertNumberToWords(int num, bool addSuffix)
{
    static
        const std::string units[] =
        {
            "",
            "un",
            "doua",
            "trei",
            "patru",
            "cinci",
            "sase",
            "sapte",
            "opt",
            "noua"
        };
    static
        const std::string teens[] =
        {
            "",
            "unsprezece",
            "doisprezece",
            "treisprezece",
            "paisprezece",
            "cincisprezece",
            "saisprezece",
            "saptesprezece",
            "optisprezece",
            "nouasprezece"
        };
    static
        const std::string tens[] =
        {
            "",
            "",
            "douazeci",
            "treizeci",
            "patruzeci",
            "cincizeci",
            "saizeci",
            "saptezeci",
            "optzeci",
            "nouazeci"
        };
    std::string result;
    if (num == 0)
    {
        return (addSuffix) ? "zero" : "";
    }
    if (num < 0)
    {
        result += "minus ";
        num = -num;
    }
    if (num >= 1000000)
    {
        result += convertNumberToWords(num / 1000000, true);
        if (num / 1000000 == 1)
        {
            result += " milion ";
        }
        else
        {
            result += " milioane ";
        }
        num %= 1000000;
    }
    if (num >= 1000)
    {
        if (num >= 2000)
        {
            result += convertNumberToWords(num / 1000, true);
        }
        else
        {
            result += "o mie ";
        }
        num %= 1000;
    }
    if (num >= 100)
    {
        if (num >= 200)
        {
            result += " " + convertNumberToWords(num / 100, true) +
                      " sute ";
        }
        else
        {
            result += "o suta ";
        }
        num %= 100;
    }
    if (num >= 11 && num <= 19)
    {
        result += teens[num - 11] + " ";
    }
    else if (num >= 20 || num == 10)
    {
        result += tens[num / 10] + " ";
        num %= 10;
    }
    if (num >= 1 && num <= 9)
    {
        result += units[num];
    }
    return result;
}

void ReportMeasurements::Translate()
{
    this -> setWindowTitle(tr(
        "WFlowLab - Informatii buletin verificare metrologica"));
    ui -> grBoxBuletin -> setTitle(tr("Date verificare metrologica"));
    ui -> lbAutorizatiaNumarul->setText(tr("Autorizatia numarul:"));
    ui -> lbNumarInregistrare -> setText((tr("Numar de inregistrare: ")));
    ui -> lbBeneficiar -> setText(tr("Beneficiar: "));
    ui -> lbCodulDinLt -> setText(tr("Codul din LT: "));
    ui -> lbNormativ -> setText(tr("Normativ: "));
    ui -> lbValabilitate -> setText(tr("Valabilitate: "));
    ui -> lbCost -> setText(tr("Cost: "));
    ui -> lbVerificatorMetrolog -> setText(tr("Verificator metrolog: "));
    ui -> lbLoculEfectuariiVerificarii -> setText(tr("Locul efectuarii verificarii:"));
    ui -> cbValabilitate -> addItem(tr("6 luni"));
    ui -> cbValabilitate -> addItem(tr("1 an"));
    ui -> cbValabilitate -> addItem(tr("2 ani"));
    ui -> cbValabilitate -> addItem(tr("3"));
    ui -> cbValabilitate -> addItem(tr("5 ani"));
    ui -> pbGenerareBV -> setText(tr("&Generare BV"));
    ui -> pbInchide -> setText(tr("&Inchide"));
}

ReportMeasurements::ReportMeasurements(QWidget *parent,
                                       const std::vector < QCheckBox * > &vectorCheckNumber,
                                       const std::vector < QLineEdit * > &vectorSerialNumber,
                                       const QString resultAllTests[20]):
    QDialog(parent),
    ui(new Ui::report),
    vectorCheckNumberCopy(vectorCheckNumber),
    vectorSerialNumberCopy(vectorSerialNumber)
{
    ui -> setupUi(this);

    setWindowFlags(Qt::Window);

    for (auto iter = 0; iter < MAX_ARRAY_SIZE; ++iter)
    {
        resultAllTestsCopy[iter] = resultAllTests[iter];
    }
    this -> setWindowTitle(tr(
        "WFlowLab - Informatii buletin de verificare metrologica"));
    ui -> grBoxBuletin -> setTitle(tr("Date verificare metrologica"));
    ui -> lbAutorizatiaNumarul->setText(tr("Autorizatia numarul:"));
    ui -> lbNumarInregistrare -> setText((tr("Numar de inregistrare: ")));
    ui -> lbBeneficiar -> setText(tr("Beneficiar: "));
    ui -> lbCodulDinLt -> setText(tr("Codul din LT: "));
    ui -> lbNormativ -> setText(tr("Normativ: "));
    ui -> lbValabilitate -> setText(tr("Valabilitate: "));
    ui -> lbCost -> setText(tr("Cost: "));
    ui -> lbVerificatorMetrolog -> setText(tr("Verificator metrolog: "));
    ui -> lbLoculEfectuariiVerificarii->setText(tr("Locul efectuarii verificarii:"));
    ui -> cbValabilitate -> addItem(tr("6 luni"));
    ui -> cbValabilitate -> addItem(tr("1 an"));
    ui -> cbValabilitate -> addItem(tr("2 ani"));
    ui -> cbValabilitate -> addItem(tr("3"));
    ui -> cbValabilitate -> addItem(tr("5 ani"));
    ui -> pbGenerareBV -> setText(tr("&Generare BV"));
    ui -> pbInchide -> setText(tr("&Inchide"));

    QDoubleValidator *validatorDoubleNumber = new QDoubleValidator(this);
    ui -> leCost -> setValidator(validatorDoubleNumber);
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab",
                       QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");

    ui -> leAutorizatiaNumarul -> setText(settings.value(
                                                  "autorizatiaNumarul", "1050/2023").toString());
    ui -> leNumarInregistrare -> setText(settings.value(
                                                 "numarInregistrare", 1).toString());
    ui -> leBeneficiar -> setText(settings.value("beneficiar", "Termo Util")
                                  .toString());
    ui -> leCoduldinLt -> setText(settings.value("codulDinLt", "1.06.28.1.1")
                                  .toString());
    ui -> leNormativ -> setText(settings.value("normativ", "NML")
                                .toString());
    ui -> cbValabilitate -> setCurrentIndex(settings.value("valabilitate",
                                                       4).toInt());
    ui -> leCost -> setText(settings.value("cost", 100).toString());
    ui -> leVerificatorMetrolog -> setText(settings.value(
                                                   "verificatorMetrolog", "Adrian Pintilie").toString());
    ui -> leLoculEfectuariiVerificarii -> setText(settings.value(
                                                          "loculEfectuariiVerificarii", "Str. Morilor nr 8, Pascani").toString());

    settings.endGroup();
    settings.sync();
    ui ->leAutorizatiaNumarul -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leNumarInregistrare -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leBeneficiar -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leCoduldinLt -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leNormativ -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> cbValabilitate -> setStyleSheet(
        "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui -> leCost -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leVerificatorMetrolog -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leLoculEfectuariiVerificarii -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> lbNumarInregistrare -> setFocus();
    connect(ui -> pbInchide, & QPushButton::clicked, this,
            &ReportMeasurements::onCloseClicked);
    connect(ui -> pbGenerareBV, & QPushButton::clicked, this,
            &ReportMeasurements::onPrintClicked);
}

ReportMeasurements::~ReportMeasurements()
{
    delete ui;
}

void ReportMeasurements::onPrintClicked()
{
    // Collect line edits in a vector
    std::vector<QLineEdit*> lineEdits = {
        ui->leAutorizatiaNumarul,
        ui->leNumarInregistrare,
        ui->leBeneficiar,
        ui->leCoduldinLt,
        ui->leNormativ,
        ui->leCost,
        ui->leVerificatorMetrolog,
        ui->leLoculEfectuariiVerificarii
    };

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
    std::tm *localTime = std::localtime(&currentTime);

    // Other variables
    size_t entriesTable = pw->selectedInfo.entriesNumber;

    QString ltCode = ui->leCoduldinLt->text();
    QString nmlNtmNorms = ui->leNormativ->text();
    QString checkValability = ui->cbValabilitate->currentText();
    QString costRon = ui->leCost->text();
    QString companyLaboratory = QString::fromStdString(pw->optionsConfiguration["company"]);
    QString autorizationNumarul = ui->leAutorizatiaNumarul->text();
    QString certiticateLaboratory = QString::fromStdString(pw->optionsConfiguration["certificate"]);
    QString detinator = ui->leBeneficiar->text();
    QString meterType = pw->ui->cbWaterMeterType->currentText();

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
              << "      margin-left: -100px;\n"
              << "    }\n"

              << "    th, td {\n"
              << "      border: 1px solid #dddddd;\n"
              << "      text-align: center;\n"
              << "      padding: 4px;\n"
              << "      margin: 0;\n"
              << "    }\n"

              << "    th {\n"
              << "      background-color: #f2f2f2;\n"
              << "    }\n"

              << "    tbody {\n"
              << "      background-color: #f0f0f0; /* Example background color */\n"
              << "    }\n"

              << "    th.smaller-column {\n"
              << "      width: 50px; /* Adjust the value as needed */\n"
              << "    }\n"

              << "    th:nth-child(2), td:nth-child(2) {\n"
              << "      width: 450px !important;\n"
              << "    }\n"

              << "    .text-container {\n"
              << "      width: 200px; /* Set the maximum width for the container */\n"
              << "      white-space: nowrap; /* Prevent text from wrapping to the next line */\n"
              << "      overflow: hidden; /* Hide any overflowing content */\n"
              << "    }\n"

              << "    br + br {\n"
              << "      display: block;\n"
              << "      content: \" \";\n"
              << "      margin: 0.5em 0; /* Adjust the margin as needed */\n"
              << "    }\n"

              << "    br {\n"
              << "      margin-bottom: 0.5em; /* Adjust the margin as needed */\n"
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
              << "  <p style=\"font-size: 10px;\"  style=\"text-align:left;\">Mijloacele de masurare apartinand\n"
              << detinator.toStdString() << ", prezentate la verificare metrologica, au obtinut urmatoarele rezultate:</p>\n"
              << "<center>\n"
              << "  <table class=\"first\">\n"
              << "    <thead>\n"
              << "      <tr>\n"
              << "        <th>Nr. <br>buc.</th>\n"
              << "        <th>Mijloc de masurare-denumire, <br>tip, producator, caracteristici, <br>seria/an de fabricatie</th>\n"
              << "        <th>Codul din LT</th>\n"
              << "        <th>Normativ<br>(NML, NTM etc)<</th>\n"
              << "        <th>Etaloane utilizate,<br>denumire, serie, nr. CE</th>\n"
              << "        <th>Rezultatul<br>verificarii</th>\n"
              << "        <th>Valabilitatea<br>verificarii</th>\n"
              << "        <th>Cost</th>\n"
              << "      </tr>\n"
              << "    </thead>\n"
              << "    <tbody>\n";

    size_t entriesTableUsed{0};

    for (size_t row = 0; row < entriesTable; ++row)
    {
        if (!vectorCheckNumberCopy[row]->checkState())
        {
            continue;
        }
        ++entriesTableUsed;
        htmlTable << "      <tr style=\"height: 20px;\">\n"
                  << "        <td class=\"reduced-height\">1</td>\n"
                  << "        <td class=\"reduced-height\">" << meterType.toStdString() <<  "<br>"
                  << vectorSerialNumberCopy[row]->text().toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << ltCode.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << nmlNtmNorms.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << certiticateLaboratory.toStdString() << "</td>\n"
                  << "        <td class=\"reduced-height\">" << resultAllTestsCopy[row].toStdString() << "</td>\n"
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

        switch (row)
        {
        case 0:
            htmlTable << "        <td style=\"no-border\" colspan=6 style=\"text-align:left;\">Locul efectuarii verificarii metrologice: " << ui->leLoculEfectuariiVerificarii->text().toStdString() << "<br>"
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
              << "               <td style=\"width: 40%; text-align: left;\">" << ui->leVerificatorMetrolog->text().toStdString() << "</td>\n"
              << "               <td style=\"width: 60%; text-align: left;\">Nume, prenume, B.I. / C.I., nr. imputernicire __________________________________</td>\n"
              << "        </tr>\n"
              << "        <tr>\n"
              << "              <td style=\"width: 40%; text-align: left;\">Semnatura _________________</td>\n"
              << "              <td style=\"width: 60%; text-align: left;\">_________________________________________________________________________________</td>\n"
              << "        </tr>\n"
              << "        <tr>\n"
              << "             <td style=\"width: 40%; text-align: left;\">Indicativul marcii: __________________" << "</td>\n"
              << "             <td style=\"width: 60%; text-align: left;\">Data, ora: __________________________________  Semnatura _______________________</td>\n"
              << "        </tr>\n"
              << "    </tbody>\n"
              << "</table>\n"
              << "<div class=\"text-container\" style=\"text-align: left;\">"
              << "<p style=\"font-size: 7px; line-height: 0.6;\">" <<
        "1) Prezentul buletin nu se refera la caractersitici sau functii pentru care normativele nu contin cerinte metrologice sau tehnice.<br>"
        "2) In cazul mijloacelor de masurare pentru care, conform reglementarilor in vigoare, este prevazuta aprobarea de model se completeazasi numarul AM sau<br>"
        "AM CEE. In cazul evaluarii conformitatii, se completeaza numarul documentului care aproba tipul.<br>"
        "3) Daca rezultatul este \"RESPINS\" se precizeaza succint cauzele respingerii, daca s-a efectuat si calibrarea, se mentioneaza numarul certificatului de "
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

    QDateTime nowPdf = QDateTime::currentDateTime();
    QString fileName = QString(pw->selectedInfo.pathResults.c_str()) +
                       "/" + QString("BV_") + nowPdf.toString(QLatin1String("yyyyMMdd_hhmmss"));
    fileName.append(".pdf");

    // Check if the directory exists, and create it if not
    QDir resultDir(pw->selectedInfo.pathResults.c_str());
    if (!resultDir.exists())
    {
        resultDir.mkpath(".");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setFullPage(true);
    qreal margin = 5.0;
    printer.setPageMargins(QMarginsF(margin, margin, margin, margin), QPageLayout::Millimeter);

    // Print HTML to PDF
    QTextDocument outputReport;
    outputReport.setHtml(QString::fromStdString(htmlTable.str()));
    outputReport.setDocumentMargin(0);
    outputReport.print(&printer);

    // Open the generated PDF
    fileName = QString("file:///") + fileName;
    QDesktopServices::openUrl(QUrl(fileName, QUrl::TolerantMode));

    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab", QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");

    settings.setValue("autorizatiaNumarul", ui->leAutorizatiaNumarul->text());
    settings.setValue("numarInregistrare", ui->leNumarInregistrare->text());
    settings.setValue("beneficiar", ui->leBeneficiar->text());
    settings.setValue("codulDinLt", ui->leCoduldinLt->text());
    settings.setValue("normativ", ui->leNormativ->text());
    settings.setValue("valabilitate", ui->cbValabilitate->currentIndex());
    settings.setValue("cost", ui->leCost->text());
    settings.setValue("verificatorMetrolog", ui->leVerificatorMetrolog->text());
    settings.setValue("loculEfectuariiVerificarii", ui->leLoculEfectuariiVerificarii->text());

    settings.endGroup();
    settings.sync();

    /*
QMessageBox messageBoxVerificationReport;
messageBoxVerificationReport.setWindowTitle(tr("Verification report"));
messageBoxVerificationReport.setText(tr("The file ") + fileName + tr(" was created!"));
messageBoxVerificationReport.setStandardButtons(QMessageBox::Ok);
messageBoxVerificationReport.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

// Create a QTimer
QTimer *timer = new QTimer(&messageBoxVerificationReport);
timer->setSingleShot(true); // Make the timer a single-shot timer
timer->setInterval(5000); // Set the interval to 5000 milliseconds (5 seconds)

// Connect the timeout signal to close the message box
QObject::connect(timer, &QTimer::timeout, &messageBoxVerificationReport, &QMessageBox::accept);

// Start the timer
timer->start();

// Show the message box
messageBoxVerificationReport.exec();
*/
}

void ReportMeasurements::onCloseClicked()
{
    this -> hide();
}


