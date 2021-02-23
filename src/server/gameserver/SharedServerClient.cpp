//////////////////////////////////////////////////////////////////////////////
// Filename    : GamePlyaer.cpp 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "SharedServerClient.h"
#include "Assert.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "GuildManager.h"
#include "Guild.h"
#include <fstream>

//////////////////////////////////////////////////////////////////////////////
// 모든 packet들에 대해서 profiling한다. by sigi. 2002.5.6
//
// 단, 이걸 사용하기 위해서는 
// Profile.h에 MAX_PROFILE_SAMPLES += 300을 해줘야 한다.
//////////////////////////////////////////////////////////////////////////////
//#define __PROFILE_PACKETS__


//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

SharedServerClient::SharedServerClient (Socket* pSocket)
	 throw (Error)
: Player(pSocket)
{
	__BEGIN_TRY

	m_Mutex.setName("SharedServerClient");

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////

SharedServerClient::~SharedServerClient ()
	 throw (Error)
{
	__BEGIN_TRY

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void SharedServerClient::processCommand () 
     throw (IOException , Error)
{
	__BEGIN_TRY

	// 헤더를 임시저장할 버퍼 생성
	char header[szPacketHeader];
	PacketID_t packetID;
	PacketSize_t packetSize;
	Packet* pPacket = NULL;

	try {

		// 입력버퍼에 들어있는 완전한 패킷들을 모조리 처리한다.
		while (true) 
		{
			// 입력스트림에서 패킷헤더크기만큼 읽어본다.
			// 만약 지정한 크기만큼 스트림에서 읽을 수 없다면,
			// Insufficient 예외가 발생하고, 루프를 빠져나간다.
			// NoSuch제거. by sigi. 2002.5.4
			if (!m_pInputStream->peek(&header[0] , szPacketHeader))
			{
				break;
			}
			
			// 패킷아이디 및 패킷크기를 알아낸다.
			// 이때 패킷크기는 헤더를 포함한다.
			memcpy(&packetID   , &header[0] , szPacketID);	
			memcpy(&packetSize , &header[szPacketID] , szPacketSize);

			// 패킷 아이디가 이상하면 프로토콜 에러로 간주한다.
			if (packetID >= (int)Packet::PACKET_MAX)
			{
				filelog("SharedServerClient.txt", "Packet ID exceed MAX, RECV [%d/%d]" );

				throw InvalidProtocolException("too large packet id");
			}

			try 
			{
				// 패킷 크기가 너무 크면 프로토콜 에러로 간주한다.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
				{
					filelog("SharedServerClient.txt", "Too Larget Packet Size, RECV [%d],PacketSize[%d]" );

					throw InvalidProtocolException("too large packet size");
				}
			
				// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					break;

				// 여기까지 왔다면 입력버퍼에는 완전한 패킷 하나 이상이 들어있다는 뜻이다.
				// 패킷팩토리매니저로부터 패킷아이디를 사용해서 패킷 스트럭처를 생성하면 된다.
				// 패킷아이디가 잘못될 경우는 패킷팩토리매니저에서 처리한다.
				pPacket = g_pPacketFactoryManager->createPacket(packetID);

				// 이제 이 패킷스트럭처를 초기화한다.
				// 패킷하위클래스에 정의된 read()가 virtual 메커니즘에 의해서 호출되어
				// 자동적으로 초기화된다.
				m_pInputStream->readPacket(pPacket);

				// 이제 이 패킷스트럭처를 가지고 패킷핸들러를 수행하면 된다.
				// 패킷아이디가 잘못될 경우는 패킷핸들러매니저에서 처리한다.
				#ifdef __PROFILE_PACKETS__
					
					beginProfileEx(	pPacket->getPacketName().c_str() );
					pPacket->execute(this);
					endProfileEx( pPacket->getPacketName().c_str() );

				#else
					pPacket->execute(this);
				#endif
			} 
			catch (IgnorePacketException & igpe) 
			{
				// 패킷 크기가 너무 크면 프로토콜 에러로 간주한다.
				if (packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID))
					throw InvalidProtocolException("too large packet size");
			
				// 입력버퍼내에 패킷크기만큼의 데이타가 들어있는지 확인한다.
				if (m_pInputStream->length() < szPacketHeader + packetSize)
					break;

				// 데이타가 모두 도착했으면, 그 크기만큼 무시하고,
				// 다른 패킷을 처리하도록 한다....
				m_pInputStream->skip(szPacketHeader + packetSize);

				// 무시된 패킷은, expire 에 영향을 주지 않게 된다.
				// 즉 유효한 패킷만이 짤리지 않게 해준다.
				// 또한 히스토리에도 들어가지 않는다.
			}
		}
	} 
	catch ( InsufficientDataException& ide )
	{
	}

	__END_CATCH
}
		    

//////////////////////////////////////////////////////////////////////
//
// flush output buffer to socket's send buffer
//
// flush할 동안 다른 쓰레드에서 출력 버퍼에 sendPacket을 호출해서는 안된다.
// (이럴 경우는 서버간 통신으로 say가 날아오는 것밖에 없다.)
//
//////////////////////////////////////////////////////////////////////
void SharedServerClient::processOutput () 
     throw (IOException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	try 
	{
		Player::processOutput();
	} 
	catch (InvalidProtocolException & It) 
	{
		throw DisconnectException("Pipe 연결의 파괴로 접속을 짜른다");
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// send packet to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void SharedServerClient::sendPacket (Packet* pPacket) 
	 throw (ProtocolException , Error)
{	
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION(m_Mutex)

	try 
	{
		Player::sendPacket(pPacket);
	} 
	catch (InvalidProtocolException & It) 
	{
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string SharedServerClient::toString () const
       throw (Error)
{
	__BEGIN_TRY
		
	StringStream msg;
	
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	__ENTER_CRITICAL_SECTION(m_Mutex)
	
	msg << "SharedServerClient(SocketID:" << m_pSocket->getSOCKET() << ",Host:" << m_pSocket->getHost() << ")" ;

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	__LEAVE_CRITICAL_SECTION(m_Mutex)
	
	return msg.toString();

	__END_CATCH
}

