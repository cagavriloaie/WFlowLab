#include "helpabout.h"
#include "ui_helpabout.h"

void HelpAbout::Translate (  ) {
    this->setWindowTitle ( tr ( "WFlowLab - About" ) );
    ui->lbName->setText ( tr ( "WFlowLab version:" ) );
    ui->lbNameValue->setText ( tr ( "1.0 Windows x86_64" ) );
    ui->lbCopyright->setText ( tr ( "Copyright:" ) );
    ui->lbCopyrightValue->setText ( tr ( "2023 ACR Technology" ) );
    ui->lbEmail->setText ( tr ( "Email:" ) );
    ui->lbEmailValue->setText ( tr ( "office@acr-tech.ro" ) );
    ui->lbAddress->setText ( tr ( "Address:" ) );
    ui->lbAddressValue->setText ( tr ( "Pascani / RO Morilor #8" ) );
    ui->lbAuthor->setText ( tr ( "Author:" ) );
    ui->lbAuthorValue->setText ( tr ( "Constantin Agavriloaie" ) );
    ui->pbClose->setText ( tr ( "Close" ) );
}

HelpAbout::HelpAbout ( QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::HelpAbout ) {
    ui->setupUi ( this );

    Translate();

    connect ( ui->pbClose, &QPushButton::clicked, this, &HelpAbout::onCloseClicked );
}

HelpAbout::~HelpAbout() {
    delete ui;
}

void HelpAbout::onCloseClicked() {
    this->hide();
}

