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
	SocketImpl () throw ();
	SocketImpl (uint port) throw ();
	SocketImpl (const string & host, uint port) throw ();

	// copy constructor
	SocketImpl (const SocketImpl & impl) throw ();

	// virtual destructor
	virtual ~SocketImpl () throw (Error);

//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// create socket
	void create () throw (Error);
	
	// close connection
	void close () throw (Error);
	
	// bind socket
	void bind () throw (BindException, Error);
	void bind (uint port) throw (BindException, Error);
	
	// listen
	void listen (uint backlog) throw (Error);
	
	// connect to remote host
	void connect () throw (ConnectException, Error);
	void connect (const string & host, uint port) throw (ConnectException, Error);
	
	// accept new connection 
	SocketImpl* accept () throw (NonBlockingIOException, ConnectException, Error);
	
	// send data to peer
	uint send (const void* buf, uint len, uint flags = 0) throw (IOException, InvalidProtocolException, Error);
	
	// receive data from peer
	uint receive (void* buf, uint len, uint flags = 0) throw (IOException, Error);
	
	// how much available?
	uint available () const throw (Error);
	

//////////////////////////////////////////////////
// socket option specific methods
//////////////////////////////////////////////////
public :

	// get/set socket's linger status
	uint getLinger () const throw (Error);
	void setLinger (uint lingertime) throw (Error);
	
	// get/set socket's reuse address status
	bool isReuseAddr () const throw (Error);
	void setReuseAddr (bool on = true) throw (Error);
	
	// get error
	bool isSockError() const throw (Error);

	// get/set socket's nonblocking status
	bool isNonBlocking () const throw (Error);
	void setNonBlocking (bool on = true) throw (Error);
	
	// get/set receive buffer size
	uint getReceiveBufferSize () const throw (Error);
	void setReceiveBufferSize (uint size) throw (Error);
	
	// get/set send buffer size
	uint getSendBufferSize () const throw (Error);
	void setSendBufferSize (uint size) throw (Error);
	

//////////////////////////////////////////////////
// socket information specific methods
//////////////////////////////////////////////////
public :

    // get/set host address and port of this socket
    string getHost () const throw () { return m_Host; }
	uint getPort () const throw () { return m_Port; }
	IP_t getHostIP () const throw () { return (IP_t)(m_SockAddr.sin_addr.s_addr); }

	// check if socket is valid
	bool isValid () const throw () { return m_SocketID != INVALID_SOCKET; }

	// get socket descriptor
	SOCKET getSOCKET () const throw () { return m_SocketID; }


//////////////////////////////////////////////////
// protected methods
//////////////////////////////////////////////////
protected :

    // get/set host address from socket address structure
    string _getHost () const throw ();
    void _setHost (const string & host) throw ();
			    
    // get/set port from socket address structure
	uint _getPort () const throw ();
	void _setPort (uint port) throw ();
	
	
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
