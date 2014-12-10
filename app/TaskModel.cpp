#include "TaskModel.h"


TaskModel::TaskModel(QObject* p_parent) :
	ListItem(p_parent),
	m_task() {
}


TaskModel::TaskModel(const TaskModel& p_taskModel) :
	ListItem(),
	m_task(p_taskModel.model()) {
}


QHash<int, QByteArray> TaskModel::roleNames() const {
	QHash<int, QByteArray> names;
	names[TaskIdRole] = "taskId";
	names[DescriptionRole] = "description";
	names[AssigneeRole] = "assignee";
	names[CategoryRole] = "category";
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
	case AssigneeRole:
		return m_task.assignee();
	case CategoryRole:
		return m_task.category();
	default:
		return QVariant();
	}
}


void TaskModel::setData(int p_role, QVariant& p_value) {
	switch (p_role) {
	case TaskIdRole:
		return m_task.setTaskId(p_value.toUInt());
	case DescriptionRole:
		return m_task.setDescription(p_value.toString());
	case AssigneeRole:
		return m_task.setAssignee(p_value.toString());
	case CategoryRole:
		return m_task.setCategory(p_value.toString());
	}
}


const Task& TaskModel::model() const {
	return Task(m_task);
}
