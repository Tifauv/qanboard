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
void Workflow::selectDefaultQueue(const QString& p_queueName) {
	// If the requested default queue exists, select it as default
	if (!p_queueName.isEmpty() && find(p_queueName) != nullptr)
		m_defaultQueue = p_queueName;
	// If there is at least one queue loaded, select the first queue
	else if (!m_queues.isEmpty())
		m_defaultQueue = m_queues.first()->name();
	// Otherwise, no default
	else
		m_defaultQueue = "";
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
 * @param p_client
 * @param p_activity
 * @param p_description
 * @param p_dueDate
 * @param p_target
 * @param p_queue
 * @return
 */
uint Workflow::createTaskInQueue(const QString& p_client, const QString& p_activity, const QString& p_description, const QString& p_dueDate, const QString& p_target, const QString& p_queue) {
	qDebug() << "(i) [Workflow] Creating new task in queue " << p_queue << "...";
	return addTaskToQueue(new Task(nextTaskId(), p_client, p_activity, p_description, p_dueDate, p_target), p_queue);
}


/**
 * @brief Reimplementation of Workflow::createTaskInQueue() that uses the defaultQueue.
 * @param p_client
 * @param p_activity
 * @param p_description
 * @param p_dueDate
 * @param p_target
 * @return
 */
uint Workflow::createTask(const QString& p_client, const QString& p_activity, const QString& p_description, const QString& p_dueDate, const QString& p_target) {
	return createTaskInQueue(p_client, p_activity, p_description, p_dueDate, p_target, defaultQueue());
}


/**
 * @brief Workflow::moveBetweenQueues
 * @param p_sourceName
 * @param p_sourceIndex
 * @param p_destinationName
 * @param p_destinationIndex
 * 
 * @return 0 : move done
 *  1 : source queue does not exist
 *  2 : destination queue does not exist
 *  3 : source index invalid
 */
uint Workflow::moveBetweenQueues(const QString& p_sourceName, int p_sourceIndex, const QString& p_destinationName, int p_destinationIndex) {
	auto source = find(p_sourceName);
	if (!source) {
		qWarning() << "/!\\ [Workflow] Source queue " << p_sourceName << " does not exist";
		return 1;
	}
	auto destination = find(p_destinationName);
	if (!destination) {
		qWarning() << "/!\\ [Workflow] Destination queue " << p_destinationName << " does not exist";
		return 2;
	}
	
	auto task = source->at(p_sourceIndex);
	if (source->removeRow(p_sourceIndex)) {
		if (p_destinationIndex == -1)
			destination->appendRow(task);
		else
			destination->insertRow(p_destinationIndex, task);
		m_history.append(new TaskMove(*task, *source, *destination));
	}
	else {
		qWarning() << "/!\\ [Workflow] Index " << p_sourceIndex << " for source queue " << p_sourceName << " is invalid";
		return 3;
	}
	
	return 0;
}
