//////////////////////////////////////////////////////////////////////
// 
// Filename    : BillingPlayerInfo.cpp 
// Written By  : sigi
// 
//////////////////////////////////////////////////////////////////////

// include files
#include <stdio.h>
#include "Assert.h"
#include "Player.h"
#include "Socket.h"
#include "BillingPlayerInfo.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
BillingPlayerInfo::BillingPlayerInfo ()
	 throw ( Error )
: m_BillingLoginRequestCount(0), m_BillingLoginVerified(false),
	m_BillingUserKey(0), m_BillingUserStatus("")
{
	m_BillingNextLoginRequestTime.tv_sec = 0;
	m_BillingNextLoginRequestTime.tv_usec = 0;
}

//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
BillingPlayerInfo::~BillingPlayerInfo ()
	 throw ( Error )
{
	__BEGIN_TRY
	__END_CATCH
}

void BillingPlayerInfo::setBillingSession (Player* pPlayer)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pPlayer!=NULL);
	Assert(pPlayer->getSocket()!=NULL);

	const string& PlayerID = pPlayer->getID();
	const Socket* pSocket = pPlayer->getSocket();

	char str[40];
	sprintf(str, "%s%03d%05d", PlayerID.c_str(), 							// ~12
								(int)(pSocket->getSOCKET() % 1000), 	//  3
								(int)(pSocket->getHostIP() % 100000)); //  5

								//(int)m_pSocket->getPort());			//  5

	// 123
	int lenID = PlayerID.length();
	int lenStr = lenID+3+5;
	for (int i=lenStr; i<32; i++)
	{
		switch (rand()%3)
		{
			case 0 : 
				str[i] = rand()%10+'0';
			break;

			case 1 :
				str[i] = rand()%26+'a';
			break;

			case 2 :
				str[i] = rand()%26+'A';
			break;
		}
	}
	str[32] = '\0';

	m_BillingSession = str;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string BillingPlayerInfo::toString () const
       throw ( Error )
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "BillingPlayerInfo("
//		<< "SocketID:" << m_pSocket->getSOCKET() 
//		<< ",Host:" << m_pSocket->getHost() 
//		<< ",ID:" << m_ID
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
