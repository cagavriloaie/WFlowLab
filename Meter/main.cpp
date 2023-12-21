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
#include <QThread>

#include "mainwindow.h"

class PixelImageWidget : public QMainWindow {

public:
    explicit PixelImageWidget(QWidget* parent = nullptr) : QMainWindow(parent) {
        setAttribute(Qt::WA_TranslucentBackground); // Enable transparency
        setWindowFlags(Qt::FramelessWindowHint);    // Remove window frame
        setFixedSize(320, 300);                     // Set the size of the widget

        // Set up a timer to hide the pixel image after five seconds
        QTimer::singleShot(5000, this, &PixelImageWidget::hidePixelImage);
    }

    MainWindow* mainWindow = nullptr;

protected:
     QRect centeredRect(const QSize &outer, const QSize &inner) {
        return QRect((outer.width() - inner.width()) / 2, (outer.height() - inner.height()) / 2, inner.width(), inner.height());
     }

    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);

        // Fill the QPixmap with pixel data (example: gradient from red to blue)
        for (int x = 0; x < width(); ++x) {
            for (int y = 0; y < height(); ++y) {

                int red = static_cast<int>(255 * static_cast<double>(x) / width());
                int green = static_cast<int>(255 * static_cast<double>(y) / height());
                int blue = static_cast<int>(255 * (1 - static_cast<double>(x) / width()));

                painter.setPen(QColor(red, green, blue));
                painter.drawPoint(x, y);
            }
        }

        QFont font;
        font.setPointSize(12);

        painter.setFont(font);

        const QString& message(
            "   >WStreamLab\n"
            "   >Elcost Romania\n"
            "   >Version [1.3 12.23]"
            );

        QRect textRect = QRect(0, 0, width(), height());
        painter.setPen(Qt::white);
        painter.drawText(textRect, Qt::AlignTop, message);
    }

private slots:
    void hidePixelImage() {
        hide();
        showMainWindow();
    }

    void showMainWindow() {
        mainWindow->show();
    }
};

QTranslator *appTranslator;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString key = QString("Constantin + 365566a75ebf0c4a5cbf");
    QSharedMemory *shared = new QSharedMemory(key);
    QString qmPath = qApp->applicationDirPath() + "/translations";
    appTranslator = new QTranslator(nullptr);
    if (appTranslator->load(qmPath + "//meter_ro_RO.qm"))
    {
        qApp->installTranslator(appTranslator);
    }
    QCoreApplication::setOrganizationName("WStreamLab");
    QCoreApplication::setOrganizationDomain("WStreamLab.com");
    QCoreApplication::setApplicationName("WStreamLab");
    if (!shared->create(512, QSharedMemory::ReadWrite))
    {
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
        exit(0);
    }

    MainWindow mainWindow;
    PixelImageWidget widget;
    widget.mainWindow = &mainWindow;
    widget.show();

    return a.exec();
}
