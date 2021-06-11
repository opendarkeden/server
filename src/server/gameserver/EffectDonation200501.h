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
	EffectDonation200501(Creature* pCreature) ;

public:
	EffectClass getEffectClass() const  { return EFFECT_CLASS_DONATION_200501; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const ;

private:
};

#endif
