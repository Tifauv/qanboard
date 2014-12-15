#include "TaskQueueModel.h"

TaskQueueModel::TaskQueueModel(QObject* p_parent) :
	ListItem(p_parent),
	m_list() {
}


TaskQueueModel::TaskQueueModel(const TaskQueueModel& p_model) :
	ListItem(),
	m_list(p_model.constModel()) {
	m_list.setParent(this);
}


TaskQueueModel::TaskQueueModel(const TaskQueue& p_TaskQueue) :
	ListItem(),
	m_list(p_TaskQueue) {
	m_list.setParent(this);
}


QHash<int, QByteArray> TaskQueueModel::roleNames() const {
	QHash<int, QByteArray> names;
	names[NameRole] = "name";
	return names;
}


QString TaskQueueModel::id() const {
	return m_list.name();
}


QVariant TaskQueueModel::data(int p_role) const {
	switch (p_role) {
	case NameRole:
		return m_list.name();
	default:
		return QVariant();
	}
}


void TaskQueueModel::setData(int p_role, QVariant& p_value) {
	switch (p_role) {
	case NameRole:
		return m_list.setName(p_value.toString());
	}
}


TaskQueue& TaskQueueModel::model() const {
	return const_cast<TaskQueue&>(m_list);
}


const TaskQueue& TaskQueueModel::constModel() const {
	return m_list;
}

