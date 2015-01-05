#include "TaskListModel.h"
#include <QtDebug>

TaskListModel::TaskListModel(QObject* p_parent) :
	QAbstractListModel(p_parent) {
	QHash<int, QByteArray> names;
	names[TaskIdRole] = "taskId";
	names[DescriptionRole] = "description";
	names[CategoryRole] = "category";
	names[AssigneeRole] = "assignee";
	setRoleNames(names);
	qDebug() << "(i) [TaskListModel] Created for queue " << m_tasks.name() << " with " << rowCount() << " tasks.";
}


TaskListModel::TaskListModel(const TaskQueue& p_tasks, QObject* p_parent) :
	QAbstractListModel(p_parent),
	m_tasks(p_tasks) {
	QHash<int, QByteArray> names;
	names[TaskIdRole] = "taskId";
	names[DescriptionRole] = "description";
	names[CategoryRole] = "category";
	names[AssigneeRole] = "assignee";
	setRoleNames(names);
	qDebug() << "(i) [TaskListModel] Created for queue " << m_tasks.name() << " with " << rowCount() << " tasks.";
}


TaskListModel::TaskListModel(const TaskListModel& p_toCopy) :
	QAbstractListModel() {
	/*foreach (Task* task, p_toCopy.m_tasks.m_tasks) {
		m_tasks.add(task);
	}*/
	qDebug() << "(i) [TaskListModel] Copied.";
}


/**
 * @brief Gives the identifier of an item.
 *
 * @param p_item
 *
 * @return the identifier of the item in the list
 */
QString TaskListModel::itemId(Task* p_item) const {
	qDebug() << "(i) TaskListModel::itemId()";
	return QString(p_item->taskId());
}


/**
 * @brief Retrieves the item's data for a given role.
 *
 * @param p_item
 *            the item from which to extract the data
 * @param p_role
 *            the data role
 *
 * @return the item's data
 */
QVariant TaskListModel::itemData(Task* p_item, int p_role) const {
	qDebug() << "(i) TaskListModel::itemData()";
	switch (p_role) {
	case TaskIdRole:
		return p_item->taskId();
	case DescriptionRole:
		return p_item->description();
	case CategoryRole:
		return p_item->category();
	case AssigneeRole:
		return p_item->assignee();
	default:
		return QVariant();
	}
}


/**
 * @brief TaskListModel::rowCount
 * @param p_parent
 * @return
 */
int TaskListModel::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	//qDebug() << "(i) TaskListModel::rowCount()";
	return m_tasks.count();
}


/**
 * @brief TaskListModel::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant TaskListModel::data(const QModelIndex& p_index, int p_role) const {
	qDebug() << "(i) TaskListModel::data()";
	if (p_index.row() < 0 || p_index.row() >= m_tasks.count())
		return QVariant();
	return itemData(m_tasks.at(p_index.row()), p_role);
}


/**
 * @brief TaskListModel::insertRow
 * @param p_row
 * @param p_item
 */
void TaskListModel::insertRow(int p_row, Task* p_item) {
	beginInsertRows(QModelIndex(), p_row, p_row);
	//connect(p_item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
	m_tasks.insert(p_row, p_item);
	endInsertRows();
}


/**
 * @brief TaskListModel::removeRow
 * @param p_row
 * @param p_parent
 * @return
 */
bool TaskListModel::removeRow(int p_row, const QModelIndex& p_parent) {
	Q_UNUSED(p_parent);
	if (p_row < 0 || p_row >= m_tasks.count())
		return false;
	beginRemoveRows(QModelIndex(), p_row, p_row);
	delete m_tasks.remove(p_row);
	endRemoveRows();
	return true;
}


// SLOTS
int TaskListModel::count() const {
	return m_tasks.count();
}

Task* TaskListModel::at(int p_index) const {
	return m_tasks.at(p_index);
}

Task* TaskListModel::find(uint p_taskId) const {
	return m_tasks.find(p_taskId);
}

void TaskListModel::add(Task* p_task) {
	m_tasks.add(p_task);
}

void TaskListModel::insert(int p_index, Task* p_task) {
	m_tasks.insert(p_index, p_task);
}

Task* TaskListModel::remove(int p_index) {
	return m_tasks.remove(p_index);
}

QModelIndex TaskListModel::indexFromItem(const Task* p_item) const {
	Q_ASSERT(p_item);
	for (int row=0; row<m_tasks.count(); ++row) {
		if (m_tasks.at(row) == p_item)
			return index(row);
	}
	return QModelIndex();
}



