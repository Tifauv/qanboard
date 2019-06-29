#include "TestTaskQueue.h"

/**
 * @brief Run before each test function.
 * Used to reset the queue.
 */
void TestTaskQueue::init() {
	m_queue = new TaskQueue();
	m_queue->setName("Test");
	m_queue->append(new Task(1, "Test task #1", "", "John Doe"));
	m_queue->append(new Task(2, "Test task #2", "", "Jane Doe"));
	m_queue->append(new Task(3, "Test task #3", "", "Pete Doe"));
	m_queue->append(new Task(4, "Test task #4", "", "John Doe"));
}


/**
 * @brief Run after each test function.
 * Destroys the queue.
 */
void TestTaskQueue::cleanup() {
	delete m_queue;
	m_queue = nullptr;
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowSameIndex() {
	m_queue->move(1, 1);

	QCOMPARE(m_queue->at(0)->taskId(), 1u);
	QCOMPARE(m_queue->at(1)->taskId(), 2u);
	QCOMPARE(m_queue->at(2)->taskId(), 3u);
	QCOMPARE(m_queue->at(3)->taskId(), 4u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowInvalidSourceIndex1() {
	m_queue->move(-1, 2);

	QCOMPARE(m_queue->at(0)->taskId(), 1u);
	QCOMPARE(m_queue->at(1)->taskId(), 2u);
	QCOMPARE(m_queue->at(2)->taskId(), 3u);
	QCOMPARE(m_queue->at(3)->taskId(), 4u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowInvalidSourceIndex2() {
	m_queue->move(m_queue->count() + 1, 2);

	QCOMPARE(m_queue->at(0)->taskId(), 1u);
	QCOMPARE(m_queue->at(1)->taskId(), 2u);
	QCOMPARE(m_queue->at(2)->taskId(), 3u);
	QCOMPARE(m_queue->at(3)->taskId(), 4u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowAtEnd1() {
	m_queue->move(1, -1);

	QCOMPARE(m_queue->at(0)->taskId(), 1u);
	QCOMPARE(m_queue->at(1)->taskId(), 3u);
	QCOMPARE(m_queue->at(2)->taskId(), 4u);
	QCOMPARE(m_queue->at(3)->taskId(), 2u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowAtEnd2() {
	m_queue->move(1, m_queue->count() + 1);

	QCOMPARE(m_queue->at(0)->taskId(), 1u);
	QCOMPARE(m_queue->at(1)->taskId(), 3u);
	QCOMPARE(m_queue->at(2)->taskId(), 4u);
	QCOMPARE(m_queue->at(3)->taskId(), 2u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowAtInvalidIndex() {
	m_queue->move(1, -2);

	QCOMPARE(m_queue->at(0)->taskId(), 1u);
	QCOMPARE(m_queue->at(1)->taskId(), 2u);
	QCOMPARE(m_queue->at(2)->taskId(), 3u);
	QCOMPARE(m_queue->at(3)->taskId(), 4u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowAfter() {
	m_queue->move(1, 2);

	QCOMPARE(m_queue->at(0)->taskId(), 1u);
	QCOMPARE(m_queue->at(1)->taskId(), 3u);
	QCOMPARE(m_queue->at(2)->taskId(), 2u);
	QCOMPARE(m_queue->at(3)->taskId(), 4u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowBefore() {
	m_queue->move(2, 1);

	QCOMPARE(m_queue->at(0)->taskId(), 1u);
	QCOMPARE(m_queue->at(1)->taskId(), 3u);
	QCOMPARE(m_queue->at(2)->taskId(), 2u);
	QCOMPARE(m_queue->at(3)->taskId(), 4u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowLastToTop() {
	m_queue->move(3, 0);

	QCOMPARE(m_queue->at(0)->taskId(), 4u);
	QCOMPARE(m_queue->at(1)->taskId(), 1u);
	QCOMPARE(m_queue->at(2)->taskId(), 2u);
	QCOMPARE(m_queue->at(3)->taskId(), 3u);
}


/**
 * @brief Test the internal move operation.
 */
void TestTaskQueue::moveRowFirstToEnd() {
	m_queue->move(0, 3);

	QCOMPARE(m_queue->at(0)->taskId(), 2u);
	QCOMPARE(m_queue->at(1)->taskId(), 3u);
	QCOMPARE(m_queue->at(2)->taskId(), 4u);
	QCOMPARE(m_queue->at(3)->taskId(), 1u);
}

QTEST_MAIN(TestTaskQueue)
