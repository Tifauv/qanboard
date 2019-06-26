#ifndef TaskMove_H
#define TaskMove_H

#include <QObject>
#include <QDateTime>
#include "Task.h"
#include "TaskQueue.h"

class TaskMove : public QObject {
	Q_OBJECT

	/*Q_PROPERTY(Task task              READ task         DESIGNABLE false)
	Q_PROPERTY(TaskQueue origin       READ origin       DESIGNABLE false)
	Q_PROPERTY(TaskQueue destination  READ destination  DESIGNABLE false)
	Q_PROPERTY(QDateTime timestamp    READ timestamp    DESIGNABLE false)*/
	
public:
	explicit TaskMove(const Task& p_task, const TaskQueue& p_origin, const TaskQueue& p_destination, const QDateTime& p_timestamp = QDateTime::currentDateTime(), QObject *p_parent = nullptr);
	explicit TaskMove(const TaskMove&);
	virtual ~TaskMove();
	
	const Task& task() const;
	const TaskQueue& origin() const;
	const TaskQueue& destination() const;
	const QDateTime& timestamp() const;
	
private:
	const Task& m_task;
	const TaskQueue& m_origin;
	const TaskQueue& m_destination;
	const QDateTime  m_timestamp;
};

//Q_DECLARE_METATYPE(TaskMove)

#endif // TaskMove_H
