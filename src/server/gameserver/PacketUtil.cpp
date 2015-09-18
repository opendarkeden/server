//////////////////////////////////////////////////////////////////////////////
// Filename    : PacketUtil.cpp
// Written by  : excel96
// Description : 
// 자주 보내고, 만들기가 복잡한 패킷은 만드는 곳을 여기 하나로 통일함으로써
// 유지보수가 쉬워진다.
//////////////////////////////////////////////////////////////////////////////

#include "PacketUtil.h"
#include "Properties.h"
#include "GamePlayer.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "NPC.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneGroupManager.h"
#include "ZonePlayerManager.h"
#include "TimeManager.h"
#include "WeatherManager.h"
#include "ItemInfo.h"
#include "Inventory.h"
#include "ItemInfoManager.h"
#include "Effect.h"
#include "EventSystemMessage.h"
#include "ZoneUtil.h"
#include "WarScheduler.h"
#include "PlayerCreature.h"
#include "ItemNameInfo.h"
#include "GameServerInfo.h"
#include "GameServerInfoManager.h"

#include "Item.h"
#include "AR.h"
#include "SR.h"
#include "SG.h"
#include "SMG.h"
#include "Belt.h"
#include "OustersArmsband.h"
#include "Mine.h"
#include "PetItem.h"

#include "Corpse.h"
#include "SlayerCorpse.h"
#include "VampireCorpse.h"
#include "OustersCorpse.h"
#include "MonsterCorpse.h"

#include "PCSlayerInfo2.h"
#include "PCVampireInfo2.h"
#include "RideMotorcycleInfo.h"
#include "NPCInfo.h"
#include "SubItemInfo.h"
#include "CastleInfoManager.h"
#include "PKZoneInfoManager.h"

#include "GCUpdateInfo.h"
#include "GCAddSlayer.h"
#include "GCAddVampire.h"
#include "GCAddOusters.h"
#include "GCAddMonster.h"
#include "GCAddNPC.h"
#include "GCAddNewItemToZone.h"
#include "GCDropItemToZone.h"
#include "GCAddSlayerCorpse.h"
#include "GCAddVampireCorpse.h"
#include "GCAddMonsterCorpse.h"
#include "GCAddOustersCorpse.h"
#include "GCOtherModifyInfo.h"
#include "GCSystemMessage.h"
#include "GCCreateItem.h"
#include "GCAddEffect.h"
#include "GCWarScheduleList.h"
#include "GCMiniGameScores.h"
#include "GCPetStashList.h"

#include "GCUpdateInfo.h"
#include "GCModifyInformation.h"
#include "ModifyInfo.h"
//#include "GCItemNameInfoList.h"

#include "GuildManager.h"

#include "Assert1.h"
//#include "LogClient.h"
#include "DB.h"
#include <list>
#include <stdio.h>

#include "PCFinder.h"
#include "GuildUnion.h"
#include "GuildManager.h"
#include "Store.h"
#include "DynamicZone.h"

void sendGCOtherModifyInfoGuildUnionByGuildID(uint gID)
	throw()
{

	__BEGIN_TRY

 	// 가입한놈에게에 보낸다.
	list<Creature*> cList = g_pPCFinder->getGuildCreatures(gID , 300);
	for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
	{

		Creature* pOtherCreature = *itr;
		Zone *pZone = pOtherCreature->getZone();

		if(pZone != NULL)
		{
			GCOtherModifyInfo   gcOtherModifyInfo;

			ZoneCoord_t X = pOtherCreature->getX();
			ZoneCoord_t Y = pOtherCreature->getY();

			makeGCOtherModifyInfoGuildUnion(&gcOtherModifyInfo, pOtherCreature);

			__ENTER_CRITICAL_SECTION((*(pZone->getZoneGroup())) )

			pZone->broadcastPacket(X, Y, &gcOtherModifyInfo , pOtherCreature);

			__LEAVE_CRITICAL_SECTION((*(pZone->getZoneGroup())) )

		}
	}
	


	__END_CATCH
	

}
// 해당크리쳐가 소속된 길드의 모든 놈에게 GCOtherModifyInfo 를 날린다.
void sendGCOtherModifyInfoGuildUnion(Creature* pTargetCreature)
	throw()
{

	__BEGIN_TRY

	GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetCreature->getPlayer());
	Assert(pTargetGamePlayer!=NULL);

	PlayerCreature* pTargetPlayerCreature = dynamic_cast<PlayerCreature*>(pTargetGamePlayer->getCreature());
	Assert(pTargetPlayerCreature != NULL);

 	// 가입한놈에게에 보낸다.
	list<Creature*> cList = g_pPCFinder->getGuildCreatures(pTargetPlayerCreature->getGuildID() , 300);
	for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
	{

		Creature* pOtherCreature = *itr;
		if(pOtherCreature != NULL)
		{
			Zone *pZone = pOtherCreature->getZone();

			if(pZone != NULL)
			{
				GCOtherModifyInfo   gcOtherModifyInfo;

				ZoneCoord_t X = pOtherCreature->getX();
				ZoneCoord_t Y = pOtherCreature->getY();

				makeGCOtherModifyInfoGuildUnion(&gcOtherModifyInfo, pOtherCreature);

				if(pTargetCreature->getZone()->getZoneGroup()->getZoneGroupID()== pOtherCreature->getZone()->getZoneGroup()->getZoneGroupID() )
				{
					pZone->broadcastPacket(X, Y, &gcOtherModifyInfo , pOtherCreature);
				}
				else
				{
					__ENTER_CRITICAL_SECTION((*(pZone->getZoneGroup())) )

					pZone->broadcastPacket(X, Y, &gcOtherModifyInfo , pOtherCreature);

					__LEAVE_CRITICAL_SECTION((*(pZone->getZoneGroup())) )

				}
			}
		}
	}
	


	__END_CATCH
	

}


void makeGCOtherModifyInfoGuildUnion(GCOtherModifyInfo* pModifyInformation, Creature* pCreature)
	throw()
{
	__BEGIN_TRY
	
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	Assert(pGamePlayer!=NULL);

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert(pPlayerCreature != NULL);
	
	GuildUnion *pUnion = NULL;
	pUnion = GuildUnionManager::Instance().getGuildUnion(pPlayerCreature->getGuildID());

	// 소속된 연합이 없으면
	if(pUnion == NULL)
	{

		pModifyInformation->addShortData(MODIFY_UNIONID,  	  0);	
		pModifyInformation->addShortData(MODIFY_UNIONGRADE,   GCUpdateInfo::UNION_NOTHING);	
	
		//cout << "GCModifyInfo->GuildInformation - NOT FOUND UNION / UNION_NOTHING" << endl;
	}
	else
	{
		// 소속된 연합이 있다.
		bool	isGuildMaster = false;
		bool	isGuildUnionMaster = false;

		pModifyInformation->addShortData(MODIFY_UNIONID, pUnion->getUnionID());
		
		if(g_pGuildManager->isGuildMaster (pPlayerCreature->getGuildID(), pPlayerCreature))
		{
			isGuildMaster = true;
		}

		if(pUnion->getMasterGuildID() == pPlayerCreature->getGuildID() )
		{
			isGuildUnionMaster = true;
		}

		if(isGuildMaster && isGuildUnionMaster )
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_MASTER);
			//cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_MASTER" << endl;
		}
		else if(isGuildMaster && !isGuildUnionMaster )
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_GUILD_MASTER);
			//cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_GUILD_MASTER" << endl;
		}
		else
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_NOTHING);
//			cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_NOTHING" << endl;
		}
	}


	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// void makeGCModifyInformation for GuildUnion Info()
//
// 길드 Union 정보를 GCModifyInformation 에 심는다.
//////////////////////////////////////////////////////////////////////////////

	
void makeGCModifyInfoGuildUnion(GCModifyInformation* pModifyInformation, Creature* pCreature)
	throw()
{
	__BEGIN_TRY
	
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	Assert(pGamePlayer!=NULL);

	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert(pPlayerCreature != NULL);
	
	GuildUnion *pUnion = NULL;
	pUnion = GuildUnionManager::Instance().getGuildUnion(pPlayerCreature->getGuildID());

	// 소속된 연합이 없으면
	if(pUnion == NULL)
	{

		pModifyInformation->addShortData(MODIFY_UNIONID,  	  0);	
		pModifyInformation->addShortData(MODIFY_UNIONGRADE,   GCUpdateInfo::UNION_NOTHING);	
	
//		cout << "GCModifyInfo->GuildInformation - NOT FOUND UNION / UNION_NOTHING" << endl;
	}
	else
	{
		// 소속된 연합이 있다.
		bool	isGuildMaster = false;
		bool	isGuildUnionMaster = false;

		pModifyInformation->addShortData(MODIFY_UNIONID, pUnion->getUnionID());
		
		if(g_pGuildManager->isGuildMaster (pPlayerCreature->getGuildID(), pPlayerCreature))
		{
			isGuildMaster = true;
		}

		if(pUnion->getMasterGuildID() == pPlayerCreature->getGuildID() )
		{
			isGuildUnionMaster = true;
		}

		if(isGuildMaster && isGuildUnionMaster )
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_MASTER);
//			cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_MASTER" << endl;
		}
		else if(isGuildMaster && !isGuildUnionMaster )
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_GUILD_MASTER);
//			cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_GUILD_MASTER" << endl;
		}
		else
		{
			pModifyInformation->addShortData(MODIFY_UNIONGRADE, GCUpdateInfo::UNION_NOTHING);
//			cout << "GCModifyInfo->GuildInformation - " << (int)pUnion->getUnionID() << " / UNION_NOTHING" << endl;
		}
	}


	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// void makeGCUpdateInfo()
//
// 포탈이나, 죽어서 맵 사이를 이동할 때 쓰는, GCUpdateInfo 정보를 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCUpdateInfo(GCUpdateInfo* pUpdateInfo, Creature* pCreature) throw() {
	__BEGIN_TRY

	////////////////////////////////////////////////////////////
	// 존 위치 정보 구성
	////////////////////////////////////////////////////////////
	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	ZoneCoord_t x = pCreature->getX();
	ZoneCoord_t y = pCreature->getY();

	ZoneGroup* pZoneGroup = pZone->getZoneGroup();
	Assert(pZoneGroup != NULL);

	pUpdateInfo->setZoneID(pZone->getZoneID());
	pUpdateInfo->setGameTime(g_pTimeManager->getGameTime());

	pUpdateInfo->setZoneX(x);
	pUpdateInfo->setZoneY(y);

	// DynamicZone 처리
	if (pZone->isDynamicZone()) {
		DynamicZone* pDynamicZone = pZone->getDynamicZone();
		Assert(pDynamicZone != NULL);

		pUpdateInfo->setZoneID(pDynamicZone->getTemplateZoneID());
	}

	////////////////////////////////////////////////////////////
	// 인벤토리 및 기어 정보 구성
	////////////////////////////////////////////////////////////
	if (pCreature->isSlayer()) {
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		Assert(pSlayer != NULL);

		pUpdateInfo->setPCInfo(pSlayer->getSlayerInfo2());

		// Inventory, Gear 정보 구성
		pUpdateInfo->setInventoryInfo(pSlayer->getInventoryInfo());
		pUpdateInfo->setGearInfo(pSlayer->getGearInfo());
		pUpdateInfo->setExtraInfo(pSlayer->getExtraInfo());

		if (pSlayer->hasRideMotorcycle())
			pUpdateInfo->setRideMotorcycleInfo(pSlayer->getRideMotorcycleInfo());

		pUpdateInfo->setSMSCharge(pSlayer->getSMSCharge());
		pUpdateInfo->setNicknameInfo(pSlayer->getNickname());
	} else if (pCreature->isVampire()) {
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		Assert(pVampire != NULL);

		pUpdateInfo->setPCInfo(pVampire->getVampireInfo2());

		// Inventory, Gear 정보 구성
		pUpdateInfo->setInventoryInfo(pVampire->getInventoryInfo());
		pUpdateInfo->setGearInfo(pVampire->getGearInfo());
		pUpdateInfo->setExtraInfo(pVampire->getExtraInfo());

		pUpdateInfo->setSMSCharge(pVampire->getSMSCharge());
		pUpdateInfo->setNicknameInfo(pVampire->getNickname());
	} else if (pCreature->isOusters()) {
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
		Assert(pOusters != NULL);

		pUpdateInfo->setPCInfo(pOusters->getOustersInfo2());

		// Inventory, Gear 정보 구성
		pUpdateInfo->setInventoryInfo(pOusters->getInventoryInfo());
		pUpdateInfo->setGearInfo(pOusters->getGearInfo());
		pUpdateInfo->setExtraInfo(pOusters->getExtraInfo());

		pUpdateInfo->setSMSCharge(pOusters->getSMSCharge());
		pUpdateInfo->setNicknameInfo(pOusters->getNickname());
	}

	////////////////////////////////////////////////////////////
	// 이펙트 인포 구성
	////////////////////////////////////////////////////////////
	pUpdateInfo->setEffectInfo(pCreature->getEffectInfo());

	////////////////////////////////////////////////////////////
	// 시야 정보 구성
	////////////////////////////////////////////////////////////
	if (pZone->getZoneType() == ZONE_CASTLE) {
		pUpdateInfo->setDarkLevel(pZone->getDarkLevel());
		pUpdateInfo->setLightLevel(pZone->getLightLevel());
	} else if (g_pPKZoneInfoManager->isPKZone(pZone->getZoneID())) {
		pUpdateInfo->setLightLevel(14);
		pUpdateInfo->setDarkLevel(0);
	} else if (pCreature->isSlayer()) {
		if (pCreature->isFlag(Effect::EFFECT_CLASS_LIGHTNESS)) {
			pUpdateInfo->setLightLevel(15);
			pUpdateInfo->setDarkLevel(1);
		} else if (pCreature->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) {
			pUpdateInfo->setDarkLevel(15);
			pUpdateInfo->setLightLevel(1);
		} else {
			pUpdateInfo->setDarkLevel(pZone->getDarkLevel());
			pUpdateInfo->setLightLevel(pZone->getLightLevel());
		}
	} else if (pCreature->isVampire()) {
		pUpdateInfo->setDarkLevel(max(0, DARK_MAX - pZone->getDarkLevel()));
		pUpdateInfo->setLightLevel(min(13, LIGHT_MAX - pZone->getLightLevel()));
	} else if (pCreature->isOusters()) {
		if (pCreature->isFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) {
			pUpdateInfo->setDarkLevel(15);
			pUpdateInfo->setLightLevel(1);
		}
	//	else if (pCreature->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
	//	{
	//		pUpdateInfo->setDarkLevel(15);
	//		pUpdateInfo->setLightLevel(3);
	//	}
		else {
			pUpdateInfo->setDarkLevel(13);
			pUpdateInfo->setLightLevel(6);
		}
	}

	////////////////////////////////////////////////////////////
	// 날씨 정보 구성
	////////////////////////////////////////////////////////////
	pUpdateInfo->setWeather(pZone->getWeatherManager()->getCurrentWeather());
	pUpdateInfo->setWeatherLevel(pZone->getWeatherManager()->getWeatherLevel());

	////////////////////////////////////////////////////////////
	// NPC 스프라이트 정보 구성
	////////////////////////////////////////////////////////////
	pUpdateInfo->setNPCCount(pZone->getNPCCount());
	for (uint i = 0; i < pZone->getNPCCount(); i++)
		pUpdateInfo->setNPCType(i , pZone->getNPCType(i));

	////////////////////////////////////////////////////////////
	// 몬스터 스프라이트 정보 구성
	////////////////////////////////////////////////////////////
	// 마스터 레어에서 소환되는 몬스터를 미리 로딩한다.
	if (pZone->isMasterLair()) {
		// 사실은 SpriteType이다. -_-; by sigi. 2002.10.8
		const int num = 25;
		const MonsterType_t mtypes[num] = {
			27,		// 블러드워록
			40,		// 골레머
			41,		// 더티스트라이더
			47,		// 카오스가디언
			48,		// 호블
			57,		// 쉐도우윙
			61,		// 위도우즈
			62,		// 에스트로이더
			64,		// 모데라스
			68,		// 빅팽
			70,		// 다크스크리머
			71,		// 카오스나이트
			72,		// 크림슨슬로터
			73,		// 로드다크니스
			74,		// 리퍼
			75,		// 헬가디언
			76,		// 헬위자드
			88,		// 다크가디언
			89,		// 로드카오스
			90,		// 카오스그리드
			91,		// 헬핀드
			92,		// 다크헤이즈
			101,	// 던울프아크
			102,	// 멈린몬
			103		// 샤먼오프

			//27, 48, 40, 41, 57, 
			//61, 62, 64, 68, 71, 
			//73, 76, 89, 90, 91, 
			//92,103,102, 101
		};

		pUpdateInfo->setMonsterCount(num);
		for (int i = 0; i < num; i++)
			pUpdateInfo->setMonsterType(i, mtypes[i]);
	} else {
		pUpdateInfo->setMonsterCount(pZone->getMonsterCount());
		for (uint i = 0; i < pZone->getMonsterCount(); i++)
			pUpdateInfo->setMonsterType(i , pZone->getMonsterType(i));
	}

	////////////////////////////////////////////////////////////
	// NPC 좌표 정보 구성
	////////////////////////////////////////////////////////////
	list<NPCInfo*>* pNPCInfos = pZone->getNPCInfos();
	list<NPCInfo*>::const_iterator itr = pNPCInfos->begin();
	for (; itr != pNPCInfos->end(); itr++) {
		NPCInfo* pInfo = *itr;
		pUpdateInfo->addNPCInfo(pInfo);
	}
	////////////////////////////////////////////////////////////
	// 서버의 상태 정보
	////////////////////////////////////////////////////////////
	ServerGroupID_t ZoneGroupCount = g_pZoneGroupManager->size();
	UserNum_t ZoneUserNum = 0;

	for(int i = 1; i < ZoneGroupCount+1; i++ ) {
		ZoneGroup* pZoneGroup;

		try {
			pZoneGroup = g_pZoneGroupManager->getZoneGroup(i);
		} catch (NoSuchElementException&) {
			throw Error("Critical Error : ZoneInfoManager에 해당 존그룹이 존재하지 않습니다.");
		}

		ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();
		ZoneUserNum += pZonePlayerManager->size();

	}

	int UserModify = 0;

	//ServerGroupID_t CurrentServerGroupID = g_pConfig->getPropertyInt("ServerID");

	/*
	if(CurrentServerGroupID == 0 
		|| CurrentServerGroupID == 1 
		|| CurrentServerGroupID == 2 
		|| CurrentServerGroupID == 7 ) {
		UserModify = 400;
	}
	*/
	UserModify = 1000;

	if (ZoneUserNum < 100 + UserModify)
		pUpdateInfo->setServerStat(SERVER_FREE);
	else if (ZoneUserNum < 250 + UserModify ) 
		pUpdateInfo->setServerStat(SERVER_NORMAL);
	else if (ZoneUserNum < 400 + UserModify ) 
		pUpdateInfo->setServerStat(SERVER_BUSY);
	else if (ZoneUserNum < 500 + UserModify ) 
		pUpdateInfo->setServerStat(SERVER_VERY_BUSY);
	else if (ZoneUserNum >= 800 + UserModify ) 
		pUpdateInfo->setServerStat(SERVER_FULL);
	else 
		pUpdateInfo->setServerStat(SERVER_DOWN);

	// 프리미엄 정보 설정
	if (pZone->isPremiumZone()) pUpdateInfo->setPremiumZone();

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
	Assert(pGamePlayer!=NULL);

	if (pGamePlayer->isPremiumPlay()) pUpdateInfo->setPremiumPlay();

	static bool bNonPK = g_pGameServerInfoManager->getGameServerInfo(1, g_pConfig->getPropertyInt("ServerID" ), g_pConfig->getPropertyInt("WorldID" ) )->isNonPKServer();

	if (bNonPK) {
		pUpdateInfo->setNonPK(1);
//		cout << "PK불가능" << endl;
	} else {
		pUpdateInfo->setNonPK(0);
//		cout << "PK가능" << endl;
	}

	// GuildUnion Information
	PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert(pPlayerCreature != NULL);
	
	GuildUnion *pUnion = NULL;
	pUnion = GuildUnionManager::Instance().getGuildUnion(pPlayerCreature->getGuildID());

	// 소속된 연합이 없으면
	if(pUnion == NULL) {
		pUpdateInfo->setGuildUnionID(0);
		pUpdateInfo->setGuildUnionUserType(GCUpdateInfo::UNION_NOTHING);
//		cout << "GCUpdateInfo->getGuildUnionUserType() : UNION_NOTHING (NOT UNION)" << endl;
	} else {
		// 소속된 연합이 있다.
		bool	isGuildMaster = false;
		bool	isGuildUnionMaster = false;

		pUpdateInfo->setGuildUnionID(pUnion->getUnionID());
		
		if(g_pGuildManager->isGuildMaster(pPlayerCreature->getGuildID(), pPlayerCreature))
			isGuildMaster = true;

		if(pUnion->getMasterGuildID() == pPlayerCreature->getGuildID())
			isGuildUnionMaster = true;

		if(isGuildMaster && isGuildUnionMaster) {
			pUpdateInfo->setGuildUnionUserType(GCUpdateInfo::UNION_MASTER);
//			cout << "GCUpdateInfo->getGuildUnionUserType() : UNION_MASTER" << endl;
		} else if(isGuildMaster && !isGuildUnionMaster) {
			pUpdateInfo->setGuildUnionUserType(GCUpdateInfo::UNION_GUILD_MASTER);
//			cout << "GCUpdateInfo->getGuildUnionUserType() : UNION_GUILD_MASTER" << endl;
		} else {
			pUpdateInfo->setGuildUnionUserType(GCUpdateInfo::UNION_NOTHING);
//			cout << "GCUpdateInfo->getGuildUnionUserType() : UNION_NOTHING" << endl;
		}
	}

	pUpdateInfo->setBloodBibleSignInfo(pPlayerCreature->getBloodBibleSign());

	// 파워 포인트
	pUpdateInfo->setPowerPoint(pPlayerCreature->getPowerPoint());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 추가 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddSlayer(GCAddSlayer* pAddSlayer, Slayer* pSlayer) 
	throw()
{
	__BEGIN_TRY

	pAddSlayer->setSlayerInfo(pSlayer->getSlayerInfo3());
	pAddSlayer->setEffectInfo(pSlayer->getEffectInfo());
	pAddSlayer->setPetInfo(pSlayer->getPetInfo());
	pAddSlayer->setNicknameInfo(pSlayer->getNickname());
	pAddSlayer->setStoreInfo(&(pSlayer->getStore()->getStoreInfo()));

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 추가 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddVampire(GCAddVampire* pAddVampire, Vampire* pVampire) 
	throw()
{
	__BEGIN_TRY

	pAddVampire->setVampireInfo(pVampire->getVampireInfo3());
	pAddVampire->setEffectInfo(pVampire->getEffectInfo());
	pAddVampire->setPetInfo(pVampire->getPetInfo());
	pAddVampire->setNicknameInfo(pVampire->getNickname());
	pAddVampire->setStoreInfo(&(pVampire->getStore()->getStoreInfo()));

	//cout << "makeGCAddVampire: CoatType=" << (int)(pAddVampire->getVampireInfo().getCoatType()) << endl;

	// 개인용 포탈을 이용해서 이동한 것이라면...
	if (pVampire->isFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL))
		pAddVampire->setFromFlag(1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 아우스터스 추가 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddOusters(GCAddOusters* pAddOusters, Ousters* pOusters) 
	throw()
{
	__BEGIN_TRY

	pAddOusters->setOustersInfo(pOusters->getOustersInfo3());
	pAddOusters->setEffectInfo(pOusters->getEffectInfo());
	pAddOusters->setPetInfo(pOusters->getPetInfo());
	pAddOusters->setNicknameInfo(pOusters->getNickname());
	pAddOusters->setStoreInfo(&(pOusters->getStore()->getStoreInfo()));

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 추가 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddMonster(GCAddMonster* pAddMonster, Monster* pMonster) 
	throw()
{
	__BEGIN_TRY

	pAddMonster->setObjectID(pMonster->getObjectID());
	pAddMonster->setMonsterType(pMonster->getMonsterType());
	pAddMonster->setMonsterName(pMonster->getName());
	pAddMonster->setX(pMonster->getX());
	pAddMonster->setY(pMonster->getY());
	pAddMonster->setDir(pMonster->getDir());
	pAddMonster->setEffectInfo(pMonster->getEffectInfo());
	pAddMonster->setCurrentHP(pMonster->getHP());
	pAddMonster->setMaxHP(pMonster->getHP(ATTR_MAX)); 

	// 개인용 포탈을 이용해서 이동한 것이라면...
	if (pMonster->isFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL))
		pAddMonster->setFromFlag(1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// NPC 추가 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddNPC(GCAddNPC* pAddNPC, NPC* pNPC) 
	throw()
{
	__BEGIN_TRY

	pAddNPC->setObjectID(pNPC->getObjectID());
	pAddNPC->setName(pNPC->getName());
	pAddNPC->setNPCID(pNPC->getNPCID());
	pAddNPC->setSpriteType(pNPC->getSpriteType());
	pAddNPC->setMainColor(pNPC->getMainColor());
	pAddNPC->setSubColor(pNPC->getSubColor());
	pAddNPC->setX(pNPC->getX());
	pAddNPC->setY(pNPC->getY());
	pAddNPC->setDir(pNPC->getDir());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 새로운 아이템을 존에다 추가할 때 보내는 GCAddNewItemToZone을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddNewItemToZone(GCAddNewItemToZone* pAddNewItemToZone, Item* pItem, int X, int Y)
	throw()
{
	__BEGIN_TRY

	Item::ItemClass IClass = pItem->getItemClass();

	pAddNewItemToZone->setObjectID(pItem->getObjectID());
	pAddNewItemToZone->setX(X);
	pAddNewItemToZone->setY(Y);
	pAddNewItemToZone->setItemClass(IClass);
	pAddNewItemToZone->setItemType(pItem->getItemType());
	pAddNewItemToZone->setOptionType(pItem->getOptionTypeList());
	pAddNewItemToZone->setDurability(pItem->getDurability());
	pAddNewItemToZone->setSilver(pItem->getSilver());
	pAddNewItemToZone->setGrade(pItem->getGrade());
	pAddNewItemToZone->setEnchantLevel(pItem->getEnchantLevel());
	pAddNewItemToZone->setItemNum(pItem->getNum());

	// 총 계열의 무기는 총알 숫자를 아이템 숫자에 실어서 보낸다.
	if (IClass == Item::ITEM_CLASS_AR) 
	{
		AR * pAR = dynamic_cast<AR*>(pItem);
		pAddNewItemToZone->setItemNum(pAR->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SG) 
	{
		SG * pSG = dynamic_cast<SG*>(pItem);
		pAddNewItemToZone->setItemNum(pSG->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SMG) 
	{
		SMG * pSMG = dynamic_cast<SMG*>(pItem);
		pAddNewItemToZone->setItemNum(pSMG->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SR) 
	{
		SR * pSR = dynamic_cast<SR*>(pItem);
		pAddNewItemToZone->setItemNum(pSR->getBulletCount());
	} 
	// 벨트라면 안에 들어있는 포션이나 탄창에 대한 정보도 날려줘야 한다.
	else if (IClass == Item::ITEM_CLASS_BELT) 
	{
		Belt*      pBelt          = dynamic_cast<Belt*>(pItem);
		Inventory* pBeltInventory = pBelt->getInventory();
		BYTE       SubItemCount   = 0;

		// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
		for(int i = 0; i < pBelt->getPocketCount(); i++) 
		{
			Item * pBeltItem = pBeltInventory->getItem(i, 0);
			if (pBeltItem != NULL) 
			{
				SubItemInfo * pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pBeltItem->getObjectID());
				pSubItemInfo->setItemClass(pBeltItem->getItemClass());
				pSubItemInfo->setItemType(pBeltItem->getItemType());
				pSubItemInfo->setItemNum(pBeltItem->getNum());
				pSubItemInfo->setSlotID(i);

				pAddNewItemToZone->addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}

		pAddNewItemToZone->setListNum(SubItemCount);
	}
	// 암스밴드라면 안에 들어있는 포션이나 탄창에 대한 정보도 날려줘야 한다.
	else if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) 
	{
		OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
		Inventory* pOustersArmsbandInventory = pOustersArmsband->getInventory();
		BYTE SubItemCount = 0;

		// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
		for(int i = 0; i < pOustersArmsband->getPocketCount(); i++) 
		{
			Item * pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
			if (pOustersArmsbandItem != NULL) 
			{
				SubItemInfo * pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
				pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
				pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
				pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
				pSubItemInfo->setSlotID(i);

				pAddNewItemToZone->addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}

		pAddNewItemToZone->setListNum(SubItemCount);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 새로운 아이템을 존에다 추가할 때 보내는 GCDropItemToZone을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCDropItemToZone(GCDropItemToZone* pDropItemToZone, Item* pItem, int X, int Y)
	throw()
{
	__BEGIN_TRY

	Item::ItemClass IClass = pItem->getItemClass();

	pDropItemToZone->setObjectID(pItem->getObjectID());
	pDropItemToZone->setX(X);
	pDropItemToZone->setY(Y);
	pDropItemToZone->setItemClass(IClass);
	pDropItemToZone->setItemType(pItem->getItemType());
	pDropItemToZone->setOptionType(pItem->getOptionTypeList());
	pDropItemToZone->setDurability(pItem->getDurability());
	pDropItemToZone->setSilver(pItem->getSilver());
	pDropItemToZone->setGrade(pItem->getGrade());
	pDropItemToZone->setEnchantLevel(pItem->getEnchantLevel());
	pDropItemToZone->setItemNum(pItem->getNum());

	// 총 계열의 무기는 총알 숫자를 아이템 숫자에 실어서 보낸다.
	if (IClass == Item::ITEM_CLASS_AR) 
	{
		AR * pAR = dynamic_cast<AR*>(pItem);
		pDropItemToZone->setItemNum(pAR->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SG) 
	{
		SG * pSG = dynamic_cast<SG*>(pItem);
		pDropItemToZone->setItemNum(pSG->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SMG) 
	{
		SMG * pSMG = dynamic_cast<SMG*>(pItem);
		pDropItemToZone->setItemNum(pSMG->getBulletCount());
	} 
	else if (IClass == Item::ITEM_CLASS_SR) 
	{
		SR * pSR = dynamic_cast<SR*>(pItem);
		pDropItemToZone->setItemNum(pSR->getBulletCount());
	} 
	// 벨트라면 안에 들어있는 포션이나 탄창에 대한 정보도 날려줘야 한다.
	else if (IClass == Item::ITEM_CLASS_BELT) 
	{
		Belt*      pBelt          = dynamic_cast<Belt*>(pItem);
		Inventory* pBeltInventory = pBelt->getInventory();
		BYTE       SubItemCount   = 0;

		// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
		for(int i = 0; i < pBelt->getPocketCount(); i++) 
		{
			Item * pBeltItem = pBeltInventory->getItem(i, 0);
			if (pBeltItem != NULL) 
			{
				SubItemInfo * pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pBeltItem->getObjectID());
				pSubItemInfo->setItemClass(pBeltItem->getItemClass());
				pSubItemInfo->setItemType(pBeltItem->getItemType());
				pSubItemInfo->setItemNum(pBeltItem->getNum());
				pSubItemInfo->setSlotID(i);

				pDropItemToZone->addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}

		pDropItemToZone->setListNum(SubItemCount);
	}
	// 암스밴드라면 안에 들어있는 포션이나 탄창에 대한 정보도 날려줘야 한다.
	else if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) 
	{
		OustersArmsband* pOustersArmsband = dynamic_cast<OustersArmsband*>(pItem);
		Inventory* pOustersArmsbandInventory = pOustersArmsband->getInventory();
		BYTE SubItemCount = 0;

		// 포켓의 숫자만큼 아이템의 정보를 읽어 들인다.
		for(int i = 0; i < pOustersArmsband->getPocketCount(); i++) 
		{
			Item * pOustersArmsbandItem = pOustersArmsbandInventory->getItem(i, 0);
			if (pOustersArmsbandItem != NULL) 
			{
				SubItemInfo * pSubItemInfo = new SubItemInfo();
				pSubItemInfo->setObjectID(pOustersArmsbandItem->getObjectID());
				pSubItemInfo->setItemClass(pOustersArmsbandItem->getItemClass());
				pSubItemInfo->setItemType(pOustersArmsbandItem->getItemType());
				pSubItemInfo->setItemNum(pOustersArmsbandItem->getNum());
				pSubItemInfo->setSlotID(i);

				pDropItemToZone->addListElement(pSubItemInfo);

				SubItemCount++;
			}
		}

		pDropItemToZone->setListNum(SubItemCount);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 존에다 슬레이어 시체를 추가할 때 보내는 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddSlayerCorpse(GCAddSlayerCorpse* pAddSlayerCorpse, SlayerCorpse* pSlayerCorpse) 
	throw()
{
	__BEGIN_TRY

	pAddSlayerCorpse->setSlayerInfo(pSlayerCorpse->getSlayerInfo());
	pAddSlayerCorpse->setTreasureCount(pSlayerCorpse->getTreasureCount());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 존에다 뱀파이어 시체를 추가할 때 보내는 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddVampireCorpse(GCAddVampireCorpse* pAddVampireCorpse, VampireCorpse* pVampireCorpse) 
	throw()
{
	__BEGIN_TRY

	pAddVampireCorpse->setVampireInfo(pVampireCorpse->getVampireInfo());
	pAddVampireCorpse->setTreasureCount(pVampireCorpse->getTreasureCount());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 존에다 몬스터 시체를 추가할 때 보내는 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddMonsterCorpse(GCAddMonsterCorpse* pAddMonsterCorpse, MonsterCorpse* pMonsterCorpse, int X, int Y) 
	throw()
{
	__BEGIN_TRY

	pAddMonsterCorpse->setObjectID(pMonsterCorpse->getObjectID());
	pAddMonsterCorpse->setMonsterType(pMonsterCorpse->getMonsterType());
	pAddMonsterCorpse->setMonsterName(pMonsterCorpse->getMonsterName());
	pAddMonsterCorpse->setX(X);
	pAddMonsterCorpse->setY(Y);
	pAddMonsterCorpse->setDir(pMonsterCorpse->getDir());
	pAddMonsterCorpse->setTreasureCount(pMonsterCorpse->getTreasureCount());
	pAddMonsterCorpse->sethasHead(pMonsterCorpse->gethasHead());
	pAddMonsterCorpse->setLastKiller(pMonsterCorpse->getLastKiller());

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 존에다 아우스터즈 시체를 추가할 때 보내는 패킷을 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCAddOustersCorpse(GCAddOustersCorpse* pAddOustersCorpse, OustersCorpse* pOustersCorpse) 
	throw()
{
	__BEGIN_TRY

	pAddOustersCorpse->setOustersInfo(pOustersCorpse->getOustersInfo());
	pAddOustersCorpse->setTreasureCount(pOustersCorpse->getTreasureCount());

	__END_CATCH
}
//////////////////////////////////////////////////////////////////////////////
// 다른 사람의 최대 체력 같은 것이 변경되었을 경우에 날아가는 
// GCOtherModifyInfo를 구성한다.
//////////////////////////////////////////////////////////////////////////////
void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Slayer* pSlayer, const SLAYER_RECORD* prev)
{
	SLAYER_RECORD cur;
	pSlayer->getSlayerRecord(cur);

	pInfo->setObjectID(pSlayer->getObjectID());

	if (prev->pHP[ATTR_CURRENT] != cur.pHP[ATTR_CURRENT]) pInfo->addShortData(MODIFY_CURRENT_HP, cur.pHP[ATTR_CURRENT]);
	if (prev->pHP[ATTR_MAX    ] != cur.pHP[ATTR_MAX    ]) pInfo->addShortData(MODIFY_MAX_HP,     cur.pHP[ATTR_MAX]);
}

void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Vampire* pVampire, const VAMPIRE_RECORD* prev)
{
	VAMPIRE_RECORD cur;
	pVampire->getVampireRecord(cur);

	pInfo->setObjectID(pVampire->getObjectID());

	if (prev->pHP[ATTR_CURRENT] != cur.pHP[ATTR_CURRENT]) pInfo->addShortData(MODIFY_CURRENT_HP, cur.pHP[ATTR_CURRENT]);
	if (prev->pHP[ATTR_MAX    ] != cur.pHP[ATTR_MAX    ]) pInfo->addShortData(MODIFY_MAX_HP,     cur.pHP[ATTR_MAX]);
}

void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Ousters* pOusters, const OUSTERS_RECORD* prev)
{
	OUSTERS_RECORD cur;
	pOusters->getOustersRecord(cur);

	pInfo->setObjectID(pOusters->getObjectID());

	if (prev->pHP[ATTR_CURRENT] != cur.pHP[ATTR_CURRENT]) pInfo->addShortData(MODIFY_CURRENT_HP, cur.pHP[ATTR_CURRENT]);
	if (prev->pHP[ATTR_MAX    ] != cur.pHP[ATTR_MAX    ]) pInfo->addShortData(MODIFY_MAX_HP,     cur.pHP[ATTR_MAX]);
}

void makeGCCreateItem(GCCreateItem* pGCCreateItem, Item* pItem, CoordInven_t x, CoordInven_t y) 
	throw(Error)
{
	pGCCreateItem->setObjectID(pItem->getObjectID());
	pGCCreateItem->setItemClass((BYTE)pItem->getItemClass());
	pGCCreateItem->setItemType(pItem->getItemType());
	pGCCreateItem->setOptionType(pItem->getOptionTypeList());
	pGCCreateItem->setDurability(pItem->getDurability());
	pGCCreateItem->setEnchantLevel(pItem->getEnchantLevel());
	pGCCreateItem->setSilver(pItem->getSilver());
	pGCCreateItem->setGrade(pItem->getGrade());
	pGCCreateItem->setItemNum(pItem->getNum());
	pGCCreateItem->setInvenX(x);
	pGCCreateItem->setInvenY(y);

	if (pItem->getItemClass() == Item::ITEM_CLASS_PET_ITEM )
	{
		PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
		list<OptionType_t> olist;

		if (pPetItem->getPetInfo()->getPetOption() != 0 )
			olist.push_back(pPetItem->getPetInfo()->getPetOption());

		pGCCreateItem->setOptionType(olist);
		pGCCreateItem->setDurability(pPetItem->getPetInfo()->getPetHP());
		pGCCreateItem->setEnchantLevel(pPetItem->getPetInfo()->getPetAttr());
		pGCCreateItem->setSilver(pPetItem->getPetInfo()->getPetAttrLevel());
		pGCCreateItem->setGrade((pPetItem->getPetInfo()->getPetHP()==0)?(pPetItem->getPetInfo()->getLastFeedTime().daysTo(VSDateTime::currentDateTime() )):(-1));
		pGCCreateItem->setItemNum(pPetItem->getPetInfo()->getPetLevel());
	}
}

void sendPayInfo(GamePlayer* pGamePlayer)
	throw(Error)
{
	__BEGIN_TRY

	/*
	char str[80];
	if (pGamePlayer->isPayPlaying())
	{
		Timeval currentTime;
		getCurrentTime(currentTime);
		Timeval payTime = pGamePlayer->getPayPlayTime(currentTime);

		if (pGamePlayer->getPayPlayType()==PAY_PLAY_TYPE_PERSON)
		{
			strcpy(str, "[개인] ");
		}
		else
		{
			strcpy(str, "[PC방] ");
		}

		if (pGamePlayer->getPayType()==PAY_TYPE_FREE)
		{	
			strcat(str, "유료서비스지만 무료 계정입니다.");
		}
		else if (pGamePlayer->getPayType()==PAY_TYPE_PERIOD)
		{	
			sprintf(str, "%s%s 까지 사용가능합니다.", str, pGamePlayer->getPayPlayAvailableDateTime().toString().c_str());
		}
		else
		{
			sprintf(str, "%s사용시간 : %d / %d 분", str, (payTime.tv_sec/60), pGamePlayer->getPayPlayAvailableHours());
		}
	}
	else
	{	
		strcpy(str, "무료 게임 중입니다.");
	}

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(str);
	pGamePlayer->sendPacket (&gcSystemMessage);
	*/

	__END_CATCH
}

// 주위에 LevelUp effect를 뿌려준다.
void sendEffectLevelUp(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);
	//Assert(pCreature->isPC());

	// 주위에 뿌려준다.
	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pCreature->getObjectID());
	gcAddEffect.setDuration(10);	// 별로 의미없지만 1초로 설정

	if (pCreature->isSlayer())
	{
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LEVELUP_SLAYER);
	}
	else if (pCreature->isVampire())
	{
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LEVELUP_VAMPIRE);
	}
	else if (pCreature->isOusters())
	{
		gcAddEffect.setEffectID(Effect::EFFECT_CLASS_LEVELUP_OUSTERS);
	}

	pCreature->getZone()->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffect);

	//cout << "send LEVEL UP : " << gcAddEffect.toString().c_str() << endl;

	__END_CATCH
}

void sendSystemMessage(GamePlayer* pGamePlayer, const string& msg)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pGamePlayer!=NULL);

	// 존에 있다면 바로 보내준다.
	if (pGamePlayer->getPlayerStatus()==GPS_NORMAL)
	{
		GCSystemMessage gcSystemMessage;

		gcSystemMessage.setMessage(msg);

		pGamePlayer->sendPacket(&gcSystemMessage);
	}
	// 존에 없다면.. GamePlayer에 추가해두고 나중에 보내준다.
	else
	{
		Event* pEvent = pGamePlayer->getEvent(Event::EVENT_CLASS_SYSTEM_MESSAGE);
		EventSystemMessage* pEventSystemMessage = NULL;

		if (pEvent==NULL)
		{
			pEvent = pEventSystemMessage = new EventSystemMessage(pGamePlayer);
			// 존에 들어가자 마자 처리된다.
			pEvent->setDeadline(0);
			pGamePlayer->addEvent(pEvent);
		}
		else
		{
			pEventSystemMessage = dynamic_cast<EventSystemMessage*>(pEvent);
		}

		Assert(pEventSystemMessage!=NULL);
		pEventSystemMessage->addMessage(msg);

		//cout << "NOT GPS_NORMAL: EventSystemMessage" << endl;
	}

	__END_CATCH
}

bool makeGCWarScheduleList(GCWarScheduleList* pGCWarScheduleList, ZoneID_t zoneID) 
	throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = getZoneByZoneID(zoneID);
	Assert(pZone!=NULL);
	Assert(pZone->isCastle());

	WarScheduler* pWarScheduler = pZone->getWarScheduler();
	Assert(pWarScheduler!=NULL);

	pWarScheduler->makeGCWarScheduleList(pGCWarScheduleList);

	__END_CATCH

	return true;
}

/*void makeGCItemNameInfoList(GCItemNameInfoList* pInfo, PlayerCreature* pPC)
	throw(Error)
{
	__BEGIN_TRY

	list<ItemNameInfo*>& itemNameInfos = pPC->getItemNameInfoList();
	list<ItemNAmeInfo*>::const_iterator itr = itemNameInfos.begin();

	for(; itr != itemNameInfos.end() ; itr++ )
	{
		pInfo->addItemNameInfo(*itr);
	}

	__END_CATCH
}*/

void sendGCMiniGameScores(PlayerCreature* pPC, BYTE gameType, BYTE Level )
{
	GCMiniGameScores gcMGS;
	gcMGS.setGameType((GameType)gameType);
	gcMGS.setLevel(Level);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT Name, Score FROM MiniGameScores WHERE Type=%u AND Level=%u LIMIT 1", gameType, Level);

		// UPDATE인 경우는 Result* 대신에.. pStmt->getAffectedRowCount()
		if (pResult->next())
		{
			gcMGS.addScore(pResult->getString(1), pResult->getInt(2));
		}

/*		pResult = pStmt->executeQuery(
				"SELECT Score FROM MiniGameScores WHERE Type=%u AND Level=%u AND Name='%s' LIMIT 1",
					gameType, Level, pPC->getName().c_str());

		if (pResult->next())
		{
			gcMGS.addScore(pPC->getName(), pResult->getInt(1));
		}*/

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	pPC->getPlayer()->sendPacket(&gcMGS);
}

void makeGCPetStashList(GCPetStashList* pPacket, PlayerCreature* pPC )
{
	for (int i=0; i<MAX_PET_STASH; ++i )
	{
		PetItem* pPetItem = dynamic_cast<PetItem*>(pPC->getPetStashItem(i));

		if (pPetItem != NULL )
		{
			PetStashItemInfo* pInfo = new PetStashItemInfo;
			pInfo->pPetInfo = pPetItem->getPetInfo();
			pInfo->KeepDays = 0;

			pPacket->getPetStashItemInfos()[i] = pInfo;
		}
	}

	//cout << pPacket->toString() << endl;
}
