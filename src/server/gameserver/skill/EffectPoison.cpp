//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPoison.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectPoison.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "DB.h"
#include "Player.h"
#include "SkillUtil.h"

#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectPoison::EffectPoison(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_UserObjectID = 0;
	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::affect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectPoison " << "begin begin" << endl;

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	//cout << "EffectPoison " << "begin end" << endl;

	__END_CATCH 

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectPoison " << "begin" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 스킬 사용자를 가져온다.
	// !! 이미 존을 나갔을 수 있으므로 NULL이 될 수 있다.
	// by bezz. 2003.1.4
	Creature* pCastCreature = pZone->getCreature(m_UserObjectID);

	// EffectPoison이 크리쳐에게 걸리게 되는 경우에는 현재로서는 
	// GreenPoison에 의해 타일 위에 생긴 
	// EffectGreenPoison 위를 플레이어가 지나갈 때 뿐이다.
	// EffectGreenPoison 내부에서 저항을 고려해서 데미지를 세팅한 다음
	// EffectPoison을 붙이므로, 내부에서 한번 더 계산하면 안된다.
	//Damage_t PoisonDamage = computeMagicDamage(pCreature, m_Point, MAGIC_DOMAIN_POISON, m_Level);
	Damage_t PoisonDamage = m_Point;

	if (!(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE)
		// 무적상태 체크. by sigi. 2002.9.5
		&& canAttack(pCastCreature, pCreature )
		)
	{
		if (pCreature->isSlayer())
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

			GCModifyInformation gcMI;
			::setDamage(pSlayer, PoisonDamage, pCastCreature, SKILL_GREEN_POISON, &gcMI);
			pSlayer->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			GCModifyInformation gcMI;
			::setDamage(pVampire, PoisonDamage, pCastCreature, SKILL_GREEN_POISON, &gcMI);
			pVampire->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			GCModifyInformation gcMI;
			::setDamage(pOusters, PoisonDamage, pCastCreature, SKILL_GREEN_POISON, &gcMI);
			pOusters->getPlayer()->sendPacket(&gcMI);
		}
		else if (pCreature->isMonster())
		{
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			::setDamage(pMonster, PoisonDamage, pCastCreature, SKILL_GREEN_POISON);
		}

		// m_CasterName이 pCreature를 죽인 경우의 KillCount 처리
		// by sigi. 2002.9.9
/*		if (pCreature->isDead())
		{
			Creature* pAttacker = pZone->getCreature(m_UserObjectID);

			if (pAttacker!=NULL)
			{ 
				affectKillCount(pAttacker, pCreature);
			}
		}*/
	}
	
	setNextTime(m_Tick);

	//cout << "EffectPoison " << "end" << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	pCreature->removeFlag(Effect::EFFECT_CLASS_POISON);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_POISON);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectPoison::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectPoison::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectPoison("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

