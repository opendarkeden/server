////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRandomSay.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionRandomSay.h"
#include "Creature.h"
#include "NPC.h"
#include "Script.h"
#include "ScriptManager.h"
#include "GamePlayer.h"

#include "Gpackets/GCNPCSay.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionRandomSay::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try 
	{
		// read script id
		m_StartScriptID = propertyBuffer.getPropertyInt("StartScriptID");
		m_EndScriptID = propertyBuffer.getPropertyInt("EndScriptID");
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
void ActionRandomSay::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(pCreature1 != NULL);
	Assert(pCreature2 == NULL);
	Assert(pCreature1->isNPC());

	// RandomSay는 아래에서 보다시피, 임의의 범위(Start와 End) 안의 
	// 스크립트 중 랜덤을 돌려 하나를 클라이언트에게 보내는 식이다.
	// 그러므로 Start와 End 사이에 존재하지 않는 스크립트가 있으면 곤란하다.
	// 스크립트 테이블을 만들 때, RandomSay에 사용하는 것은 
	// 데이터가 반드시 연속적으로 존재하게 만들어야 한다.
	NPC*          pNPC     = dynamic_cast<NPC*>(pCreature1);
	ScriptID_t    scriptID = m_StartScriptID + random() % (m_EndScriptID - m_StartScriptID + 1);
	const Script* pScript  = g_pPublicScriptManager->getScript(scriptID);

	GCNPCSay gcNPCSay;
	gcNPCSay.setObjectID(pNPC->getObjectID());
	gcNPCSay.setScriptID(pScript->getScriptID());
	gcNPCSay.setSubjectID(0);

	Zone * pZone = pNPC->getZone();
	Assert(pZone != NULL);
	pZone->broadcastPacket(pNPC->getX() , pNPC->getY() , &gcNPCSay);

	__END_DEBUG
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRandomSay::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionRandomSay("
		<< ",ScriptID:"  << (int)m_StartScriptID << "-" << (int)m_EndScriptID
		<< ")";
	
	return msg.toString();
	__END_CATCH
}
