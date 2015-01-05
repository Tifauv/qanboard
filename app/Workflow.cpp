#include "Workflow.h"
#include "TaskListModel.h"
#include <QtDebug>


Workflow::Workflow(QObject* p_parent) :
	QAbstractListModel(p_parent),
	m_taskId(0),
	m_queues() {
	QHash<int, QByteArray> names;
	names[QueueNameRole] = "name";
	names[TaskListRole] = "tasks";
	setRoleNames(names);
	qDebug() << "(i) [Workflow] Created";
}


uint Workflow::taskId() const {
	return m_taskId;
}


uint Workflow::nextTaskId() {
	qDebug() << "(i) [Workflow] Current taskId is " << m_taskId+1 ;
	return ++m_taskId;
}


int Workflow::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	qDebug() << "(i) [Workflow] Has " << m_queues.size() << " queues";
	return m_queues.size();
}


QVariant Workflow::data(const QModelIndex& p_index, int p_role) const {
	if (p_index.row() < 0 || p_index.row() >= m_queues.size())
		return QVariant();

	TaskQueue* queue = m_queues.at(p_index.row());
	switch (p_role) {
	case QueueNameRole:
		return queue->name();
	case TaskListRole:
		return qVariantFromValue(new TaskListModel(*queue));
	default:
		return QVariant();
	}
}


TaskQueue* Workflow::find(const QString& p_name) const {
	qDebug() << "(i) [Workflow] Searching queue " << p_name;
	foreach (TaskQueue* queue, m_queues) {
		if (queue->name() == p_name)
			return queue;
	}

	return NULL;
}


void Workflow::insertRow(int p_row, TaskQueue* p_queue) {
	beginInsertRows(QModelIndex(), p_row, p_row);
	m_queues.insert(p_row, p_queue);
	endInsertRows();
	qDebug() << "(i) [Workflow] Queue " << p_queue->name() << " added";
}


void Workflow::createQueue(const QString& p_name) {
	TaskQueue* queue = new TaskQueue(this);
	queue->setName(p_name);
	insertRow(m_queues.size(), queue);
}


uint Workflow::addTaskToQueue(Task* p_task, const QString& p_queue) {
	TaskQueue* queue = find(p_queue);
	if (queue) {
		qDebug() << "(i) [Workflow] Queue " << p_queue << " found";
		p_task->setTaskId(nextTaskId());
		queue->add(p_task);
	}
	else {
		qDebug() << "/!\\ [Workflow] Queue " << p_queue << " does not exist";
	}
	return p_task->taskId();
}


uint Workflow::createTaskInQueue(const QString& p_description, const QString& p_queue) {
	qDebug() << "(i) Creating new task" << p_queue << "...";
	Task* task = new Task(p_description);
	return addTaskToQueue(task, p_queue);
}
