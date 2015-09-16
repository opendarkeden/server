//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGrandMasterVampire.h
// Written by  : 
// Description : grand master 티 내는거. - -;	 by sigi. 2002.11.8
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GRAND_MASTER_VAMPIRE__
#define __EFFECT_GRAND_MASTER_VAMPIRE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGrandMasterVampire
//////////////////////////////////////////////////////////////////////////////

class EffectGrandMasterVampire : public Effect 
{
public:
	EffectGrandMasterVampire(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GRAND_MASTER_VAMPIRE; }
	EffectClass getSendEffectClass() const throw();

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

private:
};

#endif
