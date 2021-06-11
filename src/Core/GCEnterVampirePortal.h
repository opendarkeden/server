//////////////////////////////////////////////////////////////////////////////
// Filename    : GCEnterVampirePortal.h 
// Written By  : excel96
// Description : 
// 뱀파이어가 뱀파이어 포탈에 들어가서 사라지는 경우,
// 주위에 브로드캐스팅되는 패킷이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ENTER_VAMPIRE_PORTAL_H__
#define __GC_ENTER_VAMPIRE_PORTAL_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCEnterVampirePortal;
//////////////////////////////////////////////////////////////////////////////

class GCEnterVampirePortal : public Packet 
{
public:
    GCEnterVampirePortal() {};
    ~GCEnterVampirePortal() {};
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_ENTER_VAMPIRE_PORTAL; }
	PacketSize_t getPacketSize() const  { return szObjectID + szCoord*2; }
	string getPacketName() const  { return "GCEnterVampirePortal"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(const ObjectID_t & creatureID)  { m_ObjectID = creatureID; }

	Coord_t getX(void) const { return m_X; }
	void setX(Coord_t X) { m_X = X; }

	Coord_t getY(void) const { return m_Y; }
	void setY(Coord_t Y) { m_Y = Y; }

private:
	ObjectID_t m_ObjectID;
	Coord_t    m_X;
	Coord_t    m_Y;
};

//////////////////////////////////////////////////////////////////////////////
// class GCEnterVampirePortalFactory;
//////////////////////////////////////////////////////////////////////////////

class GCEnterVampirePortalFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCEnterVampirePortal(); }
	string getPacketName() const  { return "GCEnterVampirePortal"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_ENTER_VAMPIRE_PORTAL; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szCoord*2; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCEnterVampirePortalHandler;
//////////////////////////////////////////////////////////////////////////////

class GCEnterVampirePortalHandler 
{
public:
	static void execute(GCEnterVampirePortal* pPacket, Player* pPlayer) ;
};

#endif
