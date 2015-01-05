#include <QCoreApplication>
#include <QApplication>
#include <QtDeclarative>
#include <QtDebug>
#include "qmlapplicationviewer.h"
#include "Task.h"
#include "TaskQueue.h"
#include "Workflow.h"


/**
 * @brief Registers C++ objects with QML or QMetaObject.
 */
void registerTypes() {
	qmlRegisterType<Task>("qanboard.app", 1, 0, "Task");
	qmlRegisterType<TaskQueue>("qanboard.app", 1, 0, "TaskQueue");
	qmlRegisterType<Workflow>("qanboard.app", 1, 0, "Workflow");
}


void loadModel(Workflow& p_workflow) {
	qDebug() << "(i) Loading model...";
	qDebug() << "(i) Initializing structure...";
	p_workflow.createQueue("Backlog");
	p_workflow.createQueue("Ready");
	p_workflow.createQueue("Work in progress");
	p_workflow.createQueue("Done");
	qDebug() << "(i) Structure initialized...";

	qDebug() << "(i) Loading tasks...";

	p_workflow.addTaskToQueue(
				new Task("Add this awesome feature", "Feature request", "demo1"),
				"Work in progress");
	p_workflow.addTaskToQueue(
				new Task("Fix that bug [TB: 4h]", "Bug", "demo"),
				"Ready");
	p_workflow.addTaskToQueue(
				new Task("Write documentation for the new API", "Documentation", QString::null),
				"Backlog");
	p_workflow.addTaskToQueue(
				new Task("Install Redis on the server", "Sysadmins", QString::null),
				"Backlog");
	p_workflow.addTaskToQueue(
				new Task("Fix that bug in prod", "Bug", "demo2"),
				"Work in progress");
	p_workflow.addTaskToQueue(
				new Task("Code refactoring", "Improvement", QString::null),
				"Done");
	p_workflow.addTaskToQueue(
				new Task("Write documentation about this new feature", "Documentation", QString::null),
				"Backlog");
	p_workflow.addTaskToQueue(
				new Task("Implement a new algorithm", "Improvement", QString::null),
				"Backlog");
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

	registerTypes();
	Workflow wf;
	loadModel(wf);

    QmlApplicationViewer viewer;
    viewer.addImportPath(QLatin1String("modules"));
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
	viewer.rootContext()->setContextProperty("workflow", &wf);
	viewer.setMainQmlFile(QLatin1String("qml/qanboard/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
