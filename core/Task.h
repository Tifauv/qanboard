#ifndef Task_H
#define Task_H

#include <QObject>

/**
 * @brief The Task is the most basic object of a workflow.
 * A task represents a unit of work.
 *
 * @author Olivier Serve <tifauv@gmail.com>
 * @version 1.0
 */
class Task : public QObject {
	Q_OBJECT

	Q_PROPERTY(uint taskId         READ taskId      WRITE setTaskId      NOTIFY taskIdChanged      DESIGNABLE false)
	Q_PROPERTY(QString title       READ title       WRITE setTitle       NOTIFY titleChanged       DESIGNABLE false)
	Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged DESIGNABLE false)
	Q_PROPERTY(QString client      READ client      WRITE setClient      NOTIFY clientChanged      DESIGNABLE false)
	Q_PROPERTY(QString activity    READ activity    WRITE setActivity    NOTIFY activityChanged    DESIGNABLE false)
	Q_PROPERTY(QString target      READ target      WRITE setTarget      NOTIFY targetChanged      DESIGNABLE false)

public:
	enum Type {
		Incident,
		Change,
		Documentation
	};

	explicit Task(uint p_taskId = 0, const QString& p_title = QString::null, const QString& p_description = QString::null, const QString& p_client = QString::null, const QString& p_activity = QString::null, const QString& p_target = QString::null, QObject* p_parent = nullptr);
	explicit Task(const Task&);
	virtual ~Task();

	uint taskId() const;
	const QString& title() const;
	const QString& description() const;
	const QString& client() const;
	const QString& activity() const;
	const QString& target() const;

	void setTaskId(const uint);
	void setTitle(const QString&);
	void setDescription(const QString&);
	void setClient(const QString&);
	void setActivity(const QString&);
	void setTarget(const QString&);

signals:
	void taskIdChanged(uint);
	void titleChanged(QString);
	void descriptionChanged(QString);
	void clientChanged(QString);
	void activityChanged(QString);
	void targetChanged(QString);

private:
	uint	m_taskId;
	QString m_title;
	QString m_description;
	QString m_client;
	QString m_activity;
	QString m_target;
};

#endif // Task_H
