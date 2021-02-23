//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDummyDrake.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "EffectDummyDrake.h"
#include "Monster.h"
#include "Ousters.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"
#include "Zone.h"

#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectDummyDrake::EffectDummyDrake(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	m_pTarget = pCreature;
	m_UserOID = 0;
	m_Damage = 0;
	m_Duration = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDummyDrake::affect()
	throw(Error)
{
	__BEGIN_TRY

	setNextTime(10);

// 	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
// 	affect(pCreature);
// 	int cx = pCreature->getX();
// 	int cy = pCreature->getY();
// 
// 	Zone* pZone = pCreature->getZone();
// 
// 	for ( int i=-1; i<=1; ++i )
// 	for ( int j=-1; j<=1; ++j )
// 	{
// 		int tx = cx + i;
// 		int ty = cy + j;
// 		if ( tx < 0 || ty < 0 ) continue;
// 		if ( !isValidZoneCoord( pZone, tx, ty ) ) continue;
// 
// 		slist<Object*>& olist = pZone->getTile(tx, ty).getObjectList();
// 		slist<Object*>::iterator itr = olist.begin();
// 		for ( ; itr != olist.end() ; ++itr )
// 		{
// 			Object* pObject = *itr;
// 			if ( pObject == NULL || pObject->getObjectClass() != Object::OBJECT_CLASS_CREATURE ) continue;
// 
// 			Creature* pTargetCreature = dynamic_cast<Creature*>(pObject);
// 			if ( pTargetCreature == NULL || pTargetCreature->isOusters() || pTargetCreature == pCreature ) continue;
// 			if ( pTargetCreature->isFlag( getEffectClass() ) ) continue;
// 
// 			EffectDummyDrake* pEffect = new EffectDummyDrake( pTargetCreature );
// 			pEffect->setUserOID( m_UserOID );
// 			pEffect->setDamage( m_Damage );
// 			pEffect->setDeadline( m_Duration/2 );
// 			pEffect->setDuration( m_Duration/2 );
// 			pEffect->setNextTime(10);
// 			pTargetCreature->setFlag( pEffect->getEffectClass() );
// 			pTargetCreature->addEffect( pEffect );
// 
// 			GCAddEffect gcAddEffect;
// 			gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
// 			gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
// 			gcAddEffect.setDuration( m_Duration/2 );
// 			
// 			pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );
// 
// 		}
// 	}

	//cout << "EffectDummyDrake" << "affect BEGIN" << endl;

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDummyDrake::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL ) return;

	Zone* pZone = pCreature->getZone();
	Assert( pZone != NULL );

	Ousters* pOusters = dynamic_cast<Ousters*>(pZone->getCreature( m_UserOID ));

	GCModifyInformation gcMI, gcAttackerMI;

	if ( canAttack( pOusters, pCreature )
	&& !(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE) )
	{
		Damage_t damage = getDamage();
		if ( pCreature->isPC() )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

			::setDamage( pPC, damage, pOusters, SKILL_DUMMY_DRAKE, &gcMI, &gcAttackerMI, true, false );
			pPC->getPlayer()->sendPacket( &gcMI );
		}
		else if ( pCreature->isMonster() )
		{
			::setDamage( pCreature, damage, pOusters, SKILL_DUMMY_DRAKE, NULL, &gcAttackerMI, true, false );
		}

		if ( pOusters != NULL )
		{
			computeAlignmentChange(pCreature, damage, pOusters, &gcMI, &gcAttackerMI);
			increaseAlignment(pOusters, pCreature, gcAttackerMI);

			if (pCreature->isDead())
			{
				int exp = computeCreatureExp(pCreature, 100, pOusters);
				shareOustersExp(pOusters, exp, gcAttackerMI);
			}

			pOusters->getPlayer()->sendPacket( &gcAttackerMI );
		}
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDummyDrake::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	pCreature->removeFlag(Effect::EFFECT_CLASS_DUMMY_DRAKE);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DUMMY_DRAKE);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectDummyDrake::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectDummyDrake" << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	// 读取5*5范围内对象,并创建伤害
	// 	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
		// 创建目标伤害
	 	affect(pCreature);

	 	int cx = pCreature->getX();
	 	int cy = pCreature->getY();
	// 
	 	Zone* pZone = pCreature->getZone();
	// 
	 	for ( int i=-2; i<=2; ++i )
	 	for ( int j=-2; j<=2; ++j )
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
	 
	 			Creature* pTargetCreature = dynamic_cast<Creature*>(pObject);
	 			if ( pTargetCreature == NULL || pTargetCreature->isOusters() || pTargetCreature == pCreature ) continue;
	 			if ( pTargetCreature->isFlag( getEffectClass() ) ) continue;
				// 创建伤害
				affect(pTargetCreature);
// 	 			EffectDummyDrake* pEffect = new EffectDummyDrake( pTargetCreature );
// 	 			pEffect->setUserOID( m_UserOID );
// 	 			pEffect->setDamage( m_Damage );
// 	 			pEffect->setDeadline( m_Duration/2 );
// 	 			pEffect->setDuration( m_Duration/2 );
// 	 			pEffect->setNextTime(10);
// 	 			pTargetCreature->setFlag( pEffect->getEffectClass() );
// 	 			pTargetCreature->addEffect( pEffect );
// 	 
// 	 			GCAddEffect gcAddEffect;
// 	 			gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
// 	 			gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
// 	 			gcAddEffect.setDuration( m_Duration/2 );
// 	 			
// 	 			pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );
	 
	 		}
	 	}
	unaffect(pCreature);

	//cout << "EffectDummyDrake" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectDummyDrake::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectDummyDrake("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

