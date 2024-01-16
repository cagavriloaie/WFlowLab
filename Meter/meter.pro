# Project configuration
QT += core gui printsupport widgets serialbus

# Use widgets module for versions greater than 4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Set C++ standard to C++17
CONFIG += c++17

# Enable all warnings
#QMAKE_CXXFLAGS += -Wall -Wextra

# Uncomment the following line to treat warnings as errors
# QMAKE_CXXFLAGS += -Werror

# Uncomment the following line to make your code fail to compile if it uses deprecated APIs
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000  # disables all the APIs deprecated before Qt 6.0.0

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    interface.cpp \
    air-density.cpp \
    helpabout.cpp \
    ledindicator.cpp \
    license.cpp \
    md5.cpp \
    report.cpp \
    tableBoard.cpp

# Header files
HEADERS += \
    mainwindow.h \
    interface.h \
    air-density.h \
    definitions.h \
    flow-meter-type.h \
    helpabout.h \
    ledindicator.h \
    license.h \
    md5.h \
    report.h \
    tableBoard.h

# UI form files
FORMS += \
    mainwindow.ui \
    interface.ui \
    helpabout.ui \
    license.ui \
    report.ui \
    tableBoard.ui

# Translation configuration
CONFIG += lrelease
lrelease.input = TRANSLATIONS
lrelease.output = ${QMAKE_FILE_BASE}.qm
lrelease.commands = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_BASE}.qm

CONFIG += embed_translations
TRANSLATIONS += translations/meter_ro_RO.ts translations/meter_en_EN.ts

# Deployment configuration
TARGET = WStreamLab

# Distribution files
DISTFILES += water-meter-counter-equipment.png

# Resource files
RESOURCES += images.qrc

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
