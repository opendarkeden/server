//////////////////////////////////////////////////////////////////////////////
// FileName 	: Zone.h
// Written By	: Reiot
// Description	:
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZONE_H__
#define __ZONE_H__

#include "Types.h"
#include "Exception.h"
#include "Tile.h"
#include "Sector.h"
#include "ObjectRegistry.h"
#include "Mutex.h"
#include "Effect.h"
#include "Party.h"
#include "PCManager.h"
#include "Encrypter.h"
#include <queue>
#include <vector>
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class ZoneGroup;
class NPC;
class NPCManager;
class MonsterManager;
class PCManager;
class Slayer;

class MasterLairManager;
class WarScheduler;
//class EventMonsterManager;

class EffectManager;
class NPCInfo;
class WeatherManager;
class Creature;
class Vampire;
class Monster;
class Item;
class VampirePortalItem;
class EffectVampirePortal;
class EffectScheduleManager;
class TradeManager;
class Motorcycle;
class LevelWarManager;
class DynamicZone;

//////////////////////////////////////////////////////////////////////////////
// 존의 타입
//////////////////////////////////////////////////////////////////////////////
enum ZoneType 
{
	ZONE_NORMAL_FIELD,           // 일반 필드
	ZONE_NORMAL_DUNGEON,         // 일반 던전
	ZONE_SLAYER_GUILD,           // 슬레이어 길드
	ZONE_RESERVED_SLAYER_GUILD,  // ...
	ZONE_PC_VAMPIRE_LAIR,        // PC 뱀파이어 레어
	ZONE_NPC_VAMPIRE_LAIR,       // NPC 뱀파이어 레어
	ZONE_NPC_HOME,               // ...
	ZONE_NPC_SHOP,               // ...
	ZONE_RANDOM_MAP,             // -_-;
	ZONE_CASTLE,               	 // 성
};

//////////////////////////////////////////////////////////////////////////////
// 존의 접근모드
//////////////////////////////////////////////////////////////////////////////
enum ZoneAccessMode 
{
	PUBLIC = 0, 	// 아무나 들어올 수 있는 존이다.
	PRIVATE			// 지정된 사람만이 들어올 수 있는 존이다.(길드존,레어 등)
};

//////////////////////////////////////////////////////////////////////////////
// Move type for darkness
//////////////////////////////////////////////////////////////////////////////
#define INTO_DARKNESS   0
#define OUTER_DARKNESS  1
#define IN_DARKNESS     2
#define OUT_DARKNESS    3




//////////////////////////////////////////////////////////////////////////////
//
// class Zone;
//
//////////////////////////////////////////////////////////////////////////////

class Zone 
{
public: // constructor & destructor
	Zone(ZoneID_t zoneID) ;
	Zone(ZoneID_t zoneID, ZoneCoord_t width, ZoneCoord_t height) ;
	~Zone() ;

public:
	void init() ;
	void load(bool bOutput=false) ;
	void reload(bool bOutput=false) ;
	void loadItem() ;
	void loadTriggeredPortal() ;
	void initSpriteCount() ;
	void save() ;

public:
	void pushPC(Creature* pCreature) ;
	void addPC(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir) ;
	void addPC(Creature* pCreature) ;
	void addCreature(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir) ;
	TPOINT addItem(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature=true, Turn_t decayTurn=0, ObjectID_t DropPetOID=0) ; 
	Item* getItem(ObjectID_t id) const ;
	void addEffect(Effect* pEffect) ;	
	void deleteEffect(ObjectID_t id) ;	
	Effect* findEffect(Effect::EffectClass eid) ;	

	// by sigi. 2002.5.4
	void addEffect_LOCKING(Effect* pEffect) ;	
	void deleteEffect_LOCKING(ObjectID_t id) ;	

	void deletePC(Creature* pCreature) ;//NoSuchElementException, Error);
	void deleteQueuePC(Creature* pCreature) ;
	void deleteCreature(Creature* pCreature, ZoneCoord_t x, ZoneCoord_t y) ;
	void deleteObject(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) ;
	void deleteItem(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) ;

	bool deleteNPC(Creature* pCreature) ;//NoSuchElementException, Error);
	void deleteNPCs(Race_t race) ;//NoSuchElementException, Error);
	void loadNPCs(Race_t race) ;//NoSuchElementException, Error);
	void sendNPCInfo() ;

	void loadEffect() ;


public:
	void movePC(Creature* pCreature, ZoneCoord_t nx, ZoneCoord_t ny, Dir_t dir) ;
	void moveCreature(Creature* pCreature, ZoneCoord_t nx, ZoneCoord_t ny, Dir_t dir) ;

	// 몬스터가 주변을 스캔한다.
	void monsterScan(Monster* pMonster, ZoneCoord_t x, ZoneCoord_t y, Dir_t dir) ;

	void broadcastPacket(Packet* pPacket, Creature* owner = NULL) ;
	void broadcastPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, Creature* owner = NULL, bool Plus = false, Range_t Range = 0) ;
	void broadcastPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, const list<Creature *> & creatureList, bool Plus = false, Range_t Range = 0) ;
	void broadcastDarkLightPacket(Packet* pPacket1, Packet* pPacket2, Creature* owner = NULL) ;
	void broadcastSayPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, Creature* owner = NULL, bool isVampire = false) ;
	void broadcastLevelWarBonusPacket(Packet* pPacket, Creature* owner = NULL) ;
	list<Creature*> broadcastSkillPacket(ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, Packet* pPacket, list<Creature*> creatureList, bool bConcernDarkness = true) ;

	//(x,y) 타일 위에 있는 PC 에게 주변 정보를 읽어서 전송한다. pPacket 이 NULL 이 아니라면, 동시에 브로드캐스트도 담당한다.
	void scan(Creature* pPC, ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket) ;
	
	// 제자리에서 시야가 변경된 경우 주변 정보를 다시 보내준다.
	void updateScan(Creature* pPC, Sight_t oldSight, Sight_t newSight) ;

	// 그곳을 볼 수 있는 넘들(Player)의 list를 돌려준다.�
	list<Creature*>  getWatcherList(ZoneCoord_t, ZoneCoord_t, Creature* pTargetCreature = NULL) ;

	// 리젠된 몬스터가 주변의 PC 들에게 GCAddXXX 패킷을 브로드캐스트하면서동시에 그들을 잠재적인 적으로 인식하도록 한다.
	void scanPC(Creature* pCreature) ;

	// 제자리에서 hidden creature에 대한 update가 필요한 경우.
	void updateHiddenScan(Creature* pCreature) ;
	
	// 제자리에서 install mine에 대한 update가 필요한 경우.
	void updateMineScan(Creature* pCreature) ;
	
    // 제자리에서 invisible creature에 대한 update가 필요한 경우.
	void updateInvisibleScan(Creature* pCreature) ;

    // 제자리에서 hide,invisible creature에 대한 update가 필요한 경우.
	void updateDetectScan(Creature* pCreature) ;

	// PC 가 P(x1,y1)에서 Q(x2,y2)로 이동했음을 주변에 브로드캐스트한다.
	void movePCBroadcast(Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove = true, bool bKnockback=false) ;

	// !PC 가 P(x1,y1)에서 Q(x2,y2)로 이동했음을 주변에 브로드캐스트한다.
	void moveCreatureBroadcast(Creature* pCreature, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove = true, bool bKnockback=false) ;
	
	// PC 가 P(x1,y1)에서 Q(x2,y2)로 이동했음을 주변에 브로드캐스트한다.
	bool moveFastPC(Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType) ;
	bool moveFastMonster(Monster* pMonster, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType) ;

	// 전쟁시 성 안은 안전지대가 되었다가 말았다가 한다. 존을 세이프존이 아니게 만들거나 원상복구시큽다.
	void releaseSafeZone() ;
	void resetSafeZone() ;

	// 오브젝트 등록
	void registerObject( Object* pObject )  { getObjectRegistry().registerObject( pObject ); }

public:
	void heartbeat() ;

	// 이름, 크리처 클래스, OID 등을 이용해서 존에 존재하는 크리쳐 객체에 접근
	Creature* getCreature(const string& Name) const ;//NoSuchElementException, Error);
	Creature* getCreature(ObjectID_t objectID) const ;//NoSuchElementException, Error);
	Creature* getCreature(Creature::CreatureClass creatureClass, ObjectID_t objectID) const ;


public:
	void lock()  { m_Mutex.lock(); }
	void unlock()  { m_Mutex.unlock(); }

	// get debug string
	string toString() const ;

public:
	ObjectRegistry & getObjectRegistry()  { return m_ObjectRegistry; }

	const Tile & getTile(ZoneCoord_t x, ZoneCoord_t y) const ;
	Tile & getTile(ZoneCoord_t x, ZoneCoord_t y) ;

	Sector* getSector(ZoneCoord_t x, ZoneCoord_t y) ;

	ZoneID_t getZoneID() const  { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID)  { m_ZoneID = zoneID; }
	
	ZoneGroup* getZoneGroup() const  { return m_pZoneGroup; }
	void setZoneGroup(ZoneGroup* pZoneGroup)  { m_pZoneGroup = pZoneGroup; }

	ZoneType getZoneType() const  { return m_ZoneType; }
	void setZoneType(ZoneType zoneType)  { m_ZoneType = zoneType; }

	ZoneLevel_t getZoneLevel() const  { return m_ZoneLevel; }
	void setZoneLevel(ZoneLevel_t zoneLevel)  { m_ZoneLevel = zoneLevel; }
    ZoneLevel_t getZoneLevel(ZoneCoord_t x, ZoneCoord_t y) const ;

	ZoneAccessMode getZoneAccessMode() const  { return m_ZoneAccessMode; }
	void setZoneAccessMode(ZoneAccessMode zoneAccessMode)  { m_ZoneAccessMode = zoneAccessMode; }

	string getOwnerID() const  { return m_OwnerID; }
	void setOwnerID(const string & ownerID)  { m_OwnerID = ownerID; }

	DarkLevel_t getDarkLevel() const  { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel)  { m_DarkLevel = darkLevel; }

	LightLevel_t getLightLevel() const  { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel)  { m_LightLevel = lightLevel; }

	const WeatherManager* getWeatherManager() const  { return m_pWeatherManager; }

	uint getNPCCount() const  { return m_NPCCount; }
	void setNPCCount(uint n)  { Assert(n <= maxNPCPerZone); m_NPCCount = n; }

	NPCType_t getNPCType(uint n) const  { Assert(n < maxNPCPerZone); return m_NPCTypes[n]; }
	void setNPCType(uint n, NPCType_t npcType)  { Assert(n < maxNPCPerZone); m_NPCTypes[n] = npcType; }

	uint getMonsterCount() const  { return m_MonsterCount; }
	void setMonsterCount(uint n)  { Assert(n <= maxMonsterPerZone); m_MonsterCount = n; }

	MonsterType_t getMonsterType(uint n) const  { Assert(n < maxMonsterPerZone); return m_MonsterTypes[n]; }
	void setMonsterType(uint n, MonsterType_t npcType)  { Assert(n < maxMonsterPerZone); m_MonsterTypes[n] = npcType; }

	ZoneCoord_t getWidth() const  { return m_Width; }
	ZoneCoord_t getHeight() const  { return m_Height; }

	uint getTimeband() const { return m_Timeband; }
	void setTimeband( uint timeband ) { m_Timeband = timeband; }

	bool isTimeStop() { return m_bTimeStop; }
	void stopTime() { m_bTimeStop = true; }
	void resumeTime() { m_bTimeStop = false; }

	void resetDarkLightInfo() ;

	// ABCD add item to item hash map
	void addToItemList(Item* pItem) ;
	void deleteFromItemList(ObjectID_t id) ;
	unordered_map<ObjectID_t, Item*> getItems(void)  { return m_Items; }

	EffectManager* getEffectManager()  { return m_pEffectManager; }
	EffectManager* getVampirePortalManager()  { return m_pVampirePortalManager; }
	EffectScheduleManager* getEffectScheduleManager(void)  { return m_pEffectScheduleManager; }

	VSRect* getOuterRect(void) { return &m_OuterRect; }
	VSRect* getInnerRect(void) { return &m_InnerRect; }
	VSRect* getCoreRect(void) { return &m_CoreRect; }

	list<NPCInfo*>* getNPCInfos(void);
	void addNPCInfo(NPCInfo* pInfo);
	bool removeNPCInfo(NPC* pNPC);

	// 존 전체의 NPC에게 MarketCondition을 설정한다. default(100, 25)
	//void setNPCMarketCondition(MarketCond_t NPCSell, MarketCond_t NPCBuy) ;

	void addVampirePortal(ZoneCoord_t cx, ZoneCoord_t cy, Vampire* pVampire, const ZONE_COORD& ZoneCoord) ;
	void deleteMotorcycle(ZoneCoord_t cx, ZoneCoord_t cy, Motorcycle* pMotorcycle) ;

	void addItemDelayed(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature=true) ;
	void addItemToCorpseDelayed(Item* pItem, ObjectID_t corpseObjectID) ;
	void deleteItemDelayed(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) ;
	void transportItem(ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy) ;
	void transportItemToCorpse(Item* pItem, Zone* pTargetZone, ObjectID_t corpseObjectID) ;

	LocalPartyManager* getLocalPartyManager(void) const { return m_pLocalPartyManager; }
	PartyInviteInfoManager* getPartyInviteInfoManager(void) const { return m_pPartyInviteInfoManager; }
	
	TradeManager* getTradeManager(void) const { return m_pTradeManager; }


	// pPC가 pMonster를 볼때 Monster는 어땠 packet으로 add되는가?
	// pPC가 NULL인 경우 다 보이는 상태라고 가정한다.
	Packet*	createMonsterAddPacket(Monster* pMonster, Creature* pPC) const ;

	// 몹 생성 좌표
	const BPOINT& getRandomMonsterRegenPosition() const;
	const BPOINT& getRandomEmptyTilePosition() const;

	MonsterManager* getMonsterManager(void) const { return m_pMonsterManager; }
	MasterLairManager* getMasterLairManager(void) const { return m_pMasterLairManager; }
	WarScheduler* getWarScheduler(void) const { return m_pWarScheduler; }
	LevelWarManager* getLevelWarManager() const { return m_pLevelWarManager; }

	void	killAllMonsters() ;
	void	killAllMonsters_UNLOCK() ;

	void	killAllPCs() ;

	const PCManager*  getPCManager() const		{ return m_pPCManager; }             // PC Manager 
	WORD getPCCount(void) const  { return m_pPCManager->getSize(); }

#ifdef __USE_ENCRYPTER__
	// get zone's encrypt code
	uchar getEncryptCode() const { return m_EncryptCode; }
#endif

public :
	// 유료화
	bool isPayPlay() const  { return m_bPayPlay; }
    void setPayPlay(bool bPayPlay=true)  { m_bPayPlay = bPayPlay; }

	bool isPremiumZone() const  { return m_bPremiumZone; }
	void setPremiumZone(bool bPremiumZone=true)  { m_bPremiumZone = bPremiumZone; }

	bool isPKZone() const  { return m_bPKZone; }
	void setPKZone(bool bPKZone=true)  { m_bPKZone = bPKZone; }

	bool isNoPortalZone() const  { return m_bNoPortalZone; }
	void setNoPortalZone(bool bNoPortalZone=true)  { m_bNoPortalZone = bNoPortalZone; }

	bool isMasterLair() const  { return m_bMasterLair; }
	void setMasterLair(bool bMasterLair=true)  { m_bMasterLair = bMasterLair; }

	bool isCastle() const  { return m_bCastle; }
	void setCastle(bool bCastle=true)  { m_bCastle = bCastle; }

	bool isHolyLand() const  { return m_bHolyLand; }
	void setHolyLand(bool bHolyLand=true)  { m_bHolyLand = bHolyLand; }

	bool isCastleZone() const  { return m_bCastleZone; }
	void setCastleZone(bool bCastleZone=true)  { m_bCastleZone = bCastleZone; }

	// Relic보관대를 갖고 있나?
	bool hasRelicTable() const  { return m_bHasRelicTable; }
    void setRelicTable(bool bHasRelicTable=true)  { m_bHasRelicTable = bHasRelicTable; }

	bool addRelicItem(int relicIndex) ; 
	bool deleteRelicItem() ; 

	// Holy Land Race Bonus 변화에 따른 플레이어 refresh
	void setRefreshHolyLandPlayer( bool bRefresh ) { m_pPCManager->setRefreshHolyLandPlayer( bRefresh ); }
//	void setRefreshLevelWarBonusZonePlayer( bool bRefresh ) { m_pPCManager->setRefreshLevelWarBonusZonePlayer( bRefresh ); }

	void    remainRaceWarPlayers() ;

	void    remainPayPlayer() ;

	bool isLevelWarZone() const;

public :
	void   initLoadValue();
	DWORD  getLoadValue() const;

public:
	bool			isDynamicZone() const { return m_pDynamicZone != NULL; }
	void			setDynamicZone( DynamicZone* pDynamicZone ) { m_pDynamicZone = pDynamicZone; }
	DynamicZone*	getDynamicZone() const { return m_pDynamicZone; }

////////////////////////////////////////////////////////////
// member data
////////////////////////////////////////////////////////////
private:
	// 존의 기본 적인 정보
	ZoneID_t       m_ZoneID;           // zone id
	ZoneGroup*     m_pZoneGroup;       // parent zone group
	ZoneType       m_ZoneType;         // 존 타입(존 타입이 바�低� DB에 저장되어야 한다.)
	ZoneLevel_t    m_ZoneLevel;        // 존의 레벨.
	ZoneAccessMode m_ZoneAccessMode;   // 존에 대한 접근 모드 { PUBLIC | PRIVATE }
	string         m_OwnerID;          // 존 소유자 아이디(슬레이어 길드 아이디 혹은 뱀파이어 마스터 아이디)
	DarkLevel_t    m_DarkLevel;        // 존의 어둡기
	LightLevel_t   m_LightLevel;       // 존의 빛의 크기
	ZoneCoord_t    m_Width;            // 존의 가로 크기
	ZoneCoord_t    m_Height;           // 존의 세로 크기
	Tile**         m_pTiles;           // 타일의 이차원 배열
	ZoneLevel_t**  m_ppLevel;          // 존 레벨의 이차원 배열
	Sector**       m_pSectors;          // 섹터의 이차원 배열
	int            m_SectorWidth;      // 섹터의 크기
	int            m_SectorHeight;     // 섹터의 크기
	
	// 각종 매니저들
	PCManager*             m_pPCManager;             // PC Manager 
	NPCManager*            m_pNPCManager;            // NPC Manager
	MonsterManager*        m_pMonsterManager;        // Monster Manager

//	EventMonsterManager*   m_pEventMonsterManager;

	EffectManager*         m_pEffectManager;         // effect manager
	EffectManager*         m_pVampirePortalManager;  // effect manager
	EffectManager*         m_pLockedEffectManager;   // effect manager
	EffectScheduleManager* m_pEffectScheduleManager;
	list<NPCInfo*>         m_NPCInfos;               // npc infos
	WeatherManager*        m_pWeatherManager;        // 존의 날씨

	// 존에 출현하는 NPC 스프라이트 타입의 리스트
	BYTE m_NPCCount;
	NPCType_t m_NPCTypes[ maxNPCPerZone ];

	// 존에 출현하는 몬스터 스프라이트 타입의 리스트
	BYTE m_MonsterCount;
	MonsterType_t m_MonsterTypes[ maxMonsterPerZone ];

	// object registery
	ObjectRegistry m_ObjectRegistry;

	// 존에 새로 들어갈 PC들의 큐
	queue< Creature* > m_PCQueue;
	list< Creature* > m_PCListQueue;

	// zone바닥에 떨어진 item hashmap
	unordered_map<ObjectID_t, Item*> m_Items;
	
	// Monster AI를 위해 존의 영역을 구분지어 놓은 사각형들...
	VSRect m_OuterRect;
	VSRect m_InnerRect;
	VSRect m_CoreRect;

	LocalPartyManager* m_pLocalPartyManager;
	PartyInviteInfoManager* m_pPartyInviteInfoManager;
	TradeManager* m_pTradeManager;
	
	// 몹 생성 좌표를 위한 정보.
	vector<BPOINT> m_MonsterRegenPositions;
	vector<BPOINT> m_EmptyTilePositions;

	// mutex
	mutable Mutex m_Mutex;
	mutable Mutex m_MutexEffect;

	// 유료화 관련
	bool m_bPayPlay;
	bool m_bPremiumZone;

	// 기타 정보
	bool m_bPKZone;
	bool m_bNoPortalZone;
	bool m_bMasterLair;
	bool m_bCastle;
	bool m_bHolyLand;
	bool m_bCastleZone;

	// 전쟁 중?
	bool m_bHasRelicTable;

	// Relic Table 관련 정보
	ObjectID_t m_RelicTableOID;
	ZoneCoord_t m_RelicTableX;
	ZoneCoord_t m_RelicTableY;

	Timeval	m_LoadValueStartTime;
	DWORD  m_LoadValue;

	// 마스터 레어. by sigi.2002.9.2
	MasterLairManager* 	m_pMasterLairManager;

	// 전쟁 관리 by sigi. 2003.1.24
	WarScheduler* 		m_pWarScheduler;

	LevelWarManager*	m_pLevelWarManager;

	// by sigi. for debugging. 2002.12.23
	int m_LastItemClass;

	// Zone Timeband
	uint m_Timeband;

	bool m_bTimeStop;

	Timeval m_UpdateTimebandTime;

#ifdef __USE_ENCRYPTER__
	// zone's encrypt code
	uchar	m_EncryptCode;
#endif

	DynamicZone*	m_pDynamicZone;		// 인던 정보
};	

#endif
