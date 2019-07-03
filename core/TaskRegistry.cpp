#include <QtDebug>
#include "TaskRegistry.h"

// CONSTRUCTORS
TaskRegistry::TaskRegistry(QObject* p_parent) :
	QObject(p_parent) {
	qDebug() << "(i) [TaskRegistry] Created.";
}


// GETTERS
/**
 * @brief Gives the task id that will be associated to the next task.
 * @return 
 */
uint TaskRegistry::getNextTaskId() const {
	return m_nextTaskId;
}


/**
 * @brief Gives the id to use for the next task then increment the next task id.
 * @return 
 */
uint TaskRegistry::nextTaskId() {
	qDebug() << "(i) [TaskRegistry] Next taskId is " << m_nextTaskId ;
	return m_nextTaskId++;
}


// PUBLIC FUNCTIONS
/**
 * @brief TaskRegistry::iter
 * @return 
 */
QListIterator<Task*> TaskRegistry::iter() const {
	return QListIterator<Task*>(m_tasks.values());
}


// PUBLIC SLOTS
void TaskRegistry::initNextTaskId(uint p_nextId) {
	m_nextTaskId = p_nextId;
	qDebug() << "(i) [TaskRegistry] Next task id reset to " << m_nextTaskId;
}


/**
 * @brief TaskRegistry::registerTask
 * 
 * This is to be used to load tasks from a previous state (when loading a Workspace from 
 * a saved file).
 * The Task Registry takes ownership of the task.
 * The task's id is reset with the registry's next task id (which gets incremented).
 * 
 * @param p_task
 * @return the new task's id
 */
void TaskRegistry::loadTask(Task* p_task) {
	Q_ASSERT(p_task);
	
	p_task->setParent(this);
	m_tasks.insert(p_task->taskId(), p_task);
	qDebug() << "(i) [TaskRegistry] Task #" << p_task->taskId() << " loaded";
}


/**
 * @brief TaskRegistry::registerTask
 * 
 * This is for newly created tasks.
 * The Task Registry takes ownership of the task.
 * The task's id is reset with the registry's next task id (which gets incremented).
 * 
 * @param p_task
 * @return the new task's id
 */
uint TaskRegistry::registerTask(Task* p_task) {
	Q_ASSERT(p_task);
	
	p_task->setParent(this);
	p_task->setTaskId(nextTaskId());
	m_tasks.insert(p_task->taskId(), p_task);
	qDebug() << "(i) [TaskRegistry] Task #" << p_task->taskId() << " registered";
	emit taskRegistered(*p_task);
	return p_task->taskId();
}


/**
 * @brief TaskRegistry::unregisterTask
 * @param p_taskId
 */
void TaskRegistry::unregisterTask(uint p_taskId) {
	Task* task = m_tasks.take(p_taskId);
	if (task) {
		qDebug() << "(i) [TaskRegistry] Task #" << task->taskId() << " unregistered";
		emit taskUnregistered(*task);
		delete task;
		qDebug() << "(i) [TaskRegistry] Task #" << task->taskId() << " deleted";
	}
}


Task* TaskRegistry::find(uint p_taskId) const {
	return m_tasks.value(p_taskId);
}
