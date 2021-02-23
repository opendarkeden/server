//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelicTable.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectRelicTable.h"
#include "Item.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectRelicTable::EffectRelicTable(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	m_SafeTime.tv_sec = 0;
	m_SafeTime.tv_usec = 0;

	m_LockTime.tv_sec = 0;
	m_LockTime.tv_usec = 0;

	setTarget(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicTable::affect()
	throw(Error)
{
	__BEGIN_TRY

	Item* pItem = dynamic_cast<Item*>(m_pTarget);
	affect(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicTable::affect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	__END_CATCH
}

void EffectRelicTable::unaffect() 
	throw(Error)
{
	__BEGIN_TRY	

    Item* pItem = dynamic_cast<Item *>(m_pTarget);
	unaffect(pItem);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectRelicTable::unaffect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	/*
	//cout << "EffectRelicTable" << "unaffect BEGIN" << endl;

	Assert(pItem != NULL);

	// 능력치를 정상적으로 되돌리기 위해서는 플래그를 끄고,
	// initAllStat을 불러야 한다.
	pItem->removeFlag(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC);

	Zone* pZone = pItem->getZone();
	Assert(pZone != NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pItem->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_HAS_SLAYER_RELIC);
	pZone->broadcastPacket(pItem->getX(), pItem->getY(), &gcRemoveEffect);

	//cout << "EffectRelicTable" << "unaffect END" << endl;
	*/
	pItem->removeFlag( getEffectClass() );

	__END_DEBUG
	__END_CATCH
}

// SafeTime 이 지나지 않았으면 성물을 꺼낼 수 없다.
bool EffectRelicTable::isSafeTime() const
{
	Timeval currentTime;
	getCurrentTime( currentTime );

	return currentTime > m_SafeTime;
}

// LockTime 동안은 성물을 꺼낼 수 없다.
bool EffectRelicTable::isLockTime() const
{
	Timeval currentTime;
	getCurrentTime( currentTime );

	return currentTime < m_LockTime;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectRelicTable::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectRelicTable("
		<< "SafeTime:" << m_SafeTime.tv_sec
		<< ")";
	return msg.toString();

	__END_CATCH
}
