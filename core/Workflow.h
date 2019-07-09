#ifndef Workflow_H
#define Workflow_H

#include <QMetaType>
#include <QAbstractListModel>
#include <QDateTime>
#include <QListIterator>
#include "TaskRegistry.h"
#include "TaskQueue.h"
#include "History.h"
#include "TaskMove.h"

class Workflow : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(QString   name          READ name          WRITE setName             NOTIFY nameChanged)
	Q_PROPERTY(uint      taskId        READ taskId        WRITE setTaskId           NOTIFY taskIdChanged        DESIGNABLE false)
	Q_PROPERTY(QString   defaultQueue  READ defaultQueue  WRITE selectDefaultQueue  NOTIFY defaultQueueChanged)
	Q_PROPERTY(QDateTime lastSaved     READ lastSaved     WRITE setLastSaved        NOTIFY lastSavedChanged)
	Q_PROPERTY(int       count         READ count                                   NOTIFY countChanged)
	Q_PROPERTY(int       taskCount     READ taskCount                               NOTIFY taskCountChanged)
	Q_PROPERTY(History*  history       READ history                                 NOTIFY historyChanged)

public:
	enum Roles {
		QueueNameRole = Qt::UserRole+1,
		ColorRole,
		TaskCountRole,
		TaskListRole
	};

	explicit Workflow(QObject* parent = nullptr);
	~Workflow() override {}

	const QString&   name()         const;
	uint             taskId()       const;
	const QString&   defaultQueue() const;
	const QDateTime& lastSaved()    const;
	int              count()        const;
	int              taskCount()    const;
	History*         history()      const;

	void setName(const QString&);
	void setTaskId(uint);
	void selectDefaultQueue(const QString&);
	void setLastSaved(const QDateTime&);

	int rowCount(const QModelIndex& parent) const override;
	QHash<int, QByteArray> roleNames() const override;
	QVariant data(const QModelIndex& index, int role) const override;
	TaskQueue* findQueue(const QString& name) const;

	void insertQueue(int row, TaskQueue* queue);

	QListIterator<Task*> tasksIter() const;
	QListIterator<TaskQueue*> iter() const;
	
	void registerTask(Task*);
	uint loadTaskInQueue(Task* p_task, const QString& p_queue);
	void appendToHistory(TaskMove* taskMove);

public slots:
	void createQueue(const QString& name, const QString& color = QString("#cccccc"));
	uint createTaskInQueue(const QString& p_client, const QString& p_activity, const QString& p_description, const QString& p_dueDate, const QString& p_target, const QString& p_queue);
	uint createTask(const QString& p_client, const QString& p_activity, const QString& p_description, const QString& p_dueDate, const QString& p_target);
	bool appendTaskToQueue(uint taskId, const QString& queueName);
	uint moveBetweenQueues(const QString& p_sourceName, int p_sourceIndex, const QString& p_destinationName, int p_destinationIndex);
	Task* findTask(uint taskId) const;

signals:
	void nameChanged();
	void taskIdChanged();
	void defaultQueueChanged();
	void lastSavedChanged();
	void countChanged();
	void taskCountChanged();
	void historyChanged();

private:
	QString           m_name;
	uint              m_taskId;
	QString           m_defaultQueue;
	QDateTime         m_lastSaved;
	TaskRegistry      m_tasks;
	QList<TaskQueue*> m_queues;
	History*          m_history;
};

#endif // Workflow_H
