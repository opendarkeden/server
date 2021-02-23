//////////////////////////////////////////////////////////////////////
// 
// Socket.cpp
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#include "Socket.h"
#include "Assert.h"

Socket::Socket () 
	throw () 
: m_pSocketImpl(NULL) 
{ 
	__BEGIN_TRY

	m_pSocketImpl = new SocketImpl(); 
	m_pSocketImpl->create();
	
	__END_CATCH
}

Socket::Socket ( const string & host , uint port ) 
	throw () 
: m_pSocketImpl(NULL) 
{ 
	__BEGIN_TRY

	m_pSocketImpl = new SocketImpl(host,port); 
	m_pSocketImpl->create();
	
	__END_CATCH
}

Socket::Socket ( SocketImpl * impl ) 
	throw () 
: m_pSocketImpl(NULL) 
{ 
	__BEGIN_TRY

	Assert( impl != NULL );

	m_pSocketImpl = impl;
	
	__END_CATCH
}

Socket::~Socket () 
	throw ( Error ) 
{ 
	__BEGIN_TRY

	if ( m_pSocketImpl != NULL ) { 
		delete m_pSocketImpl; 
		m_pSocketImpl = NULL; 
	} 
	
	__END_CATCH
}

// close previous connection and connect to another server socket
void Socket::reconnect ( const string & host , uint port )
	throw ( ConnectException , Error )
{
	__BEGIN_TRY

	// delete old socket impl object
	m_pSocketImpl->close();
	delete m_pSocketImpl;

	// create new socket impl object
	m_pSocketImpl = new SocketImpl( host , port );
	m_pSocketImpl->create();

	// try to connect
	m_pSocketImpl->connect();	

	__END_CATCH
}

void Socket::close () 
	throw (Error) 
{ 
	__BEGIN_TRY

	m_pSocketImpl->close(); 

	__END_CATCH
}
	
void Socket::connect () 
	throw (ConnectException, Error) 
{ 
	__BEGIN_TRY

	m_pSocketImpl->connect(); 

	__END_CATCH
}

void Socket::connect (const string & host, uint port) 
	throw (ConnectException, Error)
{ 
	__BEGIN_TRY

	m_pSocketImpl->connect(host,port); 

	__END_CATCH
}

uint Socket::send (const void* buf, uint len, uint flags) 
	throw (IOException, Error)
{ 
	__BEGIN_TRY

	return m_pSocketImpl->send(buf,len,flags); 

	__END_CATCH
}

uint Socket::receive (void* buf, uint len, uint flags) 
	throw (IOException, ConnectException, Error) 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->receive(buf,len,flags); 

	__END_CATCH
}

uint Socket::available () const
	throw (Error) 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->available(); 

	__END_CATCH
}

uint Socket::getLinger () const 
	throw (Error) 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->getLinger(); 

	__END_CATCH
}

void Socket::setLinger (uint lingertime) 
	throw (Error) 
{
	__BEGIN_TRY

	m_pSocketImpl->setLinger(lingertime); 

	__END_CATCH
}

uint Socket::getSockError() const 
	throw (Error) 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->isSockError(); 

	__END_CATCH
}

bool Socket::isNonBlocking () const 
	throw (Error) 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->isNonBlocking(); 

	__END_CATCH
}

void Socket::setNonBlocking (bool on = true) 
	throw (Error) 
{ 
	__BEGIN_TRY

	m_pSocketImpl->setNonBlocking(on); 

	__END_CATCH
}

uint Socket::getReceiveBufferSize () const 
	throw (Error) 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->getReceiveBufferSize(); 

	__END_CATCH
}

void Socket::setReceiveBufferSize (uint size)
	throw (Error) 
{ 
	__BEGIN_TRY

	m_pSocketImpl->setReceiveBufferSize(size); 

	__END_CATCH
}

uint Socket::getSendBufferSize () const 
	throw (Error) 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->getSendBufferSize(); 

	__END_CATCH
}

void Socket::setSendBufferSize (uint size)
	throw (Error) 
{ 
	__BEGIN_TRY

	m_pSocketImpl->setSendBufferSize(size); 

	__END_CATCH
}

string Socket::getHost () const 
	throw () 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->getHost(); 

	__END_CATCH
}

uint Socket::getPort () const 
	throw () 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->getPort(); 

	__END_CATCH
}

IP_t Socket::getHostIP () const 
	throw () 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->getHostIP(); 

	__END_CATCH
}

bool Socket::isValid () const 
	throw () 
{
	__BEGIN_TRY

	return m_pSocketImpl->isValid(); 

	__END_CATCH
}

SOCKET Socket::getSOCKET () const 
	throw () 
{ 
	__BEGIN_TRY

	return m_pSocketImpl->getSOCKET(); 

	__END_CATCH
}

// return debug string
string Socket::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "Socket(FD:" << getSOCKET() << ",HOST:" << getHost() << ",PORT:" << getPort() << ")" ;
	return msg.toString();

	__END_CATCH
}
