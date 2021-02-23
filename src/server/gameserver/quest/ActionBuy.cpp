////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionBuy.cpp
// Written By  : 
// Description : 
// NPC가 플레이어로부터 아이템을 사들이는 액션이다. Sell 액션과
// 마찬가지로 특별히 하는 일은 없고, 단지 플레이어에게 현재 
// 상점의 버전의 패킷으로 보내주는 역할을 한다.
////////////////////////////////////////////////////////////////////////////////

#include "ActionBuy.h"
#include "Creature.h"
#include "NPC.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCShopMarketCondition.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// ActionBuy 액션은 그냥 클라이언트에게 ShopVersion을 보내주는 것이므로,
// 특별히 읽어들여야 할 파라미터가 없다.
//
// 나중에 특정 종류의 아이템을 사들이는 상점 같은 것을 만들고자 하면,
// 여기서 프로퍼티를 만들어서 읽어들이면 되겠지. 흠... NPC 부분도 고쳐야
// 할 것이고...
////////////////////////////////////////////////////////////////////////////////
void ActionBuy::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionBuy::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	NPC* pNPC = dynamic_cast<NPC*>(pCreature1);
	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	// 먼저 대답을 잘 받았다는 사실을 클라이언트에게 알려준다.
	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	// 현재 시장 시세를 알려준다.
	GCShopMarketCondition pkt;
	pkt.setObjectID(pNPC->getObjectID());
	pkt.setMarketCondBuy(pNPC->getMarketCondBuy());
	pkt.setMarketCondSell(pNPC->getMarketCondSell());
	pPlayer->sendPacket(&pkt);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionBuy::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionBuy(" << ")";
	return msg.toString();

	__END_CATCH
}
