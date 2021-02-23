//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServer.h 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GAME_SERVER_H__
#define __GAME_SERVER_H__

#include "Types.h"
#include "Exception.h"
#include "Properties.h"

//////////////////////////////////////////////////////////////////////////////
// class GameServer
//////////////////////////////////////////////////////////////////////////////

class ClientManager;
class ThreadManager;

class GameServer 
{
public:
	GameServer() throw(Error);
	~GameServer() throw(Error);

public:
	void init() throw(Error);

	void start() throw(Error);
	
	void stop() throw(Error);

private:
	void sysinit() throw(Error);
	void goBackground() throw(Error);
};

// global variable
extern GameServer* g_pGameServer;

#endif
