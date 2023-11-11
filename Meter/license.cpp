#include "license.h"
#include "mainwindow.h"
#include "ui_license.h"

namespace {
MainWindow *mainwindow;
}

void License::Translate() {
    this->setWindowTitle(tr("WStreamLab - License"));
    ui->lbCertificate->setText(tr("Certificate:"));
    ui->lbDensity->setText(tr("Water density at 20 °C:"));
        ui->lbDensityUnit->setText(tr("[kg/m²]"));
        ui->lbArchive->setText(tr("Archive folder:"));
    ui->lbCompany->setText(tr("Company:"));
    ui->lbMaximum->setText(tr("Maxim number entries"));
    ui->lbChecksum->setText(tr("Checksum:"));
    ui->pbClose->setText(tr("Close"));
}

License::License(QWidget *parent) : QDialog(parent), ui(new Ui::Licence) {
    ui->setupUi(this);
    mainwindow = dynamic_cast<MainWindow *>(parent);
    Translate();
    connect(ui->pbClose, &QPushButton::clicked, this, &License::onCloseClicked);
}

void License::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    mainwindow->optionsConfiguration["company"];
    mainwindow->optionsConfiguration["certificate"];
    mainwindow->optionsConfiguration["archive"];
    mainwindow->optionsConfiguration["maximum"];
    mainwindow->optionsConfiguration["density_20"];
    mainwindow->optionsConfiguration["control"];
    ui->lbCompanyValue->setText(
        mainwindow->optionsConfiguration["company"].c_str());
    ui->lbCertificateValue->setText(
        mainwindow->optionsConfiguration["certificate"].c_str());
    ui->lbArchiveValue->setText(
        mainwindow->optionsConfiguration["archive"].c_str());
    ui->lbMaximumValue->setText(
        mainwindow->optionsConfiguration["maximum"].c_str());
    ui->lbDensityValue->setText(
        mainwindow->optionsConfiguration["density_20"].c_str());
    ui->lbChecksumValue->setText(
        mainwindow->optionsConfiguration["control"].c_str());
}

void License::onCloseClicked() { this->hide(); }

License::~License() { delete ui; }
