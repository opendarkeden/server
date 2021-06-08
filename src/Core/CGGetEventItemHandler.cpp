//////////////////////////////////////////////////////////////////////////////
// Filename    : CGGetEventItemHandler.cpp
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGGetEventItem.h"

#ifdef __GAME_SERVER__
	#include "Assert.h"
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Inventory.h"
	#include "DB.h"
	#include "Item.h"
	#include "ItemFactoryManager.h"
	#include "ItemUtil.h"
	#include "PacketUtil.h"
	#include "Zone.h"
	#include "NicknameBook.h"

	#include "GCNPCResponse.h"
	#include "GCCreateItem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGGetEventItemHandler::execute (CGGetEventItem* pPacket , Player* pPlayer)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert( pPacket != NULL );
	Assert( pPlayer != NULL );

	if ( pPacket->getEventType() == EVENT_TYPE_200501_COMBACK_ITEM )
	{
		executeCombackItem( pPacket, pPlayer );
	}
	else if ( pPacket->getEventType() == EVENT_TYPE_200501_COMBACK_PREMIUM_ITEM )
	{
		executeCombackPremiumItem( pPacket, pPlayer );
	}
	else if ( pPacket->getEventType() == EVENT_TYPE_200501_COMBACK_RECOMMEND_ITEM )
	{
		executeCombackRecommendItem( pPacket, pPlayer );
	}

#endif

	__END_CATCH
}


#ifdef __GAME_SERVER__

void CGGetEventItemHandler::executeCombackItem( CGGetEventItem* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Statement* pStmt = NULL;

	static int i = 0;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT RecvItemDate FROM Event200501Main WHERE PlayerID = '%s'",
													pGamePlayer->getID().c_str() );

		if ( pResult->next() )
		{
			string RecvItemDate = pResult->getString(1);

			if ( RecvItemDate == "0000-00-00" )
			{
				// ������ ����~
				Creature* pCreature = pGamePlayer->getCreature();
				Assert( pCreature != NULL );

				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPC != NULL );

				Zone* pZone = pPC->getZone();
				Assert( pZone != NULL );

				Inventory* pInventory = pPC->getInventory();
				Assert( pInventory != NULL );

				Level_t level = pPC->getLevel();
				Race_t race = pPC->getRace();

				Item::ItemClass		iClass = Item::ITEM_CLASS_MAX;
				ItemType_t			iType = 0;
				Grade_t				iGrade = 6;
				list<OptionType_t>	optionType;

				// �ɼ� ����
				i = i ^ 1;
				if ( i )
				{
					optionType.push_back( 50 );		// DAM+3
					optionType.push_back( 176 );	// LUCK+3
				}
				else
				{
					optionType.push_back( 18 );		// HP+9
					optionType.push_back( 184 );	// ATTR+2
				}

				// ����
				if ( race == RACE_SLAYER )
				{
					iClass = Item::ITEM_CLASS_RING;
				}
				else if ( race == RACE_VAMPIRE )
				{
					iClass = Item::ITEM_CLASS_VAMPIRE_RING;
				}
				else if ( race == RACE_OUSTERS )
				{
					iClass = Item::ITEM_CLASS_OUSTERS_RING;
				}
				else
				{
					Assert( false );
				}

				// ����
				if ( level <= 30 )
				{
					iType = 3;
				}
				else if ( level <= 60 )
				{
					iType = 4;
				}
				else if ( level <= 90 )
				{
					iType = 4;
				}
				else if ( level <= 120 )
				{
					iType = 5;
				}
				else
				{
					iType = 5;
				}

				if ( iClass == Item::ITEM_CLASS_MAX )
				{
					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( FAIL_GET_EVENT_ITEM );
					pPlayer->sendPacket( &response );
					return;
				}

				Item* pItem = g_pItemFactoryManager->createItem( iClass, iType, optionType );
				if ( pItem == NULL )
				{
					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( FAIL_GET_EVENT_ITEM );
					pPlayer->sendPacket( &response );
					return;
				}

				pItem->setGrade( iGrade );

				// ����� Ȯ��
				_TPOINT tp;
				if ( !pInventory->getEmptySlot( pItem, tp ) )
				{
					SAFE_DELETE( pItem );

					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( NOT_ENOUGH_INVENTORY_SPACE );
					pPlayer->sendPacket( &response );
					return;
				}

				filelog( "CombackLog.txt", "[%s:%s] get %s", pGamePlayer->getID().c_str(), pPC->getName().c_str(), pItem->toString().c_str() );

				pItem->setTraceItem( bTraceLog( pItem ) );
				pZone->registerObject( pItem );

				if ( pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC );
				}

				if ( !pInventory->addItem( pItem, tp ) )
				{
					SAFE_DELETE( pItem );

					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( NOT_ENOUGH_INVENTORY_SPACE );
					pPlayer->sendPacket( &response );
					return;
				}

				pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, tp.x, tp.y );

				GCCreateItem gcCI;
				makeGCCreateItem( &gcCI, pItem, tp.x, tp.y );

				pPlayer->sendPacket( &gcCI );


				// �������ٰ� DB �� ����Ѵ�.
				pStmt->executeQuery( "UPDATE Event200501Main SET RecvItemDate = now() WHERE PlayerID = '%s'", pGamePlayer->getID().c_str() );

				// Ŭ���̾�Ʈ�� �����ߴٴ� �޽����� ������.
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
				response.setParameter( YOU_GET_EVENT_ITEM );
				pPlayer->sendPacket( &response );

				// �г����� �߰��ϰ� Ŭ���̾�Ʈ�� ��Ŷ�� ������.
				NicknameBook* pNicknameBook = pPC->getNicknameBook();
				Assert( pNicknameBook != NULL );

				pNicknameBook->addNewNickname( "Come Back!" );
				Packet* pNicknamePacket = pNicknameBook->getNicknameBookListPacket();
				pGamePlayer->sendPacket( pNicknamePacket );
				SAFE_DELETE( pNicknamePacket );
			}
			else
			{
				// �̹� �������� �޾ư���.
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
				response.setParameter( ALEADY_GET_EVENT_ITEM );
				pPlayer->sendPacket( &response );
				return;
			}
		}
		else
		{
			// ��� �ڰ� �ƴϴ�.
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
			response.setParameter( YOU_ARE_NOT_EVENT_TARGET );
			pPlayer->sendPacket( &response );
			return;
		}
	}
	END_DB( pStmt )

	__END_CATCH
}


void CGGetEventItemHandler::executeCombackPremiumItem( CGGetEventItem* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT PayPremiumDate, RecvPremiumItemDate FROM Event200501Main WHERE PlayerID = '%s'",
													pGamePlayer->getID().c_str() );

		if ( pResult->next() )
		{
			string PayPremiumDate = pResult->getString(1);
			string RecvItemDate = pResult->getString(2);

			if ( PayPremiumDate == "0000-00-00" )
			{
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
				response.setParameter( YOU_ARE_NOT_EVENT_TARGET );
				pPlayer->sendPacket( &response );
				return;
			}

			if ( RecvItemDate == "0000-00-00" )
			{
				// ������ ����~
				Creature* pCreature = pGamePlayer->getCreature();
				Assert( pCreature != NULL );

				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPC != NULL );

				Zone* pZone = pPC->getZone();
				Assert( pZone != NULL );

				Inventory* pInventory = pPC->getInventory();
				Assert( pInventory != NULL );

				Race_t race = pPC->getRace();

				Item* pItem[5] = { NULL, NULL, NULL, NULL, NULL };

				// �ɼ� DAM_3
				list<OptionType_t> optionType;
				optionType.push_back( 50 );		// DAM+3

				if ( race == RACE_SLAYER )
				{
					pItem[0] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_NECKLACE, 8, optionType );	// ���� ũ�ν�
					pItem[1] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_BRACELET, 8, optionType );	// ũ�ν� �극�̽���
					pItem[2] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_BRACELET, 8, optionType );	// ũ�ν� �극�̽���
					pItem[3] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RING, 8, optionType );		// �÷�Ƽ�� �����̷�
					pItem[4] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_RING, 8, optionType );		// �÷�Ƽ�� �����̷�
				}
				else if ( race == RACE_VAMPIRE )
				{
					pItem[0] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_NECKLACE, 8, optionType );	// �� ��ũ
					pItem[1] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_BRACELET, 7, optionType );	// ������ �극�̽���
					pItem[2] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_RING, 8, optionType );		// �� ���� ������
					pItem[3] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_EARRING, 8, optionType );	// �� ĳ�� ����
					pItem[4] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_VAMPIRE_AMULET, 8, optionType );		// ����
				}
				else if ( race == RACE_OUSTERS )
				{
					pItem[0] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_RING, 8, optionType );		// ��ũ���� ��
					pItem[1] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_RING, 8, optionType );		// ��ũ���� ��
					pItem[2] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_PENDENT, 8, optionType );	// ��ũ���� ��
					pItem[3] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_PENDENT, 8, optionType );	// �Ǿ ���Ʈ
					pItem[4] = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_PENDENT, 8, optionType );	// �Ǿ ���Ʈ
				}
				else
				{
					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( FAIL_GET_EVENT_ITEM );
					pPlayer->sendPacket( &response );
					return;
				}

				for ( int i=0; i<5; ++i )
				{
					if ( pItem[i] == NULL )
					{
						for ( int j=0; j<5; ++j )
						{
							SAFE_DELETE( pItem[j] );
						}

						GCNPCResponse response;
						response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
						response.setParameter( FAIL_GET_EVENT_ITEM );
						pPlayer->sendPacket( &response );
						return;
					}

					pItem[i]->setGrade( 6 );
				}

				_TPOINT tp[5];
				for ( int i=0; i<5; ++i )
				{
					// ����� Ȯ��

					if ( !pInventory->getEmptySlot( pItem[i], tp[i] ) )
					{
						// Ŭ����. �ѹ�
						for ( int j=0; j<i; ++j )
						{
							pInventory->deleteItem( pItem[j]->getObjectID() );
						}

						for ( int j=0; j<5; ++j )
						{
							SAFE_DELETE( pItem[j] );
						}

						GCNPCResponse response;
						response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
						response.setParameter( NOT_ENOUGH_INVENTORY_SPACE );
						pPlayer->sendPacket( &response );
						return;
					}

					pItem[i]->setTraceItem( bTraceLog( pItem[i] ) );
					pZone->registerObject( pItem[i] );

					if ( pItem[i]->isTraceItem() )
					{
						remainTraceLog( pItem[i], "", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC );
					}

					if ( !pInventory->addItem( pItem[i], tp[i] ) )
					{
						// Ŭ����. �ѹ�
						for ( int j=0; j<i; ++j )
						{
							pInventory->deleteItem( pItem[j]->getObjectID() );
						}

						for ( int j=0; j<5; ++j )
						{
							SAFE_DELETE( pItem[j] );
						}

						GCNPCResponse response;
						response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
						response.setParameter( NOT_ENOUGH_INVENTORY_SPACE );
						pPlayer->sendPacket( &response );
						return;
					}
				}

				// DB �� ���� �� �α� ����� Ŭ���̾�Ʈ�� ������
				// �ð� ���� �߰�
				for ( int i=0; i<5; ++i )
				{
					pItem[i]->create( pPC->getName(), STORAGE_INVENTORY, 0, tp[i].x, tp[i].y );

					filelog( "CombackLog.txt", "[%s:%s] get %s", pGamePlayer->getID().c_str(), pPC->getName().c_str(), pItem[i]->toString().c_str() );

					GCCreateItem gcCI;
					makeGCCreateItem( &gcCI, pItem[i], tp[i].x, tp[i].y );

					pPlayer->sendPacket( &gcCI );

					// �ð�����
					pPC->addTimeLimitItem( pItem[i], 7 * 24 * 60 * 60 );
				}

				pPC->sendTimeLimitItemInfo();

				// �������ٰ� DB �� ����Ѵ�.
				pStmt->executeQuery( "UPDATE Event200501Main SET RecvPremiumItemDate = now() WHERE PlayerID = '%s'", pGamePlayer->getID().c_str() );

				// Ŭ���̾�Ʈ�� �����ߴٴ� �޽����� ������.
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
				response.setParameter( YOU_GET_EVENT_ITEM );
				pPlayer->sendPacket( &response );
			}
			else
			{
				// �̹� �������� �޾ư���.
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
				response.setParameter( ALEADY_GET_EVENT_ITEM );
				pPlayer->sendPacket( &response );
				return;
			}
		}
		else
		{
			// ��� �ڰ� �ƴϴ�.
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
			response.setParameter( YOU_ARE_NOT_EVENT_TARGET );
			pPlayer->sendPacket( &response );
			return;
		}
	}
	END_DB( pStmt )

	__END_CATCH
}


void CGGetEventItemHandler::executeCombackRecommendItem( CGGetEventItem* pPacket, Player* pPlayer )
{
	__BEGIN_TRY

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	Statement* pStmt = NULL;

	static int i = 0;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT UniqueID, RecvItemDate FROM Event200501Recommend WHERE PlayerID = '%s'",
													pGamePlayer->getID().c_str() );

		if ( pResult->next() )
		{
			int		UniqueID = pResult->getInt(1);
			string	RecvItemDate = pResult->getString(2);

			if ( RecvItemDate == "0000-00-00" )
			{
				// ������ ����~
				Creature* pCreature = pGamePlayer->getCreature();
				Assert( pCreature != NULL );

				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert( pPC != NULL );

				Zone* pZone = pPC->getZone();
				Assert( pZone != NULL );

				Inventory* pInventory = pPC->getInventory();
				Assert( pInventory != NULL );

				Level_t level = pPC->getLevel();
				Race_t race = pPC->getRace();

				Item::ItemClass		iClass = Item::ITEM_CLASS_MAX;
				ItemType_t			iType = 0;
				Grade_t				iGrade = 6;
				list<OptionType_t>	optionType;

				// �ɼ� ����
				i = i ^ 1;
				if ( i )
				{
					optionType.push_back( 50 );		// DAM+3
					optionType.push_back( 176 );	// LUCK+3
				}
				else
				{
					optionType.push_back( 18 );		// HP+9
					optionType.push_back( 184 );	// ATTR+2
				}

				// ����
				if ( race == RACE_SLAYER )
				{
					iClass = Item::ITEM_CLASS_RING;
				}
				else if ( race == RACE_VAMPIRE )
				{
					iClass = Item::ITEM_CLASS_VAMPIRE_RING;
				}
				else if ( race == RACE_OUSTERS )
				{
					iClass = Item::ITEM_CLASS_OUSTERS_RING;
				}
				else
				{
					Assert( false );
				}

				// ����
				if ( level <= 30 )
				{
					iType = 3;
				}
				else if ( level <= 60 )
				{
					iType = 4;
				}
				else if ( level <= 90 )
				{
					iType = 4;
				}
				else if ( level <= 120 )
				{
					iType = 5;
				}
				else
				{
					iType = 5;
				}

				if ( iClass == Item::ITEM_CLASS_MAX )
				{
					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( FAIL_GET_EVENT_ITEM );
					pPlayer->sendPacket( &response );
					return;
				}

				Item* pItem = g_pItemFactoryManager->createItem( iClass, iType, optionType );
				if ( pItem == NULL )
				{
					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( FAIL_GET_EVENT_ITEM );
					pPlayer->sendPacket( &response );
					return;
				}

				pItem->setGrade( iGrade );

				// ����� Ȯ��
				_TPOINT tp;
				if ( !pInventory->getEmptySlot( pItem, tp ) )
				{
					SAFE_DELETE( pItem );

					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( NOT_ENOUGH_INVENTORY_SPACE );
					pPlayer->sendPacket( &response );
					return;
				}

				filelog( "CombackLog.txt", "[%s:%s] get %s", pGamePlayer->getID().c_str(), pPC->getName().c_str(), pItem->toString().c_str() );

				pItem->setTraceItem( bTraceLog( pItem ) );
				pZone->registerObject( pItem );

				if ( pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC );
				}

				if ( !pInventory->addItem( pItem, tp ) )
				{
					SAFE_DELETE( pItem );

					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( NOT_ENOUGH_INVENTORY_SPACE );
					pPlayer->sendPacket( &response );
					return;
				}

				pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, tp.x, tp.y );

				GCCreateItem gcCI;
				makeGCCreateItem( &gcCI, pItem, tp.x, tp.y );

				pPlayer->sendPacket( &gcCI );

				// �������ٰ� DB �� ����Ѵ�.
				pStmt->executeQuery( "UPDATE Event200501Recommend SET RecvItemDate = now() WHERE UniqueID = '%d'", UniqueID );

				// Ŭ���̾�Ʈ�� �����ߴٴ� �޽����� ������.
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
				response.setParameter( YOU_GET_EVENT_ITEM );
				pPlayer->sendPacket( &response );
			}
			else
			{
				// �̹� �������� �޾ư���.
				GCNPCResponse response;
				response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
				response.setParameter( ALEADY_GET_EVENT_ITEM );
				pPlayer->sendPacket( &response );
				return;
			}
		}
		else
		{
			// ��� �ڰ� �ƴϴ�.
			GCNPCResponse response;
			response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
			response.setParameter( YOU_ARE_NOT_EVENT_TARGET );
			pPlayer->sendPacket( &response );
			return;
		}
	}
	END_DB( pStmt )

	__END_CATCH
}

#endif

