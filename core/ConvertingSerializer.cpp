#include "ConvertingSerializer.h"
#include <QtDebug>


// CONSTRUCTOR
/**
 * @brief ConvertingSerializer::ConvertingSerializer
 * @param p_parent
 */
ConvertingSerializer::ConvertingSerializer(QObject* p_parent) :
	WorkflowSerializer(p_parent),
	m_currentSerializer(nullptr),
	m_legacySerializer(nullptr) {
}


// SETTERS
/**
 * @brief ConvertingSerializer::setCurrentSerializer
 * @param p_serializer
 */
void ConvertingSerializer::setCurrentSerializer(WorkflowSerializer* p_serializer) {
	m_currentSerializer = p_serializer;
	m_currentSerializer->setParent(this);
}


/**
 * @brief ConvertingSerializer::setLegacySerializer
 * @param p_serializer
 */
void ConvertingSerializer::setLegacySerializer(WorkflowSerializer* p_serializer) {
	m_legacySerializer = p_serializer;
	m_legacySerializer->setParent(this);
}


// MAIN METHODS
/**
 * @brief ConvertingSerializer::read
 * @param p_source
 * @param p_workflow
 */
bool ConvertingSerializer::read(QIODevice& p_source, Workflow& p_workflow) const {
	Q_ASSERT(m_currentSerializer);
	
	// Try reading using the current format, and fallback to the legacy one if it fails.
	qDebug() << "(i) [ConvertingSerializer::read] Reading using the current format.";
	bool read = m_currentSerializer->read(p_source, p_workflow);
	if (!read && m_legacySerializer != nullptr) {
		qDebug() << "(i) [ConvertingSerializer::read] Failed to read using the current format, trying the legacy format.";
		read = m_legacySerializer->read(p_source, p_workflow);
		if (read)
			qDebug() << "(i) [ConvertingSerializer::read] Legacy format successful.";
		else
			qDebug() << "(i) [ConvertingSerializer::read] Legacy format failed too.";
	}

	return read;
}


/**
 * @brief ConvertingSerializer::write
 * @param p_source
 * @param p_workflow
 */
bool ConvertingSerializer::write(QIODevice& p_source, const Workflow& p_workflow) const {
	Q_ASSERT(m_currentSerializer);
	
	// Always write using the current format
	return m_currentSerializer->write(p_source, p_workflow);
}
