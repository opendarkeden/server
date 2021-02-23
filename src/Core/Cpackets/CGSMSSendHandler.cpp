//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSMSSendHandler.cpp
// Written By  : reiot@ewestsoft.com , elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSMSSend.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "SMSServiceThread.h"
	#include "PlayerCreature.h"

	#include "Gpackets/GCAddressListVerify.h"

	#include <cstdio>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSMSSendHandler::execute (CGSMSSend* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	filelog("SMS.log", "[%s:%s] %s", pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->toString().c_str());
	GCAddressListVerify gcVerify;

	if ( pPC->getSMSCharge() < pPacket->getNumbersList().size() )
	{
		filelog("SMS.log", "[%s:%s] Charge가 모자랍니다.", pGamePlayer->getID().c_str(), pPC->getName().c_str() );
		gcVerify.setCode( GCAddressListVerify::SMS_SEND_FAIL );
		gcVerify.setParameter( GCAddressListVerify::SMS_SEND_FAIL_NOT_ENOUGH_CHARGE );
		pGamePlayer->sendPacket( &gcVerify );
		return;
	}

	pPC->setSMSCharge( pPC->getSMSCharge() - pPacket->getNumbersList().size() );

	char buffer[100];
	sprintf( buffer, "SMSCharge=%u", pPC->getSMSCharge() );
	pPC->tinysave( buffer );

	list<string>::const_iterator itr = pPacket->getNumbersList().begin();
	list<string>::const_iterator endItr = pPacket->getNumbersList().end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( SMSServiceThread::Instance().isValidNumber( *itr ) )
		{
			SMSMessage* pMsg = new SMSMessage( pPC->getName(), *itr, pPacket->getCallerNumber(), pPacket->getMessage() );
			SMSServiceThread::Instance().pushMessage( pMsg );
		}
	}

	gcVerify.setCode( GCAddressListVerify::SMS_SEND_OK );
	gcVerify.setParameter( pPC->getSMSCharge() );
	pGamePlayer->sendPacket( &gcVerify );

#endif
	
	__END_DEBUG_EX __END_CATCH
}
