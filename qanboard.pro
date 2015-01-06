# Add more folders to ship with the application, here
qml.source = qml/qanboard
qml.target = qml
DEPLOYMENTFOLDERS = qml

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# Import the C++ code
include(app/app.pri)

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/qanboard/tools/Label.qml
