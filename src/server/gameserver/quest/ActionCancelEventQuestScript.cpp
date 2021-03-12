////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCancelEventQuestScript.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionCancelEventQuestScript.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"

#include "mission/QuestManager.h"
#include "mission/EventQuestAdvance.h"

#include "Gpackets/GCNPCAsk.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionCancelEventQuestScript::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_ScriptID[0] = propertyBuffer.getPropertyInt("Level1");
		m_ScriptID[1] = propertyBuffer.getPropertyInt("Level2");
		m_ScriptID[2] = propertyBuffer.getPropertyInt("Level3");
		m_ScriptID[3] = propertyBuffer.getPropertyInt("Level4");
		m_ScriptID[4] = propertyBuffer.getPropertyInt("Level5");
		m_CounterScriptID = propertyBuffer.getPropertyInt("Counter");
		m_SuccessScriptID = propertyBuffer.getPropertyInt("Success");
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
void ActionCancelEventQuestScript::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert( pPC != NULL );

	int questLevel = pPC->getQuestManager()->getEventQuestAdvanceManager()->getQuestLevel();
	ScriptID_t sID = m_ScriptID[ questLevel ];
	QuestID_t qID;

	if ( !pPC->getQuestManager()->hasEventQuest( questLevel, qID ) ) sID = m_CounterScriptID;
	if ( pPC->getQuestManager()->successEventQuest( questLevel, qID ) ) sID = m_SuccessScriptID;
	GCNPCAsk gcNPCAsk;
	gcNPCAsk.setObjectID(pCreature1->getObjectID());
	gcNPCAsk.setScriptID(sID);
	gcNPCAsk.setNPCID( dynamic_cast<NPC*>(pCreature1)->getNPCID() );

	Player* pPlayer = pCreature2->getPlayer();
	pPlayer->sendPacket(&gcNPCAsk);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCancelEventQuestScript::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCancelEventQuestScript("
	    << ")";

	return msg.toString();

	__END_CATCH
}
