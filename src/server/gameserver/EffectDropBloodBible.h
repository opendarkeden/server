
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDropBloodBible.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DROP_BLOOD_BIBLE__
#define __EFFECT_DROP_BLOOD_BIBLE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDropBloodBible
//////////////////////////////////////////////////////////////////////////////

class EffectDropBloodBible : public Effect 
{
public:
	EffectDropBloodBible(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DROP_BLOOD_BIBLE; }
	EffectClass getSendEffectClass() throw() { return (EffectClass)((int)EFFECT_CLASS_BLOOD_BIBLE_ARMEGA + m_ItemType); }

	ItemType_t	getPart() const { return m_ItemType; }
	void		setPart( ItemType_t part ) { m_ItemType = part; }

	void affect() throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

private:
	ItemType_t	m_ItemType;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectDropBloodBibleLoader
//////////////////////////////////////////////////////////////////////////////

class EffectDropBloodBibleLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_DROP_BLOOD_BIBLE; }
	virtual string getEffectClassName() const throw() { return "EffectDropBloodBible"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectDropBloodBibleLoader* g_pEffectDropBloodBibleLoader;

#endif // __EFFECT_DROP_BLOOD_BIBLE__
