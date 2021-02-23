//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMute.h
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MUTE__
#define __EFFECT_MUTE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMute
//////////////////////////////////////////////////////////////////////////////

class EffectMute : public Effect 
{
public:
	EffectMute(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MUTE; }

	void affect() throw(Error) { }
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject) throw(Error);

	virtual void create(const string & ownerID) throw(Error);
	virtual void destroy(const string & ownerID) throw(Error);
	virtual void save(const string & ownerID) throw(Error);

	string toString() const throw();

};

//////////////////////////////////////////////////////////////////////////////
// class EffectMuteLoader
//////////////////////////////////////////////////////////////////////////////

class EffectMuteLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_MUTE; }
	virtual string getEffectClassName() const throw() { return "EffectMute"; }

public:
	virtual void load(Creature* pCreature) throw(Error);

};

extern EffectMuteLoader* g_pEffectMuteLoader;

#endif // __EFFECT_MUTE__
