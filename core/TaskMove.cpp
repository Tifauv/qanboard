#include "TaskMove.h"
#include <QtDebug>

/**
 * @brief Default constructor for a task move change.
 * 
 * @param p_task
 *            the task that was moved
 * @param p_origin
 *            the queue the task was in before beeing moved
 * @param p_destination
 *            the new queue of the task
 * @param p_timestamp
 *            the timestamp of the move
 * @param p_parent
 *            the parent QObject
 */
TaskMove::TaskMove(const Task& p_task, const TaskQueue& p_origin, const TaskQueue& p_destination, const QDateTime& p_timestamp, QObject *p_parent) :
	QObject(p_parent),
	m_task(p_task),
	m_origin(p_origin),
	m_destination(p_destination),
	m_timestamp(p_timestamp) {
	qDebug() << "(i) [TaskMove] Created for task " << m_task.taskId() << " moved from queue " << m_origin.name() << " to " << m_destination.name() << " at " << m_timestamp.toString("yyyy-MM-dd'T'hh:mm:sst");
}


/**
 * @brief Copy constructor for a task move change.
 * 
 * @param p_taskMove
 *            the task move to copy
 */
TaskMove::TaskMove(const TaskMove& p_taskMove) :
	QObject(),
	m_task(p_taskMove.task()),
	m_origin(p_taskMove.origin()),
	m_destination(p_taskMove.destination()),
	m_timestamp(p_taskMove.timestamp()) {
	qDebug() << "(i) [TaskMove] Copied task " << m_task.taskId() << " moved from queue " << m_origin.name() << " to " << m_destination.name() << " at " << m_timestamp.toString("yyyy-MM-dd'T'hh:mm:sst");
}


// DESTRUCTORS
/**
 * @brief TaskMove::~TaskMove
 */
TaskMove::~TaskMove() {
	qDebug() << "(i) [TaskMove] Destroying move of task " << m_task.taskId() << " from queue " << m_origin.name() << " to " << m_destination.name() << " at " << m_timestamp.toString("yyyy-MM-dd'T'hh:mm:sst");
}


// GETTERS
/**
 * @brief TaskMove::task
 * @return 
 */
const Task& TaskMove::task() const {
	return m_task;
}


/**
 * @brief TaskMove::origin
 * @return 
 */
const TaskQueue& TaskMove::origin() const {
	return m_origin;
}


/**
 * @brief TaskMove::destination
 * @return 
 */
const TaskQueue& TaskMove::destination() const {
	return m_destination;
}


/**
 * @brief TaskMove::timestamp
 * @return 
 */
const QDateTime& TaskMove::timestamp() const {
	return m_timestamp;
}
