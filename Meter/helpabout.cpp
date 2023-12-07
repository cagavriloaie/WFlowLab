/*
 *  Author: Constantin
 *  File:   helpabout.cpp
 */

#include "helpabout.h"
#include "ui_helpabout.h"
#include "definitions.h"

void HelpAbout::Translate()
{
    this->setWindowTitle(tr("WStreamLab - About"));
    ui->lbName->setText(tr("WStreamLab version:"));
    ui->lbNameValue->setText(VERSION_BUILD);
    ui->lbCopyright->setText(tr("Copyright:"));
    ui->lbCopyrightValue->setText(tr("2023 Elcost Company srl"));
    ui->lbEmail->setText(tr("Email:"));
    ui->lbEmailValue->setText(tr("office@elcost.ro"));
    ui->lbAddress->setText(tr("Address:"));
    ui->lbAddressValue->setText(tr("Pascani / RO Morilor #8"));
    ui->lbAuthor->setText(tr("Author:"));
    ui->lbAuthorValue->setText(tr("constantin"));
    ui->pbClose->setText(tr("&Close"));
}

HelpAbout::HelpAbout(QWidget *parent) : QDialog(parent),
    ui(new Ui::HelpAbout)
{
    ui->setupUi(this);
    Translate();
    connect(ui->pbClose, &QPushButton::clicked, this,
            &HelpAbout::onCloseClicked);
}

HelpAbout::~HelpAbout()
{
    delete ui;
}

void HelpAbout::onCloseClicked()
{
    this->hide();
}
