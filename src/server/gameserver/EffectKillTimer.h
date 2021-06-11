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
	EffectKillTimer(Creature* pCreature, bool kill = true) ;
	~EffectKillTimer() ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_TRANSPORT_CREATURE; }

	void unaffect() ;

	string toString() const ;

private:
	bool	m_bKill;
};


#endif // __EFFECT_KILL_TIMER__
