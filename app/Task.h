#ifndef TASK_H
#define TASK_H

#include <QMetaType>

class Task : public QObject {
	Q_OBJECT

	Q_PROPERTY(uint taskId         READ taskId      WRITE setTaskId      NOTIFY taskIdChanged      DESIGNABLE true)
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged DESIGNABLE false)
	Q_PROPERTY(QString assignee    READ assignee    WRITE setAssignee    NOTIFY assigneeChanged    DESIGNABLE false)
	Q_PROPERTY(QString category    READ category    WRITE setCategory    NOTIFY categoryChanged    DESIGNABLE false)

public:
	explicit Task(QObject* p_parent = 0);
	explicit Task(const Task&);
	~Task() {}

	uint taskId() const;
	const QString& description() const;
	const QString& assignee() const;
	const QString& category() const;

	void setTaskId(const uint p_taskId);
	void setDescription(const QString& p_description);
	void setAssignee(const QString& p_assignee);
	void setCategory(const QString& p_category);

signals:
	void taskIdChanged(uint);
	void descriptionChanged(QString);
	void assigneeChanged(QString);
	void categoryChanged(QString);

private:
	uint	m_taskId;
	QString m_description;
	QString m_assignee;
	QString m_category;
};

#endif // TASK_H
