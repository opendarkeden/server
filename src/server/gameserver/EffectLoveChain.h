//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLoveChain.h
// Written by  : elca@ewestsoft.com
// Description : 
// 군인기술 Sniping 또는 뱀파이어 기술 Invisibility로 인해서
// 현재 점점 희미해져가고 있는(사라지고 있는) 크리쳐에 붙는 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LOVE_CHAIN__
#define __EFFECT_LOVE_CHAIN__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectLoveChain
//////////////////////////////////////////////////////////////////////////////

class EffectLoveChain : public Effect 
{
public:
	EffectLoveChain(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_LOVE_CHAIN; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:

	// get/set Target Name
	const string& getTargetName() const throw(Error) { return m_TargetName; }
	void setTargetName( const string& targetName ) throw(Error) { m_TargetName = targetName; }

	Zone* getZone() const throw() { return m_pZone; }
	void setZone( Zone* pZone ) throw() { m_pZone = pZone; }

	ObjectID_t getItemObjectID() const throw() { return m_ItemObjectID; }
	void setItemObjectID( ObjectID_t itemObjectID ) throw() { m_ItemObjectID = itemObjectID; }
	
private:

	ObjectID_t	m_OwnerOID;			// 이펙트 걸린 놈의 OwnerID
	Zone*		m_pZone;			// Zone 포인터
	string		m_TargetName;		// Target Name
	ObjectID_t	m_ItemObjectID;		// 아이템의 오브젝트 아이디
};

#endif
