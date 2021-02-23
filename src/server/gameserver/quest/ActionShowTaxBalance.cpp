////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowTaxBalance.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionShowTaxBalance.h"
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
void ActionShowTaxBalance::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionShowTaxBalance::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
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

	GuildID_t guildID = pPC->getGuildID();
	GCNPCResponse deny;

	Guild* pGuild = g_pGuildManager->getGuild(guildID);
	if( bSuccess && pGuild == NULL ) 
	{
		// 길드가 없다.
		bSuccess = false;
		deny.setCode( NPC_RESPONSE_NO_GUILD );
	}

	if( bSuccess && pGuild->getMaster() != pPC->getName() )
	{
		// 길드 마스터가 아니다.
		bSuccess = false;
		deny.setCode( NPC_RESPONSE_NOT_GUILD_MASTER );
	}

	// 길드 마스터이다.
	list<CastleInfo*> pCastleInfoList = g_pCastleInfoManager->getGuildCastleInfos( guildID );
	if( bSuccess && pCastleInfoList.empty() )
	{
		// 길드가 소유한 성이 없다.
		bSuccess = false;
		deny.setCode( NPC_RESPONSE_HAS_NO_CASTLE );
	}

    list<CastleInfo*>::iterator itr = pCastleInfoList.begin();
    CastleInfo* pCastleInfo = NULL;

	for ( ; itr != pCastleInfoList.end() ; itr++ )
	{
		if ( (*itr)->getZoneID() == pCreature1->getZoneID() )
		{
			pCastleInfo = (*itr);
			break;
		}
	}

	if( bSuccess && pCastleInfo == NULL)
	{
		bSuccess = false;
		deny.setCode( NPC_RESPONSE_NOT_YOUR_CASTLE );
	}

	if ( bSuccess )
	{
		GCNPCResponse response;
		response.setCode( NPC_RESPONSE_SHOW_TAX_BALANCE );
		response.setParameter( (uint)pCastleInfo->getTaxBalance() );
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
string ActionShowTaxBalance::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionShowTaxBalance("
	    << ")";

	return msg.toString();

	__END_CATCH
}
