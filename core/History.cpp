#include "History.h"
#include <QtDebug>

// CONSTRUCTORS
/**
 * @brief History::History
 * @param p_parent
 */
History::History(QObject* p_parent) :
	QAbstractListModel(p_parent),
	m_moves() {
	qDebug() << "(i) [History] Created.";
}


/**
 * @brief History::History
 * @param p_toCopy
 */
History::History(const History& p_toCopy) :
	QAbstractListModel(),
	m_moves(p_toCopy.m_moves) {
	qDebug() << "(i) [History] Copied history.";
}


// MODEL/VIEW API
/**
 * @brief History::rowCount
 * @param p_parent
 * @return 
 */
int History::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	return m_moves.count();
}


/**
 * @brief History::roleNames
 * @return
 */
QHash<int, QByteArray> History::roleNames() const {
	QHash<int, QByteArray> names;
	names[TaskRole]        = "task";
	names[OriginRole]      = "origin";
	names[DestinationRole] = "destination";
	names[TimestampRole]   = "timestamp";
	return names;
}


/**
 * @brief History::data
 * @param p_index
 * @param p_role
 * @return
 */
QVariant History::data(const QModelIndex& p_index, int p_role) const {
	qDebug() << "(i) [History] Query data for role " << p_role << " of TaskMove at row " << p_index.row();
	if (p_index.row() < 0 || p_index.row() >= rowCount())
		return QVariant();

	TaskMove* move = m_moves.at(p_index.row());
	switch (p_role) {
	case TaskRole:
		return QVariant::fromValue(move->task());
	case OriginRole:
		return QVariant::fromValue(move->origin().name());
	case DestinationRole:
		return QVariant::fromValue(move->destination());
	case TimestampRole:
		return move->timestamp();
	default:
		return QVariant();
	}
}


// PUBLIC SLOTS
/**
 * @brief History::at
 * @param p_row
 * @return 
 */
const TaskMove* History::at(int p_index) const {
	if (p_index < 0 || p_index >= rowCount())
        return nullptr;
	return m_moves.at(p_index);
	
}


/**
 * @brief History::appendRow
 * @param p_move
 */
void History::appendRow(TaskMove* p_move) {
	Q_ASSERT(p_move);
	
	int lastRow = rowCount();
	
	beginInsertRows(QModelIndex(), lastRow, lastRow);
	m_moves.append(p_move);
	endInsertRows();
	p_move->setParent(this);
	qDebug() << "(i) [History] Task move appended for task #" << p_move->task().taskId() << " on " << p_move->timestamp();
}
