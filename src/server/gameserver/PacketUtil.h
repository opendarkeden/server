//////////////////////////////////////////////////////////////////////////////
// Filename    : PacketUtil.h
// Written by  : excel96
// Description : 
// 자주 보내고, 만들기가 복잡한 패킷은 만드는 곳을 여기 하나로 통일함으로써,
// 유지보수가 쉬워진다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __PACKETUTIL_H__
#define __PACKETUTIL_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////////////////////////////////

class Creature;
class Slayer;
class Vampire;
class Ousters;
class Monster;
class NPC;
class Item;
class SlayerCorpse;
class VampireCorpse;
class OustersCorpse;
class MonsterCorpse;
class SLAYER_RECORD;
class VAMPIRE_RECORD;
class OUSTERS_RECORD;
class GamePlayer;
class PlayerCreature;

class GCUpdateInfo;
class GCAddSlayer;
class GCAddVampire;
class GCAddOusters;
class GCAddMonster;
class GCAddNPC;
class GCAddNewItemToZone;
class GCDropItemToZone;
class GCAddSlayerCorpse;
class GCAddVampireCorpse;
class GCAddMonsterCorpse;
class GCAddOustersCorpse;
class GCOtherModifyInfo;
class GCCreateItem;
class GCWarScheduleList;
class GCMiniGameScores;
class GCPetStashList;
class GCModifyInformation;

//class GCItemNameInfoList;

//////////////////////////////////////////////////////////////////////////////
// function headers
//////////////////////////////////////////////////////////////////////////////

// MOdifyInformation 에 길드연합정보를 만들어 넣는다.
void makeGCModifyInfoGuildUnion(GCModifyInformation* pModifyInformation, Creature* pCreature) throw();
void makeGCOtherModifyInfoGuildUnion(GCOtherModifyInfo* pModifyInformation, Creature* pCreature) throw();
void sendGCOtherModifyInfoGuildUnion(Creature* pTargetCreature) throw();
void sendGCOtherModifyInfoGuildUnionByGuildID(uint gID) throw();
	
	
// 포탈이나, 죽어서 맵 사이를 이동할 때 쓰는, GCUpdateInfo 정보를 구성한다.
void makeGCUpdateInfo(GCUpdateInfo* pUpdateInfo, Creature* pCreature) throw();

// 슬레이어 추가 패킷을 구성한다.
void makeGCAddSlayer(GCAddSlayer* pAddSlayer, Slayer* pSlayer) throw();

// 뱀파이어 추가 패킷을 구성한다.
void makeGCAddVampire(GCAddVampire* pAddVampire, Vampire* pVampire) throw();

// 아우스터스 추가 패킷을 구성한다.
void makeGCAddOusters(GCAddOusters* pAddOusters, Ousters* pOusters) throw();

// 몬스터 추가 패킷을 구성한다.
void makeGCAddMonster(GCAddMonster* pAddMonster, Monster* pMonster) throw();

// NPc 추가 패킷을 구성한다.
void makeGCAddNPC(GCAddNPC* pAddNPC, NPC* pNPC) throw();

// 새로운 아이템을 존에다 추가할 때 보내는 GCAddNewItemToZone을 구성한다.
void makeGCAddNewItemToZone(GCAddNewItemToZone* pAddItem, Item* pItem, int X, int Y) throw();

// 새로운 아이템을 존에다 추가할 때 보내는 GCAddNewItemToZone을 구성한다.
void makeGCDropItemToZone(GCDropItemToZone* pAddItem, Item* pItem, int X, int Y) throw();

// 존에다 슬레이어 시체를 추가할 때 보내는 패킷을 구성한다.
void makeGCAddSlayerCorpse(GCAddSlayerCorpse* pAddSlayerCorpse, SlayerCorpse* pSlayerCorpse) throw();

// 존에다 뱀파이어 시체를 추가할 때 보내는 패킷을 구성한다.
void makeGCAddVampireCorpse(GCAddVampireCorpse* pAddVampireCorpse, VampireCorpse* pVampireCorpse) throw();

// 존에다 몬스터 시체를 추가할 때 보내는 패킷을 구성한다.
void makeGCAddMonsterCorpse(GCAddMonsterCorpse* pAddMonsterCorpse, MonsterCorpse* pMonsterCorpse, int X, int Y) throw();

// 존에다 아우스터즈 시체를 추가할 때 보내는 패킷을 구성한다.
void makeGCAddOustersCorpse(GCAddOustersCorpse* pAddOustersCorpse, OustersCorpse* pOustersCorpse) throw();

// 다른 사람의 최대 체력 같은 것이 변경되었을 경우에 날아가는 GCOtherModifyInfo를 구성한다.
void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Slayer* pSlayer, const SLAYER_RECORD* prev);
void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Vampire* pVampire, const VAMPIRE_RECORD* prev);
void makeGCOtherModifyInfo(GCOtherModifyInfo* pInfo, Ousters* pOusters, const OUSTERS_RECORD* prev);

// 요금 지불 관련 정보를 보여준다.
void sendPayInfo(GamePlayer* pGamePlayer) throw(Error);

// 아이템 생성
void makeGCCreateItem(GCCreateItem* pGCCreateItem, Item* pItem, CoordInven_t x, CoordInven_t y) throw(Error);

// 레벨 업 이펙트를 보여준다.
void sendEffectLevelUp(Creature* pCreature) throw(Error);

// GamePlayer에게 GCSystemMessage(msg)를 보낸다. incoming에 있는 경우는 zone에 가면 뿌려준다.
void sendSystemMessage(GamePlayer* pGamePlayer, const string& msg) throw(Error);

bool makeGCWarScheduleList(GCWarScheduleList* pGCWarScheduleList, ZoneID_t zoneID) throw(Error);

// 이름이 붙는 아이템 정보를 보내주는 패킷
//void makeGCItemNameInfoList(GCItemNameInfoList* pInfo, PlayerCreature* pPC) throw(Error);

void sendGCMiniGameScores(PlayerCreature* pPC, BYTE gameType, BYTE Level);

void makeGCPetStashList(GCPetStashList* pPacket, PlayerCreature* pPC);

#endif
