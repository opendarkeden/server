
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRequital.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REQUITAL__
#define __EFFECT_REQUITAL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRequital
//////////////////////////////////////////////////////////////////////////////

class EffectRequital : public Effect 
{
public:
	EffectRequital(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_REQUITAL; }

	void affect() throw(Error){}

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	void setReflection( int ref ) { m_Reflection = ref; }
	int getReflection() const { return m_Reflection; }

private:
	int m_Reflection;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectRequitalLoader
//////////////////////////////////////////////////////////////////////////////

class EffectRequitalLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_REQUITAL; }
	virtual string getEffectClassName() const throw() { return "EffectRequital"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_REQUITAL__
