//////////////////////////////////////////////////////////////////////////////
// Filename	: CGWithdrawPetHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGWithdrawPet.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "PetItem.h"
#include "Gpackets/GCPetStashVerify.h"
#include "Gpackets/GCPetStashList.h"

#include <cstdio>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGWithdrawPetHandler::execute (CGWithdrawPet* pPacket , Player* pPlayer)
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
	
	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory !=NULL );

	PetItem* pPetItem = dynamic_cast<PetItem*>(pPC->getPetStashItem(pPacket->getIndex()));

	if ( pPetItem == NULL )
	{ 
		gcPetStashVerify.setCode( PET_STASH_RACK_IS_EMPTY );
		pGamePlayer->sendPacket( &gcPetStashVerify );
	}
	else if ( pPetItem->getObjectID() != pPacket->getObjectID() )
	{
		gcPetStashVerify.setCode( PET_STASH_INVALID_OID );
		pGamePlayer->sendPacket( &gcPetStashVerify );
	}
	else
	{
		TPOINT tp;
		if ( !pInventory->getEmptySlot( pPetItem, tp ) )
		{
			gcPetStashVerify.setCode( PET_STASH_NO_INVENTORY_SPACE );
			pGamePlayer->sendPacket( &gcPetStashVerify );
		}
		else
		{
			pPC->addPetStashItem( pPacket->getIndex(), NULL );
			pInventory->addItemEx( tp.x, tp.y, pPetItem );

			char pField[80];
			sprintf(pField, "Storage=%d, X=%d, Y=%d ", STORAGE_INVENTORY, tp.x, tp.y);
			pPetItem->tinysave(pField);

			gcPetStashVerify.setCode( PET_STASH_OK );
			pGamePlayer->sendPacket( &gcPetStashVerify );

			pPetItem->getPetInfo()->setFeedTurn(1);
		}
	}
	
#endif	// __GAME_SERVER__

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}

