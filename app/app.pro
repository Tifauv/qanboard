TEMPLATE = app
TARGET = ../qanboard
CONFIG += c++11
QT += qml quick

LIBS          += ../core/libqanboardcore.a
PRE_TARGETDEPS = ../core/libqanboardcore.a

INCLUDEPATH += ../core

SOURCES += main.cpp

RESOURCES += ui.qrc

include(fontawesome.pri/fontawesome.pri)

isEmpty(target.path) {
    target.path = /opt/$${TARGET}/bin
    export(target.path)
}
desktop.path = /usr/share/applications
desktop.file = qanboard.desktop
INSTALLS = target desktop

export(INSTALLS)
