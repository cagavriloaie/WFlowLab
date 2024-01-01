/*
 *  Author: Constantin
 *  File:   license.cpp
 */

#include "license.h"
#include "mainwindow.h"
#include "ui_license.h"

namespace
{
    MainWindow *mainwindow;
}

void License::Translate()
{
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

License::License(QWidget *parent) : QDialog(parent),
    ui(new Ui::Licence)
{
    ui->setupUi(this);
    mainwindow = dynamic_cast<MainWindow *>(parent);
    Translate();
    connect(ui->pbClose, &QPushButton::clicked, this,
            &License::onCloseClicked);
}

void License::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    ui->lbCompanyValue->setText(QString::fromStdString(
                                    mainwindow->optionsConfiguration["company"]));
    ui->lbCertificateValue->setText(QString::fromStdString(
                                        mainwindow->optionsConfiguration["certificate"]));
    ui->lbArchiveValue->setText(QString::fromStdString(
                                    mainwindow->optionsConfiguration["archive"]));
    ui->lbMaximumValue->setText(QString::fromStdString(
                                    mainwindow->optionsConfiguration["maximum"]));
    ui->lbDensityValue->setText(QString::fromStdString(
                                    mainwindow->optionsConfiguration["density_20"]));
    ui->lbChecksumValue->setText(QString::fromStdString(
                                     mainwindow->optionsConfiguration["control"]));
}

void License::onCloseClicked()
{
    this->hide();
}

License::~License()
{
    delete ui;
}
