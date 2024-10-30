/**
 * \file helpabout.cpp
 * \brief Implementation file for HelpAbout dialog functionality.
 *
 * This file contains the implementation of the HelpAbout class, which provides
 * functionality for displaying help and about information in a dialog window.
 *
 * \author Constantin
 * \date Insert date
 */

#include "helpabout.h"    // Include the header file for HelpAbout dialog
#include "definitions.h"  // Include project-wide constants and definitions
#include "ui_helpabout.h" // Include the generated UI header file

/**
 * \brief Translates and sets the text for the About dialog.
 *
 * This function sets the translated text for various labels and the window title in the About dialog.
 * It ensures that all UI elements display the correct information in the appropriate language.
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
    setLabelText(ui->lbName, "WStreamLab version:");
    setLabelText(ui->lbNameValue, QString::fromUtf8(VERSION_BUILD));
    setLabelText(ui->lbCopyright, "Copyright:");
    setLabelText(ui->lbCopyrightValue, "2024 Elcost Company srl");
    setLabelText(ui->lbEmail, "Email:");
    setLabelText(ui->lbEmailValue, "office@elcost.ro");
    setLabelText(ui->lbAddress, "Address:");
    setLabelText(ui->lbAddressValue, "Pascani / RO Morilor #8");
    setLabelText(ui->lbAuthor, "Author:");
    setLabelText(ui->lbAuthorValue, "constantin");

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
