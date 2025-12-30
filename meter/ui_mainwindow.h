/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_StartSession;
    QAction *action_Save;
    QAction *action_Print;
    QAction *action_Exit;
    QAction *action_ExitApp;
    QAction *action_English;
    QAction *action_Romana;
    QAction *action_General_Description;
    QAction *action_WaterDensity;
    QAction *actionLineEntry;
    QAction *actionAbout;
    QAction *action_License;
    QAction *action_About;
    QAction *action_Configure_Serial_Port;
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *gbInputData;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_6;
    QComboBox *cbWaterMeterType;
    QLabel *lbPressure;
    QLabel *lbTemperature;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *lePressure;
    QLabel *lbTab5;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *leTemperature;
    QLabel *lbTab3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lbHumidity;
    QComboBox *cbNumberOfWaterMeters;
    QLabel *lbWaterMeterType;
    QLabel *lbNumberOfWaterMeters;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *leHumidity;
    QLabel *lbTab4;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QGroupBox *gbMeasurementMethod;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbGravimetric;
    QRadioButton *rbVolumetric;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *gbReadMethod;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbManual;
    QRadioButton *rbInterface;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *gbWaterMeterFeatures;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QLabel *lbTransitionFlowUnit;
    QLabel *lbMinimumFlow;
    QSpacerItem *verticalSpacer;
    QLabel *lbMaximumFlowCurrent;
    QLabel *lbNominalFlow;
    QLabel *lbNominalDiameterUnit;
    QLabel *lbNominalErrorCurrent;
    QLabel *lbNominalDiameterCurrent;
    QLabel *lbNominalFlowCurrent;
    QLabel *lbTransitionFlowCurrent;
    QLabel *lbMinimumFlowCurrent;
    QLabel *lbTab;
    QLabel *lbNominalDiameter;
    QLabel *lbMaximumError;
    QLabel *lbMaximumFlowUnit;
    QLabel *lbTransitionFlow;
    QLabel *lbMaximumErrorCurrent;
    QLabel *lbMaximumErrorUnit;
    QLabel *lbNominalError;
    QLabel *lbNominalFlowUnit;
    QLabel *lbMaximumFlow;
    QLabel *lbMinimumFlowUnit;
    QLabel *lbNominalErrorUnit;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbConnected;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbNewSession;
    QPushButton *pbExitApplication;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Language;
    QMenu *menu_Help;
    QMenu *menuInterface;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(580, 620);
        MainWindow->setMinimumSize(QSize(580, 620));
        QFont font;
        font.setFamilies({QString::fromUtf8("Verdana")});
        font.setPointSize(12);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("WStreamLab.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setUnifiedTitleAndToolBarOnMac(true);
        action_StartSession = new QAction(MainWindow);
        action_StartSession->setObjectName("action_StartSession");
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName("action_Save");
        action_Print = new QAction(MainWindow);
        action_Print->setObjectName("action_Print");
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName("action_Exit");
        action_ExitApp = new QAction(MainWindow);
        action_ExitApp->setObjectName("action_ExitApp");
        action_English = new QAction(MainWindow);
        action_English->setObjectName("action_English");
        action_Romana = new QAction(MainWindow);
        action_Romana->setObjectName("action_Romana");
        action_General_Description = new QAction(MainWindow);
        action_General_Description->setObjectName("action_General_Description");
        action_WaterDensity = new QAction(MainWindow);
        action_WaterDensity->setObjectName("action_WaterDensity");
        actionLineEntry = new QAction(MainWindow);
        actionLineEntry->setObjectName("actionLineEntry");
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("accessories-character-map")));
        actionLineEntry->setIcon(icon1);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        action_License = new QAction(MainWindow);
        action_License->setObjectName("action_License");
        action_About = new QAction(MainWindow);
        action_About->setObjectName("action_About");
        action_Configure_Serial_Port = new QAction(MainWindow);
        action_Configure_Serial_Port->setObjectName("action_Configure_Serial_Port");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName("gridLayout_5");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(4);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(5, 5, 5, 5);
        gbInputData = new QGroupBox(centralwidget);
        gbInputData->setObjectName("gbInputData");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gbInputData->sizePolicy().hasHeightForWidth());
        gbInputData->setSizePolicy(sizePolicy);
        gbInputData->setMaximumSize(QSize(16777215, 200));
        gbInputData->setFont(font);
        gridLayout_2 = new QGridLayout(gbInputData);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        cbWaterMeterType = new QComboBox(gbInputData);
        cbWaterMeterType->setObjectName("cbWaterMeterType");
        cbWaterMeterType->setMinimumSize(QSize(300, 28));
        cbWaterMeterType->setMaximumSize(QSize(300, 23));
        cbWaterMeterType->setStyleSheet(QString::fromUtf8(""));

        gridLayout_6->addWidget(cbWaterMeterType, 1, 1, 1, 1);

        lbPressure = new QLabel(gbInputData);
        lbPressure->setObjectName("lbPressure");
        lbPressure->setMaximumSize(QSize(16777215, 20));

        gridLayout_6->addWidget(lbPressure, 4, 0, 1, 1);

        lbTemperature = new QLabel(gbInputData);
        lbTemperature->setObjectName("lbTemperature");
        lbTemperature->setMinimumSize(QSize(80, 20));
        lbTemperature->setMaximumSize(QSize(1000, 20));

        gridLayout_6->addWidget(lbTemperature, 2, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        lePressure = new QLineEdit(gbInputData);
        lePressure->setObjectName("lePressure");
        lePressure->setMinimumSize(QSize(100, 23));
        lePressure->setMaximumSize(QSize(100, 23));
        lePressure->setFont(font);
        lePressure->setCursorPosition(0);

        horizontalLayout_7->addWidget(lePressure);

        lbTab5 = new QLabel(gbInputData);
        lbTab5->setObjectName("lbTab5");
        lbTab5->setMinimumSize(QSize(0, 20));
        lbTab5->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_7->addWidget(lbTab5);


        gridLayout_6->addLayout(horizontalLayout_7, 4, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        leTemperature = new QLineEdit(gbInputData);
        leTemperature->setObjectName("leTemperature");
        leTemperature->setMinimumSize(QSize(100, 23));
        leTemperature->setMaximumSize(QSize(100, 23));
        leTemperature->setFont(font);

        horizontalLayout_5->addWidget(leTemperature);

        lbTab3 = new QLabel(gbInputData);
        lbTab3->setObjectName("lbTab3");
        lbTab3->setMinimumSize(QSize(50, 20));
        lbTab3->setMaximumSize(QSize(20, 20));

        horizontalLayout_5->addWidget(lbTab3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        gridLayout_6->addLayout(horizontalLayout_5, 2, 1, 1, 1);

        lbHumidity = new QLabel(gbInputData);
        lbHumidity->setObjectName("lbHumidity");
        lbHumidity->setMinimumSize(QSize(80, 20));
        lbHumidity->setMaximumSize(QSize(1000, 20));

        gridLayout_6->addWidget(lbHumidity, 3, 0, 1, 1);

        cbNumberOfWaterMeters = new QComboBox(gbInputData);
        cbNumberOfWaterMeters->setObjectName("cbNumberOfWaterMeters");
        cbNumberOfWaterMeters->setMinimumSize(QSize(100, 28));
        cbNumberOfWaterMeters->setMaximumSize(QSize(100, 23));
        cbNumberOfWaterMeters->setAutoFillBackground(false);
        cbNumberOfWaterMeters->setStyleSheet(QString::fromUtf8(""));

        gridLayout_6->addWidget(cbNumberOfWaterMeters, 0, 1, 1, 1);

        lbWaterMeterType = new QLabel(gbInputData);
        lbWaterMeterType->setObjectName("lbWaterMeterType");
        lbWaterMeterType->setMinimumSize(QSize(80, 20));
        lbWaterMeterType->setMaximumSize(QSize(1000, 20));

        gridLayout_6->addWidget(lbWaterMeterType, 1, 0, 1, 1);

        lbNumberOfWaterMeters = new QLabel(gbInputData);
        lbNumberOfWaterMeters->setObjectName("lbNumberOfWaterMeters");
        lbNumberOfWaterMeters->setMinimumSize(QSize(80, 20));
        lbNumberOfWaterMeters->setMaximumSize(QSize(1000, 20));

        gridLayout_6->addWidget(lbNumberOfWaterMeters, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        leHumidity = new QLineEdit(gbInputData);
        leHumidity->setObjectName("leHumidity");
        leHumidity->setMinimumSize(QSize(100, 23));
        leHumidity->setMaximumSize(QSize(100, 23));
        leHumidity->setFont(font);

        horizontalLayout_6->addWidget(leHumidity);

        lbTab4 = new QLabel(gbInputData);
        lbTab4->setObjectName("lbTab4");
        lbTab4->setMinimumSize(QSize(50, 20));
        lbTab4->setMaximumSize(QSize(20, 20));

        horizontalLayout_6->addWidget(lbTab4);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        gridLayout_6->addLayout(horizontalLayout_6, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_6);


        gridLayout_2->addLayout(verticalLayout_3, 2, 0, 1, 1);


        verticalLayout_5->addWidget(gbInputData);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        gbMeasurementMethod = new QGroupBox(centralwidget);
        gbMeasurementMethod->setObjectName("gbMeasurementMethod");
        gbMeasurementMethod->setMinimumSize(QSize(120, 0));
        gbMeasurementMethod->setFont(font);
        gridLayout_4 = new QGridLayout(gbMeasurementMethod);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(9, 9, -1, 9);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        rbGravimetric = new QRadioButton(gbMeasurementMethod);
        rbGravimetric->setObjectName("rbGravimetric");
        rbGravimetric->setMinimumSize(QSize(120, 20));
        rbGravimetric->setMaximumSize(QSize(16777215, 20));
        rbGravimetric->setFont(font);
        rbGravimetric->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(rbGravimetric);

        rbVolumetric = new QRadioButton(gbMeasurementMethod);
        rbVolumetric->setObjectName("rbVolumetric");
        rbVolumetric->setMinimumSize(QSize(120, 20));
        rbVolumetric->setMaximumSize(QSize(16777215, 20));
        rbVolumetric->setFont(font);

        verticalLayout_2->addWidget(rbVolumetric);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 1, 0, 1, 1);


        horizontalLayout->addWidget(gbMeasurementMethod);

        gbReadMethod = new QGroupBox(centralwidget);
        gbReadMethod->setObjectName("gbReadMethod");
        gbReadMethod->setMinimumSize(QSize(100, 0));
        gbReadMethod->setFont(font);
        gridLayout_7 = new QGridLayout(gbReadMethod);
        gridLayout_7->setObjectName("gridLayout_7");
        gridLayout_7->setContentsMargins(9, 9, 9, 9);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        rbManual = new QRadioButton(gbReadMethod);
        rbManual->setObjectName("rbManual");
        rbManual->setMinimumSize(QSize(120, 20));
        rbManual->setMaximumSize(QSize(16777215, 20));
        rbManual->setFont(font);

        verticalLayout->addWidget(rbManual);

        rbInterface = new QRadioButton(gbReadMethod);
        rbInterface->setObjectName("rbInterface");
        rbInterface->setMinimumSize(QSize(120, 20));
        rbInterface->setMaximumSize(QSize(16777215, 20));
        rbInterface->setFont(font);

        verticalLayout->addWidget(rbInterface);


        gridLayout_7->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_7->addItem(verticalSpacer_4, 1, 0, 1, 1);


        horizontalLayout->addWidget(gbReadMethod);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        gbWaterMeterFeatures = new QGroupBox(centralwidget);
        gbWaterMeterFeatures->setObjectName("gbWaterMeterFeatures");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gbWaterMeterFeatures->sizePolicy().hasHeightForWidth());
        gbWaterMeterFeatures->setSizePolicy(sizePolicy1);
        gbWaterMeterFeatures->setMaximumSize(QSize(16777215, 200));
        gbWaterMeterFeatures->setFont(font);
        gbWaterMeterFeatures->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        gridLayout_3 = new QGridLayout(gbWaterMeterFeatures);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lbTransitionFlowUnit = new QLabel(gbWaterMeterFeatures);
        lbTransitionFlowUnit->setObjectName("lbTransitionFlowUnit");

        gridLayout->addWidget(lbTransitionFlowUnit, 3, 3, 1, 1);

        lbMinimumFlow = new QLabel(gbWaterMeterFeatures);
        lbMinimumFlow->setObjectName("lbMinimumFlow");

        gridLayout->addWidget(lbMinimumFlow, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 1, 1, 1);

        lbMaximumFlowCurrent = new QLabel(gbWaterMeterFeatures);
        lbMaximumFlowCurrent->setObjectName("lbMaximumFlowCurrent");

        gridLayout->addWidget(lbMaximumFlowCurrent, 1, 1, 1, 1);

        lbNominalFlow = new QLabel(gbWaterMeterFeatures);
        lbNominalFlow->setObjectName("lbNominalFlow");

        gridLayout->addWidget(lbNominalFlow, 2, 0, 1, 1);

        lbNominalDiameterUnit = new QLabel(gbWaterMeterFeatures);
        lbNominalDiameterUnit->setObjectName("lbNominalDiameterUnit");

        gridLayout->addWidget(lbNominalDiameterUnit, 0, 3, 1, 1);

        lbNominalErrorCurrent = new QLabel(gbWaterMeterFeatures);
        lbNominalErrorCurrent->setObjectName("lbNominalErrorCurrent");

        gridLayout->addWidget(lbNominalErrorCurrent, 6, 1, 1, 1);

        lbNominalDiameterCurrent = new QLabel(gbWaterMeterFeatures);
        lbNominalDiameterCurrent->setObjectName("lbNominalDiameterCurrent");

        gridLayout->addWidget(lbNominalDiameterCurrent, 0, 1, 1, 1);

        lbNominalFlowCurrent = new QLabel(gbWaterMeterFeatures);
        lbNominalFlowCurrent->setObjectName("lbNominalFlowCurrent");

        gridLayout->addWidget(lbNominalFlowCurrent, 2, 1, 1, 1);

        lbTransitionFlowCurrent = new QLabel(gbWaterMeterFeatures);
        lbTransitionFlowCurrent->setObjectName("lbTransitionFlowCurrent");

        gridLayout->addWidget(lbTransitionFlowCurrent, 3, 1, 1, 1);

        lbMinimumFlowCurrent = new QLabel(gbWaterMeterFeatures);
        lbMinimumFlowCurrent->setObjectName("lbMinimumFlowCurrent");

        gridLayout->addWidget(lbMinimumFlowCurrent, 4, 1, 1, 1);

        lbTab = new QLabel(gbWaterMeterFeatures);
        lbTab->setObjectName("lbTab");

        gridLayout->addWidget(lbTab, 0, 4, 1, 1);

        lbNominalDiameter = new QLabel(gbWaterMeterFeatures);
        lbNominalDiameter->setObjectName("lbNominalDiameter");

        gridLayout->addWidget(lbNominalDiameter, 0, 0, 1, 1);

        lbMaximumError = new QLabel(gbWaterMeterFeatures);
        lbMaximumError->setObjectName("lbMaximumError");

        gridLayout->addWidget(lbMaximumError, 5, 0, 1, 1);

        lbMaximumFlowUnit = new QLabel(gbWaterMeterFeatures);
        lbMaximumFlowUnit->setObjectName("lbMaximumFlowUnit");

        gridLayout->addWidget(lbMaximumFlowUnit, 1, 3, 1, 1);

        lbTransitionFlow = new QLabel(gbWaterMeterFeatures);
        lbTransitionFlow->setObjectName("lbTransitionFlow");
        lbTransitionFlow->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(lbTransitionFlow, 3, 0, 1, 1);

        lbMaximumErrorCurrent = new QLabel(gbWaterMeterFeatures);
        lbMaximumErrorCurrent->setObjectName("lbMaximumErrorCurrent");

        gridLayout->addWidget(lbMaximumErrorCurrent, 5, 1, 1, 1);

        lbMaximumErrorUnit = new QLabel(gbWaterMeterFeatures);
        lbMaximumErrorUnit->setObjectName("lbMaximumErrorUnit");

        gridLayout->addWidget(lbMaximumErrorUnit, 5, 3, 1, 1);

        lbNominalError = new QLabel(gbWaterMeterFeatures);
        lbNominalError->setObjectName("lbNominalError");

        gridLayout->addWidget(lbNominalError, 6, 0, 1, 1);

        lbNominalFlowUnit = new QLabel(gbWaterMeterFeatures);
        lbNominalFlowUnit->setObjectName("lbNominalFlowUnit");

        gridLayout->addWidget(lbNominalFlowUnit, 2, 3, 1, 1);

        lbMaximumFlow = new QLabel(gbWaterMeterFeatures);
        lbMaximumFlow->setObjectName("lbMaximumFlow");

        gridLayout->addWidget(lbMaximumFlow, 1, 0, 1, 1);

        lbMinimumFlowUnit = new QLabel(gbWaterMeterFeatures);
        lbMinimumFlowUnit->setObjectName("lbMinimumFlowUnit");

        gridLayout->addWidget(lbMinimumFlowUnit, 4, 3, 1, 1);

        lbNominalErrorUnit = new QLabel(gbWaterMeterFeatures);
        lbNominalErrorUnit->setObjectName("lbNominalErrorUnit");

        gridLayout->addWidget(lbNominalErrorUnit, 6, 3, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);


        horizontalLayout_2->addWidget(gbWaterMeterFeatures);


        verticalLayout_5->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        lbConnected = new QLabel(centralwidget);
        lbConnected->setObjectName("lbConnected");
        lbConnected->setFont(font);

        horizontalLayout_4->addWidget(lbConnected);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pbNewSession = new QPushButton(centralwidget);
        pbNewSession->setObjectName("pbNewSession");

        horizontalLayout_4->addWidget(pbNewSession);

        pbExitApplication = new QPushButton(centralwidget);
        pbExitApplication->setObjectName("pbExitApplication");

        horizontalLayout_4->addWidget(pbExitApplication);


        verticalLayout_5->addLayout(horizontalLayout_4);


        gridLayout_5->addLayout(verticalLayout_5, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 580, 30));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName("menu_File");
        menu_File->setToolTipDuration(-1);
        menu_Language = new QMenu(menubar);
        menu_Language->setObjectName("menu_Language");
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName("menu_Help");
        menuInterface = new QMenu(menubar);
        menuInterface->setObjectName("menuInterface");
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(cbNumberOfWaterMeters, cbWaterMeterType);
        QWidget::setTabOrder(cbWaterMeterType, leTemperature);
        QWidget::setTabOrder(leTemperature, leHumidity);
        QWidget::setTabOrder(leHumidity, lePressure);
        QWidget::setTabOrder(lePressure, rbGravimetric);
        QWidget::setTabOrder(rbGravimetric, rbVolumetric);
        QWidget::setTabOrder(rbVolumetric, rbManual);
        QWidget::setTabOrder(rbManual, rbInterface);
        QWidget::setTabOrder(rbInterface, pbNewSession);
        QWidget::setTabOrder(pbNewSession, pbExitApplication);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menuInterface->menuAction());
        menubar->addAction(menu_Language->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_StartSession);
        menu_File->addSeparator();
        menu_File->addAction(action_ExitApp);
        menu_Language->addAction(action_English);
        menu_Language->addAction(action_Romana);
        menu_Help->addAction(action_General_Description);
        menu_Help->addAction(action_WaterDensity);
        menu_Help->addSeparator();
        menu_Help->addAction(action_License);
        menu_Help->addSeparator();
        menu_Help->addAction(action_About);
        menuInterface->addAction(action_Configure_Serial_Port);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        action_StartSession->setText(QString());
#if QT_CONFIG(shortcut)
        action_StartSession->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Save->setText(QCoreApplication::translate("MainWindow", "&Save", nullptr));
#if QT_CONFIG(shortcut)
        action_Save->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Print->setText(QCoreApplication::translate("MainWindow", "&Print", nullptr));
#if QT_CONFIG(shortcut)
        action_Print->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Exit->setText(QCoreApplication::translate("MainWindow", "&Exit", nullptr));
        action_ExitApp->setText(QString());
#if QT_CONFIG(shortcut)
        action_ExitApp->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        action_English->setText(QString());
        action_Romana->setText(QString());
        action_General_Description->setText(QString());
        action_WaterDensity->setText(QString());
#if QT_CONFIG(shortcut)
        action_WaterDensity->setShortcut(QCoreApplication::translate("MainWindow", "F2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLineEntry->setText(QCoreApplication::translate("MainWindow", "LineEntry", nullptr));
#if QT_CONFIG(tooltip)
        actionLineEntry->setToolTip(QCoreApplication::translate("MainWindow", "water meter entry", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        action_License->setText(QString());
#if QT_CONFIG(shortcut)
        action_License->setShortcut(QCoreApplication::translate("MainWindow", "F3", nullptr));
#endif // QT_CONFIG(shortcut)
        action_About->setText(QString());
#if QT_CONFIG(shortcut)
        action_About->setShortcut(QCoreApplication::translate("MainWindow", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Configure_Serial_Port->setText(QCoreApplication::translate("MainWindow", "Configure Serial Port", nullptr));
        gbInputData->setTitle(QString());
#if QT_CONFIG(tooltip)
        cbWaterMeterType->setToolTip(QCoreApplication::translate("MainWindow", "Selecteaz\304\203 tipul de apometru pentru verificare", nullptr));
#endif // QT_CONFIG(tooltip)
        lbPressure->setText(QString());
        lbTemperature->setText(QString());
#if QT_CONFIG(tooltip)
        lePressure->setToolTip(QCoreApplication::translate("MainWindow", "Presiunea atmosferic\304\203 \303\256n mbar", nullptr));
#endif // QT_CONFIG(tooltip)
        lbTab5->setText(QString());
#if QT_CONFIG(tooltip)
        leTemperature->setToolTip(QCoreApplication::translate("MainWindow", "Temperatura ambiant\304\203 \303\256n grade Celsius", nullptr));
#endif // QT_CONFIG(tooltip)
        lbTab3->setText(QString());
        lbHumidity->setText(QString());
#if QT_CONFIG(tooltip)
        cbNumberOfWaterMeters->setToolTip(QCoreApplication::translate("MainWindow", "Num\304\203rul de apometre de verificat \303\256n aceast\304\203 sesiune", nullptr));
#endif // QT_CONFIG(tooltip)
        lbWaterMeterType->setText(QString());
        lbNumberOfWaterMeters->setText(QString());
#if QT_CONFIG(tooltip)
        leHumidity->setToolTip(QCoreApplication::translate("MainWindow", "Umiditatea relativ\304\203 a aerului \303\256n procente", nullptr));
#endif // QT_CONFIG(tooltip)
        lbTab4->setText(QString());
        gbMeasurementMethod->setTitle(QString());
#if QT_CONFIG(tooltip)
        rbGravimetric->setToolTip(QCoreApplication::translate("MainWindow", "Metoda gravimetric\304\203 - determinare prin c\303\242nt\304\203rire", nullptr));
#endif // QT_CONFIG(tooltip)
        rbGravimetric->setText(QString());
#if QT_CONFIG(tooltip)
        rbVolumetric->setToolTip(QCoreApplication::translate("MainWindow", "Metoda volumetric\304\203 - determinare prin m\304\203surare volum", nullptr));
#endif // QT_CONFIG(tooltip)
        rbVolumetric->setText(QString());
        gbReadMethod->setTitle(QString());
#if QT_CONFIG(tooltip)
        rbManual->setToolTip(QCoreApplication::translate("MainWindow", "Introducere manual\304\203 a valorilor", nullptr));
#endif // QT_CONFIG(tooltip)
        rbManual->setText(QString());
#if QT_CONFIG(tooltip)
        rbInterface->setToolTip(QCoreApplication::translate("MainWindow", "Citire automat\304\203 prin interfa\310\233\304\203 de comunicare", nullptr));
#endif // QT_CONFIG(tooltip)
        rbInterface->setText(QString());
        gbWaterMeterFeatures->setTitle(QString());
        lbTransitionFlowUnit->setText(QString());
        lbMinimumFlow->setText(QString());
        lbMaximumFlowCurrent->setText(QString());
        lbNominalFlow->setText(QString());
        lbNominalDiameterUnit->setText(QString());
        lbNominalErrorCurrent->setText(QString());
        lbNominalDiameterCurrent->setText(QString());
        lbNominalFlowCurrent->setText(QString());
        lbTransitionFlowCurrent->setText(QString());
        lbMinimumFlowCurrent->setText(QString());
        lbTab->setText(QString());
        lbNominalDiameter->setText(QString());
        lbMaximumError->setText(QString());
        lbMaximumFlowUnit->setText(QString());
        lbTransitionFlow->setText(QString());
        lbMaximumErrorCurrent->setText(QString());
        lbMaximumErrorUnit->setText(QString());
        lbNominalError->setText(QString());
        lbNominalFlowUnit->setText(QString());
        lbMaximumFlow->setText(QString());
        lbMinimumFlowUnit->setText(QString());
        lbNominalErrorUnit->setText(QString());
        lbConnected->setText(QString());
#if QT_CONFIG(tooltip)
        pbNewSession->setToolTip(QCoreApplication::translate("MainWindow", "\303\216ncepe o nou\304\203 sesiune de verificare (Ctrl+N)", nullptr));
#endif // QT_CONFIG(tooltip)
        pbNewSession->setText(QString());
#if QT_CONFIG(tooltip)
        pbExitApplication->setToolTip(QCoreApplication::translate("MainWindow", "\303\216nchide aplica\310\233ia (Ctrl+Q)", nullptr));
#endif // QT_CONFIG(tooltip)
        pbExitApplication->setText(QString());
        menu_File->setTitle(QString());
        menu_Language->setTitle(QString());
        menu_Help->setTitle(QString());
        menuInterface->setTitle(QCoreApplication::translate("MainWindow", "Interface", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
