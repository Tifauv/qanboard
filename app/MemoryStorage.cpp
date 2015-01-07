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
	qDebug() << "(i) [MemoryStorage] Structure initialized...";

	qDebug() << "(i) [MemoryStorage] Loading tasks...";
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
	qDebug() << "(i) [MemoryStorage] Workflow is ready.";
}


void MemoryStorage::store(Workflow &) const {
	qDebug() << "(i) [MemoryStorage] Storing is not supported.";
}
