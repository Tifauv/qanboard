TARGET = qanboard
TEMPLATE = app
QT += qml quick
CONFIG += c++11

# Import the C++ code
include(app/app.pri)

RESOURCES += qml.qrc

OTHER_FILES += sample.xml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment
include(deployment.pri)
