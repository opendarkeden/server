//////////////////////////////////////////////////////////////////////////////
// Filename    : AbilityBalance.h
// Written By  : 김성민
// Description : 
// 각 크리쳐 별로 능력치를 계산하는 함수들을 모아놓은 파일이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ABILITY_BALANCE_H__
#define __ABILITY_BALANCE_H__

#include "Creature.h"

#define SLAYER_MAX_HP          10000
#define SLAYER_MAX_MP          10000
#define SLAYER_MAX_TOHIT       10000
#define SLAYER_MAX_DEFENSE     10000
#define SLAYER_MAX_PROTECTION  10000
#define SLAYER_MAX_DAMAGE      10000

#define VAMPIRE_MAX_HP         10000
#define VAMPIRE_MAX_TOHIT      10000
#define VAMPIRE_MAX_DEFENSE    10000
#define VAMPIRE_MAX_PROTECTION 10000
#define VAMPIRE_MAX_DAMAGE     10000

#define OUSTERS_MAX_HP         10000
#define OUSTERS_MAX_MP         10000
#define OUSTERS_MAX_TOHIT      10000
#define OUSTERS_MAX_DEFENSE    10000
#define OUSTERS_MAX_PROTECTION 10000
#define OUSTERS_MAX_DAMAGE     10000

#define MONSTER_MAX_HP         60000
#define MONSTER_MAX_TOHIT       1000
#define MONSTER_MAX_DEFENSE     1000
#define MONSTER_MAX_PROTECTION  1000
#define MONSTER_MAX_DAMAGE      1000

#define SLAYER_MAX_ATTACK_SPEED   35
#define VAMPIRE_MAX_ATTACK_SPEED  30
#define OUSTERS_MAX_ATTACK_SPEED  35

typedef struct
{
	int   nSTR;
	int   nDEX;
	int   nINT;
	int   nLevel;
	int   pDomainLevel[SKILL_DOMAIN_MAX];
	Item* pWeapon;
} BASIC_ATTR;

HP_t         computeHP(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance=0);
MP_t         computeMP(Creature::CreatureClass CClass, BASIC_ATTR* pAttr);
ToHit_t      computeToHit(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance=0);
Defense_t    computeDefense(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance=0);
Protection_t computeProtection(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance=0);
Damage_t     computeMinDamage(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance=0);
Damage_t     computeMaxDamage(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance=0);
Speed_t      computeAttackSpeed(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance=0);
int          computeCriticalRatio(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance=0);
Steal_t      computeStealRatio(Creature::CreatureClass CClass, Steal_t amount, BASIC_ATTR* pAttr);


#endif

