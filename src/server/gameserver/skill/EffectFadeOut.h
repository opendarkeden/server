//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFadeOut.h
// Written by  : elca@ewestsoft.com
// Description : 
// 군인기술 Sniping 또는 뱀파이어 기술 Invisibility로 인해서
// 현재 점점 희미해져가고 있는(사라지고 있는) 크리쳐에 붙는 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FADE_OUT__
#define __EFFECT_FADE_OUT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFadeOut
//////////////////////////////////////////////////////////////////////////////

class EffectFadeOut : public Effect 
{
public:
	EffectFadeOut(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_FADE_OUT; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Item* pItem) {}
	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	string toString() const throw();

public:
	Duration_t getDuration() const  { return m_Duration;}
	void setDuration(Duration_t d)  { m_Duration = d;}

	bool isSniping(void) const { return m_isSniping; }
	void setSniping() throw() { m_isSniping = true; }
	
	bool isInvisibility(void) const { return !m_isSniping; }
	void setInvisibility() throw() { m_isSniping = false; }

private:
	Duration_t  m_Duration;
	bool        m_isSniping;

};

#endif // __EFFECT_FADE_OUT__
