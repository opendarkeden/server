//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSMSAddressListHandler.cpp
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSMSAddressList.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "SMSAddressBook.h"
#include "Gpackets/GCSMSAddressList.h"
#endif	

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSMSAddressListHandler::execute (CGSMSAddressList* pPacket , Player* pPlayer)
	 throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );
	Assert( pPlayer != NULL );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	SMSAddressBook* pBook = pPC->getAddressBook();
	if ( pBook != NULL )
	{
		GCSMSAddressList* pPacket = pBook->getGCSMSAddressList();
		if ( pPacket != NULL ) pGamePlayer->sendPacket( pPacket );
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

