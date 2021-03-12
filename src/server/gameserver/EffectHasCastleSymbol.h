//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHasCastleSymbol.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HAS_CASTLE_SYMBOL__
#define __EFFECT_HAS_CASTLE_SYMBOL__

#include "EffectHasRelic.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHasCastleSymbol
//////////////////////////////////////////////////////////////////////////////

class EffectHasCastleSymbol : public EffectHasRelic 
{
public:
	EffectHasCastleSymbol(Creature* pCreature) ;
	EffectHasCastleSymbol(Item* pItem) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_HAS_CASTLE_SYMBOL; }
	EffectClass getSendEffectClass() const  { return EffectClasses[m_Part]; }

	void affect(Creature* pCreature) ;
	void affect(Item* pItem) ;

	string toString() const ;

public:
	void   	setPart(int part) ;

private:
	string		m_PartName;	// 성의 상징 이름
	static const EffectClass EffectClasses[6];
};

#endif 
