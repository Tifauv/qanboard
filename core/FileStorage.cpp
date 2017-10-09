#include "FileStorage.h"
#include <QStandardPaths>
#include <QtDebug>

#define WF_FILE "workflow.xml"


FileStorage::FileStorage(WorkflowSerializer& p_serializer, QObject* p_parent) :
	WorkflowStorage(p_parent),
	m_serializer(p_serializer),
	m_dataDir() {
	checkDataDir();
	qDebug() << "(i) [FileStorage] Created.";
}


/**
 * @brief FileStorage::load
 *
 * @param p_workflow
 *            the workflow to load
 */
void FileStorage::load(Workflow& p_workflow) const {
	QFile file(m_dataDir.filePath(WF_FILE));
	m_serializer.read(file, p_workflow);
}


/**
 * @brief FileStorage::store
 *
 * @param p_workflow
 *            the workflow to save
 */
void FileStorage::store(const Workflow& p_workflow) const {
	QFile file(m_dataDir.filePath(WF_FILE));
	m_serializer.write(file, p_workflow);
}


/**
 * @brief Checks the data directory.
 * If the data directory does not exist, it is created.
 */
void FileStorage::checkDataDir() {
	// Get the application configuration directory
	QString location = QStandardPaths::writableLocation(QStandardPaths::DataLocation);


	// If the configuration directory does not exist...
	if (!m_dataDir.cd(location)) {
		if (!m_dataDir.mkpath(location)) {
			qWarning() << "(i) [FileStorage] Could not create the " << location << " directory";
			qWarning() << "(i) [FileStorage] I will not be able to store the workflow, exiting...";
		}
		else {
			m_dataDir.cd(location);
			qDebug() << "(i) [FileStorage] Data directory " << m_dataDir.path() << " created.";
		}
	}
	else
		qDebug() << "(i) [FileStorage] Data directory " << m_dataDir.path() << " found.";
}
