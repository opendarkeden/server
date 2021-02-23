//////////////////////////////////////////////////////////////////////
//
// ServerSocket.cpp
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "ServerSocket.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ServerSocket::ServerSocket ( uint port , uint backlog ) 
	throw ( BindException , Error )
: m_Impl(NULL)
{
	__BEGIN_TRY
		
	// create socket implementation object
	m_Impl = new SocketImpl(port);
	
	// create socket
	m_Impl->create();
	
	// reuse address before Bind()
	// 바인드 하기 전에 주소 리유즈를 시스템에 알려야 한다.
	m_Impl->setReuseAddr();
	
	// bind address to socket
	// 이미 port가 m_Impl에 저장되어 있으므로, 파라미터없는 Bind()를 호출해도 된다.
	m_Impl->bind();

//	m_Impl->setSendBufferSize( 9000 );
//	m_Impl->setReceiveBufferSize( 9000 );
	
	// set listening queue size
	m_Impl->listen(backlog);

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
ServerSocket::~ServerSocket () 
	throw ( Error )
{
	__BEGIN_TRY
		
	if ( m_Impl != NULL ) 
	{
		m_Impl->close();
		delete m_Impl;
		m_Impl = NULL;
	}

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// close socket
//////////////////////////////////////////////////////////////////////
void ServerSocket::close ()
	 throw ( Error )
{
	__BEGIN_TRY
		
	m_Impl->close();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// accept new connection
//////////////////////////////////////////////////////////////////////
Socket * ServerSocket::accept () 
	throw ( Error )
{
	__BEGIN_TRY
		
	Socket * Client = NULL;
	
	try {

		SocketImpl * impl = m_Impl->accept();

		if ( impl == NULL )
			throw UnknownError("impl == NULL");
		
		Client = new Socket(impl);	
//		Client->setNonBlocking();

	} catch ( NonBlockingIOException& ) {
		// ignore
	} catch ( ConnectException& ) {
		// ignore
	}

	return Client;

	__END_CATCH
}
