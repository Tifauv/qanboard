#ifndef Workflow_H
#define Workflow_H

#include <QMetaType>
#include <QAbstractListModel>
#include <QListIterator>
#include "TaskRegistry.h"
#include "TaskQueue.h"
#include "TaskMove.h"

class Workflow : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(uint    taskId        READ taskId        WRITE setTaskId        NOTIFY taskIdChanged  DESIGNABLE false)
	Q_PROPERTY(QString defaultQueue  READ defaultQueue)
	Q_PROPERTY(int     count         READ count                                NOTIFY countChanged)

public:
	enum Roles {
		QueueNameRole = Qt::UserRole+1,
		TaskListRole
	};

	explicit Workflow(QObject* parent = nullptr);
	~Workflow() override {}

	uint taskId() const;
	const QString& defaultQueue() const;
	int count() const;
	const QList<TaskMove*>& history() const;

	void setTaskId(uint);
	void selectDefaultQueue(const QString&);

	int rowCount(const QModelIndex& parent) const override;
	QHash<int, QByteArray> roleNames() const override;
	QVariant data(const QModelIndex& index, int role) const override;
	TaskQueue* findQueue(const QString& name) const;
	Task* findTask(uint taskId) const;

	void insertRow(int row, TaskQueue* queue);

	QListIterator<TaskQueue*> iter() const;
	
	uint loadTaskInQueue(Task* p_task, const QString& p_queue);
	void appendToHistory(TaskMove* taskMove);

public slots:
	void createQueue(const QString&);
	uint createTaskInQueue(const QString& p_client, const QString& p_activity, const QString& p_description, const QString& p_dueDate, const QString& p_target, const QString& p_queue);
	uint createTask(const QString& p_client, const QString& p_activity, const QString& p_description, const QString& p_dueDate, const QString& p_target);
	uint moveBetweenQueues(const QString& p_sourceName, int p_sourceIndex, const QString& p_destinationName, int p_destinationIndex);

signals:
	void taskIdChanged(uint);
	void countChanged(int);

private:
	uint              m_taskId;
	QString           m_defaultQueue;
	QList<TaskQueue*> m_queues;
	TaskRegistry      m_tasks;
	QList<TaskMove*>  m_history;
};

#endif // Workflow_H
