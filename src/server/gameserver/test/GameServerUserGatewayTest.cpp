#include "GameServerUserGatewayTest.h"
#include "Types.h"
#include "Exception.h"
#include "UserGateway.h"

void
GameServerUserGatewayTest::testUserPass()
{
	__BEGIN_TEST_CASE

	UserGateway* pUserGateway = UserGateway::getInstance();

	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==0 );

	pUserGateway->passUser(UserGateway::USER_IN_NORMAL);
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==1 );

	pUserGateway->passUser(UserGateway::USER_IN_NORMAL);
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==2 );

	pUserGateway->passUser(UserGateway::USER_OUT_NORMAL);
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==2 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_NORMAL)==1 );

	pUserGateway->passUser(UserGateway::USER_OUT_ZPM_EXCEPTION);
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==2 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_NORMAL)==1 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_ZPM_EXCEPTION)==1 );

	pUserGateway->passUser(UserGateway::USER_OUT_NORMAL);
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==2 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_NORMAL)==2 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_ZPM_EXCEPTION)==1 );

	pUserGateway->clear();
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==0 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_NORMAL)==0 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_ZPM_EXCEPTION)==0 );

	pUserGateway->passUser(UserGateway::USER_IN_NORMAL);
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==1 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_NORMAL)==0 );
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_OUT_ZPM_EXCEPTION)==0 );

	pUserGateway->clear();

	__END_TEST_CASE
}


void
GameServerUserGatewayTest::testUserPassToString()
{
	__BEGIN_TEST_CASE

	UserGateway* pUserGateway = UserGateway::getInstance();
	pUserGateway->clear();

	string msg = pUserGateway->toString();
	CPPUNIT_ASSERT( msg=="UserGateway(  )" );

	pUserGateway->passUser(UserGateway::USER_IN_NORMAL);
	pUserGateway->passUser(UserGateway::USER_IN_NORMAL);
	pUserGateway->passUser(UserGateway::USER_IN_NORMAL);
	CPPUNIT_ASSERT( pUserGateway->getInfo(UserGateway::USER_IN_NORMAL)==3 );

	msg = pUserGateway->toString();

	CPPUNIT_ASSERT( msg=="UserGateway( IN_NORMAL=3 )" );

	pUserGateway->passUser(UserGateway::USER_OUT_NORMAL);
	pUserGateway->passUser(UserGateway::USER_OUT_NORMAL);

	msg = pUserGateway->toString();
	CPPUNIT_ASSERT( msg=="UserGateway( IN_NORMAL=3, OUT_NORMAL=2 )" );

	pUserGateway->clear();

	__END_TEST_CASE
}
