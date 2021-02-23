//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCanEnterGDRLair.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CAN_ENTER_GDR_LAIR__
#define __EFFECT_CAN_ENTER_GDR_LAIR__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectEffectCanEnterGDRLair
//////////////////////////////////////////////////////////////////////////////

class EffectCanEnterGDRLair : public Effect 
{
public:
	EffectCanEnterGDRLair(Creature* pCreature) throw(Error);
	~EffectCanEnterGDRLair() throw(Error);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CAN_ENTER_GDR_LAIR; }

    virtual void create(const string & ownerID) throw(Error);
    virtual void save(const string & ownerID) throw(Error);
    virtual void destroy(const string & ownerID) throw(Error);

	string toString() const throw();

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EffectCanEnterGDRLairLoader
//////////////////////////////////////////////////////////////////////////////

class EffectCanEnterGDRLairLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR; }
	virtual string getEffectClassName() const throw() { return "EffectCanEnterGDRLair"; }

public:
	virtual void load(Creature* pCreature) throw(Error);
};

extern EffectCanEnterGDRLairLoader* g_pEffectCanEnterGDRLairLoader;

#endif // __EFFECT_CAN_ENTER_GDR_LAIR__
