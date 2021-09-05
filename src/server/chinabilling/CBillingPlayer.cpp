////////////////////////////////////////////////////////////////
//
// filename		: CBillingPlayer.cpp
//
////////////////////////////////////////////////////////////////

// include files
#include "CBillingPlayer.h"
#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"
#include "Packet.h"
#include "CBillingPlayerManager.h"

#include "CBillingPacketHeader.h"
#include "CBillingPacketErrorBody.h"

#include <stdio.h>
#include "signal.h"

#ifdef __GAME_SERVER__
	#include "PCFinder.h"
	#include "GamePlayer.h"
	#include "CBillingPacketRequestLoginBody.h"
	#include "CBillingPacketResponseLoginBody.h"
	#include "CBillingPacketRequestMinusPointBody.h"
	#include "CBillingPacketRequestMinusMinuteBody.h"
	#include "CBillingPacketRequestLogoutBody.h"
	#include "CBillingPacketRequestIntervalValidationBody.h"
	#include "CBillingPacketResponseMinusPointBody.h"
	#include "CBillingPacketResponseMinusMinuteBody.h"
	#include "CBillingPacketResponseLogoutBody.h"
	#include "CBillingPacketResponseIntervalValidationBody.h"

	#include "DB.h"

	#include "GCSystemMessage.h"
	#include "gameserver/StringPool.h"
#elif defined(__LOGIN_SERVER__)
	#include "LoginPlayer.h"
	#include "LoginPlayerManager.h"
	#include "CBillingPacketRequestLoginBody.h"
	#include "CBillingPacketResponseLoginBody.h"
#endif

const int defaultCBillingPlayerInputStreamSize = 10240;
const int defaultCBillingPlayerOutputStreamSize = 10240;

// constructor
CBillingPlayer::CBillingPlayer()
{
}

// constructor
CBillingPlayer::CBillingPlayer( Socket* pSocket )
{
	__BEGIN_TRY

	Assert( pSocket != NULL );
	m_pSocket = pSocket;

	// create socket input stream
	m_pInputStream = new SocketInputStream( m_pSocket, defaultCBillingPlayerInputStreamSize );
	Assert( m_pInputStream != NULL );

	// create socket output stream
	m_pOutputStream = new SocketOutputStream( m_pSocket, defaultCBillingPlayerOutputStreamSize );
	Assert( m_pOutputStream != NULL );

	__END_CATCH
}

// destructor
CBillingPlayer::~CBillingPlayer()
{
	// delete socket intput stream
	SAFE_DELETE( m_pInputStream );

	// delete socket output stream
	SAFE_DELETE( m_pOutputStream );

	// delete socket
	if ( m_pSocket != NULL )
	{
		m_pSocket->close();
		SAFE_DELETE( m_pSocket );

		filelog( LOGFILE_CBILLING_PLAYER, "Close Socket" );
	}
}

void CBillingPlayer::processInput()
{
	__BEGIN_TRY

	try
	{
		m_pInputStream->fill();
	}
	catch ( NonBlockingIOException& nbie )
	{
	}

	__END_CATCH
}

void CBillingPlayer::processOutput()
{
	__BEGIN_TRY

	try
	{
		m_pOutputStream->flush();
	}
	catch ( InvalidProtocolException& )
	{
		throw DisconnectException( "�̻��� ��Ŷ��" );
	}

	__END_CATCH
}

// parse packet and execute packet handler
void CBillingPlayer::processCommand()
{
	__BEGIN_TRY

	try
	{
		// �Է� ���ۿ� ����ִ� ������ ��Ŷ���� ������ ó���Ѵ�.
		while ( true )
		{
			// ����� ������ ���� ����
			CBillingPacketHeader header;

			// �ϴ� ����� �д´�. peek. �Է¹��ۿ��� �������� �ʴ´�.
			// ����� �������� ������ �н�
			if ( !m_pInputStream->peek( (char*)&header, szCBillingPacketHeaderInfo ) )
				return;

			header.Version_No  = ntohl( header.Version_No );
			header.Packet_Type = ntohl( header.Packet_Type );
			header.Method_Code = ntohl( header.Method_Code );
			header.Return_Code = ntohl( header.Return_Code );
			header.Body_Length = ntohl( header.Body_Length );

			////////////////////////////////////////////////////////////////////////////////////
			// Packet_Type, Method_Code, Return_Code �� ���� �ٵ� ������ �����ϴ��� Ȯ���Ѵ�.
			////////////////////////////////////////////////////////////////////////////////////
			if ( header.Packet_Type != CBILLING_PACKET_RESPONSE )
			{
				cout << "error" << endl;
				cout << "try to disconnect to china billing server" << endl;

				filelog( LOGFILE_CBILLING_PLAYER, "!!!!!!!!!!!!!!!! try to disconnect to china billing server" );

				g_pCBillingPlayerManager->setForceDisconnect();
				return;
				// ������ ����~
			}

			// ������ ���
			if ( header.Return_Code != CBILLING_RETURN_CODE_SUCCESS )
			{
				// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
				if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketErrorBodyInfo )
					return;

				// ���� ������ ������ �о� ����.
				CBillingPacketErrorBody body;
				header.read( *m_pInputStream );
				body.read( *m_pInputStream );

				executeError( header, body );
			}
			else // ������ ���
			{
				switch ( header.Method_Code )
				{
#ifdef __LOGIN_SERVER__
				case CBILLING_METHOD_CODE_LOGIN :
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseLoginBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseLoginBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeLogin( header, body );

						break;
					}
#elif defined(__GAME_SERVER__)
				case CBILLING_METHOD_CODE_INTERVAL_VALIDATION:
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseIntervalValidationBodyInfo )
							return;
						
						// ���� ������ ������ �о� ����.
						CBillingPacketResponseIntervalValidationBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeIntervalValidation( header, body );

						break;
					}
				case CBILLING_METHOD_CODE_LOGIN :
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseLoginBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseLoginBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeLogin( header, body );

						break;
					}
				case CBILLING_METHOD_CODE_MINUS_POINT:
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseMinusPointBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseMinusPointBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeMinusPoint( header, body );

						break;
					}
				case CBILLING_METHOD_CODE_MINUS_MINUTE:
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseMinusMinuteBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseMinusMinuteBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeMinusMinute( header, body );

						break;
					}
				case CBILLING_METHOD_CODE_LOGOUT:
					{
						// �ٵ� ������ ����ִ��� Ȯ���Ѵ�.
						if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketResponseLogoutBodyInfo )
							return;

						// ���� ������ ������ �о� ����.
						CBillingPacketResponseLogoutBody body;
						header.read( *m_pInputStream );
						body.read( *m_pInputStream );

						// ����
						executeLogout( header, body );

						break;
					}
#endif
				default:
					{
						throw Error( "Invaild Code" );

						// ������.
						break;
					}
				}
			}
		}
	}
	catch ( NoSuchElementException& nsee )
	{
		throw Error( nsee.toString() );
	}
	catch ( InsufficientDataException )
	{
		// do nothing
	}

	__END_CATCH
}

// send packet to player's output buffer
void CBillingPlayer::sendPacket( Packet* pPacket )
{
	__BEGIN_TRY

	//pPacket->write( *m_pOutputStream );

	__END_CATCH
}

// disconnect
void CBillingPlayer::disconnect( bool bDisconnected )
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
		cerr << "CBillingPlayer::disconnect Exception occur!!" << endl;
		cerr << t.toString() << endl;
		m_pSocket->close();
	}

	__END_CATCH
}

// set socket
void CBillingPlayer::setSocket( Socket* pSocket )
{
	__BEGIN_TRY

	m_pSocket = pSocket;

	SAFE_DELETE( m_pInputStream );
	m_pInputStream = new SocketInputStream( m_pSocket );

	SAFE_DELETE( m_pOutputStream );
	m_pOutputStream = new SocketOutputStream( m_pSocket );

	__END_CATCH
}

#ifdef __LOGIN_SERVER__

// send login packet
void CBillingPlayer::sendLogin( LoginPlayer* pLoginPlayer )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestLoginBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_LOGIN;
	header.Session_ID	= pLoginPlayer->increaseSendID();
	header.Body_Length	= szCBillingPacketRequestLoginBodyInfo;

	strcpy( body.Login_Name, pLoginPlayer->getID().c_str() );
	strcpy( body.Player_IP, pLoginPlayer->getSocket()->getHost().c_str() );

	char macstring[20];
	const BYTE* macaddress = pLoginPlayer->getMacAddress();
	sprintf( macstring, "%02X:%02X:%02X:%02X:%02X:%02X", macaddress[0], macaddress[1], macaddress[2], macaddress[3], macaddress[4], macaddress[5] );

	strcpy( body.Player_MAC, macstring );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Login : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Login : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

#elif defined(__GAME_SERVER__)

// send interval validation packet
void CBillingPlayer::sendIntervalValidation()
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestIntervalValidationBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_INTERVAL_VALIDATION;
	header.Session_ID	= 1;
	header.Body_Length	= szCBillingPacketRequestIntervalValidationBodyInfo;

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Interval Validation : " << body.Parameter_Value << " min" << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Interval Validation : %s\n%s\n%s", body.Parameter_Value, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// send login packet
void CBillingPlayer::sendLogin( GamePlayer* pGamePlayer )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestLoginBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_LOGIN;
	header.Session_ID	= pGamePlayer->increaseSendID();
	header.Body_Length	= szCBillingPacketRequestLoginBodyInfo;

	strcpy( body.Login_Name, pGamePlayer->getID().c_str() );
	strcpy( body.Player_IP, pGamePlayer->getSocket()->getHost().c_str() );

	char macstring[20];
	const BYTE* macaddress = pGamePlayer->getMacAddress();
	sprintf( macstring, "%02X:%02X:%02X:%02X:%02X:%02X", macaddress[0], macaddress[1], macaddress[2], macaddress[3], macaddress[4], macaddress[5] );

	strcpy( body.Player_MAC, macstring );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Login : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Login : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// send minus point packet
void CBillingPlayer::sendMinusPoint( GamePlayer* pGamePlayer )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestMinusPointBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_MINUS_POINT;
	header.Session_ID	= pGamePlayer->increaseSendID();
	header.Body_Length	= szCBillingPacketRequestMinusPointBodyInfo;

	strcpy( body.Login_Name, pGamePlayer->getID().c_str() );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Minus Point : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Minus Point : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// send minus minute packet
void CBillingPlayer::sendMinusMinute( GamePlayer* pGamePlayer )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestMinusMinuteBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_MINUS_MINUTE;
	header.Session_ID	= pGamePlayer->increaseSendID();
	header.Body_Length	= szCBillingPacketRequestMinusMinuteBodyInfo;

	strcpy( body.Login_Name, pGamePlayer->getID().c_str() );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Minus Minute : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Minus Minute : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

// send logout packet
void CBillingPlayer::sendLogout( GamePlayer* pGamePlayer )
{
	__BEGIN_TRY

	CBillingPacketHeader header;
	CBillingPacketRequestLogoutBody body;

	header.Packet_Type	= CBILLING_PACKET_REQUEST;
	header.Method_Code	= CBILLING_METHOD_CODE_LOGOUT;
	header.Session_ID	= pGamePlayer->increaseSendID();
	header.Body_Length	= szCBillingPacketRequestLogoutBodyInfo;

	strcpy( body.Login_Name, pGamePlayer->getID().c_str() );

	header.write( *m_pOutputStream );
	body.write( *m_pOutputStream );

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Request Logout : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif

	filelog( LOGFILE_CBILLING_PLAYER, "Request Logout : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

#endif

void CBillingPlayer::executeError( CBillingPacketHeader& header, CBillingPacketErrorBody& body )
{
	__BEGIN_TRY

#ifdef __LOGIN_SERVER__

	__ENTER_CRITICAL_SECTION( (*g_pLoginPlayerManager) )

	LoginPlayer* pLoginPlayer = g_pLoginPlayerManager->getPlayer_NOLOCKED( body.Login_Name );

	if ( pLoginPlayer != NULL )
	{
		// ���� �Ǿ��ٰ� üũ�Ѵ�. ���� ����ڰ� �ƴϹǷ� CLSelectPC ���� ©����.
		pLoginPlayer->setCBillingVerified();
	}

	__LEAVE_CRITICAL_SECTION( (*g_pLoginPlayerManager) )

#elif defined(__GAME_SERVER__)

	// ���� ������ ©����~
	__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

	Creature* pCreature = g_pPCFinder->getCreatureByID_LOCKED( body.Login_Name );

	if ( pCreature != NULL )
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
		Assert( pGamePlayer != NULL );

		pGamePlayer->setPayPlayer( false );
	}

	__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )

	logPacket( &header, NULL, NULL, NULL, &body );

#endif

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Error : " << body.Login_Name << endl;
	cout << body.Return_Message << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Error : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

#ifdef __LOGIN_SERVER__

void CBillingPlayer::executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( (*g_pLoginPlayerManager) )

	try
	{
		LoginPlayer* pLoginPlayer = g_pLoginPlayerManager->getPlayer_NOLOCKED( body.Login_Name );

		if ( pLoginPlayer != NULL )
		{
			// ���� �Ǿ��ٰ� üũ�Ѵ�.
			pLoginPlayer->setCBillingVerified();

			bool bPayPlayer = ( body.Free_Left_Time + body.Rating_Left_Time > 0 );

			// set pay player
			pLoginPlayer->setPayPlayer( bPayPlayer );
		}
	}
	catch ( NoSuchElementException& nsee )
	{
		// ignore
	}

	__LEAVE_CRITICAL_SECTION( (*g_pLoginPlayerManager) )

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Login OK : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Login OK : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

#elif defined(__GAME_SERVER__)
void CBillingPlayer::executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketResponseIntervalValidationBody& body )
{
	__BEGIN_TRY

	if ( atoi(body.Parameter_Value) != g_pCBillingPlayerManager->getMinusIntervalInt() )
	{
		// ���Ӽ����� �߱� ���� �������� minus interval �� ���� �ʴ�. �׾�� �Ѵ�.
		cerr << "-------------------------------------------------------------------------------" << endl;
		cerr << "Interval configuration is different between gameserver and china billing server" << endl;
		cerr << "gameserver interval : " << g_pCBillingPlayerManager->getMinusIntervalInt() << ", china billing server interval : " << body.Parameter_Value << endl;
		cerr << "-------------------------------------------------------------------------------" << endl;

		filelog( LOGFILE_CBILLING_ERROR, "Different Interval between gameserver and china billing server\ngameserver interval : %d, china billing server interval : %s", g_pCBillingPlayerManager->getMinusIntervalInt(), body.Parameter_Value );

		// �׾��. ���� �Ф�.
		kill( getpid(), 9 );
	}

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Interval Validation : " << body.Parameter_Value << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Interval Validation : %s\n%s\n%s", body.Parameter_Value, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

void CBillingPlayer::executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body )
{
	__BEGIN_TRY

	// disconnect if no Left Time
	__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

	Creature* pCreature = g_pPCFinder->getCreatureByID_LOCKED( body.Login_Name );

	if ( pCreature != NULL )
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
		if ( pGamePlayer == NULL )
		{
			g_pPCFinder->unlock();
			Assert( false );
		}

		// ���� �Ǿ��ٰ� üũ�Ѵ�.
		pGamePlayer->setCBillingVerified();

		// set CBillingInfo
		pGamePlayer->setCBPlayerType( body.Player_Type );
		pGamePlayer->setCBPayType( body.Pay_Type );

		if ( pGamePlayer->getCBPlayerType() == CBILLING_PLAYER_TYPE_MONTHLY )
		{
			VSDateTime endDateTime = VSDateTime::fromYYYYMMDDHHMMSS( body.End_Date_Time );
			pGamePlayer->setCBEndDateTime( endDateTime );
		}
		else if ( pGamePlayer->getCBPlayerType() == CBILLING_PLAYER_TYPE_POINT )
		{
			pGamePlayer->setCBLeftTime( body.Free_Left_Time + body.Rating_Left_Time );
		}

		// set false pay player. ZonePlayerManager will disconnect this player.
		if ( body.Free_Left_Time + body.Rating_Left_Time == 0 )
		{
			pGamePlayer->setPayPlayer( false );

#ifdef __COUT_CBILLING_SYSTEM__
			cout << "----------------------------------------------------------------" << endl;
			cout << "Response Login OK : " << body.Login_Name << " has no left time. DISCONNECT" << endl;
			cout << header.toString().c_str() << endl;
			cout << body.toString().c_str() << endl;
#endif
			filelog( LOGFILE_CBILLING_PACKET, "Response Login OK : %s has no left time. DISCONNECT\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );
		}
		else
		{
#ifdef __COUT_CBILLING_SYSTEM__
			cout << "----------------------------------------------------------------" << endl;
			cout << "Response Login OK : " << body.Login_Name << endl;
			cout << header.toString().c_str() << endl;
			cout << body.toString().c_str() << endl;
#endif
			filelog( LOGFILE_CBILLING_PACKET, "Response Login OK : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );
		}

//		char m[100];
//		sprintf( m, "Free Left Point : %d.%d Left Point %d.%d", body.Free_Left_Time / 10, body.Free_Left_Time % 10, body.Rating_Left_Time / 10, body.Rating_Left_Time % 10 );
//		GCSystemMessage msg;
//		msg.setMessage( m );
//		pGamePlayer->sendPacket( &msg );
	}
	else
	{
#ifdef __COUT_CBILLING_SYSTEM__
		cout << "----------------------------------------------------------------" << endl;
		cout << "Response Login OK : " << body.Login_Name << endl;
		cout << header.toString().c_str() << endl;
		cout << body.toString().c_str() << endl;
#endif
		filelog( LOGFILE_CBILLING_PACKET, "Response Login OK : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );
	}

	__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )

	logPacket( &header, &body, NULL, NULL, NULL );

	__END_CATCH
}

void CBillingPlayer::executeMinusPoint( CBillingPacketHeader& header, CBillingPacketResponseMinusPointBody& body )
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

	Creature* pCreature = g_pPCFinder->getCreatureByID_LOCKED( body.Login_Name );

	if ( pCreature != NULL )
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());
		if ( pGamePlayer == NULL )
		{
			g_pPCFinder->unlock();
			Assert( false );
		}

		// �������� ���, �ð��� �� ���Ҵٰ� �����ش�.
		if ( body.Player_Type == CBILLING_PLAYER_TYPE_POINT )
		{
			int leftTime = body.Free_Left_Time + body.Rating_Left_Time;

			if ( leftTime <= pGamePlayer->getCBLastShowLeftTime() )
			{
				char m[200];
				sprintf( m, g_pStringPool->c_str( STRID_CB_LEFT_POINT ), leftTime / 10 );

				GCSystemMessage msg;
				msg.setMessage( m );
				pGamePlayer->sendPacket( &msg );

				// ������ ���� �� �ð� ����
				pGamePlayer->setCBLastShowLeftTime( leftTime - 30 );
			}
		}

		if ( pGamePlayer->getCBPlayerType() != body.Player_Type )
		{
			if ( body.Player_Type == CBILLING_PLAYER_TYPE_POINT )
			{
				int leftTime = body.Free_Left_Time + body.Rating_Left_Time;

				// point user �� �ٲ���.
				char m[200];
				sprintf( m, g_pStringPool->c_str( STRID_CB_CHANGE_TO_POINT_PLAYER ), leftTime / 10 );

				GCSystemMessage msg;
				msg.setMessage( m );
				pGamePlayer->sendPacket( &msg );
			}
			else if ( body.Player_Type == CBILLING_PLAYER_TYPE_MONTHLY )
			{
				// monthly user �� �ٲ���.
				char m[200];
				sprintf( m, g_pStringPool->c_str( STRID_CB_CHANGE_TO_MONTHLY_PLAYER ) );

				GCSystemMessage msg;
				msg.setMessage( m );
				pGamePlayer->sendPacket( &msg );
			}

			pGamePlayer->setCBPlayerType( body.Player_Type );
		}
	}

	__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Minus Point : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Minus Point : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	logPacket( &header, NULL, &body, NULL, NULL );

	__END_CATCH
}

void CBillingPlayer::executeMinusMinute( CBillingPacketHeader& header, CBillingPacketResponseMinusMinuteBody& body )
{
	__BEGIN_TRY

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Minus Minute : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Minus Minute : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	__END_CATCH
}

void CBillingPlayer::executeLogout( CBillingPacketHeader& header, CBillingPacketResponseLogoutBody& body )
{
	__BEGIN_TRY

#ifdef __COUT_CBILLING_SYSTEM__
	cout << "----------------------------------------------------------------" << endl;
	cout << "Response Logout OK : " << body.Login_Name << endl;
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;
#endif
	filelog( LOGFILE_CBILLING_PACKET, "Response Logout OK : %s\n%s\n%s", body.Login_Name, header.toString().c_str(), body.toString().c_str() );

	logPacket( &header, NULL, NULL, &body, NULL );

	__END_CATCH
}

#endif

#ifdef __GAME_SERVER__
void CBillingPlayer::checkSessionID( CBillingPacketHeader& header, GamePlayer* pGamePlayer )
{
	__BEGIN_TRY

	if ( pGamePlayer->increaseRecvID() != header.Session_ID )
	{
#ifdef __COUT_CBILLING_SYSTEM__
		cerr << "******************************************************************" << endl;
		cerr << "Session Fail : Recv ID = " << header.Session_ID << ", Respect ID = " << pGamePlayer->getRecvID() << endl;
		cerr << header.toString().c_str() << endl;
#endif
		filelog( LOGFILE_CBILLING_ERROR, "Session Fail : RecvID = %d, Respect ID = %d\n%s", header.Session_ID, pGamePlayer->getRecvID(), header.toString().c_str() );
	}

	__END_CATCH
}
#endif

#ifdef __GAME_SERVER__
	// DB�� packet �α� �����
void CBillingPlayer::logPacket( CBillingPacketHeader* header, CBillingPacketResponseLoginBody* login, CBillingPacketResponseMinusPointBody* point, CBillingPacketResponseLogoutBody* logout, CBillingPacketErrorBody* error )
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		string playerID( "" );
		string methodCode( "" );
		string returnCode( "" );
		string playerType( "NONE" );
		string payType( "NONE" );
		int freePayPoint = 0;
		int freeLeftTime = 0;
		int payPoint = 0;
		int leftPayTime = 0;
		VSDateTime endDateTime( "2004-01-01 00:00:00" );

		switch ( header->Return_Code )
		{
			case CBILLING_RETURN_CODE_SUCCESS:
			{
				returnCode = "SUCCESS";
				break;
			}
			case CBILLING_RETURN_CODE_FAIL:
			{
				returnCode = "FAIL";
				break;
			}
			case CBILLING_RETURN_CODE_DB_ERROR:
			{
				returnCode = "DB_ERROR";
				break;
			}
			case CBILLING_RETURN_CODE_INVALID_LOGIN_NAME:
			{
				returnCode = "INVALID_LOGIN_NAME";
				break;
			}
			case CBILLING_RETURN_CODE_FAIL_MINUS_POINT:
			{
				returnCode = "FAIL_MINUS_POINT";
				break;
			}
			case CBILLING_RETURN_CODE_FAIL_MINUS_MINUTE:
			{
				returnCode = "FAIL_MINUS_MINUTE";
				break;
			}
			default:
			{
				throw Error( "Return Code Error" );
				break;
			}
		}

		switch ( header->Method_Code )
		{
			case CBILLING_METHOD_CODE_LOGIN:
			{
				methodCode = "LOGIN";

				if ( header->Return_Code != CBILLING_RETURN_CODE_SUCCESS )
				{
					Assert( error != NULL );
					playerID = error->Login_Name;

					break;
				}

				Assert( login != NULL );

				playerID = login->Login_Name;
				endDateTime = VSDateTime::fromYYYYMMDDHHMMSS( login->End_Date_Time );

				switch ( login->Player_Type )
				{
					case CBILLING_PLAYER_TYPE_UNLIMITED:
					{
						playerType = "UNLIMITED";
						break;
					}
					case CBILLING_PLAYER_TYPE_LIMITED:
					{
						playerType = "LIMITED";
						break;
					}
					case CBILLING_PLAYER_TYPE_MONTHLY:
					{
						playerType = "MONTHLY";
						break;
					}
					case CBILLING_PLAYER_TYPE_POINT:
					{
						playerType = "POINT";
						break;
					}
					default:
					{
						throw Error( "Player Type Error" );
						break;
					}
				}
				
				switch ( login->Pay_Type )
				{
					case CBILLING_PAY_TYPE_PRE_PAID:
					{
						payType = "PRE_PAID";
						break;
					}
					case CBILLING_PAY_TYPE_POST_PAID:
					{
						payType = "POST_PAID";
						break;
					}
					default:
					{
						throw Error( "Pay Type Error" );
						break;
					}
				}

				freeLeftTime = login->Free_Left_Time;
				leftPayTime = login->Rating_Left_Time;

				break;
			}
			case CBILLING_METHOD_CODE_MINUS_POINT:
			{
				methodCode = "MINUS_POINT";

				if ( header->Return_Code != CBILLING_RETURN_CODE_SUCCESS )
				{
					Assert( error != NULL );
					playerID = error->Login_Name;

					break;
				}

				Assert( point != NULL );
				playerID = point->Login_Name;

				switch ( point->Player_Type )
				{
					case CBILLING_PLAYER_TYPE_UNLIMITED:
					{
						playerType = "UNLIMITED";
						break;
					}
					case CBILLING_PLAYER_TYPE_LIMITED:
					{
						playerType = "LIMITED";
						break;
					}
					case CBILLING_PLAYER_TYPE_MONTHLY:
					{
						playerType = "MONTHLY";
						break;
					}
					case CBILLING_PLAYER_TYPE_POINT:
					{
						playerType = "POINT";
						break;
					}
					default:
					{
						throw Error( "Player Type Error" );
						break;
					}
				}
				
				switch ( point->Pay_Type )
				{
					case CBILLING_PAY_TYPE_PRE_PAID:
					{
						payType = "PRE_PAID";
						break;
					}
					case CBILLING_PAY_TYPE_POST_PAID:
					{
						payType = "POST_PAID";
						break;
					}
					default:
					{
						throw Error( "Pay Type Error" );
						break;
					}
				}

				freeLeftTime = point->Free_Left_Time;
				leftPayTime = point->Rating_Left_Time;
				freePayPoint = point->Minus_Free_Point;
				payPoint = point->Minus_Point;

				break;
			}
			case CBILLING_METHOD_CODE_LOGOUT:
			{
				methodCode = "LOGOUT";

				if ( header->Return_Code != CBILLING_RETURN_CODE_SUCCESS )
				{
					Assert( error != NULL );
					playerID = error->Login_Name;

					break;
				}

				Assert( logout != NULL );
				playerID = logout->Login_Name;

				freePayPoint = logout->Minus_Free_Point;
				payPoint = logout->Minus_Point;

				break;
			}
			default:
			{
				throw Error( "Method Code error" );
				break;
			}
		}

		pStmt = g_pDatabaseManager->getCBillingConnection( "CBILLING" )->createStatement();
		Assert( pStmt != NULL );

		pStmt->executeQuery( "INSERT INTO TB_BillingLog( DateTime, PlayerID, PacketType, ReturnCode, PlayerType, PayType, FreePayPoint, FreeLeftTime, PayPoint, LeftPayTime, EndDateTime ) VALUES ( NOW(), '%s', '%s', '%s', '%s', '%s', %d, %d, %d, %d, '%s' )",
															playerID.c_str(), methodCode.c_str(), returnCode.c_str(), playerType.c_str(), payType.c_str(), freePayPoint, freeLeftTime, payPoint, leftPayTime, endDateTime.toDateTime().c_str() );
		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )

	__END_CATCH
}
#endif

// get debug string
string CBillingPlayer::toString() const
{
	__BEGIN_TRY

	StringStream msg;

	msg << "CBillingPlayer("
		<< "SocketID:" << m_pSocket->getSOCKET()
		<< ",Host:"<< m_pSocket->getHost()
		<< ",ID:" << m_ID
		<< ")";

	return msg.toString();

	__END_CATCH
}

