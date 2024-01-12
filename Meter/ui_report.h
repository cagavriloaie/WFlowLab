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
    QLabel *lbCodulDinLt;
    QLabel *lbCost;
    QLineEdit *leAutorizatiaNumarul;
    QLineEdit *leBeneficiar;
    QLabel *lbBeneficiar;
    QLabel *lbAutorizatiaNumarul;
    QLabel *lbLoculEfectuariiVerificarii;
    QLineEdit *leCoduldinLt;
    QComboBox *cbValabilitate;
    QLineEdit *leNumarInregistrare;
    QLineEdit *leCost;
    QLabel *lbNumarInregistrare;
    QLineEdit *leNormativ;
    QLabel *lbVerificatorMetrolog;
    QLabel *lbValabilitate;
    QLineEdit *leVerificatorMetrolog;
    QLabel *lbNormativ;
    QLineEdit *leLoculEfectuariiVerificarii;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbGenerareBV;
    QPushButton *pbInchide;

    void setupUi(QDialog *report)
    {
        if (report->objectName().isEmpty())
            report->setObjectName("report");
        report->resize(490, 351);
        report->setMinimumSize(QSize(490, 351));
        report->setMaximumSize(QSize(490, 351));
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
        lbCodulDinLt = new QLabel(grBoxBuletin);
        lbCodulDinLt->setObjectName("lbCodulDinLt");

        gridLayout->addWidget(lbCodulDinLt, 3, 0, 1, 1);

        lbCost = new QLabel(grBoxBuletin);
        lbCost->setObjectName("lbCost");

        gridLayout->addWidget(lbCost, 6, 0, 1, 1);

        leAutorizatiaNumarul = new QLineEdit(grBoxBuletin);
        leAutorizatiaNumarul->setObjectName("leAutorizatiaNumarul");
        QFont font;
        font.setPointSize(12);
        leAutorizatiaNumarul->setFont(font);

        gridLayout->addWidget(leAutorizatiaNumarul, 0, 1, 1, 1);

        leBeneficiar = new QLineEdit(grBoxBuletin);
        leBeneficiar->setObjectName("leBeneficiar");
        leBeneficiar->setFont(font);

        gridLayout->addWidget(leBeneficiar, 2, 1, 1, 1);

        lbBeneficiar = new QLabel(grBoxBuletin);
        lbBeneficiar->setObjectName("lbBeneficiar");

        gridLayout->addWidget(lbBeneficiar, 2, 0, 1, 1);

        lbAutorizatiaNumarul = new QLabel(grBoxBuletin);
        lbAutorizatiaNumarul->setObjectName("lbAutorizatiaNumarul");

        gridLayout->addWidget(lbAutorizatiaNumarul, 0, 0, 1, 1);

        lbLoculEfectuariiVerificarii = new QLabel(grBoxBuletin);
        lbLoculEfectuariiVerificarii->setObjectName("lbLoculEfectuariiVerificarii");

        gridLayout->addWidget(lbLoculEfectuariiVerificarii, 8, 0, 1, 1);

        leCoduldinLt = new QLineEdit(grBoxBuletin);
        leCoduldinLt->setObjectName("leCoduldinLt");
        leCoduldinLt->setFont(font);

        gridLayout->addWidget(leCoduldinLt, 3, 1, 1, 1);

        cbValabilitate = new QComboBox(grBoxBuletin);
        cbValabilitate->setObjectName("cbValabilitate");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(12);
        cbValabilitate->setFont(font1);

        gridLayout->addWidget(cbValabilitate, 5, 1, 1, 1);

        leNumarInregistrare = new QLineEdit(grBoxBuletin);
        leNumarInregistrare->setObjectName("leNumarInregistrare");
        leNumarInregistrare->setFont(font);

        gridLayout->addWidget(leNumarInregistrare, 1, 1, 1, 1);

        leCost = new QLineEdit(grBoxBuletin);
        leCost->setObjectName("leCost");
        leCost->setFont(font);

        gridLayout->addWidget(leCost, 6, 1, 1, 1);

        lbNumarInregistrare = new QLabel(grBoxBuletin);
        lbNumarInregistrare->setObjectName("lbNumarInregistrare");

        gridLayout->addWidget(lbNumarInregistrare, 1, 0, 1, 1);

        leNormativ = new QLineEdit(grBoxBuletin);
        leNormativ->setObjectName("leNormativ");
        leNormativ->setFont(font);

        gridLayout->addWidget(leNormativ, 4, 1, 1, 1);

        lbVerificatorMetrolog = new QLabel(grBoxBuletin);
        lbVerificatorMetrolog->setObjectName("lbVerificatorMetrolog");

        gridLayout->addWidget(lbVerificatorMetrolog, 7, 0, 1, 1);

        lbValabilitate = new QLabel(grBoxBuletin);
        lbValabilitate->setObjectName("lbValabilitate");

        gridLayout->addWidget(lbValabilitate, 5, 0, 1, 1);

        leVerificatorMetrolog = new QLineEdit(grBoxBuletin);
        leVerificatorMetrolog->setObjectName("leVerificatorMetrolog");
        leVerificatorMetrolog->setFont(font);

        gridLayout->addWidget(leVerificatorMetrolog, 7, 1, 1, 1);

        lbNormativ = new QLabel(grBoxBuletin);
        lbNormativ->setObjectName("lbNormativ");

        gridLayout->addWidget(lbNormativ, 4, 0, 1, 1);

        leLoculEfectuariiVerificarii = new QLineEdit(grBoxBuletin);
        leLoculEfectuariiVerificarii->setObjectName("leLoculEfectuariiVerificarii");
        leLoculEfectuariiVerificarii->setFont(font);

        gridLayout->addWidget(leLoculEfectuariiVerificarii, 8, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbGenerareBV = new QPushButton(grBoxBuletin);
        pbGenerareBV->setObjectName("pbGenerareBV");
        QFont font2;
        font2.setPointSize(9);
        pbGenerareBV->setFont(font2);
        pbGenerareBV->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pbGenerareBV);

        pbInchide = new QPushButton(grBoxBuletin);
        pbInchide->setObjectName("pbInchide");
        pbInchide->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pbInchide);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(grBoxBuletin, 0, 0, 1, 1);

        QWidget::setTabOrder(leNumarInregistrare, leBeneficiar);
        QWidget::setTabOrder(leBeneficiar, leCoduldinLt);
        QWidget::setTabOrder(leCoduldinLt, leNormativ);
        QWidget::setTabOrder(leNormativ, cbValabilitate);
        QWidget::setTabOrder(cbValabilitate, leCost);
        QWidget::setTabOrder(leCost, leVerificatorMetrolog);

        retranslateUi(report);

        QMetaObject::connectSlotsByName(report);
    } // setupUi

    void retranslateUi(QDialog *report)
    {
        report->setWindowTitle(QString());
        grBoxBuletin->setTitle(QString());
        lbCodulDinLt->setText(QString());
        lbCost->setText(QString());
        lbBeneficiar->setText(QString());
        lbAutorizatiaNumarul->setText(QString());
        lbLoculEfectuariiVerificarii->setText(QString());
        lbNumarInregistrare->setText(QString());
        lbVerificatorMetrolog->setText(QString());
        lbValabilitate->setText(QString());
        lbNormativ->setText(QString());
        pbGenerareBV->setText(QString());
        pbInchide->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class report: public Ui_report {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORT_H
