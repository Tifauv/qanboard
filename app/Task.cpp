#include "Task.h"


Task::Task(QObject* p_parent) :
	QObject(p_parent) {
}


Task::Task(const Task& p_task) :
	QObject(),
	m_taskId(p_task.taskId()),
	m_description(p_task.description()),
	m_assignee(p_task.assignee()),
	m_category(p_task.category()) {
}


uint Task::taskId() const {
	return m_taskId;
}


const QString& Task::description() const {
	return m_description;
}


const QString& Task::assignee() const {
	return m_assignee;
}


const QString& Task::category() const {
	return m_category;
}


void Task::setTaskId(uint p_taskId) {
	m_taskId = p_taskId;
	emit taskIdChanged(m_taskId);
}

void Task::setDescription(const QString& p_description) {
	m_description = p_description;
	emit descriptionChanged(m_description);
}


void Task::setAssignee(const QString& p_assignee) {
	m_assignee = p_assignee;
	emit assigneeChanged(m_assignee);
}


void Task::setCategory(const QString& p_category) {
	m_category = p_category;
	emit categoryChanged(m_category);
}
