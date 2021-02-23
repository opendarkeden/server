////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionRaceComp.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionRaceComp.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionRaceComp::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	throw () 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());

	if (pCreature2->getCreatureClass() != m_CClass) return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionRaceComp::read (PropertyBuffer & propertyBuffer) 
	throw (Error)
{
	try
	{
		string identifier = propertyBuffer.getProperty("Race");

		if (identifier == "SLAYER") m_CClass = Creature::CREATURE_CLASS_SLAYER;
		else if (identifier == "VAMPIRE") m_CClass = Creature::CREATURE_CLASS_VAMPIRE;
		else if (identifier == "OUSTERS") m_CClass = Creature::CREATURE_CLASS_OUSTERS;
		else
		{
			cout << "ConditionRaceComp::read() : unknown race" << endl;
			throw ("ConditionRaceComp::read() : unknown race");
		}
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionRaceComp::toString () const 
	throw () 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionRaceComp("
		<< "CClass:" << (int)m_CClass
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
