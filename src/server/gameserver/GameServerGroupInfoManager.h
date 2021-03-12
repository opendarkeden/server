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
// 게임 서버의 ID 를 키값으로 하는 GameServerGroupInfo의 unordered_map 을 
// 내부에 가지고 있다.
//
//----------------------------------------------------------------------

class GameServerGroupInfoManager {
	
public :
	
	// constructor
	GameServerGroupInfoManager () ;
	
	// destructor
	~GameServerGroupInfoManager () ;

	// initialize manager
	void init () ;

	// load from database
	void load () ;

	// clear GameServerGroupInfos
	void clear() ;
	
	// add info
	void addGameServerGroupInfo ( GameServerGroupInfo * pGameServerGroupInfo, WorldID_t WorldID ) ;
	
	// delete info
	void deleteGameServerGroupInfo ( const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) ;
	
	// get GameServerGroupInfo by ServerGroupID
	GameServerGroupInfo * getGameServerGroupInfo ( const ServerGroupID_t ServerGroupID, WorldID_t WorldID ) const ;

	// get count of info
	uint getSize ( WorldID_t WorldID ) const  { return m_GameServerGroupInfos[WorldID].size(); }

	// get debug string
	string toString () const ;

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
