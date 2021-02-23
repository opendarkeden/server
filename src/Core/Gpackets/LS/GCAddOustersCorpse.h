//----------------------------------------------------------------------
// 
// Filename    : GCAddOustersCorpse.h 
// Written By  : Reiot
// 
//----------------------------------------------------------------------

#ifndef __GC_ADD_OUSTERS_CORPSE_H__
#define __GC_ADD_OUSTERS_CORPSE_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"
#include "PCOustersInfo3.h"


//----------------------------------------------------------------------
//
// class GCAddOustersCorpse;
//
//----------------------------------------------------------------------

class GCAddOustersCorpse : public Packet {

public :

	// constructor
	GCAddOustersCorpse() throw() { m_TreasureCount = 0; }
	GCAddOustersCorpse(const PCOustersInfo3 & oustersInfo) throw() : m_OustersInfo(oustersInfo) {}

	
public :

    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_OUSTERS_CORPSE; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return m_OustersInfo.getSize() + szBYTE; }

	// get packet's name
	string getPacketName() const throw() { return "GCAddOustersCorpse"; }
	
	// get packet's debug string
	string toString() const throw();


public :

	// get ousters info
	PCOustersInfo3 & getOustersInfo() throw() { return m_OustersInfo; }
	const PCOustersInfo3 & getOustersInfo() const throw() { return m_OustersInfo; }
	void setOustersInfo(const PCOustersInfo3 & oustersInfo) throw() { m_OustersInfo = oustersInfo; }

	// get/set Treasure Count
	BYTE getTreasureCount() const throw() { return m_TreasureCount; }
	void setTreasureCount(BYTE Count) throw() { m_TreasureCount = Count; }
	
private :
	
	PCOustersInfo3 m_OustersInfo;

	BYTE m_TreasureCount;
	
};


//--------------------------------------------------------------------------------
//
// class GCAddOustersCorpseFactory;
//
// Factory for GCAddOustersCorpse
//
//--------------------------------------------------------------------------------

class GCAddOustersCorpseFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCAddOustersCorpse(); }

	// get packet name
	string getPacketName() const throw() { return "GCAddOustersCorpse"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_OUSTERS_CORPSE; }

	// get packet's body size
	PacketSize_t getPacketMaxSize() const throw() { return PCOustersInfo3::getMaxSize() + szBYTE; }

};


//--------------------------------------------------------------------------------
//
// class GCAddOustersCorpseHandler;
//
//--------------------------------------------------------------------------------

class GCAddOustersCorpseHandler {

public :

	// execute packet's handler
	static void execute(GCAddOustersCorpse* pPacket, Player* pPlayer) throw(Error);

};

#endif
