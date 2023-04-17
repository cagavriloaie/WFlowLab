/*
 *  Author: Constantin
 */

#include "tableBoard.h"
#include "ui_dialog.h"

#include <QValidator>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QDesktopServices>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>
#include <iomanip>
#include <fstream>
#include <thread>
#include <string.h>
#include <iostream>
#include <algorithm>

#include "mainwindow.h"
#include "air-density.h"

constexpr size_t MAX_ENTRIES {20};

extern MainWindow *pw;

namespace
{
MainWindow *mainwindow;
}

QString Dialog::report;


void Dialog::printPdfThread ( QString report )
    {
    QDateTime now = QDateTime::currentDateTime();
    QString fileName = QString ( mainwindow->selectedInfo.pathResults.c_str() ) + "/" + QString ( "WStreamLab_" ) +
                       now.toString ( QLatin1String ( "dd-MM-yyyy_hh_mm_ss" ) );
    fileName.append ( ".pdf" );

    QPrinter printer ( QPrinter::PrinterResolution );
    printer.setOutputFormat ( QPrinter::PdfFormat );
    printer.setOutputFileName ( fileName );
    printer.setPageSize ( QPageSize::A4 );
    printer.setFullPage ( true );
    printer.setPageMargins ( QMarginsF ( 5, 4, 4, 4 ) );
    printer.setColorMode ( QPrinter::ColorMode::Color );
    QTextDocument outputReport;
    outputReport.setHtml ( report );
    outputReport.print ( &printer );
    fileName = QString ( "file:///" ) + fileName;
    QDesktopServices::openUrl ( QUrl ( fileName, QUrl::TolerantMode ) );
    }

void Dialog::onSaveCurrentInputDataClicked()
    {
    size_t entries = mainwindow->selectedInfo.entriesNumber;

    QDateTime now = QDateTime::currentDateTime();
    QString fileName = QString ( mainwindow->selectedInfo.pathResults.c_str() ) + "/inputData/" + QString ( "WStreamLab_" ) +
                       now.toString ( QLatin1String ( "dd-MM-yyyy_hh_mm_ss" ) );
    fileName.append ( ".in" );

    std::ofstream outputDataFile ( fileName.toStdString() );

    outputDataFile << mainwindow->selectedInfo.entriesNumber << "\n";
    outputDataFile << mainwindow->selectedInfo.nameWaterMeter << "\n";

    outputDataFile << mainwindow->selectedInfo.ambientTemperature << "\n";
    outputDataFile << mainwindow->selectedInfo.relativeAirHumidity << "\n";
    outputDataFile << mainwindow->selectedInfo.athmosphericPressure << "\n";

    outputDataFile << mainwindow->selectedInfo.rbVolumetric << "\n";
    outputDataFile << mainwindow->selectedInfo.rbGravitmetric << "\n";

    outputDataFile << mainwindow->selectedInfo.rbManual << "\n";
    outputDataFile << mainwindow->selectedInfo.rbInterface << "\n";
    outputDataFile << mainwindow->selectedInfo.rbTerminal << "\n";

    for ( size_t iter = 0; iter < entries; ++iter )
        {
        outputDataFile << vectorSerialNumber[iter]->text().toStdString() << "\n";
        outputDataFile << vectorFirstIndexStart[iter]->text().toStdString() << "\n";
        outputDataFile << vectorFirstIndexStop[iter]->text().toStdString() << "\n";
        outputDataFile << vectorSecondIndexStart[iter]->text().toStdString() << "\n";
        outputDataFile << vectorSecondIndexStop[iter]->text().toStdString() << "\n";
        outputDataFile << vectorThirdIndexStart[iter]->text().toStdString() << "\n";
        outputDataFile << vectorThirdIndexStop[iter]->text().toStdString() << "\n";
        }

    outputDataFile << ui->leMass1->text().toStdString() << "\n";
    outputDataFile << ui->leTemperature1->text().toStdString() << "\n";
    outputDataFile << ui->leMass2->text().toStdString() << "\n";
    outputDataFile << ui->leTemperature2->text().toStdString() << "\n";
    outputDataFile << ui->leMass3->text().toStdString() << "\n";
    outputDataFile << ui->leTemperature3->text().toStdString() << "\n";

    QMessageBox messageBox;
    messageBox.setWindowTitle ( tr ( "Save input data" ) );
    messageBox.setText ( "The file " + fileName + " was created!" );
    messageBox.setStandardButtons ( QMessageBox::Ok );
    messageBox.setWindowFlags ( Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

    if ( messageBox.exec() == QMessageBox::Ok )
        {
        messageBox.close();
        }
    }

void Dialog::onOpenInputDataClicked()
    {
    QString fileName = QFileDialog::getOpenFileName (
                           this, \
                           tr ( "Open Input Data" ), QString ( mainwindow->selectedInfo.pathResults.c_str() ) + \
                           "/inputData/", tr ( "Input data (*.in);;All file (*.*)" ) );

    std::ifstream inputDataFile ( fileName.toStdString() );

    size_t entriesNumber;
    std::string nameWaterMeter;
    double ambientTemperature;
    double relativeAirHumidity;
    double athmosphericPressure;
    bool rbVolumetric;
    bool rbGravitmetric;
    bool rbManual;
    bool rbInterface;
    bool rbTerminal;

    std::string tmpInput;
    inputDataFile >> entriesNumber;
    std::getline ( inputDataFile, tmpInput );
    std::getline ( inputDataFile, nameWaterMeter );
    inputDataFile >> ambientTemperature;
    inputDataFile >> relativeAirHumidity;
    inputDataFile >> athmosphericPressure;
    inputDataFile >> rbVolumetric;
    inputDataFile >> rbGravitmetric;
    inputDataFile >> rbManual;
    inputDataFile >> rbInterface;
    inputDataFile >> rbTerminal;

    int index = mainwindow->ui->cbNumberOfWaterMeters->findText ( std::to_string ( entriesNumber ).c_str() );

    if ( index != -1 )
        {
        mainwindow->ui->cbNumberOfWaterMeters->setCurrentIndex ( index );
        }

    index = mainwindow->ui->cbWaterMeterType->findText ( nameWaterMeter.c_str() );

    if ( index != -1 )
        {
        mainwindow->ui->cbWaterMeterType->setCurrentIndex ( index );
        }

    mainwindow->ui->leTemperature->setText ( std::to_string ( ambientTemperature ).c_str() );
    mainwindow->ui->leHumidity->setText ( std::to_string ( relativeAirHumidity ).c_str() );
    mainwindow->ui->lePressure->setText ( std::to_string ( athmosphericPressure ).c_str() );

    if ( rbVolumetric )
        {
        mainwindow->ui->rbVolumetric->setChecked ( true );
        }

    if ( rbGravitmetric )
        {
        mainwindow->ui->rbGravitmetric->setChecked ( true );
        }

    if ( rbManual )
        {
        mainwindow->ui->rbManual->setChecked ( true );
        }

    if ( rbInterface )
        {
        mainwindow->ui->rbInterface->setChecked ( true );
        }

    std::getline ( inputDataFile, tmpInput );

    for ( size_t iter = 0; iter < entries; ++iter )
        {

        std::getline ( inputDataFile, tmpInput );
        vectorSerialNumber[iter]->setText ( tmpInput.c_str() );

        std::getline ( inputDataFile, tmpInput );
        vectorFirstIndexStart[iter]->setText ( tmpInput.c_str() );

        std::getline ( inputDataFile, tmpInput );
        vectorFirstIndexStop[iter]->setText ( tmpInput.c_str() );

        std::getline ( inputDataFile, tmpInput );
        vectorSecondIndexStart[iter]->setText ( tmpInput.c_str() );

        std::getline ( inputDataFile, tmpInput );
        vectorSecondIndexStop[iter]->setText ( tmpInput.c_str() );

        std::getline ( inputDataFile, tmpInput );
        vectorThirdIndexStart[iter]->setText ( tmpInput.c_str() );

        std::getline ( inputDataFile, tmpInput );
        vectorThirdIndexStop[iter]->setText ( tmpInput.c_str() );

        }

    std::getline ( inputDataFile, tmpInput );
    ui->leMass1->setText ( tmpInput.c_str() );

    std::getline ( inputDataFile, tmpInput );
    ui->leTemperature1->setText ( tmpInput.c_str() );

    std::getline ( inputDataFile, tmpInput );
    ui->leMass2->setText ( tmpInput.c_str() );

    std::getline ( inputDataFile, tmpInput );
    ui->leTemperature2->setText ( tmpInput.c_str() );

    std::getline ( inputDataFile, tmpInput );
    ui->leMass3->setText ( tmpInput.c_str() );

    std::getline ( inputDataFile, tmpInput );
    ui->leTemperature3->setText ( tmpInput.c_str() );
    }

std::string precision_2 ( double number )
    {
    int decimal_part = ( number * 100 ) - ( ( int ) number * 100 );

    if ( decimal_part > 10 )
        {
        return std::to_string ( ( int ) number ) + "." + std::to_string ( decimal_part );
        }
    else
        {
        return std::to_string ( ( int ) number ) + ".0" + std::to_string ( decimal_part );
        }
    }

bool XOR ( bool a, bool b )
    {
    return ( a + b ) % 2;
    }

void Dialog::ValidatorInput()
    {
    QLabel *pNumber[] =
        {
        ui->lbN1,   ui->lbN2,   ui->lbN3,   ui->lbN4,   ui->lbN5,
        ui->lbN6,   ui->lbN7,   ui->lbN8,   ui->lbN9,   ui->lbN10,
        ui->lbN11,  ui->lbN12,  ui->lbN13,  ui->lbN14,  ui->lbN15,
        ui->lbN16,  ui->lbN17,  ui->lbN18,  ui->lbN19,  ui->lbN20
        };
    vectorNumber.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorNumber.push_back ( pNumber[iter] );
        }

    QCheckBox *pCheckNumber[] =
        {
        ui->cbSet1,     ui->cbSet2,     ui->cbSet3,     ui->cbSet4,     ui->cbSet5,
        ui->cbSet6,     ui->cbSet7,     ui->cbSet8,     ui->cbSet9,     ui->cbSet10,
        ui->cbSet11,    ui->cbSet12,    ui->cbSet13,    ui->cbSet14,    ui->cbSet15,
        ui->cbSet16,    ui->cbSet17,    ui->cbSet18,    ui->cbSet19,    ui->cbSet20,
        };
    vectorCheckNumber.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorCheckNumber.push_back ( pCheckNumber[iter] );
        pCheckNumber[iter]->installEventFilter ( this );
        }

    QLineEdit *pSerialNumber[] =
        {
        ui->leSN1,  ui->leSN2,  ui->leSN3,  ui->leSN4,  ui->leSN5,
        ui->leSN6,  ui->leSN7,  ui->leSN8,  ui->leSN9,  ui->leSN10,
        ui->leSN11, ui->leSN12, ui->leSN13, ui->leSN14, ui->leSN15,
        ui->leSN16, ui->leSN17, ui->leSN18, ui->leSN19, ui->leSN20
        };
    vectorSerialNumber.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorSerialNumber.push_back ( pSerialNumber[iter] );
        pSerialNumber[iter]->installEventFilter ( this );
        }

    QLineEdit  *pFirstIndexStart[] =
        {
        ui->leStart1_1,  ui->leStart1_2,  ui->leStart1_3,  ui->leStart1_4,  ui->leStart1_5,
        ui->leStart1_6,  ui->leStart1_7,  ui->leStart1_8,  ui->leStart1_9,  ui->leStart1_10,
        ui->leStart1_11, ui->leStart1_12, ui->leStart1_13, ui->leStart1_14, ui->leStart1_15,
        ui->leStart1_16, ui->leStart1_17, ui->leStart1_18, ui->leStart1_19, ui->leStart1_20
        };
    vectorFirstIndexStart.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorFirstIndexStart.push_back ( pFirstIndexStart[iter] );
        pFirstIndexStart[iter]->installEventFilter ( this );
        }

    QLineEdit    *pFirstIndexStop[] =
        {
        ui->leStop1_1,  ui->leStop1_2,  ui->leStop1_3,  ui->leStop1_4,  ui->leStop1_5,
        ui->leStop1_6,  ui->leStop1_7,  ui->leStop1_8,  ui->leStop1_9,  ui->leStop1_10,
        ui->leStop1_11, ui->leStop1_12, ui->leStop1_13, ui->leStop1_14, ui->leStop1_15,
        ui->leStop1_16, ui->leStop1_17, ui->leStop1_18, ui->leStop1_19, ui->leStop1_20
        };
    vectorFirstIndexStop.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorFirstIndexStop.push_back ( pFirstIndexStop[iter] );
        pFirstIndexStop[iter]->installEventFilter ( this );
        }

    QLineEdit    *pFirstError[] =
        {
        ui->leError1_1,     ui->leError1_2,     ui->leError1_3,     ui->leError1_4,     ui->leError1_5,
        ui->leError1_6,     ui->leError1_7,     ui->leError1_8,     ui->leError1_9,     ui->leError1_10,
        ui->leError1_11,    ui->leError1_12,    ui->leError1_13,    ui->leError1_14,    ui->leError1_15,
        ui->leError1_16,    ui->leError1_17,    ui->leError1_18,    ui->leError1_19,    ui->leError1_20
        };
    vectorFirstError.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorFirstError.push_back ( pFirstError[iter] );
        }

    QLineEdit  *pSecondIndexStart[] =
        {
        ui->leStart2_1,  ui->leStart2_2,  ui->leStart2_3,  ui->leStart2_4,  ui->leStart2_5,
        ui->leStart2_6,  ui->leStart2_7,  ui->leStart2_8,  ui->leStart2_9,  ui->leStart2_10,
        ui->leStart2_11, ui->leStart2_12, ui->leStart2_13, ui->leStart2_14, ui->leStart2_15,
        ui->leStart2_16, ui->leStart2_17, ui->leStart2_18, ui->leStart2_19, ui->leStart2_20
        };
    vectorSecondIndexStart.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorSecondIndexStart.push_back ( pSecondIndexStart[iter] );
        pSecondIndexStart[iter]->installEventFilter ( this );
        }

    QLineEdit  *pSecondIndexStop[] =
        {
        ui->leStop2_1,  ui->leStop2_2,  ui->leStop2_3,  ui->leStop2_4,  ui->leStop2_5,
        ui->leStop2_6,  ui->leStop2_7,  ui->leStop2_8,  ui->leStop2_9,  ui->leStop2_10,
        ui->leStop2_11, ui->leStop2_12, ui->leStop2_13, ui->leStop2_14, ui->leStop2_15,
        ui->leStop2_16, ui->leStop2_17, ui->leStop2_18, ui->leStop2_19, ui->leStop2_20
        };
    vectorSecondIndexStop.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorSecondIndexStop.push_back ( pSecondIndexStop[iter] );
        pSecondIndexStop[iter]->installEventFilter ( this );
        }

    QLineEdit  *pSecondError[] =
        {
        ui->leError2_1,     ui->leError2_2,     ui->leError2_3,     ui->leError2_4,     ui->leError2_5,
        ui->leError2_6,     ui->leError2_7,     ui->leError2_8,     ui->leError2_9,     ui->leError2_10,
        ui->leError2_11,    ui->leError2_12,    ui->leError2_13,    ui->leError2_14,    ui->leError2_15,
        ui->leError2_16,    ui->leError2_17,    ui->leError2_18,    ui->leError2_19,    ui->leError2_20
        };
    vectorSecondError.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorSecondError.push_back ( pSecondError[iter] );
        }

    QLineEdit  *pThirdIndexStart[] =
        {
        ui->leStart3_1,  ui->leStart3_2,  ui->leStart3_3,  ui->leStart3_4,  ui->leStart3_5,
        ui->leStart3_6,  ui->leStart3_7,  ui->leStart3_8,  ui->leStart3_9,  ui->leStart3_10,
        ui->leStart3_11, ui->leStart3_12, ui->leStart3_13, ui->leStart3_14, ui->leStart3_15,
        ui->leStart3_16, ui->leStart3_17, ui->leStart3_18, ui->leStart3_19, ui->leStart3_20
        };
    vectorThirdIndexStart.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorThirdIndexStart.push_back ( pThirdIndexStart[iter] );
        pThirdIndexStart[iter]->installEventFilter ( this );
        }

    QLineEdit  *pThirdIndexStop[] =
        {
        ui->leStop3_1,  ui->leStop3_2,  ui->leStop3_3,  ui->leStop3_4,  ui->leStop3_5,
        ui->leStop3_6,  ui->leStop3_7,  ui->leStop3_8,  ui->leStop3_9,  ui->leStop3_10,
        ui->leStop3_11, ui->leStop3_12, ui->leStop3_13, ui->leStop3_14, ui->leStop3_15,
        ui->leStop3_16, ui->leStop3_17, ui->leStop3_18, ui->leStop3_19, ui->leStop3_20
        };
    vectorThirdIndexStop.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorThirdIndexStop.push_back ( pThirdIndexStop[iter] );
        pThirdIndexStop[iter]->installEventFilter ( this );
        }

    QLineEdit  *pThirdError[] =
        {
        ui->leError3_1,     ui->leError3_2,     ui->leError3_3,     ui->leError3_4,     ui->leError3_5,
        ui->leError3_6,     ui->leError3_7,     ui->leError3_8,     ui->leError3_9,     ui->leError3_10,
        ui->leError3_11,    ui->leError3_12,    ui->leError3_13,    ui->leError3_14,    ui->leError3_15,
        ui->leError3_16,    ui->leError3_17,    ui->leError3_18,    ui->leError3_19,    ui->leError3_20
        };
    vectorThirdError.clear();

    for ( size_t iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        vectorThirdError.push_back ( pThirdError[iter] );
        }

    ui->cbSet->installEventFilter ( this );

    ui->pbCalculate->installEventFilter ( this );
    ui->pbClean->installEventFilter ( this );
    ui->pbClose->installEventFilter ( this );
    ui->pbOpen->installEventFilter ( this );
    ui->pbPrint->installEventFilter ( this );
    ui->pbSave->installEventFilter ( this );

    ui->leVolume1->installEventFilter ( this );
    ui->leVolume2->installEventFilter ( this );
    ui->leVolume3->installEventFilter ( this );

    ui->leMass1->installEventFilter ( this );
    ui->leMass2->installEventFilter ( this );
    ui->leMass3->installEventFilter ( this );

    ui->leTemperature1->installEventFilter ( this );
    ui->leTemperature2->installEventFilter ( this );
    ui->leTemperature3->installEventFilter ( this );

    QRegularExpression rx ( "\\b[A-Z0-9.-]*",
                            QRegularExpression::CaseInsensitiveOption );
    auto validatorAlphanumeric = new QRegularExpressionValidator ( rx, this );
    QDoubleValidator *validatorDoubleNumber = new QDoubleValidator ( this );

    // set natural numbers as input for SN input line
    for ( auto iter = begin ( vectorSerialNumber ); iter != end ( vectorSerialNumber ); ++iter )
        {
        ( *iter )->setValidator ( validatorAlphanumeric );
        }

    // set natural numbers as input for minimal flow input line
    for ( auto iter = begin ( vectorFirstIndexStart ); iter != end ( vectorFirstIndexStart ); ++iter )
        {
        ( *iter )->setValidator ( validatorDoubleNumber );
        }

    for ( auto iter = begin ( vectorFirstIndexStop ); iter != end ( vectorFirstIndexStop ); ++iter )
        {
        ( *iter )->setValidator ( validatorDoubleNumber );
        }

    ui->leMass1->setValidator ( validatorDoubleNumber );
    ui->leTemperature1->setValidator ( validatorDoubleNumber );

    // set natural numbers as input for transient flow input line
    for ( auto iter = begin ( vectorSecondIndexStart ); iter != end ( vectorSecondIndexStart ); ++iter )
        {
        ( *iter )->setValidator ( validatorDoubleNumber );
        }

    for ( auto iter = begin ( vectorSecondIndexStop ); iter != end ( vectorSecondIndexStop ); ++iter )
        {
        ( *iter )->setValidator ( validatorDoubleNumber );
        }

    ui->leMass2->setValidator ( validatorDoubleNumber );
    ui->leTemperature2->setValidator ( validatorDoubleNumber );

    // set natural numbers as input for nominal flow input line
    for ( auto iter = begin ( vectorThirdIndexStart ); iter != end ( vectorThirdIndexStart ); ++iter )
        {
        ( *iter )->setValidator ( validatorDoubleNumber );
        }

    for ( auto iter = begin ( vectorThirdIndexStop ); iter != end ( vectorThirdIndexStop ); ++iter )
        {
        ( *iter )->setValidator ( validatorDoubleNumber );
        }

    ui->leMass3->setValidator ( validatorDoubleNumber );
    ui->leTemperature3->setValidator ( validatorDoubleNumber );

    for ( auto iter = begin ( vectorFirstError ); iter != end ( vectorFirstError ); ++iter )
        {
        ( *iter )->setReadOnly ( true );
        }

    for ( auto iter = begin ( vectorSecondError ); iter != end ( vectorSecondError ); ++iter )
        {
        ( *iter )->setReadOnly ( true );
        }

    for ( auto iter = begin ( vectorThirdError ); iter != end ( vectorThirdError ); ++iter )
        {
        ( *iter )->setReadOnly ( true );
        }

    ui->leMass1->show();
    ui->leMass2->show();
    ui->leMass2->show();
    ui->lbTemperature1->show();
    ui->lbTemperature2->show();
    ui->lbTemperature3->show();
    ui->leVolume1->setReadOnly ( true );
    ui->leVolume2->setReadOnly ( true );
    ui->leVolume3->setReadOnly ( true );

    QPalette paletteDiactivatedLineEdit;
    paletteDiactivatedLineEdit.setColor ( QPalette::Base, QColor ( 220, 235, 220, 255 ) );

    ui->leVolume1->setStyleSheet ( "QLineEdit {background-color: rgb(235, 235, 235)}" );
    ui->leVolume2->setStyleSheet ( "QLineEdit {background-color: rgb(235, 235, 235)}" );
    ui->leVolume3->setStyleSheet ( "QLineEdit {background-color: rgb(235, 235, 235)}" );

    for ( auto iter = begin ( vectorCheckNumber ); iter != end ( vectorCheckNumber ); ++iter )
        {
        ( *iter )->setCheckState ( Qt::Checked );
        }

    ui->cbSet->setCheckState ( Qt::Checked );
    }

void Dialog::Translate ()
    {
    this->setWindowTitle ( tr ( "WStreamLab - Input Table" ) );
    ui->lbN1->setText ( "01" );
    ui->lbN2->setText ( "02" );
    ui->lbN3->setText ( "03" );
    ui->lbN4->setText ( "04" );
    ui->lbN5->setText ( "05" );
    ui->lbN6->setText ( "06" );
    ui->lbN7->setText ( "07" );
    ui->lbN8->setText ( "08" );
    ui->lbN9->setText ( "09" );
    ui->lbN10->setText ( "10" );
    ui->lbN11->setText ( "11" );
    ui->lbN12->setText ( "12" );
    ui->lbN13->setText ( "13" );
    ui->lbN14->setText ( "14" );
    ui->lbN15->setText ( "15" );
    ui->lbN16->setText ( "16" );
    ui->lbN17->setText ( "17" );
    ui->lbN18->setText ( "18" );
    ui->lbN19->setText ( "19" );
    ui->lbN20->setText ( "20" );

    ui->lbSN->setText ( "S / N" );

    ui->lbIndex1->setText ( tr ( "Index" ) );
    ui->lbStart1->setText ( tr ( "Start" ) );
    ui->lbStop1->setText ( tr ( "Stop" ) );
    ui->lbError1->setText ( tr ( "Err Qmin" ) );

    ui->lbIndex2->setText ( tr ( "Index" ) );
    ui->lbStart2->setText ( tr ( "Start" ) );
    ui->lbStop2->setText ( tr ( "Stop" ) );
    ui->lbError2->setText ( tr ( "Err Qt" ) );

    ui->lbIndex3->setText ( tr ( "Index" ) );
    ui->lbStart3->setText ( tr ( "Start" ) );
    ui->lbStop3->setText ( tr ( "Stop" ) );
    ui->lbError3->setText ( tr ( "Err Qn" ) );

    ui->lbMass1->setText ( tr ( "Mass [kg]" ) );
    ui->lbTemperature1->setText ( tr ( "Temperature [\302\260C]" ) );
    ui->lbVolume1->setText ( tr ( "Volume [L]" ) );
    ui->lbMass2->setText ( tr ( "Mass [kg]" ) );
    ui->lbTemperature2->setText ( tr ( "Temperature [\302\260C]" ) );
    ui->lbVolume2->setText ( tr ( "Volume [L]" ) );
    ui->lbMass3->setText ( tr ( "Mass [kg]", nullptr ) );
    ui->lbTemperature3->setText ( tr ( "Temperature [\302\260C]" ) );
    ui->lbVolume3->setText ( tr ( "Volume [L]", nullptr ) );

    ui->pbPrint->setText ( tr ( "&Print PDF" ) );
    ui->pbOpen->setText ( tr ( "&Open" ) );
    ui->pbSave->setText ( tr ( "&Save" ) );
    ui->pbCalculate->setText ( tr ( "Check it out" ) );
    ui->pbClean->setText ( tr ( "Clean &Input" ) );
    ui->pbClose->setText ( tr ( "&Close" ) );

    ui->lbIndex1->setText ( QString ( "Index [L] -  Qmin: %1  [L/h]  Err: %2 %" ).arg ( QString::number ( minimumFlowMain ) ).arg ( QString::number ( maximumError ) ) );
    ui->lbIndex2->setText ( QString ( "Index [L] -  Qt:  %1  [L/h]  Err: % 2%" ).arg ( QString::number ( transitoriuFlowMain ) ).arg ( QString::number ( nominalError ) ) );
    ui->lbIndex3->setText ( QString ( "Index [L] -  Qn: %1  [L/h]  Err: %2 %" ).arg ( QString::number ( nominalFlowMain ) ).arg ( QString::number ( nominalError ) ) );
    }

Dialog::Dialog ( QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::Dialog )

    {
    //mainwindow = dynamic_cast<MainWindow *> ( parent );
    mainwindow = pw;
    ui->setupUi ( this );

    setWindowFlags ( Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint | Qt::Dialog | Qt::WindowTitleHint );
    Translate();

    ValidatorInput();

    connect ( ui->pbCalculate, &QPushButton::clicked, this, &Dialog::onCalculateClicked );
    connect ( ui->pbClean, &QPushButton::clicked, this, &Dialog::onCleanClicked );
    connect ( ui->pbClose, &QPushButton::clicked, this, &Dialog::onCloseClicked );
    connect ( ui->pbSave, &QPushButton::clicked, this, &Dialog::onSaveCurrentInputDataClicked );
    connect ( ui->pbOpen, &QPushButton::clicked, this, &Dialog::onOpenInputDataClicked );
    connect ( ui->pbPrint, &QPushButton::clicked, this, &Dialog::onPrintPdfDocClicked );


    connect ( ui->cbSet, &QCheckBox::stateChanged, this, &Dialog::onSelectAllChanged );

    for ( unsigned iter = 0; iter < MAX_ENTRIES; ++iter )
        {
        connect ( vectorCheckNumber[iter], SIGNAL ( clicked ( bool ) ), this, SLOT ( onCbClicked ( bool ) ) );
        }

    }

Dialog::~Dialog()
    {
    delete ui;
    }

void Dialog::onCleanClicked()
    {
    for ( unsigned iter = 0; iter <  entries; ++iter )
        {
        vectorSerialNumber[iter]->clear();
        vectorFirstIndexStart[iter]->clear();
        vectorFirstIndexStop[iter]->clear();
        vectorFirstError[iter]->clear();
        vectorSecondIndexStart[iter]->clear();
        vectorSecondIndexStop[iter]->clear();
        vectorSecondError[iter]->clear();
        vectorThirdIndexStart[iter]->clear();
        vectorThirdIndexStop[iter]->clear();
        vectorThirdError[iter]->clear();
        }

    ui->leTemperature1->clear();
    ui->leTemperature2->clear();
    ui->leTemperature3->clear();
    ui->leMass1->clear();
    ui->leMass2->clear();
    ui->leMass3->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();
    }

void Dialog::onCalculateClicked()
    {

    //double nominalError = mainwindow->selectedInfo.nominalError;
    //double maximumError = mainwindow->selectedInfo.maximumError;

    QPalette paletteOddRowErr;
    paletteOddRowErr.setColor ( QPalette::Base, QColor ( 220, 235, 220, 255 ) );
    QPalette paletteEvenRowErr;
    paletteEvenRowErr.setColor ( QPalette::Base, QColor ( 235, 235, 235, 255 ) );

    QPalette paletteNormal;
    paletteNormal.setColor ( QPalette::Base, QColor ( 250, 250, 250, 255 ) );
    QPalette paletteErr;
    paletteErr.setColor ( QPalette::Base, QColor ( 245, 220, 220, 255 ) );

    bool result{true};

    if ( mainwindow->selectedInfo.rbGravitmetric == true )
        {

        bool result_t1{true}, result_t2{true}, result_t3{true};
        bool result_m1{true}, result_m2{true}, result_m3{true};

        double tmp {0};

        double temperatureFirst {0};
        double temperatureSecond {0};
        double temperatureThird {0};

        bool bConvert ( false );

        // Temperature for minimal flow
        tmp = ui->leTemperature1->text().toDouble ( &bConvert );
        ui->leTemperature1->setPalette ( paletteNormal );

        if ( bConvert )
            {
            temperatureFirst = tmp;

            if ( temperatureFirst < 0 || temperatureFirst > 100 )
                {
                ui->leTemperature1->setPalette ( paletteErr );
                result_t1 = false;
                }
            }
        else
            {
            ui->leTemperature1->setPalette ( paletteErr );
            temperatureFirst = 20;
            result_t1 = false;
            }

        // Temperature for transitoriu flow
        tmp = ui->leTemperature2->text().toDouble ( &bConvert );
        ui->leTemperature2->setPalette ( paletteNormal );

        if ( bConvert )
            {
            temperatureSecond = tmp;

            if ( temperatureSecond < 0 || temperatureSecond > 100 )
                {
                ui->leTemperature2->setPalette ( paletteErr );
                result_t2 = false;
                }
            }
        else
            {
            ui->leTemperature2->setPalette ( paletteErr );
            temperatureSecond = 20;
            result_t2 = false;
            }

        // Temperature for nominal flow
        tmp = ui->leTemperature3->text().toDouble ( &bConvert );
        ui->leTemperature3->setPalette ( paletteNormal );

        if ( bConvert )
            {
            temperatureThird = tmp;

            if ( temperatureThird < 0 || temperatureThird > 100 )
                {
                ui->leTemperature3->setPalette ( paletteErr );
                result_t3 = false;
                }
            }
        else
            {
            ui->leTemperature3->setPalette ( paletteErr );
            temperatureThird = 20;
            result_t3 = false;
            }

        double massFirst {0};
        double massSecond {0};
        double massThird {0};

        // Mass for minimal flow
        tmp = ui->leMass1->text().toDouble ( &bConvert );
        ui->leMass1->setPalette ( paletteNormal );

        if ( bConvert )
            {
            massFirst = tmp;

            if ( massFirst < 0 )
                {
                ui->leMass1->setPalette ( paletteErr );
                massFirst = 100;
                result_m1 = false;
                }
            }
        else
            {
            ui->leMass1->setPalette ( paletteErr );
            massFirst = 100;
            result_m1 = false;
            }

        // Mass for transitoriu flow
        tmp = ui->leMass2->text().toDouble ( &bConvert );
        ui->leMass2->setPalette ( paletteNormal );

        if ( bConvert )
            {
            massSecond = tmp;

            if ( massSecond < 0 )
                {
                ui->leMass2->setPalette ( paletteErr );
                massSecond = 100;
                result_m2 = false;
                }
            }
        else
            {
            ui->leMass2->setPalette ( paletteErr );
            massSecond = 100;
            result_m2 = false;
            }

        // Mass for nominal flow
        tmp = ui->leMass3->text().toDouble ( &bConvert );
        ui->leMass3->setPalette ( paletteNormal );

        if ( bConvert )
            {
            massThird = tmp;

            if ( massThird < 0 )
                {
                ui->leMass3->setPalette ( paletteErr );
                massThird = 100;
                result_m3 = false;
                }
            }
        else
            {
            ui->leMass3->setPalette ( paletteErr );
            massThird = 100;
            result_m3 = false;
            }

        double densityFirst {0};
        double densitySecond {0};
        double densityThird {0};

        double correction = mainwindow->selectedInfo.density_20;

        densityFirst = quadraticInterpolationTemperature ( temperatureFirst, correction );
        densitySecond = quadraticInterpolationTemperature ( temperatureSecond, correction );
        densityThird = quadraticInterpolationTemperature ( temperatureThird, correction );

        double VolumeFirst = 1000 * massFirst / densityFirst;
        double VolumeSecond = 1000 * massSecond / densitySecond;
        double VolumeThird =  1000 * massThird / densityThird;

        std::ostringstream streamObj;

        if ( VolumeFirst > 0 && result_t1 && result_m1 )
            {
            streamObj.str ( "" );
            streamObj << std::fixed << std::setprecision ( 4 ) << VolumeFirst;
            ui->leVolume1->setText ( streamObj.str().c_str() );
            }

        if (  VolumeSecond > 0 && result_t2 && result_m2  )
            {
            streamObj.str ( "" );
            streamObj << std::fixed << std::setprecision ( 4 ) << VolumeSecond;
            ui->leVolume2->setText ( streamObj.str().c_str() );
            }

        if ( VolumeThird > 0 && result_t3 && result_m3 )
            {
            streamObj.str ( "" );
            streamObj << std::fixed << std::setprecision ( 4 ) << VolumeThird;
            ui->leVolume3->setText ( streamObj.str().c_str() );
            }

        /// Q minim
        if ( VolumeFirst > 0 && result_t1 && result_m1 )
            for ( unsigned iter = 0; iter <  entries; ++iter )
                {

                double start {0};
                bool bStart {false};

                double stop {0};
                bool bStop {false};

                tmp = vectorFirstIndexStart[iter]->text().toDouble ( &bConvert );

                if ( bConvert )
                    {
                    bStart = true;
                    start = tmp;
                    }
                else
                    {
                    start = 0;
                    }

                tmp = vectorFirstIndexStop[iter]->text().toDouble ( &bConvert );

                if ( bConvert )
                    {
                    bStop = true;
                    stop = tmp;
                    }
                else
                    {
                    stop = 0;
                    }

                if ( bStart && bStop && ( start >= 0 ) && ( stop >= 0 ) && ( stop >= start ) )
                    {
                    double error = ( stop - start - VolumeFirst ) / VolumeFirst * 100;
                    streamObj.str ( "" );
                    streamObj << std::fixed << std::setprecision ( 2 ) << error;
                    vectorFirstError[iter]->setText ( streamObj.str().c_str() );

                    if ( abs ( error ) > maximumError )
                        {
                        vectorFirstError[iter]->setStyleSheet ( "QLineEdit { color: red }" );
                        }
                    else
                        {
                        vectorFirstError[iter]->setStyleSheet ( "QLineEdit { color: black }" );
                        }

                    if ( iter % 4 == 0 || iter % 4 == 1 )
                        {
                        vectorFirstError[iter]->setPalette ( paletteOddRowErr );
                        }
                    else
                        {
                        vectorFirstError[iter]->setPalette ( paletteEvenRowErr );
                        }
                    }
                }

        /// Q transitor
        if ( VolumeSecond > 0 && result_t2 && result_m2 )
            for ( unsigned iter = 0; iter <  entries; ++iter )
                {

                double start {0};
                bool bStart {false};

                double stop {0};
                bool bStop {false};

                tmp = vectorSecondIndexStart[iter]->text().toDouble ( &bConvert );

                if ( bConvert )
                    {
                    bStart = true;
                    start = tmp;
                    }
                else
                    {
                    start = 0;
                    }

                tmp = vectorSecondIndexStop[iter]->text().toDouble ( &bConvert );

                if ( bConvert )
                    {
                    bStop = true;
                    stop = tmp;
                    }
                else
                    {
                    stop = 0;
                    }

                if ( bStart && bStop && ( start >= 0 ) && ( stop >= 0 ) && ( stop >= start ) )
                    {
                    double error = ( stop - start - VolumeSecond ) / VolumeSecond * 100;
                    streamObj.str ( "" );
                    streamObj << std::fixed << std::setprecision ( 2 ) << error;
                    vectorSecondError[iter]->setText ( streamObj.str().c_str() );

                    if ( abs ( error ) > nominalError )
                        {
                        vectorSecondError[iter]->setStyleSheet ( "QLineEdit { color: red }" );
                        }
                    else
                        {
                        vectorSecondError[iter]->setStyleSheet ( "QLineEdit { color: black }" );
                        }

                    if ( iter % 4 == 0 || iter % 4 == 1 )
                        {
                        vectorSecondError[iter]->setPalette ( paletteOddRowErr );
                        }
                    else
                        {
                        vectorSecondError[iter]->setPalette ( paletteEvenRowErr );
                        }
                    }
                }

        /// Q nominal
        if ( VolumeThird > 0 && result_t3 && result_m3 )
            for ( unsigned iter = 0; iter <  entries; ++iter )
                {

                double start {0};
                bool bStart {false};

                double stop {0};
                bool bStop {false};

                tmp = vectorThirdIndexStart[iter]->text().toDouble ( &bConvert );

                if ( bConvert )
                    {
                    bStart = true;
                    start = tmp;
                    }
                else
                    {
                    start = 0;
                    }

                tmp = vectorThirdIndexStop[iter]->text().toDouble ( &bConvert );

                if ( bConvert )
                    {
                    bStop = true;
                    stop = tmp;
                    }
                else
                    {
                    stop = 0;
                    }

                if ( bStart && bStop && ( start >= 0 ) && ( stop >= 0 ) && ( stop >= start ) )
                    {
                    double error = ( stop - start - VolumeThird ) / VolumeThird * 100;
                    streamObj.str ( "" );
                    streamObj << std::fixed << std::setprecision ( 2 ) << error;
                    vectorThirdError[iter]->setText ( streamObj.str().c_str() );

                    if ( abs ( error ) > nominalError )
                        {
                        vectorThirdError[iter]->setStyleSheet ( "QLineEdit { color: red }" );
                        }
                    else
                        {
                        vectorThirdError[iter]->setStyleSheet ( "QLineEdit { color: black }" );
                        }

                    if ( iter % 4 == 0 || iter % 4 == 1 )
                        {
                        vectorThirdError[iter]->setPalette ( paletteOddRowErr );
                        }
                    else
                        {
                        vectorThirdError[iter]->setPalette ( paletteEvenRowErr );
                        }
                    }
                }

        result = result_t1 && result_m1 &&
                 result_t2 && result_m2 &&
                 result_t3 && result_m3;
        }
    else
        {

        double tmp {0};

        double volumeFirst {0};
        double volumeSecond {0};
        double volumeThird {0};

        bool bConvert ( false );

        // Volume for minimal flow
        tmp = ui->leVolume1->text().toDouble ( &bConvert );

        if ( bConvert )
            {
            volumeFirst = tmp;

            if ( volumeFirst < 0 )
                {
                ui->leVolume1->setPalette ( paletteErr );
                volumeFirst = 100;
                result = false;
                }
            }
        else
            {
            ui->leVolume1->setPalette ( paletteErr );
            volumeFirst = 100;
            result = false;
            }

        // Volume for transitoriu flow
        tmp = ui->leVolume2->text().toDouble ( &bConvert );

        if ( bConvert )
            {
            volumeSecond = tmp;

            if ( volumeSecond < 0 )
                {
                ui->leVolume2->setPalette ( paletteErr );
                volumeSecond = 100;
                result = false;
                }
            }
        else
            {
            ui->leVolume2->setPalette ( paletteErr );
            volumeSecond = 100;
            result = false;
            }

        // Volume for nominal flow
        tmp = ui->leVolume3->text().toDouble ( &bConvert );

        if ( bConvert )
            {
            volumeThird = tmp;

            if ( volumeThird < 0 )
                {
                ui->leVolume3->setPalette ( paletteErr );
                volumeThird = 100;
                result = false;
                }
            }
        else
            {
            ui->leVolume3->setPalette ( paletteErr );
            volumeThird = 100;
            result = false;
            }

        std::ostringstream streamObj;

        /// Q minim
        for ( unsigned iter = 0; iter <  entries; ++iter )
            {

            double start {0};
            bool bStart {false};

            double stop {0};
            bool bStop {false};

            tmp = vectorFirstIndexStart[iter]->text().toDouble ( &bConvert );

            if ( bConvert )
                {
                bStart = true;
                start = tmp;
                }
            else
                {
                start = 0;
                }

            tmp = vectorFirstIndexStop[iter]->text().toDouble ( &bConvert );

            if ( bConvert )
                {
                bStop = true;
                stop = tmp;
                }
            else
                {
                stop = 0;
                }

            if ( bStart && bStop && ( start >= 0 ) && ( stop >= 0 ) && ( stop >= start ) )
                {

                double error = ( stop - start - volumeFirst ) / volumeFirst * 100;
                streamObj.str ( "" );
                streamObj << std::fixed << std::setprecision ( 2 ) << error;
                vectorFirstError[iter]->setText ( streamObj.str().c_str() );

                if ( abs ( error ) > maximumError )
                    {
                    vectorFirstError[iter]->setStyleSheet ( "QLineEdit { color: red }" );
                    }
                else
                    {
                    vectorFirstError[iter]->setStyleSheet ( "QLineEdit { color: black }" );
                    }

                if ( iter % 4 == 0 || iter % 4 == 1 )
                    {
                    vectorFirstError[iter]->setPalette ( paletteOddRowErr );
                    }
                else
                    {
                    vectorFirstError[iter]->setPalette ( paletteEvenRowErr );
                    }
                }
            }

        /// Q transition
        for ( unsigned iter = 0; iter <  entries; ++iter )
            {

            double start {0};
            bool bStart {false};

            double stop {0};
            bool bStop {false};

            tmp = vectorSecondIndexStart[iter]->text().toDouble ( &bConvert );

            if ( bConvert )
                {
                bStart = true;
                start = tmp;
                }
            else
                {
                start = 0;
                }

            tmp = vectorSecondIndexStop[iter]->text().toDouble ( &bConvert );

            if ( bConvert )
                {
                bStop = true;
                stop = tmp;
                }
            else
                {
                stop = 0;
                }

            if ( bStart && bStop && ( start >= 0 ) && ( stop >= 0 ) && ( stop >= start ) )
                {

                double error = ( stop - start - volumeSecond ) / volumeSecond * 100;
                streamObj.str ( "" );
                streamObj << std::fixed << std::setprecision ( 2 ) << error;
                vectorSecondError[iter]->setText ( streamObj.str().c_str() );

                if ( abs ( error ) > maximumError )
                    {
                    vectorSecondError[iter]->setStyleSheet ( "QLineEdit { color: red }" );
                    }
                else
                    {
                    vectorSecondError[iter]->setStyleSheet ( "QLineEdit { color: black }" );
                    }

                if ( iter % 4 == 0 || iter % 4 == 1 )
                    {
                    vectorSecondError[iter]->setPalette ( paletteOddRowErr );
                    }
                else
                    {
                    vectorSecondError[iter]->setPalette ( paletteEvenRowErr );
                    }
                }
            }

        /// Q nominal
        for ( unsigned iter = 0; iter <  entries; ++iter )
            {

            double start {0};
            bool bStart {false};

            double stop {0};
            bool bStop {false};

            tmp = vectorThirdIndexStart[iter]->text().toDouble ( &bConvert );

            if ( bConvert )
                {
                bStart = true;
                start = tmp;
                }
            else
                {
                start = 0;
                }

            tmp = vectorThirdIndexStop[iter]->text().toDouble ( &bConvert );

            if ( bConvert )
                {
                bStop = true;
                stop = tmp;
                }
            else
                {
                stop = 0;
                }

            if ( bStart && bStop && ( start >= 0 ) && ( stop >= 0 ) && ( stop >= start ) )
                {

                double error = ( stop - start - volumeThird ) / volumeThird * 100;
                streamObj.str ( "" );
                streamObj << std::fixed << std::setprecision ( 2 ) << error;
                vectorThirdError[iter]->setText ( streamObj.str().c_str() );

                if ( abs ( error ) > maximumError )
                    {
                    vectorThirdError[iter]->setStyleSheet ( "QLineEdit { color: red }" );
                    }
                else
                    {
                    vectorThirdError[iter]->setStyleSheet ( "QLineEdit { color: black }" );
                    }

                if ( iter % 4 == 0 || iter % 4 == 1 )
                    {
                    vectorThirdError[iter]->setPalette ( paletteOddRowErr );
                    }
                else
                    {
                    vectorThirdError[iter]->setPalette ( paletteEvenRowErr );
                    }
                }
            }
        }

    if ( !result )
        {
        QMessageBox messageInputData;
        messageInputData.setWindowTitle ( tr ( "Collected data from flow meters." ) );
        messageInputData.setText ( tr ( "Some user input data are not available or are outside the normal rage!" ) );
        messageInputData.setStandardButtons ( QMessageBox::Ok );
        messageInputData.setWindowFlags ( Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

        if ( messageInputData.exec() == QMessageBox::Ok )
            {
            messageInputData.close();
            }
        }
    }

void Dialog::onCloseClicked()
    {
    this->hide();
    }

void Dialog::onTypeMeterChanged()
    {
    PopulateTable();
    }

void Dialog::onNumberOfWaterMetersChanged()
    {
    PopulateTable();
    }

void Dialog::onCbClicked ( bool checked )
    {

    QObject *obj = sender();

    QCheckBox *checkBox = dynamic_cast<QCheckBox *> ( obj );

    auto iter = std::find ( vectorCheckNumber.begin(), vectorCheckNumber.end(), checkBox );

    if ( iter != vectorCheckNumber.end() )
        {

        auto index = std::distance ( vectorCheckNumber.begin(), iter );

        if ( checked )
            {
            vectorSerialNumber[index]->setDisabled ( false );
            vectorFirstIndexStart[index]->setDisabled ( false );
            vectorFirstIndexStop[index]->setDisabled ( false );
            vectorSecondIndexStart[index]->setDisabled ( false );
            vectorSecondIndexStop[index]->setDisabled ( false );
            vectorThirdIndexStart[index]->setDisabled ( false );
            vectorThirdIndexStop[index]->setDisabled ( false );
            }
        else
            {
            vectorSerialNumber[index]->setDisabled ( true );
            vectorFirstIndexStart[index]->setDisabled ( true );
            vectorFirstIndexStop[index]->setDisabled ( true );
            vectorSecondIndexStart[index]->setDisabled ( true );
            vectorSecondIndexStop[index]->setDisabled ( true );
            vectorThirdIndexStart[index]->setDisabled ( true );
            vectorThirdIndexStop[index]->setDisabled ( true );
            }
        }
    }


void Dialog::onSelectAllChanged()
    {
    if ( ui->cbSet->checkState() == Qt::Checked )
        {
        for ( auto iter = begin ( vectorCheckNumber ); iter != end ( vectorCheckNumber ); ++iter )
            {
            ( *iter )->setCheckState ( Qt::Checked );
            }
        }
    else
        {
        for ( auto iter = begin ( vectorCheckNumber ); iter != end ( vectorCheckNumber ); ++iter )
            {
            ( *iter )->setCheckState ( Qt::Unchecked );
            }
        }
    }

bool Dialog::eventFilter ( QObject *target, QEvent *event )
    {
    if ( event->type() == QEvent::KeyPress )
        {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *> ( event );

        if ( keyEvent->key() == Qt::Key_Enter ||  keyEvent->key() == Qt::Key_Return )
            {
            focusNextChild();
            return true;
            }
        }

    return QDialog::eventFilter ( target, event );
    }

void Dialog::onMeasurementTypeChanged()
    {
    if ( mainwindow->selectedInfo.rbGravitmetric == true )
        {

        ui->leMass1->show();
        ui->leMass2->show();
        ui->leMass3->show();
        ui->lbMass1->show();
        ui->lbMass2->show();
        ui->lbMass3->show();

        ui->lbTemperature1->show();
        ui->lbTemperature2->show();
        ui->lbTemperature3->show();
        ui->leTemperature1->show();
        ui->leTemperature2->show();
        ui->leTemperature3->show();

        ui->leVolume1->setReadOnly ( true );
        ui->leVolume2->setReadOnly ( true );
        ui->leVolume3->setReadOnly ( true );

        QPalette paletteDiactivatedLineEdit;
        paletteDiactivatedLineEdit.setColor ( QPalette::Base, QColor ( 220, 235, 220, 255 ) );

        ui->leVolume1->setStyleSheet ( "QLineEdit {background-color: rgb(235, 235, 235)}" );
        ui->leVolume2->setStyleSheet ( "QLineEdit {background-color: rgb(235, 235, 235)}" );
        ui->leVolume3->setStyleSheet ( "QLineEdit {background-color: rgb(235, 235, 235)}" );
        }
    else
        {
        ui->leMass1->hide();
        ui->leMass2->hide();
        ui->leMass3->hide();
        ui->lbMass1->hide();
        ui->lbMass2->hide();
        ui->lbMass3->hide();

        ui->lbTemperature1->hide();
        ui->lbTemperature2->hide();
        ui->lbTemperature3->hide();
        ui->leTemperature1->hide();
        ui->leTemperature2->hide();
        ui->leTemperature3->hide();

        setAttribute ( Qt::WA_InputMethodEnabled );
        ui->leVolume1->setReadOnly ( false );
        ui->leVolume2->setReadOnly ( false );
        ui->leVolume3->setReadOnly ( false );

        ui->leVolume1->setStyleSheet ( "QLineEdit {background-color: rgb(255, 255, 255)}" );
        ui->leVolume2->setStyleSheet ( "QLineEdit {background-color: rgb(255, 255, 255)}" );
        ui->leVolume3->setStyleSheet ( "QLineEdit {background-color: rgb(255, 255, 255)}" );
        }
    }

void Dialog::onPrintPdfDocClicked()
    {
    onCalculateClicked();

    QString companyName = mainwindow->optionsConfiguration["company"].c_str();
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString ( "dd.MM.yyyy hh:mm:ss" );

    if ( mainwindow->selectedInfo.selectedLanguage == ROMANIAN )
        {
        formattedTime = QString ( "Data / Ora:" ) + formattedTime;
        }
    else
        {
        formattedTime = QString ( "Date / Time:" ) + formattedTime;
        }

    double ambientTemperature = mainwindow->selectedInfo.ambientTemperature;
    double athmosphericPressure = mainwindow->selectedInfo.athmosphericPressure;
    double humidity = mainwindow->selectedInfo.relativeAirHumidity;
    QString certificate = mainwindow->selectedInfo.certificate.c_str();
    QString nameWaterMeter = mainwindow->selectedInfo.nameWaterMeter.c_str();
    unsigned nominalDiameter = mainwindow->selectedInfo.nominalDiameter;

    QString methodMeasurement{"Volumetric"};

    if ( mainwindow->selectedInfo.rbGravitmetric == true )
        {
        methodMeasurement = "Gravitmetric";
        }

    double minimumFlow = mainwindow->selectedInfo.minimumFlow;
    double trasitionFlow = mainwindow->selectedInfo.trasitionFlow;
    double nominalFlow = mainwindow->selectedInfo.nominalFlow;
    double maximumFlow = mainwindow->selectedInfo.maximumFlow;

    QString minimumFlowString = to_string_with_precision ( minimumFlow, 2 ).c_str();
    QString transitionFlowString = to_string_with_precision ( trasitionFlow, 2 ).c_str();
    QString nominalFlowString = to_string_with_precision ( nominalFlow, 2 ).c_str();
    QString maximumFlowString = to_string_with_precision ( maximumFlow, 2 ).c_str();

    auto size = minimumFlowString.size();

    for ( auto iter = 1; iter < 10 - size; iter++ )
        {
        minimumFlowString = QString ( "&nbsp;" ) + minimumFlowString;
        }

    size = transitionFlowString.size();

    for ( auto iter = 1; iter < 10 - size; iter++ )
        {
        transitionFlowString = QString ( "&nbsp;" ) + transitionFlowString;
        }

    size = nominalFlowString.size();

    for ( auto iter = 1; iter < 10 - size; iter++ )
        {
        nominalFlowString = QString ( "&nbsp;" ) + nominalFlowString;
        }

    size = maximumFlowString.size();

    for ( auto iter = 1; iter < 10 - size; iter++ )
        {
        maximumFlowString = QString ( "&nbsp;" ) + maximumFlowString;
        }

    double nominalError = mainwindow->selectedInfo.nominalError;
    double maximumError = mainwindow->selectedInfo.maximumError;

    if ( mainwindow->selectedInfo.selectedLanguage == ROMANIAN )
        {
        report =
            QString ( "<!DOCTYPE html>" ) +
            "<html>" +
            "<head>" +
            "<style>" +

            "   table, th, td {" +
            "       border: 1px solid black;" +
            "       border-collapse: collapse;" +
            "       width: 100%;" +
            "       font-family: Courier New;" +
            "       font-size: 4;" +
            "       font-weight: 700;" +
            "       table-layout: fixed;" +
            "   }" +

            "th {" +
            "    word-wrap: break-word;" +
            "}" +

            "</style>" +
            "</head>" +
            "<body style=\"font-family:'Courier New'\" \"font-weight: 700\" style=\"font-size: 4\" style=\"text-align: left\" >" +
            "<h4>" + companyName + "</h>" +
            "<h2 style=\"text-align: center\" style=\"font-color: dark blue\">[ Stand verificare contoare de apa ]</h2>" +
            "<h3 style=\"text-align: center\"><u>Fisa masuratori</u></h3><br>" +
            "<h3>" +
            formattedTime + "<br>"
            "Numar certificat::&nbsp;" + certificate + "&nbsp;<br>" +
            "Temperatura:&nbsp;" + to_string_with_precision ( ambientTemperature, 2 ).c_str() + "&nbsp;[°C]<br>" +
            "Presiune atmosferica:&nbsp;" + to_string_with_precision ( athmosphericPressure, 2 ).c_str() + "&nbsp;[Pa]<br>" +
            "Umiditate:&nbsp;" + to_string_with_precision ( humidity, 2 ).c_str() + "&nbsp;[%]<br><br>" +
            "Tip contor apa:&nbsp;" + nameWaterMeter + "<br>" +
            "Medoda de verificare:&nbsp;" + methodMeasurement + "<br>" +
            "Diametru nominal:&nbsp;" + to_string_with_precision ( nominalDiameter, 2 ).c_str() + "&nbsp;[mm]<br>" +

            "Debit maxim:&nbsp;&nbsp;&nbsp;&nbsp;" +
            maximumFlowString + "&nbsp;[L/h]"  + "&nbsp;/&nbsp;" + "Max error:&nbsp;" +
            to_string_with_precision ( nominalError, 2 ).c_str() + "&nbsp;[%]" + "<br>" +

            "Debit nominal:&nbsp;&nbsp;&nbsp;&nbsp;" +
            nominalFlowString + "&nbsp;[L/h]"  + "&nbsp;/&nbsp;"  + "Max error:&nbsp;" +
            to_string_with_precision ( nominalError, 2 ).c_str() + "&nbsp;[%]" + "<br>" +

            "Debit tranzitoriu:&nbsp;" +
            transitionFlowString + "&nbsp;[L/h]"  + "&nbsp;/&nbsp;" + "Max error:&nbsp;" +
            to_string_with_precision ( nominalError, 2 ).c_str() + "&nbsp;[%]" + "<br>" +

            "Debit minim:&nbsp;&nbsp;&nbsp;&nbsp;" +
            minimumFlowString + "&nbsp;[L/h]"  + "&nbsp;/&nbsp;" + "Max error:&nbsp;" +
            to_string_with_precision ( maximumError, 2 ).c_str() + "&nbsp;[%]" + "<br>" +

            "</h3>";

        report +=
            QString ( "<table width=\"100%\" border=\"1\">" ) +
            "    <caption>        Resultate: " "</caption>" +
            "    <thead>" +
            "    <tr>" +
            "        <th style=\"text-align: center\" width=\"13%\"> S/N </th>" +
            "        <th style=\"text-align: center\" width=\"12%\"> &nbsp;Debit&nbsp;&nbsp; [L/h] </th>" +
            "        <th style=\"text-align: center\" width=\"14%\"> Start Index [L] </th>" +
            "        <th style=\"text-align: center\" width=\"14%\">Stop &nbsp;Index [L] </th>" +
            "        <th style=\"text-align: center\" width=\"14%\"> Volum Contor apa [L] </th>" +
            "        <th style=\"text-align: center\" width=\"14%\"> Volum standard [L] </th>" +
            "        <th style=\"text-align: center\" width=\"8%\"> Err </th>" +
            "        <th style=\"text-align: center\"  width=\"15%\"> Resultate</th>" +
            "    </tr>" +
            "    </thead>" +
            "    <tbody>";

        for ( unsigned iter = 0; iter < mainwindow->selectedInfo.entriesNumber; ++iter )
            {

            if ( !vectorCheckNumber[iter]->checkState() )
                {
                continue;
                }

            QString SN = vectorSerialNumber[iter]->text();

            QString startFirst = vectorFirstIndexStart[iter]->text();
            QString stopFirst  = vectorFirstIndexStop[iter]->text();
            double registerVolumeDoubleFirst = ( vectorFirstIndexStop[iter]->text().toDouble() -
                                                 vectorFirstIndexStart[iter]->text().toDouble() );
            QString errorFirst = vectorFirstError[iter]->text();
            QString realVolumeFirst = precision_2 ( ui->leVolume1->text().toDouble() ).c_str();

            QString startSecond = vectorSecondIndexStart[iter]->text();
            QString stopSecond  = vectorSecondIndexStop[iter]->text();
            double registerVolumeDoubleSecond = ( vectorSecondIndexStop[iter]->text().toDouble() -
                                                  vectorSecondIndexStart[iter]->text().toDouble() );
            QString errorSecond = vectorSecondError[iter]->text();
            QString realVolumeSecond = precision_2 ( ui->leVolume2->text().toDouble() ).c_str();

            QString startThird = vectorThirdIndexStart[iter]->text();
            QString stopThird  = vectorThirdIndexStop[iter]->text();
            double registerVolumeDoubleThird = ( vectorThirdIndexStop[iter]->text().toDouble() -
                                                 vectorThirdIndexStart[iter]->text().toDouble() );
            QString errorThird = vectorThirdError[iter]->text();
            QString realVolumeThird = precision_2 ( ui->leVolume3->text().toDouble() ).c_str();

            if (
                XOR ( startFirst.isEmpty(), stopFirst.isEmpty() ) ||
                XOR ( startSecond.isEmpty(), stopSecond.isEmpty() ) ||
                XOR ( startThird.isEmpty(), stopThird.isEmpty() ) ||
                SN.isEmpty()
            )
                {
                continue;
                }

            QString resultTests {"ACCEPTAT"};

            try
                {

                bool bFirst = std::abs ( std::stod ( errorFirst.toStdString().c_str() ) ) < maximumError;
                bool bSecond = std::abs ( std::stod ( errorFirst.toStdString().c_str() ) ) < nominalError;
                bool bThird = std::abs ( std::stod ( errorFirst.toStdString().c_str() ) ) < nominalError;

                resultTests = ( bFirst && bSecond && bThird ?  "ACCEPTAT" : "RESPINS" );

                }
            catch ( ... )
                {
                resultTests = "RESPINS";
                }

            report +=
                QString ( "    <tr>" ) +
                "        <th style=\"text-align: left\" rowspan=\"3\"><br>"   + SN + "</th>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( minimumFlowMain ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + startFirst + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + stopFirst + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( registerVolumeDoubleFirst ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + realVolumeFirst + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + errorFirst + "</td>" +
                "        <th style=\"text-align: center\" rowspan=\"3\">" + resultTests + "</th>" +
                "    </tr>" +
                "    <tr>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( transitoriuFlowMain ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + startSecond + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + stopSecond + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( registerVolumeDoubleSecond ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + realVolumeSecond + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + errorSecond + "</td>" +
                "    </tr>" +
                "    <tr>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( nominalFlowMain ) +  "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + startThird + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + stopThird + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( registerVolumeDoubleThird ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + realVolumeThird + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + errorThird + "</td>" +
                "     </tr>";
            };

        report += QString ( "</tbody>" ) + "</table>";

        report += QString ( "<br><br><br><br><pre><h3>" ) +
                  "  Verificator                                  Sef laborator<br><br>" +
                  "  Nume ________________________                Nume________________________<br><br>" +
                  "<br><br>" +
                  "  Semnatura____________________                Semnatura___________________<br><br><br>" +
                  "<br></h3></pre>";

        std::thread  pdfThread ( printPdfThread, report );

        pdfThread.detach();
        }
    // English translation
    else
        {
        report =
            QString ( "<!DOCTYPE html>" ) +
            "<html>" +
            "<head>" +
            "<style>" +

            "   table, th, td {" +
            "       border: 1px solid black;" +
            "       border-collapse: collapse;" +
            "       width: 100%;" +
            "       font-family: Courier New;" +
            "       font-size: 4;" +
            "       font-weight: 700;" +
            "       table-layout: fixed;" +
            "   }" +

            "th {" +
            "    word-wrap: break-word;" +
            "}" +

            "</style>" +
            "</head>" +
            "<body style=\"font-family:'Courier New'\" \"font-weight: 700\" style=\"font-size: 4\" style=\"text-align: left\" >" +
            "<h4>" + companyName + "</h>" +
            "<h2 style=\"text-align: center\" style=\"font-color: dark blue\">[Water meters test bench]</h2>" +
            "<h3 style=\"text-align: center\"><u>Measurement sheet</u></h3><br>" +
            "<h3>" +
            formattedTime + "<br>" +
            "Certificat number:&nbsp;" + certificate + "&nbsp;<br>" +
            "Temperature:&nbsp;" + to_string_with_precision ( ambientTemperature, 2 ).c_str() + "&nbsp;[°C]<br>" +
            "Athmopheric pressure:&nbsp;" + to_string_with_precision ( athmosphericPressure, 2 ).c_str() + "&nbsp;[Pa]<br>" +
            "Humidity:&nbsp;" + to_string_with_precision ( humidity, 2 ).c_str() + "&nbsp;[%]<br><br>" +
            "Water meter type:&nbsp;" + nameWaterMeter + "<br>" +
            "Used measurement method:&nbsp;" + methodMeasurement + "<br>" +
            "Nominal diameter&nbsp;:" + to_string_with_precision ( nominalDiameter, 2 ).c_str() + "&nbsp;[mm]<br>" +

            "Maximum flow:&nbsp;&nbsp;&nbsp;&nbsp;" +
            maximumFlowString + "&nbsp;[L/h]"  + "&nbsp;/&nbsp;" + "Max error:&nbsp;" +
            to_string_with_precision ( nominalError, 2 ).c_str() + "&nbsp;[%]" + "<br>" +

            "Nominal flow:&nbsp;&nbsp;&nbsp;&nbsp;" +
            nominalFlowString + "&nbsp;[L/h]"  + "&nbsp;/&nbsp;"  + "Max error:&nbsp;" +
            to_string_with_precision ( nominalError, 2 ).c_str() + "&nbsp;[%]" + "<br>" +

            "Transition flow:&nbsp;" +
            transitionFlowString + "&nbsp;[L/h]"  + "&nbsp;/&nbsp;" + "Max error:&nbsp;" +
            to_string_with_precision ( nominalError, 2 ).c_str() + "&nbsp;[%]" + "<br>" +

            "Minimum flow:&nbsp;&nbsp;&nbsp;&nbsp;" +
            minimumFlowString + "&nbsp;[L/h]"  + "&nbsp;/&nbsp;" + "Max error:&nbsp;" +
            to_string_with_precision ( maximumError, 2 ).c_str() + "&nbsp;[%]" + "<br>" +

            "</h3>";

        report +=
            QString ( "<table width=\"100%\" border=\"1\">" ) +
            "    <caption>        Results: " "</caption>" +
            "    <thead>" +
            "    <tr>" +
            "        <th style=\"text-align: center\" width=\"14%\"> S/N </th>" +
            "        <th style=\"text-align: center\" width=\"12%\"> &nbsp;Flow&nbsp;&nbsp; [L/h] </th>" +
            "        <th style=\"text-align: center\" width=\"14%\"> Start Index [L] </th>" +
            "        <th style=\"text-align: center\" width=\"14%\">Stop &nbsp;Index [L] </th>" +
            "        <th style=\"text-align: center\" width=\"14%\"> Flow Meter Volume [L] </th>" +
            "        <th style=\"text-align: center\" width=\"14%\"> Standard Volume [L] </th>" +
            "        <th style=\"text-align: center\" width=\"8%\"> Error [%]</th>" +
            "        <th style=\"text-align: center\"  width=\"10%\"> Result</th>" +
            "    </tr>" +
            "    </thead>" +
            "    <tbody>";

        for ( unsigned iter = 0; iter < mainwindow->selectedInfo.entriesNumber; ++iter )
            {

            if ( !vectorCheckNumber[iter]->checkState() )
                {
                continue;
                }

            QString SN = vectorSerialNumber[iter]->text();

            QString startFirst = vectorFirstIndexStart[iter]->text();
            QString stopFirst  = vectorFirstIndexStop[iter]->text();
            double registerVolumeDoubleFirst = ( vectorFirstIndexStop[iter]->text().toDouble() -
                                                 vectorFirstIndexStart[iter]->text().toDouble() );
            QString errorFirst = vectorFirstError[iter]->text();
            QString realVolumeFirst = precision_2 ( ui->leVolume1->text().toDouble() ).c_str();

            QString startSecond = vectorSecondIndexStart[iter]->text();
            QString stopSecond  = vectorSecondIndexStop[iter]->text();
            double registerVolumeDoubleSecond = ( vectorSecondIndexStop[iter]->text().toDouble() -
                                                  vectorSecondIndexStart[iter]->text().toDouble() );
            QString errorSecond = vectorSecondError[iter]->text();
            QString realVolumeSecond = precision_2 ( ui->leVolume2->text().toDouble() ).c_str();

            QString startThird = vectorThirdIndexStart[iter]->text();
            QString stopThird  = vectorThirdIndexStop[iter]->text();
            double registerVolumeDoubleThird = ( vectorThirdIndexStop[iter]->text().toDouble() -
                                                 vectorThirdIndexStart[iter]->text().toDouble() );
            QString errorThird = vectorThirdError[iter]->text();
            QString realVolumeThird = precision_2 ( ui->leVolume3->text().toDouble() ).c_str();

            if (
                XOR ( startFirst.isEmpty(), stopFirst.isEmpty() ) ||
                XOR ( startSecond.isEmpty(), stopSecond.isEmpty() ) ||
                XOR ( startThird.isEmpty(), stopThird.isEmpty() ) ||
                SN.isEmpty()
            )
                {
                continue;
                }

            QString resultTests {"PASSED"};

            try
                {

                bool bFirst = std::abs ( std::stod ( errorFirst.toStdString().c_str() ) ) < maximumError;
                bool bSecond = std::abs ( std::stod ( errorFirst.toStdString().c_str() ) ) < nominalError;
                bool bThird = std::abs ( std::stod ( errorFirst.toStdString().c_str() ) ) < nominalError;

                resultTests = ( bFirst && bSecond && bThird ?  "PASSED" : "FAILED" );

                }
            catch ( ... )
                {
                resultTests = "FAILED";
                }

            report +=
                QString ( "    <tr>" ) +
                "        <th style=\"text-align: left\" rowspan=\"3\"><br>"   + SN + "</th>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( minimumFlowMain ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + startFirst + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + stopFirst + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( registerVolumeDoubleFirst ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + realVolumeFirst + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + errorFirst + "</td>" +
                "        <th style=\"text-align: center\" rowspan=\"3\">" + resultTests + "</th>" +
                "    </tr>" +
                "    <tr>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( transitoriuFlowMain ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + startSecond + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + stopSecond + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( registerVolumeDoubleSecond ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + realVolumeSecond + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + errorSecond + "</td>" +
                "    </tr>" +
                "    <tr>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( nominalFlowMain ) +  "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + startThird + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + stopThird + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + QString::number ( registerVolumeDoubleThird ) + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + realVolumeThird + "</td>" +
                "        <td style=\"text-align: right\" \"padding-right: 5px\">" + errorThird + "</td>" +
                "     </tr>";
            };

        report += QString ( "</tbody>" ) + "</table>";

        report += QString ( "<br><br><br><br><pre><h3>" ) +
                  "  Verification certified person                Laboratory manager<br>" +
                  "  Name ________________________                Name________________________<br><br>" +
                  "<br><br>" +
                  "  Signature____________________                Signature___________________<br><br>" +
                  "<br></h3></pre>";

        std::thread  pdfThread ( printPdfThread, report );

        pdfThread.detach();
        }
    }

void Dialog::showEvent ( QShowEvent *event )
    {
    PopulateTable();
    }

void Dialog::PopulateTable()
    {
    entries = mainwindow->selectedInfo.entriesNumber;

    minimumFlowMain = mainwindow->selectedInfo.minimumFlow;
    transitoriuFlowMain = mainwindow->selectedInfo.trasitionFlow;
    nominalFlowMain = mainwindow->selectedInfo.nominalFlow;

    nominalError = mainwindow->selectedInfo.nominalError;
    maximumError = mainwindow->selectedInfo.maximumError;

    QPalette paletteOddRow;
    paletteOddRow.setColor ( QPalette::Base, QColor ( 240, 255, 240, 255 ) );
    QPalette paletteEvenRow;
    paletteEvenRow.setColor ( QPalette::Base, QColor ( 255, 255, 255, 255 ) );

    QPalette paletteOddRowErr;
    paletteOddRowErr.setColor ( QPalette::Base, QColor ( 220, 235, 220, 255 ) );
    QPalette paletteEvenRowErr;
    paletteEvenRowErr.setColor ( QPalette::Base, QColor ( 235, 235, 235, 255 ) );

    for ( unsigned iter = 0; iter <  MAX_ENTRIES; ++iter )
        {
        if ( iter <  entries )
            {
            vectorNumber[iter]->show();
            vectorCheckNumber[iter]->show();
            vectorCheckNumber[iter]->setCheckState ( Qt::Checked );
            vectorSerialNumber[iter]->show();
            vectorFirstIndexStart[iter]->show();
            vectorFirstIndexStop[iter]->show();
            vectorFirstError[iter]->show();
            vectorSecondIndexStart[iter]->show();
            vectorSecondIndexStop[iter]->show();
            vectorSecondError[iter]->show();
            vectorThirdIndexStart[iter]->show();
            vectorThirdIndexStop[iter]->show();
            vectorThirdError[iter]->show();

            if ( iter % 4 == 0 || iter % 4 == 1 )
                {
                vectorNumber[iter]->setPalette ( paletteOddRow );
                vectorCheckNumber[iter]->setPalette ( paletteOddRow );
                vectorSerialNumber[iter]->setPalette ( paletteOddRow );
                vectorFirstIndexStart[iter]->setPalette ( paletteOddRow );
                vectorFirstIndexStop[iter]->setPalette ( paletteOddRow );
                vectorFirstError[iter]->setPalette ( paletteOddRowErr );
                vectorSecondIndexStart[iter]->setPalette ( paletteOddRow );
                vectorSecondIndexStop[iter]->setPalette ( paletteOddRow );
                vectorSecondError[iter]->setPalette ( paletteOddRowErr );
                vectorThirdIndexStart[iter]->setPalette ( paletteOddRow );
                vectorThirdIndexStop[iter]->setPalette ( paletteOddRow );
                vectorThirdError[iter]->setPalette ( paletteOddRowErr );
                }
            else
                {
                vectorNumber[iter]->setPalette ( paletteEvenRow );
                vectorCheckNumber[iter]->setPalette ( paletteEvenRow );
                vectorSerialNumber[iter]->setPalette ( paletteEvenRow );
                vectorFirstIndexStart[iter]->setPalette ( paletteEvenRow );
                vectorFirstIndexStop[iter]->setPalette ( paletteEvenRow );
                vectorFirstError[iter]->setPalette ( paletteEvenRowErr );
                vectorSecondIndexStart[iter]->setPalette ( paletteEvenRow );
                vectorSecondIndexStop[iter]->setPalette ( paletteEvenRow );
                vectorSecondError[iter]->setPalette ( paletteEvenRowErr );
                vectorThirdIndexStart[iter]->setPalette ( paletteEvenRow );
                vectorThirdIndexStop[iter]->setPalette ( paletteEvenRow );
                vectorThirdError[iter]->setPalette ( paletteEvenRowErr );
                }
            }
        else
            {
            vectorNumber[iter]->hide();
            vectorCheckNumber[iter]->hide();
            vectorCheckNumber[iter]->setCheckState ( Qt::Unchecked );
            vectorSerialNumber[iter]->hide();
            vectorFirstIndexStart[iter]->hide();
            vectorFirstIndexStop[iter]->hide();
            vectorFirstError[iter]->hide();
            vectorSecondIndexStart[iter]->hide();
            vectorSecondIndexStop[iter]->hide();
            vectorSecondError[iter]->hide();
            vectorThirdIndexStart[iter]->hide();
            vectorThirdIndexStop[iter]->hide();
            vectorThirdError[iter]->hide();
            }
        }

    ui->lbIndex1->setText ( QString ( "Index [L] -  Qmin: %1  [L/h]  Err: %2 %" ).arg ( QString::number ( minimumFlowMain ) ).arg ( QString::number ( maximumError ) ) );
    ui->lbIndex2->setText ( QString ( "Index [L] -  Qt:  %1  [L/h]  Err: %2 %" ).arg ( QString::number ( transitoriuFlowMain ) ).arg ( QString::number ( nominalError ) ) );
    ui->lbIndex3->setText ( QString ( "Index [L] -  Qn: %1  [L/h]  Err: %2 %" ).arg ( QString::number ( nominalFlowMain ) ).arg ( QString::number ( nominalError ) ) );
    }

void Dialog::focusInEvent ( QFocusEvent *event )
    {
    QDialog::focusInEvent ( event );
    }

void Dialog::focusOutEvent ( QFocusEvent *event )
    {
    QDialog::focusOutEvent ( event );
    }
