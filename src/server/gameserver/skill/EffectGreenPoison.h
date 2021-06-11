//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGreenPoison.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GREEN_POISON__
#define __EFFECT_GREEN_POISON__

#include "Effect.h"
#include "EffectLoader.h"
#include "Tile.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGreenPoison
//////////////////////////////////////////////////////////////////////////////

class EffectGreenPoison : public Effect 
{
public:
	EffectGreenPoison(Zone*, ZoneCoord_t, ZoneCoord_t) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GREEN_POISON; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) ;

	void unaffect() ;
	void unaffect(Creature* pCreature)  {};
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject ) ;
	void unaffect(Item* pItem)  {}

	string toString() const throw();

public:
	void setLevel(Attr_t l)  { m_Level = l;}
	void setDamage(Damage_t d)  { m_Damage = d;}
	void setDuration(Duration_t d)  { m_Duration = d;}
	Duration_t getDuration() const  { return m_Duration;}

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID() const throw() { return m_UserObjectID; }

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() const { return m_bVampire; }

	bool affectCreature(Creature* pCreature, bool bAffectByMove) ;

private:
	int        m_Level;    // 마법의 MagicLevel
	Damage_t   m_Damage;   // 마법의 데미지
	Duration_t m_Duration; // 마법의 지속 시간
	ObjectID_t m_UserObjectID;
	bool       m_bVampire;
};

class EffectGreenPoisonLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_GREEN_POISON; }
	virtual string getEffectClassName() const throw() { return "EffectGreenPoison"; }

public:
	virtual void load(Creature* pCreature)  {}
	virtual void load(Zone* pZone) ;
};

extern EffectGreenPoisonLoader* g_pEffectGreenPoisonLoader;

#endif // __EFFECT_GREEN_POISON__
