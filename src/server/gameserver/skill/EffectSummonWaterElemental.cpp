//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSummonWaterElemental.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectSummonWaterElemental.h"
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
EffectSummonWaterElemental::EffectSummonWaterElemental(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	setTarget(pCreature);

	__END_CATCH
}

void EffectSummonWaterElemental::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCastCreature = dynamic_cast<Creature*>(m_pTarget);

	if ( pCastCreature == NULL || !pCastCreature->isOusters() || pCastCreature->isDead() ) return;

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

	SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo( SKILL_SUMMON_WATER_ELEMENTAL );
	OustersSkillSlot* pSkillSlot = pOusters->getSkill( SKILL_SUMMON_WATER_ELEMENTAL );

	bool bHitRoll = HitRoll::isSuccessMagic( pOusters, pSkillInfo, pSkillSlot );

	if ( bHitRoll )
	{
		int HealPoint = getDamage();

		bool healed = false;

		int PartyID = pOusters->getPartyID();
		if (PartyID != 0)
		{
			// 파티에 가입되어 있다면 로컬 파티 매니저를 통해 
			// 주위의 파티원들과 경험치를 공유한다.
			LocalPartyManager* pLPM = pOusters->getLocalPartyManager();
			Assert(pLPM != NULL);
			healed = pLPM->shareWaterElementalHeal( PartyID, pOusters, HealPoint );
		}

		if ( pOusters->getHP(ATTR_MAX) != pOusters->getHP() )
		{
			GCModifyInformation gcMI;
			HP_t final = min( (int)pOusters->getHP(ATTR_MAX), pOusters->getHP() + HealPoint );
			if ( final > pOusters->getHP(ATTR_MAX) - pOusters->getSilverDamage() )
			{
				pOusters->setSilverDamage( pOusters->getHP(ATTR_MAX) - final );
				gcMI.addShortData(MODIFY_SILVER_DAMAGE, pOusters->getSilverDamage());
			}

			if ( pOusters->getHP() != final )
			{
				pOusters->setHP( final );
				gcMI.addShortData(MODIFY_CURRENT_HP, final);
			}

			GCStatusCurrentHP gcHP;
			gcHP.setObjectID( pOusters->getObjectID() );
			gcHP.setCurrentHP( final );

			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcHP);
			
			pOusters->getPlayer()->sendPacket( &gcMI );

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pOusters->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_WATER_ELEMENTAL_HEALED);
			gcAddEffect.setDuration(0);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcAddEffect);

			healed = true;
		}

		if ( healed )
		{
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID( pOusters->getObjectID() );
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_WATER_ELEMENTAL_HEAL);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcAddEffect);
		}
	}

	setNextTime( 20 );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSummonWaterElemental::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectSummonWaterElemental" << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isOusters());

	// 플래그를 끈다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_WATER_ELEMENTAL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	Ousters* pTargetOusters = dynamic_cast<Ousters*>(pCreature);
	Assert( pTargetOusters != NULL );

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_WATER_ELEMENTAL);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectSummonWaterElemental" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectSummonWaterElemental::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectSummonWaterElemental::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectSummonWaterElemental("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}

