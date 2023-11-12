/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <ledindicator.h>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
  public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QLabel *lbSelectStopBits;
    QLabel *lbTimeout;
    QLabel *lbSelectSerial;
    QComboBox *cbSelectDataBits;
    QLabel *lbDataBits;
    QComboBox *cbBaudRate;
    QComboBox *cbSelectStopBits;
    QComboBox *cbSelectSerial;
    QLabel *lbSelectParity;
    QLineEdit *leTimeout;
    QLabel *lbBaudRate;
    QComboBox *cbSelectParity;
    QLabel *lbNumberOfRetries;
    QComboBox *cbNumberRetries;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_2;
    QCheckBox *checkWaterMeters_11_15;
    LedIndicator *ledWaterMeters_1_5State;
    QLabel *lbAddress;
    QCheckBox *checkSmallScale;
    QCheckBox *checkWaterMeters_16_20;
    QLineEdit *leWaterMeters_1_5;
    QLineEdit *leSmallScale;
    QLineEdit *leWaterMeters_11_15;
    QCheckBox *checkTemperature;
    QLineEdit *leWaterMeter1;
    LedIndicator *ledSmallScaleState;
    QLabel *label_2;
    QLineEdit *leWaterMeter2;
    QCheckBox *checkWaterMeter3;
    QLabel *label_10;
    QLineEdit *leLargeScale;
    LedIndicator *ledWaterMeter3State;
    QLineEdit *leWaterMeter3;
    LedIndicator *ledTemperatureState;
    LedIndicator *ledWaterMeters_11_15Status;
    QCheckBox *checkWaterMeter1;
    QLineEdit *leWaterMeters_6_10;
    LedIndicator *ledWaterMeter2State;
    LedIndicator *ledWaterMeters_16_20State;
    QCheckBox *checkWaterMeters_6_10;
    QCheckBox *checkLargeScale;
    QLineEdit *leWaterMeters_16_20;
    LedIndicator *ledLargeScaleState;
    QLineEdit *leTemperature;
    LedIndicator *ledWaterMeters_6_10State;
    QCheckBox *checkWaterMeters_1_5;
    LedIndicator *ledWaterMeter1State;
    QCheckBox *checkWaterMeter2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbRefreshSerialPort;
    QPushButton *pbTestConnection;
    QPushButton *pbSaveConfiguration;
    QPushButton *pbClose;

    void setupUi(QDialog *Interface)
    {
        if (Interface->objectName().isEmpty())
        {
            Interface->setObjectName("Interface");
        }
        Interface->resize(500, 700);
        Interface->setMinimumSize(QSize(500, 650));
        Interface->setMaximumSize(QSize(500, 784));
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(),
                     QIcon::Normal, QIcon::Off);
        Interface->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(Interface);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox = new QGroupBox(Interface);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox  {\n"
                                "    border: 2px solid gray;\n"
                                "    border-color: #FF17365D;\n"
                                "    background-color: #E6E6FF;\n"
                                "	font-family: \"Segoe UI\";\n"
                                "	font-size: 12pt;\n"
                                "    margin-top: 10px;\n"
                                "}\n"
                                "\n"
                                "QGroupBox::title {\n"
                                "    subcontrol-origin: margin;\n"
                                "    left: 7px;\n"
                                "    padding: -5px 5px 0px 5px;\n"
                                "}\n"
                                "\n"
                                "QCheckBox::indicator {\n"
                                "    width: 15px;\n"
                                "    height: 15px;\n"
                                "    background: rgb(100, 100, 100);\n"
                                " }\n"
                                "\n"
                                "QCheckBox::indicator:checked\n"
                                " {\n"
                                "    width: 15px;\n"
                                "    height: 15px;\n"
                                "    background: rgb(240, 255, 240);\n"
                                " }\n"
                                "\n"
                                "QCheckBox {\n"
                                "	font-family: \"Segoe UI\";\n"
                                "	font-size: 12pt;\n"
                                "}\n"
                                "\n"
                                "QSpinBox {\n"
                                "	background: rgb(240, 255, 240);\n"
                                "	font-family: \"Segoe UI\";\n"
                                "	font-size: 12pt;\n"
                                "}\n"
                                "\n"
                                "QLineEdit {	\n"
                                "	background: rgb(240, 255, 240);\n"
                                "	selection-background-color: rgb(233, 99, 0);\n"
                                "	font-family: \"Segoe UI\";\n"
                                "	font-size: 12pt;\n"
                                " }"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lbSelectStopBits = new QLabel(groupBox);
        lbSelectStopBits->setObjectName("lbSelectStopBits");
        gridLayout->addWidget(lbSelectStopBits, 4, 0, 1, 1);
        lbTimeout = new QLabel(groupBox);
        lbTimeout->setObjectName("lbTimeout");
        gridLayout->addWidget(lbTimeout, 5, 0, 1, 1);
        lbSelectSerial = new QLabel(groupBox);
        lbSelectSerial->setObjectName("lbSelectSerial");
        lbSelectSerial->setMinimumSize(QSize(200, 0));
        lbSelectSerial->setMaximumSize(QSize(200, 16777215));
        gridLayout->addWidget(lbSelectSerial, 0, 0, 1, 1);
        cbSelectDataBits = new QComboBox(groupBox);
        cbSelectDataBits->setObjectName("cbSelectDataBits");
        gridLayout->addWidget(cbSelectDataBits, 2, 1, 1, 1);
        lbDataBits = new QLabel(groupBox);
        lbDataBits->setObjectName("lbDataBits");
        gridLayout->addWidget(lbDataBits, 2, 0, 1, 1);
        cbBaudRate = new QComboBox(groupBox);
        cbBaudRate->setObjectName("cbBaudRate");
        gridLayout->addWidget(cbBaudRate, 1, 1, 1, 1);
        cbSelectStopBits = new QComboBox(groupBox);
        cbSelectStopBits->setObjectName("cbSelectStopBits");
        gridLayout->addWidget(cbSelectStopBits, 4, 1, 1, 1);
        cbSelectSerial = new QComboBox(groupBox);
        cbSelectSerial->setObjectName("cbSelectSerial");
        gridLayout->addWidget(cbSelectSerial, 0, 1, 1, 1);
        lbSelectParity = new QLabel(groupBox);
        lbSelectParity->setObjectName("lbSelectParity");
        gridLayout->addWidget(lbSelectParity, 3, 0, 1, 1);
        leTimeout = new QLineEdit(groupBox);
        leTimeout->setObjectName("leTimeout");
        gridLayout->addWidget(leTimeout, 5, 1, 1, 1);
        lbBaudRate = new QLabel(groupBox);
        lbBaudRate->setObjectName("lbBaudRate");
        gridLayout->addWidget(lbBaudRate, 1, 0, 1, 1);
        cbSelectParity = new QComboBox(groupBox);
        cbSelectParity->setObjectName("cbSelectParity");
        gridLayout->addWidget(cbSelectParity, 3, 1, 1, 1);
        lbNumberOfRetries = new QLabel(groupBox);
        lbNumberOfRetries->setObjectName("lbNumberOfRetries");
        gridLayout->addWidget(lbNumberOfRetries, 6, 0, 1, 1);
        cbNumberRetries = new QComboBox(groupBox);
        cbNumberRetries->setObjectName("cbNumberRetries");
        gridLayout->addWidget(cbNumberRetries, 6, 1, 1, 1);
        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);
        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);
        groupBox_2 = new QGroupBox(Interface);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox  {\n"
                                  "    border: 2px solid gray;\n"
                                  "    border-color: #FF17365D;\n"
                                  "    background-color: #E6E6FF;\n"
                                  "	font-family: \"Segoe UI\";\n"
                                  "	font-size: 12pt;\n"
                                  "    margin-top: 10px;\n"
                                  "}\n"
                                  "\n"
                                  "QGroupBox::title {\n"
                                  "    subcontrol-origin: margin;\n"
                                  "    left: 7px;\n"
                                  "    padding: -5px 5px 0px 5px;\n"
                                  "}\n"
                                  "\n"
                                  "QCheckBox::indicator {\n"
                                  "    width:   10px;\n"
                                  "    height:  10px;\n"
                                  "    background: rgb(240, 255, 240);   \n"
                                  " }\n"
                                  "\n"
                                  "QCheckBox::indicator:checked\n"
                                  " {\n"
                                  "    width:   10px;\n"
                                  "    height: 10px;\n"
                                  "    background-color:       black;\n"
                                  " }\n"
                                  "\n"
                                  "QCheckBox {\n"
                                  "    font-family: \"Segoe UI\";\n"
                                  "    font-size: 12pt;\n"
                                  "}\n"
                                  "\n"
                                  "QLineEdit {	\n"
                                  "	background: rgb(240, 255, 240);\n"
                                  "	selection-background-color: rgb(233, 99, 0);\n"
                                  "    font-family: \"Segoe UI\";\n"
                                  "    font-size: 12pt;\n"
                                  " }\n"
                                  ""));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        checkWaterMeters_11_15 = new QCheckBox(groupBox_2);
        checkWaterMeters_11_15->setObjectName("checkWaterMeters_11_15");
        gridLayout_2->addWidget(checkWaterMeters_11_15, 9, 0, 1, 1);
        ledWaterMeters_1_5State = new LedIndicator(groupBox_2);
        ledWaterMeters_1_5State->setObjectName("ledWaterMeters_1_5State");
        gridLayout_2->addWidget(ledWaterMeters_1_5State, 7, 2, 1, 1);
        lbAddress = new QLabel(groupBox_2);
        lbAddress->setObjectName("lbAddress");
        gridLayout_2->addWidget(lbAddress, 0, 1, 1, 1);
        checkSmallScale = new QCheckBox(groupBox_2);
        checkSmallScale->setObjectName("checkSmallScale");
        checkSmallScale->setMinimumSize(QSize(200, 0));
        checkSmallScale->setMaximumSize(QSize(200, 16777215));
        gridLayout_2->addWidget(checkSmallScale, 1, 0, 1, 1);
        checkWaterMeters_16_20 = new QCheckBox(groupBox_2);
        checkWaterMeters_16_20->setObjectName("checkWaterMeters_16_20");
        gridLayout_2->addWidget(checkWaterMeters_16_20, 10, 0, 1, 1);
        leWaterMeters_1_5 = new QLineEdit(groupBox_2);
        leWaterMeters_1_5->setObjectName("leWaterMeters_1_5");
        gridLayout_2->addWidget(leWaterMeters_1_5, 7, 1, 1, 1);
        leSmallScale = new QLineEdit(groupBox_2);
        leSmallScale->setObjectName("leSmallScale");
        gridLayout_2->addWidget(leSmallScale, 1, 1, 1, 1);
        leWaterMeters_11_15 = new QLineEdit(groupBox_2);
        leWaterMeters_11_15->setObjectName("leWaterMeters_11_15");
        gridLayout_2->addWidget(leWaterMeters_11_15, 9, 1, 1, 1);
        checkTemperature = new QCheckBox(groupBox_2);
        checkTemperature->setObjectName("checkTemperature");
        gridLayout_2->addWidget(checkTemperature, 3, 0, 1, 1);
        leWaterMeter1 = new QLineEdit(groupBox_2);
        leWaterMeter1->setObjectName("leWaterMeter1");
        gridLayout_2->addWidget(leWaterMeter1, 4, 1, 1, 1);
        ledSmallScaleState = new LedIndicator(groupBox_2);
        ledSmallScaleState->setObjectName("ledSmallScaleState");
        gridLayout_2->addWidget(ledSmallScaleState, 1, 2, 1, 1);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(150, 0));
        label_2->setMaximumSize(QSize(150, 16777215));
        gridLayout_2->addWidget(label_2, 0, 2, 1, 1);
        leWaterMeter2 = new QLineEdit(groupBox_2);
        leWaterMeter2->setObjectName("leWaterMeter2");
        gridLayout_2->addWidget(leWaterMeter2, 5, 1, 1, 1);
        checkWaterMeter3 = new QCheckBox(groupBox_2);
        checkWaterMeter3->setObjectName("checkWaterMeter3");
        gridLayout_2->addWidget(checkWaterMeter3, 6, 0, 1, 1);
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");
        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);
        leLargeScale = new QLineEdit(groupBox_2);
        leLargeScale->setObjectName("leLargeScale");
        gridLayout_2->addWidget(leLargeScale, 2, 1, 1, 1);
        ledWaterMeter3State = new LedIndicator(groupBox_2);
        ledWaterMeter3State->setObjectName("ledWaterMeter3State");
        gridLayout_2->addWidget(ledWaterMeter3State, 6, 2, 1, 1);
        leWaterMeter3 = new QLineEdit(groupBox_2);
        leWaterMeter3->setObjectName("leWaterMeter3");
        gridLayout_2->addWidget(leWaterMeter3, 6, 1, 1, 1);
        ledTemperatureState = new LedIndicator(groupBox_2);
        ledTemperatureState->setObjectName("ledTemperatureState");
        gridLayout_2->addWidget(ledTemperatureState, 3, 2, 1, 1);
        ledWaterMeters_11_15Status = new LedIndicator(groupBox_2);
        ledWaterMeters_11_15Status->setObjectName("ledWaterMeters_11_15Status");
        gridLayout_2->addWidget(ledWaterMeters_11_15Status, 9, 2, 1, 1);
        checkWaterMeter1 = new QCheckBox(groupBox_2);
        checkWaterMeter1->setObjectName("checkWaterMeter1");
        gridLayout_2->addWidget(checkWaterMeter1, 4, 0, 1, 1);
        leWaterMeters_6_10 = new QLineEdit(groupBox_2);
        leWaterMeters_6_10->setObjectName("leWaterMeters_6_10");
        gridLayout_2->addWidget(leWaterMeters_6_10, 8, 1, 1, 1);
        ledWaterMeter2State = new LedIndicator(groupBox_2);
        ledWaterMeter2State->setObjectName("ledWaterMeter2State");
        gridLayout_2->addWidget(ledWaterMeter2State, 5, 2, 1, 1);
        ledWaterMeters_16_20State = new LedIndicator(groupBox_2);
        ledWaterMeters_16_20State->setObjectName("ledWaterMeters_16_20State");
        gridLayout_2->addWidget(ledWaterMeters_16_20State, 10, 2, 1, 1);
        checkWaterMeters_6_10 = new QCheckBox(groupBox_2);
        checkWaterMeters_6_10->setObjectName("checkWaterMeters_6_10");
        checkWaterMeters_6_10->setStyleSheet(QString::fromUtf8("QLabel \n"
                                             "{\n"
                                             "	font-family: \"Segoe UI\";\n"
                                             "	font-size: 12pt;\n"
                                             "}\n"
                                             "\n"
                                             "\n"
                                             "QPushButton \n"
                                             "{\n"
                                             "	font-family: \"Segoe UI\";\n"
                                             "	font-size: 12pt;\n"
                                             "}\n"
                                             "\n"
                                             "QComboBox \n"
                                             "{\n"
                                             "	font-family: \"Segoe UI\";\n"
                                             "	font-size: 12pt;\n"
                                             "}\n"
                                             "\n"
                                             "QGroupBox  {\n"
                                             "    border: 2px solid gray;\n"
                                             "    border-color: #FF17365D;\n"
                                             "    background-color: #E6E6FF;\n"
                                             "	font-family: \"Segoe UI\";\n"
                                             "	font-size: 12pt;\n"
                                             "    margin-top: 10px;\n"
                                             "}\n"
                                             "\n"
                                             "QGroupBox::title {\n"
                                             "    subcontrol-origin: margin;\n"
                                             "    left: 7px;\n"
                                             "    padding: -5px 5px 0px 5px;\n"
                                             "}\n"
                                             "\n"
                                             "QMenu {\n"
                                             "    background-color: white;\n"
                                             "    margin: 2px; /* some spacing around the menu */\n"
                                             "}\n"
                                             "\n"
                                             "QMenu::item {\n"
                                             "    padding: 2px 25px 2px 20px;\n"
                                             "    border: 1px solid transparent; /* reserve space for selection border */\n"
                                             "}\n"
                                             "\n"
                                             "QMenu::item:selected {\n"
                                             "    border-color: darkblue;\n"
                                             "    background: rgba(100, 100, 100, 150);\n"
                                             "}\n"
                                             "\n"
                                             "QRadioButton::indicator {\n"
                                             "    width:                  1"
                                             "0px;\n"
                                             "    height:                 10px;\n"
                                             "    border-radius:       7px;\n"
                                             "}\n"
                                             "\n"
                                             "QRadioButton::indicator:checked {\n"
                                             "    background-color:       black;\n"
                                             "    border:                         4px;\n"
                                             "}\n"
                                             "\n"
                                             "QRadioButton::indicator:unchecked {\n"
                                             "    background-color:       white;\n"
                                             "    border:                         4px;\n"
                                             "}\n"
                                             "\n"
                                             "\n"
                                             ""));
        gridLayout_2->addWidget(checkWaterMeters_6_10, 8, 0, 1, 1);
        checkLargeScale = new QCheckBox(groupBox_2);
        checkLargeScale->setObjectName("checkLargeScale");
        gridLayout_2->addWidget(checkLargeScale, 2, 0, 1, 1);
        leWaterMeters_16_20 = new QLineEdit(groupBox_2);
        leWaterMeters_16_20->setObjectName("leWaterMeters_16_20");
        gridLayout_2->addWidget(leWaterMeters_16_20, 10, 1, 1, 1);
        ledLargeScaleState = new LedIndicator(groupBox_2);
        ledLargeScaleState->setObjectName("ledLargeScaleState");
        gridLayout_2->addWidget(ledLargeScaleState, 2, 2, 1, 1);
        leTemperature = new QLineEdit(groupBox_2);
        leTemperature->setObjectName("leTemperature");
        gridLayout_2->addWidget(leTemperature, 3, 1, 1, 1);
        ledWaterMeters_6_10State = new LedIndicator(groupBox_2);
        ledWaterMeters_6_10State->setObjectName("ledWaterMeters_6_10State");
        gridLayout_2->addWidget(ledWaterMeters_6_10State, 8, 2, 1, 1);
        checkWaterMeters_1_5 = new QCheckBox(groupBox_2);
        checkWaterMeters_1_5->setObjectName("checkWaterMeters_1_5");
        gridLayout_2->addWidget(checkWaterMeters_1_5, 7, 0, 1, 1);
        ledWaterMeter1State = new LedIndicator(groupBox_2);
        ledWaterMeter1State->setObjectName("ledWaterMeter1State");
        gridLayout_2->addWidget(ledWaterMeter1State, 4, 2, 1, 1);
        checkWaterMeter2 = new QCheckBox(groupBox_2);
        checkWaterMeter2->setObjectName("checkWaterMeter2");
        gridLayout_2->addWidget(checkWaterMeter2, 5, 0, 1, 1);
        gridLayout_5->addLayout(gridLayout_2, 0, 0, 1, 1);
        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                         QSizePolicy::Expanding);
        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(259, 20, QSizePolicy::Expanding,
                                           QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);
        pbRefreshSerialPort = new QPushButton(Interface);
        pbRefreshSerialPort->setObjectName("pbRefreshSerialPort");
        horizontalLayout->addWidget(pbRefreshSerialPort);
        pbTestConnection = new QPushButton(Interface);
        pbTestConnection->setObjectName("pbTestConnection");
        horizontalLayout->addWidget(pbTestConnection);
        pbSaveConfiguration = new QPushButton(Interface);
        pbSaveConfiguration->setObjectName("pbSaveConfiguration");
        horizontalLayout->addWidget(pbSaveConfiguration);
        pbClose = new QPushButton(Interface);
        pbClose->setObjectName("pbClose");
        horizontalLayout->addWidget(pbClose);
        gridLayout_3->addLayout(horizontalLayout, 3, 0, 1, 1);
        QWidget::setTabOrder(cbSelectSerial, cbBaudRate);
        QWidget::setTabOrder(cbBaudRate, cbSelectDataBits);
        QWidget::setTabOrder(cbSelectDataBits, cbSelectParity);
        QWidget::setTabOrder(cbSelectParity, cbSelectStopBits);
        QWidget::setTabOrder(cbSelectStopBits, leTimeout);
        QWidget::setTabOrder(leTimeout, cbNumberRetries);
        QWidget::setTabOrder(cbNumberRetries, checkSmallScale);
        QWidget::setTabOrder(checkSmallScale, checkLargeScale);
        QWidget::setTabOrder(checkLargeScale, checkTemperature);
        QWidget::setTabOrder(checkTemperature, checkWaterMeter1);
        QWidget::setTabOrder(checkWaterMeter1, checkWaterMeter2);
        QWidget::setTabOrder(checkWaterMeter2, checkWaterMeter3);
        QWidget::setTabOrder(checkWaterMeter3, checkWaterMeters_1_5);
        QWidget::setTabOrder(checkWaterMeters_1_5, checkWaterMeters_6_10);
        QWidget::setTabOrder(checkWaterMeters_6_10, checkWaterMeters_11_15);
        QWidget::setTabOrder(checkWaterMeters_11_15, checkWaterMeters_16_20);
        QWidget::setTabOrder(checkWaterMeters_16_20, leSmallScale);
        QWidget::setTabOrder(leSmallScale, leLargeScale);
        QWidget::setTabOrder(leLargeScale, leTemperature);
        QWidget::setTabOrder(leTemperature, leWaterMeter1);
        QWidget::setTabOrder(leWaterMeter1, leWaterMeter2);
        QWidget::setTabOrder(leWaterMeter2, leWaterMeter3);
        QWidget::setTabOrder(leWaterMeter3, leWaterMeters_1_5);
        QWidget::setTabOrder(leWaterMeters_1_5, leWaterMeters_6_10);
        QWidget::setTabOrder(leWaterMeters_6_10, leWaterMeters_11_15);
        QWidget::setTabOrder(leWaterMeters_11_15, leWaterMeters_16_20);
        QWidget::setTabOrder(leWaterMeters_16_20, pbRefreshSerialPort);
        QWidget::setTabOrder(pbRefreshSerialPort, pbTestConnection);
        QWidget::setTabOrder(pbTestConnection, pbSaveConfiguration);
        QWidget::setTabOrder(pbSaveConfiguration, pbClose);
        retranslateUi(Interface);
        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QDialog *Interface)
    {
        Interface->setWindowTitle(QCoreApplication::translate("Interface",
                                  "Serial Port Configuration", nullptr));
        groupBox->setTitle(QString());
        lbSelectStopBits->setText(QString());
        lbTimeout->setText(QString());
        lbSelectSerial->setText(QString());
        lbDataBits->setText(QString());
        lbSelectParity->setText(QString());
        lbBaudRate->setText(QString());
        lbNumberOfRetries->setText(QString());
        groupBox_2->setTitle(QString());
        checkWaterMeters_11_15->setText(QString());
        lbAddress->setText(QString());
        checkSmallScale->setText(QString());
        checkWaterMeters_16_20->setText(QString());
        leWaterMeters_1_5->setText(QString());
        leSmallScale->setText(QString());
        checkTemperature->setText(QString());
        leWaterMeter1->setText(QString());
        label_2->setText(QString());
        leWaterMeter2->setText(QString());
        checkWaterMeter3->setText(QString());
        label_10->setText(QString());
        leLargeScale->setText(QString());
        leWaterMeter3->setText(QString());
        checkWaterMeter1->setText(QString());
        leWaterMeters_6_10->setText(QString());
        checkWaterMeters_6_10->setText(QString());
        checkLargeScale->setText(QString());
        leTemperature->setText(QString());
        checkWaterMeters_1_5->setText(QString());
        checkWaterMeter2->setText(QString());
        pbRefreshSerialPort->setText(QString());
        pbTestConnection->setText(QString());
        pbSaveConfiguration->setText(QString());
        pbClose->setText(QString());
    } // retranslateUi

};

namespace Ui
{
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
