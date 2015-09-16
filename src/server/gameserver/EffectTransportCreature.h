//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransportCreature.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////
// 이거 검증된 Effect가 아니다.

#ifndef __EFFECT_TRANSPORT_CREATURE_H__
#define __EFFECT_TRANSPORT_CREATURE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTransportCreature;
//////////////////////////////////////////////////////////////////////////////

class Corpse;

class EffectTransportCreature : public Effect 
{
public:
	EffectTransportCreature(Creature* pCreature, ZoneID_t ZoneID, ZoneCoord_t x, ZoneCoord_t y, Turn_t delay) throw(Error);
	virtual ~EffectTransportCreature() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSPORT_CREATURE; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error);
	virtual void affect(Creature* pCreature) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}

	virtual string toString() const throw();

public:
	void setZoneName(const string& zoneName) throw() { m_ZoneName = zoneName; }

	void setMessageTick(Turn_t tick) throw() { m_MessageTick = tick; }
	Turn_t getMessageTick() const throw() { return m_MessageTick; }
	
private:
	ZoneID_t 	m_ZoneID;
	ObjectID_t 	m_CreatureID;
	string		m_ZoneName;
	Turn_t  	m_MessageTick;

};

#endif
