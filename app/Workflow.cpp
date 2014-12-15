#include "Workflow.h"
#include "TaskModel.h"
#include "TaskQueueModel.h"
#include <QtDebug>


Workflow::Workflow(QObject* p_parent) :
	ListModel(new TaskQueueModel(), p_parent),
	m_taskId(0) {
}


uint Workflow::taskId() const {
	return m_taskId;
}


uint Workflow::nextTaskId() {
	return ++m_taskId;
}


void Workflow::createQueue(const QString& p_name) {
	qDebug() << "(i) Adding new queue " << p_name << " to the workflow.";
	TaskQueue queue;
	queue.setName(p_name);
	qDebug() << "(i)   - Queue " << queue.name() << " created.";
	appendRow(new TaskQueueModel(queue));
	qDebug() << "(i)   - Queue " << queue.name() << " added to the workflow.";
}


uint Workflow::addTaskToQueue(Task& p_task, const QString& p_queue) {
	qDebug() << "(i) Adding new task to queue " << p_queue << "...";
	ListItem* queue = find(p_queue);
	if (queue) {
		qDebug() << "(i)   - queue " << p_queue << " found.";
		p_task.setTaskId(nextTaskId());
		qDebug() << "(i)   - task has id " << p_task.taskId() << ".";
		static_cast<TaskQueueModel*>(queue)->model().tasks()->appendRow(new TaskModel(p_task));
		qDebug() << "(i)   - task " << p_task.taskId() << " added to queue " << p_queue << ".";
	}
	else {
		qDebug() << "/!\\   - queue " << p_queue << " does not exist.";
	}
	return p_task.taskId();
}


uint Workflow::createTaskInQueue(const QString& p_description, const QString& p_queue) {
	qDebug() << "(i) Creating new task" << p_queue << "...";
	Task task(p_description);
	return addTaskToQueue(task, p_queue);
}
