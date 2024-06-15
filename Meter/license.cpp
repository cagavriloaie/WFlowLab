/**
 * \file license.cpp
 * \brief Implementation of the License dialog functionality.
 *
 * This file contains the implementation of methods for the License dialog,
 * which displays configuration details retrieved from the main window.
 *
 * \author Constantin
 */

#include "license.h"  // Include the header file for the License dialog class.
#include "mainwindow.h"  // Include the header file for the MainWindow class.
#include "ui_license.h"  // Include the UI header file generated by Qt Designer.

namespace
{
    MainWindow *mainwindow;
}

/**
 * \brief Translates and sets text for UI elements in the License dialog.
 *
 * This function translates and sets the text for various QLabel and QPushButton
 * UI elements in the License dialog using Qt's translation mechanism (tr()).
 * It ensures that all UI elements display text in the appropriate language
 * specified by the application's current locale.
 */
    void License::Translate()
    {
        this->setWindowTitle(tr("WStreamLab - License"));  ///< Set the window title.
        ui->lbCertificate->setText(tr("Certificate:"));  ///< Set text for certificate label.
        ui->lbDensity->setText(tr("Water density at 20 °C:"));  ///< Set text for water density label.
        ui->lbDensityUnit->setText(tr("[kg/m²]"));  ///< Set text for density unit label.
        ui->lbArchive->setText(tr("Archive folder:"));  ///< Set text for archive folder label.
        ui->lbCompany->setText(tr("Company:"));  ///< Set text for company label.
        ui->lbMaximum->setText(tr("Maxim number entries"));  ///< Set text for maximum entries label.
        ui->lbChecksum->setText(tr("Checksum:"));  ///< Set text for checksum label.
        ui->pbClose->setText(tr("Close"));  ///< Set text for close button.
    }

/**
 * \brief Constructs a License dialog.
 *
 * This constructor initializes the License dialog by setting up the user interface
 * defined in Ui::License. It performs translation of UI elements and connects the
 * close button click signal to the onCloseClicked slot.
 *
 * \param parent Pointer to the parent widget.
 */
    License::License(QWidget *parent) : QDialog(parent),
        ui(new Ui::Licence)
    {
        ui->setupUi(this);  ///< Set up the user interface.
        mainwindow = dynamic_cast<MainWindow *>(parent);  ///< Cast parent to MainWindow pointer.
        Translate();  ///< Translate UI elements.

        // Connect close button click signal to onCloseClicked slot
        connect(ui->pbClose, &QPushButton::clicked, this,
                &License::onCloseClicked);
    }


/**
 * \brief Event handler for when the License dialog is shown.
 *
 * This function overrides QWidget::showEvent(event) to update the displayed values
 * based on the options configuration stored in the MainWindow instance. It sets the
 * text of several QLabel widgets with specific keys from the options configuration,
 * converting them from std::string to QString.
 *
 * \param event Show event object.
 */
    void License::showEvent(QShowEvent *event)
    {
        QWidget::showEvent(event);  ///< Call base class showEvent.

        // Update UI elements with values from MainWindow's options configuration
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

/**
 * \brief Slot function to handle the close button clicked signal.
 *
 * This function is connected to the clicked signal of the close button (pbClose).
 * It hides the License dialog when the close button is clicked by calling hide().
 */
    void License::onCloseClicked()
    {
        this->hide();  ///< Hide the License dialog.
    }

/**
 * \brief Destructor for the License dialog.
 *
 * Deletes the user interface object (ui) associated with the License dialog.
 * This ensures that resources allocated for the user interface are properly freed
 * when the License dialog is destroyed.
 */
    License::~License()
    {
        delete ui;  ///< Delete the user interface object.
    }

