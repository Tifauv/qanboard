#include "TaskQueue.h"
#include <QtDebug>

TaskQueue::TaskQueue(QObject* p_parent) :
	QObject(p_parent),
	m_name(""),
	m_tasks() {
	qDebug() << "(i) [TaskQueue] Created";
}


TaskQueue::TaskQueue(const TaskQueue& p_tasks) :
	QObject(),
	m_name(p_tasks.name()),
	m_tasks(p_tasks.m_tasks) {
	qDebug() << "(i) [TaskQueue] Queue " << name() << " copied with " << m_tasks.count() << " elements.";
}


// GETTERS
const QString& TaskQueue::name() const {
	return m_name;
}


// SETTERS
void TaskQueue::setName(const QString &p_name) {
	m_name = p_name;
	qDebug() << "(i) [TaskQueue] Changed name to " << p_name;
	emit nameChanged(p_name);
}


// METHODS
int TaskQueue::count() const {
	return m_tasks.size();
}


Task* TaskQueue::at(int p_index) const {
	if (p_index < 0 || p_index >= m_tasks.size())
		return NULL;
	return m_tasks.at(p_index);
}

Task* TaskQueue::find(uint p_taskId) const {
	foreach(Task* task, m_tasks) {
		if (task->taskId() == p_taskId)
			return task;
	}
	return NULL;
}


void TaskQueue::add(Task* p_task) {
	Q_ASSERT(p_task);
	insert(m_tasks.size(), p_task);
}


void TaskQueue::insert(int p_index, Task* p_task) {
	Q_ASSERT(p_task);
	m_tasks.insert(p_index, p_task);
	qDebug() << "(i) [TaskQueue] Task " << p_task->taskId() << " added to queue " << name();
	emit taskAdded(p_index, p_task);
}


Task* TaskQueue::remove(int p_index) {
	if (p_index < 0 || p_index >= m_tasks.size())
		return NULL;

	Task* task = m_tasks.takeAt(p_index);
	emit taskRemoved(p_index, task);
	return task;
}
