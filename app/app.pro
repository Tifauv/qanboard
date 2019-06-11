TEMPLATE = app
TARGET = qanboard
CONFIG += c++11
QT += qml quick

LIBS          += ../core/libqanboardcore.a
PRE_TARGETDEPS = ../core/libqanboardcore.a

INCLUDEPATH += ../core

SOURCES += main.cpp

RESOURCES += ui.qrc

OTHER_FILES += eu.catwitch.qanboard.desktop

include(fontawesome.pri/fontawesome.pri)

isEmpty(target.path) {
    target.path = /usr/local/bin/
    export(target.path)
}
INSTALLS += target

DESKTOP_FILES = *.desktop
desktop.files = $$DESKTOP_FILES
desktop.path = /usr/local/share/applications
INSTALLS += desktop

export(INSTALLS)
