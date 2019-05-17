QT -= qt core gui

TARGET = KitsuneIni
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14


INCLUDEPATH += $$PWD \
               $$PWD/../include/libKitsuneJson

LIBS +=  -lfl -ly
