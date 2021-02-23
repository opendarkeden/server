//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDepositPetHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGDepositPet.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "PetItem.h"
#include "CreatureUtil.h"
#include "Gpackets/GCPetStashVerify.h"
#include "Gpackets/GCPetStashList.h"

#include <cstdio>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDepositPetHandler::execute (CGDepositPet* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	GCPetStashVerify gcPetStashVerify;

	if ( pPacket->getIndex() >= MAX_PET_STASH )
	{
		gcPetStashVerify.setCode( PET_STASH_INVALID_INDEX );
		pGamePlayer->sendPacket( &gcPetStashVerify );
		return;
	}

	if ( pPC->getPetStashItem( pPacket->getIndex() ) != NULL )
	{
		gcPetStashVerify.setCode( PET_STASH_RACK_IS_NOT_EMPTY );
		pGamePlayer->sendPacket( &gcPetStashVerify );
		return;
	}

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	PetItem* pPetItem = dynamic_cast<PetItem*>(pInventory->getItemWithObjectID( pPacket->getObjectID() ));
	if ( pPetItem == NULL )
	{
		gcPetStashVerify.setCode( PET_STASH_INVALID_OID );
		pGamePlayer->sendPacket( &gcPetStashVerify );
		return;
	}

	pInventory->deleteItem( pPetItem->getObjectID() );
	pPC->addPetStashItem( pPacket->getIndex(), pPetItem );
	pGamePlayer->sendPacket( &gcPetStashVerify );

	char pField[80];
	sprintf(pField, "Storage=%d, StorageID=%d ", STORAGE_PET_STASH, pPacket->getIndex());
	pPetItem->tinysave(pField);

	pPetItem->getPetInfo()->setFeedTurn(2);

	if ( pPetItem != NULL && pPetItem->getPetInfo() != NULL && pPetItem->getPetInfo() == pPC->getPetInfo() )
	{
		pPC->setPetInfo(NULL);
		pPC->initAllStatAndSend();
		sendPetInfo( pGamePlayer, true );
	}

#endif	// __GAME_SERVER__

    __END_DEBUG
	__END_DEBUG_EX __END_CATCH
}

