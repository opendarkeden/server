//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectRegenZoneHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSelectRegenZone.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "RegenZoneManager.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectRegenZoneHandler::execute(CGSelectRegenZone* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );
	
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	cout << pPC->getName() << " ... RegenZone ... " << (int)pPacket->getRegenZoneID() << endl;

	if ( !RegenZoneManager::getInstance()->canRegen( pPC, pPacket->getRegenZoneID() ) ) return;

	cout << pPC->getName() << " ... Can Regen ... " << (int)pPacket->getRegenZoneID() << endl;

	RegenZoneManager::getInstance()->regeneratePC( pPC, pPacket->getRegenZoneID() );

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}
