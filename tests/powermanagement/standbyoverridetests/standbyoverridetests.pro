QT += testlib \
      dbus \
      network
QT -= gui

include(../../common-install.pri)

CONFIG += debug
TEMPLATE = app
TARGET = sensorstandbyoverride-test
HEADERS += standbyoverridetests.h helpslot.h
SOURCES += standbyoverridetests.cpp

SENSORFW_INCLUDEPATHS = ../../../qt-api \
                        ../../../include \
                        ../../../filters \
                        ../../../datatypes \
                        ../../../core \
                        ../../..

DEPENDPATH += $$SENSORFW_INCLUDEPATHS
INCLUDEPATH += $$SENSORFW_INCLUDEPATHS

QMAKE_LIBDIR_FLAGS += -L../../../qt-api  \
                      -L../../../datatypes\
                      -L../../../core

QMAKE_LIBDIR_FLAGS += -lsensordatatypes-qt$${QT_MAJOR_VERSION} -lsensorclient-qt$${QT_MAJOR_VERSION}

#CONFIG += link_pkgconfig
#PKGCONFIG += mlite5
