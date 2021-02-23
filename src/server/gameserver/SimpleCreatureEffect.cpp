//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleCreatureEffect.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SimpleCreatureEffect.h"
#include "Ousters.h"
#include "Player.h"

#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SimpleCreatureEffect::SimpleCreatureEffect(EffectClass eClass, Creature* pCreature)
	throw(Error) : m_EffectClass(eClass)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void SimpleCreatureEffect::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);

	// 플래그를 끈다.
	pCreature->removeFlag(getEffectClass());

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	// 이펙트를 삭제하라고 알려준다.
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(getSendEffectClass());

	if ( isBroadcastingEffect() )
	{
		pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);
	}
	else
	{
		Player* pPlayer = pCreature->getPlayer();
		if ( pPlayer != NULL ) pPlayer->sendPacket( &gcRemoveEffect );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void SimpleCreatureEffect::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string SimpleCreatureEffect::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "SimpleCreatureEffect("
		<< "EffectClass:" << (int)m_EffectClass
		<< ")";
	return msg.toString();

	__END_CATCH

}

