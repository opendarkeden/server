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

void saveItemInCorpse(Item* pItem, Corpse* pCorpse) ;

bool addRelicEffect(Creature* pCreature, Item* pItem) ;
bool addHasRelicEffect(Zone* pZone, Corpse* pCorpse, Item* pItem) ;

bool addEffectRelicPosition( Item* pItem, ZoneID_t zoneID, TPOINT tp ) ;
bool deleteEffectRelicPosition( Item* pItem ) ;
bool deleteRelicEffect( Corpse* pCorpse, Item* pItem ) ;
bool deleteRelicEffect(Creature* pCreature, Item* pItem) ;

//////////////////////////////////////////////////////////////////////////////
// relicÀ» zone¿¡ ¶³¾î¶ß¸®´Â °æ¿ì
//////////////////////////////////////////////////////////////////////////////
bool dropRelicToZone(PlayerCreature* pPC, Item* pItem) ;
bool dropRelicToZone(Creature* pCreature, bool bSendPacket=true) ;

bool dissectionRelicItem( Corpse* pCorpse, Item* pItem, const TPOINT& pt ) ;

void sendBloodBibleEffect( Object* pObject, Effect::EffectClass EClass ) ;
void sendHolyLandWarpEffect( Creature* pCreature ) ;
void sendRelicWarpEffect(Corpse* pCorpse) ;


#endif
