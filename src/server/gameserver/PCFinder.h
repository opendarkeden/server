//////////////////////////////////////////////////////////////////////////////
// Filename    : PCFinder.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_FINDER_H__
#define __PC_FINDER_H__

#include "Types.h"
#include "Exception.h"
#include "Creature.h"
#include "NPC.h"
#include "Mutex.h"
#include <unordered_map>
#include <map>

//////////////////////////////////////////////////////////////////////////////
// class PCFinder;
// 게임 서버의 글로벌 매니저 객체로, PC 이름을 사용해서 PC객체에 접근할 수 있도록
// 해준다. 내부적으로 unordered_map 을 사용해서, 검색 속도를 향상시킨다.
//////////////////////////////////////////////////////////////////////////////

class PCFinder 
{
public:
	PCFinder() ;
	~PCFinder() ;

public:
	// add creature to unordered_map
	// execute just once at PC's login
	void addCreature(Creature* pCreature) ;

	// delete creature from unordered_map
	// execute just once at PC's logout
	void deleteCreature(const string & name) ;//NoSuchElementException, Error);

	// get creature with PC-name
	Creature* getCreature(const string & name) const ; //NoSuchElementException, Error);

	// get creature with PC-name
	Creature* getCreature_LOCKED(const string & name) const ; //NoSuchElementException, Error);

	// PlayerID. for BillingServer. by sigi. 2002.11.18
	Creature* getCreatureByID(const string & ID) const ; //NoSuchElementException, Error);
	Creature* getCreatureByID_LOCKED(const string & ID) const ; //NoSuchElementException, Error);

	// add NPC to unordered_map
	void addNPC(NPC *npc) ;
	
	// delete NPC from unordered_map
	void deleteNPC(const string & name) ;

	// get NPC 
	NPC* getNPC(const string & name) const ;
	NPC* getNPC_LOCKED(const string & name) const ;

	// get creature's IP address
	IP_t getIP(const string & name) const ;

	list<Creature*>	getGuildCreatures(GuildID_t gID, uint Num);

/*	pair<multimap< GuildID_t, Creature* >::const_iterator, multimap< GuildID_t, Creature* >::const_iterator>
		getGuildRange(GuildID_t gID) const { return m_GuildMap.equal_range(gID); }*/

	void lock()  { m_Mutex.lock(); }
	void unlock()  { m_Mutex.unlock(); }

private:
	unordered_map< string, Creature* > 	m_PCs;
	unordered_map< string, Creature* > 	m_IDs;	// PlayerID. for BillingServer. by sigi. 2002.11.18
	unordered_map< string, NPC* > 		m_NPCs;	// NPCs.. for NPC trace ;; by DEW  2003. 04. 16
//	multimap< GuildID_t, Creature* >	m_GuildMap;
	mutable Mutex m_Mutex;
};

// global variable declaration
extern PCFinder* g_pPCFinder;

#endif
