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
		AssigneeRole,
		CategoryRole
	};

	explicit TaskModel(QObject *p_parent = 0);
	explicit TaskModel(const TaskModel&);
	~TaskModel() {}

	QString id() const;
	QVariant data(int p_role) const;
	void setData(int p_role, QVariant& p_value);
	QHash<int, QByteArray> roleNames() const;

	const Task& model() const;

private:
	Task m_task;
};

#endif // TaskModel_H
