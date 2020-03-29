include(../../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

LIBS += -L../../../libKitsunemimiCommon/src -lKitsunemimiCommon
LIBS += -L../../../libKitsunemimiCommon/src/debug -lKitsunemimiCommon
LIBS += -L../../../libKitsunemimiCommon/src/release -lKitsunemimiCommon
INCLUDEPATH += ../../../libKitsunemimiCommon/include

INCLUDEPATH += $$PWD

LIBS += -L../../src -lKitsunemimiIni

SOURCES += \
        main.cpp \
    libKitsunemimiIni/ini_item_test.cpp

HEADERS += \
    libKitsunemimiIni/ini_item_test.h

