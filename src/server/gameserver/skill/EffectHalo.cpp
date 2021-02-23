//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHalo.cpp
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "EffectHalo.h"
#include "Slayer.h"
#include "Ousters.h"
#include "Monster.h"
#include "GamePlayer.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"

#include "Gpackets/GCDeleteEffectFromTile.h"
#include "Gpackets/GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHalo::EffectHalo(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) 
	throw(Error)
{
	__BEGIN_TRY

	m_pZone = pZone;
	m_X = zoneX;
	m_Y = zoneY;
	m_UserOID = 0;
	m_TargetOID = 0;
	m_Damage = 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHalo::affect()
	throw(Error)
{
	__BEGIN_TRY

	setNextTime(10);

	//cout << "EffectHalo" << "affect BEGIN" << endl;
	Creature* pCreature = m_pZone->getCreature( m_TargetOID );
	affect(pCreature);
	
	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHalo::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( pCreature == NULL ) return;

	Zone* pZone = m_pZone;
	Assert( pZone != NULL );

	if ( abs((int)pCreature->getX() - (int)m_X) > 6 ||
		abs((int)pCreature->getY() - (int)m_Y) > 6 ) return;

	Creature* pCastCreature = pZone->getCreature( m_UserOID );

	GCModifyInformation gcMI, gcAttackerMI;

	if ( canAttack( pCastCreature, pCreature )
	&& !(pZone->getZoneLevel() & COMPLETE_SAFE_ZONE) )
	{
		if ( pCreature->isPC() )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

			::setDamage( pPC, getDamage(), pCastCreature, SKILL_HALO, &gcMI, &gcAttackerMI );
			pPC->getPlayer()->sendPacket( &gcMI );
		}
		else if ( pCreature->isMonster() )
		{
			::setDamage( pCreature, getDamage(), pCastCreature, SKILL_HALO, NULL, &gcAttackerMI );
		}

		if ( pCastCreature != NULL && pCastCreature->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCastCreature);

			computeAlignmentChange(pCreature, getDamage(), pOusters, &gcMI, &gcAttackerMI);
			increaseAlignment(pOusters, pCreature, gcAttackerMI);

			if (pCreature->isDead())
			{
				int exp = computeCreatureExp(pCreature, 100, pOusters);
				shareOustersExp(pOusters, exp, gcAttackerMI);
			}

			pOusters->getPlayer()->sendPacket( &gcAttackerMI );
		}
	}

	GCAddEffectToTile gcAET;
	gcAET.setEffectID( getSendEffectClass() );
	gcAET.setDuration( 15 );
	gcAET.setObjectID( pCreature->getObjectID() );
	gcAET.setXY( m_X, m_Y );

	pZone->broadcastPacket( m_X, m_Y, &gcAET );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHalo::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHalo::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectHalo" << "unaffect BEGIN" << endl;

    Tile& tile = m_pZone->getTile(m_X, m_Y);
	tile.deleteEffect(m_ObjectID);

	GCDeleteEffectFromTile gcDT;
	gcDT.setXY(m_X, m_Y);
	gcDT.setObjectID(getObjectID());
	gcDT.setEffectID(Effect::EFFECT_CLASS_HALO);
	m_pZone->broadcastPacket( m_X, m_Y, &gcDT );

	//cout << "EffectHalo" << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHalo::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectHalo("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

