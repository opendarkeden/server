//////////////////////////////////////////////////////////////////////////////
// Filename	: EffectDonation200501.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DONATION_200501__
#define __EFFECT_DONATION_200501__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDonation200501
//////////////////////////////////////////////////////////////////////////////

class EffectDonation200501 : public Effect 
{
public:
	EffectDonation200501(Creature* pCreature) throw(Error);

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DONATION_200501; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

private:
};

#endif
