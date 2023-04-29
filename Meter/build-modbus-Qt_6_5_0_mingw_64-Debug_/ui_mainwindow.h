/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
  public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButtonHumidity;
    QPushButton *pushButtonTemperature;
    QLineEdit *leHumidity;
    QLineEdit *leTemperature;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
        {
            MainWindow->setObjectName("MainWindow");
        }
        MainWindow->resize(283, 138);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pushButtonHumidity = new QPushButton(centralwidget);
        pushButtonHumidity->setObjectName("pushButtonHumidity");
        gridLayout->addWidget(pushButtonHumidity, 1, 1, 1, 1);
        pushButtonTemperature = new QPushButton(centralwidget);
        pushButtonTemperature->setObjectName("pushButtonTemperature");
        gridLayout->addWidget(pushButtonTemperature, 1, 0, 1, 1);
        leHumidity = new QLineEdit(centralwidget);
        leHumidity->setObjectName("leHumidity");
        gridLayout->addWidget(leHumidity, 0, 1, 1, 1);
        leTemperature = new QLineEdit(centralwidget);
        leTemperature->setObjectName("leTemperature");
        gridLayout->addWidget(leTemperature, 0, 0, 1, 1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum,
                                         QSizePolicy::Expanding);
        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);
        verticalLayout->addLayout(gridLayout);
        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 283, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        retranslateUi(MainWindow);
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow",
                                   "MainWindow", nullptr));
        pushButtonHumidity->setText(QCoreApplication::translate("MainWindow",
                                    "Humidity", nullptr));
        pushButtonTemperature->setText(
            QCoreApplication::translate("MainWindow", "Temperature", nullptr));
    } // retranslateUi

};

namespace Ui
{
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
