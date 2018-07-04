#include "Workflow.h"
#include <QList>
#include <QtDebug>


/**
 * @brief Workflow::Workflow
 * @param p_parent
 */
Workflow::Workflow(QObject* p_parent) :
	QAbstractListModel(p_parent),
	m_taskId(0),
	m_defaultQueue(),
	m_queues() {
	qDebug() << "(i) [Workflow] Created";
}


// GETTERS
/**
 * @brief Workflow::taskId
 * @return
 */
uint Workflow::taskId() const {
	return m_taskId;
}


/**
 * @brief Workflow::defaultQueue
 * @return
 */
const QString& Workflow::defaultQueue() const {
	return m_defaultQueue;
}


/**
 * @brief Workflow::count
 * @return
 */
int Workflow::count() const {
	return m_queues.count();
}


/**
 * @brief Workflow::nextTaskId
 * @return
 */
uint Workflow::nextTaskId() {
	qDebug() << "(i) [Workflow] Current taskId is " << m_taskId ;
	return m_taskId++;
}


// SETTERS
/**
 * @brief Workflow::setTaskId
 * @param p_taskId
 */
void Workflow::setTaskId(uint p_taskId) {
	m_taskId = p_taskId;
}


/**
 * @brief Workflow::setDefaultQueue
 * @param p_queueName
 */
void Workflow::setDefaultQueue(const QString& p_queueName) {
	m_defaultQueue = p_queueName;
}


// MODEL/VIEW API
/**
 * @brief Workflow::rowCount
 * @param p_parent
 * @return
 */
int Workflow::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	return m_queues.size();
}


/**
 * @brief Workflow::roleNames
 * @return
 */
QHash<int, QByteArray> Workflow::roleNames() const {
	QHash<int, QByteArray> names;
	names[QueueNameRole] = "name";
	names[TaskListRole] = "tasks";
	return names;
}


/**
 * @brief Workflow::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant Workflow::data(const QModelIndex& p_index, int p_role) const {
	if (p_index.row() < 0 || p_index.row() >= m_queues.size())
		return QVariant();

	qDebug() << "(i) [Workflow] Looking for data at row " << p_index.row() << " with role " << p_role;
	TaskQueue* queue = m_queues.at(p_index.row());
	switch (p_role) {
	case QueueNameRole:
		return queue->name();
	case TaskListRole:
		return QVariant::fromValue(queue);
	default:
		return QVariant();
	}
}


/**
 * @brief Workflow::iter
 * @return
 */
QListIterator<TaskQueue*> Workflow::iter() const {
	return QListIterator<TaskQueue*>(m_queues);
}


/**
 * @brief Workflow::find
 * @param p_name
 * @return
 */
TaskQueue* Workflow::find(const QString& p_name) const {
	qDebug() << "(i) [Workflow] Searching queue " << p_name;
	foreach (TaskQueue* queue, m_queues) {
		if (queue->name() == p_name)
			return queue;
	}

    return nullptr;
}


/**
 * @brief Workflow::insertRow
 * @param p_row
 * @param p_queue
 */
void Workflow::insertRow(int p_row, TaskQueue* p_queue) {
	beginInsertRows(QModelIndex(), p_row, p_row);
	m_queues.insert(p_row, p_queue);
	endInsertRows();
	emit countChanged(count());
	qDebug() << "(i) [Workflow] Queue " << p_queue->name() << " added";
}


/**
 * @brief Workflow::createQueue
 * @param p_name
 */
void Workflow::createQueue(const QString& p_name) {
	TaskQueue* queue = new TaskQueue(this);
	queue->setName(p_name);
	insertRow(m_queues.size(), queue);
}


/**
 * @brief Workflow::addTaskToQueue
 * @param p_task
 * @param p_queue
 * @return
 */
uint Workflow::addTaskToQueue(Task* p_task, const QString& p_queue) {
	TaskQueue* queue = find(p_queue);
	if (queue) {
		qDebug() << "(i) [Workflow] Queue " << p_queue << " found";
		queue->appendRow(p_task);
	}
	else {
		qWarning() << "/!\\ [Workflow] Queue " << p_queue << " does not exist";
	}
	return p_task->taskId();
}


/**
 * @brief Workflow::createTaskInQueue
 * @param p_description
 * @param p_queue
 * @return
 */
uint Workflow::createTaskInQueue(const QString& p_description, const QString& p_queue) {
	qDebug() << "(i) [Workflow] Creating new task in queue " << p_queue << "...";
	return addTaskToQueue(new Task(nextTaskId(), p_description), p_queue);
}


/**
 * @brief Reimplementation of Workflow::createTaskInQueue() that uses the defaultQueue.
 * @param p_description
 * @param p_queue
 * @return
 */
uint Workflow::createTask(const QString& p_description) {
	return createTaskInQueue(p_description, defaultQueue());
}