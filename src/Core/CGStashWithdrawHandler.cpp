//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashWithdrawHandler.cpp
// Written By  : ±è¼º¹Î
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStashWithdraw.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Item.h"
	#include "LogClient.h"

	#include "item/Money.h"

	#include "Gpackets/GCDeleteandPickUpOK.h"
	#include "Gpackets/GCDeleteObject.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGStashWithdrawHandler::execute (CGStashWithdraw* pPacket, Player* pPlayer)
	
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature* pPC		= dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Gold_t      amount      = pPacket->getAmount();

	if ( !pPC->checkGoldIntegrity() || !pPC->checkStashGoldIntegrity() )
	{
		filelog("GoldBug.log", "CGStashWithdraw : µ·ÀÌ DB¶û ¾È ¸Â´Â´Ù! [%s:%s]", pGamePlayer->getID().c_str(), pPC->getName().c_str() );
		throw DisconnectException("CGStashWithdraw : µ·ÀÌ DB¶û ¾È ¸Â´Â´Ù!");
	}

	if (amount == 0) return;

	if (pPC->isSlayer()) 
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);

		if (pSlayer->getStashGold() < amount)  return;

		if (pSlayer->getGold() + amount > MAX_MONEY)
		{
			Gold_t margin = MAX_MONEY - pSlayer->getGold();
			//pSlayer->setStashGoldEx(pSlayer->getStashGold() - margin);
			//pSlayer->setGoldEx(pSlayer->getGold() + margin);

			// by sigi. 2002.9.4
			pSlayer->decreaseStashGoldEx(margin);
			pSlayer->increaseGoldEx(margin);

			log(LOG_STASH_REMOVE_MONEY, pSlayer->getName(), "", itos(margin));
		}
		else
		{
			//pSlayer->setStashGoldEx(pSlayer->getStashGold() - amount);
			//pSlayer->setGoldEx(pSlayer->getGold() + amount);

			// by sigi. 2002.9.4
			pSlayer->decreaseStashGoldEx(amount);
			pSlayer->increaseGoldEx(amount);

			log(LOG_STASH_REMOVE_MONEY, pSlayer->getName(), "", itos(amount));
		}
	}
	else if (pPC->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);

		if (pVampire->getStashGold() < amount) return;

		if (pVampire->getGold() + amount > MAX_MONEY)
		{
			Gold_t margin = MAX_MONEY - pVampire->getGold();
			//pVampire->setStashGoldEx(pVampire->getStashGold() - margin);
			//pVampire->setGoldEx(pVampire->getGold() + margin);

			// by sigi. 2002.9.18
			pVampire->decreaseStashGoldEx(margin);
			pVampire->increaseGoldEx(margin);

			log(LOG_STASH_REMOVE_MONEY, pVampire->getName(), "", itos(margin));
		}
		else
		{
			//pVampire->setStashGoldEx(pVampire->getStashGold() - amount);
			//pVampire->setGoldEx(pVampire->getGold() + amount);

			// by sigi. 2002.9.18
			pVampire->decreaseStashGoldEx(amount);
			pVampire->increaseGoldEx(amount);

			log(LOG_STASH_REMOVE_MONEY, pVampire->getName(), "", itos(amount));
		}
	}
	else if (pPC->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);

		if (pOusters->getStashGold() < amount) return;

		if (pOusters->getGold() + amount > MAX_MONEY)
		{
			Gold_t margin = MAX_MONEY - pOusters->getGold();
			//pOusters->setStashGoldEx(pOusters->getStashGold() - margin);
			//pOusters->setGoldEx(pOusters->getGold() + margin);

			// by sigi. 2002.9.18
			pOusters->decreaseStashGoldEx(margin);
			pOusters->increaseGoldEx(margin);

			log(LOG_STASH_REMOVE_MONEY, pOusters->getName(), "", itos(margin));
		}
		else
		{
			//pOusters->setStashGoldEx(pOusters->getStashGold() - amount);
			//pOusters->setGoldEx(pOusters->getGold() + amount);

			// by sigi. 2002.9.18
			pOusters->decreaseStashGoldEx(amount);
			pOusters->increaseGoldEx(amount);

			log(LOG_STASH_REMOVE_MONEY, pOusters->getName(), "", itos(amount));
		}
	}

#endif	// __GAME_SERVER__

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}



