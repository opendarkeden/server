////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasInvenSpace.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionHasInvenSpace.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "FlagSet.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionHasInvenSpace::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	Inventory* pInventory = pPC->getInventory();
	if ( pInventory == NULL ) return false;

	_TPOINT tp;
	return pInventory->getEmptySlot( m_Width, m_Height, tp );

	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionHasInvenSpace::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	try
	{
		// read turn
		m_Height = propertyBuffer.getPropertyInt("Height");
		m_Width = propertyBuffer.getPropertyInt("Width");

	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionHasInvenSpace::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionHasInvenSpace("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
