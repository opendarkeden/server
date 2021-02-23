////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterGDRLair.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionCanEnterGDRLair.h"
#include "GDRLairManager.h"
#include "Effect.h"
#include "Gpackets/GCSystemMessage.h"
#include "Player.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionCanEnterGDRLair::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

//	return false;

/*	if ( GDRLairManager::Instance().getTotalPCs() > 36 )
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( "Á¦ÇÑ ÀÎ¿øÀÌ ÃÊ°úµÇ¾î µé¾î°¥ ¼ö ¾ø½À´Ï´Ù." );
		pCreature2->getPlayer()->sendPacket (&gcSystemMessage);
		return false;
	}*/

	if ( !GDRLairManager::Instance().canEnter() )
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( "ÈÈ´ïÈðÐÐ¹¬»¹Ã»¿ªÆô." );
		pCreature2->getPlayer()->sendPacket (&gcSystemMessage);
		return false;
	}

	if ( !pCreature2->isFlag( Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR ) )
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( "±ØÐëµ½Ê§ÂäÖ®Ëþ2²ãÆÆ»µÏÄÂóË¹Ã¤ÈËÊ¯Ïñ." );
		pCreature2->getPlayer()->sendPacket (&gcSystemMessage);
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionCanEnterGDRLair::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionCanEnterGDRLair::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionCanEnterGDRLair("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
