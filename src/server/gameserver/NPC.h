//////////////////////////////////////////////////////////////////////////////
// Filename    : NPC.h
// Written By  : 김성민
// Description : 
// 원래는 상점 처리 부분이 없었으나, 이 클래스를 상속받아 상점 NPC를 
// 만들기도 좀 그래서, 그냥 NPC 안에다 상점 인터페이스를 집어넣었다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __NPC_H__
#define __NPC_H__

#include "Creature.h"
#include "Zone.h"
#include "Assert.h"
#include "Timeval.h"
#include "Inventory.h"

#include "quest/TriggerManager.h"
#include "couple/PartnerWaitingManager.h"

class QuestInfoManager;
class RewardClassInfoManager;
class Script;

//////////////////////////////////////////////////////////////////////////////
// 상점의 종류 (크리스마스 이벤트용)
//////////////////////////////////////////////////////////////////////////////
enum ShopType
{
	SHOPTYPE_NORMAL = 0, // 일반 상점
	SHOPTYPE_EVENT,      // 이벤트 상점

	SHOPTYPE_MAX
};

//////////////////////////////////////////////////////////////////////////////
// NPC의 종족 상수
// 이 상수를 이용해 슬레이어가 뱀파이어 NPC에게 말을 걸거나 
// 상점을 이용하는 것들을 막는다. 
//////////////////////////////////////////////////////////////////////////////
enum
{
	NPC_RACE_SLAYER = 0,
	NPC_RACE_VAMPIRE,
	NPC_RACE_OUSTERS,
	NPC_RACE_MONSTER,
	NPC_RACE_UNKNOWN,
	NPC_RACE_MAX
};


//////////////////////////////////////////////////////////////////////////////
// Class NPC
//////////////////////////////////////////////////////////////////////////////

class ShopRack;

class NPC : public Creature 
{
public: 
	NPC() throw();
	NPC(const string & name) throw();
	virtual ~NPC() throw (Error);

public: 
	virtual CreatureClass getCreatureClass() const throw() { return CREATURE_CLASS_NPC; }
	virtual string getCreatureClassString() const throw() { return "CREATURE_CLASS_NPC"; }

	virtual void registerObject() throw(Error);

	virtual bool load() throw(Error);
	virtual void save() const throw(Error) { throw UnsupportedError(__PRETTY_FUNCTION__); }

	virtual string toString() const throw();

public:
	void init() throw(Error);
	void act(const Timeval& currentTime) throw(Error);

public:
	virtual Level_t getLevel() const throw() { return 1; }

	Race_t getRace(void) const { return m_Race;}
	void setRace(int race) { m_Race = race;}
	
	bool isSlayer() const throw() { return(m_Race == NPC_RACE_SLAYER) ? true : false;}
	bool isVampire() const throw() { return(m_Race == NPC_RACE_VAMPIRE) ? true : false;}
	bool isOusters() const throw() { return(m_Race == NPC_RACE_OUSTERS) ? true : false;}

	SpriteType_t getSpriteType() const throw() { return m_SpriteType; } 
	void setSpriteType(SpriteType_t spriteType) throw() { m_SpriteType = spriteType; }

	const string& getName() const throw() { return m_Name; }
	void setName(const string & name) throw() { m_Name = name; }

	NPCID_t getNPCID() const throw() { return m_NPCID;}
	void setNPCID(NPCID_t NPCID) throw() { m_NPCID = NPCID;}

	Color_t getMainColor() const throw() { return m_MainColor; }
	void setMainColor(Color_t color) throw() { m_MainColor = color; }

	Color_t getSubColor() const throw() { return m_SubColor; }
	void setSubColor(Color_t color) throw() { m_SubColor = color; }

	Inventory* getInventory() throw() { return m_pInventory; }
	void setInventory(Inventory* pInventory) throw() { m_pInventory = pInventory; }

	TriggerManager & getTriggerManager() throw() { return m_TriggerManager; }
	const TriggerManager & getTriggerManager() const throw() { return m_TriggerManager; }

	bool isShowInMinimap(void) const { return m_bShowInMinimap; }
	void setShowInMinimap(bool bShow) { m_bShowInMinimap = bShow; }

	bool isDead() const throw() { return false; }
	bool isAlive() const throw() { return true; }

////////////////////////////////////////////////////////////
// 상점 관련 인터페이스
// 상점 인터페이스에 관련된 함수는 NPC가 실제로
// 상점 NPC가 아닌 경우에는 거의 모두가 exception을
// 던지므로, 이 NPC가 확실히 상점 NPC인지 체크하고,
// 함수를 호출해야 한다.
////////////////////////////////////////////////////////////
public:
	int getShopType(void) const { return m_ShopType; }
	void setShopType(int type) { m_ShopType = type; }

	ShopVersion_t getShopVersion(ShopRackType_t type) const;
	void setShopVersion(ShopRackType_t type, ShopVersion_t ver);
	void increaseShopVersion(ShopRackType_t type);

	bool  isExistShopItem(ShopRackType_t type, BYTE index) const;
	void  insertShopItem(ShopRackType_t type, BYTE index, Item* pItem);
	void  removeShopItem(ShopRackType_t type, BYTE index);
	Item* getShopItem(ShopRackType_t type, BYTE index) const;
	void  clearShopItem(void);

	BYTE getFirstEmptySlot(ShopRackType_t type) const;
	BYTE getLastEmptySlot(ShopRackType_t type) const;

	bool isEmpty(ShopRackType_t type) const;
	bool isFull(ShopRackType_t type) const;

	MarketCond_t getMarketCondBuy(void) const { return m_MarketCondBuy;}
	void setMarketCondBuy(MarketCond_t cond) { m_MarketCondBuy = cond;}
	
	MarketCond_t getMarketCondSell(void) const { return m_MarketCondSell;}
	void setMarketCondSell(MarketCond_t cond) { m_MarketCondSell = cond;}

	virtual ClanType_t getClanType(void) const { return m_ClanType; }
	virtual void setClanType(ClanType_t clan) { m_ClanType = clan; }
	
	// SimpleQuest by sigi. 2002.12.3
//	bool regenSimpleQuest() throw (Error);
//	bool giveSimpleQuest(Creature* pPC, QuestID_t qid) throw (Error);
//	void setSimpleQuestListScript(Script* pScript) throw (Error);
	//void sendSimpleQuestListPacket(Creature* pCreature) throw (Error);
	
	void setCoupleRegisterManager( PartnerWaitingManager* pPWM ) 	{ m_pCoupleRegisterManager = pPWM; }
	void setCoupleUnregisterManager( PartnerWaitingManager* pPWM ) 	{ m_pCoupleUnregisterManager = pPWM; }

	PartnerWaitingManager* getCoupleRegisterManager() const { return m_pCoupleRegisterManager; }
	PartnerWaitingManager* getCoupleUnregisterManager() const { return m_pCoupleUnregisterManager; }

	void setQuestInfoManager( QuestInfoManager* pQIM ) { m_pQuestInfoManager = pQIM; }
	void setRewardClassInfoManager( RewardClassInfoManager* pRIM ) { m_pRewardClassInfoManager = pRIM; }

	QuestInfoManager* getQuestInfoManager() const { return m_pQuestInfoManager; }
	RewardClassInfoManager* getRewardClassInfoManager() const { return m_pRewardClassInfoManager; }

	ZoneID_t	getTaxingCastleZoneID() const { return m_TaxingCastleZoneID; }
	void		setTaxingCastleZoneID( ZoneID_t castleZoneID ) { m_TaxingCastleZoneID = castleZoneID; }

	int			getTaxRatio(PlayerCreature* pPC) const;

protected:
	string          m_Name;
	NPCID_t         m_NPCID;
	int             m_Race;
	SpriteType_t    m_SpriteType;
	Color_t         m_MainColor;
	Color_t         m_SubColor;	
	Timeval         m_NextTurn;       // 다음 액션 실행 시간
	Inventory*      m_pInventory;     // NPC의 인벤토리
	TriggerManager  m_TriggerManager; // 트리거 매니저
	bool            m_bShowInMinimap;
	ClanType_t      m_ClanType;

	// 상점 인터페이스
	int          m_ShopType;
	ShopRack*    m_pRack;
	MarketCond_t m_MarketCondBuy;
	MarketCond_t m_MarketCondSell;
//	QuestBoard*  m_pQuestBoard;

	// 커플 등록 매니저
	PartnerWaitingManager* m_pCoupleRegisterManager;
	PartnerWaitingManager* m_pCoupleUnregisterManager;

	// 퀘스트 관련 정보들
	QuestInfoManager* m_pQuestInfoManager;
	RewardClassInfoManager* m_pRewardClassInfoManager;

	ZoneID_t	m_TaxingCastleZoneID;
};



#endif
