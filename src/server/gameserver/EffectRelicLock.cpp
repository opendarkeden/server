//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelicLock.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectRelicLock.h"
#include "Creature.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "MonsterCorpse.h"
#include "Player.h"
#include "ZoneGroupManager.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRelicLock::EffectRelicLock(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	//m_LockTime.tv_sec = 0;
	//m_LockTime.tv_usec = 0;
	setTarget( pItem );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicLock::affect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}


void EffectRelicLock::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

	Item* pItem = dynamic_cast<Item *>(m_pTarget);
	unaffect(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicLock::unaffect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	pItem->removeFlag(Effect::EFFECT_CLASS_RELIC_LOCK);

	__END_DEBUG
	__END_CATCH
}

/*
bool EffectRelicLock::isLockTime() const
{
	Timeval currentTime;

	getCurrentTime(&currentTime);

	return currentTime.tv_sec >= m_LockTime.tv_sec
			&& currentTime.tv_usec >= m_LockTime.tv_usec;
}
*/



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectRelicLock::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectRelicLock("
//		<< "LockTime:" << m_LockTime.tv_sec
		<< ")";
	return msg.toString();

	__END_CATCH
}
