/**
 * \file helpabout.cpp
 * \brief Implementation of the HelpAbout dialog.
 *
 * This file contains the implementation of the HelpAbout class, which
 * displays application information such as version, author, and contact
 * details in an "About" dialog.
 *
 * \author Constantin
 * \date To be defined
 */

#include "helpabout.h"    // Include the header file for HelpAbout dialog
#include "definitions.h"  // Include project-wide constants and definitions
#include "ui_helpabout.h" // Include the generated UI header file

/**
 * \brief Applies translated text to the About dialog.
 *
 * This function sets the window title and updates all labels in the About
 * dialog with localized text, ensuring correct language display.
 */
void HelpAbout::Translate() {
    // Set window title
    setWindowTitle(tr("WStreamLab - About"));

    /**
     * \brief Helper function to set the text of a QLabel.
     *
     * This lambda function sets the translated text of the provided QLabel.
     *
     * \param label Pointer to the QLabel to set the text for.
     * \param text The text to set for the QLabel.
     */
    auto setLabelText = [](QLabel* label, const QString& text) {
        label->setText(tr(text.toUtf8()));
    };

    // Set label texts
    setLabelText(ui->lbName, tr("WStreamLab version:"));
    setLabelText(ui->lbNameValue, QString::fromUtf8(VERSION_BUILD));
    setLabelText(ui->lbCopyright, tr("Copyright:"));
    setLabelText(ui->lbCopyrightValue, tr("© 2026 Elcost Company SRL"));
    setLabelText(ui->lbEmail, tr("Email:"));
    setLabelText(ui->lbEmailValue, tr("office@elcost.ro"));
    setLabelText(ui->lbAddress, tr("Address:"));
    setLabelText(ui->lbAddressValue, tr("Pascani / RO Morilor #8"));
    setLabelText(ui->lbAuthor, tr("Author:"));
    setLabelText(ui->lbAuthorValue, tr("constantin"));


    // Set close button text
    ui->pbClose->setText(tr("&Close"));
}

/**
 * \brief Constructor for the HelpAbout dialog.
 *
 * This constructor initializes the HelpAbout dialog, sets up the user interface, calls the
 * translation function to set the appropriate texts, and connects the close button signal
 * to the onCloseClicked slot.
 *
 * \param parent Pointer to the parent widget. Defaults to nullptr.
 */
HelpAbout::HelpAbout(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::HelpAbout) {
    ui->setupUi(this);
    Translate(); // Call the translation function

    QSize newSize(490, 230); // New size
    this->resize(newSize);

    // Connect signals and slots
    connect(ui->pbClose, &QPushButton::clicked, this, &HelpAbout::onCloseClicked);
}

/**
 * \brief Destructor for the HelpAbout dialog.
 *
 * This destructor cleans up the user interface by deleting the `ui` pointer.
 */
HelpAbout::~HelpAbout() {
    delete ui;
}

/**
 * \brief Slot function to handle the close button click event.
 *
 * This function is called when the close button is clicked. It hides the About dialog.
 */
void HelpAbout::onCloseClicked() {
    this->hide();
}
