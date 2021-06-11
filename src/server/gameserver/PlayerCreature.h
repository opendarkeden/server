//////////////////////////////////////////////////////////////////////////////
// Filename    : PlayerCreature.h
// Written by  : excel96
// Description : 
// Slayer 및 Vampire 클래스의 인터페이스 중 공통되는 부분을 모아놓은 
// 클래스다. abstract 클래스이므로, 바로 선언하면 안 될 것이당.
//////////////////////////////////////////////////////////////////////////////

#ifndef __PLAYER_CREATURE_H__
#define __PLAYER_CREATURE_H__

#include "Creature.h"
#include "ObjectRegistry.h"
#include "InventorySlot.h"
#include "Garbage.h"
#include "RankBonus.h"
#include "ExpFwd.h"
//#include "RankExpTable.h"
//#include "ItemNameInfo.h"
//#include "quest/Squest/QuestManager.h"
#include "GCMonsterKillQuestInfo.h"
#include "OptionInfo.h"

#include <unordered_map>
#include <bitset>
#include <forward_list>
#include <vector>

static const GuildID_t SlayerCommon	=99;
static const GuildID_t VampireCommon=0;
static const GuildID_t OustersCommon=66;


//////////////////////////////////////////////////////////////////////////////
// class PlayerCreature
//////////////////////////////////////////////////////////////////////////////

class Inventory;
class InventorySlot;
class Stash;
class Player;
class FlagSet;
class QuestManager;
class TimeLimitItemManager;
class GoodsInventory;
class PetInfo;
class PetItem;
class Pet;
class SMSAddressBook;
class NicknameBook;
class NicknameInfo;
class GQuestManager;
class BloodBibleSignInfo;
class Store;
//class GCMonsterKillQuestInfo;
//struct GCMonsterKillQuestInfo::QuestInfo;

typedef unordered_map<DWORD, RankBonus*> HashMapRankBonus;
typedef HashMapRankBonus::iterator HashMapRankBonusItor;
typedef HashMapRankBonus::const_iterator HashMapRankBonusConstItor;


class PlayerCreature : public Creature
{
////////////////////////////////////////////////////////////
// 생성자 및 소멸자
////////////////////////////////////////////////////////////
public:
	PlayerCreature(ObjectID_t objectID = 0, Player* pPlayer = NULL) ;
	virtual ~PlayerCreature() ;

	virtual bool load() ;
	virtual void tinysave(const string & field) const  = 0;
//	virtual void tinysave(const char* field) const  = 0;

////////////////////////////////////////////////////////////
// OID 등록 관련 메쏘드
////////////////////////////////////////////////////////////
protected:
	virtual void registerItem(Item* pItem, ObjectRegistry& OR) ;

public:
	virtual void registerInventory(ObjectRegistry& OR) ;
	virtual void registerInitInventory(ObjectRegistry& OR) ;
	virtual void registerStash(void) ;

	virtual void registerGoodsInventory(ObjectRegistry& OR) ;

//////////////////////////////////////////////////////////////
// 시간제한 아이템 관련 함수
//////////////////////////////////////////////////////////////
public:
	bool wasteIfTimeLimitExpired(Item* pItem) ;
	virtual void checkItemTimeLimit()  = 0;
	void sendTimeLimitItemInfo() ;
	void addTimeLimitItem(Item* pItem, DWORD time) ;
	void sellItem( Item* pItem ) ;
	void deleteItemByMorph( Item* pItem ) ;
	void updateItemTimeLimit( Item* pItem, DWORD time ) ;
	virtual void updateEventItemTime( DWORD time )  = 0;
	void loadTimeLimitItem() ;

//////////////////////////////////////////////////////////////
// 구매 상품 아이템 관련 함수
//////////////////////////////////////////////////////////////
public:
	void loadGoods() ;

//////////////////////////////////////////////////////////////
// 퀘스트 매니저 관련 함수
//////////////////////////////////////////////////////////////
public:
	QuestManager*	getQuestManager() const { return m_pQuestManager; }
	void			sendCurrentQuestInfo() const ;

	virtual	int		getQuestLevel() const = 0;
	virtual void	whenQuestLevelUpgrade();

////////////////////////////////////////////////////////////
// 인벤토리 관련 메쏘드
////////////////////////////////////////////////////////////
public:
	virtual Inventory* getInventory() const  { return m_pInventory; }
	virtual void setInventory(Inventory* pInventory)  { m_pInventory = pInventory; }

	virtual InventorySlot* getExtraInventorySlot()  { return m_pExtraInventorySlot; }
	virtual Item* getExtraInventorySlotItem()  { return m_pExtraInventorySlot->getItem(); }
	virtual void deleteItemFromExtraInventorySlot()  { m_pExtraInventorySlot->deleteItem(); }
	virtual void addItemToExtraInventorySlot(Item* pItem)  { m_pExtraInventorySlot->addItem(pItem); }

	// 2003.04.04. by Sequoia
	virtual void loadItem() ;

	virtual GoodsInventory* getGoodsInventory() const  { return m_pGoodsInventory; }

////////////////////////////////////////////////////////////
// 보관함 관련 메쏘드
////////////////////////////////////////////////////////////
public:
	virtual Stash* getStash(void) const  { return m_pStash; }
	virtual void setStash(Stash* pStash)  { m_pStash = pStash; }

	virtual BYTE getStashNum(void) const  { return m_StashNum; }
	virtual void setStashNum(BYTE num)  { m_StashNum = num; }
	virtual void setStashNumEx(BYTE num) ;

	virtual Gold_t getStashGold(void) const  { return m_StashGold; }
	virtual void setStashGold(Gold_t gold)  { m_StashGold = gold; }
	virtual void setStashGoldEx(Gold_t gold) ;
	virtual void increaseStashGoldEx(Gold_t gold) ;
	virtual void decreaseStashGoldEx(Gold_t gold) ;
	virtual bool checkStashGoldIntegrity() = 0;

	virtual bool getStashStatus(void) const  { return m_bStashStatus; }
	virtual void setStashStatus(bool s)  { m_bStashStatus = s; }

	virtual void deleteStash(void) ;


////////////////////////////////////////////////////////////
// 가비지 관련 메쏘드
////////////////////////////////////////////////////////////
public:
	void addItemToGarbage(Item* pItem) { m_Garbage.addItem(pItem); }
	void addItemToGarbageEx(Item* pItem) { m_Garbage.addItemEx(pItem, getName()); }
	Item* popItemFromGarbage(void) { return m_Garbage.popItem(); }
	void saveGarbage(void) { m_Garbage.save(getName()); }
	int getGarbageSize(void) { return m_Garbage.size(); }

////////////////////////////////////////////////////////////
// 아이템 검색 함수
////////////////////////////////////////////////////////////
public:
	virtual Item* findItemOID(ObjectID_t id)  = 0;
	virtual Item* findItemOID(ObjectID_t id, int& storage, int& x, int& y)  = 0;

	virtual Item* findItemIID(ItemID_t id)  = 0;
	virtual Item* findItemIID(ItemID_t id, int& storage, int& x, int& y)  = 0;

	virtual Item* findBeltOID(ObjectID_t id)  = 0;
	virtual Item* findBeltOID(ObjectID_t id, int& storage, int& x, int& y)  = 0;

	virtual Item* findBeltIID(ItemID_t id)  = 0;
	virtual Item* findBeltIID(ItemID_t id, int& storage, int& x, int& y)  = 0;


////////////////////////////////////////////////////////////
// 플래그 셋 관련 함수
////////////////////////////////////////////////////////////
public:
	FlagSet* getFlagSet(void) const  { return m_pFlagSet; }
	void setFlagSet(FlagSet* pSet)  { m_pFlagSet = pSet; } 
	void deleteFlagSet(void) ;


////////////////////////////////////////////////////////////
// 기타 함수
////////////////////////////////////////////////////////////
public:
	virtual Fame_t getFame() const  = 0;
	virtual void setFame(Fame_t fame)  = 0;

	virtual Gold_t getGold() const  = 0;
	virtual void setGold(Gold_t gold)  = 0;
	virtual void setGoldEx(Gold_t gold)  = 0;
	virtual void   increaseGoldEx(Gold_t gold)  = 0;
    virtual void   decreaseGoldEx(Gold_t gold)  = 0;
	virtual bool checkGoldIntegrity() = 0;
	bool checkDBGold( Gold_t gold )
	{
		Gold_t temp = getGold();
		setGold(gold);
		bool ret = checkGoldIntegrity();
		setGold(temp);
		return ret;
	}


	virtual Sex	getSex() const  = 0;

	virtual ZoneID_t getResurrectZoneID(void) const  = 0;
	virtual void setResurrectZoneID(ZoneID_t id)  = 0;
	virtual void setResurrectZoneIDEx(ZoneID_t id)  = 0;

	//virtual Race_t getRace() const = 0; - Creature로 올렸다.
	virtual GuildID_t getCommonGuildID() const = 0;

	virtual IP_t getIP(void) const = 0;


////////////////////////////////////////////////////////////
// 성향 시스템 관련
////////////////////////////////////////////////////////////
	// enemy specific methods
	void addEnemy(const string& Name) ;
	void deleteEnemy(const string& Name) ;

	// 이 특정 사용자가 이미 선공을 하였는가?
	bool hasEnemy(const string& Name) const ;
	uint getMaxEnemies() const ;

	list<string>& getEnemies(void)  { return m_Enemies;}

	bool isPK()  { return m_isPK; }

	void setPK(bool isPK)  { m_isPK = isPK; }

	void setGuildID( GuildID_t GuildID )  { m_GuildID = GuildID; }
	GuildID_t getGuildID() const  { return m_GuildID; }

	string getGuildName() const ;
	GuildMemberRank_t getGuildMemberRank() const ;

	Rank_t  	getRank() const ;
	RankExp_t   getRankExp() const ;
	RankExp_t   getRankGoalExp() const ;

//	virtual Rank_t getRank() const  = 0;
	void increaseRankExp(RankExp_t Point);

	WORD getRankExpSaveCount(void) const { return m_RankExpSaveCount; }
	void setRankExpSaveCount(WORD count) { m_RankExpSaveCount = count; }

	virtual Alignment_t getAlignment() const =0;
	virtual void setAlignment(Alignment_t Alignment) =0;

////////////////////////////////////////////////////////////
// Rank Bonus 관련
////////////////////////////////////////////////////////////
	void loadRankBonus() ;
	bool hasRankBonus( RankBonus::RankBonusType type )  { return m_RankBonusFlag.test(type); }
	RankBonus* getRankBonus( RankBonus::RankBonusType type ) const ;
	RankBonus* getRankBonusByRank( Rank_t rank ) const ;
	bool learnRankBonus( DWORD type ) ;
	void clearRankBonus() ;
	void clearRankBonus( Rank_t rank ) ;
	HashMapRankBonus& getRankBonuses() { return m_RankBonuses; }

	void sendRankBonusInfo() ;

protected:
	void addRankBonus( RankBonus* rankBonus ) ;

public :
	// by sigi. 2002.11.19
	bool isBillingPlayAvaiable() ;
	virtual bool isPayPlayAvaiable() ;
	virtual bool canPlayFree() ;

public:
	Item*	getQuestItem() const { return m_pQuestItem; }
	void	setQuestItem( Item* pItem ) { m_pQuestItem = pItem; }

public :
	// by sigi. 2002.12.3
/*	void	loadQuest() ;
	bool 	hasQuest() const 	{ return m_pQuestManager!=NULL && !m_pQuestManager->isEmpty(); }
	bool 	addQuest(Quest* pQuest) ;
	bool 	checkEvent(QuestEvent* pQuest) ;
	Quest* 	removeCompleteQuest() ;
	void 	removeAllQuest() 	{ if (m_pQuestManager!=NULL) m_pQuestManager->release(); }*/

	virtual void initAllStatAndSend() = 0;
	virtual void initAllStat(int numPartyMember)  = 0;

	virtual void computeStatOffset(void)  = 0;
	virtual void computeItemStat(Item* pItem)  = 0;
	virtual void computeOptionStat(Item* pItem)  = 0;
	virtual void computeOptionStat(OptionType_t optionType)  = 0;
	virtual void computeOptionClassStat( OptionClass OClass, int PlusPoint ) = 0;

	void heartbeat(const Timeval& currentTime) ;

	virtual bool canSee( Object* pObject ) const;

////////////////////////////////////////////////////////////
// 멤버 데이터
////////////////////////////////////////////////////////////
protected:
	Inventory*     m_pInventory;          // 인벤토리 포인터
	InventorySlot* m_pExtraInventorySlot; // 마우스 포인터

	GoodsInventory* m_pGoodsInventory;    // 구매 아이템 인벤토리

	Stash*         m_pStash;              // 보관함 포인터
	BYTE           m_StashNum;            // 보관함의 숫자
	Gold_t         m_StashGold;           // 보관함 안의 돈 액수
	bool           m_bStashStatus;        // 보관함 아이템 OID 등록 여부

	Garbage        m_Garbage;             // 가비지...

	FlagSet*       m_pFlagSet;            // 플래그 집합

	// 먼저 선공한 사람들의 이름을 저장한다.
	// ObjectID를 저장할 수도 있으나, 죽어서 다시 오면 정당방위가 인정되지 않기 때문에 이름으로 저장해준다.
    list<string> m_Enemies;

	// PK를 당했느냐 아니냐를 구분한다.
	bool m_isPK;

	// GuildID
	GuildID_t		m_GuildID;

	// Rank Bonus map
	HashMapRankBonus m_RankBonuses;
	bitset<RankBonus::RANK_BONUS_MAX> m_RankBonusFlag;

	Rank*	m_pRank;
	WORD	m_RankExpSaveCount;

//	QuestManager*	m_pQuestManager;
	QuestManager*			m_pQuestManager;
	TimeLimitItemManager*	m_pTimeLimitItemManager;

	Item*					m_pQuestItem;
	vector<Item*>			m_PetStash;		// pet 보관함

public:
	/////////////////////////////////////////////////////////
	// pet 보관하에 관련된 method
	/////////////////////////////////////////////////////////
	Item*				getPetStashItem(int idx);	
	void				addPetStashItem(int idx, Item* pPetItem);

	/////////////////////////////////////////////////////////
	// BloodBible 관련 보너스 수치들
	/////////////////////////////////////////////////////////
public:
	int					getConsumeMPRatio() const { return m_ConsumeMPRatio; }
	void				setConsumeMPRatio( int ratio ) { m_ConsumeMPRatio = ratio; }

	int					getGamblePriceRatio() const { return m_GamblePriceRatio; }
	void				setGamblePriceRatio( int ratio ) { m_GamblePriceRatio = ratio; }

	int					getPotionPriceRatio() const { return m_PotionPriceRatio; }
	void				setPotionPriceRatio( int ratio ) { m_PotionPriceRatio = ratio; }

	Damage_t			getMagicBonusDamage() const { return m_MagicBonusDamage; }
	void				setMagicBonusDamage( Damage_t damage ) { m_MagicBonusDamage = damage; }

	Damage_t			getPhysicBonusDamage() const { return m_PhysicBonusDamage; }
	void				setPhysicBonusDamage( Damage_t damage ) { m_PhysicBonusDamage = damage; }

	Damage_t			getMagicDamageReduce() const { return m_MagicDamageReduce; }
	void				setMagicDamageReduce( Damage_t damage ) { m_MagicDamageReduce = damage; }

	Damage_t			getPhysicDamageReduce() const { return m_PhysicDamageReduce; }
	void				setPhysicDamageReduce( Damage_t damage ) { m_PhysicDamageReduce = damage; }

/*	bool				isEmptyItemNameInfoList() { return m_ItemNameInfoList.empty(); }
	void				clearItemNameInfoList() { m_ItemNameInfoList.clear(); }
	const list<ItemNameInfo*>& getItemNameInfoList() const { return m_ItemNameInfoList; }
	void				addItemNameInfoList( ItemNameInfo* itemNameInfo ) { m_ItemNameInfoList.push_back(itemNameInfo); }
	bool				deleteItemNameInfoList( ObjectID_t objectID ) ;
	string				getItemName( ObjectID_t objectID ) ;*/

protected:
	int						m_ConsumeMPRatio;
	int						m_GamblePriceRatio;
	int						m_PotionPriceRatio;
	Damage_t				m_MagicBonusDamage;
	Damage_t				m_PhysicBonusDamage;

	Damage_t				m_MagicDamageReduce;
	Damage_t				m_PhysicDamageReduce;

//	list<ItemNameInfo*> 	m_ItemNameInfoList;

// 사용자의 당첨 여부를 기록하기 위해 어쩔 수 없이 여기 추가해야 될듯

public:
	DWORD				getLottoRewardID() const { return m_LottoRewardID; }
	void				setLottoRewardID( DWORD lottoRewardID ) { m_LottoRewardID = lottoRewardID; }

	DWORD				getLottoQuestLevel() const { return m_LottoQuestLevel; }
	void 				setLottoQuestLevel( DWORD lottoQuestLevel ) { m_LottoQuestLevel = lottoQuestLevel; }

	bool				isLotto() const { return m_bLotto; }
	void				setLotto( bool lotto ) { m_bLotto = lotto; }

protected:
	DWORD				m_LottoRewardID;
	DWORD				m_LottoQuestLevel;
	bool				m_bLotto;

	//////////////////////////////////////////////
	// Default Option Set Info
	//////////////////////////////////////////////
public:
	void	addDefaultOptionSet( DefaultOptionSetType_t type ) ;
	void	removeDefaultOptionSet( DefaultOptionSetType_t type ) ;

protected:
	forward_list<DefaultOptionSetType_t>		m_DefaultOptionSet;

public:
	PetInfo*	getPetInfo() const;
	void		setPetInfo(PetInfo* pPetInfo);

	list<PetItem*>& getPetItems() { return m_PetItems; }
	const list<PetItem*>& getPetItems() const { return m_PetItems; }

	Pet*		getPet() const { return m_pPet; }

protected:
	PetInfo* m_pPetInfo;
	list<PetItem*> m_PetItems;
	Pet*	m_pPet;

	// 2차 펫 퀘스트 관련 
public:
	SpriteType_t	getTargetMonsterSType() const { return m_TargetMonster; }
	virtual void	initPetQuestTarget() = 0;
	GCMonsterKillQuestInfo::QuestInfo*	getPetQuestInfo() const;

protected:
	SpriteType_t	m_TargetMonster;
	DWORD			m_TargetNum;
	DWORD			m_TimeLimit;

	// SMS 관련
public:
	SMSAddressBook*	getAddressBook() const { return m_pSMSAddressBook; }
	uint			getSMSCharge() const { return m_SMSCharge; }
	void			setSMSCharge(uint charge) { m_SMSCharge = charge; }

	NicknameBook*	getNicknameBook() const { return m_pNicknameBook; }

	NicknameInfo*	getNickname() const { return m_pNickname; }
	void			setNickname(NicknameInfo* pNickname) { m_pNickname = pNickname; }
	
	GQuestManager*	getGQuestManager() const { return m_pGQuestManager; }

	BloodBibleSignInfo* getBloodBibleSign() const { return m_pBloodBibleSign; }

	virtual int		getBloodBibleSignOpenNum() const = 0;
	void			applyBloodBibleSign();

private:
	SMSAddressBook*	m_pSMSAddressBook;
	uint			m_SMSCharge;

	NicknameBook*	m_pNicknameBook;
	NicknameInfo*	m_pNickname;

	GQuestManager*	m_pGQuestManager;
	BloodBibleSignInfo*	m_pBloodBibleSign;

public:
	void			setBaseLuck(Luck_t luck) { m_BaseLuck = luck; }
	Luck_t			getBaseLuck() const { return m_BaseLuck; }
protected:
	Luck_t			m_BaseLuck;

public:
	Store*			getStore() const { return m_pStore; }

protected:
	Store*			m_pStore;

public:
    // get / set PowerPoint
    int getPowerPoint() const { return m_PowerPoint; }
    void setPowerPoint( int powerpoint ) { m_PowerPoint = powerpoint; }

protected:
    // 파워짱 포인트
    int             m_PowerPoint;

public:
	bool			isAdvanced() const { return m_bAdvanced; }
	
	Level_t			getAdvancementClassLevel() const;
	Exp_t			getAdvancementClassGoalExp() const;
	bool			increaseAdvancementClassExp(Exp_t exp, bool bApplyExpBount = true);

protected:
	bool				m_bAdvanced;
	AdvancementClass*	m_pAdvancementClass;
	WORD				m_AdvancementClassExpSaveCount;

public:
	Attr_t				getAdvancedAttrBonus() const { return m_AdvancedAttrBonus; }
	bool				putAdvancedBonusToSTR();
	bool				putAdvancedBonusToDEX();
	bool				putAdvancedBonusToINT();

	virtual Bonus_t getBonus() const  = 0;
	virtual void    setBonus(Bonus_t bonus)  = 0;

protected:
	Attr_t				m_AdvancedSTR;
	Attr_t				m_AdvancedDEX;
	Attr_t				m_AdvancedINT;
	Attr_t				m_AdvancedAttrBonus;

public:
	BYTE				getMasterEffectColor() const { return m_MasterEffectColor; }
	void				setMasterEffectColor(BYTE color) { m_MasterEffectColor = color; }
	// add by sonic 2006.10.29
	bool				canChangeMasterEffectColor();

protected:
	BYTE				m_MasterEffectColor;
};

#endif
