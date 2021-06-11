//--------------------------------------------------------------------------------
// 
// Filename    : GCSearchMotorcycleFail.h 
// Written By  : 김성민
// Description : 플레이어에게 서버 측의 상점 버전을 알려줄 때 쓰이는 패킷이다.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SEARCH_MOTORCYCLE_FAIL_H__
#define __GC_SEARCH_MOTORCYCLE_FAIL_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCSearchMotorcycleFail;
//
//--------------------------------------------------------------------------------

class GCSearchMotorcycleFail : public Packet 
{
public :
    GCSearchMotorcycleFail() {};
    ~GCSearchMotorcycleFail() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SEARCH_MOTORCYCLE_FAIL; }
	PacketSize_t getPacketSize() const  { return 0; }
	string getPacketName() const  { return "GCSearchMotorcycleFail"; }
	string toString() const ;
};


//////////////////////////////////////////////////////////////////////
//
// class GCSearchMotorcycleFailFactory;
//
// Factory for GCSearchMotorcycleFail
//
//////////////////////////////////////////////////////////////////////

class GCSearchMotorcycleFailFactory : public PacketFactory 
{

public :
	
	Packet* createPacket()  { return new GCSearchMotorcycleFail(); }
	string getPacketName() const  { return "GCSearchMotorcycleFail"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SEARCH_MOTORCYCLE_FAIL; }
	PacketSize_t getPacketMaxSize() const  { return 0; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSearchMotorcycleFailHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSearchMotorcycleFailHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCSearchMotorcycleFail* pPacket, Player* pPlayer) ;

};

#endif
