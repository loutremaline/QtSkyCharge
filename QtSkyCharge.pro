QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chargerDevice.cpp \
    chargeslot.cpp \
    main.cpp \
    mainwindow.cpp \
    systemsettings.cpp

HEADERS += \
    chargeAction.h \
    chargeInfo.h \
    chargerDevice.h \
    chargerInfo.h \
    chargeslot.h \
    const.h \
    enum.h \
    hidexception.h \
    mainwindow.h \
    systemInfo.h \
    systemsettings.h

FORMS += \
    chargeslot.ui \
    mainwindow.ui \
    systemsettings.ui

TRANSLATIONS += \
    QtSkyCharge_fr.ts

LIBS += -lhidapi-libusb

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
