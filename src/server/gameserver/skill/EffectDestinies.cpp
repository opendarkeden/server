//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDestinies.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "EffectDestinies.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"
#include "Zone.h"

#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK6.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDestinies::EffectDestinies(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_pTarget = pCreature;
	m_UserOID = 0;
	m_Damage = 0;
	m_TargetClass = Creature::CREATURE_CLASS_MAX;
	m_TargetSpriteType = 0;

	__END_CATCH
}

void EffectDestinies::setTargetType( Creature* pCreature )
{
	if ( pCreature == NULL ) return;
	m_TargetClass = pCreature->getCreatureClass();

	if ( m_TargetClass == Creature::CREATURE_CLASS_MONSTER )
	{
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);
		m_TargetSpriteType = pMonster->getSpriteType();
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDestinies::affect()
	throw(Error)
{
	__BEGIN_TRY

	setDeadline(0);

	Creature* pCaster = dynamic_cast<Creature*>(m_pTarget);
	int cx = pCaster->getX();
	int cy = pCaster->getY();

	Zone* pZone = pCaster->getZone();

	for ( int i=-8; i<=8; ++i )
	for ( int j=-8; j<=8; ++j )
	{
		int tx = cx + i;
		int ty = cy + j;
		if ( tx < 0 || ty < 0 ) continue;
		if ( !isValidZoneCoord( pZone, tx, ty ) ) continue;

		slist<Object*>& olist = pZone->getTile(tx, ty).getObjectList();
		slist<Object*>::iterator itr = olist.begin();
		for ( ; itr != olist.end() ; ++itr )
		{
			Object* pObject = *itr;
			if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;

			Creature* pCreature = dynamic_cast<Creature*>(pObject);
			if ( pCreature == NULL ) continue;

			bool isTarget = false;
			if ( pCreature->getCreatureClass() == m_TargetClass )
			{
				isTarget = true;
				if ( m_TargetClass == Creature::CREATURE_CLASS_MONSTER )
				{
					Monster* pTargetMonster = dynamic_cast<Monster*>(pCreature);
					if ( pTargetMonster->getSpriteType() != m_TargetSpriteType ) isTarget = false;
				}
			}

			if ( isTarget ) affect(pCreature);
		}
	}

	//cout << "EffectDestinies" << "affect BEGIN" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDestinies::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL ) return;

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	Ousters* pOusters = dynamic_cast<Ousters*>(m_pTarget);
	if ( pOusters == NULL ) return;

	GCModifyInformation gcMI, gcAttackerMI;

	if ( canAttack( pOusters, pCreature )
	&& !(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE) )
	{
		Damage_t damage = computeOustersMagicDamage( pOusters, pCreature, getDamage(), SKILL_DESTINIES );
		damage /= 2;
		if ( pCreature->isPC() )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

			::setDamage( pPC, damage, pOusters, SKILL_DESTINIES, &gcMI, &gcAttackerMI, true, false );
			pPC->getPlayer()->sendPacket( &gcMI );
		}
		else if ( pCreature->isMonster() )
		{
			::setDamage( pCreature, damage, pOusters, SKILL_DESTINIES, NULL, &gcAttackerMI, true, false );
		}

		computeAlignmentChange(pCreature, damage, pOusters, &gcMI, &gcAttackerMI);
		increaseAlignment(pOusters, pCreature, gcAttackerMI);

		if (pCreature->isDead())
		{
			int exp = computeCreatureExp(pCreature, 100, pOusters);
			shareOustersExp(pOusters, exp, gcAttackerMI);
		}

		pOusters->getPlayer()->sendPacket( &gcAttackerMI );

		GCSkillToObjectOK4 gcOK;
		gcOK.setTargetObjectID( pCreature->getObjectID() );
		gcOK.setSkillType( SKILL_DESTINIES );

		pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcOK, pCreature );

		if ( pCreature->isPC() )
		{
			GCSkillToObjectOK6 gcOK6;
			gcOK6.setXY( pCreature->getX(), pCreature->getY() );
			gcOK6.setSkillType( SKILL_DESTINIES );

			pCreature->getPlayer()->sendPacket( &gcOK6 );
		}

	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDestinies::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDestinies::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDestinies" << "unaffect BEGIN" << endl;

	//cout << "EffectDestinies" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDestinies::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectDestinies("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

