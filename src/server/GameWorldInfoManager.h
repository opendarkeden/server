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
#include <hash_map>

typedef hash_map< WorldID_t , GameWorldInfo* > HashMapGameWorldInfo;

//----------------------------------------------------------------------
//
// class GameWorldInfoManager;
//
// 게임 서버의 ID 를 키값으로 하는 GameWorldInfo의 hash_map 을 
// 내부에 가지고 있다.
//
//----------------------------------------------------------------------

class GameWorldInfoManager {
	
public :
	
	// constructor
	GameWorldInfoManager () throw ();
	
	// destructor
	~GameWorldInfoManager () throw ();

	// initialize manager
	void init () throw ( Error );

	// load from database
	void load () throw ( Error );

	// clear GameWorldInfo objects
	void clear() throw ( Error );
	
	// add info
	void addGameWorldInfo ( GameWorldInfo * pGameWorldInfo ) throw ( DuplicatedException );
	
	// delete info
	void deleteGameWorldInfo ( const WorldID_t WorldID ) throw ( NoSuchElementException );
	
	// get GameWorldInfo by WorldID
	GameWorldInfo * getGameWorldInfo ( const WorldID_t WorldID ) const throw( NoSuchElementException );

	// get count of info
	uint getSize () const throw () { return m_GameWorldInfos.size(); }

	// get debug string
	string toString () const throw ();

private :
	
	// hash map of GameWorldInfo
	// key   : WorldID_t
	// value : GameWorldInfo *
	HashMapGameWorldInfo m_GameWorldInfos;

};


// global variable declaration
extern GameWorldInfoManager * g_pGameWorldInfoManager;

#endif
