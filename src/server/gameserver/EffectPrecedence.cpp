//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPrecedence.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectPrecedence.h"
#include "Assert.h"
#include "Zone.h"
#include "DB.h"
#include "Creature.h"

EffectPrecedence::EffectPrecedence(Creature* pCreature) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	Assert(pCreature->isMonster());

	setTarget(pCreature);

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	m_bItem = false;

	__END_CATCH
}

EffectPrecedence::EffectPrecedence(Item* pItem) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pItem != NULL);
	setTarget(pItem);

	m_bItem = true;

	// 서버 전용 Effect이다. by sigi. 2002.11.14
	m_bBroadcastingEffect = false;

	__END_CATCH
}

void EffectPrecedence::affect()
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectPrecedence::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectPrecedence::affect (Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget)
	throw (Error)
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);
	
	__END_CATCH
}

void EffectPrecedence::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	if (m_bItem)
	{
		Item* pItem = dynamic_cast<Item*>(m_pTarget);
		pItem->removeFlag(getEffectClass());
	}
	else
	{
		Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
		Assert(pCreature != NULL);
		Assert(pCreature->isMonster());
		pCreature->removeFlag(getEffectClass());
	}

	__END_CATCH
}

void EffectPrecedence::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(false);

	__END_CATCH
}

void EffectPrecedence::unaffect (Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget)
	throw (Error)
{
	__BEGIN_TRY

	Assert(false);

	__END_CATCH
}

string EffectPrecedence::toString () const 
	throw ()
{
	StringStream msg;
	msg << "EffectPrecedence("
		<< "HostName:" << m_HostName
		<< ",PartyID:" << m_HostPartyID
		<< ",bItem:" << m_bItem
		<< ")";
	return msg.toString();
}
