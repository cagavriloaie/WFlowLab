/********************************************************************************
** Form generated from reading UI file 'interface.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_1;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QLabel *lbSelectStopBits_1;
    QLabel *lbTimeout_1;
    QLabel *lbSelectSerial_1;
    QComboBox *cbSelectDataBits_1;
    QLabel *lbDataBits_1;
    QComboBox *cbBaudRate_1;
    QComboBox *cbSelectStopBits_1;
    QComboBox *cbSelectSerial_1;
    QLabel *lbSelectParity_1;
    QLineEdit *leTimeout_1;
    QLabel *lbBaudRate_1;
    QComboBox *cbSelectParity_1;
    QLabel *lbNumberOfRetries_1;
    QComboBox *cbNumberRetries_1;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QGridLayout *gridLayout_3;
    QLabel *lbSelectStopBits_2;
    QLabel *lbTimeout_2;
    QLabel *lbSelectSerial_2;
    QComboBox *cbSelectDataBits_2;
    QLabel *lbDataBits_2;
    QComboBox *cbBaudRate_2;
    QComboBox *cbSelectStopBits_2;
    QComboBox *cbSelectSerial_2;
    QLabel *lbSelectParity_2;
    QLineEdit *leTimeout_2;
    QLabel *lbBaudRate_2;
    QComboBox *cbSelectParity_2;
    QLabel *lbNumberOfRetries_2;
    QComboBox *cbNumberRetries_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbRefreshSerialPort;
    QPushButton *pbTestConnection;
    QPushButton *pbSaveConfiguration;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbConnect;
    QPushButton *pbClose;

    void setupUi(QDialog *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName("Interface");
        Interface->resize(830, 361);
        Interface->setMinimumSize(QSize(1, 1));
        Interface->setMaximumSize(QSize(10000, 10000));
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Interface->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(Interface);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        groupBox_1 = new QGroupBox(Interface);
        groupBox_1->setObjectName("groupBox_1");
        groupBox_1->setStyleSheet(QString::fromUtf8("QGroupBox  {\n"
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
        gridLayout_4 = new QGridLayout(groupBox_1);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lbSelectStopBits_1 = new QLabel(groupBox_1);
        lbSelectStopBits_1->setObjectName("lbSelectStopBits_1");
        lbSelectStopBits_1->setMinimumSize(QSize(150, 0));
        lbSelectStopBits_1->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(lbSelectStopBits_1, 4, 0, 1, 1);

        lbTimeout_1 = new QLabel(groupBox_1);
        lbTimeout_1->setObjectName("lbTimeout_1");
        lbTimeout_1->setMinimumSize(QSize(150, 0));
        lbTimeout_1->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(lbTimeout_1, 5, 0, 1, 1);

        lbSelectSerial_1 = new QLabel(groupBox_1);
        lbSelectSerial_1->setObjectName("lbSelectSerial_1");
        lbSelectSerial_1->setMinimumSize(QSize(150, 0));
        lbSelectSerial_1->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(lbSelectSerial_1, 0, 0, 1, 1);

        cbSelectDataBits_1 = new QComboBox(groupBox_1);
        cbSelectDataBits_1->setObjectName("cbSelectDataBits_1");
        cbSelectDataBits_1->setMinimumSize(QSize(200, 28));
        cbSelectDataBits_1->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(cbSelectDataBits_1, 2, 1, 1, 1);

        lbDataBits_1 = new QLabel(groupBox_1);
        lbDataBits_1->setObjectName("lbDataBits_1");
        lbDataBits_1->setMinimumSize(QSize(150, 0));
        lbDataBits_1->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(lbDataBits_1, 2, 0, 1, 1);

        cbBaudRate_1 = new QComboBox(groupBox_1);
        cbBaudRate_1->setObjectName("cbBaudRate_1");
        cbBaudRate_1->setMinimumSize(QSize(200, 28));
        cbBaudRate_1->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(cbBaudRate_1, 1, 1, 1, 1);

        cbSelectStopBits_1 = new QComboBox(groupBox_1);
        cbSelectStopBits_1->setObjectName("cbSelectStopBits_1");
        cbSelectStopBits_1->setMinimumSize(QSize(200, 28));
        cbSelectStopBits_1->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(cbSelectStopBits_1, 4, 1, 1, 1);

        cbSelectSerial_1 = new QComboBox(groupBox_1);
        cbSelectSerial_1->setObjectName("cbSelectSerial_1");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbSelectSerial_1->sizePolicy().hasHeightForWidth());
        cbSelectSerial_1->setSizePolicy(sizePolicy);
        cbSelectSerial_1->setMinimumSize(QSize(200, 28));
        cbSelectSerial_1->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(cbSelectSerial_1, 0, 1, 1, 1);

        lbSelectParity_1 = new QLabel(groupBox_1);
        lbSelectParity_1->setObjectName("lbSelectParity_1");
        lbSelectParity_1->setMinimumSize(QSize(150, 0));
        lbSelectParity_1->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(lbSelectParity_1, 3, 0, 1, 1);

        leTimeout_1 = new QLineEdit(groupBox_1);
        leTimeout_1->setObjectName("leTimeout_1");
        leTimeout_1->setMinimumSize(QSize(200, 0));
        leTimeout_1->setMaximumSize(QSize(200, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(12);
        leTimeout_1->setFont(font);
        leTimeout_1->setStyleSheet(QString::fromUtf8("/* Common styles */\n"
"* {\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 12pt;\n"
"}\n"
"\n"
"/* QPushButton */\n"
"QPushButton {\n"
"    padding: 5px 10px;\n"
"    border: 2px solid #ccc; /* Light gray border */\n"
"    background-color: #f0f0f0; /* Light gray background */\n"
"    border-radius: 5px; /* Rounded corners */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #d7d9d7; /* Light gray background on hover */\n"
"    border: 2px solid #aaa; /* Darker gray border on hover */\n"
"}\n"
"\n"
"/* QComboBox */\n"
"QComboBox {\n"
"    border: 2px solid #ADD8E6; /* Light blue border */\n"
"    border-radius: 4px; /* Rounded corners */\n"
"    padding: 2px;\n"
"    min-height: 28px; /* Adjust the minimum height */\n"
"    background-color: #f0f0f0; /* Light gray background */\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #ADD8E6; /* Light blue border for the dropdown */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-posi"
                        "tion: top right;\n"
"    width: 20px; /* Adjust width as needed */\n"
"    border-left: 1px solid #ADD8E6; /* Light blue border for the drop-down button */\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    width: 0;\n"
"    height: 0;\n"
"}\n"
"\n"
"QComboBox::down-arrow:disabled {\n"
"    image: url(circle.png); /* Replace with your own circle image */\n"
"    width: 16px; /* Adjust width of circle */\n"
"    height: 16px; /* Adjust height of circle */\n"
"}\n"
"\n"
"/* QLineEdit */\n"
"QLineEdit {\n"
"    border: 2px solid #ADD8E6; /* Light blue border */\n"
"    border-radius: 4px; /* Rounded corners */\n"
"    height: 28px; /* Adjusted height */\n"
"    padding: 2px; /* Adjust padding if needed */\n"
"    background-color: #f0f0f0; /* Light gray background */\n"
"}\n"
"\n"
"/* QRadioButton */\n"
"QRadioButton::indicator {\n"
"    width: 14px; /* Adjusted width */\n"
"    height: 14px; /* Adjusted height */\n"
"    border-radius: 7px;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background-color: b"
                        "lack;\n"
"    border: 4px solid black; /* Added border style */\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked {\n"
"    background-color: white;\n"
"    border: 4px solid black; /* Added border style */\n"
"}\n"
"\n"
"/* QGroupBox */\n"
"QGroupBox {\n"
"    border: 2px solid black;\n"
"    border-color: rgba(0, 0, 0, 0.36); /* Black with transparency */\n"
"    background-color: #E6E6FF; /* Light purple background */\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 12pt;\n"
"    margin-top: 10px;\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding-top: 10px; /* Padding for the top of the group box */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 7px;\n"
"    padding: 5px; /* Adjusted padding for better appearance */\n"
"}\n"
""));

        gridLayout->addWidget(leTimeout_1, 5, 1, 1, 1);

        lbBaudRate_1 = new QLabel(groupBox_1);
        lbBaudRate_1->setObjectName("lbBaudRate_1");
        lbBaudRate_1->setMinimumSize(QSize(150, 0));
        lbBaudRate_1->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(lbBaudRate_1, 1, 0, 1, 1);

        cbSelectParity_1 = new QComboBox(groupBox_1);
        cbSelectParity_1->setObjectName("cbSelectParity_1");
        cbSelectParity_1->setMinimumSize(QSize(200, 28));
        cbSelectParity_1->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(cbSelectParity_1, 3, 1, 1, 1);

        lbNumberOfRetries_1 = new QLabel(groupBox_1);
        lbNumberOfRetries_1->setObjectName("lbNumberOfRetries_1");
        lbNumberOfRetries_1->setMinimumSize(QSize(150, 0));
        lbNumberOfRetries_1->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(lbNumberOfRetries_1, 6, 0, 1, 1);

        cbNumberRetries_1 = new QComboBox(groupBox_1);
        cbNumberRetries_1->setObjectName("cbNumberRetries_1");
        cbNumberRetries_1->setMinimumSize(QSize(200, 28));
        cbNumberRetries_1->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(cbNumberRetries_1, 6, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 1, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox_1);

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
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName("formLayout");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        lbSelectStopBits_2 = new QLabel(groupBox_2);
        lbSelectStopBits_2->setObjectName("lbSelectStopBits_2");
        lbSelectStopBits_2->setMinimumSize(QSize(150, 0));
        lbSelectStopBits_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(lbSelectStopBits_2, 4, 0, 1, 1);

        lbTimeout_2 = new QLabel(groupBox_2);
        lbTimeout_2->setObjectName("lbTimeout_2");
        lbTimeout_2->setMinimumSize(QSize(150, 0));
        lbTimeout_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(lbTimeout_2, 5, 0, 1, 1);

        lbSelectSerial_2 = new QLabel(groupBox_2);
        lbSelectSerial_2->setObjectName("lbSelectSerial_2");
        lbSelectSerial_2->setMinimumSize(QSize(150, 0));
        lbSelectSerial_2->setMaximumSize(QSize(150, 150));

        gridLayout_3->addWidget(lbSelectSerial_2, 0, 0, 1, 1);

        cbSelectDataBits_2 = new QComboBox(groupBox_2);
        cbSelectDataBits_2->setObjectName("cbSelectDataBits_2");
        cbSelectDataBits_2->setMinimumSize(QSize(200, 28));
        cbSelectDataBits_2->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(cbSelectDataBits_2, 2, 1, 1, 1);

        lbDataBits_2 = new QLabel(groupBox_2);
        lbDataBits_2->setObjectName("lbDataBits_2");
        lbDataBits_2->setMinimumSize(QSize(150, 0));
        lbDataBits_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(lbDataBits_2, 2, 0, 1, 1);

        cbBaudRate_2 = new QComboBox(groupBox_2);
        cbBaudRate_2->setObjectName("cbBaudRate_2");
        cbBaudRate_2->setMinimumSize(QSize(200, 28));
        cbBaudRate_2->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(cbBaudRate_2, 1, 1, 1, 1);

        cbSelectStopBits_2 = new QComboBox(groupBox_2);
        cbSelectStopBits_2->setObjectName("cbSelectStopBits_2");
        cbSelectStopBits_2->setMinimumSize(QSize(200, 28));
        cbSelectStopBits_2->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(cbSelectStopBits_2, 4, 1, 1, 1);

        cbSelectSerial_2 = new QComboBox(groupBox_2);
        cbSelectSerial_2->setObjectName("cbSelectSerial_2");
        sizePolicy.setHeightForWidth(cbSelectSerial_2->sizePolicy().hasHeightForWidth());
        cbSelectSerial_2->setSizePolicy(sizePolicy);
        cbSelectSerial_2->setMinimumSize(QSize(200, 28));
        cbSelectSerial_2->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(cbSelectSerial_2, 0, 1, 1, 1);

        lbSelectParity_2 = new QLabel(groupBox_2);
        lbSelectParity_2->setObjectName("lbSelectParity_2");
        lbSelectParity_2->setMinimumSize(QSize(150, 0));
        lbSelectParity_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(lbSelectParity_2, 3, 0, 1, 1);

        leTimeout_2 = new QLineEdit(groupBox_2);
        leTimeout_2->setObjectName("leTimeout_2");
        leTimeout_2->setMinimumSize(QSize(200, 0));
        leTimeout_2->setMaximumSize(QSize(200, 16777215));
        leTimeout_2->setFont(font);
        leTimeout_2->setAutoFillBackground(false);
        leTimeout_2->setStyleSheet(QString::fromUtf8("/* Common styles */\n"
"* {\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 12pt;\n"
"}\n"
"\n"
"/* QPushButton */\n"
"QPushButton {\n"
"    padding: 5px 10px;\n"
"    border: 2px solid #ccc; /* Light gray border */\n"
"    background-color: #f0f0f0; /* Light gray background */\n"
"    border-radius: 5px; /* Rounded corners */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #d7d9d7; /* Light gray background on hover */\n"
"    border: 2px solid #aaa; /* Darker gray border on hover */\n"
"}\n"
"\n"
"/* QComboBox */\n"
"QComboBox {\n"
"    border: 2px solid #ADD8E6; /* Light blue border */\n"
"    border-radius: 4px; /* Rounded corners */\n"
"    padding: 2px;\n"
"    min-height: 28px; /* Adjust the minimum height */\n"
"    background-color: #f0f0f0; /* Light gray background */\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #ADD8E6; /* Light blue border for the dropdown */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-posi"
                        "tion: top right;\n"
"    width: 20px; /* Adjust width as needed */\n"
"    border-left: 1px solid #ADD8E6; /* Light blue border for the drop-down button */\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    width: 0;\n"
"    height: 0;\n"
"}\n"
"\n"
"QComboBox::down-arrow:disabled {\n"
"    image: url(circle.png); /* Replace with your own circle image */\n"
"    width: 16px; /* Adjust width of circle */\n"
"    height: 16px; /* Adjust height of circle */\n"
"}\n"
"\n"
"/* QLineEdit */\n"
"QLineEdit {\n"
"    border: 2px solid #ADD8E6; /* Light blue border */\n"
"    border-radius: 4px; /* Rounded corners */\n"
"    height: 28px; /* Adjusted height */\n"
"    padding: 2px; /* Adjust padding if needed */\n"
"    background-color: #f0f0f0; /* Light gray background */\n"
"}\n"
"\n"
"/* QRadioButton */\n"
"QRadioButton::indicator {\n"
"    width: 14px; /* Adjusted width */\n"
"    height: 14px; /* Adjusted height */\n"
"    border-radius: 7px;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked {\n"
"    background-color: b"
                        "lack;\n"
"    border: 4px solid black; /* Added border style */\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked {\n"
"    background-color: white;\n"
"    border: 4px solid black; /* Added border style */\n"
"}\n"
"\n"
"/* QGroupBox */\n"
"QGroupBox {\n"
"    border: 2px solid black;\n"
"    border-color: rgba(0, 0, 0, 0.36); /* Black with transparency */\n"
"    background-color: #E6E6FF; /* Light purple background */\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 12pt;\n"
"    margin-top: 10px;\n"
"    border-radius: 8px; /* Rounded corners */\n"
"    padding-top: 10px; /* Padding for the top of the group box */\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 7px;\n"
"    padding: 5px; /* Adjusted padding for better appearance */\n"
"}\n"
""));

        gridLayout_3->addWidget(leTimeout_2, 5, 1, 1, 1);

        lbBaudRate_2 = new QLabel(groupBox_2);
        lbBaudRate_2->setObjectName("lbBaudRate_2");
        lbBaudRate_2->setMinimumSize(QSize(150, 0));
        lbBaudRate_2->setMaximumSize(QSize(150, 150));

        gridLayout_3->addWidget(lbBaudRate_2, 1, 0, 1, 1);

        cbSelectParity_2 = new QComboBox(groupBox_2);
        cbSelectParity_2->setObjectName("cbSelectParity_2");
        cbSelectParity_2->setMinimumSize(QSize(200, 28));
        cbSelectParity_2->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(cbSelectParity_2, 3, 1, 1, 1);

        lbNumberOfRetries_2 = new QLabel(groupBox_2);
        lbNumberOfRetries_2->setObjectName("lbNumberOfRetries_2");
        lbNumberOfRetries_2->setMinimumSize(QSize(150, 0));
        lbNumberOfRetries_2->setMaximumSize(QSize(150, 16777215));

        gridLayout_3->addWidget(lbNumberOfRetries_2, 6, 0, 1, 1);

        cbNumberRetries_2 = new QComboBox(groupBox_2);
        cbNumberRetries_2->setObjectName("cbNumberRetries_2");
        cbNumberRetries_2->setMinimumSize(QSize(200, 28));
        cbNumberRetries_2->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(cbNumberRetries_2, 6, 1, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        formLayout->setItem(1, QFormLayout::LabelRole, verticalSpacer_2);


        horizontalLayout_2->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(259, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbRefreshSerialPort = new QPushButton(Interface);
        pbRefreshSerialPort->setObjectName("pbRefreshSerialPort");
        pbRefreshSerialPort->setMaximumSize(QSize(16777215, 29));
        pbRefreshSerialPort->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pbRefreshSerialPort);

        pbTestConnection = new QPushButton(Interface);
        pbTestConnection->setObjectName("pbTestConnection");
        pbTestConnection->setMaximumSize(QSize(16777215, 29));
        pbTestConnection->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pbTestConnection);

        pbSaveConfiguration = new QPushButton(Interface);
        pbSaveConfiguration->setObjectName("pbSaveConfiguration");
        pbSaveConfiguration->setMaximumSize(QSize(16777215, 29));
        pbSaveConfiguration->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pbSaveConfiguration);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pbConnect = new QPushButton(Interface);
        pbConnect->setObjectName("pbConnect");
        pbConnect->setMaximumSize(QSize(16777215, 29));

        horizontalLayout->addWidget(pbConnect);

        pbClose = new QPushButton(Interface);
        pbClose->setObjectName("pbClose");
        pbClose->setMaximumSize(QSize(16777215, 29));
        pbClose->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pbClose);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(cbSelectSerial_1, cbBaudRate_1);
        QWidget::setTabOrder(cbBaudRate_1, cbSelectDataBits_1);
        QWidget::setTabOrder(cbSelectDataBits_1, cbSelectParity_1);
        QWidget::setTabOrder(cbSelectParity_1, cbSelectStopBits_1);
        QWidget::setTabOrder(cbSelectStopBits_1, leTimeout_1);
        QWidget::setTabOrder(leTimeout_1, cbNumberRetries_1);
        QWidget::setTabOrder(cbNumberRetries_1, pbRefreshSerialPort);
        QWidget::setTabOrder(pbRefreshSerialPort, pbTestConnection);
        QWidget::setTabOrder(pbTestConnection, pbSaveConfiguration);
        QWidget::setTabOrder(pbSaveConfiguration, pbClose);

        retranslateUi(Interface);

        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QDialog *Interface)
    {
        Interface->setWindowTitle(QCoreApplication::translate("Interface", "Serial Port Configuration", nullptr));
        groupBox_1->setTitle(QString());
        lbSelectStopBits_1->setText(QString());
        lbTimeout_1->setText(QString());
        lbSelectSerial_1->setText(QString());
        lbDataBits_1->setText(QString());
        lbSelectParity_1->setText(QString());
        lbBaudRate_1->setText(QString());
        lbNumberOfRetries_1->setText(QString());
        groupBox_2->setTitle(QString());
        lbSelectStopBits_2->setText(QString());
        lbTimeout_2->setText(QString());
        lbSelectSerial_2->setText(QString());
        lbDataBits_2->setText(QString());
        lbSelectParity_2->setText(QString());
        lbBaudRate_2->setText(QString());
        lbNumberOfRetries_2->setText(QString());
        pbRefreshSerialPort->setText(QString());
        pbTestConnection->setText(QString());
        pbSaveConfiguration->setText(QString());
        pbConnect->setText(QString());
        pbClose->setText(QString());
#if QT_CONFIG(shortcut)
        pbClose->setShortcut(QCoreApplication::translate("Interface", "Esc", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
