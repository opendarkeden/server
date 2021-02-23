////////////////////////////////////////////////////////////////////////
//
// SocketImpl.cpp
//
// by Reiot
//
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "SocketImpl.h"
#include "FileAPI.h"
#include "SocketAPI.h"

#if __LINUX__
#include <sys/socket.h>
#include <arpa/inet.h>	// for inet_ntoa()
#elif __WINDOWS__
#endif

//////////////////////////////////////////////////
// forward declarations
//////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// 
// SocketImpl::SocketImpl () throw ( Error );
// 
// Parameters 
//     none
// 
// Exceptions
//     Error
// 
////////////////////////////////////////////////////////////////////////
SocketImpl::SocketImpl () 
	 throw ()
: m_SocketID(INVALID_SOCKET), m_Host("Unknown"), m_Port(0)
{

}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
SocketImpl::SocketImpl ( uint port ) 
	 throw ()
: m_SocketID(INVALID_SOCKET), m_Host("Unknown"), m_Port(port)
{

}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
SocketImpl::SocketImpl ( const string & host , uint port ) 
	throw ()
: m_SocketID(INVALID_SOCKET), m_Host(host), m_Port(port)
{

}


////////////////////////////////////////////////////////////////////////
//
// SocketImpl::SocketImpl ( const SocketImpl & impl ) throw ();
//
// copy constructor 
//
// Parameters
//     impl - socket implementation object
//
// Exceptions
//     none
//
////////////////////////////////////////////////////////////////////////
SocketImpl::SocketImpl ( const SocketImpl & impl ) 
	throw ()
: m_SocketID(impl.m_SocketID), m_Host(impl.m_Host), m_Port(impl.m_Port)
{

}

////////////////////////////////////////////////////////////////////////
//
// SocketImpl::~SocketImpl () throw ( Error );
//
// virtual destructor
//
// Parameters
//     none
//
// Exceptions
//     Error
//
////////////////////////////////////////////////////////////////////////
SocketImpl::~SocketImpl () 
	throw ( Error )
{
	__BEGIN_TRY 

	close();
	
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// create connection
//////////////////////////////////////////////////////////////////////
void SocketImpl::create () throw ( Error )
{
	__BEGIN_TRY
		
	// create socket
	m_SocketID = SocketAPI::socket_ex( AF_INET , SOCK_STREAM , 0 );

	// clear socket address structure
    memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );

	// set socket address's family to "AF_INET"
	m_SockAddr.sin_family      = AF_INET;
 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// close connection
//////////////////////////////////////////////////////////////////////
void SocketImpl::close () throw ( Error )
{
	__BEGIN_TRY 

	if( !isSockError() ) {
		try {
			SocketAPI::closesocket_ex( m_SocketID );
		} catch ( FileNotOpenedException& ) {
			// if already closed, ignore...
		}
	}
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// bind address to socket
//////////////////////////////////////////////////////////////////////
void SocketImpl::bind ()
	 throw ( BindException , Error )
{
	__BEGIN_TRY

	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_SockAddr.sin_port        = htons(m_Port);

	SocketAPI::bind_ex( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// bind address to socket
//////////////////////////////////////////////////////////////////////
void SocketImpl::bind ( uint port )
	 throw ( BindException , Error )
{
	__BEGIN_TRY

	// set server's port
	m_Port = port;

	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_SockAddr.sin_port        = htons(m_Port);

	SocketAPI::bind_ex( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) );
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// bind address to socket
//////////////////////////////////////////////////////////////////////
void SocketImpl::listen ( uint backlog )
	 throw ( Error )
{
	__BEGIN_TRY
		
	SocketAPI::listen_ex( m_SocketID , backlog );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// connect to remote host
//////////////////////////////////////////////////////////////////////
void SocketImpl::connect ( const string & host , uint port )
     throw ( ConnectException , Error )
{
	__BEGIN_TRY 
		
	m_Host = host;
	m_Port = port;

	// set sockaddr's host
	m_SockAddr.sin_addr.s_addr = inet_addr( m_Host.c_str() );
	
	// set sockaddr's port
	m_SockAddr.sin_port = htons(m_Port);
	
	// try to connect to peer host
	SocketAPI::connect_ex( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) );
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
void SocketImpl::connect ()
     throw ( ConnectException , Error )
{
	__BEGIN_TRY 

	// set sockaddr's host
	m_SockAddr.sin_addr.s_addr = inet_addr( m_Host.c_str() );
	
	// set sockaddr's port
	m_SockAddr.sin_port = htons(m_Port);
	
	// try to connect to peer host
	SocketAPI::connect_ex( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) );
	
	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
SocketImpl * SocketImpl::accept ()
	throw ( NonBlockingIOException , ConnectException , Error )
{
	__BEGIN_TRY

    // make client socket address structure ready
    SOCKADDR_IN ClientAddr;
    memset( &ClientAddr , 0 , sizeof(ClientAddr) );
    uint len = sizeof(ClientAddr);
 
    // get client socket descriptor
    uint ClientID = SocketAPI::accept_ex( m_SocketID , (struct sockaddr *)&ClientAddr , &len );
 
    // create MSocketImpl with socket descriptor
    SocketImpl * client = new SocketImpl();
 
	// initialize client socket implementation object
	client->m_SocketID = ClientID;
	memcpy( &(client->m_SockAddr) , &ClientAddr , sizeof(SOCKADDR_IN) );
	client->m_Host = client->_getHost();
	client->m_Port = client->_getPort();
 
    // return SocketImpl
    return client;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// send data to peer
//////////////////////////////////////////////////////////////////////
uint SocketImpl::send ( const void * buf , uint len , uint flags ) 
     throw ( IOException , InvalidProtocolException, Error )
{
	__BEGIN_TRY 

	uint result;

	try {

	result = SocketAPI::send_ex( m_SocketID , buf , len , flags );

	} catch ( Throwable & t ) {
		cout << "SocketImpl::send Exception Check!" << endl;
		cout << t.toString() << endl;
		throw InvalidProtocolException( "음 여까지 올라왔군" );
	}

	return result;
	
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// receive data from peer
//////////////////////////////////////////////////////////////////////
uint SocketImpl::receive ( void * buf , uint len , uint flags ) 
     throw ( IOException , Error )
{
	__BEGIN_TRY 

	Retlen = SocketAPI::recv_ex(m_SocketID, buf, len, flags);
	
	DecryptBuf(buf, m_HashTable, Retlen);

	return Retlen;
		
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// how much available?
//////////////////////////////////////////////////////////////////////
uint SocketImpl::available () const 
     throw ( Error )
{
	__BEGIN_TRY 
		
	return SocketAPI::availablesocket_ex( m_SocketID );

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// get socket's linger status
//////////////////////////////////////////////////////////////////////
uint SocketImpl::getLinger () const
     throw ( Error )
{
	__BEGIN_TRY 

	struct linger ling;
	uint len = sizeof(ling);
	
	SocketAPI::getsockopt_ex( m_SocketID , SOL_SOCKET , SO_LINGER , &ling , &len );
	
	return ling.l_linger;
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// set socket's linger status
//////////////////////////////////////////////////////////////////////
void SocketImpl::setLinger ( uint lingertime )
     throw ( Error )
{
	__BEGIN_TRY 

	struct linger ling;
	
	ling.l_onoff = lingertime > 0 ? 1 : 0;
	ling.l_linger = lingertime;
	
	SocketAPI::setsockopt_ex( m_SocketID , SOL_SOCKET , SO_LINGER , &ling , sizeof(ling) );
	
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// get socket's reuse address status
//////////////////////////////////////////////////////////////////////
bool SocketImpl::isReuseAddr () const
     throw ( Error )
{
	__BEGIN_TRY 
		
	int reuse;
	uint len = sizeof(reuse);
	
	SocketAPI::getsockopt_ex( m_SocketID , SOL_SOCKET , SO_REUSEADDR , &reuse , &len );
	
	return reuse == 1;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// get socket's reuse address status
//////////////////////////////////////////////////////////////////////
bool SocketImpl::isSockError () const
     throw ( Error )
{
	__BEGIN_TRY 
		
	int error;
	uint len = sizeof(error);
	
	int Result = SocketAPI::getsockopt_ex2( m_SocketID , SOL_SOCKET , SO_ERROR , &error, &len );

	if( Result == 0 ) return false;
	else 			  return true;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// set socket's reuse address status
//////////////////////////////////////////////////////////////////////
void SocketImpl::setReuseAddr ( bool on )
     throw ( Error )
{
	__BEGIN_TRY 

	int opt = on == true ? 1 : 0;
	
	SocketAPI::setsockopt_ex( m_SocketID , SOL_SOCKET , SO_REUSEADDR , &opt , sizeof(opt) );
	
	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// get socket's nonblocking status
//////////////////////////////////////////////////////////////////////
bool SocketImpl::isNonBlocking () const 
     throw ( Error )
{
	__BEGIN_TRY 

	return SocketAPI::getsocketnonblocking_ex( m_SocketID );
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// set socket's nonblocking status
//////////////////////////////////////////////////////////////////////
void SocketImpl::setNonBlocking ( bool on ) 
     throw ( Error )
{
	__BEGIN_TRY 

	SocketAPI::setsocketnonblocking_ex( m_SocketID , on );
	
	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// get receive buffer size
//////////////////////////////////////////////////////////////////////
uint SocketImpl::getReceiveBufferSize () const 
     throw ( Error )
{
	__BEGIN_TRY 

	uint ReceiveBufferSize;
	uint size = sizeof(ReceiveBufferSize);

	SocketAPI::getsockopt_ex( m_SocketID , SOL_SOCKET , SO_SNDBUF , &ReceiveBufferSize, &size );
	
	return ReceiveBufferSize;
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// set receive buffer size
//////////////////////////////////////////////////////////////////////
void SocketImpl::setReceiveBufferSize ( uint ReceiveBufferSize ) 
	 throw ( Error )
{
	__BEGIN_TRY 

	SocketAPI::setsockopt_ex( m_SocketID , SOL_SOCKET , SO_SNDBUF , &ReceiveBufferSize, sizeof(ReceiveBufferSize) );
	
	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// get send buffer size
//////////////////////////////////////////////////////////////////////
uint SocketImpl::getSendBufferSize () const 
     throw ( Error )
{
	__BEGIN_TRY 
		
	uint SendBufferSize;
	uint size = sizeof(SendBufferSize);

	SocketAPI::getsockopt_ex( m_SocketID , SOL_SOCKET , SO_SNDBUF , &SendBufferSize, &size );
	
	return SendBufferSize;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// void SocketImpl::setSendBufferSize ( uint SendBufferSize ) throw ( Error )
//
// set send buffer size
//
// Parameters
//
// Return
//
// Exceptions
//     Error from setsockopt_ex()
//
//////////////////////////////////////////////////////////////////////
void SocketImpl::setSendBufferSize ( uint SendBufferSize ) 
     throw ( Error )
{
	__BEGIN_TRY 
		
	SocketAPI::setsockopt_ex( m_SocketID , SOL_SOCKET , SO_SNDBUF , &SendBufferSize, sizeof(SendBufferSize) );
	
	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
//
// string SocketImpl::_getHost () const throw ();
//
// get host address of this socket
//
// Parameters
//     none
//
// Return
//     host string
//
// Exceptions
//     none
//
//////////////////////////////////////////////////////////////////////
string SocketImpl::_getHost () const 
       throw ()
{
	return string( inet_ntoa( m_SockAddr.sin_addr ) );
}


//////////////////////////////////////////////////////////////////////
//
// void SocketImpl::_setHost ( const string & host ) throw ()
//
// set host address of this socket
//
// Parameters
//     host - peer host's address
//
// Return
//     none
//
// Exceptions
//     none
//
//////////////////////////////////////////////////////////////////////
void SocketImpl::_setHost ( const string & host ) 
     throw ()
{
	m_SockAddr.sin_addr.s_addr = inet_addr( host.c_str() );
}
			    

//////////////////////////////////////////////////////////////////////
//
// uint SocketImpl::_getPort () const throw ()
//
// get port of this socket
//
// Parameters
//     none
//
// Return
//     port
//
// Exceptions
//     none
//
//////////////////////////////////////////////////////////////////////
uint SocketImpl::_getPort () const 
     throw ()
{
	return ntohs( m_SockAddr.sin_port );
}


//////////////////////////////////////////////////////////////////////
//
// void SocketImpl::_setPort ( uint port ) throw ()
//
// set host address of this socket
//
// Parameters
//     port - peer host's port
//
// Return
//     none
//
// Exceptions
//     none
//
//////////////////////////////////////////////////////////////////////
void SocketImpl::_setPort ( uint port ) 
	 throw ()
{
	m_SockAddr.sin_port = htons(port);
}

