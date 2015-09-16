//----------------------------------------------------------------------
//
// Filename    : GameWorldInfoManager.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//----------------------------------------------------------------------

#ifndef __GAME_WORLD_INFO_MANAGER_H__
#define __GAME_WORLD_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "GameWorldInfo.h"
#include <map>

typedef map<WorldID_t, GameWorldInfo*> HashMapGameWorldInfo;

//----------------------------------------------------------------------
//
// class GameWorldInfoManager;
//
// 게임 서버의 ID 를 키값으로 하는 GameWorldInfo의 map 을 
// 내부에 가지고 있다.
//
//----------------------------------------------------------------------

class GameWorldInfoManager {
public:
    GameWorldInfoManager() throw() {};
    ~GameWorldInfoManager() throw();

    void init() throw(Error);
    void load() throw(Error);

    void clear() throw(Error);

    void addGameWorldInfo(GameWorldInfo * pGameWorldInfo) throw(DuplicatedException);
    void deleteGameWorldInfo(const WorldID_t WorldID) throw(NoSuchElementException);

    GameWorldInfo * getGameWorldInfo(const WorldID_t WorldID) const throw(NoSuchElementException);

    uint getSize() const throw() { return m_GameWorldInfos.size(); }

    string toString() const throw();

private :
    // hash map of GameWorldInfo
    // key   : WorldID_t
    // value : GameWorldInfo *
    HashMapGameWorldInfo m_GameWorldInfos;
};

extern GameWorldInfoManager * g_pGameWorldInfoManager;

#endif
