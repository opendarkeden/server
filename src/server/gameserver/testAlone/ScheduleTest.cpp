#include "ScheduleTest.h"

#include "Work.h"
#include "Schedule.h"
#include "Scheduler.h"
#include <unistd.h>
#include <vector>
#include <queue>

class TestWork : public Work
{
public:
	~TestWork() { }

public:
	bool test;

public:
	TestWork() { test = false; }
	void execute() { test = true; }

	string toString() const throw(Error) { return "TestWork"; }
};

void
ScheduleTest::setUp()
{
}

void
ScheduleTest::tearDown()
{
}

void ScheduleTest::testSchedule()
{
	__BEGIN_TEST_CASE

	VSDateTime::setCurrentDateTime(0);		// 처음에
	VSDateTime dt(100);						// 100초 뒤에 실행하도록 예약해둔다.

	TestWork* pWork = new TestWork();
	Schedule* pSchedule = new Schedule( pWork, dt );

	CPPUNIT_ASSERT( pWork != NULL );
	CPPUNIT_ASSERT( pSchedule != NULL );

	CPPUNIT_ASSERT( !pSchedule->heartbeat() );
	CPPUNIT_ASSERT( !pWork->test );

	VSDateTime::setCurrentDateTime(50);	// 50 (50분? 50시간?) 뒤에

	CPPUNIT_ASSERT( !pSchedule->heartbeat() );	// 아직 실행되어선 안 된다.
	CPPUNIT_ASSERT( !pWork->test );

	VSDateTime::setCurrentDateTime(101);	// 100초 (100분? 100시간?) 뒤에

	CPPUNIT_ASSERT( pSchedule->heartbeat() );	// 실행되어야 한다.
	CPPUNIT_ASSERT( pWork->test );

	SAFE_DELETE( pSchedule );

	__END_TEST_CASE
}

void ScheduleTest::testScheduler()
{
	__BEGIN_TEST_CASE

	VSDateTime::setCurrentDateTime( 0 );
	Scheduler* pScheduler = new Scheduler();

	TestWork* pWork1 = new TestWork();
	Schedule* pSchedule1 = new Schedule( pWork1, VSDateTime(100) );						// 100초 뒤에 실행하도록 예약해둔다.

	pScheduler->addSchedule( pSchedule1 );

	TestWork* pWork2 = new TestWork();
	Schedule* pSchedule2 = new Schedule( pWork2, VSDateTime(200) );

	TestWork* pWork = NULL;

	pScheduler->addSchedule( pSchedule2 );

	CPPUNIT_ASSERT( pScheduler->getSize() == 2 );		// 두개 다 잘 들어가야 한다.

	pScheduler->heartbeat();

	CPPUNIT_ASSERT( !pWork1->test );
	CPPUNIT_ASSERT( !pWork2->test );

	VSDateTime::setCurrentDateTime(50);			// 50초 뒤에

	pScheduler->heartbeat();
	CPPUNIT_ASSERT( pScheduler->getSize() == 2 );

	CPPUNIT_ASSERT( !pWork1->test );			// 아무것도 실행되지 않았어야 한다.
	CPPUNIT_ASSERT( !pWork2->test );

	VSDateTime::setCurrentDateTime(101);			// 100초 뒤에

	pWork = dynamic_cast<TestWork*>(pScheduler->heartbeat());
	CPPUNIT_ASSERT( pWork1 == pWork );
	CPPUNIT_ASSERT( pScheduler->getSize() == 1 );		// 한개는 지워졌어야 한다.

	CPPUNIT_ASSERT( pWork1->test );				// 1번 스케줄만 실행되었어야 한다.
	CPPUNIT_ASSERT( !pWork2->test );

	VSDateTime::setCurrentDateTime(151);			// 150초 뒤에

	pScheduler->heartbeat();
	CPPUNIT_ASSERT( pScheduler->getSize() == 1 );		// 한개는 지워졌어야 한다.

	CPPUNIT_ASSERT( pWork1->test );
	CPPUNIT_ASSERT( !pWork2->test );

	VSDateTime::setCurrentDateTime(201);			// 200초 뒤에

	pWork = dynamic_cast<TestWork*>(pScheduler->heartbeat());

	CPPUNIT_ASSERT( pWork2 == pWork );
	CPPUNIT_ASSERT( pScheduler->getSize() == 0 );		// 두개 다 지워졌어야 한다.

	CPPUNIT_ASSERT( pWork1->test );
	CPPUNIT_ASSERT( pWork2->test );

	SAFE_DELETE( pScheduler );

	__END_TEST_CASE
}

class Less {
public :
	bool operator () ( int i1, int i2 )
	{
		return i1 > i2;
	}
};

void ScheduleTest::testPQ()
{
	priority_queue< int, vector<int>, Less > pq;

	pq.push( 5 );
	pq.push( 2 );
	pq.push( 6 );
	pq.push( 4 );
	pq.push( 3 );
	pq.push( 1 );
	pq.push( 7 );

	CPPUNIT_ASSERT( pq.top() == 1 ); pq.pop();
	CPPUNIT_ASSERT( pq.top() == 2 ); pq.pop();
	CPPUNIT_ASSERT( pq.top() == 3 ); pq.pop();
	CPPUNIT_ASSERT( pq.top() == 4 ); pq.pop();
	CPPUNIT_ASSERT( pq.top() == 5 ); pq.pop();
	CPPUNIT_ASSERT( pq.top() == 6 ); pq.pop();
	CPPUNIT_ASSERT( pq.top() == 7 ); pq.pop();
	CPPUNIT_ASSERT( pq.empty() );
}
