#ifndef __RELIC_UTIL_H__
#define __RELIC_UTIL_H__

#include "Effect.h"
#include "Exception.h"
#include "Item.h"

class Object;
class Corpse;
class Creature;
class Zone;
class PlayerCreature;

bool isRelicItem(const Item* pItem);
bool isRelicItem(Item::ItemClass IClass);

void saveItemInCorpse(Item* pItem, Corpse* pCorpse);

bool addRelicEffect(Creature* pCreature, Item* pItem);
bool addHasRelicEffect(Zone* pZone, Corpse* pCorpse, Item* pItem);

bool addEffectRelicPosition(Item* pItem, ZoneID_t zoneID, TPOINT tp);
bool deleteEffectRelicPosition(Item* pItem);
bool deleteRelicEffect(Corpse* pCorpse, Item* pItem);
bool deleteRelicEffect(Creature* pCreature, Item* pItem);

//////////////////////////////////////////////////////////////////////////////
// relic을 zone에 떨어뜨리는 경우
//////////////////////////////////////////////////////////////////////////////
bool dropRelicToZone(PlayerCreature* pPC, Item* pItem);
bool dropRelicToZone(Creature* pCreature, bool bSendPacket = true);

bool dissectionRelicItem(Corpse* pCorpse, Item* pItem, const TPOINT& pt);

void sendBloodBibleEffect(Object* pObject, Effect::EffectClass EClass);
void sendHolyLandWarpEffect(Creature* pCreature);
void sendRelicWarpEffect(Corpse* pCorpse);


#endif
