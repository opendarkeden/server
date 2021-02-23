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
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature* pCreature = pGamePlayer->getCreature();

	DWORD Command = pPacket->getCommand();

	if(Command>MAX_CG)
		throw InvalidProtocolException("Command Error");

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
			break;
		}
		///////////////////////////////////////////////CG_ADD_FRIEND///////////////////////////////////////////////////
	case CG_ADD_FRIEND:
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
				gcFriend.setCommand(GC_ADD_FRIEND_REQUEST);
				gcFriend.setPlayerName(pCreature->getName());
				pTargetGamePlayer->sendPacket(&gcFriend);				

				GCFriendChatting gcFriend2;
				gcFriend.setCommand(GC_ADD_FRIEND_WAIT);
				pGamePlayer->sendPacket(&gcFriend2);
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

			if(pTargetCreature==NULL)
			{
				GCFriendChatting gcFriend;
				gcFriend.setCommand(GC_NO_ONLINE);
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
				gcFriend.setCommand(GC_MESSAGE);
				gcFriend.setPlayerName(pCreature->getName());
				gcFriend.setMessage(pPacket->getMessage());
				pTargetGamePlayer->sendPacket(&gcFriend);
			}
			break;
		}
	///////////////////////////////////////////CG_GETSTATE//////////////////////////////////////////////////////////
	case CG_GETSTATE:
		{
			Statement* pStmt = NULL;
			Result* pResult = NULL;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
				pResult = pStmt->executeQuery( "SELECT Friend_Name, IsBlack FROM FriendLIst WHERE Owner_Name = '%s'", pCreature->getName().c_str() );
				while( pResult->next() )
				{
					GCFriendChatting gcFriend;
					gcFriend.setCommand(GC_GETSTATE);
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
				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

				break;
		}
		////////////////////////////////////////////DEFAULT/////////////////////////////////////////////////////////////////
	default:
		break;
	}
	__END_DEBUG_EX __END_CATCH
}
