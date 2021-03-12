//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPrecedence.h
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PRECEDENCE_H__
#define __EFFECT_PRECEDENCE_H__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPrecedence;
//////////////////////////////////////////////////////////////////////////////

class EffectPrecedence : public Effect 
{
public:
	EffectPrecedence(Creature* pCreature) ;
	EffectPrecedence(Item* pItem) ;
	
public:
	virtual EffectClass getEffectClass() const  { return EFFECT_CLASS_PRECEDENCE; }

	// OBJECT_PRIORITY_NONE 라는 뜻은, 타일에 들어가서는 안된다는 뜻이다.
	virtual ObjectPriority getObjectPriority() const  { return OBJECT_PRIORITY_NONE; }

	virtual void affect() ;
	virtual void affect(Creature* pCreature) ;
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) ;
	
	virtual void unaffect() ;
	virtual void unaffect(Creature* pCreature) ;
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget) ;
	void unaffect(Item* pItem)  {}

	void create(const string & ownerID)  {}
	void save(const string & ownerID)  {}
	void destroy(const string & ownerID)  {}
	
	virtual string toString() const ;

public:
	string getHostName(void) const { return m_HostName; }
	void setHostName(const string& ID) { m_HostName = ID; }

	int getHostPartyID(void) const { return m_HostPartyID; }
	void setHostPartyID(int ID) { m_HostPartyID = ID; }

private:
	string m_HostName;
	int    m_HostPartyID;
	bool   m_bItem;
};

#endif
