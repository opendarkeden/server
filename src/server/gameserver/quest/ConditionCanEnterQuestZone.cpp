////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterQuestZone.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionCanEnterQuestZone.h"
#include "PlayerCreature.h"
#include "GQuestManager.h"
#include "DynamicZoneInfo.h"
#include "DynamicZoneManager.h"
#include "DynamicZoneGroup.h"


////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionCanEnterQuestZone::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	bool bQuestCondition = pPC->getGQuestManager()->canEnterDynamicZone( m_QuestZoneID );
	bool bDynamicZoneAvailable = true;

	// Dynamic 존인지를 확인한다.
	int targetDynamicZoneType = g_pDynamicZoneInfoManager->getDynamicZoneTypeByZoneID( m_QuestZoneID );

	if ( targetDynamicZoneType != DYNAMIC_ZONE_MAX )
	{
		DynamicZoneGroup* pDynamicZoneGroup = g_pDynamicZoneManager->getDynamicZoneGroup( targetDynamicZoneType );
		Assert( pDynamicZoneGroup != NULL );

		bDynamicZoneAvailable = pDynamicZoneGroup->canEnter();
	}

	cout << "QuestZoneID: " << m_QuestZoneID << endl;
	cout << "Quest: " << ( bQuestCondition ? "true" : "false" ) << " Zone: " << ( bDynamicZoneAvailable ? "true" : "false" ) << endl;

	return bQuestCondition && bDynamicZoneAvailable;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionCanEnterQuestZone::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	m_QuestZoneID = propertyBuffer.getPropertyInt("ZoneID");
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionCanEnterQuestZone::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionCanEnterQuestZone("
		<< "ZoneID:" << (int)m_QuestZoneID
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
