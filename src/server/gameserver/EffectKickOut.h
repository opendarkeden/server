#ifndef __EFFECT_KICK_OUT_H__
#define __EFFECT_KICK_OUT_H__

#include "Effect.h"

class EffectKickOut : public Effect
{
public:
	EffectClass getEffectClass() const  { return Effect::EFFECT_CLASS_TRANSPORT_CREATURE; }
	EffectKickOut( Zone* pZone, int minutes ) { setZone(pZone); setDeadline( minutes * 600 ); m_MinutesCount = minutes; setNextTime( 600 ); }

	void affect() ;
	void unaffect() ;

	string toString() const  { return "EffectKickOut"; }

private:
	int	m_MinutesCount;
};

#endif
