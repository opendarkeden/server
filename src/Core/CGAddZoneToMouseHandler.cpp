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

	#include "GCDeleteandPickUpOK.h"
	#include "GCDeleteObject.h"
	#include "GCCannotAdd.h"
	#include "GCSystemMessage.h"
	#include "GCAddEffect.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddZoneToMouseHandler::execute (CGAddZoneToMouse* pPacket , Player* pPlayer)
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

		// �ٿ�带 �Ѿ���� �ʴ��� üũ�Ѵ�.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) goto ERROR;

		Tile& _Tile = pZone->getTile(ZoneX, ZoneY);


		// Ÿ�Ͽ� �������� ���ٸ� �翬�� ���� �� ����.
		if (!_Tile.hasItem()) goto ERROR;

		// ������ �����Ͱ� ���̰ų�, ���� �� ���� �������̶�� ���� �� ����.
		Item* pItem = _Tile.getItem();
		if (pItem == NULL || !isPortableItem(pItem)) goto ERROR;
		if (!isAbleToPickupItem(pPC, pItem)) goto ERROR;

		// ���� ������ ��� �ֿ� �� �ִ��� Ȯ���Ѵ�. --> isAbleToPickupItem ���ο� �־���.

		ObjectID_t ItemObjectID = pItem->getObjectID();

		// �������� ObjectID�� ��ġ�ϴ��� üũ�Ѵ�.
		if (ItemObjectID == pPacket->getObjectID()) 
		{
			Item* pExtraItem = pPC->getExtraInventorySlotItem();

			// �̹� ���𰡸� ��� �ִٸ�, �������� ���� �� ����.
			if (pExtraItem != NULL) goto ERROR;

			// �켱���� �پ��ִ� �������� ��쿡�� ���� �Ǵ� ������Ƽ�� �ƴ϶�� ���� �� ����.
			if (pItem->isFlag(Effect::EFFECT_CLASS_PRECEDENCE))
			{
				Timeval currentTime;
				getCurrentTime(currentTime);

				EffectManager& rEffectManager = pItem->getEffectManager();

				EffectPrecedence* pEffectPrecedence = dynamic_cast<EffectPrecedence*>(rEffectManager.findEffect(Effect::EFFECT_CLASS_PRECEDENCE));
				Assert(pEffectPrecedence != NULL);

				// Relic�̸� �ƹ��� �ֿ� �� �ִ�.
				if (isRelicItem( pItem )
					|| pEffectPrecedence->getDeadline() < currentTime)
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
			Inventory* pInventory = pPC->getInventory();
			// �������� �������� ��� ���� ���ڶ��,
			// �κ��丮�� ��� ���� ���ڸ� ������ �ִٸ� ���� �� ����.
			if (pItem->getItemClass() == Item::ITEM_CLASS_EVENT_GIFT_BOX &&
				pItem->getItemType() == 0 &&
				pInventory->hasGreenGiftBox()) goto ERROR;
#endif
*/
			pItem->whenPCTake(pPC);

			Item::ItemClass itemclass = pItem->getItemClass();
			//ItemType_t itemtype = pItem->getItemType();

			// relic�� ���� �̹� ���� �ִ� relic������ �� ���� ���� ����.
			// ���� �� �ִٸ� relic�� �����ٴ� effect�� �ɾ��ְ�
			// CombatInfoManager�� ������ ���� �������ش�.
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
//				addSimpleCreatureEffect( pPC, (Effect::EffectClass)(Effect::EFFECT_CLASS_HAS_SWEEPER + pItem->getItemType()) );

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

			pZone->deleteItem(pItem,ZoneX, ZoneY);
			pPC->addItemToExtraInventorySlot(pItem);

			// ���� �𿡰� �� �־��ٰ� ����� �˷��ش�.
			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);

			// ��ó�� �ִ� �ٸ� ����鿡�� �����ۿ� ������ٴ� ���� �����ش�.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
//			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject, pPC);
//			pZone->broadcastPacket(ZoneX, ZoneY, &_GCDeleteObject, pPC);
			pZone->broadcastPacket(ZoneX, ZoneY, &_GCDeleteObject);

			Success = true;

			// �������� �����Ѵ�.
			//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
			// item���� ����ȭ. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "OwnerID='%s', Storage=%d", pPC->getName().c_str(), STORAGE_EXTRASLOT);
			pItem->tinysave(pField);

			// ��Ʈ�� ��� ��Ʈ ���� �����۵鵵 ��� �������� �Ѿ�� �Ѵ�. 2003.3.22 by Sequoia
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
			// �Ͻ������ ��� ���� �����۵鵵 ��� �������� �Ѿ�� �Ѵ�. 2003.3.22 by Sequoia
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
// �̺�Ʈ �ڵ尡 ���ִ� �����̴�.
// �Ȱ��� �̺�Ʈ�� �� ����� �� �𸣴�, ������ �� ��! -- by �輺��
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

		// �ٿ�带 �Ѿ���� �ʴ��� üũ�Ѵ�.
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY)) goto ERROR;

		Tile& _Tile = pZone->getTile(ZoneX, ZoneY);

		// Ÿ�Ͽ� �������� ���ٸ� �翬�� ���� �� ����.
		if (!_Tile.hasItem())
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// ������ �����Ͱ� ���̶�� �翬�� ���� �� ����.
		Item* pItem = _Tile.getItem();
		if (pItem == NULL)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		ObjectID_t ItemObjectID = pItem->getObjectID();

		// �������� ObjectID�� ��ġ�ϴ��� üũ�Ѵ�.
		if (ItemObjectID == pPacket->getObjectID()) 
		{
			Item* pExtraItem = pPC->getExtraInventorySlotItem();

			// �̹� ���𰡸� ��� �ִٸ�, �������� ���� �� ����.
			if (pExtraItem != NULL) 
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			// �ٴڿ� ������ �ִ� �������� �̺�Ʈ�� �ذ��̶��...
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
				cur = scount/10;

				// ������ �������� �����Ѵ�.
				pZone->deleteItem(pItem, ZoneX, ZoneY);

				// ���� �𿡰� �� �־��ٰ� �����ش�.
				GCDeleteandPickUpOK _GCDeleteandPickUpOK;
				GCDeleteObject _GCDeleteObject;
				_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
				pPlayer->sendPacket(&_GCDeleteandPickUpOK); 
				// ��ó�� �ִ� �ٸ� ����鿡�� �����ۿ� ������ٴ� ���� �����ش�.
				_GCDeleteObject.setObjectID(pItem->getObjectID());
				pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject, pPC);

				// ���������� ���� ������ ��ü�� �����Ѵ�.
				SAFE_DELETE(pItem);

				// ������ ���������� �������ش�.
				StringStream msg;
				msg << "����� ���� �̺�Ʈ ����Ʈ�� " << pGamePlayer->getSpecialEventCount() << " ����Ʈ �Դϴ�.";
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
					pPlayer->sendPacket(&gcMsg);
					pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcMsg , pPC);
				}

				return;
			}

			// ������ �������� �����ϰ�, ���콺���� �޾��ش�.
			pZone->deleteItem(pItem, ZoneX, ZoneY);
			pPC->addItemToExtraInventorySlot(pItem);

			// ���� �𿡰� �� �־��ٰ� ����� �˷��ش�.
			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			GCDeleteObject _GCDeleteObject;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);

			// ��ó�� �ִ� �ٸ� ����鿡�� �����ۿ� ������ٴ� ���� �����ش�.
			_GCDeleteObject.setObjectID(pItem->getObjectID());
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &_GCDeleteObject, pPC);

			Success = true;

			// �������� �����Ѵ�.
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
