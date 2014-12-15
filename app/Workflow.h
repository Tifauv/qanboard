#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <QObject>
#include "ListModel.h"
#include "Task.h"

class Workflow : public ListModel {
	Q_OBJECT

	Q_PROPERTY(uint taskId  READ taskId  NOTIFY taskIdChanged  DESIGNABLE false)

public:
	explicit Workflow(QObject *parent = 0);
	~Workflow() {}

	uint taskId() const;

signals:
	void taskIdChanged(uint);

public slots:
	uint nextTaskId();
	void createQueue(const QString&);
	uint addTaskToQueue(Task& p_task, const QString& p_queue);
	uint createTaskInQueue(const QString& p_description, const QString& p_queue);

private:
	uint m_taskId;
};

#endif // WORKFLOW_H
