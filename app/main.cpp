#include <QCoreApplication>
#include <QApplication>
#include <QtDeclarative>
#include <QtDebug>
#include "qmlapplicationviewer.h"
#include "Task.h"
#include "TaskQueue.h"
#include "Workflow.h"
#include "MemoryStorage.h"


/**
 * @brief Registers C++ objects with QML or QMetaObject.
 */
void registerTypes() {
	qmlRegisterType<Task>("qanboard.app", 1, 0, "Task");
	qmlRegisterType<TaskQueue>("qanboard.app", 1, 0, "TaskQueue");
	qmlRegisterType<Workflow>("qanboard.app", 1, 0, "Workflow");
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
	QCoreApplication::setApplicationName("Qanboard");
	QCoreApplication::setApplicationVersion("0.3");

	registerTypes();
	Workflow wf;
	MemoryStorage storage;
	storage.load(wf);

    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
	viewer.rootContext()->setContextProperty("workflow", &wf);
	viewer.setMainQmlFile(QLatin1String("qml/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
