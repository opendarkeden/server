//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSoulChain.h
// Written by  : elca@ewestsoft.com
// Description : 
// 군인기술 Sniping 또는 뱀파이어 기술 Invisibility로 인해서
// 현재 점점 희미해져가고 있는(사라지고 있는) 크리쳐에 붙는 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SOUL_CHAIN__
#define __EFFECT_SOUL_CHAIN__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSoulChain
//////////////////////////////////////////////////////////////////////////////

class EffectSoulChain : public Effect 
{
public:
	EffectSoulChain(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SOUL_CHAIN; }

	void affect() {}
	void affect(Creature* pCreature) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

	string toString() const throw();

public:

	Duration_t getDuration() const  { return m_Duration;}
	void setDuration(Duration_t d)  { m_Duration = d;}

	// get/set Target Name
	const string& getTargetName() const  { return m_TargetName; }
	void setTargetName( const string& targetName )  { m_TargetName = targetName; }

	Zone* getZone() const throw() { return m_pZone; }
	void setZone( Zone* pZone ) throw() { m_pZone = pZone; }
	
private:

	ObjectID_t	m_OwnerOID;			// 이펙트 걸린 놈의 OwnerID

	Zone*		m_pZone;			// Zone 포인터

	Duration_t  m_Duration;

	string		m_TargetName;		// Target Name

};

#endif
