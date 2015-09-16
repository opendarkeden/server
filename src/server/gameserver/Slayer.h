//////////////////////////////////////////////////////////////////////////////
// Filename    : Slayer.h
// Written By  : Elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __SLAYER_H__
#define __SLAYER_H__

#include "PlayerCreature.h"
#include "Zone.h"
#include "Assert1.h"
#include "Inventory.h"
#include "PCSlayerInfo.h"
#include "PCSlayerInfo2.h"
#include "PCSlayerInfo3.h"
#include "InventoryInfo.h"
#include "ItemLoaderManager.h"
#include "GearInfo.h"
#include "ExtraInfo.h"
#include "OptionInfo.h"
#include "RideMotorcycleInfo.h"
#include "SlayerSkillInfo.h"
#include "CreatureUtil.h"
#include "ModifyInfo.h"
#include "Mutex.h"
#include <map>
//#include "RankExpTable.h"
#include "SlayerAttrExpTable.h"

#include "skill/Skill.h"
#include "skill/SkillSlot.h"

#include "GCModifyInformation.h"

#ifdef __CHINA_SERVER__
#define	SLAYER_BOUND_LEVEL			100
#define SLAYER_BOUND_ATTR			200
#define	SLAYER_BOUND_ATTR_SUM		300
#define SLAYER_BOUND_ONE_EXP_ATTR	200
#define SLAYER_BOUND_SUB_ATTR		50
#define SLAYER_MAX_LEVEL			150
#define SLAYER_MAX_ATTR				295
#define	SLAYER_MAX_ATTR_SUM			435
#define SLAYER_ONE_EXP_ATTR			400
#define	SLAYER_MAX_DOMAIN_LEVEL		150
#define SLAYER_MAX_SUB_ATTR			70

#define SLAYER_MAX_RANK	50
#else
// 슬레이어는 도메인 레벨이 BOUND_LEVEL에 도달하기 전까지는
// 능력치가 BOUND_ATTR 이하로, 능력치 총합이 BOUND_ATTR_SUM 이하로 제한된다.
// BOUND_LEVEL이 넘은 뒤에는 MAX_ATTR과 MAX_ATTR_SUM으로 제한된다.
#define	SLAYER_BOUND_LEVEL			100
#define SLAYER_BOUND_ATTR			210
#define	SLAYER_BOUND_ATTR_SUM		330
#define SLAYER_BOUND_ONE_EXP_ATTR	210
#define SLAYER_BOUND_SUB_ATTR		60
#define SLAYER_MAX_LEVEL			150
//#define SLAYER_MAX_ATTR				295
#define SLAYER_MAX_ATTR				315
//#define	SLAYER_MAX_ATTR_SUM			435
#define	SLAYER_MAX_ATTR_SUM			475
#define SLAYER_ONE_EXP_ATTR			400
#define	SLAYER_MAX_DOMAIN_LEVEL		150
#define SLAYER_MAX_SUB_ATTR			80

#define SLAYER_MAX_RANK	50
#endif

////////////////////////////////////////////////////////////////////////////////
// 장비를 입고 벗을 때 장비 입고 벗기 전의 능력치를 
// 저장해 두기 위한 버퍼(?) 클래스.
////////////////////////////////////////////////////////////////////////////////

class SLAYER_RECORD
{
public:
	Attr_t       pSTR[3];
	Attr_t       pDEX[3];
	Attr_t       pINT[3];
	Rank_t    	 Rank;
	HP_t         pHP[2];
	MP_t         pMP[2];
	Damage_t     pDamage[2];
	Defense_t    Defense;
	Protection_t Protection;
	ToHit_t      ToHit;
	Speed_t      AttackSpeed;
};




////////////////////////////////////////////////////////////////////////////////
//
// Class Slayer;
//
// Creature 의 하위 클래스로 플레이어가 조종하는 PC 이당.
//
////////////////////////////////////////////////////////////////////////////////
	
class Motorcycle;

class Slayer : public PlayerCreature 
{

//////////////////////////////////////////////////////////////
// 클래스 내부 상수 선언
//////////////////////////////////////////////////////////////
public:

	enum WearPart 
	{ 
		WEAR_HEAD, 
		WEAR_NECK, 
		WEAR_BODY, 
		WEAR_LEFTHAND, 
		WEAR_RIGHTHAND,
		WEAR_HAND3,
		WEAR_BELT,
		WEAR_LEG,
		WEAR_WRIST1, 
		WEAR_WRIST2, 				
		WEAR_FINGER1, 
		WEAR_FINGER2, 
		WEAR_FINGER3, 
		WEAR_FINGER4,
		WEAR_FOOT,
		WEAR_ZAP1,
		WEAR_ZAP2,
		WEAR_ZAP3,
		WEAR_ZAP4,
		WEAR_PDA,
		WEAR_SHOULDER,
		WEAR_MAX 
	};

//////////////////////////////////////////////////////////////
// 생성자/소멸자
//////////////////////////////////////////////////////////////
public:
	Slayer() throw();
	virtual ~Slayer() throw();
	
//////////////////////////////////////////////////////////////
// 하위 클래스 상속 함수
//////////////////////////////////////////////////////////////
public:
	virtual CreatureClass getCreatureClass() const throw() { return CREATURE_CLASS_SLAYER; }
	virtual string getCreatureClassString() const throw() { return "CREATURE_CLASS_SLAYER"; }

	virtual void registerObject() throw(Error);
	virtual void registerInitObject() throw(Error);

	virtual bool load() throw(InvalidProtocolException, Error);
	void loadItem(bool checkTimeLimit = false ) throw(InvalidProtocolException, Error);

	virtual void save() const throw(Error);
	virtual void tinysave(const string & field) const throw(Error);
//	virtual void tinysave(const char* field) const throw(Error);
	void saveSkills(void) const throw(Error);
	void saveGears(void) const throw(Error);
	void saveExps(void) const throw(Error);

	virtual void act(const Timeval& currentTime) throw(Error) {}

	virtual string toString() const throw();

	virtual Race_t getRace() const { return RACE_SLAYER; }
	virtual GuildID_t getCommonGuildID() const { return SlayerCommon; }

//////////////////////////////////////////////////////////////
// 시간제한 아이템 관련 함수
//////////////////////////////////////////////////////////////
public:
	void checkItemTimeLimit() throw(Error);
	void updateEventItemTime(DWORD time ) throw(Error);

//////////////////////////////////////////////////////////////
// 상태 관련 함수(dead or alive)
//////////////////////////////////////////////////////////////
public:
	virtual bool isDead() const throw() { return m_HP[ATTR_CURRENT] == 0; }
	virtual bool isAlive() const throw() { return m_HP[ATTR_CURRENT] != 0; }

//////////////////////////////////////////////////////////////
// 겉모습 관련 함수(이름, 권한, 성별, 머리, 피부, 전화번호)
//////////////////////////////////////////////////////////////
public:
	const string& getName() const throw() { return m_Name; }
	void setName(const string & name) throw() { m_Name = name; m_Owner = name; }

	BYTE getCompetence() const throw() { return m_Competence; }
	void setCompetence(BYTE Competence) { m_Competence = Competence; }

	BYTE getCompetenceShape() const throw() { return m_CompetenceShape; }
	void setCompetenceShape(BYTE CompetenceShape) { m_CompetenceShape = CompetenceShape; }

	Sex getSex() const throw() { return m_Sex; }
	void setSex(Sex sex) throw() { m_Sex = sex; m_SlayerInfo.setSex(sex); }
	void setSex(const string & sex) throw(InvalidProtocolException)
	{
		if(sex == Sex2String[MALE]) setSex(MALE);
		else if(sex == Sex2String[FEMALE]) setSex(FEMALE);
		else throw InvalidProtocolException("invalid sex value");
	}

	HairStyle getHairStyle() const throw() { return m_HairStyle; }
	void setHairStyle(HairStyle hairStyle) throw() { m_HairStyle = hairStyle; }
	void setHairStyle(const string& hairStyle) throw(InvalidProtocolException)
	{
		if(hairStyle == HairStyle2String[HAIR_STYLE1])      m_HairStyle = HAIR_STYLE1;
		else if(hairStyle == HairStyle2String[HAIR_STYLE2]) m_HairStyle = HAIR_STYLE2;
		else if(hairStyle == HairStyle2String[HAIR_STYLE3]) m_HairStyle = HAIR_STYLE3;
		else throw InvalidProtocolException("invalid hairstyle value");
	}

	Color_t getHairColor() const throw() { return m_HairColor; }
	void setHairColor(Color_t hairColor) throw() { m_HairColor = hairColor; }

	Color_t getSkinColor() const throw() { return m_SkinColor; }
	void setSkinColor(Color_t skinColor) throw() { m_SkinColor = skinColor; }

//////////////////////////////////////////////////////////////
// 전화 관련 함수
//////////////////////////////////////////////////////////////
public:
	PhoneNumber_t getPhoneNumber() const throw() { return m_PhoneNumber; }
	void setPhoneNumber(PhoneNumber_t PhoneNumber) throw() { m_PhoneNumber = PhoneNumber; }
	
	PhoneNumber_t getPhoneSlotNumber(SlotID_t SlotID) throw();
	void setPhoneSlotNumber(SlotID_t SlotID, PhoneNumber_t PhoneNumber) throw();
	SlotID_t getSlotWithPhoneNumber(PhoneNumber_t PhoneNumber) throw();
	SlotID_t findEmptyPhoneSlot() throw();
	bool isEmptyPhoneSlot() throw();
	bool isSlotByPhoneNumber(PhoneNumber_t PhoneNumber) throw();

//////////////////////////////////////////////////////////////
// 능력치 관련 함수(STR, DEX, INT)
//////////////////////////////////////////////////////////////
public:

	Bonus_t getBonus() const throw() { return m_AdvancedAttrBonus; }
	void    setBonus(Bonus_t bonus) throw() { m_AdvancedAttrBonus = bonus; }

	// 성향
	Alignment_t getAlignment() const throw() { return m_Alignment; }
	void setAlignment(Alignment_t Alignment) throw() { m_Alignment = Alignment; }
	void saveAlignment(Alignment_t alignment) throw();

	Attr_t  getSTR(AttrType attrType = ATTR_CURRENT) const throw() { return m_STR[attrType]; }
	void    setSTR(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_STR[attrType] = attr; }
	Exp_t   getSTRGoalExp() const throw() { return m_pAttrs[ATTR_KIND_STR]->getGoalExp(); }

	Attr_t  getDEX(AttrType attrType = ATTR_CURRENT) const throw() { return m_DEX[attrType]; }
	void    setDEX(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_DEX[attrType] = attr; }
	Exp_t   getDEXGoalExp() const throw() { return m_pAttrs[ATTR_KIND_DEX]->getGoalExp(); }

	Attr_t  getINT(AttrType attrType = ATTR_CURRENT) const throw() { return m_INT[attrType]; }
	void    setINT(Attr_t attr, AttrType attrType = ATTR_CURRENT) throw() { m_INT[attrType] = attr; }
	Exp_t   getINTGoalExp() const throw() { return m_pAttrs[ATTR_KIND_INT]->getGoalExp(); }

	Attr_t	getTotalAttr(AttrType attrType = ATTR_CURRENT ) const throw() { return getSTR(attrType ) + getDEX(attrType ) + getINT(attrType); }
	QuestGrade_t getQuestGrade() const throw();

	void divideAttrExp(AttrKind kind, Damage_t damage, ModifyInfo& ModifyInfo);

	// 계급 추가. by sigi. 2002.8.30
	// PlayerCreature로 옮김. 2004.1 by Sequoia

	// 초보자인가? 순수 능력치 합이 40 이하
	bool	isNovice() const;

//////////////////////////////////////////////////////////////
// 능력치 관련 함수(HP, MP)
//////////////////////////////////////////////////////////////
public:
	HP_t getHP(AttrType attrType = ATTR_CURRENT) const throw() { return m_HP[attrType]; }
	void setHP(HP_t hp, AttrType attrType = ATTR_CURRENT) throw() { m_HP[attrType] = hp; }
	void setHP(HP_t current, HP_t max) throw() { m_HP[ATTR_CURRENT] = current; m_HP[ATTR_MAX] = max; }

	MP_t getMP(AttrType attrType = ATTR_CURRENT) const throw() { return m_MP[attrType]; }
	void setMP(MP_t mp, AttrType attrType = ATTR_CURRENT) throw() { m_MP[attrType] = mp; }
	void setMP(MP_t current, MP_t max) throw() { m_MP[ATTR_CURRENT] = current; m_MP[ATTR_MAX] = max; }


//////////////////////////////////////////////////////////////
// 능력치 관련 함수(Damage, CC, Defense, ToHit)
//////////////////////////////////////////////////////////////
public:
	Damage_t     getDamage(AttrType attrType = ATTR_CURRENT) const throw() { return m_Damage[attrType]; }
	Protection_t getProtection(void) const throw() { return m_Protection[ATTR_CURRENT]; }
	Defense_t    getDefense(void) const throw() { return m_Defense[ATTR_CURRENT]; }
	ToHit_t      getToHit(void) const throw() { return m_ToHit[ATTR_CURRENT]; }
	Speed_t      getAttackSpeed(void) const throw() { return m_AttackSpeed[ATTR_CURRENT]; }

	
//////////////////////////////////////////////////////////////
// 스킬 관련 함수
//////////////////////////////////////////////////////////////
public:
	Exp_t getGoalExp(SkillDomainType_t Domain) const throw() { return m_GoalExp[Domain]; }
	void  setGoalExp(SkillDomainType_t Domain, Exp_t GoalExp) throw() { m_GoalExp[Domain] = GoalExp; }

	SkillLevel_t getSkillDomainLevel(SkillDomainType_t skillDomain) const throw() { return m_SkillDomainLevels[skillDomain]; }
	void         setSkillDomainLevel(SkillDomainType_t skillDomain, SkillLevel_t skillLevel) throw() { m_SkillDomainLevels[skillDomain] = skillLevel; }
	SkillLevel_t getHighestSkillDomainLevel() const throw();
	SkillDomainType_t getHighestSkillDomain() const throw();

//	SkillExp_t getSkillDomainExp(SkillDomainType_t skillDomain) const throw() { return m_SkillDomainExps[skillDomain]; }
//	void       setSkillDomainExp(SkillDomainType_t skillDomain, SkillExp_t skillExp) throw() { m_SkillDomainExps[skillDomain] = skillExp; }

//	void setSkillDomain(SkillDomainType_t skillDomain, SkillLevel_t skillLevel, SkillExp_t skillExp) throw() { m_SkillDomainLevels[skillDomain] = skillLevel; m_SkillDomainExps[skillDomain] = skillExp; }

	SkillLevel_t getSkillDomainLevelSum() const throw();
	Level_t getLevel() const throw() { return (Level_t)getHighestSkillDomainLevel(); }

	int getQuestLevel() const { return getHighestSkillDomainLevel(); }

	void addSkill(SkillSlot* pSkillSlot) throw();
	void addSkill(SkillType_t SkillType) throw();
	void removeCastleSkill(SkillType_t SkillType) throw();
	void removeAllCastleSkill() throw();
	SkillSlot* hasSkill(SkillType_t SkillType) const throw() { return getSkill(SkillType); }
	SkillSlot* getSkill(SkillType_t SkillType) const throw();

	Exp_t getGunBonusExp() const throw() { return m_GunBonusExp; }
	void setGunBonusExp(Exp_t GunBonusExp) throw() { m_GunBonusExp = GunBonusExp; }

	Exp_t getRifleBonusExp() const throw() { return m_RifleBonusExp; }
	void setRifleBonusExp(Exp_t RifleBonusExp) throw() { m_RifleBonusExp = RifleBonusExp; }
	
	// 지정된 domain에서 가장 높은 level의 기술의 타입을 되돌린다.
	//SkillType_t getMaxLevelSkillType(SkillDomainType_t domain) throw();
//	void setHotKey(BYTE pos, SkillType_t SkillType) throw() { m_HotKey[pos] = SkillType; }
//	SkillType_t getHotKey(BYTE pos) const throw() { return m_HotKey[pos]; }


//////////////////////////////////////////////////////////////
// 아이템 착/탈 관련 함수
//////////////////////////////////////////////////////////////
public:
	bool  isWear(WearPart Part) throw() { return m_pWearItem[Part] != NULL ? true : false; }
	void  addWearItem(WearPart Part, Item* pItem) throw() { Assert(m_pWearItem[Part] = NULL); m_pWearItem[Part] = pItem;}
	void  deleteWearItem(WearPart Part) throw(Error) { Assert(m_pWearItem[Part] != NULL); m_pWearItem[Part] = NULL; }
	Item* getWearItem(WearPart Part) throw() { return m_pWearItem[Part]; }
	void  wearItem(WearPart Part) throw(Error);
	void  wearItem(WearPart Part, Item* pItem) throw(Error);
	void  takeOffItem(WearPart Part, bool bAddOnMouse, bool bSendModifyInfo) throw(Error);
	WearPart getWearPart(Item::ItemClass IClass) const;
	bool 	changeShape(Item* pItem, Color_t color, bool bSendPacket=true);
	bool 	addShape(Item::ItemClass IClass, ItemType_t IType, Color_t color);
	bool 	removeShape(Item::ItemClass IClass, bool bSendPacket=true);
	Color_t getItemShapeColor(Item* pItem, OptionInfo* pOptionInfo=NULL) const;


	void  destroyGears() throw();

	bool  isRealWearing(WearPart part) const throw();
	bool  isRealWearing(Item* pItem) const throw();
	bool  isRealWearingEx(WearPart part) const;
	DWORD sendRealWearingInfo(void) const throw();
	void  getShapeInfo (DWORD& flag, Color_t color[PCSlayerInfo::SLAYER_COLOR_MAX]) const;

//////////////////////////////////////////////////////////////
// 아이템 착/탈 시 능력치 수정 관련 함수
//////////////////////////////////////////////////////////////
public:
	void initAllStat(int numPartyMember=-1) throw();
	void initCastleSkill() throw();
	void addModifyInfo(const SLAYER_RECORD& previous, ModifyInfo& pkt) const throw();
	void sendModifyInfo(const SLAYER_RECORD& previous) const throw();
	void initAllStatAndSend();

private:
	void computeStatOffset(void) throw();
	void computeItemStat(Item* pItem) throw();
	void computeOptionStat(Item* pItem) throw();
	void computeOptionStat(OptionType_t optionType) throw();
	void computeOptionClassStat(OptionClass OClass, int PlusPoint);

//////////////////////////////////////////////////////////////
// 아이템 검색 함수
//////////////////////////////////////////////////////////////
public:

	virtual Item* findItemOID(ObjectID_t id) throw() { return ::findItemOID(this, id); }
	virtual Item* findItemOID(ObjectID_t id, int& storage, int& x, int& y) throw() { return ::findItemOID(this, id, storage, x, y); }

	virtual Item* findItemIID(ItemID_t id) throw() { return ::findItemIID(this, id); }
	virtual Item* findItemIID(ItemID_t id, int& storage, int& x, int& y) throw() { return ::findItemIID(this, id, storage, x, y); }

	virtual Item* findBeltOID(ObjectID_t id) throw() { return ::findItemOID(this, id, Item::ITEM_CLASS_BELT); }
	virtual Item* findBeltOID(ObjectID_t id, int& storage, int& x, int& y) throw() { return ::findItemOID(this, id, Item::ITEM_CLASS_BELT, storage, x, y); }

	virtual Item* findBeltIID(ItemID_t id) throw(){ return ::findItemIID(this, id, Item::ITEM_CLASS_BELT); }
	virtual Item* findBeltIID(ItemID_t id, int& storage, int& x, int& y) throw(){ return ::findItemIID(this, id, Item::ITEM_CLASS_BELT, storage, x, y); }

//////////////////////////////////////////////////////////////
// 모터 사이클 관련 함수
//////////////////////////////////////////////////////////////
public:
	Motorcycle* getMotorcycle() const throw() { return m_pMotorcycle; }
	void setMotorcycle(Motorcycle* pMotorcycle) throw();
	void getOffMotorcycle() throw(Error);

	RideMotorcycleInfo* getRideMotorcycleInfo() const throw();
	bool hasRideMotorcycle() const throw() { return((m_pMotorcycle != NULL) ? true : false);}


//////////////////////////////////////////////////////////////
// 인포 관련 함수
//////////////////////////////////////////////////////////////
public:
	PCSlayerInfo2* getSlayerInfo2() const throw();
	PCSlayerInfo3  getSlayerInfo3() const throw();
	GearInfo*      getGearInfo() const throw();
	InventoryInfo* getInventoryInfo() const throw();
	ExtraInfo*     getExtraInfo() const throw();
	void sendSlayerSkillInfo() throw();

	// get/set EffectInfo
    EffectInfo* getEffectInfo() const throw();

//////////////////////////////////////////////////////////////
// 기타 함수
//////////////////////////////////////////////////////////////
public:

	virtual Fame_t getFame() const throw() { return m_Fame; }
	virtual void   setFame(Fame_t fame) throw() { m_Fame = fame; }

	virtual Gold_t getGold() const throw() { return m_Gold; }
	virtual void   setGold(Gold_t gold) throw();
	virtual void   setGoldEx(Gold_t gold) throw();
	virtual void   increaseGoldEx(Gold_t gold) throw();
	virtual void   decreaseGoldEx(Gold_t gold) throw();
	virtual bool checkGoldIntegrity();
	virtual bool checkStashGoldIntegrity();


	void setInMagics(const string & blob) throw() {}

	void heartbeat(const Timeval& currentTime) throw();

	void getSlayerRecord(SLAYER_RECORD& record) const throw();

	virtual ZoneID_t getResurrectZoneID(void) const throw() { return m_ResurrectZoneID; }
	virtual void setResurrectZoneID(ZoneID_t id) throw() { m_ResurrectZoneID = id; }
	virtual void setResurrectZoneIDEx(ZoneID_t id) throw();

	virtual Steal_t getHPStealAmount(void) const { return m_HPStealAmount; }
	virtual void setHPStealAmount(Steal_t steal) { m_HPStealAmount = steal; }

	virtual Steal_t getMPStealAmount(void) const { return m_MPStealAmount; }
	virtual void setMPStealAmount(Steal_t steal) { m_MPStealAmount = steal; }

	virtual Steal_t getHPStealRatio(void) const { return m_HPStealRatio; }
	virtual void setHPStealRatio(Steal_t steal) { m_HPStealRatio = steal; }

	virtual Steal_t getMPStealRatio(void) const { return m_MPStealRatio; }
	virtual void setMPStealRatio(Steal_t steal) { m_MPStealRatio = steal; }

	virtual Regen_t getHPRegen(void) const { return m_HPRegen; }
	virtual void setHPRegen(Regen_t regen) { m_HPRegen = regen; }

	virtual Regen_t getMPRegen(void) const { return m_MPRegen; }
	virtual void setMPRegen(Regen_t regen) { m_MPRegen = regen; }

	virtual Luck_t getLuck(void) const { return m_Luck; }
	virtual void setLuck(Luck_t luck) { m_Luck = luck; }

	virtual int getCriticalRatio(void) const { return m_CriticalRatio[ATTR_CURRENT]; }
	virtual void setCriticalRatio(int ratio) { m_CriticalRatio[ATTR_CURRENT] = ratio; }

	uint getSlayerLevel(void) const throw();
	void saveInitialRank(void) throw();

	virtual IP_t getIP(void) const;

	WORD getDomainExpSaveCount(void) const { return m_DomainExpSaveCount; }
	void setDomainExpSaveCount(WORD count) { m_DomainExpSaveCount = count; }

	WORD getAttrExpSaveCount(void) const { return m_AttrExpSaveCount; }
	void setAttrExpSaveCount(WORD count) { m_AttrExpSaveCount = count; }

	WORD getSkillExpSaveCount(void) const { return m_SkillExpSaveCount; }
	void setSkillExpSaveCount(WORD count) { m_SkillExpSaveCount = count; }

	WORD getFameSaveCount(void) const { return m_FameSaveCount; }
	void setFameSaveCount(WORD count) { m_FameSaveCount = count; }

	WORD getAlignmentSaveCount(void) const { return m_AlignmentSaveCount; }
	void setAlignmentSaveCount(WORD count) { m_AlignmentSaveCount = count; }

//	WORD getRankExpSaveCount(void) const { return m_RankExpSaveCount; }
//	void setRankExpSaveCount(WORD count) { m_RankExpSaveCount = count; }

//	void increaseRankExp(RankExp_t Point);

public :
	// by sigi. 2002.11.19
	virtual bool isPayPlayAvaiable() throw(Error);
	virtual bool canPlayFree() throw(Error);

	virtual void setLastTarget(ObjectID_t value);

	void	initPetQuestTarget();
	int		getBloodBibleSignOpenNum() const;

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
private:

	// PC name
	string m_Name;

	// 권한
	BYTE m_Competence;
	BYTE m_CompetenceShape;

	// Sex(1bit), HairStyle(2bit)
	// 나중에는 bit 연산을 해서 메모리를 줄이도록 하자.
	Sex m_Sex;
	HairStyle m_HairStyle;	

	// HairColor(8bit), SkinColor(8bit)
	Color_t m_HairColor;
	Color_t m_SkinColor;

    // Phone Number
	PhoneNumber_t m_PhoneNumber;
	
	// Phone Slot
	PhoneNumber_t m_PhoneSlot[3];

	// Alignment
	Alignment_t m_Alignment;

	// STR/DEX/INT
	Attr_t m_STR[3];
	Attr_t m_DEX[3];
	Attr_t m_INT[3];

	Attr* m_pAttrs[ATTR_KIND_MAX];

	// STR/DEX/INT exp
//	Exp_t m_STRExp;
//	Exp_t m_STRGoalExp;
//	Exp_t m_DEXExp;
//	Exp_t m_DEXGoalExp;
//	Exp_t m_INTExp;
//	Exp_t m_INTGoalExp;

	// Rank
//	Rank_t 		m_Rank;
//	RankExp_t 	m_RankExp;
//	RankExp_t 	m_RankGoalExp;

//	Rank*		m_pRank;

	// HP/MP
	HP_t m_HP[3];
	MP_t m_MP[3];

	Damage_t     m_Damage[3];
	ToHit_t      m_ToHit[2];
	Defense_t    m_Defense[2];
	Protection_t m_Protection[2];
	Speed_t      m_AttackSpeed[2];
	int          m_CriticalRatio[2];

	// Vision / SkillPoint
	Vision_t     m_Vision[2];
	SkillPoint_t m_SkillPoint;
	
	// Fame/Gold
	Fame_t m_Fame;
	Gold_t m_Gold;

	// SkillLevel, SkillExp
	SkillLevel_t m_SkillDomainLevels[SKILL_DOMAIN_VAMPIRE];
//	SkillExp_t m_SkillDomainExps[SKILL_DOMAIN_VAMPIRE];

	// Goal Exp
	Exp_t m_GoalExp[SKILL_DOMAIN_VAMPIRE];

	// Gun, Rifle Bonus Exp
	Exp_t m_GunBonusExp;
	Exp_t m_RifleBonusExp;

	// SkillSlot
	//SkillSlot* m_pSkillSlot[MAX_SLAYER_SKILL_SLOT];
	map<SkillType_t, SkillSlot*> m_SkillSlot;

	// WearItem Field
	Item* m_pWearItem[WEAR_MAX];
	bool  m_pRealWearingCheck[WEAR_MAX];

	// Motorcycle Pointer
	Motorcycle* m_pMotorcycle;

	// outlook information
	mutable PCSlayerInfo3 m_SlayerInfo;

	// Hot Key Set
//	SkillType_t m_HotKey[4];

	mutable Mutex m_Mutex;

	// 슬레이어의 이전 능력치를 저장해 두는 버퍼 구조체
	SLAYER_RECORD m_Record;

	// 부활존 관련
	ZoneID_t m_ResurrectZoneID;

	// HP, MP 스틸
	Steal_t m_HPStealAmount;
	Steal_t m_MPStealAmount;
	Steal_t m_HPStealRatio;
	Steal_t m_MPStealRatio;

	// HP, MP 재생
	Regen_t m_HPRegen;
	Regen_t m_MPRegen;
	
	// luck
	Luck_t  m_Luck;

	// Prayer와 Meditation과 관련된 timer
	Timeval m_MPRegenTime;

	// 각종 경험치 세이브 카운트
	WORD m_DomainExpSaveCount;
	WORD m_AttrExpSaveCount;
	WORD m_SkillExpSaveCount;
	WORD m_FameSaveCount;
	WORD m_AlignmentSaveCount;
//	WORD m_RankExpSaveCount;
};

#endif // __SLAYER_H__
