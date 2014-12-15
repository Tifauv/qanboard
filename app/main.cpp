#include <QCoreApplication>
#include <QApplication>
#include <QtDeclarative>
#include <QtDebug>
#include "qmlapplicationviewer.h"
#include "ListModel.h"
#include "Task.h"
#include "TaskModel.h"
#include "TaskQueue.h"
#include "TaskQueueModel.h"
#include "Workflow.h"


/**
 * @brief Registers C++ objects with QML or QMetaObject.
 */
void registerTypes() {
	qmlRegisterType<Task>("Task", 1, 0, "Task");
	qmlRegisterType<TaskModel>("TaskModel", 1, 0, "TaskModel");
	qmlRegisterType<ListModel>("ListModel", 1, 0, "ListModel");
	qmlRegisterType<TaskQueue>("TaskQueue", 1, 0, "TaskQueue");
	qmlRegisterType<TaskQueueModel>("TaskQueueModel", 1, 0, "TaskQueueModel");
	qmlRegisterType<Workflow>("Workflow", 1, 0, "Workflow");
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
	Task task1("Add this awesome feature", "Feature request", "demo1");
	p_workflow.addTaskToQueue(task1, "Work in progress");

	Task task2("Fix that bug [TB: 4h]", "Bug", "demo");
	p_workflow.addTaskToQueue(task2, "Ready");

	Task task3("Write documentation for the new API", "Documentation", QString::null);
	p_workflow.addTaskToQueue(task3, "Backlog");

	Task task4("Install Redis on the server", "Sysadmins", QString::null);
	p_workflow.addTaskToQueue(task4, "Backlog");

	Task task22("Fix that bug in prod", "Bug", "demo2");
	p_workflow.addTaskToQueue(task22, "Work in progress");

	Task task23("Code refactoring", "Improvement", QString::null);
	p_workflow.addTaskToQueue(task23, "Done");

	Task task24("Write documentation about this new feature", "Documentation", QString::null);
	p_workflow.addTaskToQueue(task24, "Backlog");

	Task task25("Implement a new algorithm", "Improvement", QString::null);
	p_workflow.addTaskToQueue(task25, "Backlog");
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
    viewer.setMainQmlFile(QLatin1String("qml/qanboard/main.qml"));
	viewer.rootContext()->setContextProperty("workflow", &wf);
    viewer.showExpanded();

    return app->exec();
}
