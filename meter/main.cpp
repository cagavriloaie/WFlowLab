/**
 * \file main.cpp
 * \brief Main entry point of the application.
 *
 * This file contains the main function, which serves as the entry point
 * for the application. It initializes necessary components and starts
 * the main event loop.
 *
 * \author Constantin
 * \date Insert date
 *
 * \section notes_sec Notes
 *
 *  astyle *.cpp,*.h --style=java --indent=spaces=4 --break-blocks --pad-oper
 *  --pad-comma --pad-paren --align-pointer=name --add-braces --mode=c
 * --recursive
 */

#include <QApplication>  // Qt application handling
#include <QDir>          // Qt directory handling
#include <QEventLoop>    // Qt event loop for event handling
#include <QMessageBox>   // Qt message box for displaying alerts
#include <QPainter>      // Qt painter for drawing operations
#include <QSharedMemory> // Qt class for managing shared memory segments
#include <QString>       // Qt string class
#include <QThread>       // Qt thread management
#include <QTimer>        // Qt timer class for periodic events

#include <fstream>   // File stream operations
#include <windows.h> // Windows API main header
#include <winnt.h>   // Windows NT definitions

#include "mainwindow.h" // Include header for MainWindow class

/**
 * \brief The PixelImageWidget class represents a custom widget that displays
 *        a pixelated image and handles application-specific functionalities.
 */
class PixelImageWidget : public QMainWindow {
  public:
    /**
     * \brief Constructor for PixelImageWidget.
     *
     * Constructs a PixelImageWidget instance with optional parent widget.
     * Initializes the widget with translucent background, frameless window hint,
     * and a fixed size of 400x300 pixels. Sets up a timer to hide the widget after
     * five seconds.
     *
     * \param parent Optional parent widget (default is nullptr).
     */
    explicit PixelImageWidget(QWidget* parent = nullptr)
        : QMainWindow(parent) {
        setAttribute(Qt::WA_TranslucentBackground); // Enable transparency
        setWindowFlags(Qt::FramelessWindowHint);    // Remove window frame
        setFixedSize(400, 300);                     // Set the size of the widget

        // Set up a timer to hide the pixel image after five seconds
        QTimer::singleShot(3000, this, &PixelImageWidget::hidePixelImage);
    }

    MainWindow* mainWindow = nullptr;

  protected:
    /**
     * \brief Calculates the centered rectangle within an outer rectangle.
     *
     * Calculates and returns a QRect that represents a centered rectangle
     * within the given outer and inner sizes.
     *
     * \param outer Size of the outer rectangle.
     * \param inner Size of the inner rectangle.
     * \return QRect representing the centered rectangle.
     */
    QRect centeredRect(const QSize& outer, const QSize& inner) {
        return QRect((outer.width() - inner.width()) / 2,
                     (outer.height() - inner.height()) / 2, inner.width(), inner.height());
    }

    /**
     * \brief Retrieves the path of the executable file.
     *
     * Retrieves the path of the current executable file.
     *
     * \return std::wstring containing the path of the executable.
     */
    std::wstring ExePath() {
        TCHAR buffer[MAX_PATH] = {0};
        GetModuleFileName(NULL, buffer, MAX_PATH);
        std::wstring::size_type pos = std::wstring(buffer).find_last_of(
            L"\\/");
        return std::wstring(buffer).substr(0, pos);
    }

    /**
     * \brief Paints the widget with a gradient and textual information.
     *
     * This method overrides the QWidget::paintEvent and is responsible for painting
     * the widget with a gradient from red to blue across its entire area. It also
     * displays textual information at the top of the widget.
     *
     * \param event The paint event that triggered this method.
     */
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);

        // Fill the QPixmap with pixel data (example: gradient from red to blue)
        for (int x = 0; x < width(); ++x) {
            for (int y = 0; y < height(); ++y) {
                int red   = static_cast<int>(255 * static_cast<double>(x) / width());
                int green = static_cast<int>(255 * static_cast<double>(y) / height());
                int blue  = static_cast<int>(255 * (1 - static_cast<double>(x) / width()));
                painter.setPen(QColor(red, green, blue));
                painter.drawPoint(x, y);
            }
        }

        // Setup font for displaying text
        QFont font;
        font.setFamily("Arial");
        font.setPointSize(12);
        painter.setFont(font);

        // Constructing message to display
        QString message(
            "\n"
            "   > WStreamLab\n"
            "   > Elcost Company\n"
            "   > Ver [1.5 01.25]\n");

        // Reading configuration file for additional company information
        std::wstring                       pathToConfig = ExePath() + L"\\watermeters.conf";
        std::ifstream                      inConfigurationFile(pathToConfig.c_str());
        std::map<std::string, std::string> optionsConfiguration;
        if (inConfigurationFile.is_open()) {
            std::string key;
            while (std::getline(inConfigurationFile, key, '=')) {
                std::string value;
                if (std::getline(inConfigurationFile, value, '>')) {
                    optionsConfiguration[key] = value;
                    std::getline(inConfigurationFile, value);
                }
            }
        }

        // Adding company information to the message
        message += "   > " + optionsConfiguration["company"] + "\n";

        // Drawing the text on the widget
        QRect textRect = QRect(0, 0, width(), height());
        painter.setPen(Qt::white);
        painter.drawText(textRect, Qt::AlignTop, message);
    }

  private slots:
    /**
     * \brief Hides the PixelImageWidget and shows the main window.
     *
     * This slot function hides the PixelImageWidget and then shows the main window
     * associated with this widget.
     */
    void hidePixelImage() {
        hide();           // Hide the PixelImageWidget
        showMainWindow(); // Show the main window
    }

    /**
     * \brief Shows the main window associated with the PixelImageWidget.
     *
     * This slot function shows the main window that is associated with the current
     * PixelImageWidget instance.
     */
    void showMainWindow() {
        mainWindow->show(); // Show the main window
    }
};

/**
 * \brief Global pointer to manage application translations.
 *
 * This pointer is used globally to manage translations for the application.
 * It is initially set to nullptr and later assigned an instance of QTranslator
 * when loading translations.
 */
QTranslator* appTranslator = nullptr;

/**
 * \brief Loads the application translations from a specified path.
 *
 * This function initializes a global QTranslator object (`appTranslator`) with
 * translations loaded from a specified .qm file located in the application's
 * "translations" directory.
 *
 * \return True if the translation loaded successfully, false otherwise.
 */
bool loadTranslations() {
    QString qmPath = qApp->applicationDirPath() + QDir::separator() + "translations";
    appTranslator  = new QTranslator(nullptr);

    if (appTranslator->load(qmPath + QDir::separator() + "meter_ro_RO.qm")) {
        qApp->installTranslator(appTranslator);
        return true; // Translation loaded successfully
    }

    return false;
}

/**
 * \brief Checks and handles multiple instances of the application using shared memory.
 *
 * This function attempts to create a shared memory segment with a given key. If the segment
 * cannot be created, it indicates that another instance of the application is already running
 * and displays a warning message.
 *
 * \param shared Pointer to a QSharedMemory instance for managing shared memory.
 * \return True if another instance is already running, false if this is the first instance.
 */
bool checkAndHandleMultipleInstances(QSharedMemory* shared) {
    // Create a shared memory segment
    if (!shared->create(512, QSharedMemory::ReadWrite)) {
        // Another instance is already running
        QMessageBox warningMessage;
        QApplication::beep();
        warningMessage.addButton(QMessageBox::Ok);
        warningMessage.setWindowTitle(QObject::tr("Warning"));
        warningMessage.setText(QObject::tr("Already running"));
        warningMessage.setInformativeText(
            QObject::tr("More than one instance of the WStreamLab program is "
                        "not permitted."));
        warningMessage.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                                      Qt::WindowTitleHint |
                                      Qt::WindowCloseButtonHint);
        warningMessage.exec();

        return true; // Another instance is running
    }

    return false; // This instance is the first one
}

/**
 * \brief The main entry point of the application.
 * \param argc Number of command-line arguments.
 * \param argv Array of command-line arguments.
 * \return Application exit status.
 */
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // Unique key for shared memory
    QString        key    = QString("Constantin + 365566a75ebf0c4a5cbf");
    QSharedMemory* shared = new QSharedMemory(key);

    // Load translations
    if (loadTranslations()) {
        MainWindow mainWindow;

        // Check if another instance is already running
        if (!checkAndHandleMultipleInstances(shared)) {
            mainWindow.show();
            return a.exec();
        }
    }

    delete shared;
    return 0;
}
