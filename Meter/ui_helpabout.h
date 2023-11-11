/********************************************************************************
** Form generated from reading UI file 'helpabout.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
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
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbName;
    QLabel *lbNameValue;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbCopyright;
    QLabel *lbCopyrightValue;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbEmail;
    QLabel *lbEmailValue;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lbAddress;
    QLabel *lbAddressValue;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lbAuthor;
    QLabel *lbAuthorValue;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *HelpAbout)
    {
        if (HelpAbout->objectName().isEmpty())
            HelpAbout->setObjectName("HelpAbout");
        HelpAbout->resize(390, 233);
        HelpAbout->setMinimumSize(QSize(390, 230));
        HelpAbout->setMaximumSize(QSize(390, 233));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons8-blur-80.png"), QSize(), QIcon::Normal, QIcon::Off);
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
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lbName = new QLabel(grAbout);
        lbName->setObjectName("lbName");

        horizontalLayout_2->addWidget(lbName);

        lbNameValue = new QLabel(grAbout);
        lbNameValue->setObjectName("lbNameValue");

        horizontalLayout_2->addWidget(lbNameValue);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        lbCopyright = new QLabel(grAbout);
        lbCopyright->setObjectName("lbCopyright");

        horizontalLayout_3->addWidget(lbCopyright);

        lbCopyrightValue = new QLabel(grAbout);
        lbCopyrightValue->setObjectName("lbCopyrightValue");

        horizontalLayout_3->addWidget(lbCopyrightValue);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        lbEmail = new QLabel(grAbout);
        lbEmail->setObjectName("lbEmail");

        horizontalLayout_4->addWidget(lbEmail);

        lbEmailValue = new QLabel(grAbout);
        lbEmailValue->setObjectName("lbEmailValue");

        horizontalLayout_4->addWidget(lbEmailValue);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        lbAddress = new QLabel(grAbout);
        lbAddress->setObjectName("lbAddress");

        horizontalLayout_5->addWidget(lbAddress);

        lbAddressValue = new QLabel(grAbout);
        lbAddressValue->setObjectName("lbAddressValue");

        horizontalLayout_5->addWidget(lbAddressValue);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        lbAuthor = new QLabel(grAbout);
        lbAuthor->setObjectName("lbAuthor");

        horizontalLayout_6->addWidget(lbAuthor);

        lbAuthorValue = new QLabel(grAbout);
        lbAuthorValue->setObjectName("lbAuthorValue");

        horizontalLayout_6->addWidget(lbAuthorValue);


        verticalLayout->addLayout(horizontalLayout_6);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(grAbout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbClose = new QPushButton(HelpAbout);
        pbClose->setObjectName("pbClose");

        horizontalLayout->addWidget(pbClose);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

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
        lbName->setText(QString());
        lbNameValue->setText(QString());
        lbCopyright->setText(QString());
        lbCopyrightValue->setText(QString());
        lbEmail->setText(QString());
        lbEmailValue->setText(QString());
        lbAddress->setText(QString());
        lbAddressValue->setText(QString());
        lbAuthor->setText(QString());
        lbAuthorValue->setText(QString());
        pbClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HelpAbout: public Ui_HelpAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPABOUT_H
