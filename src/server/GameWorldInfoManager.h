//----------------------------------------------------------------------
//
// Filename    : GameWorldInfoManager.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//----------------------------------------------------------------------

#ifndef __GAME_WORLD_INFO_MANAGER_H__
#define __GAME_WORLD_INFO_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "GameWorldInfo.h"
#include <unordered_map>

typedef unordered_map< WorldID_t , GameWorldInfo* > HashMapGameWorldInfo;

//----------------------------------------------------------------------
//
// class GameWorldInfoManager;
//
// 게임 서버의 ID 를 키값으로 하는 GameWorldInfo의 unordered_map 을 
// 내부에 가지고 있다.
//
//----------------------------------------------------------------------

class GameWorldInfoManager {
	
public :
	
	// constructor
	GameWorldInfoManager () ;
	
	// destructor
	~GameWorldInfoManager () ;

	// initialize manager
	void init () ;

	// load from database
	void load () ;

	// clear GameWorldInfo objects
	void clear() ;
	
	// add info
	void addGameWorldInfo ( GameWorldInfo * pGameWorldInfo ) ;
	
	// delete info
	void deleteGameWorldInfo ( const WorldID_t WorldID ) ;
	
	// get GameWorldInfo by WorldID
	GameWorldInfo * getGameWorldInfo ( const WorldID_t WorldID ) const ;

	// get count of info
	uint getSize () const  { return m_GameWorldInfos.size(); }

	// get debug string
	string toString () const ;

private :
	
	// hash map of GameWorldInfo
	// key   : WorldID_t
	// value : GameWorldInfo *
	HashMapGameWorldInfo m_GameWorldInfos;

};


// global variable declaration
extern GameWorldInfoManager * g_pGameWorldInfoManager;

#endif
