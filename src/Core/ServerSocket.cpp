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
: m_Impl(NULL)
{
	__BEGIN_TRY
		
	// create socket implementation object
	m_Impl = new SocketImpl(port);
	
	// create socket
	m_Impl->create();
	
	// reuse address before Bind()
	// ���ε� �ϱ� ���� �ּ� ����� �ý��ۿ� �˷��� �Ѵ�.
	m_Impl->setReuseAddr();
	
	// bind address to socket
	// �̹� port�� m_Impl�� ����Ǿ� �����Ƿ�, �Ķ���;��� Bind()�� ȣ���ص� �ȴ�.
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
ServerSocket::~ServerSocket () noexcept
{
	if ( m_Impl != NULL ) 
	{
		m_Impl->close();
		delete m_Impl;
		m_Impl = NULL;
	}
}
	

//////////////////////////////////////////////////////////////////////
// close socket
//////////////////////////////////////////////////////////////////////
void ServerSocket::close ()
{
	__BEGIN_TRY
		
	m_Impl->close();

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// accept new connection
//////////////////////////////////////////////////////////////////////
Socket * ServerSocket::accept () 
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
