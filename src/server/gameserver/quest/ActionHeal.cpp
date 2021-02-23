////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionHeal.cpp
// Written By  : 
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "ActionHeal.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "GamePlayer.h"
#include "Zone.h"
#include "DB.h"
#include "LogClient.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCStatusCurrentHP.h"

#include "EffectAftermath.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionHeal::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionHeal::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Zone*   pZone   = pCreature2->getZone();
	
	Assert(pPlayer != NULL);

	// 일단 클라이언트를 위해서 OK 패킷을 함 날린다.
	GCNPCResponse okpkt;
	okpkt.setCode(NPC_RESPONSE_HEAL);
	pPlayer->sendPacket(&okpkt);

	// 죽었거나 코마 걸려있으면 안 치료해준다.
	if ( pCreature2->isDead() || pCreature2->isFlag( Effect::EFFECT_CLASS_COMA ) )
	{
		return;
	}

	// 슬레이어라면...
	if (pCreature2->isSlayer())
	{
		Slayer*             pSlayer        = dynamic_cast<Slayer*>(pCreature2);
		EffectManager*      pEffectManager = pSlayer->getEffectManager();
		GCModifyInformation modifyPkt;
		GCRemoveEffect      removePkt;
		GCStatusCurrentHP   hpPkt;

		// 먼저 HP랑 MP를 풀로 채워준다.
		if (pSlayer->getHP(ATTR_CURRENT) < pSlayer->getHP(ATTR_MAX))
		{
			pSlayer->setHP(pSlayer->getHP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_HP, pSlayer->getHP(ATTR_CURRENT));

			hpPkt.setObjectID(pSlayer->getObjectID());
			hpPkt.setCurrentHP(pSlayer->getHP(ATTR_CURRENT));
		}
		if (pSlayer->getMP(ATTR_CURRENT) < pSlayer->getMP(ATTR_MAX))
		{
			pSlayer->setMP(pSlayer->getMP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_MP, pSlayer->getMP(ATTR_CURRENT));
		}

		// 흡혈 이펙트를 삭제한다.
		Effect* pBloodDrainEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		if (pBloodDrainEffect != NULL)
		{
			// DB에서 삭제하고, 이펙트 매니저에서 삭제한다.
			pBloodDrainEffect->destroy(pSlayer->getName());
			pEffectManager->deleteEffect(pSlayer, Effect::EFFECT_CLASS_BLOOD_DRAIN);

			// 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
			if (pSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
			{
				Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
				EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
				pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
			}
			else
			{
				EffectAftermath* pEffectAftermath = new EffectAftermath(pSlayer);
				pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
				pEffectManager->addEffect(pEffectAftermath);
				pSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
				pEffectAftermath->create(pSlayer->getName());
			}

			// 패킷에다 정보를 더한다.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);

			// 흡혈을 치료하면 능력치가 변화하게 된다.
			SLAYER_RECORD prev;
			pSlayer->getSlayerRecord(prev);
			pSlayer->initAllStat();
			pSlayer->sendModifyInfo(prev);
			pSlayer->sendRealWearingInfo();
		}

		// 독 이펙트를 삭제한다.
		Effect* pEffectPoison = pEffectManager->findEffect(Effect::EFFECT_CLASS_POISON);
		if (pEffectPoison != NULL)
		{
			// 이펙트 매니저에서 삭제한다.
			pEffectManager->deleteEffect(pSlayer, Effect::EFFECT_CLASS_POISON);

			// 패킷에다 정보를 더한다.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_POISON);
		}

		// 다크블루 포이즌 이펙트를 삭제한다.
		Effect* pEffectDarkBluePoison = pEffectManager->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON);
		if (pEffectDarkBluePoison != NULL)
		{
			// 이펙트 매니저에서 삭제한다.
			pEffectManager->deleteEffect(pSlayer, Effect::EFFECT_CLASS_DARKBLUE_POISON);

			// 패킷에다 정보를 더한다.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_DARKBLUE_POISON);
		}

		// 패킷 날려준다.
		removePkt.setObjectID(pSlayer->getObjectID());
		pPlayer->sendPacket(&modifyPkt);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &removePkt);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &hpPkt, pSlayer);

		log(LOG_HEAL, pSlayer->getName(), "");
	}
	else if (pCreature2->isVampire())
	{
		Vampire*            pVampire = dynamic_cast<Vampire*>(pCreature2);
		//EffectManager*      pEffectManager = pVampire->getEffectManager();
		GCModifyInformation modifyPkt;
		GCRemoveEffect      removePkt;
		GCStatusCurrentHP   hpPkt;

		// HP 채워주고...
		if (pVampire->getHP(ATTR_CURRENT) < pVampire->getHP(ATTR_MAX))
		{
			pVampire->setHP(pVampire->getHP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_HP, pVampire->getHP(ATTR_CURRENT));

			hpPkt.setObjectID(pVampire->getObjectID());
			hpPkt.setCurrentHP(pVampire->getHP(ATTR_CURRENT));
		}

		// 패킷 날려준다.
		removePkt.setObjectID(pVampire->getObjectID());
		pPlayer->sendPacket(&modifyPkt);
		pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &removePkt);
		pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &hpPkt, pVampire);

		log(LOG_HEAL, pVampire->getName(), "");
	}
	else if (pCreature2->isOusters())
	{
		Ousters*             pOusters        = dynamic_cast<Ousters*>(pCreature2);
		EffectManager*      pEffectManager = pOusters->getEffectManager();
		GCModifyInformation modifyPkt;
		GCRemoveEffect      removePkt;
		GCStatusCurrentHP   hpPkt;

		// 먼저 HP랑 MP를 풀로 채워준다.
		if (pOusters->getHP(ATTR_CURRENT) < pOusters->getHP(ATTR_MAX) || pOusters->getSilverDamage() != 0 )
		{
			Silver_t prev = pOusters->getSilverDamage();

			if ( prev != 0 )
			{
				pOusters->setSilverDamage(0);
				modifyPkt.addShortData(MODIFY_SILVER_DAMAGE, pOusters->getSilverDamage());
			}

			pOusters->setHP(pOusters->getHP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_HP, pOusters->getHP(ATTR_CURRENT));

			hpPkt.setObjectID(pOusters->getObjectID());
			hpPkt.setCurrentHP(pOusters->getHP(ATTR_CURRENT));
		}
		if (pOusters->getMP(ATTR_CURRENT) < pOusters->getMP(ATTR_MAX))
		{
			pOusters->setMP(pOusters->getMP(ATTR_MAX), ATTR_CURRENT);
			modifyPkt.addShortData(MODIFY_CURRENT_MP, pOusters->getMP(ATTR_CURRENT));
		}

		// 독 이펙트를 삭제한다.
		Effect* pEffectPoison = pEffectManager->findEffect(Effect::EFFECT_CLASS_POISON);
		if (pEffectPoison != NULL)
		{
			// 이펙트 매니저에서 삭제한다.
			pEffectManager->deleteEffect(pOusters, Effect::EFFECT_CLASS_POISON);

			// 패킷에다 정보를 더한다.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_POISON);
		}

		// 다크블루 포이즌 이펙트를 삭제한다.
		Effect* pEffectDarkBluePoison = pEffectManager->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON);
		if (pEffectDarkBluePoison != NULL)
		{
			// 이펙트 매니저에서 삭제한다.
			pEffectManager->deleteEffect(pOusters, Effect::EFFECT_CLASS_DARKBLUE_POISON);

			// 패킷에다 정보를 더한다.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_DARKBLUE_POISON);
		}

		// 흡혈 이펙트를 삭제한다.
		Effect* pBloodDrainEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		if (pBloodDrainEffect != NULL)
		{
			pBloodDrainEffect->setDeadline(0);

			// 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
			if (pOusters->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
			{
				Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
				EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
				pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
			}
			else
			{
				EffectAftermath* pEffectAftermath = new EffectAftermath(pOusters);
				pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
				pEffectManager->addEffect(pEffectAftermath);
				pOusters->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
				pEffectAftermath->create(pOusters->getName());
			}

			// 패킷에다 정보를 더한다.
			removePkt.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);
		}


		// 패킷 날려준다.
		removePkt.setObjectID(pOusters->getObjectID());
		pPlayer->sendPacket(&modifyPkt);
		pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &removePkt);
		pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &hpPkt, pOusters);

		log(LOG_HEAL, pOusters->getName(), "");

	}
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
string ActionHeal::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionHeal("
	    << ")";
	return msg.toString();

	__END_CATCH
}
