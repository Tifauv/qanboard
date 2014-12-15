#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <QObject>
#include "ListModel.h"

class TaskQueue : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString   name  READ name  WRITE setName  NOTIFY nameChanged  DESIGNABLE false)
	Q_PROPERTY(ListModel* tasks READ tasks)

public:
	explicit TaskQueue(QObject *parent = 0);
	explicit TaskQueue(const TaskQueue&);
	~TaskQueue() {}

	const QString& name() const;
	ListModel* tasks() const;

	void setName(const QString& p_name);

signals:
	void nameChanged(const QString&);

private:
	QString    m_name;
	ListModel* m_tasks;
};

#endif // TASKQUEUE_H
