/**
 * \file helpabout.cpp
 * \brief Implementation of the HelpAbout dialog.
 *
 * Defines the HelpAbout class, which displays application information
 * such as version, author, and contact details in an "About" dialog.
 *
 * \author Constantin
 * \date To be defined
 */

#include "helpabout.h"  // Include the header file for HelpAbout dialog

#include "definitions.h"   // Include project-wide constants and definitions
#include "ui_helpabout.h"  // Include the generated UI header file

/**
 * \brief Updates the About dialog with localized text.
 *
 * Sets the window title and updates all labels in the About dialog
 * to display the appropriate translations according to the current language.
 */
void HelpAbout::Translate() {
    // Retranslate UI elements from .ui file (tooltips, etc.)
    ui->retranslateUi(this);

    // Set window title
    setWindowTitle(tr("WStreamLab - About"));

    // Set group box title
    ui->grAbout->setTitle(tr("About Application"));

    /**
     * \brief Helper function to set the text of a QLabel.
     *
     * This lambda function sets the translated text of the provided QLabel.
     *
     * \param label Pointer to the QLabel to set the text for.
     * \param text The text to set for the QLabel.
     */
    auto setLabelText = [](QLabel* label, const QString& text) { label->setText(tr(text.toUtf8())); };

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
 * \brief Constructs the HelpAbout dialog.
 *
 * Initializes the HelpAbout dialog, sets up the UI, applies translations
 * to display the correct text, and connects the close button to the
 * onCloseClicked slot.
 *
 * \param parent Pointer to the parent QWidget. Defaults to nullptr.
 */
HelpAbout::HelpAbout(QWidget* parent) : QDialog(parent), ui(new Ui::HelpAbout) {
    ui->setupUi(this);
    Translate();  // Call the translation function

    QSize newSize(490, 230);  // New size
    this->resize(newSize);

    // Set initial focus to the close button
    ui->pbClose->setFocus();

    // Connect signals and slots
    connect(ui->pbClose, &QPushButton::clicked, this, &HelpAbout::onCloseClicked);
}

/**
 * \brief Destroys the HelpAbout dialog.
 *
 * Cleans up resources by deleting the `ui` pointer.
 */
HelpAbout::~HelpAbout() {
    delete ui;
}

/**
 * \brief Slot triggered when the close button is clicked.
 *
 * Hides the HelpAbout dialog when the close button is pressed.
 */
void HelpAbout::onCloseClicked() {
    this->hide();
}
