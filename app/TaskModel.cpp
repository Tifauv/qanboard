#include "TaskModel.h"


TaskModel::TaskModel(QObject* p_parent) :
	ListItem(p_parent),
	m_task() {
}


TaskModel::TaskModel(const TaskModel& p_model) :
	ListItem(),
	m_task(p_model.model()) {
	m_task.setParent(this);
}

TaskModel::TaskModel(const Task& p_task) :
	ListItem(),
	m_task(p_task) {
	m_task.setParent(this);
}


QHash<int, QByteArray> TaskModel::roleNames() const {
	QHash<int, QByteArray> names;
	names[TaskIdRole] = "taskId";
	names[DescriptionRole] = "description";
	names[CategoryRole] = "category";
	names[AssigneeRole] = "assignee";
	return names;
}


QString TaskModel::id() const {
	return QString(m_task.taskId());
}


QVariant TaskModel::data(int p_role) const {
	switch (p_role) {
	case TaskIdRole:
		return m_task.taskId();
	case DescriptionRole:
		return m_task.description();
	case CategoryRole:
		return m_task.category();
	case AssigneeRole:
		return m_task.assignee();
	default:
		return QVariant();
	}
}


void TaskModel::setData(int p_role, QVariant& p_value) {
	switch (p_role) {
	case TaskIdRole:
		m_task.setTaskId(p_value.toUInt());
	case DescriptionRole:
		m_task.setDescription(p_value.toString());
	case CategoryRole:
		m_task.setCategory(p_value.toString());
	case AssigneeRole:
		m_task.setAssignee(p_value.toString());
	}
}


const Task& TaskModel::model() const {
	return m_task;
}
