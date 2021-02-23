//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRegenerate.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectRegenerate.h"
#include "Creature.h"
#include "Monster.h"
#include "Zone.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRegenerate::EffectRegenerate(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY 

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRegenerate::~EffectRegenerate()
	throw(Error)
{
	__BEGIN_TRY 
	__END_CATCH
}

void EffectRegenerate::affect() throw(Error)
{
	__BEGIN_TRY

	setNextTime( m_Tick );

	Monster* pMonster = dynamic_cast<Monster*>(m_pTarget);
	if ( pMonster == NULL ) return;

	HP_t regenPoint = min( (int)m_Point, pMonster->getHP(ATTR_MAX) - pMonster->getHP(ATTR_CURRENT) );

	if ( regenPoint != 0 )
	{
		pMonster->setHP( pMonster->getHP() + regenPoint );
		GCStatusCurrentHP gcHP;
		gcHP.setObjectID( pMonster->getObjectID() );
		gcHP.setCurrentHP( pMonster->getHP() );
		pMonster->getZone()->broadcastPacket( pMonster->getX(), pMonster->getY(), &gcHP );

		cout << pMonster->getName() << "의 HP가 " << pMonster->getHP() << "가 되었습니다." << endl;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRegenerate::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectRegenerate" << "unaffect BEGIN" << endl;

	//cout << "EffectRegenerate" << "unaffect END" << endl;
						
	__END_CATCH
}

string EffectRegenerate::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "EffectRegenerate("
		<< "ObjectID:" << getObjectID()
		<< ")";

	return msg.toString();

	__END_CATCH

}
