//////////////////////////////////////////////////////////////////////////////
// Filename    : NPCManager.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __NPC_MANANGER_H__
#define __NPC_MANANGER_H__

#include "CreatureManager.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class NPCManager
//////////////////////////////////////////////////////////////////////////////

class Zone;

class NPCManager : public CreatureManager 
{
public:
	NPCManager() throw(Error);
	~NPCManager() throw();
	
public:
	void load(ZoneID_t zoneID, int race=0xFF) throw(Error);	// 0xFF¿Ã∏È ALL.. -_-;
	void processCreatures() throw(Error);
	string toString() const throw();
};

#endif
