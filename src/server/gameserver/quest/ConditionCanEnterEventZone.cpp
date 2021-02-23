////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterEventZone.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionCanEnterEventZone.h"
#include "CreatureUtil.h"
#include "EventZoneInfo.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionCanEnterEventZone::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	ZoneEventInfo* pZoneEventInfo = EventZoneInfoManager::Instance().getZoneEventInfo( m_EventID );
	EventZoneInfo* pEventZoneInfo = pZoneEventInfo->getCurrentEventZoneInfo();

	if ( pEventZoneInfo == NULL || !pEventZoneInfo->canEnter() ) return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionCanEnterEventZone::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	m_EventID = propertyBuffer.getPropertyInt("EventID");
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionCanEnterEventZone::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionCanEnterEventZone("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
