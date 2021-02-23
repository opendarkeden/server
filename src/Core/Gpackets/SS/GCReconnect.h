//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCReconnect.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_RECONNECT_H__
#define __GC_RECONNECT_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCReconnect;
//
// 서버간 이동시, 이전 서버가 클라이언트에게 다음 서버로 연결하라고 
// 하면서 접속을 끊도록 하는 패킷이다. 클라이언트는 이 패킷을 받으면,
// 서버와의 연결을 끊고 패킷에 담긴 서버의 IP/Port 로 접속하면 된다.
//
//////////////////////////////////////////////////////////////////////

class GCReconnect : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_RECONNECT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szBYTE + m_Name.size() 		// 캐릭터 이름
			+ szPCType 						// 슬레이어 or 뱀파이어?
			+ szBYTE + m_ServerIP.size() 	// 새로 접속할 게임 서버 IP
			+ szDWORD; 						// 인증 키
	}

	// get packet name
	string getPacketName() const throw() { return "GCReconnect"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set creature name
	string getName() const throw() { return m_Name; }
	void setName(const string & name) throw() { m_Name = name; }

	// get/set pc type
	PCType getPCType() const throw() { return m_PCType; }
	void setPCType(PCType pcType) throw() { m_PCType = pcType; }

	// get/set server ip
	string getServerIP() const throw() { return m_ServerIP; }
	void setServerIP(const string & serverIP) throw() { m_ServerIP = serverIP; }

	// get/set key
	DWORD getKey() const throw() { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

private :
	
	// creature name
	string m_Name;

	// pc type
	PCType m_PCType;
	
	// New Server IP
	string m_ServerIP;

	// authentication key
	DWORD m_Key;

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectFactory;
//
// Factory for GCReconnect
//
//////////////////////////////////////////////////////////////////////

class GCReconnectFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCReconnect(); }

	// get packet name
	string getPacketName() const throw() { return "GCReconnect"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_RECONNECT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCReconnectPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw()
	{
		return szBYTE + 20 		 		// 캐릭터 이름
			+ szPCType 					// 슬레이어 or 뱀파이어?
			+ szBYTE + 15			 	// 새로 접속할 게임 서버 IP
			+ szDWORD; 					// 인증 키
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCReconnectHandler;
//
//////////////////////////////////////////////////////////////////////

class GCReconnectHandler {

public :

	// execute packet's handler
	static void execute(GCReconnect* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
