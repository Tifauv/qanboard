#ifndef XmlSerializer10_H
#define XmlSerializer10_H

#include "WorkflowSerializer.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>


/**
 * @brief A WorkflowSerializer using the XML schema version 1.0.
 * 
 * This format is organized as follow:
 * @code{.xml}
 * <Workflow xmlns=urn:qanboard:workflow:1.0" nextId="_nextTaskId_" defaultQueue="_queueName_">
 *   <TaskQueue name="_queueName_">*
 *     <Task id="_taskId_">*
 *       <Client>_taskClient_</Client>
 *       <Activity>_taskActivity_</Activity>
 *       <Description>_taskDescription_</Description>
 *       <DueDate>_taskDueDate_</Description>
 *       <Target>_taskTarget_</Target>
 *     </Task>
 *   </TaskQueue>
 *   <History>
 *     <TaskMove taskId="_taskId_" fromQueue="_queueName_" toQueue="_queueName_" timestamp="_moveTimestamp(yyyy-MM-dd'T'hh:mm:sst)_"/>*
 *   </History>
 * </Workflow>
 * @endcode
 */
class XmlSerializer10 : public WorkflowSerializer {
	Q_OBJECT

public:
	explicit XmlSerializer10(QObject* parent = nullptr);

	bool read(QIODevice&, Workflow&)  const override;
	bool write(QIODevice&, Workflow&) const override;

private:
	void readWorkflow(QXmlStreamReader&, Workflow&) const;
	void readTaskQueue(QXmlStreamReader&, Workflow&) const;
	Task* readTask(QXmlStreamReader&) const;
	void readHistory(QXmlStreamReader&, Workflow&) const;
	TaskMove* readTaskMove(QXmlStreamReader&, const Workflow&) const;

	void writeWorkflow(QXmlStreamWriter&, const Workflow&) const;
	void writeTaskQueue(QXmlStreamWriter&, const TaskQueue&) const;
	void writeTask(QXmlStreamWriter&, const Task&) const;
	void writeHistory(QXmlStreamWriter&, const History&) const;
	void writeTaskMove(QXmlStreamWriter&, const TaskMove&) const;
};

#endif // XmlSerializer10_H
