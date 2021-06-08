//////////////////////////////////////////////////////////////////////////////
// Filename    : CGStashDepositHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGStashDeposit.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Item.h"
	#include "LogClient.h"
	#include "Utility.h"

	#include "item/Money.h"

	#include "GCDeleteandPickUpOK.h"
	#include "GCDeleteObject.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGStashDepositHandler::execute (CGStashDeposit* pPacket, Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	PlayerCreature* pPC		= dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Gold_t      amount      = pPacket->getAmount();

	if ( !pPC->checkGoldIntegrity() || !pPC->checkStashGoldIntegrity() )
	{
		filelog("GoldBug.log", "CGStashDeposit : ���� DB�� �� �´´�! [%s:%s]", pGamePlayer->getID().c_str(), pPC->getName().c_str() );
		throw DisconnectException("CGStashDeposit : ���� DB�� �� �´´�!");
	}


	if (amount == 0) return;

	if (pPC->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);

		if (pSlayer->getGold() < amount)  return;

		// �����Կ� �� �� �ִ� ������ ���� ���� ���� ������ �Ѵٸ�
		// �Ϻθ� �ְ�, �������� �� �÷��̾�� ���ܳ��ƾ� �Ѵ�.
		if (pSlayer->getStashGold() + amount > MAX_MONEY)
		{
			Gold_t margin = MAX_MONEY - pSlayer->getStashGold();
			//pSlayer->setGoldEx(pSlayer->getGold() - margin);
			//pSlayer->setStashGoldEx(pSlayer->getStashGold() + margin);
			// by sigi. 2002.9.4
			pSlayer->decreaseGoldEx(margin);
			pSlayer->increaseStashGoldEx(margin);

			log(LOG_STASH_ADD_MONEY, pSlayer->getName(), "", itos(margin));
		}
		else
		{
			//pSlayer->setGoldEx(pSlayer->getGold() - amount);
			//pSlayer->setStashGoldEx(pSlayer->getStashGold() + amount);
			// by sigi. 2002.9.4
			pSlayer->decreaseGoldEx(amount);
			pSlayer->increaseStashGoldEx(amount);

			log(LOG_STASH_ADD_MONEY, pSlayer->getName(), "", itos(amount));
		}
	}
	else if (pPC->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);

		if (pVampire->getGold() < amount) return;

		if (pVampire->getStashGold() + amount > MAX_MONEY)
		{
			Gold_t margin = MAX_MONEY - pVampire->getStashGold();
			//pVampire->setGoldEx(pVampire->getGold() - margin);
			//pVampire->setStashGoldEx(pVampire->getStashGold() + margin);
			pVampire->decreaseGoldEx(margin);
			pVampire->increaseStashGoldEx(margin);

			log(LOG_STASH_ADD_MONEY, pVampire->getName(), "", itos(margin));
		}
		else
		{
			//pVampire->setGoldEx(pVampire->getGold() - amount);
			//pVampire->setStashGoldEx(pVampire->getStashGold() + amount);
			pVampire->decreaseGoldEx(amount);
			pVampire->increaseStashGoldEx(amount);

			log(LOG_STASH_ADD_MONEY, pVampire->getName(), "", itos(amount));
		}
	}
	else if (pPC->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);

		if (pOusters->getGold() < amount) return;

		if (pOusters->getStashGold() + amount > MAX_MONEY)
		{
			Gold_t margin = MAX_MONEY - pOusters->getStashGold();
			//pOusters->setGoldEx(pOusters->getGold() - margin);
			//pOusters->setStashGoldEx(pOusters->getStashGold() + margin);
			pOusters->decreaseGoldEx(margin);
			pOusters->increaseStashGoldEx(margin);

			log(LOG_STASH_ADD_MONEY, pOusters->getName(), "", itos(margin));
		}
		else
		{
			//pOusters->setGoldEx(pOusters->getGold() - amount);
			//pOusters->setStashGoldEx(pOusters->getStashGold() + amount);
			pOusters->decreaseGoldEx(amount);
			pOusters->increaseStashGoldEx(amount);

			log(LOG_STASH_ADD_MONEY, pOusters->getName(), "", itos(amount));
		}
	}

#endif	// __GAME_SERVER__

	__END_DEBUG_EX __END_CATCH
}



