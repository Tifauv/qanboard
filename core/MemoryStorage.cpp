#include "MemoryStorage.h"
#include <QtDebug>

MemoryStorage::MemoryStorage(QObject* p_parent) :
	WorkflowStorage(p_parent) {
	qDebug() << "(i) [MemoryStorage] Created.";
}


void MemoryStorage::load(Workflow& p_workflow) const {
	qDebug() << "(i) [MemoryStorage] Loading workflow...";
	qDebug() << "(i) [MemoryStorage] Initializing structure...";
	p_workflow.createQueue("Backlog");
	p_workflow.createQueue("Ready");
	p_workflow.createQueue("Work in progress");
	p_workflow.createQueue("Done");
	p_workflow.setDefaultQueue("Backlog");
	qDebug() << "(i) [MemoryStorage] Structure initialized...";

	qDebug() << "(i) [MemoryStorage] Loading tasks...";
	p_workflow.addTaskToQueue(
				new Task(1, "Add this awesome feature", "Feature request", "demo1"),
				"Work in progress");
	p_workflow.addTaskToQueue(
				new Task(2, "Fix that bug [TB: 4h]", "Bug", "demo"),
				"Ready");
	p_workflow.addTaskToQueue(
				new Task(3, "Write documentation for the new API", "Documentation", QString::null),
				"Backlog");
	p_workflow.addTaskToQueue(
				new Task(4, "Install Redis on the server", "Sysadmins", QString::null),
				"Backlog");
	p_workflow.addTaskToQueue(
				new Task(22, "Fix that bug in prod", "Bug", "demo2"),
				"Work in progress");
	p_workflow.addTaskToQueue(
				new Task(23, "Code refactoring", "Improvement", QString::null),
				"Done");
	p_workflow.addTaskToQueue(
				new Task(24, "Write documentation about this new feature", "Documentation", QString::null),
				"Backlog");
	p_workflow.addTaskToQueue(
				new Task(25, "Implement a new algorithm", "Improvement", QString::null),
				"Backlog");
	p_workflow.setTaskId(26);
	qDebug() << "(i) [MemoryStorage] Workflow is ready.";
}


void MemoryStorage::store(const Workflow&) const {
	qDebug() << "(i) [MemoryStorage] Storing is not supported.";
}
