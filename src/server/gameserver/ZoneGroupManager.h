//--------------------------------------------------------------------------------
//
// Filename    : ZoneGroupManager.h
// Written By  : Reiot
// Description :
//
//--------------------------------------------------------------------------------

#ifndef __ZONE_GROUP_MANAGER_H__
#define __ZONE_GROUP_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include <vector>
#include <map>
#include "ZoneGroup.h"
#include "Effect.h"

class BroadcastFilter;

//--------------------------------------------------------------------------------
// LoadInfo
//--------------------------------------------------------------------------------
struct LoadInfo
{
	int id;

	int groupID;
	int oldGroupID;

	int load;
};

template<class T>
struct loadCheck : public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const
	{
		return x > y;
	}
};

typedef loadCheck<DWORD> loadCheckInfo;

typedef map<DWORD, LoadInfo*, loadCheckInfo>	LOAD_INFOS;
typedef vector<DWORD> 							GROUPS;


//--------------------------------------------------------------------------------
//
// class ZoneGroupManager;
//
// Collection of ZoneGroup
//
//--------------------------------------------------------------------------------
class ZoneGroupManager {
	
public:
	
	// constructor
	ZoneGroupManager() throw();
	
	// destructor
	~ZoneGroupManager() throw();
	

public:
	
	// initialize zone group manager
	void init() throw(Error);
	
	// load sub zone groups from database
	void load() throw(Error);
	
	// save sub zone groups to database
	void save() throw(Error);
	
	// add zone group to zone group manager
	void addZoneGroup(ZoneGroup* pZoneGroup) throw(Error);
	
	// delete zone group from zone group manager
	void deleteZoneGroup(ZoneGroupID_t zoneGroupID) throw(NoSuchElementException);
	
	// get zone group from zone group manager
	ZoneGroup* getZoneGroup(ZoneGroupID_t zoneGroupID) const throw(NoSuchElementException);

	ZoneGroup* getZoneGroupByGroupID(ZoneGroupID_t ZoneGroupID) const throw(NoSuchElementException);

	// size of zone group
	uint size() const throw() { return m_ZoneGroups.size(); }

	// getZoneGroups
	const hash_map<ZoneGroupID_t, ZoneGroup*>& getZoneGroups() const { return m_ZoneGroups; }

	void   broadcast(Packet* pPacket) throw (Error); 
	void   pushBroadcastPacket(Packet* pPacket, BroadcastFilter* pFilter=NULL) throw (Error); 

	bool   makeBalancedLoadInfo(LOAD_INFOS& loadInfos, bool bForce=false) throw (Error); 
	bool   makeDefaultLoadInfo(LOAD_INFOS& loadInfos) throw (Error); 
	void   balanceZoneGroup(bool bForce=false, bool bDefault=false) throw (Error); 


	// get debug string
	string toString() const throw();

	void	outputLoadValue() throw (Error);

	void    lock() throw (Error)        { m_Mutex.lock(); }
    void    unlock() throw (Error)      { m_Mutex.unlock(); }

	void	lockZoneGroups() throw( Error );
	void	unlockZoneGroups() throw( Error );

	int 	getPlayerNum () const throw(Error);

	void 	removeFlag (Effect::EffectClass EC) throw(Error);

private:
	
	// zone ÀÇ ÇØ½¬¸Ê
	hash_map< ZoneGroupID_t, ZoneGroup* > m_ZoneGroups;

	mutable Mutex	m_Mutex;
};

// global variable declaration
extern ZoneGroupManager* g_pZoneGroupManager;


#endif
