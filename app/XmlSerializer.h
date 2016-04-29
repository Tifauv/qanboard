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
	explicit XmlSerializer(QObject* parent = 0);

	void read(QIODevice&, Workflow&)        const override;
	void write(QIODevice&, const Workflow&) const override;

private:
	void readWorkflow(QXmlStreamReader&, Workflow&) const;
	void readTaskQueue(QXmlStreamReader&, Workflow&) const;
	Task* readTask(QXmlStreamReader&) const;

	void writeWorkflow(QXmlStreamWriter&, const Workflow&) const;
	void writeTaskQueue(QXmlStreamWriter&, TaskQueue*) const;
	void writeTask(QXmlStreamWriter&, Task*) const;
};

#endif // XmlSerializer_H
