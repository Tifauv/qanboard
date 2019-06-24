#ifndef XmlSerializer_H
#define XmlSerializer_H

#include "WorkflowSerializer.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>


/**
 * @brief The XmlSerializer class
 */
class XmlSerializer : public WorkflowSerializer {
	Q_OBJECT

public:
	explicit XmlSerializer(QObject* parent = nullptr);

	void read(QIODevice&, Workflow&)        const override;
	void write(QIODevice&, const Workflow&) const override;

private:
	void readWorkflow(QXmlStreamReader&, Workflow&) const;
	void readTaskQueue(QXmlStreamReader&, Workflow&) const;
	Task* readTask(QXmlStreamReader&) const;
	void readHistory(QXmlStreamReader&, Workflow&) const;
	TaskMove* readTaskMove(QXmlStreamReader&, const Workflow&) const;

	void writeWorkflow(QXmlStreamWriter&, const Workflow&) const;
	void writeTaskQueue(QXmlStreamWriter&, const TaskQueue&) const;
	void writeTask(QXmlStreamWriter&, const Task&) const;
	void writeHistory(QXmlStreamWriter&, const QList<TaskMove*>&) const;
	void writeTaskMove(QXmlStreamWriter&, const TaskMove&) const;
};

#endif // XmlSerializer_H
