#ifndef __RELIC_UTIL_H__
#define __RELIC_UTIL_H__

#include "Exception.h"
#include "Effect.h"
#include "Item.h"

class Object;
class Corpse;
class Creature;
class Zone;
class PlayerCreature;

bool isRelicItem(const Item* pItem);
bool isRelicItem(Item::ItemClass IClass);

void saveItemInCorpse(Item* pItem, Corpse* pCorpse) throw (Error);

bool addRelicEffect(Creature* pCreature, Item* pItem) throw (Error);
bool addHasRelicEffect(Zone* pZone, Corpse* pCorpse, Item* pItem) throw (Error);

bool addEffectRelicPosition( Item* pItem, ZoneID_t zoneID, TPOINT tp ) throw(Error);
bool deleteEffectRelicPosition( Item* pItem ) throw (Error);
bool deleteRelicEffect( Corpse* pCorpse, Item* pItem ) throw (Error);
bool deleteRelicEffect(Creature* pCreature, Item* pItem) throw (Error);

//////////////////////////////////////////////////////////////////////////////
// relicÀ» zone¿¡ ¶³¾î¶ß¸®´Â °æ¿ì
//////////////////////////////////////////////////////////////////////////////
bool dropRelicToZone(PlayerCreature* pPC, Item* pItem) throw (Error);
bool dropRelicToZone(Creature* pCreature, bool bSendPacket=true) throw (Error);

bool dissectionRelicItem( Corpse* pCorpse, Item* pItem, const TPOINT& pt ) throw (Error);

void sendBloodBibleEffect( Object* pObject, Effect::EffectClass EClass ) throw (Error);
void sendHolyLandWarpEffect( Creature* pCreature ) throw (Error);
void sendRelicWarpEffect(Corpse* pCorpse) throw (Error);


#endif
