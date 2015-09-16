//////////////////////////////////////////////////////////////////////////////
// Filename    : HitRoll.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __HITROLL_H__
#define __HITROLL_H__

#include "ModifyInfo.h"

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Creature;
class Slayer;
class Vampire;
class Ousters;
class Monster;
class SkillInfo;
class SkillSlot;
class VampireSkillSlot;
class OustersSkillSlot;

//////////////////////////////////////////////////////////////////////////////
// class HitRoll
// 각종 명중굴림 함수를 하나의 네임스페이스로 묶기 위해 만들어진 클래스이다.
//////////////////////////////////////////////////////////////////////////////

class HitRoll
{
public:
	// 일반 공격 명중굴림 함수
	static bool isSuccess(Creature* pAttacker, Creature* pDefender, int ToHitBonus = 0);
//	static bool isSuccess(ToHit_t ToHit, Creature* pDefender, int ToHitBonus = 0);

	// 슬레이어용 마법 명중굴림 함수
	static bool isSuccessMagic(Slayer* pSlayer, SkillInfo* pSkillInfo, SkillSlot* pSkillSlot);

	// 뱀파이어용 마법 명중굴림 함수
	static bool isSuccessMagic(Vampire* pVampire, SkillInfo* pSkillInfo, VampireSkillSlot* pVampireSkillSlot, int BonusPoint = 0);

	// 아우스터스용 마법 명중굴림 함수
	static bool isSuccessMagic(Ousters* pOusters, SkillInfo* pSkillInfo, OustersSkillSlot* pOustersSkillSlot, int BonusPoint = 0);

	// 몬스터용 마법 명중굴림 함수
	static bool isSuccessMagic(Monster* pMonster, SkillInfo* pSkillInfo);

	// 뱀파이어 및 몬스터용 흡혈 명중굴림 함수
	static bool isSuccessBloodDrain(Creature* pAttacker, Creature* pDefender, int multiplier = 3);

	// 저주 계열 마법 명중굴림 함수
	static bool isSuccessCurse(int MagicLevel, Resist_t resist);
	static bool isSuccessVampireCurse(int MagicLevel, Resist_t resist);

	// CurePoison 명중굴림 함수
	static bool isSuccessCurePoison(int Base, int SkillLevel, int Difficulty, int MagicLevel, int MinRatio = 0);

	// Flare 명중굴림 함수
	static bool isSuccessFlare(Creature* pTargetCreature, int SkillLevel);

	// RemoveCurse 명중굴림 함수
	static bool isSuccessRemoveCurse(int Base, int SkillLevel, int Difficulty, int MagicLevel, int MinRatio = 0);

	// Rebuke 명중굴림 함수
	static bool isSuccessRebuke(Slayer* pSlayer, SkillSlot* pSkillSlot, Creature* pDefender);

	// Magic Elusion 명중굴림 함수
	static bool isSuccessMagicElusion(Slayer* pSlayer);

	// Poison Mesh 명중굴림 함수
	static bool isSuccessPoisonMesh(Vampire* pVampire);

	// Illusion Of Avenge 명중굴림 함수
	static bool isSuccessIllusionOfAvenge(Slayer *pSlayer);

	// Will Of Life 명중굴림 함수
	static bool isSuccessWillOfLife(Vampire* pVampire);

	// 크리티컬 히트 롤을 수행한다.
	static bool isCriticalHit(Creature* pCreature, int CriticalBonus = 0);

	// 슬레이어 셀프 스킬인가를 체크하는 함수
	static bool isSlayerSelfSkill(SkillType_t skillType);
	static bool isOustersSelfSkill(SkillType_t skillType);

	// 할루 성공률
	static bool isSuccessHallucination(Vampire* pAttacker, Creature* pTarget);

	// 백스탭 성공률
	static bool isSuccessBackStab(Ousters* pAttacker);
};

#endif
