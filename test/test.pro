TEMPLATE = app
TARGET = ../qanboard-tests
CONFIG += c++11 testcase
QT += testlib

LIBS          += ../core/libqanboardcore.a
PRE_TARGETDEPS = ../core/libqanboardcore.a

INCLUDEPATH += ../core

SOURCES += TestTaskQueue.cpp
HEADERS += TestTaskQueue.h

