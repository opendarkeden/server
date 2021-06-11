//--------------------------------------------------------------------------------
// 
// Filename    : UpdateServerPlyaer.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "UpdateServerPlayer.h"
#include "Assert.h"
#include "Packet.h"
#include "Upackets/CUBeginUpdate.h"
#include "Upackets/CURequest.h"
#include "Upackets/CUEndUpdate.h"
#include "Upackets/CURequestLoginMode.h"

//--------------------------------------------------------------------------------
//
// constructor
//
// *CAUTION*
//
// 업데이트 서버용 플레이어는 파일의 내용을 클라이언트로 전송하기 때문에, 기존의 
// 플레이어 클래스에서 소켓출력스트림과 관련된 부분만을 재정의해주면 된다. 왜냐하면, 
// 파일의 크기를 알 수 없는 상태에서 출력을 버퍼링하게 되면 문제가 생길 소지가 있기 
// 때문이다. 따라서, 버퍼링하지 않는 출력 방법을 모색해야 하겠다. 단 입력 부분은 
// 이전과 같이 버퍼링을 해도 무방하다. 
//
// 생성할때, 다른 플레이어 하위 클래스와는 달리, Player 클래스의 생성자를 명시적으로
// 호출하지 않는다. 이는 SocketOutputStream 이 생성되지 않는 Player의 디폴트 생성자를
// 호출하도록 하기 위해서이다. 
//
//--------------------------------------------------------------------------------
//static int maxIdleSec         = 60 * 5;      // 5분.
static int maxIdleSec         = 30; // 20초

// Http 방식으로 바꿨기 때문에 더 이상 buffer는 많이 필요하지 않다.
// 혹시라도 SocketInputStream이 resize 되는지는 확이해 봐야겠지.
// by sigi. 2002.11.11
const int clientBufferSize = 1024;	

UpdateServerPlayer::UpdateServerPlayer ( Socket * pSocket )
	 throw ( Error )
//: m_pSocket(pSocket), m_PlayerStatus(USPS_NONE)
: m_PlayerStatus(USPS_NONE)
{
	__BEGIN_TRY

	m_pSocket = pSocket;

	getCurrentTime(m_ExpireTime);
	m_ExpireTime.tv_sec += maxIdleSec;

	Assert( m_pInputStream == NULL );
	Assert( m_pOutputStream == NULL );

	try {
		// 소켓입력스트림은 그대로 생성해준다.
		m_pInputStream = new SocketInputStream( m_pSocket, clientBufferSize );
	} catch (Error& t) {
		filelog("updateServerPlayerBUG.txt", "%s", t.toString().c_str());
		throw;
	} catch (Throwable& t) {
		filelog("updateServerPlayerBUG.txt", "%s", t.toString().c_str());
	}

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// destructor
//
//--------------------------------------------------------------------------------
UpdateServerPlayer::~UpdateServerPlayer ()
	 throw ( Error )
{
	__BEGIN_TRY
		
	// 그 어떤 플레이어 객체가 삭제될 때에도, 그 상태는 로그아웃이어야 한다.
	// 즉 어떤 플레이어를 접속 종료 시키려면, 그 상태를 로그아웃으로 만들어야 한다.
	Assert( m_PlayerStatus == USPS_END_SESSION );

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// parse packet and execute handler for the packet
//
// 패킷팩토리를 사용하지 않는 이유는 필요없기 때문이다. -_-;
//
//--------------------------------------------------------------------------------
void UpdateServerPlayer::processCommand () 
     throw ( IOException , Error )
{
	__BEGIN_TRY

	//__BEGIN_DEBUG

	bool bLog = false;

	/*
	if (getSocket()->getHost()=="211.208.59.138"
		|| getSocket()->getHost()=="202.30.110.120")
	{
		bLog = true;
	}
	*/

	//try {

		// 헤더를 임시저장할 버퍼 생성
		char header[szPacketHeader];
		PacketID_t packetID;
		PacketSize_t packetSize;

		if (isPenaltyFlag(PENALTY_TYPE_KICKED)) {
			throw DisconnectException("He is had penalty");
		}

		//--------------------------------------------------------------------------------
		// UpdateServerPlayer 의 소켓은 blocking socket 이라는 점에 유의할 것!
		//--------------------------------------------------------------------------------
		bool bInsufficientData = false;

		while ( true ) {

			m_pInputStream->peek( &header[0] , szPacketHeader );
			memcpy( &packetID   , &header[0]          , szPacketID );
			memcpy( &packetSize , &header[szPacketID] , szPacketSize );

			if (bLog)
			{
				//cout << "packetID:" << packetID << ",packetSize:" << szPacketHeader + packetSize << endl;
				StringStream msg;
				msg << "packetID:" << packetID << ",packetSize:" << szPacketHeader + packetSize;
				filelog("badUser.txt", "%s", msg.toString().c_str());
			}

			switch ( packetID ) {

				case Packet::PACKET_CU_BEGIN_UPDATE :
					{
						if (bLog)
						{
							StringStream msg;
							msg << "RECV PACKET CUBeginUpdate[" << packetID << "](" 
								<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << ") from "
								<< m_pSocket->getHost() << ":" << m_pSocket->getPort();

							//cout << msg.toString() << endl;
							filelog("badUser.txt", "%s", msg.toString().c_str());
						}
						

						if ( packetSize > CUBeginUpdate::getPacketMaxSize() )
							throw InvalidProtocolException("too large packet size");

						if ( m_PlayerStatus != USPS_BEGIN_SESSION )
							throw InvalidProtocolException("invalid packet order");

						// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
						// 최적화시 break 를 사용하면 된다. (여기서는 일단 exception을 쓸 것이다.)
						if ( m_pInputStream->length() < szPacketHeader + packetSize )
						{
							bInsufficientData = true;
							goto INSUFFICIENT_DATA;
							//throw InsufficientDataException();
						}

						// 패킷 하나를 읽었으니, expire time 을 연기한다.
						getCurrentTime(m_ExpireTime);
						m_ExpireTime.tv_sec += maxIdleSec;
	
						// 원래는 Packet::read()를 호출하면 내부에서 패킷 헤더를 날려 주지만.
						// 여기서는 직접 날려줘야 한당...
						m_pInputStream->skip( szPacketHeader );

						CUBeginUpdate cuBeginUpdate;
						cuBeginUpdate.read( *m_pInputStream );
						//cout << "before execute" << endl;

						if (bLog)
						{
							filelog("badUser.txt", "%s", cuBeginUpdate.toString().c_str());

							try {
								cuBeginUpdate.execute( this );
							} catch (Throwable& t) {
								filelog("badUser.txt", "%s", t.toString().c_str());
							}
						}
						else
						{
							cuBeginUpdate.execute( this );
						}	
						//cout << "after execute" << endl;
					}
					break;

				case Packet::PACKET_CU_REQUEST :
					{
						if (bLog)
						{
							StringStream msg;
							msg << "RECV PACKET CURequest[" << packetID << "](" 
								<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << ") from "
								<< m_pSocket->getHost() << ":" << m_pSocket->getPort();

							//cout << msg.toString() << endl;
							filelog("badUser.txt", "%s", msg.toString().c_str());
						}

						if ( packetSize > CURequest::getPacketMaxSize() )
							throw InvalidProtocolException("too large packet size");

						if ( m_PlayerStatus != USPS_AFTER_SENDING_UC_UPDATE_LIST && 
							 m_PlayerStatus != USPS_AFTER_SENDING_UC_UPDATE )
							throw InvalidProtocolException("invalid packet order");

						// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
						// 최적화시 break 를 사용하면 된다. (여기서는 일단 exception을 쓸 것이다.)
						if ( m_pInputStream->length() < szPacketHeader + packetSize )
						{
							bInsufficientData = true;
							goto INSUFFICIENT_DATA;
							//throw InsufficientDataException();
						}

						// 패킷 하나를 읽었으니, expire time 을 연기한다.
						getCurrentTime(m_ExpireTime);
						m_ExpireTime.tv_sec += maxIdleSec;

						// 원래는 Packet::read()를 호출하면 내부에서 패킷 헤더를 날려 주지만.
						// 여기서는 직접 날려줘야 한당...
						m_pInputStream->skip( szPacketHeader );

						CURequest cuRequest;
						cuRequest.read( *m_pInputStream );
						cuRequest.execute( this );
					}
					break;

				case Packet::PACKET_CU_END_UPDATE :
					{
						if (bLog)
						{
							StringStream msg;
							msg << "RECV PACKET UCUpdate[" << packetID << "](" 
								<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << ") from "
								<< m_pSocket->getHost() << ":" << m_pSocket->getPort();

							//cout << msg.toString() << endl;
							filelog("badUser.txt", "%s", msg.toString().c_str());
						}
						

						if ( packetSize > CUEndUpdate::getPacketMaxSize() )
							throw InvalidProtocolException("too large packet size");

						if ( m_PlayerStatus != USPS_AFTER_SENDING_UC_UPDATE_LIST || 
							 m_PlayerStatus != USPS_AFTER_SENDING_UC_UPDATE )
							throw InvalidProtocolException("invalid packet order");

						// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
						// 최적화시 break 를 사용하면 된다. (여기서는 일단 exception을 쓸 것이다.)
						if ( m_pInputStream->length() < szPacketHeader + packetSize )
						{
							bInsufficientData = true;
							goto INSUFFICIENT_DATA;
							//throw InsufficientDataException();
						}

						// 패킷 하나를 읽었으니, expire time 을 연기한다.
						getCurrentTime(m_ExpireTime);
						m_ExpireTime.tv_sec += maxIdleSec;
	
						// 원래는 Packet::read()를 호출하면 내부에서 패킷 헤더를 날려 주지만.
						// 여기서는 직접 날려줘야 한당...
						m_pInputStream->skip( szPacketHeader );

						CUEndUpdate cuEndUpdate;
						cuEndUpdate.read( *m_pInputStream );
						cuEndUpdate.execute( this );
					}
					break;

				case Packet::PACKET_CU_REQUEST_LOGIN_MODE :
					{
						if (bLog)
						{
							StringStream msg;
							msg << "RECV PACKET CURequestLoginMode[" << packetID << "](" 
								<< szPacketHeader + packetSize << "/" << m_pInputStream->length() << ") from "
								<< m_pSocket->getHost() << ":" << m_pSocket->getPort();

							//cout << msg.toString() << endl;
							filelog("badUser.txt", "%s", msg.toString().c_str());
						}
						

						if ( packetSize > CUEndUpdate::getPacketMaxSize() )
							throw InvalidProtocolException("too large packet size");

						if ( m_PlayerStatus != USPS_BEGIN_SESSION )
							throw InvalidProtocolException("invalid packet order");

						// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
						// 최적화시 break 를 사용하면 된다. (여기서는 일단 exception을 쓸 것이다.)
						if ( m_pInputStream->length() < szPacketHeader + packetSize )
						{
							bInsufficientData = true;
							goto INSUFFICIENT_DATA;
							//throw InsufficientDataException();
						}

						// 패킷 하나를 읽었으니, expire time 을 연기한다.
						getCurrentTime(m_ExpireTime);
						m_ExpireTime.tv_sec += maxIdleSec;
	
						// 원래는 Packet::read()를 호출하면 내부에서 패킷 헤더를 날려 주지만.
						// 여기서는 직접 날려줘야 한당...
						m_pInputStream->skip( szPacketHeader );

						CURequestLoginMode cuRequestLoginMode;
						cuRequestLoginMode.read( *m_pInputStream );
						cuRequestLoginMode.execute( this );
					}
					break;

				default :
					{
						if (bLog)
						{
							//cout << "Invalid Packet ID!!!" << endl;
							filelog("badUser.txt", "Invalid Packet ID");
						}
						throw InvalidProtocolException("invalid packet id");
					}
			}

		}
	//}
	
	//} catch ( InsufficientDataException ) {
// by sigi. 2002.11.9
INSUFFICIENT_DATA:
	if (bInsufficientData)
	{
		// 단지 루프의 탈출 조건일 뿐이다. 상위로 전달할 필요는 없다.
		        // expire time 을 초과했을 경우 연결을 종료한다.
		Timeval currentTime;
		getCurrentTime(currentTime);
		if (currentTime >= m_ExpireTime)
			throw DisconnectException("일정 시간동안 입력하지 않을 경우, 연결을 종료합니다.");

	}

//	__END_DEBUG

	__END_CATCH
}
		    

//--------------------------------------------------------------------------------
// 출력을 버퍼링하지 않기 때문에, 아무 것도 하지 않아도 된다.
//--------------------------------------------------------------------------------
void UpdateServerPlayer::processOutput ()
	throw ( IOException , Error )
{
	__BEGIN_TRY

	// do nothing

	__END_CATCH
}


//--------------------------------------------------------------------------------
// send packet to socket
//--------------------------------------------------------------------------------
void UpdateServerPlayer::sendPacket ( Packet * pPacket )
	throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	__BEGIN_DEBUG

	//cout << "SEND PACKET " << pPacket->getPacketName().c_str() << " to "
//		<< m_pSocket->getHost().c_str() << ":" << m_pSocket->getPort() << endl;

	PacketID_t packetID = pPacket->getPacketID();
	PacketSize_t packetSize = pPacket->getPacketSize();
	m_pSocket->send( &packetID , szPacketID );
	m_pSocket->send( &packetSize , szPacketSize );
	// 패킷을 소켓에 직접 뿌린다.
	pPacket->write( m_pSocket );

	//cout << "Send Packet Size : " << pPacket->getPacketSize() << endl;
	//cout << "Send Buffer Size : " << m_pSocket->getSendBufferSize() << endl;

	__END_DEBUG

	__END_CATCH
}


//--------------------------------------------------------------------------------
// disconnect player
//--------------------------------------------------------------------------------
void UpdateServerPlayer::disconnect ( bool bDisconnected )
	throw ( Error )
{
	__BEGIN_TRY

	if ( bDisconnected == UNDISCONNECTED ) {

		// 출력 버퍼에 남아있는 데이타를 전송한다.
		m_pOutputStream->flush();

	}

	// 소켓 연결을 닫는다.
	m_pSocket->close();

	// 플레이어의 상태를 로그아웃으로 만든다.
	Assert( m_PlayerStatus != USPS_END_SESSION );
	m_PlayerStatus = USPS_END_SESSION;

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// get debug string
//
//--------------------------------------------------------------------------------
string UpdateServerPlayer::toString () const
       throw ( Error )
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "UpdateServerPlayer("
		<< "SocketID:" << m_pSocket->getSOCKET() 
		<< ",Host:" << m_pSocket->getHost() 
		<< ",Port:" << m_pSocket->getPort() 
		<< ")" ;

	return msg.toString();

	__END_CATCH
}
