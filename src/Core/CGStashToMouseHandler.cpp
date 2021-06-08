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

	#include "GCCannotAdd.h"
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

	// �ƽ� ������ �ʰ��ϴ� �� ����
	// �ڱⰡ ������ �ִ� �ִ����� ���� �ʰ��ص� ������.
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
	
	// �����Կ� �������� ���ų�, ���콺�� �������� �޷��ִ� ���
	// �������� ���콺�� �� �޾��� ���� ���� �� �ƴѰ�?
	if (pStashItem == NULL || pMouseItem != NULL)
	{
		//throw ProtocolException("CGStashToMouseHandler::executeSlayer() : �������� ���ų�, ���콺�� �������� �޷��ֽ��ϴ�.");
		// �������� �����ų�...���콺�� �������� �޷��־��� ��쿡�� ���� �� ����.
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

	// �����Կ��� �������� �����ϰ�, ���콺���� �޾��� �� DB���� ����.
	pStash->remove(rack, index);
	pPC->addItemToExtraInventorySlot(pStashItem);
//	pStashItem->whenPCTake(pPC);
	//pStashItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
	// ������ ���� ����ȭ. by sigi. 2002.5.13
	char pField[80];
	sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
	pStashItem->tinysave(pField);


	log(LOG_STASH_REMOVE_ITEM, pPC->getName(), "", pStashItem->toString());
	
#endif	// __GAME_SERVER__

    __END_DEBUG
	__END_DEBUG_EX __END_CATCH
}

