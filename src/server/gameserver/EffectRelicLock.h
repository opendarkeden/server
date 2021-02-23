//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelicLock.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RELIC_LOCK__
#define __EFFECT_RELIC_LOCK__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRelicLock
//////////////////////////////////////////////////////////////////////////////
// 성물 보관대에 붙는 이펙트이다.

class EffectRelicLock : public Effect 
{
public:
	EffectRelicLock(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_RELIC_LOCK; }

	void affect() throw(Error) {}
	void affect(Item* pItem) throw(Error);

	void unaffect(Item* pItem) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	//bool   isLockTime() const;
	//void   setLockTime(const Timeval& tv) throw() { m_LockTime = tv; }

private:
	//Timeval m_LockTime;
	
};

#endif // __EFFECT_DOOM__
