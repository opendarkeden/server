//////////////////////////////////////////////////////////////////////////////
// Filename    : CGWhisperHandler.cc
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGWhisper.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Creature.h"
	#include "PCFinder.h"
	#include "LogNameManager.h"

	#include "Gpackets/GCWhisper.h"
	#include "Gpackets/GCWhisperFailed.h"
	#include "Gpackets/GGServerChat.h"

	#include "DB.h"

	#include "GameServerInfoManager.h"
	#include "LoginServerManager.h"
	#include "Properties.h"

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGWhisperHandler::execute (CGWhisper* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	try 
	{
		Player* pTargetPlayer = NULL;
		
		Creature* pCreature = pGamePlayer->getCreature();

		bool Success = false;
			
		// 이름으로 사용자를 찾아온다.
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))
			
		Creature* pTargetCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getName());

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature != NULL) 
		{
			// 채팅 로그를 남긴다. by sigi. 2002.10.30
			if (LogNameManager::getInstance().isExist( pCreature->getName() ))
			{
				filelog("chatLog.txt", "[Whisper] %s --> %s> %s", 
						pCreature->getName().c_str(), 
						pTargetCreature->getName().c_str(), 
						pPacket->getMessage().c_str());
			}

			pTargetPlayer = pTargetCreature->getPlayer();
			Assert(pTargetPlayer != NULL);
			Success = true;

			if (pGamePlayer->isPenaltyFlag(PENALTY_TYPE_MUTE)) {
				Success = false;
			}

			// 사용자를 성공적으로 찾았으면 Message 전송
			if (Success) {
				if (((GamePlayer*)pTargetPlayer)->getPlayerStatus() == GPS_NORMAL) {

					if (pCreature != NULL && pTargetCreature != NULL) {
						// 서버에서 클라이언트로 전송하므로 GC- 패킷을 사용해야 한다.
						GCWhisper gcWhisper;
					
						// 크리처 이름과 메시지를 패킷에 대입한다.
						gcWhisper.setName(pCreature->getName());	
						gcWhisper.setColor( pPacket->getColor() );
						gcWhisper.setMessage(pPacket->getMessage());
						gcWhisper.setRace(pCreature->getRace());
						pTargetPlayer->sendPacket(&gcWhisper);

					} else {
						GCWhisperFailed gcWhisperFailed;
						pGamePlayer->sendPacket(&gcWhisperFailed);
					}
				}
			}

			// 그런 사용자가 없거나 이름을 잘못 넣었을때 Failed
		} 
		else 
		{

			/*inthesky*/
			/*	DB를 뒤져서 사용자를 찾는다. DB에서 가져올 정보는 Player, Logon 정보와, ServerID 정도가 되곘다?
			 *	찾으면 해당게임서버로 GGServerChat 패킷을 전송한다 (sender, Color, Message, Race(종족), 
			 *	GGServerChat 패킷을 받은 서버는 사용자 이름으로 플레이어를 찾아서 GCWhisper패킷을 만들어 쏜다.
			 *	없으면 말자(Failed보낸다).
			 *	사용자가 있다 없다는 DB에서만 판단하자. DB의 신뢰도는..??????
			 */
			Statement* pStmt = NULL;
			Result* pResult = NULL;
			
			bool 				bServerFind	= false;
			ServerGroupID_t		CurrentServerGroupID;		
        	string				LogOn;		
			string				PlayerID;

			try 
			{
    	        BEGIN_DB
        	    {
           	    	pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

					// 크리쳐이름으로 Slayer테이블에서 PlayerID 를 찾는다.
			//add by viva 
					if(pPacket->getName().find('\'')>0 || pPacket->getName().find(' ')>0)
						//pPacket->getName() = "";
			//end
					pResult = pStmt->executeQuery("SELECT PlayerID FROM Slayer WHERE Name='vivaqq'");
					
					else
						
					pResult = pStmt->executeQuery("SELECT PlayerID FROM Slayer WHERE Name='%s'",pPacket->getName().c_str());
					
					if ( pResult->next() )		
					{
						PlayerID				= pResult->getString( 1 );
						SAFE_DELETE(pStmt);

						// 찾은 PlayerID로 Player테이블에서 ServerGroupID와 LogOn정보를 찾는다.
						pStmt	= g_pDatabaseManager->getDistConnection("USERINFO")->createStatement();
						pResult	= pStmt->executeQuery("SELECT CurrentServerGroupID, LogOn FROM Player WHERE PlayerID='%s'",PlayerID.c_str());
					
						// Player 정보를 찾았다.
						if ( pResult->next() )
						{
							CurrentServerGroupID	= pResult->getInt	( 1 );
							LogOn					= pResult->getString( 2 );

							// 게임중인 상태일때 bServerFind에 true flag
							if ( LogOn == "GAME" )
							{
								bServerFind = true;
								SAFE_DELETE(pStmt);
							}
						}
						else { SAFE_DELETE(pStmt); }
					}
					else { SAFE_DELETE(pStmt); }
					
					if(bServerFind)			// 찾았을때
					{
						/*	GGServerChat 패킷을 만들어서
						 *	쏜다...게임서버로..
						 *  pCreature->getName() = 보내는 크리쳐 이름	
						 *	pPacket->getName() = 받는 크리쳐 이름
						 *	PlayerID	= 받는 크리쳐 계정
						 *	pPacket->getColor()	= 글자색	
						 *	pPacket->getMessage() = 메세지
						 *  pCreature->getRace() = 보내는 크리쳐 종족
						 * */

										
						GameServerInfo*	pGameServerInfo = g_pGameServerInfoManager->getGameServerInfo(1,CurrentServerGroupID,g_pConfig->getPropertyInt( "WorldID" ));
						if ( pGameServerInfo != NULL )
						{
							GGServerChat ggServerChat;
							ggServerChat.setSender	(pCreature->getName()		);
							ggServerChat.setReceiver(pPacket->getName()	);
							ggServerChat.setColor	(pPacket->getColor()		);
							ggServerChat.setMessage	(pPacket->getMessage()		);
							ggServerChat.setRace	(pCreature->getRace()		);
							
							g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggServerChat );
						}
						else
						{
							GCWhisperFailed gcWhisperFailed;
							pGamePlayer->sendPacket(&gcWhisperFailed);
						}
					}
					else
					{
						GCWhisperFailed gcWhisperFailed;
		                pGamePlayer->sendPacket(&gcWhisperFailed);
					}

	            }
    	        END_DB(pStmt)
        	} catch(...) { /* write log plz */ }
			
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
	} 
	catch(Throwable & t) 
	{
		//cout << t.toString() << endl;
		GCWhisperFailed gcWhisperFailed;
		pGamePlayer->sendPacket(&gcWhisperFailed);
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}
