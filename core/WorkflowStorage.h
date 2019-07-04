#ifndef WorkflowStorage_H
#define WorkflowStorage_H

#include <QObject>
#include "Workflow.h"

/**
 * @brief The WorkflowStorage interface defines the two methods
 * shared by the implementations.
 */
class WorkflowStorage : public QObject {
	Q_OBJECT

public:
	explicit WorkflowStorage(QObject* parent = nullptr);

	virtual void load(Workflow&)  const = 0;
	virtual void store(Workflow&) const = 0;
};

#endif // WorkflowStorage_H
