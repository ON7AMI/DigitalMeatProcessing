#-------------------------------------------------
#
# Project created by QtCreator 2015-07-27T21:11:33
#
#-------------------------------------------------

QT       += qml network sql xml
QT       += widgets

QT       -= gui

TARGET = CommonObjects
TEMPLATE = lib

DEFINES += COMMONOBJECTS_LIBRARY

SOURCES += commonobjects.cpp \
    postcodes.cpp \
    talen.cpp \
    landen.cpp \
    geslachten.cpp \
    aansprekingen.cpp \
    firma.cpp \
    sites.cpp \
    afdelingen.cpp \
    gebruikers.cpp \
    btwregimes.cpp \
    bkhcategorie.cpp \
    kortingscategorie.cpp \
    betalingstermijn.cpp

HEADERS += commonobjects.h\
        commonobjects_global.h \
    postcodes.h \
    talen.h \
    landen.h \
    geslachten.h \
    aansprekingen.h \
    firma.h \
    sites.h \
    afdelingen.h \
    gebruikers.h \
    btwregimes.h \
    bkhcategorie.h \
    kortingscategorie.h \
    betalingstermijn.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
