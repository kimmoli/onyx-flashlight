#
# Project onyx-flashlight
#

TARGET = onyx-flashlight

CONFIG += sailfishapp

DEFINES += "APPVERSION=\\\"$${SPECVERSION}\\\""

udevrule.path = /etc/udev/rules.d/
udevrule.files = config/70-onyx-flashlight.rules

INSTALLS += udevrule

message($${DEFINES})

SOURCES += src/main.cpp \
    src/torch.cpp
	
OTHER_FILES += qml/flashlight.qml \
    qml/cover/CoverPage.qml \
    qml/pages/Flashlight.qml \
    qml/pages/AboutPage.qml \
    rpm/onyx-flashlight.spec \
    onyx-flashlight.png \
    onyx-flashlight.desktop \
    config/70-onyx-flashlight.rules

HEADERS += \
    src/torch.h

