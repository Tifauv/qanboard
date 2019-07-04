#ifndef History_H
#define History_H

#include <QMetaType>
#include <QAbstractListModel>
#include <QVector>
#include "TaskMove.h"

class History : public QAbstractListModel {
	Q_OBJECT

	Q_PROPERTY(int count  READ count  NOTIFY countChanged)
	
public:
	enum Roles {
		TaskRole = Qt::UserRole+1,
		TaskIdRole,
		TaskClientRole,
		TaskActivityRole,
		TaskDescriptionRole,
		OriginNameRole,
		OriginColorRole,
		DestinationNameRole,
		DestinationColorRole,
		TimestampRole,
		DateRole,
		TimeRole
	};
	
	explicit History(QObject* parent = nullptr);
	explicit History(const History&);
	~History() override {}
	
	int count() const;
	
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QHash<int, QByteArray> roleNames() const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	
public slots:
	const TaskMove* at(int row) const;
	void append(TaskMove*);

signals:
	void countChanged(int);

private:
	QVector<TaskMove*> m_moves;
};

Q_DECLARE_METATYPE(History*)

#endif // History_H
