#ifndef TaskRegistry_H
#define TaskRegistry_H

#include <QObject>
#include <QMap>
#include "Task.h"

/**
 * @brief The TaskRegistry is responsible for the tasks' life cycle.
 */
class TaskRegistry : public QObject {
	Q_OBJECT
	
public:
	explicit TaskRegistry(QObject* p_parent = nullptr);
	
	uint getNextTaskId() const;
	
	QListIterator<Task*> iter() const;
	
signals:
	void taskRegistered(const Task& task);
	void taskUnregistered(const Task& task);
	
public slots:
	void initNextTaskId(uint taskId);
	void loadTask(Task*);
	uint registerTask(Task*);
	void unregisterTask(uint taskId);
	
	Task* find(uint taskId) const;

protected:
	uint nextTaskId();

private:
	uint m_nextTaskId;
	QMap<uint,Task*> m_tasks;
};

#endif // TaskRegistry_H
