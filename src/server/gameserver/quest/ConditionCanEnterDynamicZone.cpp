////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterDynamicZone.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionCanEnterDynamicZone.h"
#include "PlayerCreature.h"
#include "GQuestManager.h"
#include "DynamicZoneInfo.h"
#include "DynamicZoneManager.h"
#include "DynamicZoneGroup.h"


////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionCanEnterDynamicZone::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( m_DynamicZoneID );

	DynamicZoneGroup* pDynamicZoneGroup = g_pDynamicZoneManager->getDynamicZoneGroup( targetDynamicZoneType );
	Assert( pDynamicZoneGroup != NULL );

	return ( pPC->getGQuestManager()->canEnterDynamicZone( m_DynamicZoneID )
			&& pDynamicZoneGroup->canEnter() );
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionCanEnterDynamicZone::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	m_DynamicZoneID = propertyBuffer.getPropertyInt("ZoneID");
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionCanEnterDynamicZone::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionCanEnterDynamicZone("
		<< "ZoneID:" << (int)m_DynamicZoneID
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
