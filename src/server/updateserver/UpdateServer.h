//--------------------------------------------------------------------------------
// 
// Filename    : UpdateServer.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __UPDATE_SERVER_H__
#define __UPDATE_SERVER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Properties.h"
#include "ServerSocket.h"


//--------------------------------------------------------------------------------
//
// class UpdateServer
//
//--------------------------------------------------------------------------------

class UpdateServer {

public :
	
	// constructor
	UpdateServer () throw ( Error );
	
	// destructor
	~UpdateServer () throw ( Error );

	// intialize game server
	void init () throw ( Error );

	// start game server
	void start () throw ( Error );
	
	// stop game server
	void stop () throw ( Error );

	// main loop
	void run () throw ();

private :

	// system level initialization
	void sysinit () throw ( Error );

	// become daemon
	void goBackground () throw ( Error );

	// update client
	void updateClient ( Socket * pClient ) throw ();

	int getGuildMarkVersion() throw() { return m_GuildMarkVersion; }
	int getLastGuildMarkVersion() throw() { return m_LastGuildMarkVersion; }

private :

	ServerSocket* 	m_pServerSocket;
	int				m_GuildMarkVersion; 
	int				m_LastGuildMarkVersion; 

};


// global variable
extern UpdateServer * g_pUpdateServer;

#endif
