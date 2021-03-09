//--------------------------------------------------------------------------------
// 
// Filename    : GCSearchMotorcycleOK.h 
// Written By  : 김성민
// Description : 플레이어에게 서버 측의 상점 버전을 알려줄 때 쓰이는 패킷이다.
// 
//--------------------------------------------------------------------------------

#ifndef __GC_SEARCH_MOTORCYCLE_OK_H__
#define __GC_SEARCH_MOTORCYCLE_OK_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//--------------------------------------------------------------------------------
//
// class GCSearchMotorcycleOK;
//
//--------------------------------------------------------------------------------

class GCSearchMotorcycleOK : public Packet 
{
public :
    GCSearchMotorcycleOK() {};
    ~GCSearchMotorcycleOK() {};
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_SEARCH_MOTORCYCLE_OK; }
	PacketSize_t getPacketSize() const  { return szZoneID+szCoord*2; }
	string getPacketName() const  { return "GCSearchMotorcycleOK"; }
	string toString() const ;

public :
	ZoneID_t getZoneID(void) const   { return m_ZoneID;}
	Coord_t  getX(void) const        { return m_ZoneX;}
	Coord_t  getY(void) const        { return m_ZoneY;}
	void     setZoneID(ZoneID_t id)  { m_ZoneID = id;}
	void     setX(Coord_t x)         { m_ZoneX = x;}
	void     setY(Coord_t y)         { m_ZoneY = y;}

private :
	ZoneID_t m_ZoneID;
	Coord_t  m_ZoneX;
	Coord_t  m_ZoneY;

};


//////////////////////////////////////////////////////////////////////
//
// class GCSearchMotorcycleOKFactory;
//
// Factory for GCSearchMotorcycleOK
//
//////////////////////////////////////////////////////////////////////

class GCSearchMotorcycleOKFactory : public PacketFactory 
{

public :
	
	// create packet
	Packet* createPacket()  { return new GCSearchMotorcycleOK(); }

	// get packet name
	string getPacketName() const  { return "GCSearchMotorcycleOK"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_SEARCH_MOTORCYCLE_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSearchMotorcycleOKPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const  { return szZoneID + szCoord*2; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCSearchMotorcycleOKHandler;
//
//////////////////////////////////////////////////////////////////////

class GCSearchMotorcycleOKHandler 
{
	
public :
	
	// execute packet's handler
	static void execute(GCSearchMotorcycleOK* pPacket, Player* pPlayer) ;

};

#endif
