//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashToMouseHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGStashToMouse.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "Stash.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "LogClient.h"

	#include "Gpackets/GCCannotAdd.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGStashToMouseHandler::execute (CGStashToMouse* pPacket , Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer*         pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*           pCreature   = pGamePlayer->getCreature();
	PlayerCreature*     pPC         = dynamic_cast<PlayerCreature*>(pCreature);
	BYTE                rack        = pPacket->getRack();
	BYTE                index       = pPacket->getIndex();

	// 맥스 범위를 초과하는 것 말고도
	// 자기가 가지고 있는 최대한의 랙을 초과해도 에러당.
	if (rack >= STASH_RACK_MAX || index >= STASH_INDEX_MAX || rack >= pPC->getStashNum())
    {
        GCCannotAdd _GCCannotAdd;
        _GCCannotAdd.setObjectID(pPacket->getObjectID());
        pPlayer->sendPacket(&_GCCannotAdd);
        return;
	}

	Stash* pStash     = pPC->getStash();
	Item*  pStashItem = pStash->get(rack , index);
	Item*  pMouseItem = pPC->getExtraInventorySlotItem();
	
	// 보관함에 아이템이 없거나, 마우스에 아이템이 달려있는 경우
	// 아이템을 마우스에 또 달아줄 수는 없는 것 아닌가?
	if (pStashItem == NULL || pMouseItem != NULL)
	{
		//throw ProtocolException("CGStashToMouseHandler::executeSlayer() : 아이템이 없거나, 마우스에 아이템이 달려있습니다.");
		// 아이템이 없었거나...마우스에 아이템이 달려있었을 경우에는 더할 수 없다.
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
		return;
	}
	
	ObjectID_t ObjectID = pStashItem->getObjectID();
	
	if (ObjectID != pPacket->getObjectID()) 
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
		return;
	}

	// 보관함에서 아이템을 제거하고, 마우스에다 달아준 후 DB에다 저장.
	pStash->remove(rack, index);
	pPC->addItemToExtraInventorySlot(pStashItem);
//	pStashItem->whenPCTake(pPC);
	//pStashItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
	// 아이템 저장 최적화. by sigi. 2002.5.13
	char pField[80];
	sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
	pStashItem->tinysave(pField);


	log(LOG_STASH_REMOVE_ITEM, pPC->getName(), "", pStashItem->toString());
	
#endif	// __GAME_SERVER__

    __END_DEBUG
	__END_DEBUG_EX __END_CATCH
}

