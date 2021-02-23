//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddVampirePortal.h 
// Written By  : excel96
// Description :
// 뱀파이어 포탈은 현재 이펙트의 일종으로서 구현되는데, 이 패킷은
// 클라이언트에게 바닥에다 뱀파이어 포탈 이펙트를 붙이라는 패킷이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_VAMPIRE_PORTAL_H__
#define __GC_ADD_VAMPIRE_PORTAL_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampirePortal;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampirePortal : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_VAMPIRE_PORTAL; }
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID + szBYTE + m_OwnerID.size() + szDuration 
			+ szCoord*2 + szZoneID + szCoord*2 + szBYTE;
	}
	string getPacketName() const throw() { return "GCAddVampirePortal"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID(void) const { return m_ObjectID; }
	void setObjectID(ObjectID_t d) { m_ObjectID = d; }

	string getOwnerID(void) const { return m_OwnerID; }
	void setOwnerID(string ownerID) { m_OwnerID = ownerID; }

	Duration_t getDuration() const { return m_Duration; }
	void setDuration(Duration_t d) { m_Duration = d; }

	Coord_t getX(void) const { return m_X; }
	void setX(Coord_t x) { m_X = x; }
	
	Coord_t getY(void) const { return m_Y; }
	void setY(Coord_t x) { m_Y = x; }

	ZoneID_t getTargetZoneID(void) const { return m_TargetZoneID; }
	void setTargetZoneID(ZoneID_t id) { m_TargetZoneID = id; }

	Coord_t getTargetX(void) const { return m_TargetX; }
	void setTargetX(Coord_t x) { m_TargetX = x; }
	
	Coord_t getTargetY(void) const { return m_TargetY; }
	void setTargetY(Coord_t x) { m_TargetY = x; }

	BYTE getCreateFlag(void) const { return m_CreateFlag; }
	void setCreateFlag(BYTE flag) { m_CreateFlag = flag; }

	
private:
	ObjectID_t  m_ObjectID;       // 이펙트의 OID
	string      m_OwnerID;        // 포탈 주인
	Duration_t	m_Duration;       // 포탈의 지속 시간
	Coord_t     m_X;              // 포탈이 붙어있는 타일의 좌표 x
	Coord_t     m_Y;              // 포탈이 붙어있는 타일의 좌표 y
	ZoneID_t    m_TargetZoneID;   // 포탈의 목표 존 ID
	Coord_t     m_TargetX;        // 포탈의 목표 좌표 x
	Coord_t     m_TargetY;        // 포탈의 목표 좌표 y
	BYTE        m_CreateFlag;     // 방금 생성되었는가? (0이면 생성된지 시간이 좀 지난 것...)
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampirePortalFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampirePortalFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddVampirePortal(); }
	string getPacketName() const throw() { return "GCAddVampirePortal"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_VAMPIRE_PORTAL; }
	PacketSize_t getPacketMaxSize() const throw()
	{ 
		return szObjectID + szBYTE + 20 + szDuration 
			+ szCoord*2 + szZoneID + szCoord*2 + szBYTE;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCAddVampirePortalHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddVampirePortalHandler 
{
public:
	static void execute(GCAddVampirePortal* pGCAddVampirePortal, Player* pPlayer) throw(Error);
};

#endif
