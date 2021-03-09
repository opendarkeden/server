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
	Socket ();
	Socket (const string & host, uint port);
	Socket (SocketImpl* impl);
	
	// destructor
	virtual ~Socket ();

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// close connection
	void close ();
	
	// try connect to remote host
	void connect ();
	void connect (const string & host, uint port);

	// close previous connection and connect to another socket
	void reconnect (const string & host, uint port);
	
	// send data to peer
	uint send (const void* buf, uint len, uint flags = 0);
	
	// receive data from peer
	uint receive (void* buf, uint len, uint flags = 0);
	
	uint available () const;


//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
 
    // get/set socket's linger status
    uint getLinger () const;
    void setLinger (uint lingertime);

	// get is Error
    uint getSockError() const;
 
    // get/set socket's nonblocking status
    bool isNonBlocking () const;
    void setNonBlocking (bool on);
 
    // get/set receive buffer size
    uint getReceiveBufferSize () const;
    void setReceiveBufferSize (uint size);
 
    // get/set send buffer size
    uint getSendBufferSize () const;
    void setSendBufferSize (uint size);
 
	// get host & port
	string getHost () const;
	uint getPort () const;
	IP_t getHostIP () const;

	// check if socket is valid
	bool isValid () const;

	// get socket descriptor
	SOCKET getSOCKET () const;

	// return debug string (FD, HOST, PORT)
	string toString () const;
	
	//add by viva
	string getLocalHost() const { return m_pSocketImpl->getLocalHost(); }

//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private :
	// socket implementation object
	SocketImpl* m_pSocketImpl;
};

#endif
