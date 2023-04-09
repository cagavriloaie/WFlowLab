/*
 *  Author: Constantin
 *
 *  astyle /*.cpp,*.h --style=java --indent=spaces=4 --break-blocks --pad-oper
 *  --pad-comma --pad-paren --align-pointer=name --add-braces --mode=c --recursive
 */

#include "mainwindow.h"
#include <QString>
#include <QSharedMemory>
#include <QMessageBox>

#include <QApplication>

QTranslator *appTranslator;

int main ( int argc, char *argv[] ) {
    QApplication a ( argc, argv );
    QString key = QString ( "Constantin + 365566a75ebf0c4a5cbf" );

    QSharedMemory *shared = new QSharedMemory ( key );

    QString qmPath = qApp->applicationDirPath() + "/translations";
    appTranslator = new QTranslator ( nullptr );

    if ( appTranslator->load ( qmPath + "/romanian.qm" ) ) {
        qApp->installTranslator ( appTranslator );
    }

    QCoreApplication::setOrganizationName ( "WStreamLab" );
    QCoreApplication::setOrganizationDomain ( "WStreamLab.com" );
    QCoreApplication::setApplicationName ( "WStreamLab" );

    if ( ! shared->create ( 512, QSharedMemory::ReadWrite ) ) {
        QMessageBox warningMessage;

        QApplication::beep();

        warningMessage.addButton ( QMessageBox::Ok );
        warningMessage.setWindowTitle ( QObject::tr ( "Warning" ) );

        warningMessage.setText ( QObject::tr ( "Already running" ) );
        warningMessage.setInformativeText ( QObject::tr ( "More than one instance of the WFlowLab program is not permitted." ) );

        warningMessage.setWindowFlags ( Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

        warningMessage.exec();

        exit ( 0 );
    }

    MainWindow w;
    w.show();

    return a.exec();
}
