////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionSiegeDefenderSide.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionSiegeDefenderSide.h"
#include "GDRLairManager.h"
#include "Effect.h"
#include "Gpackets/GCSystemMessage.h"
#include "Player.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionSiegeDefenderSide::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	if ( !pCreature2->isFlag( Effect::EFFECT_CLASS_SIEGE_DEFENDER )
		&& !pCreature2->isFlag( Effect::EFFECT_CLASS_SIEGE_REINFORCE )
		)
	{
/*		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( "수비측만 사용할 수 있습니다." );
		pCreature2->getPlayer()->sendPacket (&gcSystemMessage);*/
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionSiegeDefenderSide::read (PropertyBuffer & propertyBuffer) 
	
{
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionSiegeDefenderSide::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionSiegeDefenderSide("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
