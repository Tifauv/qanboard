#ifndef XmlStorage_H
#define XmlStorage_H

#include "WorkflowStorage.h"
#include <QString>
#include <QXmlStreamReader>

class XmlStorage : public WorkflowStorage {
	Q_OBJECT

public:
	explicit XmlStorage(const QString& fileName, QObject *parent = 0);

	void load(Workflow&) const;
	void store(const Workflow&) const;

private:
	void readWorkflow(QXmlStreamReader&, Workflow&) const;
	void readTaskQueue(QXmlStreamReader&, Workflow&) const;
	Task* readTask(QXmlStreamReader&) const;

	QString m_file;
};

#endif // XmlStorage_H
