#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <QMetaType>
#include <QAbstractListModel>
#include "TaskQueue.h"

class Workflow : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(uint taskId  READ taskId  NOTIFY taskIdChanged  DESIGNABLE false)
	Q_PROPERTY(int  count   READ count   NOTIFY countChanged)

public:
	enum Roles {
		QueueNameRole = Qt::UserRole+1,
		TaskListRole
	};

	explicit Workflow(QObject* parent = 0);
	~Workflow() {}

	uint taskId() const;

	int rowCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
	TaskQueue* find(const QString& name) const;

	void insertRow(int row, TaskQueue* queue);

public slots:
	int count() const;
	uint nextTaskId();
	void createQueue(const QString&);
	uint addTaskToQueue(Task* p_task, const QString& p_queue);
	uint createTaskInQueue(const QString& p_description, const QString& p_queue);

signals:
	void taskIdChanged(uint);
	void countChanged(int);

private:
	uint m_taskId;
	QList<TaskQueue*> m_queues;
};

//Q_DECLARE_METATYPE(QList<TaskQueue*>)

#endif // WORKFLOW_H
