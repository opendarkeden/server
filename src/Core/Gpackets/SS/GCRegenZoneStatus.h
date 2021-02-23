//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCRegenZoneStatus.h 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_REGEN_ZONE_STATUS_H__
#define __GC_REGEN_ZONE_STATUS_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

#include <vector>

//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatus;
//
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatus : public Packet {

public :
	GCRegenZoneStatus() { for( int i=0; i<8; ++i ) m_Statuses.push_back(0); }
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_REGEN_ZONE_STATUS; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw() { return szBYTE * 8; }

	// get packet name
	string getPacketName() const throw() { return "GCRegenZoneStatus"; }
	
	// get packet's debug string
	string toString() const throw();

	BYTE getStatus( uint index ) const { return m_Statuses[index]; }
	void setStatus( uint index, BYTE status ) { m_Statuses[index] = status; }

private :
	vector<BYTE>	m_Statuses;
};


//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatusFactory;
//
// Factory for GCRegenZoneStatus
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatusFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCRegenZoneStatus(); }

	// get packet name
	string getPacketName() const throw() { return "GCRegenZoneStatus"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_REGEN_ZONE_STATUS; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCRegenZoneStatusPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE * 8; } 
};


//////////////////////////////////////////////////////////////////////
//
// class GCRegenZoneStatusHandler;
//
//////////////////////////////////////////////////////////////////////

class GCRegenZoneStatusHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCRegenZoneStatus* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
