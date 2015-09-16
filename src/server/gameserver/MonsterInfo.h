//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterInfo.h
// Written By  : 김성민
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTERINFO_H__
#define __MONSTERINFO_H__

#include "Types.h"
#include "Exception.h"
#include "Assert1.h"
#include "Creature.h"
#include "MonsterSummonInfo.h"
#include "MonsterInfoTypes.h"
#include "Treasure.h"
#include <list>
#include <vector>
#include <map>

// 몬스터 스프라이트 종류 최대 숫자
const int MAX_SPRITE_TYPE = 255;

//////////////////////////////////////////////////////////////////////////////
// 몬스터가 기억할 수 있는 적의 최대 개수, 또는 적의 리스트에 접근하는 인덱스
//////////////////////////////////////////////////////////////////////////////
enum EnemyPriority 
{
	ENEMY_PRIMARY = 1 ,
	ENEMY_SECONDARY ,
	ENEMY_THIRD ,
	ENEMY_FOURTH ,
	ENEMY_FIFTH ,
	ENEMY_SIXTH ,
	ENEMY_SEVENTH ,
	ENEMY_EIGHTH ,
	ENEMY_MAX
};


//////////////////////////////////////////////////////////////////////////////
// 적이 여러명일 때, 누구를 먼저 공격하는가?
//////////////////////////////////////////////////////////////////////////////
enum AttackOrder 
{
	ATTACK_FIRST,          // 제일 먼저 때린 놈부터 공격
	ATTACK_LAST,           // 제일 나중에 때린 놈 부터 공격
	ATTACK_WEAKEST,        // 제일 약한 놈부터 공격
	ATTACK_STRONGEST,      // 제일 강한 놈부터 공격
	ATTACK_CLOSEST,        // 제일 가까운 놈 부터 공격
	ATTACK_FAREST,         // 제일 먼 놈 부터 공격
	ATTACK_FIGHTER,        // 전사 먼저 공격
	ATTACK_PRIEST,         // 성직자 먼저 공격
	ATTACK_GUNNER,         // 건너 먼저 공격
	ATTACK_MAX
};

const string AttackOrder2String[] = 
{
	"ATTACK_FIRST" ,
	"ATTACK_LAST" ,
	"ATTACK_WEAKEST" ,
	"ATTACK_STRONGEST" ,
	"ATTACK_CLOSEST" ,
	"ATTACK_FAREST" ,
	"ATTACK_FIGHTER" ,
	"ATTACK_PRIEST" ,
	"ATTACK_GUNNER" ,
	"ATTACK_BOMBER"
};


//////////////////////////////////////////////////////////////////////////////
// 몬스터 성향 - 몬스터는 PC를 보고 어떻게 반응하는가?
//////////////////////////////////////////////////////////////////////////////
enum MAlignment 
{
    ALIGNMENT_FRIENDLY ,
    ALIGNMENT_NEUTRAL ,
    ALIGNMENT_AGGRESSIVE
};

const string MAlignment2String[] = 
{
	"ALIGNMENT_FRIENDLY" ,
    "ALIGNMENT_NEUTRAL" ,
    "ALIGNMENT_AGGRESSIVE"
};


//////////////////////////////////////////////////////////////////////////////
// AI Level - 몬스터는 얼마나 똑똑한가?
//////////////////////////////////////////////////////////////////////////////
enum AILevel 
{
	AI_VERY_LOW ,		//   1 - 50
	AI_LOW ,			//  51 - 100
	AI_MEDIUM ,			// 101 - 150
	AI_HIGH ,			// 151 - 200
	AI_VERY_HIGH 		// 201 - 250
};

//////////////////////////////////////////////////////////////////////////////
// Body Size - 몬스터의 몸통 크기
//////////////////////////////////////////////////////////////////////////////
enum BodySize
{
	BODYSIZE_SMALL = 0,
	BODYSIZE_MEDIUM,
	BODYSIZE_LARGE
};

//////////////////////////////////////////////////////////////////////////////
// class MonsterInfo
//////////////////////////////////////////////////////////////////////////////

class MonsterInfo 
{
public:
	MonsterInfo() throw();
	~MonsterInfo() throw();

public:
	MonsterType_t getMonsterType() const { return m_MonsterType; }
	void setMonsterType(MonsterType_t spriteType) { m_MonsterType = spriteType; }

	SpriteType_t getSpriteType() const { return m_SpriteType; }
	void setSpriteType(SpriteType_t spriteType) { m_SpriteType = spriteType; }

	string getHName() const { return m_HName; }
	void setHName(const string & name) { m_HName = name; }

	string getEName() const { return m_EName; }
	void setEName(const string & name) { m_EName = name; }

	Level_t getLevel() const { return m_Level; }
	void setLevel(Level_t level) { m_Level = level; }

	Attr_t getSTR() const { return m_STR; }
	void setSTR(Attr_t str) { m_STR = str; }

	Attr_t getDEX() const { return m_DEX; }
	void setDEX(Attr_t dex) { m_DEX = dex; }

	Attr_t getINT() const { return m_INT; }
	void setINT(Attr_t inte) { m_INT = inte; }

	uint getBodySize() const { return m_BodySize; }
	void setBodySize(uint size) { m_BodySize = size; }

	HP_t getHP() const { return m_HP; }
	void setHP(HP_t hp) { m_HP = hp; }

	Exp_t getExp() const { return m_Exp; }
	void setExp(Exp_t exp) { m_Exp = exp; }

	Color_t getMainColor() const { return m_MainColor; }
	void setMainColor(Color_t mainColor) { m_MainColor = mainColor; }

	Color_t getSubColor() const { return m_SubColor; }
	void setSubColor(Color_t subColor) { m_SubColor = subColor; }

	MAlignment getAlignment() const { return m_Alignment; }
	void setAlignment(MAlignment alignment) { m_Alignment = alignment; }

	AttackOrder getAttackOrder() const { return m_AttackOrder; }
	void setAttackOrder(AttackOrder attackOrder) { m_AttackOrder = attackOrder; }

	Moral_t getMoral() const { return m_Moral; }
	void setMoral(Moral_t moral) { m_Moral = moral; }

	Turn_t getDelay() const { return m_Delay; }
	void setDelay(Turn_t delay) { m_Delay = delay; }

	Turn_t getAttackDelay() const { return m_AttackDelay; }
	void setAttackDelay(Turn_t delay) { m_AttackDelay = delay; }

	Sight_t getSight() const { return m_Sight; }
	void setSight(Sight_t sight) { m_Sight = sight; }

	int getMeleeRange(void) const { return m_MeleeRange; }
	void setMeleeRange(int range) { m_MeleeRange = range; }

	int getMissileRange(void) const { return m_MissileRange; }
	void setMissileRange(int range) { m_MissileRange = range; }

	Creature::MoveMode getMoveMode() const { return m_MoveMode; }
	void setMoveMode(Creature::MoveMode moveMode) { m_MoveMode = moveMode; }
	void setMoveMode(const string & moveMode) throw(Error);

	uint getAIType(void) const { return m_AIType;}
	void setAIType(uint aitype) { m_AIType = aitype;}

	int getEnhanceHP(void) const { return m_EnhanceHP; }
	int getEnhanceToHit(void) const { return m_EnhanceToHit; }
	int getEnhanceDefense(void) const { return m_EnhanceDefense; }
	int getEnhanceProtection(void) const { return m_EnhanceProtection; }
	int getEnhanceMinDamage(void) const { return m_EnhanceMinDamage; }
	int getEnhanceMaxDamage(void) const { return m_EnhanceMaxDamage; }
	void parseEnhanceAttr(const string& enhance) throw();

	void parseSlayerTreasureString(const string& text) throw();
	TreasureList* getSlayerTreasureList(void) const { return m_pSlayerTreasureList; }
	TreasureList* getSlayerTreasureList(void) { return m_pSlayerTreasureList; }
	void setSlayerTreasureList(TreasureList* pTreasureList) throw();

	void parseVampireTreasureString(const string& text) throw();
	TreasureList* getVampireTreasureList(void) const { return m_pVampireTreasureList; }
	TreasureList* getVampireTreasureList(void) { return m_pVampireTreasureList; }
	void setVampireTreasureList(TreasureList* pTreasureList) throw();

	void parseOustersTreasureString(const string& text) throw();
	TreasureList* getOustersTreasureList(void) const { return m_pOustersTreasureList; }
	TreasureList* getOustersTreasureList(void) { return m_pOustersTreasureList; }
	void setOustersTreasureList(TreasureList* pTreasureList) throw();

	RegenType selectRegenType() const;
	int getRegenType(RegenType rt) const				{ return m_RegenType[rt]; }
	void setRegenType(RegenType rt, int percent);

	int  getUnburrowChance(void) const { return m_UnburrowChance;}
	void setUnburrowChance(uint uc) { m_UnburrowChance = uc;}	// 0~128

	int  isMaster(void) const { return m_bMaster;}
	void setMaster(bool bMaster=true) { m_bMaster = bMaster;}

	int  getClanType(void) const { return m_ClanType;}
	void setClanType(int clanType) { m_ClanType = clanType;}

	void setMonsterSummonInfo(const string& text);
	bool getMonsterSummonInfo(int step, SUMMON_INFO2& summonInfo) const;
	bool hasNextMonsterSummonInfo(int step) const;

	void setDefaultEffects(const string& text);
	const list<Effect::EffectClass>& getDefaultEffects() const { return m_DefaultEffects; }
	void addDefaultEffects(Creature* pCreature) const;

	bool isChief(void) const { return m_bChief; }
	void setChief(bool flag) { m_bChief = flag; }

	bool  isNormalRegen(void) const { return m_bNormalRegen;}
	void setNormalRegen(bool bNormalRegen=true) { m_bNormalRegen = bNormalRegen;}

	bool  hasTreasure(void) const { return m_bHasTreasure;}
	void setHasTreasure(bool bHasTreasure=true) { m_bHasTreasure = bHasTreasure;}

	int  getMonsterClass(void) const { return m_MonsterClass;}
	void setMonsterClass(int mClass) { m_MonsterClass = mClass;}

	int  getSkullType(void) const { return m_SkullType;}
	void setSkullType(int skullType) { m_SkullType = skullType;}

	string toString() const throw();

private:
	MonsterType_t      m_MonsterType;               // 몬스터 타입
	SpriteType_t       m_SpriteType;                // 사용 스프라이트 타입
	string             m_HName;                     // 몬스터 한글 이름
	string             m_EName;                     // 몬스터 영문 이름
	Level_t            m_Level;                     // 몬스터 레벨
	Attr_t             m_STR;                       // 기본 STR
	Attr_t             m_DEX;                       // 기본 DEX
	Attr_t             m_INT;                       // 기본 INT
	uint               m_BodySize;                  // 몬스터의 크기
	HP_t               m_HP;                        // 생명력
	Exp_t              m_Exp;                       // 죽였을 때 PC 뱀파이어가 받는 경험치 (not used)
	Color_t            m_MainColor;                 // Main Color (not used)
	Color_t            m_SubColor;                  // Sub Color (not used)
	MAlignment         m_Alignment;                 // 성향
	AttackOrder        m_AttackOrder;               // 공격 순서에 관련된 성향
	Moral_t            m_Moral;                     // 사기
	Turn_t             m_Delay;                     // 다음 행위를 하기 까지의 딜레이 시간.
	Turn_t             m_AttackDelay;               // 다음 공격을 하기 까지의 딜레이 시간.
	Sight_t            m_Sight;                     // 시야
	int                m_MeleeRange;                // 접근전 사정거리
	int                m_MissileRange;              // 미사일 사정거리
	Creature::MoveMode m_MoveMode;                  // 이동 모드
	uint               m_AIType;                    // 인공지능 타입
	int                m_EnhanceHP;                 // 체력 강화 배수
	int                m_EnhanceToHit;              // ToHit 강화 배수
	int                m_EnhanceDefense;            // 디펜스 강화 배수
	int                m_EnhanceProtection;         // 프로텍션 강화 배수
	int                m_EnhanceMinDamage;             // 데미지 강화 배수
	int                m_EnhanceMaxDamage;             // 데미지 강화 배수
	TreasureList*      m_pSlayerTreasureList;       // 슬레이어를 위한 보물의 리스트
	TreasureList*      m_pVampireTreasureList;      // 뱀파이어를 위한 보물의 리스트
	TreasureList*      m_pOustersTreasureList;      // 아우스터즈를 위한 보물의 리스트
	int   		       m_RegenType[REGENTYPE_MAX];	// 각 생성방법의 확률
	int                m_UnburrowChance;            // 생성된 후에 땅위로 나올 확률
	bool               m_bMaster;                   // 뱀파이어 마스터인가?
	int                m_ClanType;                    // 어느 clan에 속하는 몬스터인가?
	MonsterSummonInfo* m_pMonsterSummonInfo;	    // 몬스터 소환 정보
	list<Effect::EffectClass> m_DefaultEffects;		// 몬스터에게 기본적으로 붙어있는 이펙트
	bool				m_bNormalRegen;		// 리젠 시에 선택되는 몬스터 타잎인가?
	bool				m_bHasTreasure;		// Treasure.bin 화일이 필요한가?
	bool				m_bChief;			// 치프 몬스터인가?

	int					m_MonsterClass;		// 몬스터의 클래스
	ItemType_t			m_SkullType;		// 몬스터의 해골 타입
};


//////////////////////////////////////////////////////////////////////////////
// class MonsterInfoManager
//////////////////////////////////////////////////////////////////////////////

class MonsterInfoManager 
{
public:
	MonsterInfoManager() throw();
	~MonsterInfoManager() throw();

public:
	// initialize
	void init() throw(Error);

	// load to database
	void load() throw(Error);
	void reload(MonsterType_t monsterType) throw(Error);

	// add monster info with monster type
	void addMonsterInfo(MonsterType_t monsterType, MonsterInfo* pMonsterInfo) throw(DuplicatedException, OutOfBoundException, Error);

	// get monster info with monster type
	const MonsterInfo* getMonsterInfo(MonsterType_t monsterType) const throw(NoSuchElementException, OutOfBoundException, Error);

	// 임의의 스프라이트 타입을 가진 몬스터의 타입 리스트를 가져온다.
	// (여러 몬스터가 하나의 스프라이트 타입을 가질 수 있기 때문에) 
	const vector<MonsterType_t>& getMonsterTypeBySprite(SpriteType_t spriteType) const throw(NoSuchElementException, OutOfBoundException, Error);
	string	getNameBySpriteType(SpriteType_t spriteType) const;

	SpriteType_t getSpriteTypeByName(const string& monsterName) const throw(NoSuchElementException, Error);
	MonsterType_t getChiefMonsterTypeByName(const string& monsterName) const throw(NoSuchElementException, Error);
	vector<MonsterType_t>& getMonsterTypesByMonsterClass(int MonsterClass) { return m_MonsterClassMap[MonsterClass]; }

	uint	getMaxMonsterType() const	{ return m_MaxMonsterType; }
	MonsterType_t	getRandomMonsterByClass(int minClass, int maxClass);

	// get debug string
	string toString() const throw();

protected :
	void	clearTreasures();

private:
	uint                  m_MaxMonsterType;      // size of MonsterInfo* array
	MonsterInfo**         m_MonsterInfos;          // array of monster info
	vector<MonsterType_t> m_MonsterSpriteSet[MAX_SPRITE_TYPE]; // array of MonsterType by SpriteType
	map<string, SpriteType_t> m_MonsterSpriteTypes; 	// 이름으로 SpriteType_t찾기
	map<string, MonsterType_t> m_ChiefMonster; 	// Chief 몬스터 정보 가지고 있기
	map<int, vector<SpriteType_t> > m_MonsterClassMap; // 몬스터 클래스로 몬스터 타입 찾기

	TreasureLists 			m_SlayerTreasureLists;       // 슬레이어를 위한 보물의 리스트
	TreasureLists    		m_VampireTreasureLists;      // 뱀파이어를 위한 보물의 리스트
	TreasureLists    		m_OustersTreasureLists;      // 아우스터즈를 위한 보물의 리스트
};

// global variable declaration
extern MonsterInfoManager* g_pMonsterInfoManager;

#endif
