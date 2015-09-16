//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillHandler.h 
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HANDLER_H__
#define __SKILL_HANDLER_H__

#include "Skill.h"
#include "SkillInfo.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Monster.h"
#include "Item.h"
#include "ModifyInfo.h"
#include "HitRoll.h"
#include "SkillUtil.h"
#include "ZoneUtil.h"
#include "GamePlayer.h"
#include "Thread.h"
#include <algorithm>
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// 매크로, 상수, 함수 헤더
//////////////////////////////////////////////////////////////////////////////

#define MAKEWORD(U,D) (WORD)((WORD)(U)<<8  |(WORD)(D))
#define MAKEDWORD(U,D)(DWORD)((DWORD)(U)<<16 |(DWORD)(D))

void getExplosionTypeXYOffset(int, int, const int*&, const int*&, int&); 


//////////////////////////////////////////////////////////////////////////////
// class SkillInput & SkillOutput
//////////////////////////////////////////////////////////////////////////////

class SkillInput
{
public:
	enum TargetType
	{
		TARGET_SELF = 0,
		TARGET_OTHER,
		TARGET_MAX
	};

	enum TargetRace
	{
		TARGET_PC = 0,
		TARGET_MONSTER
	};

public:
	SkillInput() {}
	SkillInput(Slayer* pSlayer, SkillSlot* pSkillSlot);
	SkillInput(Vampire* pVampire);
	SkillInput(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot);
	SkillInput(Monster* pMonster);

public:
	int             SkillLevel;
	int             DomainLevel;
	int				STR;
	int				DEX;
	int             INTE;
	int             TargetType;
	int             Range;
	Item::ItemClass IClass;
	int             PartySize;
};

class SkillOutput
{
public:
	SkillOutput()
	{
		Damage   = 0;
		Duration = 0;
		Tick     = 0;
		ToHit    = 0;
		Range    = 0;
		Delay    = 0;
	}

public:
	int Damage;    // 데미지 또는 효과치
	int Duration;  // 지속 시간을 가지는 기술일 경우, 지속 시간
	int Tick;      // 일정 주기마다 영향을 주는 기술일 경우, 그 일정 주기
	int ToHit;     // 데미지와 함께 명중률도 같이 변화시키는 기술일 경우.
	int Range;     // 숙련도, INT 등에 따라 영향 범위가 변하는 기술일 경우.
	int Delay;     // 다음으로 기술을 쓸 수 있는 시간
};


//////////////////////////////////////////////////////////////////////////////
// class SkillHandler
//////////////////////////////////////////////////////////////////////////////

class SkillHandler 
{
///// constructor & destructor /////
public:
	SkillHandler() throw() {}
	virtual ~SkillHandler() throw() {}


///// method header for overriding /////
public:
	virtual void execute(Slayer* pSlayer, ObjectID_t ObjectID) throw(Error);
	virtual void execute(Vampire* pVampire, ObjectID_t ObjectID) throw(Error);
	virtual void execute(Vampire* pVampire) throw(Error);
	virtual void execute(Ousters* pOusters, ObjectID_t ObjectID) throw(Error);
	virtual void execute(Ousters* pOusters) throw(Error);

	// Skill To Self
	virtual void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	// Skill To Object
	virtual void execute(Creature* pCreature, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID, SkillType_t SkillType) throw(Error);
	virtual void execute(Slayer* pSlayer,     ObjectID_t ObjectID, SkillSlot*  pSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Vampire* pVampire,   ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Ousters* pOusters,   ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	// Skill To Tile
	virtual void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	// Skill To Sub Inventory
	virtual void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, ObjectID_t InventoryItemObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot) throw(Error);
	virtual void execute(Vampire* pVampire, ObjectID_t TargetObjectID, ObjectID_t InventoryItemObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot) throw(Error);
	virtual void execute(Ousters* pOusters, ObjectID_t TargetObjectID, ObjectID_t InventoryItemObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, OustersSkillSlot* pOustersSkillSlot) throw(Error);

	// Skill To Inventory
	virtual void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot) throw(Error);
	virtual void execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot) throw(Error);
	virtual void execute(Ousters* pOusters, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, OustersSkillSlot* pOustersSkillSlot) throw(Error);
	// Throw Holy Water용...
	virtual void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, ObjectID_t ItemObjectID, CoordInven_t X, CoordInven_t Y) throw(Error);
	// Absorb Soul 용
	virtual void execute(Ousters* pOusters, ObjectID_t TargetObjectID, ZoneCoord_t TargetZoneX, ZoneCoord_t TargetZoneY, ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY) throw(Error);

	// Target이 이름으로 식별되는 경우
	// ex) SoulChain . 
	virtual void execute(PlayerCreature* pPC, const string& TargetName, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Slayer* pSlayer, const string& TargetName, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Vampire* pVampire, const string& TargetName, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	virtual void execute(Ousters* pOusters, const string& TargetName, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	virtual void execute(Monster* pMonster) throw(Error);
	virtual void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	virtual void execute(Monster* pMonster, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

	virtual void computeOutput(const SkillInput& input, SkillOutput& output) = 0;


///// identity methods /////
public:
	virtual string getSkillHandlerName() const throw() = 0;
	virtual SkillType_t getSkillType() const throw() = 0;
};

#endif
