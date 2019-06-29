#ifndef TaskQueue_H
#define TaskQueue_H

#include <QMetaType>
#include <QAbstractListModel>
#include "Task.h"

class TaskQueue : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(QString name   READ name   WRITE setName  NOTIFY nameChanged   DESIGNABLE false)
	Q_PROPERTY(int     count  READ count                 NOTIFY countChanged)

public:
	enum Roles {
		TaskIdRole = Qt::UserRole+1,
		ClientRole,
		ActivityRole,
		DescriptionRole,
		DueDateRole,
		TargetRole
	};

	explicit TaskQueue(QObject* parent = nullptr);
	explicit TaskQueue(const TaskQueue&);
	~TaskQueue() override {}

	const QString& name() const;
	int count() const;
	void setName(const QString& p_name);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

public slots:
	void append(Task* task);
	void insert(int row, Task* item);
	bool remove(int row, const QModelIndex &parent = QModelIndex());
	void move(int origin, int destination);

	Task* at(int row) const;
	Task* find(uint taskId) const;

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
Q_DECLARE_METATYPE(QList<TaskQueue*>)

#endif // TaskQueue_H
