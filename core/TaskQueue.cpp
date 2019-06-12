#include "TaskQueue.h"
#include <QList>
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief TaskQueue::TaskQueue
 * @param p_parent
 */
TaskQueue::TaskQueue(QObject* p_parent) :
	QAbstractListModel(p_parent),
	m_name(""),
	m_tasks() {
	qDebug() << "(i) [TaskQueue] Created.";
}


/**
 * @brief TaskQueue::TaskQueue
 * @param p_toCopy
 */
TaskQueue::TaskQueue(const TaskQueue& p_toCopy) :
	QAbstractListModel(),
	m_name(p_toCopy.name()),
	m_tasks(p_toCopy.m_tasks) {
	qDebug() << "(i) [TaskQueue] Copied queue " << m_name << " with " << m_tasks.count() << " tasks.";
}


// GETTERS
/**
 * @brief TaskQueue::name
 * @return
 */
const QString& TaskQueue::name() const {
	return m_name;
}


/**
 * @brief TaskQueue::count
 * @return
 */
int TaskQueue::count() const {
	return m_tasks.count();
}


// SETTERS
/**
 * @brief TaskQueue::setName
 * @param p_name
 */
void TaskQueue::setName(const QString &p_name) {
	m_name = p_name;
	qDebug() << "(i) [TaskQueue] Changed name to " << p_name;
	emit nameChanged(p_name);
}


// MODEL/VIEW API
/**
 * @brief TaskQueue::rowCount
 * @param p_parent
 * @return
 */
int TaskQueue::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	//qDebug() << "(i) TaskQueue::rowCount()";
	return m_tasks.count();
}


/**
 * @brief TaskQueue::roleNames
 * @return
 */
QHash<int, QByteArray> TaskQueue::roleNames() const {
	QHash<int, QByteArray> names;
	names[TaskIdRole]      = "taskId";
	names[TitleRole]       = "title";
	names[DescriptionRole] = "description";
	names[ClientRole]      = "client";
	names[ActivityRole]    = "activity";
	names[TargetRole]      = "target";
	return names;
}


/**
 * @brief TaskQueue::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant TaskQueue::data(const QModelIndex& p_index, int p_role) const {
	qDebug() << "(i) [TaskQueue] Query data for role " << p_role << " of task at row " << p_index.row();
	if (p_index.row() < 0 || p_index.row() >= rowCount())
		return QVariant();

	Task* task = m_tasks.at(p_index.row());
	switch (p_role) {
	case TaskIdRole:
		return task->taskId();
	case TitleRole:
		return task->title();
	case DescriptionRole:
		return task->description();
	case ClientRole:
		return task->client();
	case ActivityRole:
		return task->activity();
	case TargetRole:
		return task->target();
	default:
		return QVariant();
	}
}


bool TaskQueue::setData(const QModelIndex& p_index, const QVariant& p_value, int p_role) {
	qDebug() << "(i) [TaskQueue] Setting data for role " << p_role << " of task at row " << p_index.row();
	if (p_index.row() < 0 || p_index.row() >= rowCount())
		return false;

	Task* task = m_tasks.at(p_index.row());
	switch (p_role) {
/*  TaskId should not be editable.
 *	case TaskIdRole:
 *		task->setTaskId(p_value.toUInt());
 *		break;
 */
	case TitleRole:
		task->setTitle(p_value.toString());
		break;
	case DescriptionRole:
		task->setDescription(p_value.toString());
		break;
	case ClientRole:
		task->setClient(p_value.toString());
		break;
	case ActivityRole:
		task->setActivity(p_value.toString());
		break;
	case TargetRole:
		task->setTarget(p_value.toString());
		break;
	default:
		return false;
	}
	emit dataChanged(p_index, p_index);
	return true;
}


/**
 * @brief TaskQueue::insertRow
 * @param p_row
 * @param p_item
 */
void TaskQueue::insertRow(int p_row, Task* p_task) {
	beginInsertRows(QModelIndex(), p_row, p_row);
	connect(p_task, SIGNAL(taskIdChanged(uint)),         SLOT(handleDataChanged()));
	connect(p_task, SIGNAL(titleChanged(QString)),       SLOT(handleDataChanged()));
	connect(p_task, SIGNAL(descriptionChanged(QString)), SLOT(handleDataChanged()));
	connect(p_task, SIGNAL(clientChanged(QString)),      SLOT(handleDataChanged()));
	connect(p_task, SIGNAL(activityChanged(QString)),    SLOT(handleDataChanged()));
	connect(p_task, SIGNAL(targetChanged(QString)),      SLOT(handleDataChanged()));
	m_tasks.insert(p_row, p_task);
	p_task->setParent(this);
	endInsertRows();
	emit countChanged(count());
	qDebug() << "(i) [TaskQueue] Task " << p_task->taskId() << " inserted into queue " << name() << " at position " << p_row;
}


/**
 * @brief TaskQueue::removeRow
 * @param p_row
 * @param p_parent
 * @return
 */
bool TaskQueue::removeRow(int p_row, const QModelIndex& p_parent) {
	Q_UNUSED(p_parent);
	if (p_row < 0 || p_row >= rowCount())
		return false;

	beginRemoveRows(QModelIndex(), p_row, p_row);
	Task* task = m_tasks.takeAt(p_row);
	task->disconnect(this, SLOT(handleDataChanged()));
	endRemoveRows();
	emit countChanged(count());
	qDebug() << "(i) [TaskQueue] Task " << task->taskId() << " removed from queue " << name();
	return true;
}


// RAW API
/**
 * @brief TaskQueue::at
 * @param p_index
 * @return
 */
Task* TaskQueue::at(int p_index) const {
	if (p_index < 0 || p_index >= rowCount())
        return nullptr;
	return m_tasks.at(p_index);
}


/**
 * @brief TaskQueue::find
 * @param p_taskId
 * @return
 */
Task* TaskQueue::find(uint p_taskId) const {
	foreach(Task* task, m_tasks) {
		if (task->taskId() == p_taskId)
			return task;
	}
    return nullptr;
}


/**
 * @brief TaskQueue::add
 * @param p_task
 */
void TaskQueue::appendRow(Task* p_task) {
	Q_ASSERT(p_task);
	insertRow(rowCount(), p_task);
}


/**
 * @brief TaskQueue::moveRow
 * @param p_row
 * @param p_destRow
 */
void TaskQueue::moveRow(int p_row, int p_destRow) {
	if (p_row < 0 || p_row >= rowCount()) {
		qDebug() << "(i) [TaskQueue] Moved skipped because there is no index " << p_row;
		return;
	}

	int destRow = p_destRow;
	int realDestRow = destRow;
	if (destRow < -1) {
		qDebug() << "(i) [TaskQueue] Moved skipped because target index " << destRow << " is invalid";
		return;
	}
	if (destRow == -1 || destRow >= rowCount()) {
		destRow = rowCount();
		realDestRow = destRow - 1;
	}
	else if (destRow > p_row)
		destRow += 1;

	QModelIndex parent;
	if (beginMoveRows(parent, p_row, p_row, parent, destRow)) {
		m_tasks.move(p_row, realDestRow);
		qDebug() << "(i) [TaskQueue] Moved task from row " << p_row << " to " << destRow << " (really " << realDestRow << ")";
		endMoveRows();
	}
	else {
		qDebug() << "(i) [TaskQueue] Moving task from row " << p_row << " to " << destRow << " was rejected.";
	}

}


void TaskQueue::log() {
	qDebug() << "{d} [TaskQueue] Queue " << m_name << " ----------";
	for (int i=0; i<m_tasks.count(); ++i) {
		Task* task = m_tasks.at(i);
		if (task == nullptr)
			qDebug() << "{d} [TaskQueue]   #" << i << ": <null>";
		else
			qDebug() << "{d} [TaskQueue]   #" << i << ": id " << task->taskId() << "  -  title " << task->title() << "  -  desc. " << task->description() << "  -  client " << task->client() << "  -  act. " << task->activity() << "  -  tgt. " << task->target();
	}
	qDebug() << "{d} [TaskQueue] ----------------------------------------";
}


// PRIVATE SLOTS : DATA CHANGE SIGNALLING
void TaskQueue::handleDataChanged() {
	Task* task = static_cast<Task*>(sender());
	QModelIndex index = createIndex(m_tasks.indexOf(task), 0);
	emit dataChanged(index, index);
}
