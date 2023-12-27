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
    QLabel *lb3;
    QLabel *lb6;
    QLabel *lbChecker;
    QComboBox *cbValability;
    QLineEdit *leCostRon;
    QLabel *lb4;
    QLabel *lb1;
    QLineEdit *leLtCode;
    QLabel *lb5;
    QLineEdit *leMeansOfMeasurement;
    QLabel *lb2;
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
        {
            report->setObjectName("report");
        }
        report->resize(658, 384);
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(),
                     QIcon::Normal, QIcon::Off);
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
        lb3 = new QLabel(grBoxBuletin);
        lb3->setObjectName("lb3");
        gridLayout->addWidget(lb3, 3, 0, 1, 1);
        lb6 = new QLabel(grBoxBuletin);
        lb6->setObjectName("lb6");
        gridLayout->addWidget(lb6, 8, 0, 1, 1);
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
        lb4 = new QLabel(grBoxBuletin);
        lb4->setObjectName("lb4");
        gridLayout->addWidget(lb4, 4, 0, 1, 1);
        lb1 = new QLabel(grBoxBuletin);
        lb1->setObjectName("lb1");
        gridLayout->addWidget(lb1, 1, 0, 1, 1);
        leLtCode = new QLineEdit(grBoxBuletin);
        leLtCode->setObjectName("leLtCode");
        leLtCode->setFont(font1);
        gridLayout->addWidget(leLtCode, 2, 1, 1, 1);
        lb5 = new QLabel(grBoxBuletin);
        lb5->setObjectName("lb5");
        gridLayout->addWidget(lb5, 5, 0, 1, 1);
        leMeansOfMeasurement = new QLineEdit(grBoxBuletin);
        leMeansOfMeasurement->setObjectName("leMeansOfMeasurement");
        leMeansOfMeasurement->setFont(font1);
        gridLayout->addWidget(leMeansOfMeasurement, 1, 1, 1, 1);
        lb2 = new QLabel(grBoxBuletin);
        lb2->setObjectName("lb2");
        gridLayout->addWidget(lb2, 2, 0, 1, 1);
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
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                         QSizePolicy::Expanding);
        verticalLayout->addItem(verticalSpacer);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding,
                                           QSizePolicy::Minimum);
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
        report->setWindowTitle(QCoreApplication::translate("report",
                               "WFlowLab - Buletin de Verificare Metrologica", nullptr));
        grBoxBuletin->setTitle(QCoreApplication::translate("report",
                               "Date buletin verificare", nullptr));
        lbBuletinNumber->setText(QCoreApplication::translate("report",
                                 "Numar buletin:", nullptr));
        lb3->setText(QCoreApplication::translate("report",
                     "NML, NTM, alte normative:", nullptr));
        lb6->setText(QCoreApplication::translate("report", "Cost (RON):",
                     nullptr));
        lbChecker->setText(QCoreApplication::translate("report",
                           "Verificator metrolog:", nullptr));
        lb4->setText(QCoreApplication::translate("report",
                     "Etaloane utilizate, denumire, serie, nr. CE: ", nullptr));
        lb1->setText(QCoreApplication::translate("report",
                     "Mijloc de masurare apartinand:", nullptr));
        lb5->setText(QCoreApplication::translate("report",
                     "Valabilitatea verificarii:", nullptr));
        lb2->setText(QCoreApplication::translate("report", "Codul din LT:",
                     nullptr));
        lbTehnicalSuperviser->setText(QCoreApplication::translate("report",
                                      "Responsabil tehnic:", nullptr));
        pbPrint->setText(QCoreApplication::translate("report",
                         "&Tipareste PDF", nullptr));
        pbClose->setText(QCoreApplication::translate("report", "&Inchide",
                         nullptr));
    } // retranslateUi

};

namespace Ui
{
    class report: public Ui_report {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORT_H
