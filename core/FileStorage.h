#ifndef FileStorage_H
#define FileStorage_H

#include "WorkflowStorage.h"
#include "WorkflowSerializer.h"
#include <QDir>

class FileStorage : public WorkflowStorage {
	Q_OBJECT

public:
	explicit FileStorage(QObject* parent = nullptr);

	Q_INVOKABLE void setup(WorkflowSerializer* const p_serializer);

	Q_INVOKABLE void load(Workflow&)  override;
	Q_INVOKABLE void store(Workflow&) override;

private:
	bool isDataDirReady();
	bool isReady();

	WorkflowSerializer* m_serializer;
	QDir                m_dataDir;
};

#endif // FileStorage_H
