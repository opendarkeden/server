#include "GameServerSpeedCheckTest.h"
#include "GamePlayer.h"
#include "Cpackets/CGVerifyTime.h"

void
GameServerSpeedCheckTest::testSpeedHack()
{
	__BEGIN_TEST_CASE
	
	Socket* pSocket = new Socket();	 // gameplayer안에서 delete된다.
	GamePlayer gameplayer(pSocket);

	bool bCheck = false;

	// 1st try
	bCheck = gameplayer.verifySpeed( NULL );

	CPPUNIT_ASSERT( bCheck == true );

	// 2nd try
	bCheck = gameplayer.verifySpeed( NULL );

	CPPUNIT_ASSERT( bCheck == true );

	// 3rd try
	bCheck = gameplayer.verifySpeed( NULL );

	CPPUNIT_ASSERT( bCheck == true );

	// 4th try
	bCheck = gameplayer.verifySpeed( NULL );

	CPPUNIT_ASSERT( bCheck == true );

	// 5th try
	bCheck = gameplayer.verifySpeed( NULL );

	CPPUNIT_ASSERT( bCheck == true );

	// 6th try
	bCheck = gameplayer.verifySpeed( NULL );

	CPPUNIT_ASSERT( bCheck == false );

	// verify time packet test
	CGVerifyTime pkt;

	cout << "before CGVerifyTime excute" << endl;
	bool bDisconnectException = false;
	try {

		pkt.execute( &gameplayer );

	} catch (DisconnectException& de) {
		bDisconnectException = true;
		cout << "speedhack disconnect" << endl;
	} catch (Throwable& t) {
		cout << t.toString().c_str() << endl;
	}
	cout << "after CGVerifyTime excute" << endl;

	CPPUNIT_ASSERT( bDisconnectException );
	gameplayer.setPlayerStatus( GPS_END_SESSION );

	__END_TEST_CASE
}
