//////////////////////////////////////////////////////////////////////////////
// Filename    : CGModifyNicknameHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGModifyNickname.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "PlayerCreature.h"
#include "NicknameBook.h"
#include "NicknameInfo.h"
#include "Zone.h"

#include "CreatureUtil.h"
#include "PetInfo.h"

#include "Gpackets/GCModifyNickname.h"
#include "Gpackets/GCNicknameVerify.h"
#include "Gpackets/GCUseOK.h"

#include "item/PetItem.h"
#include "item/EventGiftBox.h"
#include "Inventory.h"

#include "DB.h"
#endif

string getDBString(const string& str)
{
	char ret[100];
	int index=0;

	for ( int i=0; i<str.size(); ++i )
	{
		char c = str[i];
		if ( c == '\\' || c == '\'' )
		{
			ret[index++] = '\\';
		}
		ret[index++] = c;
		if ( index >= 100 ) break;
	}
	ret[index] = 0;

	return string(ret);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGModifyNicknameHandler::execute (CGModifyNickname* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	GCNicknameVerify gcNV;

	ObjectID_t itemOID = pPacket->getItemObjectID();
	EventGiftBox* pItem = NULL;

	if ( itemOID != 0 )
	{
		pItem = dynamic_cast<EventGiftBox*>(pInventory->getItemWithObjectID( itemOID ));

		if ( pItem == NULL )
		{
			filelog("Nickname.log", "[%s:%s] 아이템이 없거나 EventGiftBox가 아닙니다.",
					pPlayer->getID().c_str(),
					pPC->getName().c_str() );

			gcNV.setCode(NICKNAME_MODIFY_FAIL_NO_ITEM);
			pGamePlayer->sendPacket( &gcNV );
			return;
		}
	}
	else
	{
		PetInfo* pPetInfo = pPC->getPetInfo();
		if ( pPetInfo == NULL || pPetInfo->getPetType() != PET_PACKAGE )
		{
			gcNV.setCode(NICKNAME_MODIFY_FAIL_NO_ITEM);
			pGamePlayer->sendPacket( &gcNV );
			return;
		}

		pPetInfo->setNickname( pPacket->getNickname() );
		pPetInfo->getPetItem()->savePetInfo();
		sendPetInfo( pGamePlayer, true );

		gcNV.setCode( NICKNAME_MODIFY_OK );
		pGamePlayer->sendPacket( &gcNV );
		return;
	}

	switch ( pItem->getItemType() )
	{
		// 펫 닉네임 바꾸기
		case 23 :
		{
			PetInfo* pPetInfo = pPC->getPetInfo();
			if ( pPetInfo == NULL )
			{
				gcNV.setCode(NICKNAME_MODIFY_FAIL_NO_ITEM);
				pGamePlayer->sendPacket( &gcNV );
				return;
			}

			if ( pPetInfo->getPetType() != PET_PACKAGE && pItem == NULL )
			{
				gcNV.setCode(NICKNAME_MODIFY_FAIL_NO_ITEM);
				pGamePlayer->sendPacket( &gcNV );
				return;
			}

			pPetInfo->setNickname( pPacket->getNickname() );
			pPetInfo->getPetItem()->savePetInfo();
			sendPetInfo( pGamePlayer, true );

			gcNV.setCode( NICKNAME_MODIFY_OK );
			pGamePlayer->sendPacket( &gcNV );

			if ( pPetInfo->getPetType() != PET_PACKAGE )
			{
				pInventory->deleteItem( itemOID );
				pItem->destroy();
				SAFE_DELETE( pItem );

				GCUseOK gcOK;
				pGamePlayer->sendPacket( &gcOK );
			}

			return;
		}

		// 커스텀 닉네임 바꾸기
		case 22 :
		case 25 :
		{
			NicknameInfo* pNickname = pPC->getNicknameBook()->getNicknameInfo( 0 );

			if ( pNickname == NULL || pNickname->getNicknameType() != NicknameInfo::NICK_CUSTOM || pPacket->getNickname() == "" )
			{
				gcNV.setCode(NICKNAME_MODIFY_FAIL_NO_ITEM);
				pGamePlayer->sendPacket( &gcNV );
				return;
			}

			if ( pItem == NULL )
			{
				gcNV.setCode(NICKNAME_MODIFY_FAIL_NO_ITEM);
				pGamePlayer->sendPacket( &gcNV );
				return;
			}

//			pPC->removeFlag( Effect::EFFECT_CLASS_CAN_MODIFY_NICKNAME_0 );
			pNickname->setNickname( pPacket->getNickname() );

			Statement* pStmt = NULL;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery("UPDATE NicknameBook SET Nickname='%s' WHERE OwnerID='%s' AND nID=%u",
						getDBString(pNickname->getNickname()).c_str(), pPC->getName().c_str(), pNickname->getNicknameID() );
				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			gcNV.setCode( NICKNAME_MODIFY_OK );
			pGamePlayer->sendPacket( &gcNV );

			if ( pItem->getItemType() == 22 )
			{
				pInventory->deleteItem( itemOID );
				pItem->destroy();
				SAFE_DELETE( pItem );

				GCUseOK gcOK;
				pGamePlayer->sendPacket( &gcOK );
			}

			if ( pPC->getNickname() == pNickname )
			{
				GCModifyNickname gcMN;
				gcMN.setObjectID( pPC->getObjectID() );
				gcMN.setNicknameInfo( pNickname );
				pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcMN );
			}

			break;
		}

		// 닉네임 추가하기
		case 24 :
		{
			if ( pItem == NULL )
			{
				gcNV.setCode(NICKNAME_MODIFY_FAIL_NO_ITEM);
				pGamePlayer->sendPacket( &gcNV );
				return;
			}

			NicknameInfo* pNickname = new NicknameInfo;
			pNickname->setNicknameID( pPC->getNicknameBook()->popNicknameID() );
			pNickname->setNicknameType( NicknameInfo::NICK_CUSTOM );
			pNickname->setNickname( pPacket->getNickname() );

			pPC->getNicknameBook()->setNicknameInfo( pNickname->getNicknameID(), pNickname );

			Statement* pStmt = NULL;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery("INSERT INTO NicknameBook (nID, OwnerID, NickType, Nickname, Time) "
						"VALUES (%u, '%s', %u, '%s', now())",
						pNickname->getNicknameID(), pPC->getName().c_str(), pNickname->getNicknameType(), getDBString(pNickname->getNickname()).c_str() );
				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			gcNV.setCode( NICKNAME_MODIFY_OK );
			pGamePlayer->sendPacket( &gcNV );

			Packet* pNickList = pPC->getNicknameBook()->getNicknameBookListPacket();
			pGamePlayer->sendPacket( pNickList );
			SAFE_DELETE( pNickList );

			pInventory->deleteItem( itemOID );
			pItem->destroy();
			SAFE_DELETE( pItem );

			GCUseOK gcOK;
			pGamePlayer->sendPacket( &gcOK );

			break;
		}
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
