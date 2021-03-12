//////////////////////////////////////////////////////////////////////////////
// Filename    : CreatureManager.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CREATURE_MANANGER_H__
#define __CREATURE_MANANGER_H__

#include "Creature.h"
#include "Mutex.h"
#include <unordered_map>

class Packet;

//////////////////////////////////////////////////////////////////////////////
// class CreatureManager
//////////////////////////////////////////////////////////////////////////////

class CreatureManager 
{
public:
	CreatureManager() ;
	virtual ~CreatureManager() ;
	
public:
	virtual void addCreature(Creature* pCreature) ;
	virtual void deleteCreature(ObjectID_t objectID) ;//NoSuchElementException, Error);
	Creature* getCreature(ObjectID_t objectID) const ;//NoSuchElementException, Error);
	Creature* getCreature(const string& Name) const ;//NoSuchElementException, Error);

	virtual void processCreatures() ;
	virtual void killCreature(Creature* pDeadCreature) ;

	void broadcastPacket(Packet* pPacket, Creature* owner) ;
	void broadcastDarkLightPacket(Packet* pPacket1, Packet* pPacket2, Creature* owner) ;
	void broadcastLevelWarBonusPacket(Packet* pPacket, Creature* owner) ;

	WORD getSize() const  { return m_Creatures.size(); }

	unordered_map< ObjectID_t, Creature* > & getCreatures()  { return m_Creatures; }
	const unordered_map< ObjectID_t, Creature* > & getCreatures() const  { return m_Creatures; }

	string toString() const ;

protected:
	unordered_map< ObjectID_t, Creature* > m_Creatures;
	mutable Mutex m_Mutex;
};

#endif
