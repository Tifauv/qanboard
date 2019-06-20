#include "Task.h"
#include <QtDebug>

/**
 * @brief Default constructor for a task.
 *
 * @param p_taskId
 *            the (unique) task identifier
 * @param p_client
 *            the task's client
 * @param p_activity
 *            the task's activity
 * @param p_description
 *            the task's description
 * @param p_due date
 *            the task's expected completion date
 * @param p_target
 *            the task's target object (CI)
 * @param p_parent
 *            the parent QObject
 */
Task::Task(uint p_taskId, const QString& p_client, const QString& p_activity, const QString& p_description, const QString& p_dueDate, const QString& p_target, QObject* p_parent) :
	QObject(p_parent),
	m_taskId(p_taskId),
	m_client(p_client),
    m_activity(p_activity),
    m_description(p_description),
	m_dueDate(p_dueDate),
    m_target(p_target) {
	qDebug() << "(i) [Task] Created " << m_taskId << " for client " << m_client;
}


/**
 * @brief Copy constructor for a task.
 *
 * @param p_task
 *            the task to copy
 */
Task::Task(const Task& p_task) :
	QObject(),
	m_taskId(p_task.taskId()),
	m_client(p_task.client()),
    m_activity(p_task.activity()),
	m_description(p_task.description()),
	m_dueDate(p_task.dueDate()),
    m_target(p_task.target()) {
	qDebug() << "(i) [Task] Copied task " << m_taskId << " for client " << m_client;
}


// DESTRUCTORS
Task::~Task() {
	qDebug() << "(i) [Task] Destroying task " << m_taskId;
}

// GETTERS
/**
 * @brief Task::taskId
 * @return
 */
uint Task::taskId() const {
	return m_taskId;
}


/**
 * @brief Task::client
 * @return
 */
const QString& Task::client() const {
	return m_client;
}


/**
 * @brief Task::activity
 * @return
 */
const QString& Task::activity() const {
	return m_activity;
}


/**
 * @brief Task::description
 * @return
 */
const QString& Task::description() const {
	return m_description;
}


/**
 * @brief Task::dueDate
 * @return
 */
const QString& Task::dueDate() const {
	return m_dueDate;
}


/**
 * @brief Task::target
 * @return
 */
const QString& Task::target() const {
	return m_target;
}


/**
 * @brief Task::setTaskId
 * @param p_taskId
 */
void Task::setTaskId(uint p_taskId) {
	m_taskId = p_taskId;
	emit taskIdChanged(m_taskId);
}


/**
 * @brief Task::setClient
 * @param p_client
 */
void Task::setClient(const QString& p_client) {
	m_client = p_client;
	emit clientChanged(m_client);
}


/**
 * @brief Task::setActivity
 * @param p_activity
 */
void Task::setActivity(const QString& p_activity) {
	m_activity = p_activity;
	emit activityChanged(m_activity);
}


/**
 * @brief Task::setDescription
 * @param p_description
 */
void Task::setDescription(const QString& p_description) {
	m_description = p_description;
	emit descriptionChanged(m_description);
}


/**
 * @brief Task::setDueDate
 * @param p_title
 */
void Task::setDueDate(const QString& p_title) {
	m_dueDate = p_title;
	emit dueDateChanged(m_dueDate);
}


/**
 * @brief Task::setTarget
 * @param p_target
 */
void Task::setTarget(const QString& p_target) {
	m_target = p_target;
	emit targetChanged(m_target);
}
