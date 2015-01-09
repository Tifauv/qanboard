#ifndef Task_H
#define Task_H

#include <QObject>

class Task : public QObject {
	Q_OBJECT

	Q_PROPERTY(uint taskId         READ taskId      WRITE setTaskId      NOTIFY taskIdChanged      DESIGNABLE false)
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged DESIGNABLE false)
	Q_PROPERTY(QString category    READ category    WRITE setCategory    NOTIFY categoryChanged    DESIGNABLE false)
	Q_PROPERTY(QString assignee    READ assignee    WRITE setAssignee    NOTIFY assigneeChanged    DESIGNABLE false)

public:
	explicit Task(uint p_taskId = 0, const QString& p_description = QString::null, const QString& p_category = QString::null, const QString& p_assignee = QString::null, QObject* p_parent = 0);
	explicit Task(const Task&);
	~Task() {}

	uint taskId() const;
	const QString& description() const;
	const QString& category() const;
	const QString& assignee() const;

	void setTaskId(const uint p_taskId);
	void setDescription(const QString& p_description);
	void setCategory(const QString& p_category);
	void setAssignee(const QString& p_assignee);

signals:
	void taskIdChanged(uint);
	void descriptionChanged(QString);
	void categoryChanged(QString);
	void assigneeChanged(QString);

private:
	uint	m_taskId;
	QString m_description;
	QString m_category;
	QString m_assignee;
};

#endif // Task_H
