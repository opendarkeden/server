////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCreateGuild.cpp
// Written By  : 
// Description :
// NPC를 통해 클라이언트로 하여금 길드 생성창을 띄우게 한다.
////////////////////////////////////////////////////////////////////////////////

#include "ActionCreateGuild.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "Gpackets/GCNPCResponse.h"

#include "SystemAvailabilitiesManager.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionCreateGuild::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	// 길드 생성창을 띄우는 것뿐이므로 특별히 읽어들일 인수는 없다.

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionCreateGuild::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	SYSTEM_RETURN_IF_NOT(SYSTEM_GUILD);

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse okpkt;
	okpkt.setCode(NPC_RESPONSE_INTERFACE_CREATE_GUILD);
	pPlayer->sendPacket(&okpkt);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionCreateGuild::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionCreateGuild("
		<< ")";
	return msg.toString();

	__END_CATCH
}
