//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDonationMoneyHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGDonationMoney.h"

#ifdef __GAME_SERVER__
	#include "DB.h"
	#include "Assert.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "NicknameBook.h"
	#include "Guild.h"
	#include "GuildManager.h"
	#include "EffectDonation200501.h"
	#include "VariableManager.h"
	#include "Properties.h"

	#include "Gpackets/GCNPCResponse.h"
	#include "Gpackets/GCModifyInformation.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDonationMoneyHandler::execute (CGDonationMoney* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Creature* pCreature = pGamePlayer->getCreature();
	Assert( pCreature != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert( pPC != NULL );

	// 결과 패킷
	GCNPCResponse gcNPCResponse;

	// Dimension ID
	static int dimensionID = g_pConfig->getPropertyInt( "Dimension" );
	// 월드 ID
	static int worldID = g_pConfig->getPropertyInt( "WorldID" );

	// affectWorldID
	static int affectWorldID = dimensionID * 3 + worldID;

	// 기부 횟수
	int sumBeforePersonal = 0;
	int sumAfterPersonal = 0;
	int sumBeforeGuild = 0;
	int sumAfterGuild = 0;

	// 기부 이벤트가 활성화된 상태인지 확인한다.
	if ( g_pVariableManager->getVariable( DONATION_EVENT_200501 ) != 1 )
	{
		return;
	}

	// 돈이 충분한지 확인
	if ( pPC->getGold() < pPacket->getGold() )
	{
		gcNPCResponse.setCode( NPC_RESPONSE_NOT_ENOUGH_MONEY );
		pPlayer->sendPacket( &gcNPCResponse );
		return;
	}

	// 인단 돈을 까고
	pPC->decreaseGoldEx( pPacket->getGold() );

	// 바뀐 금액을 보낸다.
	GCModifyInformation gcModifyInformation;
	gcModifyInformation.addLongData( MODIFY_GOLD, pPC->getGold() );
	pPlayer->sendPacket( &gcModifyInformation );

	// 지금까지의 기부 회수를 구한다.
	{
		Statement* pStmt = NULL;
		Result* pResult = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
			pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM DonationPersonal200501 WHERE Name = '%s' AND WorldID = %d", pCreature->getName().c_str(), affectWorldID );

			if ( pResult->next() )
			{
				sumBeforePersonal = pResult->getInt(1);
			}

			pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM DonationGuild200501 WHERE Name = '%s' AND WorldID = %d", pCreature->getName().c_str(), affectWorldID );

			if ( pResult->next() )
			{
				sumBeforeGuild = pResult->getInt(1);
			}
		}
		END_DB( pStmt )
	}

	// 기부 내용을 데이터 베이스에 기록한다.
	{
		Statement* pStmt = NULL;

		if ( pPacket->getDonationType() == DONATION_TYPE_200501_PERSONAL )
		{
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
				pStmt->executeQuery( "INSERT INTO DonationPersonal200501 VALUES ( '%s', '%s', %d, %u, now() )",
											pGamePlayer->getID().c_str(),
											pCreature->getName().c_str(),
											affectWorldID,
											pPacket->getGold() );
			}
			END_DB( pStmt )
		}
		else if ( pPacket->getDonationType() == DONATION_TYPE_200501_GUILD )
		{
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
				pStmt->executeQuery( "INSERT INTO DonationGuild200501 VALUES ( %u, '%s', '%s', '%s', %d, %u, now() )",
											pPC->getGuildID(),
											pPC->getGuildName().c_str(),
											pGamePlayer->getID().c_str(),
											pCreature->getName().c_str(),
											affectWorldID,
											pPacket->getGold() );
			}
			END_DB( pStmt )
		}
		else
		{
			return;
		}
	}

	// 지금까지의 기부 회수를 구한다.
	{
		Statement* pStmt = NULL;
		Result* pResult = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
			pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM DonationPersonal200501 WHERE Name = '%s' AND WorldID = %d", pCreature->getName().c_str(), affectWorldID );

			Packet* pNicknamePacket = NULL;

			if ( pResult->next() )
			{
				sumAfterPersonal = pResult->getInt(1);

				// 닉 네임을 추가해야되는 경우
				if ( sumAfterPersonal == 1  && sumBeforePersonal != sumAfterPersonal )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "새해 복 많이 받으세요" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
				else if ( sumAfterPersonal == 3 && sumBeforePersonal != sumAfterPersonal )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "밝은세상을 위해 노력한" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
				else if ( sumAfterPersonal == 5 && sumBeforePersonal != sumAfterPersonal )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "진정한 사랑을 아는" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
			}

			pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM DonationGuild200501 WHERE Name = '%s' AND WorldID = %d", pCreature->getName().c_str(), affectWorldID );

			if ( pResult->next() )
			{
				sumAfterGuild = pResult->getInt(1);

				// 닉 네임을 추가해야되는 경우
				if ( sumAfterGuild == 1 && sumBeforeGuild != sumAfterGuild )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "따뜻한 세상을 만듭시다" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
				else if ( sumAfterGuild == 3 && sumBeforeGuild != sumAfterGuild )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "밝은 세상을 만듭시다" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
				else if ( sumAfterGuild == 5 && sumBeforeGuild != sumAfterGuild )
				{
					NicknameBook* pNicknameBook = pPC->getNicknameBook();
					Assert( pNicknameBook != NULL );

					pNicknameBook->addNewNickname( "사랑을 실천한 사람들" );
					pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				}
			}

			if ( pNicknamePacket != NULL )
			{
				pGamePlayer->sendPacket( pNicknamePacket );
				SAFE_DELETE( pNicknamePacket );
			}
		}
		END_DB( pStmt )
	}


	// 이펙트를 추가한다.
	if ( !pPC->isFlag( Effect::EFFECT_CLASS_DONATION_200501 ) )
	{
		EffectDonation200501* pEffect = new EffectDonation200501( pPC );
		pPC->addEffect( pEffect );
		// 강제로 affect 한다. 안에서 브로드캐스팅 등의 처리를 한다.
		pEffect->affect();
	}

	// 기부 결과를 알린다.
	gcNPCResponse.setCode( NPC_RESPONSE_SHOW_DONATION_COMPLETE_DIALOG );
	pPlayer->sendPacket( &gcNPCResponse );
	
#endif

	__END_CATCH
}

