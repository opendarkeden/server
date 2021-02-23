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
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SEARCH_MOTORCYCLE_OK; }
	PacketSize_t getPacketSize() const throw() { return szZoneID+szCoord*2; }
	string getPacketName() const throw() { return "GCSearchMotorcycleOK"; }
	string toString() const throw();

public :
	ZoneID_t getZoneID(void) const throw()  { return m_ZoneID;}
	Coord_t  getX(void) const throw()       { return m_ZoneX;}
	Coord_t  getY(void) const throw()       { return m_ZoneY;}
	void     setZoneID(ZoneID_t id) throw() { m_ZoneID = id;}
	void     setX(Coord_t x) throw()        { m_ZoneX = x;}
	void     setY(Coord_t y) throw()        { m_ZoneY = y;}

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
	Packet* createPacket() throw() { return new GCSearchMotorcycleOK(); }

	// get packet name
	string getPacketName() const throw() { return "GCSearchMotorcycleOK"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SEARCH_MOTORCYCLE_OK; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSearchMotorcycleOKPacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szZoneID + szCoord*2; }

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
	static void execute(GCSearchMotorcycleOK* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
