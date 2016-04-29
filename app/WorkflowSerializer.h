#ifndef WorkflowSerializer_H
#define WorkflowSerializer_H

#include <QObject>
#include <QIODevice>
#include "Workflow.h"


/**
 * @brief The WorkflowSerializer class
 */
class WorkflowSerializer : public QObject {
	Q_OBJECT

public:
	explicit WorkflowSerializer(QObject *parent = 0);

	/**
	 * @brief Reads the given XML source to initialize a Workflow.
	 *
	 * @param source
	 *            the data source to read from
	 * @param workflow
	 *            the workflow to initialize
	 */
	virtual void read(QIODevice& source, Workflow& workflow) const = 0;

	/**
	 * @brief Write a Workflow to an XML destination.
	 *
	 * @param dest
	 *            the data destination to write to
	 * @param workflow
	 *            the workflow to save
	 */
	virtual void write(QIODevice& dest, const Workflow& workflow) const = 0;
};

#endif // WorkflowSerializer_H
