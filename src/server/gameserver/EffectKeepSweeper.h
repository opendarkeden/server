//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectKeepSweeper.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_KEEP_SWEEPER__
#define __EFFECT_KEEP_SWEEPER__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectKeepSweeper
//////////////////////////////////////////////////////////////////////////////

class EffectKeepSweeper : public Effect
{
public:
	EffectKeepSweeper(Item* pItem) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_KEEP_SWEEPER; }
	EffectClass getSendEffectClass() const  { return (EffectClass)(EFFECT_CLASS_KEEP_SWEEPER + m_Part); }

	void unaffect() ;

	string toString() const ;

public:
	void   	setPart(int part)  { m_Part = part; }

private:
	ItemType_t	m_Part;	
};

#endif 
