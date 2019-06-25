#ifndef History_H
#define History_H

#include <QMetaType>
#include <QAbstractListModel>
#include <QVector>
#include "TaskMove.h"

class History : public QAbstractListModel {
	Q_OBJECT
	
	
public:
	enum Roles {
		TaskRole = Qt::UserRole+1,
		OriginRole,
		DestinationRole,
		TimestampRole
	};
	
	explicit History(QObject* parent = nullptr);
	explicit History(const History& p_toCopy);
	~History() override {}
	
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	
public slots:
	const TaskMove* at(int row) const;
	void appendRow(TaskMove*);

private:
	QVector<TaskMove*> m_moves;
};

Q_DECLARE_METATYPE(History)

#endif // History_H
