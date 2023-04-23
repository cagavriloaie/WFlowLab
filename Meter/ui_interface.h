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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
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
    QLineEdit *leSmallScale;
    QCheckBox *checkSmallScale;
    QCheckBox *checkWaterMeters_11_20;
    QLineEdit *leTemperature;
    QLineEdit *leWaterMeters_11_20;
    QLabel *lbAddress;
    QCheckBox *checkLargeScale;
    QLineEdit *leLargeScale;
    QLineEdit *leWaterMeters_1_10;
    QLabel *label_10;
    QCheckBox *checkTemperature;
    QLabel *label_2;
    QCheckBox *checkWaterMeters_1_10;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbRefresh;
    QPushButton *pbConnect;
    QPushButton *pbClose;

    void setupUi(QDialog *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName("Interface");
        Interface->resize(450, 485);
        Interface->setMinimumSize(QSize(450, 485));
        Interface->setMaximumSize(QSize(450, 485));
        gridLayout_3 = new QGridLayout(Interface);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
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


        verticalLayout->addWidget(groupBox);

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
        leSmallScale = new QLineEdit(groupBox_2);
        leSmallScale->setObjectName("leSmallScale");

        gridLayout_2->addWidget(leSmallScale, 1, 1, 1, 1);

        checkSmallScale = new QCheckBox(groupBox_2);
        checkSmallScale->setObjectName("checkSmallScale");
        checkSmallScale->setMinimumSize(QSize(200, 0));
        checkSmallScale->setMaximumSize(QSize(200, 16777215));

        gridLayout_2->addWidget(checkSmallScale, 1, 0, 1, 1);

        checkWaterMeters_11_20 = new QCheckBox(groupBox_2);
        checkWaterMeters_11_20->setObjectName("checkWaterMeters_11_20");
        checkWaterMeters_11_20->setStyleSheet(QString::fromUtf8("QLabel \n"
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

        gridLayout_2->addWidget(checkWaterMeters_11_20, 5, 0, 1, 1);

        leTemperature = new QLineEdit(groupBox_2);
        leTemperature->setObjectName("leTemperature");

        gridLayout_2->addWidget(leTemperature, 3, 1, 1, 1);

        leWaterMeters_11_20 = new QLineEdit(groupBox_2);
        leWaterMeters_11_20->setObjectName("leWaterMeters_11_20");

        gridLayout_2->addWidget(leWaterMeters_11_20, 5, 1, 1, 1);

        lbAddress = new QLabel(groupBox_2);
        lbAddress->setObjectName("lbAddress");

        gridLayout_2->addWidget(lbAddress, 0, 1, 1, 1);

        checkLargeScale = new QCheckBox(groupBox_2);
        checkLargeScale->setObjectName("checkLargeScale");

        gridLayout_2->addWidget(checkLargeScale, 2, 0, 1, 1);

        leLargeScale = new QLineEdit(groupBox_2);
        leLargeScale->setObjectName("leLargeScale");

        gridLayout_2->addWidget(leLargeScale, 2, 1, 1, 1);

        leWaterMeters_1_10 = new QLineEdit(groupBox_2);
        leWaterMeters_1_10->setObjectName("leWaterMeters_1_10");

        gridLayout_2->addWidget(leWaterMeters_1_10, 4, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName("label_10");

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        checkTemperature = new QCheckBox(groupBox_2);
        checkTemperature->setObjectName("checkTemperature");

        gridLayout_2->addWidget(checkTemperature, 3, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(100, 0));
        label_2->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(label_2, 0, 2, 1, 1);

        checkWaterMeters_1_10 = new QCheckBox(groupBox_2);
        checkWaterMeters_1_10->setObjectName("checkWaterMeters_1_10");

        gridLayout_2->addWidget(checkWaterMeters_1_10, 4, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(259, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbRefresh = new QPushButton(Interface);
        pbRefresh->setObjectName("pbRefresh");

        horizontalLayout->addWidget(pbRefresh);

        pbConnect = new QPushButton(Interface);
        pbConnect->setObjectName("pbConnect");

        horizontalLayout->addWidget(pbConnect);

        pbClose = new QPushButton(Interface);
        pbClose->setObjectName("pbClose");

        horizontalLayout->addWidget(pbClose);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(cbSelectSerial, cbBaudRate);
        QWidget::setTabOrder(cbBaudRate, cbSelectDataBits);
        QWidget::setTabOrder(cbSelectDataBits, cbSelectParity);
        QWidget::setTabOrder(cbSelectParity, cbSelectStopBits);
        QWidget::setTabOrder(cbSelectStopBits, pbRefresh);
        QWidget::setTabOrder(pbRefresh, pbConnect);
        QWidget::setTabOrder(pbConnect, pbClose);

        retranslateUi(Interface);

        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QDialog *Interface)
    {
        Interface->setWindowTitle(QCoreApplication::translate("Interface", "Serial Port Configuration", nullptr));
        groupBox->setTitle(QString());
        lbSelectStopBits->setText(QString());
        lbTimeout->setText(QCoreApplication::translate("Interface", "Timeout [ms]:", nullptr));
        lbSelectSerial->setText(QString());
        lbDataBits->setText(QString());
        lbSelectParity->setText(QString());
        lbBaudRate->setText(QString());
        lbNumberOfRetries->setText(QCoreApplication::translate("Interface", "Number of Retries:", nullptr));
        groupBox_2->setTitle(QString());
        checkSmallScale->setText(QString());
        checkWaterMeters_11_20->setText(QString());
        lbAddress->setText(QString());
        checkLargeScale->setText(QString());
        label_10->setText(QString());
        checkTemperature->setText(QString());
        label_2->setText(QString());
        checkWaterMeters_1_10->setText(QString());
        pbRefresh->setText(QString());
        pbConnect->setText(QString());
        pbClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
