//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectInvisibility.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectInvisibility.h"
#include "Creature.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "ZoneUtil.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectInvisibility::EffectInvisibility(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

void EffectInvisibility::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH 
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectInvisibility::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if ( !pCreature->isVampire() ) return;

	Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

	HP_t currentHP = pVampire->getHP();

	if ( currentHP == 1 )
	{
		setDeadline(0);
		return;
	}

	HP_t decreaseHP = 3 + pVampire->getINT()/250 + pVampire->getDEX()/60 + pVampire->getSTR()/200;
	int finalHP = currentHP - decreaseHP;

	if ( finalHP < 1 ) finalHP = 1;
	pVampire->setHP( finalHP );
	
	GCStatusCurrentHP gcHP;
	gcHP.setObjectID( pVampire->getObjectID() );
	gcHP.setCurrentHP( finalHP );
	
	pVampire->getZone()->broadcastPacket( pVampire->getX(), pVampire->getY(), &gcHP );

	setNextTime(10);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectInvisibility::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectInvisibility::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectInvisibility " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);
	
	Zone* pZone = pCreature->getZone();
	Assert(pZone);

	// true면 내부에서 effectManager의 effect를 삭제한다.
	addVisibleCreature(pZone, pCreature, false);

	//cout << "EffectInvisibility " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectInvisibility::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectInvisibility " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);
	
	//cout << "EffectInvisibility " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectInvisibility::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectInvisibility::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectInvisibility("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}

