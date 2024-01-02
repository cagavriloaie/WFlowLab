/********************************************************************************
** Form generated from reading UI file 'license.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LICENSE_H
#define UI_LICENSE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Licence
{
  public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lbChecksumValue;
    QLabel *lbChecksum;
    QLabel *lbCertificate;
    QLabel *lbMaximum;
    QLabel *lbMaximumValue;
    QLabel *lbArchive;
    QLabel *lbCompanyValue;
    QLabel *lbArchiveValue;
    QLabel *lbCertificateValue;
    QLabel *lbCompany;
    QLabel *lbDensity;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbDensityValue;
    QLabel *lbDensityUnit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Licence)
    {
        if (Licence->objectName().isEmpty())
        {
            Licence->setObjectName("Licence");
        }
        Licence->resize(520, 301);
        Licence->setMinimumSize(QSize(520, 301));
        Licence->setMaximumSize(QSize(520, 301));
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(),
                     QIcon::Normal, QIcon::Off);
        Licence->setWindowIcon(icon);
        Licence->setStyleSheet(QString::fromUtf8("QPushButton:hover {\n"
                               "       background-color: #d7d9d7;\n"
                               "}"));
        verticalLayoutWidget = new QWidget(Licence);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(11, 11, 498, 281));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName("groupBox");
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lbChecksumValue = new QLabel(groupBox);
        lbChecksumValue->setObjectName("lbChecksumValue");
        QFont font;
        font.setPointSize(12);
        lbChecksumValue->setFont(font);
        gridLayout->addWidget(lbChecksumValue, 5, 1, 1, 1);
        lbChecksum = new QLabel(groupBox);
        lbChecksum->setObjectName("lbChecksum");
        lbChecksum->setFont(font);
        gridLayout->addWidget(lbChecksum, 5, 0, 1, 1);
        lbCertificate = new QLabel(groupBox);
        lbCertificate->setObjectName("lbCertificate");
        lbCertificate->setFont(font);
        gridLayout->addWidget(lbCertificate, 1, 0, 1, 1);
        lbMaximum = new QLabel(groupBox);
        lbMaximum->setObjectName("lbMaximum");
        lbMaximum->setFont(font);
        gridLayout->addWidget(lbMaximum, 3, 0, 1, 1);
        lbMaximumValue = new QLabel(groupBox);
        lbMaximumValue->setObjectName("lbMaximumValue");
        lbMaximumValue->setFont(font);
        gridLayout->addWidget(lbMaximumValue, 3, 1, 1, 1);
        lbArchive = new QLabel(groupBox);
        lbArchive->setObjectName("lbArchive");
        lbArchive->setFont(font);
        gridLayout->addWidget(lbArchive, 2, 0, 1, 1);
        lbCompanyValue = new QLabel(groupBox);
        lbCompanyValue->setObjectName("lbCompanyValue");
        lbCompanyValue->setFont(font);
        gridLayout->addWidget(lbCompanyValue, 0, 1, 1, 1);
        lbArchiveValue = new QLabel(groupBox);
        lbArchiveValue->setObjectName("lbArchiveValue");
        lbArchiveValue->setFont(font);
        gridLayout->addWidget(lbArchiveValue, 2, 1, 1, 1);
        lbCertificateValue = new QLabel(groupBox);
        lbCertificateValue->setObjectName("lbCertificateValue");
        lbCertificateValue->setFont(font);
        gridLayout->addWidget(lbCertificateValue, 1, 1, 1, 1);
        lbCompany = new QLabel(groupBox);
        lbCompany->setObjectName("lbCompany");
        lbCompany->setFont(font);
        gridLayout->addWidget(lbCompany, 0, 0, 1, 1);
        lbDensity = new QLabel(groupBox);
        lbDensity->setObjectName("lbDensity");
        lbDensity->setFont(font);
        gridLayout->addWidget(lbDensity, 4, 0, 1, 1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        lbDensityValue = new QLabel(groupBox);
        lbDensityValue->setObjectName("lbDensityValue");
        lbDensityValue->setMaximumSize(QSize(65, 16777215));
        lbDensityValue->setFont(font);
        horizontalLayout_3->addWidget(lbDensityValue);
        lbDensityUnit = new QLabel(groupBox);
        lbDensityUnit->setObjectName("lbDensityUnit");
        lbDensityUnit->setFont(font);
        horizontalLayout_3->addWidget(lbDensityUnit);
        gridLayout->addLayout(horizontalLayout_3, 4, 1, 1, 1);
        verticalLayout->addLayout(gridLayout);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                         QSizePolicy::Expanding);
        verticalLayout->addItem(verticalSpacer);
        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);
        verticalLayout_2->addWidget(groupBox);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding,
                                           QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);
        pbClose = new QPushButton(verticalLayoutWidget);
        pbClose->setObjectName("pbClose");
        pbClose->setFont(font);
        pbClose->setStyleSheet(QString::fromUtf8(" padding-left: 10px; \n"
                               " padding-top: 1px; \n"
                               " padding-right: 10px;\n"
                               " padding-down: 10px; "));
        horizontalLayout->addWidget(pbClose);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding,
                                             QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer_2);
        verticalLayout_2->addLayout(horizontalLayout);
        retranslateUi(Licence);
        QMetaObject::connectSlotsByName(Licence);
    } // setupUi

    void retranslateUi(QDialog *Licence)
    {
        Licence->setWindowTitle(QString());
        groupBox->setTitle(QString());
        lbChecksumValue->setText(QString());
        lbChecksum->setText(QString());
        lbCertificate->setText(QString());
        lbMaximum->setText(QString());
        lbMaximumValue->setText(QString());
        lbArchive->setText(QString());
        lbCompanyValue->setText(QString());
        lbArchiveValue->setText(QString());
        lbCertificateValue->setText(QString());
        lbCompany->setText(QString());
        lbDensity->setText(QString());
        lbDensityValue->setText(QString());
        lbDensityUnit->setText(QString());
        pbClose->setText(QString());
    } // retranslateUi

};

namespace Ui
{
    class Licence: public Ui_Licence {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LICENSE_H
