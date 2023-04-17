QT += core gui
QT += printsupport
QT += widgets
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    air-density.cpp \
    dialog.cpp \
    helpabout.cpp \
    interface.cpp \
    ledindicator.cpp \
    licence.cpp \
    main.cpp \
    mainwindow.cpp \
    md5.cpp

HEADERS += \
    air-density.h \
    dialog.h \
    flow-meter-type.h \
    helpabout.h \
    interface.h \
    ledindicator.h \
    licence.h \
    mainwindow.h \
    md5.h

FORMS += \
    dialog.ui \
    helpabout.ui \
    interface.ui \
    licence.ui \
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

DISTFILES += \
    Elegantthemes-Beautiful-Flat-Water.128.png \
    Elegantthemes-Beautiful-Flat-Water.64.png \
    Elegantthemes-Beautiful-Flat-Water.72.png \
    Elegantthemes-Beautiful-Flat-Water.96.png \
    Elegantthemes-Beautiful-Flat-Water.ico

TARGET = WStreamLab
