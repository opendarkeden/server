//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGnomesWhisper.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GNOMES_WHISPER__
#define __EFFECT_GNOMES_WHISPER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGnomesWhisper
//////////////////////////////////////////////////////////////////////////////

class EffectGnomesWhisper : public Effect 
{
public:
	EffectGnomesWhisper(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GNOMES_WHISPER; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	bool canSeeHide() const { return true; }
	bool canSeeInvisibility() const { return m_Level >= 15; }
	bool canSeeSniping() const { return m_Level >= 25; }

	string toString() const throw();

public:
	void setLevel( uint level ) { m_Level = level; }
	uint getLevel() const { return m_Level; }

private:
	uint	m_Level;
};

#endif // __EFFECT_GNOMES_WHISPER__
