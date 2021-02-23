//////////////////////////////////////////////////////////////////////
// 
// Filename    : Player.h 
// Written by  : reiot@ewestsoft.com
// Description : 게임서버/로그인서버/테스트 클라이언트용 플레이어 클래스
// 
//////////////////////////////////////////////////////////////////////

#ifndef __PLAYER_H__
#define __PLAYER_H__

// include files
#include "Types.h"
#include "Exception.h"

// forward declaration
class Socket;
class SocketInputStream;
class SocketOutputStream;
class Packet;

//////////////////////////////////////////////////////////////////////
//
// class Player
//
// 플레이어는 시스템 객체로, 연결된 하나의 클라이언트와 대응된다.
// TCP 소켓과 소켓입출력스트림을 내부에 가지며, 패킷 입출력/처리 메쏘드를
// 갖고 있다. 게임서버/로그인서버/테스트클라이언트에서는 이 클래스를
// 상속받아서 사용하게 된다.?
//
// *CAUTION*
//
// 특히 게임서버나 로그인서버의 경우, 이 클래스를 상속받은 클래스에서
// 동기화(Mutex Lock/Unlock)를 해줘야 한다.
//
//////////////////////////////////////////////////////////////////////

const bool UNDISCONNECTED = true;
const bool DISCONNECTED   = false;

class Player {

public :

	// constructor
	Player () throw (Error);
	Player (Socket * pSocket) throw ( Error );
	
	// destructor
	virtual ~Player () throw (Error);

	// read socket's receive buffer and fill input buffer
	virtual void processInput () throw (IOException, Error);
	
	// parse packet and execute handler for the packet
	virtual void processCommand (bool Option = true) throw (IOException, Error);
	
	// flush output buffer to socket's send buffer
	virtual void processOutput () throw (IOException, Error, ProtocolException);
	
	// send packet to player's output buffer
	virtual void sendPacket (Packet* pPacket) throw (ProtocolException, Error);

	// send stream to player's output buffer
	virtual void sendStream( SocketOutputStream* pOutputStream ) throw (ProtocolException, Error);

	// disconnect
	// 플레이어의 연결을 종료할 때, 상대편이 적절하게 로그아웃하지 않을 경우 소켓의 연결이 
	// 이미 끊겨 있으므로 disconnect(DISCONNECTED) 를 사용해서 연결을 종료해야 한다. 반면, 
	// 정당하게 로그아웃을 한 경우에는 disconnect(UNDISCONNECTED) 를 사용해야 한다.
	virtual void disconnect (bool bDisconnected = DISCONNECTED) throw (InvalidProtocolException, Error);
	
	// get/set socket
	Socket* getSocket () throw () { return m_pSocket; }
	void setSocket (Socket* pSocket) throw ();

	// get/set player ID
	string getID () const throw () { return m_ID; }
	void setID (const string & id) throw () { m_ID = id; }

	// get / set ServerGroupID
	ServerGroupID_t getServerGroupID() const throw() { return m_ServerGroupID; }
	void setServerGroupID(const ServerGroupID_t ServerGroupID) throw() { m_ServerGroupID = ServerGroupID; }

	// get / set MAC Address
	const BYTE* getMacAddress() const { return m_MacAddress; }
	void setMacAddress(const BYTE* ma) { copy( ma, ma+6, (BYTE*)m_MacAddress ); }

	// get debug string
	virtual string toString () const throw (Error);

	//add by viva
	//void setKey(WORD EncryptKey, WORD HashKey) throw(); 
	
protected :

	// player id
	string m_ID;
	
	// TCP client socket
	Socket* m_pSocket;
	
	// buffered socket input stream
	SocketInputStream* m_pInputStream;

	// buffered socket output stream
	SocketOutputStream* m_pOutputStream;

	// 이 플레이어가 현재 존재하는 서버의 위치
	ServerGroupID_t m_ServerGroupID;

	// MAC Address
	BYTE m_MacAddress[6];

	//add by viva 2008-12-31
	//BYTE* pHashTable;
};

#endif
