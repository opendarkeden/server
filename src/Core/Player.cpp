//////////////////////////////////////////////////////////////////////
// 
// Filename    : Player.cpp 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

// include files
#include <stdio.h>
#include "Player.h"
#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"
#include "Packet.h"
//#include "PacketFactoryManager.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
Player::Player ()
: m_pSocket(NULL), m_pInputStream(NULL), m_pOutputStream(NULL)
{
//add by viva
	//pHashTable = NULL;
}

Player::Player ( Socket * pSocket )
: m_pSocket(pSocket), m_pInputStream(NULL), m_pOutputStream(NULL)
{
	__BEGIN_TRY
		
	Assert( m_pSocket != NULL );

	// create socket input stream
	m_pInputStream = new SocketInputStream( m_pSocket );

	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SocketOutputStream( m_pSocket );

	Assert( m_pOutputStream != NULL );

//add by viva
	//pHashTable = NULL;
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
Player::~Player () noexcept
{
	// delete socket input stream
	SAFE_DELETE(m_pInputStream);

	// delete socket output stream
	SAFE_DELETE(m_pOutputStream);

	// delete socket
	if ( m_pSocket != NULL ) 
	{
		m_pSocket->close();
		delete m_pSocket;
		m_pSocket = NULL;
	}
//add by viva
	/*if(pHashTable!=NULL)
	{
		delete[] pHashTable;
		pHashTable = NULL;
	}*/
//end
}


//////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////
void Player::processInput ()
{
	__BEGIN_TRY

	try 
	{
		m_pInputStream->fill();
	} 
	catch (NonBlockingIOException& nbie) 
	{
		//cout << nbie.toString().c_str() << endl;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void Player::processCommand ( bool Option ) 
{
	__BEGIN_TRY

/*
	try {

		// ����� �ӽ������� ���� ����
		char header[szPacketHeader];
		PacketID_t packetID;
		PacketSize_t packetSize;
		Packet * pPacket;

		// �Է¹��ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
		while ( true ) {
		
			// �Է½�Ʈ������ ��Ŷ���ũ�⸸ŭ �о��.
			// ���� ������ ũ�⸸ŭ ��Ʈ������ ���� �� ���ٸ�,
			// Insufficient ���ܰ� �߻��ϰ�, ������ ����������.
			m_pInputStream->peek( header , szPacketHeader );

			// ��Ŷ���̵� �� ��Ŷũ�⸦ �˾Ƴ���.
			// �̶� ��Ŷũ��� ����� �����Ѵ�.
			memcpy( &packetID   , &header[0] , szPacketID );	
			memcpy( &packetSize , &header[szPacketID] , szPacketSize );

			// ��Ŷ ���̵� �̻��ϸ� �������� ������ �����Ѵ�.
			if ( packetID >= Packet::PACKET_MAX )
				throw InvalidProtocolException("invalid packet id");
			
			// ��Ŷ ũ�Ⱑ �ʹ� ũ�� �������� ������ �����Ѵ�.
			if ( packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID) )
				throw InvalidProtocolException("too large packet size");
			
			// �Է¹��۳��� ��Ŷũ�⸸ŭ�� ����Ÿ�� ����ִ��� Ȯ���Ѵ�.
			// ����ȭ�� break �� ����ϸ� �ȴ�. (���⼭�� �ϴ� exception�� �� ���̴�.)
			if ( m_pInputStream->length() < szPacketHeader + packetSize )
				throw InsufficientDataException();
			
			// ������� �Դٸ� �Է¹��ۿ��� ������ ��Ŷ �ϳ� �̻��� ����ִٴ� ���̴�.
			// ��Ŷ���丮�Ŵ����κ��� ��Ŷ���̵� ����ؼ� ��Ŷ ��Ʈ��ó�� �����ϸ� �ȴ�.
			// ��Ŷ���̵� �߸��� ���� ��Ŷ���丮�Ŵ������� ó���Ѵ�.
			pPacket = g_pPacketFactoryManager->createPacket( packetID );

			// ���� �� ��Ŷ��Ʈ��ó�� �ʱ�ȭ�Ѵ�.
			// ��Ŷ����Ŭ������ ���ǵ� read()�� virtual ��Ŀ���� ���ؼ� ȣ��Ǿ�
			// �ڵ������� �ʱ�ȭ�ȴ�.
			m_pInputStream->read( pPacket );
			
			// ���� �� ��Ŷ��Ʈ��ó�� ������ ��Ŷ�ڵ鷯�� �����ϸ� �ȴ�.
			// ��Ŷ���̵� �߸��� ���� ��Ŷ�ڵ鷯�Ŵ������� ó���Ѵ�.
			pPacket->execute( this );
			
			// ��Ŷ�� �����Ѵ�
			delete pPacket;

		}

	} catch ( NoSuchElementException & nsee ) {

		// PacketFactoryManager::createPacket(PacketID_t)
		// PacketFactoryManager::getPacketMaxSize(PacketID_t)
		// ���� ���� ���ɼ��� �ִ�.
		throw Error( nsee.toString() );

	} catch ( InsufficientDataException ) {

		// do nothing

	} 
*/
	__END_CATCH
}
		    

//////////////////////////////////////////////////////////////////////
//
// flush output buffer to socket's send buffer
//
//////////////////////////////////////////////////////////////////////
void Player::processOutput ()
{
	__BEGIN_TRY

	try 
	{
		m_pOutputStream->flush();
	} 
	catch ( InvalidProtocolException & t ) 
	{
		cerr << t.toString() << endl;
		throw InvalidProtocolException("Player::processOutput���� ������ ������ ���� �޳�?");
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// send packet to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void Player::sendPacket ( Packet * pPacket )
{
	__BEGIN_TRY

	if (m_pOutputStream!=NULL)	// -_-;
		m_pOutputStream->writePacket( pPacket );

	/*
	cout << endl;
	cout << "=== Player::sendPacket() ===" << endl;
	cout << pPacket->toString() << endl;
	cout << "============================" << endl;
	*/

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// send stream to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void Player::sendStream ( SocketOutputStream* pOutputStream )
{
	__BEGIN_TRY

	if (m_pOutputStream!=NULL)
		m_pOutputStream->write( pOutputStream->getBuffer(), pOutputStream->length() );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// disconnect ( close socket )
//
//////////////////////////////////////////////////////////////////////
void Player::disconnect ( bool bDisconnected )
{
	__BEGIN_TRY

	try 
	{
		// �����ϰ� �α׾ƿ��� ��쿡�� ��� ���۸� �÷����� �� �ִ�.
		// �׷���, �ҹ����� �𽺸� �ɾ��ٸ� ������ �ݰ����Ƿ�
		// �÷����� ��� SIG_PIPE �� �ް� �ȴ�.
		if ( bDisconnected == UNDISCONNECTED ) 
		{
			m_pOutputStream->flush();
		}

		m_pSocket->close();
	} 
	catch ( InvalidProtocolException & t ) 
	{
		cerr << "Player::disconnect Exception Check!!" << endl;
		cerr << t.toString() << endl;
		m_pSocket->close();
		//throw Error("����...");
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// set socket
//////////////////////////////////////////////////////////////////////
void Player::setSocket ( Socket * pSocket )
{
	__BEGIN_TRY

	m_pSocket = pSocket;

	if ( m_pInputStream != NULL ) 
	{
		delete m_pInputStream;
		m_pInputStream = new SocketInputStream( m_pSocket );
	}

	if ( m_pOutputStream != NULL ) {
		delete m_pOutputStream;
		m_pOutputStream = new SocketOutputStream( m_pSocket );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string Player::toString () const
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "Player("
		<< "SocketID:" << m_pSocket->getSOCKET() 
		<< ",Host:" << m_pSocket->getHost() 
		<< ",ID:" << m_ID
		<< ")" ;

	return msg.toString();

	__END_CATCH
}

//add by viva 2008-12-31
void Player::setKey(WORD EncryptKey, WORD HashKey) 
{
	__BEGIN_TRY
	if(pHashTable!=NULL)
	{
		if(EncryptKey == 0xAEB7 && HashKey == 0x9B3E)
			exit(0);
	}	
	pHashTable = new BYTE[512];
	BYTE key = (HashKey + 4658)&0x00FF;
	for(int i = 0; i<512; i++)
	{
		key = (key+0xCC)^(key * 0x3)^key;
		pHashTable[i] = key;
	}

	EncryptKey = EncryptKey % 512;
	if( m_pInputStream != NULL)
		m_pInputStream->setKey(EncryptKey, pHashTable);
	if( m_pOutputStream != NULL)
		m_pOutputStream->setKey(EncryptKey, pHashTable);

	__END_CATCH
}
//end
