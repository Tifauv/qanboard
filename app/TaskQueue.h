#ifndef TaskQueue_H
#define TaskQueue_H

#include <QMetaType>
#include <QAbstractListModel>
#include "Task.h"

class TaskQueue : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(QString name  READ name  WRITE setName  NOTIFY nameChanged  DESIGNABLE false)
    Q_PROPERTY(int     count READ count                NOTIFY countChanged)

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
	int count() const;
	void setName(const QString& p_name);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

public slots:
	void insertRow(int row, Task* item);
	bool removeRow(int row, const QModelIndex &parent = QModelIndex());

	Task* at(int row) const;
	Task* find(uint taskId) const;
	void appendRow(Task* task);
	void moveRow(int origin, int destination);

	void log();

signals:
	void nameChanged(const QString&);
	void countChanged(int);

private slots:
	void handleDataChanged();

private:
	QString      m_name;
	QList<Task*> m_tasks;
};

Q_DECLARE_METATYPE(TaskQueue)
Q_DECLARE_METATYPE(TaskQueue*)
Q_DECLARE_METATYPE(QList<TaskQueue*>)

#endif // TaskQueue_H
