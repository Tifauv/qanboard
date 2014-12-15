#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QMetaType>
#include "ListModel.h"
#include "Task.h"

class TaskModel : public ListItem {
	Q_OBJECT

public:
	enum Roles {
		TaskIdRole = Qt::UserRole+1,
		DescriptionRole,
		CategoryRole,
		AssigneeRole
	};

	explicit TaskModel(QObject* p_parent = 0);
	explicit TaskModel(const TaskModel&);
	explicit TaskModel(const Task&);
	~TaskModel() {}

	QString id() const;
	QVariant data(int p_role) const;
	void setData(int p_role, QVariant& p_value);
	QHash<int, QByteArray> roleNames() const;

private:
	const Task& model() const;

	Task m_task;
};

#endif // TaskModel_H
