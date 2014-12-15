#ifndef TASKQUEUEMODEL_H
#define TASKQUEUEMODEL_H

#include <QObject>
#include "ListModel.h"
#include "TaskQueue.h"

class TaskQueueModel : public ListItem {
	Q_OBJECT

public:
	enum Roles {
		NameRole = Qt::UserRole+1
	};

	explicit TaskQueueModel(QObject* p_parent = 0);
	explicit TaskQueueModel(const TaskQueueModel&);
	explicit TaskQueueModel(const TaskQueue&);
	~TaskQueueModel() {}

	QString id() const;
	QVariant data(int p_role) const;
	void setData(int p_role, QVariant& p_value);
	QHash<int, QByteArray> roleNames() const;

	TaskQueue& model() const;

private:
	const TaskQueue& constModel() const;

	TaskQueue m_list;
};

#endif // TASKQUEUEMODEL_H
