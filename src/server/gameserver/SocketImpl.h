////////////////////////////////////////////////////////////////////////
//
// SocketImpl.h
//
// by Reiot
//
////////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_IMPL_H__
#define __SOCKET_IMPL_H__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "Types.h"
#include "Exception.h"
#include "SocketAPI.h"

//////////////////////////////////////////////////
// forward declarations
//////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//
// class SocketImpl
//
// TCP Socket Implementation Class
//
////////////////////////////////////////////////////////////////////////

class SocketImpl {
	
//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	SocketImpl () ;
	SocketImpl (uint port) ;
	SocketImpl (const string & host, uint port) ;

	// copy constructor
	SocketImpl (const SocketImpl & impl) ;

	// virtual destructor
	virtual ~SocketImpl () ;

//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// create socket
	void create () ;
	
	// close connection
	void close () ;
	
	// bind socket
	void bind () ;
	void bind (uint port) ;
	
	// listen
	void listen (uint backlog) ;
	
	// connect to remote host
	void connect () ;
	void connect (const string & host, uint port) ;
	
	// accept new connection 
	SocketImpl* accept () ;
	
	// send data to peer
	uint send (const void* buf, uint len, uint flags = 0) ;
	
	// receive data from peer
	uint receive (void* buf, uint len, uint flags = 0) ;
	
	// how much available?
	uint available () const ;
	

//////////////////////////////////////////////////
// socket option specific methods
//////////////////////////////////////////////////
public :

	// get/set socket's linger status
	uint getLinger () const ;
	void setLinger (uint lingertime) ;
	
	// get/set socket's reuse address status
	bool isReuseAddr () const ;
	void setReuseAddr (bool on = true) ;
	
	// get error
	bool isSockError() const ;

	// get/set socket's nonblocking status
	bool isNonBlocking () const ;
	void setNonBlocking (bool on = true) ;
	
	// get/set receive buffer size
	uint getReceiveBufferSize () const ;
	void setReceiveBufferSize (uint size) ;
	
	// get/set send buffer size
	uint getSendBufferSize () const ;
	void setSendBufferSize (uint size) ;
	

//////////////////////////////////////////////////
// socket information specific methods
//////////////////////////////////////////////////
public :

    // get/set host address and port of this socket
    string getHost () const  { return m_Host; }
	uint getPort () const  { return m_Port; }
	IP_t getHostIP () const  { return (IP_t)(m_SockAddr.sin_addr.s_addr); }

	// check if socket is valid
	bool isValid () const  { return m_SocketID != INVALID_SOCKET; }

	// get socket descriptor
	SOCKET getSOCKET () const  { return m_SocketID; }


//////////////////////////////////////////////////
// protected methods
//////////////////////////////////////////////////
protected :

    // get/set host address from socket address structure
    string _getHost () const ;
    void _setHost (const string & host) ;
			    
    // get/set port from socket address structure
	uint _getPort () const ;
	void _setPort (uint port) ;
	
	
//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
protected :
	
	// socket descriptor
	SOCKET m_SocketID;
	
	// socket address structure
	SOCKADDR_IN m_SockAddr;
	
	// peer host
	string m_Host;
	
	// peer port
	uint m_Port;
};

//begin hashsize
const static m_HashSize = 512;
//end

#endif
