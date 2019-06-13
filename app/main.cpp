#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "Task.h"
#include "TaskQueue.h"
#include "Workflow.h"
#include "XmlSerializer.h"
#include "FileStorage.h"


/**
 * @brief Launcher function.
 *
 * @param p_argc
 *            number of parameters
 * @param p_argv
 *            array of parameters
 */
int main(int p_argc, char *p_argv[]) {
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(p_argc, p_argv);
	app.setOrganizationName("Catwitch");
	app.setOrganizationDomain("catwitch.eu");
	app.setApplicationName("qanboard");
	app.setApplicationDisplayName("Qanboard");
	app.setApplicationVersion("0.5");

	// Register model types with the QML engine
	qmlRegisterType<Task>(     "Qanboard", 1, 0, "Task"     );
	qmlRegisterType<TaskQueue>("Qanboard", 1, 0, "TaskQueue");
	qmlRegisterType<Workflow>( "Qanboard", 1, 0, "Workflow" );

	// Create the workflow and initialize the storage layer
	Workflow wf;
	XmlSerializer serializer;
	FileStorage storage(serializer);

	// Load the workflow
	storage.load(wf);
	// If no workflow was loaded, create an empty structure
	if (wf.count() == 0) {
		wf.createQueue("Backlog");
		wf.createQueue("Selected");
		wf.createQueue("In progress");
		wf.createQueue("Done");
		wf.selectDefaultQueue("Backlog");
	}

	// Create the QML view & show it !
	QQmlApplicationEngine engine;
	//engine.addImportPath(QStringLiteral("modules"));
	engine.addImportPath("qrc:///");
	engine.rootContext()->setContextProperty("workflow", &wf);
	engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	int rc = app.exec();
	// Save the current workflow before leaving
	storage.store(wf);
	return rc;
}
