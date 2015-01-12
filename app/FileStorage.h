#ifndef FileStorage_H
#define FileStorage_H

#include "WorkflowStorage.h"
#include "WorkflowSerializer.h"
#include <QDir>

//template <class Serializer>
class FileStorage : public WorkflowStorage {
	Q_OBJECT

public:
	explicit FileStorage(WorkflowSerializer& p_serializer, QObject* parent = 0);

	void load(Workflow&)        const;
	void store(const Workflow&) const;

private:
	void checkDataDir();

	WorkflowSerializer& m_serializer;
	QDir                m_dataDir;
};

#endif // FileStorage_H
