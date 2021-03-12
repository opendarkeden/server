//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasSweeper.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HAS_SWEEPER__
#define __EFFECT_HAS_SWEEPER__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasSweeper
//////////////////////////////////////////////////////////////////////////////

class EffectHasSweeper : public Effect
{
public:
	EffectHasSweeper(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_HAS_SWEEPER; }
	EffectClass getSendEffectClass() const  { return (EffectClass)(EFFECT_CLASS_HAS_SWEEPER + m_Part); }

	void unaffect() ;

	string toString() const ;

public:
	void   	setPart(int part)  { m_Part = part; }

private:
	ItemType_t	m_Part;	
};

#endif 
