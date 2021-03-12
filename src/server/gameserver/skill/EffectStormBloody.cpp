//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStormBloody.cpp
// Written by  : 장홍창
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectStormBloody.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillUtil.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectStormBloody::EffectStormBloody(Creature* pCreature)
	
{
	__BEGIN_TRY

	m_UserObjectID=0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormBloody::affect()
	
{
	__BEGIN_TRY

	//cout << "EffectStormBloody " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectStormBloody " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormBloody::affect(Creature* pCreature)
	
{
	__BEGIN_TRY

	//cout << "EffectStormBloody " << "begin" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 사용자를 가져온다.
	// !! 이미 존을 나갔을 수 있으므로 NULL이 될 수 있다.
	// by bezz. 2003.3.13
	Creature* pCastCreature = pZone->getCreature( m_UserObjectID );
	// 캐스터가 없으면 무시한다.
	if ( pCastCreature == NULL )
		return;

	// EffectStormBloody은 AcidStorm, PoisonStorm, BloodyStorm위를 지나갈때 붙는다.
	// 이는 3번의 연속 데미지를 주고 사라진다.

	Damage_t StormDamage = m_Point;
	GCModifyInformation GCAttackerMI;

	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		// 무적상태 체크. by sigi. 2002.9.5
		&& canAttack( pCastCreature, pCreature )
		)
	{
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pSlayer, StormDamage, pCastCreature, SKILL_BLOODY_STORM, &gcMI, &GCAttackerMI );

			pSlayer->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pVampire, StormDamage, pCastCreature, SKILL_BLOODY_STORM, &gcMI, &GCAttackerMI );

			pVampire->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			GCModifyInformation gcMI;
			setDamage( pOusters, StormDamage, pCastCreature, SKILL_BLOODY_STORM, &gcMI, &GCAttackerMI );

			pOusters->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isMonster())
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			setDamage( pMonster, StormDamage, pCastCreature, SKILL_BLOODY_STORM, NULL, &GCAttackerMI );
		}

		if ( pCastCreature->isVampire() && pCreature->isDead() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCastCreature);
			int exp = computeCreatureExp(pCreature, KILL_EXP);
			shareVampExp(pVampire, exp, GCAttackerMI);
			pVampire->getPlayer()->sendPacket( &GCAttackerMI );
		}

		// m_CasterName이 pCreature를 죽인 경우의 KillCount 처리
		// by sigi. 2002.9.9
		// setDamage 를 불러서 처리한다. 주석처리
		// by bezz. 2002.12.31
/*		if (pCreature->isDead())
		{
			Creature* pAttacker = pZone->getCreature( m_UserObjectID );

			if (pAttacker!=NULL)
			{ 
				affectKillCount(pAttacker, pCreature);
			}
		}*/
	}
	
	setNextTime(m_Tick);

	//cout << "EffectStormBloody " << "end" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormBloody::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormBloody::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	pCreature->removeFlag(Effect::EFFECT_CLASS_STORM_BLOODY);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_STORM_BLOODY);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormBloody::unaffect()
	
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectStormBloody::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectStormBloody::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectStormBloody("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

