//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSummonFireElemental.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSummonFireElemental.h"
#include "Ousters.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "SkillUtil.h"
#include "HitRoll.h"
#include "SkillInfo.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCAddEffectToTile.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectSummonFireElemental::EffectSummonFireElemental(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

void EffectSummonFireElemental::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCastCreature = dynamic_cast<Creature*>(m_pTarget);

	if ( pCastCreature == NULL || !pCastCreature->isOusters() ) return;

	Ousters* pOusters = dynamic_cast<Ousters*>(pCastCreature);
	Assert( pOusters != NULL );

	Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
	if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
	{
		// 중간에 리스틀릿을 빼버리면 이펙트도 사라진다.
		setDeadline(0);
		return;
	}

	Player* pPlayer = dynamic_cast<Player*>(pCastCreature->getPlayer());
	Assert( pPlayer != NULL );

	Zone* pZone = pCastCreature->getZone();
	Assert( pZone != NULL );

	ObjectID_t targetObjectID = pOusters->getLastTarget();
	if ( targetObjectID == 0 )
	{
		setNextTime(20);
		return;
	}

	Creature* pTargetCreature = pZone->getCreature( targetObjectID );

	if ( pTargetCreature == NULL || pTargetCreature->isDead() || pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) )
	{
		pOusters->setLastTarget(0);
		setNextTime(20);
		return;
	}

	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo( SKILL_SUMMON_FIRE_ELEMENTAL );
	OustersSkillSlot* pSkillSlot = pOusters->getSkill( SKILL_SUMMON_FIRE_ELEMENTAL );

	bool bRaceCheck = pTargetCreature->isSlayer() || pTargetCreature->isVampire() || pTargetCreature->isMonster();
	bool bRangeCheck = verifyDistance( pOusters, pTargetCreature, getRange() );
	bool bHitRoll = HitRoll::isSuccessMagic( pOusters, pSkillInfo, pSkillSlot ) && canAttack( pOusters, pTargetCreature );

	GCModifyInformation AttackerMI, TargetMI;

	if ( bRaceCheck && bRangeCheck && bHitRoll )
	{
		::setDamage( pTargetCreature, getDamage(), pOusters, SKILL_SUMMON_FIRE_ELEMENTAL, &TargetMI, &AttackerMI );
		computeAlignmentChange(pTargetCreature, getDamage(), pOusters, &TargetMI, &AttackerMI);
		decreaseDurability(pOusters, pTargetCreature, pSkillInfo, &TargetMI, &AttackerMI);

		if (pTargetCreature->isDead())
		{
			int exp = computeCreatureExp(pTargetCreature, 100, pOusters);
			shareOustersExp(pOusters, exp, AttackerMI);
		}

		increaseAlignment(pOusters, pTargetCreature, AttackerMI);

		GCAddEffect gcAttackerEffect, gcTargetEffect;

		gcAttackerEffect.setObjectID( pOusters->getObjectID() );
		gcAttackerEffect.setEffectID( Effect::EFFECT_CLASS_FIRE_ELEMENTAL_ATTACK );
		gcAttackerEffect.setDuration( 0 );

		gcTargetEffect.setObjectID( pTargetCreature->getObjectID() );
		gcTargetEffect.setEffectID( Effect::EFFECT_CLASS_FIRE_ELEMENTAL_DAMAGED );
		gcTargetEffect.setDuration( 0 );

		pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcTargetEffect );
		pZone->broadcastPacket( pOusters->getX(), pOusters->getY(), &gcAttackerEffect );

		pPlayer->sendPacket( &AttackerMI );

		if ( pTargetCreature->isPC() )
		{
			pTargetCreature->getPlayer()->sendPacket( &TargetMI );
		}
	}

	setNextTime( 20 );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSummonFireElemental::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectSummonFireElemental" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	// 플래그를 끈다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_FIRE_ELEMENTAL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
	Assert( pTargetOusters != NULL );

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_FIRE_ELEMENTAL);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectSummonFireElemental" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSummonFireElemental::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSummonFireElemental::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSummonFireElemental("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

