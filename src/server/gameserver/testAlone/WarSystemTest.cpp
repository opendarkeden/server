#include "VSDateTime.h"
#include "WarSystemTest.h"
#include "WarSystem.h"
#include <unistd.h>
#include <vector>
#include <queue>

void
WarSystemTest::setUp()
{
	__BEGIN_TEST_CASE

	g_pWarSystem = new WarSystem;
	g_pWarSystem->init();
	g_pWarSystem->setWarIDSuccessor(2);

	__END_TEST_CASE
}

void
WarSystemTest::tearDown()
{
	__BEGIN_TEST_CASE

	SAFE_DELETE(g_pWarSystem);

	__END_TEST_CASE
}

void WarSystemTest::testWarStart()
{
	__BEGIN_TEST_CASE

	War* pWar = new War(111, WAR_GUILD, 10, War::WAR_STATE_CURRENT);

	g_pWarSystem->addWar( pWar );

	CPPUNIT_ASSERT( pWar->getWarID() == 2 );

	__END_TEST_CASE
}
