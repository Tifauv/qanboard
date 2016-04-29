TARGET = qanboard
TEMPLATE = app
QT += qml quick
CONFIG += c++11

# Import the C++ code
include(app/app.pri)

RESOURCES += qml.qrc

OTHER_FILES += sample.xml

# Default rules for deployment
include(deployment.pri)
