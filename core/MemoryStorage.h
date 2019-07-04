#ifndef MemoryStorage_H
#define MemoryStorage_H

#include "WorkflowStorage.h"

class MemoryStorage : public WorkflowStorage {
	Q_OBJECT

public:
	explicit MemoryStorage(QObject* parent = nullptr);

	void load(Workflow&)  const override;
	void store(Workflow&) const override;
};

#endif // MemoryStorage_H
