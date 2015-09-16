//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleSkill.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SIMPLESKILL__
#define __SIMPLESKILL__

#include "SkillHandler.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class TILE_MASK
{
public:
	TILE_MASK()
	{
		x       = 0;
		y       = 0;
		penalty = 100;
	}
	TILE_MASK(int _x, int _y, int _penalty=100)
	{
		x       = _x;
		y       = _y;
		penalty = _penalty;
	}

public:
	int x;        // 중심이 되는 좌표로부터의 x offset
	int y;        // 중심이 되는 좌표로부터의 y offset
	int penalty;  // 데미지 계산시 가할 페널티
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class SIMPLE_SKILL_INPUT
{
public:
	SIMPLE_SKILL_INPUT()
	{
		SkillType     = SKILL_MAX;
		SkillDamage   = 0;
		Delay         = 0;
		ItemClass     = Item::ITEM_CLASS_MAX;
		STRMultiplier = 0;
		DEXMultiplier = 0;
		INTMultiplier = 0;
		Level         = 0;
		bMagicHitRoll = false;
		bMagicDamage  = false;
		bAdd          = false;
		bExpForTotalDamage = false;
		Grade		  = 0;
	}

	~SIMPLE_SKILL_INPUT()
	{
		MaskList.clear();
	}

public:
	void addMask(const TILE_MASK& mask)
	{
		MaskList.push_back(mask);
	}
	void addMask(int x, int y, int penalty)
	{
		MaskList.push_back(TILE_MASK(x, y, penalty));
	}

public:
	SkillType_t     SkillType;     // 스킬 타입
	Damage_t        SkillDamage;   // 스킬의 효과치
	Turn_t          Delay;         // 스킬의 딜레이
	Item::ItemClass ItemClass;     // 기술을 사용하기 위해 필요한 아이템
	int             STRMultiplier; // 슬레이어 능력치 경험치 증폭치
	int             DEXMultiplier; // 슬레이어 능력치 경험치 증폭치
	int             INTMultiplier; // 슬레이어 능력치 경험치 증폭치
	int             Level;         // 여러 가지 목적으로 쓰이는 레벨
	bool            bMagicHitRoll; // 마법 명중률 굴림인가, 일반 공격 굴림인가...
	bool            bMagicDamage;  // 스킬의 데미지가 마법 데미지인가...
	bool            bAdd;          // SkillDamage를 더해야 하나, 그냥 써야 하나...
	list<TILE_MASK> MaskList;      // 타일 스킬일 경우, 마스크 리스트
	bool			bExpForTotalDamage;	// 전체 damage에 대해서 경험치를 올려준다.
	BYTE			Grade;		   // 스킬 등급
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class SIMPLE_SKILL_OUTPUT
{
public:
	SIMPLE_SKILL_OUTPUT()
	{
		bSuccess = false;
		pTargetCreature = NULL;
	}

public:
	bool      bSuccess;
	Creature* pTargetCreature;
	list<Creature*> targetCreatures;
};

#endif
