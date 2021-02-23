//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPetGambleHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGPetGamble.h"

#ifdef __GAME_SERVER__

#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "PetInfo.h"
#include "CreatureUtil.h"
#include "PetItem.h"

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPetGambleHandler::execute (CGPetGamble* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	cout << "Æê °·ºíÇÔ´Ï´ç" << endl;

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	PetInfo* pPetInfo = pPC->getPetInfo();
	if ( pPetInfo == NULL ) return;
	if ( !pPetInfo->canGamble() ) return;

	int value = rand()%100;
	pPetInfo->setGamble(0);

	cout << value << endl;

	if ( value < pPetInfo->getPetLevel() )
	{
		if ( !pPetInfo->canCutHead() )
		{
			pPetInfo->setCutHead(1);
			if ( pPetInfo->getPetType() > 2 && pPetInfo->getPetLevel() >= 30 ) pPetInfo->setGamble(1);
		}
		else if ( pPetInfo->getPetType() > 2 )
		{
			pPetInfo->setAttack(1);
		}
//		cout << "°·ºí ¼º°ø!" << endl;
	}

	pPetInfo->getPetItem()->savePetInfo();
	
	sendPetInfo( pGamePlayer, false );

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
