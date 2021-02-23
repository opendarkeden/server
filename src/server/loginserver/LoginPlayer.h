//////////////////////////////////////////////////////////////////////
// 
// Filename    : LoginPlayer.h 
// Written by  : reiot@ewestsoft.com
// Description : 게임 서버용 플레이어 클래스
// 
//////////////////////////////////////////////////////////////////////

#ifndef __LOGIN_PLAYER_H__
#define __LOGIN_PLAYER_H__

// include files
#include "Player.h"
#include "Mutex.h"
#include "PlayerStatus.h"
#include <deque>
#include "Timeval.h"
#include "PaySystem.h"
#include "gameserver/billing/BillingPlayerInfo.h"
#include "chinabilling/CBillingPlayerInfo.h"
#include "Gpackets/GCReconnectLogin.h"

#include "Packet.h"

class LCPCList;

//////////////////////////////////////////////////////////////////////
//
// class LoginPlayer
//
// 게임 서버용 플레이어 클래스
//
// Player 클래스를 상속받아서, 게임 서버에서만 사용되는 Mutex 및 
// Creature 관련 데이터 및 메쏘드, PreviousPacket 관련 데이터 및
// 메소드들을 추가했다.
//
// 특히 processOutput() 및 sendPacket()은 Race Condition 이 발생될 수
// 있으므로, Mutex 로 보호되어야 한다. ( MODE-IV의 경우이며, MODE-I, II
// 의 경우에는 processInput(), processCommand() 모두 Mutex 로 보호해야
// 한다.)
//
//////////////////////////////////////////////////////////////////////

class LoginPlayer : public Player, public PaySystem, public BillingPlayerInfo, public CBillingPlayerInfo {

public :

	// 저장해놓을 이전 패킷의 개수
	static const uint nPacketHistory = 10;

	static const uint maxFailure  = 3;

public :
	
	// constructor
	LoginPlayer (Socket * pSocket) throw ( Error );
	
	// destructor
	~LoginPlayer () throw ( Error );

	// read socket's receive buffer and fill input buffer
	//virtual void processInput () throw ( IOException , Error );
	
	// parse packet and execute handler for the packet
	virtual void processCommand ( bool Option = true ) throw ( IOException , Error );
	
	// flush output buffer to socket's send buffer
	//virtual void processOutput () throw ( IOException , Error );
	
	// send packet to player's output buffer
	virtual void sendPacket ( Packet * packet ) throw ( ProtocolException , Error );

	// disconnect
	// 정식 로그아웃의 경우 disconnect(LOGOUT)
	virtual void disconnect ( bool bDisconnected = DISCONNECTED ) throw ( Error );
	virtual void disconnect_nolog ( bool bDisconnected = DISCONNECTED ) throw ( Error );

	
	// get debug string
	virtual string toString () const throw ( Error );
	
public :

	// return recent N-th packet
	// 최근 전송된 N 번째 패킷을 리턴한다.
	Packet * getOldPacket ( uint prev = 0 ) throw ( OutOfBoundException , NoSuchElementException );

	// return recent packet which has packetID
	// 특정 ID를 가진 패킷 중 가장 최근의 패킷을 리턴한다.
	Packet * getOldPacket ( PacketID_t packetID ) throw ( NoSuchElementException );

	// get/set player's status
	PlayerStatus getPlayerStatus () const throw () { return m_PlayerStatus; }
	void setPlayerStatus ( PlayerStatus playerStatus ) throw () { m_PlayerStatus = playerStatus; }

	// 실패한 회수
	uint getFailureCount () const throw () { return m_FailureCount; }
	void setFailureCount ( uint nFailed ) throw () { m_FailureCount = nFailed; }

    // get / set GoreLevel
    bool isAdult() const throw() { return m_isAdult; }
    void setAdult(bool isAdult) throw() { m_isAdult = isAdult; }

public :
	int		getKickCharacterCount() const throw()	{ return m_KickCharacterCount; }	
	void 	setExpireTimeForKickCharacter() throw();

	// 현재 월드의 ID
	WorldID_t getWorldID() const throw() { return m_WorldID; }
	void setWorldID( WorldID_t WorldID ) throw() { m_WorldID = WorldID; }

	// 현재 서버의 ID
	WorldID_t getGroupID() const throw() { return m_ServerGroupID; }
	void setGroupID( ServerGroupID_t ServerGroupID ) throw() { m_ServerGroupID = ServerGroupID; }

	// 현재 서버의 ID
	uint getLastSlot() const throw() { return m_LastSlot; }
	void setLastSlot( uint lastSlot ) throw() { m_LastSlot = lastSlot; }

    // WorldID, GroupID가 설정되었나?
    bool isSetWorldGroupID() const throw() { return m_bSetWorldGroupID; }
    void setWorldGroupID(bool bSet) throw() { m_bSetWorldGroupID = bSet; }

    // 마지막으로 접속한 캐릭터의 이름
	const string& getLastCharacterName() const throw() { return m_LastCharacterName; }
	void setLastCharacterName( const string& name ) throw() { m_LastCharacterName = name; }

	const string& getZipcode() const throw() { return m_Zipcode; }
	void setZipcode( const string& zipcode ) throw() { m_Zipcode = zipcode; }

	const string& getSSN() const throw() { return m_SSN; }
	void setSSN( const string& ssn ) throw() { m_SSN = ssn; }

	bool isFreePass() const	{ return m_bFreePass; }
	void setFreePass(bool bFreePass=true) { m_bFreePass = bFreePass; }

	bool isWebLogin() const { return m_bWebLogin; }
	void setWebLogin( bool bWebLogin = true ) { m_bWebLogin = bWebLogin; }

	void makePCList( LCPCList& lcPCList ) throw( DisconnectException );

public :
	void sendLGKickCharacter() throw();
	void sendLCLoginOK() throw();

public :
	void    setBillingSession() throw (Error)   { BillingPlayerInfo::setBillingSession(this); }
	bool    sendBillingLogin() throw (Error);


private :
	
	// previous packet queue
	deque<Packet *> m_PacketHistory;

	// player status
	PlayerStatus m_PlayerStatus;

	// expire time 
	Timeval m_ExpireTime;

	// 캐릭터 등록(CLRegisterPlayer) 또는 로그인(CLLogin)에 실패한 회수
	uint m_FailureCount;

	// mutex
	mutable Mutex m_Mutex;

	// 현재 월드 ID
	bool			m_bSetWorldGroupID;
	WorldID_t 		m_WorldID;
	ServerGroupID_t m_ServerGroupID;
	uint			m_LastSlot;
	string			m_LastCharacterName;

	// LoginPlayerData때문에.. T_T;
	string			m_SSN;
	string			m_Zipcode;

	bool m_isAdult;

	// '이미 접속 중'인 경우 캐릭터 강제 접속 해제 대기 시간
	uint    m_KickCharacterCount;
	Timeval m_ExpireTimeForKickCharacter;	

	// 다른 곳에서 검증(넷마블)을 받았다고 하고.. FreePass를 받는다. - -; by sigi. 2002.10.23
	bool 			m_bFreePass;

	// 웹 로그인 모드
	bool			m_bWebLogin;
};

#endif
