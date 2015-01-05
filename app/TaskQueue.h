#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <QMetaType>
#include <QObject>
#include <QList>
#include "Task.h"

class TaskQueue : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString name  READ name  WRITE setName  NOTIFY nameChanged  DESIGNABLE false)

public:
	explicit TaskQueue(QObject *parent = 0);
	explicit TaskQueue(const TaskQueue&);
	~TaskQueue() {}

	const QString& name() const;
	void setName(const QString& p_name);

	int count() const;
	Task* at(int index) const;
	Task* find(uint taskId) const;
	void add(Task* task);
	void insert(int index, Task* task);
	Task* remove(int index);

signals:
	void nameChanged(const QString&);
	void taskAdded(int, Task*);
	void taskRemoved(int, Task*);

private:
	QString      m_name;
	QList<Task*> m_tasks;
};

Q_DECLARE_METATYPE(TaskQueue*)

#endif // TASKQUEUE_H
