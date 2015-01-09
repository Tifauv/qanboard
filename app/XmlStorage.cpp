#include "XmlStorage.h"
#include <QFile>
#include <QtDebug>

#define QWF_NS "urn:qanboard:workflow:1.0"
#define QWF_TAG_WORKFLOW "Workflow"
#define QWF_TAG_TASKQUEUE "TaskQueue"
#define QWF_TAG_TASK "Task"
#define QWF_TAG_DESCRIPTION "Description"
#define QWF_TAG_CATEGORY "Category"
#define QWF_TAG_ASSIGNEE "Assignee"
#define QWF_ATTR_NEXTID "nextId"
#define QWF_ATTR_NAME "name"
#define QWF_ATTR_TASKID "id"


XmlStorage::XmlStorage(const QString& p_file, QObject* p_parent) :
	WorkflowStorage(p_parent),
	m_file(p_file) {
}


/**
 * @brief XmlStorage::load
 * @param p_workflow
 */
void XmlStorage::load(Workflow& p_workflow) const {
	QFile source(m_file);

	if (!source.exists()) {
		qWarning() << "/!\\ [XmlStorage] File " << m_file << " does not exist.";
		return;
	}

	if (!source.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "/!\\ [XmlStorage] File " << m_file << " could not be opened. Maybe you should check the file's permissions.";
		return;
	}

	qDebug() << "(i) [XmlStorage] Loading workflow from file " << m_file << ".";
	QXmlStreamReader xml;
	xml.setDevice(&source);

	if (xml.readNextStartElement()) {
		if (xml.name() == QWF_TAG_WORKFLOW && xml.namespaceUri() == QWF_NS)
			readWorkflow(xml, p_workflow);
		else
			xml.raiseError("The file does not conform to the schema '" + QString(QWF_NS) + "'.");
	}

	if (xml.hasError()) {
		qWarning() << "/!\\ [XmlStorage] Error reading file " << m_file << ": " << xml.errorString();
	}

	source.close();
	qDebug() << "(i) [XmlStorage] Workflow loaded from file " << m_file << ".";
}


/**
 * @brief XmlStorage::loadWorkflow
 * @param p_xml
 * @param p_workflow
 */
void XmlStorage::readWorkflow(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_WORKFLOW && p_xml.namespaceUri() == QWF_NS);

	// Get the nextId
	bool formatOk;
	QString nextIdStr = p_xml.attributes().value(QWF_ATTR_NEXTID).toString();
	uint nextId = nextIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qWarning() << "/!\\ [XmlStorage] Failed to parse nextId " << nextIdStr << " as integer.";
		return;
	}
	p_workflow.setTaskId(nextId);

	// Load the task queues
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_TASKQUEUE)
			readTaskQueue(p_xml, p_workflow);
		else
			p_xml.skipCurrentElement();
	}
}


void XmlStorage::readTaskQueue(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASKQUEUE && p_xml.namespaceUri() == QWF_NS);

	// Get the task queue name
	QString queueName = p_xml.attributes().value(QWF_ATTR_NAME).toString();
	p_workflow.createQueue(queueName);

	// Load the Tasks
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_TASK) {
			Task* task = readTask(p_xml);
			if (task != NULL)
				p_workflow.addTaskToQueue(task, queueName);
			else
				qWarning() << "/!\\ [XmlStorage] Task could not be created and was skipped.";
		}
		else
			p_xml.skipCurrentElement();
	}
}


/**
 * @brief XmlStorage::readTask
 * @param p_xml
 * @return
 */
Task* XmlStorage::readTask(QXmlStreamReader& p_xml) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASK && p_xml.namespaceUri() == QWF_NS);

	// Get the task id
	bool formatOk;
	QString taskIdStr = p_xml.attributes().value(QWF_ATTR_TASKID).toString();
	uint taskId = taskIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qWarning() << "/!\\ [XmlStorage] Failed to parse taskId " << taskIdStr << " as integer; skipping this task.";
		return NULL;
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


/**
 * @brief XmlStorage::store
 * @param p_workflow
 */
void XmlStorage::store(const Workflow& p_workflow) const {
	QFile source(m_file);

	if (!source.exists()) {
		qWarning() << "/!\\ [XmlStorage] File " << m_file << " does not exist.";
		return;
	}

	if (!source.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qWarning() << "/!\\ [XmlStorage] File " << m_file << " could not be opened. Maybe you should check the file's permissions.";
		return;
	}

	qDebug() << "(i) [XmlStorage] Writing workflow to file " << m_file << ".";
	QXmlStreamWriter xml;
	xml.setDevice(&source);
	xml.setAutoFormatting(true);

	// Start the document
	xml.writeStartDocument();
	writeWorkflow(xml, p_workflow);
	xml.writeEndDocument();
	qDebug() << "(i) [XmlStorage] Workflow written to file " << m_file << ".";
}


void XmlStorage::writeWorkflow(QXmlStreamWriter& p_xml, const Workflow& p_workflow) const {
	p_xml.writeStartElement(QWF_NS, QWF_TAG_WORKFLOW);
	p_xml.writeAttribute(QWF_ATTR_NEXTID, QString::number(p_workflow.taskId()));

	QListIterator<TaskQueue*> i = p_workflow.iter();
	while (i.hasNext())
		writeTaskQueue(p_xml, i.next());

	p_xml.writeEndElement();
}


void XmlStorage::writeTaskQueue(QXmlStreamWriter& p_xml, TaskQueue* p_queue) const {
	Q_ASSERT(p_queue);

	p_xml.writeStartElement(QWF_NS, QWF_TAG_TASKQUEUE);
	p_xml.writeAttribute(QWF_ATTR_NAME, p_queue->name());

	for (int i=0; i<p_queue->count(); ++i)
		writeTask(p_xml, p_queue->at(i));

	p_xml.writeEndElement();
}


void XmlStorage::writeTask(QXmlStreamWriter& p_xml, Task* p_task) const {
	Q_ASSERT(p_task);

	p_xml.writeStartElement(QWF_NS, QWF_TAG_TASK);
	p_xml.writeAttribute(QWF_ATTR_TASKID, QString::number(p_task->taskId()));
	p_xml.writeTextElement(QWF_NS, QWF_TAG_DESCRIPTION, p_task->description());
	p_xml.writeTextElement(QWF_NS, QWF_TAG_CATEGORY, p_task->category());
	p_xml.writeTextElement(QWF_NS, QWF_TAG_ASSIGNEE, p_task->assignee());
	p_xml.writeEndElement();
}
