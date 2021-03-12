//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelicTable.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RELIC_TABLE__
#define __EFFECT_RELIC_TABLE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRelicTable
//////////////////////////////////////////////////////////////////////////////
class EffectRelicTable : public Effect 
{
public:
	EffectRelicTable(Item* pItem) ;

public:
	void affect() ;
	void affect(Item* pItem) ;

	void unaffect(Item* pItem) ;
	void unaffect() ; 

	string toString() const ;

public:
	void   setSafeTime(const Timeval& tv)  { m_SafeTime = tv; }
	bool   isSafeTime() const;

	void   setLockTime(const Timeval& tv)  { m_LockTime = tv; }
	bool   isLockTime() const;

private:
	Timeval		m_SafeTime;
	Timeval		m_LockTime;
};

class EffectSlayerRelicTable : public EffectRelicTable
{
public:
	EffectSlayerRelicTable(Item* pItem)  : EffectRelicTable(pItem) {}

    EffectClass getEffectClass() const  { return EFFECT_CLASS_SLAYER_RELIC_TABLE; }
};

class EffectVampireRelicTable : public EffectRelicTable
{
public:
	EffectVampireRelicTable(Item* pItem)  : EffectRelicTable(pItem) {}

    EffectClass getEffectClass() const  { return EFFECT_CLASS_VAMPIRE_RELIC_TABLE; }
};



#endif // __EFFECT_DOOM__
