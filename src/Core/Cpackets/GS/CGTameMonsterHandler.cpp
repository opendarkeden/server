//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTameMonsterHandler.cc
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGTameMonster.h"

#ifdef __GAME_SERVER__

#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "PetItem.h"
#include "PetFood.h"
#include "PetInfo.h"
#include "Zone.h"
#include "Monster.h"
#include "Inventory.h"
#include "ItemUtil.h"
#include "CreatureUtil.h"

#include "ItemFactoryManager.h"
#include <list>

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCCannotUse.h"
#include "Gpackets/GCDeleteInventoryItem.h"
#include "PacketUtil.h"

#include "PetTypeInfo.h"
#include "VSDateTime.h"

#include "GQuestManager.h"
#include "VariableManager.h"

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTameMonsterHandler::execute (CGTameMonster* pPacket , Player* pPlayer)
	     throw (Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	Zone* pZone = pPC->getZone();
	Assert( pZone != NULL );

	Monster* pMonster = dynamic_cast<Monster*>(pZone->getCreature( pPacket->getObjectID() ));
	if ( pMonster == NULL ) return;

	Item* pItem = pPC->getExtraInventorySlotItem();
	if ( pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_PET_FOOD || pItem->getNum() != 1 ) return;

	PetFoodInfo* pPetFoodInfo = dynamic_cast<PetFoodInfo*>(g_pPetFoodInfoManager->getItemInfo( pItem->getItemType() ));
	Assert( pPetFoodInfo != NULL );

	Inventory* pInventory = pPC->getInventory();
	if ( pInventory == NULL ) return;

	ItemType_t petType = PET_COMMON;
	PetItem* pPetItem = dynamic_cast<PetItem*>(g_pItemFactoryManager->createItem( Item::ITEM_CLASS_PET_ITEM, petType, list<OptionType_t>() ));
	Assert( pPetItem != NULL );

	_TPOINT pt;
	if ( !pInventory->getEmptySlot( pPetItem, pt ) )
	{
		GCCannotUse gcCannotUse;
		pGamePlayer->sendPacket(&gcCannotUse);
		SAFE_DELETE( pPetItem );
		return;
	}

	pPC->deleteItemFromExtraInventorySlot();
	GCDeleteInventoryItem gcDI;
	gcDI.setObjectID( pItem->getObjectID() );
	pGamePlayer->sendPacket( &gcDI );

	pItem->destroy();
	SAFE_DELETE( pItem );

	/*
	 * 여기서 뭔가 확인을 해야 한다.
	 */

	int ratio = rand()%100;

	if ( g_pVariableManager->getVariable(PET_DAY_EVENT) != 0 )
	{
		ratio = 100;
	}

	// 공용 펫만 꼬실 수 있다.
	PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo(petType);
	if ( pPetTypeInfo == NULL || pPetTypeInfo->getOriginalMonsterType() != pMonster->getMonsterType() || ratio >= pPetFoodInfo->getTameRatio() )
	{
		//cout << "꼬시기 실패 : " << ratio << endl;
		SAFE_DELETE( pPetItem );
		pMonster->addEnemy( pPC );
		return;
	}

	pZone->deleteCreature( pMonster, pMonster->getX(), pMonster->getY() );
	SAFE_DELETE( pMonster );

	/*
	 * 여기서 해당 펫의 정보를 가져와야 된다.
	 */

	PetInfo* pPetInfo = new PetInfo;

	pPetInfo->setPetType( petType );
	pPetInfo->setPetLevel(0);
	pPetInfo->setPetCreatureType(pPetTypeInfo->getPetCreatureType(0));
	pPetInfo->setPetAttr(0xff);
	pPetInfo->setPetExp(0);
	pPetInfo->setPetAttrLevel(0);
	pPetInfo->setFoodType(pPetFoodInfo->getItemType());
	pPetInfo->setGamble(0);
	pPetInfo->setCutHead(0);
	pPetInfo->setPetHP(pPetFoodInfo->getPetHP());
	pPetInfo->setFeedTime( VSDateTime::currentDateTime() );

	// 양방향 링크
	pPetItem->setPetInfo( pPetInfo );
	pPetInfo->setPetItem( pPetItem );

	pZone->registerObject( pPetItem );
	pInventory->addItem( pPetItem, pt );
	Assert( pt.x != -1 );

	pPetItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

	// TraceLog 를 남긴다.
	remainTraceLog( pPetItem, "GOD", pPC->getName(), ITEM_LOG_CREATE, DETAIL_PICKUP );
	
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pPetItem, pt.x, pt.y );

	pGamePlayer->sendPacket( &gcCreateItem );

	pPetItem->whenPCTake( pPC );

	pPC->getGQuestManager()->tamePet(pPetInfo);
	addOlympicStat( pPC, 9 );

#endif

	__END_CATCH
}
