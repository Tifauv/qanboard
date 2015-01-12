#include <QCoreApplication>
#include <QApplication>
#include <QtDeclarative>
#include <QtDebug>
#include "qmlapplicationviewer.h"
#include "Task.h"
#include "TaskQueue.h"
#include "Workflow.h"
#include "XmlSerializer.h"
#include "FileStorage.h"


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
	QCoreApplication::setApplicationVersion("0.4");
	QCoreApplication::setOrganizationName("catwitch.eu");

	registerTypes();

	// Create the workflow and initialize the storage layer
	Workflow wf;
	XmlSerializer serializer;
	FileStorage storage(serializer);

	// Load the workflow
	storage.load(wf);
	// If no workflow was loaded, create an empty structure
	if (wf.count() == 0) {
		wf.createQueue("Backlog");
		wf.createQueue("Ready");
		wf.createQueue("Work in progress");
		wf.createQueue("Done");
	}

	// Create the QML view & show it !
    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
	viewer.rootContext()->setContextProperty("workflow", &wf);
	viewer.setMainQmlFile(QLatin1String("qml/main.qml"));
    viewer.showExpanded();

	int rc = app->exec();
	// Save the current workflow before leaving
	storage.store(wf);
	return rc;
}
