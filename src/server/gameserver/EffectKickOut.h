#ifndef __EFFECT_KICK_OUT_H__
#define __EFFECT_KICK_OUT_H__

#include "Effect.h"

class EffectKickOut : public Effect
{
public:
	EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_TRANSPORT_CREATURE; }
	EffectKickOut( Zone* pZone, int minutes ) { setZone(pZone); setDeadline( minutes * 600 ); m_MinutesCount = minutes; setNextTime( 600 ); }

	void affect() throw(Error);
	void unaffect() throw(Error);

	string toString() const throw() { return "EffectKickOut"; }

private:
	int	m_MinutesCount;
};

#endif
