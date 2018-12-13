#-------------------------------------------------
#
# Project created by QtCreator 2015-07-26T19:45:01
#
#-------------------------------------------------

QT       += widgets network sql xml

TARGET = Relaties
TEMPLATE = lib
CONFIG += staticlib

SOURCES += relaties.cpp \
    relatiefiche.cpp \
    relatiesettings.cpp \
    findrelaties.cpp

HEADERS += relaties.h \
    relatiefiche.h \
    relatiesettings.h \
    findrelaties.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    relatiefiche.ui \
    relatiesettings.ui \
    findrelaties.ui
