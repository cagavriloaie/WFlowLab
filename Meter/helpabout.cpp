/*
 *  Author: Constantin
 *  File:   helpabout.cpp
 */

#include "helpabout.h"
#include "ui_helpabout.h"
#include "definitions.h"

void HelpAbout::Translate()
{
    // Set window title
    setWindowTitle(tr("WStreamLab - About"));

    // Helper function to set label text
    auto setLabelText = [](QLabel *label, const QString &text) {
        label->setText(tr(text.toUtf8()));
    };

    // Set label texts
    setLabelText(ui->lbName, "WStreamLab version:");
    setLabelText(ui->lbNameValue, QString::fromUtf8(VERSION_BUILD));
    setLabelText(ui->lbCopyright, "Copyright:");
    setLabelText(ui->lbCopyrightValue, "2023 Elcost Company srl");
    setLabelText(ui->lbEmail, "Email:");
    setLabelText(ui->lbEmailValue, "office@elcost.ro");
    setLabelText(ui->lbAddress, "Address:");
    setLabelText(ui->lbAddressValue, "Pascani / RO Morilor #8");
    setLabelText(ui->lbAuthor, "Author:");
    setLabelText(ui->lbAuthorValue, "constantin");

    // Set close button text
    ui->pbClose->setText(tr("&Close"));
}


HelpAbout::HelpAbout(QWidget *parent) : QDialog(parent),
    ui(new Ui::HelpAbout)
{
    ui->setupUi(this);
    Translate(); // Call the translation function

    // Connect signals and slots
    connect(ui->pbClose, &QPushButton::clicked, this, &HelpAbout::onCloseClicked);
}

HelpAbout::~HelpAbout()
{
    delete ui;
}

void HelpAbout::onCloseClicked()
{
    this->hide();
}
