#
# Project onyx-flashlight
#

TARGET = onyx-flashlight

CONFIG += sailfishapp
QT += dbus

DEFINES += "APPVERSION=\\\"$${SPECVERSION}\\\""

message($${DEFINES})

SOURCES += src/main.cpp \
    src/torch.cpp
	
OTHER_FILES += qml/flashlight.qml \
    qml/pages/Flashlight.qml \
    qml/pages/AboutPage.qml \
    rpm/onyx-flashlight.spec \
    onyx-flashlight.png \
    onyx-flashlight.desktop

HEADERS += \
    src/torch.h

