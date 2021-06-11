//////////////////////////////////////////////////////////////////////////////
// Filename    : GCKnockBack.h 
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_KNOCK_BACK_H__
#define __GC_KNOCK_BACK_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class GCKnockBack;
//////////////////////////////////////////////////////////////////////////////

class GCKnockBack : public Packet 
{
public:
	GCKnockBack()   {}
	~GCKnockBack()  {}

public:
    void read(SocketInputStream & iStream) ;
    void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_KNOCK_BACK; }
	PacketSize_t getPacketSize() const  { return szObjectID + szZoneCoord*4; }
	string getPacketName() const  { return "GCKnockBack"; }
	string toString() const ;

public:
	ObjectID_t getObjectID() const { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) { m_ObjectID = ObjectID; }

	ZoneCoord_t getOriginX(void) const { return m_OriginX; }
	void setOriginX(ZoneCoord_t x) { m_OriginX = x; }

	ZoneCoord_t getOriginY(void) const { return m_OriginY; }
	void setOriginY(ZoneCoord_t y) { m_OriginY = y; }

	ZoneCoord_t getTargetX(void) const { return m_TargetX; }
	void setTargetX(ZoneCoord_t x) { m_TargetX = x; }

	void setTargetY(ZoneCoord_t y) { m_TargetY = y; }
	ZoneCoord_t getTargetY(void) const { return m_TargetY; }

	void setOrigin(ZoneCoord_t x, ZoneCoord_t y)  { setOriginX(x); setOriginY(y); }
	void setTarget(ZoneCoord_t x, ZoneCoord_t y)  { setTargetX(x); setTargetY(y); }

private:
	ObjectID_t  m_ObjectID;
	ZoneCoord_t m_OriginX;
	ZoneCoord_t m_OriginY;
	ZoneCoord_t m_TargetX;
	ZoneCoord_t m_TargetY;
};

//////////////////////////////////////////////////////////////////////////////
// class GCKnockBackFactory;
//////////////////////////////////////////////////////////////////////////////

class GCKnockBackFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCKnockBack(); }
	string getPacketName() const  { return "GCKnockBack"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_KNOCK_BACK; }
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szZoneCoord*4; }
};

//////////////////////////////////////////////////////////////////////////////
// class GCKnockBackHandler;
//////////////////////////////////////////////////////////////////////////////

class GCKnockBackHandler 
{
public:
	static void execute(GCKnockBack* pGCKnockBack, Player* pPlayer) ;

};

#endif
