////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTurnOffFlag.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionTurnOffFlag.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionTurnOffFlag::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		m_Index = propertyBuffer.getPropertyInt("Index");
	} 
	catch (NoSuchElementException & nsee)
	{
		cout << nsee.toString() << endl;
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionTurnOffFlag::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	FlagSet* pFlagSet = pPC->getFlagSet();

	if (pFlagSet->isOn(m_Index) == true)
	{
		pFlagSet->turnOff(m_Index);
		pFlagSet->save(pCreature2->getName());
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionTurnOffFlag::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionTurnOffFlag("
		<< "Index:" << m_Index
	    << ")";
	return msg.toString();

	__END_CATCH
}
