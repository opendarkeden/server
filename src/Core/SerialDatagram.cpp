//////////////////////////////////////////////////////////////////////
//
// Filename    : SerialDatagram.cpp
// Written By  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

// include files
#include "SerialDatagram.h"
#include "Assert.h"
#include "PacketFactoryManager.h"
#include "SerialDatagramPacket.h"
#include <exception>

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
SerialDatagram::SerialDatagram () 
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
SerialDatagram::~SerialDatagram () noexcept
{ 
	try
	{
		if ( m_Data != NULL ) {
			SAFE_DELETE_ARRAY(m_Data);
			m_Data = NULL;
		}
	}
	catch (const std::exception&)
	{
		// ignore
	}
}


//////////////////////////////////////////////////////////////////////
// ���� ���ۿ� ����ִ� ������ �ܺ� ���۷� �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void SerialDatagram::read ( char * buf , uint len )
{
	__BEGIN_TRY

	// boundary check
	Assert( m_InputOffset + len <= m_Length );

	memcpy( buf , &m_Data[m_InputOffset] , len );

	m_InputOffset += len;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// ���� ���ۿ� ����ִ� ������ �ܺ� ��Ʈ������ �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void SerialDatagram::read ( string & str , uint len )
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
// SerialDatagram ��ü���� Packet ��ü�� �������.
// SerialDatagramSocket �� ���� ������ ũ�⸸ �����(?) ũ�ٸ�,
// peer���� ���� ��Ŷ�� �߷��� ���� ���ɼ��� ����. 
// 
// (Ư�� �츮 ���ӿ����� UDP�� ���� ���󿡼��� ���Ǳ� ������
// Ȯ���� �� ����..)
// 
// *CAUTION*
// 
// �Ʒ��� �˰�������, (1) ���� �ּҿ��� ���ƿ� 2���� ���� �ٸ� ��Ŷ��
// recvfrom()���� ���� ���� ���ϵǾ�� �ϸ�, (2) �ϳ��� ��Ŷ�� �Ѳ�����
// ��������.. ��� �����Ͽ����� �ǹ̰� �ִ�.
// 
//////////////////////////////////////////////////////////////////////
void SerialDatagram::read ( SerialDatagramPacket * & pPacket )
{
	__BEGIN_TRY

	Assert( pPacket == NULL );

	PacketID_t packetID;
	PacketSize_t packetSize;
	uint serial;

	// initialize packet header
	read( (char*)&packetID , szPacketID );
	read( (char*)&packetSize , szPacketSize );
	read( (char*)&serial, szuint );

	cout << "SerialDatagramPacket I  D : " << packetID << endl;

	// ��Ŷ ���̵� �̻��� ���
	if ( packetID >= Packet::PACKET_MAX )
		throw InvalidProtocolException("invalid packet id");

	// ��Ŷ ����� �̻��� ���
	if ( packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID) )
		throw InvalidProtocolException("too large packet size");

	// �����ͱ׷��� ũ�Ⱑ ��Ŷ�� ũ�⺸�� ���� ���
	if ( m_Length < szPacketHeader + packetSize )
		throw Error("�����ͱ׷� ��Ŷ�� �ѹ��� �������� �ʾҽ��ϴ�.");

	// �����ͱ׷��� ũ�Ⱑ ��Ŷ�� ũ�⺸�� Ŭ ���
	if ( m_Length > szPacketHeader + packetSize )
		throw Error("���� ���� �����ͱ׷� ��Ŷ�� �Ѳ����� ���������ϴ�.");

	// ��Ŷ�� �����Ѵ�.
	pPacket = (SerialDatagramPacket*)g_pPacketFactoryManager->createPacket( packetID );

	Assert( pPacket != NULL );

	// �ø����� �ִ´�
	pPacket->setSerial( serial );

	// ��Ŷ�� �ʱ�ȭ�Ѵ�.
	pPacket->read( *this );

	// ��Ŷ�� ���� �ּ�/��Ʈ�� �����Ѵ�.
	pPacket->setHost( getHost() );
	pPacket->setPort( getPort() );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �ܺ� ���ۿ� ����ִ� ������ ���� ���۷� �����Ѵ�.
//////////////////////////////////////////////////////////////////////
void SerialDatagram::write ( const char * buf , uint len )
{
	__BEGIN_TRY

	// boundary check
	Assert( m_OutputOffset + len <= m_Length );
//	if (m_OutputOffset + len > m_Length)
//	{
//		throw Error( "SerialDatagram::write(): ������ ������ ������ ũ�⺸�� Ů�ϴ�.");
//	}

	memcpy( &m_Data[m_OutputOffset] , buf , len );

	m_OutputOffset += len;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// �ܺ� ��Ʈ���� ����ִ� ������ ���� ���۷� �����Ѵ�.
//
// *CAUTION*
//
// ��� write()���� write(const char*,uint)�� ����ϹǷ�, m_OutputOffset
// �� �������� �ʿ�� ����.
//
//////////////////////////////////////////////////////////////////////
void SerialDatagram::write ( const string & str )
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
// ��Ŷ�� ���̳ʸ� �̹����� �����ͱ׷����� ����ִ´�.
// ��Ŷ�� �����ϴ� �ʿ��� �� �޽�带 ȣ���ϸ�, �� ���¿��� �����ͱ׷���
// ���� ���۴� NULL �̾�� �Ѵ�. �� �� �޽�带 ȣ���� �� ���۰� �Ҵ�
// �Ǿ�� �Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void SerialDatagram::write ( const SerialDatagramPacket * pPacket )
{
	__BEGIN_TRY

	Assert( pPacket != NULL );

	PacketID_t packetID = pPacket->getPacketID();
	PacketSize_t packetSize = pPacket->getPacketSize();
	uint serial = pPacket->getSerial();

	// ����Ÿ�׷��� ���۸� ������ ũ��� �����Ѵ�.
	setData( szPacketHeader + packetSize );

	// ��Ŷ ����� �����Ѵ�.
	write( (char*)&packetID , szPacketID );
	write( (char*)&packetSize , szPacketSize );
	write( (char*)&serial, szuint );

	// ��Ŷ �ٵ� �����Ѵ�.
	pPacket->write( *this );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// set data
//
// �����ͱ׷����Ͽ��� �о���� �����͸� ���ι��ۿ� �����Ѵ�.
//
//////////////////////////////////////////////////////////////////////
void SerialDatagram::setData ( char * data , uint len ) 
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
void SerialDatagram::setData ( uint len )
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
void SerialDatagram::setAddress ( SOCKADDR_IN * pSockAddr ) 
{ 
	__BEGIN_TRY

	Assert( pSockAddr != NULL );

	memcpy( &m_SockAddr , pSockAddr , szSOCKADDR_IN ); 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string SerialDatagram::toString () const
{
	StringStream msg;
	msg << "SerialDatagram("
		<< "Length:" << m_Length
		<< ",InputOffset:" << m_InputOffset
		<< ",OutputOffset:" << m_OutputOffset
		<< ")";
	return msg.toString();
}
