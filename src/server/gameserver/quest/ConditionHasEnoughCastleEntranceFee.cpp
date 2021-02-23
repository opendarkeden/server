////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasEnoughCastleEntranceFee.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionHasEnoughCastleEntranceFee.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "PaySystem.h"
#include "GamePlayer.h"
#include "PacketUtil.h"
#include "DB.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionHasEnoughCastleEntranceFee::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	Gold_t fee = g_pCastleInfoManager->getCastleInfo( m_ZoneID )->getEntranceFee();
	Gold_t remain = pPC->getGold();

	if( fee <= remain ) return true;
	else return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionHasEnoughCastleEntranceFee::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	try
	{
		// read turn
		m_ZoneID = propertyBuffer.getPropertyInt("ZoneID");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionHasEnoughCastleEntranceFee::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionHasEnoughCastleEntranceFee("
//		<< "Index:" << (int)m_Index
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
