//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectKillTimer.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_KILL_TIMER__
#define __EFFECT_KILL_TIMER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectKillTimer
//////////////////////////////////////////////////////////////////////////////

class EffectKillTimer : public Effect 
{
public:
	EffectKillTimer(Creature* pCreature, bool kill = true) throw(Error);
	~EffectKillTimer() throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_CREATURE; }

	void unaffect() throw(Error);

	string toString() const throw();

private:
	bool	m_bKill;
};


#endif // __EFFECT_KILL_TIMER__
