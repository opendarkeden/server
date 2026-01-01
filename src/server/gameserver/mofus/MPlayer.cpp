/////////////////////////////////////////////////////////////////////////////
// Filename : MPlayer.cpp
// Desc		: ���۽� ��� ��ü
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "MPlayer.h"
#include "MPacket.h"
#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "MPacketManager.h"
#include "Assert.h"
#include "MJob.h"
#include "Properties.h"

// include packet header
#include "PKTConnectAsk.h"
#include "PKTLogout.h"
#include "PKTUserInfo.h"
#include "PKTReceiveOK.h"
#include "PKTResult.h"
#include "PKTSError.h"

#include <unistd.h>

const int defaultMPlayerInputStreamSize = 10240;
const int defaultMPlayerOutputStreamSize = 10240;

// constructor
MPlayer::MPlayer( MJob* pJob )
{
	Assert( pJob != NULL );

	m_pSocket = NULL;
	m_pInputStream = NULL;
	m_pOutputStream = NULL;

	m_pJob = pJob;
}

// destructor
MPlayer::~MPlayer()
{
	// delete socket input stream
	SAFE_DELETE( m_pInputStream );

	// delete socket output stream
	SAFE_DELETE( m_pOutputStream );

	// delete socket
	if ( m_pSocket != NULL )
	{
		m_pSocket->close();
		SAFE_DELETE( m_pSocket );

		filelog( MOFUS_LOG_FILE, "Close socket" );
	}
}

void MPlayer::processInput()
{
	try
	{
		m_pInputStream->fill();
	}
	catch ( NonBlockingIOException& nibe )
	{
	}
}

void MPlayer::processOutput()
{
	try
	{
		m_pOutputStream->flush();
	}
	catch ( InvalidProtocolException& )
	{
		throw DisconnectException( "�̻��� ��Ŷ��" );
	}
}

void MPlayer::processCommand()
{
	__BEGIN_TRY

	try
	{
		// �Է� ���ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
		while ( true )
		{
			// �ϴ� ��Ŷ�� ������� ID �� �о�´�.
			char header[szMPacketHeader];
			MPacketSize_t packetSize;
			MPacketID_t packetID;

			if ( !m_pInputStream->peek( &header[0], szMPacketHeader ) )
				return;

			memcpy( &packetSize, &header[0], szMPacketSize );
			memcpy( &packetID, &header[szMPacketSize], szMPacketID );

			//packetSize = ntohl( packetSize );
			//packetID = ntohl( packetID );

			// ��Ŷ ���̵� �̻��ϸ� �������� ����
			if ( !g_pMPacketManager->hasHandler( packetID ) )
			{
				filelog( MOFUS_ERROR_FILE, "Invalid PacketID : %d", packetID );
				throw ProtocolException( "Invalid PacketID" );
			}

			// ��Ŷ ������ Ȯ��
			if ( g_pMPacketManager->getPacketSize( packetID ) != packetSize )
			{
				filelog( MOFUS_ERROR_FILE, "Invalid PacketSize : %d, expected size : %d", packetSize, g_pMPacketManager->getPacketSize(packetID) );
				throw ProtocolException( "Invalid PacketSize" );
			}

			// ������ �ϳ��� ��Ŷ�� ����ִ��� Ȯ��
			if ( m_pInputStream->length() < (unsigned int)( packetSize + szMPacketSize ) )
				return;

			// ��Ŷ�� ����
			MPacket* pPacket = g_pMPacketManager->createPacket( packetID );
			
			// ��Ŷ ��ü�� ���� ������ ä���.
			pPacket->read( *m_pInputStream );

			// ��Ŷ�� �ش� �ڵ鷯�� �����Ѵ�.
			g_pMPacketManager->execute( this, pPacket );
		}
	}
	catch ( const InsufficientDataException& )
	{
		// ����
	}

	__END_CATCH
}

void MPlayer::sendPacket( MPacket* pPacket )
{
	Assert( pPacket != NULL );

	pPacket->write( *m_pOutputStream );
}

void MPlayer::connect()
{
	// ����Ǿ� ���� �ʾƾ��Ѵ�.
	Assert( m_pSocket == NULL );

	// ���۽� ������ IP �� Port �� �����´�.
	const string	MofusIP = g_pConfig->getProperty( "MofusIP" );
	uint 			MofusPort = g_pConfig->getPropertyInt( "MofusPort" );

	try
	{
		// create socket
		m_pSocket = new Socket( MofusIP, MofusPort );

		// connect
		m_pSocket->connect();

		// make nonblocking socket
		m_pSocket->setNonBlocking(true);

		// make no-linger socket
		m_pSocket->setLinger(0);

		// read/write �� ����(stream) �� �����Ѵ�.
		m_pInputStream = new SocketInputStream( m_pSocket, defaultMPlayerInputStreamSize );
		m_pOutputStream = new SocketOutputStream( m_pSocket, defaultMPlayerOutputStreamSize );

		cout << "connection to Mofus server established - "
			 << MofusIP.c_str() << ":" << MofusPort << endl;
		filelog( MOFUS_LOG_FILE, "----- connection extablished(%s:%u) -----", MofusIP.c_str(), MofusPort );
	}
	catch ( Throwable& t )
	{
		cout << "connect to Mofus server fail - "
			 << MofusIP.c_str() << ":" << MofusPort << endl;
		filelog( MOFUS_LOG_FILE, "----- connecti fail(%s:%u) -----", MofusIP.c_str(), MofusPort );

		// ������ �����Ѵ�.
		try
		{
			SAFE_DELETE( m_pSocket );
		}
		catch ( Throwable& t )
		{
			filelog( MOFUS_ERROR_FILE, "[socket release error] %s", t.toString().c_str() );
		}

		// ���� ���� �õ� �ð�
		usleep( 1000000 );	// 1��
	}
}

void MPlayer::disconnect( bool bDisconnected )
{
	__BEGIN_TRY

	try
	{
		if ( bDisconnected == UNDISCONNECTED )
		{
			m_pOutputStream->flush();
		}

		m_pSocket->close();
	}
	catch ( InvalidProtocolException& t )
	{
		cerr << "MPlayer::disconnect() exception occur!!" << endl;
		cerr << t.toString() << endl;
		m_pSocket->close();
	}

	__END_CATCH
}

void MPlayer::process()
{
	__BEGIN_TRY

	Assert( m_pJob != NULL );

	try
	{
		while ( true )
		{
			usleep(100);

			// ���� �Ǿ� ���� �ʴٸ� ������ �õ��Ѵ�.
			if ( m_pSocket == NULL )
			{
				connect();

				// ���� Ȯ�� ��Ŷ�� ������.
				if ( m_pSocket != NULL )
					sendConnectAsk();
			}

			// ������ ����Ǿ� �ִٸ� ������� ó���Ѵ�.
			if ( m_pSocket != NULL )
			{
				__BEGIN_TRY

				if ( getSocket()->getSockError() )
				{
					filelog( MOFUS_ERROR_FILE, "[MPlayer socket error]" );

					// ������ ���� ���� �����ϰ�, ����� ���� �����.
					m_pSocket->close();
					SAFE_DELETE( m_pSocket );
					SAFE_DELETE( m_pInputStream );
					SAFE_DELETE( m_pOutputStream );

					// ��ƾ�� ����������.
					cout << "return" << endl;
					return;
				}
				else
				{
					// �۾��� �� ������ ���� ��Ŷ�� �� ���´ٸ� ��ƾ�� ���� ������.
					if ( m_pJob->isEnd() && m_pOutputStream->isEmpty() )
					{
						// ������ ���� ���� �����ϰ�, ����� ���� �����.
						m_pSocket->close();
						SAFE_DELETE( m_pSocket );
						SAFE_DELETE( m_pInputStream );
						SAFE_DELETE( m_pOutputStream );

						// ��ƾ�� ����������.
						cout << "return" << endl;
						return;
					}

					try
					{
						// ���� ����� ó�� �� ��Ŷ ó��
						processInput();
						processCommand();
						processOutput();
					}
					catch ( ConnectException& ce )
					{
						filelog( MOFUS_LOG_FILE, "----- connection close" );

						// ������ �����.
						// ������ �ݰ�, ����� ���� ����� ����������
						m_pSocket->close();
						SAFE_DELETE( m_pSocket );
						SAFE_DELETE( m_pInputStream );
						SAFE_DELETE( m_pOutputStream );

						cout << "return" << endl;
						return;
					}
					catch ( Throwable& t )
					{
						filelog( MOFUS_ERROR_FILE, "[MPlayer process error]" );

						// ������ �ݰ�, ����� ���� ����� ����������
						m_pSocket->close();
						SAFE_DELETE( m_pSocket );
						SAFE_DELETE( m_pInputStream );
						SAFE_DELETE( m_pOutputStream );

						cout << "return" << endl;
						return;
					}
				}

				__END_CATCH
			}
		}
	}
	catch ( Throwable& t )
	{
		filelog( "MPlayerManager.log" , "MPlayerManager::run() %s", t.toString().c_str() );
	}

	__END_CATCH
}

void MPlayer::sendConnectAsk()
{
	PKTConnectAsk pkt;

	pkt.setOnGameCode( 1 );

	sendPacket( &pkt );

	cout << "--------------------------------------------------" << endl;
	cout << "SEND [" << m_pJob->getName() << "] ConnectAsk" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "SEND [%s] ConnectAsk", m_pJob->getName().c_str() );
	filelog( MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str() );
}

void MPlayer::sendLogout()
{
	PKTLogout pkt;

	sendPacket( &pkt );

	cout << "--------------------------------------------------" << endl;
	cout << "SEND [" << m_pJob->getName() << "] Logout" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "SEND [%s] Logout", m_pJob->getName().c_str() );
	filelog( MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str() );
}

void MPlayer::sendUserInfo()
{
	PKTUserInfo pkt;

	pkt.setCellNum( m_pJob->getCellNum() );

	sendPacket( &pkt );

	cout << pkt.toString() << endl;

	cout << "--------------------------------------------------" << endl;
	cout << "SEND [" << m_pJob->getName() << "] UserInfo" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "SEND [%s] UserInfo(cellnum:%s)", m_pJob->getName().c_str(), m_pJob->getCellNum().c_str() );
	filelog( MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str() );
}

void MPlayer::sendReceiveOK()
{
	PKTReceiveOK pkt;

	sendPacket( &pkt );

	cout << "--------------------------------------------------" << endl;
	cout << "SEND [" << m_pJob->getName() << "] ReceiveOK" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "SEND [%s] ReceiveOK", m_pJob->getName().c_str() );
	filelog( MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str() );
}

void MPlayer::sendResult()
{
	PKTResult pkt;

	sendPacket( &pkt );

	cout << "--------------------------------------------------" << endl;
	cout << "SEND [" << m_pJob->getName() << "] Result" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "SEND [%s] Result", m_pJob->getName().c_str() );
	filelog( MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str() );
}

void MPlayer::sendSError( int errorCode )
{
	PKTSError pkt;

	pkt.setErrorCode( errorCode );

	sendPacket( &pkt );

	cout << "--------------------------------------------------" << endl;
	cout << "SEND [" << m_pJob->getName() << "] SError" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "SEND [%s] SError", m_pJob->getName().c_str() );
	filelog( MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str() );
}

void MPlayer::addPowerPoint( int point )
{
	Assert( m_pJob != NULL );

	m_pJob->addPowerPoint( point );
}

void MPlayer::setErrorCode( int errorCode )
{
	Assert( m_pJob != NULL );

	m_pJob->setErrorCode( errorCode );
}

void MPlayer::setEnd( bool bEnd )
{
	Assert( m_pJob != NULL );

	m_pJob->setEnd( bEnd );
}

