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

#include "HelpAbout.h"  // Include the header file for HelpAbout dialog

#include <QResizeEvent>    // Include for QResizeEvent override

#include "definitions.h"   // Include project-wide constants and definitions
#include "ui_HelpAbout.h"  // Include the generated UI header file

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
    ui->grAbout->setTitle(tr("About"));

    /**
     * \brief Helper function to set the text of a QLabel.
     *
     * This lambda function sets the translated text of the provided QLabel.
     *
     * \param label Pointer to the QLabel to set the text for.
     * \param text The text to set for the QLabel.
     */
    auto setLabelText = [](QLabel* label, const QString& text) { label->setText(tr(text.toUtf8())); };

    // Application title and description
    setLabelText(ui->lbAppTitle, tr("WStreamLab"));
    setLabelText(ui->lbAppSubtitle, tr("Professional Water Meter Test System"));

    // Description text - note: using "recognized" (correct spelling)
    setLabelText(ui->lbDescription,
        tr("WStreamLab is a professional water meter testing and verification system compliant with recognized standards."));

    // Version information
    setLabelText(ui->lbVersion, tr("Version:"));
    setLabelText(ui->lbVersionValue, QString::fromUtf8(VERSION_BUILD));
    setLabelText(ui->lbPlatform, tr("Platform:"));
    setLabelText(ui->lbPlatformValue, tr("Windows 8.1 or later"));
    setLabelText(ui->lbBuildDate, tr("Build:"));
    setLabelText(ui->lbBuildDateValue, tr("2026-01-02"));
    setLabelText(ui->lbQtVersion, tr("Qt:"));
    setLabelText(ui->lbQtVersionValue, tr("6.7.1"));
    setLabelText(ui->lbLicense, tr("License:"));
    setLabelText(ui->lbLicenseValue, tr("Commercial"));

    // Company information
    setLabelText(ui->lbCompany, tr("Company:"));
    setLabelText(ui->lbCopyright, tr("© 2026 Elcost Company SRL"));

    // Email as clickable link (using app primary color)
    ui->lbEmail->setText(QString("<a href=\"mailto:office@elcost.ro\" style=\"color: #0078D7; text-decoration: none;\">%1</a>")
                         .arg(tr("office@elcost.ro")));

    setLabelText(ui->lbAddress, tr("Pascani, Morilor #8, Romania"));

    // Website as clickable link (using app primary color)
    ui->lbWebsite->setText(QString("<a href=\"https://www.elcost.ro\" style=\"color: #0078D7; text-decoration: none;\">%1</a>")
                           .arg(tr("www.elcost.ro")));

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

    // Load and set application icon (compact size for About dialog)
    QPixmap appIcon(":/WStreamLab.ico");
    if (appIcon.isNull()) {
        // Fallback to window icon if resource not found
        appIcon = windowIcon().pixmap(64, 64);
    }
    ui->lbAppIcon->setPixmap(appIcon.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Configure email and website labels as clickable links
    ui->lbEmail->setTextFormat(Qt::RichText);
    ui->lbEmail->setOpenExternalLinks(true);
    ui->lbWebsite->setTextFormat(Qt::RichText);
    ui->lbWebsite->setOpenExternalLinks(true);

    // Apply minimal styling for title and links (matching app color scheme)
    QString dialogStyle = R"(
        QLabel#lbAppTitle {
            color: #0056b3;  /* Darker blue for better visibility */
            font-weight: bold;
        }
        QLabel#lbAppSubtitle {
            color: #495057;  /* Dark gray for professional look */
            font-weight: 500;
        }
        QLabel#lbDescription {
            color: #6c757d;  /* Medium gray for description */
            font-size: 9pt;  /* Compact font for description to prevent overflow */
        }
        QLabel#lbCompany {
            color: #0078D7;  /* Primary color from app.qss */
            margin-top: 5px;
        }
    )";
    this->setStyleSheet(dialogStyle);

    // Set fixed window size to prevent auto-resizing
    // Use setFixedSize to completely lock the dimensions
    this->setFixedSize(FIXED_WIDTH, FIXED_HEIGHT);

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
