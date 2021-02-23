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
// Á¸ÀÇ Å¸ÀÔ
//////////////////////////////////////////////////////////////////////////////
enum ZoneType 
{
	ZONE_NORMAL_FIELD,           // ÀÏ¹Ý ÇÊµå
	ZONE_NORMAL_DUNGEON,         // ÀÏ¹Ý ´øÀü
	ZONE_SLAYER_GUILD,           // ½½·¹ÀÌ¾î ±æµå
	ZONE_RESERVED_SLAYER_GUILD,  // ...
	ZONE_PC_VAMPIRE_LAIR,        // PC ¹ìÆÄÀÌ¾î ·¹¾î
	ZONE_NPC_VAMPIRE_LAIR,       // NPC ¹ìÆÄÀÌ¾î ·¹¾î
	ZONE_NPC_HOME,               // ...
	ZONE_NPC_SHOP,               // ...
	ZONE_RANDOM_MAP,             // -_-;
	ZONE_CASTLE,               	 // ¼º
};

//////////////////////////////////////////////////////////////////////////////
// Á¸ÀÇ Á¢±Ù¸ðµå
//////////////////////////////////////////////////////////////////////////////
enum ZoneAccessMode 
{
	PUBLIC = 0, 	// ¾Æ¹«³ª µé¾î¿Ã ¼ö ÀÖ´Â Á¸ÀÌ´Ù.
	PRIVATE			// ÁöÁ¤µÈ »ç¶÷¸¸ÀÌ µé¾î¿Ã ¼ö ÀÖ´Â Á¸ÀÌ´Ù.(±æµåÁ¸,·¹¾î µî)
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
	Zone(ZoneID_t zoneID) throw();
	Zone(ZoneID_t zoneID, ZoneCoord_t width, ZoneCoord_t height) throw();
	~Zone() throw();

public:
	void init() throw(Error);
	void load(bool bOutput=false) throw(Error);
	void reload(bool bOutput=false) throw(Error);
	void loadItem() throw(Error);
	void loadTriggeredPortal() throw(Error);
	void initSpriteCount() throw(Error);
	void save() throw(Error);

public:
	void pushPC(Creature* pCreature) throw(Error);
	void addPC(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir) throw(EmptyTileNotExistException, Error);
	void addPC(Creature* pCreature) throw(Error);
	void addCreature(Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir) throw(EmptyTileNotExistException, Error);
	TPOINT addItem(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature=true, Turn_t decayTurn=0, ObjectID_t DropPetOID=0) throw(EmptyTileNotExistException, Error); 
	Item* getItem(ObjectID_t id) const throw(Error);
	void addEffect(Effect* pEffect) throw(Error);	
	void deleteEffect(ObjectID_t id) throw(Error);	
	Effect* findEffect(Effect::EffectClass eid) throw(Error);	

	// by sigi. 2002.5.4
	void addEffect_LOCKING(Effect* pEffect) throw(Error);	
	void deleteEffect_LOCKING(ObjectID_t id) throw(Error);	

	void deletePC(Creature* pCreature) throw();//NoSuchElementException, Error);
	void deleteQueuePC(Creature* pCreature) throw(NoSuchElementException, Error);
	void deleteCreature(Creature* pCreature, ZoneCoord_t x, ZoneCoord_t y) throw(NoSuchElementException, Error);
	void deleteObject(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) throw(NoSuchElementException, Error);
	void deleteItem(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) throw(NoSuchElementException, Error);

	bool deleteNPC(Creature* pCreature) throw(Error);//NoSuchElementException, Error);
	void deleteNPCs(Race_t race) throw(Error);//NoSuchElementException, Error);
	void loadNPCs(Race_t race) throw(Error);//NoSuchElementException, Error);
	void sendNPCInfo() throw(Error);

	void loadEffect() throw(Error);


public:
	void movePC(Creature* pCreature, ZoneCoord_t nx, ZoneCoord_t ny, Dir_t dir) throw(ProtocolException, Error);
	void moveCreature(Creature* pCreature, ZoneCoord_t nx, ZoneCoord_t ny, Dir_t dir) throw(ProtocolException, Error);

	// ¸ó½ºÅÍ°¡ ÁÖº¯À» ½ºÄµÇÑ´Ù.
	void monsterScan(Monster* pMonster, ZoneCoord_t x, ZoneCoord_t y, Dir_t dir) throw(Error);

	void broadcastPacket(Packet* pPacket, Creature* owner = NULL) throw(ProtocolException, Error);
	void broadcastPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, Creature* owner = NULL, bool Plus = false, Range_t Range = 0) throw(ProtocolException, Error);
	void broadcastPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, const list<Creature *> & creatureList, bool Plus = false, Range_t Range = 0) throw(ProtocolException, Error);
	void broadcastDarkLightPacket(Packet* pPacket1, Packet* pPacket2, Creature* owner = NULL) throw(ProtocolException, Error);
	void broadcastSayPacket(ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket, Creature* owner = NULL, bool isVampire = false) throw(ProtocolException, Error);
	void broadcastLevelWarBonusPacket(Packet* pPacket, Creature* owner = NULL) throw(ProtocolException, Error);
	list<Creature*> broadcastSkillPacket(ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, Packet* pPacket, list<Creature*> creatureList, bool bConcernDarkness = true) throw(ProtocolException, Error);

	//(x,y) Å¸ÀÏ À§¿¡ ÀÖ´Â PC ¿¡°Ô ÁÖº¯ Á¤º¸¸¦ ÀÐ¾î¼­ Àü¼ÛÇÑ´Ù. pPacket ÀÌ NULL ÀÌ ¾Æ´Ï¶ó¸é, µ¿½Ã¿¡ ºê·ÎµåÄ³½ºÆ®µµ ´ã´çÇÑ´Ù.
	void scan(Creature* pPC, ZoneCoord_t x, ZoneCoord_t y, Packet* pPacket) throw(ProtocolException, Error);
	
	// Á¦ÀÚ¸®¿¡¼­ ½Ã¾ß°¡ º¯°æµÈ °æ¿ì ÁÖº¯ Á¤º¸¸¦ ´Ù½Ã º¸³»ÁØ´Ù.
	void updateScan(Creature* pPC, Sight_t oldSight, Sight_t newSight) throw(ProtocolException, Error);

	// ±×°÷À» º¼ ¼ö ÀÖ´Â ³Ñµé(Player)ÀÇ list¸¦ µ¹·ÁÁØ´Ù.ª
	list<Creature*>  getWatcherList(ZoneCoord_t, ZoneCoord_t, Creature* pTargetCreature = NULL) throw(Error);

	// ¸®Á¨µÈ ¸ó½ºÅÍ°¡ ÁÖº¯ÀÇ PC µé¿¡°Ô GCAddXXX ÆÐÅ¶À» ºê·ÎµåÄ³½ºÆ®ÇÏ¸é¼­µ¿½Ã¿¡ ±×µéÀ» ÀáÀçÀûÀÎ ÀûÀ¸·Î ÀÎ½ÄÇÏµµ·Ï ÇÑ´Ù.
	void scanPC(Creature* pCreature) throw(ProtocolException, Error);

	// Á¦ÀÚ¸®¿¡¼­ hidden creature¿¡ ´ëÇÑ update°¡ ÇÊ¿äÇÑ °æ¿ì.
	void updateHiddenScan(Creature* pCreature) throw(ProtocolException, Error);
	
	// Á¦ÀÚ¸®¿¡¼­ install mine¿¡ ´ëÇÑ update°¡ ÇÊ¿äÇÑ °æ¿ì.
	void updateMineScan(Creature* pCreature) throw(ProtocolException, Error);
	
    // Á¦ÀÚ¸®¿¡¼­ invisible creature¿¡ ´ëÇÑ update°¡ ÇÊ¿äÇÑ °æ¿ì.
	void updateInvisibleScan(Creature* pCreature) throw(ProtocolException, Error);

    // Á¦ÀÚ¸®¿¡¼­ hide,invisible creature¿¡ ´ëÇÑ update°¡ ÇÊ¿äÇÑ °æ¿ì.
	void updateDetectScan(Creature* pCreature) throw(ProtocolException, Error);

	// PC °¡ P(x1,y1)¿¡¼­ Q(x2,y2)·Î ÀÌµ¿ÇßÀ½À» ÁÖº¯¿¡ ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
	void movePCBroadcast(Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove = true, bool bKnockback=false) throw(ProtocolException, Error);

	// !PC °¡ P(x1,y1)¿¡¼­ Q(x2,y2)·Î ÀÌµ¿ÇßÀ½À» ÁÖº¯¿¡ ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
	void moveCreatureBroadcast(Creature* pCreature, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, bool bSendMove = true, bool bKnockback=false) throw(ProtocolException, Error);
	
	// PC °¡ P(x1,y1)¿¡¼­ Q(x2,y2)·Î ÀÌµ¿ÇßÀ½À» ÁÖº¯¿¡ ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
	bool moveFastPC(Creature* pPC, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType) throw(ProtocolException, Error);
	bool moveFastMonster(Monster* pMonster, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2, SkillType_t skillType) throw(ProtocolException, Error);

	// ÀüÀï½Ã ¼º ¾ÈÀº ¾ÈÀüÁö´ë°¡ µÇ¾ú´Ù°¡ ¸»¾Ò´Ù°¡ ÇÑ´Ù. Á¸À» ¼¼ÀÌÇÁÁ¸ÀÌ ¾Æ´Ï°Ô ¸¸µé°Å³ª ¿ø»óº¹±¸½ÃÅ®´Ù.
	void releaseSafeZone() throw();
	void resetSafeZone() throw();

	// ¿ÀºêÁ§Æ® µî·Ï
	void registerObject( Object* pObject ) throw() { getObjectRegistry().registerObject( pObject ); }

public:
	void heartbeat() throw(Error);

	// ÀÌ¸§, Å©¸®Ã³ Å¬·¡½º, OID µîÀ» ÀÌ¿ëÇØ¼­ Á¸¿¡ Á¸ÀçÇÏ´Â Å©¸®ÃÄ °´Ã¼¿¡ Á¢±Ù
	Creature* getCreature(const string& Name) const throw();//NoSuchElementException, Error);
	Creature* getCreature(ObjectID_t objectID) const throw();//NoSuchElementException, Error);
	Creature* getCreature(Creature::CreatureClass creatureClass, ObjectID_t objectID) const throw(NoSuchElementException, Error);


public:
	void lock() throw(Error) { m_Mutex.lock(); }
	void unlock() throw(Error) { m_Mutex.unlock(); }

	// get debug string
	string toString() const throw();

public:
	ObjectRegistry & getObjectRegistry() throw() { return m_ObjectRegistry; }

	const Tile & getTile(ZoneCoord_t x, ZoneCoord_t y) const throw(OutOfBoundException);
	Tile & getTile(ZoneCoord_t x, ZoneCoord_t y) throw(OutOfBoundException);

	Sector* getSector(ZoneCoord_t x, ZoneCoord_t y) throw(OutOfBoundException);

	ZoneID_t getZoneID() const throw() { return m_ZoneID; }
	void setZoneID(ZoneID_t zoneID) throw() { m_ZoneID = zoneID; }
	
	ZoneGroup* getZoneGroup() const throw() { return m_pZoneGroup; }
	void setZoneGroup(ZoneGroup* pZoneGroup) throw() { m_pZoneGroup = pZoneGroup; }

	ZoneType getZoneType() const throw() { return m_ZoneType; }
	void setZoneType(ZoneType zoneType) throw() { m_ZoneType = zoneType; }

	ZoneLevel_t getZoneLevel() const throw() { return m_ZoneLevel; }
	void setZoneLevel(ZoneLevel_t zoneLevel) throw() { m_ZoneLevel = zoneLevel; }
    ZoneLevel_t getZoneLevel(ZoneCoord_t x, ZoneCoord_t y) const throw(OutOfBoundException);

	ZoneAccessMode getZoneAccessMode() const throw() { return m_ZoneAccessMode; }
	void setZoneAccessMode(ZoneAccessMode zoneAccessMode) throw() { m_ZoneAccessMode = zoneAccessMode; }

	string getOwnerID() const throw() { return m_OwnerID; }
	void setOwnerID(const string & ownerID) throw() { m_OwnerID = ownerID; }

	DarkLevel_t getDarkLevel() const throw() { return m_DarkLevel; }
	void setDarkLevel(DarkLevel_t darkLevel) throw() { m_DarkLevel = darkLevel; }

	LightLevel_t getLightLevel() const throw() { return m_LightLevel; }
	void setLightLevel(LightLevel_t lightLevel) throw() { m_LightLevel = lightLevel; }

	const WeatherManager* getWeatherManager() const throw() { return m_pWeatherManager; }

	uint getNPCCount() const throw() { return m_NPCCount; }
	void setNPCCount(uint n) throw(Error) { Assert(n <= maxNPCPerZone); m_NPCCount = n; }

	NPCType_t getNPCType(uint n) const throw() { Assert(n < maxNPCPerZone); return m_NPCTypes[n]; }
	void setNPCType(uint n, NPCType_t npcType) throw() { Assert(n < maxNPCPerZone); m_NPCTypes[n] = npcType; }

	uint getMonsterCount() const throw() { return m_MonsterCount; }
	void setMonsterCount(uint n) throw(Error) { Assert(n <= maxMonsterPerZone); m_MonsterCount = n; }

	MonsterType_t getMonsterType(uint n) const throw() { Assert(n < maxMonsterPerZone); return m_MonsterTypes[n]; }
	void setMonsterType(uint n, MonsterType_t npcType) throw() { Assert(n < maxMonsterPerZone); m_MonsterTypes[n] = npcType; }

	ZoneCoord_t getWidth() const throw() { return m_Width; }
	ZoneCoord_t getHeight() const throw() { return m_Height; }

	uint getTimeband() const { return m_Timeband; }
	void setTimeband( uint timeband ) { m_Timeband = timeband; }

	bool isTimeStop() { return m_bTimeStop; }
	void stopTime() { m_bTimeStop = true; }
	void resumeTime() { m_bTimeStop = false; }

	void resetDarkLightInfo() throw();

	// ABCD add item to item hash map
	void addToItemList(Item* pItem) throw();
	void deleteFromItemList(ObjectID_t id) throw();
	unordered_map<ObjectID_t, Item*> getItems(void) throw() { return m_Items; }

	EffectManager* getEffectManager() throw() { return m_pEffectManager; }
	EffectManager* getVampirePortalManager() throw() { return m_pVampirePortalManager; }
	EffectScheduleManager* getEffectScheduleManager(void) throw() { return m_pEffectScheduleManager; }

	VSRect* getOuterRect(void) { return &m_OuterRect; }
	VSRect* getInnerRect(void) { return &m_InnerRect; }
	VSRect* getCoreRect(void) { return &m_CoreRect; }

	list<NPCInfo*>* getNPCInfos(void);
	void addNPCInfo(NPCInfo* pInfo);
	bool removeNPCInfo(NPC* pNPC);

	// Á¸ ÀüÃ¼ÀÇ NPC¿¡°Ô MarketConditionÀ» ¼³Á¤ÇÑ´Ù. default(100, 25)
	//void setNPCMarketCondition(MarketCond_t NPCSell, MarketCond_t NPCBuy) throw (Error);

	void addVampirePortal(ZoneCoord_t cx, ZoneCoord_t cy, Vampire* pVampire, const ZONE_COORD& ZoneCoord) throw();
	void deleteMotorcycle(ZoneCoord_t cx, ZoneCoord_t cy, Motorcycle* pMotorcycle) throw(Error);

	void addItemDelayed(Item* pItem, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature=true) throw(Error);
	void addItemToCorpseDelayed(Item* pItem, ObjectID_t corpseObjectID) throw(Error);
	void deleteItemDelayed(Object* pObject, ZoneCoord_t x, ZoneCoord_t y) throw(Error);
	void transportItem(ZoneCoord_t x, ZoneCoord_t y, Item* pItem, Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy) throw(Error);
	void transportItemToCorpse(Item* pItem, Zone* pTargetZone, ObjectID_t corpseObjectID) throw(Error);

	LocalPartyManager* getLocalPartyManager(void) const { return m_pLocalPartyManager; }
	PartyInviteInfoManager* getPartyInviteInfoManager(void) const { return m_pPartyInviteInfoManager; }
	
	TradeManager* getTradeManager(void) const { return m_pTradeManager; }


	// pPC°¡ pMonster¸¦ º¼¶§ Monster´Â ¾î¶® packetÀ¸·Î addµÇ´Â°¡?
	// pPC°¡ NULLÀÎ °æ¿ì ´Ù º¸ÀÌ´Â »óÅÂ¶ó°í °¡Á¤ÇÑ´Ù.
	Packet*	createMonsterAddPacket(Monster* pMonster, Creature* pPC) const throw();

	// ¸÷ »ý¼º ÁÂÇ¥
	const BPOINT& getRandomMonsterRegenPosition() const;
	const BPOINT& getRandomEmptyTilePosition() const;

	MonsterManager* getMonsterManager(void) const { return m_pMonsterManager; }
	MasterLairManager* getMasterLairManager(void) const { return m_pMasterLairManager; }
	WarScheduler* getWarScheduler(void) const { return m_pWarScheduler; }
	LevelWarManager* getLevelWarManager() const { return m_pLevelWarManager; }

	void	killAllMonsters() throw (Error);
	void	killAllMonsters_UNLOCK() throw (Error);

	void	killAllPCs() throw(Error);

	const PCManager*  getPCManager() const		{ return m_pPCManager; }             // PC Manager 
	WORD getPCCount(void) const throw() { return m_pPCManager->getSize(); }

#ifdef __USE_ENCRYPTER__
	// get zone's encrypt code
	uchar getEncryptCode() const { return m_EncryptCode; }
#endif

public :
	// À¯·áÈ­
	bool isPayPlay() const throw() { return m_bPayPlay; }
    void setPayPlay(bool bPayPlay=true) throw() { m_bPayPlay = bPayPlay; }

	bool isPremiumZone() const throw() { return m_bPremiumZone; }
	void setPremiumZone(bool bPremiumZone=true) throw() { m_bPremiumZone = bPremiumZone; }

	bool isPKZone() const throw() { return m_bPKZone; }
	void setPKZone(bool bPKZone=true) throw() { m_bPKZone = bPKZone; }

	bool isNoPortalZone() const throw() { return m_bNoPortalZone; }
	void setNoPortalZone(bool bNoPortalZone=true) throw() { m_bNoPortalZone = bNoPortalZone; }

	bool isMasterLair() const throw() { return m_bMasterLair; }
	void setMasterLair(bool bMasterLair=true) throw() { m_bMasterLair = bMasterLair; }

	bool isCastle() const throw() { return m_bCastle; }
	void setCastle(bool bCastle=true) throw() { m_bCastle = bCastle; }

	bool isHolyLand() const throw() { return m_bHolyLand; }
	void setHolyLand(bool bHolyLand=true) throw() { m_bHolyLand = bHolyLand; }

	bool isCastleZone() const throw() { return m_bCastleZone; }
	void setCastleZone(bool bCastleZone=true) throw() { m_bCastleZone = bCastleZone; }

	// Relicº¸°ü´ë¸¦ °®°í ÀÖ³ª?
	bool hasRelicTable() const throw() { return m_bHasRelicTable; }
    void setRelicTable(bool bHasRelicTable=true) throw() { m_bHasRelicTable = bHasRelicTable; }

	bool addRelicItem(int relicIndex) throw(Error); 
	bool deleteRelicItem() throw(Error); 

	// Holy Land Race Bonus º¯È­¿¡ µû¸¥ ÇÃ·¹ÀÌ¾î refresh
	void setRefreshHolyLandPlayer( bool bRefresh ) { m_pPCManager->setRefreshHolyLandPlayer( bRefresh ); }
//	void setRefreshLevelWarBonusZonePlayer( bool bRefresh ) { m_pPCManager->setRefreshLevelWarBonusZonePlayer( bRefresh ); }

	void    remainRaceWarPlayers() throw(Error);

	void    remainPayPlayer() throw(Error);

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
	// Á¸ÀÇ ±âº» ÀûÀÎ Á¤º¸
	ZoneID_t       m_ZoneID;           // zone id
	ZoneGroup*     m_pZoneGroup;       // parent zone group
	ZoneType       m_ZoneType;         // Á¸ Å¸ÀÔ(Á¸ Å¸ÀÔÀÌ ¹Ù®î¸é DB¿¡ ÀúÀåµÇ¾î¾ß ÇÑ´Ù.)
	ZoneLevel_t    m_ZoneLevel;        // Á¸ÀÇ ·¹º§.
	ZoneAccessMode m_ZoneAccessMode;   // Á¸¿¡ ´ëÇÑ Á¢±Ù ¸ðµå { PUBLIC | PRIVATE }
	string         m_OwnerID;          // Á¸ ¼ÒÀ¯ÀÚ ¾ÆÀÌµð(½½·¹ÀÌ¾î ±æµå ¾ÆÀÌµð È¤Àº ¹ìÆÄÀÌ¾î ¸¶½ºÅÍ ¾ÆÀÌµð)
	DarkLevel_t    m_DarkLevel;        // Á¸ÀÇ ¾îµÓ±â
	LightLevel_t   m_LightLevel;       // Á¸ÀÇ ºûÀÇ Å©±â
	ZoneCoord_t    m_Width;            // Á¸ÀÇ °¡·Î Å©±â
	ZoneCoord_t    m_Height;           // Á¸ÀÇ ¼¼·Î Å©±â
	Tile**         m_pTiles;           // Å¸ÀÏÀÇ ÀÌÂ÷¿ø ¹è¿­
	ZoneLevel_t**  m_ppLevel;          // Á¸ ·¹º§ÀÇ ÀÌÂ÷¿ø ¹è¿­
	Sector**       m_pSectors;          // ¼½ÅÍÀÇ ÀÌÂ÷¿ø ¹è¿­
	int            m_SectorWidth;      // ¼½ÅÍÀÇ Å©±â
	int            m_SectorHeight;     // ¼½ÅÍÀÇ Å©±â
	
	// °¢Á¾ ¸Å´ÏÀúµé
	PCManager*             m_pPCManager;             // PC Manager 
	NPCManager*            m_pNPCManager;            // NPC Manager
	MonsterManager*        m_pMonsterManager;        // Monster Manager

//	EventMonsterManager*   m_pEventMonsterManager;

	EffectManager*         m_pEffectManager;         // effect manager
	EffectManager*         m_pVampirePortalManager;  // effect manager
	EffectManager*         m_pLockedEffectManager;   // effect manager
	EffectScheduleManager* m_pEffectScheduleManager;
	list<NPCInfo*>         m_NPCInfos;               // npc infos
	WeatherManager*        m_pWeatherManager;        // Á¸ÀÇ ³¯¾¾

	// Á¸¿¡ ÃâÇöÇÏ´Â NPC ½ºÇÁ¶óÀÌÆ® Å¸ÀÔÀÇ ¸®½ºÆ®
	BYTE m_NPCCount;
	NPCType_t m_NPCTypes[ maxNPCPerZone ];

	// Á¸¿¡ ÃâÇöÇÏ´Â ¸ó½ºÅÍ ½ºÇÁ¶óÀÌÆ® Å¸ÀÔÀÇ ¸®½ºÆ®
	BYTE m_MonsterCount;
	MonsterType_t m_MonsterTypes[ maxMonsterPerZone ];

	// object registery
	ObjectRegistry m_ObjectRegistry;

	// Á¸¿¡ »õ·Î µé¾î°¥ PCµéÀÇ Å¥
	queue< Creature* > m_PCQueue;
	list< Creature* > m_PCListQueue;

	// zone¹Ù´Ú¿¡ ¶³¾îÁø item hashmap
	unordered_map<ObjectID_t, Item*> m_Items;
	
	// Monster AI¸¦ À§ÇØ Á¸ÀÇ ¿µ¿ªÀ» ±¸ºÐÁö¾î ³õÀº »ç°¢Çüµé...
	VSRect m_OuterRect;
	VSRect m_InnerRect;
	VSRect m_CoreRect;

	LocalPartyManager* m_pLocalPartyManager;
	PartyInviteInfoManager* m_pPartyInviteInfoManager;
	TradeManager* m_pTradeManager;
	
	// ¸÷ »ý¼º ÁÂÇ¥¸¦ À§ÇÑ Á¤º¸.
	vector<BPOINT> m_MonsterRegenPositions;
	vector<BPOINT> m_EmptyTilePositions;

	// mutex
	mutable Mutex m_Mutex;
	mutable Mutex m_MutexEffect;

	// À¯·áÈ­ °ü·Ã
	bool m_bPayPlay;
	bool m_bPremiumZone;

	// ±âÅ¸ Á¤º¸
	bool m_bPKZone;
	bool m_bNoPortalZone;
	bool m_bMasterLair;
	bool m_bCastle;
	bool m_bHolyLand;
	bool m_bCastleZone;

	// ÀüÀï Áß?
	bool m_bHasRelicTable;

	// Relic Table °ü·Ã Á¤º¸
	ObjectID_t m_RelicTableOID;
	ZoneCoord_t m_RelicTableX;
	ZoneCoord_t m_RelicTableY;

	Timeval	m_LoadValueStartTime;
	DWORD  m_LoadValue;

	// ¸¶½ºÅÍ ·¹¾î. by sigi.2002.9.2
	MasterLairManager* 	m_pMasterLairManager;

	// ÀüÀï °ü¸® by sigi. 2003.1.24
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

	DynamicZone*	m_pDynamicZone;		// ÀÎ´ø Á¤º¸
};	

#endif
