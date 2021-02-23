//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashListHandler.cpp
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStashList.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Stash.h"

	#include "Gpackets/GCStashList.h"
#endif

void CGStashListHandler::execute(CGStashList* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	ObjectID_t  PlayerOID   = pPacket->getObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();

	// 패킷에서의 object id와 PC의 object id가 다르면 안 되지.
	if (PlayerOID != pPC->getObjectID()) return;

	if (pPC->isSlayer())
	{
		Slayer*     pSlayer = dynamic_cast<Slayer*>(pPC);
		Stash*      pStash  = pSlayer->getStash();
		Item*       pItem   = NULL;
		GCStashList pkt;

		pkt.setStashNum(pSlayer->getStashNum());
		for (BYTE r=0; r<pSlayer->getStashNum(); r++)
		{
			for (BYTE i=0; i<STASH_INDEX_MAX; i++)
			{
				pItem = pStash->get(r, i);
				if (pItem != NULL) pkt.setStashItem(r, i, pItem);
			}
		}
		pkt.setStashGold(pSlayer->getStashGold());
		pPlayer->sendPacket(&pkt);
	}
	else if (pPC->isVampire())
	{
		Vampire*    pVampire = dynamic_cast<Vampire*>(pPC);
		Stash*      pStash = pVampire->getStash();
		Item*       pItem  = NULL;
		GCStashList pkt;

		pkt.setStashNum(pVampire->getStashNum());
		for (BYTE r=0; r<pVampire->getStashNum(); r++)
		{
			for (BYTE i=0; i<STASH_INDEX_MAX; i++)
			{
				pItem = pStash->get(r, i);
				if (pItem != NULL) pkt.setStashItem(r, i, pItem);
			}
		}
		pkt.setStashGold(pVampire->getStashGold());
		pPlayer->sendPacket(&pkt);
	}
	else if (pPC->isOusters())
	{
		Ousters*    pOusters = dynamic_cast<Ousters*>(pPC);
		Stash*      pStash = pOusters->getStash();
		Item*       pItem  = NULL;
		GCStashList pkt;

		pkt.setStashNum(pOusters->getStashNum());
		for (BYTE r=0; r<pOusters->getStashNum(); r++)
		{
			for (BYTE i=0; i<STASH_INDEX_MAX; i++)
			{
				pItem = pStash->get(r, i);
				if (pItem != NULL) pkt.setStashItem(r, i, pItem);
			}
		}
		pkt.setStashGold(pOusters->getStashGold());
		pPlayer->sendPacket(&pkt);
	}

#endif

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
