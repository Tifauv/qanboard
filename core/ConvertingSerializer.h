#ifndef ConvertingSerializer_H
#define ConvertingSerializer_H

#include "WorkflowSerializer.h"


/**
 * @brief The XmlSerializer class
 */
class ConvertingSerializer : public WorkflowSerializer {
	Q_OBJECT

public:
	explicit ConvertingSerializer(QObject* parent = nullptr);
	
	void setCurrentSerializer(WorkflowSerializer*);
	void setLegacySerializer(WorkflowSerializer*);

	bool read(QIODevice&, Workflow&)        const override;
	bool write(QIODevice&, const Workflow&) const override;

private:
	/** The serializer for the last version of the format. */
	WorkflowSerializer* m_currentSerializer;
	
	/** The serializer for the previous versions of the format. */
	WorkflowSerializer* m_legacySerializer;
};

#endif // ConvertingSerializer_H
