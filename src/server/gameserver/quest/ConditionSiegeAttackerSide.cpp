////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionSiegeAttackerSide.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionSiegeAttackerSide.h"
#include "GDRLairManager.h"
#include "Effect.h"
#include "Gpackets/GCSystemMessage.h"
#include "Player.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionSiegeAttackerSide::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	if ( !pCreature2->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_1 )
		&& !pCreature2->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_2 )
		&& !pCreature2->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_3 )
		&& !pCreature2->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_4 )
		&& !pCreature2->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_5 )
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
void ConditionSiegeAttackerSide::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionSiegeAttackerSide::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionSiegeAttackerSide("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
