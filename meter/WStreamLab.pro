# Project configuration for WStreamLab application

# Major.Minor.Build.Revision
VERSION = 1.5.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Include necessary Qt modules
QT += core gui printsupport widgets serialbus

# Set C++ standard to C++17
CONFIG += c++17

# Enable all warnings and treat them as errors (uncomment for development)
QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CXXFLAGS += -Werror

# Source and header files
SOURCES += $$files($$PWD/*.cpp)
HEADERS += $$files($$PWD/*.h)

# Include the icon for Windows
RC_ICONS = ..\build\WStreamLab.ico

# UI form files
FORMS += \
    mainwindow.ui \
    helpabout.ui \
    license.ui \
    report.ui \
    tableBoard.ui \
    interface.ui

# Translation configuration
TRANSLATIONS += $$files(translations/*.ts)

# Deployment configuration
TARGET = WStreamLab

# Resource files
RESOURCES += images.qrc

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
