#include "XmlSerializer.h"
#include <QtDebug>

#define QWF_NS "urn:qanboard:workflow:1.0"
#define QWF_TAG_WORKFLOW "Workflow"
#define QWF_TAG_TASKQUEUE "TaskQueue"
#define QWF_TAG_TASK "Task"
#define QWF_TAG_DESCRIPTION "Description"
#define QWF_TAG_CATEGORY "Category"
#define QWF_TAG_ASSIGNEE "Assignee"
#define QWF_ATTR_NEXTID "nextId"
#define QWF_ATTR_DEFAULTQUEUE "defaultQueue"
#define QWF_ATTR_NAME "name"
#define QWF_ATTR_TASKID "id"


// CONSTRUCTOR
/**
 * @brief XmlSerializer::XmlSerializer
 * @param p_parent
 */
XmlSerializer::XmlSerializer(QObject* p_parent) :
	WorkflowSerializer(p_parent) {
}


// MAIN METHODS
/**
 * @brief XmlSerializer::read
 * @param p_source
 * @param p_workflow
 */
void XmlSerializer::read(QIODevice& p_source, Workflow& p_workflow) const {
	if (!p_source.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "/!\\ [XmlSerializer] Source could not be opened.";
		return;
	}

	qDebug() << "(i) [XmlSerializer] Loading workflow...";
	QXmlStreamReader xml;
	xml.setDevice(&p_source);

	if (xml.readNextStartElement()) {
		if (xml.name() == QWF_TAG_WORKFLOW && xml.namespaceUri() == QWF_NS)
			readWorkflow(xml, p_workflow);
		else
			xml.raiseError("The file does not conform to the schema '" + QString(QWF_NS) + "'.");
	}

	if (xml.hasError()) {
		qWarning() << "/!\\ [XmlSerializer] Error reading source: " << xml.errorString();
	}

	p_source.close();
	qDebug() << "(i) [XmlSerializer] Workflow loaded.";
}


/**
 * @brief XmlSerializer::write
 * @param p_source
 * @param p_workflow
 */
void XmlSerializer::write(QIODevice& p_source, const Workflow& p_workflow) const {
	if (!p_source.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qWarning() << "/!\\ [XmlSerializer] Source could not be opened.";
		return;
	}

	qDebug() << "(i) [XmlSerializer] Writing workflow...";
	QXmlStreamWriter xml;
	xml.setDevice(&p_source);
	xml.setAutoFormatting(true);

	// Start the document
	xml.writeStartDocument();
	writeWorkflow(xml, p_workflow);
	xml.writeEndDocument();
	p_source.close();
	qDebug() << "(i) [XmlSerializer] Workflow written.";
}


// READ METHODS BY ELEMENTS
/**
 * @brief XmlSerializer::loadWorkflow
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer::readWorkflow(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_WORKFLOW && p_xml.namespaceUri() == QWF_NS);

	// Get the nextId
	bool formatOk;
	QString nextIdStr = p_xml.attributes().value(QWF_ATTR_NEXTID).toString();
	uint nextId = nextIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qWarning() << "/!\\ [XmlSerializer] Failed to parse nextId " << nextIdStr << " as integer.";
		return;
	}
	p_workflow.setTaskId(nextId);

	// Get the default queue
	p_workflow.setDefaultQueue(p_xml.attributes().value(QWF_ATTR_DEFAULTQUEUE).toString());

	// Load the task queues
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_TASKQUEUE)
			readTaskQueue(p_xml, p_workflow);
		else
			p_xml.skipCurrentElement();
	}
}


/**
 * @brief XmlSerializer::readTaskQueue
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer::readTaskQueue(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASKQUEUE && p_xml.namespaceUri() == QWF_NS);

	// Get the task queue name
	QString queueName = p_xml.attributes().value(QWF_ATTR_NAME).toString();
	p_workflow.createQueue(queueName);

	// Load the Tasks
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_TASK) {
			Task* task = readTask(p_xml);
            if (task != nullptr)
				p_workflow.addTaskToQueue(task, queueName);
			else
				qWarning() << "/!\\ [XmlSerializer] Task could not be created and was skipped.";
		}
		else
			p_xml.skipCurrentElement();
	}
}


/**
 * @brief XmlSerializer::readTask
 * @param p_xml
 * @return
 */
Task* XmlSerializer::readTask(QXmlStreamReader& p_xml) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASK && p_xml.namespaceUri() == QWF_NS);

	// Get the task id
	bool formatOk;
	QString taskIdStr = p_xml.attributes().value(QWF_ATTR_TASKID).toString();
	uint taskId = taskIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qWarning() << "/!\\ [XmlSerializer] Failed to parse taskId " << taskIdStr << " as integer; skipping this task.";
        return nullptr;
	}
	Task* task = new Task();
	task->setTaskId(taskId);

	// Load the task's content
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_DESCRIPTION && p_xml.namespaceUri() == QWF_NS)
			task->setDescription(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_CATEGORY && p_xml.namespaceUri() == QWF_NS)
			task->setCategory(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_ASSIGNEE && p_xml.namespaceUri() == QWF_NS)
			task->setAssignee(p_xml.readElementText());
		else
			p_xml.skipCurrentElement();
	}

	return task;
}


// WRITE METHODS BY ELEMENTS
/**
 * @brief XmlSerializer::writeWorkflow
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer::writeWorkflow(QXmlStreamWriter& p_xml, const Workflow& p_workflow) const {
	p_xml.writeStartElement(QWF_NS, QWF_TAG_WORKFLOW);
	p_xml.writeAttribute(QWF_ATTR_NEXTID, QString::number(p_workflow.taskId()));
	p_xml.writeAttribute(QWF_ATTR_DEFAULTQUEUE, p_workflow.defaultQueue());

	QListIterator<TaskQueue*> i = p_workflow.iter();
	while (i.hasNext())
		writeTaskQueue(p_xml, i.next());

	p_xml.writeEndElement();
}


/**
 * @brief XmlSerializer::writeTaskQueue
 * @param p_xml
 * @param p_queue
 */
void XmlSerializer::writeTaskQueue(QXmlStreamWriter& p_xml, TaskQueue* p_queue) const {
	Q_ASSERT(p_queue);

	p_xml.writeStartElement(QWF_NS, QWF_TAG_TASKQUEUE);
	p_xml.writeAttribute(QWF_ATTR_NAME, p_queue->name());

	for (int i=0; i<p_queue->count(); ++i)
		writeTask(p_xml, p_queue->at(i));

	p_xml.writeEndElement();
}


/**
 * @brief XmlSerializer::writeTask
 * @param p_xml
 * @param p_task
 */
void XmlSerializer::writeTask(QXmlStreamWriter& p_xml, Task* p_task) const {
	Q_ASSERT(p_task);

	p_xml.writeStartElement(QWF_NS, QWF_TAG_TASK);
	p_xml.writeAttribute(QWF_ATTR_TASKID, QString::number(p_task->taskId()));
	p_xml.writeTextElement(QWF_NS, QWF_TAG_DESCRIPTION, p_task->description());
	p_xml.writeTextElement(QWF_NS, QWF_TAG_CATEGORY, p_task->category());
	p_xml.writeTextElement(QWF_NS, QWF_TAG_ASSIGNEE, p_task->assignee());
	p_xml.writeEndElement();
}
