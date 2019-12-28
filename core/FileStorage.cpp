#include "FileStorage.h"
#include <QStandardPaths>
#include <QtDebug>

#define WF_FILE "workflow.xml"


FileStorage::FileStorage(QObject* p_parent) :
	WorkflowStorage(p_parent),
	m_serializer(nullptr),
	m_dataDir() {
	qDebug() << "(i) [FileStorage] Created.";
}


/**
 * @brief FileStorage::setup
 * @param p_serializer
 */
void FileStorage::setup(WorkflowSerializer* const p_serializer) {
	m_serializer = p_serializer;
}


/**
 * @brief FileStorage::load
 *
 * @param p_workflow
 *            the workflow to load
 */
void FileStorage::load(Workflow& p_workflow) {
	if (isReady()) {
		QFile file(m_dataDir.filePath(WF_FILE));
		m_serializer->read(file, p_workflow);
	}
}


/**
 * @brief FileStorage::store
 *
 * @param p_workflow
 *            the workflow to save
 */
void FileStorage::store(Workflow& p_workflow) {
	if (isReady()) {
		QFile file(m_dataDir.filePath(WF_FILE));
		m_serializer->write(file, p_workflow);
	}
}


/**
 * @brief Checks the data directory.
 * If the data directory does not exist, it is created.
 * 
 * @return true if the data directory exists and is cd-able;
 *         false otherwise
 */
bool FileStorage::isDataDirReady() {
	bool dataDirUsable = false;

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
			dataDirUsable = true;
		}
	}
	else {
		qDebug() << "(i) [FileStorage] Data directory " << m_dataDir.path() << " found.";
		dataDirUsable = true;
	}
	
	return dataDirUsable;
}


/**
 * @brief Check if the object's internal state is ready for load and store operations.
 * The object's internal state is ready if a WorkflowSerializer has been set and the
 * data diretory exists and is readable.
 * 
 * @return true if the load() and store() operations can proceed;
 *         false otherwise
 */
bool FileStorage::isReady() {
	if (m_serializer == nullptr) {
		qWarning() << "/!\\ [FileStorage::isReady] This FileStorage is not ready because no WorkflowSerializer has been set.";
		qWarning() << "/!\\ [FileStorage::isReady] The required function will abort.";
		qWarning() << "/!\\ [FileStorage::isReady] Please use the setup(WorkflowSerializer*) function to initialize this FileStorage.";
		return false;
	}
	
	if (!isDataDirReady()) {
		qWarning() << "/!\\ [FileStorage::isReady] This FileStorage is not ready because the data directory cannot be cd'ed into.";
		qWarning() << "/!\\ [FileStorage::isReady] The required function will abort.";
		return false;
	}
	
	return true;
}
