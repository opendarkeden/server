//////////////////////////////////////////////////////////////////////////////
// Filename    : CGVerifyTimeHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGVerifyTime.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "DB.h"
	#include "Properties.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGVerifyTimeHandler::execute (CGVerifyTime* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	if (!(pGamePlayer->verifySpeed(pPacket))) 
	{
		saveSpeedHackPlayer( pPlayer );
		throw DisconnectException("스피드핵 딱! 걸려써!!");
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGVerifyTimeHandler::saveSpeedHackPlayer( Player* pPlayer )
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature* pCreature = pGamePlayer->getCreature();

	string ID = pPlayer->getID();
	string IP = pPlayer->getSocket()->getHost();
	string Name = "";

	if ( pCreature != NULL )
	{
		if ( pCreature->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Name = "Slayer:" + pSlayer->getName();
		}
		else if ( pCreature->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			Name = "Vampire:" + pVampire->getName();
		}
		else if ( pCreature->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			Name = "Ousters:" + pOusters->getName();
		}
	}

	filelog("SpeedHack.log", "ID[%s], Name[%s], IP[%s]", ID.c_str(), Name.c_str(), IP.c_str());

	/////////////////////////////////////////////////////////
	// 디비에 관련 정보를 넣는다.
	/////////////////////////////////////////////////////////
	Statement* pStmt = NULL;

	try 
	{
		static WorldID_t 		WorldID 		= g_pConfig->getPropertyInt( "WorldID" );
		static ServerGroupID_t 	ServerGroupID 	= g_pConfig->getPropertyInt( "ServerID" );

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

			pStmt->executeQuery( "UPDATE SpeedHackPlayer SET IP = '%s', NAME = '%s', WorldID = %d, ServerGroupID = %d, Date = now(), Count = Count + 1 WHERE PlayerID = '%s'",
								IP.c_str(), Name.c_str(), (int)WorldID, (int)ServerGroupID, ID.c_str() );

			if ( pStmt->getAffectedRowCount() == 0 )
			{
				pStmt->executeQuery( "INSERT IGNORE INTO SpeedHackPlayer( PlayerID, IP, Name, WorldID, ServerGroupID, Date, Count ) VALUES ( '%s', '%s', '%s', %d, %d, now(), 1 )",
								ID.c_str(), IP.c_str(), Name.c_str(), (int)WorldID, (int)ServerGroupID );
			}

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)
	}
	catch ( Throwable& t )
	{
		filelog("SpeedHackLogError.log", "%s", t.toString().c_str() );
	}

#endif

	__END_CATCH
}

