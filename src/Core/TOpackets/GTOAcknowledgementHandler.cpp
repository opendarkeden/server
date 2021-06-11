//----------------------------------------------------------------------
//
// Filename    : GTOAcknowledgementHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GTOAcknowledgement.h"
#include "Properties.h"

//#ifdef __THE_ONE_SERVER__

#include "DB.h"

#include "Gpackets/GGCommand.h"
#include "GameServerManager.h"
#include "Properties.h"

//#endif

//----------------------------------------------------------------------
// 
// GTOAcknowledgementHander::execute()
// 
//----------------------------------------------------------------------
void GTOAcknowledgementHandler::execute ( GTOAcknowledgement * pPacket )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __THE_ONE_SERVER__

	string strTargetTableName = "TheOneServerRules_New";
	string strTargetTableName_Log = "TheOneServerRules_Log";
//	string strTargetTableName = "TheOneServerRules";

	string strPolicy;
	Statement* pStmt = NULL;
	

	string strNewServerPolicy     = g_pConfig->getProperty("NEWSERVER_POLICY");
	
	BEGIN_DB
	{

		pStmt = g_pDatabaseManager->getConnection("TheOneDB")->createStatement();

		Result*	pResult = pStmt->executeQuery("SELECT ServerIP, ActualIP, UDPPort ,Policy FROM %s WHERE ActualIP='%s'",
				strTargetTableName.c_str(),
				pPacket->getHost().c_str()	);

		
		/*
		ServerIP와 ActualIP 키를 가지고 현재 Policy를 본다.
		존재하지 않는다면 ROW를 추가한다.
		*/
		if ( pResult->getRowCount() == 0 )	
		{
			if(strNewServerPolicy == "allow" || strNewServerPolicy == "ALLOW" || strNewServerPolicy == "Allow")
			{
				pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',%d,'%s',%d, %d ,'%s',now(),'LIVE')",
				strTargetTableName.c_str(),
				pPacket->getServerIP().c_str(), pPacket->getServerType(),
				pPacket->getHost().c_str(), pPacket->getPort(),
				pPacket->getUDPPort(),
				pPacket->getMessage().c_str());

				pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'NEW','NEW','[%s] 서버가 추가 되었습니다.')",
				strTargetTableName_Log.c_str(),
				pPacket->getHost().c_str(),
				pPacket->getHost().c_str());
			}
			else
			{
				GGCommand ggCommand;

				ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );
				g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

				ggCommand.setCommand( "*shutdown 0" );
				g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
		
				pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'DENY','DENY','[%s] 서버가 허가없이 접근하여 KILL시켰습니다..')",
				strTargetTableName_Log.c_str(),
				pPacket->getHost().c_str(),
				pPacket->getHost().c_str());

			}


		}
		/*
		존재한다면
		*/
		else
		{
			pResult->next();
			strPolicy	= pResult->getString(4);	
	
			pStmt->executeQuery( "UPDATE %s SET ServerIP='%s',ServerType=%d, ActualIP='%s', ActualPort=%d, UDPPort = %d,LastMsg='%s', LastAckTime=now() WHERE ActualIP='%s'",
								strTargetTableName.c_str(),
								pPacket->getServerIP().c_str(), 
								pPacket->getServerType(), 
								pPacket->getHost().c_str(), 
								pPacket->getPort(), 
								pPacket->getUDPPort(),
								pPacket->getMessage().c_str(), 
								pPacket->getHost().c_str());
		
			if(strPolicy == "KILL")
			{
					cout << "strPolicy : KILL..."<< endl;
					// 정책이 KILL(죽여라)이다. 패킷을 날려야 하겠다.
					// 패킷을 쏴버리자.
					// POLICY FIELD를 "DEATH" 로 변경해놓는다. 죽었으니까.

					// GGCommand 로 kill_daemonctl 을 보낸뒤에.
					GGCommand ggCommand;
					ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );

					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*shutdown 0" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
					


					pStmt->executeQuery( "UPDATE %s SET Policy='DEATH' WHERE ActualIP='%s'",
										strTargetTableName.c_str(),
										pPacket->getHost().c_str() );

					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'KILL','DEATH','[%s] 서버가 KILL정책에 따라 DEATH상태가 되었습니다')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());

					
			}
			else if(strPolicy == "REMOVE")
			{
					cout << "strPolicy : REMOVE..."<< endl;

					GGCommand ggCommand;
					ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
					
					ggCommand.setCommand( "*ekwldnjqjfu" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*shutdown 0" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );


					pStmt->executeQuery( "UPDATE %s SET Policy='CLEAR' WHERE ActualIP='%s'",
										strTargetTableName.c_str(),
										pPacket->getHost().c_str() );

					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'REMOVE','CLEAR','[%s] 서버가 REMOVE정책에 따라 CLEAR상태가 되었습니다')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());


			}
			else if(strPolicy == "CLEAR")
			{

					cout << "strPolicy : CLEAR...again remove"<< endl;

					GGCommand ggCommand;
					ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*ekwldnjqjfu" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*shutdown 0" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
				
					
					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'CLEAR','REMOVE','[%s] 서버가 CLEAR상태인데도 접근하였기 때문에 다음에 다시 REMOVE시킵니다.')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());

			}
			else if(strPolicy == "DEATH")
			{

				/*
					// 죽은상태인데 또 날아왔다.
					// LIVE 로 바꿔주자.
					pStmt->executeQuery( "UPDATE %s SET Policy='LIVE' WHERE ServerIP='%s'",
										strTargetTableName.c_str(),
										pPacket->getServerIP().c_str() );

					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'DEATH','LIVE','[%s] 서버가 DEATH상태인데도 접근하였기 때문에 LIVE상태로 바꿔줍니다.')",
					strTargetTableName_Log.c_str(),
					pPacket->getServerIP().c_str(),
					pPacket->getServerIP().c_str());
				*/
					GGCommand ggCommand;
					ggCommand.setCommand( "*set KILL_DAEMONCTL 1" );

					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );

					ggCommand.setCommand( "*shutdown 0" );
					g_pGameServerManager->sendPacket(pPacket->getHost(), pPacket->getUDPPort(), &ggCommand );
					
					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'DEATH','LIVE','[%s] 서버가 DEATH상태인데도 접근하였기 때문에 다시 KILL 시켰습니다..')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());


				

			}
			else if(strPolicy == "LIVE")	// 'LIVE' 일것이다. 그냥 내비두자.
			{
					// continue..
					cout << "strPolicy : LIVE..." << endl;
			}
			else
			{
					
					cout << "strPolicy : BAD! POLICY!" << endl;
					
					pStmt->executeQuery( "INSERT IGNORE INTO %s VALUES ('%s',now(),'UNKNOWN','UNKNOWN','[%s] 서버에서 알 수 없는 상황이 발생하였습니다.')",
					strTargetTableName_Log.c_str(),
					pPacket->getHost().c_str(),
					pPacket->getHost().c_str());


			}


		}


/*
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

        Result* pResult = pStmt->executeQuery("SELECT ZoneGroupID FROM ZoneGroupInfo ORDER BY ZoneGroupID"

        while (pResult->next())
        {
            ZoneGroupID_t ID = pResult->getInt(1);
            ZoneGroupIDList.push_back(ID);
        }
*/
		
			
		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )

	filelog( "TheOneServer.log", "패킷이 도착했습니다. : [%s:%05d] %s", pPacket->getHost().c_str(), pPacket->getPort(), pPacket->toString().c_str() );
	cout << "Touch.[" << pPacket->getHost() << ":" << pPacket->getPort() <<"].[Policy : "<< strPolicy << "]" << endl;
//	cout << "패킷이 도착했습니다. : [" << pPacket->getHost() << ":" << pPacket->getPort() <<"] : " << pPacket->toString() << endl;

#endif

	__END_DEBUG_EX __END_CATCH
}
