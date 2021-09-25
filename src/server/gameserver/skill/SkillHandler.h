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
// ��ũ��, ���, �Լ� ���
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
	int		STR;
	int		DEX;
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
	int Damage;    // ������ �Ǵ� ȿ��ġ
	int Duration;  // ���� �ð��� ������ ����� ���, ���� �ð�
	int Tick;      // ���� �ֱ⸶�� ������ �ִ� ����� ���, �� ���� �ֱ�
	int ToHit;     // �������� �Բ� ���߷��� ���� ��ȭ��Ű�� ����� ���.
	int Range;     // ���õ�, INT � ���� ���� ������ ���ϴ� ����� ���.
	int Delay;     // �������� ����� �� �� �ִ� �ð�
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
	virtual void execute(Slayer* pSlayer, ObjectID_t ObjectID) ;
	virtual void execute(Vampire* pVampire, ObjectID_t ObjectID) ;
	virtual void execute(Vampire* pVampire) ;
	virtual void execute(Ousters* pOusters, ObjectID_t ObjectID) ;
	virtual void execute(Ousters* pOusters) ;

	// Skill To Self
	virtual void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) ;

	// Skill To Object
	virtual void execute(Creature* pCreature, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID, SkillType_t SkillType) ;
	virtual void execute(Slayer* pSlayer,     ObjectID_t ObjectID, SkillSlot*  pSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Vampire* pVampire,   ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Ousters* pOusters,   ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) ;

	// Skill To Tile
	virtual void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) ;

	// Skill To Inventory
	virtual void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot) ;
	virtual void execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot) ;
	virtual void execute(Ousters* pOusters, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, OustersSkillSlot* pOustersSkillSlot) ;
	// Throw Holy Water��...
	virtual void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, ObjectID_t ItemObjectID, CoordInven_t X, CoordInven_t Y) ;
	// Absorb Soul ��
	virtual void execute(Ousters* pOusters, ObjectID_t TargetObjectID, ZoneCoord_t TargetZoneX, ZoneCoord_t TargetZoneY, ObjectID_t InvenObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY) ;

	// Target�� �̸����� �ĺ��Ǵ� ���
	// ex) SoulChain . 
	virtual void execute(PlayerCreature* pPC, const string& TargetName, SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Slayer* pSlayer, const string& TargetName, SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Vampire* pVampire, const string& TargetName, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	virtual void execute(Ousters* pOusters, const string& TargetName, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) ;

	virtual void execute(Monster* pMonster) ;
	virtual void execute(Monster* pMonster, Creature* pEnemy) ;
	virtual void execute(Monster* pMonster, ZoneCoord_t x, ZoneCoord_t y) ;

	virtual void computeOutput(const SkillInput& input, SkillOutput& output) = 0;


///// identity methods /////
public:
	virtual string getSkillHandlerName() const throw() = 0;
	virtual SkillType_t getSkillType() const throw() = 0;
};

#endif
