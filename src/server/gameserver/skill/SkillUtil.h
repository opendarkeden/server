//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillUtil.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILLUTIL_H__
#define __SKILLUTIL_H__

#include "ModifyInfo.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"

//////////////////////////////////////////////////////////////////////////////
// 매크로, 상수
//////////////////////////////////////////////////////////////////////////////

// decreaseMana를 호출했을 경우, 
// MP만 닳았으면 CONSUME_MP를, HP만 닳았을 경우에는 CONSUME_HP를,
// 둘 다 소모되었을 경우에는, BOTH를 리턴한다.
#define CONSUME_MP    0
#define CONSUME_HP    1
#define CONSUME_BOTH  2

#define MAKEWORD(U,D) (WORD)((WORD)(U)<<8  |(WORD)(D))
#define MAKEDWORD(U,D)(DWORD)((DWORD)(U)<<16 |(DWORD)(D))

//#define VAMPIRE_MAX_LEVEL	150

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////
class Creature;
class Monster;
class SkillInfo;
class SkillSlot;
class VampireSkillSlot;
class Item;
class Zone;

//////////////////////////////////////////////////////////////////////////////
// 데미지 계산 함수
//////////////////////////////////////////////////////////////////////////////

// 공격자와 피공격자 사이의 파라미터를 계산해 최종 데미지를 산출한다.
Damage_t computeDamage(Creature* pCreature, Creature* pTargetCreature);

// 공격자의 순수 데미지를 계산한다.
Damage_t computePureDamage(Creature* pCreature);

// 공격자와 피공격자 사이의 파라미터를 계산해 최종 데미지를 산출한다.
// 위의 함수와 같으나, 이 함수를 부를 경우에는 내부적으로 크리티컬 히트와 관련된 부분이 처리된다.
Damage_t computeDamage(Creature* pCreature, Creature* pTargetCreature, int CriticalBonus, bool& bCritical);

// 원래 데미지에서 프로텍션을 제외한 최종 데미지를 리턴한다.
double computeFinalDamage(Damage_t minDamage, Damage_t maxDamage, Damage_t realDamage, Protection_t Protection, bool bCritical);

// 슬레이어 공격자와 피공격자 사이의 데미지를 계산한다.
Damage_t computeSlayerDamage(Slayer* pSlayer, Creature* pTargetCreature, bool bCritical);

// 뱀파이어 공격자와 피공격자 사이의 데미지를 계산한다.
Damage_t computeVampireDamage(Vampire* pVampire, Creature* pTargetCreature, bool bCritical);

// 아우스터스 공격자와 피공격자 사이의 데미지를 계산한다.
Damage_t computeOustersDamage(Ousters* pOusters, Creature* pTargetCreature, bool bCritical);

// 몬스터 공격자와 피공격자 사이의 데미지를 계산한다.
Damage_t computeMonsterDamage(Monster* pMonster, Creature* pTargetCreature, bool bCritical);

// 슬레이어 공격자의 순수 데미지를 계산한다.
Damage_t computePureSlayerDamage(Slayer* pSlayer);

// 뱀파이어 공격자의 순수 데미지를 계산한다.
Damage_t computePureVampireDamage(Vampire* pVampire);

// 아우스터스 공격자의 순수 데미지를 계산한다.
Damage_t computePureOustersDamage(Ousters* pOusters);

// 몬스터 공격자와 피공격자 사이의 데미지를 계산한다.
Damage_t computePureMonsterDamage(Monster* pMonster);

// resistance를 고려한 마법 데미지를 계산한다.
Damage_t computeMagicDamage(Creature* pTargetCreature, int Damage, SkillType_t SkillType, bool bVampire = false, Creature* pAttacker = NULL);

// 리스틀릿을 고려한 아우스터즈 마법 데미지를 계산한다.
Damage_t computeOustersMagicDamage(Ousters* pOusters, Creature* pTargetCreature, int Damage, SkillType_t SkillType);

// 타겟에게 미치는 은 데미지를 계산한다.
Damage_t computeSlayerSilverDamage(Creature* pCreature, int Damage, ModifyInfo* pMI);

// Critical Magic 과 같은 패시브 스킬로 인한 데미지 변화와 크리티컬 변화를 계산한다.
void computeCriticalBonus(Ousters* pOusters, SkillType_t skillType, Damage_t& Damage, bool& bCriticalHit);

//////////////////////////////////////////////////////////////////////////////
// 데미지 세팅, 내구도 떨어뜨리기 등등...
//////////////////////////////////////////////////////////////////////////////

// 직접적으로 데미지를 세팅한다.
HP_t setDamage(Creature* pTargetCreature, Damage_t Damage, Creature* pAttacker, SkillType_t SkillType = 0, ModifyInfo* pMI = NULL, ModifyInfo* pAttackerMI = NULL, bool canKillTarget = true, bool canSteal = true);

// 아이템 내구도를 떨어뜨린다.
void decreaseDurability(Creature* pCreature, Creature* pTargetCreature, SkillInfo* pSkillInfo, ModifyInfo*, ModifyInfo*);

// 타겟을 맞출 가능성이 있는가?
bool canHit(Creature* pAttacker, Creature* pDefender, SkillType_t SkillType, SkillLevel_t SkillLevel=0);


//////////////////////////////////////////////////////////////////////////////
// 마나 관련 함수들...
//////////////////////////////////////////////////////////////////////////////

// 인트에 따라 마나 소모량이 변하는 뱀파이어 마법의 마나 소모량을 계산한다.
MP_t decreaseConsumeMP(Vampire* pVampire, SkillInfo* pSkillInfo);

// 기술을 사용하기 위한 충분한 마나를 가지고 있는가?
bool hasEnoughMana(Creature* pCaster, int RequiredMP);

// 마나를 줄인다.
int decreaseMana(Creature* pCaster, int MP, ModifyInfo& modifyinfo);


//////////////////////////////////////////////////////////////////////////////
// 사정거리, 지속시간, 시간체크 등의 검증 함수들...
//////////////////////////////////////////////////////////////////////////////

// 슬레이어용 스킬의 사정거리를 구한다.
Range_t computeSkillRange(SkillSlot* pSkillSlot, SkillInfo* pSkillInfo);

//(OX,OY)와(TX,TY) 사이의 거리를 구한다.
Range_t getDistance(ZoneCoord_t OX, ZoneCoord_t OY, ZoneCoord_t TX, ZoneCoord_t TY);

// 스킬을 쓸 수 있는 적당한 거리인가를 검증
bool verifyDistance(Creature* pCreature, ZoneCoord_t X, ZoneCoord_t Y, Range_t Distance);

// 스킬을 쓸 수 있는 적당한 거리인가를 검증
bool verifyDistance(Creature* pCreature, Creature* pTargetCreature, Range_t Distance);

// 슬레이어용 스킬의 실행 시간을 검증한다.
bool verifyRunTime(SkillSlot* pSkillSlot);

// 뱀파이어용 스킬의 실행 시간을 검증한다.
bool verifyRunTime(VampireSkillSlot* pSkillSlot);

// 아우스터스용 스킬의 실행 시간을 검증한다.
bool verifyRunTime(OustersSkillSlot* pSkillSlot);

// 각 존의 PK 정책에 따라, PK가 되느냐 안 되느냐를 정한다.
bool verifyPK(Creature* pAttacker, Creature* pDefender);

// 기술을 사용할 수 있는 존인가?
// (셀프 기술일 경우, 존 레벨을 체크하는 함수다...)
bool checkZoneLevelToUseSkill(Creature* pCaster);

// X, Y에 서 있는 크리쳐가 임의의 기술에 영향을 받는지 체크하는 함수다.
bool checkZoneLevelToHitTarget(Creature* pTargetCreature);

// 기술이 밀리 공격인가? - 2003. 1. 1. Sequoia
//bool isMeleeSkill(SkillType_t SkillType);

// Magic 기술인가?
//bool isMagicSkill(SkillType_t SkillType);
// Physic 기술인가?
//bool isPhysicSkill(SkillType_t SkillType);

//////////////////////////////////////////////////////////////////////////////
// 성향 관련 함수들...
//////////////////////////////////////////////////////////////////////////////

// 성향을 변경한다.
// 기술을 사용하거나, PK를 할 때 생기는 성향 변화를 계산하는 함수다.
void computeAlignmentChange(Creature* pTargetCreature, Damage_t Damage, Creature* pAttacker, ModifyInfo* pMI = NULL, ModifyInfo* pAttackerMI = NULL);

// 슬레이어 및 뱀파이어가 몹을 죽일 때 성향을 약간씩 회복시킨다.
// 정당 방위 시스템 같은 것과는 관련 없이, 그냥 타종족을 공격할 때 
// 약간씩 성향을 회복시켜주는 함수이다.
void increaseAlignment(Creature* pCreature, Creature* pEnemy, ModifyInfo& mi);

//////////////////////////////////////////////////////////////////////////////
// 경험치 관련 함수들...
//////////////////////////////////////////////////////////////////////////////

// 파티 관련 슬레이어 경험치 계산 함수
void shareAttrExp(Slayer* pSlayer, Damage_t Damage, BYTE STRMultiplier, BYTE DEXMultiplier, BYTE INTMultiplier, ModifyInfo &);

// 파티 관련 뱀파이어 경험치 계산 함수
void shareVampExp(Vampire*, Exp_t, ModifyInfo&);

// 파티 관련 아우스터스 경험치 계산 함수
void shareOustersExp(Ousters*, Exp_t, ModifyInfo&);

// 슬레이어 능력치(STR,DEX,INT) 경험치를 계산한다.
void divideAttrExp(Slayer* pSlayer, Damage_t Damage, BYTE STRMultiplier, BYTE DEXMultiplier, BYTE INTMultiplier, ModifyInfo &, int numPartyMember=-1);

// 슬레이어 기술 경험치를 계산한다.
void increaseSkillExp(Slayer* pSlayer, SkillDomainType_t DomainType, SkillSlot* pSkillSlot, SkillInfo* pSkillInfo, ModifyInfo&);

// 슬레이어 계열 경험치를 계산한다.
bool increaseDomainExp(Slayer* pSlayer, SkillDomainType_t Domain, Exp_t Exp, ModifyInfo &, Level_t EnemyLevel = 0, int TargetNum = -1);

// 뱀파이어 경험치를 계산한다.
void increaseVampExp(Vampire*, Exp_t, ModifyInfo&);

// 아우스터스 경험치를 계산한다.
void increaseOustersExp(Ousters*, Exp_t, ModifyInfo&);

// 슬레이어 및 뱀파이어 명성을 계산한다.
void increaseFame(Creature* pAttackee, uint amount);

// 죽였을때의 처리
RankExp_t computeRankExp(int myLevel, int otherLevel);
void affectKillCount(Creature* pAttacker, Creature* pDeadCreature);

//////////////////////////////////////////////////////////////////////////////
// 기타 함수들...
//////////////////////////////////////////////////////////////////////////////

// 거리에 따른 SG, SR의 보너스를 계산한다.
int computeArmsWeaponSplashSize(Item* pWeapon, int ox, int oy, int tx, int ty);
int computeArmsWeaponDamageBonus(Item* pWeapon, int ox, int oy, int tx, int ty);
int computeArmsWeaponToHitBonus(Item* pWeapon, int ox, int oy, int tx, int ty);

// 지정된 좌표 주위의 스플래쉬 데미지를 맞을 크리쳐를 뽑아온다. 
int getSplashVictims(Zone* pZone, int cx, int cy, Creature::CreatureClass CClass, list<Creature*>& creatureList, int splash);
int getSplashVictims(Zone* pZone, int cx, int cy, Creature::CreatureClass CClass, list<Creature*>& creatureList, int splash, int range);
int getSplashVictims(Zone* pZone, int cx, int cy, list<Creature*>& creatureList, int splash);

// 레벨업 시 HP와 MP를 꽉 채워준다.
void healCreatureForLevelUp(Slayer* pSlayer, ModifyInfo& _ModifyInfo, SLAYER_RECORD* prev);
void healCreatureForLevelUp(Vampire* pVampire, ModifyInfo& _ModifyInfo, VAMPIRE_RECORD* prev);
void healCreatureForLevelUp(Ousters* pOusters, ModifyInfo& _ModifyInfo, OUSTERS_RECORD* prev);

// 기술 실패시 패킷을 날린다.
void executeSkillFailNormal(Creature* pCreature, SkillType_t SkillType, Creature* pTargetCreature, BYTE Grade = 0);
void executeAbsorbSoulSkillFail(Creature* pCreature, SkillType_t SkillType, ObjectID_t TargetObjectID, bool bBroadcast, bool bSendTwice);
void executeSkillFailNormalWithGun(Creature* pCreature, SkillType_t SkillType, Creature* pTargetCreature, BYTE RemainBullet);
void executeSkillFailException(Creature* pCreature, SkillType_t SkillType, BYTE Grade = 0);

void decreaseHP(Zone* pZone, Creature* pCreature, int Damage, ObjectID_t attackerObjectID=0);

Dir_t getDirectionToPosition(int originX, int originY, int destX, int destY);

Exp_t computeSkillPointBonus(SkillDomainType_t Domain, SkillLevel_t DomainLevel, Item* pWeapon, Exp_t Point);


// 점과 점사이를 걸어서 갈 수 있는가? (크리쳐로 막힌 경우는 제외 )
bool isPassLine(Zone* pZone, ZoneCoord_t sX, ZoneCoord_t sY, ZoneCoord_t eX, ZoneCoord_t eY, bool blockByCreature = false);

// 두 점사이의 진선을 이루는 점들을 구한다.
void getLinePoint(ZoneCoord_t sX, ZoneCoord_t sY, ZoneCoord_t eX, ZoneCoord_t eY, list<TPOINT>& tpList);

ElementalType getElementalTypeFromString(const string& type);

Damage_t computeElementalCombatSkill(Ousters* pOusters, Creature* pTargetCreature, ModifyInfo& AttackerMI);

//////////////////////////////////////////////////////////////////////////////
// 공격할 수 있는가?
// 무적 상태나 non PK 를 위해서 공격할 수 있는지를 체크한다.
//////////////////////////////////////////////////////////////////////////////
bool canAttack(Creature* pAttacker, Creature* pDefender);

#endif

