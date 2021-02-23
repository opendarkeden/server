//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectEternity.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ETERNITY__
#define __EFFECT_ETERNITY__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectEternity
//////////////////////////////////////////////////////////////////////////////

class EffectEternity : public Effect 
{
public:
	EffectEternity(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ETERNITY; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

	void setHPPenalty( int pen ) { m_HPPenalty = pen; }
	int getHPPenalty() const { return m_HPPenalty; }

public:
	int m_HPPenalty;
	ObjectID_t m_TargetObjectID;
};

#endif // __EFFECT_ETERNITY__
