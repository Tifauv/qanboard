#ifndef XmlSerializer20_H
#define XmlSerializer20_H

#include "WorkflowSerializer.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>


/**
 * @brief A WorkflowSerializer using the XML schema version 2.0.
 * 
 * This format is organized as follow:
 * @code{.xml}
 * <Workflow xmlns=urn:qanboard:workflow:2.0" nextId="_nextTaskId_" defaultQueue="_queueName_" name="_workflowName_" lastSaved="_workflowLastSave_">
 *   <Tasks>
 *     <Task id="_taskId_">*
 *       <Client>_taskClient_</Client>
 *       <Activity>_taskActivity_</Activity>
 *       <Description>_taskDescription_</Description>
 *       <DueDate>_taskDueDate_</Description>
 *       <Target>_taskTarget_</Target>
 *     </Task>
 *   </Tasks>
 *   <Board>
 *     <TaskQueue name="_queueName_" color="_queueColor(#rrggbb)_">*
 *       <TaskRef taskId="_taskId_"/>*
 *     </TaskQueue>
 *   </Board>
 *   <History>
 *     <TaskMove taskId="_taskId_" fromQueue="_queueName_" toQueue="_queueName_" timestamp="_moveTimestamp(yyyy-MM-dd'T'hh:mm:sst)_"/>*
 *   </History>
 * </Workflow>
 * @endcode
 */
class XmlSerializer20 : public WorkflowSerializer {
	Q_OBJECT

public:
	explicit XmlSerializer20(QObject* parent = nullptr);

	bool read(QIODevice&, Workflow&)        const override;
	bool write(QIODevice&, const Workflow&) const override;

private:
	void readWorkflow(QXmlStreamReader&, Workflow&) const;
	void readTasks(QXmlStreamReader&, Workflow&) const;
	void readTask(QXmlStreamReader&, Workflow&) const;
	void readBoard(QXmlStreamReader&, Workflow&) const;
	void readQueue(QXmlStreamReader&, Workflow&) const;
	void readHistory(QXmlStreamReader&, Workflow&) const;
	void readTaskMove(QXmlStreamReader&, Workflow&) const;

	void writeWorkflow(QXmlStreamWriter&, const Workflow&) const;
	void writeTasks(QXmlStreamWriter&, const Workflow&) const;
	void writeTask(QXmlStreamWriter&, const Task&) const;
	void writeBoard(QXmlStreamWriter&, const Workflow&) const;
	void writeQueue(QXmlStreamWriter&, const TaskQueue&) const;
	void writeTaskRef(QXmlStreamWriter&, const Task&) const;
	void writeHistory(QXmlStreamWriter&, const History&) const;
	void writeTaskMove(QXmlStreamWriter&, const TaskMove&) const;
};

#endif // XmlSerializer20_H
