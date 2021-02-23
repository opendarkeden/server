//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDeleteSMSAddressHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGDeleteSMSAddress.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "SMSAddressBook.h"
	#include "Assert.h"

	#include "Gpackets/GCAddressListVerify.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDeleteSMSAddressHandler::execute (CGDeleteSMSAddress* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	GCAddressListVerify gcVerify;

	SMSAddressBook* pBook = pPC->getAddressBook();
	Assert( pBook != NULL );
	
	int result = pBook->removeAddressElement( pPacket->getElementID() );

	if ( result != 0 )
	{
		gcVerify.setCode( GCAddressListVerify::ADDRESS_LIST_DELETE_FAIL );
		gcVerify.setParameter( result );
		pGamePlayer->sendPacket( &gcVerify );
		return;
	}

	gcVerify.setCode( GCAddressListVerify::ADDRESS_LIST_DELETE_OK );
	gcVerify.setParameter( result );
	pGamePlayer->sendPacket( &gcVerify );

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
