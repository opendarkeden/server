//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddZoneToMouseHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddZoneToMouse.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "CreatureUtil.h"
	#include "Timeval.h"
	#include "Relic.h"
	#include "RelicUtil.h"
	#include "EffectManager.h"
	#include "EffectPrecedence.h"
	//#include "EffectCombatMessage2.h"
	#include "EffectHasSlayerRelic.h"
	#include "EffectHasVampireRelic.h"
	#include "EffectRelicPosition.h"
	#include "EffectHasSweeper.h"
	#include "ZoneUtil.h"
	#include "CombatInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "BloodBible.h"
	#include "StringPool.h"
	#include "ShrineInfoManager.h"
	#include "Belt.h"
	#include "Sweeper.h"
	#include "OustersArmsband.h"

	#include "Gpackets/GCDeleteandPickUpOK.h"
	#include "Gpackets/GCDeleteObject.h"
	#include "Gpackets/GCCannotAdd.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCAddEffect.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddZoneToMouseHandler::execute (CGAddZoneToMouse* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	bool        Success     = false;

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*   pCreature   = pGamePlayer->getCreature();

		if (pCreature == NULL) return;
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

		Zone*       pZone   = pPC->getZone();
		ZoneCoord_t ZoneX   = pPacket->getZoneX();
		ZoneCoord_t ZoneY   = pPacket->getZoneY();

		// 바운드를 넘어가지는 않는지 체크한다.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) goto ERROR;

		Tile& _Tile = pZone->getTile(ZoneX, ZoneY);


		// 타일에 아이템이 없다면 당연히 더할 수 없다.
		if (!_Tile.hasItem()) goto ERROR;

		// 아이템 포인터가 널이거나, 주을 수 없는 아이템이라면 주을 수 없다.
		Item* pItem = _Tile.getItem();
		if (pItem == NULL || !isPortableItem(pItem)) goto ERROR;
		if (!isAbleToPickupItem(pPC, pItem)) goto ERROR;

		// 피의 성서일 경우 주울 수 있는지 확인한다. --> isAbleToPickupItem 내부에 넣었다.

		ObjectID_t ItemObjectID = pItem->getObjectID();

		// 아이템의 ObjectID가 일치하는지 체크한다.
		if (ItemObjectID == pPacket->getObjectID()) 
		{
			Item* pExtraItem = pPC->getExtraInventorySlotItem();

			// 이미 무언가를 들고 있다면, 아이템을 더할 수 없다.
			if (pExtraItem != NULL) goto ERROR;

			// 우선권이 붙어있는 아이템일 경우에는 주인 또는 주인파티가 아니라면 주을 수 없다.
			if (pItem->isFlag(Effect::EFFECT_CLASS_PRECEDENCE))
			{
				Timeval currentTime;
				getCurrentTime(currentTime);

				EffectManager& rEffectManager = pItem->getEffectManager();

				EffectPrecedence* pEffectPrecedence = dynamic_cast<EffectPrecedence*>(rEffectManager.findEffect(Effect::EFFECT_CLASS_PRECEDENCE));
				Assert(pEffectPrecedence != NULL);

				// Relic이면 아무나 주울 수 있다.
				if (isRelicItem( pItem )
					|| pEffectPrecedence->getDeadline() < currentTime)
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
			Inventory* pInventory = pPC->getInventory();
			// 주으려는 아이템이 녹색 선물 상자라면,
			// 인벤토리에 녹색 선물 상자를 가지고 있다면 주을 수 없다.
			if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX &&
				pItem->getItemType() == 0 &&
				pInventory->hasGreenGiftBox()) goto ERROR;
#endif
*/
			pItem->whenPCTake(pPC);

			Item::ItemClass itemclass = pItem->getItemClass();
			//ItemType_t itemtype = pItem->getItemType();

			// relic인 경우는 이미 갖고 있는 relic종류를 또 가질 수는 없다.
			// 가질 수 있다면 relic을 가졌다는 effect를 걸어주고
			// CombatInfoManager에 소유자 값을 설정해준다.
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
//				addSimpleCreatureEffect( pPC, (Effect::EffectClass)(Effect::EFFECT_CLASS_HAS_SWEEPER + pItem->getItemType()) );

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

			pZone->deleteItem(pItem,ZoneX, ZoneY);
			pPC->addItemToExtraInventorySlot(pItem);

			// 주은 놈에게 잘 주었다고 결과를 알려준다.
			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);

			// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
//			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject, pPC);
//			pZone->broadcastPacket(ZoneX, ZoneY, &_GCDeleteObject, pPC);
			pZone->broadcastPacket(ZoneX, ZoneY, &_GCDeleteObject);

			Success = true;

			// 아이템을 저장한다.
			//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
			// item저장 최적화. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "OwnerID='%s', Storage=%d", pPC->getName().c_str(), STORAGE_EXTRASLOT);
			pItem->tinysave(pField);

			// 벨트일 경우 벨트 안의 아이템들도 모두 소유권이 넘어가야 한다. 2003.3.22 by Sequoia
			if ( pItem->getItemClass() == Item::ITEM_CLASS_BELT )
			{
	            sprintf(pField, "OwnerID='%s'", pPC->getName().c_str());

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
			// 암스밴드일 경우 안의 아이템들도 모두 소유권이 넘어가야 한다. 2003.3.22 by Sequoia
			if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_ARMSBAND )
			{
	            sprintf(pField, "OwnerID='%s'", pPC->getName().c_str());

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

			if ( pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 30 )
			{
				unsigned long timeLimit = 3600 * 24;

				pPC->addTimeLimitItem( pItem, timeLimit );
				pPC->sendTimeLimitItemInfo();
				pPC->setBaseLuck(10);
				pPC->initAllStatAndSend();
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
		//cerr << t.toString();
	}

ERROR:
	if (!Success)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 이벤트 코드가 들어가있는 버전이다.
// 똑같은 이벤트가 또 실행될 지 모르니, 지우지 말 것! -- by 김성민
//////////////////////////////////////////////////////////////////////////////
/*
void CGAddZoneToMouseHandler::execute (CGAddZoneToMouse* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*   pCreature   = pGamePlayer->getCreature();
		bool        Success     = false;

		if (pCreature == NULL) return;
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

		Zone*       pZone   = pPC->getZone();
		ZoneCoord_t ZoneX   = pPacket->getZoneX();
		ZoneCoord_t ZoneY   = pPacket->getZoneY();

		// 바운드를 넘어가지는 않는지 체크한다.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) goto ERROR;

		Tile& _Tile = pZone->getTile(ZoneX, ZoneY);

		// 타일에 아이템이 없다면 당연히 더할 수 없다.
		if (!_Tile.hasItem())
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 아이템 포인터가 널이라면 당연히 더할 수 없다.
		Item* pItem = _Tile.getItem();
		if (pItem == NULL)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		ObjectID_t ItemObjectID = pItem->getObjectID();

		// 아이템의 ObjectID가 일치하는지 체크한다.
		if (ItemObjectID == pPacket->getObjectID()) 
		{
			Item* pExtraItem = pPC->getExtraInventorySlotItem();

			// 이미 무언가를 들고 있다면, 아이템을 더할 수 없다.
			if (pExtraItem != NULL) 
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			// 바닥에 떨어져 있는 아이템이 이벤트용 해골이라면...
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
				cur = scount/10;

				// 존에서 아이템을 삭제한다.
				pZone->deleteItem(pItem, ZoneX, ZoneY);

				// 주은 놈에게 잘 주었다고 날려준다.
				GCDeleteandPickUpOK _GCDeleteandPickUpOK;
				GCDeleteObject _GCDeleteObject;
				_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
				pPlayer->sendPacket(&_GCDeleteandPickUpOK); 
				// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
				_GCDeleteObject.setObjectID(pItem->getObjectID());
				pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject, pPC);

				// 마지막으로 실제 아이템 객체를 삭제한다.
				SAFE_DELETE(pItem);

				// 점수를 정기적으로 가르쳐준다.
				StringStream msg;
				msg << "당신의 현재 이벤트 포인트는 " << pGamePlayer->getSpecialEventCount() << " 포인트 입니다.";
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
					pPlayer->sendPacket(&gcMsg);
					pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcMsg , pPC);
				}

				return;
			}

			// 존에서 아이템을 삭제하고, 마우스에다 달아준다.
			pZone->deleteItem(pItem, ZoneX, ZoneY);
			pPC->addItemToExtraInventorySlot(pItem);

			// 주은 놈에게 잘 주었다고 결과를 알려준다.
			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);

			// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject, pPC);

			Success = true;

			// 아이템을 저장한다.
			pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
		}

		if (!Success) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
		}
	} 
	catch (Throwable & t) 
	{
		//cerr << t.toString();
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH

}
*/
