# Project configuration for WStreamLab application

# Major.Minor.Build.Revision
VERSION = 1.4.0.1

# Include necessary Qt modules
QT += core gui printsupport widgets serialbus

# Conditionally include widgets module for Qt versions greater than 4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Set C++ standard to C++17
CONFIG += c++17

# Enable all warnings and treat them as errors
# QMAKE_CXXFLAGS += -Wall -Wextra
# QMAKE_CXXFLAGS += -Werror

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    helpabout.cpp \
    license.cpp \
    md5.cpp \
    report.cpp \
    tableBoard.cpp \
    waterdensity.cpp

# Header files
HEADERS += \
    mainwindow.h \
    definitions.h \
    flow-meter-type.h \
    helpabout.h \
    license.h \
    md5.h \
    report.h \
    tableBoard.h \
    waterdensity.h

# UI form files
FORMS += \
    mainwindow.ui \
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
DISTFILES +=

# Resource files
RESOURCES += images.qrc

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
