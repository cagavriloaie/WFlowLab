/*
 *  Author: Constantin
 *  File:   report.cpp
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <thread>

#include <QMainWindow>
#include <QDesktopServices>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <QValidator>
#include <QtPrintSupport/QPrinter>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QKeyEvent>
#include <QSettings>
#include <QPageSize>
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

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
                               "WFlowLab - Buletin verificare metrologica"));
    ui -> grBoxBuletin -> setTitle(tr("Date verificare metrologica"));
    ui -> lbNumarInregistrare -> setText((tr("Numar de inregistrare: ")));
    ui -> lbDetinator -> setText(tr("Detinator: "));
    ui -> lbCodulLt -> setText(tr("Codul LT: "));
    ui -> lbNormative -> setText(tr("Normative: "));
    ui -> lbValabilitate -> setText(tr("Valabilitate: "));
    ui -> lbCost -> setText(tr("Cost: "));
    ui -> lbVerificatorMetrolog -> setText(tr("Verificator metrolog: "));
    ui -> lbConducatorLaborator -> setText(tr("Conducator laborator: "));
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
                                       const QString resultAllTests[20]): QDialog(parent),
    ui(new Ui::report),
    vectorCheckNumberCopy(vectorCheckNumber),
    vectorSerialNumberCopy(vectorSerialNumber)
{
    ui -> setupUi(this);
    connect(ui -> pbInchide, & QPushButton::clicked, this, &
            ReportMeasurements::onCloseClicked);
    connect(ui -> pbGenerareBV, & QPushButton::clicked, this, &
            ReportMeasurements::onPrintClicked);
    for (auto iter = 0; iter < 20; ++iter)
    {
        resultAllTestsCopy[iter] = resultAllTests[iter];
    }
    this -> setWindowTitle(tr(
                               "WFlowLab - Buletin Verificare metrologica"));
    ui -> grBoxBuletin -> setTitle(tr("Date verificare metrologica"));
    ui -> lbNumarInregistrare -> setText((tr("Numar de inregistrare: ")));
    ui -> lbDetinator -> setText(tr("Detinator: "));
    ui -> lbCodulLt -> setText(tr("Codul LT: "));
    ui -> lbNormative -> setText(tr("Normative: "));
    ui -> lbValabilitate -> setText(tr("Valabilitate: "));
    ui -> lbCost -> setText(tr("Cost: "));
    ui -> lbVerificatorMetrolog -> setText(tr("Verificator metrolog: "));
    ui -> lbConducatorLaborator -> setText(tr("Conducator laborator: "));
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
    ui -> leNumarInregistrare -> setText(settings.value(
            "numarInregistrare", 1).toString());
    ui -> leDetinator -> setText(settings.value("detinator", 1)
                                 .toString());
    ui -> leCodulLt -> setText(settings.value("codulLt", "1.06.28.1.1")
                               .toString());
    ui -> leNormative -> setText(settings.value("normative", "BRML")
                                 .toString());
    ui -> cbValabilitate -> setCurrentIndex(settings.value("valabilitate",
                                            2).toInt());
    ui -> leCost -> setText(settings.value("cost", 100).toString());
    ui -> leVerificatorMetrolog -> setText(settings.value(
            "verificatorMetrolog", "Adrian Pintilie").toString());
    ui -> leConducatorLaborator -> setText(settings.value(
            "conducatorLaborator", "Victor Trambu").toString());
    settings.endGroup();
    settings.sync();
    ui -> leNumarInregistrare -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leDetinator -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leCodulLt -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> leNormative -> setStyleSheet(
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
    ui -> leConducatorLaborator -> setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui -> lbNumarInregistrare -> setFocus();
}


ReportMeasurements::~ReportMeasurements()
{
    delete ui;
}

void ReportMeasurements::onPrintClicked()
{
    if (ui -> leNumarInregistrare -> text().isEmpty() || ui ->
            leDetinator -> text().isEmpty() || ui -> leCodulLt -> text()
            .isEmpty() || ui -> leNormative -> text().isEmpty() || ui ->
            leCost -> text().isEmpty() || ui -> leConducatorLaborator ->
            text().isEmpty())
    {
        QMessageBox messageBoxWindowsTitle;
        messageBoxWindowsTitle.setWindowTitle(tr("Verification report"));
        messageBoxWindowsTitle.setText(tr("There are unfilled fields!"));
        messageBoxWindowsTitle.setStandardButtons(QMessageBox::Ok);
        messageBoxWindowsTitle.setWindowFlags(Qt::Dialog | Qt::
                                              CustomizeWindowHint | Qt::WindowTitleHint | Qt::
                                              WindowCloseButtonHint);
        if (messageBoxWindowsTitle.exec() == QMessageBox::Ok)
        {
            messageBoxWindowsTitle.close();
        }
        return;
    }
    // Get the current time point
    auto now = std::chrono::system_clock::now();
    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    // Convert the time_t to a tm structure
    std::tm *localTime = std::localtime(& currentTime);
    size_t entriesTable = pw -> selectedInfo.entriesNumber;
    QString ltCode = ui -> leCodulLt -> text();
    QString nmlNtmNorms = ui -> leNormative -> text();
    QString checkValability = ui -> cbValabilitate -> currentText();
    QString costRon = ui -> leCost -> text();
    std::string companyLaboratory = pw -> optionsConfiguration["company"];
    std::string certiticateLaboratory = pw -> optionsConfiguration[
                                         "certificate"];
    std::stringstream htmlTable;
    // Start building the HTML string
    htmlTable << "<html>\n";
    htmlTable << "<head>\n";
    htmlTable << "  <title>Buletin de verificare metrologica</title>\n";
    htmlTable << " <style>\n";
    htmlTable <<
              "   p { font-size: 18px; }\n"; // Larger font size for paragraphs
    htmlTable << "  table.first {";
    htmlTable << "    border-collapse: collapse;";
    htmlTable << "    width: 100%;";
    htmlTable << "    font-size: 8px;";
    htmlTable << "    margin-left: -100px";
    htmlTable << " }";
    htmlTable << "th, td {";
    htmlTable << "    border: 1px solid #dddddd;";
    htmlTable << "    text-align: center;";
    htmlTable << "    padding: 4px;";
    htmlTable << "    margin: 0;";
    htmlTable << "}";
    htmlTable << "th {";
    htmlTable << "    background-color: #f2f2f2;";
    htmlTable << "}";
    htmlTable << "td.left {";
    htmlTable << "    text-align: left;";
    htmlTable << "    font-size: 10px;";
    htmlTable << "}";
    htmlTable << "* {";
    htmlTable << "    margin: 0;";
    htmlTable << "    padding: 0;";
    htmlTable << "    box-sizing: border-box;";
    htmlTable << "}";
    htmlTable << "tbody {";
    htmlTable <<
              "    background-color: #f0f0f0; /* Example background color */";
    htmlTable << "}";
    htmlTable << "th.smaller-column {";
    htmlTable << "     width: 50px; /* Adjust the value as needed */";
    htmlTable << "}";
    htmlTable << "th:nth-child(2), td:nth-child(2) {";
    htmlTable << "     width: 450px !important;";
    htmlTable << "}";
    htmlTable << "  </style>\n";
    htmlTable << "</head>\n";
    htmlTable << "<body>\n";
    htmlTable <<
              "  <p style=\"font-size: 13px;\"><strong>Biroul Roman de Metrologie Legala</strong>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
              "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Nr." <<
              ui -> leNumarInregistrare -> text().toStdString() <<
              "&nbsp;&nbsp;  /  " << std::put_time(localTime,
                      "%d-%m-%Y") << "</p>\n";
    htmlTable << "  <p style=\"font-size: 10px;\">Laboratorul " <<
              companyLaboratory << "</p><br>\n";
    htmlTable << "<center>\n";
    htmlTable <<
              "  <p style=\"font-size: 13px;\"><u>Buletin de verificare metrologica</u>";
    htmlTable << "</center>";
    QString detinator = ui->leDetinator->text();
    htmlTable <<
              "  <p style=\"font-size: 10px;\"  style=\"text-align:left;\">Mijloacele de masurare apartinand  "
              << detinator.toStdString() << " "
              "prezentate la verificare metrologica au obtinut urmatoarele rezultate:</p><br>\n";
    // Continue building the HTML string with the table
    htmlTable << "<center>\n";
    htmlTable << "  <table class=\"first\">\n";
    htmlTable << "    <thead>\n";
    htmlTable << "      <tr>\n";
    htmlTable << "        <th>Nr. <br>buc.</th>\n";
    htmlTable << "        <th>Mijloc de<br>masurare</th>\n";
    htmlTable << "        <th>Codul LT</th>\n";
    htmlTable << "        <th>NML, NTM,<br>alte normative</th>\n";
    htmlTable <<
              "        <th>Etaloane utilizate,<br>denumire, serie, nr. CE</th>\n";
    htmlTable << "        <th>Rezultatul<br>verificarii</th>\n";
    htmlTable << "        <th>Valabilitatea<br>verificarii</th>\n";
    htmlTable << "        <th>Cost (lei)</th>\n";
    htmlTable << "      </tr>\n";
    htmlTable << "    </thead>\n";
    htmlTable << "    <tbody>\n";
    // Add specified number of rows with sample data
    QString meterType = pw -> ui -> cbWaterMeterType -> currentText();
    for (size_t row = 0; row < entriesTable; ++row)
    {
        htmlTable << "      <tr style=\"height: 20px;\">\n";
        htmlTable << "        <td class=\"reduced-height\">1</td>\n";
        htmlTable << "        <td class=\"reduced-height\">" <<
                  vectorSerialNumberCopy[row] ->
                  text().toStdString() << "<br>" << meterType.toStdString() <<
                  "</td>\n";
        htmlTable << "        <td class=\"reduced-height\">" <<
                  ltCode.toStdString() << "</td>\n";
        htmlTable << "        <td class=\"reduced-height\">" <<
                  nmlNtmNorms.toStdString() <<
                  "</td>\n";
        htmlTable << "        <td class=\"reduced-height\">" <<
                  certiticateLaboratory << "</td>\n";
        htmlTable << "        <td class=\"reduced-height\">" <<
                  resultAllTestsCopy[row]
                  .toStdString() << "</td>\n";
        htmlTable << "        <td class=\"reduced-height\">" <<
                  checkValability.toStdString() <<
                  "</td>\n";
        htmlTable << "        <td class=\"reduced-height\">" <<
                  costRon.toStdString() << "</td>\n";
        htmlTable << "      </tr>\n";
    }
    std::ostringstream streamObjCost;
    streamObjCost << std::fixed;
    streamObjCost << std::setprecision(2);
    streamObjCost << costRon.toDouble() * entriesTable;
    std::string totalCost = streamObjCost.str();
    std::ostringstream streamObjTVA;
    streamObjTVA << std::fixed;
    streamObjTVA << std::setprecision(2);
    streamObjTVA << costRon.toDouble() * entriesTable * 0.19;
    std::string totaTVA = streamObjTVA.str();
    std::ostringstream streamObjCostTVA;
    streamObjCostTVA << std::fixed;
    streamObjCostTVA << std::setprecision(2);
    streamObjCostTVA << costRon.toDouble() * entriesTable * 1.19;
    std::string totalCostTVA = streamObjCostTVA.str();
    for (size_t row = 0; row < 3; ++row)
    {
        htmlTable << "     <tr style=\"height: 20px;\">\n";
        switch (row)
        {
            case 0:
                htmlTable <<
                          "        <td style=\"no-border\" colspan=6 class=\"left\">Locul efectuarii verificarii metrologice: "
                          << companyLaboratory << "</td>\n";
                htmlTable << "        <td><strong>Total</strong></td>\n";
                htmlTable << "        <td>" << totalCost << "</td>\n";
                break;
            case 1:
                htmlTable <<
                          "        <td style=\"no-border\" colspan=6 class=\"left\">Costul total al verificarii metrologice fara TVA este "
                          << totalCost << " lei.</td>\n";
                htmlTable << "        <td><strong>TVA</strong></td>\n";
                htmlTable << "        <td>" << totaTVA << "</td>\n";
                break;
            case 2:
                htmlTable << "        <td style=\"no-border\" colspan=6></td>\n";
                htmlTable <<
                          "        <td><strong>Total general</strong></td>\n";
                htmlTable << "        <td>" << totalCostTVA << "</td>\n";
                break;
        }
        htmlTable << "        </tr>\n";
    }
    htmlTable << "    </tbody>\n";
    htmlTable << "  </table>\n";
    htmlTable << "</center>";
    std::string totalCostTVALetters = convertNumberToWords(std::stoi(
                                          totalCostTVA), true);
    // Additional rows at the end of the HTML document
    htmlTable << "  <p style=\"font-size: 10px;\">";
    htmlTable <<
              "  <p style=\"font-size: 10px;\"><br>Costul total al verificarii metrologice cu TVA "
              <<
              totalCostTVA << " (" << totalCostTVALetters <<
              ") lei a fost achitat cu numerar / ordin de plata nr.______________________in contul______________________la trezoreria ______________________"
              <<
              "</p>\n";
    htmlTable << "<table width=\"100%\">\n";
    htmlTable << "    <tr style=\"height: 20px;\">";
    htmlTable <<
              "        <td style=\"font-size: 10px; border: none; padding: 8px;\">Verificator metrolog</td>\n";
    htmlTable <<
              "        <td style=\"font-size: 10px; border: none; padding: 8px;\">Conducator laborator</td>\n";
    htmlTable << "    </tr>";
    htmlTable << "    <tr style=\"height: 20px;\">";
    QString checker = ui -> leVerificatorMetrolog -> text();
    QString tehnicalSuperviser = ui -> leConducatorLaborator -> text();
    htmlTable <<
              "        <td style=\"font-size: 10px; border: none; padding: 8px;\">"
              <<
              checker.toStdString() << "</td>";
    htmlTable <<
              "        <td style=\"font-size: 10px; border: none; padding: 8px;\">"
              <<
              tehnicalSuperviser.toStdString() << "</td>\n";
    htmlTable << "    </tr>\n";
    htmlTable << "    <tr style=\"height: 20px;\">";
    htmlTable <<
              "        <td style=\"font-size: 10px; border: none; padding: 8px;\">Semnatura: _________________________________</td>\n";
    htmlTable <<
              "        <td style=\"font-size: 10px; border: none; padding: 8px;\">Semnatura: _________________________________</td>\n";
    htmlTable << "    </tr>\n";
    htmlTable << "</table>";
    htmlTable << "<br\n>";
    htmlTable <<
              "<p style=\"font-size: 10px;\">Prezentul buletin de verificare, impreuna cu mijlocul / mijloacele de masurare verificat/e au fost"
              " predate reprezentantului beneficiarului (nume, prenume, BI/CI, nr. imputernicire) _________________________________"
              "______________________________________________ <br>Data _________________________________ Semnatura ____________________________</p>\n";
    htmlTable << "</body>\n";
    htmlTable << "</html>\n";
    ///////////////////////
    std::string fileNameHtlm = "generated_html_file.html";
    std::ofstream outputFile(fileNameHtlm);
    outputFile << htmlTable.str();
    outputFile.close();
    ///////////////////////
    QDateTime nowPdf = QDateTime::currentDateTime();
    QString fileName = QString(pw -> selectedInfo.pathResults.c_str()) +
                       "/" + QString("BV_") + nowPdf.toString(QLatin1String(
                                   "yyyyMMdd_hhmmss"));
    fileName.append(".pdf");
    // Check if the directory exists, and create it if not
    QDir resultDir(pw -> selectedInfo.pathResults.c_str());
    if (!resultDir.exists())
    {
        resultDir.mkpath(".");
    }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setFullPage(true);
    qreal leftMargin = 5.0;
    qreal rightMargin = 5.0;
    qreal topMargin = 5.0;
    qreal bottomMargin = 5.0;
    printer.setPageMargins(QMarginsF(leftMargin, topMargin, rightMargin,
                                     bottomMargin), QPageLayout::Millimeter);
    // Print HTML to PDF
    QTextDocument outputReport;
    outputReport.setHtml(QString::fromStdString(htmlTable.str()));
    outputReport.setDocumentMargin(0);
    outputReport.print(& printer);
    // Open the generated PDF
    fileName = QString("file:///") + fileName;
    QDesktopServices::openUrl(QUrl(fileName, QUrl::TolerantMode));
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab",
                       QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");
    settings.setValue("numarInregistrare",
                      ui -> leNumarInregistrare ->text());
    settings.setValue("detinator", ui -> leDetinator ->text());
    settings.setValue("codulLt", ui -> leCodulLt -> text());
    settings.setValue("normative", ui -> leNormative -> text());
    settings.setValue("valabilitate",
                      ui -> cbValabilitate ->currentIndex());
    settings.setValue("cost", ui -> leCost -> text());
    settings.setValue("verificatorMetrolog",
                      ui -> leVerificatorMetrolog -> text());
    settings.setValue("conducatorLaborator",
                      ui -> leConducatorLaborator ->text());
    settings.endGroup();
    settings.sync();
    QMessageBox messageBoxVerificationReport;
    messageBoxVerificationReport.setWindowTitle(
        tr("Verification report"));
    messageBoxVerificationReport.setText(tr("The file ") + fileName + tr(
            " was created!"));
    messageBoxVerificationReport.setStandardButtons(QMessageBox::Ok);
    messageBoxVerificationReport.setWindowFlags(Qt::Dialog | Qt::
            CustomizeWindowHint | Qt::WindowTitleHint | Qt::
            WindowCloseButtonHint);
    // Create a QTimer
    QTimer *timer = new QTimer(& messageBoxVerificationReport);
    timer -> setSingleShot(true); // Make the timer a single-shot timer
    timer -> setInterval(
        5000); // Set the interval to 5000 milliseconds (5 seconds)
    // Connect the timeout signal to close the message box
    QObject::connect(timer, & QTimer::timeout, &
                     messageBoxVerificationReport, & QMessageBox::accept);
    // Start the timer
    timer -> start();
    // Show the message box
    messageBoxVerificationReport.exec();
}


void ReportMeasurements::onCloseClicked()
{
    this -> hide();
}


