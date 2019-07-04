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
    m_tasks(),
    m_queues(),
	m_history(new History(this)) {
	qDebug() << "(i) [Workflow] Created";
}


// GETTERS
/**
 * @brief Workflow::name
 * @return 
 */
const QString& Workflow::name() const {
	return m_name;
}


/**
 * @brief Workflow::taskId
 * @return
 */
uint Workflow::taskId() const {
	return m_tasks.getNextTaskId();
}


/**
 * @brief Workflow::defaultQueue
 * @return
 */
const QString& Workflow::defaultQueue() const {
	return m_defaultQueue;
}


/**
 * @brief Workflow::lastSaved
 * @return
 */
const QDateTime& Workflow::lastSaved() const {
	return m_lastSaved;
}


/**
 * @brief Workflow::count
 * @return
 */
int Workflow::count() const {
	return m_queues.count();
}


/**
 * @brief Workflow::history
 * @return 
 */
History* Workflow::history() const {
	return m_history;
}


// SETTERS
/**
 * @brief Workflow::setName
 * @param p_name
 */
void Workflow::setName(const QString& p_name) {
	if (m_name != p_name) {
		m_name = p_name;
		emit nameChanged();
	}
}


/**
 * @brief Workflow::setTaskId
 * @param p_taskId
 */
void Workflow::setTaskId(uint p_taskId) {
	m_tasks.initNextTaskId(p_taskId);
}


/**
 * @brief Workflow::setDefaultQueue
 * @param p_queueName
 */
void Workflow::selectDefaultQueue(const QString& p_queueName) {
	// If the requested default queue exists, select it as default
	if (!p_queueName.isEmpty() && findQueue(p_queueName) != nullptr)
		m_defaultQueue = p_queueName;
	// If there is at least one queue loaded, select the first queue
	else if (!m_queues.isEmpty())
		m_defaultQueue = m_queues.first()->name();
	// Otherwise, no default
	else
		m_defaultQueue = "";
}


/**
 * @brief Workflow::setLastSaved
 * @param p_date
 */
void Workflow::setLastSaved(const QDateTime& p_date) {
	if (m_lastSaved != p_date) {
		m_lastSaved = p_date;
		emit lastSavedChanged();
	}
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
	names[ColorRole]     = "color";
	names[TaskListRole]  = "tasks";
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
	case ColorRole:
		return queue->color();
	case TaskListRole:
		return QVariant::fromValue(queue);
	default:
		return QVariant();
	}
}


/**
 * @brief Workflow::tasksIter
 * @return 
 */
QListIterator<Task*> Workflow::tasksIter() const {
	return m_tasks.iter();
}

/**
 * @brief Workflow::iter
 * @return
 */
QListIterator<TaskQueue*> Workflow::iter() const {
	return QListIterator<TaskQueue*>(m_queues);
}


/**
 * @brief Workflow::findQueue
 * @param p_name
 * @return
 */
TaskQueue* Workflow::findQueue(const QString& p_name) const {
	qDebug() << "(i) [Workflow] Searching queue " << p_name;
	foreach (TaskQueue* queue, m_queues) {
		if (queue->name() == p_name)
			return queue;
	}

	return nullptr;
}


/**
 * @brief Workflow::findTask
 * @param p_taskId
 * @return 
 */
Task* Workflow::findTask(uint p_taskId) const {
	qDebug() << "(i) [Workflow] Searching task " << p_taskId;
	return m_tasks.find(p_taskId);
}


/**
 * @brief Workflow::appendToHistory
 * @param p_change
 */
void Workflow::appendToHistory(TaskMove* p_change) {
	Q_ASSERT(p_change);

	m_history->append(p_change);
	emit historyChanged();
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
	emit countChanged();
	qDebug() << "(i) [Workflow] Queue " << p_queue->name() << " added";
}


/**
 * @brief Workflow::createQueue
 * @param p_name
 * @param p_color
 */
void Workflow::createQueue(const QString& p_name, const QString& p_color) {
	TaskQueue* queue = new TaskQueue(this);
	queue->setName(p_name);
	queue->setColor(p_color);
	insertRow(m_queues.size(), queue);
}


/**
 * @brief Workflow::registerTask
 * @param p_task
 */
void Workflow::registerTask(Task* p_task) {
	Q_ASSERT(p_task);
	
	m_tasks.loadTask(p_task);
}


/**
 * @brief Workflow::addTaskToQueue
 * @param p_task
 * @param p_queue
 * @return
 */
uint Workflow::loadTaskInQueue(Task* p_task, const QString& p_queue) {
	Q_ASSERT(p_task);
	
	TaskQueue* queue = findQueue(p_queue);
	if (queue) {
		qDebug() << "(i) [Workflow] Queue " << p_queue << " found";
		m_tasks.loadTask(p_task);
		queue->append(p_task);
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
	Task* task = new Task(0, p_client, p_activity, p_description, p_dueDate, p_target);
	m_tasks.registerTask(task);
	return loadTaskInQueue(task, p_queue);
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
 * @brief Workflow::addTaskToQueue
 * @param p_taskId
 * @param p_queueName
 * @return 
 */
bool Workflow::appendTaskToQueue(uint p_taskId, const QString& p_queueName) {
	// Retrieve the task
	Task* task = findTask(p_taskId);
	if (task == nullptr) {
		qWarning() << "/!\\ [Workflow::addTaskToQueue] There is no task #" << p_taskId << " to append to queue " << p_queueName;
		return false;
	}
	
	// Retrieve the queue
	TaskQueue* queue = findQueue(p_queueName);
	if (queue == nullptr) {
		qWarning() << "/!\\ [Workflow::addTaskToQueue] There is no queue " << p_queueName << " in which to append task #" << p_taskId;
		return false;
	}
	
	// Append the task to the queue
	queue->append(task);
	qDebug() << "(i) [Workflow::addTaskToQueue] Task #" << p_taskId << " appended to queue " << p_queueName;
	return true;
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
	auto source = findQueue(p_sourceName);
	if (!source) {
		qWarning() << "/!\\ [Workflow] Source queue " << p_sourceName << " does not exist";
		return 1;
	}
	auto destination = findQueue(p_destinationName);
	if (!destination) {
		qWarning() << "/!\\ [Workflow] Destination queue " << p_destinationName << " does not exist";
		return 2;
	}
	
	auto task = source->at(p_sourceIndex);
	if (source->remove(p_sourceIndex)) {
		if (p_destinationIndex == -1)
			destination->append(task);
		else
			destination->insert(p_destinationIndex, task);
		appendToHistory(new TaskMove(*task, *source, *destination));
	}
	else {
		qWarning() << "/!\\ [Workflow] Index " << p_sourceIndex << " for source queue " << p_sourceName << " is invalid";
		return 3;
	}
	
	return 0;
}
