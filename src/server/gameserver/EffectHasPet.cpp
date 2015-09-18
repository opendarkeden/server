//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasPet.cpp
// Written by  : 쉭
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectHasPet.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "PetInfo.h"
#include "CreatureUtil.h"
#include "PetExpInfo.h"
#include "PetUtil.h"
#include "types/PetTypes.h"
#include "GCAddEffect.h"
#include "GCRemoveEffect.h"
#include "GCModifyInformation.h"
#include "PetItem.h"
#include "VSDateTime.h"
#include "VariableManager.h"

#include <cstdio>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHasPet::EffectHasPet(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasPet::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	affect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasPet::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if (pCreature == NULL || !pCreature->isPC() ) return;

	VSDateTime currentTime = VSDateTime::currentDateTime();
	setNextTime(600);
	setDeadline(999999);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPC->getPlayer());
	Assert(pGamePlayer != NULL);

	list<PetItem*>::iterator itr = pPC->getPetItems().begin();
	list<PetItem*>::iterator endItr = pPC->getPetItems().end();

	for (; itr != endItr ; ++itr )
	{
		PetItem* pPetItem = *itr;
		if (pPetItem == NULL ) continue;

		PetInfo* pPetInfo = pPetItem->getPetInfo();

		if (pPetInfo == NULL )
		{
			filelog("PetBug.log", "EffectHasPet failed, character %s has no pet.", pPC->getName().c_str());
			continue;
		}

		PetHP_t PetHP = pPetInfo->getPetHP();
		if (PetHP == 0 )
		{
			continue;
		}

		int secsLast = pPetInfo->getLastFeedTime().secsTo(currentTime);

		// 50레벨 펫은 10분에 한번씩 밥먹는다.
		if (pPetInfo->getPetLevel() == 50 && secsLast < 600 ) continue;

		pPetInfo->setCurrentFeedTurn(pPetInfo->getCurrentFeedTurn() + 1);

		// 가끔 밥먹인다.
		if (pPetInfo->getCurrentFeedTurn() >= pPetInfo->getFeedTurn() )
		{
			pPetInfo->setCurrentFeedTurn(0);

			pPetInfo->setPetHP(PetHP-1);
			pPetInfo->setFeedTime(currentTime);

			if (pPetInfo->getPetHP() == 0)
			{
				filelog("Pet.log", "%s\'s pet died.", pPC->getName().c_str());
				if (pPC->getPetInfo() == pPetInfo) {
					pPC->setPetInfo(NULL);
					pPC->initAllStatAndSend();
					sendPetInfo(pGamePlayer, true, false);
				}
			}
		}

		if (pPC->getPetInfo() == pPetInfo )
		{
			PetExp_t exp = 20;

			if (!pGamePlayer->isPayPlaying() ) exp = 12;

			exp = getPercentValue(exp, g_pVariableManager->getPetExpRatio());

			if (increasePetExp(pPetInfo, exp ) )
				sendPetInfo(pGamePlayer, true, false);
			else
			{
				GCModifyInformation gcMI;
				gcMI.addLongData(MODIFY_PET_EXP, pPetInfo->getPetExp());
				gcMI.addShortData(MODIFY_PET_HP, pPetInfo->getPetHP());

				pGamePlayer->sendPacket(&gcMI);
			}

			addOlympicStat(pPC, 8, exp);
		}

		char query[100];
		sprintf(query, "PetHP=%u, LastFeedTime='%s', PetExp=%u", pPetInfo->getPetHP(), currentTime.toDateTime().c_str(), pPetInfo->getPetExp());
		pPetInfo->getPetItem()->tinysave(query);
	}

	__END_CATCH
}

void EffectHasPet::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHasPet::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature != NULL);

	// 능력치를 정상적으로 되돌리기 위해서는 플래그를 끄고,
	// initAllStat을 불러야 한다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_HAS_PET);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_HAS_PET);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHasPet::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectHasPet("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}
