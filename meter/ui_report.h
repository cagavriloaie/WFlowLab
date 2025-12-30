/********************************************************************************
** Form generated from reading UI file 'report.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
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
        report->resize(490, 400);
        report->setMinimumSize(QSize(490, 400));
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(), QIcon::Normal, QIcon::Off);
        report->setWindowIcon(icon);
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
        leAutorizatiaNumarul->setMinimumSize(QSize(0, 28));
        QFont font;
        font.setFamilies({QString::fromUtf8("Verdana")});
        font.setPointSize(12);
        leAutorizatiaNumarul->setFont(font);

        gridLayout->addWidget(leAutorizatiaNumarul, 0, 1, 1, 1);

        leBeneficiar = new QLineEdit(grBoxBuletin);
        leBeneficiar->setObjectName("leBeneficiar");
        leBeneficiar->setMinimumSize(QSize(0, 28));
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
        leCoduldinLt->setMinimumSize(QSize(0, 28));
        leCoduldinLt->setFont(font);

        gridLayout->addWidget(leCoduldinLt, 3, 1, 1, 1);

        cbValabilitate = new QComboBox(grBoxBuletin);
        cbValabilitate->setObjectName("cbValabilitate");
        cbValabilitate->setMinimumSize(QSize(0, 28));
        cbValabilitate->setFont(font);

        gridLayout->addWidget(cbValabilitate, 5, 1, 1, 1);

        leNumarInregistrare = new QLineEdit(grBoxBuletin);
        leNumarInregistrare->setObjectName("leNumarInregistrare");
        leNumarInregistrare->setMinimumSize(QSize(0, 28));
        leNumarInregistrare->setFont(font);

        gridLayout->addWidget(leNumarInregistrare, 1, 1, 1, 1);

        leCost = new QLineEdit(grBoxBuletin);
        leCost->setObjectName("leCost");
        leCost->setMinimumSize(QSize(0, 28));
        leCost->setFont(font);

        gridLayout->addWidget(leCost, 6, 1, 1, 1);

        lbNumarInregistrare = new QLabel(grBoxBuletin);
        lbNumarInregistrare->setObjectName("lbNumarInregistrare");

        gridLayout->addWidget(lbNumarInregistrare, 1, 0, 1, 1);

        leNormativ = new QLineEdit(grBoxBuletin);
        leNormativ->setObjectName("leNormativ");
        leNormativ->setMinimumSize(QSize(0, 28));
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
        leVerificatorMetrolog->setMinimumSize(QSize(0, 28));
        leVerificatorMetrolog->setFont(font);

        gridLayout->addWidget(leVerificatorMetrolog, 7, 1, 1, 1);

        lbNormativ = new QLabel(grBoxBuletin);
        lbNormativ->setObjectName("lbNormativ");

        gridLayout->addWidget(lbNormativ, 4, 0, 1, 1);

        leLoculEfectuariiVerificarii = new QLineEdit(grBoxBuletin);
        leLoculEfectuariiVerificarii->setObjectName("leLoculEfectuariiVerificarii");
        leLoculEfectuariiVerificarii->setMinimumSize(QSize(0, 28));
        leLoculEfectuariiVerificarii->setFont(font);

        gridLayout->addWidget(leLoculEfectuariiVerificarii, 8, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbGenerareBV = new QPushButton(grBoxBuletin);
        pbGenerareBV->setObjectName("pbGenerareBV");
        pbGenerareBV->setFont(font);
        pbGenerareBV->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pbGenerareBV);

        pbInchide = new QPushButton(grBoxBuletin);
        pbInchide->setObjectName("pbInchide");
        pbInchide->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pbInchide);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_3->addWidget(grBoxBuletin, 0, 0, 1, 1);

        QWidget::setTabOrder(leAutorizatiaNumarul, leNumarInregistrare);
        QWidget::setTabOrder(leNumarInregistrare, leBeneficiar);
        QWidget::setTabOrder(leBeneficiar, leCoduldinLt);
        QWidget::setTabOrder(leCoduldinLt, leNormativ);
        QWidget::setTabOrder(leNormativ, cbValabilitate);
        QWidget::setTabOrder(cbValabilitate, leCost);
        QWidget::setTabOrder(leCost, leVerificatorMetrolog);
        QWidget::setTabOrder(leVerificatorMetrolog, leLoculEfectuariiVerificarii);
        QWidget::setTabOrder(leLoculEfectuariiVerificarii, pbGenerareBV);
        QWidget::setTabOrder(pbGenerareBV, pbInchide);

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
#if QT_CONFIG(tooltip)
        pbGenerareBV->setToolTip(QCoreApplication::translate("report", "Genereaz\304\203 buletinul de verificare metrologic\304\203", nullptr));
#endif // QT_CONFIG(tooltip)
        pbGenerareBV->setText(QString());
#if QT_CONFIG(tooltip)
        pbInchide->setToolTip(QCoreApplication::translate("report", "\303\216nchide fereastra (Esc)", nullptr));
#endif // QT_CONFIG(tooltip)
        pbInchide->setText(QString());
#if QT_CONFIG(shortcut)
        pbInchide->setShortcut(QCoreApplication::translate("report", "Esc", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class report: public Ui_report {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORT_H
