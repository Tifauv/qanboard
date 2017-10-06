#ifndef TestTaskQueue_H
#define TestTaskQueue_H

#include <QObject>
#include <QtTest/QTest>
#include "TaskQueue.h"

class TestTaskQueue : public QObject {

	Q_OBJECT

public:
	TestTaskQueue() :
	    m_queue(nullptr) {}

private slots:
	void init();
	void cleanup();

	void moveRowSameIndex();
	void moveRowInvalidSourceIndex1();
	void moveRowInvalidSourceIndex2();
	void moveRowAtEnd1();
	void moveRowAtEnd2();
	void moveRowAtInvalidIndex();
	void moveRowAfter();
	void moveRowBefore();
	void moveRowLastToTop();
	void moveRowFirstToEnd();

private:
	TaskQueue* m_queue;
};

#endif // TestTaskQueue_H
