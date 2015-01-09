#include "XmlStorage.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QtDebug>

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
		qDebug() << "/!\\ [XmlStorage] File " << m_file << " does not exist.";
		return;
	}

	if (!source.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "/!\\ [XmlStorage] File " << m_file << " could not be opened. Maybe you should check the file's permissions.";
		return;
	}

	QXmlStreamReader xml;
	xml.setDevice(&source);

	if (xml.readNextStartElement()) {
		if (xml.name() == "Workflow" && xml.namespaceUri() == "urn:qanboard:workflow:1.0")
			readWorkflow(xml, p_workflow);
		else
			xml.raiseError(QObject::tr("The file does not conform to the schema 'urn:qanboard:workflow:1.0'."));
	}

	if (xml.hasError()) {
		qDebug() << "/!\\ [XmlStorage] Error reading file " << m_file << ": " << xml.errorString();
	}

	source.close();
}


/**
 * @brief XmlStorage::loadWorkflow
 * @param p_xml
 * @param p_workflow
 */
void XmlStorage::readWorkflow(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == "Workflow" && p_xml.namespaceUri() == "urn:qanboard:workflow:1.0");

	// Get the nextId
	bool formatOk;
	QString nextIdStr = p_xml.attributes().value("nextId").toString();
	uint nextId = nextIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qDebug() << "/!\\ [XmlStorage] Failed to parse nextId " << nextIdStr << " as integer.";
		return;
	}
	p_workflow.setTaskId(nextId);

	// Load the task queues
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == "TaskQueue")
			readTaskQueue(p_xml, p_workflow);
		else
			p_xml.skipCurrentElement();
	}
}


void XmlStorage::readTaskQueue(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == "TaskQueue");

	// Get the task queue name
	QString queueName = p_xml.attributes().value("name").toString();
	p_workflow.createQueue(queueName);

	// Load the Tasks
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == "Task") {
			Task* task = readTask(p_xml);
			if (task != NULL)
				p_workflow.addTaskToQueue(task, queueName);
			else
				qDebug() << "/!\\ [XmlStorage] Task could not be created and was skipped.";
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
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == "Task");

	// Get the task id
	bool formatOk;
	QString taskIdStr = p_xml.attributes().value("id").toString();
	uint taskId = taskIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qDebug() << "/!\\ [XmlStorage] Failed to parse taskId " << taskIdStr << " as integer; skipping this task.";
		return NULL;
	}
	Task* task = new Task();
	task->setTaskId(taskId);

	// Load the task's content
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == "Description")
			task->setDescription(p_xml.readElementText());
		else if (p_xml.name() == "Category")
			task->setCategory(p_xml.readElementText());
		else if (p_xml.name() == "Assignee")
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
	Q_UNUSED(p_workflow)
	qDebug() << "(i) [XmlStorage] Storing is not (yet) supported.";
}
