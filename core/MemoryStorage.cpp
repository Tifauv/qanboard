#include "MemoryStorage.h"
#include <QtDebug>

MemoryStorage::MemoryStorage(QObject* p_parent) :
	WorkflowStorage(p_parent) {
	qDebug() << "(i) [MemoryStorage] Created.";
}


void MemoryStorage::load(Workflow& p_workflow) const {
	qDebug() << "(i) [MemoryStorage] Initializing workflow...";
	p_workflow.setName("Sample");

	qDebug() << "(i) [MemoryStorage] Initializing tasks...";
	p_workflow.registerTask(
	            new Task(1, "Client", "Development", "Add this awesome feature", "15/02/2015", "demo1"));
	p_workflow.registerTask(
	            new Task(2, "Client", "Development", "Fix that bug [TB: 4h]", "15/02/2015", "demo1"));
	p_workflow.registerTask(
	            new Task(3, "Client", "Documentation", "Write documentation for the new API", "15/02/2015"));
	p_workflow.registerTask(
	            new Task(4, "Client", "SysOps", "Install Redis on the server", "15/02/2015", "demosrv"));
	p_workflow.registerTask(
	            new Task(22, "Client", "Run", "Fix that bug in prod", "15/02/2015", "demo2"));
	p_workflow.registerTask(
	            new Task(23, "Client", "Development", "Code refactoring", "15/02/2015"));
	p_workflow.registerTask(
	            new Task(24, "Client", "Documentation", "Write documentation about this new feature", "15/02/2015"));
	p_workflow.registerTask(
	            new Task(25, "Client", "Development", "Implement a new algorithm", "15/02/2015"));

	qDebug() << "(i) [MemoryStorage] Initializing queues...";
	p_workflow.createQueue("Backlog",     "#4d4d4d");
	p_workflow.createQueue("Selected",    "#1d99f3");
	p_workflow.createQueue("In progress", "#da4453");
	p_workflow.createQueue("Done",        "#2ecc71");
	p_workflow.selectDefaultQueue("Backlog");

	qDebug() << "(i) [MemoryStorage] Loading tasks...";
	p_workflow.appendTaskToQueue( 1, "Work in progress");
	p_workflow.appendTaskToQueue( 2, "Ready");
	p_workflow.appendTaskToQueue( 3, "Backlog");
	p_workflow.appendTaskToQueue( 4, "Backlog");
	p_workflow.appendTaskToQueue(22, "Work in progress");
	p_workflow.appendTaskToQueue(23, "Done");
	p_workflow.appendTaskToQueue(24, "Backlog");
	p_workflow.appendTaskToQueue(25, "Backlog");
	p_workflow.setTaskId(26);

	qDebug() << "(i) [MemoryStorage] Workflow is ready...";
}


void MemoryStorage::store(Workflow&) const {
	qDebug() << "(i) [MemoryStorage] Storing is not supported.";
}
