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
#include <unordered_map>
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
	ZoneGroupManager() ;
	
	// destructor
	~ZoneGroupManager() ;
	

public:
	
	// initialize zone group manager
	void init() ;
	
	// load sub zone groups from database
	void load() ;
	
	// save sub zone groups to database
	void save() ;
	
	// add zone group to zone group manager
	void addZoneGroup(ZoneGroup* pZoneGroup) ;
	
	// delete zone group from zone group manager
	void deleteZoneGroup(ZoneGroupID_t zoneGroupID) ;
	
	// get zone group from zone group manager
	ZoneGroup* getZoneGroup(ZoneGroupID_t zoneGroupID) const ;

	ZoneGroup* getZoneGroupByGroupID(ZoneGroupID_t ZoneGroupID) const ;

	// size of zone group
	uint size() const  { return m_ZoneGroups.size(); }

	// getZoneGroups
	const unordered_map<ZoneGroupID_t, ZoneGroup*>& getZoneGroups() const { return m_ZoneGroups; }

	void   broadcast(Packet* pPacket) ; 
	void   pushBroadcastPacket(Packet* pPacket, BroadcastFilter* pFilter=NULL) ; 

	bool   makeBalancedLoadInfo(LOAD_INFOS& loadInfos, bool bForce=false) ; 
	bool   makeDefaultLoadInfo(LOAD_INFOS& loadInfos) ; 
	void   balanceZoneGroup(bool bForce=false, bool bDefault=false) ; 


	// get debug string
	string toString() const ;

	void	outputLoadValue() ;

	void    lock()         { m_Mutex.lock(); }
    void    unlock()       { m_Mutex.unlock(); }

	void	lockZoneGroups() ;
	void	unlockZoneGroups() ;

	int 	getPlayerNum () const ;

	void 	removeFlag (Effect::EffectClass EC) ;

private:
	
	// zone ÀÇ ÇØ½¬¸Ê
	unordered_map< ZoneGroupID_t, ZoneGroup* > m_ZoneGroups;

	mutable Mutex	m_Mutex;
};

// global variable declaration
extern ZoneGroupManager* g_pZoneGroupManager;


#endif
