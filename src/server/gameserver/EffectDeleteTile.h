//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDeleteTile.h
// Description : 제단의 입구의 바닥을 지우는 이펙트
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DELETE_TILE__
#define __EFFECT_DELETE_TILE__

#include "Effect.h"
#include "EffectLoader.h"
#include "HitRoll.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDeleteTile
//////////////////////////////////////////////////////////////////////////////

class EffectDeleteTile : public Effect 
{
public:
	EffectDeleteTile(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DELETE_TILE; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class EffectDeleteTileLoader
//////////////////////////////////////////////////////////////////////////////

class EffectDeleteTileLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_DELETE_TILE; }
	virtual string getEffectClassName() const throw() { return "EffectDeleteTile"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectDeleteTileLoader* g_pEffectDeleteTileLoader;

#endif // __EFFECT_DELETE_TILE__

