/********************************************************************************
** Form generated from reading UI file 'HelpAbout.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPABOUT_H
#define UI_HELPABOUT_H

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

class Ui_HelpAbout
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *grAbout;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_header;
    QLabel *lbAppIcon;
    QSpacerItem *horizontalSpacer_left;
    QLabel *lbAppTitle;
    QSpacerItem *horizontalSpacer_right;
    QSpacerItem *horizontalSpacer_rightFixed;
    QLabel *lbAppSubtitle;
    QSpacerItem *verticalSpacer_2;
    QLabel *lbDescription;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_version;
    QLabel *lbVersion;
    QLabel *lbVersionValue;
    QHBoxLayout *horizontalLayout_platform;
    QLabel *lbPlatform;
    QLabel *lbPlatformValue;
    QHBoxLayout *horizontalLayout_build;
    QLabel *lbBuildDate;
    QLabel *lbBuildDateValue;
    QHBoxLayout *horizontalLayout_qt;
    QLabel *lbQtVersion;
    QLabel *lbQtVersionValue;
    QHBoxLayout *horizontalLayout_license;
    QLabel *lbLicense;
    QLabel *lbLicenseValue;
    QSpacerItem *verticalSpacer_4;
    QLabel *lbCompany;
    QLabel *lbCopyright;
    QLabel *lbAddress;
    QHBoxLayout *horizontalLayout_email;
    QLabel *lbEmailLabel;
    QLabel *lbEmail;
    QSpacerItem *horizontalSpacer_email;
    QHBoxLayout *horizontalLayout_website;
    QLabel *lbWebsiteLabel;
    QLabel *lbWebsite;
    QSpacerItem *horizontalSpacer_website;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *HelpAbout)
    {
        if (HelpAbout->objectName().isEmpty())
            HelpAbout->setObjectName("HelpAbout");
        HelpAbout->resize(510, 540);
        HelpAbout->setMinimumSize(QSize(510, 540));
        HelpAbout->setMaximumSize(QSize(510, 540));
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(), QIcon::Normal, QIcon::Off);
        HelpAbout->setWindowIcon(icon);
        gridLayout = new QGridLayout(HelpAbout);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        grAbout = new QGroupBox(HelpAbout);
        grAbout->setObjectName("grAbout");
        gridLayout_2 = new QGridLayout(grAbout);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_header = new QHBoxLayout();
        horizontalLayout_header->setObjectName("horizontalLayout_header");
        lbAppIcon = new QLabel(grAbout);
        lbAppIcon->setObjectName("lbAppIcon");
        lbAppIcon->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        lbAppIcon->setMinimumSize(QSize(64, 64));
        lbAppIcon->setMaximumSize(QSize(64, 64));
        lbAppIcon->setScaledContents(true);

        horizontalLayout_header->addWidget(lbAppIcon);

        horizontalSpacer_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_header->addItem(horizontalSpacer_left);

        lbAppTitle = new QLabel(grAbout);
        lbAppTitle->setObjectName("lbAppTitle");
        lbAppTitle->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        lbAppTitle->setFont(font);

        horizontalLayout_header->addWidget(lbAppTitle);

        horizontalSpacer_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_header->addItem(horizontalSpacer_right);

        horizontalSpacer_rightFixed = new QSpacerItem(64, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_header->addItem(horizontalSpacer_rightFixed);


        verticalLayout->addLayout(horizontalLayout_header);

        lbAppSubtitle = new QLabel(grAbout);
        lbAppSubtitle->setObjectName("lbAppSubtitle");
        lbAppSubtitle->setAlignment(Qt::AlignCenter);
        QFont font1;
        font1.setPointSize(10);
        lbAppSubtitle->setFont(font1);

        verticalLayout->addWidget(lbAppSubtitle);

        verticalSpacer_2 = new QSpacerItem(20, 3, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        lbDescription = new QLabel(grAbout);
        lbDescription->setObjectName("lbDescription");
        lbDescription->setWordWrap(true);
        lbDescription->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbDescription);

        verticalSpacer_3 = new QSpacerItem(20, 8, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_version = new QHBoxLayout();
        horizontalLayout_version->setObjectName("horizontalLayout_version");
        lbVersion = new QLabel(grAbout);
        lbVersion->setObjectName("lbVersion");
        lbVersion->setMinimumSize(QSize(70, 0));

        horizontalLayout_version->addWidget(lbVersion);

        lbVersionValue = new QLabel(grAbout);
        lbVersionValue->setObjectName("lbVersionValue");

        horizontalLayout_version->addWidget(lbVersionValue);


        verticalLayout->addLayout(horizontalLayout_version);

        horizontalLayout_platform = new QHBoxLayout();
        horizontalLayout_platform->setObjectName("horizontalLayout_platform");
        lbPlatform = new QLabel(grAbout);
        lbPlatform->setObjectName("lbPlatform");
        lbPlatform->setMinimumSize(QSize(70, 0));

        horizontalLayout_platform->addWidget(lbPlatform);

        lbPlatformValue = new QLabel(grAbout);
        lbPlatformValue->setObjectName("lbPlatformValue");

        horizontalLayout_platform->addWidget(lbPlatformValue);


        verticalLayout->addLayout(horizontalLayout_platform);

        horizontalLayout_build = new QHBoxLayout();
        horizontalLayout_build->setObjectName("horizontalLayout_build");
        lbBuildDate = new QLabel(grAbout);
        lbBuildDate->setObjectName("lbBuildDate");
        lbBuildDate->setMinimumSize(QSize(70, 0));

        horizontalLayout_build->addWidget(lbBuildDate);

        lbBuildDateValue = new QLabel(grAbout);
        lbBuildDateValue->setObjectName("lbBuildDateValue");

        horizontalLayout_build->addWidget(lbBuildDateValue);


        verticalLayout->addLayout(horizontalLayout_build);

        horizontalLayout_qt = new QHBoxLayout();
        horizontalLayout_qt->setObjectName("horizontalLayout_qt");
        lbQtVersion = new QLabel(grAbout);
        lbQtVersion->setObjectName("lbQtVersion");
        lbQtVersion->setMinimumSize(QSize(70, 0));

        horizontalLayout_qt->addWidget(lbQtVersion);

        lbQtVersionValue = new QLabel(grAbout);
        lbQtVersionValue->setObjectName("lbQtVersionValue");

        horizontalLayout_qt->addWidget(lbQtVersionValue);


        verticalLayout->addLayout(horizontalLayout_qt);

        horizontalLayout_license = new QHBoxLayout();
        horizontalLayout_license->setObjectName("horizontalLayout_license");
        lbLicense = new QLabel(grAbout);
        lbLicense->setObjectName("lbLicense");
        lbLicense->setMinimumSize(QSize(70, 0));

        horizontalLayout_license->addWidget(lbLicense);

        lbLicenseValue = new QLabel(grAbout);
        lbLicenseValue->setObjectName("lbLicenseValue");

        horizontalLayout_license->addWidget(lbLicenseValue);


        verticalLayout->addLayout(horizontalLayout_license);

        verticalSpacer_4 = new QSpacerItem(20, 8, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        lbCompany = new QLabel(grAbout);
        lbCompany->setObjectName("lbCompany");
        QFont font2;
        font2.setBold(true);
        lbCompany->setFont(font2);

        verticalLayout->addWidget(lbCompany);

        lbCopyright = new QLabel(grAbout);
        lbCopyright->setObjectName("lbCopyright");

        verticalLayout->addWidget(lbCopyright);

        lbAddress = new QLabel(grAbout);
        lbAddress->setObjectName("lbAddress");

        verticalLayout->addWidget(lbAddress);

        horizontalLayout_email = new QHBoxLayout();
        horizontalLayout_email->setObjectName("horizontalLayout_email");
        lbEmailLabel = new QLabel(grAbout);
        lbEmailLabel->setObjectName("lbEmailLabel");
        lbEmailLabel->setMinimumSize(QSize(60, 0));

        horizontalLayout_email->addWidget(lbEmailLabel);

        lbEmail = new QLabel(grAbout);
        lbEmail->setObjectName("lbEmail");

        horizontalLayout_email->addWidget(lbEmail);

        horizontalSpacer_email = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_email->addItem(horizontalSpacer_email);


        verticalLayout->addLayout(horizontalLayout_email);

        horizontalLayout_website = new QHBoxLayout();
        horizontalLayout_website->setObjectName("horizontalLayout_website");
        lbWebsiteLabel = new QLabel(grAbout);
        lbWebsiteLabel->setObjectName("lbWebsiteLabel");
        lbWebsiteLabel->setMinimumSize(QSize(60, 0));

        horizontalLayout_website->addWidget(lbWebsiteLabel);

        lbWebsite = new QLabel(grAbout);
        lbWebsite->setObjectName("lbWebsite");

        horizontalLayout_website->addWidget(lbWebsite);

        horizontalSpacer_website = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_website->addItem(horizontalSpacer_website);


        verticalLayout->addLayout(horizontalLayout_website);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(grAbout);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbClose = new QPushButton(HelpAbout);
        pbClose->setObjectName("pbClose");
        pbClose->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(pbClose);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(HelpAbout);

        QMetaObject::connectSlotsByName(HelpAbout);
    } // setupUi

    void retranslateUi(QDialog *HelpAbout)
    {
        HelpAbout->setWindowTitle(QCoreApplication::translate("HelpAbout", "WMeter - About", nullptr));
        grAbout->setTitle(QString());
        lbAppIcon->setText(QString());
        lbAppTitle->setText(QString());
        lbAppSubtitle->setText(QString());
        lbDescription->setText(QString());
        lbVersion->setText(QString());
        lbVersionValue->setText(QString());
        lbPlatform->setText(QString());
        lbPlatformValue->setText(QString());
        lbBuildDate->setText(QString());
        lbBuildDateValue->setText(QString());
        lbQtVersion->setText(QString());
        lbQtVersionValue->setText(QString());
        lbLicense->setText(QString());
        lbLicenseValue->setText(QString());
        lbCompany->setText(QString());
        lbCopyright->setText(QString());
        lbAddress->setText(QString());
        lbEmailLabel->setText(QCoreApplication::translate("HelpAbout", "Email:", nullptr));
        lbEmail->setText(QString());
        lbWebsiteLabel->setText(QCoreApplication::translate("HelpAbout", "Website:", nullptr));
        lbWebsite->setText(QString());
        pbClose->setText(QString());
#if QT_CONFIG(shortcut)
        pbClose->setShortcut(QCoreApplication::translate("HelpAbout", "Esc", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class HelpAbout: public Ui_HelpAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPABOUT_H
