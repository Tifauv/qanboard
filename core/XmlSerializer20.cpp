#include "XmlSerializer20.h"
#include <QtDebug>

#define QWF_NS_20 "urn:qanboard:workflow:2.0"

#define QWF_TAG_WORKFLOW    "Workflow"
#define QWF_TAG_TASKS        "Tasks"
#define QWF_TAG_TASK          "Task"
#define QWF_TAG_CLIENT         "Client"
#define QWF_TAG_ACTIVITY       "Activity"
#define QWF_TAG_DESCRIPTION    "Description"
#define QWF_TAG_DUEDATE        "DueDate"
#define QWF_TAG_TARGET         "Target"
#define QWF_TAG_BOARD        "Board"
#define QWF_TAG_QUEUE         "Queue"
#define QWF_TAG_TASKREF        "TaskRef"
#define QWF_TAG_HISTORY      "History"
#define QWF_TAG_TASKMOVE      "TaskMove"

#define QWF_ATTR_NEXTID       "nextId"
#define QWF_ATTR_DEFAULTQUEUE "defaultQueue"
#define QWF_ATTR_NAME         "name"
#define QWF_ATTR_LASTSAVED    "lastSaved"
#define QWF_ATTR_ID           "id"
#define QWF_ATTR_COLOR        "color"
#define QWF_ATTR_TASKID       "taskId"
#define QWF_ATTR_ORIGIN       "fromQueue"
#define QWF_ATTR_DESTINATION  "toQueue"
#define QWF_ATTR_TIMESTAMP    "timestamp"

#define DATE_FORMAT "yyyy-MM-dd'T'hh:mm:sst"


// CONSTRUCTOR
/**
 * @brief XmlSerializer20::XmlSerializer20
 * @param p_parent
 */
XmlSerializer20::XmlSerializer20(QObject* p_parent) :
	WorkflowSerializer(p_parent) {
}


// MAIN METHODS
/**
 * @brief XmlSerializer20::read
 * @param p_source
 * @param p_workflow
 */
bool XmlSerializer20::read(QIODevice& p_source, Workflow& p_workflow) const {
	if (!p_source.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qWarning() << "/!\\ [XmlSerializer20::read] Source could not be opened.";
		return false;
	}

	qDebug() << "(i) [XmlSerializer20::read] Loading workflow...";
	QXmlStreamReader xml;
	xml.setDevice(&p_source);

	if (xml.readNextStartElement() && xml.name() == QWF_TAG_WORKFLOW && xml.namespaceUri() == QWF_NS_20)
		readWorkflow(xml, p_workflow);
	else
		xml.raiseError("Document does not start with a " + QString(QWF_TAG_WORKFLOW) + " element from namespace " + QString(QWF_NS_20));

	// Close the file
	p_source.close();

	if (xml.hasError()) {
		qWarning() << "/!\\ [XmlSerializer20::read] The file does not conform to the schema '" << QWF_NS_20 << "'.";
		qWarning() << "/!\\ [XmlSerializer20::read] Error: " << xml.errorString();
		return false;
	}

	qDebug() << "(i) [XmlSerializer20::read] Workflow loaded successfully.";
	return true;
}


/**
 * @brief XmlSerializer20::write
 * @param p_source
 * @param p_workflow
 */
bool XmlSerializer20::write(QIODevice& p_source, Workflow& p_workflow) const {
	if (!p_source.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qWarning() << "/!\\ [XmlSerializer20::write] Source could not be opened.";
		return false;
	}

	qDebug() << "(i) [XmlSerializer20::write] Saving current state...";
	QXmlStreamWriter xml;
	xml.setDevice(&p_source);
	xml.setAutoFormatting(true);

	// Change the workflow's last saved date
	p_workflow.setLastSaved(QDateTime::currentDateTime());

	// Start the document
	xml.writeStartDocument();
	xml.writeDefaultNamespace(QWF_NS_20);
	writeWorkflow(xml, p_workflow);
	xml.writeEndDocument();
	p_source.close();
	qDebug() << "(i) [XmlSerializer20::write] Current state saved.";
	return true;
}


// READ METHODS BY ELEMENTS
/**
 * @brief XmlSerializer20::loadWorkflow
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer20::readWorkflow(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_WORKFLOW && p_xml.namespaceUri() == QWF_NS_20);

	qDebug() << "(i) [XmlSerializer20::readWorkflow] Reading element <" << QWF_TAG_WORKFLOW << ">...";

	// Read the nextId
	bool formatOk;
	uint nextId = p_xml.attributes().value(QWF_ATTR_NEXTID).toUInt(&formatOk);
	if (!formatOk) {
		p_xml.raiseError("Failed to parse attribute /Worflow@nextId as unsigned integer");
		return;
	}
	p_workflow.setTaskId(nextId);

	// Read the name
	p_workflow.setName(p_xml.attributes().value(QWF_ATTR_NAME).toString());

	// Read the timestamp of the last save
	QString lastSaveStr = p_xml.attributes().value(QWF_ATTR_LASTSAVED).toString();
	p_workflow.setLastSaved(QDateTime::fromString(lastSaveStr, DATE_FORMAT));

	// Read the default queue name
	const QString& defaultQueueName = p_xml.attributes().value(QWF_ATTR_DEFAULTQUEUE).toString();

	// Read the /Workflow/Tasks element
	if (p_xml.readNextStartElement()) {
		readTasks(p_xml, p_workflow);
		if (p_xml.hasError())
			return;
	}

	// Read the /Workflow/Board element
	if (p_xml.readNextStartElement()) {
		readBoard(p_xml, p_workflow);
		if (p_xml.hasError())
			return;
	}
	// Select the default queue now that they are loaded
	p_workflow.selectDefaultQueue(defaultQueueName);
	qDebug() << "(i) [XmlSerializer20::readWorkflow] Default queue " << defaultQueueName << " set.";

	// Read the /Workflow/History element
	qDebug() << "(i) [XmlSerializer20::readWorkflow] Current element: <" << p_xml.name() << "> (should be <History)>";
	if (p_xml.readNextStartElement()) {
		qDebug() << "(i) [XmlSerializer20::readWorkflow] Current element: <" << p_xml.name() << ">";
		readHistory(p_xml, p_workflow);
		if (p_xml.hasError())
			return;
	}

	qDebug() << "(i) [XmlSerializer20::readWorkflow] Element <" << QWF_TAG_WORKFLOW << "> read.";
}


/**
 * @brief XmlSerializer20::readTask
 * @param p_xml
 * @return
 */
void XmlSerializer20::readTasks(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASKS && p_xml.namespaceUri() == QWF_NS_20);

	// Load each task
	qDebug() << "(i) [XmlSerializer20::readTasks] Reading element <" << QWF_TAG_TASKS << ">...";
	while (p_xml.readNextStartElement() && p_xml.name() == QWF_TAG_TASK && p_xml.namespaceUri() == QWF_NS_20) {
		readTask(p_xml, p_workflow);
		if (p_xml.hasError())
			return;
	}
	qDebug() << "(i) [XmlSerializer20::readTasks] Element <" << QWF_TAG_TASKS << "> read.";
}


/**
 * @brief XmlSerializer20::readTask
 * @param p_xml
 * @return
 */
void XmlSerializer20::readTask(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASK && p_xml.namespaceUri() == QWF_NS_20);

	qDebug() << "(i) [XmlSerializer20::readTask] Reading element <" << QWF_TAG_TASK << ">...";
	
	// Get the task id
	bool formatOk;
	uint taskId = p_xml.attributes().value(QWF_ATTR_ID).toUInt(&formatOk);
	if (!formatOk) {
		p_xml.raiseError("Failed to parse attribute /Worflow/Tasks/Task@id as unsigned integer");
		return;
	}

	// Load the task's content
	qDebug() << "(i) [XmlSerializer20::readTask] Reading task #" << taskId << "...";
	Task* task = new Task(taskId);
	while (p_xml.readNextStartElement()) {
		if (p_xml.name() == QWF_TAG_CLIENT && p_xml.namespaceUri() == QWF_NS_20)
			task->setClient(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_ACTIVITY && p_xml.namespaceUri() == QWF_NS_20)
			task->setActivity(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_DESCRIPTION && p_xml.namespaceUri() == QWF_NS_20)
			task->setDescription(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_DUEDATE && p_xml.namespaceUri() == QWF_NS_20)
			task->setDueDate(p_xml.readElementText());
		else if (p_xml.name() == QWF_TAG_TARGET && p_xml.namespaceUri() == QWF_NS_20)
			task->setTarget(p_xml.readElementText());
		else
			p_xml.skipCurrentElement();
	}
	qDebug() << "(i) [XmlSerializer20::readTask] Task #" << taskId << " read.";

	// Register the task into the workflow
	p_workflow.registerTask(task);
	qDebug() << "(i) [XmlSerializer20::readTask] Task #" << taskId << " registered.";

	qDebug() << "(i) [XmlSerializer20::readTask] Element <" << QWF_TAG_TASK << "> read.";
}


/**
 * @brief XmlSerializer20::readBoard
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer20::readBoard(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_BOARD && p_xml.namespaceUri() == QWF_NS_20);

	// Load each task
	qDebug() << "(i) [XmlSerializer20::readBoard] Reading element <" << QWF_TAG_BOARD << ">...";
	while (p_xml.readNextStartElement() && p_xml.name() == QWF_TAG_QUEUE && p_xml.namespaceUri() == QWF_NS_20) {
		readQueue(p_xml, p_workflow);
		if (p_xml.hasError())
			return;
	}
	qDebug() << "(i) [XmlSerializer20::readBoard] Element <" << QWF_TAG_BOARD << "> read.";
}


/**
 * @brief XmlSerializer20::readQueue
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer20::readQueue(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_QUEUE && p_xml.namespaceUri() == QWF_NS_20);

	qDebug() << "(i) [XmlSerializer20::readQueue] Reading element <" << QWF_TAG_QUEUE << ">...";
	
	// Get the queue name
	QString queueName = p_xml.attributes().value(QWF_ATTR_NAME).toString();
	qDebug() << "(i) [XmlSerializer20::readQueue] Reading queue " << queueName << "...";

	// Read the color
	QString color = p_xml.attributes().value(QWF_ATTR_COLOR).toString();
	p_workflow.createQueue(queueName, color);
	//p_workflow.createQueue(queueName);

	// Load the TaskRefs
	while (p_xml.readNextStartElement() && p_xml.name() == QWF_TAG_TASKREF && p_xml.namespaceUri() == QWF_NS_20) {
		qDebug() << "(i) [XmlSerializer20::readQueue] Reading element <" << QWF_TAG_TASKREF << ">...";
		bool formatOk;
		uint taskId = p_xml.attributes().value(QWF_ATTR_TASKID).toUInt(&formatOk);
		if (!formatOk) {
			p_xml.raiseError("Failed to parse attribute /Worflow/TaskQueue/TaskRef@taskId as unsigned integer");
			return;
		}
		
		qDebug() << "(i) [XmlSerializer20::readQueue] Adding task #" << taskId << " to queue " << queueName;
		if (!p_workflow.appendTaskToQueue(taskId, queueName))
			qWarning() << "/!\\ [XmlSerializer20::readQueue] Task #" << taskId << " does not exist, TaskRef skipped.";
		
		// No more info to read from a TaskRef
		p_xml.skipCurrentElement();
		qDebug() << "(i) [XmlSerializer20::readQueue] Current element is <" << p_xml.name() << ">";
		qDebug() << "(i) [XmlSerializer20::readQueue] Element <" << QWF_TAG_TASKREF << "> read.";
	}

	qDebug() << "(i) [XmlSerializer20::readQueue] Current element is <" << p_xml.name() << ">";
	qDebug() << "(i) [XmlSerializer20::readQueue] Element <" << QWF_TAG_QUEUE << "> read.";
}


/**
 * @brief XmlSerializer20::readHistory
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer20::readHistory(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_HISTORY && p_xml.namespaceUri() == QWF_NS_20);

	// Load the TaskMoves
	qDebug() << "(i) [XmlSerializer20::readHistory] Reading element <" << QWF_TAG_HISTORY << ">...";
	while (p_xml.readNextStartElement()) {
		readTaskMove(p_xml, p_workflow);
		if (p_xml.hasError())
			return;
	}
	qDebug() << "(i) [XmlSerializer20::readHistory] Element <" << QWF_TAG_HISTORY << "> read.";
}


/**
 * @brief XmlSerializer20::readTaskMove
 * @param p_xml
 * @param p_workflow
 * @return 
 */
void XmlSerializer20::readTaskMove(QXmlStreamReader& p_xml, Workflow& p_workflow) const {
	Q_ASSERT(p_xml.isStartElement() && p_xml.name() == QWF_TAG_TASKMOVE && p_xml.namespaceUri() == QWF_NS_20);

	qDebug() << "(i) [XmlSerializer20::readTaskMove] Reading element <" << QWF_TAG_TASKMOVE << ">...";
	
	// Retrieve the Task
	bool formatOk;
	uint taskId = p_xml.attributes().value(QWF_ATTR_TASKID).toUInt(&formatOk);
	if (!formatOk) {
		p_xml.raiseError("Failed to parse attribute /Worflow/History/TaskMove@taskId as unsigned integer");
		return;
	}
	Task* task = p_workflow.findTask(taskId);
	if (!task) {
		qWarning() << "/!\\ [XmlSerializer20::readTaskMove] Task #" << taskId << " does not exist, skipping this task move.";
		return;
	}
	
	// Retrieve the source queue
	QString fromQueueName = p_xml.attributes().value(QWF_ATTR_ORIGIN).toString();
	TaskQueue* fromQueue = p_workflow.findQueue(fromQueueName);
	if (!fromQueue) {
		qWarning() << "/!\\ [XmlSerializer20::readTaskMove] No queue named " << fromQueueName << ", skipping this task move.";
		return;
	}
	
	// Retrieve the destination queue
	QString toQueueName = p_xml.attributes().value(QWF_ATTR_DESTINATION).toString();
	TaskQueue* toQueue = p_workflow.findQueue(toQueueName);
	if (!toQueue) {
		qWarning() << "/!\\ [XmlSerializer20::readTaskMove] No queue named " << toQueueName << ", skipping this task move.";
		return;
	}
	
	// Retrieve the timestamp
	QString isoDateTime = p_xml.attributes().value(QWF_ATTR_TIMESTAMP).toString();
	QDateTime dateTime = QDateTime::fromString(isoDateTime, DATE_FORMAT);
	qDebug() << "(i) [XmlSerializer20::readTaskMove] Move for task #" << task->taskId() << " from queue " << fromQueueName << " to queue " << toQueueName << " on " << isoDateTime << " read.";

	// Skip the end of the element
	p_xml.skipCurrentElement();

	p_workflow.appendToHistory(new TaskMove(*task, *fromQueue, *toQueue, dateTime));
	qDebug() << "(i) [XmlSerializer20::readTaskMove] Element <" << QWF_TAG_TASKMOVE << "> read.";
}


// WRITE METHODS BY ELEMENTS
/**
 * @brief XmlSerializer20::writeWorkflow
 * @param p_xml
 * @param p_workflow
 */
void XmlSerializer20::writeWorkflow(QXmlStreamWriter& p_xml, const Workflow& p_workflow) const {
	qDebug() << "(i) [XmlSerializer20::writeWorkflow] Writing element <" << QWF_TAG_WORKFLOW << ">...";
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_WORKFLOW);
	
	p_xml.writeAttribute(QWF_ATTR_NAME,         p_workflow.name());
	p_xml.writeAttribute(QWF_ATTR_NEXTID,       QString::number(p_workflow.taskId()));
	p_xml.writeAttribute(QWF_ATTR_DEFAULTQUEUE, p_workflow.defaultQueue());
	p_xml.writeAttribute(QWF_ATTR_LASTSAVED,    p_workflow.lastSaved().toString(DATE_FORMAT));

	// The tasks
	writeTasks(p_xml, p_workflow);
	
	// The queues
	writeBoard(p_xml, p_workflow);

	// The history
	writeHistory(p_xml, *p_workflow.history());
	
	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer20::writeWorkflow] Element <" << QWF_TAG_WORKFLOW << "> written.";
}


/**
 * @brief XmlSerializer20::writeTasks
 * @param p_xml
 * @param p_queue
 */
void XmlSerializer20::writeTasks(QXmlStreamWriter& p_xml, const Workflow& p_workflow) const {
	qDebug() << "(i) [XmlSerializer20::writeTasks] Writing element <" << QWF_TAG_TASKS << ">...";
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_TASKS);

	// Write each task
	auto tasks = p_workflow.tasksIter();
	while (tasks.hasNext())
		writeTask(p_xml, *tasks.next());

	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer20::writeTasks] Element <" << QWF_TAG_TASKS << "> written.";
}


/**
 * @brief XmlSerializer20::writeTask
 * @param p_xml
 * @param p_task
 */
void XmlSerializer20::writeTask(QXmlStreamWriter& p_xml, const Task& p_task) const {
	qDebug() << "(i) [XmlSerializer20::writeTask] Writing element <" << QWF_TAG_TASK << "> for task #" << p_task.taskId() << "...";
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_TASK);
	
	p_xml.writeAttribute(QWF_ATTR_ID, QString::number(p_task.taskId()));
	
	// /Workflow/Tasks/Task/Client
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_CLIENT);
	p_xml.writeCDATA(p_task.client());
	p_xml.writeEndElement();

	// /Workflow/Tasks/Task/Activity
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_ACTIVITY);
	p_xml.writeCDATA(p_task.activity());
	p_xml.writeEndElement();

	// /Workflow/Tasks/Task/Description
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_DESCRIPTION);
	p_xml.writeCDATA(p_task.description());
	p_xml.writeEndElement();

	// /Workflow/Tasks/Task/DueDate
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_DUEDATE);
	p_xml.writeCDATA(p_task.dueDate());
	p_xml.writeEndElement();
	
	// /Workflow/Tasks/Task/Target
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_TARGET);
	p_xml.writeCDATA(p_task.target());
	p_xml.writeEndElement();
	
	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer20::writeTask] Element <" << QWF_TAG_TASK << "> written.";
}


/**
 * @brief XmlSerializer20::writeBoard
 */
void XmlSerializer20::writeBoard(QXmlStreamWriter& p_xml, const Workflow& p_workflow) const {
	qDebug() << "(i) [XmlSerializer20::writeBoard] Writing element <" << QWF_TAG_BOARD << ">...";
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_BOARD);

	// Write each queue
	auto queues = p_workflow.iter();
	while (queues.hasNext())
		writeQueue(p_xml, *queues.next());

	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer20::writeBoard] Element <" << QWF_TAG_BOARD << "> written.";
}


/**
 * @brief XmlSerializer20::writeQueue
 * @param p_xml
 * @param p_queue
 */
void XmlSerializer20::writeQueue(QXmlStreamWriter& p_xml, const TaskQueue& p_queue) const {
	qDebug() << "(i) [XmlSerializer20::writeQueue] Writing element <" << QWF_TAG_QUEUE << "> for queue " << p_queue.name() << "...";
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_QUEUE);
	
	p_xml.writeAttribute(QWF_ATTR_NAME,  p_queue.name());
	p_xml.writeAttribute(QWF_ATTR_COLOR, p_queue.color());

	// Write the tasks references
	for (int i=0; i<p_queue.count(); ++i)
		writeTaskRef(p_xml, *p_queue.at(i));

	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer20::writeQueue] Element <" << QWF_TAG_QUEUE << "> written.";
}


/**
 * @brief XmlSerializer20::writeTaskRef
 * @param p_xml
 * @param p_task
 */
void XmlSerializer20::writeTaskRef(QXmlStreamWriter& p_xml, const Task& p_task) const {
	qDebug() << "(i) [XmlSerializer20::writeTaskRef] Writing element <" << QWF_TAG_TASKREF << "> for reference to task #" << p_task.taskId() << "...";
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_TASKREF);
	
	p_xml.writeAttribute(QWF_ATTR_TASKID, QString::number(p_task.taskId()));

	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer20::writeTaskRef] Element <" << QWF_TAG_TASKREF << "> written.";
}


/**
 * @brief XmlSerializer20::writeHistory
 * @param p_xml
 * @param p_history
 */
void XmlSerializer20::writeHistory(QXmlStreamWriter& p_xml, const History& p_history) const {
	qDebug() << "(i) [XmlSerializer20::writeHistory] Writing element <" << QWF_TAG_HISTORY << ">...";
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_HISTORY);

	for (int i=0; i<p_history.rowCount(); ++i)
		writeTaskMove(p_xml, *p_history.at(i));

	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer20::writeHistory] Element <" << QWF_TAG_HISTORY << "> written.";
}


/**
 * @brief XmlSerializer20::writeTaskMove
 * @param p_xml
 * @param p_taskMove
 */
void XmlSerializer20::writeTaskMove(QXmlStreamWriter& p_xml, const TaskMove& p_taskMove) const {
	qDebug() << "(i) [XmlSerializer20::writeTaskMove] Writing element <" << QWF_TAG_TASKMOVE << "> for move of task #" << p_taskMove.task().taskId() << " at " << p_taskMove.timestamp().toString(DATE_FORMAT) << "...";
	p_xml.writeStartElement(QWF_NS_20, QWF_TAG_TASKMOVE);
	
	p_xml.writeAttribute(QWF_ATTR_TASKID,      QString::number(p_taskMove.task().taskId()));
	p_xml.writeAttribute(QWF_ATTR_ORIGIN,      p_taskMove.origin().name());
	p_xml.writeAttribute(QWF_ATTR_DESTINATION, p_taskMove.destination().name());
	p_xml.writeAttribute(QWF_ATTR_TIMESTAMP,   p_taskMove.timestamp().toString(DATE_FORMAT));
	
	p_xml.writeEndElement();
	qDebug() << "(i) [XmlSerializer20::writeTaskMove] Element <" << QWF_TAG_TASKMOVE << "> written.";
}
