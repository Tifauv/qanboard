#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <QMetaType>
#include <QAbstractListModel>
#include "TaskListModel.h"

class Workflow : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(uint taskId  READ taskId  NOTIFY taskIdChanged  DESIGNABLE false)

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
	TaskListModel* find(const QString& name) const;

	void insertRow(int row, TaskListModel* queue);

signals:
	void taskIdChanged(uint);

public slots:
	uint nextTaskId();
	void createQueue(const QString&);
	uint addTaskToQueue(Task* p_task, const QString& p_queue);
	uint createTaskInQueue(const QString& p_description, const QString& p_queue);

private:
	uint m_taskId;
	QList<TaskListModel*> m_queues;
};

//Q_DECLARE_METATYPE(QList<TaskListModel*>)

#endif // WORKFLOW_H
