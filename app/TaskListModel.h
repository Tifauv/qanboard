#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QAbstractListModel>
#include "TaskQueue.h"

class TaskListModel : public QAbstractListModel {
	Q_OBJECT

public:
	enum Roles {
		TaskIdRole = Qt::UserRole+1,
		DescriptionRole,
		CategoryRole,
		AssigneeRole
	};

	explicit TaskListModel(QObject* parent = 0);
	explicit TaskListModel(const TaskQueue& data, QObject* parent = 0);
	explicit TaskListModel(const TaskListModel&);
	~TaskListModel() {}

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	void insertRow(int row, Task* item);
	bool removeRow(int row, const QModelIndex &parent = QModelIndex());

public slots:
	int count() const;
	Task* at(int row) const;
	Task* find(uint taskId) const;
	void add(Task* task);
	void insert(int index, Task* task);
	Task* remove(int index);

	QModelIndex indexFromItem(const Task* item) const;

private:
	QString itemId(Task* item) const;
	QVariant itemData(Task* item, int role) const;
	QHash<int, QByteArray> roleNames() const;

	TaskQueue m_tasks;
};

Q_DECLARE_METATYPE(TaskListModel*)

#endif // TASKLISTMODEL_H
