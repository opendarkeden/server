////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRestore.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionRestore.h"
#include "Creature.h"
#include "NPC.h"
#include "SkillHandlerManager.h"
#include "Restore.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ActionRestore::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY 
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionRestore::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY 

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	GCNPCResponse okpkt;
	pCreature2->getPlayer()->sendPacket(&okpkt);

	// NPC를 얻어내고...
	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);

	// 스킬 핸들러를 얻어낸다...
	SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SKILL_RESTORE);
	Assert(pSkillHandler != NULL);

	// 리스토어 핸들러로 바꾸고...
	Restore* pRestore = dynamic_cast<Restore*>(pSkillHandler);
	
	// 리스토어를 수행한다.
	pRestore->execute(pNPC, pCreature2);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionRestore::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionRestore("
		<< ")";
	return msg.toString();

	__END_CATCH
}
