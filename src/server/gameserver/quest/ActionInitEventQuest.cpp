////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionInitEventQuest.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionInitEventQuest.h"
#include "NPC.h"
#include "Creature.h"

#include "mission/EventQuestInfoManager.h"
#include "mission/SimpleQuestRewardManager.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionInitEventQuest::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	try 
	{
	} 
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}
	
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionInitEventQuest::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert( pCreature1 != NULL );
	Assert( pCreature1->isNPC() );

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	EventQuestInfoManager* pQIM = new EventQuestInfoManager(pNPC);

	pQIM->load(pNPC->getName());
	pNPC->setQuestInfoManager( pQIM );

	SimpleQuestRewardManager* pRIM = new SimpleQuestRewardManager(pNPC);

	pRIM->load(pNPC->getName());
	pNPC->setRewardClassInfoManager( pRIM );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionInitEventQuest::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionInitEventQuest("
	    << ")";

	return msg.toString();

	__END_CATCH
}
