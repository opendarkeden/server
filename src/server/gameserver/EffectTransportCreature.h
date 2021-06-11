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
	EffectTransportCreature(Creature* pCreature, ZoneID_t ZoneID, ZoneCoord_t x, ZoneCoord_t y, Turn_t delay) ;
	virtual ~EffectTransportCreature() ;

public:
	virtual EffectClass getEffectClass() const  { return EFFECT_CLASS_TRANSPORT_CREATURE; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const  { return OBJECT_PRIORITY_NONE; }

	virtual void affect() ;
	virtual void affect(Creature* pCreature) ;
	
	virtual void unaffect() ;
	virtual void unaffect(Creature* pCreature) ;

	void create(const string & ownerID)  {}
	void save(const string & ownerID)  {}
	void destroy(const string & ownerID)  {}

	virtual string toString() const ;

public:
	void setZoneName(const string& zoneName)  { m_ZoneName = zoneName; }

	void setMessageTick(Turn_t tick)  { m_MessageTick = tick; }
	Turn_t getMessageTick() const  { return m_MessageTick; }
	
private:
	ZoneID_t 	m_ZoneID;
	ObjectID_t 	m_CreatureID;
	string		m_ZoneName;
	Turn_t  	m_MessageTick;

};

#endif
