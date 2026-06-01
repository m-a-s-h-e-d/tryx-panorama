QT += core gui widgets multimedia network

CONFIG += c++17
TARGET = tryx-panorama-manager
TEMPLATE = app

INCLUDEPATH += $$PWD/include

# Build output
DESTDIR = $$PWD/build
OBJECTS_DIR = $$PWD/build/obj
MOC_DIR = $$PWD/build/moc
RCC_DIR = $$PWD/build/rcc

# Core library
SOURCES += \
    src/core/protocol.cpp \
    src/core/device.cpp \
    src/core/adb.cpp \
    src/core/media.cpp \
    src/core/config.cpp

# GUI
HEADERS += \
    src/devicemanager.h \
    src/systemmonitor.h \
    src/homepage.h \
    src/panoramapage.h \
    src/displaypage.h \
    src/settingspage.h \
    src/traymanager.h \
    src/mainwindow.h \
    src/splitconfig.h

SOURCES += \
    src/main.cpp \
    src/devicemanager.cpp \
    src/systemmonitor.cpp \
    src/homepage.cpp \
    src/panoramapage.cpp \
    src/displaypage.cpp \
    src/settingspage.cpp \
    src/traymanager.cpp \
    src/mainwindow.cpp \
    src/splitconfig.cpp

RESOURCES += resources/resources.qrc
