//////////////////////////////////////////////////////////////////////////////
// Socket.h 
// by Reiot
//////////////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "Types.h"
#include "Exception.h"
#include "SocketImpl.h"

//////////////////////////////////////////////////////////////////////////////
// class Socket
//
// TCP Client Socket
//
// *Reiot's Note*
//
// 버퍼 크기를 지정하려면, connect() 전에 지정해야 한다.
//////////////////////////////////////////////////////////////////////////////

class Socket 
{
//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	Socket () throw ();
	Socket (const string & host, uint port) throw ();
	Socket (SocketImpl* impl) throw ();
	
	// destructor
	virtual ~Socket () throw (Error);

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// close connection
	void close () throw (Error);
	
	// try connect to remote host
	void connect () throw (ConnectException, Error);
	void connect (const string & host, uint port) throw (ConnectException, Error);

	// close previous connection and connect to another socket
	void reconnect (const string & host, uint port) throw (ConnectException, Error);
	
	// send data to peer
	uint send (const void* buf, uint len, uint flags = 0) throw (IOException, Error);
	
	// receive data from peer
	uint receive (void* buf, uint len, uint flags = 0) throw (IOException, ConnectException, Error);
	
	uint available () const throw (Error);


//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
 
    // get/set socket's linger status
    uint getLinger () const throw (Error);
    void setLinger (uint lingertime) throw (Error);

	// get is Error
    uint getSockError() const throw (Error);
 
    // get/set socket's nonblocking status
    bool isNonBlocking () const throw (Error);
    void setNonBlocking (bool on = true) throw (Error);
 
    // get/set receive buffer size
    uint getReceiveBufferSize () const throw (Error);
    void setReceiveBufferSize (uint size) throw (Error);
 
    // get/set send buffer size
    uint getSendBufferSize () const throw (Error);
    void setSendBufferSize (uint size) throw (Error);
 
	// get host & port
	string getHost () const throw ();
	uint getPort () const throw ();
	IP_t getHostIP () const throw ();

	// check if socket is valid
	bool isValid () const throw ();

	// get socket descriptor
	SOCKET getSOCKET () const throw ();

	// return debug string (FD, HOST, PORT)
	string toString () const throw ();
	
	//add by viva
	string getLocalHost() const throw() { return m_pSocketImpl->getLocalHost(); }

//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private :
	// socket implementation object
	SocketImpl* m_pSocketImpl;
};

#endif
