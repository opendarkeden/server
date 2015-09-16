//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillInfo.h
// Written By  : beowulf
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_INFO_H__
#define __SKILL_INFO_H__

#include "Exception.h"
#include "Types.h"
#include "Slayer.h"
#include <bitset>
#include <list>

class Ousters;

enum {
	SKILL_PROPERTY_TYPE_MELEE = 0,
	SKILL_PROPERTY_TYPE_MAGIC = 1,
	SKILL_PROPERTY_TYPE_PHYSIC = 2,

	SKILL_PROPERTY_TYPE_MAX
};


//////////////////////////////////////////////////////////////////////////////
// Class SkillInfo
//////////////////////////////////////////////////////////////////////////////

class SkillInfo 
{
public:
	SkillInfo();
	~SkillInfo();

public:
	uint getType() const { return m_Type; }
	void setType(uint type) { m_Type = type; }

	string getName() const { return m_Name ; }
	void setName(string name) { m_Name = name ; }

	uint getLevel() const { return m_Level; }
	void setLevel(uint level) { m_Level = level; }

	uint getMinDamage() const { return m_MinDamage; }
	void setMinDamage(uint mindam) { m_MinDamage = mindam ; }

	uint getMaxDamage() const { return m_MaxDamage; }
	void setMaxDamage(uint maxdam) { m_MaxDamage = maxdam; }

	uint getMinDelay() const { return m_MinDelay ; }
	void setMinDelay(uint mindelay) { m_MinDelay = mindelay; }

	uint getMaxDelay() const { return m_MaxDelay ; }
	void setMaxDelay(uint maxdelay) { m_MaxDelay = maxdelay; }

	uint getMinCastTime() const { return m_MinCastTime ; }
	void setMinCastTime(uint mincasttime) { m_MinCastTime = mincasttime ; }

	uint getMaxCastTime() const { return m_MaxCastTime ; }
	void setMaxCastTime(uint maxcasttime) { m_MaxCastTime = maxcasttime ; }

	int getMinDuration() const { return m_MinDuration ; }
	void setMinDuration(int minduration) { m_MinDuration = minduration ; }

	int getMaxDuration() const { return m_MaxDuration ; }
	void setMaxDuration(int maxduration) { m_MaxDuration = maxduration ; }

	uint getConsumeMP() const { return m_ConsumeMP; }
	void setConsumeMP(uint consumemp) { m_ConsumeMP = consumemp; }

	uint getRange() const { return m_MaxRange; }

	uint getMaxRange() const { return m_MaxRange ; }
	void setMaxRange(uint range) { m_MaxRange = range; }

	uint getMinRange() const { return m_MinRange ; }
	void setMinRange(uint range) { m_MinRange = range; }

	uint getTarget() const { return m_Target; }
	void setTarget(uint target) { m_Target = target ; }
	
	// 새로운 버젼을 위해.(합쳐진 버전...)
	uint getSubSkill() const { return m_SubSkill; }
	void setSubSkill(uint subskill) { m_SubSkill = subskill; }

	uint getPoint() const { return m_Point ; }
	void setPoint(uint point) { m_Point = point; }
	
	BYTE getDomainType() const { return m_Domain; }
	void setDomainType(uint domain) { m_Domain = domain; }

	int getMagicDomain(void) const { return m_MagicDomain; }
	void setMagicDomain(int magic) { m_MagicDomain = magic; }

	int getElementalDomain(void) const { return m_ElementalDomain; }
	void setElementalDomain(int elemental) { m_ElementalDomain = elemental; }

	bool isMelee() const { return m_PropertyType.test(SKILL_PROPERTY_TYPE_MELEE); }
	void setMelee(bool bMelee )
	{
		(bMelee ? m_PropertyType.set(SKILL_PROPERTY_TYPE_MELEE )
		  		 : m_PropertyType.reset(SKILL_PROPERTY_TYPE_MELEE )); }

	bool isMagic() const { return m_PropertyType.test(SKILL_PROPERTY_TYPE_MAGIC); }
	void setMagic(bool bMagic ) 
	{
		(bMagic ? m_PropertyType.set(SKILL_PROPERTY_TYPE_MAGIC )
				 : m_PropertyType.reset(SKILL_PROPERTY_TYPE_MAGIC ));
	}

	bool isPhysic() const { return m_PropertyType.test(SKILL_PROPERTY_TYPE_PHYSIC); }
	void setPhysic(bool bPhysic )
	{ 
		(bPhysic ? m_PropertyType.set(SKILL_PROPERTY_TYPE_PHYSIC )
		  		  : m_PropertyType.reset(SKILL_PROPERTY_TYPE_PHYSIC ));
	}

	// 배우기 위해 필요한 스킬 포인트
	int getSkillPoint() const { return m_SkillPoint; }
	void setSkillPoint(int skillPoint ) { m_SkillPoint = skillPoint; }

	// 스킬 레벨 업 포인트
	int getLevelUpPoint() const { return m_LevelUpPoint; }
	void setLevelUpPoint(int levelUpPoint ) { m_LevelUpPoint = levelUpPoint; }

	// 이전에 배워야 할 스킬들
	void addRequireSkill(SkillType_t skillType ) { m_RequireSkills.push_back(skillType); }
	list<SkillType_t>& getRequireSkills() { return m_RequireSkills; }

	// 이전에 배워야 할 스킬들
	void addRequiredSkill(SkillType_t skillType ) { m_RequiredSkills.push_back(skillType); }
	list<SkillType_t>& getRequiredSkills() { return m_RequiredSkills; }

	BYTE canDelete() const { return m_CanDelete; }
	void setCanDelete(BYTE canDelete) { m_CanDelete = canDelete; }

	////////////////////////////////////////////////////////////////////////////
	// 시전하기 위해 필요한 조건들. 아우스터스용 
	////////////////////////////////////////////////////////////////////////////
	Elemental_t getRequireFire() const { return m_RequireFire; }
	Elemental_t getRequireWater() const { return m_RequireWater; }
	Elemental_t getRequireEarth() const { return m_RequireEarth; }
	Elemental_t getRequireWind() const { return m_RequireWind; }
	Elemental_t getRequireSum() const { return m_RequireSum; }

	ElementalType getRequireWristletElemental() const { return m_RequireWristletElemental; }
	ElementalType getRequireStone1Elemental() const { return m_RequireStone1Elemental; }
	ElementalType getRequireStone2Elemental() const { return m_RequireStone2Elemental; }
	ElementalType getRequireStone3Elemental() const { return m_RequireStone3Elemental; }
	ElementalType getRequireStone4Elemental() const { return m_RequireStone4Elemental; }

	void setRequireFire(Elemental_t require ) { m_RequireFire = require; }
	void setRequireWater(Elemental_t require ) { m_RequireWater = require; }
	void setRequireEarth(Elemental_t require ) { m_RequireEarth = require; }
	void setRequireWind(Elemental_t require ) { m_RequireWind = require; }
	void setRequireSum(Elemental_t require ) { m_RequireSum = require; }

	void setRequireWristletElemental(ElementalType require ) { m_RequireWristletElemental = require; }
	void setRequireStone1Elemental(ElementalType require ) { m_RequireStone1Elemental = require; }
	void setRequireStone2Elemental(ElementalType require ) { m_RequireStone2Elemental = require; }
	void setRequireStone3Elemental(ElementalType require ) { m_RequireStone3Elemental = require; }
	void setRequireStone4Elemental(ElementalType require ) { m_RequireStone4Elemental = require; }

	void setRequireSkill(const string& requireSkill);
	void setCondition(const string& condition);

	// toString
	string toString() const ;

private:
	uint   m_Type;        // Type
	string m_Name;        // Name
	uint   m_Level;       // m_Level
	uint   m_MinDamage;   // 최소 데미지
	uint   m_MaxDamage;   // 최대 데미지
	uint   m_MinDelay;    // 최소 딜레이 
	uint   m_MaxDelay;    // 최대 딜레이
	uint   m_MinCastTime; // 캐스팅 타임.. 초단위
	uint   m_MaxCastTime; // 최대 캐스팅 타임

	// 최소 지속시간
	// 최대 최소가 구별없이 그냥 지속시간만 있는 것은 최소 지속시간에서 읽어오면 된다.
	// 지속시간이 0인 것은 Instant, -1 은 Long을 의미한다.
	int m_MinDuration;

	// 최대 지속시간
	int m_MaxDuration;

	// MP 소비량
	uint m_ConsumeMP;

	// 최대 최소 사정거리, 시야???
	uint m_MaxRange;
	uint m_MinRange;

	// 명중시킬 수 있는 타겟의 MoveType
	// 0x01 : burrowing
	// 0x02 : walking
	// 0x04 : flying
	uint m_Target;
	
	// 합쳐진 버젼을 위해..
	uint m_SubSkill;
	uint m_Point;

	BYTE m_Domain;

	// 마법의 계열. 독, 산, 저주 등등
	int m_MagicDomain;

	// 정령 계열
	int m_ElementalDomain;

	// 필요한 스킬 포인트
	int m_SkillPoint;
	int m_LevelUpPoint;

	// 이전에 배워야할 스킬들
	list<SkillType_t> m_RequireSkills;

	// 이거 다음에 배울 수 있는 스킬들
	list<SkillType_t> m_RequiredSkills;

	BYTE	m_CanDelete;

	// 시전하기 위해 필요한 조건들
	// 아우스터스 용
	Elemental_t m_RequireFire;
	Elemental_t m_RequireWater;
	Elemental_t m_RequireEarth;
	Elemental_t m_RequireWind;
	Elemental_t m_RequireSum;

	ElementalType m_RequireWristletElemental;
	ElementalType m_RequireStone1Elemental;
	ElementalType m_RequireStone2Elemental;
	ElementalType m_RequireStone3Elemental;
	ElementalType m_RequireStone4Elemental;

	bitset<SKILL_PROPERTY_TYPE_MAX> m_PropertyType;
};

//////////////////////////////////////////////////////////////////////////////
// Class SkillInfoManager
//////////////////////////////////////////////////////////////////////////////

class SkillInfoManager 
{
public:
	SkillInfoManager() throw();
	~SkillInfoManager() throw();

public:

	// initialize Manager
	void init() throw(Error);

	// void load() throw();
	void load() throw(Error);
	
	// Save to DB
	void save() throw(Error);

	// get SkillInfo
	SkillInfo* getSkillInfo(SkillType_t SkillType) const throw(NoSuchElementException, OutOfBoundException, Error);

	// add SkillInfo
	void addSkillInfo(SkillInfo* pSkillInfo) throw(DuplicatedException, Error);

	// get SkillType by LearnLevel
	// 현재의 도메인 레벨에서 배울 수 있는 기술의 타입은 어떤 것인지 찾는다.
	// 도메인의 레벨로 알 수 있지렁.
	SkillType_t getSkillTypeByLevel(SkillDomainType_t SkillDomain, Level_t Level) throw(OutOfBoundException);

	// 도메인의 레벨로 그 레벨은 어떤 등급에 해당하는지 아는 함수.
	SkillGrade getGradeByDomainLevel(Level_t Level) throw(OutOfBoundException);

	// 현재 등급에서 기술이 어느정도 레벨까지 올라갈 수 있는지 알아 본다.
	Level_t getLimitLevelByDomainGrade(SkillGrade Grade) throw(OutOfBoundException);

	// 현재 INT에서 MP 감소량을 뽑아내기 위한 함수.
	MP_t getdecreaseConsumeMP(Attr_t INT) { return m_decreaseConsumeMP[INT]; }

	// toString for Debug
	string toString() const throw();

private:
	uint         m_SkillCount;
	SkillInfo**  m_SkillInfoList;
	SkillType_t  m_SkillLevelMap[SKILL_DOMAIN_MAX][SLAYER_MAX_DOMAIN_LEVEL+1];
	SkillGrade   m_DomainGradeMap[SLAYER_MAX_DOMAIN_LEVEL+1];
	Level_t      m_LimitLevelMap[SKILL_GRADE_MAX + 1];
	MP_t         m_decreaseConsumeMP[300+1];
		
};

// Global Variable Definition
extern SkillInfoManager* g_pSkillInfoManager;

#endif	// __SKILL_INFO_MANAGER_H__
