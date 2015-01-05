#include "TaskListModel.h"
#include <QList>
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief TaskListModel::TaskListModel
 * @param p_parent
 */
TaskListModel::TaskListModel(QObject* p_parent) :
	QAbstractListModel(p_parent),
	m_name(""),
	m_tasks() {
	QHash<int, QByteArray> names;
	names[TaskIdRole] = "taskId";
	names[DescriptionRole] = "description";
	names[CategoryRole] = "category";
	names[AssigneeRole] = "assignee";
	setRoleNames(names);
	qDebug() << "(i) [TaskListModel] Created.";
}


/**
 * @brief TaskListModel::TaskListModel
 * @param p_toCopy
 */
TaskListModel::TaskListModel(const TaskListModel& p_toCopy) :
	QAbstractListModel(),
	m_name(p_toCopy.name()),
	m_tasks(p_toCopy.m_tasks) {
	qDebug() << "(i) [TaskListModel] Copied queue " << m_name << " with " << m_tasks.count() << " tasks.";
}


// GETTERS
/**
 * @brief TasklistModel::name
 * @return
 */
const QString& TaskListModel::name() const {
	return m_name;
}


// SETTERS
/**
 * @brief TaskListModel::setName
 * @param p_name
 */
void TaskListModel::setName(const QString &p_name) {
	m_name = p_name;
	qDebug() << "(i) [TaskListModel] Changed name to " << p_name;
	emit nameChanged(p_name);
}


// Utilities
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


// MODEL/VIEW API
/**
 * @brief TaskListModel::rowCount
 * @param p_parent
 * @return
 */
int TaskListModel::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	//qDebug() << "(i) TaskListModel::rowCount()";
	return m_tasks.size();
}


/**
 * @brief TaskListModel::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant TaskListModel::data(const QModelIndex& p_index, int p_role) const {
	qDebug() << "(i) TaskListModel::data()";
	if (p_index.row() < 0 || p_index.row() >= rowCount())
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
	if (p_row < 0 || p_row >= rowCount())
		return false;
	beginRemoveRows(QModelIndex(), p_row, p_row);
	Task* task = m_tasks.takeAt(p_row);
	endRemoveRows();
	qDebug() << "(i) [TaskListModel] Task " << task->taskId() << " removed from queue " << name();
	return true;
}


// RAW API
/**
 * @brief TaskListModel::at
 * @param p_index
 * @return
 */
Task* TaskListModel::at(int p_index) const {
	if (p_index < 0 || p_index >= rowCount())
		return NULL;
	return m_tasks.at(p_index);
}


/**
 * @brief TaskListModel::find
 * @param p_taskId
 * @return
 */
Task* TaskListModel::find(uint p_taskId) const {
	foreach(Task* task, m_tasks) {
		if (task->taskId() == p_taskId)
			return task;
	}
	return NULL;
}


/**
 * @brief TaskListModel::add
 * @param p_task
 */
void TaskListModel::appendRow(Task* p_task) {
	Q_ASSERT(p_task);
	insertRow(rowCount(), p_task);
}
