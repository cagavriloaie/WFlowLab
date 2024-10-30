/**
 * \file license.h
 * \brief Declaration of the License class.
 *
 * This file contains the declaration of the License class,
 * which provides functionalities related to managing license information.
 *
 * \author Constantin
 * \date [date]
 */

#ifndef LICENSE_H
#define LICENSE_H

#include <QDialog>

namespace Ui {
class Licence; ///< Forward declaration of Ui::Licence class.
}

/**
 * \brief The License class represents a dialog for displaying license information.
 *
 * This class inherits from QDialog and provides methods to translate UI components,
 * handle the show event, and manage the dialog's lifecycle.
 */
class License : public QDialog {
    Q_OBJECT

  public:
    /**
     * \brief Constructs a License dialog.
     * \param parent Pointer to the parent widget (optional).
     */
    explicit License(QWidget* parent = nullptr);

    /**
     * \brief Destroys the License dialog.
     */
    ~License();

    /**
     * \brief Translates the UI components to the current language.
     *
     * This function sets text for various UI components like labels and buttons
     * based on the current application language settings.
     */
    void Translate();

    Ui::Licence* ui; ///< Pointer to the UI object.

  private slots:
    /**
     * \brief Slot function invoked when the dialog is shown.
     * \param event Show event object.
     *
     * Updates UI elements with data from main window's configuration
     * when the License dialog is shown.
     */
    void showEvent(QShowEvent* event) override;

    /**
     * \brief Slot function invoked when the close button is clicked.
     *
     * Hides the License dialog when the close button is clicked.
     */
    void onCloseClicked();
};

#endif // LICENSE_H
