#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include <QMetaType>
#include <QAbstractListModel>
#include "Task.h"

class TaskQueue : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(QString name  READ name  WRITE setName  NOTIFY nameChanged  DESIGNABLE false)

public:
	enum Roles {
		TaskIdRole = Qt::UserRole+1,
		DescriptionRole,
		CategoryRole,
		AssigneeRole
	};

	explicit TaskQueue(QObject* parent = 0);
	explicit TaskQueue(const TaskQueue&);
	~TaskQueue() {}

	const QString& name() const;
	void setName(const QString& p_name);

public slots:
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	void insertRow(int row, Task* item);
	bool removeRow(int row, const QModelIndex &parent = QModelIndex());

	Task* at(int row) const;
	Task* find(uint taskId) const;
	void appendRow(Task* task);
	void moveRow(int origin, int destination);

signals:
	void nameChanged(const QString&);

private:
	QString itemId(Task* item) const;
	QVariant itemData(Task* item, int role) const;
	QHash<int, QByteArray> roleNames() const;

	QString      m_name;
	QList<Task*> m_tasks;
};

Q_DECLARE_METATYPE(TaskQueue)
Q_DECLARE_METATYPE(TaskQueue*)
Q_DECLARE_METATYPE(QList<TaskQueue*>)

#endif // TASKQUEUE_H
