////////////////////////////////////////////////////////////////////////////////
// Filename : CreatureUtil.h
// Written by : 김성민
// Description : 
// Slayer와 Vampire 파일의 크기를 될 수 있는 한 줄이기 위해서 둘의 공통되는
// 부분을 가능한 한 빼놓은 파일이다.
// 나중에 PlayerCreature 클래스가 나오면, 이 파일의 내용을 그 안에다가 
// 포함시키는 것이 좋을 것이다.
////////////////////////////////////////////////////////////////////////////////

#ifndef __CREATURE_UTIL_H__
#define __CREATURE_UTIL_H__

#include "Creature.h"
#include "Item.h"

class EffectObservingEye;
class EffectGnomesWhisper;
class Ousters;
class PlayerCreature;
class GamePlayer;

////////////////////////////////////////////////////////////////////////////////
// 같은 크리쳐 클래스인가? 
////////////////////////////////////////////////////////////////////////////////
bool isSameRace(Creature* pCreature1, Creature* pCreature2) throw();

////////////////////////////////////////////////////////////////////////////////
// ObjectID로 아이템 찾기
////////////////////////////////////////////////////////////////////////////////
Item* findItemOID(Creature* pCreature, ObjectID_t objectID) throw();
Item* findItemOID(Creature* pCreature, ObjectID_t objectID, Item::ItemClass IClass) throw();
Item* findItemOID(Creature* pCreature, ObjectID_t objectID, int& storage, int& x, int& y) throw();
Item* findItemOID(Creature* pCreature, ObjectID_t objectID, Item::ItemClass IClass, int& storage, int& x, int& y) throw();

////////////////////////////////////////////////////////////////////////////////
// ItemID로 아이템 찾기
////////////////////////////////////////////////////////////////////////////////
Item* findItemIID(Creature* pCreature, ItemID_t itemID) throw();
Item* findItemIID(Creature* pCreature, ItemID_t itemID, Item::ItemClass IClass) throw();
Item* findItemIID(Creature* pCreature, ItemID_t itemID, int& storage, int& x, int& y) throw();
Item* findItemIID(Creature* pCreature, ItemID_t itemID, Item::ItemClass IClass, int& storage, int& x, int& y) throw();

////////////////////////////////////////////////////////////////////////////////
// 경험치 계산하기
// 뱀파이어가 어떤 크리쳐를 흡혈하거나, 죽였을 경우에 올라가는 경험치를
// 계산하는 함수
////////////////////////////////////////////////////////////////////////////////

const int BLOODDRAIN_EXP = 70; // 흡혈했을 경우는 70%
const int KILL_EXP       = 30; // 죽였을 경우는 30%

int computeCreatureExp(Creature* pCreature, int percent, Ousters* pOusters = NULL) throw();
int computeBloodDrainHealPoint(Creature* pCreature, int percent) throw();

////////////////////////////////////////////////////////////////////////////////
// 이벤트용 몹인지 검사하기...
////////////////////////////////////////////////////////////////////////////////
bool isEventMonster(Creature* pCreature) throw();

////////////////////////////////////////////////////////////////////////////////
// 임의의 크리쳐가 현재 움직일 수 있는 상태인가를 검사하는 함수
////////////////////////////////////////////////////////////////////////////////
bool isAbleToMove(Creature* pCreature);

////////////////////////////////////////////////////////////////////////////////
// 임의의 크리쳐가 현재 기술을 사용할 수 있는 상태인가를 검사하는 함수
////////////////////////////////////////////////////////////////////////////////
bool isAbleToUseSelfSkill(Creature* pCreature, SkillType_t SkillType=0);
bool isAbleToUseObjectSkill(Creature* pCreature, SkillType_t SkillType=0);
bool isAbleToUseTileSkill(Creature* pCreature, SkillType_t SkillType=0);
bool isAbleToUseInventorySkill(Creature* pCreature, BYTE X, BYTE Y, BYTE TX, BYTE TY, SkillType_t SkillType=0);

////////////////////////////////////////////////////////////////////////////////
// 임의의 크리쳐가 아이템을 주을 수 있는 상태인가를 검사하는 함수
////////////////////////////////////////////////////////////////////////////////
bool isAbleToPickupItem(Creature* pCreature, Item* pItem);
bool canDropToZone( Creature* pCreature, Item* pItem );

//void confirmGrandMaster(Creature* pCreature);

bool getRaceFromDB(const string& name, Race_t& race) throw (Error);
bool getGuildIDFromDB(const string& name, Race_t race, GuildID_t& guildID) throw (Error);

bool canSee( const Creature* pSource, Creature* pTarget, EffectObservingEye* pEffectObservingEye = NULL, EffectGnomesWhisper* pEffectGnomesWhisper = NULL );

int changeSexEx( PlayerCreature* pPC );
void initAllStatAndSendChange( PlayerCreature* pPC );

void addSimpleCreatureEffect( Creature* pCreature, Effect::EffectClass eClass, int time = -1, bool isSend = true );
void deleteCreatureEffect( Creature* pCreature, Effect::EffectClass eClass);
bool dropFlagToZone( Creature* pPC, bool bSendPacket = true );

void disableFlags( Creature *pCreature, Zone* pZone, SkillType_t SkillType);
bool canEnterBeginnerZone( Creature* pCreature );

#ifdef __UNDERWORLD__
void giveUnderworldGift( Creature* pCreature );
#endif

void disableFlags( Creature *pCreature, Zone* pZone, SkillType_t SkillType);
bool dropSweeperToZone( Creature* pPC, bool bSendPacket = true );

Level_t getPCLevel( PlayerCreature* pPC );
void sendPetInfo( GamePlayer* pGamePlayer, bool bBroadcast = false, bool bSummon = false );
void giveGoldMedal( PlayerCreature* pPC ) throw(Error);
void giveLotto( PlayerCreature* pPC, BYTE type, uint num ) throw(Error);

void addOlympicStat( PlayerCreature* pPC, BYTE type, uint num = 1 ) throw(Error);

void deletePC( PlayerCreature* pPC ) throw(Error);

bool isAffectExp2X();

#endif
