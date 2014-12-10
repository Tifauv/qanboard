#include <QCoreApplication>
#include <QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "ListModel.h"
#include "Task.h"
#include "TaskModel.h"


/**
 * @brief Registers C++ objects with QML or QMetaObject.
 */
void registerTypes() {
	qmlRegisterType<Task>("Task", 1, 0, "Task");
	qmlRegisterType<TaskModel>("TaskModel", 1, 0, "TaskModel");
	qmlRegisterType<ListModel>("ListModel", 1, 0, "ListModel");
}


/**
 * @brief Launcher function.
 *
 * @param p_argc
 *            number of parameters
 * @param p_argv
 *            array of parameters
 */
Q_DECL_EXPORT int main(int argc, char *argv[]) {
    QScopedPointer<QApplication> app(createApplication(argc, argv));

	// Globally set app name
	QCoreApplication::setApplicationName("Qanboard");

	registerTypes();

    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/qanboard/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
