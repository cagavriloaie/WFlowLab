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

#include "mainwindow.h"
#include "report.h"
#include "ui_report.h"
#include "report.h"  // Duplicate include, consider removing one

extern MainWindow *pw;

#include <QCoreApplication>
#include <QString>
#include <QDebug>

std::string convertNumberToWords(int num, bool addSuffix)
{
    static const std::string units[] = {"", "un", "doua", "trei", "patru", "cinci", "sase", "sapte", "opt", "noua"};
    static const std::string teens[] = {"", "unsprezece", "doisprezece", "treisprezece", "paisprezece", "cincisprezece", "saisprezece", "saptesprezece", "optisprezece", "nouasprezece"};
    static const std::string tens[]  = {"", "", "douazeci", "treizeci", "patruzeci", "cincizeci", "saizeci", "saptezeci", "optzeci", "nouazeci"};
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
            result += " " + convertNumberToWords(num / 100, true) + " sute ";
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

void ReportMeasurements::Translate() {
    this->setWindowTitle(tr("WFlowLab - Checking report"));
    ui->grBoxBuletin->setTitle(tr("Date from verification report"));
    ui->lbBuletinNumber->setText(tr("Verification report:"));
    ui->lbMijlocMasurare->setText(tr("Measuring instrument:"));
    ui->lbCodulLt->setText(tr("LT code:"));
    ui->lbNmlNtm->setText(tr("Ntm, lNtm, other Norm:"));
    ui->lbEtaloane->setText(tr("Used Standards, name, series, no. CE:"));
    ui->lbValabilitate->setText(tr("Valability:"));
    ui->lbChecker->setText(tr("Checker:"));
    ui->lbTehnicalSuperviser->setText(tr("Tehnical superviser:"));
    ui->lbCost->setText(tr("Cost:"));
    ui->cbValability->addItem(tr("6 months"));
    ui->cbValability->addItem(tr("1 year"));
    ui->cbValability->addItem(tr("2 years"));
    ui->cbValability->addItem(tr("3 years"));
    ui->cbValability->addItem(tr("5 years"));
    ui->pbPrint->setText(tr("&PrintPDF"));
    ui->pbClose->setText(tr("&Close"));
}

ReportMeasurements::ReportMeasurements(QWidget *parent,
                                       const std::vector<QCheckBox *> &vectorCheckNumber,
                                       const std::vector<QLineEdit *> &vectorSerialNumber,
                                       const QString resultAllTests[20]):

    QDialog(parent),
    ui(new Ui::report),
    vectorCheckNumberCopy(vectorCheckNumber),
    vectorSerialNumberCopy(vectorSerialNumber)
{
    ui->setupUi(this);
    connect(ui->pbClose, &QPushButton::clicked, this,
            &ReportMeasurements::onCloseClicked);
    connect(ui->pbPrint, &QPushButton::clicked, this,
            &ReportMeasurements::onPrintClicked);
    for (auto iter = 0; iter < 20; ++iter)
    {
        resultAllTestsCopy[iter] = resultAllTests[iter];
    }
    this->setWindowTitle(tr("WFlowLab - Checking report"));
    ui->grBoxBuletin->setTitle(tr("Date from verification report"));
    ui->lbBuletinNumber->setText(tr("Verification report:"));
    ui->lbMijlocMasurare->setText(tr("Measuring instrument:"));
    ui->lbCodulLt->setText(tr("LT code:"));
    ui->lbNmlNtm->setText(tr("Ntm, lNtm, other Norm:"));
    ui->lbEtaloane->setText(tr("Used Standards, name, series, no. CE:"));
    ui->lbValabilitate->setText(tr("Valability:"));
    ui->lbChecker->setText(tr("Checker:"));
    ui->lbTehnicalSuperviser->setText(tr("Tehnical superviser:"));
    ui->lbCost->setText(tr("Cost:"));
    ui->cbValability->addItem(tr("6 months"));
    ui->cbValability->addItem(tr("1 year"));
    ui->cbValability->addItem(tr("2 years"));
    ui->cbValability->addItem(tr("3 years"));
    ui->cbValability->addItem(tr("5 years"));
    ui->pbPrint->setText(tr("&PrintPDF"));
    ui->pbClose->setText(tr("&Close"));
    ui->cbValability->setCurrentIndex(1);
    QDoubleValidator *validatorDoubleNumber = new QDoubleValidator(this);
    ui->leCostRon->setValidator(validatorDoubleNumber);
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab",
                       QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");
    ui->leBuletinNumber->setText(settings.value("buletinNumber",
                                                1).toString());
    ui->leMeansOfMeasurement->setText(settings.value("meansOfMeasurement",
                                                     "Dn20").toString());
    ui->leLtCode->setText(settings.value("ltCode",
                                         "1.06.28.1.1").toString());
    ui->leNmlNtmNorms->setText(settings.value("nmNtmNorms",
                                              1234).toString());
    ui->leUsedSerie->setText(settings.value("usedSerie",
                                            0001).toString());
    ui->cbValability->setCurrentIndex(settings.value("valability",
                                                     0).toInt());
    ui->leUsedSerie->setText(settings.value("usedSerie",
                                            0001).toString());
    ui->leChecker->setText(settings.value("checker",
                                          "Adrian Pintilie").toString());
    ui->leTehnicalSuperviser->setText(settings.value("superviser",
                                                     "Victor Trambu").toString());
    ui->leCostRon->setText(settings.value("costRon", 100).toString());
    ui->leBuletinNumber->setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui->leMeansOfMeasurement->setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui->leLtCode->setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui->leNmlNtmNorms->setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui->leUsedSerie->setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui->cbValability->setStyleSheet(
        "QComboBox { background: rgb(240, 255, 240);color: rgb(0, 0, 0); "
        "selection-background-color: rgb(240, 255, 240); selection-color: "
        "rgb(0, 0, 0);}");
    ui->leChecker->setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui->leTehnicalSuperviser->setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    ui->leCostRon->setStyleSheet(
        "QLineEdit { background: rgb(240, 255, 240); "
        "selection-background-color: rgb(0, 0, 0); }");
    settings.endGroup();
    settings.sync();
}

ReportMeasurements::~ReportMeasurements()
{
    delete ui;
}

void ReportMeasurements::onPrintClicked()
{
    if (
        ui->leBuletinNumber->text().isEmpty() ||
        ui->leMeansOfMeasurement->text().isEmpty() ||
        ui->leLtCode->text().isEmpty() ||
        ui->leNmlNtmNorms->text().isEmpty() ||
        ui->leUsedSerie->text().isEmpty() ||
        ui->leChecker->text().isEmpty() ||
        ui->leTehnicalSuperviser->text().isEmpty() ||
        ui->leCostRon->text().isEmpty()
        )
    {
        QMessageBox messageBoxWindowsTitle;
        messageBoxWindowsTitle.setWindowTitle(tr("Verification report"));
        messageBoxWindowsTitle.setText(tr("There are unfilled fields!"));
        messageBoxWindowsTitle.setStandardButtons(QMessageBox::Ok);
        messageBoxWindowsTitle.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                              Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
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
    std::tm *localTime = std::localtime(&currentTime);
    size_t entriesTable = pw->selectedInfo.entriesNumber;
    QString ltCode = ui->leLtCode->text();
    QString nmlNtmNorms = ui->leNmlNtmNorms->text();
    QString SerieUsed = ui->leUsedSerie->text();
    QString checkValability = ui->cbValability->currentText();
    QString costRon = ui->leCostRon->text();
    std::string companyLaboratory = pw->optionsConfiguration["company"];
    std::stringstream htmlTable;
    // Start building the HTML string
    htmlTable << "<html>\n";
    htmlTable << "<head>\n";
    htmlTable << "  <title>Buletin de verificare metrologica</title>\n";
    htmlTable << "  <style>\n";
    htmlTable <<
        "    p { font-size: 18px; }\n"; // Larger font size for paragraphs
    htmlTable << "<style>";
    htmlTable << "table {";
    htmlTable << "    border-collapse: collapse;";
    htmlTable << "    width: 100%;";
    htmlTable << "}";
    htmlTable << "th, td {";
    htmlTable << "border: 1px solid #dddddd;",
        htmlTable << "    text-align: left;",
        htmlTable << "padding: 8px;";
    htmlTable << "}";
    htmlTable << "th {";
    htmlTable << "    background-color: #f2f2f2;";
    htmlTable << "}";
    htmlTable << "  </style>\n";
    htmlTable << "</head>\n";
    htmlTable << "<body>\n";
    htmlTable <<
        "  <p style=\"font-size: 15px;\"><strong>Biroul Roman de Metrologie Legala</strong></p>\n";
    htmlTable << "  <p style=\"font-size: 12px;\">Laboratorul " <<
        companyLaboratory << "</p>\n";
    htmlTable << "<center>";

    htmlTable <<
        "  <p style=\"font-size: 15px;\">Buletin de verificare metrologica</p>";
    htmlTable <<
        "  <p style=\"font-size: 14x;\">Nr. "<< ui->leBuletinNumber->text().toStdString() << "    ["
              <<  std::put_time(localTime, "%d-%m-%Y %H:%M:%S") << "]</p><br><";

    htmlTable <<
        "  <p style=\"font-size: 14px;\"  style=\"text-align:left;\">Mijloace de masurare apartinand: _____________________________________________________</p>\n";
    htmlTable <<
        "  <p style=\"font-size: 10px;\"  style=\"text-align: left;\">"
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" <<
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" <<
        "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(Agent economic / persoana fizica, adresa, telefon)</p>\n";
    htmlTable <<
        " <p style=\"font-size: 14px;\"  style=\"text-align: left;\">prezentate la verificare metrologica au obtinut urmatoarele rezultate:</p>\n";
    htmlTable << "</center>";
    // Continue building the HTML string with the table
    htmlTable << "<center>";
    htmlTable << "  <table>\n";
    htmlTable << "    <thead>\n";
    htmlTable << "      <tr>\n";
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
    for (size_t row = 0; row < entriesTable; ++row)
    {
        htmlTable << "      <tr style=\"height: 30px;\">\n";
        htmlTable << "        <td>" <<
            vectorSerialNumberCopy[row]->text().toStdString() << "</td>\n";
        htmlTable << "        <td>" << ltCode.toStdString() << "</td>\n";
        htmlTable << "        <td>" << nmlNtmNorms.toStdString() << "</td>\n";
        htmlTable << "        <td>" << SerieUsed.toStdString() << "</td>\n";
        htmlTable << "        <td>" << resultAllTestsCopy[row].toStdString()
                  << "</td>\n";
        htmlTable << "        <td>" << checkValability.toStdString() <<
            "</td>\n";
        htmlTable << "        <td>" << costRon.toStdString() << "</td>\n";
        htmlTable << "      </tr>\n";
    }
    htmlTable << "    </tbody>\n";
    htmlTable << "  </table>\n";
    htmlTable << "</center>";
    std::ostringstream streamObjCost;
    streamObjCost << std::fixed;
    streamObjCost << std::setprecision(2);
    streamObjCost << costRon.toDouble() * entriesTable;
    std::string totalCost = streamObjCost.str();
    std::ostringstream streamObjCostTVA;
    streamObjCostTVA << std::fixed;
    streamObjCostTVA << std::setprecision(2);
    streamObjCostTVA << costRon.toDouble() * entriesTable * 1.19;
    std::string totalCostTVA = streamObjCostTVA.str();
    std::string  totalCostTVALetters = convertNumberToWords(std::stoi(
                                                               totalCostTVA), true);
    // Additional rows at the end of the HTML document
    htmlTable << "  <p style=\"font-size: 10px;\">";
    htmlTable <<
        "  <p style=\"font-size: 10px;\">Locul efectuarii verificarii metrologice: "
              << companyLaboratory << ".</p>\n";
    htmlTable << "  <p style=\"font-size: 10px;\">Costul total al verificarii metrologice fara TVA este " << totalCost << " lei.</p>";
    htmlTable <<
        "  <p style=\"font-size: 10px;\">Costul total al verificarii metrologice cu TVA "
              << totalCostTVA << " ("
              << totalCostTVALetters <<
        ") lei a fost achitat cu numerar / ordin de plata nr.______________________in contul______________________la trezoreria ______________________"
              << "</p>\n";
    htmlTable << "<table width=\"100%\">";
    htmlTable << "<br>";
    htmlTable << "    <tr style=\"height: 20px;\">";
    htmlTable << "        <td style=\"font-size: 10px; border: none; padding: 8px;\">[Verificator metrolog]</td>";
    htmlTable << "        <td style=\"font-size: 10px; border: none; padding: 8px;\">[Conducator laborator]</td>";
    htmlTable << "    </tr>";

    htmlTable << "    <tr style=\"height: 20px;\">";
    QString checker = ui->leChecker->text();
    QString tehnicalSuperviser = ui->leTehnicalSuperviser->text();
    htmlTable << "        <td style=\"font-size: 10px; border: none; padding: 8px;\">Nume, prenume: " << checker.toStdString() << "</td>";
    htmlTable << "        <td style=\"font-size: 10px; border: none; padding: 8px;\">Nume, prenume: " << tehnicalSuperviser.toStdString() << "</td>";
    htmlTable << "    </tr>";

    htmlTable << "    <tr style=\"height: 20px;\">";
    htmlTable <<"        <td style=\"font-size: 10px; border: none; padding: 8px;\">Semnatura: ___________________________</td>";
    htmlTable <<"        <td style=\"font-size: 10px; border: none; padding: 8px;\">Semnatura: ___________________________</td>";
    htmlTable << "    </tr>";

    htmlTable << "</table>";

    htmlTable << "<br>";
    htmlTable << "<p style=\"font-size: 13x;\">Prezentul buletin de verificare, impreuna cu mijlocul / mijloacele de masurare verificat/e a fost"
                  " predat reprezentantului beneficiarului (nume, prenume, BI/CI, nr. imputernicire __________________"
                 "_______________________________________ data __________________ semnatura _______________________</p>";
    htmlTable << "</body>\n";
    htmlTable << "</html>\n";
    QDateTime nowPdf = QDateTime::currentDateTime();
    QString fileName = QString(
                           pw->selectedInfo.pathResults.c_str()) +
                       "/" + QString("BV_") +
                       nowPdf.toString(QLatin1String("yyyyMMdd_hhmmss"));
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
    printer.setPageMargins(QMarginsF(5, 4, 4, 4));
    printer.setColorMode(QPrinter::ColorMode::Color);
    QTextDocument outputReport;
    QString report = QString::fromStdString(htmlTable.str());
    outputReport.setHtml(report);
    outputReport.print(&printer);
    fileName = QString("file:///") + fileName;
    QDesktopServices::openUrl(QUrl(fileName, QUrl::TolerantMode));
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\WStreamLab",
                       QSettings::NativeFormat);
    settings.sync();
    settings.beginGroup("Report");
    settings.setValue("buletinNumber", ui->leBuletinNumber->text());
    settings.setValue("meansOfMeasurement",
                      ui->leMeansOfMeasurement->text());
    settings.setValue("ltCode", ui->leLtCode->text());
    settings.setValue("nmNtmNorms", ui->leNmlNtmNorms->text());
    settings.setValue("usedSerie", ui->leUsedSerie->text());
    settings.setValue("valability", ui->cbValability->currentIndex());
    settings.setValue("checker", ui->leChecker->text());
    settings.setValue("superviser", ui->leTehnicalSuperviser->text());
    settings.setValue("costRon", ui->leCostRon->text());
    settings.endGroup();
    settings.sync();
    QMessageBox messageBoxVerificationReport;
    messageBoxVerificationReport.setWindowTitle(tr("Verification report"));
    messageBoxVerificationReport.setText(tr("The file ") + fileName + tr(" was created!"));
    messageBoxVerificationReport.setStandardButtons(QMessageBox::Ok);
    messageBoxVerificationReport.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                                Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    if (messageBoxVerificationReport.exec() == QMessageBox::Ok)
    {
        messageBoxVerificationReport.close();
    }
}

void ReportMeasurements::onCloseClicked()
{
    this->hide();
}

