//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestRepairHandler.cpp
// Written By  : 김성민
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestRepair.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "ItemUtil.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "PriceManager.h"
	#include "LogClient.h"
	#include "ZoneUtil.h"

	#include "item/Key.h"
	#include "item/SlayerPortalItem.h"
	#include "item/OustersSummonItem.h"

	#include "Gpackets/GCNPCResponse.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairHandler::execute (CGRequestRepair* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	ObjectID_t  ITEMOID     = pPacket->getObjectID();
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	bool        bSlayer     = false;
	bool        bVampire    = false;
	bool        bOusters    = false;
	Item*       pItem       = NULL;
	
	// 플레이어가 슬레이어인지 뱀파이어인지 구분.
	if (pPC->isSlayer())       bSlayer = true;
	else if (pPC->isVampire()) bVampire = true;
	else if (pPC->isOusters()) bOusters = true;
	else throw ProtocolException("CGRequestRepairHandler::execute() : Unknown player creature!");

	if (ITEMOID == 0)
	{
		// ObjectID가 0이라면 모든 아이템을 수리하고자 하는 것이다.
		executeAll(pPacket, pPlayer);
	}
	else
	{
		if (bSlayer) pItem = (dynamic_cast<Slayer*>(pPC))->findItemOID(ITEMOID);
		else if (bVampire) pItem = (dynamic_cast<Vampire*>(pPC))->findItemOID(ITEMOID);
		else if (bOusters) pItem = (dynamic_cast<Ousters*>(pPC))->findItemOID(ITEMOID);

		// 플레이어가 아이템을 가지고 있다면
		if (pItem != NULL)
		{
			// 그 아이템이 모터 사이클 키라면...
			if (pItem->getItemClass() == Item::ITEM_CLASS_KEY && pItem->getItemType() == 2)
			{
				executeMotorcycle(pPacket, pPlayer);
				return;
			}
			else executeNormal(pPacket, pPlayer);
		}
		else
		{
			// 아이템이 없으니, 당연히 수리할 수 없다.
			GCNPCResponse response;
			response.setCode(NPC_RESPONSE_REPAIR_FAIL_ITEM_NOT_EXIST);
			pPlayer->sendPacket(&response);
		}
	}
	
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 일반 아이템을 처리한다.
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairHandler::executeNormal (CGRequestRepair* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	ObjectID_t    ITEMOID       = pPacket->getObjectID();
	Creature*     pPC           = dynamic_cast<GamePlayer*>(pPlayer)->getCreature();
	bool          bSlayer       = false;
	bool          bVampire      = false;
	bool          bOusters      = false;
	Gold_t        playerMoney   = 0;
	Price_t       repairPrice   = 0;
	Item*         pItem         = NULL;
	Slayer*       pSlayer       = NULL;
	Vampire*      pVampire      = NULL;
	Ousters*      pOusters      = NULL;
	int           storage       = 0;
	int           X             = 0;
	int           Y             = 0;
	GCNPCResponse response;

	// 플레이어가 슬레이어인지 뱀파이어인지 구분.
	if (pPC->isSlayer())       bSlayer = true;
	else if (pPC->isVampire()) bVampire = true;
	else if (pPC->isOusters()) bOusters = true;

	// 플레이어가 수리하려고 하는 아이템을 가지고 있는지 검사
	if (bSlayer)
	{
		pSlayer     = dynamic_cast<Slayer*>(pPC);
		playerMoney = pSlayer->getGold();
		pItem       = pSlayer->findItemOID(ITEMOID, storage, X, Y);
	}
	else if (bVampire)
	{
		pVampire    = dynamic_cast<Vampire*>(pPC);
		playerMoney = pVampire->getGold();
		pItem       = pVampire->findItemOID(ITEMOID, storage, X, Y);
	}
	else if (bOusters)
	{
		pOusters    = dynamic_cast<Ousters*>(pPC);
		playerMoney = pOusters->getGold();
		pItem       = pOusters->findItemOID(ITEMOID, storage, X, Y);
	}

	// 플레이어가 수리하려고 하는 아이템을 가지고 있는지 
	// 상위에서 검사를 하기 때문에, pItem이 널일리는 없다.
	// 단, 수리할 수 없는 아이템인지를 검사한다.
	if (isRepairableItem(pItem) == false)
	{
		response.setCode(NPC_RESPONSE_REPAIR_FAIL_ITEM_TYPE);
		pPlayer->sendPacket(&response);
		return;
	}

	repairPrice = g_pPriceManager->getRepairPrice(pItem);

	if (repairPrice > playerMoney)
	{
		response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
		pPlayer->sendPacket(&response);
		return;
	}

	// 수리한다.
	repairItem(pItem);

	// 돈을 줄인다.
	if (bSlayer)
	{
		//pSlayer->setGoldEx(playerMoney-repairPrice);
		// by sigi. 2002.9.4
		pSlayer->decreaseGoldEx(repairPrice);
		log(LOG_REPAIR_ITEM, pSlayer->getName(), "", pItem->toString());
	}
	else if (bVampire)
	{
		// by sigi. 2002.9.4
		pVampire->decreaseGoldEx(repairPrice);
		log(LOG_REPAIR_ITEM, pVampire->getName(), "", pItem->toString());
	}
	else if (bOusters)
	{
		// by sigi. 2002.9.4
		pOusters->decreaseGoldEx(repairPrice);
		log(LOG_REPAIR_ITEM, pOusters->getName(), "", pItem->toString());
	}

	// 아이템을 수리했다는 정보를 DB에다가 저장해준다.
	// 단 분명히 STORAGE_STASH가 돌아올 수 있지만, 
	// 보관함에 있는 것을 수리한다는 것은 말이 안 되므로,
	// 저장하지 않는다.


	// item저장 최적화. by sigi. 2002.5.17
	if (repairPrice>0)
	{
		char pField[80];

		if (pItem->getItemClass()==Item::ITEM_CLASS_SLAYER_PORTAL_ITEM)
		{
			SlayerPortalItem* pSPItem = dynamic_cast<SlayerPortalItem*>(pItem);
			sprintf(pField, "Charge=%d", pSPItem->getCharge());
		}
		else if (pItem->getItemClass()==Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM)
		{
			OustersSummonItem* pOSItem = dynamic_cast<OustersSummonItem*>(pItem);
			sprintf(pField, "Charge=%d", pOSItem->getCharge());
		}
		else
		{
			sprintf(pField, "Durability=%d", pItem->getDurability());
		}

		pItem->tinysave(pField);
	}

	/*
	// 뭐가 됐든.. durability만 바꾸면 된다.
	// 근데.. ItemObject에 Durability field가 없는 것도 있고
	// Charge를 저장해야 하는 것도 있다.
	// 그래서.. 일단은 모두 다 저장하는 save를 이용하도록 한다.
	switch (storage)
	{
		case STORAGE_INVENTORY:
		{
			pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, X, Y);
		}
		break;

		case STORAGE_GEAR:
		{
			if (bSlayer) 
			{
				pItem->save(pSlayer->getName(),  STORAGE_GEAR, 0, X, 0);
			}
			else         
			{
				pItem->save(pVampire->getName(), STORAGE_GEAR, 0, X, 0);
			}
		}
		break;

		default:
			break;
	}
	*/

	// OK 패킷을 날려준다.
	response.setCode(NPC_RESPONSE_REPAIR_OK);
	response.setParameter(playerMoney-repairPrice);
	pPlayer->sendPacket(&response);

#endif

	__END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 모터 사이클을 처리한다.
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairHandler::executeMotorcycle (CGRequestRepair* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	// 패킷 정보를 뽑아낸다.
	ObjectID_t      ITEMOID     = pPacket->getObjectID();
	Creature*       pPC         = dynamic_cast<GamePlayer*>(pPlayer)->getCreature();
	Zone*           pZone       = pPC->getZone();
	Gold_t          playerMoney = 0;
	ZoneCoord_t     CenterX     = pPC->getX();
	ZoneCoord_t     CenterY     = pPC->getY();
	Item*           pItem       = NULL;
	bool            bSlayer     = false;
	bool            bVampire    = false;
	bool            bOusters    = false;
	GCNPCResponse   response;
	
	// 플레이어가 슬레이어인지 뱀파이어인지 구분.
	if (pPC->isSlayer())       bSlayer = true;
	else if (pPC->isVampire()) bVampire = true;
	else if (pPC->isOusters()) bOusters = true;
	else throw ProtocolException("CGRequestRepairHandler::execute() : Unknown player creature!");

	// 플레이어가 수리하려고 하는 아이템을 가지고 있는지 
	// 상위에서 검사를 하기 때문에, pItem이 널일리는 없다.
	if (bSlayer)
	{
		pItem       = (dynamic_cast<Slayer*>(pPC))->findItemOID(ITEMOID);
		playerMoney = (dynamic_cast<Slayer*>(pPC))->getGold();
	}
	else if (bVampire)
	{
		pItem       = (dynamic_cast<Vampire*>(pPC))->findItemOID(ITEMOID);
		playerMoney = (dynamic_cast<Vampire*>(pPC))->getGold();
	}
	else if (bOusters)
	{
		pItem       = (dynamic_cast<Ousters*>(pPC))->findItemOID(ITEMOID);
		playerMoney = (dynamic_cast<Ousters*>(pPC))->getGold();
	}

	// 주위 일정 범위를 검색해서, 모터 사이클이 있는지 확인한다.
	for (ZoneCoord_t zx=CenterX-5; zx<=CenterX+5; zx++)
	{
		for (ZoneCoord_t zy=CenterY-5; zy<=CenterY+5; zy++)
		{
			if (!isValidZoneCoord(pZone, zx, zy)) continue;

			Tile & tile = pZone->getTile(zx, zy);

			if (tile.hasItem())
			{
				Item* pItemOnTile = tile.getItem();
				Assert(pItemOnTile != NULL);

				// 만일 아이템이 타일 위에 있을 경우, 모터 사이클인지 확인한다.
				if (pItemOnTile->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE)
				{
					DWORD    targetID     = dynamic_cast<Key*>(pItem)->getTarget();
					ItemID_t motorcycleID = pItemOnTile->getItemID();

					if (targetID == motorcycleID)
					{
						Price_t repairPrice = g_pPriceManager->getRepairPrice(pItemOnTile);

						if (repairPrice > playerMoney)
						{
							response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
							pPlayer->sendPacket(&response);
							return;
						}

						// 수리한다.
						repairItem(pItemOnTile);

						// 저장한다.
						//pItemOnTile->save(pPC->getName(), STORAGE_ZONE, pZone->getZoneID(), zx, zy);
						// item저장 최적화. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Durability=%d", pItemOnTile->getDurability());
						pItemOnTile->tinysave(pField);


						// 돈을 줄인다.
						//if (bSlayer) (dynamic_cast<Slayer*>(pPC))->setGoldEx(playerMoney-repairPrice);
						//else         (dynamic_cast<Vampire*>(pPC))->setGoldEx(playerMoney-repairPrice);

						// by sigi. 2002.9.4
						(dynamic_cast<PlayerCreature*>(pPC))->decreaseGoldEx(repairPrice);

						response.setCode(NPC_RESPONSE_REPAIR_OK);
						response.setParameter(playerMoney-repairPrice);
						pPlayer->sendPacket(&response);

						return;
					} // if (targetID == 
				} // if (itemclas == MOTORCYCLE
			}
		} // end of for (ZoneCoord_t zy=CenterY-5; zy<=CenterY+5; zy++)
	} // end of for (ZoneCoord_t zx=CenterX-5; zx<=CenterX+5; zx++)

	// FOR 루프를 다 돌고, 이까지 왔다는 것은 근처에 오토바이가 없다는 말이당...
	// 그러므로 모터 사이클 팔기가 실패했다는 것을 알린다.
	response.setCode(NPC_RESPONSE_REPAIR_FAIL_ITEM_NOT_EXIST);
	pPlayer->sendPacket(&response);
	
#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 모든 아이템 수리하기
//////////////////////////////////////////////////////////////////////////////
void CGRequestRepairHandler::executeAll(CGRequestRepair* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Creature*     pPC         = dynamic_cast<GamePlayer*>(pPlayer)->getCreature();
	Price_t       repairPrice = 0;
	GCNPCResponse response;

	if (pPC->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);

		// 모든 아이템을 합한 수리비를 계산한다.
		for (int i=0; i<Slayer::WEAR_MAX; i++)
		{
			Item* pItem = pSlayer->getWearItem((Slayer::WearPart)i);
			if (pItem != NULL)
			{
				if (i == Slayer::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// 오른손이고, 현재 들고 있는 무기가 양손 무기라면...
					// 수리 가격에 포함시킬 필요가 없다.
				}
				else
				{
					repairPrice += g_pPriceManager->getRepairPrice(pItem);
				}
			}
		}

		// 돈이 모자라다면 리턴한다.
		if (pSlayer->getGold() < repairPrice)
		{
			response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
			pPlayer->sendPacket(&response);
			return;
		}

		// 각각의 아이템을 수리하고, DB에 저장한다.
		char pField[80];

		for (int i=0; i<Slayer::WEAR_MAX; i++)
		{
			Item* pItem = pSlayer->getWearItem((Slayer::WearPart)i);
			if (pItem != NULL)
			{
				if (i == Slayer::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// 오른손이고, 현재 들고 있는 무기가 양손 무기라면...
					// 수리할 필요가 없다.
				}
				else if ( isRepairableItem( pItem ) )
				{
					Durability_t oldDurability = pItem->getDurability();
					repairItem(pItem);
					if (pItem->getDurability() != oldDurability)
					{
						// DB 쿼리를 줄이기 위해서
						// 내구도의 변화가 생긴 경우에만 세이브한다.
						//pItem->save(pSlayer->getName(), STORAGE_GEAR, 0, i, 0);
						// item저장 최적화. by sigi. 2002.5.13
						sprintf(pField, "Durability=%d", pItem->getDurability());
						pItem->tinysave(pField);
					}
				}
			}
		}

		// 돈을 줄이고...
		//pSlayer->setGoldEx(pSlayer->getGold() - repairPrice);

		// by sigi.2002.9.4
		pSlayer->decreaseGoldEx(repairPrice);

		// 로그를 남긴다.
		log(LOG_REPAIR_ITEM, pSlayer->getName(), "", "ALL");

		// OK 패킷을 날려준다.
		response.setCode(NPC_RESPONSE_REPAIR_OK);
		response.setParameter(pSlayer->getGold());
		pPlayer->sendPacket(&response);
	}
	else if (pPC->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);

		// 모든 아이템을 합한 수리비를 계산한다.
		for (int i=0; i<Vampire::VAMPIRE_WEAR_MAX; i++)
		{
			Item* pItem = pVampire->getWearItem((Vampire::WearPart)i);
			if (pItem != NULL) 
			{
				if (i == Vampire::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// 양손무기는 한쪽만 수리한다.
				}
				else
				{
					repairPrice += g_pPriceManager->getRepairPrice(pItem);
				}
			}
		}

		// 돈이 모자라다면 리턴한다.
		if (pVampire->getGold() < repairPrice)
		{
			response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
			pPlayer->sendPacket(&response);
			return;
		}
 
		// 각각의 아이템을 수리하고, DB에 저장한다.
		char pField[80];

		for (int i=0; i<Vampire::VAMPIRE_WEAR_MAX; i++)
		{
			Item* pItem = pVampire->getWearItem((Vampire::WearPart)i);
			if (pItem != NULL)
			{
				if (i == Vampire::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// 양손무기는 한쪽만 수리한다.
				}
				else
				{
					Durability_t oldDurability = pItem->getDurability();
					repairItem(pItem);
					if (pItem->getDurability() != oldDurability)
					{
						// DB 쿼리를 줄이기 위해서
						// 내구도의 변화가 생긴 경우에만 세이브한다.
						//pItem->save(pVampire->getName(), STORAGE_GEAR, 0, i, 0);
						// item저장 최적화. by sigi. 2002.5.13
						sprintf(pField, "Durability=%d", pItem->getDurability());
						pItem->tinysave(pField);

					}
				}
			}
		}

		// 돈을 줄이고...
		//pVampire->setGoldEx(pVampire->getGold() - repairPrice);
		// by sigi.2002.9.4
		pVampire->decreaseGoldEx(repairPrice);

		// 로그를 남긴다.
		log(LOG_REPAIR_ITEM, pVampire->getName(), "", "ALL");

		// OK 패킷을 날려준다.
		response.setCode(NPC_RESPONSE_REPAIR_OK);
		response.setParameter(pVampire->getGold());
		pPlayer->sendPacket(&response);
	}
	else if (pPC->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);

		// 모든 아이템을 합한 수리비를 계산한다.
		for (int i=0; i<Ousters::OUSTERS_WEAR_MAX; i++)
		{
			Item* pItem = pOusters->getWearItem((Ousters::WearPart)i);
			if (pItem != NULL) 
			{
				if (i == Ousters::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// 양손무기는 한쪽만 수리한다.
				}
				else
				{
					repairPrice += g_pPriceManager->getRepairPrice(pItem);
				}
			}
		}

		// 돈이 모자라다면 리턴한다.
		if (pOusters->getGold() < repairPrice)
		{
			response.setCode(NPC_RESPONSE_REPAIR_FAIL_MONEY);
			pPlayer->sendPacket(&response);
			return;
		}
 
		// 각각의 아이템을 수리하고, DB에 저장한다.
		char pField[80];

		for (int i=0; i<Ousters::OUSTERS_WEAR_MAX; i++)
		{
			Item* pItem = pOusters->getWearItem((Ousters::WearPart)i);
			if (pItem != NULL)
			{
				if (i == Ousters::WEAR_RIGHTHAND && isTwohandWeapon(pItem))
				{
					// 양손무기는 한쪽만 수리한다.
				}
				else
				{
					Durability_t oldDurability = pItem->getDurability();
					repairItem(pItem);
					if (pItem->getDurability() != oldDurability)
					{
						// DB 쿼리를 줄이기 위해서
						// 내구도의 변화가 생긴 경우에만 세이브한다.
						//pItem->save(pOusters->getName(), STORAGE_GEAR, 0, i, 0);
						// item저장 최적화. by sigi. 2002.5.13
						sprintf(pField, "Durability=%d", pItem->getDurability());
						pItem->tinysave(pField);

					}
				}
			}
		}

		// 돈을 줄이고...
		//pOusters->setGoldEx(pOusters->getGold() - repairPrice);
		// by sigi.2002.9.4
		pOusters->decreaseGoldEx(repairPrice);

		// 로그를 남긴다.
		log(LOG_REPAIR_ITEM, pOusters->getName(), "", "ALL");

		// OK 패킷을 날려준다.
		response.setCode(NPC_RESPONSE_REPAIR_OK);
		response.setParameter(pOusters->getGold());
		pPlayer->sendPacket(&response);
	}

#endif

	__END_DEBUG_EX __END_CATCH
}
