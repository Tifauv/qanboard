#ifndef MemoryStorage_H
#define MemoryStorage_H

#include "WorkflowStorage.h"

class MemoryStorage : public WorkflowStorage {
	Q_OBJECT

public:
	explicit MemoryStorage(QObject* parent = nullptr);

	void load(Workflow&)  override;
	void store(Workflow&) override;
};

#endif // MemoryStorage_H
