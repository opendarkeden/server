/////////////////////////////////////////////////////////////////////
//
// filename		: SBillingPlayer.h
//
/////////////////////////////////////////////////////////////////////

#ifndef __SBILLING_PLAYER__
#define __SBILLING_PLAYER__

// include file
#include "Types.h"
#include "Exception.h"
#include "Player.h"

// forward declaration
class PayUser;
class Packet;
class CBillingPacketHeader;
class CBillingPacketErrorBody;

class CBillingPacketResponseIntervalValidationBody;
class CBillingPacketResponseLoginBody;
class CBillingPacketResponseMinusPointBody;
class CBillingPacketResponseMinusMinuteBody;
class CBillingPacketResponseLogoutBody;

/////////////////////////////////////////////
// class SBillingPlayer
/////////////////////////////////////////////

class SBillingPlayer : public Player
{
public:
	// constructor & destructor
	SBillingPlayer() throw ( Error );
	SBillingPlayer( Socket* pSocket ) throw ( Error );

	virtual ~SBillingPlayer() throw ( Error );

public:
	
	// network read / write
	virtual void processInput() throw ( IOException, Error );
	virtual void processOutput() throw ( IOException, Error );

	// parse packet and execute handler for the packet
	virtual void processCommand() throw ( IOException, Error );

	// send packet to player's output buffer
	virtual void sendPacket( Packet* pPacket ) throw ( ProtocolException, Error );

	// disconnect
	// 플레이어의 연결을 종료할 때, 상대편이 적절하게 로그아웃하지 않을 경우 소켓의 연결이
	// 이미 끊겨 있으므로 disconnect(DISCONNECTED) 를 사용하새 연결을 종료해야 한다.
	// 반면, 정장하게 로그아웃을 한 경우에는 disconnect(UNDISCONNECTED) 를 사용해야한다.
	virtual void disconnect( bool bDisconnected = DISCONNECTED ) throw ( InvalidProtocolException, Error );

	void setSocket( Socket* pSocket ) throw ();

	// get debug string
	virtual string toString() const throw ( Error );

public:
	void sendIntervalValidation() throw ( ProtocolException, Error );
	void sendLogin( PayUser* pPayUser ) throw ( ProtocolException, Error );
	void sendMinusPoint( PayUser* pPayUser ) throw ( ProtocolException, Error );
	void sendMinusMinute( PayUser* pPayUser ) throw ( ProtocolException, Error );
	void sendLogout( PayUser* pPayUser ) throw ( ProtocolException, Error );

public:
	// 패킷 처리용 함수들
	void executeError( CBillingPacketHeader& header, CBillingPacketErrorBody& body ) throw ( IOException, Error );
	void executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketResponseIntervalValidationBody& body ) throw ( IOException, Error );
	void executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body ) throw ( IOException, Error );
	void executeMinusPoint( CBillingPacketHeader& header, CBillingPacketResponseMinusPointBody& body ) throw ( IOException, Error );
	void executeMinusMinute( CBillingPacketHeader& header, CBillingPacketResponseMinusMinuteBody& body ) throw ( IOException, Error );
	void executeLogout( CBillingPacketHeader& header, CBillingPacketResponseLogoutBody& body ) throw ( IOException, Error );

public:
};

#endif

