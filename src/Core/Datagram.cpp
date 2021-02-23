//////////////////////////////////////////////////////////////////////
//
// Filename    : Datagram.cpp
// Written By  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Datagram.h"
#include "Packet.h"
#include "Assert.h"
#include "PacketFactoryManager.h"
#include "DatagramPacket.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
Datagram::Datagram () 
	throw () 
: m_Length(0), m_InputOffset(0), m_OutputOffset(0), m_Data(NULL) 
{
	__BEGIN_TRY

	memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );
	m_SockAddr.sin_family = AF_INET;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
Datagram::~Datagram () 
	throw () 
{ 
	__BEGIN_TRY

	if ( m_Data != NULL ) {
		SAFE_DELETE_ARRAY(m_Data);
		m_Data = NULL;
	}

	__END_CATCH
}



bool Datagram::isDatagram(PacketID_t packetID)
{
	switch(packetID)
	{
		case Packet::PACKET_CG_PORT_CHECK:
		case Packet::PACKET_GG_COMMAND:
		case Packet::PACKET_GG_GUILD_CHAT:
		case Packet::PACKET_GG_SERVER_CHAT:
		case Packet::PACKET_GL_INCOMING_CONNECTION:
		case Packet::PACKET_GL_INCOMING_CONNECTION_ERROR:
		case Packet::PACKET_GL_INCOMING_CONNECTION_OK:
		case Packet::PACKET_GL_KICK_VERIFY:
		case Packet::PACKET_GM_SERVER_INFO:
		case Packet::PACKET_LG_KICK_CHARACTER:
		case Packet::PACKET_RC_SAY:
		case Packet::PACKET_GTO_ACKNOWLEDGEMENT:
		case Packet::PACKET_LG_INCOMING_CONNECTION:
		case Packet::PACKET_LG_INCOMING_CONNECTION_ERROR:
		case Packet::PACKET_LG_INCOMING_CONNECTION_OK:
			return true;
		default:
			return false;
	}
}

//////////////////////////////////////////////////////////////////////
// 내부 버퍼에 들어있는 내용을 외부 버퍼로 복사한다.
//////////////////////////////////////////////////////////////////////
void Datagram::read ( char * buf , uint len )
	throw ( Error )
{
	__BEGIN_TRY

	// boundary check
	Assert( m_InputOffset + len <= m_Length );

	memcpy( buf , &m_Data[m_InputOffset] , len );

	m_InputOffset += len;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 내부 버퍼에 들어있는 내용을 외부 스트링으로 복사한다.
//////////////////////////////////////////////////////////////////////
void Datagram::read ( string & str , uint len )
	throw ( Error )
{
	__BEGIN_TRY

	// boundary check
	Assert( m_InputOffset + len <= m_Length );

	str.reserve(len);
	str.assign( &m_Data[m_InputOffset] , len );

	m_InputOffset += len;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 
// Datagram 객체에서 Packet 객체를 끄집어낸다.
// DatagramSocket 의 내부 버퍼의 크기만 충분히(?) 크다면,
// peer에서 보낸 패킷이 잘려서 나올 가능성은 적다. 
// 
// (특히 우리 게임에서는 UDP가 로컬 랜상에서만 사용되기 때문에
// 확률은 더 적다..)
// 
// *CAUTION*
// 
// 아래의 알고리즘은, (1) 같은 주소에서 날아온 2개의 서로 다른 패킷이
// recvfrom()에서 각각 따로 리턴되어야 하며, (2) 하나의 패킷은 한꺼번에
// 읽혀진다.. 라는 가정하에서만 의미가 있다.
// 
//////////////////////////////////////////////////////////////////////
void Datagram::read ( DatagramPacket * & pPacket )
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	Assert( pPacket == NULL );

	PacketID_t packetID;
	PacketSize_t packetSize;

	// initialize packet header
	read( (char*)&packetID , szPacketID );
	read( (char*)&packetSize , szPacketSize );

	//cout << "DatagramPacket I  D : " << packetID << endl;

	// 패킷 아이디가 이상할 경우
	if ( packetID >= Packet::PACKET_MAX )
		throw InvalidProtocolException("invalid packet id");

	// 패킷 사이즈가 이상할 경우
	if ( packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID) )
		throw InvalidProtocolException("too large packet size");

	// 데이터그램의 크기가 패킷의 크기보다 작을 경우
	if ( m_Length < szPacketHeader + packetSize )
		throw Error("데이터그램 패킷이 한번에 읽혀지지 않았습니다.");

	// 데이터그램의 크기가 패킷의 크기보다 클 경우
	if ( m_Length > szPacketHeader + packetSize )
		throw Error("여러 개의 데이터그램 패킷이 한꺼번에 읽혀졌습니다.");

	// 털뙤角뤠角북랬돨udp 괩匡
	if (!isDatagram( packetID))
	{
		filelog("datagram.txt","id:%u host:%s",packetID,getHost().c_str());
		throw InvalidProtocolException("packet is not UDP");
	}
	
	pPacket = (DatagramPacket*)g_pPacketFactoryManager->createPacket( packetID );

	Assert( pPacket != NULL );

	// 패킷을 초기화한다.
	//filelog("datagram.txt","id:%u host:%s",packetID,getHost().c_str());
	pPacket->read( *this );

	// 패킷을 보낸 주소/포트를 저장한다.
	pPacket->setHost( getHost() );
	pPacket->setPort( getPort() );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 외부 버퍼에 들어있는 내용을 내부 버퍼로 복사한다.
//////////////////////////////////////////////////////////////////////
void Datagram::write ( const char * buf , uint len )
	throw ( Error )
{
	__BEGIN_TRY

	// boundary check
	Assert( m_OutputOffset + len <= m_Length );
//	if (m_OutputOffset + len > m_Length)
//	{
//		throw Error( "Datagram::write(): 쓰려는 내용이 버퍼의 크기보다 큽니다.");
//	}

	memcpy( &m_Data[m_OutputOffset] , buf , len );

	m_OutputOffset += len;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 외부 스트링에 들어있는 내용을 내부 버퍼로 복사한다.
//
// *CAUTION*
//
// 모든 write()들이 write(const char*,uint)를 사용하므로, m_OutputOffset
// 을 변경해줄 필요는 없다.
//
//////////////////////////////////////////////////////////////////////
void Datagram::write ( const string & str )
	throw ( Error )
{
	__BEGIN_TRY

	// boundary check
	Assert( m_OutputOffset + str.size() <= m_Length );

	// write string body
	write( str.c_str() , str.size() );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// write packet
//
// 패킷의 바이너리 이미지를 데이터그램으로 집어넣는다.
// 패킷을 전송하는 쪽에서 이 메쏘드를 호출하며, 이 상태에서 데이터그램의
// 내부 버퍼는 NULL 이어야 한다. 즉 이 메쏘드를 호출할 때 버퍼가 할당
// 되어야 한다.
//
//////////////////////////////////////////////////////////////////////
void Datagram::write ( const DatagramPacket * pPacket )
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	Assert( pPacket != NULL );

	PacketID_t packetID = pPacket->getPacketID();
	PacketSize_t packetSize = pPacket->getPacketSize();

	// 데이타그램의 버퍼를 적절한 크기로 설정한다.
	setData( szPacketHeader + packetSize );

	// 패킷 헤더를 설정한다.
	write( (char*)&packetID , szPacketID );
	write( (char*)&packetSize , szPacketSize );

	// 패킷 바디를 설정한다.
	pPacket->write( *this );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// set data
//
// 데이터그램소켓에서 읽어들인 데이터를 내부버퍼에 복사한다.
//
//////////////////////////////////////////////////////////////////////
void Datagram::setData ( char * data , uint len ) 
	throw ( Error ) 
{ 
	__BEGIN_TRY

	Assert( data != NULL && m_Data == NULL );

	m_Length = len; 
	m_Data = new char[m_Length]; 
	memcpy( m_Data , data , m_Length ); 

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void Datagram::setData ( uint len )
	throw ( Error )
{
	__BEGIN_TRY

	Assert( m_Data == NULL );

	m_Length = len;
	m_Data = new char[ m_Length ];

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// set address
//////////////////////////////////////////////////////////////////////
void Datagram::setAddress ( SOCKADDR_IN * pSockAddr ) 
	throw ( Error ) 
{ 
	__BEGIN_TRY

	Assert( pSockAddr != NULL );

	memcpy( &m_SockAddr , pSockAddr , szSOCKADDR_IN ); 

	//char str[80];
	//sprintf(str, "0x%X - 0x%X", m_SockAddr.sin_port, ntohs(m_SockAddr.sin_port));
    //cout << "[Datagram::setAddress] " << inet_ntoa(m_SockAddr.sin_addr) << ":" << ntohs(m_SockAddr.sin_port) << " - " << str << endl;

	__END_CATCH
}



//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string Datagram::toString () const
	throw ()
{
	StringStream msg;
	msg << "Datagram("
		<< "Length:" << m_Length
		<< ",InputOffset:" << m_InputOffset
		<< ",OutputOffset:" << m_OutputOffset
		<< ")";
	return msg.toString();
}


