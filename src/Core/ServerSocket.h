//////////////////////////////////////////////////////////////////////
//
// ServerSocket.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

#ifndef __SERVER_SOCKET__
#define __SERVER_SOCKET__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "Types.h"
#include "Exception.h"
#include "SocketImpl.h"
#include "Socket.h"


//////////////////////////////////////////////////////////////////////
//
// class ServerSocket
//
//////////////////////////////////////////////////////////////////////

class ServerSocket {

//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	ServerSocket (uint port, uint backlog = 5);
	
	// destructor
	~ServerSocket () ;
	

//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// close socket
	void close () ;
	
	// accept new connection
	Socket* accept () ;

	// get/set socket's linger status
    uint getLinger () const  { return m_Impl->getLinger(); }
    void setLinger (uint lingertime)  { m_Impl->setLinger(lingertime); }
 
    // get/set socket's reuse address status
    bool isReuseAddr () const  { return m_Impl->isReuseAddr(); }
    void setReuseAddr (bool on = true)  { m_Impl->setReuseAddr(on); }
 
    // get/set socket's nonblocking status
    bool isNonBlocking () const  { return m_Impl->isNonBlocking(); }
    void setNonBlocking (bool on = true)  { m_Impl->setNonBlocking(on); }
 
    // get/set receive buffer size
    uint getReceiveBufferSize () const  { return m_Impl->getReceiveBufferSize(); }
    void setReceiveBufferSize (uint size)  { m_Impl->setReceiveBufferSize(size); }
 
    // get/set send buffer size
    uint getSendBufferSize () const  { return m_Impl->getSendBufferSize(); }
    void setSendBufferSize (uint size)  { m_Impl->setSendBufferSize(size); }
 
	SOCKET getSOCKET ()  { return m_Impl->getSOCKET(); }

//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
protected :
	
	// socket implementation object
	SocketImpl* m_Impl;
	
};
#endif
