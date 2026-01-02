/********************************************************************************
** Form generated from reading UI file 'license.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
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

QT_BEGIN_NAMESPACE

class Ui_Licence
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lbChecksumValue;
    QLabel *lbChecksum;
    QLabel *lbCertificate;
    QLabel *lbVolumeCorrection;
    QLabel *lbVolumeCorrectionValue;
    QLabel *lbArchive;
    QLabel *lbCompanyValue;
    QLabel *lbArchiveValue;
    QLabel *lbCertificateValue;
    QLabel *lbCompany;
    QLabel *lbDensity;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbDensityValue;
    QLabel *lbDensityUnit;
    QLabel *lbFileLocation;
    QLabel *lbFileLocationValue;
    QLabel *lbElcostInfo;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Licence)
    {
        if (Licence->objectName().isEmpty())
            Licence->setObjectName("Licence");
        Licence->resize(560, 305);
        Licence->setMinimumSize(QSize(560, 290));
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Licence->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(Licence);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setVerticalSpacing(9);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(Licence);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setVerticalSpacing(20);
        gridLayout_3->setContentsMargins(-1, 3, -1, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lbChecksumValue = new QLabel(groupBox);
        lbChecksumValue->setObjectName("lbChecksumValue");
        QFont font;
        font.setFamilies({QString::fromUtf8("Verdana")});
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

        lbVolumeCorrection = new QLabel(groupBox);
        lbVolumeCorrection->setObjectName("lbVolumeCorrection");
        lbVolumeCorrection->setFont(font);

        gridLayout->addWidget(lbVolumeCorrection, 3, 0, 1, 1);

        lbVolumeCorrectionValue = new QLabel(groupBox);
        lbVolumeCorrectionValue->setObjectName("lbVolumeCorrectionValue");
        lbVolumeCorrectionValue->setFont(font);

        gridLayout->addWidget(lbVolumeCorrectionValue, 3, 1, 1, 1);

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
        lbDensityValue->setMaximumSize(QSize(79, 16777215));
        lbDensityValue->setFont(font);

        horizontalLayout_3->addWidget(lbDensityValue);

        lbDensityUnit = new QLabel(groupBox);
        lbDensityUnit->setObjectName("lbDensityUnit");
        lbDensityUnit->setFont(font);

        horizontalLayout_3->addWidget(lbDensityUnit);


        gridLayout->addLayout(horizontalLayout_3, 4, 1, 1, 1);

        lbFileLocation = new QLabel(groupBox);
        lbFileLocation->setObjectName("lbFileLocation");
        lbFileLocation->setFont(font);

        gridLayout->addWidget(lbFileLocation, 6, 0, 1, 1);

        lbFileLocationValue = new QLabel(groupBox);
        lbFileLocationValue->setObjectName("lbFileLocationValue");
        lbFileLocationValue->setFont(font);
        lbFileLocationValue->setWordWrap(true);

        gridLayout->addWidget(lbFileLocationValue, 6, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        lbElcostInfo = new QLabel(Licence);
        lbElcostInfo->setObjectName("lbElcostInfo");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Verdana")});
        font1.setPointSize(4);
        font1.setItalic(true);
        lbElcostInfo->setFont(font1);
        lbElcostInfo->setAlignment(Qt::AlignCenter);
        lbElcostInfo->setWordWrap(false);

        verticalLayout_2->addWidget(lbElcostInfo);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(-1, 9, -1, 5);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbClose = new QPushButton(Licence);
        pbClose->setObjectName("pbClose");
        pbClose->setMaximumSize(QSize(16777215, 29));
        pbClose->setFont(font);
        pbClose->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pbClose);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


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
        lbVolumeCorrection->setText(QString());
        lbVolumeCorrectionValue->setText(QString());
        lbArchive->setText(QString());
        lbCompanyValue->setText(QString());
        lbArchiveValue->setText(QString());
        lbCertificateValue->setText(QString());
        lbCompany->setText(QString());
        lbDensity->setText(QString());
        lbDensityValue->setText(QString());
        lbDensityUnit->setText(QString());
        lbFileLocation->setText(QString());
        lbFileLocationValue->setText(QString());
        lbElcostInfo->setText(QString());
        pbClose->setText(QString());
#if QT_CONFIG(shortcut)
        pbClose->setShortcut(QCoreApplication::translate("Licence", "Esc", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class Licence: public Ui_Licence {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LICENSE_H
