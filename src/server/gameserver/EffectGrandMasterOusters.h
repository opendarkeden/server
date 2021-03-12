//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGrandMasterOusters.h
// Written by  : 
// Description : grand master 티 내는거. - -;	 by sigi. 2002.11.8
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GRAND_MASTER_OUSTERS__
#define __EFFECT_GRAND_MASTER_OUSTERS__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGrandMasterOusters
//////////////////////////////////////////////////////////////////////////////

class EffectGrandMasterOusters : public Effect 
{
public:
	EffectGrandMasterOusters(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_GRAND_MASTER_OUSTERS; }
	EffectClass getSendEffectClass() const ;

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const ;

private:
};

#endif
