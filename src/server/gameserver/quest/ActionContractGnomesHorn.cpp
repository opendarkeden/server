////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionContractGnomesHorn.cpp
// Written By  : 
// Description : 
// NPC가 아이템을 플레이어에게 파는 액션이다. 실제로는 거래를 
// 시작하게 만드는 액션이며, 하는 일은 플레이어에게 현재 NPC의
// 상점 버전을 패킷으로 보내주는 일 뿐이다.
////////////////////////////////////////////////////////////////////////////////

#include "ActionContractGnomesHorn.h"
#include "Creature.h"
#include "NPC.h"
#include "Script.h"
#include "Trigger.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "FlagSet.h"

#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// ActionContractGnomesHorn 액션은 그냥 클라이언트에게 ShopVersion을 보내주는 것이므로,
// 특별히 읽어들여야 할 파라미터가 없다.
////////////////////////////////////////////////////////////////////////////////
void ActionContractGnomesHorn::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionContractGnomesHorn::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert(pPC != NULL);

	FlagSet* pFlagSet = pPC->getFlagSet();
	Assert(pFlagSet != NULL);

	pFlagSet->turnOn( FLAGSET_GNOMES_HORN );
	pFlagSet->save( pPC->getName() );

	GCNPCResponse gcNPCResponse;
	gcNPCResponse.setCode( NPC_RESPONSE_GNOME_CONTRACT_OK );

	pPC->getPlayer()->sendPacket(&gcNPCResponse);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionContractGnomesHorn::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionContractGnomesHorn(" << ")";
	return msg.toString();

	__END_CATCH
}
