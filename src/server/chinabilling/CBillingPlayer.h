/////////////////////////////////////////////////////////////////////
//
// filename		: CBillingPlayer.h
//
/////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_PLAYER__
#define __CBILLING_PLAYER__

// include file
#include "Types.h"
#include "Exception.h"
#include "Player.h"

// forward declaration
class Packet;
class CBillingPacketHeader;
class CBillingPacketErrorBody;

#ifdef __LOGIN_SERVER__
	class LoginPlayer;
	class CBillingPacketResponseLoginBody;
#elif defined(__GAME_SERVER__)
	class GamePlayer;
	class CBillingPacketResponseIntervalValidationBody;
	class CBillingPacketResponseLoginBody;
	class CBillingPacketResponseMinusPointBody;
	class CBillingPacketResponseMinusMinuteBody;
	class CBillingPacketResponseLogoutBody;
#endif

/////////////////////////////////////////////
// class CBillingPlayer
/////////////////////////////////////////////

class CBillingPlayer : public Player
{
public:
	// constructor & destructor
	CBillingPlayer();
	CBillingPlayer( Socket* pSocket );

	virtual ~CBillingPlayer();

public:
	
	// network read / write
	virtual void processInput();
	virtual void processOutput();

	// parse packet and execute handler for the packet
	virtual void processCommand();

	// send packet to player's output buffer
	virtual void sendPacket( Packet* pPacket );

	// disconnect
	// 플레이어의 연결을 종료할 때, 상대편이 적절하게 로그아웃하지 않을 경우 소켓의 연결이
	// 이미 끊겨 있으므로 disconnect(DISCONNECTED) 를 사용하새 연결을 종료해야 한다.
	// 반면, 정장하게 로그아웃을 한 경우에는 disconnect(UNDISCONNECTED) 를 사용해야한다.
	virtual void disconnect( bool bDisconnected = DISCONNECTED );

	void setSocket( Socket* pSocket );

	// get debug string
	virtual string toString() const;

public:

#ifdef __LOGIN_SERVER__
	void sendLogin( LoginPlayer* pLoginPlayer );
#elif defined(__GAME_SERVER__)
	void sendIntervalValidation();
	void sendLogin( GamePlayer* pGamePlayer );
	void sendMinusPoint( GamePlayer* pGamePlayer );
	void sendMinusMinute( GamePlayer* pGamePlayer );
	void sendLogout( GamePlayer* pGamePlayer );
#endif

public:
	// 패킷 처리용 함수들
	void executeError( CBillingPacketHeader& header, CBillingPacketErrorBody& body );
#ifdef __LOGIN_SERVER__
	void executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body );
#elif defined(__GAME_SERVER__)
	void executeIntervalValidation( CBillingPacketHeader& header, CBillingPacketResponseIntervalValidationBody& body );
	void executeLogin( CBillingPacketHeader& header, CBillingPacketResponseLoginBody& body );
	void executeMinusPoint( CBillingPacketHeader& header, CBillingPacketResponseMinusPointBody& body );
	void executeMinusMinute( CBillingPacketHeader& header, CBillingPacketResponseMinusMinuteBody& body );
	void executeLogout( CBillingPacketHeader& header, CBillingPacketResponseLogoutBody& body );
#endif

#ifdef __GAME_SERVER__
	// DB에 packet 로그 남기기
	void logPacket( CBillingPacketHeader* header, CBillingPacketResponseLoginBody* login, CBillingPacketResponseMinusPointBody* point, CBillingPacketResponseLogoutBody* logout, CBillingPacketErrorBody* error );
#endif

public:
#ifdef __GAME_SERVER__
	void checkSessionID( CBillingPacketHeader& header, GamePlayer* pGamePlayer );
#endif
};

#endif

