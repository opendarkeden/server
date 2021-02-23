/////////////////////////////////////////////////////////////////////////////
// Filename : MPlayer.cpp
// Desc		: 모퍼스 통신 객체
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
	throw ( Error )
{
	Assert( pJob != NULL );

	m_pSocket = NULL;
	m_pInputStream = NULL;
	m_pOutputStream = NULL;

	m_pJob = pJob;
}

// destructor
MPlayer::~MPlayer()
	throw ( Error )
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
	throw ( IOException, Error )
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
	throw ( IOException, Error )
{
	try
	{
		m_pOutputStream->flush();
	}
	catch ( InvalidProtocolException& )
	{
		throw DisconnectException( "이상한 패킷임" );
	}
}

void MPlayer::processCommand()
	throw ( IOException, Error )
{
	__BEGIN_TRY

	try
	{
		// 입력 버퍼에 들어있는 완전한 패킷들을 모조리 처리한다.
		while ( true )
		{
			// 일단 패킷의 사이즈와 ID 를 읽어온다.
			char header[szMPacketHeader];
			MPacketSize_t packetSize;
			MPacketID_t packetID;

			if ( !m_pInputStream->peek( &header[0], szMPacketHeader ) )
				return;

			memcpy( &packetSize, &header[0], szMPacketSize );
			memcpy( &packetID, &header[szMPacketSize], szMPacketID );

			//packetSize = ntohl( packetSize );
			//packetID = ntohl( packetID );

			// 패킷 아이디가 이상하면 프로토콜 에러
			if ( !g_pMPacketManager->hasHandler( packetID ) )
			{
				filelog( MOFUS_ERROR_FILE, "Invalid PacketID : %d", packetID );
				throw ProtocolException( "Invalid PacketID" );
			}

			// 패킷 사이즈 확인
			if ( g_pMPacketManager->getPacketSize( packetID ) != packetSize )
			{
				filelog( MOFUS_ERROR_FILE, "Invalid PacketSize : %d, expected size : %d", packetSize, g_pMPacketManager->getPacketSize(packetID) );
				throw ProtocolException( "Invalid PacketSize" );
			}

			// 완전한 하나의 패킷이 들어있는지 확인
			if ( m_pInputStream->length() < (unsigned int)( packetSize + szMPacketSize ) )
				return;

			// 패킷을 생성
			MPacket* pPacket = g_pMPacketManager->createPacket( packetID );
			
			// 패킷 객체에 읽은 내용을 채운다.
			pPacket->read( *m_pInputStream );

			// 패킷의 해당 핸들러를 실행한다.
			g_pMPacketManager->execute( this, pPacket );
		}
	}
	catch ( InsufficientDataException )
	{
		// 무시
	}

	__END_CATCH
}

void MPlayer::sendPacket( MPacket* pPacket )
	throw ( ProtocolException, Error )
{
	Assert( pPacket != NULL );

	pPacket->write( *m_pOutputStream );
}

void MPlayer::connect()
{
	// 연결되어 있지 않아야한다.
	Assert( m_pSocket == NULL );

	// 모퍼스 서버의 IP 와 Port 를 가져온다.
	const string	MofusIP = g_pConfig->getProperty( "MofusIP" );
	uint 			MofusPort = g_pConfig->getPropertyInt( "MofusPort" );

	try
	{
		// create socket
		m_pSocket = new Socket( MofusIP, MofusPort );

		// connect
		m_pSocket->connect();

		// make nonblocking socket
		m_pSocket->setNonBlocking();

		// make no-linger socket
		m_pSocket->setLinger(0);

		// read/write 용 버퍼(stream) 을 생성한다.
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

		// 소켓을 삭제한다.
		try
		{
			SAFE_DELETE( m_pSocket );
		}
		catch ( Throwable& t )
		{
			filelog( MOFUS_ERROR_FILE, "[socket release error] %s", t.toString().c_str() );
		}

		// 다음 접속 시도 시간
		usleep( 1000000 );	// 1초
	}
}

void MPlayer::disconnect( bool bDisconnected )
	throw ( InvalidProtocolException, Error )
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

			// 연결 되어 있지 않다면 연결을 시도한다.
			if ( m_pSocket == NULL )
			{
				connect();

				// 연결 확인 패킷을 보낸다.
				if ( m_pSocket != NULL )
					sendConnectAsk();
			}

			// 소켓이 연결되어 있다면 입출력을 처리한다.
			if ( m_pSocket != NULL )
			{
				__BEGIN_TRY

				if ( getSocket()->getSockError() )
				{
					filelog( MOFUS_ERROR_FILE, "[MPlayer socket error]" );

					// 연결을 끊고 소켓 삭제하고, 입출력 버퍼 지운다.
					m_pSocket->close();
					SAFE_DELETE( m_pSocket );
					SAFE_DELETE( m_pInputStream );
					SAFE_DELETE( m_pOutputStream );

					// 루틴을 빠져나간다.
					cout << "return" << endl;
					return;
				}
				else
				{
					// 작업이 다 끝나고 보낼 패킷을 다 보냈다면 루틴을 빠져 나간다.
					if ( m_pJob->isEnd() && m_pOutputStream->isEmpty() )
					{
						// 연결을 끊고 소켓 삭제하고, 입출력 버퍼 지운다.
						m_pSocket->close();
						SAFE_DELETE( m_pSocket );
						SAFE_DELETE( m_pInputStream );
						SAFE_DELETE( m_pOutputStream );

						// 루틴을 빠져나간다.
						cout << "return" << endl;
						return;
					}

					try
					{
						// 소켓 입출력 처리 및 패킷 처리
						processInput();
						processCommand();
						processOutput();
					}
					catch ( ConnectException& ce )
					{
						filelog( MOFUS_LOG_FILE, "----- connection close" );

						// 연결이 끊겼다.
						// 소켓을 닫고, 입출력 버퍼 지우고 빠져나가기
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

						// 소켓을 닫고, 입출력 버퍼 지우고 빠져나가기
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

