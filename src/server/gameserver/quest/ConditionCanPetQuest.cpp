////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanPetQuest.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionCanPetQuest.h"
#include "CreatureUtil.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionCanPetQuest::isSatisfied (Creature * pCreature1 , Creature * pCreature2, void* pParam) const 
	 
{ 
	Assert(pCreature2 != NULL);
	Assert(pCreature2->isPC());
	int level=0;

	if ( pCreature2->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature2);
		Assert( pSlayer != NULL );
		level = pSlayer->getHighestSkillDomainLevel();
	}
	else if ( pCreature2->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature2);
		Assert( pVampire != NULL );
		level = pVampire->getLevel();
	}
	else if ( pCreature2->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature2);
		Assert( pOusters != NULL );
		level = pOusters->getLevel();
	}

	return level>=40;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionCanPetQuest::read (PropertyBuffer & propertyBuffer) 
	
{
}

////////////////////////////////////////////////////////////////////////////////
	// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionCanPetQuest::toString () const 
	 
{ 
	__BEGIN_TRY

	StringStream msg;
	msg << "ConditionCanPetQuest("
		<< ")"; 
	return msg.toString();

	__END_CATCH
}
