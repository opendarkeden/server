////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSwapAdvancementItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionSwapAdvancementItem.h"
#include "Creature.h"
#include "NPC.h"
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "Guild.h"
#include "GuildManager.h"
#include "CastleInfoManager.h"

#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionSwapAdvancementItem::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionSwapAdvancementItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	bool bSuccess = true;

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);

	Player* pPlayer = pPC->getPlayer();
	Assert( pPlayer != NULL );

	GCNPCResponse deny;

	if ( !pPC->isAdvanced() )
	{
		deny.setCode( NPC_RESPONSE_NOT_ADVANCED );
		bSuccess = false;
	}

	if ( bSuccess )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_SWAP_ADVANCEMENT_ITEM );
		pPlayer->sendPacket( &response );
	}
	else
	{
		pPlayer->sendPacket( &deny );
	}
	
	GCNPCResponse quit;
	quit.setCode( NPC_RESPONSE_QUIT_DIALOGUE );
	pPlayer->sendPacket( &quit );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionSwapAdvancementItem::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionSwapAdvancementItem("
	    << ")";

	return msg.toString();

	__END_CATCH
}
