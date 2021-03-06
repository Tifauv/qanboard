#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QIcon>

#include "Task.h"
#include "TaskQueue.h"
#include "Workflow.h"
#include "ConvertingSerializer.h"
#include "XmlSerializer10.h"
#include "XmlSerializer20.h"
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
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(p_argc, p_argv);
	app.setOrganizationName("Catwitch");
	app.setOrganizationDomain("catwitch.eu");
	app.setApplicationName("qanboard");
	app.setApplicationDisplayName("Qanboard");
	app.setApplicationVersion("0.5");

	// Register model types with the QML engine
	qmlRegisterType<Task>(       "Qanboard", 1, 0, "Task"     );
	qmlRegisterType<TaskQueue>(  "Qanboard", 1, 0, "TaskQueue");
	//qmlRegisterType<TaskMove>(   "Qanboard", 1, 0, "TaskMove" );
	qmlRegisterType<History>(    "Qanboard", 1, 0, "History"  );
	qmlRegisterType<Workflow>(   "Qanboard", 1, 0, "Workflow" );
	qmlRegisterType<FileStorage>("Qanboard", 1, 0, "FileStorage");

	// Create the workflow and initialize the storage layer
	Workflow wf;
	ConvertingSerializer serializer;
	serializer.setCurrentSerializer(new XmlSerializer20());
	serializer.setLegacySerializer(new XmlSerializer10());
	FileStorage storage;
	storage.setup(&serializer);

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
	
	// Set the default icon theme name
	if (QIcon::themeName().isEmpty()) {
		QIcon::setThemeName("breeze");
	}
	
	// Create the QML view & show it !
	QQmlApplicationEngine engine;
	engine.addImportPath("qrc:///");
	engine.rootContext()->setContextProperty("workflow", &wf);
	engine.rootContext()->setContextProperty("storage", &storage);
	engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;
	
	// Save the current workflow before leaving
	QObject::connect(&app, &QCoreApplication::aboutToQuit,
			[&storage,&wf]() { storage.store(wf); });

	return app.exec();
}
