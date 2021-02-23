//////////////////////////////////////////////////////////////////////////////
// Filename    : CreatureManager.h 
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CREATURE_MANANGER_H__
#define __CREATURE_MANANGER_H__

#include "Creature.h"
#include "Mutex.h"
#include <hash_map>

class Packet;

//////////////////////////////////////////////////////////////////////////////
// class CreatureManager
//////////////////////////////////////////////////////////////////////////////

class CreatureManager 
{
public:
	CreatureManager() throw();
	virtual ~CreatureManager() throw();
	
public:
	virtual void addCreature(Creature* pCreature) throw(DuplicatedException, Error);
	virtual void deleteCreature(ObjectID_t objectID) throw();//NoSuchElementException, Error);
	Creature* getCreature(ObjectID_t objectID) const throw();//NoSuchElementException, Error);
	Creature* getCreature(const string& Name) const throw();//NoSuchElementException, Error);

	virtual void processCreatures() throw(Error);
	virtual void killCreature(Creature* pDeadCreature) throw(Error);

	void broadcastPacket(Packet* pPacket, Creature* owner) throw(Error);
	void broadcastDarkLightPacket(Packet* pPacket1, Packet* pPacket2, Creature* owner) throw(Error);
	void broadcastLevelWarBonusPacket(Packet* pPacket, Creature* owner) throw(Error);

	WORD getSize() const throw() { return m_Creatures.size(); }

	hash_map< ObjectID_t, Creature* > & getCreatures() throw() { return m_Creatures; }
	const hash_map< ObjectID_t, Creature* > & getCreatures() const throw() { return m_Creatures; }

	string toString() const throw();

protected:
	hash_map< ObjectID_t, Creature* > m_Creatures;
	mutable Mutex m_Mutex;
};

#endif
