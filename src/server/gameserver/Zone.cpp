//////////////////////////////////////////////////////////////////////////////
// FileName 	: Zone.cpp
// WrittenBy	:
// Description	:
//////////////////////////////////////////////////////////////////////////////

#include "Zone.h"

#include <stdio.h>
#include <string.h>
#include <list>
#include "Assert1.h"
//#include "LogClient.h"

#include "ZoneGroup.h"
#include "ZoneInfo.h"
#include "ZoneInfoManager.h"
#include "PCManager.h"
#include "NPCManager.h"
#include "MonsterManager.h"
#include "Monster.h"
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
//#include "EffectCallMotorcycle.h"
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

#include <map>

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

// ������ ����� ��ü/�������� �ٴڿ��� �������� �ð�
const Turn_t DELAY_MASTER_LAIR_DECAY_CORPSE 		= 200;	// 20��
const Turn_t DELAY_MASTER_LAIR_DECAY_ITEM   		= 400;	// 40��
const Turn_t DELAY_MASTER_LAIR_DECAY_MASTER_CORPSE 	= 50;	// 5��


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
		*str = tolower(*str);

		str ++;
	}
}

//////////////////////////////////////////////////////////////////////////////
// �Ϲ����� �����͵��� ������ �ν��ϴ��� ������ �ϴ� �Լ�
//////////////////////////////////////////////////////////////////////////////
bool isPotentialEnemy(Monster* pMonster, Creature* pCreature)
{
	Assert(pCreature != NULL);

	if (pMonster->getOwnerObjectID() == pCreature->getObjectID() ) return false;

	if (pMonster->getOwnerObjectID() != 0 )
	{
		Creature* pOwner = pMonster->getZone()->getCreature(pMonster->getOwnerObjectID());
		if (pOwner != NULL && pOwner->getCreatureClass() == pCreature->getCreatureClass() && canAttack(pOwner, pCreature ) )
		{
//			cout << __PRETTY_FUNCTION__ << pCreature->getName() << "is same race as owner" << pOwner->getName() << endl;
			return false;
		}

		if (GDRLairManager::Instance().isGDRLairZone(pMonster->getZoneID()) && pCreature->isPC() ) return false;
	}

	if (SiegeManager::Instance().isSiegeZone(pMonster->getZoneID()) )
	{
/*		if (pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_5 ) ) return true;
		if (pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_4 ) ) return true;
		if (pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_3 ) ) return true;
		if (pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_2 ) ) return true;
		if (pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_ATTACKER_1 ) ) return true;

		return false;*/

		if (pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_DEFENDER ) || pCreature->isFlag(Effect::EFFECT_CLASS_SIEGE_REINFORCE ) )
			return false;
	}

	// �����μ��� �����̾ �ƿ콺�ͽ��� ������ ���̴�.
	if (pCreature->isSlayer()) return true;

	if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

		if ((pOusters->getLevel() + 10) <= pMonster->getLevel() ) return true;
		if (pOusters->getLevel() > 10 ) return true;
	}
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

		// �������� ������ �����̾��� �������� 10���� �̻� ���� ����,
		// ������ �ν��Ѵ�.
		if ((pVampire->getLevel() + 10) <= pMonster->getLevel())
		{
			return true;
		}

		// 10���� �̻��� �����̾��� ���̴�.
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
// STL find_if �˰��������� �̿��ϱ� ���� ���� Ŭ����
//////////////////////////////////////////////////////////////////////////////
class isSameCreature
{
public:
	isSameCreature(Creature* pCreature) : m_Creature(pCreature) {}

	bool operator () (Creature* pCreature) throw()
	{
		return pCreature->getName() == m_Creature->getName();
	}

private :
	Creature* m_Creature;
};

list<Packet*> * getRelicEffectPacket(MonsterCorpse* pMonsterCorpse, Effect::EffectClass EClass, list<Packet*> * pPackets )
{
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect(EClass);

		//if (pEffect == NULL ) cout << (int)EClass << endl;

		Assert(pEffect!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(pEffect->getSendEffectClass());
		pPacket->setDuration(pEffect->getRemainDuration());

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	return pPackets;
}


//////////////////////////////////////////////////////////////////////////////
// sendRelicEffect(MonsterCorpse* )
//////////////////////////////////////////////////////////////////////////////
// pMonsterCorpse�� ���� Effect�� pPlayer���� ������.
//////////////////////////////////////////////////////////////////////////////
list<Packet*> *
createRelicEffect(MonsterCorpse* pMonsterCorpse )
{
	list<Packet*>* pPackets = NULL;

	if (pMonsterCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC))
	{
		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(Effect::EFFECT_CLASS_SLAYER_RELIC);
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	if (pMonsterCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC))
	{
		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	Effect::EffectClass EClass = Effect::EFFECT_CLASS_SHRINE_GUARD;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect(EClass);
		Assert(pEffect!=NULL);

		EffectShrineGuard* pEffectShrineGuard = dynamic_cast<EffectShrineGuard*>(pEffect);
		Assert(pEffectShrineGuard!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(EClass + pEffectShrineGuard->getShrineID());
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	EClass = Effect::EFFECT_CLASS_SHRINE_HOLY;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect(EClass);
		Assert(pEffect!=NULL);

		EffectShrineHoly* pEffectShrineHoly = dynamic_cast<EffectShrineHoly*>(pEffect);
		Assert(pEffectShrineHoly!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(EClass + pEffectShrineHoly->getShrineID());
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	EClass = Effect::EFFECT_CLASS_SHRINE_SHIELD;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect(EClass);
		Assert(pEffect!=NULL);

		EffectShrineShield* pEffectShrineShield = dynamic_cast<EffectShrineShield*>(pEffect);
		Assert(pEffectShrineShield!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(EClass);
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	EClass = Effect::EFFECT_CLASS_HAS_BLOOD_BIBLE;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect(EClass);
		Assert(pEffect!=NULL);

		EffectHasBloodBible* pEffectHasBloodBible = dynamic_cast<EffectHasBloodBible*>(pEffect);
		Assert(pEffectHasBloodBible!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(pEffectHasBloodBible->getSendEffectClass());
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	EClass = Effect::EFFECT_CLASS_HAS_CASTLE_SYMBOL;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect(EClass);
		Assert(pEffect!=NULL);

		EffectHasCastleSymbol* pEffectHasCastleSymbol = dynamic_cast<EffectHasCastleSymbol*>(pEffect);
		Assert(pEffectHasCastleSymbol!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(pEffectHasCastleSymbol->getSendEffectClass());
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	EClass = Effect::EFFECT_CLASS_FLAG_INSERT;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect(EClass);
		Assert(pEffect!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(pEffect->getSendEffectClass());
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	EClass = Effect::EFFECT_CLASS_KEEP_SWEEPER;
	if (pMonsterCorpse->isFlag(EClass))
	{
		Effect* pEffect = pMonsterCorpse->getEffectManager().findEffect(EClass);
		Assert(pEffect!=NULL);

		GCAddEffect* pPacket = new GCAddEffect;
		pPacket->setObjectID(pMonsterCorpse->getObjectID());
		pPacket->setEffectID(pEffect->getSendEffectClass());
		pPacket->setDuration(65000);

		if (pPackets==NULL) pPackets = new list<Packet*>;
		pPackets->push_back(pPacket);
	}

	pPackets = getRelicEffectPacket(pMonsterCorpse, Effect::EFFECT_CLASS_SLAYER_REGEN_ZONE, pPackets);
//	pPackets = getRelicEffectPacket(pMonsterCorpse, Effect::EFFECT_CLASS_VAMPIRE_REGEN_ZONE, pPackets);
//	pPackets = getRelicEffectPacket(pMonsterCorpse, Effect::EFFECT_CLASS_OUSTERS_REGEN_ZONE, pPackets);
//	pPackets = getRelicEffectPacket(pMonsterCorpse, Effect::EFFECT_CLASS_DEFAULT_REGEN_ZONE, pPackets);
	pPackets = getRelicEffectPacket(pMonsterCorpse, Effect::EFFECT_CLASS_SLAYER_TRYING_1, pPackets);
	pPackets = getRelicEffectPacket(pMonsterCorpse, Effect::EFFECT_CLASS_VAMPIRE_TRYING_1, pPackets);
	pPackets = getRelicEffectPacket(pMonsterCorpse, Effect::EFFECT_CLASS_OUSTERS_TRYING_1, pPackets);

	return pPackets;
}

//////////////////////////////////////////////////////////////////////////////
// sendRelicEffect(MonsterCorpse* )
//////////////////////////////////////////////////////////////////////////////
// pMonsterCorpse�� ���� Effect�� pPlayer���� ������.
//////////////////////////////////////////////////////////////////////////////
void
sendRelicEffect(MonsterCorpse* pMonsterCorpse, Player* pPlayer )
{
	list<Packet*>* pPackets = createRelicEffect(pMonsterCorpse);

	if (pPackets!=NULL)
	{
		list<Packet*>::iterator itr = pPackets->begin();
		for (; itr!=pPackets->end(); itr++)
		{
			Packet* pPacket = *itr;
			pPlayer->sendPacket(pPacket);

			SAFE_DELETE(pPacket);
		}
		SAFE_DELETE(pPackets);
	}
}

//////////////////////////////////////////////////////////////////////////////
// sendRelicEffect(MonsterCorpse* )
//////////////////////////////////////////////////////////////////////////////
// pMonsterCorpse�� ���� Effect�� (x,y)�� �Ѹ���.
//////////////////////////////////////////////////////////////////////////////
void
sendRelicEffect(MonsterCorpse* pMonsterCorpse, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y)
{
	list<Packet*>* pPackets = createRelicEffect(pMonsterCorpse);

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
	throw()
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

	getCurrentTime(m_LoadValueStartTime);

	m_LoadValue = 0;

	m_bTimeStop = false;

	getCurrentTime(m_UpdateTimebandTime);

	m_pDynamicZone = NULL;

}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Zone::Zone(ZoneID_t zoneID, ZoneCoord_t width, ZoneCoord_t height)
	throw()
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

	getCurrentTime(m_LoadValueStartTime);

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
	throw()
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
	throw(Error)
{
	__BEGIN_TRY

#ifdef __USE_ENCRYPTER__
	int serverID = g_pConfig->getPropertyInt("ServerID");

	if (!isDynamicZone() )
	{
		m_EncryptCode = EncryptCode(m_ZoneID, serverID);
	}
	else
	{
		m_EncryptCode = EncryptCode(m_pDynamicZone->getTemplateZoneID(), serverID);
	}

	m_EncryptCode = (uchar)(((m_ZoneID >> 8 ) ^ m_ZoneID ) ^ ((serverID + 1 ) << 4 ));
#endif

	load();

	m_pWeatherManager->init();

	DarkLightInfo* pDIInfo = NULL;

	switch (m_ZoneType)
	{
		case ZONE_NORMAL_FIELD:
			pDIInfo = g_pDarkLightInfoManager->getCurrentDarkLightInfo(this);
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
			pDIInfo = g_pDarkLightInfoManager->getCurrentDarkLightInfo(this);
			m_DarkLevel  = pDIInfo->getDarkLevel();
			m_LightLevel = pDIInfo->getLightLevel();
			break;
	}

	switch (m_ZoneID )
	{
		case 1131:
		case 1132:
		case 1133:
		case 1134:
			{
				m_pLevelWarManager = new LevelWarManager(m_ZoneID-1130, this);
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
// �� ���Ͽ��� �� ������ �о �ε��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void Zone::load(bool bOutput)
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG
try {

	DWORD  versionLen;
	WORD   zoneID;
	WORD   zoneGroupID;
	DWORD  zonenameLen;
	BYTE   zoneType;
	BYTE   zoneLevel;
	DWORD  descLen;
	char* pDesc = NULL;
	char* version = new char [128];
	char* zonename = new char [128];
	char* lwrFilename = new char[256];

	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(m_ZoneID);

	Assert(pZoneInfo!=NULL);

	setPayPlay(pZoneInfo->isPayPlay());
	setPremiumZone(pZoneInfo->isPremiumZone());
	setPKZone(pZoneInfo->isPKZone());
	setNoPortalZone(pZoneInfo->isNoPortalZone());
	setMasterLair(pZoneInfo->isMasterLair());
	setHolyLand(pZoneInfo->isHolyLand());

	// Holy Land �� ���� HolyLandManager �� �߰�
	if (isHolyLand())
		g_pHolyLandManager->addHolyLand(this);

	if (g_pCastleInfoManager->getCastleInfo(m_ZoneID)!=NULL)
		setCastle(true);
	else
		setCastle(false);

	//filelog("zoneInfo.txt", "[%d] %d %d", (int)m_ZoneID, (int)isPayPlay(), (int)isPremiumZone());

	// SMP ���� ������ ����.
	string SMPFilename = g_pConfig->getProperty("HomePath") + "/data/" + pZoneInfo->getSMPFilename();
	ifstream SMP(SMPFilename.c_str(), ios::in | ios::binary);
	if (!SMP) {
		strcpy(lwrFilename, SMPFilename.c_str());
		strlwr(lwrFilename);
		SMP.open(lwrFilename, ios::in | ios::binary);

		if (!SMP) {
			StringStream msg;
			msg << SMPFilename << " not exist or cannot open it";
			cerr << msg.toString() << endl;
			throw FileNotExistException(msg.toString());
		}
	}

    // read zone version
	SMP.read((char*)&versionLen,szDWORD);
	SMP.read((char*)version,versionLen);
	version[versionLen] = 0;

	// read zone id
	SMP.read((char*)&zoneID,szWORD);

	// read zone group id (no use)
	SMP.read((char*)&zoneGroupID,szWORD);

	// read zone name
	SMP.read((char*)&zonenameLen,szDWORD);
	if (zonenameLen > 0) {
		SMP.read((char*)zonename,zonenameLen);
		zonename[zonenameLen] = 0;
	}

    // read zone type & level
	SMP.read((char*)&zoneType,szBYTE);
	SMP.read((char*)&zoneLevel,szBYTE);

	// read zone description
	SMP.read((char*)&descLen,szDWORD);
	if (descLen > 0) {
		pDesc = new char[descLen+1];
		SMP.read((char*)pDesc,descLen);
		pDesc[descLen] = 0;

		SAFE_DELETE_ARRAY(pDesc);	// add '_ARRAY' moved to here.. by sigi 2002.5.2
	}

	// read zone width & height
	SMP.read((char*)&m_Width, szWORD);
	SMP.read((char*)&m_Height ,szWORD);

	Assert(m_Width <= maxZoneWidth);
	Assert(m_Height <= maxZoneHeight);

	// Ÿ���� 2�����迭�� ������ �޸������߽ �Ҵ��Ѵ�.
	m_pTiles = new Tile* [ m_Width ];
	for (uint i = 0 ; i < m_Width ; i++)
		m_pTiles[i] = new Tile [m_Height];

	// ���͸� 2���� �迭�� ������ �޸������߽ �Ҵ��Ѵ�.
	m_SectorWidth = (int)ceil((float)m_Width/(float)SECTOR_SIZE);
	m_SectorHeight = (int)ceil((float)m_Height/(float)SECTOR_SIZE);
	m_pSectors = new Sector*[m_SectorWidth];
	for (int x=0; x<m_SectorWidth; x++)
		m_pSectors[x] = new Sector[m_SectorHeight];

	// ������ Ÿ�Ͽ��ٰ� ���� �����͸� �����Ѵ�.
	for (int x=0; x<m_Width; x++) {
		for (int y=0; y<m_Height; y++) {
			int sx = x/SECTOR_SIZE;
			int sy = y/SECTOR_SIZE;

			Assert(sx < m_SectorWidth && sy < m_SectorHeight);

			m_pTiles[x][y].setSector(&m_pSectors[sx][sy]);
		}
	}

	// ���ͳ��� ������ �Ѵ�.
	VSRect srect(0, 0, m_SectorWidth-1, m_SectorHeight-1);
	for (int x=0; x<m_SectorWidth; x++) {
		for (int y=0; y<m_SectorHeight; y++) {
			for (uint d=0; d<9; d++) {
				int sectorx = x + dirMoveMask[d].x;
				int sectory = y + dirMoveMask[d].y;

				if (srect.ptInRect(sectorx, sectory))
					m_pSectors[x][y].setNearbySector(d, &m_pSectors[sectorx][sectory]);
			}
		}
	}

	// MonsterAI�� ���� ���� ������ ������������ �簢���� �����Ѵ�.
	m_OuterRect.set(0, 0, m_Width-1, m_Height-1);
	if (m_Width > 64 && m_Height > 64) {
		m_InnerRect.set(15, 15, m_Width-15, m_Height-15);
		m_CoreRect.set(25, 25, m_Width-25, m_Height-25);
	}
	else
		m_InnerRect = m_CoreRect = m_OuterRect;

	char str[80];
	char str2[80];

	for (ZoneCoord_t y=0; y<m_Height; y++) {
		for (ZoneCoord_t x=0; x<m_Width; x++) {
			BYTE flag = 0;
			SMP.read((char*)&flag, szBYTE);

			// �������� ����, ����, ���� ����
			if (flag & 0x01) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_BURROWING);
			if (flag & 0x02) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_WALKING);
			if (flag & 0x04) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_FLYING);

			// �ƹ��͵� ���� ����..
			// �� ������ ���� ��ǥ������ �������д�.
			if (flag==0 && m_InnerRect.ptInRect(x, y ))
				m_MonsterRegenPositions.push_back(BPOINT((BYTE)x, (BYTE)y ));

			// ������ ������ ����: block�� �ϳ����� �� �� ���� ã�´�.
			if ((flag & 0x07)!=0x07 && (isMasterLair() || m_ZoneID == 3002))
				m_EmptyTilePositions.push_back(BPOINT((BYTE)x, (BYTE)y ));

			// ��Ż ����
			if (flag & 0x80) {
				BYTE type;
				ZoneID_t targetZoneID;
				BYTE targetX, targetY;
				SMP.read((char*)&type, szBYTE);

				PortalType_t portalType = PORTAL_NORMAL;

				bool bAddPortal = true;

				if (type == PORTAL_NORMAL) {
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_NORMAL);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);
				} else if (type == PORTAL_SLAYER) {
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_SLAYER);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_SLAYER;
				} else if (type == PORTAL_VAMPIRE) {
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_VAMPIRE);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_VAMPIRE;
				} else if (type == PORTAL_MULTI_TARGET) {
					BYTE size;
					SMP.read((char*)&size, szBYTE);

					// ��Ż�� ������ �ش�.
					MultiPortal* pMultiPortal = new MultiPortal();

					for(int i = 0; i < size; i++) {
						SMP.read((char*)&targetZoneID, szZoneID);
						SMP.read((char*)&targetX,      szBYTE);
						SMP.read((char*)&targetY,      szBYTE);

						pMultiPortal->setObjectType(PORTAL_SLAYER);

						// Ÿ�� ������ �����Ѵ�.
						PortalTargetInfo* pPortalTargetInfo = new PortalTargetInfo();
						pPortalTargetInfo->setZoneID(targetZoneID);
						pPortalTargetInfo->setX(targetX);
						pPortalTargetInfo->setY(targetY);
						pMultiPortal->setPortalTargetInfo(pPortalTargetInfo);
					}

					getObjectRegistry().registerObject(pMultiPortal);
					m_pTiles[x][y].addPortal(pMultiPortal);

					portalType = PORTAL_SLAYER;
				} else if (type == PORTAL_GUILD) {
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					GuildPortal* pGuildPortal = new GuildPortal();
					pGuildPortal->setObjectType(PORTAL_GUILD);
					pGuildPortal->setZoneID(targetZoneID);
					pGuildPortal->setX(targetX);
					pGuildPortal->setY(targetY);

					getObjectRegistry().registerObject(pGuildPortal);
					m_pTiles[x][y].addPortal(pGuildPortal);
				} else if (type == PORTAL_BATTLE) {
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_NORMAL);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);
				} else if (type == PORTAL_OUSTERS) {
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_OUSTERS);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_OUSTERS;
				}
				else
					bAddPortal = false;

				// ��Ż�� �߰��� ���쿡
				// ������ ���� �������̶���
				// TriggeredPortal�� �����ؾ� �Ѵ�.
				if (bAddPortal) {
					ZoneInfo* pTargetZoneInfo = NULL;
					try {
						pTargetZoneInfo = g_pZoneInfoManager->getZoneInfo(targetZoneID);
					} catch (NoSuchElementException& t) {
						throw Error("�׷� ���� ���ٳ�");
					}

					Assert(pTargetZoneInfo!=NULL);

					// ������ Portal�� ������?
					bool bDeleteOldPortal = false;

					if ((pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay())
						|| pTargetZoneInfo->isMasterLair()
						|| (pTargetZoneInfo->isCastle() && !g_pCastleInfoManager->isCastleZone(targetZoneID, m_ZoneID))
						|| (pTargetZoneInfo->isHolyLand() && !pZoneInfo->isHolyLand())
						|| (isCastle() && g_pCastleInfoManager->isCastleZone(m_ZoneID, pTargetZoneInfo->getZoneID()))) {
						bDeleteOldPortal = true;
					}

					Tile& rTile = m_pTiles[x][y];

					// ������ Portal�� ������ ����
					if (bDeleteOldPortal) {
						// ������ �ִ� portal�� �����Ѵ�.
						if (rTile.hasPortal()) {
							Portal* pOldPortal = rTile.getPortal();
							rTile.deletePortal();

							delete pOldPortal;
						}
					}

					// ��Ż�� �����ϰ�, �����Ѵ�.

					//----------------------------------------
					// ������ ������ ����
					// by sigi. 2002.9.2
					//----------------------------------------
					if (pTargetZoneInfo->isMasterLair()) {
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// ��Ż ������ �ε��Ѵ�.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID(0);	// �ǹ̾���.

						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterMasterLair\n\t TargetZoneID : %d\n\t", (int)pTargetZoneInfo->getZoneID());
						pTrigger->setConditions(str);
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str(STRID_CANNOT_ENTER ));
                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER);

                        pTrigger->setCounterActions(str2);

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : ������ ��� �� �����ϴ�.");

						tm.addTrigger(pTrigger);

						// Ÿ�Ͽ��� ��Ż�� ���δ�.
						rTile.addPortal(pPortal);
					}
					//----------------------------------------
					// �ƴ��� ������ ������� �� ��
					//----------------------------------------
					else if (pTargetZoneInfo->isHolyLand() && !pZoneInfo->isHolyLand()) {
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// ��Ż ������ �ε��Ѵ�.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID(0);	// �ǹ̾���.

						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterHolyLand\n\t TargetZoneID : %d\n\t", (int)pTargetZoneInfo->getZoneID());
						pTrigger->setConditions(str);
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str(STRID_CANNOT_ENTER_DURING_RACE_WAR ));
                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER_DURING_RACE_WAR);

                        pTrigger->setCounterActions(str2);

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : �������� �߿��� ��û�� ���� �ʾ����� ��� �� �����ϴ�.");

						tm.addTrigger(pTrigger);

						// Ÿ�Ͽ��� ��Ż�� ���δ�.
						rTile.addPortal(pPortal);

					}
					//----------------------------------------
					// �� �ۿ��� �� ������ ����� ����
					// isCastleZone �� �� �ȿ� ���ԵǴ� �������� üũ�Ѵ�.
					// (�� ������ �� ���̴�)
					// by bezz, Sequoia 2003. 1.20.
					//----------------------------------------
					else if (pTargetZoneInfo->isCastle() && !g_pCastleInfoManager->isCastleZone(targetZoneID, m_ZoneID)) {
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// ��Ż ������ �ε��Ѵ�.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID(0);	// �ǹ̾���.

						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterCastle\n\t TargetZoneID : %d\n\t", (int)pTargetZoneInfo->getZoneID());
						pTrigger->setConditions(str);
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str(STRID_CANNOT_ENTER ));
                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER);

                        pTrigger->setCounterActions(str2);

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : ����� �� �����ϴ�.");

						tm.addTrigger(pTrigger);

						// Ÿ�Ͽ��� ��Ż�� ���δ�.
						rTile.addPortal(pPortal);
					}
					//----------------------------------------
					// �� ���� �������� ����� �Ա�
					// by Sequoia
					//----------------------------------------
					else if (isCastle() && g_pCastleInfoManager->isCastleZone(m_ZoneID, pTargetZoneInfo->getZoneID())) {
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// ��Ż ������ �ε��Ѵ�.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID(0);	// �ǹ̾���.
						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterCastleDungeon\n\t CastleZoneID : %d\n\t", m_ZoneID);
						pTrigger->setConditions(str);
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str(STRID_CANNOT_ENTER_NOT_OWNER_GUILD ));
                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER_NOT_OWNER_GUILD);

                        pTrigger->setCounterActions(str2);

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : �� ������ �������� �ƴϸ� ����� �� �����ϴ�.");

						tm.addTrigger(pTrigger);
						rTile.addPortal(pPortal);
					}
					//----------------------------------------
					// ���� ���� ����
					//----------------------------------------
					else if (pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay()) {
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// ��Ż ������ �ε��Ѵ�.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID(0);	// �ǹ̾���.

						pTrigger->setTriggerType("QUEST");
						pTrigger->setConditions("ConditionType : CanEnterPayZone\n\t");
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

						// by sigi. 2002.10.30
						if (g_pConfig->getPropertyInt("IsNetMarble")==0) {
//                            sprintf(str2, "ActionType : SystemMessage\n\t Content : %s",
//                                            g_pStringPool->c_str(STRID_CANNOT_ENTER_PAY_ZONE ));
                            sprintf(str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER_PAY_ZONE);

                            pTrigger->setCounterActions(str2);

//							pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : �������̶��� ��� �� �����ϴ�.");
						} else {
//                            sprintf(str2, "ActionType : SystemMessage\n\t Content : %s",
 //                                           g_pStringPool->c_str(STRID_CANNOT_ENTER ));
                            sprintf(str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER);

                            pTrigger->setCounterActions(str2);

//							pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : ������ �� �� �����ϴ�.");
						}

						tm.addTrigger(pTrigger);

						// Ÿ�Ͽ��� ��Ż�� ���δ�.
						rTile.addPortal(pPortal);
					}
				}
			} //if (flag & 0x80)
		} // for
	} // for

	SMP.close();

	///*
	if (m_MonsterRegenPositions.size()==0) {
		cout << "MonsterRegenPosition not exist: Width = " << m_Width << ", Height = " << m_Height << endl;

		//Assert(m_MonsterRegenPositions.size()!=0);

		ZoneCoord_t outerMinX = m_Width/7;
		ZoneCoord_t outerMinY = m_Height/7;
		ZoneCoord_t outerMaxX = m_Width-outerMinX;
		ZoneCoord_t outerMaxY = m_Width-outerMinY;

		for (ZoneCoord_t y=outerMinY; y<outerMaxY; y++) {
			for (ZoneCoord_t x=outerMinX; x<outerMaxX; x++) {
				Tile& rTile = m_pTiles[x][y];

				if (!rTile.hasPortal() && !rTile.isGroundBlocked() && !rTile.isAirBlocked() && !rTile.isUndergroundBlocked())
					m_MonsterRegenPositions.push_back(BPOINT((BYTE)x, (BYTE)y ));
			}
		}

		Assert(m_MonsterRegenPositions.size()!=0);
	}

	if ((isMasterLair() || m_ZoneID == 3002) && m_EmptyTilePositions.size()==0) {
		cout << "MasterLair has No EmptyTilePosition" << endl;
		Assert(m_EmptyTilePositions.size()!=0);
	}
	//*/

	// Zone ������ �����Ѵ�.
	m_ZoneType  = pZoneInfo->getZoneType();
	m_ZoneLevel = pZoneInfo->getZoneLevel();

	// �޸��� �Ҵ����ְ�...
	m_ppLevel = new ZoneLevel_t*[ m_Width ];
	for (uint i = 0; i < m_Width; i++)
		m_ppLevel[i] = new ZoneLevel_t[m_Height];

	// �� ������ ����Ʈ ������ �ʱ�ȭ��Ų��.
	for (ZoneCoord_t x = 0; x < m_Width; x++)
		for (ZoneCoord_t y = 0; y < m_Height; y++)
			m_ppLevel[x][y] = m_ZoneLevel;

	// SSI ���� ������ ����.
	string SSIFilename = g_pConfig->getProperty("HomePath") + "/data/" + pZoneInfo->getSSIFilename();
	ifstream SSI(SSIFilename.c_str(), ios::in | ios::binary);
	if (!SSI) {
		strcpy(lwrFilename, SSIFilename.c_str());
		strlwr(lwrFilename);
		SSI.open(lwrFilename, ios::in | ios::binary);

		//cout << "second chk : " << lwrFilename.c_str() << endl;

		if (!SSI) {
			StringStream msg;
			msg << SSIFilename << " not exist or cannot open it";
			throw FileNotExistException(msg.toString());
		}
	}

	int size = 0;
	SSI.read((char*)&size, szint);

	BYTE left, top, right, bottom, level;
	for (int i=0; i<size; i++) {
		SSI.read((char*)&level, szBYTE);
		SSI.read((char*)&left, szBYTE);
		SSI.read((char*)&top, szBYTE);
		SSI.read((char*)&right, szBYTE);
		SSI.read((char*)&bottom, szBYTE);

		Assert(left <= right);
		Assert(top  <= bottom);

		for (int bx=left; bx<=right; bx++)
			for (int by=top; by<=bottom; by++)
				m_ppLevel[bx][by] = level;
	}

	SSI.close();

	// Ʈ���ŵ� ��Ż�� �ε��Ѵ�.
	loadTriggeredPortal();

	// ������ �ε��ϰ�....
	m_pMonsterManager->load();


//#ifdef __XMAS_EVENT_CODE__
//	printf("Begin Event Monster Loading\n");
//	m_pEventMonsterManager->load();
//	printf("Event Monster Loading Completed\n");
//#endif

	// ������ ������ ����
	// by sigi. 2002.9.2
	if (pZoneInfo->isMasterLair()) {
		SAFE_DELETE(m_pMasterLairManager);
		m_pMasterLairManager = new MasterLairManager(this);
	}

	// ���� ����
	// by sigi. 2003.1.24
	if (isCastle()) {
		SAFE_DELETE(m_pWarScheduler);
		m_pWarScheduler = new WarScheduler(this);
		m_pWarScheduler->load();

		//cout << "[" << getZoneID() << "]" << " Castle : WarScheduler->load" << endl;
	}

	// ������ �ε��Ѵ�.
	loadItem();

//	if (isCastle())
//	{
//		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo(m_ZoneID);
//		m_pNPCManager->load(m_ZoneID, pCastleInfo->getRace());
//	}
//	else
//	{
	// NPC �� �ε��Ѵ�.
	m_pNPCManager->load(m_ZoneID);
//	}

	loadEffect();

	// �Խ����� �ε��Ѵ�.
	loadBulletinBoard(this);

	// ��������Ʈ ������ �ʱ�ȭ�Ѵ�.
	initSpriteCount();

	SAFE_DELETE(version);
	SAFE_DELETE(zonename);
	SAFE_DELETE(lwrFilename);

/*	if (m_ZoneID == 1410 )
	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap(Effect::EFFECT_CLASS_ICICLE_DROP, this);
		registerObject(pEffect);

		pEffect->setStartXY(116, 66);
		pEffect->setLength(48);
		pEffect->setTick(5);
		pEffect->setUnit(5);
		pEffect->setDir(7);

		pEffect->setNextTime(0);
		pEffect->setDeadline(600);
		addEffect(pEffect);
	}*/

} catch (Throwable& t )
{ cout << t.toString() << endl; Assert(false);}


	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �� ���Ͽ��� �� ������ �о �ε��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void Zone::reload(bool bOutput)
	throw(Error)
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

	setPayPlay(pZoneInfo->isPayPlay());
	setPremiumZone(pZoneInfo->isPremiumZone());
	setPKZone(pZoneInfo->isPKZone());
	setNoPortalZone(pZoneInfo->isNoPortalZone());
	setMasterLair(pZoneInfo->isMasterLair());

	//filelog("zoneInfo.txt", "[%d] %d %d", (int)m_ZoneID, (int)isPayPlay(), (int)isPremiumZone());

	// SMP ���� ������ ����.
	string SMPFilename = g_pConfig->getProperty("HomePath") + "/data/" + pZoneInfo->getSMPFilename();
	ifstream SMP(SMPFilename.c_str(), ios::in | ios::binary);
	if (!SMP)
	{
		strcpy(lwrFilename, SMPFilename.c_str());
		strlwr(lwrFilename);
		SMP.open(lwrFilename, ios::in | ios::binary);

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
		// ���͸� 2���� �迭�� ������ �޸������߽ �Ҵ��Ѵ�.
		m_SectorWidth = (int)ceil((float)m_Width/(float)SECTOR_SIZE);
		m_SectorHeight = (int)ceil((float)m_Height/(float)SECTOR_SIZE);
		m_pSectors = new Sector*[m_SectorWidth];
		for (x=0; (int)x<m_SectorWidth; x++)
		{
			m_pSectors[x] = new Sector[m_SectorHeight];
		}

		// ���ͳ��� ������ �Ѵ�.
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

	// m_pTiles �� �̹� ���ٸ�...
	if (m_pTiles==NULL)
	{
		// Ÿ���� 2�����迭�� ������ �޸������߽ �Ҵ��Ѵ�.
		m_pTiles = new Tile* [ m_Width ];
		for (i = 0 ; i < m_Width ; i++)
		{
			m_pTiles[i] = new Tile [m_Height];
		}

		// ������ Ÿ�Ͽ��ٰ� ���� �����͸� �����Ѵ�.
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

	// MonsterAI�� ���� ���� ������ ������������ �簢���� �����Ѵ�.
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

	// �ٽ�~
	m_MonsterRegenPositions.clear();
	m_EmptyTilePositions.clear();

	for (ZoneCoord_t y=0; y<m_Height; y++)
	{
		for (ZoneCoord_t x=0; x<m_Width; x++)
		{
			BYTE flag = 0;
			SMP.read((char*)&flag, szBYTE);

			// �������� ����, ����, ���� ����
			if (flag & 0x01) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_BURROWING);
			if (flag & 0x02) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_WALKING);
			if (flag & 0x04) m_pTiles[x][y].setBlocked(Creature::MOVE_MODE_FLYING);

			// �ƹ��͵� ���� ����..
			// �� ������ ���� ��ǥ������ �������д�.
			if (flag==0 && m_InnerRect.ptInRect(x, y ))
			{
				m_MonsterRegenPositions.push_back(BPOINT((BYTE)x, (BYTE)y ));
			}

			// ������ ������ ����: block�� �ϳ����� �� �� ���� ã�´�.
			if ((flag & 0x07)!=0x07 && (isMasterLair() || m_ZoneID == 3002) )
			{
				m_EmptyTilePositions.push_back(BPOINT((BYTE)x, (BYTE)y ));
			}

			// ��Ż ����
			if (flag & 0x80)
			{
				BYTE	type;
				ZoneID_t targetZoneID;
				BYTE     targetX, targetY;
				SMP.read((char*)&type, szBYTE);

				PortalType_t portalType = PORTAL_NORMAL;

				bool bAddPortal = true;

				// �̹� ��Ż�� �ִٸ� ������ ��Ż�� �����ش�.
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

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_NORMAL);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);
/*
					if (bOutput)
					{
						cout << "Normal(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
*/
				}
				else if (type == PORTAL_SLAYER)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_SLAYER);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_SLAYER;
/*
					if (bOutput)
					{
						cout << "Slayer(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
*/
				}
				else if (type == PORTAL_VAMPIRE)
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_VAMPIRE);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);

					portalType = PORTAL_VAMPIRE;
/*
					if (bOutput)
					{
						cout << "Vampire(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
*/
				}
				else if (type == PORTAL_MULTI_TARGET)
				{
					BYTE size;
					SMP.read((char*)&size, szBYTE);

					// ��Ż�� ������ �ش�.
					MultiPortal* pMultiPortal = new MultiPortal();

					for(int i = 0; i < size; i++)
					{
						SMP.read((char*)&targetZoneID, szZoneID);
						SMP.read((char*)&targetX,      szBYTE);
						SMP.read((char*)&targetY,      szBYTE);

						pMultiPortal->setObjectType(PORTAL_SLAYER);

						// Ÿ�� ������ �����Ѵ�.
						PortalTargetInfo* pPortalTargetInfo = new PortalTargetInfo();
						pPortalTargetInfo->setZoneID(targetZoneID);
						pPortalTargetInfo->setX(targetX);
						pPortalTargetInfo->setY(targetY);
						pMultiPortal->setPortalTargetInfo(pPortalTargetInfo);
					}

					getObjectRegistry().registerObject(pMultiPortal);
					m_pTiles[x][y].addPortal(pMultiPortal);

					portalType = PORTAL_SLAYER;
/*
					if (bOutput)
					{
						cout << "Multi(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
*/
				}
				else if (type == PORTAL_GUILD )
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					GuildPortal* pGuildPortal = new GuildPortal();
					pGuildPortal->setObjectType(PORTAL_GUILD);
					pGuildPortal->setZoneID(targetZoneID);
					pGuildPortal->setX(targetX);
					pGuildPortal->setY(targetY);

					getObjectRegistry().registerObject(pGuildPortal);
					m_pTiles[x][y].addPortal(pGuildPortal);
/*
					if (bOutput)
					{
						cout << "Guild(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
*/
				}
				else if (type == PORTAL_BATTLE )
				{
					SMP.read((char*)&targetZoneID, szZoneID);
					SMP.read((char*)&targetX,      szBYTE);
					SMP.read((char*)&targetY,      szBYTE);

					// ��Ż�� ������ �ش�.
					NormalPortal* pNormalPortal = new NormalPortal();
					pNormalPortal->setObjectType(PORTAL_NORMAL);
					pNormalPortal->setZoneID(targetZoneID);
					pNormalPortal->setX(targetX);
					pNormalPortal->setY(targetY);

					getObjectRegistry().registerObject(pNormalPortal);
					m_pTiles[x][y].addPortal(pNormalPortal);
/*
					if (bOutput)
					{
						cout << "Slayer(" << (int)x << "," << (int)y << "," << (int)targetZoneID << "," << (int)targetX << "," << (int)targetY << ")" << endl;
					}
*/
				}
				else
				{
					bAddPortal = false;
				}

				// ��Ż�� �߰��� ���쿡
				// ������ ���� �������̶���
				// TriggeredPortal�� �����ؾ� �Ѵ�.
				if (bAddPortal)
				{
					ZoneInfo* pTargetZoneInfo = NULL;
					try {
						pTargetZoneInfo = g_pZoneInfoManager->getZoneInfo(targetZoneID);
					} catch (NoSuchElementException& t) {
						throw Error("�׷� ���� ���ٳ�");
					}

					Assert(pTargetZoneInfo!=NULL);

					// ������ Portal�� ������?
					bool bDeleteOldPortal = false;

					if ((pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay() )
						|| pTargetZoneInfo->isMasterLair()
						|| (pTargetZoneInfo->isCastle() && !g_pCastleInfoManager->isCastleZone(targetZoneID, m_ZoneID))
						|| (pTargetZoneInfo->isHolyLand() && !pZoneInfo->isHolyLand() )
						|| (isCastle() && g_pCastleInfoManager->isCastleZone(m_ZoneID, pTargetZoneInfo->getZoneID() ) )
					   )
					{
						bDeleteOldPortal = true;
					}

/*					if ((pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay() )
						|| pTargetZoneInfo->isMasterLair())
					{
						bDeleteOldPortal = true;
					}*/

					Tile& rTile = m_pTiles[x][y];

					// ������ Portal�� ������ ����
					if (bDeleteOldPortal)
					{
						// ������ �ִ� portal�� �����Ѵ�.
						if (rTile.hasPortal())
						{
							Portal* pOldPortal = rTile.getPortal();
							rTile.deletePortal();

							delete pOldPortal;
						}
					}

					// ��Ż�� �����ϰ�, �����Ѵ�.

					//----------------------------------------
					// ������ ������ ����
					// by sigi. 2002.9.2
					//----------------------------------------
					if (pTargetZoneInfo->isMasterLair())
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// ��Ż ������ �ε��Ѵ�.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID(0);	// �ǹ̾���.

						pTrigger->setTriggerType("QUEST");

						sprintf(str, "ConditionType : EnterMasterLair\n\t TargetZoneID : %d\n\t", (int)pTargetZoneInfo->getZoneID());
						pTrigger->setConditions(str);
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %s",
 //                                       g_pStringPool->c_str(STRID_CANNOT_ENTER ));
                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER);
                        pTrigger->setCounterActions(str2);

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : ������ ��� �� �����ϴ�.");

						tm.addTrigger(pTrigger);

						// Ÿ�Ͽ��� ��Ż�� ���δ�.
						rTile.addPortal(pPortal);

						//cout << "[" << (int)pTargetZoneInfo->getZoneID() << "] is MasterLair"
						//	 << endl;
					}
					//----------------------------------------
					// ���������� ����� ����
					//----------------------------------------
					else if (pTargetZoneInfo->isPayPlay() && !pZoneInfo->isPayPlay())
					{
						TriggeredPortal* pPortal = new TriggeredPortal();
						getObjectRegistry().registerObject(pPortal);

						// ��Ż ������ �ε��Ѵ�.
						pPortal->setObjectType(portalType);

						//pPortal->load(m_ZoneID, left, top, right, bottom);
						TriggerManager& tm = pPortal->getTriggerManager();

						Trigger* pTrigger = new Trigger();

						pTrigger->setTriggerID(0);	// �ǹ̾���.

						pTrigger->setTriggerType("QUEST");
						pTrigger->setConditions("ConditionType : PayPlay\n\t");
						sprintf(str, "ActionType : ActivatePortal\n\t ZoneID : %d\n\t X : %d\n\t Y : %d\n\t", targetZoneID, targetX, targetY);
						pTrigger->setActions(str);

//                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %s",
//                                        g_pStringPool->c_str(STRID_CANNOT_ENTER_PAY_ZONE ));
                        sprintf(str2, "ActionType : SystemMessage\n\t Content : %d", STRID_CANNOT_ENTER_PAY_ZONE);
                        pTrigger->setCounterActions(str2);

//						pTrigger->setCounterActions("ActionType : SystemMessage\n\t Content : �������̶��� ��� �� �����ϴ�.");

						tm.addTrigger(pTrigger);

						// Ÿ�Ͽ��� ��Ż�� ���δ�.
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
		cout << "MonsterRegenPosition not exist" << endl << "Width = " << m_Width << endl << "Height = " << m_Height << endl;

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
					m_MonsterRegenPositions.push_back(BPOINT((BYTE)x, (BYTE)y ));
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

	// Zone ������ �����Ѵ�.
	m_ZoneType  = pZoneInfo->getZoneType();
	m_ZoneLevel = pZoneInfo->getZoneLevel();

	// m_ppLevel ����
	for (i = 0; i < m_Width; i++)
	{
		SAFE_DELETE_ARRAY(m_ppLevel[i]);
	}
	SAFE_DELETE_ARRAY(m_ppLevel);

	// �޸��� �Ҵ����ְ�...
	m_ppLevel = new ZoneLevel_t*[ m_Width ];
	for (uint i = 0; i < m_Width; i++)
		m_ppLevel[i] = new ZoneLevel_t[m_Height];

	// �� ������ ����Ʈ ������ �ʱ�ȭ��Ų��.
	for (ZoneCoord_t x = 0; x < m_Width; x++)
		for (ZoneCoord_t y = 0; y < m_Height; y++)
			m_ppLevel[x][y] = m_ZoneLevel;

	// SSI ���� ������ ����.
	string SSIFilename = g_pConfig->getProperty("HomePath") + "/data/" + pZoneInfo->getSSIFilename();
	ifstream SSI(SSIFilename.c_str(), ios::in | ios::binary);
	if (!SSI)
	{
		strcpy(lwrFilename, SSIFilename.c_str());
		strlwr(lwrFilename);
		SSI.open(lwrFilename, ios::in | ios::binary);

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
/*
		if (bOutput)
		{
			cout << "LEVEL:" << (int)level << ",(" << (int)left << "," << (int)top << "," << (int)right << "," << (int)bottom << ")" << endl;
		}
*/
		Assert(left <= right);
		Assert(top  <= bottom);

		for (int bx=left; bx<=right; bx++)
			for (int by=top; by<=bottom; by++)
				m_ppLevel[bx][by] = level;
	}

	SSI.close();

	// Ʈ���ŵ� ��Ż�� �ε��Ѵ�.
	// reload������ ����
	//loadTriggeredPortal();

	// ������ �ε��ϰ�....
	m_pMonsterManager->load();

// eventMonsterManager�� reload������ �����Ѵ�.
//#ifdef __XMAS_EVENT_CODE__
//	cout << "Begin Event Monster Loading..." << endl;
//	m_pEventMonsterManager->load();
//	cout << "Event Monster Loading Completed..." << endl;
//#endif

	// ������ ������ ����
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

	// ���� ����
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

	// reload�� ���� �����Ѵ�.
	// ������ �ε��Ѵ�.
	//loadItem();
	// NPC �� �ε��Ѵ�.
	//m_pNPCManager->load(m_ZoneID);

	// ��������Ʈ ������ �ʱ�ȭ�Ѵ�.
	initSpriteCount();
} catch (Throwable& t )
{ cout << t.toString() << endl; Assert(false);}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// load items from database
// * NOTE *
// ���� �ٴڿ� ������ �������� ������ �����۵Ǿ �ε����� �ʴ´�.
//////////////////////////////////////////////////////////////////////////////
void Zone::loadItem ()
	throw(Error)
{
	__BEGIN_TRY

	/*
	// ������ �ε�...........
	g_pItemLoaderManager->load(this);

	// �������� �� ������������...�׷���...
	// ������ ������Ʈ ���̵��� �� �Ҵ� �ް� �ٽ� �����Ѵ�.
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
// ���� ���� Ʈ���ŵ� ��Ż�� �ε��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void Zone::loadTriggeredPortal ()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		// DynamicZone �� ���� ó��
		ZoneID_t zoneID = m_ZoneID;
		if (isDynamicZone() )
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
						//cerr << "loadTriggeredPortal : �̹� ��Ż�� �����մϴ�." << endl;
						//cerr << "ZONEID:" << m_ZoneID << ",X:" << x << "Y:" << y << endl;
						//Portal* pPortal = getTile(x,y).getPortal();
						//SAFE_DELETE(pPortal);
						getTile(x,y).deletePortal();
					}

					// ��Ż�� �����ϰ�, �����Ѵ�.
					TriggeredPortal* pPortal = new TriggeredPortal();
					getObjectRegistry().registerObject(pPortal);

					// ��Ż ������ �ε��Ѵ�.
					pPortal->setObjectType(PORTAL_NORMAL);
					pPortal->load(zoneID, left, top, right, bottom);

					// Ÿ�Ͽ��� ��Ż�� ���δ�.
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
// �� ������ ��Ÿ���� NPC�� �������� ��������Ʈ������ �����صд�.
//////////////////////////////////////////////////////////////////////////////
void Zone::initSpriteCount ()
	throw(Error)
{
	__BEGIN_TRY

	m_NPCCount = 0;
	m_MonsterCount = 0;

	// NPC ��������Ʈ Ÿ���� ������ �����Ѵ�.
	const map<ObjectID_t, Creature*>& NPCMap = m_pNPCManager->getCreatures();
	for (map<ObjectID_t, Creature*>::const_iterator i = NPCMap.begin(); i != NPCMap.end(); i++)
	{
		NPC* pNPC = dynamic_cast<NPC*>(i->second);
		bool bAdd = true;

		for (int j=0; j<m_NPCCount; j++) // ���� �ִ� ������ Ÿ�� �߿���
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

	// ������ ��������Ʈ Ÿ���� ������ �����Ѵ�.
	const map<SpriteType_t, MonsterCounter*>& MONSTER = m_pMonsterManager->getMonsters();
	for (map<SpriteType_t, MonsterCounter*>::const_iterator i = MONSTER.begin(); i != MONSTER.end(); i++)
	{
		Assert (m_MonsterCount < maxMonsterPerZone);	// by sigi

		m_MonsterTypes[m_MonsterCount] = i->first;
		m_MonsterCount++;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// Ÿ�Ͽ� ������ �� ������ �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
ZoneLevel_t Zone::getZoneLevel(ZoneCoord_t x, ZoneCoord_t y) const
	throw(OutOfBoundException)
{
	__BEGIN_TRY

	//Assert(x < m_Width && y < m_Height);

	// assert ����.
	// �� ���� �Ѱ踦 �Ѿ assert���� �׾���.
	// �̷��� ���� ������ ���� ��..
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
    throw(OutOfBoundException)
{
	__BEGIN_TRY

	Assert(x < m_Width && y < m_Height);
	return m_pTiles[x][y];

	__END_CATCH
}

Tile & Zone::getTile(ZoneCoord_t x, ZoneCoord_t y)
    throw(OutOfBoundException)
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
    throw(OutOfBoundException)
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
// �⺻������ Zone �� ó���� mutex �� �������� �ʴ´�.
// �ֳ��ϸ�, ZoneGroupThread�� ���� ó���� �ޱ� �����̴�. �׷���, ���� ����
// PC�� �߰��ϴ� ���� IPM���� �̷������� �ǹǷ�, �̷� ������ mutex ������
// �߰��ؾ� �ϸ�, �Ʒ� �޼ҵ忡 locking �� �ɾ����� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void Zone::pushPC(Creature* pCreature)
	throw(Error)
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
// P(cx,cy)�� �ִ� PC�� dir �������� �̵����� Q(nx,ny)�� �ű���.
// �׸���������, �ֺ��� PC�鿡�� �̵� ������ ���ε�ĳ��Ʈ�Ѵ�.
//
// *CAUTION*
// PC�� �ƴ� ũ��ó(NPC,Monster)�� �̵��� moveCreature�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void Zone::movePC(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	Assert(pCreature->isPC());

	Player* pPlayer = pCreature->getPlayer();
	Assert(pPlayer != NULL);

	if (dir >= DIR_MAX || !isAbleToMove(pCreature))
	{
		GCMoveError 	gcMoveError(pCreature->getX(), pCreature->getY());
		pPlayer->sendPacket(&gcMoveError);
		return;
	}

	const int threshold = 6;
	////////////////////////////////////////////////////////////
	// �ϴ� ũ��ó�� ������ �Ϸ��� ������ üũ�Ѵ�.
	// ���� �ణ �������� ����, GCMoveError ��Ŷ�� �����Ѵ�.
	//
	// OX, OY : �÷��̾��� ���� ��ǥ
	// CX, CY : Ÿ�� ��ǥ
	//
	// max(0, OX - threshold) <= CX <= min(OX + threshold, ZONEWIDTH-1)
	// max(0, OY - threshold) <= CY <= min(OY + threshold, ZONEHEIGHT-1)
	// �� �����ؾ� �������� �̵��̴�.
	////////////////////////////////////////////////////////////
	if (pCreature->getX() != cx || pCreature->getY() != cy)
	{
		if (cx >= max(0           , pCreature->getX() - threshold) &&
			cx <= min(m_Width - 1 , pCreature->getX() + threshold) &&
			cy >= max(0           , pCreature->getY() - threshold) &&
			cy <= min(m_Height - 1, pCreature->getY() + threshold))
		{
			// ���밡���� ���� ������������ ������ �׳� �������ش�.

			/*// �ּ�ó�� by sigi - �� �����°� �´� ��..
			GCMoveError gcMoveError;
			gcMoveError.setX(cx);
			gcMoveError.setY(cy);
			pCreature->getPlayer()->sendPacket(&gcMoveError);
			*/
			return;
		}
		else
		{
			// ���밡���� ���� ������ �Ѿ ���� ������ �����Ѵ�.
			//StringStream msg;
			//msg << pCreature->getName() << " try to jump from ("
			//	<< (int)pCreature->getX() << "," << (int)pCreature->getY()
			//	<< ") to (" << (int)cx << "," << (int)cy << ")";

			GCMoveError 	gcMoveError(cx, cy);
			pPlayer->sendPacket(&gcMoveError);
			return;
		}
	}

	// ���� ��ǥ�� �����Ѵ�.
	int nx = cx;
	int ny = cy;

	//////////////////////////////////////////////////////////////////////////////
	// *CAUTION*
	// ������������ ������ �ܰ����� �����̴� ��Ŷ�� ���ƿͼ��� �ȵȴ�.
	// ex> (0,10)���� LEFT �̵��� ���ƿ� �� ����. (10,0)���� UP �̵��� ���������̴�.
	//////////////////////////////////////////////////////////////////////////////
	nx = nx + dirMoveMask[dir].x;
	ny = ny + dirMoveMask[dir].y;

	VSRect rect(0, 0, m_Width-1, m_Height-1);
	if (!rect.ptInRect(nx, ny)) throw InvalidProtocolException("invalid coordination");

	////////////////////////////////////////////////////////////
	// �̵��� ���� block �Ǿ��ִٸ�, GCMoveError �� �����Ѵ�.
	// (PC�� ���� ��ġ�� block �Ǿ��� �Ѵ�.)
	////////////////////////////////////////////////////////////
	Tile& newTile = m_pTiles[nx][ny];
	Tile& oldTile = m_pTiles[cx][cy];

	 // ������ ������ �ִ� ��������.. �������뿡 ��� �� ����.
	if (pCreature->hasRelicItem() || pCreature->isFlag(Effect::EFFECT_CLASS_HAS_FLAG ) || pCreature->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER))
	{
		ZoneLevel_t ZoneLevel = getZoneLevel(nx, ny);

		// �����̾��̸� �����̾� �������뿡 �� �����.
		// �����̾��̸�  �����̾��������뿡 �� �����.
		// ���� ���������̸� �� �����.
		if (pCreature->isSlayer() && (ZoneLevel & SLAYER_SAFE_ZONE)
			|| pCreature->isVampire() && (ZoneLevel & VAMPIRE_SAFE_ZONE)
			|| pCreature->isOusters() && (ZoneLevel & OUSTERS_SAFE_ZONE)
			|| (ZoneLevel & COMPLETE_SAFE_ZONE))
		{
			GCMoveError 	gcMoveError(cx, cy);
			pPlayer->sendPacket(&gcMoveError);
			return;
		}
	}

	if (newTile.hasCreature(pCreature->getMoveMode()))
	{
		Creature* pTargetCreature = newTile.getCreature(pCreature->getMoveMode());
		if (pTargetCreature != NULL && pTargetCreature->isMonster() )
		{
			Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
			if (pMonster->getMonsterType() >= 738 && pMonster->getMonsterType() <= 740 )
			{
				pMonster->addEnemy(pTargetCreature);
				pMonster->setHP(0);
			}
		}

		GCMoveError 	gcMoveError(cx, cy);
		pPlayer->sendPacket(&gcMoveError);
	}

	if (newTile.isBlocked(pCreature->getMoveMode())
		// BloodyWallBlocked��
		// Sanctuary ����Ʈ�� �ɷ��ִٸ� �� ����.
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
		// �켱 ũ��ó�� ��ǥ�� �����Ѵ�.
		pCreature->setXYDir(nx, ny, dir);

		try
		{
			// ���� Ÿ�Ͽ��� ũ��ó�� �����Ѵ�.
			m_pTiles[cx][cy].deleteCreature(pCreature->getObjectID());

			// �� Ÿ�Ͽ� ũ��ó�� �߰��Ѵ�.
			if (!newTile.addCreature(pCreature))
			{
				// Portal�� activate ��Ų �����̴�. by sigi. 2002.5.6
				return;
			}

			try {
				checkMine(this, pCreature, nx, ny);
				checkTrap(this, pCreature);
			} catch (Throwable & t ) {
				filelog("CheckMineBug.txt", "%s : %s", "movePC", t.toString().c_str());
			}

			// Ŭ���̾�Ʈ���� GCMoveOK �� �����Ҷ�, (nx,ny)�� ���� ��ǥ���� �ϸ�,
			// dir �� �ٶ������߽(�̵���) �����̾��� �Ѵ�. �װ��� ������ ��å!
			GCMoveOK gcMoveOK(nx,ny,dir);
			pPlayer->sendPacket(&gcMoveOK);

			// �ڵ����� GCMove/GCAddSlayer/GCAddVampire ��Ŷ�� ���ε�ĳ��Ʈ�Ѵ�.
			movePCBroadcast(pCreature, cx, cy, nx, ny);
		}
		catch (NoSuchElementException & nsee)
		{
			throw Error("���� Ÿ�Ͽ� ũ��ó�� �������� �ʽ��ϴ�.");
		}
		catch (DuplicatedException & de)
		{
			throw Error("�� Ÿ�Ͽ� ũ��ó�� �̹� �����մϴ�.");
		}
		catch (PortalException&)
		{
		}
		catch (Error& e)
		{
			filelog("assertTile.txt", "Zone::movePC : %s", e.toString().c_str());
			throw;
		}
	}
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// PC�� �ƴ� ũ��ó(NPC,Monster)�� ������ �� �� �޼ҵ带 �����Ѵ�.
//
// *CAUTION*
//
// �̶�, (nx,ny,dir)�� ũ��ó�� ������ ���� ��ǥ�� �ٶ������߽ ������ ��Ÿ����.
// �׸���, �� ��ǥ�� �ƹ� �͵� ���ٴ� ������ ���� �̷������� �Ѵ�. (��ã�� ��ƾ)
//////////////////////////////////////////////////////////////////////////////
void Zone::moveCreature(Creature* pCreature, ZoneCoord_t nx, ZoneCoord_t ny, Dir_t dir)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	ZoneCoord_t cx = pCreature->getX();
	ZoneCoord_t cy = pCreature->getY();

	// ���� Ÿ�Ͽ��� ũ��ó�� �����ϰ�, ���� Ÿ�Ͽ� ũ��ó�� �߰��Ѵ�.
	try
	{
		// ���� Ÿ�Ͽ��� ũ��ó�� �����Ѵ�.
		m_pTiles[cx][cy].deleteCreature(pCreature->getObjectID());

		// ���� Ÿ�Ͽ� ũ��ó�� �߰��Ѵ�.
		m_pTiles[nx][ny].addCreature(pCreature);

		// ũ��ó�� ��ǥ�� ������ �����Ѵ�.
		pCreature->setXYDir(nx, ny, dir);

		try {
			checkMine(this, pCreature, nx, ny);
			checkTrap(this, pCreature);
		} catch (Throwable & t ) {
			filelog("CheckMineBug.txt", "%s : %s", "moveCreature", t.toString().c_str());
		}

	}
	catch (NoSuchElementException & nsee)
	{
		throw Error("���� Ÿ�Ͽ� ũ��ó�� �������� �ʽ��ϴ�.");
	}
	catch (DuplicatedException & de)
	{
		throw Error("�� Ÿ�Ͽ� ũ��ó�� �̹� �����մϴ�.");
	}
	catch (Error& e)
	{
		filelog("assertTile.txt", "Zone::moveCreature : %s", e.toString().c_str());
		throw;
	}

	// �˾Ƽ� GCMove �� GCAddMonster/GCAddNPC �� ���ε�ĳ��Ʈ�Ѵ�.
	moveCreatureBroadcast(pCreature, cx, cy, nx, ny);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// add PC
//
// PC �� ���� ���ʷ� �߰��Ѵ�. PC �ֺ��� �ٸ� PC�鿡�� �� ũ��ó�� ������ �˷��ְ�,
// �ֺ��� ��ĵ�ؼ� ��ü���� ������ �޾ƿ´�.
//////////////////////////////////////////////////////////////////////////////
void Zone::addPC(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir)
	throw(EmptyTileNotExistException, Error)
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

		// ������ ��ǥ�� Ŭ���̾�Ʈ�� �����Ѵ�.
		GCSetPosition gcSetPosition;
		gcSetPosition.setX(pt.x);
		gcSetPosition.setY(pt.y);
		gcSetPosition.setDir(dir);

		pCreature->getPlayer()->sendPacket(&gcSetPosition);

		// ũ��ó�� ��ǥ�� ������ �����Ѵ�.
		pCreature->setXYDir(pt.x, pt.y, dir);

		// ������ �o���� ã������, ũ��ó�� ������
		// PC�Ŵ����� Ÿ�Ͽ� ���� �����ִ´�.
		m_pTiles[pt.x][pt.y].addCreature(pCreature);

		//checkMine(this, pCreature, pt.x, pt.y);	// ���⼭�� mine�� ���߽��Ѿ� �ϳ�..?

		m_pPCManager->addCreature(pCreature);

		// Sanctuary �÷��װ� ���������� ���ش�.
/*		if (pCreature->isFlag(Effect::EFFECT_CLASS_SANCTUARY ) && m_pTiles[pt.x][pt.y].getEffect(Effect::EFFECT_CLASS_SANCTUARY ) == NULL )
		{
			pCreature->removeFlag(Effect::EFFECT_CLASS_SANCTUARY);
		}*/

		// �йи� �������ϰ��� Default Option ���ʽ��� �ش�.
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
		if (pGamePlayer->isFamilyPayAvailable() && !pCreature->isFlag(Effect::EFFECT_CLASS_FAMILY_BONUS ) )
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Assert(pPC != NULL);

			pPC->addDefaultOptionSet(DEFAULT_OPTION_SET_FAMILY_PAY);
			addSimpleCreatureEffect(pPC, Effect::EFFECT_CLASS_FAMILY_BONUS);
			pPC->setFlag(Effect::EFFECT_CLASS_INIT_ALL_STAT);
		}

		// EFFECT_CLASS_INIT_ALL_STAT �� ���� ������ initAllStat�� �θ��� Flag �� ����.
		if (pCreature->isFlag(Effect::EFFECT_CLASS_INIT_ALL_STAT ) )
		{
			if (pCreature->isSlayer() )
			{
				Slayer* pInitSlayer = dynamic_cast<Slayer*>(pCreature);
				Assert(pInitSlayer != NULL);

				SLAYER_RECORD prev;
				pInitSlayer->getSlayerRecord(prev);
				pInitSlayer->initAllStat();
				pInitSlayer->sendModifyInfo(prev);
			}
			else if (pCreature->isVampire() )
			{
				Vampire* pInitVampire = dynamic_cast<Vampire*>(pCreature);
				Assert(pInitVampire != NULL);

				VAMPIRE_RECORD prev;
				pInitVampire->getVampireRecord(prev);
				pInitVampire->initAllStat();
				pInitVampire->sendModifyInfo(prev);
			}
			else if (pCreature->isOusters() )
			{
				Ousters* pInitOusters = dynamic_cast<Ousters*>(pCreature);
				Assert(pInitOusters != NULL);

				OUSTERS_RECORD prev;
				pInitOusters->getOustersRecord(prev);
				pInitOusters->initAllStat();
				pInitOusters->sendModifyInfo(prev);
			}

			pCreature->removeFlag(Effect::EFFECT_CLASS_INIT_ALL_STAT);
		}

		if (pCreature->isSlayer())
		{
			((Slayer*)pCreature)->sendRealWearingInfo();
			((Slayer*)pCreature)->sendSlayerSkillInfo();
			((Slayer*)pCreature)->sendTimeLimitItemInfo();
		}
		else if (pCreature->isVampire() )
		{
			((Vampire*)pCreature)->sendRealWearingInfo();
			((Vampire*)pCreature)->sendVampireSkillInfo();
			((Vampire*)pCreature)->sendTimeLimitItemInfo();
		}
		else if (pCreature->isOusters() )
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
		// �������� �޽����� �ִٸ� ������.
		// �ϴ� ���Ƶд�. - bezz 2002. 07. 13
		//////////////////////////////////////////////////////////////////////////////
		if (!pCreature->isFlag(Effect::EFFECT_CLASS_LOGIN_GUILD_MESSAGE ) )
		{
			Statement* pStmt = NULL;
			Result* pResult = NULL;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN" )->createStatement();
				pResult = pStmt->executeQuery("SELECT Message FROM Messages WHERE Receiver = '%s'", pCreature->getName().c_str());

				while (pResult->next() )
				{
					GCSystemMessage message;
					message.setMessage(pResult->getString(1));
					pCreature->getPlayer()->sendPacket(&message);
				}

				pStmt->executeQuery("DELETE FROM Messages WHERE Receiver = '%s'", pCreature->getName().c_str());

				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			pCreature->setFlag(Effect::EFFECT_CLASS_LOGIN_GUILD_MESSAGE);
		}

		//////////////////////////////////////////////////////////////////////////////
		// PREMIUM_HALF_EVENT �� on �Ǿ� �ְ� �������̸� Ŭ���̾�Ʈ�� �˸���.
		//////////////////////////////////////////////////////////////////////////////
		if (g_pVariableManager->getVariable(PREMIUM_HALF_EVENT )
			&& (m_ZoneID == 61 || m_ZoneID == 64 || m_ZoneID == 1007 )
			)
		{
			GCNoticeEvent gcNoticeEvent;
			gcNoticeEvent.setCode(NOTICE_EVENT_PREMIUM_HALF_START);

			pCreature->getPlayer()->sendPacket(&gcNoticeEvent);
		}

		// �ֺ��� PC�鿡�� �˸� GCAddSlayer or GCAddVampire ��Ŷ�� �����Ѵ�.
		Creature::CreatureClass CClass = pCreature->getCreatureClass();
		if (CClass == Creature::CREATURE_CLASS_SLAYER)
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			GCAddSlayer gcAddSlayer;
			makeGCAddSlayer(&gcAddSlayer, pSlayer);

			scan(pCreature, pt.x, pt.y, &gcAddSlayer);

			// �ɷ�ġ 40 �̻��� ���� �������ɺο��� �Ѱܳ���. by sigi. 2002.11.7
			checkNewbieTransportToGuild(pSlayer);
		}
		else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			GCAddVampire gcAddVampire;
			makeGCAddVampire(&gcAddVampire, pVampire);

			scan(pCreature, pt.x, pt.y, &gcAddVampire);

			// �����̾����� ��Ż�� �̿��� ���� ���ɼ��� �����Ƿ�,
			// �÷��׸� ���ش�.
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

		// ��Ƽ�� ���ԵǾ� �ִٸ� ���� ��Ƽ�� ���Խ�Ų��.
		uint PartyID = pCreature->getPartyID();
		if (PartyID != 0)
		{
			// ��Ƽ�� �ִٸ� �� ���Ѵ�.
			m_pLocalPartyManager->addPartyMember(PartyID, pCreature);
		}

		// ���� ������ �����ش�.
		#if !defined(__CONNECT_BILLING_SYSTEM__) && (defined(__PAY_SYSTEM_ZONE__) || defined(__PAY_SYSTEM_FREE_LIMIT__) )
			if (pCreature->isPC())
			{
				GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());

				// ���ӹ��� ���쿡
				// ���� �������̸�
				// �ð��� ���� ���� �ʾ��� ���쿡 ���� ������ ǥ�����ش�.
				if ((pGamePlayer->isPayPlaying() || pGamePlayer->isPremiumPlay())
					&& pGamePlayer->getPayType()==PAY_TYPE_TIME)
				{
					Timeval currentTime;
					getCurrentTime(currentTime);
					Timeval payTime = pGamePlayer->getPayPlayTime(currentTime);

					int usedMin = payTime.tv_sec/60;
					int remainMin = pGamePlayer->getPayPlayAvailableHours()-usedMin;

					// PC���� ���� �ð��� 5�ð�(300��) ������ �� ����
					if (pGamePlayer->getPayPlayType()==PAY_PLAY_TYPE_PCROOM)
					{
						//cout << "PC�� �����ð� : " << usedMin << "/" << pGamePlayer->getPayPlayAvailableHours() << endl;

						if (remainMin <= 300)
						{
							char str[80];
                            sprintf(str, g_pStringPool->c_str(STRID_PCROOM_REMAIN_PLAY_TIME ),
                                            remainMin);
							//sprintf(str, "[PC��] �����ð��� %d�� ���ҽ��ϴ�.", remainMin);
							GCSystemMessage gcSystemMessage;
							gcSystemMessage.setMessage(str);
							pGamePlayer->sendPacket (&gcSystemMessage);
						}
					}
					// ������ ���� �ð��� 1�ð�(60��) ������ �� ����
					else if (pGamePlayer->getPayPlayType()==PAY_PLAY_TYPE_PERSON)
					{
						if (remainMin <= 60)
						{
							char str[80];
                            sprintf(str, g_pStringPool->c_str(STRID_PERSONAL_REMAIN_PLAY_TIME ),
                                            remainMin);
							//sprintf(str, "[����] �����ð��� %d�� ���ҽ��ϴ�.", remainMin);
							GCSystemMessage gcSystemMessage;
							gcSystemMessage.setMessage(str);
							pGamePlayer->sendPacket (&gcSystemMessage);
						}
					}
				}
			}
		#endif

		// �ұ���
		if (isMasterLair() && m_pMasterLairManager!=NULL)
		{
			MasterLairInfo* pInfo = g_pMasterLairInfoManager->getMasterLairInfo(getZoneID());
		    Assert(pInfo!=NULL);

			if (m_pMasterLairManager->getCurrentEvent()==MasterLairManager::EVENT_WAITING_PLAYER)
			{
				// �������� �ұ��� ����Ʈ�� �ִ� ���쿡 �˷��ش�.
				if (m_pEffectManager->findEffect(Effect::EFFECT_CLASS_CONTINUAL_GROUND_ATTACK )!=NULL)
				{
					GCNoticeEvent gcNoticeEvent;
					gcNoticeEvent.setCode(NOTICE_EVENT_CONTINUAL_GROUND_ATTACK);
					gcNoticeEvent.setParameter(pInfo->getStartDelay());   // ��

					broadcastPacket(&gcNoticeEvent);
				}
			}
		}

		//-----------------------------------------------------------------
		// ���� �����Ǵ� ����
		//-----------------------------------------------------------------
/*		if (isCastle())
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

			int itemTaxRatio = g_pCastleInfoManager->getItemTaxRatio(pPC);

			if (itemTaxRatio > 100)
			{
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode(NOTICE_EVENT_SHOP_TAX_CHANGE);
				gcNoticeEvent.setParameter((uint)itemTaxRatio);

				pPC->getPlayer()->sendPacket(&gcNoticeEvent);
			}
		}*/

		//-----------------------------------------------------------------
		// ���� ���� ������ ���������� �����ش�.
		//-----------------------------------------------------------------
		if (g_pWarSystem->isWarActive())
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			g_pWarSystem->sendGCWarList(pPC->getPlayer());
		}

		if (g_pFlagManager->hasFlagWar() && g_pFlagManager->isFlagAllowedZone(getZoneID() ) )
		{
			Player* pPlayer = pCreature->getPlayer();
			if (pPlayer != NULL ) pPlayer->sendPacket(g_pFlagManager->getStatusPacket());
		}

		if (m_pLevelWarManager != NULL && m_pLevelWarManager->hasWar() )
		{
			// ������ ���� ���̸� �հ� �������� �� ��
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			m_pLevelWarManager->sendGCWarList(pPC->getPlayer());
		}

		//-----------------------------------------------------------------
		// �ƴ��� ������ ������ ������ ����Ʈ�� �ѷ��ش�.
		//-----------------------------------------------------------------
		// ������ �ִ� ���� üũ�ؾ� �ɰ� ������? -_-;
		//-----------------------------------------------------------------
		//if (isHolyLand())
		//{
		sendHolyLandWarpEffect(pCreature);
		//}

		if (isHolyLand())
		{
			if (g_pWarSystem->hasActiveRaceWar() )
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				g_pShrineInfoManager->sendBloodBibleStatus(pPC);

				pPC->getPlayer()->sendPacket(RegenZoneManager::getInstance()->getStatusPacket());
			}
			else
			{
				GCHolyLandBonusInfo gcHolyLandBonusInfo;
				g_pBloodBibleBonusManager->makeHolyLandBonusInfo(gcHolyLandBonusInfo);
				pCreature->getPlayer()->sendPacket(&gcHolyLandBonusInfo);
			}
		}

		if (g_pSweeperBonusManager->isAble(getZoneID() ) && g_pLevelWarZoneInfoManager->isCreatureBonusZone(pCreature, getZoneID() ) )
		{
			GCSweeperBonusInfo gcSweeperBonusInfo;
			g_pSweeperBonusManager->makeSweeperBonusInfo(gcSweeperBonusInfo);
			pCreature->getPlayer()->sendPacket(&gcSweeperBonusInfo);
//			pCreature->setFlag(Effect::EFFECT_CLASS_INIT_ALL_STAT);
		}


		// Player ���� GCItemNameInfoList ��Ŷ�� �����ش�
/*		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		if (!pPC->isEmptyItemNameInfoList() )
		{
			GCItemNameInfoList	gcItemNamInfoList;
			makeGCItemNameInfoList(&gcItemNamInfoList, pPC);

			pPC->getPlayer()->sendPacket(&gcItemNamInfoList);
		}*/

		// PK������ �׾ �ǻ��Ƴ��� ���� ��Ȱ ����Ʈ�� �ٴ´�.
		if (pCreature->isFlag(Effect::EFFECT_CLASS_PK_ZONE_RESURRECTION ) )
		{
			Effect* pEffect = pCreature->findEffect(Effect::EFFECT_CLASS_PK_ZONE_RESURRECTION);
			if (pEffect != NULL )
			{
				// Effect�� ������ ������ �� ��Ȱ ����Ʈ �ٿ��ֶ��� ��Ŷ�� ���������߽.
				pEffect->setDeadline(0);
			}
			else
			{
				pCreature->removeFlag(Effect::EFFECT_CLASS_PK_ZONE_RESURRECTION);
			}
		}

		// �� ������ ���̶��� �հ��� �����ش�.
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		if (pPC->getFlagSet()->isOn(FLAGSET_NOT_JUST_CREATED) )
		{
			GCNoticeEvent gcNoticeEvent;
			gcNoticeEvent.setCode(NOTICE_EVENT_WELCOME_MESSAGE);
			pPC->getPlayer()->sendPacket(&gcNoticeEvent);

			pPC->getFlagSet()->turnOff(FLAGSET_NOT_JUST_CREATED);
			pPC->getFlagSet()->save(pPC->getName());

			GCNoticeEvent gcNoticeEvent2;
			gcNoticeEvent2.setCode(NOTICE_EVENT_LOGIN_JUST_NOW);
			gcNoticeEvent2.setParameter(g_pVariableManager->getHeadPriceBonus());

			pPC->getPlayer()->sendPacket(&gcNoticeEvent2);

			pPC->setFlag(Effect::EFFECT_CLASS_JUST_LOGIN);

			if (g_pVariableManager->getVariable(CHOBO_EVENT) )
			{
				pPC->getGQuestManager()->getGQuestInventory().saveOne(pPC->getName(),13);
				pPC->getPlayer()->sendPacket(pPC->getGQuestManager()->getGQuestInventory().getInventoryPacket());
				gcNoticeEvent.setCode(NOTICE_EVENT_GIVE_PRESENT_1);
				pPC->getPlayer()->sendPacket(&gcNoticeEvent);
			}
		}
		else if (!pPC->isFlag(Effect::EFFECT_CLASS_JUST_LOGIN ) )
		{
			// �Ĺ� �̺�Ʈ ����
			Statement* pStmt = NULL;
			Result* pResult = NULL;
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
				pResult = pStmt->executeQuery("SELECT PlayerID FROM Event200501Main WHERE PlayerID = '%s' AND RecvItemDate = '0000-00-00'", pPC->getPlayer()->getID().c_str());

				if (pResult->next() )
				{
					GCNPCResponse response;
					response.setCode(NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG);
					response.setParameter(YOU_CAN_GET_EVENT_200501_COMBACK_ITEM);
					pPC->getPlayer()->sendPacket(&response);
				}

				pResult = pStmt->executeQuery("SELECT PlayerID FROM Event200501Main WHERE PlayerID = '%s' AND PayPremiumDate <> '0000-00-00' AND RecvPremiumItemDate = '0000-00-00'", pPC->getPlayer()->getID().c_str());

				if (pResult->next() )
				{
					GCNPCResponse response;
					response.setCode(NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG);
					response.setParameter(YOU_CAN_GET_EVENT_200501_COMBACK_PREMIUM_ITEM);
					pPC->getPlayer()->sendPacket(&response);
				}

				pResult = pStmt->executeQuery("SELECT PlayerID FROM Event200501Recommend WHERE PlayerID = '%s' AND RecvItemDate = '0000-00-00'", pPC->getPlayer()->getID().c_str());

				if (pResult->next() )
				{
					GCNPCResponse response;
					response.setCode(NPC_RESPONSE_SHOW_COMMON_MESSAGE_DIALOG);
					response.setParameter(YOU_CAN_GET_EVENT_200501_COMBACK_RECOMMEND_ITEM);
					pPC->getPlayer()->sendPacket(&response);
				}
			}
			END_DB(pStmt);

			if (g_pVariableManager->getVariable(TODAY_IS_HOLYDAY ) )
			{
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode(NOTICE_EVENT_HOLYDAY);
				gcNoticeEvent.setParameter(g_pVariableManager->getVariable(TODAY_IS_HOLYDAY ));

				pPC->getPlayer()->sendPacket(&gcNoticeEvent);
			}

//			if (canEnterBeginnerZone(pPC ) && getZoneID() != 1122 )
			if (canEnterBeginnerZone(pPC ) )
			{
				int year = VSDate::currentDate().year() - 2000;
				int month = VSDate::currentDate().month();
				int day = VSDate::currentDate().day();
				int hour = VSTime::currentTime().hour();
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode(NOTICE_EVENT_ENTER_BEGINNER_ZONE);
				gcNoticeEvent.setParameter((year * 1000000) + (month * 10000) + (day * 100) + hour);
				pPC->getPlayer()->sendPacket(&gcNoticeEvent);
			}

			if (g_pVariableManager->isWarActive() && g_pVariableManager->isAutoStartRaceWar() && g_pWarSystem->isRaceWarToday() )
			{
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode(NOTICE_EVENT_RACE_WAR_SOON);
				gcNoticeEvent.setParameter(g_pWarSystem->getRaceWarTimeParam());
				pPC->getPlayer()->sendPacket(&gcNoticeEvent);
			}

			if (g_pVariableManager->isActiveLevelWar() )
			{
				ZoneID_t levelWarZoneId = g_pLevelWarZoneInfoManager->getCreatureZoneID(pCreature);

//				cout << "ZoneID : " << levelWarZoneId << endl;
				if (levelWarZoneId != 1 )
				{
					Zone* pLevelZone = getZoneByZoneID(levelWarZoneId);
					Assert(pLevelZone != NULL);

					LevelWarManager* pLevelWarManager = pLevelZone->getLevelWarManager();
					Assert(pLevelWarManager != NULL);

					if (pLevelWarManager->hasToDayWar() )
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
						gcNoticeEvent.setCode(NOTICE_EVENT_LEVEL_WAR_ARRANGED);
//						gcNoticeEvent.setParameter(((DWORD)((DWORD)month << 24)) | ((DWORD)((DWORD)day << 16)) | ((DWORD)((DWORD)hour << 8)) | ((DWORD)((DWORD)level)));
						gcNoticeEvent.setParameter((level * 100000000) + (year * 1000000) + (month * 10000) + (day * 100) + hour);
						pPC->getPlayer()->sendPacket(&gcNoticeEvent);
					}

				}
			}

			GCNoticeEvent gcNoticeEvent;
			gcNoticeEvent.setCode(NOTICE_EVENT_LOGIN_JUST_NOW);
			gcNoticeEvent.setParameter(g_pVariableManager->getHeadPriceBonus());

			pPC->getPlayer()->sendPacket(&gcNoticeEvent);

			pPC->setFlag(Effect::EFFECT_CLASS_JUST_LOGIN);
		}

		if (pPC->getPetInfo() != NULL ) sendPetInfo(pGamePlayer);
		// �� �̵��Ҷ�  �־��ִ� ��Ŷ
		Packet* pNicknamePacket = pPC->getNicknameBook()->getNicknameBookListPacket();
		pPC->getPlayer()->sendPacket(pNicknamePacket);
		SAFE_DELETE(pNicknamePacket);

		Packet* pGQuestPacket = pPC->getGQuestManager()->getStatusInfoPacket();
		pPC->getPlayer()->sendPacket(pGQuestPacket);
		SAFE_DELETE(pGQuestPacket);

		pGQuestPacket = pPC->getGQuestManager()->getGQuestInventory().getInventoryPacket();
		pPC->getPlayer()->sendPacket(pGQuestPacket);

		// GCUnionOfferList
		//

		GCUnionOfferList	gcUnionOfferList;

		{
			GuildUnion *pUnion = GuildUnionManager::Instance().getGuildUnion(pPC->getGuildID());
			if(pUnion != NULL)
			{
			//	cout << "GuildUNION : Union�� �ִ� PlayerCreature" << endl;

				if(g_pGuildManager->isGuildMaster (pPC->getGuildID(), pPC ) )
			//		cout << "GuildUNION : PC�� GuildMaster��" << endl;

				if(pUnion->getMasterGuildID() == pPC->getGuildID() )
			//		cout << "GuildUNION : ������ ������ ���尡 �� ������" << endl;

				// ��û�ѳ��� ���� ���� ������ �������ΰ�? || ������ �����ͱ��尡 �� ���尡 �³�?
				if(g_pGuildManager->isGuildMaster (pPC->getGuildID(), pPC )
					&& pUnion->getMasterGuildID() == pPC->getGuildID() )
				{
			//		cout << "�׷���..OfferList�� ����� ��������.." << endl;

					if(GuildUnionOfferManager::Instance().makeOfferList(pUnion->getUnionID(), gcUnionOfferList ))
					{
						pPC->getPlayer()->sendPacket(&gcUnionOfferList);
					}

				}
			}
		}

		if (g_pWarSystem->isSkyBlack() )
		{
			GCNoticeEvent gcNE;
			gcNE.setCode(NOTICE_EVENT_RACE_WAR_IN_5);
			pPC->getPlayer()->sendPacket(&gcNE);
		}

		// GCMyStoreInfo myStoreInfo;
		// myStoreInfo.setStoreInfo(&(pPC->getStore()->getStoreInfo()));
		// myStoreInfo.setOpenUI(0);
		// pPC->getPlayer()->sendPacket(&myStoreInfo);

		//pPC->getPlayer()->sendPacket(&gcUnionOfferList);

/*		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode(NOTICE_EVENT_CROWN_PRICE);
		gcNoticeEvent.setParameter(g_pVariableManager->getVariable(CROWN_PRICE));
		pPC->getPlayer()->sendPacket(&gcNoticeEvent);*/
	}
	else
	{
		ZoneCoord_t tempX = Random(20, m_Width);
		ZoneCoord_t tempY = Random(20, m_Height);
		addPC(pCreature, tempX, tempY, 0);

		// �ƽ�ī��Ʈ ������ �� ã�� ���� Assert
		//throw EmptyTileNotExistException("too many pc in this zone.. or too unlucky");
	}


	__END_PROFILE_ZONE("Z_ADD_PC")

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// detect invisibility���� ȿ���� ������ ����..���̴� ���� �Ⱥ��̰� �� ����
// pCreature���� GCDeleteObject�� �����ش�. ���� �ִ� invisible creature��
// delete�Ѵ�. �Ǵ� �Ⱥ��δ� ���� ���̰� �� ������..
//////////////////////////////////////////////////////////////////////////////
void Zone::updateInvisibleScan(Creature* pCreature)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL && pCreature->isPC());

	Coord_t cx = pCreature->getX();
	Coord_t cy = pCreature->getY();
	Player* pPlayer = pCreature->getPlayer();

	// Revealer ����Ʈ�� �����´�.
//	EffectRevealer* pEffectRevealer = NULL;
//	if (pCreature->isFlag(Effect::EFFECT_CLASS_REVEALER) )
//	{
//		pEffectRevealer = dynamic_cast<EffectRevealer*>(pCreature->findEffect(Effect::EFFECT_CLASS_REVEALER));
//		Assert(pEffectRevealer != NULL);
//	}

	// ObservingEey ����Ʈ�� �����´�.
	EffectObservingEye* pEffectObservingEye = NULL;
	if (pCreature->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
	{
		pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pCreature->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE));
		//Assert(pEffectObservingEye != NULL);
	}

	EffectGnomesWhisper* pEffectGnomesWhisper = NULL;
	// GnomesWhisper ����Ʈ�� �����´�.
	if (pCreature->isFlag(Effect::EFFECT_CLASS_GNOMES_WHISPER) )
	{
		pEffectGnomesWhisper = dynamic_cast<EffectGnomesWhisper*>(pCreature->findEffect(Effect::EFFECT_CLASS_GNOMES_WHISPER));
	}

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++)
		{
			// darkness���� ����.
			// ���� pCreature�� �翬�� slayer��.(updateInvisibleScan�̹Ƿ�..)
			if (pCreature->isSlayer() || pCreature->isOusters())
			{
				const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
				list<Object*>::const_iterator itr = objectList.begin();

				for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE ; itr++)
				{
					if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pPC = dynamic_cast<Creature*>(*itr);
						Assert(pPC != NULL);

						// �ڱ� �ڽ��� ���� ����
						if (pCreature == pPC
							|| pPC->isFlag(Effect::EFFECT_CLASS_GHOST)) continue;

						// �����ִ� ������ ���ؼ�..
						// SNIPING�̳� INVISIBILITY������ ����.
						if (pPC->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) && pCreature->getVisionState(ix,iy) >= IN_SIGHT)
						{
							// Detect Invisibility ����Ʈ�� �ְų� �����̾��� �� �� �ִ�
							// ObservingEye ����Ʈ�� ���� ���� �������� �� �� �ִ� �����̶���
							if (pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || pCreature->isVampire()
								|| (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(pPC ) )
								|| (pEffectGnomesWhisper != NULL && pEffectGnomesWhisper->canSeeInvisibility() )
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
									Packet* pAddMonsterPacket = createMonsterAddPacket(pMonster, pCreature);

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
							if ((!pCreature->isVampire() && pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) ) )
//								|| (pEffectRevealer != NULL && pEffectRevealer->canSeeSniping(pPC ) ) )
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
									throw Error("�����̾ �������� ���忡 �ִ�. ���Ľ�~");
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
// detect hidden���� ȿ���� ������ ����..���̴� ���� �Ⱥ��̰� �� ����
// pCreature���� GCDeleteObject�� �����ش�.
// ���� �ִ� burrow creature�� delete�Ѵ�. �Ǵ� �Ⱥ��δ� ���� ���̰� �� ������..
// ABCD
//--------------------------------------------------------------------------------
void Zone::updateHiddenScan(Creature* pCreature)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL && pCreature->isPC());

	Coord_t cx = pCreature->getX();
	Coord_t cy = pCreature->getY();
	Player* pPlayer = pCreature->getPlayer();

	// Revealer ����Ʈ�� �����´�.
//	EffectRevealer* pEffectRevealer = NULL;
//	if (pCreature->isFlag(Effect::EFFECT_CLASS_REVEALER) )
//	{
//		pEffectRevealer = dynamic_cast<EffectRevealer*>(pCreature->findEffect(Effect::EFFECT_CLASS_REVEALER));
//		Assert(pEffectRevealer != NULL);
//	}

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++)
		{
			// darkness���� ����.
			// ���� pCreature�� �翬�� slayer��.(updateHiddenScan�̹Ƿ�..)
			if (pCreature->isSlayer())
			{
				const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

				for (list<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE ; itr++)
				{

					if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pPC = dynamic_cast<Creature*>(*itr);
						Assert(pPC != NULL);

						// �ڱ� �ڽ��� ���� ����
						if (pCreature == pPC ) continue;

						// �����ִ� ������ ���ؼ�..
						if (pPC->isFlag(Effect::EFFECT_CLASS_HIDE) &&
								pCreature->getVisionState(ix,iy) >= IN_SIGHT)
						{
							if (pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) || pCreature->isVampire()  )
//								|| (pEffectRevealer != NULL && pEffectRevealer->canSeeHide(pPC ) ) )
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
// Detect ������ �����ų� ������ ����.
// ���� Creature �� Creature �߰� ���� ó��
// �ƿ콺�ͽ� ��
//////////////////////////////////////////////////////////////////////////////
void Zone::updateDetectScan(Creature* pCreature)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL && pCreature->isPC());

	Coord_t cx = pCreature->getX();
	Coord_t cy = pCreature->getY();
	Player* pPlayer = pCreature->getPlayer();

	EffectGnomesWhisper* pEffectGnomesWhisper = NULL;
	if (pCreature->isFlag(Effect::EFFECT_CLASS_GNOMES_WHISPER ) )
	{
		pEffectGnomesWhisper = dynamic_cast<EffectGnomesWhisper*>(pCreature->findEffect(Effect::EFFECT_CLASS_GNOMES_WHISPER));
	}

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++)
		{
			if (pCreature->getVisionState(ix,iy) == OUT_OF_SIGHT ) continue;

			if (pCreature->isOusters())
			{
				const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
				list<Object*>::const_iterator itr = objectList.begin();

				for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE ; itr++)
				{
					if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pPC = dynamic_cast<Creature*>(*itr);
						Assert(pPC != NULL);

						// �ڱ� �ڽ��� ���� ����
						if (pCreature == pPC
							|| pPC->isFlag(Effect::EFFECT_CLASS_GHOST)) continue;

						if (pPC->isSlayer() )
						{
							if (pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE ) )
							{
								if (canSee(pCreature, pPC, NULL, pEffectGnomesWhisper ) )
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
						else if (pPC->isVampire() )
						{
							if (pPC->isFlag(Effect::EFFECT_CLASS_INVISIBILITY ) )
							{
								if (canSee(pCreature, pPC, NULL, pEffectGnomesWhisper ) )
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

							if (pPC->isFlag(Effect::EFFECT_CLASS_HIDE ) )
							{
								if (canSee(pCreature, pPC, NULL, pEffectGnomesWhisper ) )
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
						else if (pPC->isMonster() )
						{
							if (pPC->isFlag(Effect::EFFECT_CLASS_INVISIBILITY ) || pPC->isFlag(Effect::EFFECT_CLASS_HIDE ) )
							{
								if (canSee(pCreature, pPC, NULL, pEffectGnomesWhisper ) )
								{
									Monster* pMonster= dynamic_cast<Monster*>(pPC);

									Packet* pAddMonsterPacket = createMonsterAddPacket(pMonster, pCreature);

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
// detect mine���� ȿ���� ������ ����..���̴� mine�� �Ⱥ��̰� �� ����
// pCreature���� GCDeleteObject�� �����ش�.
//--------------------------------------------------------------------------------
void Zone::updateMineScan(Creature* pCreature)
	throw(ProtocolException, Error)
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
			if (pCreature->getVisionState(ix,iy) == OUT_OF_SIGHT ) continue;

			// ���� pCreature�� �翬�� slayer��.(updateMineScan�̹Ƿ�..)
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
// ũ��ó�� ���� ���ʷ� ��� ��, ũ��ó �ֺ��� PC�鿡�� �� ũ��ó�� ������ �˷��ش�.
//--------------------------------------------------------------------------------
void Zone::addCreature(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir)
	throw(EmptyTileNotExistException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_ADD_CREATURE")

	TPOINT pt = findSuitablePosition(this, cx, cy, pCreature->getMoveMode());

	// ã�� ���� üũ
	if (pt.x != -1)
	{
		//--------------------------------------------------------------------------------
		// OID �� �Ҵ��޴´�.
		//--------------------------------------------------------------------------------
		m_ObjectRegistry.registerObject(pCreature);

		//--------------------------------------------------------------------------------
		// ������ Ÿ���� ã������, ũ��ó�� ũ��ó�Ŵ����� Ÿ�Ͽ� ���� �����ִ´�.
		// Monster �� ����, MonsterManager�� �߰��ϸ�, NPC �� ����, NPCManager �� �߰��Ѵ�.
		//--------------------------------------------------------------------------------
		if (pCreature->isMonster())
		{

//#ifdef __XMAS_EVENT_CODE__
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			if (isDynamicZone() )
			{
				pMonster->setScanEnemy(true);
			}

			m_pMonsterManager->addCreature(pCreature);
			//if (pCreature->getClanType() != CLAN_VAMPIRE_MONSTER )
				//cout << pCreature->toString() << " regens at " << pt.x << " , " << pt.y << endl;

			switch (pMonster->getMonsterType() )
			{
				case 717:
				case 721:
				case 723:
				case 724:
				case 725:
					{
						map<ObjectID_t, Creature*>::iterator itr = m_pPCManager->getCreatures().begin();
						map<ObjectID_t, Creature*>::iterator endItr = m_pPCManager->getCreatures().end();

						for (; itr != endItr ; ++itr )
						{
							pMonster->addPotentialEnemy(itr->second);
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

		//cout << "Ÿ�Ͽ� ������ �߰��ϱ�" << endl;
	   	m_pTiles[pt.x][pt.y].addCreature(pCreature, false);

		//--------------------------------------------------------------------------------
		// ũ��ó�� ��ǥ�� �����Ѵ�.
		//--------------------------------------------------------------------------------
		pCreature->setXYDir(pt.x, pt.y, dir);
		pCreature->setZone(this);

		//scanPC(pCreature);

		//--------------------------------------------------------------------------------
		// �ֺ��� PC�鿡�� �˸� GCAddNPC or GCAddMonster ��Ŷ�� �����Ѵ�.
		//--------------------------------------------------------------------------------
		//cout << "�ֺ��� PC�鿡�� �˸� ��Ŷ ������" << endl;
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
			//cout << "�����Ϳ� ��Ŷ ������" << endl;
			Monster* pMonster = dynamic_cast<Monster*>(pCreature);

			// zone�� ó�� ������� �������� ���°� �ִ�.. by sigi
			Packet* pAddMonsterPacket = createMonsterAddPacket(pMonster, NULL);

			if (pAddMonsterPacket!=NULL)
			{
				broadcastPacket(cx, cy, pAddMonsterPacket, pMonster);
/*				ZoneCoord_t ix = 0;
				ZoneCoord_t iy = 0;
				ZoneCoord_t endx = 0;
				ZoneCoord_t endy = 0;


				//////////////////////////////////////////////////////////////////////////////
				// ���� ���� �ʱ�ȭ..
				//////////////////////////////////////////////////////////////////////////////
				int Range = 0;
				endx = min(m_Width - 1, cx + maxViewportWidth + 1 + Range);
				endy = min(m_Height - 1, cy + maxViewportLowerHeight  + 1 + Range);

				for (ix =  max(0, cx - maxViewportWidth - 1 - Range); ix <= endx ; ix++)
				{
					for (iy = max(0, cy - maxViewportUpperHeight - 1 -  Range); iy <= endy ; iy++)
					{
						// Ÿ�Ͽ� ũ��ó�� �ִ� ���쿡��
						if (m_pTiles[ix][iy].hasCreature())
						{
							const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
							list<Object*>::const_iterator itr = objectList.begin();

							for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++)
							{
								Creature* pOtherCreature = dynamic_cast<Creature*>(*itr);
								Assert(pOtherCreature != NULL);

								if (pOtherCreature->isPC())
								{
									if (canSee(pOtherCreature, pMonster ) )
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
			// ��Ż�� ���ؼ� ��Ÿ���� ������ �����ش�.
			// �÷��׸� ���ش�.
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
// Ư�� ��ġ�� �������� �����߸���.
// Zone ::addItem()
// 7x7 ������ �˻��ؼ� ��ĭ�� �����ϸ� �����߸���. ������ �������� ���� ��ĭ��
// �������� ���� �����ε�.. �̶� ���ܸ� �������ν� �� ó���� �������� �ñ���
// �� ��...
//--------------------------------------------------------------------------------
TPOINT Zone::addItem(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature, Turn_t decayTurn, ObjectID_t DropPetOID)
	throw(EmptyTileNotExistException, Error)
{
	__BEGIN_TRY

	__BEGIN_DEBUG

	TPOINT          pt;

	__BEGIN_PROFILE_ZONE("Z_ADD_ITEM")

	Item::ItemClass IClass = pItem->getItemClass();

	bool bAllowSafeZone = true;

	if (isRelicItem(IClass ) || pItem->isFlagItem() )
		bAllowSafeZone = false;

	bool bDropForce = false;
	if (pItem->isFlag(Effect::EFFECT_CLASS_DROP_FORCE ) )
	{
		pItem->removeFlag(Effect::EFFECT_CLASS_DROP_FORCE);
		bDropForce = true;
	}
	pt     = findSuitablePositionForItem(this, cx, cy, bAllowCreature, bAllowSafeZone, bDropForce);

	// ���� ��ġ�� ã�Ƴ� ����
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

				// ������ ������� ��ü�� ���� ��������.
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

				// ������ ������� ��ü�� ���� ��������.
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

				// ������ ������� ��ü�� ���� ��������.
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

				isFlag = g_pFlagManager->isFlagPole(pMonsterCorpse);

				// ������ ������� ��ü�� ���� ��������.
				if (isMasterLair())
				{
					MonsterType_t mt = pMonsterCorpse->getMonsterType();
					const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo(mt);
					Assert(pMonsterInfo!=NULL);

					// ������ ��ü�� ������ �� ���� ��������.
					if (pMonsterInfo->isMaster())
					{
						// �������� ��� �� ���� �������� �����̴�. * 10
						DelayTime = DELAY_MASTER_LAIR_DECAY_MASTER_CORPSE * 10;
					}
					else
					{
						DelayTime = DELAY_MASTER_LAIR_DECAY_CORPSE;
					}
				}
				else DelayTime = 600;

				sendRelicEffect(pMonsterCorpse, this, pt.x, pt.y);

				// �̰� �ӽô�. -_-;
				// ���� item���� zone��ǥ�� ����� �ʴµ�
				// Ư���� ���������뿡�� �ʿ��ϱ� ������..
				pMonsterCorpse->setX(pt.x);
				pMonsterCorpse->setY(pt.y);
				pMonsterCorpse->setZone(this);

				isShrine = pMonsterCorpse->isShrine() && !g_pFlagManager->isFlagPole(pMonsterCorpse);

				// Shrine�� ���� �̴ϸʿ� �����ش�.
				if (isShrine)
				{
					NPCInfo* pNPCInfo = new NPCInfo();
					pNPCInfo->setName(pMonsterCorpse->getName());
					pNPCInfo->setNPCID(pMonsterCorpse->getMonsterType());
					pNPCInfo->setX(pt.x);
					pNPCInfo->setY(pt.y);

					addNPCInfo(pNPCInfo);
				}
			}
			else
			{
				Assert(false);
			}

			// �������� ������� ���� ��ü���� ������ �ð��� ���δ�.
			Corpse* pCorpse = dynamic_cast<Corpse*>(pItem);
			if (pCorpse->getTreasureCount() == 0)
			{
				DelayTime = DelayTime/10;
			}
			// Relic�� ���쿡�� �ð��� ������ ���� �������� �������� �ʴ´�.
			if (!isShrine && !isFlag
				&& !pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE)
			    && !pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE)
			    && !pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_GUARD)
			    && !pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_HOLY)
				&& pCorpse->getTreasureCount() < 200 )
			{
				// ������ ������ delay
				if (decayTurn!=0) DelayTime = decayTurn;

				// �ٴڿ� �������� �������� ���� �ð��� ������ �������� �ȴ�.
				EffectDecayCorpse* pEffectDecayCorpse = new EffectDecayCorpse(this, pt.x, pt.y, (Corpse*)pItem, DelayTime);
//				pEffectDecayCorpse->setNextTime(999999);
				m_ObjectRegistry.registerObject(pEffectDecayCorpse);
				addEffect(pEffectDecayCorpse);
			}
			else
			{
				// ������ ���쿣 block�Ǹ� �ȵȴ�.
				if (!isFlag )
				{
					// ���� �������� ������(��ü)������
					// Block�� �Ǿ��� �Ѵ�.
					Tile& rTile = getTile(pt.x, pt.y);

					rTile.setBlocked(Creature::MOVE_MODE_WALKING);
					rTile.setBlocked(Creature::MOVE_MODE_BURROWING);

					// ���� �������� ������ �����Ѵ�.
					m_RelicTableOID = pCorpse->getObjectID();
					m_RelicTableX = pt.x;
					m_RelicTableY = pt.y;

					//cout << "Relic�� ���쿡�� ��ü�� �������� �ʽ��ϴ�" << endl;
				}
			}
		}
		else
		{
			GCDropItemToZone gcDropItemToZone;
			makeGCDropItemToZone(&gcDropItemToZone, pItem, pt.x, pt.y);
			gcDropItemToZone.setDropPetOID(DropPetOID);

			broadcastPacket(pt.x, pt.y, &gcDropItemToZone);

			// ���ͻ���Ŭ�� �ð��� ������ �������� �ʴ´�.
			if (IClass == Item::ITEM_CLASS_MOTORCYCLE)
			{
				// transport�� ���츦 �����ؼ� üũ�����ؾ��Ѵ�.
				MotorcycleBox* pMotorcycleBox = g_pParkingCenter->getMotorcycleBox(pItem->getItemID());

				if (pMotorcycleBox!=NULL)
				{
					Motorcycle* pMotorcycle = pMotorcycleBox->getMotorcycle();
					Assert(pMotorcycle!=NULL);

					// ������ ���� ����ȭ. by sigi. 2002.5.15
					char pField[80];
					sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d",
									STORAGE_ZONE, getZoneID(), (int)pt.x, (int)pt.y);

					pMotorcycle->tinysave(pField);

					pMotorcycleBox->setZone(this);
					pMotorcycleBox->setX(pt.x);
					pMotorcycleBox->setY(pt.y);

					pMotorcycleBox->setTransport(false);
				}
			}
			else if (isRelicItem(IClass ))
			{
				// relic�� �������� �ʴ´�.
				addEffectRelicPosition(pItem, getZoneID(), pt);
				char pField[80];
				sprintf(pField, "OwnerID='', Storage=%d, StorageID=%u, X=%d, Y=%d", STORAGE_ZONE, getZoneID(), pt.x, pt.y);
				pItem->tinysave(pField);
			}
			else
			{
				// 2002.10.30 ��ȫâ
				// ������ ���� �ð��� ���� 10�п��� 3������ ���δ�.
				// Turn_t DelayTime = 6000;
				Turn_t DelayTime = 1800;

				// ������ ������� �������� ���� ��������.
				if (isMasterLair())
				{
					DelayTime = DELAY_MASTER_LAIR_DECAY_ITEM;
				}

				if (!pItem->isFlagItem() && IClass != Item::ITEM_CLASS_SWEEPER )
				{
					// ������ ������ delay
					if (decayTurn!=0) DelayTime = decayTurn;

					// �ٴڿ� �������� �������� ���� �ð��� ������ �������� �ȴ�.
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
	throw(Error)
{
    map<ObjectID_t, Item*>::const_iterator iItem = m_Items.find(id);

	if (iItem != m_Items.end())
	{
		return iItem->second;
	}

	return NULL;
}


//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void Zone::addEffect(Effect* pEffect)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pEffect != NULL);

	m_pEffectManager->addEffect(pEffect);

	__END_CATCH
}

void Zone::deleteEffect(ObjectID_t id)
	throw(Error)
{
	__BEGIN_TRY

	m_pEffectManager->deleteEffect(id);

	__END_CATCH
}

Effect* Zone::findEffect(Effect::EffectClass eid)
	throw(Error)
{
	__BEGIN_TRY

	return m_pEffectManager->findEffect(eid);

	__END_CATCH
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void Zone::addEffect_LOCKING(Effect* pEffect)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pEffect != NULL);

	__ENTER_CRITICAL_SECTION(m_MutexEffect)

	m_pLockedEffectManager->addEffect(pEffect);

	__LEAVE_CRITICAL_SECTION(m_MutexEffect)

	__END_CATCH
}

void Zone::deleteEffect_LOCKING(ObjectID_t id)
	throw(Error)
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
	throw()//NoSuchElementException, Error)
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
	throw(NoSuchElementException, Error)
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
	throw(Error)
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
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_DELETE_CREATURE")

	try
	{
		Assert(pCreature->getX() == x && pCreature->getY() == y);

		// �ش��Ǵ� CreatureManager ���� ũ��ó�� �����Ѵ�.
		if (pCreature->isPC())
		{
			m_pPCManager->deleteCreature(pCreature->getObjectID());


			// ��Ƽ �ʴ����̶��� PartyInviteInfo�� �������ش�.
			m_pPartyInviteInfoManager->cancelInvite(pCreature);

			// ��Ƽ�� ���ԵǾ� �־��ٸ� ���� ��Ƽ���� ������ �ش�.
			uint PartyID = pCreature->getPartyID();
			if (PartyID != 0)
			{
				m_pLocalPartyManager->deletePartyMember(PartyID, pCreature);
			}

			// Ʈ���̵� ���̾��ٸ� Ʈ���̵� ���� ������ �������ش�.
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

		// Ÿ�Ͽ��� ũ��ó�� �����Ѵ�.
		try {
			getTile(x, y).deleteCreature(pCreature->getObjectID());
		} catch (NoSuchElementException& nsee) {
			// by sigi. 2002.12.10
			// Playerĳ���Ͱ� ������..
			// [1] PCManager::killCreature()���� tile������ ������ ��ǥ�� �����ϰ�
			// [2] EventResurrect���� IncomingPlayer�� ������.. �ű⼭ ������ Zone�� ����µ�..
			// �� �� ����.. ���̿��� ���� ZonePlayerManager�� �ִ� ���� Pay���������ɷ� ���ؼ�
			// transport�Ǹ�.. tile���� �������� �Ҷ� ������ ������..�� ��������.
			// �ϴ�, �� �κ�(ZPM::payüũ)������ GPS_NORMAL�� ���츸 �ϵ��� �ϰ�����.
			// �̰͵� �����Ҹ��ϴٰ� �������Ƿ�.. �ϴ� �α׸� ������.
			filelog("zoneDeleteCreatureError.log", "%s", nsee.toString().c_str());
		}

		// �ֺ��� PC�鿡�� ũ��ó�� �������ٴ� ������ ���ε�ĳ��Ʈ�Ѵ�.
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
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_DELETE_OBJECT")

	//--------------------------------------------------
	// ������ ��ü�� �����Ѵ�.
	//--------------------------------------------------
	getTile(x, y).deleteObject(pObject->getObjectID());

	//--------------------------------------------------
	// �ֺ��� PC�鿡�� ��ü�� �������ٴ� ������ ���ε�ĳ��Ʈ�Ѵ�.
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
	throw(NoSuchElementException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_DELETE_ITEM")

	deleteFromItemList(pObject->getObjectID());

	//--------------------------------------------------
	// ������ ��ü�� �����Ѵ�.
	//--------------------------------------------------
	getTile(x, y).deleteItem();


	if (pObject->getObjectClass() == Object::OBJECT_CLASS_ITEM )
	{
		// ���� �������� ���� Block �� �����ؾ� �Ѵ�.
		Item* pItem = dynamic_cast<Item*>(pObject);
		Assert(pItem != NULL);
		if (pItem->getItemClass() == Item::ITEM_CLASS_CORPSE
			&& pItem->getItemType() == MONSTER_CORPSE )
		{
			MonsterCorpse* pCorpse = dynamic_cast<MonsterCorpse*>(pItem);
			Assert(pCorpse != NULL);

			if (pCorpse->isFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE)
			  || pCorpse->isFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE)
			  || pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_GUARD)
			  || pCorpse->isFlag(Effect::EFFECT_CLASS_SHRINE_HOLY))
			{
				Tile& rTile = getTile(x, y);

				// ���� ������
				rTile.clearBlocked(Creature::MOVE_MODE_WALKING);
				rTile.clearBlocked(Creature::MOVE_MODE_BURROWING);
			}
		}

		if (isRelicItem(pItem ) )
		{
			deleteEffectRelicPosition(pItem);
		}
	}

	//--------------------------------------------------
	// �ֺ��� PC�鿡�� ��ü�� �������ٴ� ������ ���ε�ĳ��Ʈ�Ѵ�.
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
// Ư�� ���� �����ϴ�, owner�� ������ ���� PC ���� ������ ��Ŷ�� �����Ѵ�.
//
//--------------------------------------------------------------------------------
void Zone::broadcastPacket(Packet* pPacket, Creature* owner)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_PCMANAGER")
	m_pPCManager->broadcastPacket(pPacket, owner);
	__END_PROFILE_ZONE("Z_BC_PCMANAGER")

	__END_CATCH
}

void Zone::broadcastDarkLightPacket(Packet* pPacket1, Packet* pPacket2, Creature* owner)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_DARKLIGHT")
	m_pPCManager->broadcastDarkLightPacket(pPacket1,  pPacket2, owner);
	__END_PROFILE_ZONE("Z_BC_DARKLIGHT")

	__END_CATCH
}

//--------------------------------------------------------------------
//
// ä���� ���ε�ĳ���� �ϴ� �Լ��̴�. ���δٸ� ���������� �� �� ����.-
// �����̾ ������ ��Ŷ�� isVampire�� True�� ���ƿ´�.
//
//--------------------------------------------------------------------
void Zone::broadcastSayPacket(ZoneCoord_t cx, ZoneCoord_t cy, Packet* pPacket, Creature* owner, bool isVampire)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_SAY")

	ZoneCoord_t ix = 0;
	ZoneCoord_t iy = 0;
	ZoneCoord_t endx = 0;
	ZoneCoord_t endy = 0;

//#ifdef __USE_ENCRYPTER__
//	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//	outputStream.setEncryptCode(m_EncryptCode);
//#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//#endif
//	pPacket->writeHeaderNBody(outputStream);

	//-------------------------------------------------------------------
	// ���� ���� �ʱ�ȭ..
	//
	// Plus ������ ���� ���� Range ��ŭ �� ���� �ش�..
	// ���� ������ ������ ȿ�������� �����ֱ� �����̴�.
	//
	// *NOTE
	// - ����ȭ�� �Ѵٸ� VisionInfo�� PLUS_SIGHT���� ������ �߰��Ͽ� ����
	//-------------------------------------------------------------------
	endx = min(m_Width - 1, cx + maxViewportWidth + 1);
	endy = min(m_Height - 1, cy + maxViewportLowerHeight  + 1);

	for (ix =  max(0, cx - maxViewportWidth - 1); ix <= endx ; ix++)
	{
		for (iy = max(0, cy - maxViewportUpperHeight - 1); iy <= endy ; iy++)
		{
			Tile& rTile = m_pTiles[ix][iy];	// by sigi. 2002.5.8

			// Ÿ�Ͽ� ũ��ó�� �ִ� ���쿡��
			if (rTile.hasCreature())
			{
				const list<Object*> & objectList = rTile.getObjectList();

				for (list<Object*>::const_iterator itr = objectList.begin() ;
					itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE;
					itr++)
				{
					Creature* pCreature = dynamic_cast<Creature*>(*itr);
					Assert(pCreature != NULL);

					// PC�̸鼭, owner�� �ƴϸ鼭, (x,y)�� �� �� �ִ� ����
					if ((pCreature->isPC() && pCreature != owner && pCreature->getVisionState(cx,cy) >= IN_SIGHT) || (pCreature->isPC() && pCreature != owner))
					{
						// ���� �ִ� ���� �� ���� �ϸ� �Ⱥ��� �ִµ�.. ���� �ϸ� Unborrowing ���Ѿ� �Ǵµ�.
						// �����̾ ������ ��Ŷ�� isVampire�� True�� ���ƿ´�.
						if (owner != NULL)
						{

							// Creature ���� ObservingEye ����Ʈ�� ������ ����Ʈ�� �����´�.
							EffectObservingEye* pEffectObservingEye = NULL;
							if (pCreature->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
							{
								pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pCreature->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE ));
								//Assert(pEffectObservingEye != NULL);
							}

							if (!owner->isFlag(Effect::EFFECT_CLASS_GHOST)
								&& (!owner->isFlag(Effect::EFFECT_CLASS_HIDE) || pCreature->isVampire() || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )// || (pEffectRevealer != NULL && pEffectRevealer->canSeeHide(owner) ) )
								&& (!owner->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) || pCreature->isVampire() || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(owner) ) )
								&& (!owner->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) ) // || (pEffectRevealer != NULL && pEffectRevealer->canSeeSniping(owner) ) )
								&& ((isVampire && pCreature->isVampire()) || (!isVampire && pCreature->isSlayer()) || pCreature->isOusters())
								)
							{
                                pCreature->getPlayer()->sendPacket(pPacket);
//								pCreature->getPlayer()->sendStream(&outputStream);
							}
						}
						else
						{
                            pCreature->getPlayer()->sendPacket(pPacket);
//							pCreature->getPlayer()->sendStream(&outputStream);
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
// (x,y) �� ������ �� �� �ִ�, owner�� ������ ���� PC �鿡�� ��Ŷ�� ���ε�ĳ��Ʈ�Ѵ�.
//
// *CAUTION*
//
// unsigned char �� ZoneCoord_t �� ������ ��, overflow �� underflow �� ������ ��
//
//--------------------------------------------------------------------------------
void Zone::broadcastPacket(ZoneCoord_t cx, ZoneCoord_t cy, Packet* pPacket, Creature* owner, bool Plus, Range_t Range)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_NORMAL")

//#ifdef __USE_ENCRYPTER__
////	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
////	outputStream.setEncryptCode(m_EncryptCode);
//#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//#endif
////	pPacket->writeHeaderNBody(outputStream);

	ZoneCoord_t ix = 0;
	ZoneCoord_t iy = 0;
	ZoneCoord_t endx = 0;
	ZoneCoord_t endy = 0;

	//-------------------------------------------------------------------
	// ���� ���� �ʱ�ȭ..
	//
	// Plus ������ ���� ���� Range ��ŭ �� ���� �ش�..
	// ���� ������ ������ ȿ�������� �����ֱ� �����̴�.
	//
	// *NOTE
	// - ����ȭ�� �Ѵٸ� VisionInfo�� PLUS_SIGHT���� ������ �߰��Ͽ� ����
	//-------------------------------------------------------------------
	endx = min(m_Width - 1, cx + maxViewportWidth + 1 + Range);
	endy = min(m_Height - 1, cy + maxViewportLowerHeight  + 1 + Range);

	for (ix =  max(0, cx - maxViewportWidth - 1 - Range); ix <= endx ; ix++)
	{
		for (iy = max(0, cy - maxViewportUpperHeight - 1 -  Range); iy <= endy ; iy++)
		{
			// (ix,iy)���� (cx,cy)�� �� �� ����
			if (VisionInfoManager::getVisionState(ix, iy, cx, cy ) == OUT_OF_SIGHT && !Plus ) continue;
			Tile& rTile = m_pTiles[ix][iy];	// by sigi.2002.5.8

			// Ÿ�Ͽ� ũ��ó�� �ִ� ���쿡��
			if (rTile.hasCreature())
			{
				const list<Object*> & objectList = rTile.getObjectList();

				for (list<Object*>::const_iterator itr = objectList.begin() ;
					itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE;
					itr++)
				{
					Creature* pCreature = dynamic_cast<Creature*>(*itr);
					Assert(pCreature != NULL);

					// by sigi. 2002.5.14
					if (pCreature->isPC() && pCreature != owner )
						// ������ üũ�ߴ�. by Sequoia
//						&& (pCreature->getVisionState(cx,cy) >= IN_SIGHT || Plus))
					{
						// ���� �ִ� ���� �� ���� �ϸ� �Ⱥ��� �ִµ�.. ���� �ϸ� Unborrowing ���Ѿ� �Ǵµ�.
						if (owner != NULL)
						{
							// canSee �Լ��� ��ü. by bezz 2003.05.29
							if (canSee(pCreature, owner ) )
							{
								pCreature->getPlayer()->sendPacket(pPacket);
								//pCreature->getPlayer()->sendStream(&outputStream);
							}
						}
						else
						{
							pCreature->getPlayer()->sendPacket(pPacket);
							//pCreature->getPlayer()->sendStream(&outputStream);
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
	throw(ProtocolException, Error)
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
// ���ڸ����� sight�� ������ ����. Add&Delete packet�� ������.
//
//--------------------------------------------------------------------------------
void Zone::updateScan (Creature* pPC, Sight_t oldSight, Sight_t newSight)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	if (pPC == NULL || pPC->isPC() == false) return;
	//Assert(pPC != NULL);
	//Assert(pPC->isPC());

	__BEGIN_PROFILE_ZONE("Z_UPDATESCAN")

	// ���� sight ���ϴ� �� �Ű� �� ����.
/*	Coord_t cx = pPC->getX(), cy = pPC->getY();

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer);

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++)
		{
			VisionState oldVS = pPC->getVisionState(ix, iy, oldSight);
			VisionState newVS = pPC->getVisionState(ix, iy, newSight);

			const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

			for (list<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() ; itr++)
			{

				Assert(*itr != NULL);

				// �Ⱥ����ٰ� ���̴� ����..
				// ADD~~
				if (oldVS == OUT_OF_SIGHT && newVS != OUT_OF_SIGHT)
				{
					//--------------------------------------------------------------------------------
					// �� ��ü�� OBJECT CLASS�� ������ ������ GCAddXXX ��Ŷ�� �����
					// owner ���� �����Ѵ�.
					// *NOTES*
					// ���� ���� Ȯ���� ���� ��ü CLASS �� case �պκп� ���;� �Ѵ�.
					//--------------------------------------------------------------------------------
					switch ((*itr)->getObjectClass())
					{
						////////////////////////////////////////////////////////////
						////////////////////////////////////////////////////////////
						case Object::OBJECT_CLASS_CREATURE:
							{
								//--------------------------------------------------------------------------------
								// PC�� ���� pPacket�� �����ؾ� �ϸ�, !PC�� ���쿡�� ������ �ʿ䰡 ����.
								// ���� ���� ũ��ó�� ������ owner���� �����ؾ� �Ѵ�.
								//--------------------------------------------------------------------------------
								Creature* pCreature = dynamic_cast<Creature*>(*itr);
								Assert(pCreature != NULL);

								// �ڱ� �ڽ��� ������ ���� �ʿ䰡 ����.
								if (pCreature == pPC) continue;

								switch (pCreature->getCreatureClass())
								{
									case Creature::CREATURE_CLASS_MONSTER :
										{
											Monster* pMonster = dynamic_cast<Monster*>(pCreature);

											// by sigi
											Packet* pAddMonsterPacket = createMonsterAddPacket(pMonster, pPC);

											if (pAddMonsterPacket!=NULL)
											{
												pPlayer->sendPacket(pAddMonsterPacket);

												delete pAddMonsterPacket;
											}
										}
										break;


									case Creature::CREATURE_CLASS_SLAYER:
										{
											// PC �� Revealer ����Ʈ�� ������ �ִٸ� ����Ʈ�� �����´�.
//											EffectRevealer* pEffectRevealer = NULL;
//											if (pPC->isFlag(Effect::EFFECT_CLASS_REVEALER ) )
//											{
//												pEffectRevealer = dynamic_cast<EffectRevealer*>(pPC->findEffect(Effect::EFFECT_CLASS_REVEALER ));
//												Assert(pEffectRevealer);
//											}

											if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)
												&& (!pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)
													|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) ))
//												|| (pEffectRevealer != NULL && pEffectRevealer->canSeeSniping(pCreature) ) )
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
											// PC �� Revealer ����Ʈ�� ������ �ִٸ� ����Ʈ�� �����´�.
//											EffectRevealer* pEffectRevealer = NULL;
//											if (pPC->isFlag(Effect::EFFECT_CLASS_REVEALER ) )
//											{
//												pEffectRevealer = dynamic_cast<EffectRevealer*>(pPC->findEffect(Effect::EFFECT_CLASS_REVEALER ));
//												Assert(pEffectRevealer);
//											}

											// PC �� ObservingEye ����Ʈ�� ������ �ִٸ� ����Ʈ�� �����´�.
											EffectObservingEye* pEffectObservingEye = NULL;
											if (pPC->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
											{
												pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE ));
												//Assert(pEffectObservingEye != NULL);
											}

											//
											// hide�� invisibility�� ���ÿ� ������ �� ���´ٴ� �����Ͽ�..
											//
											if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST))
											{
												if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE))
												{
													if (pPC->isVampire() || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )
	//													|| (pEffectRevealer != NULL && pEffectRevealer->canSeeHide(pCreature ) ) )
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
													// pCreature�� invisibility����..
													else if (pPC->isVampire() || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY)
															|| (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(pCreature ) ) )
													{
														// FIXME
														// ������������ ��� ������ ������ ��..
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
											if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST) )
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
						// Ÿ�� ���� �������� ���� ����
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

												sendRelicEffect(pMonsterCorpse, pPlayer);
											}
											break;
									}//switch
								}
								// Mine�� Install�Ǿ� �ִ� ����, DetectMine�� ������ GCAddNewItemToZone Packet�� ������ �ʴ´�.
								// �� �� �� ����.
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

									// sanctuary�� �߽���ǥ�� ���츸 packet�� ������.
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
								// Broadcasting Effect ���� üũ �߰� by Sequoia 2003.3.31
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
						// Ÿ�� ���� ���ֹ��� ���� ����
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_OBSTACLE :
							{
							}
							break;

						//--------------------------------------------------------------------------------
						// Ÿ�� ���� ��Ż�� ���� ����
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_PORTAL :
							{
							}
							break;

						default :
							throw Error("invalid object class");

					}//switch ((*itr)->getObjectClass())
				} // if
				// �����ٰ� �Ⱥ��̴� ����.
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
// (x1,y1) (x2,y2) �� ������ �� �� �ִ�,
// owner�� ������ ���� PC �鿡�� ��Ŷ�� ���ε�ĳ��Ʈ�Ѵ�.
// Tile ���� ��ų broadcastPacket�̴�.
// *CAUTION*
// unsigned char �� ZoneCoord_t �� ������ ��, overflow �� underflow �� ������ ��
//--------------------------------------------------------------------------------
list<Creature*> Zone::broadcastSkillPacket(ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2,
		Packet* pPacket ,list<Creature*> creatureList, bool bConcernDarkness)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

//#ifdef __USE_ENCRYPTER__
//	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//	outputStream.setEncryptCode(m_EncryptCode);
//#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//#endif
////	pPacket->writeHeaderNBody(outputStream);

	list<Creature*> cList;

	__BEGIN_PROFILE_ZONE("Z_BC_SKILL")

	ZoneCoord_t ix = 0;
	ZoneCoord_t iy = 0;
	ZoneCoord_t endx = 0;
	ZoneCoord_t endy = 0;

	//-------------------------------------------------------------------
	// ���� ���� �ʱ�ȭ..
	//
	// Plus ������ ���� ���� Range ��ŭ �� ���� �ش�..
	// ���� ������ ������ ȿ�������� �����ֱ� �����̴�.
	//
	// *NOTE
	//
	// - ����ȭ�� �Ѵٸ� VisionInfo�� PLUS_SIGHT���� ������ �߰��Ͽ� ����
	//
	//-------------------------------------------------------------------
	endx = min(m_Width - 1, x1 + maxViewportWidth + 1);
	endy = min(m_Height- 1, y1 + maxViewportLowerHeight + 1);

	for (ix = max(0, x1 - maxViewportWidth - 1); ix <= endx ; ix++)
	{
		for (iy = max(0, y1 - maxViewportUpperHeight - 1); iy <= endy ; iy++)
		{
			Tile& rTile = m_pTiles[ix][iy];	// by sigi.2002.5.8

			// Ÿ�Ͽ� ũ��ó�� �ִ� ���쿡��
			if (rTile.hasCreature())
			{
				const list<Object*> & objectList = rTile.getObjectList();

				for (list<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++)
				{

					Creature* pCreature = dynamic_cast<Creature*>(*itr);
					Assert(pCreature != NULL);

					// PC�̸鼭, creature list�� ������ �����鼭 (x,y)�� �� �� �ִ� ����
					if (pCreature->isPC())
					{
						// �� ��Ŷ�� �߻���Ų ���������� üũ�Ѵ�.
						bool belong = false;
						for (list<Creature*>::const_iterator itr = creatureList.begin() ; itr != creatureList.end() ; itr++)
						{
							if (pCreature == *itr)
							{
								belong = true;
								break;
							}
						}

						if (!belong && pCreature->getVisionState(x1,y1) >= IN_SIGHT && pCreature->getVisionState(x2, y2) >= IN_SIGHT)
						{
							// ���� �ִ� ���� �� ���̸鼭 ��ų�� �� ������ ����.. ������ HIDEüũ�� ���� �ʴ´�.
							Player* pPlayer = pCreature->getPlayer();
                            pPlayer->sendPacket(pPacket);
//							pPlayer->sendStream(&outputStream);
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
// (x,y) �� ������ �� �� �ִ�, creatureList �� �Ҽӵ� ũ��ó�� ������ ���� PC �鿡��
// ��Ŷ�� ���ε�ĳ��Ʈ�Ѵ�.
//
// *NOTE*
// ���� Tile Magic�� ���� Plus �� True�� �ΰ� �Ǹ� Plus ������ True�� ����..
// Magic ������ ������ ��ŭ �� ������ Ȯ���Ͽ� �����ش�.. ���� ������ ©���� �ʰ�,
// ȿ�������� �����ֱ� �����̴�.
//
// *CAUTION*
//
// unsigned char �� ZoneCoord_t �� ������ ��, overflow �� underflow �� ������ ��
//////////////////////////////////////////////////////////////////////////////
void Zone::broadcastPacket(ZoneCoord_t cx, ZoneCoord_t cy, Packet* pPacket, const list<Creature *> & creatureList, bool Plus, Range_t Range)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_EXCLIST")

//#ifdef __USE_ENCRYPTER__
//	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//	outputStream.setEncryptCode(m_EncryptCode);
//#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//#endif
//	pPacket->writeHeaderNBody(outputStream);

	ZoneCoord_t ix = 0;
	ZoneCoord_t iy = 0;
	ZoneCoord_t endx = 0;
	ZoneCoord_t endy = 0;

	//////////////////////////////////////////////////////////////////////////////
	// ���� ���� �ʱ�ȭ..
	//
	// Plus ������ ���� ���� Range ��ŭ �� ���� �ش�..
	// ���� ������ ������ ȿ�������� �����ֱ� �����̴�.
	//
	// *NOTE
	// - ����ȭ�� �Ѵٸ� VisionInfo�� PLUS_SIGHT���� ������ �߰��Ͽ� ����
	//////////////////////////////////////////////////////////////////////////////
	endx = min(m_Width - 1, cx + maxViewportWidth + 1 + Range);
	endy = min(m_Height - 1, cy + maxViewportLowerHeight  + 1 + Range);

	for (ix =  max(0, cx - maxViewportWidth - 1 - Range); ix <= endx ; ix++)
	{
		for (iy = max(0, cy - maxViewportUpperHeight - 1 -  Range); iy <= endy ; iy++)
		{
			if (VisionInfoManager::getVisionState(ix, iy, cx, cy ) == OUT_OF_SIGHT || Plus ) continue;
			Tile& rTile = m_pTiles[ix][iy]; // by sigi. 2002.5.8

			// Ÿ�Ͽ� ũ��ó�� �ִ� ���쿡��
			if (rTile.hasCreature())
			{
				const list<Object*> & objectList = rTile.getObjectList();
				list<Object*>::const_iterator itr = objectList.begin();

                for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++)
				{
					Creature* pCreature = dynamic_cast<Creature*>(*itr);
					Assert(pCreature != NULL);

					// PC�̸鼭, creatureList�� �Ҽӵ����� �����鼭, (x,y)�� �� �� �ִ� ����
					if (pCreature->isPC())
					{
						bool belong = false;
						for (list<Creature*>::const_iterator itr = creatureList.begin() ; itr != creatureList.end() ; itr++)
						{
							if (pCreature == *itr)
							{
								belong = true;
								break;
							}
						} // for

//						if ((!belong && pCreature->getVisionState(cx,cy) >= IN_SIGHT) ||(!belong && Plus))
						if (!belong )
						{
                            pCreature->getPlayer()->sendPacket(pPacket);
//							pCreature->getPlayer()->sendStream(&outputStream);
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
// (x,y)���� �þ� �����ȿ� �����ϴ� ���� ��ü���� ������ �޾ƿ´�.
//////////////////////////////////////////////////////////////////////////////
void Zone::scan (Creature* pPC, ZoneCoord_t cx, ZoneCoord_t cy, Packet* pPacket)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_SCAN")

//#ifdef __USE_ENCRYPTER__
//	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//	outputStream.setEncryptCode(m_EncryptCode);
//#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + pPacket->getPacketSize() + 2);
//#endif
//	pPacket->writeHeaderNBody(outputStream);

	Assert(pPC->isPC());

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer);

	for (ZoneCoord_t ix = max(0, cx - maxViewportWidth - 1), endx = min(m_Width - 1, cx + maxViewportWidth + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, cy - maxViewportUpperHeight - 1), endy = min(m_Height - 1, cy + maxViewportLowerHeight + 1) ; iy <= endy ; iy++)
		{
//			bool bCanSeeThere = (pPC->getVisionState(ix, iy) >= IN_SIGHT);	// ���� �þ߸����� �� �� �ֳ�?
			if (pPC->getVisionState(ix, iy ) == OUT_OF_SIGHT ) continue;

			const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

			for (list<Object*>::const_iterator itr = objectList.begin() ; itr != objectList.end() ; itr++)
			{
				Assert(*itr != NULL);

				//--------------------------------------------------------------------------------
				//
				// �� ��ü�� OBJECT CLASS�� ������ ������ GCAddXXX ��Ŷ�� �����
				// owner ���� �����Ѵ�.
				//
				// *NOTES*
				//
				// ���� ���� Ȯ���� ���� ��ü CLASS �� case �պκп� ���;� �Ѵ�.
				//
				//--------------------------------------------------------------------------------
				switch ((*itr)->getObjectClass())
				{
					//--------------------------------------------------------------------------------
					// Ÿ�� ���� ũ��ó�� ���� ����
					//--------------------------------------------------------------------------------
					case Object::OBJECT_CLASS_CREATURE :
						{
							//--------------------------------------------------------------------------------
							// PC�� ���� pPacket�� �����ؾ� �ϸ�, !PC�� ���쿡�� ������ �ʿ䰡 ����.
							// ���� ���� ũ��ó�� ������ owner���� �����ؾ� �Ѵ�.
							//--------------------------------------------------------------------------------
							Creature* pCreature = dynamic_cast<Creature*>(*itr);
							Assert(pCreature != NULL);

							if (pCreature == pPC)	// �ڱ� �ڽ��� ������ ���� �ʿ䰡 ����.
								continue;

							// �Ⱥ��̸� ��
//							if (!canSee(pPC, pCreature ) ) continue;
							bool bCanSee = canSee(pPC, pCreature);

							switch (pCreature->getCreatureClass())
							{
								case Creature::CREATURE_CLASS_MONSTER :
									{
										Monster* pMonster = dynamic_cast<Monster*>(pCreature);
										if (bCanSee)
										{
											// by sigi
											Packet* pAddMonsterPacket = createMonsterAddPacket(pMonster, pPC);

											if (pAddMonsterPacket!=NULL)
											{
												pPlayer->sendPacket(pAddMonsterPacket);

												delete pAddMonsterPacket;
											}
										}

										//--------------------------------------------------------------------------------
										// �����Ͱ� PC �� �� �� �ִ� ����, PC �� �������� Enemy �� �����Ѵ�.
										//--------------------------------------------------------------------------------
										VisionState vs = pMonster->getVisionState(cx,cy);

										// Aggressive �������� ���쿡�� ������ �������ش�.
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
										// ���� �װ��� �� �� �ִٸ�(darkness�� �����Ͽ�)
										if (bCanSee)
										{
//											if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)
//												&& !pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) )
//													|| (pEffectRevealer != NULL && pEffectRevealer->canSeeSniping(pCreature ) ) )
//											{
												Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
												GCAddSlayer gcAddSlayer;
												makeGCAddSlayer(&gcAddSlayer, pSlayer);
												pPlayer->sendPacket(&gcAddSlayer);
//											}
										}

										// ����(�����̾�)�� ���� �� �� �ִٸ�
										if (pPacket && pCreature->getVisionState(cx, cy) >= IN_SIGHT)
										{
											Assert(pCreature->getPlayer() != NULL);
											// canSee �� ��ü. 2003.05.29 by bezz
											if (canSee(pCreature, pPC ) )
											{
                                                pCreature->getPlayer()->sendPacket(pPacket);
//												pCreature->getPlayer()->sendStream(&outputStream);
											}
										}
									}
									break;

								case Creature::CREATURE_CLASS_VAMPIRE :
									{
										if (bCanSee)
										{
											// PC�� ObservingEye ����Ʈ�� ������ �ִٸ� ����Ʈ�� �����´�.
//											EffectObservingEye* pEffectObservingEye = NULL;
//											if (pPC->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//											{
//												pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE ));
//												//Assert(pEffectObservingEye != NULL);
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
								//						|| (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(pCreature ) ) )
								//					)
								//				{
													Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
													GCAddVampire gcAddVampire;
													makeGCAddVampire(&gcAddVampire, pVampire);
													pPlayer->sendPacket(&gcAddVampire);
								//				}
											}
										}

										// ���밡 ���� �� �� �ִٸ�..
										// ������ vampire�̹Ƿ� �þ߸� �����ϴٸ� darkness�ʹ� ���谡 ����.
										// �����̾ �����϶� �������� �������� ���� �� ����...
										//
										// �ٵ� scan �Լ� Ư���� snipping ���带 ���� ���� �ʰ� �Ѿ ���� ����.
										// canSee�� ��ü
										if (pPacket && pCreature->getVisionState(cx, cy) >= IN_SIGHT && canSee(pCreature, pPC ))
										{
											Assert(pCreature->getPlayer() != NULL);
                                            pCreature->getPlayer()->sendPacket(pPacket);
//											pCreature->getPlayer()->sendStream(&outputStream);
										}
									}
									break;

								case Creature::CREATURE_CLASS_OUSTERS :
									{
										if (bCanSee)
										{
											// PC�� ObservingEye ����Ʈ�� ������ �ִٸ� ����Ʈ�� �����´�.
//											EffectObservingEye* pEffectObservingEye = NULL;
//											if (pPC->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//											{
//												pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE ));
//												//Assert(pEffectObservingEye != NULL);
//											}

//											if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST) )
//											{
												Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
												GCAddOusters gcAddOusters;
												makeGCAddOusters(&gcAddOusters, pOusters);
												pPlayer->sendPacket(&gcAddOusters);
//											}
										}

										if (pPacket && pCreature->getVisionState(cx, cy) >= IN_SIGHT && canSee(pCreature, pPC ) )
										{
											Assert(pCreature->getPlayer() != NULL);
                                            pCreature->getPlayer()->sendPacket(pPacket);
//											pCreature->getPlayer()->sendStream(&outputStream);
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
					// Ÿ�� ���� �������� ���� ����
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

												sendRelicEffect(pMonsterCorpse, pPlayer);
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
					// Ÿ�� ���� ����Ʈ�� ���� ����
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

									// sanctuary�� �߽���ǥ�� ���츸 packet�� ������.
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
								// Broadcasting Effect ���� üũ �߰� by Sequoia 2003.3.31
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
					// Ÿ�� ���� ���ֹ��� ���� ����
					//--------------------------------------------------------------------------------
					case Object::OBJECT_CLASS_OBSTACLE :
						{
							/*
							*/
						}
						break;

					//--------------------------------------------------------------------------------
					// Ÿ�� ���� ��Ż�� ���� ����
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
// �����Ͱ� ���� (x,y)�� ���� �����Ǿ��� ����, �þ� �����ȿ� �����ϴ� ���� PC�鿡��
// GCAddXXX ��Ŷ�� �����鼭, ���ÿ� �� PC �� �������� ������ �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void Zone::scanPC (Creature* pCreature)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_SCAN_PC")

	Monster* pMonster = NULL;

	Assert(pCreature != NULL);

	ZoneCoord_t cx = pCreature->getX();
	ZoneCoord_t cy = pCreature->getY();

	Packet*                pGCAddXXX = NULL;

	// ũ������ ������ ����, ��Ŷ�� �������д�.
	Creature::CreatureClass CClass = pCreature->getCreatureClass();

	bool isMonster = pCreature->isMonster();
//	bool isMonsterHide = false;
//	bool isMonsterInvisibility = false;

	if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		pMonster = dynamic_cast<Monster*>(pCreature);

		// by sigi
		pGCAddXXX = createMonsterAddPacket(pMonster, NULL);

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
			const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
			list<Object*>::const_iterator itr = objectList.begin();

			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE ; itr++)
			{
				if ((*itr)->getObjectClass() == Object::OBJECT_CLASS_CREATURE)
				{
					Creature* pPC = dynamic_cast<Creature*>(*itr);
					Assert(pPC != NULL);

					// PC �̸鼭, ũ��ó�� �� �� �ִ� ����
					if (pPC->isPC() && pPC->getVisionState(cx,cy) >= IN_SIGHT
						&& canSee(pPC, pCreature ))
//						&& !pPC->isFlag(Effect::EFFECT_CLASS_GHOST)
					{
						// Creature �� Revealer ����Ʈ�� ������ �ִٸ� ����Ʈ�� �����´�.
//						EffectRevealer* pEffectRevealer = NULL;
//						if (pCreature->isFlag(Effect::EFFECT_CLASS_REVEALER ) )
//						{
//							pEffectRevealer = dynamic_cast<EffectRevealer*>(pCreature->findEffect(Effect::EFFECT_CLASS_REVEALER ));
//							Assert(pEffectRevealer);
//						}

						// Creature �� ObservingEye ����Ʈ�� ������ �ִٸ� ����Ʈ�� �����´�.
//						EffectObservingEye* pEffectObservingEye = NULL;
//						if (pCreature->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//						{
//							pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pCreature->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE ));
//							//Assert(pEffectObservingEye != NULL);
//						}

						// �����Ͱ� ���������� ������ ���� �׷��� DETECT_HIDDEN�� INVISIBILITY�� üũ �Ѵ�.
//						if (pPC->isVampire() ||
//							((!isMonsterHide || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN))// || (pEffectRevealer != NULL && pEffectRevealer->canSeeHide(pMonster ) ) )
//							&& (!isMonsterInvisibility || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) ) || (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(pMonster ) ))
//							)
//						{
							pPC->getPlayer()->sendPacket(pGCAddXXX);
//						}

						if (isMonster )
						{
							// (cx,cy)�� �ִ� �����Ͱ� (ix,iy)�� �ִ� PC�� �� �� �ִ°�?
							VisionState vs = pMonster->getVisionState(ix,iy);
							if (vs >= IN_SIGHT && pMonster->getAlignment() == ALIGNMENT_AGGRESSIVE && canSee(pCreature, pPC ))
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
// P(x1,y1)���� Q(x2,y2)�� ���� �̵��� ũ��ó�� �ֺ� ������ �����ϴ� PC�鿡��
// ���ε�ĳ��Ʈ�ϴ� �޽����̴�.
// for Skill FlashSliding, ShadowWalk
//////////////////////////////////////////////////////////////////////////////
bool Zone::moveFastPC(Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	// �� �޽����� PC �� �������� �Ѵ�.
	Assert(pPC->isPC());

	// isAbleToMove �� �ٲ۴�. by bezz. 2002.12.28
	if (!isAbleToMove(pPC ) )
		return false;

/*	if (SiegeManager::Instance().isSiegeZone(m_ZoneID ) )
	{
		if (!isPassLine(this, pPC->getX(), pPC->getY(), x2, y2, true ) ) return false;
	}*/

	 // ������ ������ �ִ� ��������.. �������뿡 ��� �� ����.
	if (pPC->hasRelicItem())
	{
		return false;
	}

	if (pPC->isFlag(Effect::EFFECT_CLASS_HAS_FLAG) || pPC->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER))
		return false;

	if (m_ZoneID == 1410 || m_ZoneID == 1411 ) return false;

	Tile& rTile = getTile(x1, y1);

	if (rTile.getEffect(Effect::EFFECT_CLASS_ON_BRIDGE ) != NULL ) return false;

	// ������ ���������� ã�´�.
	// �����ο��� ������ ����..4�� �˻�
	Dir_t dir = calcDirection(x1, y1, x2, y2);

	// g_FastMoveSearchX, Y�� ã���� �ȴ�. by sigi. 2002.5.8
	int* searchX = g_FastMoveSearchX[dir];
	int* searchY = g_FastMoveSearchY[dir];

	// �� Ÿ������ Ȯ��.
	int i=0;
	for(i = 0; i< 4; i++)
	{
		int targetX = x2 + searchX[i], targetY = y2 + searchY[i];
		if (targetX >= 0 && targetX < m_Width && targetY >= 0 && targetY < m_Height &&
			!m_pTiles[targetX][targetY].isBlocked(pPC->getMoveMode()) && !m_pTiles[targetX][targetY].hasPortal() &&
			// Sanctuary �� �ɷ����� �ʾƾ� �Ѵ�. by Sequoia 2003.3.25
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
		return false;	// ��Ÿ���� ��ã�Ҵ�!
	}

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer);

	GCFastMove gcFastMove;
	gcFastMove.setObjectID(pPC->getObjectID());
	gcFastMove.setXY(x1, y1, x2, y2);
	gcFastMove.setSkillType(skillType);

#ifdef __USE_ENCRYPTER__
//	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + gcFastMove.getPacketSize() + 2);
//	outputStream.setEncryptCode(m_EncryptCode);
#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + gcFastMove.getPacketSize() + 2);
#endif
//	gcFastMove.writeHeaderNBody(outputStream);

//	pPlayer->sendStream(&outputStream);

	pPlayer->sendPacket(&gcFastMove);

	// ����Ʈ..
	dynamic_cast<PlayerCreature*>(pPC)->getGQuestManager()->fastMove();

	//////////////////////////////////////////////////////////////
	// move�� ����....
	// �̿����� GCDelete�� Add���� �������� �� �� �� �ִ�.

	// PC�� ��ǥ ����.
	pPC->setXYDir(x2, y2, dir);
	// ���� Ÿ�Ͽ��� ũ��ó�� �����Ѵ�.

	try {
		m_pTiles[x1][y1].deleteCreature(pPC->getObjectID());
	} catch (Error& e) {
		filelog("assertTile.txt", "moveFastPC : %s", e.toString().c_str());
		throw;
	}

	// �� Ÿ�Ͽ� ũ��ó�� �߰��Ѵ�.
	m_pTiles[x2][y2].addCreature(pPC);

	try {
		checkMine(this, pPC, x2, y2);
		checkTrap(this, pPC);
	} catch (Throwable & t ) {
		filelog("CheckMineBug.txt", "%s : %s", "moveFastPC", t.toString().c_str());
	}

	if (pPC->isFlag(Effect::EFFECT_CLASS_GHOST))
	{
//		return false;
	}


	//--------------------------------------------------------------------------------
	// GCAddSlayer/GCAddVampire ��Ŷ�� �������д�.
	// ������ ��å�� ���ϸ�, GCAdd ��Ŷ�� ������ ��ǥ�� �������� �Ѵ�.
	//--------------------------------------------------------------------------------
	Packet* pGCAddXXX = NULL;

	if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_SLAYER)
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
/*		GCAddSlayer* pGCAddSlayer = new GCAddSlayer(pSlayer->getSlayerInfo3());
		pGCAddSlayer->setEffectInfo(pSlayer->getEffectInfo());*/
		GCAddSlayer* pGCAddSlayer = new GCAddSlayer;
		makeGCAddSlayer(pGCAddSlayer, pSlayer);

		pGCAddXXX = pGCAddSlayer;
	}
	else if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_VAMPIRE)
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);

		// ��.. hide���¿��� ������ ���� ������..
		// �̷��� ����.
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
			makeGCAddVampire(pGCAddVampire, pVampire);

			pGCAddXXX = pGCAddVampire;
		}
	}
	else if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_OUSTERS)
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
//		GCAddOusters* pGCAddOusters = new GCAddOusters(pOusters->getOustersInfo3());
//		pGCAddOusters->setEffectInfo(pOusters->getEffectInfo());
		GCAddOusters* pGCAddOusters = new GCAddOusters;
		makeGCAddOusters(pGCAddOusters, pOusters);

		pGCAddXXX = pGCAddOusters;
	}

	//--------------------------------------------------------------------------------
	// GCDeleteObject ��Ŷ�� �������д�.
	//--------------------------------------------------------------------------------
	GCDeleteObject gcDeleteObject;
	gcDeleteObject.setObjectID(pPC->getObjectID());


	// �� �þ��� ������ ���Ѵ�.
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

	// ObservingEye ����Ʈ�� �����´�.
//	EffectObservingEye* pEffectObservingEye = NULL;
//	if (pPC->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//	{
//		pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE ));
//		//Assert(pEffectObservingEye != NULL);
//	}
//
	for (ZoneCoord_t ix = minX ; ix <= maxX ; ix++)
	{
		for (ZoneCoord_t iy = minY ; iy <= maxY ; iy++)
		{
			const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

			list<Object*>::const_iterator itr = objectList.begin();

			// visionInfo ������..
			// if - do~while()�� ���� ���� by sigi. 2002.5.8
			if (itr != objectList.end())
			{

				// ���� ��ǥ P(x1,y1)���� I(ix,iy)�� ��� ���̴°�?
//				VisionState prevVisionState = pVisionInfo->getVisionState(x1,y1,ix,iy);
				VisionState prevVisionState = VisionInfoManager::getVisionState(x1,y1,ix,iy);
				// ���� ��ǥ Q(x2,y2)���� I(ix,iy)�� ��� ���̴°�?
//				VisionState curVisionState = pVisionInfo->getVisionState(x2,y2,ix,iy);
				VisionState curVisionState = VisionInfoManager::getVisionState(x2,y2,ix,iy);

				do
				{
					Assert(*itr != NULL);

					//--------------------------------------------------------------------------------
					//
					// �� ��ü�� OBJECT CLASS�� ������ ������ GCAddXXX ��Ŷ�� �����
					// owner ���� �����Ѵ�.
					//
					// *NOTES*
					//
					// ���� ���� Ȯ���� ���� ��ü CLASS �� case �պκп� ���;� �Ѵ�.
					//
					//--------------------------------------------------------------------------------
					switch ((*itr)->getObjectClass())
					{
						//--------------------------------------------------------------------------------
						// Ÿ�� ���� ũ��ó�� ���� ����
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_CREATURE :
							{
								Creature* pCreature = dynamic_cast<Creature*>(*itr);
								Assert(pCreature != NULL);

								// �ڱ� �ڽ��� ������ ���� �ʿ䰡 ����.
								if (pCreature == pPC) continue;

								switch (pCreature->getCreatureClass())
								{

									case Creature::CREATURE_CLASS_MONSTER :
										{
											Monster* pMonster = dynamic_cast<Monster*>(pCreature);

											//--------------------------------------------------------------------------------
											//
											// ���� ��ǥ������ �� �����͸� �� �� ��������, ���� ��ǥ���� �� �����͸� ���� ��
											// ���� GCAddMonster ��Ŷ�� �����Ѵ�.
											//
											//--------------------------------------------------------------------------------
											if (prevVisionState == OUT_OF_SIGHT && curVisionState >= IN_SIGHT)
											{
												Packet* pAddMonsterPacket = createMonsterAddPacket(pMonster, pPC);

												if (pAddMonsterPacket!=NULL)
												{
													pPlayer->sendPacket(pAddMonsterPacket);
													delete pAddMonsterPacket;
												}
											}

											//--------------------------------------------------------------------------------
											// PC�� �������� �������� ������ �������ش�.
											//--------------------------------------------------------------------------------
											VisionState vs = pMonster->getVisionState(x2,y2);

											// Aggressive �����Ϳ��Ը� ������ ���Ͻ����ش�.
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
											// ���� ��ǥ������ ������ �ʴٰ�, �̹� ��ǥ���� ���� ���̰� �� ũ��ó��
											// GCAddXXX �� �޾ƿ´�. ���� ���� ���쿡�� �޾ƿ��� �ʴ´�.
											//--------------------------------------------------------------------------------
											if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT)
											{
												// ���� �̰� �������� ���¶��� ����Ʈ �Ǿ� �־��� �Ѵ�.
//												if (!pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)
//													|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) )
//													|| (pEffectRevealer != NULL && pEffectRevealer->canSeeSniping(pCreature ) ) )
												if (canSee(pPC, pCreature ) )
												{
													Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
//													GCAddSlayer gcAddSlayer(pSlayer->getSlayerInfo3());
//													gcAddSlayer.setEffectInfo(pSlayer->getEffectInfo());
													GCAddSlayer gcAddSlayer;
													makeGCAddSlayer(&gcAddSlayer, pSlayer);

													pPlayer->sendPacket(&gcAddSlayer);
												}

											}

											Assert(pCreature->getPlayer() != NULL);

											//--------------------------------------------------------------------------------
											//
											// Q(x2,y2)�� �� ũ��ó�� �þ� �簢���� ���迡 ��ġ�ϸ鼭, P(x1,y1)�� �簢���� �ܺ�,
											// �� ������ �ʴ� ���쿡�� GCAddXXX ��Ŷ�� �����Ѵ�. �̷��� ���� ������, PC
											// ũ��ó�� pCreature�� �þ� ���迡�� ���� �����̰� �Ǹ� ���� ������ GCAddXXX ��Ŷ��
											// �����߸� �Ѵ�.
											//
											// �����ϸ�,
											//
											// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX
											// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
											//
											//--------------------------------------------------------------------------------
											VisionState prevVS = pCreature->getVisionState(x1,y1);
											VisionState currVS = pCreature->getVisionState(x2,y2);

											// ������ �ʴ� ��������, ���� ������ ��ġ�� �ʰ� �ٷ�
											// �þ� ���� �������� �����´ٴ� ���� �Ұ����ϴ�.

											// canSee �� ��ü. by bezz 2003.05.29
											if (canSee(pCreature, pPC ) )
											{
												if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(pGCAddXXX);
													pCreature->getPlayer()->sendPacket(&gcFastMove);
													//pCreature->getPlayer()->sendStream(&outputStream);
												}
												else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(&gcFastMove);
													//pCreature->getPlayer()->sendStream(&outputStream);
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
											// ���� ��ǥ������ ������ �ʴٰ�, �̹� ��ǥ���� ���� ���̰� �� ũ��ó��
											// GCAddXXX �� �޾ƿ´�. �������� NEW_SIGHT �̰�, ���ݵ� NEW_SIGHT �̸�,
											// ���� �޾ƿ��� �ʴ´�.
											//--------------------------------------------------------------------------------
											if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT)
											{
												if (canSee(pPC, pCreature ) )
												{
													if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE))
													{
												//		if (pPC->isVampire() || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )
	//														|| (pEffectRevealer != NULL && pEffectRevealer->canSeeHide(pCreature ) ) )
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
															makeGCAddVampire(&gcAddVampire, pVampire);
															pPlayer->sendPacket(&gcAddVampire);
	//													}
														// pCreature�� invisibility����..
	//													else if (pPC->isVampire() || pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY)
	//															|| (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(pCreature ) ) )
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
											// Q(x2,y2)�� �� ũ��ó�� �þ� �簢���� ���迡 ��ġ�ϸ鼭, P(x1,y1)�� �簢���� �ܺ�,
											// �� ������ �ʴ� ���쿡�� GCAddXXX ��Ŷ�� �����Ѵ�. �̷��� ���� ������, PC
											// ũ��ó�� pCreature�� �þ� ���迡�� ���� �����̰� �Ǹ� ���� ������ GCAddXXX ��Ŷ��
											// �����߸� �Ѵ�.
											//
											// �����ϸ�,
											//
											// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX
											// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
											//
											//--------------------------------------------------------------------------------
											VisionState prevVS = pCreature->getVisionState(x1,y1);
											VisionState currVS = pCreature->getVisionState(x2,y2);

											// ������ �����̾��̹Ƿ� ���� darkness���´� ��������.
											// Hide�� ��������.
											// *NOTE
											// ���밡 �����̾����� �����̾ �������� ���������� üũ �ؾ� �Ѵ�.
//											if (!pPC->isSlayer() || !pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
											if (canSee(pCreature, pPC ) )
											{
												if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(pGCAddXXX);
													pCreature->getPlayer()->sendPacket(&gcFastMove);
													//pCreature->getPlayer()->sendStream(&outputStream);
												}
												else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(&gcFastMove);
													//pCreature->getPlayer()->sendStream(&outputStream);
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
											// ���� ��ǥ������ ������ �ʴٰ�, �̹� ��ǥ���� ���� ���̰� �� ũ��ó��
											// GCAddXXX �� �޾ƿ´�. �������� NEW_SIGHT �̰�, ���ݵ� NEW_SIGHT �̸�,
											// ���� �޾ƿ��� �ʴ´�.
											//--------------------------------------------------------------------------------
											if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT && canSee(pPC, pCreature))
											{
												Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
//												GCAddOusters gcAddOusters(pOusters->getOustersInfo3());
//												gcAddOusters.setEffectInfo(pOusters->getEffectInfo());
												GCAddOusters gcAddOusters;
												makeGCAddOusters(&gcAddOusters, pOusters);
												pPlayer->sendPacket(&gcAddOusters);
											}

											Assert(pCreature->getPlayer() != NULL);

											//--------------------------------------------------------------------------------
											// Q(x2,y2)�� �� ũ��ó�� �þ� �簢���� ���迡 ��ġ�ϸ鼭, P(x1,y1)�� �簢���� �ܺ�,
											// �� ������ �ʴ� ���쿡�� GCAddXXX ��Ŷ�� �����Ѵ�. �̷��� ���� ������, PC
											// ũ��ó�� pCreature�� �þ� ���迡�� ���� �����̰� �Ǹ� ���� ������ GCAddXXX ��Ŷ��
											// �����߸� �Ѵ�.
											//
											// �����ϸ�,
											//
											// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX
											// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
											//
											//--------------------------------------------------------------------------------
											VisionState prevVS = pCreature->getVisionState(x1,y1);
											VisionState currVS = pCreature->getVisionState(x2,y2);

											// ������ �����̾��̹Ƿ� ���� darkness���´� ��������.
											// Hide�� ��������.
											// *NOTE
											// ���밡 �����̾����� �����̾ �������� ���������� üũ �ؾ� �Ѵ�.
											if (canSee(pCreature, pPC ) )
											{
												if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(pGCAddXXX);
													pCreature->getPlayer()->sendPacket(&gcFastMove);
													//pCreature->getPlayer()->sendStream(&outputStream);
												}
												else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(&gcFastMove);
													//pCreature->getPlayer()->sendStream(&outputStream);
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
											// ���� ��ǥ������ �� �����͸� �� �� ��������, ���� ��ǥ���� �� �����͸� ���� ��
											// ���� GCAddMonster ��Ŷ�� �����Ѵ�.
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
						// Ÿ�� ���� �������� ���� ����
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

													sendRelicEffect(pMonsterCorpse, pPlayer);
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
						// Ÿ�� ���� ����Ʈ�� ���� ����
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

										// sanctuary�� �߽���ǥ�� ���츸 packet�� ������.
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
									// Broadcasting Effect üũ �߰� by Sequoia 2003.3.31
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
						// Ÿ�� ���� ���ֹ��� ���� ����
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_OBSTACLE :
							{
								// darkness
							}
							break;

						//--------------------------------------------------------------------------------
						// Ÿ�� ���� ��Ż�� ���� ����
						//--------------------------------------------------------------------------------
						case Object::OBJECT_CLASS_PORTAL :
							{
								// darkness
							}
							break;

						default :
							throw Error("invalid object class");

					}//switch ((*itr)->getObjectClass())
				} while (++itr != objectList.end());	// do ~ while
			}//if
		}//for
	}//for

	SAFE_DELETE(pGCAddXXX);

	return true;

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// P(x1,y1)���� Q(x2,y2)�� ���� �̵��� ũ��ó�� �ֺ� ������ �����ϴ� PC�鿡��
// ���ε�ĳ��Ʈ�ϴ� �޽����̴�.
// for Skill FlashSliding, ShadowWalk
//////////////////////////////////////////////////////////////////////////////
bool Zone::moveFastMonster(Monster* pMonster, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	if (
/*		pMonster->isFlag(Effect::EFFECT_CLASS_PARALYZE)
		|| pMonster->isFlag(Effect::EFFECT_CLASS_HIDE)
		|| pMonster->isFlag(Effect::EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS)
		|| pMonster->isFlag(Effect::EFFECT_CLASS_SLEEP)
		|| pMonster->isFlag(Effect::EFFECT_CLASS_ARMAGEDDON) */
		!isAbleToMove(pMonster )
	) {
		// do nothing
		return false;
	}

	ZoneLevel_t ZoneLevel = getZoneLevel(x2, y2);

	// ���� ���뿡 �� �����.
	if ((ZoneLevel & SLAYER_SAFE_ZONE)
		|| (ZoneLevel & VAMPIRE_SAFE_ZONE)
		|| (ZoneLevel & COMPLETE_SAFE_ZONE))
	{
		return false;
	}

	// ������ ���������� ã�´�.
	// �����ο��� ������ ����..4�� �˻�
	Dir_t dir = calcDirection(x1, y1, x2, y2);

	// g_FastMoveSearchX, Y�� ã���� �ȴ�. by sigi. 2002.5.8
	int* searchX = g_FastMoveSearchX[dir];
	int* searchY = g_FastMoveSearchY[dir];

	// �� Ÿ������ Ȯ��.
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
		return false;	// ��Ÿ���� ��ã�Ҵ�!
	}

	// �ϴ� ��Ŷ�� �������ΰ� �ؿ��� ������.
	GCFastMove gcFastMove;
	gcFastMove.setObjectID(pMonster->getObjectID());
	gcFastMove.setXY(x1, y1, x2, y2);
	gcFastMove.setSkillType(skillType);

//#ifdef __USE_ENCRYPTER__
//	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + gcFastMove.getPacketSize() + 2);
//	outputStream.setEncryptCode(m_EncryptCode);
//#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + gcFastMove.getPacketSize() + 2);
//#endif
//	gcFastMove.writeHeaderNBody(outputStream);

	// ���������״� ���� �ʿ䰡 ����.
	//pPlayer->sendPacket(&gcFastMove);

	//////////////////////////////////////////////////////////////
	// move�� ����....
	// �̿����� GCDelete�� Add���� �������� �� �� �� �ִ�.

	// Monster ��ǥ ����.
	pMonster->setXYDir(x2, y2, dir);
	// ���� Ÿ�Ͽ��� ũ��ó�� �����Ѵ�.

	try {
		m_pTiles[x1][y1].deleteCreature(pMonster->getObjectID());
	} catch (Error& e) {
		filelog("assertTile.txt", "moveFastMonster : %s", e.toString().c_str());
		throw;
	}

	// �� Ÿ�Ͽ� ũ��ó�� �߰��Ѵ�.
	m_pTiles[x2][y2].addCreature(pMonster);

	try {
		checkMine(this, pMonster, x2, y2);
		checkTrap(this, pMonster);
	} catch (Throwable & t ) {
		filelog("CheckMineBug.txt", "%s : %s", "moveFastMonster", t.toString().c_str());
	}


	//--------------------------------------------------------------------------------
	// GCAddSlayer/GCAddVampire ��Ŷ�� �������д�.
	// ������ ��å�� ���ϸ�, GCAdd ��Ŷ�� ������ ��ǥ�� �������� �Ѵ�.
	//--------------------------------------------------------------------------------
	Packet* pAddMonsterPacket = createMonsterAddPacket(pMonster, NULL);

	if (pAddMonsterPacket!=NULL)
	{
		//--------------------------------------------------------------------------------
		// GCDeleteObject ��Ŷ�� �������д�.
		//--------------------------------------------------------------------------------
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID(pMonster->getObjectID());


		// �� �þ��� ������ ���Ѵ�.
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
				const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

				list<Object*>::const_iterator itr = objectList.begin();

				// visionInfo ������..
				// if - do~while()�� ���� ���� by sigi. 2002.5.8
				if (itr != objectList.end())
				{

					// ���� ��ǥ P(x1,y1)���� I(ix,iy)�� ��� ���̴°�?
					//VisionState prevVisionState = pVisionInfo->getVisionState(x1,y1,ix,iy);
					// ���� ��ǥ Q(x2,y2)���� I(ix,iy)�� ��� ���̴°�?
					//VisionState curVisionState = pVisionInfo->getVisionState(x2,y2,ix,iy);

					do
					{
						Assert(*itr != NULL);

						//--------------------------------------------------------------------------------
						//
						// �� ��ü�� OBJECT CLASS�� ������ ������ GCAddXXX ��Ŷ�� �����
						// owner ���� �����Ѵ�.
						//
						// *NOTES*
						//
						// ���� ���� Ȯ���� ���� ��ü CLASS �� case �պκп� ���;� �Ѵ�.
						//
						//--------------------------------------------------------------------------------
						switch ((*itr)->getObjectClass())
						{
							//--------------------------------------------------------------------------------
							// Ÿ�� ���� ũ��ó�� ���� ����
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_CREATURE :
								{
									Creature* pCreature = dynamic_cast<Creature*>(*itr);
									Assert(pCreature != NULL);

									// �ڱ� �ڽ��� ������ ���� �ʿ䰡 ����.
									if (pCreature == pMonster) continue;

									switch (pCreature->getCreatureClass())
									{

										case Creature::CREATURE_CLASS_MONSTER :
											{
												Monster* pOtherMonster = dynamic_cast<Monster*>(pCreature);

												//--------------------------------------------------------------------------------
												// PC�� �������� �������� ������ �������ش�.
												//--------------------------------------------------------------------------------
												//VisionState vs = pMonster->getVisionState(x2,y2);

												// Aggressive �����Ϳ��Ը� ������ ���Ͻ����ش�.
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

												// Creature �� ObservingEye ����Ʈ�� ������ �ִٸ� �����´�.
//												EffectObservingEye* pEffectObservingEye = NULL;
//												if (pCreature->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//												{
//													pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pCreature->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE ));
//													//Assert(pEffectObservingEye != NULL);
//												}

												// ���뿡�� PC�� ������ �˸��� ��Ŷ.
//												if ((!pMonster->isFlag(Effect::EFFECT_CLASS_HIDE) || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) ) //|| (pEffectRevealerCreature != NULL && pEffectRevealerCreature->canSeeHide(pPC ) ) )
//													&& (!pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(pMonster ) ) )
//													&& (!pMonster->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) || pCreature->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) )) //|| (pEffectRevealerCreature != NULL && pEffectRevealerCreature->canSeeSniping(pPC) ) ) )
												if (canSee(pCreature, pMonster ) )
												{
													if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
													{
														pCreature->getPlayer()->sendPacket(pAddMonsterPacket);
                                                        pCreature->getPlayer()->sendPacket(&gcFastMove);
//														pCreature->getPlayer()->sendStream(&outputStream);
													}
													else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
													{
                                                        pCreature->getPlayer()->sendPacket(&gcFastMove);
//														pCreature->getPlayer()->sendStream(&outputStream);
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
												// Q(x2,y2)�� �� ũ��ó�� �þ� �簢���� ���迡 ��ġ�ϸ鼭, P(x1,y1)�� �簢���� �ܺ�,
												// �� ������ �ʴ� ���쿡�� GCAddXXX ��Ŷ�� �����Ѵ�. �̷��� ���� ������, PC
												// ũ��ó�� pCreature�� �þ� ���迡�� ���� �����̰� �Ǹ� ���� ������ GCAddXXX ��Ŷ��
												// �����߸� �Ѵ�.
												//
												// �����ϸ�,
												//
												// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX
												// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
												//
												//--------------------------------------------------------------------------------
												VisionState prevVS = pCreature->getVisionState(x1,y1);
												VisionState currVS = pCreature->getVisionState(x2,y2);

												// ������ �����̾��̹Ƿ� ���� darkness���´� ��������.
												// Hide�� ��������.
												// *NOTE
												// ���밡 �����̾����� �����̾ �������� ���������� üũ �ؾ� �Ѵ�.
												if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
												{
													pCreature->getPlayer()->sendPacket(pAddMonsterPacket);
                                                    pCreature->getPlayer()->sendPacket(&gcFastMove);
//													pCreature->getPlayer()->sendStream(&outputStream);
												}
												else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
												{
                                                    pCreature->getPlayer()->sendPacket(&gcFastMove);
//													pCreature->getPlayer()->sendStream(&outputStream);
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

												// ���뿡�� PC�� ������ �˸��� ��Ŷ.
												if (canSee(pCreature, pMonster ) )
												{
													if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
													{
														pCreature->getPlayer()->sendPacket(pAddMonsterPacket);
                                                        pCreature->getPlayer()->sendPacket(&gcFastMove);
//														pCreature->getPlayer()->sendStream(&outputStream);
													}
													else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
													{
                                                        pCreature->getPlayer()->sendPacket(&gcFastMove);
//														pCreature->getPlayer()->sendStream(&outputStream);
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
							// Ÿ�� ���� �������� ���� ����
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_ITEM :
								{
								}
								break;

							//--------------------------------------------------------------------------------
							// Ÿ�� ���� ����Ʈ�� ���� ����
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_EFFECT :
								{
								}
								break;

							//--------------------------------------------------------------------------------
							// Ÿ�� ���� ���ֹ��� ���� ����
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_OBSTACLE :
								{
									// darkness
								}
								break;

							//--------------------------------------------------------------------------------
							// Ÿ�� ���� ��Ż�� ���� ����
							//--------------------------------------------------------------------------------
							case Object::OBJECT_CLASS_PORTAL :
								{
									// darkness
								}
								break;

							default :
								throw Error("invalid object class");

						}//switch ((*itr)->getObjectClass())
					} while (++itr != objectList.end());	// do ~ while
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
// (x1,y1)���� (x2,y2)�� PC�� �̵��� ����, �� PC�� �ڸ��� �ٲ��� ����
// ���� ���� �Ǵ� �͵鿡 ���� ������ �������� �ϰ�, �� PC�� ���� ���� �Ǵ�
// �ٸ� ũ���ĵ鿡�Ե� ������ �������� �Ѵ�.
//
// bSendMove�� move packet�� �����°��� ���� ����.
// bKnockback�� ������ �������� �������� �������ΰ�, �ƴϸ� knockback��
// ���� �������� �������ΰ��� ��Ÿ���� ����
//////////////////////////////////////////////////////////////////////////////
void Zone::movePCBroadcast (Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove, bool bKnockback)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_MOVEPC");

try
{
	// �� �޽����� PC �� �������� �Ѵ�.
	Assert(pPC->isPC());

	//////////////////////////////////////////////////////////////////////////////
	// �ڽ��� �̵��� ��Ÿ���� GCMove ��Ŷ�� �������д�. Ŭ���̾�Ʈ���� GCMove��
	// �����Ҷ�, (x,y)�� ���� ��ǥ���� �ϸ�, dir �� �ٶ������߽(�̵���) �����̾��� �Ѵ�.
	// �װ��� ������ ��å!
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

//#ifdef __USE_ENCRYPTER__
//	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + (bSendMove ? gcMove.getPacketSize() : gcKnockback.getPacketSize() ) + 2);
//	outputStream.setEncryptCode(m_EncryptCode);
//#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + (bSendMove ? gcMove.getPacketSize() : gcKnockback.getPacketSize() ) + 2);
//#endif
//	if (bSendMove )
//		gcMove.writeHeaderNBody(outputStream);
//	else
//		gcKnockback.writeHeaderNBody(outputStream);

	//////////////////////////////////////////////////////////////////////////////
	// �����̴� PC�� ���� ���Ե� �ٸ� PC���� ���ؼ� PC�� Ÿ�Կ� ���� GCAdd ��Ŷ��
	// �������д�.  ������ ��å�� ���ϸ�, GCAdd ��Ŷ�� ������ ��ǥ�� �������� �Ѵ�.
	//////////////////////////////////////////////////////////////////////////////
	Packet* pGCAddXXX = NULL;

	if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_SLAYER)
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);

//		GCAddSlayer* pGCAddSlayer = new GCAddSlayer(pSlayer->getSlayerInfo3());
//		pGCAddSlayer->setEffectInfo(pSlayer->getEffectInfo());
		GCAddSlayer* pGCAddSlayer = new GCAddSlayer;
		makeGCAddSlayer(pGCAddSlayer, pSlayer);
		pGCAddXXX = pGCAddSlayer;
	}
	else if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_VAMPIRE)
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);

		// ��.. hide���¿��� ������ ���� ������. �̷��� ����.
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
			makeGCAddVampire(pGCAddVampire, pVampire);
			pGCAddXXX = pGCAddVampire;
		}
	}
	else if (pPC->getCreatureClass() == Creature::CREATURE_CLASS_OUSTERS )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);

//		GCAddOusters* pGCAddOusters = new GCAddOusters(pOusters->getOustersInfo3());
//		pGCAddOusters->setEffectInfo(pOusters->getEffectInfo());
		GCAddOusters* pGCAddOusters = new GCAddOusters;
		makeGCAddOusters(pGCAddOusters, pOusters);
		pGCAddXXX = pGCAddOusters;
	}

	//////////////////////////////////////////////////////////////////////////////
	// PC�� �����̹Ƿ�, �����ִ� ���� �߿��� �� PC�� �� ����
	// �Ǵ� ���鵵 �ִ�. �̵鿡�� ������ GCDeleteObject ��Ŷ��
	// �������д�.
	//////////////////////////////////////////////////////////////////////////////
	GCDeleteObject gcDeleteObject;
	gcDeleteObject.setObjectID(pPC->getObjectID());

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer != NULL);

	// loop �ȿ� �ִ��� �������� ����. by sigi. 2002.5.8
//	Sight_t sight = pPC->getSight();
//	VisionInfo* pVisionInfo = g_pVisionInfoManager->getVisionInfo(sight, pPC->getDir());

//    // ObservingEye ����Ʈ�� �����´�.
//	EffectObservingEye* pEffectObservingEye = NULL;
//	if (pPC->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//	{
//		pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE));
//		//Assert(pEffectObservingEye != NULL);
//	}

	//////////////////////////////////////////////////////////////////////////////
	// �þ� ������ �����¿� ���� + 1 �� ������Ų��.
	// ������ ���⿡ ���� ON_SIGHT ������ �����Ǳ� �����̴�.
	//////////////////////////////////////////////////////////////////////////////
	for (ZoneCoord_t ix = max(0, x2 - maxViewportWidth - 1), endx = min(m_Width - 1, x2 + maxViewportWidth + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, y2 - maxViewportUpperHeight - 1), endy = min(m_Height - 1, y2 + maxViewportLowerHeight + 1) ; iy <= endy ; iy++)
		{
			//if (pPC->isFlag(Effect::EFFECT_CLASS_DARKNESS)) sight = DARKNESS_SIGHT;

			// ���� Ÿ�� ���� �ִ� ���� ������Ʈ�鿡 ���� �ݺ��Ѵ�.
			const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

			list<Object*>::const_iterator itr = objectList.begin();

			//
			// object�� �ִ� ���츸
			// pVisionInfo->getVisionState()�� üũ �ϱ� ���ؼ�
			// if - do~while �� �����ߴ�. by sigi. 2002.5.8
			//
			if (itr != objectList.end())
			{
				// ���� ��ǥ P(x1,y1)���� I(ix,iy)�� ��� ���̴°�?
//				VisionState prevVisionState = pVisionInfo->getVisionState(x1,y1,ix,iy);
				VisionState prevVisionState = VisionInfoManager::getVisionState(x1, y1, ix, iy);
				// ���� ��ǥ Q(x2,y2)���� I(ix,iy)�� ��� ���̴°�?
//				VisionState curVisionState = pVisionInfo->getVisionState(x2,y2,ix,iy);
				VisionState curVisionState = VisionInfoManager::getVisionState(x2, y2, ix, iy);

				do
				{
					Assert(*itr != NULL);

					Object* pDebugObject = *itr;

					Object::ObjectClass OClass = pDebugObject->getObjectClass();

					////////////////////////////////////////////////////////////
					// �� ��ü�� OBJECT CLASS�� ������ ������ GCAddXXX ��Ŷ��
					// ����� owner ���� �����Ѵ�.
					////////////////////////////////////////////////////////////

					////////////////////////////////////////////////////////////
					// Ÿ�� ���� ũ��ó�� ���� ����
					////////////////////////////////////////////////////////////
					if (OClass == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pCreature = dynamic_cast<Creature*>(*itr);
						Assert(pCreature != NULL);

						if (pCreature == pPC)
						{
							// �˹��� ����, �ڽ��� ������ ���� �����̴� ���� �ƴ϶�,
							// Ÿ�ο� ���� �����̴� ���̹Ƿ� �������� �Ѵ�.
							if (bKnockback)
							{
                                pPC->getPlayer()->sendPacket(&gcKnockback);
//								pPC->getPlayer()->sendStream(&outputStream);
								// �˹��� ���������� continue�Ѵ�.
							}

							// �ڱ� �ڽ��� �̵� ������ ���� �ʿ䰡 ����.
							continue;
						}

						Creature::CreatureClass CClass = pCreature->getCreatureClass();

						// Monster > Slayer > Vampire > NPC ���̶��� �Ǵ��ؼ�
						// if ������ �ٲ���. ���� �ǹ� ���� ���� �� �ٸ�������?
						// by sigi. 2002.5.8
						if (CClass == Creature::CREATURE_CLASS_MONSTER)
						{
							Monster* pMonster = dynamic_cast<Monster*>(pCreature);

							//--------------------------------------------------------------------------------
							// ���� ��ǥ������ �� �����͸� �� �� ��������, ���� ��ǥ���� �� �����͸� ���� ��
							// ���� GCAddMonster ��Ŷ�� �����Ѵ�.
							//--------------------------------------------------------------------------------
							if (prevVisionState == OUT_OF_SIGHT && curVisionState >= IN_SIGHT)
							{
								// by sigi
								Packet* pAddMonsterPacket = createMonsterAddPacket(pMonster, pPC);

								if (pAddMonsterPacket!=NULL)
								{
									pPlayer->sendPacket(pAddMonsterPacket);

									delete pAddMonsterPacket;
								}
							}

							// PC�� �������� �������� ������ �������ش�.
							VisionState vs = pMonster->getVisionState(x2,y2);

							// Aggressive �����Ϳ��Ը� ������ ���Ͻ����ش�.
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
							// ���� Ÿ���� ������ �� ���̴ٰ� ���� ���̴� ���쿡,
							// �� Ÿ�Ͽ� ũ���İ� �� �ִٸ�...
							// �����̰� �ִ� PC���� �� Ÿ�Ͽ� �� �ִ� ���� ������ �����־��� �Ѵ�.
							if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT)
							{
								// ���� �����̴� ũ���Ŀ��� �������� ���°� �ɷ����� �ʰų�,
								// �ɷ��ִٸ� ����Ʈ �κ�������Ƽ�� �ɷ��־��� �� �� �ִ�.
								// canSee �� ��ü. by bezz 2003.05.29
//								if (canSee(pPC, pCreature, pEffectObservingEye ) )
								if (canSee(pPC, pCreature ) )
								{
									Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
//									GCAddSlayer gcAddSlayer(pSlayer->getSlayerInfo3());
//									gcAddSlayer.setEffectInfo(pSlayer->getEffectInfo());
									GCAddSlayer gcAddSlayer;
									makeGCAddSlayer(&gcAddSlayer, pSlayer);
									pPlayer->sendPacket(&gcAddSlayer);
								}
							}

							Assert(pCreature->getPlayer() != NULL);

							//////////////////////////////////////////////////////////////////////////////
							// Q(x2,y2)�� �� ũ��ó�� �þ� �簢���� ���迡 ��ġ�ϸ鼭, P(x1,y1)�� �簢���� �ܺ�,
							// �� ������ �ʴ� ���쿡�� GCAddXXX ��Ŷ�� �����Ѵ�. �̷��� ���� ������, PC
							// ũ��ó�� pCreature�� �þ� ���迡�� ���� �����̰� �Ǹ� ���� ������ GCAddXXX ��Ŷ��
							// �����߸� �Ѵ�.
							//
							// �����ϸ�,
							//
							// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX
							// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
							//////////////////////////////////////////////////////////////////////////////
							VisionState prevVS = pCreature->getVisionState(x1,y1);
							VisionState currVS = pCreature->getVisionState(x2,y2);

							// ������ �ʴ� ��������, ���� ������ ��ġ�� �ʰ� �ٷ�
							// �þ� ���� �������� �����´ٴ� ���� �Ұ����ϴ�.
							// �̰� ���� ��~ IN_SIGHT�ۿ� ����.
//							Assert(prevVS != OUT_OF_SIGHT || currVS != IN_SIGHT);

							if (canSee(pCreature, pPC ) )
							{
								if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
								{
									pCreature->getPlayer()->sendPacket(pGCAddXXX);
								}
								else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
								{
                                    if (bSendMove)
                                        pCreature->getPlayer()->sendPacket(&gcMove);
                                    else if (bKnockback)
                                        pCreature->getPlayer()->sendPacket(&gcKnockback);
//									pCreature->getPlayer()->sendStream(&outputStream);
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
							// ���� ��ǥ������ ������ �ʴٰ�, �̹� ��ǥ���� ���� ���̰� �� ũ��ó��
							// GCAddXXX �� �޾ƿ´�. �������� NEW_SIGHT �̰�, ���ݵ� NEW_SIGHT �̸�,
							// ���� �޾ƿ��� �ʴ´�.
							//////////////////////////////////////////////////////////////////////////////
							if (curVisionState >= IN_SIGHT && prevVisionState == OUT_OF_SIGHT)
							{
								if (canSee(pPC, pCreature ) )
								{
									if (pCreature->isFlag(Effect::EFFECT_CLASS_HIDE))
									{
//										if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)
//											&& (pPC->isVampire()
//												|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )// || (pEffectRevealer != NULL && pEffectRevealer->canSeeHide(pCreature ) ) )
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
//												|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY) || (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(pCreature ) ) )
//											)
										{
											Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
//											GCAddVampire gcAddVampire(pVampire->getVampireInfo3());
//											gcAddVampire.setEffectInfo(pVampire->getEffectInfo());
											GCAddVampire gcAddVampire;
											makeGCAddVampire(&gcAddVampire, pVampire);

											pPlayer->sendPacket(&gcAddVampire);
										}
									}
								}
							}

							Assert(pCreature->getPlayer() != NULL);

							//////////////////////////////////////////////////////////////////////////////
							// Q(x2,y2)�� �� ũ��ó�� �þ� �簢���� ���迡 ��ġ�ϸ鼭, P(x1,y1)�� �簢���� �ܺ�,
							// �� ������ �ʴ� ���쿡�� GCAddXXX ��Ŷ�� �����Ѵ�. �̷��� ���� ������, PC
							// ũ��ó�� pCreature�� �þ� ���迡�� ���� �����̰� �Ǹ� ���� ������ GCAddXXX ��Ŷ��
							// �����߸� �Ѵ�.
							//
							// �����ϸ�,
							//
							// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX
							// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
							//////////////////////////////////////////////////////////////////////////////
							VisionState prevVS = pCreature->getVisionState(x1,y1);
							VisionState currVS = pCreature->getVisionState(x2,y2);

							// ������ �ʴ� ��������, ���� ������ ��ġ�� �ʰ� �ٷ�
							// �þ� ���� �������� �����´ٴ� ���� �Ұ����ϴ�.
							// �̰� ���� ��~ IN_SIGHT�ۿ� ����.
//							Assert(prevVS != OUT_OF_SIGHT || currVS != IN_SIGHT);

							// ������ �����̾��̹Ƿ� ���� darkness���´� ��������.
							// Hide�� ��������.
//							if (!pPC->isFlag(Effect::EFFECT_CLASS_GHOST)
//								&& (!pPC->isSlayer()
//									|| !pPC->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
//								)
							if (canSee(pCreature, pPC ) )
							{
								if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
								{
									pCreature->getPlayer()->sendPacket(pGCAddXXX);
								}
								else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
								{
                                    if (bSendMove) pCreature->getPlayer()->sendPacket(&gcMove);
                                    else if (bKnockback) pCreature->getPlayer()->sendPacket(&gcKnockback);
//									pCreature->getPlayer()->sendStream(&outputStream);
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
							// ���� ��ǥ������ ������ �ʴٰ�, �̹� ��ǥ���� ���� ���̰� �� ũ��ó��
							// GCAddXXX �� �޾ƿ´�. �������� NEW_SIGHT �̰�, ���ݵ� NEW_SIGHT �̸�,
							// ���� �޾ƿ��� �ʴ´�.
							//////////////////////////////////////////////////////////////////////////////
							if (curVisionState >= IN_SIGHT  && prevVisionState == OUT_OF_SIGHT)
							{
//								if (!pCreature->isFlag(Effect::EFFECT_CLASS_GHOST) )
								if (canSee(pPC, pCreature ) )
								{
									Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
//									GCAddOusters gcAddOusters(pOusters->getOustersInfo3());
//									gcAddOusters.setEffectInfo(pOusters->getEffectInfo());
									GCAddOusters gcAddOusters;
									makeGCAddOusters(&gcAddOusters, pOusters);
									pPlayer->sendPacket(&gcAddOusters);
								}
							}

							Assert(pCreature->getPlayer() != NULL);

							//////////////////////////////////////////////////////////////////////////////
							// Q(x2,y2)�� �� ũ��ó�� �þ� �簢���� ���迡 ��ġ�ϸ鼭, P(x1,y1)�� �簢���� �ܺ�,
							// �� ������ �ʴ� ���쿡�� GCAddXXX ��Ŷ�� �����Ѵ�. �̷��� ���� ������, PC
							// ũ��ó�� pCreature�� �þ� ���迡�� ���� �����̰� �Ǹ� ���� ������ GCAddXXX ��Ŷ��
							// �����߸� �Ѵ�.
							//
							// �����ϸ�,
							//
							// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX
							// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
							//////////////////////////////////////////////////////////////////////////////
							VisionState prevVS = pCreature->getVisionState(x1,y1);
							VisionState currVS = pCreature->getVisionState(x2,y2);

							// ������ �ʴ� ��������, ���� ������ ��ġ�� �ʰ� �ٷ�
							// �þ� ���� �������� �����´ٴ� ���� �Ұ����ϴ�.
//							Assert(prevVS != OUT_OF_SIGHT || currVS != IN_SIGHT);

							if (canSee(pCreature, pPC ) )
							{
								if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
								{
									pCreature->getPlayer()->sendPacket(pGCAddXXX);
								}
								else if (prevVS >= IN_SIGHT && currVS >= IN_SIGHT)
								{
                                    if (bSendMove) pCreature->getPlayer()->sendPacket(&gcMove);
                                    else if (bKnockback) pCreature->getPlayer()->sendPacket(&gcKnockback);
//									pCreature->getPlayer()->sendStream(&outputStream);
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
							// ���� ��ǥ������ �� �����͸� �� �� ��������, ���� ��ǥ���� �� �����͸� ���� ��
							// ���� GCAddMonster ��Ŷ�� �����Ѵ�.
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
					// Ÿ�� ���� �������� ���� ����
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

									sendRelicEffect(pMonsterCorpse, pPlayer);
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
					// Ÿ�� ���� ����Ʈ�� ���� ����
					////////////////////////////////////////////////////////////
					else if (OClass == Object::OBJECT_CLASS_EFFECT)
					{
						Effect* pEffect = dynamic_cast<Effect*>(*itr);

						// broadcasting Effect ���� üũ �߰� 2003.3.31 by Sequoia
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

								// sanctuary�� �߽���ǥ�� ���츸 packet�� ������.
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
					// Ÿ�� ���� ���ֹ��� ���� ����
					////////////////////////////////////////////////////////////
					else if (OClass == Object::OBJECT_CLASS_OBSTACLE)
					{
					}
					////////////////////////////////////////////////////////////
					// Ÿ�� ���� ��Ż�� ���� ����
					////////////////////////////////////////////////////////////
					else if (OClass == Object::OBJECT_CLASS_PORTAL)
					{
						// darkness
					}
					else
					{
						throw Error("invalid object class");
					}

				} while (++itr != objectList.end());	// by sigi. 2002.5.8
			}//for ������Ʈ�鿡 ���� �ݺ�
		}//for Y ��ǥ�� ���� �ݺ�
	}//for X ��ǥ�� ���� �ݺ�

	SAFE_DELETE(pGCAddXXX);

}
catch (Throwable& t )
{
	filelog("Zone_movePCBroadcast.log", "%s", t.toString().c_str());
	throw t;
}

	__END_PROFILE_ZONE("Z_BC_MOVEPC");

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// moveCreatureBroadcast
//
// PC�� �ƴ� ũ��ó(NPC,������)�� P(x1,y1)���� Q(x2,y2)�� �̵����� ��,
// �ֺ� ������ �����ϴ� PC�鿡�� ���ε�ĳ��Ʈ�ϴ� �޽����̴�.
//
// �� �޽��带 ȣ���ϱ� ����, 3 ���� ��Ŷ�� �������־߸� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void Zone::moveCreatureBroadcast(Creature* pCreature, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove, bool bKnockback)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	__BEGIN_PROFILE_ZONE("Z_BC_MOVE_CREATURE")

	try {

	Monster* pMonster = NULL;
	NPC* pNPC = NULL;

	Assert(pCreature != NULL);
	Assert(pCreature->isNPC() || pCreature->isMonster());

	// ������ ��å�� ���ϸ�, GCMove ��Ŷ�� ���� ��ǥ�� ���� ������ �����ϰ� �Ǿ��ִ�.
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

//#ifdef __USE_ENCRYPTER__
//	SocketEncryptOutputStream outputStream(NULL, szPacketHeader + (bSendMove ? gcMove.getPacketSize() : gcKnockback.getPacketSize() ) + 2);
//	outputStream.setEncryptCode(m_EncryptCode);
//#else
//	SocketOutputStream outputStream(NULL, szPacketHeader + (bSendMove ? gcMove.getPacketSize() : gcKnockback.getPacketSize() ) + 2);
//#endif
//	if (bSendMove )
//		gcMove.writeHeaderNBody(outputStream);
//	else
//		gcKnockback.writeHeaderNBody(outputStream);

	// GCAddNPC/GCAddMonster ��Ŷ�� �������д�.
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

		// �ϴ� �� �� �� �ִ� ����(NULL)�� �����ؼ� packet�� �����Ѵ�. by sigi
		pGCAddXXX = createMonsterAddPacket(pMonster, NULL);

		// monster�� ���¸� �����صд�.
//		isMonsterHide = pMonster->isFlag(Effect::EFFECT_CLASS_HIDE);
//		isMonsterInvisibility = pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY);
	}

	// �þ߿��� ��� ��, GCDeleteObject ��Ŷ�� ������.
	GCDeleteObject gcDeleteObject;
	gcDeleteObject.setObjectID(pCreature->getObjectID());

	//////////////////////////////////////////////////////////////////////////////
	// �þ� ������ �����¿� ���� + 1 �� ������Ų��.
	// ������ ���⿡ ���� ON_SIGHT ������ �����Ǳ� �����̴�.
	//////////////////////////////////////////////////////////////////////////////
	for (ZoneCoord_t ix = max(0, x2 - maxViewportWidth - 1), endx = min(m_Width - 1, x2 + maxViewportWidth + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, y2 - maxViewportUpperHeight - 1), endy = min(m_Height - 1, y2 + maxViewportLowerHeight + 1) ; iy <= endy ; iy++)
		{
			const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
			list<Object*>::const_iterator itr = objectList.begin();
			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++)
			{
				Assert(*itr != NULL);

				Creature* pPC = dynamic_cast<Creature*>(*itr);

				Assert(pPC != NULL);

				// PC �� ���쿡�� GCMove, GCAddMonster ��Ŷ�� �����ش�. ���������״� ���� �ʿ䰡 ����~
				if (pPC->isPC())
				{
					Assert(pPC->getPlayer() != NULL);

					//////////////////////////////////////////////////////////////////////////////
					// OUT_OF_SIGHT -> ON_SIGHT/NEW_SIGHT : GCAddXXX
					// IN_SIGHT/ON_SIGHT/NEW_SIGHT -> IN_SIGHT/ON_SIGHT/NEW_SIGHT : GCMove
					//////////////////////////////////////////////////////////////////////////////
					VisionState prevVS = pPC->getVisionState(x1,y1);
					VisionState currVS = pPC->getVisionState(x2,y2);

					// ������ �ʴ� ��������, ���� ������ ��ġ�� �ʰ� �ٷ�
					// �þ� ���� �������� �����´ٴ� ���� �Ұ����ϴ�.
					// ���� ��~ IN_SIGHT�ۿ� ����.
//					Assert(prevVS != OUT_OF_SIGHT || currVS != IN_SIGHT);

					// ObservingEye ����Ʈ�� �����´�.
//					EffectObservingEye* pEffectObservingEye = NULL;
//					if (pPC->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//					{
//						pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE));
//						//Assert(pEffectObservingEye != NULL);
//					}

					if (prevVS == OUT_OF_SIGHT && currVS >= IN_SIGHT)
					{
						if (isMonster)
						{
							if (canSee(pPC, pMonster ) )
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
                        if (bSendMove)
                        {
                            pPC->getPlayer()->sendPacket(&gcMove);
                        }
                        else if (bKnockback)
                        {
                            pPC->getPlayer()->sendPacket(&gcKnockback);
                        }
//						pPC->getPlayer()->sendStream(&outputStream);
					}
					else if (prevVS >= IN_SIGHT && currVS == OUT_OF_SIGHT)
					{
						pPC->getPlayer()->sendPacket(&gcDeleteObject);
					}

					//--------------------------------------------------------------------------------
					// ���ε�ĳ��Ʈ�� ������, ���� �� PC�� �������� ������ �����ع�����.
					//--------------------------------------------------------------------------------
					if (pCreature->isMonster())
					{
						// �� ������ �̹� dynamic_cast �� �����̴�.
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

	// ������ ��Ŷ�� �����Ѵ�.
	SAFE_DELETE(pGCAddXXX);

	// by sigi. 2002.12.15
	} catch (Throwable& t) {
		filelog("moveCreatureBroadcastError.log", "%s", t.toString().c_str());

		// �ٽ� ������ ������ - -;
		throw;
	}

	__END_PROFILE_ZONE("Z_BC_MOVE_CREATURE")

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���� �ֱ⸶�� ������ �ϴ� ���ɵ��� ���⿡ �߰��ϵ��� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void Zone::heartbeat ()
	throw(Error)
{
	__BEGIN_TRY
	__BEGIN_DEBUG

	try
	{
		__ENTER_CRITICAL_SECTION(m_Mutex)

		beginProfileEx("Z_PCQUEUE");

		// PCQueue�� PC�� ���� �߰��Ѵ�.
		while(! m_PCListQueue.empty())
		{
			Creature* pCreature = m_PCListQueue.front();
			Assert(pCreature != NULL);
			Assert(pCreature->getZone() == this);

			// ���� �߰��ϰ�, �ֺ� PC�鿡�� ���ε�ĳ��Ʈ�Ѵ�.
			addPC(pCreature, pCreature->getX(), pCreature->getY(), DOWN);

			m_PCListQueue.pop_front();
		}

		endProfileEx("Z_PCQUEUE");

		beginProfileEx("Z_PC");
		m_pPCManager->processCreatures(); // process all PC
		endProfileEx("Z_PC");

		// ������ ���� �Ŵ����� �ִٸ� ������ �����̴�
		// by sigi. 2002.9.2
		if (m_pMasterLairManager!=NULL)
			m_pMasterLairManager->heartbeat(); // process master lair

		// WarScheduler�� �ִٸ� ������..
		// by sigi. 2003.1.24
		if (m_pWarScheduler!=NULL
			&& g_pVariableManager->isWarActive())
		{
			Work* pWork = m_pWarScheduler->heartbeat();

			if (pWork!=NULL)
			{
				War* pWar = dynamic_cast<War*>(pWork);
				Assert(pWar!=NULL);

				g_pWarSystem->addWarDelayed(pWar);
			}
		}

		if (m_pLevelWarManager != NULL
			&& g_pVariableManager->isActiveLevelWar() )
		{
			m_pLevelWarManager->heartbeat();
		// LevelWar Zone ���� �ð� ���� ���� ���� ������ ���������� �̻��ؼ� ������ ��.
			m_pLevelWarManager->freeUserTimeCheck();
		}

//		if (m_pLevelWarManager != NULL )
//		{
//		}

		// player�� �־��� monster�� heartbeat�Ѵ�.
		// ��, player�� ���� zone�� monster�� ������ �ִ´�.
		// monster�� EffectManager�� �� ���ư��Ƿ� ������ �� ���� ������,
		// ũ�� ������ ���ٰ� ����.. -_-; .. by sigi. 2002.5.6
		//if (m_ZoneID >= 1121 && m_ZoneID <= 1124)
		//	m_pCombatMonsterManager->processCreatures(); // ������ �������� AI�� ó���ϴ� �κ�, ���漮
		//else
		//{
			if (getPCCount() > 0 || (isDynamicZone() && (m_pDynamicZone->getStatus() == DYNAMIC_ZONE_STATUS_RUNNING ) ) )
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
		// ���� ����Ʈ �������� ���� ������Ų��.
		m_pEffectScheduleManager->heartbeat();
		endProfileEx("Z_ESCH");

		// Item�� EffectManager���� getCurrentTime�� ȣ������ �ʰ� �ϱ� ���ؼ�.
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

		for (map<ObjectID_t, Item*>::iterator itr = m_Items.begin(); itr != m_Items.end() ; itr++)
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

		// time band �� �����Ѵ�.
		if (m_UpdateTimebandTime < currentTime )
		{
			if (!m_bTimeStop )
			{
				m_Timeband = g_pTimeManager->getTimeband();
			}

			// 5�ʸ��� timeband �� �����Ѵ�. ���� �ð����� 2��
			m_UpdateTimebandTime.tv_sec += 5;
		}

		// DynamicZone �� ����
		if (isDynamicZone() )
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
// PCManager, MonsterManager, NPCManager ���� ������ OID �� ���� ũ��ó��
// ã�Ƽ� �����Ѵ�. ���� ���� NoSuchElementException �� ������.
//
// �� �޽����� ã���� �ϴ� ũ��ó�� Ÿ��(PC,NPC,Monster)�� ���� ���쿡
// �����Ѵ�. �����ϸ�, Ÿ���� �˾Ƴ��� getCreature(Creature::CreatureClass,ObjectID_t)
// �޽��带 �����ϵ��� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////
Creature* Zone::getCreature(ObjectID_t objectID) const
	throw()//NoSuchElementException, Error)
{
	__BEGIN_TRY

	// NoSuchElementException�� �� ���� ���� by sigi. 2002.5.2
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
// PCManager, MonsterManager, NPCManager ���� ������ Name�� ���� ũ��ó�� ã�Ƽ�
// �����Ѵ�. ���� ���� NoSuchElementException �� ������.
//
// �� �޽����� ã���� �ϴ� ũ��ó�� Ÿ��(PC,NPC,Monster)�� ���� ���쿡 �����Ѵ�.
// �����ϸ�, Ÿ���� �˾Ƴ��� getCreature(Creature::CreatureClass,Name)
// �޽��带 �����ϵ��� �Ѵ�.
//////////////////////////////////////////////////////////////////////////////
Creature* Zone::getCreature(const string& Name) const
	throw()//NoSuchElementException, Error)
{
	__BEGIN_TRY

	// NoSuchElementException�� �� ���� ���� by sigi. 2002.5.2
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
// ������ Ư�� OID�� ���� Ư�� ũ��ó Ÿ���� ���� ũ��ó�� ã�Ƽ� �����Ѵ�.
//
//--------------------------------------------------------------------------------
Creature* Zone::getCreature(Creature::CreatureClass creatureClass, ObjectID_t objectID) const
	throw(NoSuchElementException, Error)
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
	throw()
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

	Assert(m_MonsterCount < maxMonsterPerZone);	// by sigi
	for (uint i = 0 ; i < m_MonsterCount ; i++)
		msg << ",Monster[" << i << "] : " << (int)m_MonsterTypes[i];

	msg << ",Width:"  << (int)m_Width
		<< ",Height:" << (int)m_Height
		<< ")";

	return msg.toString();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// pTargetCreture�� �� �� �ִ� ��(player)���� list�� �����ش�.
// **********************************
//////////////////////////////////////////////////////////////////////////////
list<Creature*> Zone::getWatcherList(ZoneCoord_t x, ZoneCoord_t y, Creature* pTargetCreature)
	throw(Error)
{
	__BEGIN_TRY

	list<Creature*> cList;

	__BEGIN_PROFILE_ZONE("Z_GET_WATCHERLIST")

	if (pTargetCreature == NULL )
		return cList;

	////////////////////////////////////////////////////////////
	// �þ� ������ �����¿� ���� + 1 �� ������Ų��.
	// ������ ���⿡ ���� ON_SIGHT ������ �����Ǳ� �����̴�.
	////////////////////////////////////////////////////////////
	for (ZoneCoord_t ix = max(0, x - maxViewportWidth - 1), endx = min(m_Width - 1, x + maxViewportWidth + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, y - maxViewportUpperHeight - 1), endy = min(m_Height - 1, y + maxViewportLowerHeight + 1) ; iy <= endy ; iy++)
		{
			const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
			list<Object*>::const_iterator itr = objectList.begin();
			for (; itr != objectList.end() && (*itr)->getObjectPriority() <= OBJECT_PRIORITY_BURROWING_CREATURE; itr++)
			{
				Assert(*itr != NULL);

				Creature* pCreature = dynamic_cast<Creature*>(*itr);

				Assert(pCreature != NULL);

				if (pCreature->isPC())
				{
					Assert(pCreature->getPlayer() != NULL);

					// �ڱ� �ڽ��� ������ ���� �ʿ䰡 ����.
					if (pTargetCreature == pCreature
						|| pCreature->isFlag(Effect::EFFECT_CLASS_GHOST)) continue;

					VisionState vs = pCreature->getVisionState(x,y);

					if (vs >= IN_SIGHT)
					{
						if (canSee(pCreature, pTargetCreature ) )
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

void Zone::addToItemList(Item* pItem) throw()
{
	__BEGIN_TRY

	m_Items[ pItem->getObjectID()] = pItem;

	__END_CATCH
}

void Zone::deleteFromItemList(ObjectID_t id) throw()
{
	__BEGIN_TRY

	map< ObjectID_t, Item*>::iterator itr = m_Items.find(id);

	if (itr == m_Items.end())
		//throw NoSuchElementException();
		// NoSuch����. by sigi. 2002.5.3
	{
		return;
	}

	m_Items.erase(itr);

	__END_CATCH
}

void Zone::addVampirePortal(ZoneCoord_t cx, ZoneCoord_t cy, Vampire* pVampire, const ZONE_COORD& ZoneCoord)
	throw()
{
	__BEGIN_TRY

	Assert(m_OuterRect.ptInRect(cx, cy));
	Assert(pVampire != NULL);

	// �����̾��� �ɷ¿� ���� ��� �� �ִ� �ο���, ���� �ð��� �����Ѵ�.
	// ���� �ٷ� �߰��Ǵ� ���� �ƴϹǷ�, �ణ�� �����̸� �߰����ش�.
	Duration_t duration = (60 + (pVampire->getINT(ATTR_CURRENT)-20)/3) * 10 + 20; // 0.1�� ������ ������...
	int        count    = 3 + (pVampire->getINT(ATTR_CURRENT)-20)/10;

	// �ϴ� ����Ʈ ��ü ��ü�� �����Ѵ�.
	EffectVampirePortal* pEffectVampirePortal = new EffectVampirePortal(this, cx, cy);
	pEffectVampirePortal->setDeadline(duration);
	pEffectVampirePortal->setOwnerID(pVampire->getName());
	pEffectVampirePortal->setZoneCoord(ZoneCoord.id, ZoneCoord.x, ZoneCoord.y);
	pEffectVampirePortal->setCount(count);

	// ����Ʈ �������� �����ؼ� ���Ѵ�.
	EffectSchedule* pEffectSchedule = new EffectSchedule;
	pEffectSchedule->setEffect(pEffectVampirePortal);
	pEffectSchedule->addWork(WORKCODE_ADD_VAMPIRE_PORTAL, NULL);
	m_pEffectScheduleManager->addEffectSchedule(pEffectSchedule);

	__END_CATCH
}

//-------------------------------------------------------------
// deleteMotorcycle(x, y, pMotorcycle )
//-------------------------------------------------------------
// �ٷ� ������ �ʰ�.. zone�� heartbeat�Ҷ� ���쵵��
// EffectDecayItem�� �ٿ��д�.
//-------------------------------------------------------------
void Zone::deleteMotorcycle(ZoneCoord_t cx, ZoneCoord_t cy, Motorcycle* pMotorcycle)
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_OuterRect.ptInRect(cx, cy));
	Assert(pMotorcycle != NULL);

	EffectDecayItem* pEffectDecayItem = new EffectDecayItem(this, cx, cy, (Item*)pMotorcycle, 0,
															false); // DB������ ������ �ʴ´�.
	pEffectDecayItem->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectDecayItem);
	addEffect_LOCKING(pEffectDecayItem);

	__END_CATCH
}

/*
void Zone::decayMotorcycle(ZoneCoord_t cx, ZoneCoord_t cy, Motorcycle* pMotorcycle, Slayer* pSlayer)
	throw()
{
	__BEGIN_TRY

	cout << "Zone::decayMotorcycle	" << endl;

	Assert(m_OuterRect.ptInRect(cx, cy));
	Assert(pMotorcycle != NULL);

	// ������ �������̸� ������ ����Ʈ�� �߰��Ѵ�.
	EffectDecayMotorcycle* pEffectDecayMotorcycle = new EffectDecayMotorcycle(this, cx, cy, (Item*)pMotorcycle, 0,
															      false); // DB������ ������ �ʴ´�.
	pEffectDecayMotorcycle->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectDecayMotorcycle);
	addEffect_LOCKING(pEffectDecayMotorcycle);

	__END_CATCH
}
*/

//-------------------------------------------------------------
// transportItemToCorpse
//-------------------------------------------------------------
// ���� ���� pItem�� pZone�� (cx, cy)�� �ű���.
// EffectTransportItem�� �ٿ��� �ű���.
//-------------------------------------------------------------
void Zone::transportItemToCorpse(Item* pItem, Zone* pTargetZone, ObjectID_t corpseObjectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "transportItemToCorpse : " << (int)pZone->getZoneID() << ", (" << cx << ", " << cy << ")" << endl;
	Assert(pItem != NULL);

	if (pTargetZone->getZoneGroup()==this->getZoneGroup())
	{
		//cout << "same zone - to corpse" << endl;
		// ���� zone�̸� �ٷ� �ű���.
		//deleteFromItemList(pItem->getObjectID());

		Item* pCorpseItem = pTargetZone->getItem(corpseObjectID);

		if (pCorpseItem==NULL)
		{
			StringStream msg;
			msg << "[" << (int)m_ZoneID << "] ��ü�� ����: corpseObjectID=" << (int)corpseObjectID;

			throw Error(msg.toString());
		}
		else if (pCorpseItem->getItemClass()!=Item::ITEM_CLASS_CORPSE)
		{
			StringStream msg;
			msg << "[" << (int)m_ZoneID << "] ��ü�� �ƴϳ�: corpseObjectID=" << (int)corpseObjectID
				<< ", itemClass=" << (int)pCorpseItem->getItemClass()
				<< ", itemType=" << (int)pCorpseItem->getItemType();

			throw Error(msg.toString());
		}
		else
		{
			Corpse* pCorpse = dynamic_cast<Corpse*>(pCorpseItem);
			Assert(pCorpse!=NULL);

			pCorpse->addTreasure(pItem);
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
// ���� ���� pItem�� pZone�� (cx, cy)�� �ű���.
// EffectTransportItem�� �ٿ��� �ű���.
//-------------------------------------------------------------
void Zone::transportItem(ZoneCoord_t x, ZoneCoord_t y, Item* pItem,
						Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "transportItem : " << (int)pZone->getZoneID() << ", (" << cx << ", " << cy << ")" << endl;

	// �̰� �߸��س��� �ٿ��Ŵ�. ��.��; by sigi
	Assert(m_OuterRect.ptInRect(x, y));
	Assert(pItem != NULL);

	if (pZone->getZoneGroup()==this->getZoneGroup())
	{
		//cout << "same zone" << endl;
		// ���� zone group �̸� �ٷ� �ű���.
		deleteFromItemList(pItem->getObjectID());
		getTile(x, y).deleteItem();

		// �������� �������ٴ� ��Ŷ�� ������.
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
// �������� �߰��ϴµ�.. �ٸ� thread���� �ص� �ȴ�.
// �ٸ� heartbeat���� �߰��ȴ�.
//-------------------------------------------------------------
void Zone::addItemToCorpseDelayed(Item* pItem, ObjectID_t corpseItemID)
	throw(Error)
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
// �������� �߰��ϴµ�.. �ٸ� thread���� �ص� �ȴ�.
// �ٸ� heartbeat���� �߰��ȴ�.
//-------------------------------------------------------------
void Zone::addItemDelayed(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature)
	throw(Error)
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

// ���� �׽�Ʈ �� �غ� �ڵ�.
void Zone::deleteItemDelayed(Object* pObject, ZoneCoord_t x, ZoneCoord_t y)
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_OuterRect.ptInRect(x, y));
	Assert(pObject != NULL);

	EffectDeleteItem* pEffectDeleteItem = new EffectDeleteItem(this, x, y, pObject, 0);
	pEffectDeleteItem->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectDeleteItem);
	addEffect_LOCKING(pEffectDeleteItem);

	__END_CATCH
}

//-------------------------------------------------------------
// add Relic Item
//-------------------------------------------------------------
// �������� �߰��ϴµ�.. �ٸ� thread���� �ص� �ȴ�.
// �ٸ� heartbeat���� �߰��ȴ�.
//-------------------------------------------------------------
bool Zone::addRelicItem(int relicIndex)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "[addRelicItem] ZoneID=" << (int)m_ZoneID << ", relicIndex=" << relicIndex << endl;

	const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(relicIndex));

	int cx = pRelicInfo->x;
	int cy = pRelicInfo->y;

	Assert(m_OuterRect.ptInRect(cx, cy));

	// �̹� ���� �����밡 �ִ� ����
	if (m_bHasRelicTable)
	{
		return false;
		// ���� ���� ���� �����븦 ã�´�. (addItem�ɶ� Zone�� ��ǥ x,y�� �����ص���)
        // ���� �����뿡 �ƹ��� ������ ���ٸ� return
        // �ƴϸ�, �ڱ� ������ �ƴ� ������ ������ ���������뿡 �ִ´�.
		// addItemDelayed�� �����ؼ� ������ Zone�� �߰��ع����� �ȴ�.
	}
	else
	{
		// Monster�� �����Ѵ�.
		Monster* pMonster = NULL;
		try {
			pMonster = new Monster(pRelicInfo->monsterType);

			m_ObjectRegistry.registerObject(pMonster);

		} catch (Throwable& ) {
			SAFE_DELETE(pMonster);
			return false;
		}

		//cout << "new Monster OK" << endl;

		// MonsterCorpse�� �����Ѵ�. (���� ������)
		MonsterCorpse* pMonsterCorpse = NULL;
		try {
			pMonsterCorpse = new MonsterCorpse(pMonster);
			pMonsterCorpse->setDir(2);
			pMonsterCorpse->setZone(this);
			pMonsterCorpse->setX(cx);
			pMonsterCorpse->setY(cy);
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

			pMonsterCorpse->getEffectManager().addEffect(pRelicTable);
			pMonsterCorpse->setFlag(Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE);

			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);
		}
		else
		{
			Effect* pRelicTable = new EffectVampireRelicTable(pMonsterCorpse);
			pRelicTable->setNextTime(999999);
			m_ObjectRegistry.registerObject(pRelicTable);

			pMonsterCorpse->getEffectManager().addEffect(pRelicTable);
			pMonsterCorpse->setFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE);

			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);
		}

		// Relic�� �����Ѵ�.
		list<OptionType_t> optionNULL;
		Item* pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_RELIC, relicIndex, optionNULL);
		Assert(pItem!=NULL);

		//cout << "new RelicItem OK" << endl;

		// �� Zone�� RelicTable�� ���� �ִٰ� ǥ���Ѵ�.
		m_bHasRelicTable = true;

		pMonsterCorpse->addTreasure(pItem);

		// �ϴ� relic�� DB�� �����Ѵ�.
		// ���� CGDissectionCorpseHandler���� create���� �ʴ´�.
		// �����뿡�� ���������� create���� �ʰ��ϱ� ���ؼ��̴�.
		pItem->create("", STORAGE_CORPSE, pMonsterCorpse->getObjectID(), 0, 0);

		if (pRelicInfo->relicType==RELIC_TYPE_SLAYER)
		{
			EffectSlayerRelic* pEffect = new EffectSlayerRelic(pMonsterCorpse);
			pMonsterCorpse->getEffectManager().addEffect(pEffect);
			pMonsterCorpse->setFlag(Effect::EFFECT_CLASS_SLAYER_RELIC);
			pEffect->affect(pMonsterCorpse);
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_SLAYER);
		}
		else
		{
			EffectVampireRelic* pEffect = new EffectVampireRelic(pMonsterCorpse);
			pMonsterCorpse->getEffectManager().addEffect(pEffect);
			pMonsterCorpse->setFlag(Effect::EFFECT_CLASS_VAMPIRE_RELIC);
			pEffect->affect(pMonsterCorpse);
			g_pCombatInfoManager->setRelicOwner(relicIndex, CombatInfoManager::RELIC_OWNER_VAMPIRE);
		}

		//cout << "addTreasure OK" << endl;

		// �ٷ� Zone�� �߰��ϸ� �ȵǹǷ�(����ȭ ����)
		// Effect�� �����ؼ� �߰��ϵ��� �Ѵ�.
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
// �������� �����ϴµ�.. �ٸ� thread���� �ص� �ȴ�.
// �ٸ� heartbeat���� �����ȴ�.
//-------------------------------------------------------------
bool Zone::deleteRelicItem()
	throw(Error)
{
	__BEGIN_TRY

	// ���� �����밡 ���ٸ� ����
	if (!m_bHasRelicTable)
	{
		return false;
	}

	// ���� �����븦 ã�´�.
	Item* pItem = dynamic_cast<Item*>(getTile(m_RelicTableX, m_RelicTableY ).getObject(m_RelicTableOID ));
	Assert(pItem != NULL);

	// �ٷ� Zone�� �߰��ϸ� �ȵǹǷ�(����ȭ ����)
	// Effect�� �����ؼ� �߰��ϵ��� �Ѵ�.
	EffectDeleteItem* pEffectDeleteItem = new EffectDeleteItem(this, m_RelicTableX, m_RelicTableY, pItem, 0);
	pEffectDeleteItem->setNextTime(999999);
	m_ObjectRegistry.registerObject(pEffectDeleteItem);

	addEffect_LOCKING(pEffectDeleteItem);

	//cout << "delete Relic OK" << endl;

	m_bHasRelicTable = false;

	return true;

	__END_CATCH
}

//-------------------------------------------------------------
// create MonsterAddPacket
//-------------------------------------------------------------
// monster�� ���¿� ������ GCAddXXX packet�� �����Ѵ�. by sigi
//-------------------------------------------------------------
Packet* Zone::createMonsterAddPacket(Monster* pMonster, Creature* pPC) const
	throw()
{
	Assert(pMonster != NULL);

	// ���� ������ �������� ���� ����
	// ��~ �� �� �ִ� ���¶��� �����Ѵ�.
	// �ϴ� packet�� �����صΰ� üũ�ϱ� ���ؼ���.
	if (pPC != NULL && !canSee(pPC, pMonster ) ) return NULL;
//	bool canSeeAll = (pPC==NULL);

	// ObservingEye ����Ʈ�� �����´�.
//	EffectObservingEye* pEffectObservingEye = NULL;
//	if (pPC != NULL && pPC->isFlag(Effect::EFFECT_CLASS_OBSERVING_EYE ) )
//	{
//		pEffectObservingEye = dynamic_cast<EffectObservingEye*>(pPC->findEffect(Effect::EFFECT_CLASS_OBSERVING_EYE ));
//		//Assert(pEffectObservingEye);
//	}

	if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
	{
		// ���İų� �� �� �ִٸ�..
//		if (canSeeAll
//			|| pPC->isVampire()
//			|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_HIDDEN) )
//			|| (pEffectRevealer != NULL && pEffectRevealer->canSeeHide(pMonster ) ) )
		{
			GCAddBurrowingCreature* pPacket = new GCAddBurrowingCreature();

			pPacket->setObjectID(pMonster->getObjectID());
			pPacket->setName(pMonster->getName());
			pPacket->setX(pMonster->getX());
			pPacket->setY(pMonster->getY());

			return pPacket;
		}

	}
	// ������ ����
	else if (pMonster->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT))
	{
		GCAddBat* pPacket = new GCAddBat();
		pPacket->setObjectID(pMonster->getObjectID());
		pPacket->setName(pMonster->getName());
		pPacket->setXYDir(pMonster->getX(), pMonster->getY(), pMonster->getDir());
		pPacket->setItemType(0);	// ���� �� ����.
		pPacket->setMaxHP(pMonster->getHP(ATTR_MAX));
		pPacket->setCurrentHP(pMonster->getHP(ATTR_CURRENT));
		pPacket->setGuildID(1);
		pPacket->setColor(0);

		return pPacket;
	}
	// ������ ����
	else if (pMonster->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF))
	{
		GCAddWolf* pPacket = new GCAddWolf();
		pPacket->setObjectID(pMonster->getObjectID());
		pPacket->setName(pMonster->getName());
		pPacket->setXYDir(pMonster->getX(), pMonster->getY(), pMonster->getDir());
		pPacket->setItemType(0);	// ���� �� ����.
		pPacket->setMaxHP(pMonster->getHP(ATTR_MAX));
		pPacket->setCurrentHP(pMonster->getHP(ATTR_CURRENT));
		pPacket->setGuildID(1);

		return pPacket;
	}
	// invisiblity ����
	else if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
	{
		// ���̳�? ���İų� ���� �ִٸ�..
//		if (canSeeAll
//			|| pPC->isVampire()
//			|| pPC->isFlag(Effect::EFFECT_CLASS_DETECT_INVISIBILITY)
//			|| (pEffectObservingEye != NULL && pEffectObservingEye->canSeeInvisibility(pMonster ) ) )
		{
			// FIXME
			// ������������ ��� ������ ������ ��..
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
	// �̰� zone delete�Ҷ� �����ߵȵ���.. - -;	by sigi
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
	getCurrentTime(m_LoadValueStartTime);
}

DWORD Zone::getLoadValue() const
{
	Timeval currentTime;
	getCurrentTime(currentTime);

	Timeval elapsedTime = timediff(currentTime, m_LoadValueStartTime);

	if (elapsedTime.tv_sec==0)
	{
		return 200;
	}

	// 10�ʴ� loop��
	DWORD loadValue = m_LoadValue*10 / elapsedTime.tv_sec;

	return loadValue;
}

void Zone::monsterScan(Monster* pMonster, ZoneCoord_t x, ZoneCoord_t y, Dir_t dir)
	throw(Error)
{
	__BEGIN_TRY

//#ifdef __MONSTER_FIGHTING__

	// [TEST CODE]

	switch (pMonster->getMonsterType() )
	{
		case 717:
		case 721:
		case 723:
		case 724:
		case 725:
			{
				map<ObjectID_t, Creature*>::iterator itr = m_pPCManager->getCreatures().begin();
				map<ObjectID_t, Creature*>::iterator endItr = m_pPCManager->getCreatures().end();

				for (; itr != endItr ; ++itr )
				{
					pMonster->addPotentialEnemy(itr->second);
				}
				break;
			}
		default:
			break;
	}

	ZoneCoord_t x2 = x;
	ZoneCoord_t y2 = y;

	//////////////////////////////////////////////////////////////////////////////
	// �þ� ������ �����¿� ���� + 1 �� ������Ų��.
	// ������ ���⿡ ���� ON_SIGHT ������ �����Ǳ� �����̴�.
	//////////////////////////////////////////////////////////////////////////////
	int sight = pMonster->getSight();

	for (ZoneCoord_t ix = max(0, x2 - sight - 1), endx = min(m_Width - 1, x2 + sight + 1) ; ix <= endx ; ix++)
	{
		for (ZoneCoord_t iy = max(0, y2 - sight - 1), endy = min(m_Height - 1, y2 + sight + 1) ; iy <= endy ; iy++)
		{
			//if (pPC->isFlag(Effect::EFFECT_CLASS_DARKNESS)) sight = DARKNESS_SIGHT;

			// ���� Ÿ�� ���� �ִ� ���� ������Ʈ�鿡 ���� �ݺ��Ѵ�.
			//const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();
			const list<Object*> & objectList = m_pTiles[ix][iy].getObjectList();

			list<Object*>::const_iterator itr = objectList.begin();

			//
			// object�� �ִ� ���츸
			// pVisionInfo->getVisionState()�� üũ �ϱ� ���ؼ�
			// if - do~while �� �����ߴ�. by sigi. 2002.5.8
			//
			if (itr != objectList.end())
			{
				do
				{
					Assert(*itr != NULL);

					Object::ObjectClass OClass = (*itr)->getObjectClass();

					////////////////////////////////////////////////////////////
					// �� ��ü�� OBJECT CLASS�� ������ ������ GCAddXXX ��Ŷ��
					// ����� owner ���� �����Ѵ�.
					////////////////////////////////////////////////////////////

					////////////////////////////////////////////////////////////
					// Ÿ�� ���� ũ��ó�� ���� ����
					////////////////////////////////////////////////////////////
					if (OClass == Object::OBJECT_CLASS_CREATURE)
					{
						Creature* pCreature = dynamic_cast<Creature*>(*itr);
						Assert(pCreature != NULL);

						Creature::CreatureClass CClass = pCreature->getCreatureClass();

						if (pCreature->isPC())
						{
							if (pMonster->isEnemyToAttack(pCreature ))
							{
								pMonster->addPotentialEnemy(pCreature);
							}
						}
						else if (CClass == Creature::CREATURE_CLASS_MONSTER)
						{
							Monster* pOtherMonster = dynamic_cast<Monster*>(pCreature);

							VisionState vs = pOtherMonster->getVisionState(x2,y2);

							// Aggressive �����Ϳ��Ը� ������ ���Ͻ����ش�.
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
				} while (++itr != objectList.end()); // do
			}	// if (itr != objectList.end())
		}	// for iy
	}	// for ix

//#endif

	__END_CATCH
}

/*
void Zone::setNPCMarketCondition(MarketCond_t NPCSell, MarketCond_t NPCBuy)
	throw(Error)
{
	__BEGIN_TRY

	map<ObjectID_t, Creature*> NPCMap = m_pNPCManager->getCreatures();
	for (map<ObjectID_t, Creature*>::const_iterator i = NPCMap.begin(); i != NPCMap.end(); i++)
	{
		NPC* pNPC = dynamic_cast<NPC*>(i->second);

		pNPC->setMarketCondBuy(NPCBuy);
		pNPC->setMarketCondSell(NPCSell);

		pNPC->increaseShopVersion(SHOP_RACK_SPECIAL);
	}

	__END_CATCH
}
*/


bool Zone::deleteNPC(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	if (pCreature==NULL
		|| !pCreature->isNPC())
		return false;

	try {

		deleteCreature(pCreature, pCreature->getX(), pCreature->getY());
		g_pPCFinder->deleteNPC(pCreature->getName());

	} catch (NoSuchElementException) {
		cout << "NoSuchNPC : " << pCreature->getName().c_str() << ", (" << pCreature->getX() << ", " << pCreature->getY() << ")" << endl;

		return false;
	}

	NPC* pNPC = dynamic_cast<NPC*>(pCreature);
	removeNPCInfo(pNPC);

	SAFE_DELETE(pCreature);

	return true;

	__END_CATCH
}

void Zone::sendNPCInfo()
	throw(Error)
{
	__BEGIN_TRY

	// NPC�� ���� ������ Ŭ���̾�Ʈ���� �����ش�.
	GCNPCInfo gcNPCInfo;

	list<NPCInfo*>::const_iterator itr = m_NPCInfos.begin();
	for (; itr != m_NPCInfos.end(); itr++)
	{
		NPCInfo* pInfo = *itr;
		gcNPCInfo.addNPCInfo(pInfo);
	}

	broadcastPacket(&gcNPCInfo);

	__END_CATCH
}


void Zone::loadNPCs(Race_t race)
	throw(Error)
{
	__BEGIN_TRY

	m_pNPCManager->load(getZoneID(), race);

	sendNPCInfo();

	__END_CATCH
}

void Zone::deleteNPCs(Race_t race)
	throw(Error)
{
	__BEGIN_TRY

	const map< ObjectID_t, Creature* >& NPCs = m_pNPCManager->getCreatures();	// hash_map�� �����ؼ� �����Ѵ�.
	map< ObjectID_t, Creature* >::const_iterator itr = NPCs.begin();

	list<ObjectID_t> creatures;

	// �ϴ� ObjectID���� �����صд�.
	for (; itr!=NPCs.end(); itr++)
	{
		Creature* pCreature = itr->second;
		creatures.push_back(pCreature->getObjectID());
	}

	list<ObjectID_t>::iterator oitr = creatures.begin();

	// NPC�� ������.
	for (; oitr!=creatures.end(); oitr++)
	{
		Creature* pCreature = m_pNPCManager->getCreature(*oitr);

		if (pCreature!=NULL)
		{
			Assert(pCreature->isNPC());

			NPC* pNPC = dynamic_cast<NPC*>(pCreature);

			if (pNPC->getRace()==race)
			{
				deleteNPC(pCreature);
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

		if (pNPCInfo->getNPCID() == pNPC->getNPCID() )
		{
			SAFE_DELETE(pNPCInfo);
			m_NPCInfos.erase(itr);

			return true;
		}
	}

	return false;

	__END_CATCH
}

void Zone::loadEffect()
	throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result*	pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		///////////////////////////////////////////////////////////////////////////////
		// EffectPKZoneRegen �ε�
		///////////////////////////////////////////////////////////////////////////////
		pResult = pStmt->executeQuery("SELECT LeftX, TopY, RightX, BottomY FROM EffectPKZoneRegen WHERE ZoneID=%u", getZoneID());

		while (pResult->next())
		{
			int count = 0;

			ZoneCoord_t left = pResult->getInt(++count);
			ZoneCoord_t top = pResult->getInt(++count);
			ZoneCoord_t right = pResult->getInt(++count);
			ZoneCoord_t bottom = pResult->getInt(++count);

			EffectPKZoneRegen *pEffect = new EffectPKZoneRegen(this, left, top, right, bottom);
			pEffect->setSlayer();
			pEffect->setVampire();
			pEffect->setOusters();
			pEffect->setTurn(10);
			pEffect->setHP(40);
			pEffect->setNextTime(0);

			registerObject(pEffect);
			addEffect(pEffect);
		}

		///////////////////////////////////////////////////////////////////////////////
		// Gnome's Horn�� Waypoint �ε�
		// WayPoint ������ 3X3 Ÿ�Ͽ� �ִ� �ƿ콺������ �ʴ� 1�� HP,MP �� ȸ���ȴ�.
		///////////////////////////////////////////////////////////////////////////////
		pResult = pStmt->executeQuery("SELECT X, Y FROM WayPointInfo WHERE ZoneID = %u AND Race = %d", getZoneID(), RACE_OUSTERS);

		while (pResult->next() )
		{
			ZoneCoord_t X = pResult->getInt(1);
			ZoneCoord_t Y = pResult->getInt(2);

			if (isValidZoneCoord(this, X-1, Y-1 )
				&& isValidZoneCoord(this, X+1, Y+1 )
			   )
			{
				EffectPKZoneRegen *pEffect = new EffectPKZoneRegen(this, X-1, Y-1, X+1, Y+1);
				pEffect->setOusters();
				pEffect->setTurn(10);
				pEffect->setHP(4);
				pEffect->setNextTime(0);

				registerObject(pEffect);
				addEffect(pEffect);
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

//	if (m_ZoneID == 3001 || m_ZoneID == 71 || m_ZoneID == 72 || m_ZoneID == 73 )
	g_pEffectLoaderManager->load(this);

	if (m_ZoneID == 3002 )
	{
		EffectContinualGroundAttack* pEffect = new EffectContinualGroundAttack(this, Effect::EFFECT_CLASS_GROUND_ATTACK, 3);
		pEffect->setDeadline(99999999);
		pEffect->setNumber(7, 11);

		registerObject(pEffect);
		addEffect(pEffect);
	}

	__END_CATCH
}

void Zone::releaseSafeZone()
	throw()
{
	__BEGIN_TRY

	m_ZoneLevel = NO_SAFE_ZONE;

	// �� ������ �ʱ�ȭ��Ų��.
	for (ZoneCoord_t x = 0; x < m_Width; x++)
		for (ZoneCoord_t y = 0; y < m_Height; y++)
			m_ppLevel[x][y] = m_ZoneLevel;

	__END_CATCH
}

void Zone::resetSafeZone()
	throw()
{
	__BEGIN_TRY

	m_ZoneLevel = g_pZoneInfoManager->getZoneInfo(m_ZoneID )->getZoneLevel();

	// �� ������ �ʱ�ȭ��Ų��.
	for (ZoneCoord_t x = 0; x < m_Width; x++)
		for (ZoneCoord_t y = 0; y < m_Height; y++)
			m_ppLevel[x][y] = m_ZoneLevel;

	__END_CATCH
}

void Zone::resetDarkLightInfo()
	throw()
{
	__BEGIN_TRY

	m_pWeatherManager->resetDarkLightInfo();

	__END_CATCH
}

void
Zone::killAllMonsters()
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map< ObjectID_t, Creature* > & monsters = m_pMonsterManager->getCreatures();
	map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		if (!pMonster->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
		{
			pMonster->setHP(0);
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void
Zone::killAllMonsters_UNLOCK()
	throw(Error)
{
	__BEGIN_TRY

	map< ObjectID_t, Creature* > & monsters = m_pMonsterManager->getCreatures();
	map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

	for (; itr!=monsters.end(); itr++)
	{
		Creature* pCreature = itr->second;
		Monster* pMonster = dynamic_cast<Monster*>(pCreature);

		if (!pMonster->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
		{
			pMonster->setHP(0);
		}
	}

	__END_CATCH
}

void Zone::killAllPCs() throw(Error)
{
	__BEGIN_TRY

	map< ObjectID_t, Creature* > & pcs = m_pPCManager->getCreatures();
	map< ObjectID_t, Creature* >::iterator itr = pcs.begin();

	for (; itr!=pcs.end(); itr++)
	{
		Creature* pCreature = itr->second;

		if (pCreature->isSlayer() )
		{
			dynamic_cast<Slayer*>(pCreature)->setHP(0);
		}
		else if (pCreature->isVampire() )
		{
			dynamic_cast<Vampire*>(pCreature)->setHP(0);
		}
		else if (pCreature->isOusters() )
		{
			dynamic_cast<Ousters*>(pCreature)->setHP(0);
		}
	}

	__END_CATCH
}

// ���� ���￡ �����ϴ� ������ ������. �������� kick�Ѵ�.
void    Zone::remainRaceWarPlayers()
	throw(Error)
{
	__BEGIN_TRY

	try {

	// ���� �ο� ������ ���� �ʴ´ٸ� �����Ѵ�.
	if (!g_pVariableManager->isActiveRaceWarLimiter())
		return;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	map< ObjectID_t, Creature* > & creatures = m_pPCManager->getCreatures();
	map< ObjectID_t, Creature* >::iterator itr = creatures.begin();

	for (; itr!=creatures.end(); itr++)
	{
		Creature* pCreature = itr->second;

		if (pCreature->isFlag(Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET ))
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
			g_pResurrectLocationManager->getPosition(pPC, ZC);

			ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(ZC.id);
			Assert(pZoneInfo!=NULL);

			EventTransport* pEventTransport = new EventTransport(pGamePlayer);

			pEventTransport->setDeadline(15*10);
			pEventTransport->setTargetZone(ZC.id, ZC.x, ZC.y);
			pEventTransport->setZoneName(pZoneInfo->getFullName());

			// �� ���Ŀ� ������ �̵��Ѵ�.�� �����ش�.
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
	switch (m_ZoneID )
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
    throw(Error)
{
	__BEGIN_TRY

	try {

		map< ObjectID_t, Creature* > & creatures = m_pPCManager->getCreatures();
		map< ObjectID_t, Creature* >::iterator itr = creatures.begin();

		for (; itr!=creatures.end(); itr++)
		{
			Creature* pCreature = itr->second;
			Player* pPlayer = pCreature->getPlayer();
			Assert(pPlayer != NULL);

			GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

			if (pGamePlayer->isPayPlaying() )
				continue;

			Event* pEvent = pGamePlayer->getEvent(Event::EVENT_CLASS_TRANSPORT);
			if (pEvent==NULL)
			{
				PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
				Assert(pPC!=NULL);

				ZONE_COORD   ZC;
				g_pResurrectLocationManager->getPosition(pPC, ZC);

				ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(ZC.id);
				Assert(pZoneInfo!=NULL);

				EventTransport* pEventTransport = new EventTransport(pGamePlayer);

				pEventTransport->setDeadline(60*10);
				pEventTransport->setTargetZone(ZC.id, ZC.x, ZC.y);
				pEventTransport->setZoneName(pZoneInfo->getFullName());

				char msg[100];

				sprintf(msg, g_pStringPool->c_str(STRID_LEVEL_WAR_ZONE_FREE_CLOSE_1 ));

				GCSystemMessage gcSystemMessage;
				gcSystemMessage.setMessage(msg);
				pPlayer->sendPacket(&gcSystemMessage);

				sprintf(msg, g_pStringPool->c_str(STRID_LEVEL_WAR_ZONE_FREE_CLOSE_2 ),
				pZoneInfo->getFullName().c_str());

				gcSystemMessage.setMessage(msg);
				pPlayer->sendPacket(&gcSystemMessage);

				// �� ���Ŀ� ������ �̵��Ѵ�.�� �����ش�.
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

