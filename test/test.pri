TARGET = qanboard-tests
TEMPLATE = app

QT += testlib

SOURCES += $$PWD/TestTaskQueue.cpp
HEADERS += $$PWD/TestTaskQueue.h

INCLUDEPATH += $$PWD/../app
