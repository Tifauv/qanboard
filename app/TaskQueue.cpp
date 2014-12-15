#include "TaskQueue.h"
#include "TaskModel.h"

TaskQueue::TaskQueue(QObject* p_parent) :
	QObject(p_parent),
	m_name(""),
	m_tasks(NULL) {
	m_tasks = new ListModel(new TaskModel());
}


TaskQueue::TaskQueue(const TaskQueue& p_tasks) :
	QObject(),
	m_name(p_tasks.name()),
	m_tasks(p_tasks.tasks()) {
}

const QString& TaskQueue::name() const {
	return m_name;
}


ListModel* TaskQueue::tasks() const {
	return m_tasks;
}


void TaskQueue::setName(const QString &p_name) {
	m_name = p_name;
	emit nameChanged(p_name);
}
