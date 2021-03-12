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
	EffectCanEnterGDRLair(Creature* pCreature) ;
	~EffectCanEnterGDRLair() ;

public:
	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

    EffectClass getEffectClass() const  { return EFFECT_CLASS_CAN_ENTER_GDR_LAIR; }

    virtual void create(const string & ownerID) ;
    virtual void save(const string & ownerID) ;
    virtual void destroy(const string & ownerID) ;

	string toString() const ;

private:
};

//////////////////////////////////////////////////////////////////////////////
// class EffectCanEnterGDRLairLoader
//////////////////////////////////////////////////////////////////////////////

class EffectCanEnterGDRLairLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const  { return Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR; }
	virtual string getEffectClassName() const  { return "EffectCanEnterGDRLair"; }

public:
	virtual void load(Creature* pCreature) ;
};

extern EffectCanEnterGDRLairLoader* g_pEffectCanEnterGDRLairLoader;

#endif // __EFFECT_CAN_ENTER_GDR_LAIR__
