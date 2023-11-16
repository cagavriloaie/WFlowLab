QT += core gui
QT += printsupport
QT += widgets
QT += serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    air-density.cpp \
    helpabout.cpp \
    interface.cpp \
    ledindicator.cpp \
    license.cpp \
    main.cpp \
    mainwindow.cpp \
    md5.cpp \
    tableBoard.cpp

HEADERS += \
    air-density.h \
    flow-meter-type.h \
    helpabout.h \
    interface.h \
    ledindicator.h \
    license.h \
    mainwindow.h \
    md5.h \
    tableBoard.h

FORMS += \
    helpabout.ui \
    interface.ui \
    tableBoard.ui \
    license.ui \
    mainwindow.ui

CONFIG += lrelease
lrelease.input = TRANSLATIONS
lrelease.output = ${QMAKE_FILE_BASE}.qm
lrelease.commands = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_BASE}.qm

CONFIG += embed_translations
TRANSLATIONS +=  translations/meter_ro_RO.ts translations/meter_en_EN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


TARGET = WStreamLab
