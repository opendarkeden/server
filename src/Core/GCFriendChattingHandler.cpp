//////////////////////////////////////////////////////////////////////
//
// Filename    : GCFriendChattingHandle.cpp
// Written By  : aliveviva@gmail.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "GCFriendChatting.h"

#include "GamePlayer.h"
#include "PCFinder.h"
#include "DB.h"

void GCFriendChattingHandler::execute ( GCFriendChatting * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	//cout<<"friend1"<<endl;
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature* pCreature = pGamePlayer->getCreature();

	DWORD Command = pPacket->getCommand();

	if(Command>MAX_CG)
		throw InvalidProtocolException("Command Error");
	//cout<<"friend2"<<endl;
	switch(Command)
	{
		/////////////////////////////////////////////////CG_ADD_FRIEND_AGREE/////////////////////////////////////////
	case CG_ADD_FRIEND_AGREE:
		{
		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery("INSERT INTO FriendList (Friend_Name, Owner_Name) VALUES "
				"('%s', '%s')", pCreature->getName().c_str(), pPacket->getPlayerName().c_str());
			pStmt->executeQuery("INSERT INTO FriendList (Friend_Name, Owner_Name) VALUES "
				"('%s', '%s')", pPacket->getPlayerName().c_str(), pCreature->getName().c_str());

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
	
		Creature* pTargetCreature = NULL;
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))
		pTargetCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getPlayerName());
		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

		if (pTargetCreature!=NULL) 
		{
			Player* pTargetPlayer = pTargetCreature->getPlayer();
			if(pTargetPlayer == NULL)
				break;
			GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);
			if(pTargetGamePlayer == NULL)
				break;

			GCFriendChatting gcFriend;
			gcFriend.setCommand(GC_ADD_FRIEND_OK);
			gcFriend.setPlayerName(pCreature->getName());
			pTargetGamePlayer->sendPacket(&gcFriend);

			GCFriendChatting gcFriend2;
			gcFriend2.setCommand(GC_ADD_FRIEND_OK);
			gcFriend2.setPlayerName(pPacket->getPlayerName());
			pGamePlayer->sendPacket(&gcFriend2);
		}
		break;
		}
		///////////////////////////////////////////////CG_ADD_FRIEND///////////////////////////////////////////////////
	case CG_ADD_FRIEND:
		{
			Creature* pTargetCreature = NULL;
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))
			pTargetCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getPlayerName());
			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))
			bool blResult = true;
			if (pTargetCreature!=NULL) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if(pTargetPlayer == NULL)
					break;
				GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);
				if(pTargetGamePlayer == NULL)
					break;
				Statement* pStmt = NULL;
				Result* pResult = NULL;

				BEGIN_DB
				{
					pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
					////////////////////GC_ADD_FRIEND_EXIST//////////////////
					pResult = pStmt->executeQuery( "SELECT Friend_Name, IsBlack FROM FriendList WHERE Owner_Name = '%s' and Friend_Name='%s'", pCreature->getName().c_str(), pPacket->getPlayerName().c_str() );
					if( pResult->next() )
					{
						blResult = false;
						GCFriendChatting gcFriend3;
						gcFriend3.setCommand(GC_ADD_FRIEND_EXIST);
						gcFriend3.setPlayerName(pPacket->getPlayerName());
						pGamePlayer->sendPacket(&gcFriend3);
					}
					/////////////////GC_ADD_FRIEND_BLACK///////////////////////
					pResult = pStmt->executeQuery("SELECT IsBlack FROM FriendList WHERE Owner_Name='%s' and Friend_Name='%s' and IsBlack=1", pPacket->getPlayerName().c_str(), pCreature->getName().c_str());
					if( pResult->next() )
					{
						blResult = false;
						GCFriendChatting gcFriend4;
						gcFriend4.setCommand(GC_ADD_FRIEND_BLACK);
						gcFriend4.setPlayerName(pPacket->getPlayerName());
						pGamePlayer->sendPacket(&gcFriend4);
					}
					SAFE_DELETE(pStmt);
				}
				END_DB(pStmt)

				if(blResult)
				{
					GCFriendChatting gcFriend;
					gcFriend.setCommand(GC_ADD_FRIEND_REQUEST);
					gcFriend.setPlayerName(pCreature->getName());
					pTargetGamePlayer->sendPacket(&gcFriend);				

					GCFriendChatting gcFriend2;
					gcFriend2.setCommand(GC_ADD_FRIEND_WAIT);
					gcFriend2.setPlayerName(pPacket->getPlayerName());
					pGamePlayer->sendPacket(&gcFriend2);
				}
			}	
			break;
		}	
		////////////////////////////////////////////////////CG_MESSAGE//////////////////////////////////////////////
	case CG_MESSAGE:
		{
			Creature* pTargetCreature = NULL;
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))
			pTargetCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getPlayerName());
			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

			if(pTargetCreature!=NULL)
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if(pTargetPlayer == NULL)
					break;
				GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);
				if(pTargetGamePlayer == NULL)
					break;
				GCFriendChatting gcFriend;
				gcFriend.setCommand(GC_MESSAGE);
				gcFriend.setPlayerName(pCreature->getName());
				gcFriend.setMessage(pPacket->getMessage());
				pTargetGamePlayer->sendPacket(&gcFriend);
			}
			else
			{
				Statement* pStmt = NULL;
				BEGIN_DB
				{
					pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
					pStmt->executeQuery("INSERT INTO FriendHistory(HistoryMessage, Owner_Name, Friend_Name) VALUES "
						"('%s', '%s', '%s')", pPacket->getMessage().c_str(), pPacket->getPlayerName().c_str(), pCreature->getName().c_str());

					SAFE_DELETE(pStmt);
				}
				END_DB(pStmt)
			}
			break;
		}
	///////////////////////////////////////////CG_GETSTATE//////////////////////////////////////////////////////////
	case CG_UPDATE:
		{
			//cout<<"friend3"<<endl;
			Statement* pStmt = NULL;
			Result* pResult = NULL;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
				pResult = pStmt->executeQuery( "SELECT Friend_Name, IsBlack FROM FriendList WHERE Owner_Name = '%s'", pCreature->getName().c_str() );
				while( pResult->next() )
				{
					GCFriendChatting gcFriend;
					gcFriend.setCommand(GC_UPDATE);
					gcFriend.setPlayerName(pResult->getString(1));
					gcFriend.setIsBlack(pResult->getBYTE(2));

					Creature* pTargetCreature = NULL;
					__ENTER_CRITICAL_SECTION((*g_pPCFinder))
					pTargetCreature = g_pPCFinder->getCreature_LOCKED(gcFriend.getPlayerName());
					__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

					if (pTargetCreature==NULL) 
						gcFriend.setIsOnLine(0);
					else 
						gcFriend.setIsOnLine(1);
					
					pGamePlayer->sendPacket(&gcFriend);
				}

				pResult = pStmt->executeQuery( "SELECT HistoryMessage,Friend_Name FROM FriendHistory WHERE Owner_Name = '%s'", pCreature->getName().c_str());
				bool IsHave = false;
				while(pResult->next())
				{
					IsHave = true;
					GCFriendChatting gcFriend2;
					gcFriend2.setCommand(GC_MESSAGE);
					gcFriend2.setMessage(pResult->getString(1));
					gcFriend2.setPlayerName(pResult->getString(2));

					pGamePlayer->sendPacket(&gcFriend2);
				}
				if(IsHave)
					pStmt->executeQuery("DELETE FROM FriendHistory WHERE Owner_Name='%s'", pCreature->getName().c_str());

				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

				break;
		}
		////////////////////////////////////////CG_ADD_FRIEND_REFUSE/////////////////////////////
	case CG_ADD_FRIEND_REFUSE:
		{
			Creature* pTargetCreature = NULL;
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))
			pTargetCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getPlayerName());
			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

			if (pTargetCreature==NULL) 
			{
				GCFriendChatting gcFriend;
				gcFriend.setCommand(GC_ADD_FRIEND_ERROR);
				pGamePlayer->sendPacket(&gcFriend);
			}
			else 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if(pTargetPlayer == NULL)
					break;
				GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);
				if(pTargetGamePlayer == NULL)
					break;
				GCFriendChatting gcFriend;
				gcFriend.setCommand(GC_ADD_FRIEND_REFUSE);
				gcFriend.setPlayerName(pCreature->getName());
				pTargetGamePlayer->sendPacket(&gcFriend);
			}	
			break;
		}
		/////////////////////////////////////CG_ADD_FRIEND_BLACK///////////////////////////////////////
	case CG_ADD_FRIEND_BLACK:
		{
			Statement* pStmt = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery("INSERT INTO FriendList (Friend_Name, Owner_Name, IsBlack) VALUES "
					"('%s', '%s', 1)", pPacket->getPlayerName().c_str(), pCreature->getName().c_str());

				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			Creature* pTargetCreature = NULL;
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))
			pTargetCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getPlayerName());
			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

			if (pTargetCreature==NULL) 
			{
				GCFriendChatting gcFriend;
				gcFriend.setCommand(GC_ADD_FRIEND_ERROR);
				pGamePlayer->sendPacket(&gcFriend);
			}
			else 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if(pTargetPlayer == NULL)
					break;
				GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);
				if(pTargetGamePlayer == NULL)
					break;
				GCFriendChatting gcFriend;
				gcFriend.setCommand(GC_ADD_FRIEND_REFUSE);
				gcFriend.setPlayerName(pCreature->getName());
				pTargetGamePlayer->sendPacket(&gcFriend);
			}	
			break;
		}
		//////////////////////////////////////////////////////CG_FRIEND_DELTET//////////////////////////////////
	case CG_FRIEND_DELETE:
		{
			Statement* pStmt = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery("DELETE FROM FriendList WHERE Owner_Name='%s' and Friend_Name='%s'", 
					pCreature->getName().c_str(), pPacket->getPlayerName().c_str());
				pStmt->executeQuery("DELETE FROM FriendList WHERE Owner_Name='%s' and Friend_Name='%s'",
					pPacket->getPlayerName().c_str(), pCreature->getName().c_str());
				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)
			
			GCFriendChatting gcFriend;
			gcFriend.setCommand(GC_FRIEND_DELETE);
			gcFriend.setPlayerName(pPacket->getPlayerName());
			pGamePlayer->sendPacket(&gcFriend);

			Creature* pTargetCreature = NULL;
			__ENTER_CRITICAL_SECTION((*g_pPCFinder))
			pTargetCreature = g_pPCFinder->getCreature_LOCKED(pPacket->getPlayerName());
			__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

			if(pTargetCreature)
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if(pTargetPlayer == NULL)
					break;
				GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);
				if(pTargetGamePlayer == NULL)
					break;
				GCFriendChatting gcFriend2;
				gcFriend2.setCommand(GC_FRIEND_DELETE);
				gcFriend2.setPlayerName(pCreature->getName());
				pTargetGamePlayer->sendPacket(&gcFriend2);
			}
			break;
		}
		////////////////////////////////////////////DEFAULT/////////////////////////////////////////////////////////////////
	default:
		break;
	}
	__END_DEBUG_EX __END_CATCH
}
