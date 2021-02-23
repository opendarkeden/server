//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterAI.h
// Written By  : 김성민
// Description : 
// 몬스터의 행동을 결정하는 뇌의 역할을 해주는 AI 클래스이당.
//////////////////////////////////////////////////////////////////////////////

#ifndef __MONSTERAI_H__
#define __MONSTERAI_H__

#include "Creature.h"
#include "Zone.h"
#include "Assert.h"
#include "Timeval.h"
#include "Directive.h"

//////////////////////////////////////////////////////////////////////////////
// 기술 실패 관련 상수
//////////////////////////////////////////////////////////////////////////////
enum
{
	SKILL_FAILED_RANGE  = 1,
	SKILL_FAILED_RATIO  = 2,
	SKILL_FAILED_STATUS = 3,

	SKILL_FAILED_MAX
};

//////////////////////////////////////////////////////////////////////////////
// 딜레이 관련 상수
//////////////////////////////////////////////////////////////////////////////
enum
{
	LAST_ACTION_NONE,
	LAST_ACTION_MOVE,
	LAST_ACTION_SKILL,

	LAST_ACTION_SKILL_MAX
};

//////////////////////////////////////////////////////////////////////////////
// 딜레이 관련 상수
//////////////////////////////////////////////////////////////////////////////
enum MoveRule
{
	MOVE_RULE_NORMAL,
	MOVE_RULE_LEFTWALL,
	MOVE_RULE_RIGHTWALL,

	MOVE_RULE_MAX,
};

//////////////////////////////////////////////////////////////////////////////
// class MonsterAI
//////////////////////////////////////////////////////////////////////////////

class Monster;

typedef bool (*ConditionCheckFunction)(Monster* pMonster, Creature* pEnemy);

class MonsterAI
{
public:

public:
	MonsterAI(Monster* pMonster, uint type) throw();
	virtual ~MonsterAI() throw();

public:
	// 데이터 함수
	bool getDamaged(void) const throw() { return m_bDamaged; }
	void setDamaged(bool value) throw() { m_bDamaged = value; }

	// 다이렉티브 관련 함수
	void addDirective(Directive* pDirective) throw();

	// 조건 함수
	bool checkCondition(int condition, Creature* pEnemy) throw();
	bool checkDirective(Directive* pDirective, Creature* pEnemy) throw();

	// 행동 함수 
	bool move(ZoneCoord_t ex, ZoneCoord_t ey) throw();
	bool move(Creature* pEnemy, bool bRetreat=false) throw();
	bool approach(Creature* pEnemy) throw() { return move(pEnemy, false); }
	bool flee(Creature* pEnemy) throw();
	int  useSkill(Creature* pEnemy, SkillType_t SkillType, int ratio) throw();

	// 이동 함수
	bool moveNormal(ZoneCoord_t ex, ZoneCoord_t ey, ZoneCoord_t& nx, ZoneCoord_t& ny, Dir_t& ndir) throw();
	bool moveWall(ZoneCoord_t ex, ZoneCoord_t ey, ZoneCoord_t& nx, ZoneCoord_t& ny, Dir_t& ndir, bool bLeft) throw();
	void setMoveRule(MoveRule mr) { m_MoveRule = mr; m_WallCount = 0; }

	// 벽타기 --
	MoveRule	getMoveRule() const			{ return m_MoveRule; }
	int			getWallCount() const		{ return m_WallCount; }

	// 행동 패턴 선택 함수 
	void deal(Creature* pEnemy, const Timeval& currentTime) throw();
	void actDeadAction(Creature* pEnemy) throw();

	// 딜레이 관련 함수
	void setDelay(const Timeval& currentTime) throw();
	void setAttackDelay(const Timeval& currentTime) throw();

	bool canAttackAir() const { return m_pDirectiveSet->canAttackAir(); }
	bool canSeeSafeZone() const { return m_pDirectiveSet->canSeeSafeZone(); }

private:
	// 이 AI가 조정하는 본체
	Monster* m_pBody;

	// AI의 성향 타입
	uint m_AIType;

	// 조건과 명령 집합
	DirectiveSet* m_pDirectiveSet;

	// 도망치는 턴 횟수 카운터
	int m_Panic;     

	// 도망치는 최대 턴 횟수
	int m_PanicMax;

	// 도망치다가 멈춰섰을 경우,
	// 안 도망치고 공격하는 횟수 카운터
	int m_Courage; 

	// 안 도망치고 공격하는 최대 턴 횟수
	int m_CourageMax;

	// 지난 턴에 맞았다, 안 맞았다 플래그...
	bool m_bDamaged;

	// 이번 턴에 무엇을 했다는 플래그
	int m_LastAction;

	// 이동하는 방법
	MoveRule m_MoveRule;

	// 벽에 의해 block된 방향==다음에 꼭 갈 수 있어야하는 방향
	Dir_t m_BlockedDir;

	// 벽타고 간 회수
	int m_WallCount;

	// 함수 포인터들...
	ConditionCheckFunction m_pCondChecker[DIRECTIVE_COND_MAX];
};

bool checkEnemyRangeMelee(Monster* pMonster, Creature* pEnemy);
bool checkEnemyRangeMissile(Monster* pMonster, Creature* pEnemy);
bool checkEnemyRangeClose(Monster* pMonster, Creature* pEnemy);
bool checkEnemyRangeOutOfSight(Monster* pMonster, Creature* pEnemy);
bool checkEnemyDying(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotBloodDrained(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotGreenPoisoned(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotYellowPoisoned(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotDarkbluePoisoned(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotGreenStalkered(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotParalyzed(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotDoomed(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotBlinded(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotInDarkness(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotSeduction(Monster* pMonster, Creature* pEnemy);
bool checkImOK(Monster* pMonster, Creature* pEnemy);
bool checkImDying(Monster* pMonster, Creature* pEnemy);
bool checkImDamaged(Monster* pMonster, Creature* pEnemy);
bool checkImHiding(Monster* pMonster, Creature* pEnemy);
bool checkImWolf(Monster* pMonster, Creature* pEnemy);
bool checkImBat(Monster* pMonster, Creature* pEnemy);
bool checkImInvisible(Monster* pMonster, Creature* pEnemy);
bool checkImWalkingWall(Monster* pMonster, Creature* pEnemy);
bool checkTimingBloodDrain(Monster* pMonster, Creature* pEnemy);
// by sigi. 2002.9.4
bool checkMasterSummonTiming(Monster* pMonster, Creature* pEnemy);
bool checkMasterNotReady(Monster* pMonster, Creature* pEnemy);
bool checkImInBadPosition(Monster* pMonster, Creature* pEnemy);
bool checkFindWeakEnemy(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotDeath(Monster* pMonster, Creature* pEnemy);
bool checkEnemyNotHallucination(Monster* pMonster, Creature* pEnemy);

// by sigi. 2002.9.16
bool checkTimingMasterBloodDrain(Monster* pMonster, Creature* pEnemy);

// by sigi. 2002.9.23
bool checkTimingDuplicateSelf(Monster* pMonster, Creature* pEnemy);

// by sigi. 2002.9.24
bool checkEnemyRangeInMissile(Monster* pMonster, Creature* pEnemy);

// by sigi. 2002.10.1
bool checkPossibleSummonMonsters(Monster* pMonster, Creature* pEnemy);

// by Sequoia. 2003.4.14
bool checkEnemyTileNotAcidSwamp(Monster* pMonster, Creature* pEnemy);

bool checkEnemyOnAir(Monster* pMonster, Creature* pEnemy);
bool checkEnemyOnSafeZone(Monster* pMonster, Creature* pEnemy);
bool checkCanAttackThrowingAxe(Monster* pMonster, Creature* pEnemy);

#endif // __MONSTER_H__
