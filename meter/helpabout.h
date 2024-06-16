/**
 * \file helpabout.h
 * \brief Header file for HelpAbout dialog.
 *
 * This file defines the HelpAbout class, which represents a dialog
 * for displaying help and information about the application.
 *
 * \author Constantin
 */

#ifndef HELPABOUT_H
#define HELPABOUT_H

#include <QDialog>  // Qt class for creating modal or modeless dialogs.

namespace Ui {
class HelpAbout;
}

/**
 * \brief HelpAbout class represents a dialog for displaying Help/About information.
 *
 * This class inherits from QDialog and provides functionality for displaying
 * Help/About information in a dialog window. It includes a slot for handling
 * the close button click event and a method for translating UI elements.
 */
class HelpAbout : public QDialog
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a HelpAbout dialog.
     * \param parent Optional pointer to the parent widget.
     */
    explicit HelpAbout(QWidget *parent = nullptr);

    /**
     * \brief Destructor.
     */
    ~HelpAbout();

    /**
     * \brief Translates UI elements to the current locale.
     *
     * This method translates UI elements such as labels, buttons, and text to the
     * current locale/language set in the application.
     */
    void Translate();

private:
    Ui::HelpAbout *ui; ///< Pointer to the UI object.

private slots:
    /**
     * \brief Slot function called when the close button is clicked.
     *
     * This function handles the close button click event and performs necessary actions
     * when the user wants to close the HelpAbout dialog.
     */
    void onCloseClicked();
};


#endif // HELPABOUT_H
