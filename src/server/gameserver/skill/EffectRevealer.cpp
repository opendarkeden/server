//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRevealer.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectRevealer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRevealer::EffectRevealer(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	// 디텍트 히든은 슬레이어만이 쓸 수 있다.
	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectRevealer " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	Assert(pCreature->isSlayer());

	// 플래그를 제거한다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_REVEALER);

	// 마법의 힘으로 보고 있던 크리쳐들을 삭제한다.
	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);
	pZone->updateMineScan(pCreature);
	// 이제 hidden도 본다.
	pZone->updateHiddenScan(pCreature);

	// 이펙트가 사라졌다고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_REVEALER);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	//cout << "EffectRevealer " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRevealer::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectRevealer::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectRevealer("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

bool EffectRevealer::canSeeHide( Creature* pTarget ) const
	throw( Error )
{
	if ( !pTarget->isFlag( Effect::EFFECT_CLASS_HIDE ) )
		return true;

	Level_t level;
	
	if ( pTarget->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pTarget);
		Assert( pVampire != NULL );

		level = pVampire->getLevel();
	}
	else if ( pTarget->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pTarget);
		Assert( pMonster != NULL );

		level = pMonster->getLevel();
	}
	else
	{
		throw Error( "뱀파이어나 몬스터가 아닌데 하이드하고 있다" );
	}

	if ( m_SkillLevel >= 25 && m_SkillLevel > level )
		return true;
	else
		return false;
}

bool EffectRevealer::canSeeSniping( Creature* pTarget ) const
	throw( Error )
{
	if ( !pTarget->isFlag( Effect::EFFECT_CLASS_SNIPING_MODE ) )
		return true;

	Assert( pTarget->isSlayer() );
	Slayer* pSlayer = dynamic_cast<Slayer*>(pTarget);

	ExpLevel_t level;

	SkillSlot* pSkillSlot = pSlayer->getSkill( SKILL_SNIPING );
	Assert( pSkillSlot != NULL );

	level = pSkillSlot->getExpLevel();

	if ( m_SkillLevel >= 45 && m_SkillLevel > level )
		return true;
	else
		return false;
}

bool EffectRevealer::canSeeInvisibility( Creature* pTarget ) const
	throw( Error )
{
	if ( !pTarget->isFlag( Effect::EFFECT_CLASS_INVISIBILITY ) )
		return true;

	Level_t level;

	if ( pTarget->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pTarget);
		Assert( pVampire != NULL );

		level = pVampire->getLevel();
	}
	else if ( pTarget->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pTarget);
		Assert( pMonster != NULL );

		level = pMonster->getLevel();
	}
	else
	{
		throw Error( "뱀파이어나 몬스터가 아닌데 인비지빌리티를 쓰고 있다." );
	}

	if ( m_SkillLevel >=65 && (m_SkillLevel-20) >= level )
		return true;
	else
		return false;
}

