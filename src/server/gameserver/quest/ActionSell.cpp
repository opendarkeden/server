////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSell.cpp
// Written By  : 
// Description : 
// NPC가 아이템을 플레이어에게 파는 액션이다. 실제로는 거래를 
// 시작하게 만드는 액션이며, 하는 일은 플레이어에게 현재 NPC의
// 상점 버전을 패킷으로 보내주는 일 뿐이다.
////////////////////////////////////////////////////////////////////////////////

#include "ActionSell.h"
#include "PlayerCreature.h"
#include "NPC.h"
#include "Script.h"
#include "Trigger.h"
#include "Gpackets/GCShopVersion.h"
#include "Gpackets/GCNPCResponse.h"
#include "GamePlayer.h"

////////////////////////////////////////////////////////////////////////////////
// ActionSell 액션은 그냥 클라이언트에게 ShopVersion을 보내주는 것이므로,
// 특별히 읽어들여야 할 파라미터가 없다.
////////////////////////////////////////////////////////////////////////////////
void ActionSell::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY
    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionSell::execute (Creature * pCreature1 , Creature * pCreature2) 
	
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

	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	GCShopVersion pkt;
	pkt.setObjectID(pNPC->getObjectID());
	pkt.setVersion(SHOP_RACK_NORMAL,     pNPC->getShopVersion(SHOP_RACK_NORMAL));
	pkt.setVersion(SHOP_RACK_SPECIAL,    pNPC->getShopVersion(SHOP_RACK_SPECIAL));
	pkt.setVersion(SHOP_RACK_MYSTERIOUS, pNPC->getShopVersion(SHOP_RACK_MYSTERIOUS));

	int taxratio = pNPC->getTaxRatio( pPC );

	if ( taxratio != 100 ) pkt.setMarketCondSell(taxratio);
	else pkt.setMarketCondSell( pNPC->getMarketCondSell() );

	pPlayer->sendPacket(&pkt);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSell::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSell(" << ")";
	return msg.toString();

	__END_CATCH
}
