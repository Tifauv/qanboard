#include <QtDebug>
#include <QGuiApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
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
int main(int p_argc, char *p_argv[]) {
	QGuiApplication app(p_argc, p_argv);
	app.setApplicationDisplayName("Qanboard");
	app.setApplicationName("Qanboard");
	app.setApplicationVersion("0.5");
	app.setOrganizationName("catwitch.eu");

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
		wf.setDefaultQueue("Backlog");
	}

	// Create the QML view & show it !
	QQmlApplicationEngine engine;
	engine.addImportPath(QStringLiteral("modules"));
	//engine.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
	engine.rootContext()->setContextProperty("workflow", &wf);

	engine.addImportPath("qrc:///");
	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

	int rc = app.exec();
	// Save the current workflow before leaving
	storage.store(wf);
	return rc;
}
