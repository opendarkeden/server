//----------------------------------------------------------------------
//
// Filename    : GameServerGroupInfoManager.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//----------------------------------------------------------------------

#ifndef __GAME_SERVER_GROUP_INFO_MANAGER_H__
#define __GAME_SERVER_GROUP_INFO_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "GameServerGroupInfo.h"
#include <unordered_map>

typedef unordered_map< ServerGroupID_t ,GameServerGroupInfo * > HashMapGameServerGroupInfo;

//----------------------------------------------------------------------
//
// class GameServerGroupInfoManager;
//
// ���� ������ ID �� Ű������ �ϴ� GameServerGroupInfo�� unordered_map �� 
// ���ο� ������ �ִ�.
//
//----------------------------------------------------------------------

class GameServerGroupInfoManager {
	
public :
	
	// constructor
	GameServerGroupInfoManager () noexcept;
	
	// destructor
	~GameServerGroupInfoManager () noexcept;

	// initialize manager
	void init () noexcept(false);

	// load from database
	void load () noexcept(false);

	// clear GameServerGroupInfos
	void clear() noexcept(false);
	
	// add info
	void addGameServerGroupInfo ( GameServerGroupInfo * pGameServerGroupInfo, WorldID_t WorldID ) noexcept(false);
	
	// delete info
	void deleteGameServerGroupInfo ( const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) noexcept(false);
	
	// get GameServerGroupInfo by ServerGroupID
	GameServerGroupInfo * getGameServerGroupInfo ( const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) const noexcept(false);

	// get count of info
	uint getSize ( WorldID_t WorldID ) const noexcept { return m_GameServerGroupInfos[WorldID].size(); }

	// get debug string
	string toString () const noexcept(false);

private :
	
	// hash map of GameServerGroupInfo
	// key   : GameServerGroupID_t
	// value : GameServerGroupInfo *
	HashMapGameServerGroupInfo* m_GameServerGroupInfos;

	WorldID_t m_MaxWorldID;

};


// global variable declaration
extern GameServerGroupInfoManager * g_pGameServerGroupInfoManager;

#endif
