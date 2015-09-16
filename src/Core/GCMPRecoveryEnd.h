//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCMPRecoveryEnd.h 
// Written By  : Reiot
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_MP_RECOVERY_END_H__
#define __GC_MP_RECOVERY_END_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "EffectInfo.h"


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEnd;
//
////////////////////////////////////////////////////////////////////

class GCMPRecoveryEnd : public Packet {

public :

	GCMPRecoveryEnd() throw(Error);

	virtual ~GCMPRecoveryEnd() throw(Error);
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_MP_RECOVERY_END; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCMPRecoveryEndPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szMP; 
	}

	// get packet's name
	string getPacketName() const throw() { return "GCMPRecoveryEnd"; }
	
	// get packet's debug string
	string toString() const throw();

public :

	// get /set CurrentMP
	MP_t getCurrentMP() const throw() { return m_CurrentMP; }
	void setCurrentMP(MP_t CurrentMP) throw() { m_CurrentMP = CurrentMP; }

private :
	
	// 현재 체력
	MP_t m_CurrentMP;

};


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEndFactory;
//
// Factory for GCMPRecoveryEnd
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryEndFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCMPRecoveryEnd(); }

	// get packet name
	string getPacketName() const throw() { return "GCMPRecoveryEnd"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_MP_RECOVERY_END; }

	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCMPRecoveryEndPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szMP; 
	}

};


//////////////////////////////////////////////////////////////////////
//
// class GCMPRecoveryEndHandler;
//
//////////////////////////////////////////////////////////////////////

class GCMPRecoveryEndHandler {

public :

	// execute packet's handler
	static void execute(GCMPRecoveryEnd* pPacket, Player* pPlayer) throw(Error);

};

#endif
