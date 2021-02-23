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

	#include "Gpackets/GCDeleteandPickUpOK.h"
	#include "Gpackets/GCDeleteObject.h"
	#include "Gpackets/GCCannotAdd.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCAddEffect.h"
	#include "Gpackets/GCCreateItem.h"
	#include "Gpackets/GCNoticeEvent.h"
	#include "Gpackets/GCDeleteInventoryItem.h"

	#include "EffectHasSlayerRelic.h"
	#include "EffectHasVampireRelic.h"
	#include "EffectRelicPosition.h"

	#include "EffectHasSweeper.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
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
		bool            Merge       = false; // 아이템이 겹쳐서 들어갈 경우 체크 변수
		bool            Success     = false; // 아이템을 Adding 할수 있는지 없는지 여부
		Zone*           pZone       = pPC->getZone();
		Coord_t         ZoneX       = pPacket->getZoneX();
		Coord_t         ZoneY       = pPacket->getZoneY();

		// 바운드를 넘어가지는 않는지 체크한다.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) goto ERROR;

		Tile& _Tile = pZone->getTile(ZoneX , ZoneY);

		// 타일에 아이템이 존재하는지를 체크한다.
		if (!_Tile.hasItem()) goto ERROR;

		// 아이템 포인터가 널이거나, 모터사이클이라면 주을 수 없다.
		Item* pItem = _Tile.getItem();
		if (pItem == NULL || !isPortableItem(pItem)) goto ERROR;

		// 아이템을 주을 수 없는 상태라면 주을 수 없다. -_-;
		if (!isAbleToPickupItem(pPC, pItem)) goto ERROR;

		// OID가 일치하는지를 검사해야 한다.
		ObjectID_t ItemObjectID = pItem->getObjectID();
		if (ItemObjectID != pPacket->getObjectID()) goto ERROR;

		// Inventory를 받아온다.
		Inventory*   pInventory = pPC->getInventory();
		CoordInven_t InvenX     = pPacket->getInvenX();
		CoordInven_t InvenY     = pPacket->getInvenY();

		// 인벤토리 좌표 초과라면 에러다.
		if (InvenX >= 10 || InvenY >= 6) goto ERROR;

		// 그 좌표에 아이템을 더할 수 없어도 에러다.
		if (!pInventory->canAdding(InvenX, InvenY, pItem)) goto ERROR;

		// 피의 성서일 경우 주울 수 있는지 확인한다. --> 이 코드는 isAbleToPickup 내부로 옮겼다..

		// 우선권이 붙어있는 아이템일 경우에는 주인 또는 주인파티가 아니라면 주을 수 없다.
		// 렐릭일 경우에는 우선순위 이펙트를 삭제해준다.
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
				// 시간이 지났다면 아무나 주을 수 있다. 더불어 여기서 이펙트를 삭제해준다.
				rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
				pItem->removeFlag(Effect::EFFECT_CLASS_PRECEDENCE);
			}
			else
			{
				// 시간이 아직 지나지 않았다면, 주인 또는 주인 파티만이 주을 수 있다.
				if ((pEffectPrecedence->getHostName() == pPC->getName()) ||
					(pPC->getPartyID() != 0 && pPC->getPartyID() == pEffectPrecedence->getHostPartyID()))
				{
					// 주을 수 있다. 이펙트를 삭제해 준다.
					rEffectManager.deleteEffect(Effect::EFFECT_CLASS_PRECEDENCE);
					pItem->removeFlag(Effect::EFFECT_CLASS_PRECEDENCE);
				}
				else
				{
					// 주을 수 없다.
					goto ERROR;
				}
			}
		}

/*
#ifdef __XMAS_EVENT_CODE__
		// 주으려는 아이템이 녹색 선물 상자라면,
		// 인벤토리에 녹색 선물 상자를 가지고 있다면 주을 수 없다.
		if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX &&
			pItem->getItemType() == 0 &&
			pInventory->hasGreenGiftBox()) goto ERROR;
#endif
*/

		// 전쟁시스템
		// 만약 같은 종족의 성물을 주웠다면, 자동으로 보관함으로 이동한다.
		// 보관함으로의 이동은 그냥 item을 삭제하고, 새로운 몬스터를 Regen하는
		// 것으로 설정한다.


		// 이미 같은 종류의 성물을 가지고 있다면 새 성물을 들지 못하도록 한다.
		// 이미 슬레이어 성물을 가지고 있다면 새로운 슬레이어 성물을 들지 못한다.
		Item::ItemClass itemclass = pItem->getItemClass();
		//ItemType_t itemtype = pItem->getItemType();
		
		TPOINT pt;
		pt.x = 99;
		pt.y = 99;
		// 아이템을 더할 자리에 다른 아이템이 있지 않은지 검사한다.
		Item* pPrevItem = pInventory->searchItem(InvenX, InvenY, pItem, pt);

		if (pPrevItem != NULL)
		{
			if (canStack(pItem, pPrevItem))
			{
				// add by sonic 2006.10.30  렝岺唐珂쇌掘齡膠틔렴瞳寧폅
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

						// 빼먹은거 같은뎅. by sigi. 2002.5.3
						// 근데.. 이게 문제가 아니고..
						// 존에서 주울때, 다 못 주으면 못 줍는거 아닌가..
						// 나머지는 다시 버려야 하는건가?
						// 이렇게 같은 좌표로 날아오는 경우가 있는가? 체크가 필요하겠지.
						// 현재는 없는거 같은데..으흠.. --;
						//pInventory->increaseNum(pItem->getNum());
						//pInventory->increaseWeight(pItem->getWeight()* pItem->getNum());

						pPrevItem->setNum(MaxStack);
						pItem->setNum(AddNum + CurrentNum - MaxStack);

						//pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
						// item저장 최적화. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "OwnerID='%s', Num=%d, Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), MaxStack, STORAGE_INVENTORY, InvenX, InvenY);
						pPrevItem->tinysave(pField);

						//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
						// item저장 최적화. by sigi. 2002.5.13
						sprintf(pField, "OwnerID='%s', Num=%d, Storage=%d", pPC->getName().c_str(), pItem->getNum(), STORAGE_EXTRASLOT);
						pItem->tinysave(pField);

					} 
					else 
					{
						pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());

						pInventory->increaseNum(pItem->getNum());
						pInventory->increaseWeight(pItem->getWeight()* pItem->getNum());

						//pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
						// item저장 최적화. by sigi. 2002.5.13
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
			// item저장 최적화. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "OwnerID='%s', Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), STORAGE_INVENTORY, InvenX, InvenY);
			pItem->tinysave(pField);

			// 벨트 안의 아이템들도 모두 소유권이 넘어가야 한다. 2003.3.22 by Sequoia
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
			// 암스밴드 안의 아이템들도 모두 소유권이 넘어가야 한다. 2003.3.22 by Sequoia
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
			// 밑에 있던거 옮김. - -; 2002.12.23
			pZone->deleteItem(pItem, ZoneX, ZoneY);

			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);
			// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
//			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject , pPC);
//			pZone->broadcastPacket(ZoneX , ZoneY, &_GCDeleteObject , pPC);
			pZone->broadcastPacket(ZoneX , ZoneY, &_GCDeleteObject);

			log(LOG_PICKUP_ITEM, pPC->getName(), "", pItem->toString());

			pItem->whenPCTake( pPC );

			// Relic 소유자 체크하기
			if (isRelicItem( itemclass ))
			{
				addRelicEffect( pPC, pItem );

				deleteEffectRelicPosition( pItem );
			}

			// Flag인 경우엔 Flag 를 붙여준다.
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

				// 주웠으면 존에 시스템 메세지 뿌려준다
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
				// 크리스마스 트리 조각이면
				if ( itemtype <= 11 )
				{
					TPOINT pt = checkEventTree( pPC, InvenX, InvenY );
					// 크리스마스 트리 조각이 맞춰지는지 본다.
					if ( pt.x != -1 && pt.y != -1 )
					{
						// 맞춰진 트리 조각을 지운다.
						deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );
						pItem = NULL;	// ㅋㅋ

						// 트리를 생성한다.
						list<OptionType_t> optionType;
						Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 12, optionType );
						pZone->getObjectRegistry().registerObject( pTreeItem );
						pInventory->addItem( pt.x, pt.y, pTreeItem );
						pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						// 클라이언트에 트리가 만들어졌다는 걸 알린다.
						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pTreeItem, pt.x, pt.y );
						pGamePlayer->sendPacket(&gcCreateItem);
					}
				}
			}
*/		
			if (Merge) 
			{
				// 합쳐졌을 경우 Item 객체를 삭제한다. 왜냐 숫자로 변신했기 땜에 -_-;
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
// 이벤트 코드가 들어가있는 버젼이다.
// 똑같은 이벤트가 또 실행될지도 모르니 지우지 말 것! -- by 김성민
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
		bool            Merge       = false; // 아이템이 겹쳐서 들어갈 경우 체크 변수
		bool            Success     = false; // 아이템을 Adding 할수 있는지 없는지 여부
		Zone*           pZone       = pPC->getZone();
		Coord_t         ZoneX       = pPacket->getZoneX();
		Coord_t         ZoneY       = pPacket->getZoneY();

		// 바운드를 넘어가지는 않는지 체크한다.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) goto ERROR;

		Tile& _Tile = pZone->getTile(ZoneX , ZoneY);

		// 타일에 아이템이 존재하는지를 체크한다.
		if (!_Tile.hasItem()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 아이템 포인터를 얻어낸다.
		Item* pItem = _Tile.getItem();
		if (pItem == NULL)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 아이템이 모터사이클이라면 주을 수가 없다.
		if (pItem->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// OID가 일치하는지를 검사해야 한다.
		ObjectID_t ItemObjectID = pItem->getObjectID();
		if (ItemObjectID != pPacket->getObjectID()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 바닥에 떨어져 있는 아이템이 이벤트용 해골이라면...
		// 인벤토리에 더하는 것이 아니라, 그냥 카운트만 올려줘야 한다.
		if (pItem->getItemClass() == Item::ITEM_CLASS_SKULL && 
			12 <= pItem->getItemType() && pItem->getItemType() <= 16)
		{
			uint scount = pGamePlayer->getSpecialEventCount();
			int  prev   = (int)(scount/10);
			int  cur    = 0;

			switch (pItem->getItemType())
			{
				case 12: scount += 1; break; // 황금 해골
				case 15: scount += 4; break; // 수정 해골
				case 14: scount += 9; break; // 검은 해골
				default: break;
			}

			// 카운트를 저장한다.
			pGamePlayer->setSpecialEventCount(scount);
			pGamePlayer->saveSpecialEventCount();
			cur = (int)(scount/10);

			// 존에서 아이템을 삭제한다.
			pZone->deleteItem(pItem, ZoneX, ZoneY);

			// 주은 놈에게 잘 주었다고 날려준다.
			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);

			// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject , pPC);

			// 마지막으로 실제 아이템 객체를 삭제한다.
			delete pItem;

			// 점수를 정기적으로 가르쳐준다.
			StringStream msg;
			msg << "당신의 현재 이벤트 점수는 " << pGamePlayer->getSpecialEventCount() << " 포인트 입니다.";
			GCSystemMessage gcMsg;
			gcMsg.setMessage(msg.toString());
			pPlayer->sendPacket(&gcMsg);

			// 점수를 정기적으로 브로드캐스팅한다.
			if (prev != cur)
			{
				StringStream msg;
				msg << pPC->getName() << "님께서 " << pGamePlayer->getSpecialEventCount() << " 포인트의 이벤트 점수를 획득하였습니다.";
				GCSystemMessage gcMsg;
				gcMsg.setMessage(msg.toString());
				pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcMsg , pPC);
			}

			return;
		}

		// Inventory를 받아온다.
		Inventory*   pInventory = pPC->getInventory();
		CoordInven_t InvenX     = pPacket->getInvenX();
		CoordInven_t InvenY     = pPacket->getInvenY();

		// 인벤토리 좌표 초과라면 에러다.
		if (InvenX >= 10 || InvenY >= 6)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 그 좌표에 아이템을 더할 수 없어도 에러다.
		if (!pInventory->canAdding(InvenX, InvenY, pItem)) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 아이템을 더할 자리에 다른 아이템이 있지 않은지 검사한다.
		Item* pPrevItem = pInventory->searchItem(InvenX, InvenY, pItem);

		if (pPrevItem != NULL)
		{
			if (canStack(pItem, pPrevItem))
			{
				// 숫자가 9개를 넘으면 9개 될때까지만 Add 하고 나머지는 마우스에 달아둔다.
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
					// 기존 슬랏에 있는 Item을 저장한다.
					pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());

					// 인벤토리의 총 숫자를 올려준다.
					pInventory->increaseNum(pItem->getNum());

					// 인벤토리의 총 무게를 올려준다.
					pInventory->increaseWeight(pItem->getWeight()* pItem->getNum());

					// 아이템을 저장한다.
					pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);

					// DB에서 삭제한다. 하나로 합쳐졌기 땜에...
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
			// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject , pPC);

			log(LOG_PICKUP_ITEM, pPC->getName(), "", pItem->toString());
		
			if (Merge) 
			{
				// 합쳐졌을 경우 Item 객체를 삭제한다. 왜냐 숫자로 변신했기 땜에 -_-;
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
