/*
 *  Author: Constantin
 *  File:   main.cpp
 *
 *  astyle *.cpp,*.h --style=java --indent=spaces=4 --break-blocks --pad-oper
 *  --pad-comma --pad-paren --align-pointer=name --add-braces --mode=c
 * --recursive
 */

#include <QApplication>
#include <QMessageBox>
#include <QSharedMemory>
#include <QString>
#include <QTimer>
#include <QPainter>
#include <QEventLoop>
#include <QDir>
#include <QThread>

#include <windows.h>
#include <winnt.h>
#include <fstream>

#include "mainwindow.h"

class PixelImageWidget : public QMainWindow
{
  public:
    explicit PixelImageWidget(QWidget *parent = nullptr) : QMainWindow(
            parent)
    {
        setAttribute(Qt::WA_TranslucentBackground); // Enable transparency
        setWindowFlags(Qt::FramelessWindowHint);    // Remove window frame
        setFixedSize(400,
                     300);                     // Set the size of the widget
        // Set up a timer to hide the pixel image after five seconds
        QTimer::singleShot(3000, this, &PixelImageWidget::hidePixelImage);
    }

    MainWindow *mainWindow = nullptr;

  protected:
    QRect centeredRect(const QSize &outer, const QSize &inner)
    {
        return QRect((outer.width() - inner.width()) / 2,
                     (outer.height() - inner.height()) / 2, inner.width(), inner.height());
    }

    std::wstring ExePath()
    {
        TCHAR buffer[MAX_PATH] = { 0 };
        GetModuleFileName(NULL, buffer, MAX_PATH);
        std::wstring::size_type pos = std::wstring(buffer).find_last_of(
                                          L"\\/");
        return std::wstring(buffer).substr(0, pos);
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        // Fill the QPixmap with pixel data (example: gradient from red to blue)
        for (int x = 0; x < width(); ++x)
        {
            for (int y = 0; y < height(); ++y)
            {
                int red = static_cast<int>(255 * static_cast<double>(x) / width());
                int green = static_cast<int>(255 * static_cast<double>(y) / height());
                int blue = static_cast<int>(255 * (1 - static_cast<double>
                                                   (x) / width()));
                painter.setPen(QColor(red, green, blue));
                painter.drawPoint(x, y);
            }
        }
        QFont font;
        font.setFamily("Arial");
        font.setPointSize(12);
        painter.setFont(font);
        QString message(
            "\n"
            "   > WStreamLab\n"
            "   > Elcost Romania\n"
            "   > Ver [1.2 12.23]\n"
        );
        std::wstring pathToConfig = ExePath() + L"\\watermeters.conf";
        std::ifstream inConfigurationFile(pathToConfig.c_str());
        std::map<std::string, std::string> optionsConfiguration;
        if (inConfigurationFile.is_open())
        {
            std::string key;
            while (std::getline(inConfigurationFile, key, '='))
            {
                std::string value;
                if (std::getline(inConfigurationFile, value, '>'))
                {
                    optionsConfiguration[key] = value;
                    std::getline(inConfigurationFile, value);
                }
            }
        }
        message += "   > " + optionsConfiguration["company"] + "\n";
        QRect textRect = QRect(0, 0, width(), height());
        painter.setPen(Qt::white);
        painter.drawText(textRect, Qt::AlignTop, message);
    }

  private slots:
    void hidePixelImage()
    {
        hide();
        showMainWindow();
    }

    void showMainWindow()
    {
        mainWindow->show();
    }
};

QTranslator *appTranslator = nullptr; // Declare the translator globally

bool loadTranslations() {
    QString qmPath = qApp->applicationDirPath() + QDir::separator() + "translations";
    appTranslator = new QTranslator(nullptr);

    if (appTranslator->load(qmPath + QDir::separator() + "meter_ro_RO.qm")) {
        qApp->installTranslator(appTranslator);
        return true; // Translation loaded successfully
    }

    return false;
}

bool checkAndHandleMultipleInstances(QSharedMemory *shared) {
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

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Unique key for shared memory
    QString key = QString("Constantin + 365566a75ebf0c4a5cbf");
    QSharedMemory *shared = new QSharedMemory(key);

    // Load translations
    if (loadTranslations()) {
        MainWindow mainWindow;

        // Check if another instance is already running
        if (!checkAndHandleMultipleInstances(shared)) {
            //This has to be revisited
            //PixelImageWidget widget;
            //widget.mainWindow = &mainWindow;
            //widget.show();

            mainWindow.show();

            return a.exec();
        }
    }

    delete shared;

    return 0;
}
