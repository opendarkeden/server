//--------------------------------------------------------------------------------
// 
// Filename    : UpdateManager.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __UPDATE_MANAGER_H__
#define __UPDATE_MANAGER_H__

// include files
#include "Update.h"
#include "Assert.h"
#include <list>
#include "Resource.h"
#include "ResourceManager.h"

//--------------------------------------------------------------------------------
// 업데이트 명령이 1024면 거의 죽음이당..
//--------------------------------------------------------------------------------
const uint maxUpdates = 1024;

//--------------------------------------------------------------------------------
//
// class UpdateManager
//
// 업데이트 명령을 관리하는 매니저이다.
//
// 패킷에 embedding 되며, 파일시스템에 save/load 되기 때문에,
//
// load/save
// read(SocketInputStream&)/write(SocketOutputStream&)
// read(Socket*)/write(Socket*)
//
// 모두 구현하도록 하자.
//
//--------------------------------------------------------------------------------

class UpdateManager{

public :

	// constructor
	UpdateManager () ;

	// destructor
	~UpdateManager () ;
	

public :

	// load from update file
	void load (const string & filename) ;

	// save to update file
	void save (const string & filename) const ;

	// read from socket input stream
	void read (SocketInputStream & iStream) ;

	// read from socket
	void read (Socket* pSocket) ;

	// write to socket output stream
	void write (SocketOutputStream & oStream) const ;

	// write to socket
	void write (Socket* pSocket) const ;

	// get size
	uint getSize () const ;

	// get max size
	static uint getMaxSize ()  { return Update::getMaxSize()* maxUpdates; }


public :

	// list methods
	void push_back (Update* pUpdate)  { Assert(pUpdate != NULL); m_Updates.push_back(pUpdate); }
	void pop_front ()  { Assert(!m_Updates.empty()); m_Updates.pop_front(); }
	Update* front () const  { Assert(!m_Updates.empty()); return m_Updates.front(); }
	bool empty () const  { return m_Updates.empty(); }

	// get resource manager
	ResourceManager* getResourceManager () ;

	// get debug string
	string toString () const ;


private :

	// list of Update
	list< Update* > m_Updates;

	ResourceManager* m_pResourceManager;

};

#endif
