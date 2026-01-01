//////////////////////////////////////////////////////////////////////
//
// Filename   : DatagramSocket.cpp
// Written By : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "DatagramSocket.h"
#include "Assert.h"
#include "FileAPI.h"
#include <exception>

//////////////////////////////////////////////////////////////////////
//
// constructor for UDP Client Socket
//
// UDP Ŭ���̾�Ʈ ������ ���� nonamed ���ϸ� ������ �θ� �ȴ�.
// �ֳ��ϸ�, ������ send�� ������ Datagram�� �ּҸ� �����صθ�
// �Ǳ� �����̴�.
//
//////////////////////////////////////////////////////////////////////
DatagramSocket::DatagramSocket () 
: m_SocketID(INVALID_SOCKET)
{
	__BEGIN_TRY 

	__BEGIN_DEBUG
	m_SocketID = SocketAPI::socket_ex( AF_INET , SOCK_DGRAM , 0 );
	__END_DEBUG

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// constructor for UDP Server Socket
//
// UDP ���� ������ ������ �����ϰ�, port �� ���ε���Ű�� �غ� �Ϸ�ȴ�.
//
//////////////////////////////////////////////////////////////////////
DatagramSocket::DatagramSocket ( uint port ) 
: m_SocketID(INVALID_SOCKET)
{
	__BEGIN_TRY 

	m_SocketID = SocketAPI::socket_ex( AF_INET , SOCK_DGRAM , 0 );

	// clear memory
	memset( &m_SockAddr , 0 , szSOCKADDR_IN );
	m_SockAddr.sin_family      = AF_INET;
	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_SockAddr.sin_port        = htons(port);
//add by viva
//	cout<<"DatagramSocket Bind Port:"<<port<<endl;
	// bind address to socket
	SocketAPI::bind_ex( m_SocketID , (SOCKADDR*)&m_SockAddr , szSOCKADDR_IN );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
DatagramSocket::~DatagramSocket () noexcept
{
	try
	{
		if ( m_SocketID != INVALID_SOCKET )
			FileAPI::close_ex( m_SocketID );
	}
	catch (const std::exception&)
	{
		// ignore during teardown
	}
}


//////////////////////////////////////////////////////////////////////
// send datagram to peer
//////////////////////////////////////////////////////////////////////
uint DatagramSocket::send ( Datagram * pDatagram )
{
	__BEGIN_TRY 

	Assert( pDatagram != NULL );
	try {

	int nSent = SocketAPI::sendto_ex( m_SocketID , pDatagram->getData() , pDatagram->getLength() , 0 , pDatagram->getAddress() , szSOCKADDR_IN );

	return (uint)nSent;

	} catch ( ConnectException & t ) {
		cout <<"DatagramSocket::send Exception Check!" << endl;
		cout << t.toString() << endl;
		throw ConnectException("DatagramSocket�� ������ ������");
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// receive datagram from peer
//
// ���࿡ �� Ŭ������ blocking ���� ����Ѵٸ�, (�� select �������)
// �Ƹ��� nReceived �� 0 ������ ���� ��������� �Ǵܵȴ�.
//
//////////////////////////////////////////////////////////////////////
Datagram * DatagramSocket::receive ()
{
	__BEGIN_TRY 

	Datagram * pDatagram = NULL;

	SOCKADDR_IN SockAddr;
	uint _szSOCKADDR_IN = szSOCKADDR_IN;

	// ���� ���ۿ��ٰ� �����صд�.
	int nReceived = SocketAPI::recvfrom_ex( m_SocketID , m_Buffer , DATAGRAM_SOCKET_BUFFER_LEN , 0 , (SOCKADDR*)&SockAddr , &_szSOCKADDR_IN );

	if ( nReceived > 0 ) {

		pDatagram = new Datagram();
		pDatagram->setData( m_Buffer , nReceived );
		pDatagram->setAddress( &SockAddr );

	}

	return pDatagram;

	__END_CATCH
}
