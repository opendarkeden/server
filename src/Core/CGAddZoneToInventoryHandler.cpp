//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddZoneToInventoryHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddZoneToInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "Relic.h"
	#include "RelicUtil.h"
	#include "Timeval.h"
	#include "EffectManager.h"
	#include "EffectPrecedence.h"
	#include "ItemUtil.h"
	#include "ItemFactoryManager.h"
	#include "CreatureUtil.h"
	#include "ZoneUtil.h"
	#include "LogClient.h"
	#include "CombatInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "PacketUtil.h"
	#include "BloodBible.h"
	#include "StringPool.h"
	#include "ShrineInfoManager.h"
	#include "Belt.h"
	#include "Sweeper.h"
	#include "OustersArmsband.h"
	#include "VariableManager.h"

	#include "GCDeleteandPickUpOK.h"
	#include "GCDeleteObject.h"
	#include "GCCannotAdd.h"
	#include "GCSystemMessage.h"
	#include "GCAddEffect.h"
	#include "GCCreateItem.h"
	#include "GCNoticeEvent.h"
	#include "GCDeleteInventoryItem.h"

	#include "EffectHasSlayerRelic.h"
	#include "EffectHasVampireRelic.h"
	#include "EffectRelicPosition.h"

	#include "EffectHasSweeper.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddZoneToInventoryHandler::execute (CGAddZoneToInventory* pPacket , Player* pPlayer)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG	

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*   pCreature   = pGamePlayer->getCreature();

		if (pCreature == NULL) return;

		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		bool            Merge       = false; // �������� ���ļ� �� ��� üũ ����
		bool            Success     = false; // �������� Adding �Ҽ� �ִ��� ������ ����
		Zone*           pZone       = pPC->getZone();
		Coord_t         ZoneX       = pPacket->getZoneX();
		Coord_t         ZoneY       = pPacket->getZoneY();

		// �ٿ�带 �Ѿ���� �ʴ��� üũ�Ѵ�.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) goto ERROR;

		Tile& _Tile = pZone->getTile(ZoneX , ZoneY);

		// Ÿ�Ͽ� �������� �����ϴ����� üũ�Ѵ�.
		if (!_Tile.hasItem()) goto ERROR;

		// ������ �����Ͱ� ���̰ų�, ���ͻ���Ŭ�̶�� ���� �� ����.
		Item* pItem = _Tile.getItem();
		if (pItem == NULL || !isPortableItem(pItem)) goto ERROR;

		// �������� ���� �� ���� ���¶�� ���� �� ����. -_-;
		if (!isAbleToPickupItem(pPC, pItem)) goto ERROR;

		// OID�� ��ġ�ϴ����� �˻��ؾ� �Ѵ�.
		ObjectID_t ItemObjectID = pItem->getObjectID();
		if (ItemObjectID != pPacket->getObjectID()) goto ERROR;

		// Inventory�� �޾ƿ´�.
		Inventory*   pInventory = pPC->getInventory();
		CoordInven_t InvenX     = pPacket->getInvenX();
		CoordInven_t InvenY     = pPacket->getInvenY();

		// �κ��丮 ��ǥ �ʰ���� ������.
		if (InvenX >= 10 || InvenY >= 6) goto ERROR;

		// �� ��ǥ�� �������� ���� �� ��� ������.
		if (!pInventory->canAdding(InvenX, InvenY, pItem)) goto ERROR;

		// ���� ������ ��� �ֿ� �� �ִ��� Ȯ���Ѵ�. --> �� �ڵ�� isAbleToPickup ���η� �Ű��..

		// �켱���� �پ��ִ� �������� ��쿡�� ���� �Ǵ� ������Ƽ�� �ƴ϶�� ���� �� ����.
		// ������ ��쿡�� �켱���� ����Ʈ�� �������ش�.
		if ( isRelicItem( pItem )
			&& pItem->isFlag(Effect::EFFECT_CLASS_PRECEDENCE))
		{
			EffectManager& effectManager = pItem->getEffectManager();

			effectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
			pItem->removeFlag(Effect::EFFECT_CLASS_PRECEDENCE);
		}

		if (pItem->isFlag(Effect::EFFECT_CLASS_PRECEDENCE))
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			EffectManager& rEffectManager = pItem->getEffectManager();

			EffectPrecedence* pEffectPrecedence = dynamic_cast<EffectPrecedence*>(rEffectManager.findEffect(Effect::EFFECT_CLASS_PRECEDENCE));
			Assert(pEffectPrecedence != NULL);

			if (pEffectPrecedence->getDeadline() < currentTime)
			{
				// �ð��� �����ٸ� �ƹ��� ���� �� �ִ�. ���Ҿ� ���⼭ ����Ʈ�� �������ش�.
				rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
				pItem->removeFlag(Effect::EFFECT_CLASS_PRECEDENCE);
			}
			else
			{
				// �ð��� ���� ������ �ʾҴٸ�, ���� �Ǵ� ���� ��Ƽ���� ���� �� �ִ�.
				if ((pEffectPrecedence->getHostName() == pPC->getName()) ||
					(pPC->getPartyID() != 0 && pPC->getPartyID() == pEffectPrecedence->getHostPartyID()))
				{
					// ���� �� �ִ�. ����Ʈ�� ������ �ش�.
					rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
					pItem->removeFlag(Effect::EFFECT_CLASS_PRECEDENCE);
				}
				else
				{
					// ���� �� ����.
					goto ERROR;
				}
			}
		}

/*
#ifdef __XMAS_EVENT_CODE__
		// �������� �������� ��� ���� ���ڶ��,
		// �κ��丮�� ��� ���� ���ڸ� ������ �ִٸ� ���� �� ����.
		if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX &&
			pItem->getItemType() == 0 &&
			pInventory->hasGreenGiftBox()) goto ERROR;
#endif
*/

		// ����ý���
		// ���� ���� ������ ������ �ֿ��ٸ�, �ڵ����� ���������� �̵��Ѵ�.
		// ������������ �̵��� �׳� item�� �����ϰ�, ���ο� ���͸� Regen�ϴ�
		// ������ �����Ѵ�.


		// �̹� ���� ������ ������ ������ �ִٸ� �� ������ ���� ���ϵ��� �Ѵ�.
		// �̹� �����̾� ������ ������ �ִٸ� ���ο� �����̾� ������ ���� ���Ѵ�.
		Item::ItemClass itemclass = pItem->getItemClass();
		//ItemType_t itemtype = pItem->getItemType();
		
		TPOINT pt;
		pt.x = 99;
		pt.y = 99;
		// �������� ���� �ڸ��� �ٸ� �������� ���� ������ �˻��Ѵ�.
		Item* pPrevItem = pInventory->searchItem(InvenX, InvenY, pItem, pt);

		if (pPrevItem != NULL)
		{
			if (canStack(pItem, pPrevItem))
			{
				// add by sonic 2006.10.30  ��ֹ��ʱ��������Ʒ����һ��
				if(pItem->isTimeLimitItem() || pPrevItem->isTimeLimitItem())
				{
					//cout << "cannot add" << endl;
					GCCannotAdd _GCCannotAdd;
					_GCCannotAdd.setObjectID(pPacket->getObjectID());
					pPlayer->sendPacket(&_GCCannotAdd);
					return;
				}
				int MaxStack = ItemMaxStack[pItem->getItemClass()];

				if( pt.x == InvenX && pt.y == InvenY ) {
					if (pItem->getNum() + pPrevItem->getNum() > MaxStack) 
					{
						ItemNum_t CurrentNum = pPrevItem->getNum();
						ItemNum_t AddNum = pItem->getNum();

						// �������� ������. by sigi. 2002.5.3
						// �ٵ�.. �̰� ������ �ƴϰ�..
						// ������ �ֿﶧ, �� �� ������ �� �ݴ°� �ƴѰ�..
						// �������� �ٽ� ������ �ϴ°ǰ�?
						// �̷��� ���� ��ǥ�� ���ƿ��� ��찡 �ִ°�? üũ�� �ʿ��ϰ���.
						// ����� ���°� ������..����.. --;
						//pInventory->increaseNum(pItem->getNum());
						//pInventory->increaseWeight(pItem->getWeight()* pItem->getNum());

						pPrevItem->setNum(MaxStack);
						pItem->setNum(AddNum + CurrentNum - MaxStack);

						//pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
						// item���� ����ȭ. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "OwnerID='%s', Num=%d, Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), MaxStack, STORAGE_INVENTORY, InvenX, InvenY);
						pPrevItem->tinysave(pField);

						//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
						sprintf(pField, "OwnerID='%s', Num=%d, Storage=%d", pPC->getName().c_str(), pItem->getNum(), STORAGE_EXTRASLOT);
						pItem->tinysave(pField);

					} 
					else 
					{
						pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());

						pInventory->increaseNum(pItem->getNum());
						pInventory->increaseWeight(pItem->getWeight()* pItem->getNum());

						//pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
						// item���� ����ȭ. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "OwnerID='%s', Num=%d, Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), pPrevItem->getNum(), STORAGE_INVENTORY, InvenX, InvenY);
						pPrevItem->tinysave(pField);

						pItem->destroy();
						Merge = true;
						Success = true;
					}

					if ( g_pVariableManager->getVariable(NETMARBLE_CARD_EVENT) != 0 && pPrevItem->getItemClass() == Item::ITEM_CLASS_MOON_CARD && pPrevItem->getItemType() == 2 && pPrevItem->getNum() == 99 )
					{
						GCNoticeEvent gcNE;
						gcNE.setCode( NOTICE_EVENT_NETMARBLE_CARD_FULL );
						pGamePlayer->sendPacket( &gcNE );
						cout << "gcNE sent" << endl;
					}

					if ( pPrevItem->getItemClass() == Item::ITEM_CLASS_LUCKY_BAG
							&& pPrevItem->getItemType() == 3
							&& pPrevItem->getNum() == 50 )
					{
						GCDeleteInventoryItem gcDI;
						gcDI.setObjectID( pPrevItem->getObjectID() );
						pGamePlayer->sendPacket( &gcDI );

						pInventory->deleteItem( pPrevItem->getObjectID() );
						pPrevItem->destroy();
						SAFE_DELETE( pPrevItem );
						
						Item* pNewItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_ITEM, 28, list<OptionType_t>() );
						pZone->registerObject( pNewItem );

						if ( !pInventory->addItem(pt.x, pt.y, pNewItem) )
						{
							cout << "-_-;" << endl;
							return;
						}

						pNewItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						if ( pNewItem != NULL )
						{
							GCCreateItem gcCI;
							makeGCCreateItem( &gcCI, pNewItem, pt.x, pt.y );
							pGamePlayer->sendPacket( &gcCI );
						}
					}
				} 
			}
		} 
		else 
		{
			pInventory->addItem(InvenX, InvenY, pItem);
			//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			// item���� ����ȭ. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "OwnerID='%s', Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), STORAGE_INVENTORY, InvenX, InvenY);
			pItem->tinysave(pField);

			// ��Ʈ ���� �����۵鵵 ��� �������� �Ѿ�� �Ѵ�. 2003.3.22 by Sequoia
			if ( pItem->getItemClass() == Item::ITEM_CLASS_BELT )
			{
				sprintf( pField, "OwnerID='%s'", pPC->getName().c_str() );

                Belt* pBelt = dynamic_cast<Belt*>( pItem );
                Assert( pBelt != NULL );

                Inventory* pBeltInventory = pBelt->getInventory();
                PocketNum_t num = pBelt->getPocketCount();

                for ( SlotID_t count = 0 ; count < num ; ++count )
                {
                    Item* pBeltItem = pBeltInventory->getItem( count, 0 );
                    if ( pBeltItem != NULL )
                    {
                        pBeltItem->tinysave( pField );
                    }
                }
			}
			// �Ͻ���� ���� �����۵鵵 ��� �������� �Ѿ�� �Ѵ�. 2003.3.22 by Sequoia
			if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_ARMSBAND )
			{
				sprintf( pField, "OwnerID='%s'", pPC->getName().c_str() );

                OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>( pItem );
                Assert( pOustersArmsband != NULL );

                Inventory* pOustersArmsbandInventory = pOustersArmsband->getInventory();
                PocketNum_t num = pOustersArmsband->getPocketCount();

                for ( SlotID_t count = 0 ; count < num ; ++count )
                {
                    Item* pOustersArmsbandItem = pOustersArmsbandInventory->getItem( count, 0 );
                    if ( pOustersArmsbandItem != NULL )
                    {
                        pOustersArmsbandItem->tinysave( pField );
                    }
                }
			}

			Success = true;
		}

		if (Success)
		{
			// �ؿ� �ִ��� �ű�. - -; 2002.12.23
			pZone->deleteItem(pItem, ZoneX, ZoneY);

			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);
			// ��ó�� �ִ� �ٸ� ����鿡�� �����ۿ� ������ٴ� ���� �����ش�.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
//			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject , pPC);
//			pZone->broadcastPacket(ZoneX , ZoneY, &_GCDeleteObject , pPC);
			pZone->broadcastPacket(ZoneX , ZoneY, &_GCDeleteObject);

			log(LOG_PICKUP_ITEM, pPC->getName(), "", pItem->toString());

			pItem->whenPCTake( pPC );

			// Relic ������ üũ�ϱ�
			if (isRelicItem( itemclass ))
			{
				addRelicEffect( pPC, pItem );

				deleteEffectRelicPosition( pItem );
			}

			// Flag�� ��쿣 Flag �� �ٿ��ش�.
			if ( pItem->isFlagItem() )
			{
				addSimpleCreatureEffect( pPC, Effect::EFFECT_CLASS_HAS_FLAG );
			}

			if ( pItem->getItemClass() == Item::ITEM_CLASS_SWEEPER )
			{
				EffectHasSweeper* pEffect = new EffectHasSweeper( pPC );
				pEffect->setPart( pItem->getItemType() );

				pPC->setFlag( pEffect->getEffectClass() );
				pPC->addEffect( pEffect );
			//	addSimpleCreatureEffect( pPC, (Effect::EffectClass)(Effect::EFFECT_CLASS_HAS_SWEEPER + pItem->getItemType()) );

				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID( pPC->getObjectID() );
				gcAddEffect.setEffectID( pEffect->getSendEffectClass() );

				pZone->broadcastPacket( pPC->getX(), pPC->getY(), &gcAddEffect );

				// �ֿ����� ���� �ý��� �޼��� �ѷ��ش�
				char race[15];
				if ( pCreature->isSlayer() )
				{
					sprintf( race, g_pStringPool->c_str( STRID_SLAYER ) );
				}
				else if ( pCreature->isVampire() )
				{
					sprintf( race, g_pStringPool->c_str( STRID_VAMPIRE ) );
				}
				else if ( pCreature->isOusters() )
				{
					sprintf( race, g_pStringPool->c_str( STRID_OUSTERS ) );
				}
				else
				{
					Assert(false);
				}

				const SweeperInfo* pSweeperInfo = dynamic_cast<SweeperInfo*>(g_pSweeperInfoManager->getItemInfo(pItem->getItemType()));

				char msg[100];
				sprintf( msg , g_pStringPool->c_str( STRID_PICK_UP_SWEEPER ) ,
									pSweeperInfo->getName().c_str(),
									pCreature->getName().c_str(),
									race
									);
				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( msg );
				pZone->broadcastPacket( &gcSystemMessage );
			}

			if ( pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 30 )
			{
				unsigned long timeLimit = 3600 * 24;

				pPC->addTimeLimitItem( pItem, timeLimit );
				pPC->sendTimeLimitItemInfo();
				pPC->setBaseLuck(10);
				pPC->initAllStatAndSend();
			}

/*			else if (itemclass == Item::ITEM_CLASS_EVENT_TREE)
			{
				// ũ�������� Ʈ�� �����̸�
				if ( itemtype <= 11 )
				{
					TPOINT pt = checkEventTree( pPC, InvenX, InvenY );
					// ũ�������� Ʈ�� ������ ���������� ����.
					if ( pt.x != -1 && pt.y != -1 )
					{
						// ������ Ʈ�� ������ �����.
						deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );
						pItem = NULL;	// ����

						// Ʈ���� �����Ѵ�.
						list<OptionType_t> optionType;
						Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 12, optionType );
						pZone->getObjectRegistry().registerObject( pTreeItem );
						pInventory->addItem( pt.x, pt.y, pTreeItem );
						pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						// Ŭ���̾�Ʈ�� Ʈ���� ��������ٴ� �� �˸���.
						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pTreeItem, pt.x, pt.y );
						pGamePlayer->sendPacket(&gcCreateItem);
					}
				}
			}
*/		
			if (Merge) 
			{
				// �������� ��� Item ��ü�� �����Ѵ�. �ֳ� ���ڷ� �����߱� ���� -_-;
				SAFE_DELETE(pItem);
			}
		}
		else
		{ 
			goto ERROR;
		}

		if ( pItem != NULL && pItem->isTraceItem() )
		{
			char zoneName[15];
			sprintf(zoneName, "%4d%3d%3d", pZone->getZoneID(), ZoneX, ZoneY);
			remainTraceLog( pItem, zoneName, pCreature->getName(), ITEM_LOG_MOVE, DETAIL_PICKUP);
		}
	} 
	catch (Throwable & t) 
	{ 
		//cerr << t.toString() << endl; 
	}

ERROR:
	GCCannotAdd _GCCannotAdd;
	_GCCannotAdd.setObjectID(pPacket->getObjectID());
	pPlayer->sendPacket(&_GCCannotAdd);
	return;

#endif	// __GAME_SERVER__

	__END_DEBUG
    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �̺�Ʈ �ڵ尡 ���ִ� �����̴�.
// �Ȱ��� �̺�Ʈ�� �� ��������� �𸣴� ������ �� ��! -- by �輺��
//////////////////////////////////////////////////////////////////////////////
/*
void CGAddZoneToInventoryHandler::execute (CGAddZoneToInventory* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG	

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*   pCreature   = pGamePlayer->getCreature();

		if (pCreature == NULL) return;

		PlayerCreature* pPC         = dynamic_cast<PlayerCreature*>(pCreature);
		bool            Merge       = false; // �������� ���ļ� �� ��� üũ ����
		bool            Success     = false; // �������� Adding �Ҽ� �ִ��� ������ ����
		Zone*           pZone       = pPC->getZone();
		Coord_t         ZoneX       = pPacket->getZoneX();
		Coord_t         ZoneY       = pPacket->getZoneY();

		// �ٿ�带 �Ѿ���� �ʴ��� üũ�Ѵ�.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) goto ERROR;

		Tile& _Tile = pZone->getTile(ZoneX , ZoneY);

		// Ÿ�Ͽ� �������� �����ϴ����� üũ�Ѵ�.
		if (!_Tile.hasItem()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// ������ �����͸� ����.
		Item* pItem = _Tile.getItem();
		if (pItem == NULL)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// �������� ���ͻ���Ŭ�̶�� ���� ���� ����.
		if (pItem->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// OID�� ��ġ�ϴ����� �˻��ؾ� �Ѵ�.
		ObjectID_t ItemObjectID = pItem->getObjectID();
		if (ItemObjectID != pPacket->getObjectID()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// �ٴڿ� ������ �ִ� �������� �̺�Ʈ�� �ذ��̶��...
		// �κ��丮�� ���ϴ� ���� �ƴ϶�, �׳� ī��Ʈ�� �÷���� �Ѵ�.
		if (pItem->getItemClass() == Item::ITEM_CLASS_SKULL && 
			12 <= pItem->getItemType() && pItem->getItemType() <= 16)
		{
			uint scount = pGamePlayer->getSpecialEventCount();
			int  prev   = (int)(scount/10);
			int  cur    = 0;

			switch (pItem->getItemType())
			{
				case 12: scount += 1; break; // Ȳ�� �ذ�
				case 15: scount += 4; break; // ���� �ذ�
				case 14: scount += 9; break; // ���� �ذ�
				default: break;
			}

			// ī��Ʈ�� �����Ѵ�.
			pGamePlayer->setSpecialEventCount(scount);
			pGamePlayer->saveSpecialEventCount();
			cur = (int)(scount/10);

			// ������ �������� �����Ѵ�.
			pZone->deleteItem(pItem, ZoneX, ZoneY);

			// ���� �𿡰� �� �־��ٰ� �����ش�.
			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);

			// ��ó�� �ִ� �ٸ� ����鿡�� �����ۿ� ������ٴ� ���� �����ش�.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject , pPC);

			// ���������� ���� ������ ��ü�� �����Ѵ�.
			delete pItem;

			// ������ ���������� �������ش�.
			StringStream msg;
			msg << "����� ���� �̺�Ʈ ������ " << pGamePlayer->getSpecialEventCount() << " ����Ʈ �Դϴ�.";
			GCSystemMessage gcMsg;
			gcMsg.setMessage(msg.toString());
			pPlayer->sendPacket(&gcMsg);

			// ������ ���������� ��ε�ĳ�����Ѵ�.
			if (prev != cur)
			{
				StringStream msg;
				msg << pPC->getName() << "�Բ��� " << pGamePlayer->getSpecialEventCount() << " ����Ʈ�� �̺�Ʈ ������ ȹ���Ͽ����ϴ�.";
				GCSystemMessage gcMsg;
				gcMsg.setMessage(msg.toString());
				pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcMsg , pPC);
			}

			return;
		}

		// Inventory�� �޾ƿ´�.
		Inventory*   pInventory = pPC->getInventory();
		CoordInven_t InvenX     = pPacket->getInvenX();
		CoordInven_t InvenY     = pPacket->getInvenY();

		// �κ��丮 ��ǥ �ʰ���� ������.
		if (InvenX >= 10 || InvenY >= 6)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// �� ��ǥ�� �������� ���� �� ��� ������.
		if (!pInventory->canAdding(InvenX, InvenY, pItem)) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// �������� ���� �ڸ��� �ٸ� �������� ���� ������ �˻��Ѵ�.
		Item* pPrevItem = pInventory->searchItem(InvenX, InvenY, pItem);

		if (pPrevItem != NULL)
		{
			if (canStack(pItem, pPrevItem))
			{
				// ���ڰ� 9���� ������ 9�� �ɶ������� Add �ϰ� �������� ���콺�� �޾Ƶд�.
				if (pItem->getNum() + pPrevItem->getNum() > 9) 
				{
					ItemNum_t CurrentNum = pPrevItem->getNum();
					ItemNum_t AddNum = pItem->getNum();

					pPrevItem->setNum(MaxSlotItem);
					pItem->setNum(AddNum + CurrentNum - MaxSlotItem);

					pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
					pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
				} 
				else 
				{
					// ���� ������ �ִ� Item�� �����Ѵ�.
					pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());

					// �κ��丮�� �� ���ڸ� �÷��ش�.
					pInventory->increaseNum(pItem->getNum());

					// �κ��丮�� �� ���Ը� �÷��ش�.
					pInventory->increaseWeight(pItem->getWeight()* pItem->getNum());

					// �������� �����Ѵ�.
					pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);

					// DB���� �����Ѵ�. �ϳ��� �������� ����...
					pItem->destroy();
					Merge = true;
					Success = true;
				}
			}
		} 
		else 
		{
			pInventory->addItem(InvenX, InvenY, pItem);
			pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			Success = true;
		}

		if (Success)
		{
			pZone->deleteItem(pItem, ZoneX, ZoneY);

			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);
			// ��ó�� �ִ� �ٸ� ����鿡�� �����ۿ� ������ٴ� ���� �����ش�.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject , pPC);

			log(LOG_PICKUP_ITEM, pPC->getName(), "", pItem->toString());
		
			if (Merge) 
			{
				// �������� ��� Item ��ü�� �����Ѵ�. �ֳ� ���ڷ� �����߱� ���� -_-;
				SAFE_DELETE(pItem);
			}
		}
		else
		{ 
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
		}
	} 
	catch (Throwable & t) 
	{ 
		//cerr << t.toString() << endl; 
	}

#endif	// __GAME_SERVER__

	__END_DEBUG
    __END_DEBUG_EX __END_CATCH
}
*/
