#include "XmlSerializer10.h"
#include <QtDebug>

#define QWF_NS_10 "urn:qanboard:workflow:1.0"
#define QWF_TAG_WORKFLOW    "Workflow"
#define QWF_TAG_TASKQUEUE    "TaskQueue"
#define QWF_TAG_TASK          "Task"
#define QWF_TAG_CLIENT         "Client"
#define QWF_TAG_ACTIVITY       "Activity"
#define QWF_TAG_DESCRIPTION    "Description"
#define QWF_TAG_DUEDATE        "DueDate"
#define QWF_TAG_TARGET         "Target"
#define QWF_TAG_HISTORY      "History"
#define QWF_TAG_TASKMOVE      "TaskMove"
#define QWF_ATTR_NEXTID       "nextId"
#define QWF_ATTR_DEFAULTQUEUE "defaultQueue"
#define QWF_ATTR_NAME         "name"
#define QWF_ATTR_ID           "id"
#define QWF_ATTR_TASKID       "taskId"
#define QWF_ATTR_ORIGIN       "fromQueue"
#define QWF_ATTR_DESTINATION  "toQueue"
#define QWF_ATTR_TIMESTAMP    "timestamp"

#define DATE_FORMAT "yyyy-MM-dd'T'hh:mm:sst"


// CONSTRUCTOR
/**
 * @brief XmlSerializer10::XmlSerializer10
 * @param p_parent
 */
XmlSerializer10::XmlSerializer10(QObject* p_parent) :
	WorkflowSerializer(p_parent) {
}


// MAIN METHODS
/**
 * @brief XmlSerializer10::read
 * @param p_source
 * @param p_workflow
 */
bool XmlSerializer10::read(QIODevice& p_source, Workflow& p_workflow) const {
	if (!p_source.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "/!\\ [XmlSerializer10::read] Source could not be opened.";
		return false;
	}

	qDebug() << "(i) [XmlSerializer10::read] Loading workflow...";
	QXmlStreamReader xml;
	xml.setDevice(&p_source);

	if (xml.readNextStartElement() && xml.name() == QWF_TAG_WORKFLOW && xml.namespaceUri() == QWF_NS_10)
		readWorkflow(xml, p_workflow);
	else
	xml.raiseError("Document does not start with a " + QString(QWF_TAG_WORKFLOW) + " element from namespace " + QString(QWF_NS_10));

	// Close the file
	p_source.close();

	if (xml.hasError()) {
		qWarning() << "/!\\ [XmlSerializer10::read] The file does not conform to the schema '" << QString(QWF_NS_10) << "'.";
		qWarning() << "/!\\ [XmlSerializer10::read] Error: " << xml.errorString();
		return false;
	}

	qDebug() << "(i) [XmlSerializer10::read] Workflow loaded successfully.";
	return true;
}


/**
 * @brief XmlSerializer10::write
 * @param p_source
 * @param p_workflow
 */
bool XmlSerializer10::write(QIODevice& p_source, const Workflow& p_workflow) const {
	if (!p_source.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qWarning() << "/!\\ [XmlSerializer10] Source could not be opened.";
		return false;
	}

	qDebug() << "(i) [XmlSerializer10] Saving current state...";
	QXmlStreamWriter xml;
	xml.setDevice(&p_source);
	xml.setAutoFormatting(true);

	// Start the document
	xml.writeStartDocument();
	writeWorkflow(xml, p_workflow);
	xml.writeEndDocument();
	p_source.close();
	qDebug() << "(i) [XmlSerializer10] Current state saved.";
	return true;
}


// READ METHODS BY ELEMENTS
/**
 * @brief XmlSerializer10::loadWorkflow
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer10::readWorkflow(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_WORKFLOW && p_xml.namespaceUri() == QWF_NS_10);

	// Get the nextId
	bool formatOk;
	QString nextIdStr = p_xml.attributes().value(QWF_ATTR_NEXTID).toString();
	uint nextId = nextIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qWarning() << "/!\\ [XmlSerializer10] Failed to parse nextId " << nextIdStr << " as integer.";
		return;
	}
	p_workflow.setTaskId(nextId);

	// Save the default queue name
	const QString& defaultQueueName = p_xml.attributes().value(QWF_ATTR_DEFAULTQUEUE).toString();

	// Load the task queues
	while (p_xml.readNextStartElement() && p_xml.name() == QWF_TAG_TASKQUEUE)
		readTaskQueue(p_xml, p_workflow);

	// Load the history
	if (p_xml.name() == QWF_TAG_HISTORY)
		readHistory(p_xml, p_workflow);

	// Let the workflow select the default queue
	p_workflow.selectDefaultQueue(defaultQueueName);
}


/**
 * @brief XmlSerializer10::readTaskQueue
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer10::readTaskQueue(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASKQUEUE && p_xml.namespaceUri() == QWF_NS_10);
	
	// Get the task queue name
	QString queueName = p_xml.attributes().value(QWF_ATTR_NAME).toString();
	p_workflow.createQueue(queueName);
	qDebug() << "(i) [XmlSerializer10]  Reading task queue " << queueName << "...";

	// Load the Tasks
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_TASK) {
			Task* task = readTask(p_xml);
			if (task != nullptr)
				p_workflow.loadTaskInQueue(task, queueName);
			else
				qWarning() << "/!\\ [XmlSerializer10] Task could not be created and was skipped.";
		}
		else
			p_xml.skipCurrentElement();
	}

	qDebug() << "(i) [XmlSerializer10]  Task queue " << queueName << " read.";
}


/**
 * @brief XmlSerializer10::readTask
 * @param p_xml
 * @return
 */
Task* XmlSerializer10::readTask(QXmlStreamReader& p_xml) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASK && p_xml.namespaceUri() == QWF_NS_10);

	// Get the task id
	bool formatOk;
	QString taskIdStr = p_xml.attributes().value(QWF_ATTR_ID).toString();
	uint taskId = taskIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qWarning() << "/!\\ [XmlSerializer10] Failed to parse taskId " << taskIdStr << " as integer; skipping this task.";
		return nullptr;
	}
	Task* task = new Task(taskId);

	// Load the task's content
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_CLIENT && p_xml.namespaceUri() == QWF_NS_10)
			task->setClient(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_ACTIVITY && p_xml.namespaceUri() == QWF_NS_10)
			task->setActivity(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_DESCRIPTION && p_xml.namespaceUri() == QWF_NS_10)
			task->setDescription(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_DUEDATE && p_xml.namespaceUri() == QWF_NS_10)
			task->setDueDate(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_TARGET && p_xml.namespaceUri() == QWF_NS_10)
			task->setTarget(p_xml.readElementText());
		else
			p_xml.skipCurrentElement();
	}

	return task;
}


/**
 * @brief XmlSerializer10::readHistory
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer10::readHistory(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_HISTORY && p_xml.namespaceUri() == QWF_NS_10);
	qDebug() << "(i) [XmlSerializer10]  Reading history...";
	
	// Load the TaskMoves
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_TASKMOVE) {
			TaskMove* taskMove = readTaskMove(p_xml, p_workflow);
			if (taskMove != nullptr)
				p_workflow.appendToHistory(taskMove);
			else
				qWarning() << "/!\\ [XmlSerializer10] TaskMove could not be created and was skipped.";
		}
		else {
			qDebug() << "(i) [XmlSerializer10]   Element " << p_xml.name() << " unexpected";
			p_xml.skipCurrentElement();
		}
	}

	qDebug() << "(i) [XmlSerializer10]  History read.";
}


/**
 * @brief XmlSerializer10::readTaskMove
 * @param p_xml
 * @param p_workflow
 * @return 
 */
TaskMove* XmlSerializer10::readTaskMove(QXmlStreamReader& p_xml, const Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASKMOVE && p_xml.namespaceUri() == QWF_NS_10);
	qDebug() << "(i) [XmlSerializer10]   Reading task move...";
	
	// Retrieve the Task
	bool formatOk;
	QString taskIdStr = p_xml.attributes().value(QWF_ATTR_TASKID).toString();
	uint taskId = taskIdStr.toUInt(&formatOk);
	if (!formatOk) {
		qWarning() << "/!\\ [XmlSerializer10] Failed to parse taskId " << taskIdStr << " as integer; skipping this task move.";
		return nullptr;
	}
	Task* task = p_workflow.findTask(taskId);
	if (!task) {
		qWarning() << "/!\\ [XmlSerializer10] No task with id " << taskId << " ; skipping this task move.";
		return nullptr;
	}
	
	// Retrieve the source queue
	QString fromQueueName = p_xml.attributes().value(QWF_ATTR_ORIGIN).toString();
	TaskQueue* fromQueue = p_workflow.findQueue(fromQueueName);
	if (!fromQueue) {
		qWarning() << "/!\\ [XmlSerializer10] No origin queue named " << fromQueueName << " ; skipping this task move.";
		return nullptr;
	}
	
	// Retrieve the destination queue
	QString toQueueName = p_xml.attributes().value(QWF_ATTR_DESTINATION).toString();
	TaskQueue* toQueue = p_workflow.findQueue(toQueueName);
	if (!toQueue) {
		qWarning() << "/!\\ [XmlSerializer10] No destination queue named " << toQueueName << " ; skipping this task move.";
		return nullptr;
	}
	
	// Retrieve the timestamp
	QString isoDateTime = p_xml.attributes().value(QWF_ATTR_TIMESTAMP).toString();
	QDateTime dateTime = QDateTime::fromString(isoDateTime, DATE_FORMAT);
	
	// Skip the end of the element
	p_xml.skipCurrentElement();

	qDebug() << "(i) [XmlSerializer10]   Move for task #" << task->taskId() << " from queue " << fromQueueName << " to queue " << toQueueName << " on " << isoDateTime << " read.";
	return new TaskMove(*task, *fromQueue, *toQueue, dateTime);
}


// WRITE METHODS BY ELEMENTS
/**
 * @brief XmlSerializer10::writeWorkflow
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer10::writeWorkflow(QXmlStreamWriter& p_xml, const Workflow& p_workflow) const {
	qDebug() << "(i) [XmlSerializer10] Writing workflow...";
	p_xml.writeStartElement(QWF_NS_10, QWF_TAG_WORKFLOW);
	
	p_xml.writeAttribute(QWF_ATTR_NEXTID, QString::number(p_workflow.taskId()));
	p_xml.writeAttribute(QWF_ATTR_DEFAULTQUEUE, p_workflow.defaultQueue());

	// The task queues
	QListIterator<TaskQueue*> i = p_workflow.iter();
	while (i.hasNext())
		writeTaskQueue(p_xml, *i.next());

	// The history
	writeHistory(p_xml, *p_workflow.history());
	
	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer10] Workflow written.";
}


/**
 * @brief XmlSerializer10::writeTaskQueue
 * @param p_xml
 * @param p_queue
 */
void XmlSerializer10::writeTaskQueue(QXmlStreamWriter& p_xml, const TaskQueue& p_queue) const {
	qDebug() << "(i) [XmlSerializer10]  Writing task queue " << p_queue.name() << " ...";
	p_xml.writeStartElement(QWF_NS_10, QWF_TAG_TASKQUEUE);
	
	//p_xml.writeAttribute(QWF_ATTR_ID, QString::number(p_queue.id()));
	p_xml.writeAttribute(QWF_ATTR_NAME, p_queue.name());

	for (int i=0; i<p_queue.count(); ++i)
		writeTask(p_xml, *p_queue.at(i));

	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer10]  Task queue " << p_queue.name() << " written.";
}


/**
 * @brief XmlSerializer10::writeTask
 * @param p_xml
 * @param p_task
 */
void XmlSerializer10::writeTask(QXmlStreamWriter& p_xml, const Task& p_task) const {
	qDebug() << "(i) [XmlSerializer10]   Writing task " << p_task.taskId() << " ...";
	p_xml.writeStartElement(QWF_NS_10, QWF_TAG_TASK);
	
	p_xml.writeAttribute(QWF_ATTR_ID, QString::number(p_task.taskId()));
	
	p_xml.writeTextElement(QWF_NS_10, QWF_TAG_CLIENT,      p_task.client());
	p_xml.writeTextElement(QWF_NS_10, QWF_TAG_ACTIVITY,    p_task.activity());
	p_xml.writeTextElement(QWF_NS_10, QWF_TAG_DESCRIPTION, p_task.description());
	p_xml.writeTextElement(QWF_NS_10, QWF_TAG_DUEDATE,     p_task.dueDate());
	p_xml.writeTextElement(QWF_NS_10, QWF_TAG_TARGET,      p_task.target());
	
	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer10]   Task #" << p_task.taskId() << " written.";
}


/**
 * @brief XmlSerializer10::writeHistory
 * @param p_xml
 * @param p_history
 */
void XmlSerializer10::writeHistory(QXmlStreamWriter& p_xml, const History& p_history) const {
	qDebug() << "(i) [XmlSerializer10]  Writing history...";
	p_xml.writeStartElement(QWF_NS_10, QWF_TAG_HISTORY);

	for (int i=0; i<p_history.rowCount(); ++i)
		writeTaskMove(p_xml, *p_history.at(i));

	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer10]  History written.";
}


/**
 * @brief XmlSerializer10::writeTaskMove
 * @param p_xml
 * @param p_taskMove
 */
void XmlSerializer10::writeTaskMove(QXmlStreamWriter& p_xml, const TaskMove& p_taskMove) const {
	qDebug() << "(i) [XmlSerializer10]   Writing move of task #" << p_taskMove.task().taskId() << " at " << p_taskMove.timestamp().toString(DATE_FORMAT) << "...";
	p_xml.writeStartElement(QWF_NS_10, QWF_TAG_TASKMOVE);
	
	p_xml.writeAttribute(QWF_ATTR_TASKID,           QString::number(p_taskMove.task().taskId()));
	p_xml.writeAttribute(QWF_ATTR_ORIGIN,      p_taskMove.origin().name());
	p_xml.writeAttribute(QWF_ATTR_DESTINATION, p_taskMove.destination().name());
	p_xml.writeAttribute(QWF_ATTR_TIMESTAMP,        p_taskMove.timestamp().toString(DATE_FORMAT));
	
	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer10]   Move of task #" << p_taskMove.task().taskId() << " at " << p_taskMove.timestamp().toString(DATE_FORMAT) << " written.";
}
