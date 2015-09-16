//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShutDown.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHUT_DOWN_H__
#define __EFFECT_SHUT_DOWN_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectShutDown;
//////////////////////////////////////////////////////////////////////////////

class Corpse;

class EffectShutDown : public Effect 
{
public:
	EffectShutDown() throw(Error);
	EffectShutDown(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Corpse* pCorpse, Turn_t delay) throw(Error);
	virtual ~EffectShutDown() throw(Error);

public:
	virtual EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SHUT_DOWN; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const throw() { return OBJECT_PRIORITY_NONE; }

	virtual void affect() throw(Error);
	virtual void affect(Creature* pCreature) throw(Error);
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	
	virtual void unaffect() throw(Error);
	virtual void unaffect(Creature* pCreature) throw(Error);
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}

	void create(const string & ownerID) throw(Error) {}
	void save(const string & ownerID) throw(Error) {}
	void destroy(const string & ownerID) throw(Error) {}

	virtual string toString() const throw();

public:
	void setDelay(Turn_t delay) throw() { m_Delay = delay; }
	Turn_t getDelay() const throw() { return m_Delay; }
	
private:
	Turn_t m_Delay;

};

#endif
