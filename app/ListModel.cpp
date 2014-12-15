/*
 * Author: Christophe Dumez <dchris@gmail.com>
 * License: Public domain (No attribution required)
 * Website: http://cdumez.blogspot.com/
 * Version: 1.0
 */

#include "ListModel.h"
#include <iostream>

using namespace std;

ListModel::ListModel() :
	QAbstractListModel(NULL),
	m_prototype(NULL) {
}

ListModel::ListModel(ListItem* p_prototype, QObject* p_parent) :
	QAbstractListModel(p_parent),
	m_prototype(p_prototype) {
	m_prototype->setParent(this);
	setRoleNames(m_prototype->roleNames());
}

ListModel::ListModel(const ListModel& p_model) :
	QAbstractListModel(),
	m_prototype(p_model.m_prototype),
	m_list(p_model.m_list) {
	m_prototype->setParent(this);
	setRoleNames(m_prototype->roleNames());
}


int ListModel::rowCount(const QModelIndex& p_parent) const {
	Q_UNUSED(p_parent);
	return m_list.size();
}


QVariant ListModel::data(const QModelIndex& p_index, int p_role) const {
	if (p_index.row() < 0 || p_index.row() >= m_list.size())
		return QVariant();
	return m_list.at(p_index.row())->data(p_role);
}


ListModel::~ListModel() {
	delete m_prototype;
	clear();
}


void ListModel::appendRow(ListItem* p_item) {
	appendRows(QList<ListItem*>() << p_item);
}


void ListModel::appendRows(const QList<ListItem *>& p_items) {
	beginInsertRows(QModelIndex(), rowCount(), rowCount() + p_items.size() - 1);
	foreach (ListItem *item, p_items) {
		connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
		m_list.append(item);
	}
	endInsertRows();
}


void ListModel::insertRow(int p_row, ListItem* p_item) {
	beginInsertRows(QModelIndex(), p_row, p_row);
	connect(p_item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
	m_list.insert(p_row, p_item);
	endInsertRows();
}


void ListModel::handleItemChange() {
	ListItem* item = static_cast<ListItem*>(sender());
	QModelIndex index = indexFromItem(item);
	if (index.isValid())
		emit dataChanged(index, index);
}


ListItem* ListModel::find(const QString& p_id) const {
	foreach(ListItem* item, m_list) {
		if (item->id() == p_id)
			return item;
	}
	return 0;
}


QModelIndex ListModel::indexFromItem(const ListItem* p_item) const {
	Q_ASSERT(p_item);
	for (int row=0; row<m_list.size(); ++row) {
		if (m_list.at(row) == p_item)
			return index(row);
	}
	return QModelIndex();
}


void ListModel::clear() {
	removeRows(0, m_list.count());
}


bool ListModel::removeRow(int p_row, const QModelIndex& p_parent) {
	Q_UNUSED(p_parent);
	if (p_row < 0 || p_row >= m_list.size())
		return false;
	beginRemoveRows(QModelIndex(), p_row, p_row);
	delete m_list.takeAt(p_row);
	endRemoveRows();
	return true;
}


bool ListModel::removeRows(int p_row, int p_count, const QModelIndex& p_parent) {
	Q_UNUSED(p_parent);
	if (p_row < 0 || (p_row+p_count-1) >= m_list.size())
		return false;
	beginRemoveRows(QModelIndex(), p_row, p_row + p_count - 1);
	for (int i=0; i<p_count; ++i)
		delete m_list.takeAt(p_row);
	endRemoveRows();
	return true;
}


ListItem* ListModel::takeRow(int p_row) {
	beginRemoveRows(QModelIndex(), p_row, p_row);
	ListItem* item = m_list.takeAt(p_row);
	endRemoveRows();
	return item;
}
