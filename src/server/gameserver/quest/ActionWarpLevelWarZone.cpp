////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionWarpLevelWarZone.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionWarpLevelWarZone.h"
#include "Creature.h"
#include "GamePlayer.h"
#include "NPC.h"
#include "Utility.h"
#include "ZoneInfo.h"
#include "ZoneUtil.h"
#include "PacketUtil.h"
#include "Properties.h"
#include "StringPool.h"
#include "VariableManager.h"
#include "ZoneInfoManager.h"
#include "LevelWarManager.h"
#include "LevelWarZoneInfoManager.h"
#include "GQuestManager.h"
#include "PlayerCreature.h"

#include "Gpackets/GCSystemMessage.h"

////////////////////////////////////////////////////////////////////////////////
// read from PropertyBuffer
////////////////////////////////////////////////////////////////////////////////
void ActionWarpLevelWarZone::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY

    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionWarpLevelWarZone::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert( pCreature2 != NULL );
	Assert( pCreature2->isPC() );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature2->getPlayer());
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	
	GCSystemMessage gcSystemMessage;

/*	if ( g_pVariableManager->getVariable( ACTIVE_LEVEL_WAR ) == 0 )
	{
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER ) );
		pGamePlayer->sendPacket( &gcSystemMessage );
		return;
	}*/

	// 레벨 너무 높은 캐릭터는 들어갈 수 없다
	if ( g_pLevelWarZoneInfoManager->getCreatureLevelGrade( pCreature2 ) == -1 )
	{
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_TO_HIGH_LEVEL_FOR_LEVEL_WAR ) );
		pGamePlayer->sendPacket (&gcSystemMessage);
		return;
	}

	// 크리쳐 정보 보고 알아서 튕겨주자 =_=;;
	ZONE_COORD pos(g_pLevelWarZoneInfoManager->getCreatureZoneID( pCreature2 ));

	if ( pCreature2->isSlayer() )
	{
		pos.x = 12;
		pos.y =  9;
	}
	else if ( pCreature2->isVampire() )
	{
		pos.x = 117;
		pos.y =   8;
	}
	else if ( pCreature2->isOusters() )
	{
		pos.x =   9;
		pos.y = 111;
	}
	
#if defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__)
	Zone* pZone = getZoneByZoneID( pos.id );
	Assert( pZone != NULL );

	LevelWarManager* pLevelWarManager = pZone->getLevelWarManager();
	Assert( pLevelWarManager != NULL );

	if ( !pLevelWarManager->hasWar() && !g_pVariableManager->canEnterLevelWarZoneFree() && !pGamePlayer->isPayPlaying() && !pLevelWarManager->canEnterFreeUser() )
	{
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_ENTER_LEVEL_WAR_ZONE ) );
		pGamePlayer->sendPacket (&gcSystemMessage);
		return;
	}
#endif
	
	if ( pCreature1 != NULL ) pPC->getGQuestManager()->illegalWarp();
	transportCreature(pCreature2, pos.id, pos.x, pos.y, false);
	return;

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionWarpLevelWarZone::toString () const
	throw ()
{
	__BEGIN_TRY

	StringStream msg;

	msg << "ActionWarpLevelWarZone("
		<< ")";

	return msg.toString();

	__END_CATCH
}
