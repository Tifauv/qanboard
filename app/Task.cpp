#include "Task.h"
#include <QtDebug>

/**
 * @brief Default constructor for a task.
 *
 * @param p_taskId
 *            the (unique) task identifier
 * @param p_description
 *            the task's description
 * @param p_category
 *            the task's category
 * @param p_assignee
 *            the task's assignee
 * @param p_parent
 *            the parent QObject
 */
Task::Task(uint p_taskId, const QString& p_description, const QString& p_category, const QString& p_assignee, QObject* p_parent) :
	QObject(p_parent),
	m_taskId(p_taskId),
	m_description(p_description),
	m_category(p_category),
	m_assignee(p_assignee),
	m_selected(false) {
	qDebug() << "(i) [Task] Created " << m_description << " in category " << m_category;
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
	m_description(p_task.description()),
	m_category(p_task.category()),
	m_assignee(p_task.assignee()),
	m_selected(false) {
	qDebug() << "(i) [Task] Copied task " << m_taskId << " with " << m_description << " in category " << m_category;
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
 * @brief Task::description
 * @return
 */
const QString& Task::description() const {
	return m_description;
}


/**
 * @brief Task::category
 * @return
 */
const QString& Task::category() const {
	return m_category;
}


/**
 * @brief Task::assignee
 * @return
 */
const QString& Task::assignee() const {
	return m_assignee;
}


/**
 * @brief Tells whether the task is marked as selected or not.
 *
 * @return true if the task is selected, false otherwise
 */
bool Task::isSelected() const {
	return m_selected;
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
 * @brief Task::setDescription
 * @param p_description
 */
void Task::setDescription(const QString& p_description) {
	m_description = p_description;
	emit descriptionChanged(m_description);
}


/**
 * @brief Task::setCategory
 * @param p_category
 */
void Task::setCategory(const QString& p_category) {
	m_category = p_category;
	emit categoryChanged(m_category);
}


/**
 * @brief Task::setAssignee
 * @param p_assignee
 */
void Task::setAssignee(const QString& p_assignee) {
	m_assignee = p_assignee;
	emit assigneeChanged(m_assignee);
}


/**
 * @brief Task::setSelected
 * @param p_selected
 */
void Task::setSelected(const bool p_selected) {
	m_selected = p_selected;
	emit selectedChanged(m_selected);
}
