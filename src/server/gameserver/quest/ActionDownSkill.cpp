////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionDownSkill.cpp
// Written By  : 
// Description :
// NPC를 통해 클라이언트로 하여금 길드 생성창을 띄우게 한다.
////////////////////////////////////////////////////////////////////////////////

#include "ActionDownSkill.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionDownSkill::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

	// 길드 생성창을 띄우는 것뿐이므로 특별히 읽어들일 인수는 없다.

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionDownSkill::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse okpkt;
	okpkt.setCode(NPC_RESPONSE_DOWN_SKILL);
	pPlayer->sendPacket(&okpkt);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionDownSkill::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionDownSkill("
		<< ")";
	return msg.toString();

	__END_CATCH
}
