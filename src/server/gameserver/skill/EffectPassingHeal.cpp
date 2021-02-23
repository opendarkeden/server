//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPassingHeal.cpp
// Written by  : excel96
// Description : PassingHeal에 의해서 생성되는 산성 데미지 약화 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#include "EffectPassingHeal.h"
#include "Creature.h"
#include "Zone.h"
#include "Player.h"
#include "HitRoll.h"
#include "EffectAftermath.h"
#include "EffectDoom.h"
#include "EffectBlunting.h"
#include "EffectParalyze.h"
#include "EffectSeduction.h"
#include "EffectPoison.h"
#include "EffectYellowPoisonToCreature.h"
#include "EffectDarkBluePoison.h"
#include "EffectGreenStalker.h"
#include "EffectBloodDrain.h"
#include "Slayer.h"
#include "ZoneUtil.h"

#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCChangeDarkLight.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCStatusCurrentHP.h"

TPOINT PassingHealSearchTiles[] = 
{
	{ 0,-1},
	{ 1,-1},
	{ 1, 0},
	{ 1, 1},
	{ 0, 1},
	{-1, 1},
	{-1, 0},
	{-1,-1},
	{ 0,-2},
	{ 1,-2},
	{ 2,-2},
	{ 2,-1},
	{ 2, 0},
	{ 2, 1},
	{ 2, 2},
	{ 1, 2},
	{ 0, 2},
	{-1, 2},
	{-2, 2},
	{-2, 1},
	{-2, 0},
	{-2,-1},
	{-2,-2},
	{-1,-2},
	{255,255}
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPassingHeal::EffectPassingHeal(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_PassingCount = 0;
	m_CureCount = 0;
	m_HealPoint = 0;

	__END_CATCH
}

void EffectPassingHeal::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pTargetCreature = dynamic_cast<Creature*>(m_pTarget);
	if ( pTargetCreature != NULL ) affect( pTargetCreature );

	__END_CATCH
}

void EffectPassingHeal::affect(Creature* pTargetCreature)
	throw(Error)
{
	__BEGIN_TRY

	setDeadline(0);
	if ( pTargetCreature == NULL ) return;

	cout << "affect passing heal : " << pTargetCreature->getName() << endl;

	Zone* pZone = pTargetCreature->getZone();

	GCModifyInformation gcMI;
	GCSkillToObjectOK5 _GCSkillToObjectOK5;

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pTargetCreature->getObjectID());

	EffectBloodDrain* pEffectBloodDrain = NULL;

	if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
	{
		Effect* pEffect = pTargetCreature->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		pEffectBloodDrain = dynamic_cast<EffectBloodDrain*>(pEffect);
		Assert(pEffectBloodDrain != NULL);
	}

	bool bDoom      = false;
	bool bBlunting	= false;
	bool bParalyze  = false;
	bool bSeduction = false;

	EffectDoom*      pEffectDoom     = NULL;
	EffectBlunting*  pEffectBlunting = NULL;
	EffectParalyze*  pEffectParalyze = NULL;
	EffectSeduction* pEffectSeduction = NULL;

	// 저주 계열 해소
	if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_DOOM)) 
	{
		pEffectDoom = dynamic_cast<EffectDoom*>( pTargetCreature->findEffect(Effect::EFFECT_CLASS_DOOM) );
		Assert(pEffectDoom != NULL);

		bDoom = HitRoll::isSuccessRemoveCurse(50, 100, 10, pEffectDoom->getLevel(), 10);
	}
	if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_BLUNTING)) 
	{
		pEffectBlunting = dynamic_cast<EffectBlunting*>( pTargetCreature->findEffect(Effect::EFFECT_CLASS_BLUNTING) );
		Assert(pEffectBlunting != NULL);

		bBlunting = HitRoll::isSuccessRemoveCurse(50, 100, 15, pEffectBlunting->getLevel(), 10);
	}
	if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_PARALYZE)) 
	{
		pEffectParalyze = dynamic_cast<EffectParalyze*>( pTargetCreature->findEffect(Effect::EFFECT_CLASS_PARALYZE) );
		Assert(pEffectParalyze != NULL);

		bParalyze = HitRoll::isSuccessRemoveCurse(50, 100, 20, pEffectParalyze->getLevel(), 10);
	}
	if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_SEDUCTION)) 
	{
		pEffectSeduction = dynamic_cast<EffectSeduction*>( pTargetCreature->findEffect(Effect::EFFECT_CLASS_SEDUCTION) );
		Assert(pEffectSeduction != NULL);

		bSeduction = HitRoll::isSuccessRemoveCurse(50, 100, 30, pEffectSeduction->getLevel(), 10);
	}

	// 독 계열 해소
	bool bGreenPoison    = false; // GreenPoison을 치료할까의 여부
	bool bYellowPoison   = false; // YellowPoison을 치료할까의 여부
	bool bDarkBluePoison = false; // DarkBluePoison을 치료할까의 여부
	bool bGreenStalker   = false; // GreenStalker를 치료할까의 여부

	EffectPoison*                 pEffectPoison                 = NULL;
	EffectYellowPoisonToCreature* pEffectYellowPoisonToCreature = NULL;
	EffectDarkBluePoison*         pEffectDBP                   = NULL;
	EffectGreenStalker*           pEffectGreenStalker           = NULL;

	if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_POISON)) 
	{
		pEffectPoison = dynamic_cast<EffectPoison*>( pTargetCreature->findEffect(Effect::EFFECT_CLASS_POISON) );
		Assert(pEffectPoison != NULL);

		bGreenPoison = HitRoll::isSuccessCurePoison(50, 100, 10, pEffectPoison->getLevel(), 10);
	}

	if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
	{
		pEffectYellowPoisonToCreature = dynamic_cast<EffectYellowPoisonToCreature*>( pTargetCreature->findEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE) );
		Assert(pEffectYellowPoisonToCreature != NULL);

		bYellowPoison = HitRoll::isSuccessCurePoison(50, 100, 20, pEffectYellowPoisonToCreature->getLevel(), 10);
	}

	if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON)) 
	{
		pEffectDBP = dynamic_cast<EffectDarkBluePoison*>( pTargetCreature->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON) );
		Assert(pEffectDBP != NULL);

		bDarkBluePoison = HitRoll::isSuccessCurePoison(50, 100, 30, pEffectDBP->getLevel(), 10);
	}

	if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_GREEN_STALKER)) 
	{
		pEffectGreenStalker = dynamic_cast<EffectGreenStalker*>( pTargetCreature->findEffect(Effect::EFFECT_CLASS_GREEN_STALKER) );
		Assert(pEffectGreenStalker != NULL);

		bGreenStalker = HitRoll::isSuccessCurePoison(50, 100, 40, pEffectGreenStalker->getLevel(), 10);
	}

	int cureCount = 0;

	// 흡혈당한 상태라면 흡혈 상태를 날려준다.
	if (cureCount < m_CureCount && pEffectBloodDrain != NULL && pEffectBloodDrain->getLevel() < 150 && pTargetCreature->isSlayer())
	{
		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
		// 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
		if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
		{
				Effect* pEffect = pTargetCreature->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
				EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
				pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
		}
		else
		{
				EffectAftermath* pEffectAftermath = new EffectAftermath(pTargetCreature);
				pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
				pTargetCreature->addEffect(pEffectAftermath);
				pTargetCreature->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
				pEffectAftermath->create(pTargetCreature->getName());
		}

		pEffectBloodDrain->destroy(pTargetSlayer->getName());
		pTargetSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);

		SLAYER_RECORD prev;
		pTargetSlayer->getSlayerRecord(prev);
		pTargetSlayer->initAllStat();
		pTargetSlayer->sendRealWearingInfo();
		pTargetSlayer->addModifyInfo(prev, gcMI);

		gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);
		++cureCount;
	}

	if (cureCount < m_CureCount && bDoom)
	{
		pEffectDoom->setDeadline(0);
		pTargetCreature->removeFlag(Effect::EFFECT_CLASS_DOOM);
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DOOM);
		++cureCount;
	}
	if (cureCount < m_CureCount && bBlunting)
	{
		pEffectBlunting->setDeadline(0);
		pTargetCreature->removeFlag(Effect::EFFECT_CLASS_BLUNTING);
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_BLUNTING);
		++cureCount;
	}
	if (cureCount < m_CureCount && bParalyze)
	{
		pEffectParalyze->setDeadline(0);
		pTargetCreature->removeFlag(Effect::EFFECT_CLASS_PARALYZE);
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PARALYZE);
		++cureCount;
	}
	if (cureCount < m_CureCount && bSeduction)
	{
		pEffectSeduction->setDeadline(0);
		pTargetCreature->removeFlag(Effect::EFFECT_CLASS_SEDUCTION);
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SEDUCTION);
		++cureCount;
	}

	// 각각의 독마다 치료를 하고,
	// 패킷에다 이펙트 삭제하라고 더한다.
	if (cureCount < m_CureCount && bGreenPoison)
	{
		pEffectPoison->setDeadline(0);
		pTargetCreature->removeFlag(Effect::EFFECT_CLASS_POISON);
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_POISON);
		++cureCount;
	}
	if (cureCount < m_CureCount && bYellowPoison)
	{
		pEffectYellowPoisonToCreature->setDeadline(0);
		pTargetCreature->removeFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
		++cureCount;
	}
	if (cureCount < m_CureCount && bDarkBluePoison)
	{
		pEffectDBP->setDeadline(0);
		pTargetCreature->removeFlag(Effect::EFFECT_CLASS_DARKBLUE_POISON);
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DARKBLUE_POISON);
		++cureCount;
	}
	if (cureCount < m_CureCount && bGreenStalker)
	{
		pEffectGreenStalker->setDeadline(0);
		pTargetCreature->removeFlag(Effect::EFFECT_CLASS_GREEN_STALKER);
		gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_GREEN_STALKER);
		++cureCount;
	}

	if ( gcRemoveEffect.getListNum() > 0 )
	{
		pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcRemoveEffect );
	}

	if ( pTargetCreature->isSlayer() )
	{
		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);

		HP_t CurrentHP = pTargetSlayer->getHP(ATTR_CURRENT);
		HP_t MaxHP     = pTargetSlayer->getHP(ATTR_MAX);

		int healpoint	= min( m_HealPoint, MaxHP - CurrentHP );
		if ( healpoint > 0 )
		{
			pTargetSlayer->setHP( CurrentHP + healpoint, ATTR_CURRENT );
			GCStatusCurrentHP gcStatusCurrentHP;
			gcStatusCurrentHP.setObjectID( pTargetSlayer->getObjectID() );
			gcStatusCurrentHP.setCurrentHP(CurrentHP);
			pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcStatusCurrentHP);
			gcMI.addShortData(MODIFY_CURRENT_HP, CurrentHP);
		}
	}

	if ( pTargetCreature->isPC() ) pTargetCreature->getPlayer()->sendPacket( &gcMI );

	if ( m_PassingCount > 0 )
	for ( int i=0; i<24; ++i )
	{
		bool bAffected = false;
		if ( PassingHealSearchTiles[i].x == 255 ) break;
		ZoneCoord_t X = pTargetCreature->getX() + PassingHealSearchTiles[i].x;
		ZoneCoord_t Y = pTargetCreature->getY() + PassingHealSearchTiles[i].y;

		if ( !isValidZoneCoord( pZone, X, Y ) ) continue;
		Tile& rTile = pZone->getTile( X, Y );
		slist<Object*>& oList = rTile.getObjectList();

		slist<Object*>::iterator itr = oList.begin();
		for ( ; itr != oList.end() ; ++itr )
		{
			Object* pObject = *itr;
			if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;
			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			if ( pCreature != NULL && pCreature->isSlayer() && !pCreature->isFlag( Effect::EFFECT_CLASS_PASSING_HEAL ) )
			{
				EffectPassingHeal* pPassingHeal = new EffectPassingHeal( pCreature );
				pPassingHeal->setBroadcastingEffect(false);
				pPassingHeal->setNextTime(5);
				pPassingHeal->setPassingCount( m_PassingCount-1 );
				pPassingHeal->setCureCount( m_CureCount-1 );
				pPassingHeal->setHealPoint( m_HealPoint*0.8 );
				pCreature->addEffect( pPassingHeal );
				pCreature->setFlag( Effect::EFFECT_CLASS_PASSING_HEAL );

				if ( pTargetCreature->isPC() )
				{
					GCSkillToObjectOK1 OK1;
					OK1.setSkillType( SKILL_HEAL_PASS );
					OK1.setCEffectID( 0 );
					OK1.setTargetObjectID( pCreature->getObjectID() );
					OK1.setDuration( 0 );
					pTargetCreature->getPlayer()->sendPacket( &OK1 );
				}

				_GCSkillToObjectOK5.setSkillType( SKILL_HEAL_PASS );
				_GCSkillToObjectOK5.setObjectID( pTargetCreature->getObjectID() );
				_GCSkillToObjectOK5.setTargetObjectID( pCreature->getObjectID() );
				_GCSkillToObjectOK5.setDuration(0);

				list<Creature*> cList;
				cList.push_back( pTargetCreature );
				pZone->broadcastSkillPacket(pTargetCreature->getX(), pTargetCreature->getY(), pCreature->getX(), pCreature->getY(), &_GCSkillToObjectOK5, cList);

				bAffected = true;
				break;
			}
		}

		if ( bAffected ) break;
	}

	cout << "affected passing heal : " << pTargetCreature->getName() << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPassingHeal::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPassingHeal::unaffect()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG
	
	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	pCreature->removeFlag(Effect::EFFECT_CLASS_PASSING_HEAL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PASSING_HEAL);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	Player* pPlayer = pCreature->getPlayer();

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPassingHeal::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectPassingHeal("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

