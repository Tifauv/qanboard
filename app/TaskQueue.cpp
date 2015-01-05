#include "TaskQueue.h"
#include <QList>
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief TaskQueue::TaskQueue
 * @param p_parent
 */
TaskQueue::TaskQueue(QObject* p_parent) :
	QAbstractListModel(p_parent),
	m_name(""),
	m_tasks() {
	QHash<int, QByteArray> names;
	names[TaskIdRole] = "taskId";
	names[DescriptionRole] = "description";
	names[CategoryRole] = "category";
	names[AssigneeRole] = "assignee";
	setRoleNames(names);
	qDebug() << "(i) [TaskQueue] Created.";
}


/**
 * @brief TaskQueue::TaskQueue
 * @param p_toCopy
 */
TaskQueue::TaskQueue(const TaskQueue& p_toCopy) :
	QAbstractListModel(),
	m_name(p_toCopy.name()),
	m_tasks(p_toCopy.m_tasks) {
	QHash<int, QByteArray> names;
	names[TaskIdRole] = "taskId";
	names[DescriptionRole] = "description";
	names[CategoryRole] = "category";
	names[AssigneeRole] = "assignee";
	setRoleNames(names);
	qDebug() << "(i) [TaskQueue] Copied queue " << m_name << " with " << m_tasks.count() << " tasks.";
}


// GETTERS
/**
 * @brief TaskQueue::name
 * @return
 */
const QString& TaskQueue::name() const {
	return m_name;
}


// SETTERS
/**
 * @brief TaskQueue::setName
 * @param p_name
 */
void TaskQueue::setName(const QString &p_name) {
	m_name = p_name;
	qDebug() << "(i) [TaskQueue] Changed name to " << p_name;
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
QString TaskQueue::itemId(Task* p_item) const {
	qDebug() << "(i) TaskQueue::itemId()";
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
QVariant TaskQueue::itemData(Task* p_item, int p_role) const {
	qDebug() << "(i) TaskQueue::itemData()";
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
 * @brief TaskQueue::rowCount
 * @param p_parent
 * @return
 */
int TaskQueue::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	//qDebug() << "(i) TaskQueue::rowCount()";
	return m_tasks.size();
}


/**
 * @brief TaskQueue::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant TaskQueue::data(const QModelIndex& p_index, int p_role) const {
	qDebug() << "(i) TaskQueue::data()";
	if (p_index.row() < 0 || p_index.row() >= rowCount())
		return QVariant();
	return itemData(m_tasks.at(p_index.row()), p_role);
}


/**
 * @brief TaskQueue::insertRow
 * @param p_row
 * @param p_item
 */
void TaskQueue::insertRow(int p_row, Task* p_item) {
	beginInsertRows(QModelIndex(), p_row, p_row);
	//connect(p_item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
	m_tasks.insert(p_row, p_item);
	endInsertRows();
}


/**
 * @brief TaskQueue::removeRow
 * @param p_row
 * @param p_parent
 * @return
 */
bool TaskQueue::removeRow(int p_row, const QModelIndex& p_parent) {
	Q_UNUSED(p_parent);
	if (p_row < 0 || p_row >= rowCount())
		return false;
	beginRemoveRows(QModelIndex(), p_row, p_row);
	Task* task = m_tasks.takeAt(p_row);
	endRemoveRows();
	qDebug() << "(i) [TaskQueue] Task " << task->taskId() << " removed from queue " << name();
	return true;
}


// RAW API
/**
 * @brief TaskQueue::at
 * @param p_index
 * @return
 */
Task* TaskQueue::at(int p_index) const {
	if (p_index < 0 || p_index >= rowCount())
		return NULL;
	return m_tasks.at(p_index);
}


/**
 * @brief TaskQueue::find
 * @param p_taskId
 * @return
 */
Task* TaskQueue::find(uint p_taskId) const {
	foreach(Task* task, m_tasks) {
		if (task->taskId() == p_taskId)
			return task;
	}
	return NULL;
}


/**
 * @brief TaskQueue::add
 * @param p_task
 */
void TaskQueue::appendRow(Task* p_task) {
	Q_ASSERT(p_task);
	insertRow(rowCount(), p_task);
}


/**
 * @brief TaskQueue::moveRow
 * @param p_origin
 * @param p_destination
 */
void TaskQueue::moveRow(int p_row, int p_destination) {
	int destination = p_destination;
	if (destination == -1)
		destination = rowCount();

	QModelIndex parent;
	if (beginMoveRows(parent, p_row, p_row, parent, destination)) {
		qDebug() << "(i) [TaskQueue] Moving task from row " << p_row << " to " << destination;
		m_tasks.move(p_row, destination-1);
		endMoveRows();
	}
	else {
		qDebug() << "(i) [TaskQueue] Moving task from row " << p_row << " to " << destination << " was rejected.";
	}

}
