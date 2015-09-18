//////////////////////////////////////////////////////////////////////////////
// Filename    : EventMorph.cpp
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EventMorph.h"
#include "GamePlayer.h"
#include "PCFinder.h"
#include "Vampire.h"
#include "Slayer.h"
#include "ItemUtil.h"
#include "Zone.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupManager.h"
#include "IncomingPlayerManager.h"
#include "ZonePlayerManager.h"
#include "TimeManager.h"
#include <fstream>
//#include "LogClient.h"
#include "PacketUtil.h"
#include "Party.h"
#include "TradeManager.h"
#include "GuildManager.h"
#include "Guild.h"
#include "ZoneUtil.h"
#include "RelicUtil.h"
#include "SharedServerManager.h"
#include "DB.h"
#include "CreatureUtil.h"

#include "GCUpdateInfo.h"
#include "GCMorph1.h"
#include "GCMorphVampire2.h"
#include "GSGuildMemberLogOn.h"

#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
// class EventMorph member methods
//////////////////////////////////////////////////////////////////////////////

EventMorph::EventMorph(GamePlayer* pGamePlayer)
	throw()
	: Event(pGamePlayer)
{
	__BEGIN_TRY
	__END_CATCH
}

EventMorph::~EventMorph()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

void EventMorph::activate () 
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	Assert(m_pGamePlayer != NULL);

	Creature* pFromCreature = m_pGamePlayer->getCreature();
	Assert(pFromCreature->isSlayer());

	if (m_pGamePlayer->getPlayerStatus() != GPS_NORMAL)
	{
		// 플레이어의 상태가 WAITING_FOR_CG_READY인데, morph가 
		// activate되어 밑의 존에서 크리쳐를 지우는 부분에서 에러가 throw되어
		// 서버가 죽는 버그가 있었다. 정확히 어떻게 해서 CG_READY상태에서
		// 이벤트가 activate되는지는 모르겠으나, GamePlayer의 
		// EventManager 자체를 GPS_NORMAL일 때만 돌아가게 하면,
		// Resurrect가 되지 않으니 주의하길 바란다. 결국 GamePlayer 내부에서
		// 체크를 하기가 곤란하기 때문에 이 부분에서, 처리한다.
		StringStream msg;
		msg << "EventMorph::activate() : GamePlayer의 상태가 GPS_NORMAL이 아닙니다."
			<< "PlayerID[" << m_pGamePlayer->getID() << "]"
			<< "CreatureName[" << pFromCreature->getName() << "]";

		filelog("EventMorphError.log", "%s", msg.toString().c_str());
		return;
	}

	pFromCreature->removeFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
	Zone* pZone = pFromCreature->getZone();

	// 만일 Restore 이펙트가 걸려있다면 변신이 되지 않는다.
	if (pFromCreature->isFlag(Effect::EFFECT_CLASS_RESTORE))
	{
		return;
	}

	dropRelicToZone(pFromCreature);
	dropFlagToZone(pFromCreature);
	dropSweeperToZone(pFromCreature);

	//////////////////////////////////////////////////////////////////////
	// 각종 존 레벨 정보를 삭제해야 한다.
	//////////////////////////////////////////////////////////////////////
	
	// 파티 초대 중이라면 정보를 삭제해 준다.
	PartyInviteInfoManager* pPIIM = pZone->getPartyInviteInfoManager();
	Assert(pPIIM != NULL);
	pPIIM->cancelInvite(pFromCreature);

	// 파티 관련 정보를 삭제해 준다.
	uint PartyID = pFromCreature->getPartyID();
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

	Vampire* pVampire = new Vampire();
	
	GCMorph1 gcEventMorph1;	// 변신 당사자에게..
	GCMorphVampire2 gcEventMorphVampire2;	// 변신 구경꾼들에게..
		
	pVampire->setName(pFromCreature->getName());

	ObjectID_t fromObjectID = pFromCreature->getObjectID();
	pVampire->setObjectID(fromObjectID);

	Player* pPlayer = pFromCreature->getPlayer();
	dynamic_cast<GamePlayer*>(pPlayer)->setCreature(pVampire);
	pVampire->setPlayer(pPlayer);
	pVampire->setZone(pZone);
	pVampire->load();

	Coord_t x = pFromCreature->getX(), y = pFromCreature->getY();
	Dir_t dir = pFromCreature->getDir();
	pVampire->setXYDir(x, y, dir);
	pVampire->setMoveMode(pFromCreature->getMoveMode());
	
	// slayer to vampire
	Slayer* pSlayer = dynamic_cast<Slayer*>(pFromCreature);

	// 뱀파이어로 변신할때 Creature Pointer가 달라지므로...
	// 원래 등록 되어있던 포인터는 개가 된다...
	// 따라서 새로운 Creature Pointer를 등록해줘야 한다.
	g_pPCFinder->deleteCreature(pFromCreature->getName());
	g_pPCFinder->addCreature(pVampire);

	// 길드 현재 접속 리스트에서 삭제한다.
	if (pSlayer->getGuildID() != 99 )
	{
		Guild* pGuild = g_pGuildManager->getGuild(pSlayer->getGuildID());
		if (pGuild != NULL )
		{
			pGuild->deleteCurrentMember(pSlayer->getName());

			GSGuildMemberLogOn gsGuildMemberLogOn;
			gsGuildMemberLogOn.setGuildID(pGuild->getID());
			gsGuildMemberLogOn.setName(pSlayer->getName());
			gsGuildMemberLogOn.setLogOn(false);

			g_pSharedServerManager->sendPacket(&gsGuildMemberLogOn);
			
			Statement* pStmt = NULL;
			// 디비에 업데이트 한다.
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery("UPDATE GuildMember SET LogOn = 0 WHERE Name = '%s'", pSlayer->getName().c_str());
			}
			END_DB(pStmt)
		}
		else
			filelog("GuildMissing.log", "[NoSuchGuild] GuildID : %d, Name : %s\n", (int)pSlayer->getGuildID(), pSlayer->getName().c_str());
	}

	// 인벤토리 교체.
	Inventory* pInventory = pSlayer->getInventory();
	pVampire->setInventory(pInventory);
	pSlayer->setInventory(NULL);

	// 보관함 교체
	pVampire->deleteStash();                 // 이전 객체를 지워주고...
	pVampire->setStash(pSlayer->getStash()); // 슬레이어 걸로 바꾼 다음에
	pVampire->setStashNum(pSlayer->getStashNum());
	pVampire->setStashStatus(false);         // OID 할당 상태를 false로...
	pSlayer->setStash(NULL);                 // 포인터 에러를 막기 위해 슬레이어 것은 NULL로...

	/*
	// 가비지 교체
	while (true)
	{
		Item* pGarbage = pSlayer->popItemFromGarbage();

		// 더 이상 없다면 브레이크...
		if (pGarbage == NULL) break;

		pVampire->addItemToGarbage(pGarbage);
	}
	*/


	// 플래그 셋 교체
	pVampire->deleteFlagSet();
	pVampire->setFlagSet(pSlayer->getFlagSet());
	pSlayer->setFlagSet(NULL);

	Item* pItem = NULL;
	_TPOINT point;
	// 기어에서 인벤토리로..
    for(int part = 0; part < (int)Slayer::WEAR_MAX; part++)
   	{
       	pItem = pSlayer->getWearItem((Slayer::WearPart)part);
        if (pItem)
   	    {
			if (isTwohandWeapon(pItem))
            {
				Assert(((Slayer::WearPart)part == Slayer::WEAR_RIGHTHAND) || ((Slayer::WearPart)part == Slayer::WEAR_LEFTHAND));
				Assert(pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND) == pSlayer->getWearItem(Slayer::WEAR_LEFTHAND));
				// 양손 아템.
				pSlayer->deleteWearItem(Slayer::WEAR_RIGHTHAND);
				pSlayer->deleteWearItem(Slayer::WEAR_LEFTHAND);
            }
   	        else
       	    {
				pSlayer->deleteWearItem((Slayer::WearPart)part);
            }
	
			if (pInventory->getEmptySlot(pItem, point))
       	    {
				// 인벤토리에 여유 슬롯이 있으면..
				// 인벤토리에 추가
				pInventory->addItem(point.x, point.y, pItem);
				pItem->save(pVampire->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
   	        }
       	    else if (pItem->isTimeLimitItem() )
			{
				pSlayer->deleteItemByMorph(pItem);

				pItem->destroy();
				SAFE_DELETE(pItem);
			}
			else 
			{
				TPOINT pt;
				ZoneCoord_t ZoneX = pSlayer->getX();
				ZoneCoord_t ZoneY = pSlayer->getY();

				// 존으로 뿌린다.
   	            pt = pZone->addItem(pItem, ZoneX, ZoneY);

				if (pt.x != -1) 
				{
					pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x , pt.y);
					//log(LOG_DROP_ITEM_MORPH, pSlayer->getName(), "", pItem->toString());

					// ItemTraceLog 를 남긴다
					if (pItem != NULL && pItem->isTraceItem() )
					{
						char zoneName[15];
						sprintf(zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
						remainTraceLog(pItem, pFromCreature->getName(), zoneName, ITEM_LOG_MOVE, DETAIL_DROP);
						remainTraceLogNew(pItem, pFromCreature->getName(), ITL_DROP, ITLD_MOVE, pZone->getZoneID(), pt.x, pt.y);
					}
				} 
				else 
				{
					// ItemTraceLog 를 남긴다
					if (pItem != NULL && pItem->isTraceItem() )
					{
						remainTraceLog(pItem, pFromCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_DROP);
						remainTraceLogNew(pItem, pFromCreature->getName(), ITL_ETC, ITLD_DELETE);
					}
					pItem->destroy();
					SAFE_DELETE(pItem);
				}
      	    }
        }
    }
	// ExtraInventorySlot에서 인벤토리로..
    pItem = pSlayer->getExtraInventorySlotItem();
   	if (pItem)
    {
   	    pSlayer->deleteItemFromExtraInventorySlot();

		if (pInventory->getEmptySlot(pItem, point))
        {
   	        pInventory->addItem(point.x, point.y, pItem);
			pItem->save(pVampire->getName(), STORAGE_INVENTORY, 0, point.x, point.y);
        }
		else if (pItem->isTimeLimitItem() )
		{
			pSlayer->deleteItemByMorph(pItem);

			pItem->destroy();
			SAFE_DELETE(pItem);
		}
		else
		{

			TPOINT pt;
			ZoneCoord_t ZoneX = pSlayer->getX();
			ZoneCoord_t ZoneY = pSlayer->getY();

            pt = pZone->addItem(pItem, ZoneX, ZoneY); 

			if (pt.x != -1) 
			{
				pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x , pt.y);
				//log(LOG_DROP_ITEM_MORPH, pSlayer->getName(), "");

				// ItemTraceLog 를 남긴다
				if (pItem != NULL && pItem->isTraceItem() )
				{
					char zoneName[15];
					sprintf(zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
					remainTraceLog(pItem, pFromCreature->getName(), zoneName, ITEM_LOG_MOVE, DETAIL_DROP);
					remainTraceLogNew(pItem, pFromCreature->getName(), ITL_DROP, ITLD_MOVE, pZone->getZoneID(), pt.x, pt.y);
				}
			}
			else 
			{
				// ItemTraceLog 를 남긴다
				if (pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog(pItem, pFromCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_DROP);
					remainTraceLogNew(pItem, pFromCreature->getName(), ITL_DROP, ITLD_DELETE);
				}
				pItem->destroy();
				SAFE_DELETE(pItem);
			}
   	    }
    }

	if (pSlayer->hasRideMotorcycle()) {
		pSlayer->getOffMotorcycle();
	}

	pVampire->loadTimeLimitItem();

	// Vampire로 변했을때는 돈을 초기화한다.
	//pVampire->setGoldEx(pSlayer->getGold());
	pVampire->setGoldEx(0);
	pVampire->setStashGoldEx(0);

	// set packet data
	gcEventMorph1.setPCInfo2(pVampire->getVampireInfo2());
	gcEventMorph1.setInventoryInfo(pVampire->getInventoryInfo());
	gcEventMorph1.setGearInfo(pVampire->getGearInfo());
	gcEventMorph1.setExtraInfo(pVampire->getExtraInfo());

	gcEventMorphVampire2.setVampireInfo(pVampire->getVampireInfo3());

	if (pFromCreature->isPC())
	{
		Player* pPlayer = pFromCreature->getPlayer();
		pPlayer->sendPacket(&gcEventMorph1);
	}

	pZone->broadcastPacket(x, y, &gcEventMorphVampire2, pFromCreature);

	Tile & tile = pZone->getTile(x, y);

	// Delete FromCreature from tile & PCManager
	tile.deleteCreature(fromObjectID);
	pZone->deletePC(pFromCreature);

	// add toCreature
	tile.addCreature(pVampire, false, false);
	pZone->addPC(pVampire);

//	pZone->addPC(pVampire, x, y, pVampire->getDir());
//	pZone->deleteCreature(pFromCreature, x, y);
//	pZone->morphCreature(pFromCreature, pVampire);

	// 시야 update..
	pZone->updateHiddenScan(pVampire);

	// 뱀프 기술
	pVampire->sendVampireSkillInfo();

	m_pTargetCreature = NULL;

	// 뱀프로 변했다는 정보를 Slayer Field에 추가한다.
	pSlayer->tinysave("Race='VAMPIRE'");

	// 뱀파이어 마을로 이동시킨다.
	uint ZoneNum = 1003;

	ZoneCoord_t ZoneX = 62;
	ZoneCoord_t ZoneY = 64;

	Assert((int)ZoneX < 256);
	Assert((int)ZoneY < 256);

	Assert(pVampire->isPC());

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pVampire->getPlayer());
//	Zone* pZone = pVampire->getZone();

	//--------------------------------------------------------------------------------
	// 도착존이 어느 서버, 어느 존그룹에 속하는지 알아본다.
	//--------------------------------------------------------------------------------
	ZoneInfo* pZoneInfo;
	try 
	{
		pZoneInfo = g_pZoneInfoManager->getZoneInfo(ZoneNum);
	} 
	catch (NoSuchElementException&) 
	{
		cerr << "Critical Error : 포탈에 지정된 존 아이디가 틀리거나, ZoneInfoManager에 해당 존이 존재하지 않습니다." << endl;
		throw Error("Critical Error : 포탈에 지정된 존 아이디가 틀리거나, ZoneInfoManager에 해당 존이 존재하지 않습니다.");
	}

	ZoneGroup* pZoneGroup;
	try 
	{
		pZoneGroup = g_pZoneGroupManager->getZoneGroup(pZoneInfo->getZoneGroupID());
	}
	catch (NoSuchElementException&) 
	{
		cerr << "Critical Error : 현재로는 게임 서버는 1대뿐이당.." << endl;

		// 일단은 서버가 1대이므로.. 그대로 나간다...
		throw Error("Critical Error : 현재로는 게임 서버는 1대뿐이당..");
	}

	//--------------------------------------------------------------------------------
	// 우선 이전 존에서 PC 를 삭제하고, 플레이어를 ZPM -> IPM 으로 옮긴다.
	//--------------------------------------------------------------------------------
	try 
	{
		// 이제, 존에서 PC를 삭제한다.
		//
		// *CAUTION*
		//
		// pVampire 좌표가 실제로 pVampire가 존재하는 타일의 좌표와 같아야 한다.
		// 따라서, 이 메쏘드를 호출하기 전에 좌표를 잘 바꿔놔야 한당..
		//
		pZone->deleteCreature(pVampire, pVampire->getX() , pVampire->getY());

		// 존그룹의 ZPM에서 플레이어를 삭제한다.
		//pZone->getZoneGroup()->getZonePlayerManager()->deletePlayer_NOBLOCKED(pGamePlayer);
		//pZone->getZoneGroup()->getZonePlayerManager()->deletePlayer_NOBLOCKED(pGamePlayer->getSocket()->getSOCKET());
		pZone->getZoneGroup()->getZonePlayerManager()->deletePlayer(pGamePlayer->getSocket()->getSOCKET());

		//--------------------------------------------------
		// 크리처의 새로운 좌표는 포탈의 도착 지점이다.
		//--------------------------------------------------
		// 주석처리 by sigi. 2002.5.17
		//pVampire->setXY(ZoneX, ZoneY);
		//pVampire->setZone(NULL);

		// IPM으로 플레이어를 옮긴다.
		//g_pIncomingPlayerManager->addPlayer(pGamePlayer);
		//g_pIncomingPlayerManager->pushPlayer(pGamePlayer);
		pZone->getZoneGroup()->getZonePlayerManager()->pushOutPlayer(pGamePlayer);

	} 
	catch (NoSuchElementException & nsee) 
	{
		cerr << nsee.toString() << endl;
		throw Error(nsee.toString());
	}

	// 크리처에다가 존을 지정해준다. 이는 OID 를 할당받기 위해서이다.
	Zone* pNewZone = pZoneGroup->getZone(ZoneNum);
	Assert(pNewZone != NULL);

	//pVampire->setZone(pZone);
	// 이동할 존을 설정한다. by sigi. 2002.5.11
	pVampire->setNewZone(pNewZone);
	pVampire->setNewXY(ZoneX, ZoneY);


	// 크리처의 정보를 저장한다.
	pVampire->setZone(pNewZone);
	pVampire->setXY(ZoneX, ZoneY);

	pVampire->save();

	pVampire->setZone(pZone);
	pVampire->setXY(x, y);

	// 크리처 자신과 소유 아이템들의 OID를 할당받는다.
	//pVampire->registerObject();

	/*
	//--------------------------------------------------------------------------------
	// GCUpdateInfo 패킷을 만들어둔다.
	//--------------------------------------------------------------------------------
	GCUpdateInfo gcUpdateInfo;

	makeGCUpdateInfo(&gcUpdateInfo, pVampire);

	pGamePlayer->sendPacket(&gcUpdateInfo);
	*/

	//--------------------------------------------------
	// change player status
	//--------------------------------------------------
	pGamePlayer->setPlayerStatus(GPS_WAITING_FOR_CG_READY);


	// 지금 지우면.. 돌고 있는 EffectManager는 어케 되남? -_-;
	//----------------------------------

	/*
	Creature* pEventMorphCreature = m_pGamePlayer->getCreature();
	Assert(pEventMorphCreature != m_pTargetCreature);
	Assert(pEventMorphCreature != NULL);	// by sigi

	Zone* pZone = pEventMorphCreature->getZone();
	Assert(pZone != NULL);
	*/

	/*
	ofstream file("blood.txt", ios::out | ios::app);
	file << "슬레이어 [" << pSlayer->getName() << "] 뱀파로 변하다 >> ";
	file << getCurrentTimeStringEx() << endl;
	file.close();
	*/

	//log(LOG_SLAYER_TO_VAMPIRE, pFromCreature->getName(), "");

	SAFE_DELETE(pFromCreature);

	__END_DEBUG
	__END_CATCH
}
	
string EventMorph::toString () const 
	throw()
{
	StringStream msg;
	msg << "EventMorph("
		<< ")";
	return msg.toString();
}
