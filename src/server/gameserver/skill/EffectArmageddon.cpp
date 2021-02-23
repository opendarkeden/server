//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectArmageddon.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectArmageddon.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "SkillUtil.h"
#include "Player.h"

#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectArmageddon::EffectArmageddon(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectArmageddon::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>( m_pTarget );

	Assert( pCreature != NULL );

	affect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectArmageddon::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert( pCreature != NULL );

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	// 이펙트를 건 크리쳐를 가져온다.
	// !! 이미 존을 떠났을 수도 있으므로 NULL 이 될 수 있다.
	// by bezz. 2003.1.4 
	//Creature* pCastCreature = pZone->getCreature( m_UserObjectID );

	//ZoneCoord_t X = pCreature->getX();
	//ZoneCoord_t Y = pCreature->getY();

	//if ( pCreature->isFlag( Effect::EFFECT_CLASS_NO_DAMAGE ) )
	//{
	//	return;
	//}

	//cout << "EffectArmageddon affect damage :" << m_Damage << endl;

	// 매초 데미지 주는거 잠시 막아놓음. by Sequoia
	/*if ( pCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

		GCModifyInformation gcMI;
		::setDamage( pSlayer, m_Damage, pCastCreature, SKILL_ARMAGEDDON, &gcMI );

		pSlayer->getPlayer()->sendPacket( &gcMI );
	}
	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		GCModifyInformation gcMI;
		::setDamage( pVampire, m_Damage, pCastCreature, SKILL_ARMAGEDDON, &gcMI );

		pVampire->getPlayer()->sendPacket( &gcMI );
	}
	else if ( pCreature->isMonster() )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		::setDamage( pMonster, m_Damage, pCastCreature, SKILL_ARMAGEDDON );
	}*/

	setNextTime( m_Delay );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectArmageddon::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	//cout << "EffectArmageddon unaffect.." << endl;

	// 플래그를 끈다.
	pCreature->removeFlag(Effect::EFFECT_CLASS_ARMAGEDDON);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_ARMAGEDDON);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectArmageddon::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectArmageddon::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectArmageddon("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH

}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectArmageddon::decreaseHP( Damage_t damage )
	throw()
{
	//cout << "EffectArmageddon Damaged : " << (int)damage << endl;

	HP_t RemainHP = max( 0, m_HP - damage );

	setHP( RemainHP );
	// 남은 HP가 0일 경우 다음 EffectManager::heartbeat() 에서 이펙트를 날려준다.
	if( RemainHP == 0 )
		setDeadline(0);
}
