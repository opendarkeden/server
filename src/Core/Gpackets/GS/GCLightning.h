//--------------------------------------------------------------------------------
// 
// Filename    : GCLightning.h 
// Written By  : reiot
// 
//--------------------------------------------------------------------------------

#ifndef __GC_LIGHTNING_H__
#define __GC_LIGHTNING_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCLightning;
//
// 번개가 쳤을 경우, 서버에서 그 존의 모든 클라이언트들에게 전송하는 패킷이다.
// 
//
//////////////////////////////////////////////////////////////////////

class GCLightning : public Packet {

public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_LIGHTNING; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCLightningPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const throw() { return szBYTE; }

	// get packet's name
	string getPacketName() const throw() { return "GCLightning"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get/set delay
	BYTE getDelay() const throw() { return m_Delay; }
	void setDelay(BYTE delay) throw() { m_Delay = delay; }


private :

	// 번개가 친 후, 천둥이 올 때까지의 딜레이시간
	// 1 -> 0.1초
	BYTE m_Delay;

};


//////////////////////////////////////////////////////////////////////
//
// class GCLightningFactory;
//
// Factory for GCLightning
//
//////////////////////////////////////////////////////////////////////

class GCLightningFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCLightning(); }

	// get packet name
	string getPacketName() const throw() { return "GCLightning"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_LIGHTNING; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCLightningPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCLightningHandler;
//
//////////////////////////////////////////////////////////////////////

class GCLightningHandler {

public :

	// execute packet's handler
	static void execute(GCLightning* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
