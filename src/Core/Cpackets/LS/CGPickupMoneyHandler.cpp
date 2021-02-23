//////////////////////////////////////////////////////////////////////////////
// Filename    : CGPickupMoneyHandler.cc
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGPickupMoney.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "LogClient.h"
	#include "ZoneUtil.h"

	#include "VariableManager.h"

	#include "item/Money.h"

	#include "Gpackets/GCDeleteandPickUpOK.h"
	#include "Gpackets/GCDeleteObject.h"
	#include "Gpackets/GCCannotAdd.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGPickupMoneyHandler::execute (CGPickupMoney* pPacket, Player* pPlayer)
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
		bool        bSuccess    = false; 
		bool        bMargin     = false;
		Gold_t      itemGold    = 0;
		Gold_t      currentGold = 0;
		Gold_t      marginGold  = 0;
		Slayer*     pSlayer     = NULL;
		Vampire*    pVampire    = NULL;
		Ousters*    pOusters    = NULL;
		Zone*       pZone       = NULL;
		Coord_t     ZoneX       = pPacket->getZoneX();
		Coord_t     ZoneY       = pPacket->getZoneY();

		if (pCreature->isSlayer()) 
		{
			pSlayer = dynamic_cast<Slayer*>(pCreature);
			pZone   = pSlayer->getZone();
		}
		else if (pCreature->isVampire())
		{
			pVampire = dynamic_cast<Vampire*>(pCreature);
			pZone    = pVampire->getZone();
		}
		else if (pCreature->isOusters())
		{
			pOusters = dynamic_cast<Ousters*>(pCreature);
			pZone    = pOusters->getZone();
		}
		else throw ProtocolException("CGDropMoneyHandler::execute() : 알 수 없는 플레이어 크리쳐.");
		
		Assert(pZone != NULL);

		// 바운드를 넘어가면 안 된다. 
		if (!isValidZoneCoord(pZone, ZoneX, ZoneY))
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 타일에 아이템이 없다면 리턴이다.
		Tile& _Tile = pZone->getTile(ZoneX, ZoneY);
		if (!_Tile.hasItem()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		Item* pItem = _Tile.getItem();
		Assert(pItem != NULL);
		Item::ItemClass IClass = pItem->getItemClass();
		ObjectID_t ObjectID    = pItem->getObjectID();

		// 아이템이 돈이 맞는지, 그리고 오브젝트 ID가 맞는지 체크한다.
		if ((IClass == Item::ITEM_CLASS_MONEY) && (ObjectID == pPacket->getObjectID()))
		{ 
			Money* pMoney = dynamic_cast<Money*>(pItem);
			itemGold      = pMoney->getAmount();
			marginGold    = 0;

			if (pCreature->isSlayer()) currentGold = pSlayer->getGold();
			else if (pCreature->isVampire()) currentGold = pVampire->getGold();
			else if (pCreature->isOusters()) currentGold = pOusters->getGold();

			// 상대방의 돈은 들지 못한다.
			
			if ( (pCreature->isSlayer() && pItem->getItemType() != 0) ||
			     (pCreature->isVampire() && pItem->getItemType() != 1) ||
			     (pCreature->isOusters() && pItem->getItemType() != 2) 
			)
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}
			

			if (currentGold + itemGold > MAX_MONEY)
			{
				// 현재 소유한 돈에다 바닥에 있는 돈을 더하면 맥스를 초과할 경우
				// 바닥에 있는 돈의 일부만을 주워야 한다.
				Gold_t pickupMoney = MAX_MONEY - currentGold;
				marginGold = currentGold + itemGold - MAX_MONEY;
				pMoney->setAmount(marginGold);

				//if (pCreature->isSlayer()) pSlayer->setGoldEx(MAX_MONEY);
				//else                       pVampire->setGoldEx(MAX_MONEY);
				// by sigi. 2002.9.4
				if (pCreature->isSlayer()) pSlayer->increaseGoldEx(pickupMoney);
				else if (pCreature->isVampire()) pVampire->increaseGoldEx(pickupMoney);
				else if (pCreature->isOusters()) pOusters->increaseGoldEx(pickupMoney);

				bSuccess = true;
				bMargin  = true;
			}
			else
			{
				//if (pCreature->isSlayer()) pSlayer->setGoldEx(currentGold + itemGold);
				//else                       pVampire->setGoldEx(currentGold + itemGold);
				// by sigi. 2002.9.4
				if (pCreature->isSlayer()) pSlayer->increaseGoldEx(itemGold);
				else if (pCreature->isVampire()) pVampire->increaseGoldEx(itemGold);
				else if (pCreature->isOusters()) pOusters->increaseGoldEx(itemGold);

				bSuccess = true;
				bMargin  = false;
			}
		}
		else // 돈이 아닐 경우에는 그냥 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		if (bSuccess) 
		{
			log(LOG_PICKUP_MONEY, pCreature->getName(), "", pItem->toString());

			// 일단은 존으로부터 아이템을 삭제한다.
			pZone->deleteItem(pItem, ZoneX, ZoneY);

			GCDeleteandPickUpOK _GCDeleteandPickUpOK;
			_GCDeleteandPickUpOK.setObjectID(pItem->getObjectID());
			pPlayer->sendPacket(&_GCDeleteandPickUpOK);

			if (pCreature->isSlayer())
			{
				// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
				GCDeleteObject _GCDeleteObject;
				_GCDeleteObject.setObjectID(pItem->getObjectID());
				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &_GCDeleteObject , pSlayer);
			}
			else if (pCreature->isVampire())
			{
				// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
				GCDeleteObject _GCDeleteObject;
				_GCDeleteObject.setObjectID(pItem->getObjectID());
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &_GCDeleteObject , pVampire);
			}
			else if (pCreature->isOusters())
			{
				// 근처에 있는 다른 사람들에겐 아이템에 사라졌다는 것을 보내준다.
				GCDeleteObject _GCDeleteObject;
				_GCDeleteObject.setObjectID(pItem->getObjectID());
				pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &_GCDeleteObject , pOusters);
			}

			// 돈이 남아있다면 남아있는 액수만큼의 돈을 다시 생성해서 떨어뜨린다.
			if (bMargin)
			{
				TPOINT pt = pZone->addItem(pItem, ZoneX, ZoneY);
				if (pt.x != -1) 
				{
					//pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);	
					// item저장 최적화. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Storage=%d, StorageID=%lu, X=%d, Y=%d", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
					pItem->tinysave(pField);

				}
				else
				{
					// 돈을 떨어뜨리지 못했다면 그냥 삭제한다.
					//cout << "#############################################" << endl;
					//cout << "# CRITICAL ERROR! CANNOT ADD MONEY TO ZONE! #" << endl;
					//cout << "#############################################" << endl;

					SAFE_DELETE(pItem);
				}
			}
			else
			{
				pItem->destroy();
				SAFE_DELETE(pItem);
			}

			// 돈로그 남길 액수면 돈로그 남긴다
			if ( (itemGold - marginGold) >= g_pVariableManager->getMoneyTraceLogLimit() )
			{
				char zoneName[15];
				sprintf(zoneName, "%4d%3d%3d", pZone->getZoneID(), ZoneX, ZoneY);
				remainMoneyTraceLog( zoneName, pCreature->getName(), ITEM_LOG_MOVE, DETAIL_PICKUP, itemGold - marginGold );
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
		//cout << t.toString() << endl; 
	}

#endif	// __GAME_SERVER__

	__END_DEBUG
	__END_DEBUG_EX __END_CATCH
}


