//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCPartyPosition.h 
// Written By  : reiot@ewestsoft.com
// Description : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_PARTY_POSITION_H__
#define __GC_PARTY_POSITION_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////
//
// class GCPartyPosition;
//
// 게임 서버에서 특정 사용자가 움직였다는 정보를 클라이언트로 보내줄 
// 때 사용하는 패킷 객체이다.(ObjectID,X,Y,DIR) 을 포함한다.
//
//////////////////////////////////////////////////////////////////////

class GCPartyPosition : public Packet
{
public :
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_PARTY_POSITION; }
	
	// get packet's body size
	// *OPTIMIZATION HINT*
	// const static GCPartyPositionPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketSize() const throw() { return szBYTE + m_Name.size() + szZoneID + szZoneCoord*2 + szHP*2; }

	// get packet's name
	string getPacketName() const throw() { return "GCPartyPosition"; }
	
	// get packet's debug string
	string toString() const throw();


public :
	string	getName() const { return m_Name; }
	void	setName( const string& name ) { m_Name = name; }

	void		setZoneID( ZoneID_t zoneID ) { m_ZoneID = zoneID; }
	ZoneID_t	getZoneID() const { return m_ZoneID; }

	void	setXY( ZoneCoord_t X, ZoneCoord_t Y ) { m_X = X; m_Y = Y; }
	ZoneCoord_t	getX() const { return m_X; }
	ZoneCoord_t getY() const { return m_Y; }

	void	setMaxHP(HP_t hp) { m_MaxHP = hp; }
	HP_t	getMaxHP() const { return m_MaxHP; }

	void	setHP(HP_t hp) { m_HP = hp; }
	HP_t	getHP() const { return m_HP; }

private :
	string	m_Name;
	ZoneID_t	m_ZoneID;
	ZoneCoord_t	m_X, m_Y;
	HP_t	m_MaxHP;
	HP_t	m_HP;
};


//////////////////////////////////////////////////////////////////////
//
// class GCPartyPositionFactory;
//
// Factory for GCPartyPosition
//
//////////////////////////////////////////////////////////////////////

class GCPartyPositionFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCPartyPosition(); }

	// get packet name
	string getPacketName() const throw() { return "GCPartyPosition"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_PARTY_POSITION; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCPartyPositionPacketSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 20 + szZoneID + szZoneCoord*2 + szHP*2; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCPartyPositionHandler;
//
//////////////////////////////////////////////////////////////////////

class GCPartyPositionHandler {

public :

	// execute packet's handler
	static void execute(GCPartyPosition* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
