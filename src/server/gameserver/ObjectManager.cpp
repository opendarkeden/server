//////////////////////////////////////////////////////////////////////////////
// Filename    : ObjectManager.cpp 
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ObjectManager.h"
#include "Assert1.h"
#include "CreatureManager.h"
//#include "LogClient.h"
#include "PlayerManager.h"
#include "MonsterInfo.h"
#include "TimeManager.h"
#include "DarkLightInfo.h"
#include "VisionInfo.h"
#include "WeatherInfo.h"
#include "ZoneGroupManager.h"
#include "ZoneInfoManager.h"
#include "ItemInfoManager.h"
#include "ItemMineInfo.h"
#include "ItemFactoryManager.h"
#include "ItemLoaderManager.h"
#include "SkillInfo.h"
#include "SkillDomainInfoManager.h"
#include "GameWorldInfoManager.h"
#include "SkillParentInfo.h"
#include "SkillHandlerManager.h"
#include "VolumeInfo.h"
#include "OptionInfo.h"
#include "PCFinder.h"
#include "ParkingCenter.h"
#include "TelephoneCenter.h"
#include "ScriptManager.h"
#include "ShopTemplate.h"
#include "PriceManager.h"
#include "TradeManager.h"
#include "Directive.h"
#include "MonsterNameManager.h"
#include "GuildManager.h"
#include "ResurrectLocationManager.h"
#include "AlignmentManager.h"
#include "WayPoint.h"
#include "Party.h"
#include "VariableManager.h"
#include "CombatInfoManager.h"
#include "UniqueItemManager.h"
#include "Properties.h"

#include "quest/ConditionFactoryManager.h"
#include "quest/ActionFactoryManager.h"

//#include "AttrBalanceInfo.h"

#include "EffectLoaderManager.h"
#include "VampEXPInfo.h"
#include "OustersEXPInfo.h"
#include "FlagSet.h"
#include <stdio.h>

// by sigi. 2002.8.31
//#include "RankEXPInfo.h"

// by Sequoia 2004.1.8
#include "RankExpTable.h"

// by sigi. 2002.9.2
#include "MasterLairInfoManager.h"
// 2003. 1. 20. by bezz, Sequoia
#include "CastleInfoManager.h"

// by sigi. 2002.10.21
//#include "LuckInfo.h"

// by sigi. 2002.10.30
#include "LogNameManager.h"

// by bezz. 2002.11.18
#include "RankBonusInfo.h"

//#include "GuildRegistrationManager.h"
//#include "GuildVoteManager.h"

//#include "MonsterKillQuest.h"

// 아담의 성지 보너스
//#include "HolyLandRaceBonus.h"
#include "WarSystem.h"
#include "War.h"

#include "ShrineInfoManager.h"
#include "CastleShrineInfoManager.h"

#include "HolyLandManager.h"
#include "BloodBibleBonusManager.h"
#include "SkillPropertyManager.h"
#include "RaceWarLimiter.h"

// 커플 이벤트용
#include "CoupleManager.h"

// PK존용
#include "PKZoneInfoManager.h"

// 성지스킬
#include "CastleSkillInfo.h"

#include "StringPool.h"
//#include "FameLimitInfo.h"
#include "GameServerGroupInfoManager.h"

#include "GoodsInfoManager.h"
#include "mission/EventQuestLootingManager.h"
#include "ctf/FlagManager.h"

#include "DefaultOptionSetInfo.h"

#include "LevelWarZoneInfoManager.h"
#include "SweeperBonusManager.h"
#include "RegenZoneManager.h"
#include "PetTypeInfo.h"
#include "PetAttrInfo.h"
#include "PetExpInfo.h"

#include "SlayerAttrExpTable.h"
#include "ItemGradeManager.h"
#include "EventZoneInfo.h"

#include "SystemAvailabilitiesManager.h"
#include "LevelNickInfoManager.h"

#include "GQuestInfo.h"
#include "GQuestElement.h"
#include "GQuestCheckPoint.h"
#include "SiegeManager.h"

//#include "gameguard/CSAuth.h"
#include "GuildUnion.h"
#include "war/DragonEyeManager.h"
#include "AdvancementClassExpTable.h"

#include "TimeChecker.h"

#include "DynamicZoneManager.h"
#include "DynamicZoneInfo.h"
#include "DynamicZoneFactoryManager.h"

/*// 심플퀘스트
#include "mission/QuestInfoManager.h"
#include "mission/RewardClassInfoManager.h"
*/
//////////////////////////////////////////////////////////////////////////////
// class ObjectManager member methods
//////////////////////////////////////////////////////////////////////////////

ObjectManager::ObjectManager ()
	throw(Error)
{
	__BEGIN_TRY

	FlagSet::initialize();

	g_pStringPool				= new StringPool();
	g_pZoneInfoManager          = new ZoneInfoManager ();
	g_pVariableManager          = new VariableManager();
	g_pItemInfoManager          = new ItemInfoManager ();
	g_pItemFactoryManager       = new ItemFactoryManager ();
	g_pVolumeInfoManager        = new VolumeInfoManager();
	g_pItemLoaderManager        = new ItemLoaderManager();
	g_pShopTemplateManager      = new ShopTemplateManager();
	g_pOptionInfoManager        = new OptionInfoManager ();
	g_pItemMineInfoManager		= new ItemMineInfoManager();
	g_pDirectiveSetManager      = new DirectiveSetManager();
	g_pMonsterNameManager       = new MonsterNameManager();
	g_pZoneGroupManager         = new ZoneGroupManager ();
	g_pTimeManager              = new TimeManager ();
	g_pDarkLightInfoManager     = new DarkLightInfoManager ();
	g_pVisionInfoManager        = new VisionInfoManager ();
	g_pWeatherInfoManager       = new WeatherInfoManager ();
	g_pMonsterInfoManager       = new MonsterInfoManager ();
	g_pSkillHandlerManager      = new SkillHandlerManager ();
	g_pSkillInfoManager         = new SkillInfoManager ();
	g_pSkillDomainInfoManager   = new SkillDomainInfoManager ();
	//g_pSkillParentInfoManager   = new SkillParentInfoManager ();
	g_pPCFinder                 = new PCFinder();
	g_pParkingCenter            = new ParkingCenter();
	g_pTelephoneCenter          = new TelephoneCenter();
	g_pPublicScriptManager      = new ScriptManager();
	//g_pSkillParentInfoManager   = new SkillParentInfoManager();
	g_pConditionFactoryManager  = new ConditionFactoryManager();
	g_pActionFactoryManager     = new ActionFactoryManager();
//	g_pDEXBalanceInfoManager    = new DEXBalanceInfoManager();
//	g_pSTRBalanceInfoManager    = new STRBalanceInfoManager();
//	g_pINTBalanceInfoManager    = new INTBalanceInfoManager();
	g_pVampEXPInfoManager       = new VampEXPInfoManager();
	g_pOustersEXPInfoManager    = new OustersEXPInfoManager();
	g_pPriceManager             = new PriceManager();
	g_pEffectLoaderManager      = new EffectLoaderManager();
	//다른 작업을 위해서 임시로 막아둠.
	g_pGuildManager             = new GuildManager();
//	g_pGuildRegistrationManager = new GuildRegistrationManager();
//	g_pGuildVoteManager         = new GuildVoteManager();
	g_pResurrectLocationManager = new ResurrectLocationManager();
	g_pAlignmentManager         = new AlignmentManager();
	g_pWayPointManager          = new WayPointManager();
	g_pGlobalPartyManager       = new GlobalPartyManager();
	g_pGameWorldInfoManager     = new GameWorldInfoManager();
	g_pCombatInfoManager	    = new CombatInfoManager();
	g_pUniqueItemManager	    = new UniqueItemManager();

	// by sigi. 2002.8.31
//	g_pRankEXPInfoManager[RANK_TYPE_SLAYER]	= new RankEXPInfoManager();
//	g_pRankEXPInfoManager[RANK_TYPE_VAMPIRE] = new RankEXPInfoManager();
//	g_pRankEXPInfoManager[RANK_TYPE_OUSTERS] = new RankEXPInfoManager();

	// by sigi. 2002.9.2
	g_pMasterLairInfoManager	= new MasterLairInfoManager();
	// 2003. 1. 20. by bezz,Sequoia
	g_pCastleInfoManager	= new CastleInfoManager();

//	g_pLuckInfoManager = new LuckInfoManager();

	g_pRankBonusInfoManager = new RankBonusInfoManager();

//	g_pHolyLandRaceBonus	= new HolyLandRaceBonus();

	g_pWarSystem	= new WarSystem();

	g_pShrineInfoManager = new ShrineInfoManager();
	g_pCastleShrineInfoManager = new CastleShrineInfoManager();

	g_pHolyLandManager = new HolyLandManager();

	g_pBloodBibleBonusManager = new BloodBibleBonusManager();

	g_pSkillPropertyManager = new SkillPropertyManager();

	g_pCoupleManager = new CoupleManager();
	g_pPKZoneInfoManager = new PKZoneInfoManager();
//	g_pFameLimitInfoManager = new FameLimitInfoManager();
	g_pGameServerGroupInfoManager = new GameServerGroupInfoManager();
	g_pCastleSkillInfoManager = new CastleSkillInfoManager();

	g_pGoodsInfoManager = new GoodsInfoManager();
	g_pEventQuestLootingManager = new EventQuestLootingManager();

	//g_pQuestInfoManager = new QuestInfoManager();
	//g_pRewardClassInfoManager = new RewardClassInfoManager();

	g_pFlagManager = new FlagManager();
	g_pDefaultOptionSetInfoManager = new DefaultOptionSetInfoManager();

	g_pLevelWarZoneInfoManager = new LevelWarZoneInfoManager();
	g_pSweeperBonusManager = new SweeperBonusManager();
	g_pDragonEyeManager = new DragonEyeManager();
	g_pTimeChecker = new TimeChecker();
	g_pDynamicZoneInfoManager = new DynamicZoneInfoManager();
	g_pDynamicZoneManager = new DynamicZoneManager();
	g_pDynamicZoneFactoryManager = new DynamicZoneFactoryManager();

	__END_CATCH
}

ObjectManager::~ObjectManager ()
	throw(Error)
{
	__BEGIN_TRY

	SAFE_DELETE(g_pStringPool);
	SAFE_DELETE(g_pActionFactoryManager);
	SAFE_DELETE(g_pConditionFactoryManager);
	SAFE_DELETE(g_pPublicScriptManager);
	SAFE_DELETE(g_pPCFinder);
	SAFE_DELETE(g_pParkingCenter);
	SAFE_DELETE(g_pTelephoneCenter);
	SAFE_DELETE(g_pItemMineInfoManager);
	SAFE_DELETE(g_pOptionInfoManager); 
	SAFE_DELETE(g_pSkillInfoManager); 
	SAFE_DELETE(g_pSkillDomainInfoManager); 
	SAFE_DELETE(g_pMonsterInfoManager); 
	SAFE_DELETE(g_pItemInfoManager); 
	SAFE_DELETE(g_pWeatherInfoManager); 
	SAFE_DELETE(g_pVisionInfoManager); 
	SAFE_DELETE(g_pDarkLightInfoManager); 
	SAFE_DELETE(g_pTimeManager); 
	SAFE_DELETE(g_pDirectiveSetManager);
	SAFE_DELETE(g_pMonsterNameManager);
	SAFE_DELETE(g_pZoneInfoManager); 
	SAFE_DELETE(g_pZoneGroupManager); 
	SAFE_DELETE(g_pSkillDomainInfoManager); 
	//SAFE_DELETE(g_pSkillParentInfoManager); 
	SAFE_DELETE(g_pSkillHandlerManager); 
	SAFE_DELETE(g_pOptionInfoManager); 
	SAFE_DELETE(g_pItemFactoryManager); 
	SAFE_DELETE(g_pItemLoaderManager); 
//	SAFE_DELETE(g_pSTRBalanceInfoManager);
//	SAFE_DELETE(g_pDEXBalanceInfoManager);
//	SAFE_DELETE(g_pINTBalanceInfoManager);
	SAFE_DELETE(g_pShopTemplateManager);
	SAFE_DELETE(g_pEffectLoaderManager);
	SAFE_DELETE(g_pPriceManager);
	SAFE_DELETE(g_pVampEXPInfoManager);
	SAFE_DELETE(g_pOustersEXPInfoManager);
	SAFE_DELETE(g_pGuildManager);
//	SAFE_DELETE(g_pGuildRegistrationManager);
//	SAFE_DELETE(g_pGuildVoteManager);
	SAFE_DELETE(g_pResurrectLocationManager);
	SAFE_DELETE(g_pAlignmentManager);
	SAFE_DELETE(g_pWayPointManager);
	SAFE_DELETE(g_pGlobalPartyManager);
	SAFE_DELETE(g_pGameWorldInfoManager);
	SAFE_DELETE(g_pVariableManager);
	SAFE_DELETE(g_pCombatInfoManager);
	SAFE_DELETE(g_pUniqueItemManager);
	// by sigi. 2002.8.31
//	SAFE_DELETE(g_pRankEXPInfoManager[RANK_TYPE_SLAYER]);
//	SAFE_DELETE(g_pRankEXPInfoManager[RANK_TYPE_VAMPIRE]);
//	SAFE_DELETE(g_pRankEXPInfoManager[RANK_TYPE_OUSTERS]);
	SAFE_DELETE(g_pMasterLairInfoManager);
	SAFE_DELETE(g_pCastleInfoManager);
//	SAFE_DELETE(g_pLuckInfoManager);
	SAFE_DELETE(g_pRankBonusInfoManager);
//	SAFE_DELETE(g_pHolyLandRaceBonus);
	SAFE_DELETE(g_pWarSystem);
	SAFE_DELETE(g_pShrineInfoManager);
	SAFE_DELETE(g_pCastleShrineInfoManager);

	SAFE_DELETE(g_pHolyLandManager);

	SAFE_DELETE(g_pBloodBibleBonusManager);

	SAFE_DELETE(g_pSkillPropertyManager);

	SAFE_DELETE(g_pCoupleManager);
	SAFE_DELETE(g_pPKZoneInfoManager);
//	SAFE_DELETE(g_pFameLimitInfoManager);
	SAFE_DELETE(g_pGameServerGroupInfoManager);
	SAFE_DELETE(g_pCastleSkillInfoManager);

	SAFE_DELETE(g_pGoodsInfoManager);
	SAFE_DELETE(g_pEventQuestLootingManager);

	//SAFE_DELETE(g_pQuestInfoManager);
	//SAFE_DELETE(g_pRewardClassInfoManager);

	SAFE_DELETE(g_pFlagManager);
	SAFE_DELETE(g_pDefaultOptionSetInfoManager);

	SAFE_DELETE(g_pLevelWarZoneInfoManager);
	SAFE_DELETE(g_pSweeperBonusManager);
	SAFE_DELETE(g_pDragonEyeManager);
	SAFE_DELETE(g_pTimeChecker);

	SAFE_DELETE(g_pDynamicZoneInfoManager);
	SAFE_DELETE(g_pDynamicZoneManager);
	SAFE_DELETE(g_pDynamicZoneFactoryManager);
	
	__END_CATCH
}

void ObjectManager::init ()
	 throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG
    cout << "[ObjectManager] Initializing Object Managers..." << endl;
	//printf("ObjectManager::load() : SystemAvailabilitiesManager Initialization Start\n");
	SystemAvailabilitiesManager::getInstance()->load();
	//printf("ObjectManager::load() : SystemAvailabilitiesManager Initialization Success\n");

	//--------------------------------------------------------------------------------
	// 존을 로딩할때, NPC 를 로딩하며 이때 이 팩토리들이 사용되므로
	// 존 로딩보다 먼저 호출되어야 한다.
	//--------------------------------------------------------------------------------
	//printf("ObjectManager::init() : StringPool Initialization Start....... \n");
	g_pStringPool->load();
	//printf("ObjectManager::init() : StringPool Initialization Success....... \n");

	//printf("ObjectManager::init() : VariableManager Initialization Start....... \n");
	g_pVariableManager->init();
	//printf("ObjectManager::init() : VariableManager Initialization Success....... \n");

	//printf("ObjectManager::init() : ConditionFactoryManager Initialization Start\n");
	g_pConditionFactoryManager->init();
	//printf("ObjectManager::init() : ConditionFactoryManager Initialization Success\n");

	//printf("ObjectManager::init() : ActionFactoryManager Initialization Start\n");
	g_pActionFactoryManager->init();
	//printf("ObjectManager::init() : ActionFactoryManager Initialization Success\n");

	//printf("ObjectManager::init() : ShopTemplate Initialization Start\n");
	g_pShopTemplateManager->init();
	//printf("ObjectManager::init() : ShopTemplate Initialization Success\n");

	//printf("ObjectManager::init() : DirectiveSetManager Initialization Start\n");
	g_pDirectiveSetManager->init();
	//printf("ObjectManager::init() : DirectiveSetManager Initialization Success\n");

	//printf("ObjectManager::init() : MonsterNameManager Initialization Start\n");
	g_pMonsterNameManager->init();
	//printf("ObjectManager::init() : MonsterNameManager Initialization Success\n");

	//printf("ObjectManager::init() : TimeManager Initialization Start\n");
	g_pTimeManager->init();
	//printf("ObjectManager::init() : TimeManager Initialization Success\n");

	//printf("ObjectManager::init() : PublicScriptManager Initialization Start\n");
	g_pPublicScriptManager->init();
	//printf("ObjectManager::init() : PublicScriptManager Initialization Success\n");
	
	// option을 itemInfo보다 먼저 load()해야한다.
	//printf("ObjectManager::init() : OptionInfoManager Initialization Start\n");
	g_pOptionInfoManager->init();
	//printf("ObjectManager::init() : OptionInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : SweeperBonusManager Initialization Start....... \n");
	g_pSweeperBonusManager->init();
	//printf("ObjectManager::init() : SweeperBonusManager Initialization Success....... \n");

	//printf("ObjectManager::init() : ItemInfoManager Initialization Start\n");
	g_pItemInfoManager->init();
	//printf("ObjectManager::init() : ItemInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : ItemMineInfoManager Initialization Start\n");
	g_pItemMineInfoManager->load();
	//printf("ObjectManager::init() : ItemMineInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : WarID Initialization Start\n");
	g_pWarSystem->setWarIDSuccessor(g_pConfig->getPropertyInt("ServerCount"));
	War::initWarIDRegistry();
	//printf("ObjectManager::init() : WarID Initialization Success\n");

	//printf("ObjectManager::init() : VolumeInfoManager Initialization Start\n");
	g_pVolumeInfoManager->init();
	//printf("ObjectManager::init() : VolumeInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : ItemFactory Initialization Start\n");
	g_pItemFactoryManager->init();
	//printf("ObjectManager::init() : ItemFactory Initialization Success\n");

	//printf("ObjectManager::init() : ItemLoaderManager Initialization Start\n");
	g_pItemLoaderManager->init();
	//printf("ObjectManager::init() : ItemLoaderManager Initialization Success\n");

	//printf("ObjectManager::init() : DarkLightInfoManager Initialization Start\n");
	g_pDarkLightInfoManager->init();
	//printf("ObjectManager::init() : DarkLightInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : MonsterInfoManager Initialization Start\n");
	g_pMonsterInfoManager->init();
	//printf("ObjectManager::init() : MonsterInfoManager Initialization Success\n");

	// 반드시 ZoneInfoManager보다 먼저 로드되어야 한다.
	// 반드시 OptionInfo 보다 나중에 로드되어야 한다.
/*	printf("ObjectManager::load() : RewardClassInfoManager Initialization Start\n");
	g_pRewardClassInfoManager->load();
	printf("ObjectManager::load() : RewardClassInfoManager Initialization Success\n");*/

	//printf("ObjectManager::init() : EffectLoaderManager Initialization Start\n");
	g_pEffectLoaderManager->init();
	//printf("ObjectManager::init() : EffectLoaderManager Initialization Success\n");

	//printf("ObjectManager::init() : ZoneInfoManager Initialization Start\n");
	g_pZoneInfoManager->init();
	//printf("ObjectManager::init() : ZoneInfoManager Initialization Success\n");

	// by sigi. 2002.9.2
	//printf("ObjectManager::load() : MasterLairInfoManager Initialization Start\n");
	g_pMasterLairInfoManager->init();	// ZoneInfo, MonsterManager이후, Zone 이전에 loading해야 한다.
	//printf("ObjectManager::load() : MasterLairInfoManager Initialization Success\n");

	// by bezz,Sequoia. 2003. 1. 20.
	//printf("ObjectManager::load() : CastleInfoManager Initialization Start\n");
	g_pCastleInfoManager->init();	// ZoneInfo, MonsterManager이후, Zone 이전에 loading해야 한다.
	//printf("ObjectManager::load() : CastleInfoManager Initialization Success\n");

//	printf("ObjectManager::load() : HolyLandRaceBonus Initialization Start\n");
//	g_pHolyLandRaceBonus->refresh();
//	printf("ObjectManager::load() : HolyLandRaceBonus Initialization Success\n");

	//printf("ObjectManager::init() : ZoneGroupManager Initialization Start\n");
	g_pZoneGroupManager->init();
	//printf("ObjectManager::init() : ZoneGroupManager Initialization Success\n");

	//printf("ObjectManager::load() : BloodBibleBonusManager Initialization Start\n");
	g_pBloodBibleBonusManager->init();
	//printf("ObjectManager::load() : BloodBibleBonusManager Initialization Success\n");
		
	// ShrineInfoManager 는 필살로 Zone 이 모두 로딩된 다음에 불려야 한다.
	// BloodBibleBonusManager에 BloodBible 소유 종족을 세팅하므로 BloodBibleBonusManager가 로딩된 다음에 불려야 한다.
	//printf("ObjectManager::init() : ShrineInfoManager Initialization Start\n");
	g_pShrineInfoManager->init();
	//printf("ObjectManager::init() : ShrineInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : CastleShrineInfoManager Initialization Start\n");
	g_pCastleShrineInfoManager->init();
	//printf("ObjectManager::init() : CastleShrineInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : WeatherInfoManager Initialization Start\n");
	g_pWeatherInfoManager->init();
	//printf("ObjectManager::init() : WeatherInfoManager Initialization Success\n");

	// WayPointManager 도 필살로 Zone이 모두 로딩된 다음에 불려야 된다.
	//printf("ObjectManager::load() : WayPointManager Initialization Start\n");
	g_pWayPointManager->load();
	//printf("ObjectManager::load() : WayPointManager Initialization Success\n");

	//printf("ObjectManager::load() : LevelWarZoneInfoManager Initialization Start\n");
	g_pLevelWarZoneInfoManager->init();	// 머 아무때나 Loading 해도 됨
	//printf("ObjectManager::load() : LevelWarZoneInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : LevelNickInfoManager Initialization Start\n");
	LevelNickInfoManager::Instance().load();	// 머 아무때나 Loading 해도 됨
	//printf("ObjectManager::load() : LevelNickInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : DragonEyeManagerManager Initialization Start\n");
	g_pDragonEyeManager->init();	// 아이템 인포가 로딩된 뒤.
	//printf("ObjectManager::load() : DragonEyeManagerManager Initialization Success\n");

	//printf("ObjectManager::init() : TimeChecker Initialization Start\n");
	g_pTimeChecker->init(); // 아무때나 Loading 해도 됨
	//printf("ObjectManager::init() : TimeChecker Initialization Success\n");

    cout << "[ObjectManager] Object Managers Initialized." << endl;
	__END_DEBUG
	__END_CATCH
}


void ObjectManager::load()
	 throw(Error)
{
	__BEGIN_TRY
    cout << "[ObjectManager] Loading Objects..." << endl;
	//--------------------------------------------------------------------------------
	// 존그룹을 로딩하면, 내부적으로 존을 로딩한다.
	// 이때 존 안에 소속된 NPC 들이 로딩되는데.. SetPosition 액션이 수행되기
	// 위해서는 먼저 ZoneInfoManager 가 Initialization되어야 한다.
	// 따라서, ZoneInfoManager -> ZoneGroupManager 순으로 Initialization되어야 한다.
	//--------------------------------------------------------------------------------
	//printf("ObjectManager::init() : ZoneInfoManager Initialization Start\n");
	//g_pZoneInfoManager->init();
	//printf("ObjectManager::init() : ZoneInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : ZoneGroupManager Initialization Start\n");
	//g_pZoneGroupManager->init();
	//printf("ObjectManager::init() : ZoneGroupManager Initialization Success\n");


	//printf("ObjectManager::init() : SkillParentInfoManager Initialization Start\n");
	//g_pSkillParentInfoManager->init();
	//printf("ObjectManager::init() : SkillParentInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : GuildManager Initialization Start\n");
	if (g_pGuildManager!=NULL) g_pGuildManager->init();
	//printf("ObjectManager::init() : GuildManager Initialization Success\n");

	//printf("ObjectManager::init() : GuildUnionManager Initialization Start\n");
	GuildUnionManager::Instance().load();
	//printf("ObjectManager::init() : GuildUnionManager Initialization Success\n");

	//printf("ObjectManager::init() : SkillHandlerManager Initialization Start\n");
	g_pSkillHandlerManager->init();
	//printf("ObjectManager::init() : SkillHandlerManager Initialization Success\n");

	//printf("ObjectManager::init() : SkillInfoManager Initialization Start\n");
	g_pSkillInfoManager->init();
	//printf("ObjectManager::init() : SkillInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : SkillDomainInfoManager Initialization Start\n");
	g_pSkillDomainInfoManager->init();
	//printf("ObjectManager::init() : SkillDomainInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : ResurrectLocationManager Initialization Start\n");
	g_pResurrectLocationManager->init();
	//printf("ObjectManager::init() : ResurrectLocationManager Initialization Success\n");

	// balnce info manager init//abcd
	//printf("ObjectManager::init() : STR Exp Table Initialization Start\n");
//	g_pSTRBalanceInfoManager->init();
	SlayerAttrExpTable::s_SlayerAttrExpTable[ATTR_KIND_STR].load();
	//printf("ObjectManager::init() : STR Exp Table Initialization Success\n");

	//printf("ObjectManager::init() : DEX Exp Table Initialization Start\n");
//	g_pDEXBalanceInfoManager->init();
	SlayerAttrExpTable::s_SlayerAttrExpTable[ATTR_KIND_DEX].load();
	//printf("ObjectManager::init() : DEX Exp Table Initialization Success\n");

	//printf("ObjectManager::init() : INT Exp Table Initialization Start\n");
//	g_pINTBalanceInfoManager->init();
	SlayerAttrExpTable::s_SlayerAttrExpTable[ATTR_KIND_INT].load();
	//printf("ObjectManager::init() : INT Exp Table Initialization Success\n");

	//printf("ObjectManager::init() : VampExpInfoManager Initialization Start\n");
	g_pVampEXPInfoManager->init();
	//printf("ObjectManager::init() : VampExpInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : OustersEXPInfoManager Initialization Start\n");
	g_pOustersEXPInfoManager->init();
	//printf("ObjectManager::init() : OustersEXPInfoManager Initialization Success\n");

	//printf("ObjectManager::init() : AdvancementClassExpTable Initialization Start\n");
	AdvancementClassExpTable::s_AdvancementClassExpTable.load();
	//printf("ObjectManager::init() : AdvancementClassExpTable Initialization Success\n");

	//printf("ObjectManager::init() : VisionInfoManager Initialization Start\n");
	g_pVisionInfoManager->init();
	//printf("ObjectManager::init() : VisionInfoManager Initialization Success\n");

//	printf("ObjectManager::init() : GuildRegistrationManager Initialization Start\n");
//	g_pGuildRegistrationManager->init();
//	printf("ObjectManager::init() : GuildRegistrationManager Initialization Success\n");

//	printf("ObjectManager::init() : GuildVoteManager Initialization Start\n");
//	g_pGuildVoteManager->init();
//	printf("ObjectManager::init() : GuildVoteManager Initialization Success\n");

	//printf("ObjectManager::load() : GameWorldInfoManager Initialization Start\n");
	g_pGameWorldInfoManager->load();
	//printf("ObjectManager::load() : GameWorldInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : CombatInfoManager Initialization Start\n");
	g_pCombatInfoManager->initModify();
	//printf("ObjectManager::load() : CombatInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : UniqueItemManager Initialization Start\n");
	g_pUniqueItemManager->init();
	//printf("ObjectManager::load() : UniqueItemManager Initialization Success\n");

	// by sigi. 2002.8.31
	//printf("ObjectManager::load() : RankExpTables Initialization Start\n");
//	g_pRankEXPInfoManager[RANK_TYPE_SLAYER]->init(RANK_TYPE_SLAYER);
//	g_pRankEXPInfoManager[RANK_TYPE_VAMPIRE]->init(RANK_TYPE_VAMPIRE);
//	g_pRankEXPInfoManager[RANK_TYPE_OUSTERS]->init(RANK_TYPE_OUSTERS);

	// by Sequoia 2004.1.8
	RankExpTable::s_RankExpTables[RANK_TYPE_SLAYER].load();
	RankExpTable::s_RankExpTables[RANK_TYPE_VAMPIRE].load();
	RankExpTable::s_RankExpTables[RANK_TYPE_OUSTERS].load();
	//printf("ObjectManager::load() : RankExpTables Initialization Success\n");

//	printf("ObjectManager::load() : UniqueItemManager Initialization Start\n");
//	g_pLuckInfoManager->init();
//	printf("ObjectManager::load() : UniqueItemManager Initialization Success\n");

	//printf("ObjectManager::load() : LogNameManager Initialization Start\n");
	LogNameManager::getInstance().init();
	//printf("ObjectManager::load() : LogNameManager Initialization Success\n");

	//printf("ObjectManager::load() : RankBonusInfoManager Initialization Start\n");
	g_pRankBonusInfoManager->load();
	//printf("ObjectManager::load() : RankBonusInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : WarSystem Initialization Start\n");
	g_pWarSystem->init();
	//printf("ObjectManager::load() : WarSystem Initialization Success\n");

	//printf("ObjectManager::load() : RaceWarLimiter Initialization Start\n");
	RaceWarLimiter::getInstance()->load();
	//printf("ObjectManager::load() : RaceWarLimiter Initialization Success\n");

	//printf("ObjectManager::load() : PKZoneInfoManager Initialization Start\n");
	g_pPKZoneInfoManager->load();
	//printf("ObjectManager::load() : PKZoneInfoManager Initialization Success\n");

//	printf("ObjectManager::load() : FameLimitInfoManager Initialization Start\n");
//	g_pFameLimitInfoManager->load();
//	printf("ObjectManager::load() : FameLimitInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : GameServerGroupInfoManager Initialization Start\n");
	g_pGameServerGroupInfoManager->init();
	//printf("ObjectManager::load() : GameServerGroupInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : CastleSkillInfoManager Initialization Start\n");
	g_pCastleSkillInfoManager->load();
	//printf("ObjectManager::load() : CastleSkillInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : GoodsInfoManager Initialization Start\n");
	g_pGoodsInfoManager->load();
	//printf("ObjectManager::load() : GoodsInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : EventQuestLootingManager Initialization Start\n");
	g_pEventQuestLootingManager->load();
	//printf("ObjectManager::load() : EventQuestLootingManager Initialization Success\n");

	//printf("ObjectManager::load() : FlagManager Initialization Start\n");
	g_pFlagManager->init();
	//printf("ObjectManager::load() : FlagManager Initialization Success\n");

	//printf("ObjectManager::load() : RegenZoneManager Initialization Start\n");
	RegenZoneManager::getInstance()->load();
	//printf("ObjectManager::load() : RegenZoneManager Initialization Success\n");

	//printf("ObjectManager::load() : DefaultOptionSetInfoManager Initialization Start\n");
	g_pDefaultOptionSetInfoManager->load();
	//printf("ObjectManager::load() : DefaultOptionSetInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : PetTypeInfoManager Initialization Start\n");
	PetTypeInfoManager::getInstance()->load();
	//printf("ObjectManager::load() : PetTypeInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : PetAttrInfoManager Initialization Start\n");
	PetAttrInfoManager::Instance().load();
	//printf("ObjectManager::load() : PetAttrInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : PetExpInfoManager Initialization Start\n");
	PetExpInfoManager::Instance().load();
	//printf("ObjectManager::load() : PetExpInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : ItemGradeManager Initialization Start\n");
	ItemGradeManager::Instance().load();
	//printf("ObjectManager::load() : ItemGradeManager Initialization Success\n");

	//printf("ObjectManager::load() : EventZoneInfoManager Initialization Start\n");
	EventZoneInfoManager::Instance().load();
	//printf("ObjectManager::load() : EventZoneInfoManager Initialization Success\n");

	//printf("ObjectFactory::load() : GQuestElementFactory Initialization Start\n");
	GQuestElementFactory::Instance().init();
	//printf("ObjectFactory::load() : GQuestElementFactory Initialization Success\n");

	//printf("ObjectManager::load() : GQuestInfoManager Initialization Start\n");
	GQuestInfoManager::Instance().load();
	//printf("ObjectManager::load() : GQuestInfoManager Initialization Success\n");

	//printf("ObjectManager::load() : GQuestCheckPoint Initialization Start\n");
	GQuestCheckPoint::Instance().load();
	//printf("ObjectManager::load() : GQuestCheckPoint Initialization Success\n");

	//printf("ObjectManager::load() : SiegeManager Initialization Start\n");
	SiegeManager::Instance().init();
	//printf("ObjectManager::load() : SiegeManager Initialization Success\n");

//	printf("ObjectManager::load() : CSAuth Table Initialization Start\n");
//	LoadAuthTable((g_pConfig->getProperty("HomePath") + "/data/CSAuth.tab").c_str());
//	printf("ObjectManager::load() : CSAuth Table Initialization Success\n");

//	printf("ObjectManager::load() : CSAuth Index Initialization Start\n");
//	LoadAuthIndex((g_pConfig->getProperty("HomePath") + "/data/CSAuth.idx").c_str());
//	printf("ObjectManager::load() : CSAuth Index Initialization Success\n");

	//printf("ObjectManager::load() : DynamicZoneInfoManager Initialization Start\n");
	g_pDynamicZoneInfoManager->init();
	//printf("ObjectManager::load() : DynamicZoneInfoManager Initialization Success\n");

	// DynamicZoneInfoManager init 후에 호출
	//printf("ObjectManager::load() : DynamicZoneManager Initialization Start\n");
	g_pDynamicZoneManager->init();
	//printf("ObjectManager::load() : DynamicZoneManager Initialization Success\n");

	//printf("ObjectManager::load() : DynamicZoneFactoryManager Initialization Start\n");
	g_pDynamicZoneFactoryManager->init();
	//printf("ObjectManager::load() : DynamicZoneFactoryManager Initialization Success\n");

	/*
	printf("ObjectManager::load() : QuestInfoManager Initialization Start\n");
	g_pQuestInfoManager->load();
	printf("ObjectManager::load() : QuestInfoManager Initialization Success\n");
	printf("ObjectManager::load() : DarkLightInfoManager Loading Start\n");
	g_pDarkLightInfoManager->load();
	printf("ObjectManager::load() : DarkLightInfoManager Loading Success\n");

	printf("ObjectManager::load() : MonsterInfoManager Loading Start\n");
	g_pMonsterInfoManager->load();
	printf("ObjectManager::load() : MonsterInfoManager Loading Success\n");

	printf("ObjectManager::load() : WeatherInfoManager Loading Start\n");
	g_pWeatherInfoManager->load();
	printf("ObjectManager::load() : WeatherInfoManager Loading Success\n");

	printf("ObjectManager::load() : ZoneGroupManager Loading Start\n");
	g_pZoneGroupManager->load();
	printf("ObjectManager::load() : ZoneGroupManager Loading Success\n");

	printf("ObjectManager::load() : ZoneInfoManager Loading Start\n");
	g_pZoneInfoManager->load();
	printf("ObjectManager::load() : ZoneInfoManager Loading Success\n");

	printf("ObjectManager::load() : PublicScriptManager Loading Start\n");
	g_pPublicScriptManager->load("");
	printf("ObjectManager::load() : PublicScriptManager Loading Success\n");
	*/

	// by sigi. 2002.12.3
/*#ifdef __ACTIVE_QUEST__
	MonsterKillQuestFactory::initMonsterTypeInfos();
#endif*/
    cout << "[ObjectManager] Objects Loaded." << endl;
	__END_CATCH
}

void ObjectManager::save ()
	 throw(Error)
{
	__BEGIN_TRY

	throw UnsupportedError(__PRETTY_FUNCTION__);

	__END_CATCH
}

// global variable definition
ObjectManager* g_pObjectManager = NULL;
