//////////////////////////////////////////////////////////////////////////////
// Filename    : ZoneUtil.h
// Written by  : excel96
// Description : 
// 존과 관련된 특정한 작업들을 수행하는 함수들을 존 안에 넣으니까,
// 존 파일이 너무 커지는 경향이 있어서, 존 파일 외부로 꺼낸 함수들이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ZONE_UTIL_H__
#define __ZONE_UTIL_H__

#include "Types.h"
#include "Exception.h"
#include "Creature.h"
#include "Effect.h"
#include "VSDateTime.h"
#include <list>

// forward declaration
class Zone;
class Mine;
class Effect;
class PlayerCreature;
class Item;
class Monster;
class Slayer;
class Corpse;

struct ZONE_COORD;
struct SUMMON_INFO;

// 종류별로 소환
struct SUMMON_INFO2;

//////////////////////////////////////////////////////////////////////////////
// 특정 크리쳐를 더할 수 있는 위치를 찾는다.
// 
// Zone*       pZone        : 존에 대한 포인터
// ZoneCoord_t cx           : 더하고자 하는 초기 위치 x
// ZoneCoord_t cy           : 더하고자 하는 초기 위치 y
// Creature::MoveMode MMode : 크리쳐의 움직임 모드
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePosition
(
	Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, Creature::MoveMode MMode
) throw();


//////////////////////////////////////////////////////////////////////////////
// 특정 아이템을 더할 수 있는 위치를 찾는다.
//
// Zone*       pZone          : 존에 대한 포인터
// ZoneCoord_t cx             : 더하고자 하는 초기 위치 x
// ZoneCoord_t cy             : 더하고자 하는 초기 위치 y
// bool        bAllowCreature : 크리쳐가 존재하는 곳도 괜찮은가?
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePositionForItem
(
	Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, bool bAllowCreature, bool bAllowSafeZone = true, bool bForce = false
) throw();

//////////////////////////////////////////////////////////////////////////////
// 특정 이펙트를 더할 수 있는 위치를 찾는다.
//
// Zone*       pZone          : 존에 대한 포인터
// ZoneCoord_t cx             : 더하고자 하는 초기 위치 x
// ZoneCoord_t cy             : 더하고자 하는 초기 위치 y
// Effect::EffectClass EClass : 더하고자 하는 이펙트 클래스
//////////////////////////////////////////////////////////////////////////////
TPOINT findSuitablePositionForEffect
(
	Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy, Effect::EffectClass EClass
) throw();

//////////////////////////////////////////////////////////////////////////////
// 특정 위치에서 지정된 무브 모드의 크리쳐를 추가할 수 있는지 검사한다.
//
// Zone*              pZone : 존에 대한 포인터
// ZoneCoord_t        x     : 버로우하고자 하는 좌표 x
// ZoneCoord_t        y     : 버로우하고자 하는 좌표 y
// Creature::MoveMode MMode : 크리쳐의 무브 모드
//////////////////////////////////////////////////////////////////////////////
bool canAddCreature
(
	Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Creature::MoveMode MMode
) throw();


//////////////////////////////////////////////////////////////////////////////
// 특정 위치에 버로우가 가능한지 체크를 한다. 
//
// Zone* pZone   : 존에 대한 포인터
// ZoneCoord_t x : 버로우하고자 하는 좌표 x
// ZoneCoord_t y : 버로우하고자 하는 좌표 y
//////////////////////////////////////////////////////////////////////////////
bool canBurrow
(
	Zone* pZone, ZoneCoord_t x, ZoneCoord_t y
) throw();


//////////////////////////////////////////////////////////////////////////////
// 특정 위치에 언버로우가 가능한지 체크를 한다.
//
// Zone* pZone   : 존에 대한 포인터
// ZoneCoord_t x : 버로우하고자 하는 좌표 x
// ZoneCoord_t y : 버로우하고자 하는 좌표 y
//////////////////////////////////////////////////////////////////////////////
bool canUnburrow
(
	Zone* pZone, ZoneCoord_t x, ZoneCoord_t y
) throw();


//////////////////////////////////////////////////////////////////////////////
// 크리쳐를 뒤로 물러나게 한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 물러나게 할 크리쳐
// ZoneCoord_t originX   : pCreature를 물러나게 한 상대방의 좌표 x
// ZoneCoord_t originY   : pCreature를 물러나게 한 상대방의 좌표 y
//////////////////////////////////////////////////////////////////////////////
Dir_t knockbackCreature
(
	Zone* pZone, Creature* pCreature, 
	ZoneCoord_t originX, ZoneCoord_t originY
) throw(ProtocolException, Error);


//////////////////////////////////////////////////////////////////////////////
// 하이드를 쓴 크리쳐를 존에다 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 하이드를 쓴 크리쳐
// ZoneCoord_t cx        : 크리쳐의 원래 좌표 x 
// ZoneCoord_t cy        : 크리쳐의 원래 좌표 y
//////////////////////////////////////////////////////////////////////////////
void addBurrowingCreature
(
	Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy
) throw(EmptyTileNotExistException, Error);


//////////////////////////////////////////////////////////////////////////////
// 하이드를 푼 크리쳐를 존에다 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 하이드를 푼 크리쳐
// ZoneCoord_t cx        : 크리쳐의 원래 좌표 x
// ZoneCoord_t cy        : 크리쳐의 원래 좌표 y
// Dir_t       dir       : 나온 크리쳐가 향할 방향
//////////////////////////////////////////////////////////////////////////////
void addUnburrowCreature
(
	Zone* pZone, Creature* pCreature, 
	ZoneCoord_t cx, ZoneCoord_t cy, Dir_t dir 
) throw(EmptyTileNotExistException, Error);


//////////////////////////////////////////////////////////////////////////////
// 변신을 푼 크리쳐를 존에다 추가한다.
//
// Zone*     pZone     : 존에 대한 포인터
// Creature* pCreature : 변신을 푼 크리쳐
// bool      bForce    : 이펙트의 duration이 만기가 되지 않았는데,
//                       강제로 푸는 것인가?
//////////////////////////////////////////////////////////////////////////////
void addUntransformCreature 
(
	Zone* pZone, Creature* pCreature, bool bForce
) throw();


//////////////////////////////////////////////////////////////////////////////
// 안 보이는 크리쳐를 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 안 보이는 크리쳐
// ZoneCoord_t cx        : 크리쳐의 원래 좌표 x
// ZoneCoord_t cy        : 크리쳐의 원래 좌표 y
//////////////////////////////////////////////////////////////////////////////
void addInvisibleCreature
(
	Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy
) throw();


//////////////////////////////////////////////////////////////////////////////
// 안 보이던 크리쳐가 보일 경우, 이 크리쳐를 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 안 보이던 크리쳐
// bool        bForce    : 강제로 visible 상태가 되었나?
//////////////////////////////////////////////////////////////////////////////
void addVisibleCreature
(
	Zone* pZone, Creature* pCreature, bool bForced
) throw();


//////////////////////////////////////////////////////////////////////////////
// 스나이핑 모드의 크리쳐를 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 안 보이는 크리쳐
// ZoneCoord_t cx        : 크리쳐의 원래 좌표 x
// ZoneCoord_t cy        : 크리쳐의 원래 좌표 y
//////////////////////////////////////////////////////////////////////////////
void addSnipingModeCreature(Zone* pZone, Creature* pCreature, ZoneCoord_t cx, ZoneCoord_t cy) throw();


//////////////////////////////////////////////////////////////////////////////
// 안 보이던 크리쳐가 보일 경우, 이 크리쳐를 추가한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 안 보이던 크리쳐
// bool        bForce    : 강제로 visible 상태가 되었나?
//////////////////////////////////////////////////////////////////////////////
void addUnSnipingModeCreature(Zone* pZone, Creature* pCreature, bool bForced) throw();


//////////////////////////////////////////////////////////////////////////////
// 존에다 지뢰를 더한다.
//
// Zone*       pZone : 존에 대한 포인터
// Mine*       pMine : 지뢰 객체에 대한 포인터
// ZoneCoord_t cx    : 지뢰를 더할 좌표 x
// ZoneCoord_t cy    : 지뢰를 더할 좌표 y
//////////////////////////////////////////////////////////////////////////////
void addInstalledMine(Zone* pZone, Mine* pMine, ZoneCoord_t cx, ZoneCoord_t cy) throw();


//////////////////////////////////////////////////////////////////////////////
// 특정 크리쳐가 지뢰를 밟지 않았는지 체크한다.
//
// Zone*       pZone     : 존에 대한 포인터
// Creature*   pCreature : 검사할 크리쳐
// ZoneCoord_t X         : 검사할 좌표 x
// ZoneCoord_t Y         : 검사할 좌표 y
//////////////////////////////////////////////////////////////////////////////
bool checkMine(Zone* pZone, Creature* pCreature, ZoneCoord_t X, ZoneCoord_t Y) throw();
bool checkMine(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y ) throw();

bool checkTrap(Zone* pZone, Creature* pCreature);

//////////////////////////////////////////////////////////////////////////////
// 특정 크리쳐를 다른 존으로 이동시킨다.
//
// Creature*   pCreature    : 이동할 크리쳐
// ZoneID_t    TargetZoneID : 이동할 존 ID
// ZoneCoord_t TargetX      : 이동할 존 좌표 X
// ZoneCoord_t TargetY      : 이동할 존 좌표 Y
// bool        bSendMoveOK  : GCMoveOK를 날려주는가에 대한 여부
//////////////////////////////////////////////////////////////////////////////
void transportCreature(
	Creature* pCreature, ZoneID_t TargetZoneID, ZoneCoord_t TX, ZoneCoord_t TY, bool bSendMoveOK = true
) throw();


//////////////////////////////////////////////////////////////////////////////
// 특정 존ID를 가진 존을 찾아서 포인터를 리턴한다.
// ZoneID_t ZID : 찾고자 하는 존 ID
//////////////////////////////////////////////////////////////////////////////
Zone* getZoneByZoneID(ZoneID_t ZID) throw(Error);

//////////////////////////////////////////////////////////////////////////////
// 운영자 명령어로서, 특정 타입의 몬스터를 존에다 추가한다.
//////////////////////////////////////////////////////////////////////////////
void addMonstersToZone(
	Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, SpriteType_t SType, MonsterType_t MType, int num, const SUMMON_INFO& summonInfo, list<Monster*>* pSummonedMonsters=NULL
) throw();

void addMonstersToZone(
	Zone* pZone, const SUMMON_INFO2& summonInfo, list<Monster*>* pSummonedMonsters=NULL
) throw();

//////////////////////////////////////////////////////////////////////////////
// 특정 크리쳐가 현재 안전 지대 내부에 있는가를 검사하는 함수
// 교환할 때 쓰인다. 
//////////////////////////////////////////////////////////////////////////////
bool isInSafeZone(Creature* pCreature);

//////////////////////////////////////////////////////////////////////////////
// 좌표가 존의 범위 안인지를 체크한다.
//////////////////////////////////////////////////////////////////////////////
bool isValidZoneCoord(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, int offset=0);

//////////////////////////////////////////////////////////////////////////////
// master lair 에  pCreature가 들어갈 수 있는가?
//////////////////////////////////////////////////////////////////////////////
bool enterMasterLair(Zone* pZone, Creature* pCreature) throw (Error);

// 야전사령부에서 초보자들을 다른 곳으로 보낼때.. 목표 존의 정보
void checkNewbieTransportToGuild(Slayer* pSlayer);
void getNewbieTransportZoneInfo(Slayer* pSlayer, ZONE_COORD& zoneInfo);

// Corpse를 Zone에 추가한다.
bool addCorpseToZone(Corpse* pCorpse, Zone* pZone, ZoneCoord_t cx, ZoneCoord_t cy) throw (Error);

// 범위 안에 특정한 몬스터 시체가 있는지 확인한다. 
// 있으면 true, 없으면 false
bool checkCorpse( Zone* pZone, MonsterType_t MType, ZoneCoord_t x1, ZoneCoord_t y1, ZoneCoord_t x2, ZoneCoord_t y2 ) throw();

void makeZoneIDList(const string& zoneIDs, list<ZoneID_t>& zoneIDList ) throw(Error);

uint getZoneTimeband( Zone* pZone );

bool createBulletinBoard( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y, MonsterType_t type, const string& msg, const VSDateTime& timeLimit );
void loadBulletinBoard( Zone* pZone );

void forbidDarkness( Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y, int range );

#endif
