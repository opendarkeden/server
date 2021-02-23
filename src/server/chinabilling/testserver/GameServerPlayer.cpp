//////////////////////////////////////////////////////////////////////
// 
// Filename    : GameServerPlayer.cpp 
// Written By  : Reiot
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "GameServerPlayer.h"
#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Assert.h"
#include "Packet.h"

#include "CBillingPacketHeader.h"
#include "CBillingPacketErrorBody.h"
#include "CBillingPacketRequestIntervalValidationBody.h"
#include "CBillingPacketRequestLoginBody.h"
#include "CBillingPacketRequestMinusPointBody.h"
#include "CBillingPacketRequestMinusMinuteBody.h"
#include "CBillingPacketRequestLogoutBody.h"
#include "CBillingPacketResponseIntervalValidationBody.h"
#include "CBillingPacketResponseLoginBody.h"
#include "CBillingPacketResponseMinusPointBody.h"
#include "CBillingPacketResponseMinusMinuteBody.h"
#include "CBillingPacketResponseLogoutBody.h"


// by sigi. 2002.11.12
const int defaultGameServerPlayerInputStreamSize = 10240;
const int defaultGameServerPlayerOutputStreamSize = 163840;


//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
GameServerPlayer::GameServerPlayer ()
	 throw ( Error )
//: m_pSocket(NULL), m_pInputStream(NULL), m_pOutputStream(NULL)
{
}


GameServerPlayer::GameServerPlayer (Socket * pSocket)
	 throw ( Error )
//: Player( pSocket )//m_pSocket(pSocket), m_pInputStream(NULL), m_pOutputStream(NULL)
{
	__BEGIN_TRY
		
	Assert( pSocket != NULL );
	m_pSocket = pSocket;

	// create socket input stream
	m_pInputStream = new SocketInputStream( m_pSocket, defaultGameServerPlayerInputStreamSize );

	Assert( m_pInputStream != NULL );
	
	// create socket output stream
	m_pOutputStream = new SocketOutputStream( m_pSocket, defaultGameServerPlayerOutputStreamSize );

	Assert( m_pOutputStream != NULL );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
GameServerPlayer::~GameServerPlayer ()
	 throw ( Error )
{
	__BEGIN_TRY
		
		/*
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
	*/

	__END_CATCH
}


void GameServerPlayer::processInput()
	throw ( IOException, Error )
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


void GameServerPlayer::processOutput()
	throw ( IOException, Error )
{
	__BEGIN_TRY

	try
	{
		m_pOutputStream->flush();
	}
	catch ( InvalidProtocolException& )
	{
		throw DisconnectException( "이상한 패킷임" );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void GameServerPlayer::processCommand () 
     throw ( IOException , Error )
{
	__BEGIN_TRY

	try {

		// 입력버퍼에 들어있는 완전한 패킷들을 모조리 처리한다.
		while ( true )
		{
			// 헤더를 저장할 버퍼 생성
			CBillingPacketHeader header;
		
			// 입력스트림에서 패킷헤더크기만큼 읽어본다.
			// 만약 지정한 크기만큼 스트림에서 읽을 수 없다면,
			// Insufficient 예외가 발생하고, 루프를 빠져나간다.
			if ( !m_pInputStream->peek( (char*)&header, szCBillingPacketHeaderInfo ) )
				break;

			header.Version_No  = ntohl( header.Version_No );
			header.Packet_Type = ntohl( header.Packet_Type );
			header.Method_Code = ntohl( header.Method_Code );
			header.Return_Code = ntohl( header.Return_Code );
			header.Body_Length = ntohl( header.Body_Length );

			cout << header.toString().c_str() << endl;

			if ( header.Packet_Type != CBILLING_PACKET_REQUEST )
			{
				cout << "error" << endl;
				return;
			}
			
			switch ( header.Method_Code )
			{
			case CBILLING_METHOD_CODE_INTERVAL_VALIDATION :
				{
					if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketRequestIntervalValidationBodyInfo )
						return;

					CBillingPacketRequestIntervalValidationBody body;
					header.read( *m_pInputStream );
					body.read( *m_pInputStream );

					executeIntervalValidation( header, body );

					break;
				}
			case CBILLING_METHOD_CODE_LOGIN :
				{
					if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketRequestLoginBodyInfo )
						return;

					CBillingPacketRequestLoginBody body;
					header.read( *m_pInputStream );
					body.read( *m_pInputStream );

					executeLogin( header, body );

					break;
				}
			case CBILLING_METHOD_CODE_MINUS_POINT :
				{
					if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketRequestMinusPointBodyInfo )
						return;

					CBillingPacketRequestMinusPointBody body;
					header.read( *m_pInputStream );
					body.read( *m_pInputStream );

					executeMinusPoint( header, body );

					break;
				}
			case CBILLING_METHOD_CODE_MINUS_MINUTE :
				{
					if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketRequestMinusMinuteBodyInfo )
						return;

					CBillingPacketRequestMinusMinuteBody body;
					header.read( *m_pInputStream );
					body.read( *m_pInputStream );

					executeMinusMinute( header, body );

					break;
				}
			case CBILLING_METHOD_CODE_LOGOUT :
				{
					if ( m_pInputStream->length() < szCBillingPacketHeaderInfo + szCBillingPacketRequestLogoutBodyInfo )
						return;

					CBillingPacketRequestLogoutBody body;
					header.read( *m_pInputStream );
					body.read( *m_pInputStream );

					executeLogout( header, body );

					break;
				}
			default:
				{
					break;
				}
			}
		}

	} catch ( NoSuchElementException & nsee ) {

		throw Error( nsee.toString() );

	} catch ( InsufficientDataException ) {

		// do nothing

	} 
	__END_CATCH
}
		    

//////////////////////////////////////////////////////////////////////
//
// send packet to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void GameServerPlayer::sendPacket ( Packet * pPacket )
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	m_pOutputStream->writePacket( pPacket );

	/*
	cout << endl;
	cout << "=== GameServerPlayer::sendPacket() ===" << endl;
	cout << pPacket->toString() << endl;
	cout << "============================" << endl;
	*/

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// disconnect ( close socket )
//
//////////////////////////////////////////////////////////////////////
void GameServerPlayer::disconnect ( bool bDisconnected )
	throw (InvalidProtocolException, Error)
{
	__BEGIN_TRY

	try 
	{
		// 정당하게 로그아웃한 경우에는 출력 버퍼를 플러시할 수 있다.
		// 그러나, 불법적인 디스를 걸었다면 소켓이 닫겼으므로
		// 플러시할 경우 SIG_PIPE 을 받게 된다.
		if ( bDisconnected == UNDISCONNECTED ) 
		{
			m_pOutputStream->flush();
		}

		m_pSocket->close();
	} 
	catch ( InvalidProtocolException & t ) 
	{
		cerr << "GameServerPlayer::disconnect Exception Check!!" << endl;
		cerr << t.toString() << endl;
		m_pSocket->close();
		//throw Error("씨바...");
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// set socket
//////////////////////////////////////////////////////////////////////
void GameServerPlayer::setSocket ( Socket * pSocket )
	throw ()
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

void GameServerPlayer::executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketRequestIntervalValidationBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader sHeader;
	CBillingPacketResponseIntervalValidationBody sBody;
	
	sHeader.Packet_Type = CBILLING_PACKET_RESPONSE;
	sHeader.Method_Code = CBILLING_METHOD_CODE_INTERVAL_VALIDATION;
	sHeader.Return_Code = CBILLING_RETURN_CODE_SUCCESS;
	sHeader.Body_Length = szCBillingPacketResponseIntervalValidationBodyInfo;

	strcpy( sBody.Parameter_Name, "MINUS_INTERVAL" );
	strcpy( sBody.Parameter_Value, "1" );

	sHeader.write( *m_pOutputStream );
	sBody.write( *m_pOutputStream );

	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;

	__END_CATCH
}

void GameServerPlayer::executeLogin( CBillingPacketHeader& header, CBillingPacketRequestLoginBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader sHeader;
	//CBillingPacketErrorBody sBody;
	CBillingPacketResponseLoginBody sBody;

	sHeader.Packet_Type = CBILLING_PACKET_RESPONSE;
	sHeader.Method_Code = CBILLING_METHOD_CODE_LOGIN;
	sHeader.Return_Code = CBILLING_RETURN_CODE_SUCCESS;
	//sHeader.Return_Code = CBILLING_RETURN_CODE_FAIL;
	sHeader.Body_Length = szCBillingPacketResponseLoginBodyInfo;
	//sHeader.Body_Length = szCBillingPacketErrorBodyInfo;

	//strcpy( sBody.Return_Message, "메롱" );
	strcpy( sBody.Login_Name, body.Login_Name );
	sBody.Player_Type = CBILLING_PLAYER_TYPE_UNLIMITED;
	sBody.Pay_Type = CBILLING_PAY_TYPE_PRE_PAID;
	sBody.Free_Left_Time = 10;
	sBody.Rating_Left_Time = 10;

	sHeader.write( *m_pOutputStream );
	sBody.write( *m_pOutputStream );

	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;

	__END_CATCH
}
void GameServerPlayer::executeMinusPoint( CBillingPacketHeader& header, CBillingPacketRequestMinusPointBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader sHeader;
	CBillingPacketResponseMinusPointBody sBody;

	sHeader.Packet_Type = CBILLING_PACKET_RESPONSE;
	sHeader.Method_Code = CBILLING_METHOD_CODE_MINUS_POINT;
	sHeader.Return_Code = CBILLING_RETURN_CODE_SUCCESS;
	sHeader.Body_Length = szCBillingPacketResponseMinusPointBodyInfo;

	strcpy( sBody.Login_Name, body.Login_Name );
	sBody.Player_Type = CBILLING_PLAYER_TYPE_MONTHLY;
	sBody.Pay_Type = CBILLING_PAY_TYPE_PRE_PAID;
	sBody.Free_Left_Time = 10;
	sBody.Rating_Left_Time = 10;
	sBody.Minus_Free_Point = 1;
	sBody.Minus_Point = 1;

	sHeader.write( *m_pOutputStream );
	sBody.write( *m_pOutputStream );

	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;

	__END_CATCH
}
void GameServerPlayer::executeMinusMinute( CBillingPacketHeader& header, CBillingPacketRequestMinusMinuteBody& body )
	throw ( IOException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader sHeader;
	CBillingPacketResponseMinusMinuteBody sBody;

	sHeader.Packet_Type = CBILLING_PACKET_RESPONSE;
	sHeader.Method_Code = CBILLING_METHOD_CODE_MINUS_MINUTE;
	sHeader.Return_Code = CBILLING_RETURN_CODE_SUCCESS;
	sHeader.Body_Length = szCBillingPacketResponseMinusMinuteBodyInfo;

	strcpy( sBody.Login_Name, body.Login_Name );
	sBody.Pay_Type = CBILLING_PAY_TYPE_PRE_PAID;
	sBody.Free_Left_Time = 10;
	sBody.Rating_Left_Time = 10;
	sBody.Minus_Free_Duration = 1;
	sBody.Minus_Duration = 1;

	sHeader.write( *m_pOutputStream );
	sBody.write( *m_pOutputStream );

	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;

	__END_CATCH
}
void GameServerPlayer::executeLogout( CBillingPacketHeader& header, CBillingPacketRequestLogoutBody& body )
throw ( IOException, Error )
{
	__BEGIN_TRY

	CBillingPacketHeader sHeader;
	CBillingPacketResponseLogoutBody sBody;

	sHeader.Packet_Type = CBILLING_PACKET_RESPONSE;
	sHeader.Method_Code = CBILLING_METHOD_CODE_LOGOUT;
	sHeader.Return_Code = CBILLING_RETURN_CODE_SUCCESS;
	sHeader.Body_Length = szCBillingPacketResponseLogoutBodyInfo;

	strcpy( sBody.Login_Name, body.Login_Name );
	sBody.Minus_Free_Point = 1;
	sBody.Minus_Point = 1;

	sHeader.write( *m_pOutputStream );
	sBody.write( *m_pOutputStream );
	
	cout << header.toString().c_str() << endl;
	cout << body.toString().c_str() << endl;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string GameServerPlayer::toString () const
       throw ( Error )
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GameServerPlayer("
		<< "SocketID:" << m_pSocket->getSOCKET() 
		<< ",Host:" << m_pSocket->getHost() 
		<< ",ID:" << m_ID
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
