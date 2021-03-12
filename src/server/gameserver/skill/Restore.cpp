//////////////////////////////////////////////////////////////////////////////
// Filename    : Restore.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Restore.h"
#include "PCFinder.h"
#include "NPC.h"
#include "DB.h"
#include "Party.h"
#include "TradeManager.h"
#include "GuildManager.h"
#include "Guild.h"

#include "EffectBloodDrain.h"
#include "EffectRestore.h"
#include "ItemUtil.h"
#include "RelicUtil.h"
#include "SharedServerManager.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCMorph1.h"
#include "Gpackets/GCMorphSlayer2.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCDeleteObject.h"
#include "Gpackets/GSGuildMemberLogOn.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Restore::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pFromCreature = pZone->getCreature(TargetObjectID);

		// 뱀파이어만 건드릴 수가 있다.
		// NoSuch제거. by sigi. 2002.5.2
		if (pFromCreature==NULL
			|| !pFromCreature->isVampire())
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1; // 스킬 쓴 넘에게...
		GCMorph1           _GCMorph1;           // 변신 당사자에게..
		GCMorphSlayer2     _GCMorphSlayer2;     // 변신 구경꾼들에게..

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		bool bRangeCheck = verifyDistance(pSlayer, pFromCreature, pSkillInfo->getRange());
		bool bHitRoll    = true;

		if (bRangeCheck && bHitRoll)
		{
			dropRelicToZone(pFromCreature);
			dropFlagToZone(pFromCreature);

			//////////////////////////////////////////////////////////////////////
			// 각종 존 레벨 정보를 삭제해야 한다.
			//////////////////////////////////////////////////////////////////////

			// 파티 초대 중이라면 정보를 삭제해 준다.
			PartyInviteInfoManager* pPIIM = pZone->getPartyInviteInfoManager();
			Assert(pPIIM != NULL);
			pPIIM->cancelInvite(pFromCreature);

			// 파티 관련 정보를 삭제해 준다.
			int PartyID = pFromCreature->getPartyID();
			if (PartyID != 0)
			{
				// 먼저 로컬에서 삭제하고...
				LocalPartyManager* pLPM = pZone->getLocalPartyManager();
				Assert(pLPM != NULL);
				pLPM->deletePartyMember(PartyID, pFromCreature);

				// 글로벌에서도 삭제해 준다.
				deleteAllPartyInfo(pFromCreature);
			}

			// 트레이드 중이었다면 트레이드 관련 정보를 삭제해준다.
			TradeManager* pTM = pZone->getTradeManager();
			Assert(pTM != NULL);
			pTM->cancelTrade(pFromCreature);

			//////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////

			Slayer*  pNewSlayer = new Slayer;
			Vampire* pVampire   = dynamic_cast<Vampire*>(pFromCreature);

			// DB에서 혹시 남아있을 지 모르는 흡혈 정보를 삭제해준다.
			Statement* pStmt = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				StringStream sql;
				sql << "DELETE FROM EffectBloodDrain WHERE OwnerID = '" + pFromCreature->getName() + "'";
				pStmt->executeQuery(sql.toString());
				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			pNewSlayer->setName(pFromCreature->getName());

			// 크리쳐 안의 플레이어 포인터와 플레이어 안의 크리쳐 포인터를 갱신한다.
			Player* pFromPlayer = pFromCreature->getPlayer();
			pNewSlayer->setPlayer(pFromPlayer);
			GamePlayer* pFromGamePlayer = dynamic_cast<GamePlayer*>(pFromPlayer);
			pFromGamePlayer->setCreature(pNewSlayer);

			// load하면 load한 zone에서 objectID를 받으므로 다시 설정한다. by sigi. 2002.6.4
			pNewSlayer->load();
			pNewSlayer->setZone(pZone);
			pNewSlayer->setObjectID(pFromCreature->getObjectID());
			//pZone->getObjectRegistry().registerObject(pNewSlayer);
			pNewSlayer->setMoveMode(Creature::MOVE_MODE_WALKING);
			
			ZoneCoord_t x    = pFromCreature->getX();
			ZoneCoord_t y    = pFromCreature->getY();
			Dir_t       dir  = pFromCreature->getDir();
			Tile&       tile = pZone->getTile(x, y);

			// 곧 pFromCreature 즉, 원래의 뱀파이어 객체는 지워질 것이므로,
			// PCFinder에 들어가 있는 값은 쓰레기 값이 될 것이다. 
			// 그러므로 뱀파이어 포인터를 지워주고, 새로운 슬레이어 포인터를 더한다.
			g_pPCFinder->deleteCreature(pFromCreature->getName());
			g_pPCFinder->addCreature(pNewSlayer);

			// 길드 현재 접속 멤버 리스트에서 삭제한다.
			if ( pVampire->getGuildID() != 0 )
			{
				Guild* pGuild = g_pGuildManager->getGuild( pVampire->getGuildID() );
				if ( pGuild != NULL )
				{
					pGuild->deleteCurrentMember( pVampire->getName() );

					GSGuildMemberLogOn gsGuildMemberLogOn;
					gsGuildMemberLogOn.setGuildID( pGuild->getID() );
					gsGuildMemberLogOn.setName( pVampire->getName() );
					gsGuildMemberLogOn.setLogOn( false );

					g_pSharedServerManager->sendPacket( &gsGuildMemberLogOn );

					Statement* pStmt = NULL;
					// 디비에 업데이트 한다.
					BEGIN_DB
					{
						pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
						pStmt->executeQuery( "UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pVampire->getName().c_str() );
					}
					END_DB(pStmt)
				}
				else
					filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pVampire->getGuildID(), pVampire->getName().c_str() );
			}

			// 인벤토리 교체.
			Inventory* pInventory = pVampire->getInventory();
			pNewSlayer->setInventory(pInventory);
			pVampire->setInventory(NULL);

			// 보관함 교체
			pNewSlayer->deleteStash();
			pNewSlayer->setStash(pVampire->getStash());
			pNewSlayer->setStashNum(pVampire->getStashNum());
			pNewSlayer->setStashStatus(false);
			pVampire->setStash(NULL);

			/*
			// 가비지 교체
			while (true)
			{
				Item* pGarbage = pVampire->popItemFromGarbage();

				// 더 이상 없다면 브레이크...
				if (pGarbage == NULL) break;

				pNewSlayer->addItemToGarbage(pGarbage);
			}
			*/

			// 플래그 셋 교체
			pNewSlayer->deleteFlagSet();
			pNewSlayer->setFlagSet(pVampire->getFlagSet());
			pVampire->setFlagSet(NULL);

			Item* pItem = NULL;
			_TPOINT point;

			// 입고 있는 아이템들을 인벤토리 또는 바닥으로 옮긴다.
			for(int part = 0; part < (int)Vampire::VAMPIRE_WEAR_MAX; part++)
			{
				pItem = pVampire->getWearItem((Vampire::WearPart)part);
				if (pItem != NULL)
				{
					// 먼저 기어에서 삭제하고...
					if (isTwohandWeapon(pItem))
					{
						Assert(((Vampire::WearPart)part == Vampire::WEAR_RIGHTHAND) || ((Vampire::WearPart)part==Vampire::WEAR_LEFTHAND));
						Assert(pVampire->getWearItem(Vampire::WEAR_RIGHTHAND) == pVampire->getWearItem(Vampire::WEAR_LEFTHAND));
						// 양손 아템.
						pVampire->deleteWearItem(Vampire::WEAR_RIGHTHAND);
						pVampire->deleteWearItem(Vampire::WEAR_LEFTHAND);
					}
					else
					{
						pVampire->deleteWearItem((Vampire::WearPart)part);
					}

					// 인벤토리에 자리가 있으면 인벤토리에 더하고...
					if (pInventory->getEmptySlot(pItem, point))
					{
						pInventory->addItem(point.x, point.y, pItem);
						pItem->save(pNewSlayer->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
					}
					else if ( pItem->isTimeLimitItem() )
					{
						pVampire->deleteItemByMorph( pItem );

						pItem->destroy();
						SAFE_DELETE( pItem );
					}
					// 자리가 없으면 바닥에 떨어뜨린다.
					else
					{
						ZoneCoord_t ZoneX = pVampire->getX();
						ZoneCoord_t ZoneY = pVampire->getY();

						TPOINT pt;

						pt = pZone->addItem(pItem, ZoneX , ZoneY);

						if (pt.x != -1) 
						{
							pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);

							// ItemTraceLog 를 남긴다
							if ( pItem != NULL && pItem->isTraceItem() )
							{
								char zoneName[15];
								sprintf( zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
								remainTraceLog( pItem, pFromCreature->getName(), zoneName, ITEM_LOG_MOVE, DETAIL_DROP);
							}
						} 
						else 
						{
							// ItemTraceLog 를 남긴다
							if ( pItem != NULL && pItem->isTraceItem() )
							{
								remainTraceLog( pItem, pFromCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_DROP);
							}

							pItem->destroy();
							SAFE_DELETE(pItem);
						}
					}
				}
			}

			pItem = pVampire->getExtraInventorySlotItem();
			if (pItem != NULL)
			{
				pVampire->deleteItemFromExtraInventorySlot();

				// 인벤토리에 자리가 있으면 인벤토리에 더하고...
				if (pInventory->getEmptySlot(pItem, point))
				{
					pInventory->addItem(point.x, point.y, pItem);
					pItem->save(pNewSlayer->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
				}
				else if ( pItem->isTimeLimitItem() )
				{
					pVampire->deleteItemByMorph( pItem );

					pItem->destroy();
					SAFE_DELETE( pItem );
				}
				// 자리가 없으면 바닥에 떨어뜨린다.
				else
				{
					TPOINT pt;
					ZoneCoord_t ZoneX = pVampire->getX();
					ZoneCoord_t ZoneY = pVampire->getY();

					pt = pZone->addItem(pItem, ZoneX , ZoneY);

					if (pt.x != -1) 
					{
						pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);

						// ItemTraceLog 를 남긴다
						if ( pItem != NULL && pItem->isTraceItem() )
						{
							char zoneName[15];
							sprintf( zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
							remainTraceLog( pItem, pFromCreature->getName(), zoneName, ITEM_LOG_MOVE, DETAIL_DROP);
						}
					} 
					else 
					{
						// ItemTraceLog 를 남긴다
						if ( pItem != NULL && pItem->isTraceItem() )
						{
							remainTraceLog( pItem, pFromCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_DROP);
						}

						pItem->destroy();
						SAFE_DELETE(pItem);
					}
				}
			}

			// 퀘스트 아이템 정보를 다시 로드한다.
			pNewSlayer->loadTimeLimitItem();

			// 뱀파이어 가지고 있던 돈을 슬레이어로 옮겨준다.
			// 뱀파이어가 가지고 있던 돈은 슬레이어로 옮겨가지 않는다.
			// 새로운 슬레이어의 돈을 0으로 세팅한다.
			pNewSlayer->setGoldEx(0);
			pNewSlayer->setStashGoldEx(0);

			// 스킬 정보를 전송한다.
			pNewSlayer->sendSlayerSkillInfo();

			
			// 타일 및 존에서 기존 뱀파이어를 삭제하고, 새로운 슬레이어를 더한다.
			tile.deleteCreature(pFromCreature->getObjectID());
			pZone->deletePC(pFromCreature);

			TPOINT pt = findSuitablePosition(pZone, x, y, Creature::MOVE_MODE_WALKING);
			Tile& newtile = pZone->getTile(pt.x, pt.y);

			newtile.addCreature(pNewSlayer);
			pNewSlayer->setXYDir(pt.x, pt.y, dir);

			pZone->addPC(pNewSlayer);

			// 시야 update..
			pZone->updateHiddenScan(pNewSlayer);
		
			_GCMorph1.setPCInfo2(pNewSlayer->getSlayerInfo2());
			_GCMorph1.setInventoryInfo(pNewSlayer->getInventoryInfo());
			_GCMorph1.setGearInfo(pNewSlayer->getGearInfo());
			_GCMorph1.setExtraInfo(pNewSlayer->getExtraInfo());

			_GCMorphSlayer2.setSlayerInfo(pNewSlayer->getSlayerInfo3());

			pFromPlayer->sendPacket(&_GCMorph1);
			//pFromGamePlayer->deleteEvent(Event::EVENT_CLASS_REGENERATION);


			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

	
			GCDeleteObject _GCDeleteObject;
			_GCDeleteObject.setObjectID( TargetObjectID );
			pZone->broadcastPacket(x, y, &_GCDeleteObject, pNewSlayer);
			pZone->broadcastPacket(x, y, &_GCMorphSlayer2, pNewSlayer);


			pNewSlayer->tinysave("Race='SLAYER'");
			SAFE_DELETE(pFromCreature);


			pSkillSlot->setRunTime(0);

			EffectRestore* pEffectRestore = new EffectRestore(pNewSlayer);
			pEffectRestore->setDeadline(60*60*24*7*10); // 7일 
			pNewSlayer->addEffect(pEffectRestore);
			pNewSlayer->setFlag(Effect::EFFECT_CLASS_RESTORE);
			pEffectRestore->create(pNewSlayer->getName());
		}
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), pFromCreature);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// NPC 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Restore::execute(NPC* pNPC, Creature* pFromCreature)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pNPC != NULL);
	Assert(pFromCreature != NULL);

	try 
	{
		Zone* pZone = pNPC->getZone();
		Assert(pZone != NULL);

		// 뱀파이어만 건드릴 수가 있다.
		if (!pFromCreature->isVampire())
		{
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCMorph1           _GCMorph1;           // 변신 당사자에게..
		GCMorphSlayer2     _GCMorphSlayer2;     // 변신 구경꾼들에게..

		//SkillType_t SkillType = SKILL_RESTORE;

		//bool bRangeCheck = verifyDistance(pNPC, pFromCreature, pSkillInfo->getRange());
		bool bHitRoll    = true;

		//if (bRangeCheck && bHitRoll)
		if (bHitRoll)
		{
			//////////////////////////////////////////////////////////////////////
			// 각종 존 레벨 정보를 삭제해야 한다.
			//////////////////////////////////////////////////////////////////////

			// 파티 초대 중이라면 정보를 삭제해 준다.
			PartyInviteInfoManager* pPIIM = pZone->getPartyInviteInfoManager();
			Assert(pPIIM != NULL);
			pPIIM->cancelInvite(pFromCreature);

			// 파티 관련 정보를 삭제해 준다.
			int PartyID = pFromCreature->getPartyID();
			if (PartyID != 0)
			{
				// 먼저 로컬에서 삭제하고...
				LocalPartyManager* pLPM = pZone->getLocalPartyManager();
				Assert(pLPM != NULL);
				pLPM->deletePartyMember(PartyID, pFromCreature);

				// 글로벌에서도 삭제해 준다.
				deleteAllPartyInfo(pFromCreature);
			}

			// 트레이드 중이었다면 트레이드 관련 정보를 삭제해준다.
			TradeManager* pTM = pZone->getTradeManager();
			Assert(pTM != NULL);
			pTM->cancelTrade(pFromCreature);

			//////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////

			Slayer*  pNewSlayer = new Slayer;
			Vampire* pVampire   = dynamic_cast<Vampire*>(pFromCreature);

			// DB에서 혹시 남아있을 지 모르는 흡혈 정보를 삭제해준다.
			Statement* pStmt = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				StringStream sql;
				sql << "DELETE FROM EffectBloodDrain WHERE OwnerID = '" + pFromCreature->getName() + "'";
				pStmt->executeQuery(sql.toString());
				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			pNewSlayer->setName(pFromCreature->getName());
			pNewSlayer->setPlayer(pFromCreature->getPlayer());
			pNewSlayer->load();
			// load하면 load한 zone에서 objectID를 받으므로 다시 설정한다. by sigi. 2002.6.4
			pNewSlayer->setZone(pZone);
			pNewSlayer->setObjectID(pFromCreature->getObjectID());
			//pZone->getObjectRegistry().registerObject(pNewSlayer);
			pNewSlayer->setMoveMode(Creature::MOVE_MODE_WALKING);
			
			ZoneCoord_t x    = pFromCreature->getX();
			ZoneCoord_t y    = pFromCreature->getY();
			Dir_t       dir  = pFromCreature->getDir();
			Tile&       tile = pZone->getTile(x, y);

			pNewSlayer->setXYDir(x, y, dir);

			// 크리쳐 안의 플레이어 포인터와 플레이어 안의 크리쳐 포인터를 갱신한다.
			Player* pFromPlayer = pFromCreature->getPlayer();
			//pNewSlayer->setPlayer(pFromPlayer);
			GamePlayer* pFromGamePlayer = dynamic_cast<GamePlayer*>(pFromPlayer);
			pFromGamePlayer->setCreature(pNewSlayer);

			// 곧 pFromCreature 즉, 원래의 뱀파이어 객체는 지워질 것이므로,
			// PCFinder에 들어가 있는 값은 쓰레기 값이 될 것이다. 
			// 그러므로 뱀파이어 포인터를 지워주고, 새로운 슬레이어 포인터를 더한다.
			g_pPCFinder->deleteCreature(pFromCreature->getName());
			g_pPCFinder->addCreature(pNewSlayer);

			// 길드 현재 접속 멤버 리스트에서 삭제한다.
			if ( pVampire->getGuildID() != 0 )
			{
				Guild* pGuild = g_pGuildManager->getGuild( pVampire->getGuildID() );
				if ( pGuild != NULL )
					pGuild->deleteCurrentMember( pVampire->getName() );
				else
					filelog( "GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pVampire->getGuildID(), pVampire->getName().c_str() );
			}

			// 인벤토리 교체.
			Inventory* pInventory = pVampire->getInventory();
			pNewSlayer->setInventory(pInventory);
			pVampire->setInventory(NULL);

			// 보관함 교체
			pNewSlayer->deleteStash();
			pNewSlayer->setStash(pVampire->getStash());
			pNewSlayer->setStashNum(pVampire->getStashNum());
			pNewSlayer->setStashStatus(false);
			pVampire->setStash(NULL);

			// 플래그 셋 교체
			pNewSlayer->deleteFlagSet();
			pNewSlayer->setFlagSet(pVampire->getFlagSet());
			pVampire->setFlagSet(NULL);

			Item* pItem = NULL;
			_TPOINT point;

			// 입고 있는 아이템들을 인벤토리 또는 바닥으로 옮긴다.
			for(int part = 0; part < (int)Vampire::VAMPIRE_WEAR_MAX; part++)
			{
				pItem = pVampire->getWearItem((Vampire::WearPart)part);
				if (pItem != NULL)
				{
					// 먼저 기어에서 삭제하고...
					if (isTwohandWeapon(pItem))
					{
						Assert(((Vampire::WearPart)part == Vampire::WEAR_RIGHTHAND) || ((Vampire::WearPart)part==Vampire::WEAR_LEFTHAND));
						Assert(pVampire->getWearItem(Vampire::WEAR_RIGHTHAND) == pVampire->getWearItem(Vampire::WEAR_LEFTHAND));
						// 양손 아템.
						pVampire->deleteWearItem(Vampire::WEAR_RIGHTHAND);
						pVampire->deleteWearItem(Vampire::WEAR_LEFTHAND);
					}
					else
					{
						pVampire->deleteWearItem((Vampire::WearPart)part);
					}
			
					// 인벤토리에 자리가 있으면 인벤토리에 더하고...
					if (pInventory->getEmptySlot(pItem, point))
					{
						pInventory->addItem(point.x, point.y, pItem);
						pItem->save(pNewSlayer->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
					}
					else if ( pItem->isTimeLimitItem() )
					{
						pVampire->deleteItemByMorph( pItem );

						pItem->destroy();
						SAFE_DELETE( pItem );
					}
					// 자리가 없으면 바닥에 떨어뜨린다.
					else
					{
						ZoneCoord_t ZoneX = pVampire->getX();
						ZoneCoord_t ZoneY = pVampire->getY();

						TPOINT pt;

						pt = pZone->addItem(pItem, ZoneX , ZoneY);

						if (pt.x != -1) 
						{
							pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);

							// ItemTraceLog 를 남긴다
							if ( pItem != NULL && pItem->isTraceItem() )
							{
								char zoneName[15];
								sprintf( zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
								remainTraceLog( pItem, pFromCreature->getName(), zoneName, ITEM_LOG_MOVE, DETAIL_DROP);
							}
						} 
						else 
						{
							// ItemTraceLog 를 남긴다
							if ( pItem != NULL && pItem->isTraceItem() )
							{
								remainTraceLog( pItem, pFromCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_DROP);
							}

							pItem->destroy();
							SAFE_DELETE(pItem);
						}
					}
				}
			}

			pItem = pVampire->getExtraInventorySlotItem();
			if (pItem != NULL)
			{
				pVampire->deleteItemFromExtraInventorySlot();

				// 인벤토리에 자리가 있으면 인벤토리에 더하고...
				if (pInventory->getEmptySlot(pItem, point))
				{
					pInventory->addItem(point.x, point.y, pItem);
					pItem->save(pNewSlayer->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
				}
				else if ( pItem->isTimeLimitItem() )
				{
					pVampire->deleteItemByMorph( pItem );

					pItem->destroy();
					SAFE_DELETE( pItem );
				}
				// 자리가 없으면 바닥에 떨어뜨린다.
				else
				{
					TPOINT pt;
					ZoneCoord_t ZoneX = pVampire->getX();
					ZoneCoord_t ZoneY = pVampire->getY();

					pt = pZone->addItem(pItem, ZoneX , ZoneY);

					if (pt.x != -1) 
					{
						pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);

						// ItemTraceLog 를 남긴다
						if ( pItem != NULL && pItem->isTraceItem() )
						{
							char zoneName[15];
							sprintf( zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
							remainTraceLog( pItem, pFromCreature->getName(), zoneName, ITEM_LOG_MOVE, DETAIL_DROP);
						}
					} 
					else 
					{
						// ItemTraceLog 를 남긴다
						if ( pItem != NULL && pItem->isTraceItem() )
						{
							remainTraceLog( pItem, pFromCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_DROP);
						}

						pItem->destroy();
						SAFE_DELETE(pItem);
					}
				}
			}

			pNewSlayer->loadTimeLimitItem();

			// 뱀파이어 가지고 있던 돈을 슬레이어로 옮겨준다.
			// 슬레이어돈을 초기화한다.
			//pNewSlayer->setGoldEx(pVampire->getGold());
			pNewSlayer->setGoldEx(0);
			pNewSlayer->setStashGoldEx(0);


			// 스킬 정보를 전송한다.
			pNewSlayer->sendSlayerSkillInfo();

			_GCMorph1.setPCInfo2(pNewSlayer->getSlayerInfo2());
			_GCMorph1.setInventoryInfo(pNewSlayer->getInventoryInfo());
			_GCMorph1.setGearInfo(pNewSlayer->getGearInfo());
			_GCMorph1.setExtraInfo(pNewSlayer->getExtraInfo());

			_GCMorphSlayer2.setSlayerInfo(pNewSlayer->getSlayerInfo3());

			pFromPlayer->sendPacket(&_GCMorph1);
			//pFromGamePlayer->deleteEvent(Event::EVENT_CLASS_REGENERATION);


			// 타일 및 존에서 기존 뱀파이어를 삭제하고, 새로운 슬레이어를 더한다.
			tile.deleteCreature(pFromCreature->getObjectID());
			pZone->deletePC(pFromCreature);

			TPOINT pt = findSuitablePosition(pZone, x, y, Creature::MOVE_MODE_WALKING);
			Tile& newtile = pZone->getTile(pt.x, pt.y);

			newtile.addCreature(pNewSlayer);
			pNewSlayer->setXYDir(pt.x, pt.y, dir);

			pZone->addPC(pNewSlayer);


			GCDeleteObject _GCDeleteObject;
			_GCDeleteObject.setObjectID( pFromCreature->getObjectID() );
			pZone->broadcastPacket(x, y, &_GCDeleteObject, pNewSlayer);
			pZone->broadcastPacket(x, y, &_GCMorphSlayer2, pNewSlayer);

			pNewSlayer->tinysave("Race='SLAYER'");
			SAFE_DELETE(pFromCreature);


			// 시야 update..
			pZone->updateHiddenScan(pNewSlayer);

			EffectRestore* pEffectRestore = new EffectRestore(pNewSlayer);
			pEffectRestore->setDeadline(60*60*24*7*10); // 7일 
			pNewSlayer->addEffect(pEffectRestore);
			pNewSlayer->setFlag(Effect::EFFECT_CLASS_RESTORE);
			pEffectRestore->create(pNewSlayer->getName());
		}
		else 
		{
			executeSkillFailNormal(pNPC, getSkillType(), pFromCreature);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pNPC, getSkillType());

	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

Restore g_Restore;
