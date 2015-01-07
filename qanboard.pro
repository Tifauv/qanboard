TARGET = qanboard
TEMPLATE = app

# Add more folders to ship with the application, here
qml.source = qml
qml.target = /
DEPLOYMENTFOLDERS = qml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# Import the C++ code
include(app/app.pri)

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()


# Installation
target.path = /usr/local/bin
desktop.path = /usr/share/applications
desktop.file = qanboard.desktop

INSTALLS = target desktop

OTHER_FILES += \
    sample.xml
