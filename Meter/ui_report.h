/********************************************************************************
** Form generated from reading UI file 'report.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORT_H
#define UI_REPORT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
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

class Ui_report
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *grBoxBuletin;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lbBuletinNumber;
    QLabel *lbNmlNtm;
    QLabel *lbCost;
    QLabel *lbChecker;
    QComboBox *cbValability;
    QLineEdit *leCostRon;
    QLabel *lbEtaloane;
    QLabel *lbMijlocMasurare;
    QLineEdit *leLtCode;
    QLabel *lbValabilitate;
    QLineEdit *leMeansOfMeasurement;
    QLabel *lbCodulLt;
    QLineEdit *leUsedSerie;
    QLineEdit *leNmlNtmNorms;
    QLineEdit *leBuletinNumber;
    QLabel *lbTehnicalSuperviser;
    QLineEdit *leChecker;
    QLineEdit *leTehnicalSuperviser;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbPrint;
    QPushButton *pbClose;

    void setupUi(QDialog *report)
    {
        if (report->objectName().isEmpty())
            report->setObjectName("report");
        report->resize(658, 384);
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(), QIcon::Normal, QIcon::Off);
        report->setWindowIcon(icon);
        report->setStyleSheet(QString::fromUtf8("QPushButton:hover {\n"
"       background-color: #d7d9d7;\n"
"}\n"
"\n"
"QLabel \n"
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
"QRadioButton {\n"
"   padding-left: 20px; \n"
"   padding-right: 20px;\n"
"}\n"
""
                        "\n"
"QRadioButton::indicator {\n"
"    width:                  10px; \n"
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
"QEdit \n"
"{\n"
"	font-family: \"Segoe UI\";\n"
"	font-size: 12pt;\n"
"}\n"
"\n"
"QFrame[frameShape=\"4\"] /* QFrame::HLine == 0x0004 */\n"
"{\n"
"    color: red;\n"
"}\n"
"\n"
"QFrame[frameShape=\"5\"] /* QFrame::VLine == 0x0005 */\n"
"{\n"
"    color: green;\n"
"}\n"
"\n"
"QMessageBox  {\n"
" 	font-family: \"Segoe UI\";\n"
"	font-size: 12pt;\n"
"    border-width: 2px;\n"
"    border-radius: 10px;\n"
"    color: green;\n"
"}"));
        gridLayout_3 = new QGridLayout(report);
        gridLayout_3->setObjectName("gridLayout_3");
        grBoxBuletin = new QGroupBox(report);
        grBoxBuletin->setObjectName("grBoxBuletin");
        gridLayout_2 = new QGridLayout(grBoxBuletin);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lbBuletinNumber = new QLabel(grBoxBuletin);
        lbBuletinNumber->setObjectName("lbBuletinNumber");

        gridLayout->addWidget(lbBuletinNumber, 0, 0, 1, 1);

        lbNmlNtm = new QLabel(grBoxBuletin);
        lbNmlNtm->setObjectName("lbNmlNtm");

        gridLayout->addWidget(lbNmlNtm, 3, 0, 1, 1);

        lbCost = new QLabel(grBoxBuletin);
        lbCost->setObjectName("lbCost");

        gridLayout->addWidget(lbCost, 8, 0, 1, 1);

        lbChecker = new QLabel(grBoxBuletin);
        lbChecker->setObjectName("lbChecker");

        gridLayout->addWidget(lbChecker, 6, 0, 1, 1);

        cbValability = new QComboBox(grBoxBuletin);
        cbValability->setObjectName("cbValability");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(12);
        cbValability->setFont(font);

        gridLayout->addWidget(cbValability, 5, 1, 1, 1);

        leCostRon = new QLineEdit(grBoxBuletin);
        leCostRon->setObjectName("leCostRon");
        QFont font1;
        font1.setPointSize(12);
        leCostRon->setFont(font1);

        gridLayout->addWidget(leCostRon, 8, 1, 1, 1);

        lbEtaloane = new QLabel(grBoxBuletin);
        lbEtaloane->setObjectName("lbEtaloane");

        gridLayout->addWidget(lbEtaloane, 4, 0, 1, 1);

        lbMijlocMasurare = new QLabel(grBoxBuletin);
        lbMijlocMasurare->setObjectName("lbMijlocMasurare");

        gridLayout->addWidget(lbMijlocMasurare, 1, 0, 1, 1);

        leLtCode = new QLineEdit(grBoxBuletin);
        leLtCode->setObjectName("leLtCode");
        leLtCode->setFont(font1);

        gridLayout->addWidget(leLtCode, 2, 1, 1, 1);

        lbValabilitate = new QLabel(grBoxBuletin);
        lbValabilitate->setObjectName("lbValabilitate");

        gridLayout->addWidget(lbValabilitate, 5, 0, 1, 1);

        leMeansOfMeasurement = new QLineEdit(grBoxBuletin);
        leMeansOfMeasurement->setObjectName("leMeansOfMeasurement");
        leMeansOfMeasurement->setFont(font1);

        gridLayout->addWidget(leMeansOfMeasurement, 1, 1, 1, 1);

        lbCodulLt = new QLabel(grBoxBuletin);
        lbCodulLt->setObjectName("lbCodulLt");

        gridLayout->addWidget(lbCodulLt, 2, 0, 1, 1);

        leUsedSerie = new QLineEdit(grBoxBuletin);
        leUsedSerie->setObjectName("leUsedSerie");
        leUsedSerie->setFont(font1);

        gridLayout->addWidget(leUsedSerie, 4, 1, 1, 1);

        leNmlNtmNorms = new QLineEdit(grBoxBuletin);
        leNmlNtmNorms->setObjectName("leNmlNtmNorms");
        leNmlNtmNorms->setFont(font1);

        gridLayout->addWidget(leNmlNtmNorms, 3, 1, 1, 1);

        leBuletinNumber = new QLineEdit(grBoxBuletin);
        leBuletinNumber->setObjectName("leBuletinNumber");
        leBuletinNumber->setFont(font1);

        gridLayout->addWidget(leBuletinNumber, 0, 1, 1, 1);

        lbTehnicalSuperviser = new QLabel(grBoxBuletin);
        lbTehnicalSuperviser->setObjectName("lbTehnicalSuperviser");

        gridLayout->addWidget(lbTehnicalSuperviser, 7, 0, 1, 1);

        leChecker = new QLineEdit(grBoxBuletin);
        leChecker->setObjectName("leChecker");
        leChecker->setFont(font1);

        gridLayout->addWidget(leChecker, 6, 1, 1, 1);

        leTehnicalSuperviser = new QLineEdit(grBoxBuletin);
        leTehnicalSuperviser->setObjectName("leTehnicalSuperviser");
        leTehnicalSuperviser->setFont(font1);

        gridLayout->addWidget(leTehnicalSuperviser, 7, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbPrint = new QPushButton(grBoxBuletin);
        pbPrint->setObjectName("pbPrint");
        QFont font2;
        font2.setPointSize(9);
        pbPrint->setFont(font2);
        pbPrint->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pbPrint);

        pbClose = new QPushButton(grBoxBuletin);
        pbClose->setObjectName("pbClose");
        pbClose->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pbClose);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(grBoxBuletin, 0, 0, 1, 1);

        QWidget::setTabOrder(leBuletinNumber, leMeansOfMeasurement);
        QWidget::setTabOrder(leMeansOfMeasurement, leLtCode);
        QWidget::setTabOrder(leLtCode, leNmlNtmNorms);
        QWidget::setTabOrder(leNmlNtmNorms, leUsedSerie);
        QWidget::setTabOrder(leUsedSerie, cbValability);
        QWidget::setTabOrder(cbValability, leChecker);
        QWidget::setTabOrder(leChecker, leTehnicalSuperviser);
        QWidget::setTabOrder(leTehnicalSuperviser, leCostRon);

        retranslateUi(report);

        QMetaObject::connectSlotsByName(report);
    } // setupUi

    void retranslateUi(QDialog *report)
    {
        report->setWindowTitle(QString());
        grBoxBuletin->setTitle(QString());
        lbBuletinNumber->setText(QString());
        lbNmlNtm->setText(QString());
        lbCost->setText(QString());
        lbChecker->setText(QString());
        lbEtaloane->setText(QString());
        lbMijlocMasurare->setText(QString());
        lbValabilitate->setText(QString());
        lbCodulLt->setText(QString());
        lbTehnicalSuperviser->setText(QString());
        pbPrint->setText(QString());
        pbClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class report: public Ui_report {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORT_H
