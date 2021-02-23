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

//////////////////////////////////////////////////////////////////////
//
// constructor for UDP Client Socket
//
// UDP 클라이언트 소켓은 단지 nonamed 소켓만 생성해 두면 된다.
// 왜냐하면, 서버로 send할 때마다 Datagram의 주소를 지정해두면
// 되기 때문이다.
//
//////////////////////////////////////////////////////////////////////
DatagramSocket::DatagramSocket () 
	throw ( Error, BindException )
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
// UDP 서버 소켓은 소켓을 생성하고, port 를 바인딩시키면 준비가 완료된다.
//
//////////////////////////////////////////////////////////////////////
DatagramSocket::DatagramSocket ( uint port ) 
	throw ( Error, BindException )
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
DatagramSocket::~DatagramSocket ()
	throw ( Error )
{
	__BEGIN_TRY
	
	if ( m_SocketID != INVALID_SOCKET )
		FileAPI::close_ex( m_SocketID );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// send datagram to peer
//////////////////////////////////////////////////////////////////////
uint DatagramSocket::send ( Datagram * pDatagram )
	throw ( ConnectException , Error )
{
	__BEGIN_TRY 

	Assert( pDatagram != NULL );
	try {

	int nSent = SocketAPI::sendto_ex( m_SocketID , pDatagram->getData() , pDatagram->getLength() , 0 , pDatagram->getAddress() , szSOCKADDR_IN );

	return (uint)nSent;

	} catch ( ConnectException & t ) {
		cout <<"DatagramSocket::send Exception Check!" << endl;
		cout << t.toString() << endl;
		throw ConnectException("DatagramSocket의 상위로 던진다");
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// receive datagram from peer
//
// 만약에 이 클래스를 blocking 으로 사용한다면, (즉 select 기반으로)
// 아마도 nReceived 가 0 이하인 경우는 없으리라고 판단된다.
//
//////////////////////////////////////////////////////////////////////
Datagram * DatagramSocket::receive ()
	throw ( ConnectException , Error )
{
	__BEGIN_TRY 

	Datagram * pDatagram = NULL;

	SOCKADDR_IN SockAddr;
	uint _szSOCKADDR_IN = szSOCKADDR_IN;

	// 내부 버퍼에다가 복사해둔다.
	int nReceived = SocketAPI::recvfrom_ex( m_SocketID , m_Buffer , DATAGRAM_SOCKET_BUFFER_LEN , 0 , (SOCKADDR*)&SockAddr , &_szSOCKADDR_IN );

	if ( nReceived > 0 ) {

		pDatagram = new Datagram();
		pDatagram->setData( m_Buffer , nReceived );
		pDatagram->setAddress( &SockAddr );

	}

	return pDatagram;

	__END_CATCH
}
